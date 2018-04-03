#ifndef SOURCE_H
#define SOURCE_H
#include <image.h>
#include <logging.h>
class Source
{
    protected:
        Image img;
        virtual void Execute() = 0;
        bool updateCheck;
    public:

        Source(){updateCheck = false; img.SetSrc(this);};
        Image* GetOutput();
        virtual void Update();
        virtual const char *SourceName()=0;
        bool updated(){return updateCheck;};
        void nowItsUpdated(){updateCheck = true;};

};

#endif
