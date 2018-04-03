#include <stdio.h>
#include <PNMwriter.h>
#include <string.h>
void
PNMwriter::Write(char *filename){
    
    Image *image = GetImage();
    FILE *f_out = fopen(filename, "w");
    fprintf(f_out, "P6\n%d %d\n255\n", image->getWidth(), image->getHeight());
    fwrite(image->getBuffer(), sizeof(Pixel), image->getWidth()*image->getHeight(), f_out);
    fclose(f_out);
};

