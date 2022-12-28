#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "engine/time.h"
#include "engine/global.h"
#include "engine/config/config.h"
#include "engine/input/input.h"
#include "engine/draw/pixel.h"
#define SDL_MAIN_HANDLED

static bool running = false;
static vec2 pos;

//Unused
static void input_handle(void) {
    if (global.input.left == KS_PRESSED || global.input.left == KS_HELD)
        pos[0] -= 500 * global.time.delta;
    if (global.input.right == KS_PRESSED || global.input.right == KS_HELD)
        pos[0] += 500 * global.time.delta;
    if (global.input.up == KS_PRESSED || global.input.up == KS_HELD)
        pos[1] += 500 * global.time.delta;
    if (global.input.down == KS_PRESSED || global.input.down == KS_HELD)
        pos[1] -= 500 * global.time.delta;
    if (global.input.escape == KS_PRESSED || global.input.escape == KS_HELD)
        running = false;
}

int main() {
    time_init(60);
    config_init();
    render_init();

    running = true;
    SDL_Color c = {98, 3, 252, 0};
    while(running){
        time_update();
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }
        //Start render pass
        render_begin();
        input_update();
        input_handle();

        //Draw Elements
        for(int i = 0; i < global.render.height; i++){
            for(int j = 0; j < global.render.width; j++){
                draw_pixel(&c, j, i);
            }
        }

        //End frame
        render_end();
        time_update_late();

        static char buffer[12];
        snprintf(buffer, 12, "Engine - %u", global.time.frame_rate);
        SDL_SetWindowTitle(global.render.window, buffer);
    }

    SDL_DestroyRenderer(global.render.renderer);
    SDL_DestroyWindow(global.render.window);
    SDL_Quit();

    return 0;
}

