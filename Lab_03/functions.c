#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void scan_array(int rows, int cols, int (*arr)[cols]){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            scanf("%d", &arr[i][j]);
        }
    }
}

void print_array(int rows, int cols, int (*arr)[cols]){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
}

void print_column(int arr[], int size){
    for (int i=0; i<size; i++){
        printf("%d\n", arr[i]);
    }
}

//function to find the gap between elements
int find_gap(int gap){
    gap=(gap*10)/13;
    if (gap<1){
        return 1;
    }
    return gap;
}

//function for comb sort
void comb_sort(int *arr, int size){
    int gap=size;
    bool swapped=true;
    while (gap != 1 || swapped){
        gap=find_gap(gap);
        swapped=false;
        //compare all elements with current gap
        for (int i=0; i<size-gap; i++){
            if (arr[i]<arr[i+gap]){
                int temp=arr[i];
                arr[i]=arr[i+gap];
                arr[i+gap]=temp;
                swapped=true;
            }
        }
    }
}

//function to find the largest element
int find_max(int arr[], int size){
	int max=arr[0];
	for (int i=1; i<size; i++){
		if (arr[i]>max){
			max=arr[i];
        }
    }
	return max;
}

//function for counting sort by digits
void counting_sort(int arr[], int size, int exp){
	int output[size];
	int i, count[10]={ 0 };

	for (i=0; i<size; i++)
		count[(arr[i]/exp)%10]++;

	for (i=1; i<10; i++)
		count[i] += count[i-1];

	for (i=size-1; i >= 0; i--){
		output[count[(arr[i]/exp) % 10]-1]=arr[i];
		count[(arr[i]/exp) % 10]--;
	}

	for (i=0; i<size; i++)
		arr[i]=output[i];
}

//function for radix sort
void radix_sort(int arr[], int size){
	int max=find_max(arr, size);
	for (int exp=1; max / exp>0; exp *= 10)
		counting_sort(arr, size, exp);
}

//recursive function to find pairs of elements equal to S
int find_pairs(int arr[], int size, int S, int x1, int x2){
    if (x1>=size || x2>=size){
        return 0;
    }
    int pairs=0;
    if ((x1!=x2) && (arr[x1]+arr[x2]==S)){
        printf("%d + %d = S = %d\n", arr[x1], arr[x2], S);
        pairs++;
    }
    if (x2 < size-1){
        pairs+=find_pairs(arr, size, S, x1, x2 + 1);
    } 
    else{
        pairs+=find_pairs(arr, size, S, x1 + 1, x1 + 2);
    }
    return pairs;
}

void task(int rows, int cols, int (*arr)[cols], int S){
    int num_of_pairs=0;
    int max_pairs=0;
    int min_pairs=rows;
    int biggest_col=0;
    int smallest_col=0;
    int *temp_col=(int*)malloc(rows*sizeof(int));
    int pairs=0;
    for (int i=0; i<cols; i++){
        pairs=0;
        for (int j=0; j<rows; j++){
            temp_col[j]=arr[j][i];
        }
        printf("\nColumn %d pairs:\n", i);
        pairs=find_pairs(temp_col, rows, S, 0, 1);
        if (pairs==0){
            printf("No pairs in this column\n");
        }
        num_of_pairs+=pairs;
        if (pairs>max_pairs){
            biggest_col=i;
            max_pairs=pairs;
        }
        if (pairs<min_pairs){
            smallest_col=i;
            min_pairs=pairs;
        }
    }
    if (num_of_pairs==0){
        printf("There were no pairs of elements equal to %d. Array was not changed.\n", S);
        return;
    }
    printf("\nColumn with the most (%d) pairs: %d\n", max_pairs, biggest_col);
    printf("Column with the least (%d) pairs: %d\n", min_pairs, smallest_col);
    if (num_of_pairs%2==0){
        printf("The number of pairs is even (%d).\n", num_of_pairs);
        printf("Applying comb sort in descending order to the column with the most pairs.\n");
        for (int i=0; i<rows; i++){
            temp_col[i]=arr[i][biggest_col];
        }
        comb_sort(temp_col, rows);
        for (int i=0; i<rows; i++){
            arr[i][biggest_col]=temp_col[i];
        }
        printf("Array with column %d sorted in descending order by comb sort:\n", biggest_col);
    }
    else{
        printf("The number of pairs is odd (%d).\n", num_of_pairs);
        printf("Applying radix sort in ascending order to the column with the fewest pairs.\n");
        for (int i=0; i<rows; i++){
            temp_col[i]=arr[i][smallest_col];
        }
        radix_sort(temp_col, rows);
        for (int i=0; i<rows; i++){
            arr[i][smallest_col]=temp_col[i];
        }
        printf("Array with column %d sorted in ascending order by radix sort:\n", smallest_col);
    }
}