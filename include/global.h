#ifndef SDLCENGINE_GLOBAL_H
#define SDLCENGINE_GLOBAL_H

#include "core/core.h"
#include "render/render.h"
#include "config/config.h"
#include "graphics/bitmap.h"
#include "audio/sound.h"
#include "controller/controller.h"
#include "time.h"

typedef struct global {
    //State variables - Contain information about the program
    Engine_State engine;
    Render_State render;
    Config_State config;
    Bitmap_State bitmap;
    Time_State time;
    Sound_State sound;
    Controller_State controller;

    //Flags
    Render_Flags render_flags;
} Global;

extern Global global;
#endif //SDLCENGINE_GLOBAL_H
