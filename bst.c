#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

struct bst_node_t *create_text(void)
{
   struct bst_node_t *txt;
   txt = get_node();
   txt->length = 0;
   txt->left = NULL;

   return txt;
}

int length_text( struct bst_node_t *txt )
{
   return txt->length;
}

char * get_line( struct bst_node_t *txt, int index)
{
   return NULL;
}

void append_line( struct bst_node_t *txt, char * new_line)
{

}

char * set_line( struct bst_node_t *txt, int index, char * new_line)
{
   return NULL;
}

void insert_line( struct bst_node_t *txt, int index, char * new_line )
{

}

char * delete_line( struct bst_node_t *txt, int index)
{
   return NULL;
}

struct bst_node_t *get_node(void)
{
   struct bst_node_t *bst;
   bst = (struct bst_node_t *) malloc( sizeof(struct bst_node_t) );
   return bst;
}

/* returns 1 for yes and 0 for no */
int is_empty( struct bst_node_t *tree)
{
   if ( tree->left == NULL)
   {
      return 1;
   }
   return 0;
}
