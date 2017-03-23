#include "tgaimage.h"
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor &color);
void test(TGAImage &image);
void triangle();

TGAColor white = TGAColor(255, 255, 255, 255);
TGAColor red   = TGAColor(255, 0,   0,   255);

int main(){
    TGAImage image(100, 100, TGAImage::RGB);
    // image.set(52, 41, red);
    test(image);
    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}
//Line Drawing Algorithm
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor &color){
    if(x0 > x1){ 
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    bool steep = (std::abs(y1-y0) > x1-x0);
    if(steep){
        std::swap(x0, y0);
        std::swap(x1, y1);
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
    for (int i=0; i<1000000; i++) {
        line(13, 20, 80, 40, image, white);
        line(20, 13, 40, 80, image, red);
        line(80, 40, 13, 20, image, red);
    }
}





void triangle(){
    //todo
}