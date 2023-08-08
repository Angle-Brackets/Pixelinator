#ifndef PIXELINATOR_PIXELINATOR_H
#define PIXELINATOR_PIXELINATOR_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

//May make this into a single header file include for all the code, but not right now.

//Global information
#include "global.h"
#include "time.h"
#include "types.h"
#include "util.h"

//Audio
#include "audio/sound.h"

//Config
#include "config/config.h"

//Core
#include "core/core.h"

//Graphics
#include "graphics/bitmap.h"
#include "graphics/shapes.h"
#include "graphics/sprite.h"

//Input
#include "input/input.h"

//IO
#include "io/io.h"

//Render
#include "render/render.h"

//Text
#include "text/text.h"
#include "text/SDL_FontCache.h"

#endif //PIXELINATOR_PIXELINATOR_H
