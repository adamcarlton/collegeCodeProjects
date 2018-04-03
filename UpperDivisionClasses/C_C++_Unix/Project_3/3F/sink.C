#include <sink.h>

Sink::Sink(){
  img1 = NULL;
  img2 = NULL;
}
void
Sink::SetInput(Image *image){
    img1 = image;
};
void
Sink::SetInput2(Image *image2){
    img2 = image2;
}

Image*
Sink::GetImage(){
  return img1;
}

Image*
Sink::GetImage2(){
  return img2;
}
