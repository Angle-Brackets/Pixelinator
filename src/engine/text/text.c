#include <dirent.h>
#include "text/text.h"
#include "global.h"

static PIX_Font* default_font = NULL;

PIX_Font* load_pix_font(const char* font_path, u32 font_size, SDL_Color color){
    PIX_Font* font = FC_CreateFont();
    FC_LoadFont(font, global.render.renderer, font_path, font_size, color, TTF_STYLE_NORMAL);
    return font;
}

bool set_default_font(PIX_Font* font){
    if(font == NULL){
        return false;
    }
    default_font = font;
    return true;
}

static PIX_Font* find_system_default(const char* font_dir){
    DIR* dir = NULL;
    struct dirent* entry = NULL;
    if((dir = opendir(font_dir)) == NULL){
        WARN("Failed to open default font directory!\n")
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG || entry->d_type == DT_LNK) {  // Check if it's a regular file
            const char* extension = strrchr(entry->d_name, '.');
            if (extension != NULL && strncmp(extension, ".ttf", 4) == 0) {
                char buffer[256] = "\0";

                //Windows uses backslash.
                #ifdef _WIN32
                snprintf(buffer, 256, "%s\\%s", font_dir, entry->d_name);
                #else
                snprintf(buffer, 256, "%s/%s", font_dir, entry->d_name);
                #endif

                if((default_font = load_pix_font(buffer, 12, (SDL_Color){0,0,0,255})) == NULL){
                    WARN("Failed to load default font. Please provide a font manually.\n")
                    closedir(dir);
                    break;
                }
                closedir(dir);
                printf("Found font: %s\nSet to font size 12 and black fill color.\n", entry->d_name);
                return default_font;
            }
        }
    }

    WARN("Failed to find a default font. Please provide a font manually.\n")
    return NULL;
}

PIX_Font* get_default_font(){
    //Either return the currently set default font or the default system font.
    if(default_font != NULL){
        return default_font;
    }

    WARN("Attempting to set default font to system font...\n");
    #ifdef __APPLE__
        return find_system_default("/Library/Fonts/");
    #elif _WIN32
        return find_system_default("C:\\\\Windows\\\\Fonts"); //NOT TESTED
    #elif __linux__
        return find_system_default("/usr/share/fonts"); //NOT TESTED
    #else
        WARN("Unknown Operating System. Returning NULL for default font.\n");
        return NULL;
    #endif
}

void free_pix_font(PIX_Font* font){
    FC_FreeFont(font);
    font = NULL;
}
