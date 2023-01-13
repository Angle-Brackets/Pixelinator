#define IO_READ_CHUNK_SIZE 2097152 //~20MiB, should be fine for most files
#define IO_READ_ERROR_GENERAL "Error reading file: %s. Errno: %d\n"
#define IO_READ_ERROR_MEMORY "Not enough free memory to read this file: %s\n"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <SDL_image.h>

#include "../../../include/types.h"
#include "../../../include/util.h"
#include "../../../include/io/io.h"

File io_file_read(const char* path){
    File file = {.is_valid = false};
    FILE *fp = fopen(path, "rb");

    if(fp == NULL || ferror(fp)){
        ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
    }

    char* data = NULL;
    char* temp;
    size_t used = 0;
    size_t size = 0;
    size_t n = 0;

    while(true){
        if(used + IO_READ_CHUNK_SIZE + 1 > size){
            size = used + IO_READ_CHUNK_SIZE + 1;

            if(size <= used) {
                free(data);
                ERROR_RETURN(file, "Input file too large: %s\n", path);
            }

            temp = (char*)realloc(data, size);
            if(temp == NULL){
                free(data);
                ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
            }
            data = temp;
        }

        n = fread(data + used, 1, IO_READ_CHUNK_SIZE, fp);
        if(n == 0){
            break;
        }

        used += n;
    }

    if(ferror(fp)){
        free(data);
        ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
    }

    temp = (char*)realloc(data, used + 1);

    if(temp == NULL){
        free(data);
        ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
    }

    data = temp;
    data[used] = '\0';
    file.data = data;
    file.len = used;
    file.is_valid = true;

    return file;
}


int io_file_write(void* buffer, size_t size, const char* path){
    FILE *fp = fopen(path, "wb");

    if(fp == NULL || ferror(fp)){
        ERROR_RETURN(1, "Cannot write file: %s\n", path);
    }

    size_t chunks_written = fwrite(buffer, size, 1, fp);
    fclose(fp);

    if(chunks_written != 1){
        ERROR_RETURN(1, "Write error. Expected 1 chunk got %zu.\n", chunks_written);
    }

    return 0;
}

SDL_Surface* read_png(const char* file) {
    static SDL_RWops *io = NULL;
    io = SDL_RWFromFile(file, "rb");
    SDL_Surface* frame = IMG_LoadPNG_RW(io);
    SDL_RWclose(io);

    return frame;
}

