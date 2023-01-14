<p align="center">
  <img src="imgs/Pixelinator_logo.png"/>
</p>

<h3 align="center">
Version 1.0
</h3>

This is a simple 2D engine written in C using the SDL Library + OpenGL, primarily designed for bitmap graphics,
but technically does support other OpenGL primitives.
## Features
- Can render individual pixels to screen in a multithreaded bitmap graphics mode efficiently.
- Bitmap graphics autoscale to the resolution of the window and then interpolate if necessary to minimize quality loss.
- Can play sound effects and music with wav and mp3 respectively.
- Bitmap can be transformed easily (rotations, scaling, translation).
- Keyboard Input
- Rudimentary support for loading PNGs as bitmaps (must be RGBA format) and loading custom file
  formats like ``.ini`` through the config header.
- Engine automatically pauses all processes if focus is lost to save resources (can be disabled if wanted).

## In Progress
- A better way to import the library other than just shoving the code in a project, but statically linking this has been a headache.

## Other Contributors
- Thank you to [@rishitkhare](https://github.com/rishitkhare) for the logo, initial testing, and code contributions!

## Installation
- There is a Makefile inside clang-builds (should also work with gcc but not tested) that will compile all of the code correctly
  for MacOS and in theory Linux as well. Make sure that you have the SDL2, SDL2_Mixer, SDL2_Image, and glad libraries installed beforehand.
  You should then be able to compile them on Mac and Linux with the respective Makefile or CMakeLists.

### Examples
1. Bitmap graphics example
![alt text](imgs/bitmapexample1.png?raw=true)
2. Bitmap Graphics Example 2 (Runs at full speed in engine)
![alt text](imgs/demo2.gif?raw=true)

