#include <stdio.h>
#include <PNMwriter.h>
#include <string.h>
void
PNMwriter::Write(char *filename) const{

    FILE *f_out = fopen(filename, "w");
    fprintf(f_out, "P6\n%d %d\n255\n", img1->getWidth(), img1->getHeight());
    fwrite(img1->getBuffer(), sizeof(Pixel), img1->getWidth()*img1->getHeight(), f_out);
    fclose(f_out);
};
