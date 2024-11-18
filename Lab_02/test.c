#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//variant 6
//function to read the array from keyboard
void scan_array(int arr[], int size){
    printf("Input %d elements: ", size);
    for (int i=0; i<size; i++){
        scanf("%d", &arr[i]);
    }
}

//function to print the array
void print_array(int arr[], int size){
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

//function to check if a number is prime
bool prime(int number){
    if (number==2){
        return true;
    }
    for (int i=2; i<pow(number, 0.5); i++){
        if (number%i==0){
            return false;
        }
    }
    return true;
}

//function for task 1
//if the element is even then find its largest prime factor
//if the element is odd then find the sum of its digits
void new_task(int arr[], int size){
    for (int i=0; i<size; i++){
        if (arr[i]%2==0){
            int max_prime=0;
            for (int j=2; j<abs(arr[i]); j++){
                if (prime(j) && (arr[i]%j==0)){
                    max_prime=j;
                }
            }
            printf("\n%d is even. ", arr[i]);
            if (max_prime!=0){
                printf("It's largest prime factor is %d.", max_prime);
            }
            else{
                printf("This number has no prime fctors.");
            }
        }
        else{
            int number=abs(arr[i]);
            int sum=0;
            while (number>0){
                sum+=number%10;
                number/=10;
            }
            printf("\n%d is odd. The sum of it's digits is %d.", arr[i], sum);
        }
    }
    printf("\n");
}

//function to merge two arrays
//boolean variable is used to switch into ascending/descending mode
void merge(int arr[], int left, int middle, int right){
    int i, j, k;
    int size1=middle-left+1;
    int size2=right-middle;
    int left_arr[size1], right_arr[size2];
    for (i=0; i<size1; i++){
        left_arr[i]=arr[left+i];
    }
    for (j=0; j<size2; j++){
        right_arr[j]=arr[middle+1+j];
    }
    i=0;
    j=0;
    k=left;
    while (i<size1 && j<size2){
        //conditions change based on sorting mode
        if (left_arr[i] <= right_arr[j]){
            arr[k]=left_arr[i];
            i++;
        } 
        else{
            arr[k]=right_arr[j];
            j++;
        }
        k++; 
    }
    while (i<size1){
        arr[k]=left_arr[i];
        i++;
        k++;
    }
    while (j<size2){
        arr[k]=right_arr[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int left, int right){
    if (left<right){
        int middle=(left+right)/2;
        merge_sort(arr, left, middle);
        merge_sort(arr, middle+1, right);
        merge(arr, left, middle, right);
    }
}

int main(){
    int size;
    printf("Input the size of the array: ");
    scanf("%d", &size);
    //declare the array and it's copy
    int *array=(int*)malloc(size*sizeof(int));
    int *array_copy=(int*)malloc(size*sizeof(int));

    //call the functions for task 1
    scan_array(array, size);
    copy_array(array, array_copy, size);
    new_task(array, size);

    //call the functions for merge sort
    printf("\nOriginal array sorted in ascending order using merge sort:\n");
    merge_sort(array_copy, 0, size);
    print_array(array_copy, size);
    printf("\nOriginal array sorted in descending order using merge sort:\n");
    merge_sort(array_copy, 0, size);
    print_array(array_copy, size);

    //call the functions for counting sort
    
    
}