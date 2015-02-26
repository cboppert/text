#ifndef BST_H_
#define BST_H_

struct bst_node_t
{
   int key;
   int length;

   struct bst_node_t *left;
   struct bst_node_t *right;
};

struct bst_node_t *create_text();

int length_text( struct bst_node_t *txt );

char *get_line( struct bst_node_t *txt, int index );

void append_line( struct bst_node_t *txt, char * new_line );

char *set_line( struct bst_node_t *txt, int index, char * new_line );

void insert_line( struct bst_node_t *txt, int index, char * new_line );

char *delete_line( struct bst_node_t *txt, int index );

#endif // BST_H_
