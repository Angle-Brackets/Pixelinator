#include "global.h"
#include "controller/controller.h"

void init_controllers(u8 max_controllers){
    global.controller.connected_controllers = 0;
    global.controller.max_controllers = max_controllers;
    global.controller.controllers = (controller_t*)calloc(global.controller.max_controllers, sizeof(controller_t));

    //Only supports up to 256 controllers.
    for(u8 i = 0; i < (u8)SDL_NumJoysticks(); i++){
        if(SDL_IsGameController(i)){
            global.controller.controllers[global.controller.connected_controllers++].controller = SDL_GameControllerOpen(i);
        }
    }

    //Set the rest to null!
    for(u8 i = global.controller.connected_controllers; i < global.controller.max_controllers; i++){
        global.controller.controllers[i].controller = NULL;
    }
}

void update_controller_list(i32 joystick_id, u32 event_type){
    if(event_type == SDL_CONTROLLERDEVICEADDED){
        for(u8 i = 0; i < global.controller.max_controllers; i++){
            if(global.controller.controllers[i].controller == NULL){
                //Found the first open spot, add new controller.
                global.controller.controllers[i].controller = SDL_GameControllerOpen(joystick_id);
                global.controller.connected_controllers += global.controller.controllers[i].controller != NULL; //Did it actually add a new controller?
                break;
            }
        }
        if(global.controller.connected_controllers == MAX_SUPPORTED_CONTROLLERS) {
            WARN("Maximum number of controllers added, cannot add anymore!\n")
        }
    }
    else if(event_type == SDL_CONTROLLERDEVICEREMOVED) {
        for (u8 i = 0; i < global.controller.max_controllers; i++) {
            if (global.controller.controllers[i].controller != NULL && TEST_JOY_ID(global.controller.controllers[i].controller, joystick_id)) {
                SDL_GameControllerClose(global.controller.controllers[i].controller);
                global.controller.controllers[i].controller = NULL;
                global.controller.connected_controllers--;
                break;
            }
        }
    }
}

void controller_update(){
    for(u8 i = 0; i < global.controller.connected_controllers; i++) {
        controller_t* controller = &global.controller.controllers[i];
        if (!controller) {
            return;
        }

        //Loops over all buttons and updates the state for each of them accordingly. (Start at BUTTON A to skip INVALID)
        for (u32 button = SDL_CONTROLLER_BUTTON_A; button < SDL_CONTROLLER_BUTTON_MAX; button++) {
            //Prepare status flag (bit shift button status [0/1] by controller ID to turn on the correct bit in the union)
            u32 new_status = SDL_GameControllerGetButton(controller->controller, button);

            //Set the bit accordingly.
            //The button + 1 is because the invalid bit isn't directly set by this method (or at all).
            controller->state = (controller->state & ~(1UL << (button + 1))) | (new_status << (button + 1));
        }
    }
}

button_state get_button_state(controller_t* controller, SDL_GameControllerButton button){
    u32 current_status = (controller->state >> (button + 1)) & 0x1;
    return 0;
}

void close_controllers(){
    for(u8 i = 0; i < global.controller.max_controllers; i++){
        SDL_GameControllerClose(global.controller.controllers[i].controller);
        global.controller.controllers[i].controller = NULL;
    }

    free(global.controller.controllers);
    global.controller.controllers = NULL;
}

