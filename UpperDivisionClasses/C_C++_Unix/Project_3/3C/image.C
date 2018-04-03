#include <image.h>
#include <stdlib.h>

Image::Image(void)
{
    Pixel *pixels = NULL;
};

Image::Image(int w, int h)
{
    this->width = w;
    this->height = w;
    Pixel *pixels = new Pixel[width*height];
};

Image::Image(Image &img)
{
    width = img.width;
    height = img.height;
    Pixel *pixels = new Pixel[width*height];
    int i;
    for(i = 0; i < img.height*img.width; i++){
        pixels[i] = img.pixels[i];
    }
};

void
Image::ResetSize(int w, int h)
{
    this->width = w;
    this->height = h;
};

void
Image::SetSize(int w, int h){
    this->width = w;
    this->height = h;
};

int
Image::getWidth(){
    return this->width;
};

int
Image::getHeight(){
    return this->height;
};
void
Image::setBuffer(int width, int height){
    this->pixels = new Pixel[width*height];
};

Pixel*
Image::getBuffer(){
    return (this->pixels);
};


Image::~Image(){
    delete pixels;
}
