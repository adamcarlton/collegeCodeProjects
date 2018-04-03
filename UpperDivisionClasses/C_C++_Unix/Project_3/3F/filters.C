#include <filters.h>
#include <stdio.h>
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
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);

    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}

void
Shrinker::Execute()
{
    Image *input = GetImage();
    Image *output = GetOutput();
    if(input == NULL){
        char msg[1024];
        sprintf(msg, "%s: the input image is NULL", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int halfWidth = (int)input->getWidth() / 2;
    int halfHeight = (int)input->getHeight() / 2;
    output->SetSize(halfWidth, halfHeight);
    output->setBuffer(halfWidth, halfHeight);
    int i,j;
    for(i = 0; i < halfWidth; i++){
        for(j = 0; j<halfHeight; j++){
            output->getBuffer()[j*halfWidth+i].red = input->getBuffer()[4*j*halfWidth + 2*i].red;
            output->getBuffer()[j*halfWidth+i].green = input->getBuffer()[4*j*halfWidth + 2*i].green;
            output->getBuffer()[j*halfWidth+i].blue = input->getBuffer()[4*j*halfWidth + 2*i].blue;
        }
    }
};

void
LRConcat::Execute(){
    Image *leftInput = GetImage();
    Image *rightInput = GetImage2();
    if(leftInput == NULL){
        char msg[1024];
        sprintf(msg, "%s: the first image input is null", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(rightInput == NULL){
        char msg[1024];
        sprintf(msg, "%s: the second image input is null", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    Image *output = GetOutput();
    int bigWidth = (int)leftInput->getWidth() + (int)rightInput->getWidth();
    int leftCheck = leftInput->getWidth();
    int rightWidth = rightInput->getWidth();
    int workHeight = leftInput->getHeight();
    output->SetSize(bigWidth, workHeight);
    output->setBuffer(bigWidth, workHeight);
    if(leftInput->getHeight() != rightInput->getHeight()){
            char msg[1024];
            sprintf(msg, "%s: heights must match: %d, %d", SinkName(), leftInput->getHeight(), rightInput->getHeight());
            DataFlowException e(SinkName(), msg);
            throw e;
            }
    int i, j;
    for(i = 0; i < bigWidth; i++){
       for(j= 0; j < workHeight; j++){
           if(i < leftCheck){
            output->getBuffer()[j*bigWidth+i].red = leftInput->getBuffer()[j*leftCheck + i].red;
            output->getBuffer()[j*bigWidth+i].green = leftInput->getBuffer()[j*leftCheck + i].green;
            output->getBuffer()[j*bigWidth+i].blue = leftInput->getBuffer()[j*leftCheck + i].blue;
           }
           else{
            output->getBuffer()[j*bigWidth+i].red = rightInput->getBuffer()[j*rightWidth + (i-leftCheck)].red;
            output->getBuffer()[j*bigWidth+i].green = rightInput->getBuffer()[j*rightWidth + (i-leftCheck)].green;
            output->getBuffer()[j*bigWidth+i].blue = rightInput->getBuffer()[j*rightWidth + (i-leftCheck)].blue;
           }
       }
    }
};


void
TBConcat::Execute()
{
    Image *topInput = GetImage();
    Image *botInput = GetImage2();
    Image *output = GetOutput();
    if(topInput == NULL){
        char msg[1024];
        sprintf(msg, "%s: the first image input is null", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(botInput == NULL){
        char msg[1024];
        sprintf(msg, "%s: the second image input is null", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int bigHeight = (int)topInput->getHeight() + (int)botInput->getHeight();
    int topCheck = topInput->getHeight();
    int workWidth = topInput->getWidth();
    output->SetSize(workWidth, bigHeight);
    output->setBuffer(workWidth, bigHeight);
    if(topInput->getWidth() != botInput->getWidth()){
            char msg[1024];
            sprintf(msg, "%s: widths must match: %d, %d", SinkName(), topInput->getWidth(), botInput->getWidth());
            DataFlowException e(SinkName(), msg);
            throw e;
            }
    int i,j;
    for(i=0; i < workWidth; i++){
        for(j=0; j < bigHeight; j++){
            if(j<topCheck){
            output->getBuffer()[j*workWidth+i].red = topInput->getBuffer()[j*workWidth + i].red;
            output->getBuffer()[j*workWidth+i].green = topInput->getBuffer()[j*workWidth + i].green;
            output->getBuffer()[j*workWidth+i].blue = topInput->getBuffer()[j*workWidth + i].blue;
            }
            else{
            output->getBuffer()[j*workWidth+i].red = botInput->getBuffer()[(j-topCheck)*workWidth + i].red;
            output->getBuffer()[j*workWidth+i].green = botInput->getBuffer()[(j-topCheck)*workWidth + i].green;
            output->getBuffer()[j*workWidth+i].blue = botInput->getBuffer()[(j-topCheck)*workWidth + i].blue;
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
    Image *input1 = GetImage();
    Image *input2 = GetImage2();
    Image *output = GetOutput();
    if(input1 == NULL){
        char msg[1024];
        sprintf(msg, "%s: the first image input is null", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(input2 == NULL){
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
    int workWidth = input1->getWidth();
    int workHeight = input2->getHeight();
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
            output->getBuffer()[increment].red = input1->getBuffer()[increment].red*factor + input2->getBuffer()[increment].red*fact;
            output->getBuffer()[increment].green = input1->getBuffer()[increment].green*factor + input2->getBuffer()[increment].green*fact;
            output->getBuffer()[increment].blue = input1->getBuffer()[increment].blue*factor + input2->getBuffer()[increment].blue*fact;
        }
    }
};
