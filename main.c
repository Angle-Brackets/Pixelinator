#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "global.h"
#include "graphics/bitmap.h"
#include "graphics/shapes.h"
#include "text/text.h"

#define WIDTH 750
#define HEIGHT 750

static i32 circle_num = 1;
static i32 circle_capacity = 2;

struct Circle {
    u32 x;
    u32 y;
    u32 r;
    f32 velocity[2];
    SDL_Color color;
};

struct Circle* circles;

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

    if(get_key_state_str("A") & KS_HELD){
        if(circle_capacity == circle_num){
            circle_capacity *= 2;
            circles = (struct Circle*)realloc(circles, sizeof(struct Circle) * circle_capacity);
        }

        struct Circle c = {
                .r = arc4random() % 100,
                .x = arc4random() % WIDTH,
                .y = arc4random() % HEIGHT,
                .velocity = {(arc4random() % 10) + 5, (arc4random() % 10) + 5},
                .color = {arc4random() % 255, arc4random() % 255, arc4random() % 255}
        };

        circles[circle_num] = c;
        circle_num++;

        printf("%i circles drawn\n", circle_num);
    }

    if(get_key_state_str("R") & KS_HELD){
        if(circle_num > 0) {
            circles[circle_num--] = (struct Circle) {0};
            printf("%i circles drawn\n", circle_num);
        }
    }

    //Draw Elements
    fill_background(&B);

    for (i32 i = 0; i < circle_num; i++) {
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

    //printf("%i\n", SDL_CONTROLLER_BUTTON_MAX - SDL_CONTROLLER_BUTTON_INVALID + 1);
    u32 z = get_button_state(&global.controller.controllers[0], SDL_CONTROLLER_BUTTON_A);
    if(z & CON_PRESSED) {
        printf("Pressed A\n");
    }
    else if(z & CON_HELD){
        printf("Held A\n");
    }
    else if(z & CON_RELEASED){
        printf("Released A\n");
    }

    bitmap_scale(s, s);
    bitmap_shift(x, 0);
    draw_bitmap();

    render_text(NULL, 0, 0, LEFT, "%i", get_joystick_state(&global.controller.controllers[0]));
    static char buffer[20];
    snprintf(buffer, 20, "Engine - %u", global.time.frame_rate);
    SDL_SetWindowTitle(global.render.window, buffer);
}

i32 main(){
    initialize(WIDTH, HEIGHT, WIDTH, HEIGHT, 120, 15, 1, MULTITHREADING_ENABLED | BITMAP_ACTIVE | IGNORE_FOCUS, 0, draw);
    circles = (struct Circle*)malloc(sizeof(struct Circle) * circle_capacity);
    set_default_font(load_pix_font("../assets/pixel-emulator-font/PixelEmulator-xq08.ttf", 12, (SDL_Color){255,0,0,255}));

    for (i32 i = 0; i < circle_num; i++) {
        circles[i].r = arc4random() % 100;
        circles[i].x = arc4random() % WIDTH;
        circles[i].y = arc4random() % HEIGHT;
        circles[i].velocity[0] = (arc4random() % 10) + 5;
        circles[i].velocity[1] = (arc4random() % 10) + 5;

        circles[i].color.r = arc4random() % 255;
        circles[i].color.g = arc4random() % 255;
        circles[i].color.b = arc4random() % 255;
    }

    start();
}