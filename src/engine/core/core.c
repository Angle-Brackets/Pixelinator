#include "core/core.h"
#include "util.h"
#include "time.h"
#include "input/input.h"
#include "audio/sound.h"
#include "graphics/bitmap.h"
#include "global.h"

static bool running = false;
static void (*draw)() = NULL;

/**
 * Used to poll universal events like closing the window or if its size changes.
 */
static void poll_events(){
    SDL_Event event;

    //This might be moved to be an event.h/event.c file FOR EVERY event to be polled.
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit_program();
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        global.render.width = event.window.data1;
                        global.render.height = event.window.data2;
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        global.engine = FOCUSED;
                        if(!(global.render_flags & IGNORE_FOCUS))
                            resume_audio();
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        global.engine = UNFOCUSED;
                        if(!(global.render_flags & IGNORE_FOCUS))
                            pause_audio();
                        break;
                }
            default:
                break;
        }
    }
}

/**
 * The draw loop effectively, run every frame.
 */
static void loop(){
  poll_events();
  time_update();

  //Will not update screen if the window is not focused, unless appropriate render flag is set.
  if(global.engine & FOCUSED || global.render_flags & IGNORE_FOCUS){
      render_begin();
      input_update();
      draw();
      render_end();
  }

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
        ERROR_RETURN(1, "Could not access given function, make sure they are defined.\n")
    }

    //Setup draw function
    draw = draw_func;

    //Start engine
    running = true;
    global.engine = FOCUSED;

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

