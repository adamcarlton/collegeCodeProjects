#ifndef WRITERCPP_H
#define WRITERCPP_H
#include <sink.h>
class PNMwriterCPP:public Sink
{
    public:
        void Write(char *filename);
};

#endif
