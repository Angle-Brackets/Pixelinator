#Compiles the library
cmake_minimum_required(VERSION 3.21)
project(Pixelinator VERSION 1.0 DESCRIPTION "A 2D Engine using SDL and C")
set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
add_subdirectory(../../SDLCEngine/glad ../../SDLCEngine/src/engine/glad)
include_directories(../../SDLCEngine/include)

add_library(Pixelinator STATIC
        ../../SDLCEngine/src/engine/audio/sound.c
        ../../SDLCEngine/src/engine/config/config.c
        ../../SDLCEngine/src/engine/core/core.c
        ../../SDLCEngine/src/engine/graphics/bitmap/bitmap.c
        ../../SDLCEngine/src/engine/graphics/bitmap/pixel_threading.c
        ../../SDLCEngine/src/engine/graphics/sprite/sprite.c
        ../../SDLCEngine/src/engine/graphics/draw/shapes.c
        ../../SDLCEngine/src/engine/input/input.c
        ../../SDLCEngine/src/engine/io/io.c
        ../../SDLCEngine/src/engine/render/render.c
        ../../SDLCEngine/src/engine/render/render_init.c
        ../../SDLCEngine/src/engine/render/render_util.c
        ../../SDLCEngine/src/engine/font_cache/SDL_FontCache.c
        ../../SDLCEngine/src/engine/text/text.c
        ../../SDLCEngine/src/engine/global.c
        ../../SDLCEngine/src/engine/time.c
)

set_target_properties(Pixelinator PROPERTIES VERSION ${PROJECT_VERSION})
#set_target_properties(Pixelinator PROPERTIES SOVERSION 1)

#set_target_properties(Pixelinator PROPERTIES PUBLIC_HEADER pixelinator.h)
target_include_directories(Pixelinator INTERFACE ../../SDLCEngine)
target_link_libraries(Pixelinator PRIVATE ../../SDLCEngine/src/engine/glad SDL2::SDL2 SDL2_mixer::SDL2_mixer SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
set("-OFast")

include(GNUInstallDirs)
install(TARGETS Pixelinator
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})