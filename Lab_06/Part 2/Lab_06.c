#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Linked_lists.h"

int main(){
    FILE *f1, *f2, *f3;
    char path[50];
    printf("Input output file directory: ");
    scanf("%s", path);

    f1=fopen("info.txt", "r");
    f2=fopen(path, "w");
    f3=fopen("search.txt", "w");

    int num_of_accounts=31;
    int version=get_version();

    account *accounts=(account*)malloc(num_of_accounts*sizeof(account));
    get_data(f1, accounts, num_of_accounts);

    node single_head=NULL;
    double_node double_head=NULL;
    circular_node circular_head=NULL;

    switch(version){
        case 1:
            fill_list(&single_head, accounts, num_of_accounts-1);
            insert_node(&single_head, accounts[30], 12);
            delete_node(&single_head, 5);
            list_element_search(f3, &single_head, 3);
            print_list(f2, single_head);
            break;
        case 2:
            double_fill_list(&double_head, accounts, num_of_accounts-1);
            insert_double_node(&double_head, accounts[30], 12);
            delete_double_node(&double_head, 5);
            double_list_element_search(f3, double_head, 3);
            double_print_list(f2, double_head);
            break;
        case 3:
            circular_fill_list(&circular_head, accounts, num_of_accounts-1);
            insert_circular_node(&circular_head, accounts[30], 12);
            delete_circular_node(&circular_head, 5);
            circular_list_element_search(f3, circular_head, 3);
            circular_print_list(f2, circular_head);
            break;
    }

    free(accounts);
    fclose(f1);
    fclose(f2);
    fclose(f3);
}