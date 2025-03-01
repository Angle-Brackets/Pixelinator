include(FetchContent)

# Set common properties for all dependencies
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(FETCHCONTENT_QUIET OFF)

# SDL2
message(STATUS "Fetching SDL2...")
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.28.5
)
set(SDL_LIBC ON CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL2)

# SDL_image
message(STATUS "Fetching SDL_image...")
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.1
)
set(SDL2IMAGE_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_VENDORED ON CACHE BOOL "" FORCE)
set(SDL2IMAGE_DEPS_SHARED OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL2_image)

# SDL_ttf
message(STATUS "Fetching SDL_ttf...")
FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.20.2
)
set(SDL2TTF_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2TTF_VENDORED ON CACHE BOOL "" FORCE)
set(SDL2TTF_HARFBUZZ ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL2_ttf)

# SDL_mixer
message(STATUS "Fetching SDL_mixer...")
FetchContent_Declare(
    SDL2_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-2.6.3
)
set(SDL2MIXER_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_VENDORED ON CACHE BOOL "" FORCE)
set(SDL2MIXER_DEPS_SHARED OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_FLAC OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_MOD OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_MP3 OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_MIDI OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_OPUS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL2_mixer)

# Link dependencies to the main project
target_link_libraries(${CMAKE_PROJECT_NAME} 
    SDL2::SDL2main 
    SDL2::SDL2-static
    SDL2_image::SDL2_image-static
    SDL2_ttf::SDL2_ttf-static
    SDL2_mixer::SDL2_mixer-static
)