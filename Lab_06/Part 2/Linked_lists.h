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

//function to determine the version
int get_version(){
    int version=0;
    printf("\n1. Use single linked list\n2. Use double linked list\n3. Use circular linked list\nInput version: ");
    scanf("%d", &version);
    return version;
}

//below are the same functions as above but modified for double and circular linked lists
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