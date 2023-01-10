#include "../../global.h"
#include "../../types.h"

#ifndef SDLCENGINE_SHAPES_H
#define SDLCENGINE_SHAPES_H


/**
 * Draw a single point to the bitmap
 * @param x
 * @param y
 */
void draw_point(u32 x, u32 y);
/**
 * Draw a line to the bitmap
 * @param x1 start x position
 * @param y1 start y position
 * @param x2 end x position
 * @param y2 end y position
 */
void draw_line(u32 x1, u32 y1, u32 x2, u32 y2);
/**
 * Draw a square to the bitmap
 * @param x0 top left hand corner of square
 * @param y0 top left hand corner of square
 * @param s size of square
 */
void draw_square(u32 x0, u32 y0, u32 s);
/**
 * Draw a rectangle to the bitmap
 * @param x0 top left hand corner of rectangle
 * @param y0 top left hand corner of rectangle
 * @param w width of the rectangle
 * @param h height of the rectangle
 */
void draw_rect(u32 x0, u32 y0, u32 w, u32 h);
/**
 * Draw a circle to the bitmap
 * @param x0 center x position of the circle
 * @param y0 center y position of the circle
 * @param r radius of the circle
 */
void draw_circle(u32 x0, u32 y0, u32 r);

#endif //SDLCENGINE_SHAPES_H
