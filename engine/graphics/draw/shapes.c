#include "shapes.h"

static void intensify_pixel(i32 x, i32 y, f32 r, SDL_Color* color){
    f32 alpha = (1 - (r * r))*255;
    color->a = alpha;
    draw_pixel(color, x, y);
}

void draw_point(u32 x, u32 y) {
    draw_pixel(&global.bitmap.shape_fill, x, y);
}

void draw_line(u32 x1, u32 y1, u32 x2, u32 y2) {
    //This draws anti-aliased lines using the Gupta-Sproull algorithm.
    //It's based on the Bresenham and Wu algorithms for drawing anti-aliased lines, but just more optimized.
    //Kinda hard to explain, sources used were Wikipedia and this repo:
    //https://en.wikipedia.org/wiki/Line_drawing_algorithm
    //https://github.com/davidmigloz/photo-editor/blob/master/src/main/java/com/davidmiguel/photoeditor/drawing/GuptaSproullsAlgorithm.java
    i32 x = x1;
    i32 y = y1;
    i32 dx = x2 - x1;
    i32 dy = y2 - y1;
    i32 d = 2 * dy - dx;
    f32 D = 0;

    f32 line_length = sqrt(dx * dx + dy * dy);
    f32 sine = dx / line_length;
    f32 cosine = dy / line_length;

    SDL_Color color = {global.bitmap.stroke_fill.r, global.bitmap.stroke_fill.g, global.bitmap.stroke_fill.b, global.bitmap.stroke_fill.a};

    while(x <= x2){
        intensify_pixel(x, y - 1, D + cosine, &color);
        intensify_pixel(x, y, D, &color);
        intensify_pixel(x, y + 1, D - cosine, &color);
        x++;

        if(d <= 0){
            D += sine;
            d = d + 2 * dy;
        }
        else {
            D = D + sine - cosine;
            d = d + 2 * (dy - dx);
            y++;
        }
    }
}

void draw_square(u32 x, u32 y, u32 s) {

}

void draw_rect(u32 x, u32 y, u32 w, u32 h) {

}

void draw_circle(u32 x, u32 y, u32 r) {

}
