#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void copy(int arr[], int arr_copy[], int size)                 //function to copy the array
{
    for (int i=0; i<size; i++)
    {
        arr_copy[i]=arr[i];                             
    }
}

void print_array(int arr[], int size)                          //function to print the array
{
    for (int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);                          
    }
    printf("\n");
}

int *find_repeated_delete_first(int arr[], int size)
{
    printf("Original array: \n");
    print_array(arr, size);                                    //print the original array

    int repeated_element;                                      //declare a variable to store the value of the repeated element
    int repeated_index;                                        //declare a variable to store the index of the repeated element
    
    for (int i=0; i<size; i++)                                 //start a loop to go through all the elements
    {
        for (int j=i+1; j<size; j++)
        {
            if (arr[i]==arr[j])                                //compare all elements to each other
            {
                repeated_element=arr[i];                       //store the repeated element 
                repeated_index=i;                              //store the index of the element
                break;                                         //once the element is found, exit the loop
            }
        }
    }
    printf("\nElement %d is repeated\n", repeated_element);    //print the repeated element
    printf("Array without the repeated element:\n");
    for (int i=repeated_index; i<size-1; i++)
    {
        arr[i]=arr[i+1];                                       //shifting remaining elements to fill the empty place
    }
    int *result_arr=(int *)malloc((size-1)*sizeof(int));       //creating a temporary array to store the result
    for (int i=0; i<size-1; i++)
    {
        result_arr[i]=arr[i];
    }
    return result_arr;                                         //return the result
}

int *bubble_sort_descending(int arr[], int size)               //function for bubble sort in reverse order
{
    for (int i=0; i<size; i++)
    {
        for (int j=i; j<size; j++)
        {
            if (arr[j]>arr[i])                                 //go through the array and compare each element to its neighbour
            {
                int temp=arr[j];                               //using a temporary variable to store the value of an element
                arr[j]=arr[i];                                 //swapping the elements when condition is met
                arr[i]=temp;
            }
        }
    }
    return arr;                                                //return the result
}

int *selection_sort_ascending(int arr[], int size)             //function for selection sort
{
    int min=arr[0];                                            //declare a variable to store the smallest element
    for (int i=0; i<size; i++)
    {
        min=arr[i];
        for (int j=i+1; j<size; j++)
        {           
            if (arr[j]<min)                                    //compare each element to the current minimum
            {
                min=arr[j];                                    //update the minimum variable
                arr[j]=arr[i];                                 //swap elements if smaller one is found
                arr[i]=min;                              
            }
        }
    }
    return arr;                                                //return the result
}

int main()
{
    printf("Input the size of the array: ");
    int size; 
    scanf("%d", &size);                                        //reading the size of the array

    int *array=(int *)malloc(size*sizeof(int));                //allocating memory for the array
    int *array_copy=(int *)malloc(size*sizeof(int));           //allocating memory to copy the array for later use

    printf("Input %d elements: ", size);
    for (int i=0; i<size; i++)
    {
        scanf("%d", &array[i]);                                //read array from console
    }

    copy(array, array_copy, size);                             //copy the array for later use

    int *array_unique=find_repeated_delete_first(array, size); //make a pointer to the result of the function 
    print_array(array_unique, size-1);                         //print the result

    int *sorted_desc=bubble_sort_descending(array_copy, size); //make a pointer to the result of the function 
    printf("\nArray sorted in descending order by bubble sort:\n");
    print_array(sorted_desc, size);                            //print the result

    int *sorted_asc=selection_sort_ascending(array_copy, size);//make a pointer to the result of the function 
    printf("\nArray sorted in ascending order by selection sort:\n");
    print_array(sorted_asc, size);                             //print the result

    free(array);                                               //free the used memory
    free(array_copy);
    free(array_unique);
}