#ifndef SDLCENGINE_RENDER_H
#define SDLCENGINE_RENDER_H

#include <SDL2/SDL.h>
#include <linmath.h>

#include "../types.h"

typedef struct render_state {
    SDL_Window* window;
    SDL_Renderer* renderer;
    u32 width;
    u32 height;
} Render_State;

void render_init(void);
void render_begin(void);
void render_end(void);

#endif //SDLCENGINE_RENDER_H
