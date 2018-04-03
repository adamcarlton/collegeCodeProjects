#ifndef IMAGE_H
#define IMAGE_H
#include <stdlib.h>
struct Pixel
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};
class Source;

class Image
{
    private:
        int width;
        int height;
        Pixel *pixels;
        Source* src;
    public:
        Image(void);
        Image(int width, int height);
        Image(Image &);
        void ResetSize(int width, int height);
        void SetSize(int width, int height);
        int getWidth() const;
        int getHeight() const;
        Pixel* getBuffer() const;
        void setBuffer(int width, int height);
        virtual void Update() const;
        void SetSrc(Source*);
        ~Image();
};

#endif
