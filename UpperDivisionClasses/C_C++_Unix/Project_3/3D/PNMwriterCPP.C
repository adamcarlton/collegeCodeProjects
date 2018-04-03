#include <PNMwriterCPP.h>
#include <fstream>
#include <iostream>
using namespace std;

void
PNMwriterCPP::Write(char *filename)
{
    ofstream output;
    output.open(filename);
    Image *image = GetImage();
    char P6[3] = "P6";
    int max = 255;
    int width = image->getWidth();
    int height = image->getHeight();
    output << P6 << endl;
    output << width << " " << height << endl;
    output << max << endl;
    output.write((char*)image->getBuffer(), 3*width*height);
    output.close();
};
