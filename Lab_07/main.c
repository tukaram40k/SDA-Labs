#include <stdio.h>
#include <stdlib.h>
#include "trees.h"

int main(){
    FILE *f1, *f2, *f3;
    f1=fopen("info.txt", "r");
    f2=fopen("output.txt", "w");

    int num_of_accounts=30;
    account *accounts=(account*)malloc(num_of_accounts*sizeof(account));

    get_data(f1, accounts, num_of_accounts);

    printf("Select the output directory: C:\\Users\\Ivan\\Desktop\\C files\\SDA_Labs\\Lab_07\\output.txt\n\n");

    int version;
    printf("Input version:\n1. AVL Tree\n2. B Tree\n3. B+ Tree\n");
    scanf("%d", &version);

    if (version==1){
        AVLNode *avl_root=NULL;
        for (int i=0; i<num_of_accounts; i++){
            avl_root=avl_insert(avl_root, accounts[i]);
        }
        avl_print(f2, avl_root);
        avl_free(avl_root);
    }
    if (version==2){
        BTree *btree=btree_create(3);
        for (int i=0; i<num_of_accounts; i++){
            btree_insert(btree, accounts[i]);
        }
        btree_print(f2, btree->root);
        btree_free(btree->root);
        free(btree);
    }
    if (version==3){
        BPlusTree *bplustree=bplustree_create(3);
        for (int i=0; i<num_of_accounts; i++){
            bplustree_insert(bplustree, accounts[i]);
        }
        bplustree_print(f2, bplustree->root);
        bplustree_free(bplustree->root);
        free(bplustree);
    }

    fclose(f1);
    fclose(f2);
    free(accounts);
}
