// The author believes it has <3> memory errors

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int i, j, k, n;
    int w = 3;
    int h = 3;
    int d = 3;
    int *buffer = (int *)malloc(w*h*d*sizeof(int));
    int **buffer2 = (int **)malloc(w*h*d*sizeof(int *));

    int count = 0;
    for(i = 0; i < w; i++){
        for(j = 0; i < h; j++){
            for(k = 0; k < d; k++){
                buffer[i*h*d + j*d + k] = count;
                count++;
            }
        }
    }

    for(n = 0; n < w*h*d; n++){
        buffer2[n] = &buffer[n];
    }

    free(buffer);

    for(n = 0; n < w*h*d; n++){
        printf("%d\n", *buffer2[n]);
    }

    free(buffer2);
}
