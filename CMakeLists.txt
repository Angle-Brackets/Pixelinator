cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0075 NEW)
cmake_policy(SET CMP0091 NEW)
project(Pixelinator VERSION 1.0 DESCRIPTION "A 2D Engine using SDL and C")

set( CMAKE_CXX_STANDARD 11 CACHE STRING "" FORCE )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE )
set(CMAKE_OSX_ARCHITECTURES "x86_64") #Build for x86 Darwin

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE EQUAL Release)
    message(WARNING "Building Release...")
    set(CMAKE_CXX_FLAGS_RELEASE "-OFast")
endif()

set(CMAKE_C_STANDARD 11)

if(CMAKE_BUILD_TYPE EQUAL DEBUG)
    message(WARNING "Building Debug...")
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

add_library(Pixelinator STATIC
        ../../Pixelinator/src/engine/audio/sound.c
        ../../Pixelinator/src/engine/config/config.c
        ../../Pixelinator/src/engine/core/core.c
        ../../Pixelinator/src/engine/graphics/bitmap/bitmap.c
        ../../Pixelinator/src/engine/graphics/bitmap/pixel_threading.c
        ../../Pixelinator/src/engine/graphics/sprite/sprite.c
        ../../Pixelinator/src/engine/graphics/draw/shapes.c
        ../../Pixelinator/src/engine/input/input.c
        ../../Pixelinator/src/engine/io/io.c
        ../../Pixelinator/src/engine/render/render.c
        ../../Pixelinator/src/engine/render/render_init.c
        ../../Pixelinator/src/engine/render/render_util.c
        ../../Pixelinator/src/engine/font_cache/SDL_FontCache.c
        ../../Pixelinator/src/engine/text/text.c
        ../../Pixelinator/src/engine/global.c
        ../../Pixelinator/src/engine/time.c
        ../../Pixelinator/src/engine/controller/controller.c

        # SDL (Not sure if needed)
        ../external/SDL
        ../external/sdl-image
        ../external/sdl-mixer
        ../external/sdl-ttf)

set(APP_EXE PixelinatorExe)


if( ${CMAKE_SYSTEM_NAME} MATCHES "Android" )
    add_library( ${APP_EXE} SHARED )
else()
    add_executable(${APP_EXE} main.c)
    set_target_properties( ${APP_EXE} PROPERTIES OUTPUT_NAME ${CMAKE_PROJECT_NAME} )
endif()

find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(${APP_EXE} PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(${APP_EXE} "${CMAKE_THREAD_LIBS_INIT}")
endif()

add_subdirectory("external")
add_subdirectory(glad/)
include_directories("include")


# Library is generated inside of the cmake-build-debug or release folder!
target_link_libraries(${APP_EXE} glad Pixelinator)

