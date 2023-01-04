#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "engine/time.h"
#include "engine/global.h"
#include "engine/config/config.h"
#include "engine/input/input.h"
#include "engine/draw/bitmap.h"

#define SDL_MAIN_HANDLED
#define WIDTH 800
#define HEIGHT 256

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
    time_init(120);
    config_init();
    render_init(WIDTH, HEIGHT, BITMAP_ACTIVE | MULTITHREADING_ENABLED);
    initialize_bitmap(800, 256);

    running = true;
    SDL_Color A = {0, 0, 0, 0};
    SDL_Color B = {255, 255, 255, 0};

    while(running){
        time_update();
        SDL_Event event;

        //This might be moved to be an event.h/event.c file FOR EVERY event to be polled.
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_WINDOWEVENT:
                    switch(event.window.event){
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            global.render.width = event.window.data1;
                            global.render.height = event.window.data2;
                            break;
                    }
                default:
                    break;
            }
        }

        //Start render pass
        render_begin();
        input_update();
        input_handle();

        //Draw Elements
        for(int i = 0; i < global.bitmap.height; i++){
            for(int j = 0; j < global.bitmap.width; j++){
                //draw_pixel(arc4random() % 2 ? &A : &B, j, i);
                draw_pixel(&B, j, i);
                //draw_pixel(i % 2 ? &A : &B, j, i);
            }
            B.r--;
        }
        //End frame
        render_end();
        time_update_late();

        static char buffer[20];
        snprintf(buffer, 20, "Engine - %u", global.time.frame_rate);
        SDL_SetWindowTitle(global.render.window, buffer);
    }

    SDL_DestroyRenderer(global.render.renderer);
    SDL_DestroyWindow(global.render.window);
    SDL_Quit();

    return 0;
}

