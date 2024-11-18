#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//declare the structures for bank accounts
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

//declare structures for the stack
typedef struct node_struct{
    account info;
    struct node_struct* previous;
} node_t;

typedef node_t* node;

typedef struct stack_struct{
    node first;
} stack_t;

typedef stack_t* stack;

//function to create a new node
node create_node(account acc){
    node n;
    n=(node)malloc(sizeof(node_t));
    n->info.account_number=acc.account_number;
    n->info.opening_balance=acc.opening_balance;
    strcpy(n->info.account_type, acc.account_type);
    strcpy(n->info.name, acc.name);
    strcpy(n->info.surname, acc.surname);
    n->info.last_access.day=acc.last_access.day;
    n->info.last_access.month=acc.last_access.month;
    n->info.last_access.year=acc.last_access.year;
    n->info.opening_date.day=acc.opening_date.day;
    n->info.opening_date.month=acc.opening_date.month;
    n->info.opening_date.year=acc.opening_date.year;
    n->previous=NULL;
    return n;
}

//function to add a node to the stack
void add_node(stack s, account acc){
    node n=create_node(acc);
    n->previous=s->first;
    s->first=n;
}

//function to create a new stack
stack create_stack(){
    stack s;
    s=(stack)malloc(sizeof(stack_t));
    s->first=NULL;
    return s;
}

//function to delete a node
node_t delete_node(stack s){
    node temp;
    node_t n;
    if (s->first!=NULL){
        temp=s->first;
        s->first=s->first->previous;
        n=*temp;
        free(temp);
    }
    return n;
}

//function to destroy a stack
void kill_stack(stack s){
    node_t n;
    while(s->first!=NULL){
        n=delete_node(s);
    }
    free(s);
}

//function to fill the stack with the info about customers
void fill_stack(stack s, account* arr, int num_of_accounts){
    for (int i=0; i<num_of_accounts; i++){
        add_node(s, arr[i]);
    }
}

//helper function to print a node's content into a file
void print_node(FILE *f, node_t n){
    fprintf(f, "\n");
    fprintf(f, "    Account number: %d\n", n.info.account_number);
    fprintf(f, "    Name: %s\n", n.info.name);
    fprintf(f, "    Surname: %s\n", n.info.surname);
    fprintf(f, "    Account type: %s\n", n.info.account_type);
    fprintf(f, "    Opening date: %d.", n.info.opening_date.day);
    fprintf(f, "%d.", n.info.opening_date.month);
    fprintf(f, "%d\n", n.info.opening_date.year);
    fprintf(f, "    Opening balance: %d\n", n.info.opening_balance);
    fprintf(f, "    Date of the last access: %d.", n.info.last_access.day);
    fprintf(f, "%d.", n.info.last_access.month);
    fprintf(f, "%d\n", n.info.last_access.year);
}

//function to extract stack contents into a file
void extract_stack_data(FILE *f, stack s){
    node_t n;
    fprintf(f, "Stack contents:\n{");
    while(s->first!=NULL){
        n=delete_node(s);
        print_node(f, n);
    }
    fprintf(f, "\n}");
}

//function to search for an element
void element_search(FILE *f, stack s, int criteria){
    node_t n;
    int counter=0;
    while(s->first!=NULL){
        n=delete_node(s);
        counter++;
        if (counter==criteria){
            continue;
        }
    }
    fprintf(f, "Element found on position %d:\n{", criteria);
    print_node(f, n);
    fprintf(f, "\n}");
}

//function to read the customer info from a file
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

int main(){
    FILE *f1, *f2, *f3;
    f1=fopen("info.txt", "r");
    f2=fopen("output.txt", "w");
    f3=fopen("search.txt", "w");

    int num_of_accounts=30;

    account *accounts=(account*)malloc(num_of_accounts*sizeof(account));
    stack registry=create_stack();

    get_data(f1, accounts, num_of_accounts);
    fill_stack(registry, accounts, num_of_accounts);
    element_search(f3, registry, 7);
    extract_stack_data(f2, registry);
    fill_stack(registry, accounts, num_of_accounts);
    extract_stack_data(f2, registry);
    kill_stack(registry);
    
    fclose(f1);
    fclose(f2);
    fclose(f3);
}