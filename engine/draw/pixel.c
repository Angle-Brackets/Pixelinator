#include <SDL2/SDL.h>
#include <string.h>
#include "../util.h"
#include "../global.h"
#include "pixel.h"

//2D array that is initialized to be a 2D matrix of pixels that is HEIGHT, WIDTH (rows and cols)
static SDL_Color** pixel_buffer = NULL;
//Bitmap for drawing pixels to screen
SDL_Texture* bitmap = NULL;

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

void draw_pixel(SDL_Color* color, i32 x, i32 y){
    if(pixel_buffer == NULL){
        ERROR_EXIT("Pixel Buffer not initialized, run initialize_bitmap() before any draw calls!")
    }

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

void initialize_bitmap(){
    static bool initialized = false;

    if(!initialized) {
        if ((pixel_buffer = (SDL_Color**)calloc(global.render.height, sizeof(SDL_Color*))) == NULL) {
            ERROR_EXIT("Failed to initialize pixel buffer rows.\n")
        }

        for (int i = 0; i < global.render.height; i++) {
            pixel_buffer[i] = (SDL_Color*)calloc(global.render.width, sizeof(SDL_Color));

            if (pixel_buffer[i] == NULL) {
                ERROR_EXIT("Failed to initialize pixel buffer columns.\n")
            }
        }

        bitmap = SDL_CreateTexture(global.render.renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, global.render.width, global.render.height);

        if(bitmap == NULL){
            ERROR_EXIT("Failed to initialize bitmap matrix.\n")
        }

        initialized = true;
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

    if(SDL_LockTexture(bitmap, NULL, &pixels, &pitch) != 0){
        ERROR_EXIT("Couldn't lock texture for bitmap.\n")
    }

    //The reason why we need to update all the pixels is that it is not a safe assumption to say that
    //the read in pixels are going to be initialized with the current screen colors, SDL does not guarantee this!
    for(int i = 0; i < global.render.height; i++){
        current_row = (u32*)((u8*)pixels + i * pitch);
        for(int j = 0; j < global.render.width; j++){
            current_row[j] = SDL_MapRGBA(format,
                                         pixel_buffer[i][j].r,
                                         pixel_buffer[i][j].g,
                                         pixel_buffer[i][j].b,
                                         pixel_buffer[i][j].a);
        }
    }

    SDL_UnlockTexture(bitmap);
    SDL_FreeFormat(format);
}
