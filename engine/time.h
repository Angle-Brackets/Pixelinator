#ifndef SDLCENGINE_TIME_H
#define SDLCENGINE_TIME_H

#include "types.h"

typedef struct time_state {
    f32 delta; //Time between frames
    f32 now; //Time of the current frame
    f32 last; //Time of the last frame

    f32 frame_last; //Last time the FPS was calculated
    f32 frame_delay; //Maximum amount of time a frame should take
    f32 frame_time; //Amount of time the current frame took

    u32 frame_rate; //Obvious
    u32 frame_count; //Number of frames rendered
} Time_State;

void time_init(u32 frame_rate);
void time_update(void);
void time_update_late(void);

#endif //SDLCENGINE_TIME_H
