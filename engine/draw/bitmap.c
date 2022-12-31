#include <SDL2/SDL.h>
#include <string.h>
#include "../util.h"
#include "../global.h"
#include "bitmap.h"

static SDL_Color** pixel_buffer = NULL; //2D array that is initialized to be a 2D matrix of pixels that is HEIGHT, WIDTH (rows and cols)
static u32 bitmap_scale_x = 1; //Field for appropriately scaling the bitmap to fit the screen width (X values)
static u32 bitmap_scale_y = 1; //Field for appropriately scaling the bitmap to fit the screen height (Y values)
SDL_Texture* bitmap = NULL; //Bitmap for drawing pixels to screen
bool bitmap_initialized = false; //Field to tell if we've initialized bitmap graphics

void set_fill_color(SDL_Color* color){
    if(color != NULL) {
        if (SDL_SetRenderDrawColor(global.render.renderer, color->r, color->g, color->b, color->a) != 0) {
            ERROR_EXIT("Failed to set default render draw color.\n")
        }
    }
    else if(SDL_SetRenderDrawColor(global.render.renderer, 0, 0, 0, 0) != 0) {
        ERROR_EXIT("Failed to set default render draw color.\n")
    }
}

static i32 clamp(i32 value, i32 min, i32 max){
    if(value < min)
        value = min;
    else if(value > max)
        value = max;
    return value;
}

void draw_pixel(SDL_Color* color, i32 x, i32 y){
    if(pixel_buffer == NULL){
        ERROR_EXIT("Pixel Buffer not initialized, run initialize_bitmap() before any draw calls!")
    }

    //Will clamp to appropriate x,y.
    x = clamp(x, 0, global.bitmap.width);
    y = clamp(y, 0, global.bitmap.height);

    //Update the pixel buffer, this does not draw to the screen just yet, we use draw_pixel_buffer() to do that.
    if(color != NULL){
        pixel_buffer[y][x].r = color->r;
        pixel_buffer[y][x].g = color->g;
        pixel_buffer[y][x].b = color->b;
        pixel_buffer[y][x].a = color->a;
    }
    else{
        //If it is NULL it is just set to zero.
        memset(pixel_buffer, 0, sizeof(SDL_Color));
    }
}

void initialize_bitmap(u32 width, u32 height){
    if(!bitmap_initialized) {
        Bitmap_State bmp;
        bmp.width = global.render.width;
        bmp.height = global.render.height;

        if(width > 0)
            bmp.width = width;
        if(height > 0)
            bmp.height = height;

        global.bitmap = bmp; //Copies the bitmap state information to global

        //Sets the scale-factor to be the largest, strictly less-than integer multiple of the with and height
        //This is so that we can repeat this many pixels on the X,Y axes and THEN use a interpolation algorithm to scale the bitmap for larger resolutions.
        bitmap_scale_x = floor(global.render.width / global.bitmap.width);
        bitmap_scale_y = floor(global.render.height / global.bitmap.height);

        if ((pixel_buffer = (SDL_Color**)calloc(global.bitmap.height, sizeof(SDL_Color*))) == NULL) {
            ERROR_EXIT("Failed to initialize pixel buffer rows.\n")
        }

        for (int i = 0; i < global.bitmap.height; i++) {
            pixel_buffer[i] = (SDL_Color*)calloc(global.bitmap.width, sizeof(SDL_Color));

            if (pixel_buffer[i] == NULL) {
                ERROR_EXIT("Failed to initialize pixel buffer columns.\n")
            }
        }

        bitmap = SDL_CreateTexture(global.render.renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, global.bitmap.width * bitmap_scale_x, global.bitmap.height * bitmap_scale_y);

        if(bitmap == NULL){
            ERROR_EXIT("Failed to initialize bitmap matrix.\n")
        }

        bitmap_initialized = true;
    }
    else {
        WARN("Repeated usage of initialize_bitmap() is disallowed and undefined, remove any repeated references to this function.")
    }
}

void draw_pixel_buffer(){
    SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32); //Format (really want this to be static...)
    void* pixels; //Read-Only Pixels read from the image to update (flattened 2D array).
    u32* current_row; //Current row of pixels we're writing to.
    i32 pitch; //Length of one row in bytes...I have no idea why it's called pitch.

    //Need to reset the texture in case the window size changed.
    bitmap_scale_x = global.render.width / global.bitmap.width;
    bitmap_scale_y = global.render.height / global.bitmap.height;

    SDL_DestroyTexture(bitmap);
    bitmap = SDL_CreateTexture(global.render.renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, global.bitmap.width * bitmap_scale_x, global.bitmap.height * bitmap_scale_y);

    if(SDL_LockTexture(bitmap, NULL, &pixels, &pitch) != 0){
        //Just exits and retries to render this the next frame.
        //We do this to just avoid a crash and this only happens if the window size changes rapidly.
        return;
    }

    //The reason why we need to update all the pixels is that it is not a safe assumption to say that
    //the read in pixels are going to be bitmap_initialized with the current screen colors, SDL does not guarantee this!

    //u32 rather than SDL_Color is used because the texture interprets the bits as colors correctly.
    for(int i = 0; i < global.bitmap.height; i++){
        for(int j = 0; j < global.bitmap.width; j++){
            u32 color = SDL_MapRGBA(format,
                        pixel_buffer[i][j].r,
                        pixel_buffer[i][j].g,
                        pixel_buffer[i][j].b,
                        pixel_buffer[i][j].a);

            for(int y = 0; y < bitmap_scale_y; y++){
                for(int x = 0; x < bitmap_scale_x; x++){
                    current_row = (u32*)((u8*)pixels + (i * bitmap_scale_y + y) * pitch);
                    current_row[j * bitmap_scale_x + x] = color;
                }
            }

        }
    }

    SDL_UnlockTexture(bitmap);
    SDL_FreeFormat(format);
}
