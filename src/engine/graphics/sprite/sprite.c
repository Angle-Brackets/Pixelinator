#include <SDL_image.h>
#include "util.h"
#include "../../../../global.h"
#include "graphics/sprite.h"

static SDL_RWops* io = NULL;

sprite_t* create_sprite(i32 x, i32 y, u32 width, u32 height, sprite_sheet* sheet){
    if(width < 0 || width > global.bitmap.width || height < 0 || height > global.bitmap.height){
        ERROR_RETURN(NULL, "Invalid height or width provided! Make sure it is widin the bounds of the bitmap!\n")
    }

    sprite_t* sprite = (sprite_t*)malloc(sizeof(sprite_t));
    VERIFY_HEAP_DATA(sprite)
    *sprite = (sprite_t){
        .x = x,
        .y = y,
        .width = width,
        .height = height,
        .sheet = sheet,
        .sprite_data = NULL
    };

    sprite->sprite_data = (SDL_Color**)malloc(sizeof(SDL_Color*) * height);
    VERIFY_HEAP_DATA(sprite->sprite_data)
    for(u32 i = 0; i < height; i++){
        sprite->sprite_data[i] = (SDL_Color*)malloc(sizeof(SDL_Color) * width);
        VERIFY_HEAP_DATA(sprite->sprite_data[i])
    }

    return sprite;
}

sprite_sheet* create_sprite_sheet(const char* file_path, SDL_Color* ignored_colors, u32 ignored_colors_len){
    //Reading in the file before we actually make the struct
    if((io = SDL_RWFromFile(file_path, "rb")) == NULL){
        ERROR_RETURN(NULL, "Failed to read file.\n")
    }

    sprite_sheet* sheet = (sprite_sheet*)malloc(sizeof(sprite_sheet));
    VERIFY_HEAP_DATA(sheet)
    sheet->sheet_path = file_path;

    if(ignored_colors != NULL) {
        sheet->ignored_colors = (SDL_Color *) malloc(sizeof(SDL_Color) * ignored_colors_len);
        sheet->ignored_colors_len = ignored_colors_len;
        VERIFY_HEAP_DATA(sheet->ignored_colors)
        for (u32 i = 0; i < ignored_colors_len; i++) {
            sheet->ignored_colors[i] = ignored_colors[i];
        }
    }
    else {
        sheet->ignored_colors = NULL;
        ignored_colors_len = 0;
    }

    //Loads up the surface data!
    sheet->sheet_data = IMG_LoadPNG_RW(io);
    SDL_RWclose(io);
    io = NULL;

    return sheet;
}

bool update_sprite_from_spritesheet(sprite_t* sprite, u32 sheet_x, u32 sheet_y, u32 sprite_x, u32 sprite_y, u32 width, u32 height){
    if(sprite == NULL || sprite->sheet == NULL){
        ERROR_RETURN(false, "Invalid sprite or spritesheet provided.\n")
    }

    u32* current_row;
    for(u32 i = sheet_y; i < sprite->sheet->sheet_data->h && i < sheet_y + height; i++){
        current_row = (u32 *)((u8 *) sprite->sheet->sheet_data->pixels + (sheet_y + i) * sprite->sheet->sheet_data->pitch);
        for(u32 j = sheet_x; j < sprite->sheet->sheet_data->w && j < sheet_x + width; j++){
            if(sprite_y + (i - sheet_y) < sprite->height && sprite_x + (j - sheet_x) < sprite->width) {
                sprite->sprite_data[sprite_y + (i - sheet_y)][sprite_x +(j - sheet_x)] = *(SDL_Color*)&current_row[j];
            }
        }
    }

    return true;
}

void free_sprite(sprite_t* sprite){
    for(u32 i = 0; i < sprite->height; i++){
        free(sprite->sprite_data[i]);
        sprite->sprite_data[i] = NULL;
    }
    free(sprite->sprite_data);
    sprite->sprite_data = NULL;
    sprite = NULL;
}

void free_sprite_sheet(sprite_sheet* sheet){
    free(sheet->ignored_colors);
    sheet->ignored_colors = NULL;
    SDL_FreeSurface(sheet->sheet_data);
    sheet->sheet_data = NULL;
    free(sheet);
    sheet = NULL;
}
