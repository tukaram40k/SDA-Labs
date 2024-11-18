#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct customer{
    int account_number;
    char name[50];
    char surname[50];
    char account_type[50];
    char opening_date[50];
    int opening_balance;
    char last_access[50];
};

void print_info(struct customer *customer){
    printf("\nAccount number: %d\n", customer->account_number);
    printf("Name: %s", customer->name);
    printf("Surname: %s", customer->surname);
    printf("Account type: %s", customer->account_type);
    printf("Opening date: %s", customer->opening_date);
    printf("Opening balance: %d\n", customer->opening_balance);
    printf("Last access date: %s", customer->last_access);
}

void scan_number(struct customer *customer){
    printf("Input the account number: ");
    scanf("%d", &customer->account_number);
    getchar();
}

void scan_name(struct customer *customer){
    printf("Input the name: ");
    fgets(customer->name, 50, stdin);
}

void scan_surname(struct customer *customer){
    printf("Input the surname: ");
    fgets(customer->surname, 50, stdin);
}

void scan_type(struct customer *customer){
    printf("Input the account type: ");
    fgets(customer->account_type, 50, stdin);
}

void scan_date(struct customer *customer){
    printf("Input the opening date: ");
    fgets(customer->opening_date, 50, stdin);
}

void scan_balance(struct customer *customer){
    printf("Input the opening balance: ");
    scanf("%d", &customer->opening_balance);
    getchar();
}

void scan_access(struct customer *customer){
    printf("Input the day of last access: ");
    fgets(customer->last_access, 50, stdin);
}

void modify_field(struct customer *customer, int field_num){
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

void modify_data(struct customer *customer){
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
                if (strcmp(str_input, customer->name)!=0){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
            break;
            case 3:
                printf("Input the surname: ");
                fgets(str_input, 50, stdin);
                if (strcmp(str_input, customer->surname)!=0){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
            break;
            case 4:
                printf("Input account type: ");
                fgets(str_input, 50, stdin);
                if (strcmp(str_input, customer->account_type)!=0){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
            break;
            case 5:
                printf("Input opening date: ");
                fgets(str_input, 50, stdin);
                if (strcmp(str_input, customer->opening_date)!=0){
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
                fgets(str_input, 50, stdin);
                if (strcmp(str_input, customer->last_access)!=0){
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
    printf("Modifyed data:\n");
    print_info(customer);
    free(criteria);
}

int main(){
    struct customer first_customer;
    scan_number(&first_customer);
    scan_name(&first_customer);
    scan_surname(&first_customer);
    scan_type(&first_customer);
    scan_date(&first_customer);
    scan_balance(&first_customer);
    scan_access(&first_customer);
    print_info(&first_customer);
    modify_data(&first_customer);
}