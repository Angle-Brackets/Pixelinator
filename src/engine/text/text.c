#include "text/text.h"
#include "global.h"
static PIX_Font* default_font = NULL;

PIX_Font* load_pix_font(const char* font_path, u32 font_size, SDL_Color color){
    PIX_Font* font = FC_CreateFont();
    FC_LoadFont(font, global.render.renderer, font_path, font_size, color, TTF_STYLE_NORMAL);
    return font;
}

bool set_default_font(PIX_Font* font){
    if(font == NULL){
        return false;
    }
    default_font = font;
    return true;
}

PIX_Font* get_default_font(){
    return default_font;
}

void free_pix_font(PIX_Font* font){
    FC_FreeFont(font);
    font = NULL;
}
