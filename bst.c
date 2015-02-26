#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

struct bst_node_t *create_text()
{
   struct bst_node_t *txt;
   txt = (struct bst_node_t *) malloc( sizeof(struct bst_node_t) );
   txt->length = 0;

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
