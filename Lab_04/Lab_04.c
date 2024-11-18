#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "version1.h"
#include "version2.h"

int main(){
    int version=0;
    printf("Input version:\n1. Version 1 (using struct)\n2. Version 2 (using union)\n");
    scanf("%d", &version);

    bank_customer first_customer;
    bank_customer second_customer;
    bank_customer third_customer;

    union Info customer1[7];
    union Info customer2[7];
    union Info customer3[7];

    switch(version){
        case 1:
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
            break;
        case 2:
            Get_data(customer2, 1);
            Get_data(customer3, 2);
            scan_Number(customer1);
            scan_Name(customer1);
            scan_Surname(customer1);
            scan_Type(customer1);
            scan_Opening_date(customer1);
            scan_Balance(customer1);
            scan_Last_access_date(customer1);
            print_Info(customer1);
            sort_Data(customer1, customer2, customer3);
            modify_Data(customer1);
            break;
    }
}