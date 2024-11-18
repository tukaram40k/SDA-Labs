#include <stdio.h>

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

int main() {
    int arr[] = {7, 7, 6, 5, 4, 5, 3};
    int size = 7;
    int S = 10;

    for (int i=0; i<size; i++){
        printf("%d ", arr[i]);
    }
    printf("Pairs with sum %d:\n", S);
    int pairs=find_pairs(arr, size, S, 0, 1);
    printf("%d pairs found.", pairs);
    return 0;
}
