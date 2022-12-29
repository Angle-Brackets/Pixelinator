#ifndef SDLCENGINE_PIXEL_H
#define SDLCENGINE_PIXEL_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../global.h"
#include "../types.h"

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
 */
void initialize_bitmap();

//Global texture used for drawing bitmap graphics
extern SDL_Texture* bitmap;
extern bool bitmap_initialized;

#endif //SDLCENGINE_PIXEL_H
