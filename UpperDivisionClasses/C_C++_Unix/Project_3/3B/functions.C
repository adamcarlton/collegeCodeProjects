#include <functions.h>
#include <image.h>
#include <stdio.h>
#include <stdlib.h>
void
ReadImage(char *filename, Image &output){
    FILE *f_in = fopen(filename, "rb");
    fscanf(f_in, "P6\n%d %d\n255\n", &(output.width), &(output.height));
    output.pixels = (Pixel *)malloc(output.width*output.height*sizeof(Pixel));
    fread(output.pixels, sizeof(Pixel), output.width*output.height, f_in);
    fclose(f_in);
}

void
WriteImage(char *filename, Image &img){
    FILE *f_out = fopen(filename, "w");
    fprintf(f_out, "P6\n%d %d\n255\n", img.width, img.height);
    fwrite(img.pixels, sizeof(Pixel), img.width * img.height, f_out);
    fclose(f_out);
}

void 
HalveInSize(Image &input, Image &output){
    int halfWidth = (int)(input.width) / 2;
    int halfHeight = (int)(input.height) / 2;
    output.width = halfWidth;
    output.height = halfHeight;
    output.pixels = (Pixel *)malloc(output.width * output.height * sizeof(Pixel));
    int i, j;
    for(i = 0; i < halfWidth; i++){
        for(j = 0; j < halfHeight; j++){
            output.pixels[j*halfWidth+i].red = input.pixels[4 * j * halfWidth + 2*i].red;
            output.pixels[j*halfWidth+i].green = input.pixels[4 * j * halfWidth + 2*i].green;
            output.pixels[j*halfWidth+i].blue = input.pixels[4 * j * halfWidth + 2*i].blue;
        }
    }
}

void
LeftRightConcatenate(Image &leftInput, Image &rightinput, Image &output){
    int bigWidth = leftInput.width + rightinput.width;
    int leftCheckWidth = leftInput.width;
    int rightWidth = rightinput.width;
    int workHeight = leftInput.height;
    output.width = bigWidth;
    output.height = workHeight;
    output.pixels = (Pixel *)malloc(output.width * output.height * sizeof(Pixel));
    int i, j;
    for(i = 0; i < bigWidth; i++){
        for(j = 0; j < workHeight; j++){
            if(i < leftCheckWidth){
                output.pixels[j * bigWidth + i].red = leftInput.pixels[j*leftCheckWidth+i].red;
                output.pixels[j * bigWidth + i].green = leftInput.pixels[j*leftCheckWidth+i].green;
                output.pixels[j * bigWidth + i].blue = leftInput.pixels[j*leftCheckWidth+i].blue;
            }
            else{
                output.pixels[j * bigWidth + i].red = rightinput.pixels[j*rightWidth+(i-leftCheckWidth)].red;
                output.pixels[j * bigWidth + i].green = rightinput.pixels[j*rightWidth+(i-leftCheckWidth)].green;
                output.pixels[j * bigWidth + i].blue = rightinput.pixels[j*rightWidth+(i-leftCheckWidth)].blue;
            }
        }
    }
}

void
TopBottomConcatenate(Image &topInput, Image &bottomInput, Image &output){
    int bigHeight = topInput.height + bottomInput.height;
    int topCheck = topInput.height;
    int botCheck = bottomInput.height;
    int workWidth = topInput.width;
    output.height = bigHeight;
    output.width = workWidth;
    output.pixels = (Pixel *)malloc(output.width * output.height * sizeof(Pixel));
    int i,j;
    for(i = 0; i < workWidth; i++){
        for(j = 0; j < bigHeight; j++){
            if(j < topCheck){
                output.pixels[j*workWidth + i].red = topInput.pixels[j*workWidth + i].red;
                output.pixels[j*workWidth + i].green = topInput.pixels[j*workWidth + i].green;
                output.pixels[j*workWidth + i].blue = topInput.pixels[j*workWidth + i].blue;
            }
            else{
                output.pixels[j*workWidth + i].red = bottomInput.pixels[(j-topCheck)*workWidth + i].red;
                output.pixels[j*workWidth + i].green = bottomInput.pixels[(j-topCheck)*workWidth + i].green;
                output.pixels[j*workWidth + i].blue = bottomInput.pixels[(j-topCheck)*workWidth + i].blue;
            }
        }
    }
}

void
Blend(Image &input1, Image &input2, float factor, Image &output){
    float fact = 1-factor;
    int workWidth = input1.width;
    int workHeight = input1.height;
    output.width = workWidth;
    output.height = workHeight;
    output.pixels = (Pixel *)malloc(output.width * output.height * sizeof(Pixel));
    int i,j;
    for(i = 0; i < workWidth; i++){
        for(j = 0; j < workHeight; j++){
            int increment = (j*workWidth + i);
            output.pixels[increment].red = input1.pixels[increment].red*factor + input2.pixels[increment].red*(fact);
            output.pixels[increment].green = input1.pixels[increment].green*factor + input2.pixels[increment].green*(fact);
            output.pixels[increment].blue = input1.pixels[increment].blue*factor + input2.pixels[increment].blue*(fact);
        }
    }
}
