#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//variant 6
//function to read the array from keyboard
void scan_array(int* arr, int size){
    printf("Input %d elements: ", size);
    for (int i=0; i<size; i++){
        scanf("%d", &arr[i]);
    }
}

//function to print the array
void print_array(int* arr, int size){
    for (int i=0; i<size; i++){
        printf("%d ", arr[i]);                          
    }
    printf("\n");
}

//function to copy an array
void copy_array(int arr[], int arr_copy[], int size){
    for (int i=0; i<size; i++){
        arr_copy[i]=arr[i];
    }
}

//function for task 1
void task1(int* arr, int size){
    //create a variable to store the last odd element
    int last_odd;
    //create two variables to check if all elements are odd/even
    bool all_odd=true, all_even=true;
    //start a loop to locate the last odd element
    for (int i=0; i<size; i++){
        if (arr[i]%2!=0){
            last_odd=arr[i];
        }
    }
    //check if all elements are even
    for (int i=0; i<size; i++){
        if (arr[i]%2!=0){
            all_even=false;
            break;
        }
    }
    if (all_even){
        printf("All elements are even. The array was not changed.\n");
        return;
    }
    //check if all the elements are odd
    else{
        for (int i=0; i<size; i++){
            if (arr[i]%2==0){
                all_odd=false;
                break;
            }
        }
    }
    //changing the odd elements acording to the task
    if (all_odd){
        for (int i=1; i<size-1; i++){
            arr[i]+=arr[0];
        }
        printf("All elements were odd.\n");
        printf("All elements except the last are increased by %d:\n",arr[0]);
        arr[0]*=2;
        print_array(arr, size);
        return;
    }
    //changing the even elements according to the task
    else{
        for (int i=0; i<size; i++){
            arr[i]+=last_odd;
        }
        printf("Not all elements were odd.\n");
        printf("All elements increased by %d:\n", last_odd);
        print_array(arr, size);
        return;
    }
}

void swap(int* num1, int* num2){
    int temp=*num1;
    *num1=*num2;
    *num2=temp;
}

//partition function for quicksort to locate the new pivot 
//boolean variable is used to switch into ascending/descending mode
int partition(int* arr, int *left_index, int *right_index, bool ascending){
    int pivot=arr[*right_index];
    int i=(*left_index-1);
    for (int j=*left_index; j<=*right_index-1; j++){
        if ((ascending && arr[j]<pivot) || (!ascending && arr[j]>pivot)){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[*right_index]);
    return (i+1);
}

//function for quicksort 
//boolean variable is used to switch into ascending/descending mode
void quicksort(int* arr, int *left_index, int *right_index, bool ascending){
    if (*left_index<*right_index){
        int pivot=partition(arr, left_index, right_index, ascending);
        quicksort(arr, left_index, &pivot-1, ascending);
        quicksort(arr, &pivot+1, right_index, ascending);
    }
}

//function for shell sort
//boolean variable is used to switch into ascending/descending mode
void shell_sort(int* arr, int* size, bool ascending){
    for (int i=*size/2; i>0; i/=2){
        for (int j=i; j<*size; j+=1){
            int temp=arr[j];
            int k;
            if (ascending){
                for (k=j; k>=i && arr[k-i]>temp; k-=i){
                    arr[k]=arr[k-i];
                }
            }
            else{
                for (k=j; k>=i && arr[k-i]<temp; k-=i){
                    arr[k]=arr[k-i];
                }
            }
            arr[k]=temp;
        }
    }
    printf("\nArray from task 1 sorted in ");   
    if (ascending){
        printf("ascending");
    }
    else{
        printf("descending");
    }
    printf(" order using shell sort:\n");
    print_array(arr, *size);
}

int main(){
    int size;
    printf("Input the size of the array: ");
    scanf("%d", &size);
    //declare the array and it's copy
    int *array=(int*)malloc(sizeof(int)*size);
    int *array_copy=(int*)malloc(sizeof(int)*size);
    //call the function for task 1
    scan_array(array, size);
    copy_array(array, array_copy, size);
    task1(array, size);

    //call the functions for quicksort
    int zero=0;
    printf("\nOriginal array sorted in ascending order using quicksort:\n");
    quicksort(array_copy, &zero, &size - 1, true);
    print_array(array_copy, size);
    printf("\nOriginal array sorted in descending order using quicksort:\n");
    quicksort(array_copy, &zero, &size - 1, false);
    print_array(array_copy, size);

    //call the functions for shell sort
    shell_sort(array, &size, true);
    shell_sort(array, &size, false);

    free(array);
    free(array_copy);
    
}