#ifndef SOURCE_H
#define SOURCE_H
#include <image.h>

class Source
{
    protected:
        Image img;
        virtual void Execute() = 0;
    public:
        Source(){img.SetSrc(this);};
        Image* GetOutput();
        virtual void Update();
};

#endif
