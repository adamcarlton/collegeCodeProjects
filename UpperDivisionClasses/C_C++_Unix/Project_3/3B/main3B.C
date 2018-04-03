#include "image.h"
#include "functions.h"

int main(int argc, char *argv[])
{
    Image img, img2, img3, img4, img5, img6, img7, img8;

    ReadImage(argv[1], img);
    HalveInSize(img, img2);
    LeftRightConcatenate(img2, img2, img3);
    TopBottomConcatenate(img3, img3, img4);
    HalveInSize(img4, img5);
    LeftRightConcatenate(img5, img2, img6);
    TopBottomConcatenate(img6, img3, img7);
    Blend(img7, img, 0.8, img8);
    WriteImage(argv[2], img8);
    return 0;
}
