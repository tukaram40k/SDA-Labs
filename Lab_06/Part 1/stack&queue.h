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
typedef struct node_s_struct{
    account info;
    struct node_s_struct* previous;
} node_s_t;

typedef node_s_t* node_s;

typedef struct stack_struct{
    node_s first;
} stack_t;

typedef stack_t* stack;

//declare structures for the queue
typedef struct node_q_struct{
    account info;
    struct node_q_struct* next;
} node_q_t;

typedef node_q_t* node_q;

typedef struct queue_struct{
    node_q first;
    node_q last;
} queue_t;

typedef queue_t* queue;

//function to create a new node
node_s create_node_s(account acc){
    node_s n;
    n=(node_s)malloc(sizeof(node_s_t));
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
void add_node_s(stack s, account acc){
    node_s n=create_node_s(acc);
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
node_s_t delete_node_s(stack s){
    node_s temp;
    node_s_t n;
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
    node_s_t n;
    while(s->first!=NULL){
        n=delete_node_s(s);
    }
    free(s);
}

//function to fill the stack with the info about customers
void fill_stack(stack s, account* arr, int num_of_accounts){
    for (int i=0; i<num_of_accounts; i++){
        add_node_s(s, arr[i]);
    }
}

//helper function to print a node's content into a file
void print_node_s(FILE *f, node_s_t n){
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
    node_s_t n;
    fprintf(f, "Stack contents:\n{");
    while(s->first!=NULL){
        n=delete_node_s(s);
        print_node_s(f, n);
    }
    fprintf(f, "\n}");
}

//function to search for an element
void stack_element_search(FILE *f, stack s, int criteria){
    node_s_t n;
    int counter=0;
    while(s->first!=NULL){
        n=delete_node_s(s);
        counter++;
        if (counter==criteria){
            continue;
        }
    }
    fprintf(f, "Element found on position %d:\n{", criteria);
    print_node_s(f, n);
    fprintf(f, "\n}");
}

//function to create a new node
node_q create_node_q(account acc){
    node_q n;
    n=(node_q)malloc(sizeof(node_q_t));
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

//function to add a node_q to the queue
void add_node_q(queue q, account acc){
    node_q n=create_node_q(acc);
    if(q->first==NULL){
        q->first=n;
        q->last=n;
    }
    else{
        q->last->next=n;
        q->last=q->last->next;
    }
}

//function to create a new queue
queue create_queue(){
    queue q;
    q=(queue)malloc(sizeof(queue_t));
    q->first=NULL;
    q->last=NULL;
    return q;
}

//function to delete a node_q
node_q_t delete_node_q(queue q){
    node_q temp;
    node_q_t n;
    if (q->first!=NULL){
        temp=q->first;
        q->first=q->first->next;
        n=*temp;
        free(temp);
    }
    return n;
}

//function to destroy a queue
void kill_queue(queue q){
    node_q_t n;
    while(q->first!=NULL){
        n=delete_node_q(q);
    }
    free(q);
}

//function to fill the queue with the info about customers
void fill_queue(queue q, account* arr, int num_of_accounts){
    for (int i=0; i<num_of_accounts; i++){
        add_node_q(q, arr[i]);
    }
}

//helper function to print a node_q's content into a file
void print_node_q(FILE *f, node_q_t n){
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

//function to extract queue contents into a file
void extract_queue_data(FILE *f, queue q){
    node_q_t n;
    fprintf(f, "queue contents:\n{");
    while(q->first!=NULL){
        n=delete_node_q(q);
        print_node_q(f, n);
    }
    fprintf(f, "\n}");
}

//function to search for an element
void queue_element_search(FILE *f, queue q, int criteria){
    node_q_t n;
    int counter=0;
    while(q->first!=NULL){
        n=delete_node_q(q);
        counter++;
        if (counter==criteria){
            continue;
        }
    }
    fprintf(f, "Element found on position %d:\n{", criteria);
    print_node_q(f, n);
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

//function to determine the version
int get_version(){
    int version=0;
    printf("\n1. Use dynamic stack\n2. Use dynamic queue\nInput version: ");
    scanf("%d", &version);
    return version;
}