#Compiles the library
cmake_minimum_required(VERSION 3.21)
project(Pixelinator VERSION 1.0 DESCRIPTION "A 2D Engine using SDL and C")
set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
add_subdirectory(../../Pixelinator/glad ../../Pixelinator/src/engine/glad)
include_directories(../../Pixelinator/include)

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
)

set_target_properties(Pixelinator PROPERTIES VERSION ${PROJECT_VERSION})
#set_target_properties(Pixelinator PROPERTIES SOVERSION 1)

#set_target_properties(Pixelinator PROPERTIES PUBLIC_HEADER pixelinator.h)
target_include_directories(Pixelinator INTERFACE ../../Pixelinator)
target_link_libraries(Pixelinator PRIVATE ../../Pixelinator/src/engine/glad SDL2::SDL2 SDL2_mixer::SDL2_mixer SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
set("-OFast")

include(GNUInstallDirs)
install(TARGETS Pixelinator
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})