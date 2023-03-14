#ifndef SDLCENGINE_UTIL_H
#define SDLCENGINE_UTIL_H

#include <stdio.h>
#define ERROR_EXIT(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define ERROR_RETURN(R, ...) { fprintf(stderr, __VA_ARGS__); return R; }
#define WARN(...){ fprintf(stderr, __VA_ARGS__); }
#define VERIFY_HEAP_DATA(pointer) { if(pointer == NULL){fprintf(stderr, "Ran out of memory.\n"); exit(1);} } //Checks if heap memory is not NULL

#endif //SDLCENGINE_UTIL_H
