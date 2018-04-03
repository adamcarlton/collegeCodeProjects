#include <filters.h>
#include <stdio.h>
#include <sys/time.h>
void
Filters::Update(){
    if(img1 != NULL){
        char msg[1024];
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        img1->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);
    }
    if(img2 != NULL){
        char msg[1024];
        sprintf(msg, "%s: about to update input2", SourceName());
        Logger::LogEvent(msg);
        img2->Update();
        sprintf(msg, "%s: done updating input2", SourceName());
        Logger::LogEvent(msg);
    }
    char msg[1024];
    struct timeval startTime;
    gettimeofday(&startTime, 0);
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    struct timeval endTime;
    gettimeofday(&endTime, 0);
    double seconds = double(endTime.tv_sec - startTime.tv_sec) + double(endTime.tv_usec - startTime.tv_usec) / 1000000;
    sprintf(msg, "%s: done executing with time: %f", SourceName(), seconds);
    Logger::LogEvent(msg);
}

void
Shrinker::Execute()
{
    Image *output = GetOutput();
    if(img1 == NULL){
        char msg[1024];
        sprintf(msg, "%s: the input image is NULL", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int halfWidth = (int)img1->getWidth() / 2;
    int halfHeight = (int)img1->getHeight() / 2;
    output->SetSize(halfWidth, halfHeight);
    output->setBuffer(halfWidth, halfHeight);
    int i,j;
    for(i = 0; i < halfWidth; i++){
        for(j = 0; j<halfHeight; j++){
            output->getBuffer()[j*halfWidth+i].red = img1->getBuffer()[4*j*halfWidth + 2*i].red;
            output->getBuffer()[j*halfWidth+i].green = img1->getBuffer()[4*j*halfWidth + 2*i].green;
            output->getBuffer()[j*halfWidth+i].blue = img1->getBuffer()[4*j*halfWidth + 2*i].blue;
        }
    }
};

void
LRConcat::Execute(){
    if(img1 == NULL){
        char msg[1024];
        sprintf(msg, "%s: the first image input is null", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(img2 == NULL){
        char msg[1024];
        sprintf(msg, "%s: the second image input is null", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    Image *output = GetOutput();
    int bigWidth = (int)img1->getWidth() + (int)img2->getWidth();
    int leftCheck = img1->getWidth();
    int rightWidth = img2->getWidth();
    int workHeight = img1->getHeight();
    output->SetSize(bigWidth, workHeight);
    output->setBuffer(bigWidth, workHeight);
    if(img1->getHeight() != img2->getHeight()){
            char msg[1024];
            sprintf(msg, "%s: heights must match: %d, %d", SinkName(), img1->getHeight(), img2->getHeight());
            DataFlowException e(SinkName(), msg);
            throw e;
            }
    int i, j;
    for(i = 0; i < bigWidth; i++){
       for(j= 0; j < workHeight; j++){
           if(i < leftCheck){
            output->getBuffer()[j*bigWidth+i].red = img1->getBuffer()[j*leftCheck + i].red;
            output->getBuffer()[j*bigWidth+i].green = img1->getBuffer()[j*leftCheck + i].green;
            output->getBuffer()[j*bigWidth+i].blue = img1->getBuffer()[j*leftCheck + i].blue;
           }
           else{
            output->getBuffer()[j*bigWidth+i].red = img2->getBuffer()[j*rightWidth + (i-leftCheck)].red;
            output->getBuffer()[j*bigWidth+i].green = img2->getBuffer()[j*rightWidth + (i-leftCheck)].green;
            output->getBuffer()[j*bigWidth+i].blue = img2->getBuffer()[j*rightWidth + (i-leftCheck)].blue;
           }
       }
    }
};


void
TBConcat::Execute()
{
    Image *output = GetOutput();
    if(img1 == NULL){
        char msg[1024];
        sprintf(msg, "%s: the first image input is null", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(img2 == NULL){
        char msg[1024];
        sprintf(msg, "%s: the second image input is null", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int bigHeight = (int)img1->getHeight() + (int)img2->getHeight();
    int topCheck = img1->getHeight();
    int workWidth = img1->getWidth();
    output->SetSize(workWidth, bigHeight);
    output->setBuffer(workWidth, bigHeight);
    if(img1->getWidth() != img2->getWidth()){
            char msg[1024];
            sprintf(msg, "%s: widths must match: %d, %d", SinkName(), img1->getWidth(), img2->getWidth());
            DataFlowException e(SinkName(), msg);
            throw e;
            }
    int i,j;
    for(i=0; i < workWidth; i++){
        for(j=0; j < bigHeight; j++){
            if(j<topCheck){
            output->getBuffer()[j*workWidth+i].red = img1->getBuffer()[j*workWidth + i].red;
            output->getBuffer()[j*workWidth+i].green = img1->getBuffer()[j*workWidth + i].green;
            output->getBuffer()[j*workWidth+i].blue = img1->getBuffer()[j*workWidth + i].blue;
            }
            else{
            output->getBuffer()[j*workWidth+i].red = img2->getBuffer()[(j-topCheck)*workWidth + i].red;
            output->getBuffer()[j*workWidth+i].green = img2->getBuffer()[(j-topCheck)*workWidth + i].green;
            output->getBuffer()[j*workWidth+i].blue = img2->getBuffer()[(j-topCheck)*workWidth + i].blue;
            }
        }
    }
};


void
Blender::SetFactor(float factor){
    this->factor = factor;
};

float
Blender::getFactor(){
    return this->factor;
};

void
Blender::Execute()
{
    float fact = 1 - getFactor();
    float factor = getFactor();
    Image *output = GetOutput();
    if(img1 == NULL){
        char msg[1024];
        sprintf(msg, "%s: the first image input is null", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(img2 == NULL){
        char msg[1024];
        sprintf(msg, "%s: the second image input is null", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(factor > 1){
      char msg[1024];
      sprintf(msg, "%s: Invalid factor for Blender: %f", SinkName(), factor);
      DataFlowException e(SinkName(), msg);
      throw e;
    }
    if(factor < 0){
      char msg[1024];
      sprintf(msg, "%s: Invalid factor for Blender: %f", SinkName(), factor);
      DataFlowException e(SinkName(), msg);
      throw e;
    }
    int workWidth = img1->getWidth();
    int workHeight = img2->getHeight();
    output->SetSize(workWidth, workHeight);
    output->setBuffer(workWidth, workHeight);
    if(output == NULL){
        char msg[1024];
        sprintf(msg, "%s: the source can't be null", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    int i,j;
    for(i = 0; i < workWidth; i++){
        for(j=0; j< workHeight; j++){
            int increment = (j*workWidth+i);
            output->getBuffer()[increment].red = img1->getBuffer()[increment].red*factor + img2->getBuffer()[increment].red*fact;
            output->getBuffer()[increment].green = img1->getBuffer()[increment].green*factor + img2->getBuffer()[increment].green*fact;
            output->getBuffer()[increment].blue = img1->getBuffer()[increment].blue*factor + img2->getBuffer()[increment].blue*fact;
        }
    }
};

void
Crop::Execute()
{
    Image *output = GetOutput();
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart >= img1->getWidth() || Istop >= img1->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart >= img1->getHeight() || Jstop >= img1->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }

    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = img1->getWidth();
    output->SetSize(width, height);
    output->setBuffer(width, height);
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            output->getBuffer()[idx].red   = img1->getBuffer()[idx1].red;
            output->getBuffer()[idx].green = img1->getBuffer()[idx1].green;
            output->getBuffer()[idx].blue = img1->getBuffer()[idx1].blue;
        }
};

void
Transpose::Execute(){
    Image *output = GetOutput();
    int outHeight = img1->getWidth();
    int outWidth = img1->getHeight();
    output->SetSize(outWidth, outHeight);
    output->setBuffer(outHeight, outWidth);
    Pixel *outBuff = output->getBuffer();
    const Pixel *inBuff = img1->getBuffer();
    int i,j;
    for(i = 0; i < outHeight; i++){
        for(j = 0; j < outWidth; j++){
            outBuff[i*outWidth+j].red = inBuff[j*outHeight+i].red;
            outBuff[i*outWidth+j].green = inBuff[j*outHeight+i].green;
            outBuff[i*outWidth+j].blue = inBuff[j*outHeight+i].blue;
        }
    }
};
void
Invert::Execute(){
    Image *output = GetOutput();
    int height = img1->getHeight();
    int width = img1->getWidth();
    output->SetSize(width, height);
    output->setBuffer(width, height);
    Pixel *outBuff = output->getBuffer();
    Pixel *inBuff = img1->getBuffer();
    int i,j;
    for(i = 0; i < width; i++){
        for(j = 0; j < height; j++){
            outBuff[j*width+i].red = 255-inBuff[j*width+i].red;
            outBuff[j*width+i].green = 255-inBuff[j*width+i].green;
            outBuff[j*width+i].blue = 255-inBuff[j*width+i].blue;
        }
    }
};

Color::Color(int width, int height, int red, int green, int blue){
  this->_width = width;
  this->_height = height;
  this->_red = red;
  this->_green = green;
  this->_blue = blue;

}

void
Color::Execute(){
  Image *output = GetOutput();
  output->SetSize(_width, _height);
  output->setBuffer(_width, _height);
  Pixel *outBuff = output->getBuffer();
  int total = _width * _height;
  int i;
  for(i=0; i < total; i++){
    outBuff[i].red = _red;
    outBuff[i].green = _green;
    outBuff[i].blue = _blue;
  }
}

void
Checkerboard::Execute(){
  Image *output = GetOutput();
  int width = img1->getWidth();
  int height = img2->getHeight();
  output->SetSize(width, height);
  output->setBuffer(width, height);
  Pixel *outBuff = output->getBuffer();
  Pixel *img1Buff = img1->getBuffer();
  Pixel *img2Buff = img2->getBuffer();
  int i,j;
  for(i = 0; i < width; i++){
    for(j = 0; j < height; j++){
      if((i/10+j/10) % 2 == 0){
        outBuff[j*width+i].red = img1Buff[j*width+i].red;
        outBuff[j*width+i].green = img1Buff[j*width+i].green;
        outBuff[j*width+i].blue = img1Buff[j*width+i].blue;
      }
      else{
        outBuff[j*width+i].red = img2Buff[j*width+i].red;
        outBuff[j*width+i].green = img2Buff[j*width+i].green;
        outBuff[j*width+i].blue = img2Buff[j*width+i].blue;
      }
    }
  }
};

CheckSum::CheckSum(){
  _red = 0;
  _green = 0;
  _blue = 0;
}

void
CheckSum::OutputCheckSum(const char *filename){
  FILE *file = fopen(filename, "w");
  int total = img1->getWidth()*img1->getHeight();
  Pixel* inBuff = img1->getBuffer();
  int i;
  for(i = 0; i < total; i++){
    _red += inBuff[i].red;
    _green += inBuff[i].green;
    _blue += inBuff[i].blue;
  }
  fprintf(file, "CHECKSUM: %d, %d, %d\n", _red, _green, _blue);
  fclose(file);
}
