#ifndef SDLCENGINE_GLOBAL_H
#define SDLCENGINE_GLOBAL_H

#include "render/render.h"

typedef struct global {
    Render_State render;
} Global;

extern Global global;
#endif //SDLCENGINE_GLOBAL_H
