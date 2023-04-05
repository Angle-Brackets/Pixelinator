#ifndef SDLCENGINE_CORE_H
#define SDLCENGINE_CORE_H

#include <SDL_mixer.h>
#include "types.h"
#include "render/render.h"

#define VERIFY_LOW_BOUND(x, min, name) {if(x < min){fprintf(stderr, "Illegal value for %s passed.\n", name); return 1;}} //Validates if an entered value is not lower than a given value. Can't check a max because multiple monitors might screw with it too much.

typedef enum engine_state {
    UNFOCUSED = 0x1 << 0, //If the window is not currently focused, the engine will pause.
    FOCUSED = 0x1 << 1, //If the window is focused, the engine will be running.
} Engine_State;

/**
 * You must call this function before you render anything to initialize the engine. Do not call this more than once unless if you know what you're doing.
 * @param window_width Width in pixels of the window
 * @param window_height Height in pixels of the window
 * @param bitmap_width Width in pixels of the bitmap - unused if the BITMAP_ENABLED Render Flag is omitted.
 * @param bitmap_height Height in pixels of the bitmap - unused if the BITMAP_ENABLED Render Flag is omitted.
 * @param max_fps Max fps cap for the engine to attempt to reach, may be limited by VSYNC of monitor if not disabled with the DISABLE_VSYNC Render Flag.
 * @param volume Starting volume for both music and sfx.
 * @param render_flags Flags to modify attributes of the rendering pipeline. It is recommended that MULTITHREADING_ENABLED is passed at minimum for a performance gain.
 *                     If you want access to bitmap graphics, pass the BITMAP_ENABLED flag, otherwise they will not work.
 * @param sound_flags Flags to modify attributes of the sound pipeline. By default MP3 (Music) and WAV (SFX) are automatically supported. If that is all that's needed, then pass 0.
 * @param draw_func You must provide an implementation for this function! This function is run every frame and is primarily used to render pixels to the screen.
 *
 * @return 0 for success, 1 if an error occurred.
 */
i32 initialize(u32 window_width, u32 window_height, u32 bitmap_width, u32 bitmap_height, u32 max_fps, u32 volume, Render_Flags render_flags, MIX_InitFlags sound_flags, void (*draw_func)());

/**
 * Starts the program, must call initialize() before this function.
 */
void start();

/**
 * Closes the program
 */
void exit_program();


#endif //SDLCENGINE_CORE_H
