# Author: Rishit Khare
# Modified by Angle-Brackets
# This Makefile is written to compile the PIXELINATOR engine
# using Clang, a version of gcc for OSX. It will not work on 
# other operating systems.

# ---- DEPENDENCIES ----
# Make sure all the necessary SDL library frameworks are installed:
# Download the SDL2.framework from https://github.com/libsdl-org/SDL/releases (.dmg for mac)
# Download the SDL2_mixer.framework from https://github.com/libsdl-org/SDL_mixer/releases (.dmg for mac)
# Download the SDL2_image.framework from https://github.com/libsdl-org/SDL_image/releases (.dmg for mac)

# download Glad with online assembler: https://glad.dav1d.de

# move all .framework files in dmgs into the /Library/Frameworks/ folder.
# place glad/ directory directly under root of project directory.

# ---- MAKEFILE ----
# files are located relative to ROOT.
# Objects compiled to OBJ_DIR directory.
# Final executable compiled to EXE_DIR directory.
OBJ_DIR = objects/
EXE_DIR = executables/
ROOT = ../

# to add flags to ALL gcc commands, add flags here:
FLAGS_RELEASE = -Wall -Wextra -Ofast -g -lpthread
FLAGS_DEBUG = -Wall -Wextra -g -lpthread

# directories used to resolve include preprocessors
FDIR = /Library/Frameworks # additional directory for user frameworks (apart from /System/Library/Frameworks/)
GLAD_INCLUDE = $(ROOT)glad/include/
SDL_INCLUDE = /Library/Frameworks/SDL2.framework/Headers/
SDL_IMG_INCLUDE = /Library/Frameworks/SDL2_image.framework/Headers/
SDL_MIX_INCLUDE = /Library/Frameworks/SDL2_mixer.framework/Headers/

# Makefile object prereqs for linking
GLOBAL = $(OBJ_DIR)global.o $(OBJ_DIR)time.o
RENDER = $(OBJ_DIR)render_init.o $(OBJ_DIR)render.o
IO = $(OBJ_DIR)io.o
INPUT = $(OBJ_DIR)input.o
GRAPHICS = $(OBJ_DIR)bitmap.o $(OBJ_DIR)pixel_threading.o $(OBJ_DIR)shapes.o
CORE = $(OBJ_DIR)core.o
CONFIG = $(OBJ_DIR)config.o
AUDIO = $(OBJ_DIR)sound.o

ALL_REQS = $(OBJ_DIR)main.o $(GLOBAL) $(RENDER) $(IO) $(INPUT) $(GRAPHICS) $(CORE) $(CONFIG) $(AUDIO)

# compiles all files (MacOS)
compile_osx_release: $(ALL_REQS)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(EXE_DIR)
	gcc $(ALL_REQS) -F$(FDIR) -framework SDL2 -framework SDL2_mixer -framework SDL2_image $(FLAGS_RELEASE) -o $(EXE_DIR)Pixelinator
	@echo "Executable generated! Successfully compiled :D"

compile_osx_debug: $(ALL_REQS)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(EXE_DIR)
	gcc $(ALL_REQS) -F$(FDIR) -framework SDL2 -framework SDL2_mixer -framework SDL2_image $(FLAGS_DEBUG) -o $(EXE_DIR)Pixelinator_DEBUG
	@echo "Executable generated! Successfully compiled :D"
	
# deletes all C ROF files generated thus far
clean:
	rm -r $(OBJ_DIR)
	mkdir $(OBJ_DIR)

# ---- OBJECT FILE TARGETS ----

$(OBJ_DIR)main.o:
	mkdir -p $(OBJ_DIR)
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
