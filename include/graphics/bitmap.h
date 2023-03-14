#ifndef SDLCENGINE_BITMAP_H
#define SDLCENGINE_BITMAP_H

#include <SDL.h>
#include <math.h>
#include <stdbool.h>
#include "../types.h"
#include "sprite.h"

typedef struct bitmap_state {
    u32 width;
    u32 height;
    u32 rotation;
    SDL_Color tint;
    SDL_Color stroke_fill;
    SDL_Color shape_fill;
    SDL_Rect transform;

    //Debug/Performance Logging Features
    u32 bitmap_calls; //Number of pixels attempted to be drawn to the bitmap in a frame.
    u32 bitmap_updates; //Number of pixels updated by the bitmap per frame.
} Bitmap_State;
/**
 * Sets the clear color (color used after rendering a frame) of the window
 * @param color
 */
void set_background_clear(SDL_Color* color);

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
 * Fills the screen with a particular color
 * @param color
 */
void fill_background(SDL_Color* color);

/**
 * Draws a pixel to the screen at the x, y position
 * @param color
 * @param x
 * @param y
 */
void draw_pixel(SDL_Color* color, i32 x, i32 y);

/**
 * Draws a sprite to the bitmap.
 * @param sprite
 */
void draw_sprite_to_bitmap(sprite_t* sprite);

/**
 * Draw pixels from a given texture into the bitmap
 * Does not necessarily clear the entire bitmap if the width and height of the texture aren't the same as the Bitmap!
 * @param surface
 */
void draw_pixels_from_surface(SDL_Surface* surface);

/**
 * Rotate the bitmap by a given amount of degrees
 * @param degrees 0 - 360 degree rotation on the bitmap after its done rendering (Any values larger are moved into this range)
 */
void rotate_bitmap_deg(u32 degrees);

/**
 * Rotate the bitmap by a given amount of radians
 * @param degrees 0 - 2π degree rotation on the bitmap after its done rendering (Any values larger are moved into this range)
 */
void rotate_bitmap_rad(f64 radians);

/**
 * Will move the position that the bitmap is rendering to the new x and y positions given.
 * @param x New x position to start rendering from (top left hand corner of rectangular region)
 * @param y New y position to start rendering from (top left hand corner of rectangular region)
 */
void bitmap_shift(i32 x, i32 y);

/**
 * Scale the bitmap by a percentage of the window width and height to zoom in or out of the bitmap
 * @param width_scale percentage from 0 - 500% for the width of the window
 * @param height_scale percentage from 0 - 500% for the height of the window
 */
void bitmap_scale(u32 width_scale, u32 height_scale);

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

/**
 * Draw the bitmap to the screen, the order in which you call this DOES matter. (For example, render the bitmap, then place text so you can see it!)
 */
void draw_bitmap();

//Global texture used for drawing bitmap graphics
extern SDL_Texture* bitmap;
extern bool bitmap_initialized;

#endif //SDLCENGINE_BITMAP_H
