# Rishit Khare
# This makefile is written to use the Apple clang compiler.

# Make sure all the necessary SDL library frameworks are installed:
# Download the SDL2.framework using https://github.com/libsdl-org/SDL/releases (.dmg for mac)
# Download the SDL2_mixer.framework using https://github.com/libsdl-org/SDL_mixer/releases (.dmg for mac)
# Download the SDL2_image.framework using https://github.com/libsdl-org/SDL_image/releases (.dmg for mac)

# download Glad with online assembler: https://glad.dav1d.de

# move all .framework files in dmgs into the /Library/Frameworks/ folder.

# files to compile:
# src/engine/render/render.c 
# include/render/render.h 
# src/engine/render/render_init.c 
# src/engine/render/render_internal.h 
# src/engine/global.c 
# include/global.h 
# src/engine/io/io.c 
# include/io/io.h 
# src/engine/render/render_util.c 
# include/input/input.h 
# src/engine/input/input.c 
# include/config/config.h 
# src/engine/config/config.c 
# src/engine/time.c 
# include/time.h 
# src/engine/graphics/bitmap/bitmap.c 
# include/graphics/bitmap.h 
# src/engine/graphics/bitmap/pixel_threading.c 
# src/engine/graphics/bitmap/pixel_threading.h 
# src/engine/audio/sound.c 
# include/audio/sound.h 
# src/engine/graphics/draw/shapes.c 
# include/graphics/shapes.h 
# src/engine/core/core.c 
# include/core/core.h

CLANG_DIR = ./clang/
OBJ_DIR = $(CLANG_DIR)/objects/

FLAGS = -Wall -Wextra -Ofast -g
FDIR = /Library/Frameworks # additional directory for user frameworks 

# directories used to resolve include preprocessors
GLAD_INCLUDE = ./glad/include/
SDL_INCLUDE = /Library/Frameworks/SDL2.framework/Headers/
SDL_IMG_INCLUDE = /Library/Frameworks/SDL2_image.framework/Headers/
SDL_MIX_INCLUDE = /Library/Frameworks/SDL2_mixer.framework/Headers/

# makefile prereqs for linking
REQUIRED_OBJECTS = $(OBJ_DIR)main.o $(OBJ_DIR)render.o

# compiles all files
compile_osx: $(OBJ_DIR)main.o | $(CLANG_DIR) $(OBJ_DIR)
	gcc test.c -F$(FDIR) -framework SDL2,SDL2_mixer,SDL_image $(FLAGS) -o $(CLANG_DIR)Pixelinator
	@echo "Completed successfully"

# --- directories ---

$(CLANG_DIR):
	mkdir clang_builds

$(OBJ_DIR):
	mkdir clang/objects

# --- object files ---

$(OBJ_DIR)main.o:
	gcc main.c -F$(FDIR) $(FLAGS) -I$(GLAD_INCLUDE) -I$(SDL_INCLUDE) -I$(SDL_MIX_INCLUDE) -c -o clang/objects/main.o

$(OBJ_DIR)render.o:
	gcc src/engine/render/render.c -c -o clang/objects/render.o


