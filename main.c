#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <math.h>
#include "engine/time.h"
#include "engine/global.h"
#include "engine/config/config.h"
#include "engine/input/input.h"
#include "engine/graphics/draw/shapes.h"
#include "engine/audio/sound.h"

#define SDL_MAIN_HANDLED
#define WIDTH 1440
#define HEIGHT 900

static bool running = false;

int main() {
    time_init(120);
    config_init();
    init_input();
    render_init(WIDTH, HEIGHT, BITMAP_ACTIVE | MULTITHREADING_ENABLED);
    init_mixer(MIX_INIT_MP3, 0);
    initialize_bitmap(WIDTH,HEIGHT);

    running = true;

    SDL_Color A = {0,0,0,255};
    SDL_Color B = {255,255,255,0};
    SDL_Color C = {255,0,0,0};

    struct Circle {
        u32 x;
        u32 y;
        u32 r;
        vec2 velocity;
        SDL_Color color;
    };

    struct Circle circles[100];

    for(i32 i = 0; i < 100; i++){
        circles[i].r = arc4random() % 100;
        circles[i].x = arc4random() % WIDTH;
        circles[i].y = arc4random() % HEIGHT;
        circles[i].velocity[0] = (arc4random() % 10) + 5;
        circles[i].velocity[1] = (arc4random() % 10) + 5;

        circles[i].color.r = arc4random() % 255;
        circles[i].color.g = arc4random() % 255;
        circles[i].color.b = arc4random() % 255;
    }

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

        if(get_key_state_str("Escape") & KS_PRESSED){
            running = false;
        }

        //Draw Elements
        fill_background(&B);

        for(i32 i = 0; i < 100; i++){
            set_shape_fill(&circles[i].color);
            set_stroke_fill(&circles[i].color);
            circles[i].x += circles[i].velocity[0];
            circles[i].y += circles[i].velocity[1];

            if(circles[i].x <= 0 || circles[i].x >= WIDTH)
                circles[i].velocity[0] *= -1;
            if(circles[i].y <= 0 || circles[i].y >= HEIGHT)
                circles[i].velocity[1] *= -1;
            draw_circle(circles[i].x, circles[i].y, circles[i].r);
            set_stroke_fill(&A);
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
    quit_mixer();
    SDL_Quit();

    return 0;
}

