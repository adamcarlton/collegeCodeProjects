#include <sink.h>

Sink::Sink(){
  img1 = NULL;
  img2 = NULL;
}
void
Sink::SetInput(const Image *image){
    img1 = image;
};
void
Sink::SetInput2(const Image *image2){
    img2 = image2;
};
