#ifndef SDLCENGINE_BITMAP_H
#define SDLCENGINE_BITMAP_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../types.h"

typedef struct bitmap_state {
    u32 width;
    u32 height;
} Bitmap_State;
/**
 * Sets the fill color of the pixel's being currently drawn
 * @param red
 * @param green
 * @param blue
 * @param alpha
 */
void set_fill_color(SDL_Color* color);

/**
 * Draws a pixel to the screen at the x, y position
 * @param SDL_Color* color
 * @param x
 * @param y
 */
void draw_pixel(SDL_Color* color, i32 x, i32 y);

/**
 * Draws the pixel buffer stored in memory to a bitmap texture.
 */
void draw_pixel_buffer();

/**
 * DO NOT USE MORE THAN ONCE!
 * Initializes pixel buffer used for drawing bitmap graphics
 * @param width Width of bitmap in pixels
 * @param height Height of bitmap in pixels
 */
void initialize_bitmap(u32 width, u32 height);

//Global texture used for drawing bitmap graphics
extern SDL_Texture* bitmap;
extern bool bitmap_initialized;

#endif //SDLCENGINE_BITMAP_H
