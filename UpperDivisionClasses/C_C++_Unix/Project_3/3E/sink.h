#ifndef SINK_H
#define SINK_H
#include <image.h>

class Sink
{
protected:
        Image *img1;
        Image *img2;

    public:
        Sink(void);
        Image* GetImage();
        Image* GetImage2();
        void SetInput(Image*);
        void SetInput2(Image*);
};

#endif
