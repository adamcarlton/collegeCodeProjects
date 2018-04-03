#include <sink.h>
void
Sink::SetInput(Image *image){
    this->img = image;
};
void
Sink::SetInput2(Image *image2){
    this->img2 = image2;
}

Image*
Sink::GetImage(){
  return img;
}

Image*
Sink::GetImage2(){
  return img2;
}
