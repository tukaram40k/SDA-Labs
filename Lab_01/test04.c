#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void copy(int arr[], int arr_copy[], int size)       //function to copy the array for later use
{
    for (int i=0; i<size; i++)
    {
        arr_copy[i]=arr[i];                          //copying elements one by one  
    }
}

void print_array(int arr[], int size)                //function for printing the array
{
    printf("\n");
    for (int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);                          
    }
    printf("\n");
}

void delete_repeating_elements(int arr[], int size)
{                                              
    int repeated=0;                                  //declare a variable to keep track of repeated elements
    printf("\nArray without the repeated elements: ");
    for (int i=0; i<size; i++)                       //starting the loop to go through all the elements
    {
        repeated=0;
        for (int j=0; j<i; j++)
        {
            if (arr[i]==arr[j]) repeated=1;          //compare each elements to all the previous ones
        }
        if (repeated==0) printf("%d ", arr[i]);      //if the element was not repeated before, print it
    }
}

int main()
{
    printf("Input the size of the array: ");  
    int size=0;
    scanf("%d", &size);                              //reading the size of the array

    int *array=(int *)malloc(size*sizeof(int));      //allocating memory for the array
    int *array_copy=(int *)malloc(size*sizeof(int)); //allocating memory to copy the array for later use

    printf("\nInput %d elements: ", size);             
    for (int i=0; i<size; i++)
    {
        scanf("%d", &array[i]);                      //reading the array from console
    }
    
    copy(array, array_copy, size);                   //copy the array for later use

    delete_repeating_elements(array_copy, size);    //calling the function to delete repeating elements
}