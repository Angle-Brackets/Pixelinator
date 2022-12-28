#ifndef SDLCENGINE_RENDER_INTERNAL_H
#define SDLCENGINE_RENDER_INTERNAL_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../types.h"
#include "render.h"

typedef struct render_state_internal {
    u32 shader_default;
    u32 texture_color;
} Render_State_Internal;

void initialize_SDL(const char* name, u32 width, u32 height);


#endif //SDLCENGINE_RENDER_INTERNAL_H
