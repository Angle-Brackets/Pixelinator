#Compiles the library
cmake_minimum_required(VERSION 3.21)
project(main VERSION 1.0 DESCRIPTION "A 2D Engine using SDL and C")
set(CMAKE_C_STANDARD 11)

add_subdirectory(../external bin)
add_subdirectory(../../Pixelinator/glad ../../Pixelinator/src/engine/glad)
include_directories(../../Pixelinator/include)

add_library(main STATIC
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
)

set_target_properties(main PROPERTIES VERSION ${PROJECT_VERSION})
#set_target_properties(Pixelinator PROPERTIES SOVERSION 1)

#set_target_properties(Pixelinator PROPERTIES PUBLIC_HEADER pixelinator.h)
target_include_directories(main INTERFACE ../../Pixelinator)
target_link_libraries(main PRIVATE ../../Pixelinator/src/engine/glad SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static SDL2_ttf::SDL2_ttf-static SDL2_mixer::SDL2_mixer-static)
set("-OFast")

include(GNUInstallDirs)
install(TARGETS main
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})