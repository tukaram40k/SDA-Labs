#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void copy(int arr[], int arr_copy[], int size)          //function to copy the array
{
    for (int i=0; i<size; i++)
    {
        arr_copy[i]=arr[i];                             
    }
}

void print_array(int arr[], int size)                   //function to print the array
{
    for (int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);                          
    }
    printf("\n");
}

int *bubble_sort_descending(int arr[], int size)        //function for bubble sort in reverse order
{
    for (int i=0; i<size; i++)
    {
        for (int j=i; j<size; j++)
        {
            if (arr[j]>arr[i])                          //iterating through the array and comparing each element to its neighbour
            {
                int temp=arr[j];                        //swapping the elements when condition is met
                arr[j]=arr[i];                          //using a temporary variable to store the value of an element
                arr[i]=temp;
            }
        }
    }
    return arr;
}

int main()
{
    printf("Input the size of the array: ");
    int size; 
    scanf("%d", &size);                                 //reading the size of the array

    int *array=(int *)malloc(size*sizeof(int));         //allocating memory for the array
    int *array_copy=(int *)malloc(size*sizeof(int));    //allocating memory to copy the array for later use

    printf("Input %d elements: ", size);
    for (int i=0; i<size; i++)
    {
        scanf("%d", &array[i]);                         //read array from console
    }

    copy(array, array_copy, size);                      //calling the functions           
    int *sorted_desc=bubble_sort_descending(array_copy, size);
    printf("\nArray sorted in descending order by bubble sort:\n");
    print_array(sorted_desc, size);
    
    free(array);
    free(array_copy);
}