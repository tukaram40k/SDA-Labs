#ifndef TREES_H
#define TREES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Structures for the customer's data
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

// AVL tree structures
typedef struct AVLNode {
    account data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// AVL tree function prototypes
AVLNode* avl_create();
AVLNode* avl_insert(AVLNode* node, account data);
AVLNode* avl_search(AVLNode* root, int account_number);
AVLNode* avl_delete(AVLNode* root, int account_number);
void avl_print(FILE *f, AVLNode* root);
void avl_free(AVLNode* root);
void avl_task(AVLNode* root, int delete_num, int search_num);

// B tree structures
typedef struct BTreeNode {
    account *accounts;
    int t;
    struct BTreeNode **C;
    int n;
    bool leaf;
} BTreeNode;

typedef struct BTree {
    BTreeNode *root;
    int t;
} BTree;

// B tree function prototypes
BTree* btree_create(int t);
void btree_insert(BTree *tree, account k);
BTreeNode* btree_search(BTreeNode* root, int account_number);
void btree_delete(BTree *tree, int account_number);
void btree_print(FILE *f, BTreeNode* root);
void btree_free(BTreeNode* root);
void btree_task(BTree *tree, int delete_num, int search_num);

// B+ tree structures
typedef struct BPlusTreeNode {
    account *accounts;
    struct BPlusTreeNode **children;
    int n;
    bool is_leaf;
    struct BPlusTreeNode *next;
} BPlusTreeNode;

typedef struct BPlusTree {
    BPlusTreeNode *root;
    int t;
} BPlusTree;

// B+ tree function prototypes
BPlusTree* bplustree_create(int t);
void bplustree_insert(BPlusTree *tree, account k);
BPlusTreeNode* bplustree_search(BPlusTreeNode* root, int account_number);
void bplustree_delete(BPlusTree *tree, int account_number);
void bplustree_print(FILE *f, BPlusTreeNode* root);
void bplustree_free(BPlusTreeNode* root);
void bplustree_task(BPlusTree *tree, int delete_num, int search_num);

// Function to fill the structures with data
void get_data(FILE *f, account* arr, int num_of_accounts) {
    for (int i = 0; i < num_of_accounts; i++) {
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

// AVL tree functions

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

AVLNode* newAVLNode(account data) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode* rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVLNode *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

AVLNode* avl_insert(AVLNode* node, account data) {
    if (node == NULL)
        return newAVLNode(data);

    if (data.account_number < node->data.account_number)
        node->left = avl_insert(node->left, data);
    else if (data.account_number > node->data.account_number)
        node->right = avl_insert(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data.account_number < node->left->data.account_number)
        return rightRotate(node);

    if (balance < -1 && data.account_number > node->right->data.account_number)
        return leftRotate(node);

    if (balance > 1 && data.account_number > node->left->data.account_number) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data.account_number < node->right->data.account_number) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

AVLNode* avl_delete(AVLNode* root, int account_number) {
    if (root == NULL)
        return root;

    if (account_number < root->data.account_number)
        root->left = avl_delete(root->left, account_number);
    else if (account_number > root->data.account_number)
        root->right = avl_delete(root->right, account_number);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            AVLNode* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = avl_delete(root->right, temp->data.account_number);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

AVLNode* avl_search(AVLNode* root, int account_number) {
    if (root == NULL || root->data.account_number == account_number)
        return root;

    if (root->data.account_number < account_number)
        return avl_search(root->right, account_number);

    return avl_search(root->left, account_number);
}

void avl_print(FILE *f, AVLNode* root) {
    if (root != NULL) {
        avl_print(f, root->left);
        fprintf(f, "\n");
        fprintf(f, "    Account number: %d\n", root->data.account_number);
        fprintf(f, "    Name: %s\n", root->data.name);
        fprintf(f, "    Surname: %s\n", root->data.surname);
        fprintf(f, "    Account type: %s\n", root->data.account_type);
        fprintf(f, "    Opening date: %d.", root->data.opening_date.day);
        fprintf(f, "%d.", root->data.opening_date.month);
        fprintf(f, "%d\n", root->data.opening_date.year);
        fprintf(f, "    Opening balance: %d\n", root->data.opening_balance);
        fprintf(f, "    Date of the last access: %d.", root->data.last_access.day);
        fprintf(f, "%d.", root->data.last_access.month);
        fprintf(f, "%d\n", root->data.last_access.year);
        avl_print(f, root->right);
    }
}

void avl_free(AVLNode* root) {
    if (root != NULL) {
        avl_free(root->left);
        avl_free(root->right);
        free(root);
    }
}

void avl_task(AVLNode* root, int delete_num, int search_num) {
    avl_search(root, search_num);
    avl_delete(root, delete_num);
}

// B Tree functions

BTreeNode* newBTreeNode(int t, bool leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->t = t;
    node->leaf = leaf;
    node->accounts = (account*)malloc((2*t-1) * sizeof(account));
    node->C = (BTreeNode**)malloc(2*t * sizeof(BTreeNode*));
    node->n = 0;
    return node;
}

BTree* btree_create(int t) {
    BTree* tree = (BTree*)malloc(sizeof(BTree));
    tree->t = t;
    tree->root = newBTreeNode(t, true);
    return tree;
}

void btree_split_child(BTreeNode* x, int i) {
    int t = x->t;
    BTreeNode* y = x->C[i];
    BTreeNode* z = newBTreeNode(t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t-1; j++)
        z->accounts[j] = y->accounts[j+t];
    
    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }
    
    y->n = t - 1;
    
    for (int j = x->n; j >= i+1; j--)
        x->C[j+1] = x->C[j];
    
    x->C[i+1] = z;
    
    for (int j = x->n-1; j >= i; j--)
        x->accounts[j+1] = x->accounts[j];
    
    x->accounts[i] = y->accounts[t-1];
    x->n++;
}

void btree_insert_nonfull(BTreeNode* x, account k) {
    int i = x->n - 1;
    
    if (x->leaf) {
        while (i >= 0 && k.account_number < x->accounts[i].account_number) {
            x->accounts[i+1] = x->accounts[i];
            i--;
        }
        x->accounts[i+1] = k;
        x->n++;
    } else {
        while (i >= 0 && k.account_number < x->accounts[i].account_number)
            i--;
        i++;
        if (x->C[i]->n == 2*x->t - 1) {
            btree_split_child(x, i);
            if (k.account_number > x->accounts[i].account_number)
                i++;
        }
        btree_insert_nonfull(x->C[i], k);
    }
}

void btree_insert(BTree *tree, account k) {
    BTreeNode* r = tree->root;
    if (r->n == 2*tree->t - 1) {
        BTreeNode* s = newBTreeNode(tree->t, false);
        s->C[0] = r;
        btree_split_child(s, 0);
        int i = 0;
        if (s->accounts[0].account_number < k.account_number)
            i++;
        btree_insert_nonfull(s->C[i], k);
        tree->root = s;
    } else {
        btree_insert_nonfull(r, k);
    }
}

BTreeNode* btree_search(BTreeNode* root, int account_number) {
    int i = 0;
    while (i < root->n && account_number > root->accounts[i].account_number)
        i++;
    if (i < root->n && account_number == root->accounts[i].account_number)
        return root;
    if (root->leaf)
        return NULL;
    return btree_search(root->C[i], account_number);
}

void btree_print(FILE *f, BTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->leaf)
                btree_print(f, root->C[i]);
            fprintf(f, "\n");
            fprintf(f, "    Account number: %d\n", root->accounts[i].account_number);
            fprintf(f, "    Name: %s\n", root->accounts[i].name);
            fprintf(f, "    Surname: %s\n", root->accounts[i].surname);
            fprintf(f, "    Account type: %s\n", root->accounts[i].account_type);
            fprintf(f, "    Opening date: %d.", root->accounts[i].opening_date.day);
            fprintf(f, "%d.", root->accounts[i].opening_date.month);
            fprintf(f, "%d\n", root->accounts[i].opening_date.year);
            fprintf(f, "    Opening balance: %d\n", root->accounts[i].opening_balance);
            fprintf(f, "    Date of the last access: %d.", root->accounts[i].last_access.day);
            fprintf(f, "%d.", root->accounts[i].last_access.month);
            fprintf(f, "%d\n", root->accounts[i].last_access.year);
        }
        if (!root->leaf)
            btree_print(f, root->C[i]);
    }
}

void btree_free(BTreeNode* root) {
    if (root != NULL) {
        if (!root->leaf) {
            for (int i = 0; i <= root->n; i++)
                btree_free(root->C[i]);
        }
        free(root->accounts);
        free(root->C);
        free(root);
    }
}

void btree_task(BTree *tree, int delete_num, int search_num) {
    btree_search(tree->root, search_num);
    btree_delete(tree, delete_num);
}

// B+ Tree functions

BPlusTreeNode* newBPlusTreeNode(int t, bool is_leaf) {
    BPlusTreeNode* node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    node->n = t;
    node->is_leaf = is_leaf;
    node->accounts = (account*)malloc((2*t-1) * sizeof(account));
    node->children = (BPlusTreeNode**)malloc(2*t * sizeof(BPlusTreeNode*));
    node->n = 0;
    node->next = NULL;
    return node;
}

BPlusTree* bplustree_create(int t) {
    BPlusTree* tree = (BPlusTree*)malloc(sizeof(BPlusTree));
    tree->t = t;
    tree->root = newBPlusTreeNode(t, true);
    return tree;
}

void bplustree_split_child(BPlusTreeNode* x, int i) {
    int t = x->n;
    BPlusTreeNode* y = x->children[i];
    BPlusTreeNode* z = newBPlusTreeNode(t, y->is_leaf);
    z->n = t - 1;

    for (int j = 0; j < t-1; j++)
        z->accounts[j] = y->accounts[j+t];
    
    if (!y->is_leaf) {
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j+t];
    } else {
        z->next = y->next;
        y->next = z;
    }
    
    y->n = t - 1;
    
    for (int j = x->n; j >= i+1; j--)
        x->children[j+1] = x->children[j];
    
    x->children[i+1] = z;
    
    for (int j = x->n-1; j >= i; j--)
        x->accounts[j+1] = x->accounts[j];
    
    x->accounts[i] = y->accounts[t-1];
    x->n++;
}

void bplustree_insert_nonfull(BPlusTreeNode* x, account k) {
    int i = x->n - 1;
    
    if (x->is_leaf) {
        while (i >= 0 && k.account_number < x->accounts[i].account_number) {
            x->accounts[i+1] = x->accounts[i];
            i--;
        }
        x->accounts[i+1] = k;
        x->n++;
    } else {
        while (i >= 0 && k.account_number < x->accounts[i].account_number)
            i--;
        i++;
        if (x->children[i]->n == 2*x->n - 1) {
            bplustree_split_child(x, i);
            if (k.account_number > x->accounts[i].account_number)
                i++;
        }
        bplustree_insert_nonfull(x->children[i], k);
    }
}

void bplustree_insert(BPlusTree *tree, account k) {
    BPlusTreeNode* r = tree->root;
    if (r->n == 2*tree->t - 1) {
        BPlusTreeNode* s = newBPlusTreeNode(tree->t, false);
        s->children[0] = r;
        bplustree_split_child(s, 0);
        int i = 0;
        if (s->accounts[0].account_number < k.account_number)
            i++;
        bplustree_insert_nonfull(s->children[i], k);
        tree->root = s;
    } else {
        bplustree_insert_nonfull(r, k);
    }
}

BPlusTreeNode* bplustree_search(BPlusTreeNode* root, int account_number) {
    int i = 0;
    while (i < root->n && account_number > root->accounts[i].account_number)
        i++;
    if (i < root->n && account_number == root->accounts[i].account_number)
        return root;
    if (root->is_leaf)
        return NULL;
    return bplustree_search(root->children[i], account_number);
}

void bplustree_delete_internal(BPlusTreeNode* node, int account_number);

void bplustree_delete_leaf(BPlusTreeNode* leaf, int idx) {
    for (int i = idx + 1; i < leaf->n; ++i)
        leaf->accounts[i - 1] = leaf->accounts[i];
    leaf->n--;
}

void bplustree_delete_non_leaf(BPlusTreeNode* node, int idx) {
    int t = node->n;
    BPlusTreeNode* child = node->children[idx];
    BPlusTreeNode* sibling = node->children[idx + 1];

    if (child->n >= t) {
        BPlusTreeNode* cur = child;
        while (!cur->is_leaf)
            cur = cur->children[cur->n];
        account pred = cur->accounts[cur->n - 1];
        node->accounts[idx] = pred;
        bplustree_delete_internal(child, pred.account_number);
    } else if (sibling->n >= t) {
        BPlusTreeNode* cur = sibling;
        while (!cur->is_leaf)
            cur = cur->children[0];
        account succ = cur->accounts[0];
        node->accounts[idx] = succ;
        bplustree_delete_internal(sibling, succ.account_number);
    } else {
        child->accounts[t - 1] = node->accounts[idx];
        for (int i = 0; i < sibling->n; ++i)
            child->accounts[i + t] = sibling->accounts[i];
        if (!child->is_leaf) {
            for (int i = 0; i <= sibling->n; ++i)
                child->children[i + t] = sibling->children[i];
        }
        for (int i = idx + 1; i < node->n; ++i)
            node->accounts[i - 1] = node->accounts[i];
        for (int i = idx + 2; i <= node->n; ++i)
            node->children[i - 1] = node->children[i];
        child->n += sibling->n + 1;
        node->n--;
        free(sibling);
        bplustree_delete_internal(child, idx);
    }
}

void bplustree_delete_internal(BPlusTreeNode* node, int account_number) {
    int idx = 0;
    while (idx < node->n && node->accounts[idx].account_number < account_number)
        idx++;
    if (idx < node->n && node->accounts[idx].account_number == account_number) {
        if (node->is_leaf)
            bplustree_delete_leaf(node, idx);
        else
            bplustree_delete_non_leaf(node, idx);
    } else {
        if (node->is_leaf)
            return;
        bool flag = (idx == node->n);
        if (node->children[idx]->n < node->n)
            bplustree_fill(node, idx);
        if (flag && idx > node->n)
            bplustree_delete_internal(node->children[idx - 1], account_number);
        else
            bplustree_delete_internal(node->children[idx], account_number);
    }
}

void bplustree_delete(BPlusTree* tree, int account_number) {
    if (!tree->root)
        return;
    bplustree_delete_internal(tree->root, account_number);
    if (tree->root->n == 0) {
        BPlusTreeNode* tmp = tree->root;
        if (tree->root->is_leaf)
            tree->root = NULL;
        else
            tree->root = tree->root->children[0];
        free(tmp);
    }
}

void bplustree_fill(BPlusTreeNode* node, int idx) {
    int t = node->n;
    if (idx != 0 && node->children[idx - 1]->n >= t)
        bplustree_borrow_from_prev(node, idx);
    else if (idx != node->n && node->children[idx + 1]->n >= t)
        bplustree_borrow_from_next(node, idx);
    else {
        if (idx != node->n)
            bplustree_merge(node, idx);
        else
            bplustree_merge(node, idx - 1);
    }
}

void bplustree_borrow_from_prev(BPlusTreeNode* node, int idx) {
    BPlusTreeNode* child = node->children[idx];
    BPlusTreeNode* sibling = node->children[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->accounts[i + 1] = child->accounts[i];
    if (!child->is_leaf) {
        for (int i = child->n; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }
    child->accounts[0] = node->accounts[idx - 1];
    if (!child->is_leaf)
        child->children[0] = sibling->children[sibling->n];
    node->accounts[idx - 1] = sibling->accounts[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}

void bplustree_borrow_from_next(BPlusTreeNode* node, int idx) {
    BPlusTreeNode* child = node->children[idx];
    BPlusTreeNode* sibling = node->children[idx + 1];
    child->accounts[child->n] = node->accounts[idx];
    if (!child->is_leaf)
        child->children[child->n + 1] = sibling->children[0];
    node->accounts[idx] = sibling->accounts[0];
    for (int i = 1; i < sibling->n; ++i)
        sibling->accounts[i - 1] = sibling->accounts[i];
    if (!sibling->is_leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }
    child->n += 1;
    sibling->n -= 1;
}

void bplustree_merge(BPlusTreeNode* node, int idx) {
    int t = node->n;
    BPlusTreeNode* child = node->children[idx];
    BPlusTreeNode* sibling = node->children[idx + 1];
    child->accounts[t - 1] = node->accounts[idx];
    for (int i = 0; i < sibling->n; ++i)
        child->accounts[i + t] = sibling->accounts[i];
    if (!child->is_leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->children[i + t] = sibling->children[i];
    }
    for (int i = idx + 1; i < node->n; ++i)
        node->accounts[i - 1] = node->accounts[i];
    for (int i = idx + 2; i <= node->n; ++i)
        node->children[i - 1] = node->children[i];
    child->n += sibling->n + 1;
    node->n--;
    free(sibling);
}


void btree_remove_from_leaf(BTreeNode* node, int idx) {
    for (int i = idx + 1; i < node->n; ++i)
        node->accounts[i - 1] = node->accounts[i];
    node->n--;
}

void btree_remove_from_non_leaf(BTreeNode* node, int idx) {
    account k = node->accounts[idx];
    int t = node->t;

    if (node->C[idx]->n >= t) {
        BTreeNode* cur = node->C[idx];
        while (!cur->leaf)
            cur = cur->C[cur->n];
        account pred = cur->accounts[cur->n - 1];
        node->accounts[idx] = pred;
    } else if (node->C[idx + 1]->n >= t) {
        BTreeNode* cur = node->C[idx + 1];
        while (!cur->leaf)
            cur = cur->C[0];
        account succ = cur->accounts[0];
        node->accounts[idx] = succ;
    } else {
        BTreeNode* child = node->C[idx];
        BTreeNode* sibling = node->C[idx + 1];
        child->accounts[t - 1] = node->accounts[idx];

        for (int i = 0; i < sibling->n; ++i)
            child->accounts[i + t] = sibling->accounts[i];

        if (!child->leaf) {
            for (int i = 0; i <= sibling->n; ++i)
                child->C[i + t] = sibling->C[i];
        }

        for (int i = idx + 1; i < node->n; ++i)
            node->accounts[i - 1] = node->accounts[i];

        for (int i = idx + 2; i <= node->n; ++i)
            node->C[i - 1] = node->C[i];

        child->n += sibling->n + 1;
        node->n--;

        free(sibling);
    }
}

void btree_delete(BTree *tree, int account_number) {
    BTreeNode* root = tree->root;
    if (root == NULL)
        return;

    btree_delete_node(root, account_number);

    if (root->n == 0) {
        BTreeNode* tmp = root;
        if (root->leaf)
            tree->root = NULL;
        else
            tree->root = root->C[0];

        free(tmp);
    }
}

void btree_delete_node(BTreeNode* node, int account_number) {
    int idx = 0;
    while (idx < node->n && node->accounts[idx].account_number < account_number)
        ++idx;

    if (idx < node->n && node->accounts[idx].account_number == account_number) {
        if (node->leaf)
            btree_remove_from_leaf(node, idx);
        else
            btree_remove_from_non_leaf(node, idx);
    } else {
        if (node->leaf)
            return;

        bool flag = (idx == node->n);
        if (node->C[idx]->n < node->t)
            btree_fill(node, idx);

        if (flag && idx > node->n)
            btree_delete_node(node->C[idx - 1], account_number);
        else
            btree_delete_node(node->C[idx], account_number);
    }
}

void btree_fill(BTreeNode* node, int idx) {
    int t = node->t;

    if (idx != 0 && node->C[idx - 1]->n >= t)
        btree_borrow_from_prev(node, idx);
    else if (idx != node->n && node->C[idx + 1]->n >= t)
        btree_borrow_from_next(node, idx);
    else {
        if (idx != node->n)
            btree_merge(node, idx);
        else
            btree_merge(node, idx - 1);
    }
}

void btree_borrow_from_prev(BTreeNode* node, int idx) {
    BTreeNode* child = node->C[idx];
    BTreeNode* sibling = node->C[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->accounts[i + 1] = child->accounts[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->accounts[0] = node->accounts[idx - 1];

    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    node->accounts[idx - 1] = sibling->accounts[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}

void btree_borrow_from_next(BTreeNode* node, int idx) {
    BTreeNode* child = node->C[idx];
    BTreeNode* sibling = node->C[idx + 1];

    child->accounts[child->n] = node->accounts[idx];

    if (!child->leaf)
        child->C[child->n + 1] = sibling->C[0];

    node->accounts[idx] = sibling->accounts[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->accounts[i - 1] = sibling->accounts[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

void btree_merge(BTreeNode* node, int idx) {
    int t = node->t;
    BTreeNode* child = node->C[idx];
    BTreeNode* sibling = node->C[idx + 1];

    child->accounts[t - 1] = node->accounts[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->accounts[i + t] = sibling->accounts[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    for (int i = idx + 1; i < node->n; ++i)
        node->accounts[i - 1] = node->accounts[i];

    for (int i = idx + 2; i <= node->n; ++i)
        node->C[i - 1] = node->C[i];

    child->n += sibling->n + 1;
    node->n--;

    free(sibling);
}


void bplustree_print(FILE *f, BPlusTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->is_leaf)
                bplustree_print(f, root->children[i]);
            fprintf(f, "\n");
            fprintf(f, "    Account number: %d\n", root->accounts[i].account_number);
            fprintf(f, "    Name: %s\n", root->accounts[i].name);
            fprintf(f, "    Surname: %s\n", root->accounts[i].surname);
            fprintf(f, "    Account type: %s\n", root->accounts[i].account_type);
            fprintf(f, "    Opening date: %d.", root->accounts[i].opening_date.day);
            fprintf(f, "%d.", root->accounts[i].opening_date.month);
            fprintf(f, "%d\n", root->accounts[i].opening_date.year);
            fprintf(f, "    Opening balance: %d\n", root->accounts[i].opening_balance);
            fprintf(f, "    Date of the last access: %d.", root->accounts[i].last_access.day);
            fprintf(f, "%d.", root->accounts[i].last_access.month);
            fprintf(f, "%d\n", root->accounts[i].last_access.year);
        }
        if (!root->is_leaf)
            bplustree_print(f, root->children[i]);
    }
}

void bplustree_free(BPlusTreeNode* root) {
    if (root != NULL) {
        if (!root->is_leaf) {
            for (int i = 0; i <= root->n; i++)
                bplustree_free(root->children[i]);
        }
        free(root->accounts);
        free(root->children);
        free(root);
    }
}

void bplustree_task(BPlusTree *tree, int delete_num, int search_num) {
    bplustree_search(tree->root, search_num);
    bplustree_delete(tree, delete_num);
}

#endif