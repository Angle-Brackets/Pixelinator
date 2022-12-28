#include "render.h"
#include "../global.h"
#include "render_internal.h"
#include "../draw/pixel.h"

static Render_State_Internal state = {0};

void render_init(void) {
    SDL_Init(SDL_INIT_VIDEO);
    global.render.width = 800;
    global.render.height = 224;
    initialize_SDL("Engine", global.render.width, global.render.height);
    initialize_bitmap();
}

void render_begin(void){
    SDL_RenderClear(global.render.renderer);
}

void render_end(void){
    //Updates bitmap and writes it to a texture.
    draw_pixel_buffer();
    SDL_RenderCopy(global.render.renderer, bitmap, NULL, NULL);

    SDL_RenderPresent(global.render.renderer);
}
