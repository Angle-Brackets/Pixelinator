cmake_minimum_required(VERSION 3.21)
project(SDLCEngine C)

set(CMAKE_C_STANDARD 99)
find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)

add_subdirectory(glad/)

add_executable(SDLCEngine main.c engine/types.h engine/util.h engine/render/render.c engine/render/render.h engine/render/render_init.c engine/render/render_internal.h engine/global.c engine/global.h engine/io/io.c engine/io/io.h engine/render/render_util.c engine/input/input.h engine/input/input.c engine/config/config.h engine/config/config.c engine/time.c engine/time.h engine/draw/bitmap.c engine/draw/bitmap.h engine/draw/pixel_threading.c engine/draw/pixel_threading.h engine/audio/sound.c engine/audio/sound.h)
target_link_libraries(SDLCEngine PRIVATE glad SDL2::SDL2 SDL2_mixer::SDL2_mixer SDL2_image::SDL2_image)