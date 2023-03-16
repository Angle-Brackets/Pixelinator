#ifndef PIXELINATOR_SPRITE_H
#define PIXELINATOR_SPRITE_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../types.h"

typedef struct SPRITE_SHEET {
    const char* sheet_path;
    SDL_Surface* sheet_data;
    SDL_Color* ignored_colors; //Most sprite sheets have non-transparent backgrounds for sprites, these colors are ignored when rendering.
    u32 ignored_colors_len;
} sprite_sheet;

typedef struct Sprite {
    i32 x;
    i32 y;
    u32 width;
    u32 height;
    SDL_Color** sprite_data; //Pixel data - Dimensions are width x height and passed into the bitmap at the x,y position
    sprite_sheet* sheet;
} sprite_t;

/**
 * Creates a bitmap sprite with or without an existing sprite sheet
 * @param x X position of the sprite
 * @param y Y Position of the sprite
 * @param width Width of the sprite
 * @param height Height of the sprite
 * @param sheet Optional sprite sheet for the sprite to reference, pass NULL if unneeded
 * @return A new sprite, NULL on failure
 */
sprite_t* create_sprite(i32 x, i32 y, u32 width, u32 height, sprite_sheet* sheet);

/**
 * Creates a sprite sheet that can be used for multiple sprites to reference
 * @param file_path file path to sprite sheet (currently only PNGs are supported)
 * @param ignored_colors colors to ignore when reading from the sprite sheet
 * @param ignored_colors_len length of ignored colors array
 * @return A new sprite sheet, NULL on failure
 */
sprite_sheet* create_sprite_sheet(const char* file_path, SDL_Color* ignored_colors, u32 ignored_colors_len);

/**
 * Update the provided sprite by drawing pixels from the sprite sheet.
 * The function finds a rectangular box with the dimensions provided and draws the pixel information into the sprite provided.
 * The information is written to the sprite starting at (sprite_x, sprite_y) and is the same dimensions as the rectangular region read from.
 * @param sprite sprite to update
 * @param sheet_x top left corner of new sprite data in sheet
 * @param sheet_y top left corner of new sprite data in sheet
 * @param sprite_x leftmost x position of where to begin writing new sprite data
 * @param sprite_y topmost y position of where to begin writing new sprite data
 * @param width width of sprite in sheet
 * @param height height of sprite in sheet
 * @return true if successfully updated, false if not.
 */
bool update_sprite_from_spritesheet(sprite_t* sprite, u32 sheet_x, u32 sheet_y, u32 sprite_x, u32 sprite_y, u32 width, u32 height);

/**
 * Frees the associated sprite, DOES NOT FREE THE SPRITE SHEET!
 */
void free_sprite(sprite_t* sprite);

/**
 * Frees the associated sprite sheet
 */
void free_sprite_sheet(sprite_sheet* sheet);


#endif //PIXELINATOR_SPRITE_H
