#include <string.h>

#include "sound.h"
#include "../util.h"
#include "../global.h"

static Mix_Music* music[MAX_STORED_SOUNDS]; //Location of all stored music samples
static Mix_Chunk* sfx[MAX_STORED_SOUNDS]; //Location of all stored sfx samples
static u32 music_size = 0; //Number of music pieces stored in file
static u32 sfx_size = 0;  //Number of sfx stored in file

u8 init_mixer(MIX_InitFlags flags, u8 volume){
    Mix_Init(flags | MIX_INIT_MP3); //Default will have MP3 enabled.

    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        WARN("Could not initialize SDL_Mixer: %s\n", SDL_GetError())
        return 1;
    }

    //Clear up memory
    memset(music, 0, sizeof(Mix_Music*) * MAX_STORED_SOUNDS);
    memset(sfx, 0, sizeof(Mix_Chunk*) * MAX_STORED_SOUNDS);

    //Initialize global variable for sound information
    global.sound.loop_music = false;
    global.sound.loop_sfx = false;
    global.sound.music_active = false;
    global.sound.sfx_active = false;
    global.sound.volume = 100;

    set_volume(volume);

    return 0;
}

u8 quit_mixer(){
    //Free up memory!
    for(int i = 0; i < MAX_STORED_SOUNDS; i++){
        Mix_FreeMusic(music[i]);
        Mix_FreeChunk(sfx[i]);

        music[i] = NULL;
        sfx[i] = NULL;
    }
    Mix_Quit();

    return 0;
}

u32 load_music(const char* file){
    Mix_Music* m = Mix_LoadMUS(file);

    if(music_size == MAX_STORED_SOUNDS){
        WARN("Cannot add more music to buffer, try freeing some unused music pieces before allocating more music data!\n")
        return -1;
    }

    if(m == NULL){
        WARN("Failed to load music with SDL_Mixer: %s\n", Mix_GetError())
        return -1;
    }

    //Search for an empty spot.
    for(int i = 0; i < MAX_STORED_SOUNDS; i++){
        if(music[i] == NULL){
            music[i] = m;
            music_size++;
            return i;
        }
    }

    return -1; //Should NEVER reach here.
}

u32 load_sfx(const char* file){
    Mix_Chunk* m = Mix_LoadWAV(file);

    if(sfx_size == MAX_STORED_SOUNDS){
        WARN("Cannot add more sfx to buffer, try freeing some unused sfx pieces before allocating more sfx data!\n")
        return 1;
    }

    if(m == NULL){
        WARN("Failed to load music with SDL_Mixer: %s\n", Mix_GetError())
        return 1;
    }

    //Search for an empty spot.
    for(int i = 0; i < MAX_STORED_SOUNDS; i++){
        if(sfx[i] == NULL){
            sfx[i] = m;
            sfx_size++;
            return i;
        }
    }

    return 1; //Should never reach here.
}

void set_volume(u8 percentage){
    if(percentage > 100)
        percentage = 100;

    global.sound.volume = (MIX_MAX_VOLUME * percentage) / 100;
}

u8 play_music(u32 index){
    if(index >= 0 && index < music_size && Mix_PlayingMusic() == 0){
        Mix_VolumeMusic(global.sound.volume);
        Mix_Volume(1, global.sound.volume);
        Mix_PlayMusic(music[index], 0); //TODO: Implement looping here?
        return 0;
    }
    return 1;
}

u8 play_sfx(u32 index){
    if(index >= 0 && index < music_size) {
        Mix_Volume(-1, global.sound.volume);
        Mix_PlayChannel(-1, sfx[index], 0);
        return 0;
    }
    return 1;
}

void pause_audio() {
    Mix_Pause(-1); //Sfx
    Mix_PauseMusic(); //Music
}

void resume_audio() {
    Mix_Resume(-1); //Sfx
    Mix_ResumeMusic(); //Music
}

void free_music(u32 index){
    Mix_FreeMusic(music[index]);
    music[index] = NULL;
    music_size--;
}

void free_sfx(u32 index){
    Mix_FreeChunk(sfx[index]);
    sfx[index] = NULL;
    sfx_size--;
}