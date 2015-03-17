#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/* root->left NULL then tree empty
   root->left not NULL, root->right NULL, root is leaf, root->left is object, n->key is key
   root->left not NULL, root->right not NULL, then each points to root of left and right subtrees

   All keys in left subtree < root->key, all keys in right subtree > root->key

   Algorithms based upon: http://algs4.cs.princeton.edu/33balanced/
   Princeton's balanced search trees section
*/
text_t *create_text(void)
{
   text_t *txt;
   txt = get_node();
   txt->key_l = 0,
   txt->key_r = 0;

   return txt;
}

char *get_line( text_t *txt, int index )
{
   text_t *bst;
   bst = search_tree( txt, index );

   if ( bst->key_l == index )
   {
      return bst->line_l;
   }

   if ( bst->key_r == index )
   {
      return bst->line_r;
   }

   return NULL;
}

void append_line( text_t *txt, char *new_line )
{
   insert_line( txt, length_text( txt ) + 1, new_line);
}

char *set_line( text_t *txt, int index, char * new_line )
{
   text_t *bst = search_tree( txt, index );

   if ( bst->key_l == index )
   {
      char* line = bst->line_l;
      bst->line_l = new_line;
      return line;
   }

   if ( bst->key_r == index )
   {
      char* line = bst->line_r;
      bst->line_r = new_line;
      return line;
   }

   return NULL;
}

void insert_line( text_t *txt, int index, char * new_line )
{
   text_t *bst = search_tree( txt, index );

   if ( bst->key_l == index )
   {

   }

   if ( bst->key_r == index )
   {

   }


}

char * delete_line( text_t *txt, int index )
{
   return NULL;
}

text_t *get_node(void)
{
   text_t *bst;
   bst = (text_t *) malloc( sizeof(text_t) );
   return bst;
}

int length_text( text_t *txt )
{
   if ( txt->right == NULL )
   {
      return ( txt->key_r == 0 ) ? txt->key_l : txt->key_r;
   }

   return length_text( txt->right );
}

text_t *search_tree( text_t *txt, int index )
{
   if ( index < txt->key_l )
   {
      return ( txt->left == NULL ) ? txt : search_tree( txt->left, index );
   }

   if ( index == txt->key_l )
   {
      return txt;
   }

   if ( txt->key_r == 0 )
   {
      return ( txt->right == NULL ) ? txt : search_tree( txt->right, index );
   }

   if ( index < txt->key_r )
   {
      return ( txt->middle == NULL ) ? txt : search_tree( txt->middle, index );
   }

   if ( index == txt->key_r )
   {
      return txt;
   }

   if ( index > txt->key_r )
   {
      return ( txt->right == NULL ) ? txt : search_tree( txt->right, index );
   }

   printf("Your get_line method got somewhere it shouldnt't\n");
   return NULL;
}

/* returns 1 for yes and 0 for no */
int is_empty( text_t *txt )
{
   if ( txt->left == NULL)
   {
      return 1;
   }
   return 0;
}

int get_height( text_t *txt )
{
   if ( txt->left == NULL )
   {
      return 0;
   }
   return ( get_height( txt->left ) > get_height( txt->right ) ) ? get_height( txt->left ) + 1 : get_height( txt->right ) + 1;
}
