#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.c"

int main(){
    int rows=0;
    int cols=0;
    int S=0;
    printf("Input the dimensions of the matrix: ");
    scanf("%d %d", &rows, &cols);
    printf("Input the number S: ");
    scanf("%d", &S);
    printf("Input the %d by %d matrix:\n", rows, cols);
    int array[rows][cols];
    scan_array(rows, cols, array);
    task(rows, cols, array, S);
    print_array(rows, cols, array);
}