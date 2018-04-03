#ifndef PNMREADCPP_H
#define PNMREADCPP_H
#include <source.h>

class PNMreaderCPP : public Source
{
    private:
        char *_file;
        int width;
        int height;
    public:
        PNMreaderCPP(char *filename);
        ~PNMreaderCPP();
        virtual void Execute();
};

#endif
