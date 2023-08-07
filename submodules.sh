#!/bin/bash
# This file is to manually download the dependencies for the project, shouldn't be necessary if you pulled.
# Download all dependencies.
git submodule add -b SDL2 https://github.com/libsdl-org/SDL.git external/sdl2
git submodule add -b SDL2 https://github.com/libsdl-org/SDL_image.git external/sdl-image
git submodule add -b SDL2 https://github.com/libsdl-org/SDL_ttf.git external/sdl-ttf
git submodule add -b SDL2 https://github.com/libsdl-org/SDL_mixer.git external/sdl-mixer

# SDL-TTF and SDL-Mixer require some extra dependencies to get working. For some reason the download shell
# file is not included with TTF so it is copied from the repo.

cd external/sdl-ttf/external
set -e

cd $(dirname "$0")/..
cat .gitmodules | \
while true; do
    read module || break
    read line; set -- $line
    path=$3
    read line; set -- $line
    url=$3
    read line; set -- $line
    branch=$3
    git clone $url $path -b $branch --recursive
done

cd ..
cd ..
cd sdl-mixer/external
./download.sh

echo "Make sure that you git checkout within each submodule to have them point to the corresponding RELEASED commit by checking out to a pariticular commit."
echo "All dependencies downloaded, make sure to add the CMakeLists.txt file that is in the repo to the external directory to add these to your project."
