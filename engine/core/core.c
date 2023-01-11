#include "core.h"
#include "../util.h"
#include "../time.h"
#include "../input/input.h"
#include "../audio/sound.h"
#include "../graphics/bitmap/bitmap.h"
#include "../global.h"
#define SDL_MAIN_HANDLED

static bool running = false;
static void (*draw)() = NULL;

/**
 * The draw loop effectively, run every frame.
 */
static void loop(){
  time_update();
  render_begin();
  input_update();
  draw();
  render_end();
  time_update_late();
}

i32 initialize(u32 window_width, u32 window_height, u32 bitmap_width, u32 bitmap_height, u32 max_fps, u32 volume,
               Render_Flags render_flags, MIX_InitFlags sound_flags, void (*draw_func)()) {
    //Verify bounds
    VERIFY_LOW_BOUND(window_width, 0, "width")
    VERIFY_LOW_BOUND(window_height, 0, "height")
    VERIFY_LOW_BOUND(bitmap_width, window_width, "bitmap width")
    VERIFY_LOW_BOUND(bitmap_height, window_height, "bitmap height")
    VERIFY_LOW_BOUND(max_fps, 0, "maximum fps")
    VERIFY_LOW_BOUND(volume, 0, "volume")

    //Set max fps
    time_init(max_fps);
    //Initialize input devices
    init_input();
    //Initialize Sounds
    volume = volume > 100 ? 100 : volume;
    if(init_mixer(sound_flags, volume) != 0){
        return 1;
    }
    //Initialize Renderer + Some warnings
    render_init(window_width, window_height, render_flags);
    if(!(render_flags & MULTITHREADING_ENABLED)){
        WARN("Multithreading is currently disabled, if you want to enable it pass the MULTITHREADING_ENABLED flag into the Render Flags argument!\n")
    }
    //Initialize bitmap if desired
    if(render_flags & BITMAP_ACTIVE){
        initialize_bitmap(bitmap_width, bitmap_height);
    }
    else if(bitmap_width > 0 || bitmap_height > 0){
        WARN("Bitmap was not initialized despite nonzero width and/or height provided, make sure you passed the BITMAP_ACTIVE flag to the Render Flags argument!\n")
    }

    if(draw_func == NULL){
        ERROR_RETURN(1, "Could not access given function(s), make sure they are defined.\n")
    }

    //Setup draw function
    draw = draw_func;

    //Start engine
    running = true;

    return 0;
}

void exit_program() {
    running = false;
}

void start(){
    if(!running){
        WARN("Call initialize() before running start!\n")
        return;
    }

    while(running){
        loop();
    }

    //Cleanup code - It can reach this code, don't worry about it.
    SDL_DestroyRenderer(global.render.renderer);
    SDL_DestroyWindow(global.render.window);
    quit_mixer();
    SDL_Quit();
}

