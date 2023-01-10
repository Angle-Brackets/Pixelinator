cmake_minimum_required(VERSION 3.21)
project(SDLCEngine C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE EQUAL Release)
    message("Building Release...")
endif()

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-OFast")

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)

add_subdirectory(glad/)

add_executable(SDLCEngine main.c engine/types.h engine/util.h engine/render/render.c engine/render/render.h engine/render/render_init.c engine/render/render_internal.h engine/global.c engine/global.h engine/io/io.c engine/io/io.h engine/render/render_util.c engine/input/input.h engine/input/input.c engine/config/config.h engine/config/config.c engine/time.c engine/time.h engine/graphics/bitmap/bitmap.c engine/graphics/bitmap/bitmap.h engine/graphics/bitmap/pixel_threading.c engine/graphics/bitmap/pixel_threading.h engine/audio/sound.c engine/audio/sound.h engine/graphics/draw/shapes.c engine/graphics/draw/shapes.h)
target_link_libraries(SDLCEngine PRIVATE glad SDL2::SDL2 SDL2_mixer::SDL2_mixer SDL2_image::SDL2_image)