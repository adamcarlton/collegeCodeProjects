#ifndef SINK_H
#define SINK_H
#include <image.h>
class Sink
{
protected:
        const Image *img1;
        const Image *img2;

    public:
        Sink(void);
        void SetInput(const Image*);
        void SetInput2(const Image*);
        virtual const char *SinkName()=0;
};

#endif
