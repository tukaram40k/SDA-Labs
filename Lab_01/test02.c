#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void copy(int arr[], int arr_copy[], int size)       
{
    for (int i=0; i<size; i++)
    {
        arr_copy[i]=arr[i];                          
    }
}

void print_array(int arr[], int size)                
{
    printf("\n");
    for (int i=0; i<size; i++)
    {
        printf("%d ", arr[i]);                      
    }
    printf("\n");
}

//function to delete the repeating elements
void delete_repeating_elements(int arr[], int size)  
{                                              
    bool repeated=false;                             
    bool unique=true;                                
    printf("\nArray without the repeated elements: ");
    for (int i=0; i<size; i++)                       
    {
        repeated=false;
        for (int j=0; j<i; j++)
        {
            if (arr[i]==arr[j]) 
            {
                repeated=true;                       
                unique=false;
            }
        }
        if (!repeated) printf("%d ", arr[i]);        
    }
    if (unique) printf("\nThere were no repeating elements in the array.\n");
    printf("\n");
}

//function to merge two arrays
void merge(int arr[], int left, int middle, int right)
{
    int i, j, k;                                     
    int size1=middle-left+1;
    int size2=right-middle;

    int left_arr[size1], right_arr[size2];

    for (i=0; i<size1; i++)                          
    {
        left_arr[i]=arr[left+i];                     
    }
    for (j=0; j<size2; j++)                          
    {
        right_arr[j]=arr[middle+1+j];                
    }

    i=0;
    j=0;
    k=left;
    while (i<size1 && j<size2)
    {
        if (left_arr[i] >= right_arr[j]) 
        {
            arr[k]=left_arr[i];   
            i++;
        } 
        else 
        {
            arr[k]=right_arr[j];   
            j++;
        }
        k++;
    }

    while (i<size1) 
    {
        arr[k]=left_arr[i];
        i++;
        k++;
    }

    while (j<size2)
    {
        arr[k]=right_arr[j];
        j++;
        k++;
    }
}

//function for merge sort
void merge_sort(int arr[], int left, int right)      
{
    if (left<right)                                  
    {
        int middle=(left+right)/2;                   
        merge_sort(arr, left, middle);               
        merge_sort(arr, middle+1, right);
        merge(arr, left, middle, right);
    }
}
//function for insertion 
void insertion_sort(int arr[], int size)             
{
    for(int i=1; i<size; i++)                        
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

bool sorted(int arr[], int size)                     
{
    for (int i=0; i<size-1; i++)
    {
        if (arr[i]>arr[i+1]) return false;           
    }
    return true;                                     
}

int bogosort(int arr[], int size)                    
{
    int attempts_needed=0;
    while (sorted(arr, size)==false)                 
    {
        for (int i=0; i<size; i++)                   
        {
            int temp1=arr[i];                        
            int temp2=rand() % size;                 
            arr[i]=arr[temp2];                       
            arr[temp2]=temp1;
        }
        attempts_needed++;                           
    }

    print_array(arr, size);                          
    printf("Attempts needed: %d\n\n", attempts_needed);
    return attempts_needed;                          
}

void simulation(int num_of_sortings, int arr[], int arr_copy[], int size)
{
    int total_attempts=0;                            
    float average_attempts=0;                        
    float average_time=0;                            
    double insertion_sort_time=0;                    

    struct timespec begin1;                          
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin1);

    for (int i=0; i<num_of_sortings; i++)            
    {
        printf("Sorting N%d:", i+1);
        total_attempts+=bogosort(arr, size);         
        copy(arr_copy, arr, size);                   
    }

    struct timespec end1;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end1);  
    double time=(end1.tv_sec-begin1.tv_sec)+(end1.tv_nsec-begin1.tv_nsec)/1000000000.0;

    average_attempts=(float)total_attempts/num_of_sortings; 
    average_time=time/num_of_sortings; 
              
    struct timespec begin2;                          
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin2);

    insertion_sort(arr, size);
    printf("\n");

    struct timespec end2;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end2);  
    insertion_sort_time=(end2.tv_sec-begin2.tv_sec)+(end2.tv_nsec-begin2.tv_nsec)/1000000000.0;

    printf("Array of %d elements sorted %d times.", size, num_of_sortings);       
    printf("\nAverage number of attempts needed: %.3f", average_attempts);
    printf("\nAverage time needed to sort the array: %.5f seconds\n", average_time);
    printf("Time needed to sort the same array with insertion sort: %.7lf seconds\n\n", insertion_sort_time);
}

int main()
{
    srand(time(NULL));                               
    printf("Input the size of the array: ");  
    int size=0;
    scanf("%d", &size);                              

    int *array=(int *)malloc(size*sizeof(int));      
    int *array_copy=(int *)malloc(size*sizeof(int)); 

    printf("\nInput %d elements: ", size);             
    for (int i=0; i<size; i++)
    {
        scanf("%d", &array[i]);                      
    }
    
    copy(array, array_copy, size);                   

    delete_repeating_elements(array_copy, size);     
    copy(array, array_copy, size);                   
    merge_sort(array_copy, 0, size-1);               
    printf("\nArray sorted in descending order by merge sort:");
    print_array(array_copy, size);

    insertion_sort(array_copy, size);                
    copy(array, array_copy, size);                   

    printf("\nInput the size of the array for bogosort simulation: ");  
    size=0;
    int number_of_sortings=0;
    scanf("%d", &size);                              

    int *array_bogosort=(int *)malloc(size*sizeof(int));      
    int *array_copy_bogosort=(int *)malloc(size*sizeof(int)); 

    printf("\nInput %d elements: ", size);             
    for (int i=0; i<size; i++)
    {
        scanf("%d", &array_bogosort[i]);             
    }
    copy(array_bogosort, array_copy_bogosort, size);

    printf("Input the number of simulations for bogosort: ", number_of_sortings);
    scanf("%d", &number_of_sortings);                
    simulation(number_of_sortings, array_bogosort, array_copy_bogosort, size);
                                                     
    free(array);                                     
    free(array_copy);                                
    free(array_bogosort);
    free(array_copy_bogosort);
}
