#include <SDL.h>
#include "util.h"
#include "global.h"
#include "graphics/pixel_threading.h"

static SDL_Color** pixel_buffer = NULL; //2D array that is initialized to be a 2D matrix of pixels that is HEIGHT, WIDTH (rows and cols)
static u32 bitmap_scale_x = 1; //Field for appropriately transform the bitmap to fit the screen width (X values)
static u32 bitmap_scale_y = 1; //Field for appropriately transform the bitmap to fit the screen height (Y values)
SDL_Texture* bitmap = NULL; //Bitmap for drawing pixels to screen
bool bitmap_initialized = false; //Field to tell if we've initialized bitmap graphics

void set_background_clear(SDL_Color* color){
    if(color != NULL) {
        if (SDL_SetRenderDrawColor(global.render.renderer, color->r, color->g, color->b, color->a) != 0) {
            ERROR_EXIT("Failed to set default render graphics color.\n")
        }
    }
    else if(SDL_SetRenderDrawColor(global.render.renderer, 0, 0, 0, 0) != 0) {
        ERROR_EXIT("Failed to set default render graphics color.\n")
    }
}

void set_stroke_fill(SDL_Color* color){
    global.bitmap.stroke_fill = *color;
}

void set_shape_fill(SDL_Color* color){
    global.bitmap.shape_fill = *color;
}

void set_bitmap_tint(SDL_Color* color){
    global.bitmap.tint = *color;
}

void fill_background(SDL_Color *color) {
    for(u32 i = 0; i < global.bitmap.height; i++){
        for(u32 j = 0; j < global.bitmap.width; j++){
            draw_pixel(color, j, i);
        }
    }
}

static i32 clamp(i32 value, i32 min, i32 max){
    if(value < min)
        value = min;
    else if(value > max)
        value = max;
    return value;
}

void draw_pixel(SDL_Color* color, i32 x, i32 y){
    if(pixel_buffer == NULL){
        ERROR_EXIT("Pixel Buffer not initialized, make sure that you have enabled the bitmap with the Render Flag BITMAP_ENABLED!")
    }

    if(x < 0 || x >= global.bitmap.width || y < 0 || y >= global.bitmap.height)
        return;

    //Update the pixel buffer, this does not draw graphics to the screen just yet, we use draw_pixel_buffer() to do that.
    if(color != NULL && *(u32*)&pixel_buffer[y][x] != *(u32*)color && color->a > 0){
        //Alpha blending calculation.
        if(color->a > 0 && color->a < 255){
            f32 alpha = color->a / 255.0F;
            SDL_Color new = {
                    .r = (color->r * alpha) + ((1-alpha) * pixel_buffer[y][x].r),
                    .g = (color->g * alpha) + ((1-alpha) * pixel_buffer[y][x].g),
                    .b = (color->b * alpha) + ((1-alpha) * pixel_buffer[y][x].b),
                    .a = color->a
            };

            pixel_buffer[y][x] = new;
        }
        else {
            pixel_buffer[y][x] = *color;
        }

        global.bitmap.bitmap_updates++;
    }
    global.bitmap.bitmap_calls++;
}

//Used to check if the color is not the denylist for the sprite sheet.
static bool verify_color(sprite_sheet* sheet, SDL_Color* color){
    if(sheet == NULL)
        return true;

    for(i32 k = 0; k < sheet->ignored_colors_len; k++){
        if (color->r == sheet->ignored_colors[k].r &&
            color->g == sheet->ignored_colors[k].g &&
            color->b == sheet->ignored_colors[k].b){
            return false;
        }
    }

    return true;
}

void draw_sprite_to_bitmap(sprite_t* sprite, u32 scale){
    //Scale up code.
    i32 fxs = 0, fxm = 1, fx = 0;
    i32 fys = 0, fym = 1, fy = 0;
    if(scale > 1){
        for (i32 j = 0; j < sprite->height; j++) {
            fy = fys + j * fym;
            for (u32 js = 0; js < scale; js++) {
                for (i32 i = 0; i < sprite->width; i++) {
                    fx = fxs + i * fxm;
                    for (u32 is = 0; is < scale; is++) {
                        if(verify_color(sprite->sheet, &sprite->sprite_data[fy][fx]))
                            draw_pixel(&sprite->sprite_data[fy][fx], sprite->x + (i * scale) + is, sprite->y + (j * scale) + js);
                    }
                }
            }
        }
    }
    else{
        fx = fxs;
        for(i32 i = 0; i < sprite->width; i++, fx += fxm){
            fy = fys;
            for(i32 j = 0; j < sprite->height; j++, fy += fym){
                if(verify_color(sprite->sheet, &sprite->sprite_data[fy][fx])){
                    draw_pixel(&sprite->sprite_data[fy][fx], sprite->x + i, sprite->y + j);
                }
            }
        }
    }
}

void draw_pixels_from_surface(SDL_Surface* surface, i32 x0, i32 y0){
    static SDL_Surface* temp = NULL;
    //Need to fix surface format if it's not RGBA.
    u32* current_row;
    temp = surface;
    if(surface->format->format != SDL_PIXELFORMAT_RGBA32) {
        temp = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    }

    for(i32 y = 0; y < temp->h; y++){
        current_row = (u32 *)((u8 *) temp->pixels + y * temp->pitch);
        for(i32 x = 0; x < temp->w; x++){
            draw_pixel((SDL_Color*)&current_row[x], x + x0, y + y0);
        }
    }

    SDL_FreeSurface(temp);
}

SDL_Color* get_pixel(u32 x, u32 y){
    if(!bitmap_initialized){
        ERROR_RETURN(NULL, "Bitmap not initialized! Make sure you have the render flag BITMAP_ENABLED on and call initialize_bitmap()!\n")
    }

    if(x < 0 || x >= global.bitmap.width || y < 0 || y >= global.bitmap.height){
        ERROR_RETURN(NULL, "Invalid bitmap coordinates provided.\n")
    }

    return &pixel_buffer[y][x];
}

SDL_Color** get_pixel_buffer(){
    if(pixel_buffer == NULL){
        ERROR_EXIT("Pixel Buffer not initialized, make sure that you have enabled the bitmap with the Render Flag BITMAP_ENABLED!")
    }
    return pixel_buffer;
}

void rotate_bitmap_deg(u32 degrees) {
    global.bitmap.rotation = degrees % 360;
}

void rotate_bitmap_rad(f64 radians) {
    global.bitmap.rotation = (u32)(radians * (180.0 / M_PI)) % 360;
}

void bitmap_shift(i32 x, i32 y) {
    global.bitmap.transform.x = x;
    global.bitmap.transform.y = y;
}

void bitmap_scale(u32 width_scale, u32 height_scale) {
    if(width_scale > 500)
        width_scale = 500;
    if(height_scale > 500)
        height_scale = 500;

    if(width_scale == 0 || height_scale == 0){
        WARN("Scale-factor of 0 percent not allowed!\n")
        return;
    }

    f32 scale_w = 100.0f/width_scale;
    f32 scale_h = 100.0f/height_scale;

    global.bitmap.transform.w = global.render.width * scale_w;
    global.bitmap.transform.h = global.render.height * scale_h;
}

void initialize_bitmap(u32 width, u32 height){
    if(!bitmap_initialized) {
        Bitmap_State bmp;
        bmp.width = global.render.width;
        bmp.height = global.render.height;
        bmp.rotation = 0;

        bmp.tint = (SDL_Color){255,255,255};
        bmp.stroke_fill = (SDL_Color){0,0,0};
        bmp.shape_fill = (SDL_Color){255,255,255};
        bmp.transform = (SDL_Rect){.x = 0, .y = 0, .w = global.render.width, .h = global.render.height};

        if(width > 0)
            bmp.width = width;
        if(height > 0)
            bmp.height = height;

        global.bitmap = bmp; //Copies the bitmap state information to global

        //Sets the scale-factor to be the largest, strictly less-than integer multiple of the with and height
        //This is so that we can repeat this many pixels on the X,Y axes and THEN use a interpolation algorithm to scale the bitmap for larger resolutions.
        bitmap_scale_x = floor(global.render.width / global.bitmap.width);
        bitmap_scale_y = floor(global.render.height / global.bitmap.height);

        if ((pixel_buffer = (SDL_Color**)calloc(global.bitmap.height, sizeof(SDL_Color*))) == NULL) {
            ERROR_EXIT("Failed to initialize pixel buffer rows.\n")
        }

        for (int i = 0; i < global.bitmap.height; i++) {
            pixel_buffer[i] = (SDL_Color*)calloc(global.bitmap.width, sizeof(SDL_Color));

            if (pixel_buffer[i] == NULL) {
                ERROR_EXIT("Failed to initialize pixel buffer columns.\n")
            }
        }

        bitmap = SDL_CreateTexture(global.render.renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, global.bitmap.width * bitmap_scale_x, global.bitmap.height * bitmap_scale_y);

        if(bitmap == NULL){
            ERROR_EXIT("Failed to initialize bitmap matrix (Your window size might be too small).\n")
        }

        bitmap_initialized = true;
    }
    else {
        WARN("Repeated usage of initialize_bitmap() is disallowed and undefined, remove any repeated references to this function.")
    }
}

static void draw_pixel_buffer(){
    static u32 prev_bitmap_scale_x, prev_bitmap_scale_y;
    static SDL_PixelFormat* format = NULL; //Format
    void* pixels; //Read-Only Pixels read from the image to update (flattened 2D array).
    u32* current_row; //Current row of pixels we're writing to.
    i32 pitch; //Length of one row in bytes...I have no idea why it's called pitch.

    prev_bitmap_scale_x = bitmap_scale_x;
    prev_bitmap_scale_y = bitmap_scale_y;

    //Need to reset the texture in case the window size changed.
    bitmap_scale_x = global.render.width / global.bitmap.width;
    bitmap_scale_y = global.render.height / global.bitmap.height;

    if(bitmap == NULL || prev_bitmap_scale_x != bitmap_scale_x || prev_bitmap_scale_y != bitmap_scale_y) {
        SDL_DestroyTexture(bitmap);
        bitmap = SDL_CreateTexture(global.render.renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
                                   global.bitmap.width * bitmap_scale_x, global.bitmap.height * bitmap_scale_y);
    }

    if(SDL_LockTexture(bitmap, NULL, &pixels, &pitch) != 0){
        //Just exits and retries to render this the next frame.
        //We do this to just avoid a crash and this only happens if the window size changes rapidly.
        return;
    }

    if(format == NULL){
        format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    }

    //The reason why we need to update all the pixels is that it is not a safe assumption to say that
    //the read in pixels are going to be initialized with the current screen colors, SDL does not guarantee this!

    //u32 rather than SDL_Color is used because the texture interprets the bits as colors correctly.
    //This transform is using a Kronecker's Product between our bitmap matrix and our rescaled matrix that is scale_x and scale_y larger.

    //Multithreaded version, should basically always be used.
    if(global.render_flags & MULTITHREADING_ENABLED){
        process_pixels(pixels, pixel_buffer, format, global.bitmap.width, global.bitmap.height, pitch, bitmap_scale_x, bitmap_scale_y);
    }
    else {
        for (u32 i = 0; i < global.bitmap.height; i++) {
            for (u32 j = 0; j < global.bitmap.width; j++) {
                u32 color = SDL_MapRGBA(format,
                                        pixel_buffer[i][j].r,
                                        pixel_buffer[i][j].g,
                                        pixel_buffer[i][j].b,
                                        pixel_buffer[i][j].a);

                //Rescaling the bitmap pixels to fit a larger resolution
                for (u32 y = 0; y < bitmap_scale_y; y++) {
                    current_row = (u32 *) ((u8 *) pixels + (i * bitmap_scale_y + y) * pitch);
                    for (u32 x = 0; x < bitmap_scale_x; x++) {
                        current_row[j * bitmap_scale_x + x] = color;
                    }
                }

            }
        }
    }

    SDL_UnlockTexture(bitmap);
}

void draw_bitmap(){
    if (bitmap_initialized) {
        draw_pixel_buffer();
        SDL_SetTextureColorMod(bitmap, global.bitmap.tint.r, global.bitmap.tint.g, global.bitmap.tint.b);
        SDL_RenderCopyEx(global.render.renderer, bitmap, &global.bitmap.transform, NULL, global.bitmap.rotation, NULL, 0);
    }
    else {
        ERROR_EXIT("Bitmap not initialized, make sure that you have enabled the bitmap with the Render Flag BITMAP_ENABLED!")
    }
}

void resize_bitmap(u32 width, u32 height){
    if(!bitmap_initialized){
        WARN("Bitmap not initialized! Enable the bitmap with the Render Flag BITMAP_ENABLED!\n")
        return;
    }
    //Most things don't need to be updated, just anything that involved the old height needs to change.
    bitmap_scale_x = floor(global.render.width / width);
    bitmap_scale_y = floor(global.render.height / height);

    /**
     * Need to reallocate the pixel buffer array to the new size. This requires freeing the entire array since
     * if the array is shrunken, then it will cause a memory leak.
     */

    for(i32 i = 0; i < global.bitmap.height; i++){
        CLEAR_FREE(pixel_buffer[i])
    }
    CLEAR_FREE(pixel_buffer)
    global.bitmap.width = width;
    global.bitmap.height = height;

    //Now we reallocate!
    if ((pixel_buffer = (SDL_Color**)calloc(global.bitmap.height, sizeof(SDL_Color*))) == NULL) {
        ERROR_EXIT("Failed to initialize pixel buffer rows.\n")
    }

    for (int i = 0; i < global.bitmap.height; i++) {
        pixel_buffer[i] = (SDL_Color*)calloc(global.bitmap.width, sizeof(SDL_Color));

        if (pixel_buffer[i] == NULL) {
            ERROR_EXIT("Failed to initialize pixel buffer columns.\n")
        }
    }

    if(bitmap != NULL) {
        SDL_DestroyTexture(bitmap);
    }

    bitmap = SDL_CreateTexture(global.render.renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, global.bitmap.width * bitmap_scale_x, global.bitmap.height * bitmap_scale_y);
}

