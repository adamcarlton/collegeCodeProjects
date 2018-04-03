#include <PNMreaderCPP.h>
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;

PNMreaderCPP::PNMreaderCPP(char *filename)
{
    _file = new char[strlen(filename)+1];
    int i;
    for(i=0; i < strlen(filename) + 1; i++){
        _file[i] = filename[i];
    }
};

void
PNMreaderCPP::Execute()
{
    ifstream f_in;
    f_in.open(_file);
    Image *image = GetOutput();
    char p6[3];
    int width, height, max;
    f_in >>p6;
    f_in >>width >>height;
    f_in >>max;
    f_in.ignore(256, '\n');
    image->SetSize(width, height);
    image->setBuffer(width, height);
    f_in.read((char*)image->getBuffer(), 3*width*height);
    f_in.close();
};

PNMreaderCPP::~PNMreaderCPP(){
    delete _file;
};
