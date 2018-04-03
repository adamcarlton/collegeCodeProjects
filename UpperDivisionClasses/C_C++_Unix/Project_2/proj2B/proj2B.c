#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <printf.h>

int main(int argc, char *argv[]){
    FILE *input, *output;
    int *mem_array;
    int buff_size = 1;
    output = fopen(argv[2], "w");
    int count = 0;
    int i;
    int j;
    if(argc != 3){
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    input = fopen(argv[1], "rb");
    mem_array = malloc(sizeof(int)*25);
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            fseek(input,i*(10*sizeof(int)) + j*sizeof(int), SEEK_SET);
            fread(mem_array+count, sizeof(int), buff_size, input);
            fprintf(output, "%d\n", mem_array[count]); 
            count++;

        }
    }
   
    fclose(input);
    fclose(output);
    free(mem_array);
}

