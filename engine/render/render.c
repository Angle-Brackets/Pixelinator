#include "render.h"
#include "../global.h"
#include "render_internal.h"

static Render_State_Internal state = {0};

void render_init(u32 width, u32 height, Render_Flags flags) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    global.render.width = width;
    global.render.height = height;
    initialize_SDL("Engine", global.render.width, global.render.height);
    //Makes the interpolation the nicest it can be.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    //Set flags
    global.render_flags = flags;
}

void render_begin(void){
    SDL_RenderClear(global.render.renderer);
}

void render_end(void){
    //Updates bitmap and writes it to a texture.
    if(bitmap_initialized) {
        draw_pixel_buffer();
        SDL_RenderCopy(global.render.renderer, bitmap, NULL, NULL);
    }

    SDL_RenderPresent(global.render.renderer);
}
