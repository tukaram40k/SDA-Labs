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

//declare the structures for the single linked list
typedef struct node_str{
    account info;
    struct node_str* next;
} node_t;

typedef node_t* node;

//function to create a new node
node create_node(account acc){
    node n=(node)malloc(sizeof(node_t));
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
    n->next=NULL;
    return n;
}

//function to add a node at the beginning of the list
void add_node(node* head, account acc){
    node n=create_node(acc);
    n->next=*head;
    *head=n;
}

//function to insert a node at a specified position
void insert_node(node* head, account acc, int position){
    if(position==0){
        add_node(head, acc);
        return;
    }
    node n=create_node(acc);
    node current=*head;
    int current_position=0;
    while(current_position<position-1 && current!=NULL){
        current=current->next;
        current_position++;
    }
    n->next=current->next;
    current->next=n;
}

//function to delete a node
void delete_node(node* head, int position){
    node temp=*head;
    if(position==0){
        *head=temp->next;
        return;
    }
    int current_position=0;
    while(temp!=NULL && current_position<position-1){
        temp=temp->next;
        current_position++;
    }
    node deleted=temp->next;
    temp->next=deleted->next;
}

//function to print the list
void print_list(FILE *f, node head){
    node temp=head;
    fprintf(f, "List contents:\n{");
    while (temp!=NULL){
        fprintf(f, "\n    Account number: %d\n", temp->info.account_number);
        fprintf(f, "    Name: %s\n", temp->info.name);
        fprintf(f, "    Surname: %s\n", temp->info.surname);
        fprintf(f, "    Account type: %s\n", temp->info.account_type);
        fprintf(f, "    Opening date: %d.", temp->info.opening_date.day);
        fprintf(f, "%d.", temp->info.opening_date.month);
        fprintf(f, "%d\n", temp->info.opening_date.year);
        fprintf(f, "    Opening balance: %d\n", temp->info.opening_balance);
        fprintf(f, "    Date of the last access: %d.", temp->info.last_access.day);
        fprintf(f, "%d.", temp->info.last_access.month);
        fprintf(f, "%d\n", temp->info.last_access.year);
        temp=temp->next;
    }
    fprintf(f, "}");
}

//function to add data to the list
void fill_list(node* head, account* arr, int num_of_accounts){
    for (int i=0; i<num_of_accounts; i++){
        add_node(head, arr[i]);
    }
}

//function to find an element
void list_element_search(FILE *f, node* head, int criteria){
    node temp=*head;
    int current=0;
    while(temp!=NULL){
        current++;
        if(current==criteria){
            fprintf(f, "Element found on position %d:\n{", criteria);
            fprintf(f, "\n    Account number: %d\n", temp->info.account_number);
            fprintf(f, "    Name: %s\n", temp->info.name);
            fprintf(f, "    Surname: %s\n", temp->info.surname);
            fprintf(f, "    Account type: %s\n", temp->info.account_type);
            fprintf(f, "    Opening date: %d.", temp->info.opening_date.day);
            fprintf(f, "%d.", temp->info.opening_date.month);
            fprintf(f, "%d\n", temp->info.opening_date.year);
            fprintf(f, "    Opening balance: %d\n", temp->info.opening_balance);
            fprintf(f, "    Date of the last access: %d.", temp->info.last_access.day);
            fprintf(f, "%d.", temp->info.last_access.month);
            fprintf(f, "%d\n", temp->info.last_access.year);
            fprintf(f, "}");
            return;
        }
        temp=temp->next;
    }
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

    int num_of_accounts=31;
    account *accounts=(account*)malloc(num_of_accounts*sizeof(account));
    get_data(f1, accounts, num_of_accounts);

    node head=NULL;
    fill_list(&head, accounts, num_of_accounts-1);
    insert_node(&head, accounts[30], 17);
    delete_node(&head, 12);
    list_element_search(f3, &head, 3);
    print_list(f2, head);

    free(accounts);
    fclose(f1);
    fclose(f2);
    fclose(f3);
}