#ifndef SDLCENGINE_RENDER_H
#define SDLCENGINE_RENDER_H
#include <SDL.h>
#include "types.h"

//Stored in an 4 byte unsigned integer.
//Could also be stored in a union, but this is more flexible.
typedef enum render_flags {
    BITMAP_ACTIVE = 0x1, //Flag to set the bitmap to be activated.
    MULTITHREADING_ENABLED = 0x1 << 1, //Flag to enable multithreading
    DISABLE_VSYNC = 0x1 << 2, //Flag to disable vsync
    IGNORE_FOCUS = 0x1 << 3, //Will ignore if the window is focused or not (will still draw if not focused for example)
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

/**
 * Change the window size forcefully. Both must be greater than zero, otherwise it will give a warning.
 * @param width New width of window
 * @param height New height of window.
 *
 */
void set_window_size(i32 width, i32 height);

#endif //SDLCENGINE_RENDER_H
