#ifndef SDLCENGINE_GLOBAL_H
#define SDLCENGINE_GLOBAL_H

#include "render/render.h"
#include "config/config.h"
#include "input/input.h"
#include "time.h"

typedef struct global {
    Render_State render;
    Config_State config;
    Input_State input;
    Time_State time;
} Global;

extern Global global;
#endif //SDLCENGINE_GLOBAL_H
