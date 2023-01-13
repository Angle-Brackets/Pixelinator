#ifndef SDLCENGINE_IO_H
#define SDLCENGINE_IO_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct file {
    char* data;
    size_t len;
    bool is_valid;
} File;

File io_file_read(const char* path);
int io_file_write(void* buffer, size_t size, const char* path);

/**
 * Read in a png and convert it into a bitmap surface that can be read or passed to other functions
 * @param file path to the png
 * @return A bitmap surface of pixels - Remember to free the surface when done with SDL_FreeSurface! NULL on failure.
 */
SDL_Surface* read_png(const char* file);

#endif //SDLCENGINE_IO_H
