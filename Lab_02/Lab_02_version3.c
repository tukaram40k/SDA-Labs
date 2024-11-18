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
    if (abs(number)<2){
        return false;
    }
    for (int i=2; i<number-1; i++){
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
            for (int j=1; j<abs(arr[i]); j++){
                if (prime(j) && (arr[i]%j==0)){
                    max_prime=j;
                }
            }
            printf("\n%d is even. ", arr[i]);
            if (max_prime!=0){
                printf("It's largest prime factor is %d.", max_prime);
            }
            else{
                printf("This number has no prime factors.");
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
void merge(int arr[], int left, int middle, int right, bool ascending){
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
        if (ascending){
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
        else{
            if (left_arr[i] >= right_arr[j]){
                arr[k]=left_arr[i];
                i++;
            } 
            else{
                arr[k]=right_arr[j];
                j++;
            }
            k++;
        }
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

void merge_sort(int arr[], int left, int right, bool ascending){
    if (left<right){
        int middle=(left+right)/2;
        merge_sort(arr, left, middle, ascending);
        merge_sort(arr, middle+1, right, ascending);
        merge(arr, left, middle, right, ascending);
    }
}

void counting_sort(int arr[], int size, bool ascending){
    int max=arr[0];
    for (int i=1; i<size; i++){
        if (arr[i] > max){
            max=arr[i];
        }
    }
    int* counter_array=(int*)malloc((max+1)*sizeof(int));
    for (int i=0; i <= max; i++){
        counter_array[i]=0;
    }
    for (int i=0; i<size; i++){
        counter_array[arr[i]]++;
    }
    int* result_array=(int*)malloc(size*sizeof(int));

    //conditions change based on sorting mode
    if (ascending){
        for (int i=1; i<=max; i++){
            counter_array[i]+=counter_array[i-1];
        }
        for (int i=size-1; i>=0; i--){
            result_array[--counter_array[arr[i]]]=arr[i];
        }
    }
    else{
        for (int i=max-1; i >= 0; i--){
            counter_array[i]+=counter_array[i+1];
        }
        for (int i=0; i<size; i++){
            result_array[--counter_array[arr[i]]]=arr[i];
        }
    }
    for (int i=0; i<size; i++){
        arr[i]=result_array[i];
    }
    free(counter_array);
    free(result_array);
    printf("\nArray sorted in ");
    if (ascending){
        printf("ascending");
    }
    else{
        printf("descending");
    }
    printf(" order by the counting sort:\n");
    print_array(arr, size);
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
    printf("\nArray sorted in ascending order using merge sort:\n");
    merge_sort(array_copy, 0, size-1, true);
    print_array(array_copy, size);
    printf("\nArray sorted in descending order using merge sort:\n");
    merge_sort(array_copy, 0, size-1, false);
    print_array(array_copy, size);

    //call the functions for counting sort
    counting_sort(array, size, true);
    counting_sort(array, size, false);
    
    free(array);
    free(array_copy);
}