#include <iostream>
#include "model.h"
#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 0);
const TGAColor red   = TGAColor(255, 0,   0,   0);
const TGAColor green = TGAColor(0,   255, 0,   0);
const int width = 1024;
const int height = 1024;

Model *model = NULL;
const char* DIFFUSE = "diffuse";

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

Vec3f world2screen(Vec3f p){
    int x = .5f + (p.x + 1.f)*width/2;
    int y = .5f + (p.y + 1.f)*height/2;
    return Vec3f(x , y, p.z);
}

// A,B,C from triangle, P is the point to test
Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P){
    Vec3f AC = C - A;
    Vec3f AB = B - A;
    Vec3f PA = A - P;
    Vec3f v[2];
    for(int i = 0 ; i < 2 ; i++){
        v[i] = Vec3f(PA[i], AB[i], AC[i]);
    }
    Vec3f u = v[0].cross(v[1]);
    if(std::abs(u.x) < 1.f) return Vec3f(-1, 0, 0);
    return Vec3f((u.x - u.y - u.z) / u.x, u.y / u.x, u.z / u.x);     
}


//use barycentric coordinates
// void triangle(Vec3f *pts, TGAImage &image, float* zbuffer, const TGAColor &color){
void triangle(Vec3f *pts, Vec2f *texture_coords, float* zbuffer, TGAImage &image, float intensity){
    if(pts[0].y == pts[1].y && pts[0].y == pts[2].y) return;
    int minY = std::min(std::min(pts[0].y, pts[1].y), pts[2].y);
    int maxY = std::max(std::max(pts[0].y, pts[1].y), pts[2].y);
    int minX = std::min(std::min(pts[0].x, pts[1].x), pts[2].x);
    int maxX = std::max(std::max(pts[0].x, pts[1].x), pts[2].x);
    maxX = std::min(maxX, image.get_width() - 1);
    maxY = std::min(maxY, image.get_height() - 1);
    Vec3f P(0.f,0.f,0.f);
    Vec2i P_texture(0,0);
    int diffusemap_height = model->get_texture_height(DIFFUSE);
    int diffusemap_width = model->get_texture_width(DIFFUSE);     
    //using determinant and invert matrix to solve 2 * 3 matrix for u and v
    for(P.x = minX ; P.x <= maxX; P.x++){
        for(P.y = minY; P.y <= maxY; P.y++){
            Vec3f bc = barycentric(pts[0], pts[1], pts[2], P);
            if(bc.x < 0 || bc.y < 0 || bc.z < 0) continue;
            int idx = P.x + P.y * image.get_width();
            //tofix: deal with negative zero value in barycentric vector
            P.z = pts[0].z * bc.x + pts[1].z * bc.y + pts[2].z * bc.z;
            P_texture.x = (texture_coords[0].x * bc.x + texture_coords[1].x * bc.y+ texture_coords[2].x * bc.z ) * diffusemap_width + .5f;
            P_texture.y = (texture_coords[0].y * bc.x + texture_coords[1].y * bc.y+ texture_coords[2].y * bc.z ) * diffusemap_height + .5f;
            TGAColor color = model->get_diffuse(P_texture.x, P_texture.y);
            if(P.z > zbuffer[idx]){
                zbuffer[idx] = P.z;
                image.set(P.x, P.y, color*intensity);
            }
        }
    }
}

int main(){
    const char* diffusemap_filename = "../model/african_head/african_head_diffuse.tga";
    const char* model_filename = "../model/african_head/african_head.obj";
    TGAImage image(width, height, TGAImage::RGB);
    TGAImage diffuse_texture;

    model = new Model(model_filename);
    if(!model->load_texture(diffusemap_filename, DIFFUSE)) return 0;
    /***/
    float *zbuffer = new float[width * height];
    for (int i=width*height; i--; zbuffer[i] = -std::numeric_limits<float>::max());
    float lightIntensity = 1.f;
    float diffuseK = .9f;
    Vec3f lightNorm = Vec3f(0, 0, -1.f);
    for (int i=0; i<model->nfaces(); i++) { 
        std::vector<Vec3i> face = model->face(i);
        Vec3f screen_coords[3]; 
        Vec2f texture_coords[3]; 
        Vec3f world_coords[3];
        for (int j=0; j<3; j++) { 
            Vec3f v = model->vert(face[j][0]);
            Vec2f vt = model->tcoord(face[j][1]);
            world_coords[j] = v;
            screen_coords[j] = world2screen(v); 
            texture_coords[j] = vt;
        }
        Vec3f v01 = world_coords[1] - world_coords[0];
        Vec3f v02 = world_coords[2] - world_coords[0];
        Vec3f n = v02.cross(v01);
        n.normalize(); 
        float intensity = lightIntensity * diffuseK * n.dot(lightNorm);
        if(intensity > 0){
            triangle(screen_coords, texture_coords, zbuffer, image, intensity);
        }
    }
    
    image.flip_vertically();
    image.write_tga_file("./output.tga");
    return 0;
}

