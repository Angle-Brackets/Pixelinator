#ifndef SDLCENGINE_RENDER_H
#define SDLCENGINE_RENDER_H

#include <SDL2/SDL.h>
#include <linmath.h>
#include "../types.h"

//Stored in an 4 byte unsigned integer.
//Could also be stored in a union, but this is more flexible.
typedef enum render_flags {
    BITMAP_ACTIVE = 0x1, //Flag to set the bitmap to be activated.
    UNUSED_1 = 0x1 << 1,
    UNUSED_2 = 0x1 << 2,
    UNUSED_3 = 0x1 << 3,
    UNUSED_4 = 0x1 << 4,
    UNUSED_5 = 0x1 << 5,
    UNUSED_6 = 0x1 << 6,
    UNUSED_7 = 0x1 << 7,
} Render_Flags;

typedef struct render_state {
    SDL_Window* window;
    SDL_Renderer* renderer;
    u32 width;
    u32 height;
} Render_State;

/**
 * Initializes Renderer
 * @param flags Flags to tell the renderer what additional resources it needs to initialize, if none are needed, input 0.
 */
void render_init(u32 width, u32 height, enum render_flags flags);
/**
 * Start render pass
 */
void render_begin(void);
/**
 * Finish render pass
 */
void render_end(void);

#endif //SDLCENGINE_RENDER_H
