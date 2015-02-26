#include <stdio.h>
#include "bst.h"

int main(void) {
   struct bst_node_t bst_tree;
   bst_tree = * create_text();
   printf("%d\n", length_text( &bst_tree ) );

   return 0;
}
