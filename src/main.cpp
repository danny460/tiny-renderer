#include <iostream>
#include "tgaimage.h"
int testIntersection(int x0, int y0, int x1, int y1, int yy);
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor &color);
void triangle(int x0, int y0, int x1, int y1, int x2, int y2, TGAImage &image, TGAColor &color);
void test(TGAImage &image);


TGAColor white = TGAColor(255, 255, 255, 255);
TGAColor red   = TGAColor(255, 0,   0,   255);
TGAColor green = TGAColor(0,   255, 0,   255);

int main(){
    TGAImage image(200, 200, TGAImage::RGB);
    test(image);
    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}
//Line Drawing Algorithm
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor &color){
    bool steep = false;
    if(std::abs(y1-y0) > std::abs(x1-x0)){
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if(x0 > x1){
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    for(int x = x0 ; x <= x1 ; x++){
        int y = y0 + dy * (x-x0)/(float)dx;
        if(steep){
            image.set(y, x, color);
        }else{
            image.set(x, y, color);
        } 
            
    }
}
//Scan Line
void test(TGAImage &image){
    /*triangle test*/
    triangle(10, 70, 50, 160, 70, 80, image, red);
    triangle(180, 50,  150, 1,   70, 180, image, white);
    triangle(180, 150, 120, 160, 130, 180, image, green);
}

void triangle(int x0, int y0, int x1, int y1, int x2, int y2, TGAImage &image, TGAColor &color){
    int top = std::max( std::max(y0, y1), y2);
    int bot = std::min( std::min(y0, y1), y2);
    for(int y = top ; y >= bot; y--){
        int x01, x12, x20;
        x01 = testIntersection(x0, y0, x1, y1, y);
        x12 = testIntersection(x1, y1, x2, y2, y);
        x20 = testIntersection(x2, y2, x0, y0, y);
        if(x01 == -1)
            line(x12, y, x20, y, image, color);
        else if( x12 == -1)    
            line(x01, y, x20, y, image, color);   
        else if( x20 == -1)   
            line(x01, y, x12, y, image, color);
        else if(x01 == x12 || x01 == x20) line(x12, y, x20, y, image, color);
        else if (x12 == x20) line(x01, y, x20, y, image, color);         
    }
    line(x0, y0, x1, y1, image, color);
    line(x1, y1, x2, y2, image, color);
    line(x2, y2, x0, y0, image, color);
}

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