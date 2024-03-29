set( BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE )

# SDL
# https://github.com/libsdl-org/SDL
set( SDL_LIBC ON CACHE BOOL "" FORCE )
set( SDL_TEST OFF CACHE BOOL "" FORCE )
add_subdirectory(SDL)
target_link_libraries( ${CMAKE_PROJECT_NAME} SDL2::SDL2main SDL2::SDL2-static )

# SDL_image
# https://github.com/libsdl-org/SDL_image
set( SDL2IMAGE_SAMPLES OFF CACHE BOOL "" FORCE )
set( SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE )
set( SDL2IMAGE_VENDORED ON CACHE BOOL "" FORCE )
set( SDL2IMAGE_DEPS_SHARED OFF CACHE BOOL "" FORCE )
add_subdirectory( sdl-image )
target_link_libraries( ${CMAKE_PROJECT_NAME} SDL2_image::SDL2_image-static)

# SDL_ttf
# https://github.com/libsdl-org/SDL_ttf
# Make sure you run ./download.sh in the directory.
set( SDL2TTF_SAMPLES OFF CACHE BOOL "" FORCE )
set( SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE )
set( SDL2TTF_VENDORED ON CACHE BOOL "" FORCE )
set( SDL2TTF_HARFBUZZ ON CACHE BOOL "" FORCE )
add_subdirectory( sdl-ttf )
target_link_libraries( ${CMAKE_PROJECT_NAME} SDL2_ttf::SDL2_ttf-static )

# SDL_mixer
# https://github.com/libsdl-org/SDL_mixer
# Make sure you run ./download.sh in the directory.
set( SDL2MIXER_SAMPLES OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_INSTALL OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_VENDORED ON CACHE BOOL "" FORCE )
set( SDL2MIXER_DEPS_SHARED OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_FLAC OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_MOD OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_MP3 OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_MIDI OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_OPUS OFF CACHE BOOL "" FORCE )
add_subdirectory( sdl-mixer )
target_link_libraries( ${CMAKE_PROJECT_NAME} SDL2_mixer::SDL2_mixer-static )