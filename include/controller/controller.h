#ifndef PIXELINATOR_CONTROLLER_H
#define PIXELINATOR_CONTROLLER_H

#define MAX_SUPPORTED_CONTROLLERS 255
#define TEST_JOY_ID(CONTROLLER, ID) SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(CONTROLLER)) == ID

#include <SDL.h>
#include "types.h"
#include "util.h"

typedef enum Button_State {
    INVALID = 0x1 << 0, //Invalid Controller / Button State
    CON_UNPRESSED = 0x1 << 1, //Button was never pressed
    CON_RELEASED = 0x1 << 2, //Button was just unpressed
    CON_PRESSED = 0x1 << 3, //Button was just pressed
    CON_HELD = 0x1 << 4 //Button was previously pressed
} button_state;

typedef struct Controller {
    SDL_GameController* controller;

    //Button press state (used for debounce)
    union {
        //23 different flags possible
        u32 state;
        struct {
            u32 invalid : 1;
            u32 a : 1;
            u32 b : 1;
            u32 x : 1;
            u32 y : 1;
            u32 back : 1;
            u32 guide : 1;
            u32 start : 1;
            u32 left_stick : 1;
            u32 right_stick : 1;
            u32 left_shoulder : 1;
            u32 right_shoulder : 1;
            u32 dpad_up : 1;
            u32 dpad_down : 1;
            u32 dpad_left : 1;
            u32 dpad_right : 1;
            u32 misc1 : 1; /* Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button */
            u32 paddle1 : 1; /* Xbox Elite paddle P1 (upper left, facing the back) */
            u32 paddle2 : 1; /* Xbox Elite paddle P3 (upper right, facing the back) SDL LABELED THIS */
            u32 paddle3 : 1; /* Xbox Elite paddle P2 (lower left, facing the back) SDL LABELED THIS */
            u32 paddle4 : 1; /* Xbox Elite paddle P4 (lower right, facing the back) */
            u32 touchpad : 1; /* PS4/PS5 touchpad button */
            u32 max : 1;
            u32 unused : 9;
        };
    };

} controller_t;

typedef struct controller_state {
    controller_t* controllers; //Controllers connected (NULL means not connected)
    u8 connected_controllers; //Number of controllers connected.
    u8 max_controllers;
} Controller_State;

/**
 * Initializes controllers (internal use), finds any that are connected on startup and sets up the initial array of controllers.
 */
void init_controllers(u8 max_controllers);

/**
 * Updates the list of controllers
 */
void update_controller_list(i32 joystick_id, u32 event_type);

/**
 * Detect the action of a button on a particular controller. \n
 * This does not differentiate between a button being PRESSED VS HELD, you must implement your own debounce.
 * @param controller controller to check button action on (NULLs are ignored safely)
 * @param event Button event to listen for
 * @param button Button to listen for
 * @return a boolean indicating whether the button followed the desired event.
 */
button_state get_button_state(controller_t* controller, SDL_GameControllerButton button);

/**
 * Detect the action of a joystick on a particular controller
 * @param controller controller to check button action on (NULLs are ignored safely)
 * @param event Joystick event to listen for
 * @param joystick Joystick to listen for
 * @return a boolean indicating whether the joystick followed the desired event.
 */
int get_joystick_state(controller_t* controller);

/**
 * Frees up memory associated with controllers
 */
void close_controllers();



#endif //PIXELINATOR_CONTROLLER_H
