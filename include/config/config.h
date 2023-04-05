#ifndef SDLCENGINE_CONFIG_H
#define SDLCENGINE_CONFIG_H

#include "input/input.h"
#include "types.h"

typedef struct config {
    u8 keybinds[5];
} Config_State;

void config_init(void);
int config_key_bind(Input_Key key, const char* key_name);

#endif //SDLCENGINE_CONFIG_H
