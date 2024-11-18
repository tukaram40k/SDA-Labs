#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void copy(int arr[], int arr_copy[], int size)       //function to copy the array for later use
{
    for (int i=0; i<size; i++)
    {
        arr_copy[i]=arr[i];                          //copying elements one by one  
    }
}

void print_array(int arr[], int size)                //function for printing the array
{
    printf("\n");
    for (int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);                       //print each element individually    
    }
    printf("\n");
}

void delete_repeating_elements(int arr[], int size)  //function to delete the repeating elements
{                                              
    bool repeated=false;                             //declare a variable to keep track of repeated elements
    bool unique=true;                                //declare a variable to find if all the elements were unique
    printf("\nArray without the repeated elements: ");
    for (int i=0; i<size; i++)                       //starting the loop to go through all the elements
    {
        repeated=false;
        for (int j=0; j<i; j++)
        {
            if (arr[i]==arr[j]) 
            {
                repeated=true;                       //compare each elements to all the previous ones
                unique=false;
            }
        }
        if (!repeated) printf("%d ", arr[i]);        //if the element was not repeated before, print it
    }
    if (unique) printf("\nThere were no repeating elements in the array.\n");
    printf("\n");
}

void merge(int arr[], int left, int middle, int right)//function to merge two arrays
{
    int i, j, k;                                     //declare counter variables
    int size1=middle-left+1;                         //calculate the size for temporary arrays
    int size2=right-middle;

    int left_arr[size1], right_arr[size2];           //declare two temporary arrays

    for (i=0; i<size1; i++)                          //fill the left array with elements from the original array
    {
        left_arr[i]=arr[left+i];                     //copy the elements one by one
    }
    for (j=0; j<size2; j++)                          //fill the left array with elements from the original array
    {
        right_arr[j]=arr[middle+1+j];                //copy the elements one by one
    }

    i=0;
    j=0;
    k=left;
    while (i<size1 && j<size2)                       //merge the temporary arrays into the original one
    {
        if (left_arr[i] >= right_arr[j])             //compare the elements and put into the original array
        {
            arr[k]=left_arr[i];                      //copy the elements one by one
            i++;
        } 
        else 
        {
            arr[k]=right_arr[j];                     //copy the elements one by one
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

void insertion_sort(int arr[], int size)             //function for insertion sort
{
    for(int i=1; i<size; i++)                        //starting the loop to go through all the elements
    {
        int temp=arr[i];
        int j=i-1;
        while((j >= 0) && (arr[j]>temp))
        {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=temp;
    }
    printf("\nArray sorted in ascending order by insertion sort:");
    print_array(arr, size);
}

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

    print_array(arr, size);                          //printing the sorted array
    printf("Attempts needed: %d\n\n", attempts_needed);
    return attempts_needed;                          //return number of attempts for bogosort
}

void simulation(int num_of_sortings, int arr[], int arr_copy[], int size)
{
    int total_attempts=0;                            //variable to store the number of attempts
    float average_attempts=0;                        //variable to store the average number of attempts
    float average_time=0;                            //variable to store the average time for sorting with bogosort
    double insertion_sort_time=0;                    //variable to store the time for sorting with insertion sort

    struct timespec begin1;                          //start the timer using CPU time
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin1);

    for (int i=0; i<num_of_sortings; i++)            //start the loop for sorting
    {
        printf("Sorting N%d:", i+1);
        total_attempts+=bogosort(arr, size);         //incrementing the total attempts counter
        copy(arr_copy, arr, size);                   //restoring the original array
    }

    struct timespec end1;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end1);  //end the timer
    double time=(end1.tv_sec-begin1.tv_sec)+(end1.tv_nsec-begin1.tv_nsec)/1000000000.0;
                                                     //calculate the time between start and end in seconds


    average_attempts=(float)total_attempts/(float)num_of_sortings; //counting the average number of attempts by dividing
                                                     //total attempts by the number of sortings 

    average_time=time/num_of_sortings;               //counting the average time for sorting the array by dividing
                                                     //total elapsed time by the number of sortings 

    struct timespec begin2;                          //start the timer using CPU time
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);

    insertion_sort(arr, size);
    printf("\n");

    struct timespec end2;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);  //end the timer
    insertion_sort_time=(end2.tv_sec-begin2.tv_sec)+(end2.tv_nsec-begin2.tv_nsec)/1000000000.0;
                                                     //calculate the time between start and end in seconds

    printf("Array of %d elements sorted %d times.", size, num_of_sortings);       //printing results
    printf("\nAverage number of attempts needed: %.3f", average_attempts);
    printf("\nAverage time needed to sort the array: %.5f seconds\n", average_time);
    printf("Time needed to sort the same array with insertion sort: %.7lf seconds\n\n", insertion_sort_time);
}

int main()
{
    srand(time(NULL));                               //creating the seed for random number generator
    printf("Input the size of the array: ");  
    int size=0;
    scanf("%d", &size);                              //reading the size of the array

    int *array=(int *)malloc(size*sizeof(int));      //allocating memory for the array
    int *array_copy=(int *)malloc(size*sizeof(int)); //allocating memory to copy the array for later use

    printf("\nInput %d elements: ", size);             
    for (int i=0; i<size; i++)
    {
        scanf("%d", &array[i]);                      //reading the array from console
    }
    
    copy(array, array_copy, size);                   //copy the array for later use

    delete_repeating_elements(array_copy, size);     //calling the function to delete repeating elements
    copy(array, array_copy, size);                   //restoring the original array

    merge_sort(array_copy, 0, size-1);               //calling the merge sort function 
    printf("\nArray sorted in descending order by merge sort:");
    print_array(array_copy, size);

    insertion_sort(array_copy, size);                //calling the insertion sort function    
    copy(array, array_copy, size);                   //restoring the original array

    printf("\nInput the size of the array for bogosort simulation: ");  
    size=0;
    int number_of_sortings=0;
    scanf("%d", &size);                              //reading the size of the array for bogosort

    int *array_bogosort=(int *)malloc(size*sizeof(int));      //allocating memory for the array
    int *array_copy_bogosort=(int *)malloc(size*sizeof(int)); //allocating memory to copy the array for later use

    printf("\nInput %d elements: ", size);             
    for (int i=0; i<size; i++)
    {
        scanf("%d", &array_bogosort[i]);             //reading the array from console
    }
    copy(array_bogosort, array_copy_bogosort, size);

    printf("Input the number of simulations for bogosort: ", number_of_sortings);
    scanf("%d", &number_of_sortings);                //reading the number of sortings
    simulation(number_of_sortings, array_bogosort, array_copy_bogosort, size);
                                                     //calling the function for bogosort simulation and time calculation
    free(array);                                     
    free(array_copy);                                //freeing the used memory
    free(array_bogosort);
    free(array_copy_bogosort);
}