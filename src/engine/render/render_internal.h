#ifndef SDLCENGINE_RENDER_INTERNAL_H
#define SDLCENGINE_RENDER_INTERNAL_H

typedef struct render_state_internal {
    u32 shader_default;
    u32 texture_color;
} Render_State_Internal;

void initialize_SDL(const char* name, u32 width, u32 height, Render_Flags flags);


#endif //SDLCENGINE_RENDER_INTERNAL_H
