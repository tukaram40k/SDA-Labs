#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int middle, int right)//function to merge two arrays
{
    int i, j, k;
    int size1=middle-left+1;                         //calculate the size for temporary arrays
    int size2=right-middle;

    int left_arr[size1], right_arr[size2];           //declare two temporary arrays

    for (i=0; i<size1; i++)                          //fill the arrays with elements from the original array
    {
        left_arr[i]=arr[left+i];
    }
    for (j=0; j<size2; j++)
    {
        right_arr[j]=arr[middle+1+j];
    }

    
    i=0;
    j=0;
    k=left;
    while (i<size1 && j<size2)                       //merge the temporary arrays into the original one
    {
        if (left_arr[i] >= right_arr[j]) 
        {
            arr[k]=left_arr[i];
            i++;
        } 
        else 
        {
            arr[k]=right_arr[j];
            j++;
        }
        k++;
    }

    while (i<size1)                                  //if there are elements left, put them back into original array
    {
        arr[k]=left_arr[i];
        i++;
        k++;
    }

    while (j<size2)                                  //if there are elements left, put them back into original array
    {
        arr[k]=right_arr[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int left, int right)      //function for merge sort
{
    if (left<right)                                  //the base condition to stop the recursion
    {
        int middle=(left+right)/2;                   //find the middle position
        merge_sort(arr, left, middle);               //split the array and sort each half
        merge_sort(arr, middle+1, right);
        merge(arr, left, middle, right);
    }
}

// Utility function to print the array
void printArray(int arr[], int size) 
{
    int i;
    for (i=0; i<size; i++) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() 
{
    int arr[]={38, 27, 43, 3, 9, 82, 10};
    int arr_size=sizeof(arr)/sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    merge_sort(arr, 0, arr_size-1);

    printf("Sorted array in descending order is \n");
    printArray(arr, arr_size);
    return 0;
}