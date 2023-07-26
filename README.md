<p align="center">
  <img src="imgs/Pixelinator_logo.png"/>
</p>

<h3 align="center">
Version 1.1
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
- TTF Text Rendering Support!
- Support for Sprites and Drawing from Sprite Sheets with Bitmap Graphics.
- Statically link the library to include and use in your own projects!

## In Progress
- Optimizations mostly

## Other Contributors
- Thank you to [@rishitkhare](https://github.com/rishitkhare) for the logo, initial testing, and code contributions!

## Installation
- There is a CMakeLists.txt file within the ``include`` directory, just run `cmake .` while inside that directory in your terminal and then
run ``make`` to generate the `libPixelinator.a` file. This is the entire codebase as a library now!
- Make sure that when you link the library, include all the headers in the include directory in your project along with the SDL dependencies!

### Examples
1. Bitmap graphics example
![alt text](imgs/bitmapexample1.png?raw=true)
2. Bitmap Graphics Example 2 (Runs at full speed in engine)
![alt text](imgs/demo2.gif?raw=true)
3. Bitmap Graphics Example 3 (Runs at full speed in engine at 60fps)
![alt text](imgs/s3gif.gif)
