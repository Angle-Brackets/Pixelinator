#include "graphics/pixel_threading.h"

static pthread_t pixel_threads[THREADS]; //The amount of threads does not change during the course of the program
static u32 bmp_scale_x = 1;
static u32 bmp_scale_y = 1;

void* update_pixels(void* args){
    struct pixel_args* pix_args = (struct pixel_args*)args;

    for(u32 i = 0; i < pix_args->new_pixel_data_rows; i++){
        for(u32 j = 0; j < pix_args->new_pixel_data_length; j++) {
            u32 color = SDL_MapRGBA(pix_args->format,
                                    pix_args->new_pixel_data[i][j].r,
                                    pix_args->new_pixel_data[i][j].g,
                                    pix_args->new_pixel_data[i][j].b,
                                    pix_args->new_pixel_data[i][j].a);

            for(u32 y = 0; y < bmp_scale_y; y++){
                u32* current_row = pix_args->pixel_rows[i * bmp_scale_y + y];
                for(u32 x = 0; x < bmp_scale_x; x++){
                    current_row[j * bmp_scale_x + x] = color;
                }
            }

        }
    }

    return NULL;
}

void process_pixels(void* pixels, SDL_Color** color_data, SDL_PixelFormat* format, u32 bitmap_width, u32 bitmap_height, u32 pitch, u32 scale_x, u32 scale_y){
    //This has to be malloc as opposed to a SAA because the SAA variables might get reused, which is bad behavior for threading.
    struct pixel_args** all_arguments = (struct pixel_args**)malloc(sizeof(struct pixel_args*) * THREADS);
    VERIFY_HEAP_DATA(all_arguments)
    bmp_scale_x = scale_x;
    bmp_scale_y = scale_y;
    u32 rows_per_thread = bitmap_height / THREADS; //NUMBER OF BITMAP PIXELS FOR EACH THREAD TO MAP TO TEXTURE

    //Any extra rows left over will be given for the main thread to process.
    for(u32 i = 0; i < THREADS; i++){
        all_arguments[i] = (struct pixel_args*)malloc(sizeof(struct pixel_args));
        VERIFY_HEAP_DATA(all_arguments[i]);
        all_arguments[i]->pixel_rows = (u32**)malloc(sizeof(u32*) * rows_per_thread * bmp_scale_y);
        VERIFY_HEAP_DATA(all_arguments[i]->pixel_rows)
        all_arguments[i]->new_pixel_data = (SDL_Color**)malloc(sizeof(SDL_Color*) * rows_per_thread);
        VERIFY_HEAP_DATA(all_arguments[i]->new_pixel_data)

        all_arguments[i]->new_pixel_data_rows = rows_per_thread;
        all_arguments[i]->new_pixel_data_length = bitmap_width;

        all_arguments[i]->pixel_row_count = rows_per_thread * bmp_scale_y;
        all_arguments[i]->pixel_length = bitmap_width * bmp_scale_x;
        all_arguments[i]->format = format;

        //Send the bitmap pixels for us to write to the pixel texture
        for(u32 j = i * rows_per_thread; j < rows_per_thread * (1 + i); j++){
            all_arguments[i]->new_pixel_data[j % rows_per_thread] = color_data[j];
        }

        //Send the texture pixels to write to
        for(u32 j = i * all_arguments[i]->pixel_row_count; j < all_arguments[i]->pixel_row_count * (1 + i); j++){
            //Gets each row of the pixel array and stores it in the struct for the thread to use.
            //from Kronecker's product in the y direction, the x direction is handled by the threads themselves.
            all_arguments[i]->pixel_rows[j % (rows_per_thread * bmp_scale_y)] = (u32*)((u8*)pixels + j * pitch);
        }

        pthread_create(&pixel_threads[i], NULL, update_pixels, all_arguments[i]);
    }

    for(int i = 0; i < THREADS; i++){
        pthread_join(pixel_threads[i], NULL);
    }

    //Any remaining rows can be completed by the main thread (if it evenly divides, nothing happens here)
    u32 remaining = bitmap_height % THREADS;
    for(u32 j = bitmap_height - remaining; j < bitmap_height; j++){
        for(u32 k = 0; k < bitmap_width; k++){
            u32 color = SDL_MapRGBA(format,
                                    color_data[j][k].r,
                                    color_data[j][k].g,
                                    color_data[j][k].b,
                                    color_data[j][k].a);

            for(u32 y = 0; y < bmp_scale_y; y++){
                u32* current_row = (u32*)((u8*)pixels + (j * bmp_scale_y + y) * pitch);
                for(u32 x = 0; x < bmp_scale_x; x++){
                    current_row[k * bmp_scale_x + x] = color;
                }
            }
        }
    }

    //Free up memory!
    for(u32 i = 0; i < THREADS; i++){
        CLEAR_FREE(all_arguments[i]->pixel_rows)
        CLEAR_FREE(all_arguments[i]->new_pixel_data)
        CLEAR_FREE(all_arguments[i])
    }

    CLEAR_FREE(all_arguments)
}