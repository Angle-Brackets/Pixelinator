#ifndef SDLCENGINE_UTIL_H
#define SDLCENGINE_UTIL_H

#include <stdio.h>
#define ERROR_EXIT(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define ERROR_RETURN(R, ...) { fprintf(stderr, __VA_ARGS__); return R; }
#define WARN(...){ fprintf(stderr, __VA_ARGS__); }

#endif //SDLCENGINE_UTIL_H
