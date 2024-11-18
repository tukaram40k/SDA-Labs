#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
    bool is_leaf;
    int height;
} node;



void WriteLeaf(node *const root) {
   if (root == NULL) {
       printf("Tree DS is empty.\n");
       return;
   }
   int i;
   node *c = root;
   while (!c->is_leaf)
          c = c->ptr[0];
    while (true) {
         for (i = 0; 
i < (*c).num_keys;
 i++) {
             if (output)
               printf("%p ", 
(*c).ptr[i]);

             printf("%d ", c->keys[i]);
      }
      if (output)
          printf("%p ", c->ptr[order - 1]);
      if 
((*c).ptr[order - 1]
 != NULL) {
          printf(" | ");
          c = c->ptr[order - 1];
       } else

         break;

     }
     printf("\n");
}