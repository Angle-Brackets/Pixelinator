# Rishit Khare
# This makefile is written to use the Apple clang compiler.

# Make sure all the necessary SDL library frameworks are installed:
# Download the SDL2.framework using https://github.com/libsdl-org/SDL/releases (.dmg for mac)
# Download the SDL2_mixer.framework using https://github.com/libsdl-org/SDL_mixer/releases (.dmg for mac)
# Download the SDL2_image.framework using https://github.com/libsdl-org/SDL_image/releases (.dmg for mac)

# download Glad with online assembler: https://glad.dav1d.de

# move all .framework files in dmgs into the /Library/Frameworks/ folder.

# files are located relative to project root, and compiled to objects in clang/objects/ directory.
OBJ_DIR = objects/
ROOT = ../

# to add flags to ALL gcc commands, add flags here:
FLAGS = -Wall -Wextra -Ofast -g

# directories used to resolve include preprocessors
FDIR = /Library/Frameworks # additional directory for user frameworks 
GLAD_INCLUDE = $(ROOT)glad/include/
SDL_INCLUDE = /Library/Frameworks/SDL2.framework/Headers/
SDL_IMG_INCLUDE = /Library/Frameworks/SDL2_image.framework/Headers/
SDL_MIX_INCLUDE = /Library/Frameworks/SDL2_mixer.framework/Headers/

# makefile prereqs for linking


ALL_REQS = $(OBJ_DIR)main.o $(OBJ_DIR)render.o

# compiles all files
compile_osx: $(ALL_REQS)
	mkdir -p $(OBJ_DIR)
# gcc test.c -F$(FDIR) -framework SDL2,SDL2_mixer,SDL_image $(FLAGS) -o $(CLANG_DIR)Pixelinator
	@echo "Linking stage is not complete"
	
# deletes all C ROF files generated thus far
clean:
	rm -r $(OBJ_DIR)

# --- object files ---

$(OBJ_DIR)main.o:
	gcc $(ROOT)main.c $(FLAGS) -F$(FDIR) -I$(GLAD_INCLUDE) -I$(SDL_INCLUDE) -I$(SDL_MIX_INCLUDE) -c -o $(OBJ_DIR)main.o

$(OBJ_DIR)render.o:
	gcc $(ROOT)src/engine/render/render.c $(FLAGS) -F$(FDIR) -I$(SDL_INCLUDE) -I$(SDL_MIX_INCLUDE) -c -o $(OBJ_DIR)render.o

$(OBJ_DIR)render_init.o:
	gcc $(ROOT)src/engine/render/render_init.c $(FLAGS) -F$(FDIR) -I$(SDL_INCLUDE) -I$(SDL_MIX_INCLUDE) -c -o $(OBJ_DIR)render_init.o

$(OBJ_DIR)global.o:
	gcc $(ROOT)src/engine/global.c $(FLAGS) -F$(FDIR) -I$(SDL_INCLUDE) -I$(SDL_MIX_INCLUDE) -c -o $(OBJ_DIR)global.o

$(OBJ_DIR)io.o:
	gcc $(ROOT)src/engine/io/io.c $(FLAGS) -F$(FDIR) -I$(SDL_INCLUDE) -I$(SDL_MIX_INCLUDE) -I$(SDL_IMG_INCLUDE) -c -o $(OBJ_DIR)io.o

$(OBJ_DIR)render_util.o:
	@echo "render_util.c is deprecated, cannot generate object file!"

$(OBJ_DIR)input.o:
	gcc $(ROOT)src/engine/input/input.c $(FLAGS) -F$(FDIR) -I$(SDL_INCLUDE) -I$(SDL_MIX_INCLUDE) -c -o $(OBJ_DIR)input.o

$(OBJ_DIR)config.o:
	gcc $(ROOT)src/engine/config/config.c $(FLAGS) -F$(FDIR) -I$(SDL_INCLUDE) -I$(SDL_MIX_INCLUDE) -c -o $(OBJ_DIR)config.o

$(OBJ_DIR)time.o:
	gcc $(ROOT)src/engine/time.c $(FLAGS) -F$(FDIR) -I$(SDL_INCLUDE) -I$(SDL_MIX_INCLUDE) -c -o $(OBJ_DIR)time.o

$(OBJ_DIR)bitmap.o:
	gcc $(ROOT)src/engine/graphics/bitmap/bitmap.c $(FLAGS) -F$(FDIR) -I$(SDL_INCLUDE) -I$(SDL_MIX_INCLUDE) -c -o $(OBJ_DIR)bitmap.o

$(OBJ_DIR)pixel_threading.o:
	gcc $(ROOT)src/engine/graphics/bitmap/pixel_threading.c $(FLAGS) -F$(FDIR) -I$(SDL_INCLUDE) -c -o $(OBJ_DIR)pixel_threading.o

$(OBJ_DIR)shapes.o:
	gcc $(ROOT)src/engine/graphics/draw/shapes.c $(FLAGS) -F$(FDIR) -I$(SDL_INCLUDE) -I$(SDL_MIX_INCLUDE) -c -o $(OBJ_DIR)shapes.o

$(OBJ_DIR)sound.o:
	gcc $(ROOT)src/engine/audio/sound.c $(FLAGS) -F$(FDIR) -I$(SDL_INCLUDE) -I$(SDL_MIX_INCLUDE) -c -o $(OBJ_DIR)sound.o

$(OBJ_DIR)core.o:
	gcc $(ROOT)src/engine/core/core.c $(FLAGS) -F$(FDIR) -I$(SDL_INCLUDE) -I$(SDL_MIX_INCLUDE) -c -o $(OBJ_DIR)core.o
