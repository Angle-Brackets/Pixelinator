#include "../../../include/types.h"
#include "../../../global.h"
#include "../../../include/util.h"
#include "../../../include/input/input.h"

static const u8* current_state;
static Key_State* key_states;
static i32 num_keys = 0;

static void update_key_state(u8 state, Key_State* key_state){
    if(state != 0){
        if(*key_state > 0){
            *key_state = KS_HELD;
        }
        else{
            *key_state = KS_PRESSED;
        }
    }
    else {
        *key_state = KS_UNPRESSED;
    }
}

void init_input(){
    //Side note: I am unsure why it defaults to 512 when we can only represent 256 unique keys with a u8...
    current_state = SDL_GetKeyboardState(&num_keys);
    if((key_states = (Key_State*)calloc(num_keys, sizeof(Key_State))) == NULL){
        ERROR_EXIT("Failed to allocate memory for keyboard data.\n")
    }
}

void input_update(void){
    i32 previous = num_keys;
    current_state = SDL_GetKeyboardState(&num_keys);

    if(previous != num_keys){
        WARN("Number of keys changed suddenly, undefined behavior may occur. Check your code for potential bugs.\n")
        if((key_states = (Key_State*)realloc(key_states, sizeof(Key_State) * num_keys)) == NULL){
            ERROR_EXIT("Failed to reallocate memory for keyboard data.\n")
        }
    }

    for(i32 i = 0; i < num_keys; i++){
        update_key_state(current_state[i], &key_states[i]);
    }
}

Key_State get_key_state_scancode(SDL_Scancode scancode) {
    if(scancode == SDL_SCANCODE_UNKNOWN){
        ERROR_RETURN(INVALID_KEY, "Invalid scancode specified: %i.\n", scancode)
    }

    return key_states[scancode];
}

Key_State get_key_state_str(const char* key) {
    SDL_Scancode scancode = SDL_GetScancodeFromName(key);
    if(scancode == SDL_SCANCODE_UNKNOWN){
        ERROR_RETURN(INVALID_KEY, "Invalid key name specified: %s. Check your spelling and capitalization!\n", key)
    }

    return key_states[scancode];
}

Key_State get_key_state_id(SDL_KeyCode key) {
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key);

    if(scancode == SDL_SCANCODE_UNKNOWN){
        ERROR_RETURN(INVALID_KEY, "Invalid key specified: %i.\n", key)
    }

    return key_states[scancode];
}
