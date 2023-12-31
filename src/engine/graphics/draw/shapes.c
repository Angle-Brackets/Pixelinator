#include "graphics/shapes.h"
#include "global.h"

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

void draw_square(u32 x0, u32 y0, u32 s) {
    for(i32 y = y0; y < y0 + s; y++){
        for(i32 x = x0; x < x0 + s; x++){
            if(x == x0 || y == y0 || x == x0 + s - 1 || y == y0 + s - 1)
                draw_pixel(&global.bitmap.stroke_fill, x, y);
            else
                draw_pixel(&global.bitmap.shape_fill, x, y);
        }
    }
}

void draw_rect(u32 x0, u32 y0, u32 w, u32 h) {
    for(i32 y = y0; y < y0 + h; y++){
        for(i32 x = x0; x < x0 + w; x++){
            if(x == x0 || y == y0 || x == x0 + w - 1 || y == y0 + h - 1)
                draw_pixel(&global.bitmap.stroke_fill, x, y);
            else
                draw_pixel(&global.bitmap.shape_fill, x, y);
        }
    }
}

void draw_circle(u32 x0, u32 y0, u32 r) {
    //Source: https://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles
    //The polynomial used for bounding the edge (r^2 - 2r - 1) is very strange, and I am unsure why it works so well.
    i32 r2 = r * r;
    i32 area = r2 << 2;
    i32 diameter = r << 1;

    for(i32 i = 0; i < area; i++){
        i32 x = (i % diameter) - r;
        i32 y = (i / diameter) - r;

        if(x * x + y * y < r2){
            if(x * x + y * y > r2 - 2*r - 1)
                draw_pixel(&global.bitmap.stroke_fill, x0 + x, y0 + y);
            else
                draw_pixel(&global.bitmap.shape_fill, x0 + x, y0 + y);
        }
    }
}
