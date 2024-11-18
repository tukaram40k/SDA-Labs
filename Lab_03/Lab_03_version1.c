#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//variant 6
//function to read an array from keyboard
void scan_array(int rows, int cols, int arr[rows][cols]){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            scanf("%d", &arr[i][j]);
        }
    }
}

//function to print an array
void print_array(int rows, int cols, int arr[rows][cols]){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
}

//function for counting sort in descending order
void counting_sort_descending(int arr[], int size){
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
    for (int i=max-1; i >= 0; i--){
        counter_array[i]+=counter_array[i+1];
    }
    for (int i=0; i<size; i++){
        result_array[--counter_array[arr[i]]]=arr[i];
    }
    for (int i=0; i<size; i++){
        arr[i]=result_array[i];
    }
    free(counter_array);
    free(result_array);
}

//helper function for heap sort
void heapify(int arr[], int size, int i){
    int temp, maximum, left_index, right_index; 
    maximum=i; 
    right_index=2*i+2;
    left_index=2*i+1;
    if (left_index < size && arr[left_index] > arr[maximum]){
        maximum=left_index;
    }
    if (right_index < size && arr[right_index] > arr[maximum]){
        maximum=right_index;
    }  
    if (maximum != i){
        temp=arr[i]; 
        arr[i]=arr[maximum]; 
        arr[maximum]=temp; 
        heapify(arr, size, maximum); 
    }
}

//function for heap sort
void heap_sort(int arr[], int size){
    int i, temp;  
    for (i=size/2-1; i>=0; i--){ 
        heapify(arr, size, i); 
    } 
    for (i=size-1; i>0; i--){ 
        temp=arr[0]; 
        arr[0]=arr[i]; 
        arr[i]=temp; 
        heapify(arr, i, 0); 
    } 
}

//function for the main task
void task(int rows, int cols, int arr[rows][cols], int S){
    int num_of_pairs=0;
    int max_pairs=0;
    int min_pairs=rows;
    int biggest_col=0;
    int smallest_col=0;
    //go through the rows
    for (int i=0; i<cols; i++){
        int pairs=0;
        for (int j=0; j<rows; j++){
            for (int k=j+1; k<cols; k++){
                //find the pairs
                if (arr[j][i]+arr[k][i]==S){
                    pairs++;
                    num_of_pairs++;
                    printf("arr[%d][%d] + arr[%d][%d] = %d + %d = %d = S\n", j, i, k, i, arr[j][i], arr[k][i], S);
                }
            }
        }
        //find the biggest/smallest column
        if (pairs>max_pairs){
            biggest_col=i;
            max_pairs=pairs;
        }
        if (pairs<min_pairs){
            smallest_col=i;
            min_pairs=pairs;
        }
    }
    //conditions for different sorts
    if (num_of_pairs==0){
        printf("There were no pairs of elements equal to %d. Array was not changed.\n", S);
        return;
    }
    printf("Column with the most (%d) pairs: %d\n", max_pairs, biggest_col);
    printf("Column with the least (%d) pairs: %d\n", min_pairs, smallest_col);
    //declare a 1d array to store the column for sorting
    int col_for_sort[rows];
    if (num_of_pairs%2==0){
        printf("The number of pairs is even (%d).\n", num_of_pairs);
        printf("Applying counting sort in descending order to the column with the most pairs.\n");
        for (int i=0; i<rows; i++){
            col_for_sort[i]=arr[i][biggest_col];
        }
        //applying counting sort to a column
        counting_sort_descending(col_for_sort, rows);
        for (int i=0; i<rows; i++){
            arr[i][biggest_col]=col_for_sort[i];
        }
        printf("Array with column %d sorted in descending order by counting sort:\n", biggest_col);
    }
    else{
        printf("The number of pairs is odd (%d).\n", num_of_pairs);
        printf("Applying heap sort in ascending order to the column with the fewest pairs.\n");
        for (int i=0; i<rows; i++){
            col_for_sort[i]=arr[i][smallest_col];
        }
        //applying heap sort to a column
        heap_sort(col_for_sort, rows);
        for (int i=0; i<rows; i++){
            arr[i][smallest_col]=col_for_sort[i];
        }
        printf("Array with column %d sorted in ascending order by heap sort:\n", smallest_col);
    }
}

int main(){
    int rows=0;
    int cols=0;
    int S=0;
    printf("Input the dimensions of the matrix: ");
    scanf("%d %d", &rows, &cols);
    printf("Input the number S: ");
    scanf("%d", &S);
    printf("Input the %d by %d matrix:\n", rows, cols);
    //declaring the matrix
    int array[rows][cols];
    //calling the functions
    scan_array(rows, cols, array);
    task(rows, cols, array, S);
    print_array(rows, cols, array);
}