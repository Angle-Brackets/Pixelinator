#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "glad.h"
#include "engine/time.h"
#include "engine/global.h"
#include "engine/config/config.h"
#include "engine/input/input.h"
#define SDL_MAIN_HANDLED


static bool running = false;
static vec2 pos;

//Temporary
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

    pos[0] = global.render.width * 0.5;
    pos[1] = global.render.height * 0.5;

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

        //Objects to render
        render_quad(
                pos,
                (vec2){50, 50},
                (vec4){0.5,1,0.2,1}
        );
        input_update();
        input_handle();

        //End frame
        render_end();
        time_update_late();
    }

    return 0;
}
