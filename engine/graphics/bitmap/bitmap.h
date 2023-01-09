#ifndef SDLCENGINE_BITMAP_H
#define SDLCENGINE_BITMAP_H

#include <SDL.h>
#include <stdbool.h>
#include "../../types.h"

typedef struct bitmap_state {
    u32 width;
    u32 height;
    SDL_Color tint;
    SDL_Color stroke_fill;
    SDL_Color shape_fill;
} Bitmap_State;
/**
 * Sets the fill color of the pixel's being currently drawn
 * @param color
 */
void set_background_fill(SDL_Color* color);

/**
 * Sets the outline color for the edge of bitmap shapes drawn
 * @param color
 */
void set_stroke_fill(SDL_Color* color);

/**
 * Sets the inner fill color of bitmap shapes drawn.
 * @param color
 */
void set_shape_fill(SDL_Color* color);

/**
 * Draws a pixel to the screen at the x, y position
 * @param color
 * @param x
 * @param y
 */
void draw_pixel(SDL_Color* color, i32 x, i32 y);

/**
 * Draw pixels from a given texture into the bitmap
 * Does not necessarily clear the entire bitmap if the width and height of the texture aren't the same as the Bitmap!
 * @param surface
 */
void draw_pixels_from_surface(SDL_Surface* surface);

/**
 * Draws the pixel buffer stored in memory to a bitmap texture.
 */
void draw_pixel_buffer();

/**
 * Sets the tint of the bitmap (multiplies the rgb values against the bitmap texture before rendering)
 * Default is 255,255,255, or white (no tint).
 * @param color
 */
void set_bitmap_tint(SDL_Color* color);

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
