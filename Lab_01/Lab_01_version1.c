#include <stdio.h>
#include <stdlib.h>
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

void find_repeated_delete_first(int arr[], int size)
{
    printf("Original array: \n");
    print_array(arr, size);                             //print the original array

    int repeated_index;                                 //declare a variable to store the index of the repeated element
    bool repeated=false;
    
    for (int i=0; i<size; i++)                          //start a loop to go through all the elements
    {
        for (int j=i+1; j<size; j++)
        {
            if (arr[i]==arr[j])                         //finding the repeating element by comparing all elements to each other
            {
                repeated_index=i;                       //store the index of the element
                repeated=true;
                break;                                  //once the element is found, exit the loop
            }
        }
    }
    if (!repeated)
    {
        printf("No repeating elements.\n");
        return;
    }
    printf("\nElement %d is repeated\n", arr[repeated_index]);
    printf("Array without the repeated element:\n");
    for (int i=repeated_index; i<size-1; i++)
    {
        arr[i]=arr[i+1];                                //shifting remaining elements to fill the empty place
    }
    print_array(arr, size-1);                           //printing the result
}

void bubble_sort_descending(int arr[], int size)        //function for bubble sort in reverse order
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
    printf("\nCopy of the original array sorted in descending order by bubble sort:\n");
    print_array(arr, size);                             //printing the result
}

void selection_sort_ascending(int arr[], int size)      //function for selection sort
{
    int min=arr[0];                                     //declaring a variable to store the smallest element
    for (int i=0; i<size; i++)
    {
        min=arr[i];
        for (int j=i+1; j<size; j++)
        {           
            if (arr[j]<min)                             //comparing each element to the current minimum
            {
                min=arr[j];                             //swapping elements if smaller one is found
                arr[j]=arr[i];
                arr[i]=min;                              
            }
        }
    }
    printf("\nThe array sorted in ascending order by selection sort:\n");
    print_array(arr, size);                             //printing the result
}

int main()
{
    printf("Input the size of the array: ");
    int size; 
    scanf("%d", &size);                                 //reading the size of the array
    printf("Input %d elements: ", size);
    int array[size], array_copy[size];                  //declaring the array and its copy
    for (int i=0; i<size; i++)
    {
        scanf("%d", &array[i]);                         //read array from console
    }
                           
    copy(array, array_copy, size);                      //calling the functions
    find_repeated_delete_first(array, size);             
    bubble_sort_descending(array_copy, size);
    selection_sort_ascending(array_copy, size);
}