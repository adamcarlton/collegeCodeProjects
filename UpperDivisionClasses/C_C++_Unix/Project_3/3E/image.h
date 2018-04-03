#ifndef IMAGE_H
#define IMAGE_H
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
        int getWidth();
        int getHeight();
        Pixel* getBuffer();
        void setBuffer(int width, int height);
        virtual void Update();
        void SetSrc(Source*);
        virtual ~Image();
};

#endif
