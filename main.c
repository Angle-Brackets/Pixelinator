#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "include/graphics/shapes.h"
#include "include/global.h"
#include "core/core.h"
#include "text/text.h"

#define BMPW 256
#define BMPH 384
#define WIDTH 1920
#define HEIGHT 1080

SDL_Color A = {0, 0, 0, 255};
SDL_Color B = {255, 255, 255, 0};
SDL_Color C = {255, 0, 0, 0};
static sprite_t* spriteA;
static sprite_sheet* sheetA;

void draw() {
    static u32 sx = 0, sy = 0;
    static u32 frame = 0;
    static bool paused = false;
    static SDL_RWops *io = NULL;
    static SDL_Surface* bg = NULL;

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
        sy += 1;
    }

    //Draw Elements
    io = SDL_RWFromFile("../assets/MLTopFloor.png", "rb");
    bg = IMG_LoadPNG_RW(io);
    draw_pixels_from_surface(bg);
    update_sprite_from_spritesheet(spriteA, 2 + frame * 50, 2 + sy, 0, 0, 50, 50);
    draw_sprite_to_bitmap(spriteA);

    static bool inc = false;
    if(inc)
        frame = (frame + 1) % 38;
    inc = !inc;

    draw_bitmap();
    render_text(NULL, global.render.width, 0, RIGHT, "FPS: %u\nUpdates: %u", global.time.frame_rate, global.bitmap.bitmap_updates);

    static char buffer[20];
    snprintf(buffer, 20, "Engine - %u", global.time.frame_rate);
    SDL_SetWindowTitle(global.render.window, buffer);
    SDL_FreeSurface(bg);
    SDL_RWclose(io);
}

i32 main(){
    initialize(WIDTH, HEIGHT, BMPW, BMPH, 120, 15, MULTITHREADING_ENABLED | BITMAP_ACTIVE | IGNORE_FOCUS, 0, draw);

    PIX_Font* font;
    font = load_pix_font("../assets/pixel-emulator-font/PixelEmulator-xq08.ttf", 25, (SDL_Color){255,0,0,255});
    set_default_font(font);

    SDL_Color bad_colors[2] = {{0,174,174}, {0,174,0}};
    sheetA = create_sprite_sheet("../assets/MarioSpriteSheet.png", bad_colors, 2);
    spriteA = create_sprite(52, BMPH/2, 50, 50, sheetA);


    start();
}



