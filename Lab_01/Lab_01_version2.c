#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_array(int* arr, int size)                           //function to print the array
{
    for (int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);                           
    }
    printf("\n");
}

void find_repeated_delete_first(int* arr, int* size)
{
    printf("Original array: \n");
    print_array(arr, *size);                                   //print the original array

    int repeated_index;                                        //declare a variable to store the index of the repeated element
    bool repeated=false;
    
    for (int i=0; i<*size; i++)                                //start a loop to go through all the elements
    {
        for (int j=i+1; j<*size; j++)
        {
            if (arr[i]==arr[j])                                //compare all elements to each other
            {
                repeated=true;
                repeated_index=i;                              //store the index of the element
                break;                                         //once the element is found, exit the loop
            }
        }
    }
    if (!repeated)                                             //check if any elements were repeated
    {
        printf("No repeating elements.");
        return;
    }
    printf("\nElement %d is repeated\n", arr[repeated_index]); //print the repeated element
    printf("Array without the repeated element:\n");
    for (int i=0; i<*size; i++)
    {
        if (i!=repeated_index) printf("%d ", arr[i]);          //print the array without the repeating element
    }
}

void bubble_sort_descending(int* arr, int* size)               //function for bubble sort in reverse order
{
    for (int i=0; i<*size; i++)
    {
        for (int j=i; j<*size; j++)
        {
            if (arr[j]>arr[i])                                 //go through the array and compare each element to its neighbour
            {
                int temp=arr[j];                               //using a temporary variable to store the value of an element
                arr[j]=arr[i];                                 //swapping the elements when condition is met
                arr[i]=temp;
            }
        }
    }
    printf("\n\nArray sorted in descending order by bubble sort:\n");
    print_array(arr, *size);                                   //return the result
}

void selection_sort_ascending(int* arr, int* size)             //function for selection sort
{
    int min=arr[0];                                            //declare a variable to store the smallest element
    for (int i=0; i<*size; i++)
    {
        min=arr[i];
        for (int j=i+1; j<*size; j++)
        {           
            if (arr[j]<min)                                    //compare each element to the current minimum
            {
                min=arr[j];                                    //update the minimum variable
                arr[j]=arr[i];                                 //swap elements if smaller one is found
                arr[i]=min;                              
            }
        }
    }
    printf("\nArray sorted in ascending order by selection sort:\n");
    print_array(arr, *size);                                   //return the result
}

int main()
{
    printf("Input the size of the array: ");
    int size; 
    scanf("%d", &size);                                        //reading the size of the array

    int *array=(int *)malloc(size*sizeof(int));                //allocating memory for the array

    printf("Input %d elements: ", size);
    for (int i=0; i<size; i++)
    {
        scanf("%d", &array[i]);                                //read array from console
    }

    find_repeated_delete_first(array, &size);                  //call the functions 
    bubble_sort_descending(array, &size);
    selection_sort_ascending(array, &size); 
    free(array);                                               //free the used memory
}