#Compiles the library (Not fully working, headers somehow aren't included)
cmake_minimum_required(VERSION 3.21)
project(Pixelinator VERSION 1.0 DESCRIPTION "A 2D Engine using SDL and C")
set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
add_subdirectory(../glad ../src/engine/glad)

add_library(Pixelinator STATIC
        ../src/engine/audio/sound.c
        ../src/engine/config/config.c
        ../src/engine/core/core.c
        ../src/engine/graphics/bitmap/bitmap.c
        ../src/engine/graphics/bitmap/pixel_threading.c
        ../src/engine/graphics/draw/shapes.c
        ../src/engine/input/input.c
        ../src/engine/io/io.c
        ../src/engine/render/render.c
        ../src/engine/render/render_init.c
        ../src/engine/render/render_util.c
        ../src/engine/global.c
        ../src/engine/time.c
)

set_target_properties(Pixelinator PROPERTIES VERSION ${PROJECT_VERSION})
#set_target_properties(Pixelinator PROPERTIES SOVERSION 1)

#set_target_properties(Pixelinator PROPERTIES PUBLIC_HEADER pixelinator.h)
target_include_directories(Pixelinator INTERFACE ..)
target_link_libraries(Pixelinator PRIVATE ../src/engine/glad SDL2::SDL2 SDL2_mixer::SDL2_mixer SDL2_image::SDL2_image)
set("-OFast")

include(GNUInstallDirs)
install(TARGETS Pixelinator
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})