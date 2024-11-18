#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack&queue.h"

int main(){
    FILE *f1, *f2, *f3;
    /*
    char path[50];
    printf("Input output file directory: ");
    scanf("%s", path);*/

    f1=fopen("info.txt", "r");
    f2=fopen("output.txt", "w");
    f3=fopen("search.txt", "w");

    int num_of_accounts=30;
    int version=get_version();

    account *accounts=(account*)malloc(num_of_accounts*sizeof(account));
    get_data(f1, accounts, num_of_accounts);

    if (version==1){
        stack registry=create_stack();
        fill_stack(registry, accounts, num_of_accounts);
        stack_element_search(f3, registry, 7);
        extract_stack_data(f2, registry);
        fill_stack(registry, accounts, num_of_accounts);
        extract_stack_data(f2, registry);
        kill_stack(registry);
    }
    else{
        queue registry=create_queue();
        fill_queue(registry, accounts, num_of_accounts);
        queue_element_search(f3, registry, 13);
        fill_queue(registry, accounts, num_of_accounts);
        extract_queue_data(f2, registry);
        kill_queue(registry);
    }
    
    free(accounts);
    fclose(f1);
    fclose(f2);
    fclose(f3);
}