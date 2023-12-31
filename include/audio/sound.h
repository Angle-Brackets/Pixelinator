#ifndef SDLCENGINE_SOUND_H
#define SDLCENGINE_SOUND_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include "types.h"

#define MAX_STORED_SOUNDS 256

typedef struct sound_state {
    bool music_active; //If music is toggled on
    bool loop_music; //Whether the last piece of music played should be looped

    bool sfx_active; //If sfx are active
    bool loop_sfx; //Whether the last sfx played should be looped

    u8 volume; //Volume of audio
} Sound_State;

/**
 * Initializes music/mixer code
 * @param flags Flags to set when initializing sounds (default has MP3 enabled)
 * @param volume 0 - 100, defaults to 100.
 * @return 0 for success, 1 for failure.
 */
u8 init_mixer(MIX_InitFlags flags, u8 volume);

/**
 * Frees up all memory associated with mixer.
 * @return 0 for success, 1 for failure.
 */
u8 quit_mixer();

/**
 * Loads music from a file into the music buffer, make sure to delete it when unneeded!
 * @param file file path to music, must be an mp3 right now (probably will change later)
 * @return The index to the location of the music file in the buffer, used in deleting it later.
 */
u32 load_music(const char* file);

/**
 * Loads sfx from a file into the sfx buffer, make sure to delete it when unneeded!
 * @param file file path to sfx, must be an wav right now (probably will change later)
 * @return The index to the location of the sfx file in the buffer, used in deleting it later.
 */
u32 load_sfx(const char* file);

/**
 * Sets the new volume with an absolute number
 * @param percentage A value between 0 - 100.
 */
void set_volume(u8 percentage);

/**
 * Play music stored at the specified index
 * @param index index where the music is stored
 * @return 0 for success, 1 for failure
 */
u8 play_music(u32 index);

/**
 * Play an sfx stored at the specified index
 * @param index index where the sfx is stored
 * @return 0 for success, 1 for failure
 */
u8 play_sfx(u32 index);

/**
 * Pauses all audio playing.
 */
void pause_audio();

/**
 * Resumes all audio playing.
 */
void resume_audio();

/**
 * Frees up the memory for this particular index's music.
 * @param index index of where the music is stored
 */
void free_music(u32 index);

/**
 * Frees up the memory for this particular index's sfx.
 * @param index index of where the sfx is stored
 */
void free_sfx(u32 index);

#endif //SDLCENGINE_SOUND_H
