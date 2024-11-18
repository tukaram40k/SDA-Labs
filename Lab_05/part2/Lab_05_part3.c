#include <stdio.h>
#include <stdlib.h>

void task(FILE *f1, FILE *f2){
    char symbol;
    fprintf(f2, "\n");
    while ((symbol=fgetc(f1))!=EOF){
        fprintf(f2, "%c", symbol);
    }
}

int main(){
    FILE *f1, *f2;
    f1=fopen("output.txt", "r");
    f2=fopen("experiment.txt", "a");
    task(f1, f2);
    fclose(f1);
    fclose(f2);
}