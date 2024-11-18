#include <stdio.h>

void findPairs(int i, int j, int k, int rows, int cols, int arr[rows][cols], int S, int *pairs, int *max_pairs, int *min_pairs, int *biggest_col, int *smallest_col) {
    if (j < cols) {
        if (k < cols) {
            if (arr[i][j] + arr[i][k] == S) {
                (*pairs)++;
                printf("arr[%d][%d] + arr[%d][%d] = %d + %d = %d = S\n", i, j, i, k, arr[i][j], arr[i][k], S);
            }
            findPairs(i, j, k + 1, rows, cols, arr, S, pairs, max_pairs, min_pairs, biggest_col, smallest_col);
        } else {
            findPairs(i, j + 1, j + 2, rows, cols, arr, S, pairs, max_pairs, min_pairs, biggest_col, smallest_col);
        }
    } else {
        if (*pairs > *max_pairs) {
            *biggest_col = j - 1;
            *max_pairs = *pairs;
        }
        if (*pairs < *min_pairs) {
            *smallest_col = j - 1;
            *min_pairs = *pairs;
        }
    }
}

void task1Helper(int i, int rows, int cols, int arr[rows][cols], int S, int *num_of_pairs, int *max_pairs, int *min_pairs, int *biggest_col, int *smallest_col) {
    int pairs = 0;
    findPairs(i, 0, 1, rows, cols, arr, S, &pairs, max_pairs, min_pairs, biggest_col, smallest_col);
    *num_of_pairs += pairs;
}

void task1(int i, int rows, int cols, int arr[rows][cols], int S, int num_of_pairs, int max_pairs, int min_pairs, int biggest_col, int smallest_col) {
    if (i < rows) {
        task1Helper(i, rows, cols, arr, S, &num_of_pairs, &max_pairs, &min_pairs, &biggest_col, &smallest_col);
        task1(i + 1, rows, cols, arr, S, num_of_pairs, max_pairs, min_pairs, biggest_col, smallest_col);
    } else {
        if (num_of_pairs % 2 == 0) {
            printf("The number of pairs is even (%d).\n", num_of_pairs);
        } else {
            printf("The number of pairs is odd (%d).\n", num_of_pairs);
        }
        printf("Column with the most pairs: %d\n", biggest_col);
        printf("Column with the least pairs: %d\n", smallest_col);
    }
}

int main() {
    int rows = 3;
    int cols = 4;
    int arr[3][4] = {{1, 2, 3, 4}, {5, 4, 3, 8}, {3, 10, 11, 12}};
    int S = 6;
    int num_of_pairs = 0;
    int max_pairs = 0;
    int min_pairs = cols;
    int biggest_col = 0;
    int smallest_col = 0;
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            printf("%2d ", arr[i][j]);
        }
        printf("\n");
    }

    task1(0, rows, cols, arr, S, num_of_pairs, max_pairs, min_pairs, biggest_col, smallest_col);

    return 0;
}
