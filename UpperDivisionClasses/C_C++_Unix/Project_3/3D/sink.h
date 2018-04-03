#ifndef SINK_H
#define SINK_H
#include <image.h>

class Sink
{
    private:
        Image *img;
        Image *img2;

    public:
        Image* GetImage();
        Image* GetImage2();
        void SetInput(Image*);
        void SetInput2(Image*);
};

#endif
