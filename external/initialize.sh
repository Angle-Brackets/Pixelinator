#!/bin/bash

# Downloads SDL-TTF dependencies
cd sdl-ttf/external
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

cd ....
cd sdl-mixer/external
./download.sh
echo "All dependencies downloaded, make sure to add the CMakeLists.txt file that is in the repo to the external directory to add these to your project"
