#ifndef PNMREAD_H
#define PNMREAD_H
#include <source.h>


class PNMreader : public Source
{
    private:
        char *_file;
        int width;
        int height;
    public:
        PNMreader(const char *filename);
        ~PNMreader();
        virtual void Execute();
        const char *SourceName(){return "PNMreader";};
};

#endif
