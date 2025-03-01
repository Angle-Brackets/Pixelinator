cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0075 NEW)
cmake_policy(SET CMP0091 NEW)

project(Pixelinator 
        VERSION 1.0 
        DESCRIPTION "A 2D Engine using SDL and C"
        LANGUAGES C)

# Build configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Building Release...")
    set(CMAKE_C_FLAGS_RELEASE "-Ofast")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building Debug...")
    set(CMAKE_C_FLAGS "-Wall -Wextra")
    set(CMAKE_C_FLAGS_DEBUG "-g")
endif()

# Uncomment for platform-specific settings
# set(CMAKE_OSX_ARCHITECTURES "x86_64")  # Build for x86 Darwin
# set(CMAKE_C_COMPILER emcc)             # Emscripten compiler

# Engine library
set(ENGINE_SOURCES
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
)

add_library(Pixelinator STATIC ${ENGINE_SOURCES})

# Main executable
set(APP_EXE PixelinatorExe)

if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    add_library(${APP_EXE} SHARED)
else()
    add_executable(${APP_EXE} main.c)
    set_target_properties(${APP_EXE} PROPERTIES OUTPUT_NAME ${CMAKE_PROJECT_NAME})
endif()

# Threading support
find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(${APP_EXE} PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(${APP_EXE} "${CMAKE_THREAD_LIBS_INIT}")
endif()

# Include directories
target_include_directories(Pixelinator PUBLIC include)
target_include_directories(${APP_EXE} PUBLIC include)

# Setup external dependencies
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake)

# Link the engine library to the executable
target_link_libraries(${APP_EXE} Pixelinator)