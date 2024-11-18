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
    date opening_date;
    int opening_balance;
    date last_access;
} account;

typedef struct double_node_str {
    account info;
    struct double_node_str* next;
    struct double_node_str* prev;
} double_node_t;

typedef double_node_t* double_node;

double_node create_double_node(account acc){
    double_node n=(double_node)malloc(sizeof(double_node_t));
    if (n!=NULL){
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
        n->prev=NULL;
    }
    return n;
}

void add_double_node(double_node* head, account acc){
    double_node n=create_double_node(acc);
    if (*head==NULL){
        *head=n;
    } else {
        n->next=*head;
        (*head)->prev=n;
        *head=n;
    }
}

void insert_double_node(double_node* head, account acc, int position){
    double_node new_double_node=create_double_node(acc);
    double_node current=*head;
    int current_position=0;
    while (current_position<position-1 && current!=NULL){
        current=current->next;
        current_position++;
    }
    if (current==NULL){
        free(new_double_node);
        return;
    }
    new_double_node->next=current->next;
    if (current->next!=NULL){
        current->next->prev=new_double_node;
    }
    new_double_node->prev=current;
    current->next=new_double_node;
}

void delete_double_node(double_node* head, int position){
    if (*head==NULL){
        return;
    }
    if (position <= 0){
        double_node temp=*head;
        *head=(*head)->next;
        if (*head!=NULL){
            (*head)->prev=NULL;
        }
        free(temp);
        return;
    }
    double_node current=*head;
    int current_position=0;
    while (current_position<position && current!=NULL){
        current=current->next;
        current_position++;
    }
    if (current==NULL){
        return;
    }
    if (current->prev!=NULL){
        current->prev->next=current->next;
    }
    if (current->next!=NULL){
        current->next->prev=current->prev;
    }
}

void double_print_list(FILE* f, double_node head){
    fprintf(f, "List contents:\n{");
    double_node temp=head;
    while (temp!=NULL){
        fprintf(f, "\n    Account number: %d\n", temp->info.account_number);
        fprintf(f, "    Name: %s\n", temp->info.name);
        fprintf(f, "    Surname: %s\n", temp->info.surname);
        fprintf(f, "    Account type: %s\n", temp->info.account_type);
        fprintf(f, "    Opening date: %d.%d.%d\n", temp->info.opening_date.day, temp->info.opening_date.month, temp->info.opening_date.year);
        fprintf(f, "    Opening balance: %d\n", temp->info.opening_balance);
        fprintf(f, "    Date of the last access: %d.%d.%d\n", temp->info.last_access.day, temp->info.last_access.month, temp->info.last_access.year);
        temp=temp->next;
    }
    fprintf(f, "}");
}

void double_fill_list(double_node* head, account* arr, int num_of_accounts){
    for (int i=0; i<num_of_accounts; i++){
        add_double_node(head, arr[i]);
    }
}

void double_list_element_search(FILE* f, double_node head, int criteria){
    int current=0;
    double_node temp=head;
    while (temp!=NULL){
        current++;
        if (current==criteria){
            fprintf(f, "Element found on position %d:\n{", criteria);
            fprintf(f, "\n    Account number: %d\n", temp->info.account_number);
            fprintf(f, "    Name: %s\n", temp->info.name);
            fprintf(f, "    Surname: %s\n", temp->info.surname);
            fprintf(f, "    Account type: %s\n", temp->info.account_type);
            fprintf(f, "    Opening date: %d.%d.%d\n", temp->info.opening_date.day, temp->info.opening_date.month, temp->info.opening_date.year);
            fprintf(f, "    Opening balance: %d\n", temp->info.opening_balance);
            fprintf(f, "    Date of the last access: %d.%d.%d\n", temp->info.last_access.day, temp->info.last_access.month, temp->info.last_access.year);
            fprintf(f, "}");
            return;
        }
        temp=temp->next;
    }
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

    double_node head=NULL;
    double_fill_list(&head, accounts, num_of_accounts-1);
    insert_double_node(&head, accounts[30], 12);
    delete_double_node(&head, 5);
    double_list_element_search(f3, head, 3);
    double_print_list(f2, head);

    free(accounts);
    fclose(f1);
    fclose(f2);
    fclose(f3);
}
