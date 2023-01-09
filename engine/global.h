#ifndef SDLCENGINE_GLOBAL_H
#define SDLCENGINE_GLOBAL_H

#include "render/render.h"
#include "config/config.h"
#include "input/input.h"
#include "graphics/bitmap/bitmap.h"
#include "audio/sound.h"
#include "time.h"

typedef struct global {
    //State variables - Contain information about the program
    Render_State render;
    Config_State config;
    Input_State input;
    Bitmap_State bitmap;
    Time_State time;
    Sound_State sound;

    //Flags
    Render_Flags render_flags;
} Global;

extern Global global;
#endif //SDLCENGINE_GLOBAL_H
