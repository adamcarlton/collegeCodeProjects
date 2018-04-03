#include <image.h>
#include <stdlib.h>
#include <source.h>
Image::Image(void)
{
    height = 0;
    width = 0;
    pixels = NULL;
    src = NULL;
};

Image::Image(int w, int h)
{
    this->width = w;
    this->height = h;
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
Image::getWidth() const{
    return this->width;
};

int
Image::getHeight() const{
    return this->height;
};
void
Image::setBuffer(int width, int height){
  if(pixels!=NULL){
    delete [] pixels;
  }
  pixels = NULL;
  this->pixels = new Pixel[width*height];
};

Pixel*
Image::getBuffer() const{
    return (this->pixels);
};
void
Image::SetSrc(Source* src){
    this->src = src;
}

void
Image::Update() const{
  if(src->updated() == false){
    src->nowItsUpdated();
    src->Update();
  }
}

Image::~Image(){
  if(pixels!=NULL){
    delete [] this->pixels;
  }
  pixels = NULL;
}
