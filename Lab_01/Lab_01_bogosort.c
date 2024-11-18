#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

bool sorted(int arr[], int size)                     //function to check if the array is sorted
{
    for (int i=0; i<size-1; i++)
    {
        if (arr[i]>arr[i+1]) return false;           //if any element is bigger than the next one, return false
    }
    return true;                                     //otherwise, return true
}

int bogosort(int arr[], int size)                    //function for bogosort
{
    int attempts_needed=0;
    while (sorted(arr, size)==false)                 //repeat while array is unsorted 
    {
        for (int i=0; i<size; i++)                   //swapping each element with another randomly chosen one
        {
            int temp1=arr[i];                        //store the value in temporary variable
            int temp2=rand() % size;                 //store index of a random element
            arr[i]=arr[temp2];                       //swapping the elements
            arr[temp2]=temp1;
        }
        attempts_needed++;                           //incrementing the attempt counter
    }

    for (int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);                       //printing the sorted array
    }
    printf("\nAttempts needed: %d\n\n", attempts_needed);

    return attempts_needed;                          //return number of attempts for bogosort
}

void simulation(int num_of_sortings, int arr[], int arr_copy[], int size)
{
    int total_attempts=0;                            //variable to store the number of attempts
    float average_attempts=0;                        //variable to store the average number of attempts
    float average_time=0;                            //variable to store the average time for sorting

    struct timespec begin;                           //start the timer using CPU time
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);

    for (int i=0; i<num_of_sortings; i++)            //start the loop for sorting
    {
        printf("Sorting N%d:\n", i+1);
        total_attempts+=bogosort(arr, size);         //incrementing the total attempts counter
        for (int i=0; i<size; i++)
        {
            arr[i]=arr_copy[i];                      //restoring the original array
        }
    }

    struct timespec end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);   //end the timer
    double time=(end.tv_sec-begin.tv_sec)+(end.tv_nsec-begin.tv_nsec)/1000000000.0;
                                                     //calculate the time between start and end in seconds


    average_attempts=(float)total_attempts/num_of_sortings; //counting the average number of attempts by dividing
                                                     //total attempts by the number of sortings 

    average_time=time/num_of_sortings;               //counting the average time for sorting the array by dividing
                                                     //total elapsed time by the number of sortings 


    printf("Array of %d elements sorted %d times.", size, num_of_sortings);       //printing results
    printf("\nAverage number of attempts needed: %.3f", average_attempts);
    printf("\nAverage time needed to sort the array: %.5f seconds\n\n", average_time);

}


int main()
{
    srand(time(NULL));
    printf("Input the size of the array: ");  
    int size=0, number_of_sortings=0;
    scanf("%d", &size);                              //reading the size of the array

    int *array=(int *)malloc(size*sizeof(int));      //allocating memory for the array
    int *array_copy=(int *)malloc(size*sizeof(int)); //copying the array for later use

    printf("Input %d elements: ", size);             
    for (int i=0; i<size; i++)
    {
        scanf("%d", &array[i]);                      //reading the array from console
    }

    printf("Input the number of sortings: ", number_of_sortings);
    scanf("%d", &number_of_sortings);                //reading the number of sortings

    for (int i=0; i<size; i++)
    {
        array_copy[i]=array[i];                      //copy the array for later use
    }

    simulation(number_of_sortings, array, array_copy, size);
                                                     //calling the function that does all the calculations

    free(array);                                     //freeing the used memory
    free(array_copy);
}