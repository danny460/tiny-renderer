#include <iostream>
#include "model.h"
#include "tgaimage.h"

void test(TGAImage &image);
void wireframe(Model *model, TGAImage &image);
void flatshade(Model *model, TGAImage &image);
void line(Vec2i p0, Vec2i p1, TGAImage &image, const TGAColor &color);
void triangle(Vec2i p0, Vec2i p1, Vec2i p2, TGAImage &image, const TGAColor &color);

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const int width = 800;
const int height = 800;

int main(){
    TGAImage image(width, height, TGAImage::RGB);
    Model model = Model("../obj/african_head/african_head.obj");
    /***/
    // wireframe(&model,image);
    // test(image);
    flatshade(&model,image);
    /***/ 
    image.flip_vertically();
    image.write_tga_file("./output.tga");
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

void flatshade(Model *model, TGAImage &image){
    float lightIntensity = 1.f;
    float diffuseK = .5f;
    Vec3f lightNorm = Vec3f(0, 0, -1.f);
    for (int i=0; i<model->nfaces(); i++) { 
        std::vector<int> face = model->face(i); 
        Vec2i screen_coords[3]; 
        Vec3f world_coords[3];
        for (int j=0; j<3; j++) { 
            Vec3f v = model->vert(face[j]); 
            screen_coords[j] = Vec2i((v.x+1.)*width/2., (v.y+1.)*height/2.); 
            world_coords[j] = v;
        }
        Vec3f v01 = world_coords[1] - world_coords[0];
        Vec3f v02 = world_coords[2] - world_coords[0];
        Vec3f n = v02.cross(v01);
        n.normalize(); 
        float intensity = lightIntensity * diffuseK * n.dot(lightNorm);
        if(intensity > 0){
            triangle(screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255)); 
        }
    }
}

void test(TGAImage &image){
    //test triangles
    Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}; 
    Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}; 
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};
    Vec2i t3[3] = {Vec2i(180, 150), Vec2i(120, 150), Vec2i(170, 80)};
    triangle(t0[0], t0[1], t0[2], image, red); 
    triangle(t1[0], t1[1], t1[2], image, white); 
    triangle(t2[0], t2[1], t2[2], image, green);
    triangle(t3[0], t3[1], t3[2], image, red);
}
//bresenham line drawing algorithm;
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
//use barycentric coordinates
void triangle(Vec2i p0, Vec2i p1, Vec2i p2, TGAImage &image, const TGAColor &color){
    if(p0.y == p1.y && p0.y == p2.y) return;
    if(p0.y > p1.y) std::swap(p0, p1);
    if(p1.y > p2.y) std::swap(p1, p2);
    if(p0.y > p1.y) std::swap(p0, p1);
    int minX = std::min(std::min(p0.x, p1.x), p2.x);
    int maxX = std::max(std::max(p0.x, p1.x), p2.x);
    Vec2i v0 = p0 - p2;
    Vec2i v1 = p1 - p2;
    float dot00 = v0.dot(v0);
    float dot01 = v0.dot(v1);
    float dot11 = v1.dot(v1);
    //using determinant and invert matrix to solve 2 * 3 matrix for u and v
    float det = 1./(dot00 * dot11 - dot01 * dot01);
    for(int x = minX ; x <= maxX; x++){
        for(int y = p0.y; y <= p2.y; y++){
            Vec2i v2 = Vec2i(x, y) - p2;
            float dot20 = v2.dot(v0);
            float dot21 = v2.dot(v1);
            float v = det * (dot11 * dot20 - dot01 * dot21);
            float u = det * (dot00 * dot21 - dot01 * dot20);
            if(u < 0 || v < 0 || u + v > 1) continue;
            image.set(x, y, color);
        }
    }
}

