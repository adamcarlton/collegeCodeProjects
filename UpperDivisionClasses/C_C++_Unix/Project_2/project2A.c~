#include <stdlib.h>
#include <stdio.h>

int main(){
    int *A = malloc(sizeof(int)*21);
    int *B[3] = {A, A+7, A+14};
    int i = 0;
    for(; i < 21; i++){
        int input = 0;
        printf("Enter value %d: ", i);
        scanf("%d", &A[i]);
    }
    printf("B[2][2] - A [15]: %d\n", (B[2][2]-A[15]));
    printf("Dereference Adress B[2][3]-A[15]: %ld\n", &(B[2][3])-&(A[15]));
    printf("B[2]-B[1]: %ld\n", B[2]-B[1]);
    printf("(A+6): %p\n", (A+6));
    printf("B[0]: %p\n", B[0]);
 
}

