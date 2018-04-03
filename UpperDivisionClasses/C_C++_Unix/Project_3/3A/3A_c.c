#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

typedef struct
{
    int height;
    int width;
    Pixel *pixels;
} Image;


Image *
ReadImage(char *filename)
{
    Image *img = malloc(sizeof(Image));
    FILE *f_in = fopen(filename, "rb");
    fscanf(f_in, "P6\n%d %d\n255\n", &(img->width), &(img->height));
    img->pixels = malloc(img->width * img->height * sizeof(Pixel));
    fread(img->pixels, sizeof(Pixel), img->width * img->height, f_in);
    fclose(f_in);
    return img;
}


void WriteImage(Image *img, char *filename)
{
    FILE *picture = fopen(filename, "w");
    fprintf(picture, "P6\n%d %d\n255\n", img->width, img->height);
    fwrite(img->pixels, sizeof(Pixel), img->width * img->height, picture);
    fclose(picture);

}

Image *
YellowDiagonal(Image *input)
{
    Image *newimg = malloc(sizeof(Image));
    newimg->width = input->width;
    newimg->height = input->height;
    newimg->pixels = malloc(newimg->height * newimg->width * sizeof(Pixel));
    int x;
    for(x = 0; x < newimg->height * newimg->width; x++){
        newimg->pixels[x] = input->pixels[x];
    }
    int i,j;
    for(i = 0; i < newimg->width; i++){
        for(j = 0; j < newimg->height; j++){
            if(i==j){
                newimg->pixels[j*newimg->width+i].red = 255;
                newimg->pixels[j*newimg->width+i].green = 255;
                newimg->pixels[j*newimg->width+i].blue = 0;
            }
        }
    }
    return newimg;
}

int main(int argc, char *argv[])
{
    Image *img = ReadImage(argv[1]);
    Image *yellowImg = YellowDiagonal(img);
    WriteImage(yellowImg, argv[2]);

    free(img->pixels);
    free(img);
    free(yellowImg->pixels);
    free(yellowImg);
    return 0;
}
