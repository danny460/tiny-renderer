#include <iostream>
#include "model.h"
#include "tgaimage.h"

void test(TGAImage &image);
void wireframe(Model *model, TGAImage &image);
void line(Vec2i p0, Vec2i p1, TGAImage &image, const TGAColor &color);
void triangle(Vec2i p0, Vec2i p1, Vec2i p2, TGAImage &image, const TGAColor &color);
int testIntersection(int x0, int y0, int x1, int y1, int yy);

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const int width = 800;
const int height = 800;

int main(){
    TGAImage image(width, height, TGAImage::RGB);
    Model model = Model("../obj/african_head/african_head.obj");
    wireframe(&model,image);
    image.flip_vertically();
    image.write_tga_file("../out/output.tga");
    return 0;
}

void wireframe(Model *model, TGAImage &image){
    for (int i=0; i<model->nfaces(); i++) { 
        std::vector<int> face = model->face(i); 
        for (int j=0; j<3; j++) { 
            Vec3f v0 = model->vert(face[j]); 
            Vec3f v1 = model->vert(face[(j+1)%3]); 
            v0.x = (v0.x+1.)*width/2.; 
            v0.y = (v0.y+1.)*height/2.; 
            v1.x = (v1.x+1.)*width/2.; 
            v1.y = (v1.y+1.)*height/2.;
            Vec2i vi0 = Vec2i(v0.x , v0.y);
            Vec2i vi1 = Vec2i(v1.x, v1.y);

            line(vi0, vi1, image, white); 
        } 
    }
}

void test(TGAImage &image){
    /*triangle test*/
    // triangle(10, 70, 50, 160, 70, 80, image, red);
    // triangle(180, 50,  150, 1,   70, 180, image, white);
    // triangle(180, 150, 120, 160, 130, 180, image, green);
}

void line(Vec2i p0, Vec2i p1, TGAImage &image, const TGAColor &color){
    bool steep = std::abs(p1.y - p0.y) > std::abs(p1.x - p0.x);
    if(steep){
        std::swap(p0.x, p0.y);
        std::swap(p1.x, p1.y);
    }
    if(p0.x > p1.x){
        std::swap(p0.x, p1.x);
        std::swap(p0.y, p1.y);
    }
    int y = p0.y;
    float derror = (p1.y - y)/(float)(p1.x-p0.x);
    for(int x = p0.x ; x <= p1.x ; x++){
        if(steep){
            image.set((int) (y + (x - p0.x) * derror), x, color);
        }else{
            image.set(x, (int) (y + (x - p0.x) * derror), color);
        }
    }
}

// void triangle(Vec2i p0, Vec2i p1, Vec2 p2, TGAImage &image, const TGAColor &color){
//     int top = std::max( std::max(y0, y1), y2);
//     int bot = std::min( std::min(y0, y1), y2);
//     for(int y = top ; y >= bot; y--){
//         int x01, x12, x20;
//         x01 = testIntersection(x0, y0, x1, y1, y);
//         x12 = testIntersection(x1, y1, x2, y2, y);
//         x20 = testIntersection(x2, y2, x0, y0, y);
//         if(x01 == -1)
//             line(x12, y, x20, y, image, color);
//         else if( x12 == -1)    
//             line(x01, y, x20, y, image, color);   
//         else if( x20 == -1)   
//             line(x01, y, x12, y, image, color);
//         else if(x01 == x12 || x01 == x20) line(x12, y, x20, y, image, color);
//         else if (x12 == x20) line(x01, y, x20, y, image, color);         
//     }
//     line(x0, y0, x1, y1, image, color);
//     line(x1, y1, x2, y2, image, color);
//     line(x2, y2, x0, y0, image, color);
// }

int testIntersection(int x0, int y0, int x1, int y1, int yy){
    int top = std::max(y0, y1);
    int bot = std::min(y0, y1);
    if( yy > top || yy < bot){
        return -1;
    }else{
        float t = (x1 - x0)/(float)(y1 - y0);
        int xx = x0 + t * (yy - y0);
        return xx;
    }

}