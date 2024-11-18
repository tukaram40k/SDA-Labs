#include <stdio.h>
#include <stdlib.h>

void countingSortDescending(int arr[], int n) {
    // Find the maximum element to determine the range
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // Create a count array to store the count of each element
    int* count = (int*)malloc((max + 1) * sizeof(int));

    // Initialize count array with zeros
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // Count the occurrences of each element in the input array
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // Create a temporary array to store the sorted result
    int* result = (int*)malloc(n * sizeof(int));

    // Update the count array to store the position of each element
    for (int i = max - 1; i >= 0; i--) {
        count[i] += count[i + 1];
    }
    // Build the result array by placing elements in descending order
    for (int i = 0; i < n; i++) {
        result[--count[arr[i]]] = arr[i];
    }

    // Copy the sorted result back to the original array
    for (int i = 0; i < n; i++) {
        arr[i] = result[i];
    }

    // Free dynamically allocated memory
    free(count);
    free(result);
}

int main() {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    countingSortDescending(arr, n);

    printf("\nSorted array in descending order: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
