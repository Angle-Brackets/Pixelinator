#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "glad.h"
#include "engine/global.h"

#define SDL_MAIN_HANDLED

int main() {
    static bool running = false;
    render_init();
    running = true;

    while(running){
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
                (vec2){global.render.width * 0.5, global.render.height * 0.5},
                (vec2){50, 50},
                (vec4){0.5,1,0.2,1}
        );

        //End frame
        render_end();
    }

    return 0;
}
