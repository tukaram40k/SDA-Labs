#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct date{
    int day;
    int month;
    int year;
} date;

typedef struct bank_account{
    int account_number;
    char name[50];
    char surname[50];
    char account_type[50];
    struct date opening_date;
    int opening_balance;
    struct date last_access;
} account;

/*
I don't want to spend 10 years introducing this info in console every time, 
so I will read it from a file instead
*/

void get_data(FILE *f, account* arr, int num_of_accounts){
    for (int i=0; i<num_of_accounts; i++){
        fscanf(f, "%d,%49[^,],%49[^,],%49[^,],%d,%d,%d,%d,%d,%d,%d",
        &arr[i].account_number,
        arr[i].name,
        arr[i].surname,
        arr[i].account_type,
        &arr[i].opening_date.day,
        &arr[i].opening_date.month,
        &arr[i].opening_date.year,
        &arr[i].opening_balance,
        &arr[i].last_access.day,
        &arr[i].last_access.month,
        &arr[i].last_access.year);
    }
}

void print_data(account* arr, int num_of_accounts){
    printf("Entered data:\n");
    for (int i=0; i<num_of_accounts; i++){
        printf("%d, %s %s, %s, %d.%d.%d, %d, %d.%d.%d\n",
        arr[i].account_number,
        arr[i].name,
        arr[i].surname,
        arr[i].account_type,
        arr[i].opening_date.day,
        arr[i].opening_date.month,
        arr[i].opening_date.year,
        arr[i].opening_balance,
        arr[i].last_access.day,
        arr[i].last_access.month,
        arr[i].last_access.year);
    }
}

void task(account* arr, FILE *f, int num_of_accounts){
    int type1=0, type2=0, type3=0;
    for (int i=0; i<num_of_accounts; i++){
        if (strcmp(arr[i].account_type, "deposit")==0){
            type1++;
        }
        if (strcmp(arr[i].account_type, "payroll")==0){
            type2++;
        }
        if (strcmp(arr[i].account_type, "pensioner bonus program")==0){
            type3++;
        }
    }
    fprintf(f, "Deposit: %d", type1);
    fprintf(f, "\nPayroll: %d", type2);
    fprintf(f, "\nPensioner bonus program: %d", type3);
   
}

int main(){
    FILE *f1, *f2;
    f1=fopen("info.txt", "r");
    f2=fopen("output.txt", "w");
    int num_of_accounts=30;
    account *accounts=(account*)malloc(num_of_accounts*sizeof(account));
    get_data(f1, accounts, num_of_accounts);
    print_data(accounts, num_of_accounts);
    task(accounts, f2, num_of_accounts);
    fclose(f1);
    fclose(f2);
}