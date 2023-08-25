#ifndef PIXELINATOR_PIXELINATOR_H
#define PIXELINATOR_PIXELINATOR_H

/**
 * UPDATED FOR VERSION 1.2.3
 *
 * Changelog V.1.2.3: Added functions to resize the window and bitmap at runtime.
 * Changelog V1.2.2: Hotfix for global.h not being updated.
 * Changelog V1.2.1: Hotfix for initialize function in core.h!
 * Changelog V1.2: Added controller support. Supports most modern controllers and joysticks.
 *
 * Include this into your project to immediately start using Pixelinator after all dependencies are installed!
 * Manually updated each MAJOR update.
 */

#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

//Types
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float f32;
typedef double f64;


//Time
typedef struct time_state {
    f32 delta; //Time between frames
    f32 now; //Time of the current frame
    f32 last; //Time of the last frame

    f32 frame_last; //Last time the FPS was calculated
    f32 frame_delay; //Maximum amount of time a frame should take
    f32 frame_time; //Amount of time the current frame took

    u32 frame_rate; //Obvious
    u32 frame_count; //Number of frames rendered
} Time_State;

void time_init(u32 frame_rate);
void time_update(void);
void time_update_late(void);

//Audio
typedef struct sound_state {
    bool music_active; //If music is toggled on
    bool loop_music; //Whether the last piece of music played should be looped

    bool sfx_active; //If sfx are active
    bool loop_sfx; //Whether the last sfx played should be looped

    u8 volume; //Volume of audio
} Sound_State;

u8 init_mixer(MIX_InitFlags flags, u8 volume);

/**
 * Frees up all memory associated with mixer.
 * @return 0 for success, 1 for failure.
 */
u8 quit_mixer();

/**
 * Loads music from a file into the music buffer, make sure to delete it when unneeded!
 * @param file file path to music, must be an mp3 right now (probably will change later)
 * @return The index to the location of the music file in the buffer, used in deleting it later.
 */
u32 load_music(const char* file);

/**
 * Loads sfx from a file into the sfx buffer, make sure to delete it when unneeded!
 * @param file file path to sfx, must be an wav right now (probably will change later)
 * @return The index to the location of the sfx file in the buffer, used in deleting it later.
 */
u32 load_sfx(const char* file);

/**
 * Sets the new volume with an absolute number
 * @param percentage A value between 0 - 100.
 */
void set_volume(u8 percentage);

/**
 * Play music stored at the specified index
 * @param index index where the music is stored
 * @return 0 for success, 1 for failure
 */
u8 play_music(u32 index);

/**
 * Play an sfx stored at the specified index
 * @param index index where the sfx is stored
 * @return 0 for success, 1 for failure
 */
u8 play_sfx(u32 index);

/**
 * Pauses all audio playing.
 */
void pause_audio();

/**
 * Resumes all audio playing.
 */
void resume_audio();

/**
 * Frees up the memory for this particular index's music.
 * @param index index of where the music is stored
 */
void free_music(u32 index);

/**
 * Frees up the memory for this particular index's sfx.
 * @param index index of where the sfx is stored
 */
void free_sfx(u32 index);

//Input
#define INVALID_KEY (-1)

typedef enum input_key {
    INPUT_KEY_LEFT,
    INPUT_KEY_RIGHT,
    INPUT_KEY_UP,
    INPUT_KEY_DOWN,
    INPUT_KEY_ESCAPE
} Input_Key;

//State of Key
//Kind of uses a hacky fix - I want to make these powers of 2, but there are issues trying to do this with the current structure
//of how the private function update_key_state works.
typedef enum key_state {
    KS_UNPRESSED,
    KS_PRESSED,
    KS_HELD
} Key_State;

/**
 * Initializes input variables.
 */
void init_input(void);
void input_update(void);
/**
 * Get the state of a current key by name
 * @param key name of the key as a string
 * @return state of the key, use bitwise AND with the KS_State enums to check its state! INVALID_KEY if no match.
 */
Key_State get_key_state_str(const char* key);
/**
 * Get the state of a current key by key id
 * @param key Key id of the key
 * @return state of the key, use bitwise AND with the KS_State enums to check its state! INVALID_KEY if no match.
 */
Key_State get_key_state_id(SDL_KeyCode key);
/**
 * Get the state of a current key by scancode (technically the fastest method)
 * @param scancode scancode of the key
 * @return state of the key, use bitwise AND with the KS_State enums to check its state! INVALID_KEY if no match.
 */
Key_State get_key_state_scancode(SDL_Scancode scancode);

//Config
typedef struct config {
    u8 keybinds[5];
} Config_State;

void config_init(void);
int config_key_bind(Input_Key key, const char* key_name);

//Controller
typedef enum Button_State {
    CON_INVALID = 0x1 << 0, //Invalid Controller / Button State
    CON_UNPRESSED = 0x1 << 1, //Button was never pressed
    CON_RELEASED = 0x1 << 2, //Button was just unpressed
    CON_PRESSED = 0x1 << 3, //Button was just pressed
    CON_HELD = 0x1 << 4 //Button was previously pressed
} button_state;

typedef struct Controller {
    SDL_GameController* controller;

    //Button press state (used for debounce)
    union {
        //23 different flags possible
        u32 state;
        struct {
            u32 invalid : 1;
            u32 a : 1;
            u32 b : 1;
            u32 x : 1;
            u32 y : 1;
            u32 back : 1;
            u32 guide : 1;
            u32 start : 1;
            u32 left_stick : 1;
            u32 right_stick : 1;
            u32 left_shoulder : 1;
            u32 right_shoulder : 1;
            u32 dpad_up : 1;
            u32 dpad_down : 1;
            u32 dpad_left : 1;
            u32 dpad_right : 1;
            u32 misc1 : 1; /* Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button */
            u32 paddle1 : 1; /* Xbox Elite paddle P1 (upper left, facing the back) */
            u32 paddle2 : 1; /* Xbox Elite paddle P3 (upper right, facing the back) SDL LABELED THIS */
            u32 paddle3 : 1; /* Xbox Elite paddle P2 (lower left, facing the back) SDL LABELED THIS */
            u32 paddle4 : 1; /* Xbox Elite paddle P4 (lower right, facing the back) */
            u32 touchpad : 1; /* PS4/PS5 touchpad button */
            u32 max : 1;
            u32 unused : 9;
        };
    };

} controller_t;

typedef struct controller_state {
    controller_t* controllers; //Controllers connected (NULL means not connected)
    u8 connected_controllers; //Number of controllers connected.
    u8 max_controllers;
} Controller_State;

/**
 * Initializes controllers (internal use), finds any that are connected on startup and sets up the initial array of controllers.
 */
void init_controllers(u8 max_controllers);

/**
 * Updates the list of controllers
 */
void update_controller_list(i32 joystick_id, u32 event_type);

/**
 * Detect the action of a button on a particular controller. \n
 * This does not differentiate between a button being PRESSED VS HELD, you must implement your own debounce.
 * @param controller controller to check button action on (NULLs are ignored safely)
 * @param event Button event to listen for
 * @param button Button to listen for
 * @return a boolean indicating whether the button followed the desired event.
 */
button_state get_button_state(controller_t* controller, SDL_GameControllerButton button);

/**
 * Detect the action of a joystick on a particular controller
 * @param controller controller to check button action on (NULLs are ignored safely)
 * @param axis Joystick axis to read (Typically the even numbered axis is X and the odd numbered axis is Y)
 * @param deadzone Joystick deadzone (Ignores inputs below this threshold)
 * @return A value that ranges from -32768 to 32767 representing the magnitude of the stick's direction for that axis.
 */
int get_joystick_state(controller_t* controller, u16 axis, u16 deadzone);

/**
 * Frees up memory associated with controllers
 */
void close_controllers();

//Render

//Stored in an 4 byte unsigned integer.
//Could also be stored in a union, but this is more flexible.
typedef enum render_flags {
    BITMAP_ACTIVE = 0x1, //Flag to set the bitmap to be activated.
    MULTITHREADING_ENABLED = 0x1 << 1, //Flag to enable multithreading
    DISABLE_VSYNC = 0x1 << 2, //Flag to disable vsync
    IGNORE_FOCUS = 0x1 << 3, //Will ignore if the window is focused or not (will still draw if not focused for example)
    UNUSED_4 = 0x1 << 4,
    UNUSED_5 = 0x1 << 5,
    UNUSED_6 = 0x1 << 6,
    UNUSED_7 = 0x1 << 7,
} Render_Flags;

typedef struct render_state {
    SDL_Window* window;
    SDL_Renderer* renderer;
    u32 width;
    u32 height;
} Render_State;

/**
 * Initializes Renderer
 * @param flags Flags to tell the renderer what additional resources it needs to initialize, if none are needed, input 0.
 */
void render_init(u32 width, u32 height, enum render_flags flags);
/**
 * Start render pass
 */
void render_begin(void);
/**
 * Finish render pass
 */
void render_end(void);

/**
 * Change the window size forcefully. Both must be greater than zero, otherwise it will give a warning.
 * @param width New width of window
 * @param height New height of window.
 */
void set_window_size(i32 width, i32 height);

//Core
#define VERIFY_LOW_BOUND(x, min, name) {if(x < min){fprintf(stderr, "Illegal value for %s passed.\n", name); return 1;}} //Validates if an entered value is not lower than a given value. Can't check a max because multiple monitors might screw with it too much.

typedef enum engine_state {
    UNFOCUSED = 0x1 << 0, //If the window is not currently focused, the engine will pause.
    FOCUSED = 0x1 << 1, //If the window is focused, the engine will be running.
} Engine_State;

/**
 * You must call this function before you render anything to initialize the engine. Do not call this more than once unless if you know what you're doing.
 * @param window_width Width in pixels of the window
 * @param window_height Height in pixels of the window
 * @param bitmap_width Width in pixels of the bitmap - unused if the BITMAP_ENABLED Render Flag is omitted.
 * @param bitmap_height Height in pixels of the bitmap - unused if the BITMAP_ENABLED Render Flag is omitted.
 * @param max_fps Max fps cap for the engine to attempt to reach, may be limited by VSYNC of monitor if not disabled with the DISABLE_VSYNC Render Flag.
 * @param volume Starting volume for both music and sfx.
 * @param controllers Number of max controllers allowed in your program.
 * @param render_flags Flags to modify attributes of the rendering pipeline. It is recommended that MULTITHREADING_ENABLED is passed at minimum for a performance gain.
 *                     If you want access to bitmap graphics, pass the BITMAP_ENABLED flag, otherwise they will not work.
 * @param sound_flags Flags to modify attributes of the sound pipeline. By default MP3 (Music) and WAV (SFX) are automatically supported. If that is all that's needed, then pass 0.
 * @param draw_func You must provide an implementation for this function! This function is run every frame and is primarily used to render pixels to the screen.
 *
 * @return 0 for success, 1 if an error occurred.
 */
i32 initialize(u32 window_width, u32 window_height, u32 bitmap_width, u32 bitmap_height, u32 max_fps, u32 volume, u8 controllers, Render_Flags render_flags, MIX_InitFlags sound_flags, void (*draw_func)());

/**
 * Starts the program, must call initialize() before this function.
 */
void start();

/**
 * Closes the program
 */
void exit_program();

//Sprite
typedef struct SPRITE_SHEET {
    const char* sheet_path;
    SDL_Surface* sheet_data;
    SDL_Color* ignored_colors; //Most sprite sheets have non-transparent backgrounds for sprites, these colors are ignored when rendering.
    u32 ignored_colors_len;
} sprite_sheet;

typedef struct Sprite {
    i32 x;
    i32 y;
    u32 width;
    u32 height;
    SDL_Color** sprite_data; //Pixel data - Dimensions are width x height and passed into the bitmap at the x,y position
    sprite_sheet* sheet;
} sprite_t;

/**
 * Creates a bitmap sprite with or without an existing sprite sheet
 * @param x X position of the sprite
 * @param y Y Position of the sprite
 * @param width Width of the sprite
 * @param height Height of the sprite
 * @param sheet Optional sprite sheet for the sprite to reference, pass NULL if unneeded
 * @return A new sprite, NULL on failure
 */
sprite_t* create_sprite(i32 x, i32 y, u32 width, u32 height, sprite_sheet* sheet);

/**
 * Creates a sprite sheet that can be used for multiple sprites to reference
 * @param file_path file path to sprite sheet
 * @param ignored_colors colors to ignore when reading from the sprite sheet (not sensitive to alpha)
 * @param ignored_colors_len length of ignored colors array
 * @return A new sprite sheet, NULL on failure
 */
sprite_sheet* create_sprite_sheet(const char* file_path, SDL_Color* ignored_colors, u32 ignored_colors_len);

/**
 * Creates a bitmap sprite from a source image.
 * @param x X position of the sprite
 * @param y Y Position of the sprite
 * @param path File path to source image to be loaded.
 * @return A new sprite, NULL on failure
 */
sprite_t* create_sprite_from_img(i32 x, i32 y, const char* path);

/**
 * Update the provided sprite by drawing pixels from the sprite sheet.
 * The function finds a rectangular box with the dimensions provided and draws the pixel information into the sprite provided.
 * The information is written to the sprite starting at (sprite_x, sprite_y) and is the same dimensions as the rectangular region read from.
 * @param sprite sprite to update
 * @param sheet_x top left corner of new sprite data in sheet
 * @param sheet_y top left corner of new sprite data in sheet
 * @param sprite_x leftmost x position of where to begin writing new sprite data
 * @param sprite_y topmost y position of where to begin writing new sprite data
 * @param width width of sprite in sheet
 * @param height height of sprite in sheet
 * @return true if successfully updated, false if not.
 */
bool update_sprite_from_spritesheet(sprite_t* sprite, u32 sheet_x, u32 sheet_y, u32 sprite_x, u32 sprite_y, u32 width, u32 height);

/**
 * Frees the associated sprite, DOES NOT FREE THE SPRITE SHEET!
 */
void free_sprite(sprite_t* sprite);

/**
 * Frees the associated sprite sheet
 */
void free_sprite_sheet(sprite_sheet* sheet);

//Bitmap
typedef struct bitmap_state {
    u32 width;
    u32 height;
    u32 rotation;
    SDL_Color tint;
    SDL_Color stroke_fill;
    SDL_Color shape_fill;
    SDL_Rect transform;

    //Debug/Performance Logging Features
    u32 bitmap_calls; //Number of pixels attempted to be drawn to the bitmap in a frame.
    u32 bitmap_updates; //Number of pixels updated by the bitmap per frame.
} Bitmap_State;
/**
 * Sets the clear color (color used after rendering a frame) of the window
 * @param color
 */
void set_background_clear(SDL_Color* color);

/**
 * Sets the outline color for the edge of bitmap shapes drawn
 * @param color
 */
void set_stroke_fill(SDL_Color* color);

/**
 * Sets the inner fill color of bitmap shapes drawn.
 * @param color
 */
void set_shape_fill(SDL_Color* color);

/**
 * Fills the screen with a particular color
 * @param color
 */
void fill_background(SDL_Color* color);

/**
 * Draws a pixel to the screen at the x, y position.\n
 * This uses an additive alpha to combine colors for alpha \< 255.
 * @param color
 * @param x
 * @param y
 */
void draw_pixel(SDL_Color* color, i32 x, i32 y);

/**
 * Draws a sprite to the bitmap.
 * @param sprite
 * @param scale size to rescale it to.
 */
void draw_sprite_to_bitmap(sprite_t* sprite, u32 scale);

/**
 * Draw pixels from a given texture into the bitmap (Pixels out of bounds are automatically cropped).
 * Does not necessarily clear the entire bitmap if the width and height of the texture aren't the same as the Bitmap!
 * @param surface SDL Surface to draw pixels from.
 * @param x x coordinate to draw the surface at.
 * @param y y coordinate to draw the surface at.
 */
void draw_pixels_from_surface(SDL_Surface* surface, i32 x, i32 y);

/**
 * Gets the pixel located in the BITMAP at (x,y) [x and y are not necessarily screen space coordinates, they relate to the bitmap only]
 * @param x X position of pixel
 * @param y Y position of the pixel
 * @return The pixel information at (x,y) in the bitmap. If an invalid position is passed, NULL is returned. Modifying the struct will modify the pixel!
 */
SDL_Color* get_pixel(u32 x, u32 y);

/**
 * Get the entire bitmap pixel buffer. Any modifications done to the buffer ARE reflected in the actual bitmap, so be weary!
 * The buffer is a 2D array of SDL_Color structs where each position corresponds to a pixel.
 * @return Address to the pixel buffer
 */
SDL_Color** get_pixel_buffer();

/**
 * Rotate the bitmap by a given amount of degrees
 * @param degrees 0 - 360 degree rotation on the bitmap after its done rendering (Any values larger are moved into this range)
 */
void rotate_bitmap_deg(u32 degrees);

/**
 * Rotate the bitmap by a given amount of radians
 * @param degrees 0 - 2π degree rotation on the bitmap after its done rendering (Any values larger are moved into this range)
 */
void rotate_bitmap_rad(f64 radians);

/**
 * Will move the position that the bitmap is rendering to the new x and y positions given.
 * @param x New x position to start rendering from (top left hand corner of rectangular region)
 * @param y New y position to start rendering from (top left hand corner of rectangular region)
 */
void bitmap_shift(i32 x, i32 y);

/**
 * Scale the bitmap by a percentage of the window width and height to zoom in or out of the bitmap
 * @param width_scale percentage from 0 - 500% for the width of the window
 * @param height_scale percentage from 0 - 500% for the height of the window
 */
void bitmap_scale(u32 width_scale, u32 height_scale);

/**
 * Sets the tint of the bitmap (multiplies the rgb values against the bitmap texture before rendering)
 * Default is 255,255,255, or white (no tint).
 * @param color
 */
void set_bitmap_tint(SDL_Color* color);

/**
 * DO NOT USE MORE THAN ONCE!
 * Initializes pixel buffer used for drawing bitmap graphics
 * @param width Width of bitmap in pixels
 * @param height Height of bitmap in pixels
 */
void initialize_bitmap(u32 width, u32 height);

/**
 * Draw the bitmap to the screen, the order in which you call this DOES matter. (For example, render the bitmap, then place text so you can see it!)
 */
void draw_bitmap();

/**
 * Resize the bitmap. This clears the bitmap, so be careful!\n
 * This function is <b>expensive</b>! Do not call it often. \n
 * (It is recommended you update the size of the bitmap THEN update the size of the window to avoid blanking out the screen!)
 * @param width New width of bitmap
 * @param height New height of bitmap
 */
void resize_bitmap(u32 width, u32 height);

//Global texture used for drawing bitmap graphics
extern SDL_Texture* bitmap;
extern bool bitmap_initialized;

//Shapes
/**
 * Draw a single point to the bitmap
 * @param x
 * @param y
 */
void draw_point(u32 x, u32 y);
/**
 * Draw a line to the bitmap
 * @param x1 start x position
 * @param y1 start y position
 * @param x2 end x position
 * @param y2 end y position
 */
void draw_line(u32 x1, u32 y1, u32 x2, u32 y2);
/**
 * Draw a square to the bitmap
 * @param x0 top left hand corner of square
 * @param y0 top left hand corner of square
 * @param s size of square
 */
void draw_square(u32 x0, u32 y0, u32 s);
/**
 * Draw a rectangle to the bitmap
 * @param x0 top left hand corner of rectangle
 * @param y0 top left hand corner of rectangle
 * @param w width of the rectangle
 * @param h height of the rectangle
 */
void draw_rect(u32 x0, u32 y0, u32 w, u32 h);
/**
 * Draw a circle to the bitmap
 * @param x0 center x position of the circle
 * @param y0 center y position of the circle
 * @param r radius of the circle
 */
void draw_circle(u32 x0, u32 y0, u32 r);

//Pixel threading
#define THREADS 8
#define VERIFY_HEAP_DATA(pointer) { if(pointer == NULL){fprintf(stderr, "Ran out of memory.\n"); exit(1);} } //Checks if heap memory is not NULL
#define CLEAR_FREE(pointer) { if(pointer == NULL){fprintf(stderr, "Warning: Attempted to free NULL pointer.\n");} else{free(pointer); pointer = NULL;} } //Clears heap allocated memory and sets the given pointer to NULL

struct pixel_args {
    u32** pixel_rows; //Pixel rows to write to
    u32 pixel_row_count; //Number of pixel rows to write to
    u32 pixel_length; //Length of each pixel row

    SDL_Color** new_pixel_data; //Bitmap pixel data to write to pixel rows
    u32 new_pixel_data_rows; //Number of bitmap rows to read from
    u32 new_pixel_data_length; //Length of a bitmap row
    SDL_PixelFormat* format; //Pixel format for colors (maybe unused)
};

/**
 * Will write pixel data to each row stored in the struct passed
 * @param args - pixel_args struct
 * @return NULL
 */
void* update_pixels(void* args);

/**
 * Function to call to begin processing pixels with the given color data.
 * @param pixels - Pixel array to write to
 * @param color_data - Color data to write to pixel array
 * @param format - Pixel format
 * @param bitmap_height - height of the bitmap
 * @param bitmap_width - width of the bitmap
 * @param pitch - size of row in bytes
 * @param scale_x - Bitmap scale factor for x
 * @param scale_y - Bitmap scale factor for y
 */
void process_pixels(void* pixels, SDL_Color** color_data, SDL_PixelFormat* format, u32 bitmap_width, u32 bitmap_height, u32 pitch, u32 scale_x, u32 scale_y);

//IO
typedef struct file {
    char* data;
    size_t len;
    bool is_valid;
} File;

File io_file_read(const char* path);
int io_file_write(void* buffer, size_t size, const char* path);

/**
 * Read in a png and convert it into a bitmap surface that can be read or passed to other functions
 * @param file path to the png
 * @return A bitmap surface of pixels - Remember to free the surface when done with SDL_FreeSurface! NULL on failure.
 */
SDL_Surface* read_png(const char* file);

//Font cache
#ifdef FC_USE_SDL_GPU
#include <SDL_gpu.h>
#endif


#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif


// Let's pretend this exists...
#define TTF_STYLE_OUTLINE	16



// Differences between SDL_Renderer and SDL_gpu
#ifdef FC_USE_SDL_GPU
#define FC_Rect GPU_Rect
#define FC_Target GPU_Target
#define FC_Image GPU_Image
#define FC_Log GPU_LogError
#else
#define FC_Rect SDL_Rect
#define FC_Target SDL_Renderer
#define FC_Image SDL_Texture
#define FC_Log SDL_Log
#endif


// SDL_FontCache types

typedef enum
{
    FC_ALIGN_LEFT,
    FC_ALIGN_CENTER,
    FC_ALIGN_RIGHT
} FC_AlignEnum;

typedef enum
{
    FC_FILTER_NEAREST,
    FC_FILTER_LINEAR
} FC_FilterEnum;

typedef struct FC_Scale
{
    float x;
    float y;

} FC_Scale;

typedef struct FC_Effect
{
    FC_AlignEnum alignment;
    FC_Scale scale;
    SDL_Color color;

} FC_Effect;

// Opaque type
typedef struct FC_Font FC_Font;


typedef struct FC_GlyphData
{
    SDL_Rect rect;
    int cache_level;

} FC_GlyphData;




// Object creation

FC_Rect FC_MakeRect(float x, float y, float w, float h);

FC_Scale FC_MakeScale(float x, float y);

SDL_Color FC_MakeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

FC_Effect FC_MakeEffect(FC_AlignEnum alignment, FC_Scale scale, SDL_Color color);

FC_GlyphData FC_MakeGlyphData(int cache_level, Sint16 x, Sint16 y, Uint16 w, Uint16 h);



// Font object

FC_Font* FC_CreateFont(void);

#ifdef FC_USE_SDL_GPU
Uint8 FC_LoadFont(FC_Font* font, const char* filename_ttf, Uint32 pointSize, SDL_Color color, int style);

Uint8 FC_LoadFontFromTTF(FC_Font* font, TTF_Font* ttf, SDL_Color color);

Uint8 FC_LoadFont_RW(FC_Font* font, SDL_RWops* file_rwops_ttf, Uint8 own_rwops, Uint32 pointSize, SDL_Color color, int style);
#else
Uint8 FC_LoadFont(FC_Font* font, SDL_Renderer* renderer, const char* filename_ttf, Uint32 pointSize, SDL_Color color, int style);

Uint8 FC_LoadFontFromTTF(FC_Font* font, SDL_Renderer* renderer, TTF_Font* ttf, SDL_Color color);

Uint8 FC_LoadFont_RW(FC_Font* font, SDL_Renderer* renderer, SDL_RWops* file_rwops_ttf, Uint8 own_rwops, Uint32 pointSize, SDL_Color color, int style);
#endif

#ifndef FC_USE_SDL_GPU
// note: handle SDL event types SDL_RENDER_TARGETS_RESET(>= SDL 2.0.2) and SDL_RENDER_DEVICE_RESET(>= SDL 2.0.4)
void FC_ResetFontFromRendererReset(FC_Font* font, SDL_Renderer* renderer, Uint32 evType);
#endif

void FC_ClearFont(FC_Font* font);

void FC_FreeFont(FC_Font* font);



// Built-in loading strings

char* FC_GetStringASCII(void);

char* FC_GetStringLatin1(void);

char* FC_GetStringASCII_Latin1(void);


// UTF-8 to SDL_FontCache codepoint conversion

/*!
Returns the Uint32 codepoint (not UTF-32) parsed from the given UTF-8 string.
\param c A pointer to a string of proper UTF-8 character values.
\param advance_pointer If true, the source pointer will be incremented to skip the extra bytes from multibyte codepoints.
*/
Uint32 FC_GetCodepointFromUTF8(const char** c, Uint8 advance_pointer);

/*!
Parses the given codepoint and stores the UTF-8 bytes in 'result'.  The result is NULL terminated.
\param result A memory buffer for the UTF-8 values.  Must be at least 5 bytes long.
\param codepoint The Uint32 codepoint to parse (not UTF-32).
*/
void FC_GetUTF8FromCodepoint(char* result, Uint32 codepoint);


// UTF-8 string operations

/*! Allocates a new string of 'size' bytes that is already NULL-terminated.  The NULL byte counts toward the size limit, as usual.  Returns NULL if size is 0. */
char* U8_alloc(unsigned int size);

/*! Deallocates the given string. */
void U8_free(char* string);

/*! Allocates a copy of the given string. */
char* U8_strdup(const char* string);

/*! Returns the number of UTF-8 characters in the given string. */
int U8_strlen(const char* string);

/*! Returns the number of bytes in the UTF-8 multibyte character pointed at by 'character'. */
int U8_charsize(const char* character);

/*! Copies the source multibyte character into the given buffer without overrunning it.  Returns 0 on failure. */
int U8_charcpy(char* buffer, const char* source, int buffer_size);

/*! Returns a pointer to the next UTF-8 character. */
const char* U8_next(const char* string);

/*! Inserts a UTF-8 string into 'string' at the given position.  Use a position of -1 to append.  Returns 0 when unable to insert the string. */
int U8_strinsert(char* string, int position, const char* source, int max_bytes);

/*! Erases the UTF-8 character at the given position, moving the subsequent characters down. */
void U8_strdel(char* string, int position);


// Internal settings

/*! Sets the string from which to load the initial glyphs.  Use this if you need upfront loading for any reason (such as lack of render-target support). */
void FC_SetLoadingString(FC_Font* font, const char* string);

/*! Returns the size of the internal buffer which is used for unpacking variadic text data.  This buffer is shared by all FC_Fonts. */
unsigned int FC_GetBufferSize(void);

/*! Changes the size of the internal buffer which is used for unpacking variadic text data.  This buffer is shared by all FC_Fonts. */
void FC_SetBufferSize(unsigned int size);

/*! Returns the width of a single horizontal tab in multiples of the width of a space (default: 4) */
unsigned int FC_GetTabWidth(void);

/*! Changes the width of a horizontal tab in multiples of the width of a space (default: 4) */
void FC_SetTabWidth(unsigned int width_in_spaces);

void FC_SetRenderCallback(FC_Rect (*callback)(FC_Image* src, FC_Rect* srcrect, FC_Target* dest, float x, float y, float xscale, float yscale));

FC_Rect FC_DefaultRenderCallback(FC_Image* src, FC_Rect* srcrect, FC_Target* dest, float x, float y, float xscale, float yscale);


// Custom caching

/*! Returns the number of cache levels that are active. */
int FC_GetNumCacheLevels(FC_Font* font);

/*! Returns the cache source texture at the given cache level. */
FC_Image* FC_GetGlyphCacheLevel(FC_Font* font, int cache_level);

// TODO: Specify ownership of the texture (should be shareable)
/*! Sets a cache source texture for rendering.  New cache levels must be sequential. */
Uint8 FC_SetGlyphCacheLevel(FC_Font* font, int cache_level, FC_Image* cache_texture);

/*! Copies the given surface to the given cache level as a texture.  New cache levels must be sequential. */
Uint8 FC_UploadGlyphCache(FC_Font* font, int cache_level, SDL_Surface* data_surface);


/*! Returns the number of codepoints that are stored in the font's glyph data map. */
unsigned int FC_GetNumCodepoints(FC_Font* font);

/*! Copies the stored codepoints into the given array. */
void FC_GetCodepoints(FC_Font* font, Uint32* result);

/*! Stores the glyph data for the given codepoint in 'result'.  Returns 0 if the codepoint was not found in the cache. */
Uint8 FC_GetGlyphData(FC_Font* font, FC_GlyphData* result, Uint32 codepoint);

/*! Sets the glyph data for the given codepoint.  Duplicates are not checked.  Returns a pointer to the stored data. */
FC_GlyphData* FC_SetGlyphData(FC_Font* font, Uint32 codepoint, FC_GlyphData glyph_data);


// Rendering

FC_Rect FC_Draw(FC_Font* font, FC_Target* dest, float x, float y, const char* formatted_text, ...);
FC_Rect FC_DrawAlign(FC_Font* font, FC_Target* dest, float x, float y, FC_AlignEnum align, const char* formatted_text, ...);
FC_Rect FC_DrawScale(FC_Font* font, FC_Target* dest, float x, float y, FC_Scale scale, const char* formatted_text, ...);
FC_Rect FC_DrawColor(FC_Font* font, FC_Target* dest, float x, float y, SDL_Color color, const char* formatted_text, ...);
FC_Rect FC_DrawEffect(FC_Font* font, FC_Target* dest, float x, float y, FC_Effect effect, const char* formatted_text, ...);

FC_Rect FC_DrawBox(FC_Font* font, FC_Target* dest, FC_Rect box, const char* formatted_text, ...);
FC_Rect FC_DrawBoxAlign(FC_Font* font, FC_Target* dest, FC_Rect box, FC_AlignEnum align, const char* formatted_text, ...);
FC_Rect FC_DrawBoxScale(FC_Font* font, FC_Target* dest, FC_Rect box, FC_Scale scale, const char* formatted_text, ...);
FC_Rect FC_DrawBoxColor(FC_Font* font, FC_Target* dest, FC_Rect box, SDL_Color color, const char* formatted_text, ...);
FC_Rect FC_DrawBoxEffect(FC_Font* font, FC_Target* dest, FC_Rect box, FC_Effect effect, const char* formatted_text, ...);

FC_Rect FC_DrawColumn(FC_Font* font, FC_Target* dest, float x, float y, Uint16 width, const char* formatted_text, ...);
FC_Rect FC_DrawColumnAlign(FC_Font* font, FC_Target* dest, float x, float y, Uint16 width, FC_AlignEnum align, const char* formatted_text, ...);
FC_Rect FC_DrawColumnScale(FC_Font* font, FC_Target* dest, float x, float y, Uint16 width, FC_Scale scale, const char* formatted_text, ...);
FC_Rect FC_DrawColumnColor(FC_Font* font, FC_Target* dest, float x, float y, Uint16 width, SDL_Color color, const char* formatted_text, ...);
FC_Rect FC_DrawColumnEffect(FC_Font* font, FC_Target* dest, float x, float y, Uint16 width, FC_Effect effect, const char* formatted_text, ...);


// Getters

FC_FilterEnum FC_GetFilterMode(FC_Font* font);
Uint16 FC_GetLineHeight(FC_Font* font);
Uint16 FC_GetHeight(FC_Font* font, const char* formatted_text, ...);
Uint16 FC_GetWidth(FC_Font* font, const char* formatted_text, ...);

// Returns a 1-pixel wide box in front of the character in the given position (index)
FC_Rect FC_GetCharacterOffset(FC_Font* font, Uint16 position_index, int column_width, const char* formatted_text, ...);
Uint16 FC_GetColumnHeight(FC_Font* font, Uint16 width, const char* formatted_text, ...);

int FC_GetAscent(FC_Font* font, const char* formatted_text, ...);
int FC_GetDescent(FC_Font* font, const char* formatted_text, ...);
int FC_GetBaseline(FC_Font* font);
int FC_GetSpacing(FC_Font* font);
int FC_GetLineSpacing(FC_Font* font);
Uint16 FC_GetMaxWidth(FC_Font* font);
SDL_Color FC_GetDefaultColor(FC_Font* font);

FC_Rect FC_GetBounds(FC_Font* font, float x, float y, FC_AlignEnum align, FC_Scale scale, const char* formatted_text, ...);

Uint8 FC_InRect(float x, float y, FC_Rect input_rect);
// Given an offset (x,y) from the text draw position (the upper-left corner), returns the character position (UTF-8 index)
Uint16 FC_GetPositionFromOffset(FC_Font* font, float x, float y, int column_width, FC_AlignEnum align, const char* formatted_text, ...);

// Returns the number of characters in the new wrapped text written into `result`.
int FC_GetWrappedText(FC_Font* font, char* result, int max_result_size, Uint16 width, const char* formatted_text, ...);

// Setters

void FC_SetFilterMode(FC_Font* font, FC_FilterEnum filter);
void FC_SetSpacing(FC_Font* font, int LetterSpacing);
void FC_SetLineSpacing(FC_Font* font, int LineSpacing);
void FC_SetDefaultColor(FC_Font* font, SDL_Color color);


#ifdef __cplusplus
}
#endif

//Text
typedef FC_Font PIX_Font;
typedef enum PIX_ALIGN {
    LEFT = FC_ALIGN_LEFT,
    CENTER = FC_ALIGN_CENTER,
    RIGHT = FC_ALIGN_RIGHT
} PIX_Align;

/**
 * Create a font structure to be used to render strings.
 * @param font_path path to ttf font file
 * @param font_size size of text to render
 * @param color font color
 * @return A heap allocated Font object that can be used to render text to the screen. NULL on failure.
 */
PIX_Font* load_pix_font(const char* font_path, u32 font_size, SDL_Color color);

//Basically just aliased a function to not confuse people.
/**
 * @param font PIX_FONT font to render as (NULL defaults to default font if one is set)
 * @param x f32 x position
 * @param y f32 y position
 * @param align Pix-Align parameter for how to align the text (left, center, right)
 * @param formatted_text Format string for text
 * @return SDL_Rect the text was rendered to if desired.
 */
#define render_text(font, x, y, align, fstring, ...) { \
    if(font == NULL && get_default_font() == NULL){WARN("NULL passed without default font being specified.\n")}                                                        \
    else if(font == NULL){FC_DrawAlign(get_default_font(), global.render.renderer, x, y, (FC_AlignEnum)align, fstring, ##__VA_ARGS__);}                                                    \
    else{FC_DrawAlign(font, global.render.renderer, x, y, (FC_AlignEnum)align, fstring, ##__VA_ARGS__);}                                                    \
}

/**
 * Sets the default font for the program, if NULL is passed into render_text, this font will then be used.
 * @param font Font to be set as the default
 * @return true for success, false for failure.
 */
bool set_default_font(PIX_Font* font);

/**
 * Returns the default font (mostly for internal use)
 * @return The currently set default font
 */
PIX_Font* get_default_font();

/**
 * Frees memory associated with a font
 * @param font font to free
 */
void free_pix_font(PIX_Font* font);

//Util
#define ERROR_EXIT(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define ERROR_RETURN(R, ...) { fprintf(stderr, __VA_ARGS__); return R; }
#define WARN(...){ fprintf(stderr, __VA_ARGS__); }
#define VERIFY_HEAP_DATA(pointer) { if(pointer == NULL){fprintf(stderr, "Ran out of memory.\n"); exit(1);} } //Checks if heap memory is not NULL

//Global
typedef struct global {
    //State variables - Contain information about the program
    Engine_State engine;
    Render_State render;
    Config_State config;
    Bitmap_State bitmap;
    Time_State time;
    Sound_State sound;
    Controller_State controller;

    //Flags
    Render_Flags render_flags;
} Global;

extern Global global;

#endif //PIXELINATOR_PIXELINATOR_H
