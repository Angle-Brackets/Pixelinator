#include <SDL2/SDL.h>

#include "../util.h"
#include "../global.h"
#include "render.h"
#include "render_internal.h"

void initialize_SDL(const char* name, u32 width, u32 height, Render_Flags flags){
    global.render.window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);

    if(global.render.window == NULL){
        ERROR_EXIT("Failed to initialize window\n")
    }

    global.render.renderer = SDL_CreateRenderer(global.render.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | (flags & DISABLE_VSYNC ? 0 : SDL_RENDERER_PRESENTVSYNC));

    if(global.render.renderer == NULL){
        ERROR_EXIT("Failed to initialize renderer.\n")
    }

    SDL_SetWindowTitle(global.render.window, name);
    SDL_Color c = {0,0,0,0};
    set_background_clear(&c);

    struct SDL_RendererInfo info;
    SDL_GetRendererInfo(global.render.renderer, &info);

    printf("%s Renderer Loaded\n", info.name);
}

