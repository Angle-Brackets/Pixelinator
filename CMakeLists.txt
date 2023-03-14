cmake_minimum_required(VERSION 3.21)
project(Pixelinator VERSION 1.0 DESCRIPTION "A 2D Engine using SDL and C")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE EQUAL Release)
    message("Building Release...")
endif()

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(Pixelinator PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(Pixelinator "${CMAKE_THREAD_LIBS_INIT}")
endif()

add_subdirectory(glad/)
include_directories(include/)

add_executable(Pixelinator main.c include/types.h include/util.h src/engine/render/render.c include/render/render.h src/engine/render/render_init.c src/engine/render/render_internal.h src/engine/global.c include/global.h src/engine/io/io.c include/io/io.h src/engine/render/render_util.c include/input/input.h src/engine/input/input.c include/config/config.h src/engine/config/config.c src/engine/time.c include/time.h src/engine/graphics/bitmap/bitmap.c include/graphics/bitmap.h src/engine/graphics/bitmap/pixel_threading.c src/engine/graphics/bitmap/pixel_threading.h src/engine/audio/sound.c include/audio/sound.h src/engine/graphics/draw/shapes.c include/graphics/shapes.h src/engine/core/core.c include/core/core.h src/engine/font_cache/SDL_FontCache.c src/engine/font_cache/SDL_FontCache.h src/engine/text/text.c include/text/text.h src/engine/graphics/sprite/sprite.c include/graphics/sprite.h)
target_link_libraries(Pixelinator PRIVATE glad SDL2::SDL2 SDL2_mixer::SDL2_mixer SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)