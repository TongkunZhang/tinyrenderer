#include "tgaimage.h"
#include "geometry.h"
#include <cmath>
#include <vector>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);

void line(int, int, int, int, TGAImage &, TGAColor);
void triangle(Vec2i, Vec2i, Vec2i, TGAImage &, TGAColor);

int main(int argc, char **argv)
{
    TGAImage image(300, 300, TGAImage::RGB);

    // Lesson 0:

    // image.set(52, 41, red);
    // image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    // image.write_tga_file("output.tga");

    // Lesson 1:
    // for (int i = 0; i < 1000000; i++)
    // {
        // line(13, 20, 80, 40, image, white);
        // line(20, 13, 40, 80, image, red);
        // line(80, 40, 13, 20, image, red);
    // }

    // Lesson 2:
    Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}; 
    Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}; 
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)}; 
    triangle(t0[0], t0[1], t0[2], image, red); 
    triangle(t1[0], t1[1], t1[2], image, white); 
    triangle(t2[0], t2[1], t2[2], image, green);

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color){
    // for (float t=0; t<1; t+=0.1) {
    //         int x = x0 + (x1-x0) * t;
    //         int y = y0 + (y1-y0) * t;
    //         image.set(x, y, color);
    // }
    bool steep = false;
    if (std::abs(x1-x0) < std::abs(y1-y0)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        std::swap(x1, x0);
        std::swap(y1, y0);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror = std::abs(dy) * 2;
    int error = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            image.set(y, x, color);
        }
        else {
            image.set(x, y, color);
        }
        error += derror;
        if (error > 2 * dx) {
            y += (y1>y0?1:-1);
            error -= 2 * dx;
        }
    }
}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) {
    // line(t0.u, t0.v, t1.u, t1.v, image, color);
    // line(t2.u, t2.v, t1.u, t1.v, image, color);
    // line(t0.u, t0.v, t2.u, t2.v, image, color);
    if (t0.u > t1.u) std::swap(t0, t1);
    if (t1.u > t2.u) std::swap(t1, t2);
    if (t0.u > t1.u) std::swap(t0, t1);
    
    float dt10y = ((float)(t1.v - t0.v))*(1/((float)(t1.u - t0.u)));
    float dt21y = ((float)(t2.v - t1.v))*(1/((float)(t2.u - t1.u)));
    float dt20y = ((float)(t2.v - t0.v))*(1/((float)(t2.u - t0.u)));

    for (int x = t0.u; x <= t2.u; x++) {
        if (x < t1.u) {
            line(x, t0.v + dt20y*(x-t0.u), x, t0.v + dt10y*(x-t0.u), image, color);
        } else
        {
            line(x, t0.v + dt20y*(x-t0.u), x,  t1.v + dt21y*(x-t1.u), image, color);
        }
    }
}