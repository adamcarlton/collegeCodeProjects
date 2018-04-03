#ifndef IMAGE_H
#define IMAGE_H

struct Pixel
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct Image
{
    int width;
    int height;
    Pixel *pixels;
    Image(void);
    Image(int width, int height);
    Image(Image &);
    void ResetSize(int width, int height);
};

#endif
