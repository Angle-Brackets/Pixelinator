#ifndef PIXELINATOR_TEXT_H
#define PIXELINATOR_TEXT_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../../src/engine/font_cache/SDL_FontCache.h"
#include "../types.h"

typedef FC_Font PIX_Font;
typedef enum PIX_ALIGN {
    LEFT = FC_ALIGN_LEFT,
    CENTER = FC_ALIGN_CENTER,
    RIGHT = FC_ALIGN_RIGHT
} PIX_Align;

/**
 * Create a text structure to be used to render strings.
 * @param font_path path to font file
 * @param font_size size of text to render
 * @param color font color
 * @return A heap allocated Font object that can be used to render text to the screen. NULL on failure.
 */
PIX_Font* load_pix_font(const char* font_path, u32 font_size, SDL_Color color);

//Basically just aliased a function to not confuse people.
/**
 * @param font PIX_FONT font to render as
 * @param x f32 x position
 * @param y f32 y position
 * @param align Pix-Align parameter for how to align the text (left, center, right)
 * @param formatted_text Format string for text
 * @return SDL_Rect the text was rendered to if desired.
 */
#define render_text(font, x, y, align, fstring, ...) FC_DrawAlign(font, global.render.renderer, x, y, (FC_AlignEnum)align, fstring, ##__VA_ARGS__)

/**
 * Frees memory associated with a font
 * @param font font to free
 */
void free_pix_font(PIX_Font* font);

#endif
