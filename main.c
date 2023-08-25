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
static sprite_t* button;

SDL_Color A = {0, 0, 0, 255};
SDL_Color WHITE = {255, 255, 255, 255};
SDL_Color BROWN = {168, 130, 96, 255};
static u32 speed = 350;

void draw() {
    static bool paused = false;

    if (get_key_state_str("Escape") & KS_PRESSED) {
        exit_program();
    }

    if(get_key_state_str("R") & KS_PRESSED){
        set_window_size(WIDTH, HEIGHT);
        resize_bitmap(WIDTH, HEIGHT);
    }

    if(get_key_state_str("I") & KS_HELD){
        resize_bitmap(global.render.width + 10, global.render.height + 10);
        set_window_size(global.render.width + 10, global.render.height + 10);
    }

    if(get_key_state_str("D") & KS_HELD){
        resize_bitmap(global.render.width - 10, global.render.height - 10);
        set_window_size(global.render.width - 10, global.render.height - 10);

    }

    //Draw Elements
    fill_background(&BROWN);

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
        circle.color.a -= 1;
    }
    if(get_button_state(&global.controller.controllers[0], SDL_CONTROLLER_BUTTON_START) & CON_HELD){
        circle.color = (SDL_Color){0,0,0,255};
    }
    if(get_button_state(&global.controller.controllers[0], SDL_CONTROLLER_BUTTON_DPAD_UP) & CON_HELD){
        speed += 1;
    }
    if(get_button_state(&global.controller.controllers[0], SDL_CONTROLLER_BUTTON_DPAD_DOWN) & CON_HELD){
        speed -= 1;
    }

    f32 xMag = get_joystick_state(&global.controller.controllers[0], 0, 3200);
    f32 yMag = get_joystick_state(&global.controller.controllers[0], 1, 3200);
    circle.x += (xMag / 32767.0F) * global.time.delta * speed;
    circle.y += (yMag / 32767.0F) * global.time.delta * speed;

    set_stroke_fill(&circle.color);
    set_shape_fill(&circle.color);
    draw_circle(circle.x, circle.y, circle.r);

    draw_bitmap();

    render_text(NULL, 0, 0, LEFT, "X: %f\nY: %f\nSpeed: %u", circle.x, circle.y, speed)
    render_text(NULL, 0, 45, LEFT, "RGBA: (%u, %u, %u, %u)", circle.color.r, circle.color.g, circle.color.b, circle.color.a)
    render_text(NULL, 0, 60, LEFT, "Updates: %u\nCalls: %u", global.bitmap.bitmap_updates, global.bitmap.bitmap_calls)
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