#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "engine/graphics/draw/shapes.h"
#include "engine/global.h"
#include "engine/core/core.h"

#define WIDTH 1440
#define HEIGHT 900

struct Circle {
    u32 x;
    u32 y;
    u32 r;
    vec2 velocity;
    SDL_Color color;
};

struct Circle circles[100];

SDL_Color A = {0, 0, 0, 255};
SDL_Color B = {255, 255, 255, 0};
SDL_Color C = {255, 0, 0, 0};

void draw() {
    static bool paused = false;

    if (get_key_state_str("Escape") & KS_PRESSED) {
        exit_program();
    }

    if (get_key_state_str("P") & KS_PRESSED) {
        paused = !paused;

        if(paused)
            pause_audio();
        else
            resume_audio();
    }
    static u32 s = 100;
    static i32 x = 0;

    if(get_key_state_str("Up") & KS_HELD){
        s += 1;
    }

    if(get_key_state_str("Down") & KS_HELD){
        s -= 1;
    }

    if(get_key_state_str("Left") & KS_HELD){
        x -=  10;
    }

    if(get_key_state_str("Right") & KS_HELD){
        x += 10;
    }

    //Draw Elements
    fill_background(&B);

    for (i32 i = 0; i < 100; i++) {
        set_shape_fill(&circles[i].color);
        set_stroke_fill(&circles[i].color);
        if (!paused) {
            circles[i].x += circles[i].velocity[0];
            circles[i].y += circles[i].velocity[1];

            if (circles[i].x <= 0 || circles[i].x >= WIDTH) {
                circles[i].velocity[0] *= -1;
            }
            if (circles[i].y <= 0 || circles[i].y >= HEIGHT) {
                circles[i].velocity[1] *= -1;
            }
        }
        draw_circle(circles[i].x, circles[i].y, circles[i].r);
        set_stroke_fill(&A);
    }

    bitmap_scale(s, s);
    bitmap_shift(x, 0);

    static char buffer[20];
    snprintf(buffer, 20, "Engine - %u", global.time.frame_rate);
    SDL_SetWindowTitle(global.render.window, buffer);
}

i32 main(){
    initialize(WIDTH, HEIGHT, WIDTH, HEIGHT, 120, 15, MULTITHREADING_ENABLED | BITMAP_ACTIVE | IGNORE_FOCUS, 0, draw);
    u32 music_index = load_music("../demo_imgs_rgba/bad_apple.mp3");

    play_music(music_index);

    for (i32 i = 0; i < 100; i++) {
        circles[i].r = arc4random() % 100;
        circles[i].x = arc4random() % WIDTH;
        circles[i].y = arc4random() % HEIGHT;
        circles[i].velocity[0] = (arc4random() % 10) + 5;
        circles[i].velocity[1] = (arc4random() % 10) + 5;

        circles[i].color.r = arc4random() % 255;
        circles[i].color.g = arc4random() % 255;
        circles[i].color.b = arc4random() % 255;
    }
    SDL_RWops io;

    start();
}



