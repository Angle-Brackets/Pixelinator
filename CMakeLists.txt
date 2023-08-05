cmake_minimum_required(VERSION 3.21)
project(Pixelinator VERSION 1.0 DESCRIPTION "A 2D Engine using SDL and C")

set( CMAKE_CXX_STANDARD 11 CACHE STRING "" FORCE )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE )

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE EQUAL Release)
    message("Building Release...")
endif()

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")


if( ${CMAKE_SYSTEM_NAME} MATCHES "Android" )
    add_library( main SHARED )
else()
    add_executable(main main.c include/types.h include/util.h src/engine/render/render.c include/render/render.h src/engine/render/render_init.c src/engine/render/render_internal.h src/engine/global.c include/global.h src/engine/io/io.c include/io/io.h src/engine/render/render_util.c include/input/input.h src/engine/input/input.c include/config/config.h src/engine/config/config.c src/engine/time.c include/time.h src/engine/graphics/bitmap/bitmap.c include/graphics/bitmap.h src/engine/graphics/bitmap/pixel_threading.c src/engine/graphics/bitmap/pixel_threading.h src/engine/audio/sound.c include/audio/sound.h src/engine/graphics/draw/shapes.c include/graphics/shapes.h src/engine/core/core.c include/core/core.h src/engine/font_cache/SDL_FontCache.c src/engine/font_cache/SDL_FontCache.h src/engine/text/text.c include/text/text.h src/engine/graphics/sprite/sprite.c include/graphics/sprite.h)
    set_target_properties( main PROPERTIES OUTPUT_NAME ${CMAKE_PROJECT_NAME} )
endif()



find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(main PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(main "${CMAKE_THREAD_LIBS_INIT}")
endif()

add_subdirectory("external")
add_subdirectory(glad/)
include_directories(include/)

target_link_libraries(main glad)