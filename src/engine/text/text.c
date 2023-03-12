#include "text/text.h"
#include "global.h"

PIX_Font* load_pix_font(const char* font_path, u32 font_size, SDL_Color color){
    PIX_Font* font = FC_CreateFont();
    FC_LoadFont(font, global.render.renderer, font_path, font_size, color, TTF_STYLE_NORMAL);
    return font;
}

void free_pix_font(PIX_Font* font){
    FC_FreeFont(font);
    font = NULL;
}
