#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct date {
    int day;
    int month;
    int year;
} date;

typedef struct bank_account {
    int account_number;
    char name[50];
    char surname[50];
    char account_type[50];
    struct date opening_date;
    int opening_balance;
    struct date last_access;
} account;

typedef struct circular_node_str {
    account info;
    struct circular_node_str* next;
} circular_node_t;

typedef circular_node_t* circular_node;

circular_node create_circular_node(account acc){
    circular_node n=(circular_node)malloc(sizeof(circular_node_t));
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

void add_circular_node(circular_node* head, account acc){
    circular_node new_circular_node=create_circular_node(acc);
    if (*head==NULL){
        *head=new_circular_node;
        (*head)->next=*head;
    } else {
        new_circular_node->next=(*head)->next;
        (*head)->next=new_circular_node;
    }
}

void insert_circular_node(circular_node* head, account acc, int position){
    if (position==0){
        add_circular_node(head, acc);
        return;
    }
    circular_node current=*head;
    int current_position=0;
    while (current_position<position-1 && current->next!=*head){
        current=current->next;
        current_position++;
    }
    circular_node new_circular_node=create_circular_node(acc);
    new_circular_node->next=current->next;
    current->next=new_circular_node;
}

void delete_circular_node(circular_node* head, int position){
    if (*head==NULL){
        return;
    }
    circular_node temp=*head;
    if (position==0){
        circular_node last_circular_node=*head;
        while (last_circular_node->next!=*head){
            last_circular_node=last_circular_node->next;
        }
        if (*head==(*head)->next){
            *head=NULL;
        } else {
            *head=(*head)->next;
            last_circular_node->next=*head;
        }
        return;
    }
    int current_position=0;
    while (temp->next!=*head && current_position<position-1){
        temp=temp->next;
        current_position++;
    }
    if (temp->next==*head){
        return;
    }
    circular_node deleted=temp->next;
    temp->next=deleted->next;
    free(deleted);
}

void circular_print_list(FILE* f, circular_node head){
    circular_node temp=head;
    fprintf(f, "List contents:\n{");
    do {
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
    } while (temp!=head);
    fprintf(f, "}\n");
}

void circular_fill_list(circular_node* head, account* arr, int num_of_accounts){
    for (int i=0; i<num_of_accounts; i++){
        add_circular_node(head, arr[i]);
    }
}

void circular_list_element_search(FILE* f, circular_node head, int criteria){
    if (head==NULL){
        fprintf(f, "List is empty.\n");
        return;
    }
    circular_node temp=head;
    int current=0;
    do {
        current++;
        if (current==criteria){
            fprintf(f, "Element found at position %d:\n{", criteria);
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
    } while (temp!=head);
    fprintf(f, "Element not found.\n");
}

void get_data(FILE* f, account* arr, int num_of_accounts){
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
    account* accounts=(account*)malloc(num_of_accounts*sizeof(account));
    get_data(f1, accounts, num_of_accounts);

    circular_node head=NULL;
    circular_fill_list(&head, accounts, num_of_accounts-1);
    insert_circular_node(&head, accounts[30], 12);
    delete_circular_node(&head, 5);
    circular_list_element_search(f3, head, 3);
    circular_print_list(f2, head);

    free(accounts);
    fclose(f1);
    fclose(f2);
    fclose(f3);
}
