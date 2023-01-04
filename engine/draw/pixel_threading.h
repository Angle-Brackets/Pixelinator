#ifndef SDLCENGINE_PIXEL_THREADING_H
#define SDLCENGINE_PIXEL_THREADING_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include "../types.h"
#include "util.h"

#define THREADS 8
#define VERIFY_HEAP_DATA(pointer) { if(pointer == NULL){fprintf(stderr, "Ran out of memory.\n"); exit(1);} }

struct pixel_args {
    u32** pixel_rows; //Pixel rows to write to
    u32 pixel_row_count; //Number of pixel rows to write to
    u32 pixel_length; //Length of each pixel row

    SDL_Color** new_pixel_data; //Bitmap pixel data to write to pixel rows
    u32 new_pixel_data_rows; //Number of bitmap rows to read from
    u32 new_pixel_data_length; //Length of a bitmap row
    SDL_PixelFormat* format; //Pixel format for colors (maybe unused)
};

/**
 * Will write pixel data to each row stored in the struct passed
 * @param args - pixel_args struct
 * @return NULL
 */
void* update_pixels(void* args);

/**
 * Function to call to begin processing pixels with the given color data.
 * @param pixels - Pixel array to write to
 * @param color_data - Color data to write to pixel array
 * @param format - Pixel format
 * @param bitmap_height - height of the bitmap
 * @param bitmap_width - width of the bitmap
 * @param pitch - size of row in bytes
 * @param scale_x - Bitmap scale factor for x
 * @param scale_y - Bitmap scale factor for y
 */
void process_pixels(void* pixels, SDL_Color** color_data, SDL_PixelFormat* format, u32 bitmap_width, u32 bitmap_height, u32 pitch, u32 scale_x, u32 scale_y);

#endif //SDLCENGINE_PIXEL_THREADING_H
