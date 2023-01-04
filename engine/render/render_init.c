#include <SDL2/SDL.h>

#include "../util.h"
#include "../global.h"
#include "render.h"
#include "render_internal.h"

void initialize_SDL(const char* name, u32 width, u32 height){
    int result = SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &global.render.window, &global.render.renderer);

    if(result != 0){
        ERROR_EXIT("Failed to initialize window and renderer.\n")
    }

    SDL_SetWindowTitle(global.render.window, name);
    SDL_Color c = {0,0,0,0};
    set_fill_color(&c);

    struct SDL_RendererInfo info;
    SDL_GetRendererInfo(global.render.renderer, &info);

    printf("%s Renderer Loaded\n", info.name);
}

