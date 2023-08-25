#include <SDL_image.h>
#include "util.h"
#include "global.h"
#include "graphics/sprite.h"

static SDL_RWops* io = NULL;

sprite_t* create_sprite(i32 x, i32 y, u32 width, u32 height, sprite_sheet* sheet){
    if(width < 0 || height < 0){
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

sprite_t* create_sprite_from_img(i32 x, i32 y, const char* path){
    //Reading in the file before we actually make the struct
    SDL_Surface* temp;
    SDL_Surface* surface;
    if((temp = IMG_Load(path)) == NULL){
        ERROR_RETURN(NULL, "Failed to read file.\n")
    }

    if((surface = SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_RGBA32, 0)) == NULL){
        ERROR_RETURN(NULL, "Failed to convert surface.\n")
    }

    if(surface->w < 0 || surface->h < 0){
        ERROR_RETURN(NULL, "Invalid height or width provided! Make sure it is within the bounds of the bitmap!\n")
    }

    sprite_t* sprite = (sprite_t*)malloc(sizeof(sprite_t));
    VERIFY_HEAP_DATA(sprite)
    *sprite = (sprite_t){
            .x = x,
            .y = y,
            .width = surface->w,
            .height = surface->h,
            .sheet = NULL,
            .sprite_data = NULL
    };

    sprite->sprite_data = (SDL_Color**)malloc(sizeof(SDL_Color*) * surface->h);
    for(u32 i = 0; i < surface->h; i++){
        sprite->sprite_data[i] = (SDL_Color*)malloc(sizeof(SDL_Color) * surface->w);
        VERIFY_HEAP_DATA(sprite->sprite_data[i])
    }

    u32* current_row;

    for(i32 i = 0; i < surface->h; i++){
        current_row = (u32 *)((u8 *) surface->pixels + i * surface->pitch);
        for(i32 j = 0; j < surface->w; j++){
            sprite->sprite_data[i][j] = *(SDL_Color*)&current_row[j];
        }
    }

    SDL_FreeSurface(temp);
    SDL_FreeSurface(surface);

    return sprite;
}

sprite_sheet* create_sprite_sheet(const char* file_path, SDL_Color* ignored_colors, u32 ignored_colors_len){
    //Reading in the file before we actually make the struct
    SDL_Surface* sheet_img = IMG_Load(file_path);
    if(sheet_img == NULL){
        ERROR_RETURN(NULL, "Failed to load file.\n")
    }

    if(sheet_img->format->format != SDL_PIXELFORMAT_RGBA32){
        SDL_Surface* temp = sheet_img;
        sheet_img = SDL_ConvertSurfaceFormat(sheet_img, SDL_PIXELFORMAT_RGBA32, 0);
        SDL_FreeSurface(temp);
    }

    sprite_sheet* sheet = (sprite_sheet*)malloc(sizeof(sprite_sheet));
    VERIFY_HEAP_DATA(sheet)
    sheet->sheet_path = file_path;
    sheet->sheet_data = sheet_img;

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
