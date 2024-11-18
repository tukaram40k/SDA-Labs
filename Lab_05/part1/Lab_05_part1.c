#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void read_str(char* str, int size){
    printf("Input a string: ");
    fgets(str, size, stdin);
}

void print_str(FILE *f){
    char *str=(char*)malloc(1000*sizeof(char));
    read_str(str, 1000);
    fprintf(f, "%s", str);
    free(str);
}

void task(FILE *input, FILE *output){
    int first_sentence=0;
    int num_of_sentences=0;
    bool found=false;
    char symbol;
    
    while ((symbol=fgetc(input))!=EOF){
        if (!found){
            if (symbol=='.'){
                found=true;
            }
            first_sentence++;
        }
        if (symbol=='.'){
            num_of_sentences++;
        }
    }
    // decrement the length of the 1st sentence to not include the '.'
    first_sentence--;

    printf("There are %d declarative sentences in the input file.\n", num_of_sentences);
    printf("Length of the 1st declarative sentence is %d.", first_sentence);
    fprintf(output, "There are %d declarative sentences in the input file.\n", num_of_sentences);
    fprintf(output, "Length of the 1st declarative sentence is %d.", first_sentence);
}

int main(){
    FILE *f1, *f2;
    f1=fopen("input.txt", "w");
    print_str(f1);
    fclose(f1);

    f1=fopen("input.txt", "r");
    f2=fopen("output.txt", "w");
    task(f1, f2);
    fclose(f1);
    fclose(f2);
}