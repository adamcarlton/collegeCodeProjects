#include <image.h>
#include <stdlib.h>

Image::Image(void)
{
    Pixel *pixels = NULL;
}

Image::Image(int w, int h)
{
    width = w;
    height = w;
    Pixel *pixels = (Pixel *)malloc(width*height*sizeof(Pixel));
}

Image::Image(Image &img)
{
    width = img.width;
    height = img.height;
    Pixel *pixels = (Pixel *)malloc(width * height * sizeof(Pixel));
    int i;   
    for(i = 0; i < img.height*img.width; i++){
        pixels[i] = img.pixels[i];
    }
}

void
Image::ResetSize(int w, int h)
{
    width = w;
    height = h;
}

