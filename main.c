#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "global.h"
#include "graphics/bitmap.h"
#include "graphics/shapes.h"
#include "text/text.h"

#define WIDTH 750
#define HEIGHT 750

struct Circle {
    f32 x;
    f32 y;
    u32 r;
    f32 velocity[2];
    SDL_Color color;
};

struct Circle circle;

SDL_Color A = {0, 0, 0, 255};
SDL_Color WHITE = {255, 255, 255, 0};
SDL_Color C = {255, 0, 0, 0};

void draw() {
    static bool paused = false;

    if (get_key_state_str("Escape") & KS_PRESSED) {
        exit_program();
    }

    //Draw Elements
    fill_background(&WHITE);

    if(get_button_state(&global.controller.controllers[0], SDL_CONTROLLER_BUTTON_A) & CON_HELD){
        circle.color.r += 1;
    }
    if(get_button_state(&global.controller.controllers[0], SDL_CONTROLLER_BUTTON_B) & CON_HELD){
        circle.color.g += 1;
    }
    if(get_button_state(&global.controller.controllers[0], SDL_CONTROLLER_BUTTON_X) & CON_HELD){
        circle.color.b += 1;
    }
    if(get_button_state(&global.controller.controllers[0], SDL_CONTROLLER_BUTTON_Y) & CON_HELD){
        circle.color = (SDL_Color){0};
    }

    f32 xMag = get_joystick_state(&global.controller.controllers[0], 0, 3200);
    f32 yMag = get_joystick_state(&global.controller.controllers[0], 1, 3200);
    circle.x += (xMag / 32767.0F) * 5;
    circle.y += (yMag / 32767.0F) * 5;

    set_stroke_fill(&circle.color);
    set_shape_fill(&circle.color);
    draw_circle(circle.x, circle.y, circle.r);

    draw_bitmap();

    render_text(NULL, 0, 0, LEFT, "X: %f\nY: %f", circle.x, circle.y)
    render_text(NULL, 0, 30, LEFT, "RGB: (%u, %u, %u)", circle.color.r, circle.color.g, circle.color.b)
    static char buffer[20];
    snprintf(buffer, 20, "Engine - %u", global.time.frame_rate);
    SDL_SetWindowTitle(global.render.window, buffer);
}

i32 main(){
    initialize(WIDTH, HEIGHT, WIDTH, HEIGHT, 120, 15, 4, MULTITHREADING_ENABLED | BITMAP_ACTIVE | IGNORE_FOCUS, 0, draw);
    set_default_font(load_pix_font("../assets/pixel-emulator-font/PixelEmulator-xq08.ttf", 12, (SDL_Color){255,0,0,255}));
    circle.color = (SDL_Color){0,0,0,255};
    circle.r = 15;
    circle.x = global.render.width / 2;
    circle.y = global.render.height / 2;

    start();
}