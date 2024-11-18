#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct date{
    int day;
    int month;
    int year;
};

typedef struct customer{
    int account_number;
    char name[50];
    char surname[50];
    char account_type[50];
    struct date opening_date;
    int opening_balance;
    struct date last_access;
} bank_customer;

void print_info(bank_customer *customer){
    printf("\nAccount number: %d", customer->account_number);
    printf("\nName: %s", customer->name);
    printf("\nSurname: %s", customer->surname);
    printf("\nAccount type: %s", customer->account_type);
    printf("\nOpening date: %d.%d.%d", customer->opening_date.day, customer->opening_date.month, customer->opening_date.year);
    printf("\nOpening balance: %d", customer->opening_balance);
    printf("\nLast access date: %d.%d.%d\n\n", customer->last_access.day, customer->last_access.month, customer->last_access.year);
}

void scan_number(bank_customer *customer){
    printf("Input the account number: ");
    scanf("%d", &customer->account_number);
    getchar();
}

void scan_name(bank_customer *customer){
    printf("Input the name: ");
    fgets(customer->name, 50, stdin);
    customer->name[strcspn(customer->name, "\n")] = '\0';
}

void scan_surname(bank_customer *customer){
    printf("Input the surname: ");
    fgets(customer->surname, 50, stdin);
    customer->surname[strcspn(customer->surname, "\n")] = '\0';
}

void scan_type(bank_customer *customer){
    printf("Input the account type: ");
    fgets(customer->account_type, 50, stdin);
    customer->account_type[strcspn(customer->account_type, "\n")] = '\0';
}

void scan_date(bank_customer *customer){
    int day=0, month=0, year=0;
    printf("Input the opening date:\n");
    printf("Input day: ");
    scanf("%d", &day);
    printf("Input month: ");
    scanf("%d", &month);
    printf("Input year: ");
    scanf("%d", &year);
    customer->opening_date.day=day;
    customer->opening_date.month=month;
    customer->opening_date.year=year;
    getchar();
}

void scan_balance(bank_customer *customer){
    printf("Input the opening balance: ");
    scanf("%d", &customer->opening_balance);
    getchar();
}

void scan_access(bank_customer *customer){
    printf("Input the day of last access:\n");
    int day=0, month=0, year=0;
    printf("Input day: ");
    scanf("%d", &day);
    printf("Input month: ");
    scanf("%d", &month);
    printf("Input year: ");
    scanf("%d", &year);
    customer->last_access.day=day;
    customer->last_access.month=month;
    customer->last_access.year=year;
    getchar();
}

void compare_date(bank_customer *customer1, bank_customer *customer2, bank_customer *customer3, bool ascending, int days[], int months[], int years[]){
    if (ascending){
        printf("%s, %s, %s\n", customer3->name, customer1->name, customer2->name);
    }
    else{
        printf("%s, %s, %s\n", customer2->name, customer1->name, customer3->name);
    }
}

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

int partition(int arr[], int left_index, int right_index, bool ascending){
    int pivot=arr[right_index];
    int i=left_index-1;
    for (int j=left_index; j<=right_index-1; j++){
        if ((ascending && arr[j]<pivot) || (!ascending && arr[j]>pivot)){
            i++;
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }
    int temp=arr[i+1];
    arr[i+1]=arr[right_index];
    arr[right_index]=temp;
    return (i+1);
}

void quicksort(int arr[], int left_index, int right_index, bool ascending){
    if (left_index<right_index){
        int pivot=partition(arr, left_index, right_index, ascending);
        quicksort(arr, left_index, pivot-1, ascending);
        quicksort(arr, pivot+1, right_index, ascending);
    }
}

void sort_data(bank_customer *customer1, bank_customer *customer2, bank_customer *customer3){
    int days[3];
    int months[3];
    int years[4];
    days[0]=customer1->opening_date.day;
    days[1]=customer2->opening_date.day;
    days[2]=customer3->opening_date.day;
    months[0]=customer1->opening_date.month;
    months[1]=customer2->opening_date.month;
    months[2]=customer3->opening_date.month;
    years[0]=customer1->opening_date.year;
    years[1]=customer2->opening_date.year;
    years[2]=customer3->opening_date.year;
    printf("\nSorted by opening date in ascending order:\n");
    quicksort(days, 0, 2, true);
    quicksort(months, 0, 2, true);
    quicksort(years, 0, 2, true);
    compare_date(customer1, customer2, customer3, true, days, months, years);
    printf("\nSorted by opening date in descending order:\n");
    merge_sort(days, 0, 2, false);
    merge_sort(months, 0, 2, false);
    merge_sort(years, 0, 2, false);
    compare_date(customer1, customer2, customer3, true, days, months, years);
}

void modify_field(bank_customer *customer, int field_num){
    getchar();
    switch (field_num){
        case 1: scan_number(customer);
            break;
        case 2: scan_name(customer);
            break;
        case 3: scan_surname(customer);
            break;
        case 4: scan_type(customer);
            break;
        case 5: scan_date(customer);
            break;
        case 6: scan_balance(customer);
            break;
        case 7: scan_access(customer);
            break;
    }
}

void modify_data(bank_customer *customer){
    int num=0;
    printf("\nInput the number of criteria for modification: ");
    scanf("%d", &num);
    int *criteria=(int*)malloc(num*sizeof(int));
    printf("Select the criteria:\n");
    printf("1. Account number\n2. Name\n3. Surname\n4. Account type\n5. Opening date\n6. Opening balance\n7. Last access\n");
    for (int i=0; i<num; i++){
        scanf("%d", &criteria[i]);
    }
    getchar();
    for (int i=0; i<num; i++){
        int day=0, month=0, year=0;
        int int_input=0;
        char str_input[50];
        switch (criteria[i]){
            case 1:
                printf("Input account number: ");
                scanf("%d", &int_input);
                getchar();
                if (int_input!=customer->account_number){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
            case 2:
                printf("Input the name: ");
                fgets(str_input, 50, stdin);
                str_input[strcspn(str_input, "\n")] = '\0';
                if (strcmp(str_input, customer->name)!=0){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
            case 3:
                printf("Input the surname: ");
                fgets(str_input, 50, stdin);
                str_input[strcspn(str_input, "\n")] = '\0';
                if (strcmp(str_input, customer->surname)!=0){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
            case 4:
                printf("Input account type: ");
                fgets(str_input, 50, stdin);
                str_input[strcspn(str_input, "\n")] = '\0';
                if (strcmp(str_input, customer->account_type)!=0){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
            case 5:
                printf("Input the opening date:\n");
                day=0; 
                month=0; 
                year=0;
                printf("Input day: ");
                scanf("%d", &day);
                printf("Input month: ");
                scanf("%d", &month);
                printf("Input year: ");
                scanf("%d", &year);
                if ((customer->opening_date.day!=day)||(customer->opening_date.month!=month)||(customer->opening_date.year!=year)){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
            case 6:
                printf("Input opening balance: ");
                scanf("%d", &int_input);
                getchar();
                if (int_input!=customer->opening_balance){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
            case 7:
                printf("Input last access date: ");
                day=0; 
                month=0; 
                year=0;
                printf("Input day: ");
                scanf("%d", &day);
                printf("Input month: ");
                scanf("%d", &month);
                printf("Input year: ");
                scanf("%d", &year);
                if ((customer->last_access.day!=day)||(customer->last_access.month!=month)||(customer->last_access.year!=year)){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
        }
    }    
    printf("Select the field to modify:\n");
    printf("1. Account number\n2. Name\n3. Surname\n4. Account type\n5. Opening date\n6. Opening balance\n7. Last access\n");
    int field;
    scanf("%d", &field);
    modify_field(customer, field);
    printf("Modified data:\n");
    print_info(customer);
    free(criteria);
}

void get_data(bank_customer *customer, int num){
    if (num==1){
        customer->account_number=45;
        strcpy(customer->name, "Mihail");
        strcpy(customer->surname, "Petrov");
        strcpy(customer->account_type, "type 1");
        customer->opening_date.day=5;
        customer->opening_date.month=7;
        customer->opening_date.year=1998;
        customer->opening_balance=5000;
        customer->last_access.day=24;
        customer->last_access.month=11;
        customer->last_access.year=2023;
    }
    else{
        customer->account_number=52;
        strcpy(customer->name, "Alex");
        strcpy(customer->surname, "Parker");
        strcpy(customer->account_type, "type 2");
        customer->opening_date.day=24;
        customer->opening_date.month=3;
        customer->opening_date.year=2005;
        customer->opening_balance=10000;
        customer->last_access.day=8;
        customer->last_access.month=6;
        customer->last_access.year=2021;
    }
    print_info(customer);
}

int main(){
    bank_customer first_customer;
    bank_customer second_customer;
    bank_customer third_customer;

    get_data(&second_customer, 1);
    get_data(&third_customer, 2);
    scan_number(&first_customer);
    scan_name(&first_customer);
    scan_surname(&first_customer);
    scan_type(&first_customer);
    scan_date(&first_customer);
    scan_balance(&first_customer);
    scan_access(&first_customer);
    print_info(&first_customer);
    sort_data(&first_customer, &second_customer, &third_customer);
    modify_data(&first_customer);
}
