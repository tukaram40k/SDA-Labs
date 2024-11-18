#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "version1.h"

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