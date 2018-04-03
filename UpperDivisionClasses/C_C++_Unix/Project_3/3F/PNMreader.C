#include <PNMreader.h>
#include <string.h>
#include <stdio.h>
PNMreader::PNMreader(char *filename){
    _file = new char[strlen(filename)+1];
    int i;
    for(i = 0; i < strlen(filename) + 1; i++){
      _file[i] = filename[i];
    }
    width = 0;
    height = 0;
};

void
PNMreader::Execute(){
    FILE *f_in = fopen(_file, "rb");
    Image* image = GetOutput();
    fscanf(f_in, "P6\n%d %d\n255\n", &width, &height);
    image->SetSize(width, height);
    image->setBuffer(width, height);
    fread(image->getBuffer(), sizeof(Pixel), image->getWidth()*image->getHeight(), f_in);
    fclose(f_in);
}

PNMreader::~PNMreader(){
    delete[] _file;
}
