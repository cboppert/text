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

int minimum( int key_a, int key_b, int key_c );
int maximum( int key_a, int key_b, int key_c );
int middle( int key_a, int key_b, int key_c );

text_t *create_text(void)
{
   text_t *txt;
   txt = get_node();
   txt->line_l = NULL;
   txt->line_r = NULL;

   txt->left = NULL;
   txt->right = NULL;
   txt->middle = NULL;
   txt->parent = NULL;

   txt->key_l = 0,
   txt->key_r = 0;
   txt->key_m = 0;

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
   printf("length text: %d \n", length_text( txt ));
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

   //Empty tree
   if ( txt->key_l == 0 )
   {
      printf("1 key_l: %d\n", index);
      txt->key_l = index;
      txt->line_l = new_line;
   }

   //Right node is empty
   else if ( txt->key_r == 0 )
   {
      if ( txt->key_l < index )
      {      printf("2, key_l: %d  index: %d \n", txt->key_l, index);

         txt->key_r = index;
         txt->line_r = new_line;
      }

      else if ( txt->key_l == index )
      {      printf("3\n");

         char *temp = txt->line_l;
         txt->line_l = new_line;
         insert_line( txt, index + 1, temp );
      }

      else if ( txt->key_l > index )
      {      printf("4\n");

         txt->key_r = txt->key_l;
         txt->key_l = index;
         txt->line_r = txt->line_l;
         txt->line_l = new_line;
      }
   }

   //Parent is empty and 3 node
   else if ( txt->parent == NULL )
   {
      if ( index == txt->key_l )
      {      printf("5\n");

         char *temp = txt->line_l;
         txt->line_l = new_line;
         insert_line( txt, index + 1, temp );
      }

      else if ( index == txt->key_r )
      {      printf("6 index/txt->key_r: %d \n", index);

         char *temp = txt->line_r;
         txt->line_r = new_line;
         insert_line( txt, index + 1, temp );
      }

      else {
         text_t *left_node = create_text();
         text_t *right_node = create_text();
         left_node->parent = txt;
         right_node->parent = txt;

         txt->left = left_node;
         txt->right = right_node;

         if ( index < txt->key_l )
         {      printf("7\n");

            left_node->key_l = index;
            left_node->line_l = new_line;

            right_node->key_l = txt->key_r;
            right_node->line_l = txt->line_r;
         }

         else if ( index < txt->key_r )
         {      printf("8\n");

            left_node->key_l = txt->key_l;
            left_node->line_l = txt->line_l;

            right_node->key_l = txt->key_r;
            right_node->line_l = txt->line_r;

            txt->key_l = index;
            txt->line_l = new_line;
         }

         else
         {      printf("9 l-k-l: %d l-k-r: %d r-k-l: %d r-k-r: %d \n", left_node->key_l, left_node->key_r, right_node->key_l, right_node->key_r);

            left_node->key_l = txt->key_l;
            left_node->line_l = txt->line_l;

            right_node->key_l = index;
            right_node->line_l = new_line;
            printf("9 l-k-l: %d l-k-r: %d r-k-l: %d r-k-r: %d \n", left_node->key_l, left_node->key_r, right_node->key_l, right_node->key_r);

         }
      printf("10\n");
         txt->key_r = 0;
         txt->line_r = NULL;
         txt->right = NULL;
      }
   }

   /*  Parent is a 2 nope */
   else if ( txt->parent->key_r == 0 )
   {
      printf("Parent is a two node index: %d \n", index);
   }

   /* parent is a three node */
   else
   {
      printf("Parent is a three node index %d \n", index);

   }


   printf("Got to end, index: %d \n", index);
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
   printf("Length text called\n");
   if ( txt->right == NULL )
   {
      printf("txt->right is Null\n");
      return ( txt->key_r == 0 ) ? txt->key_l : txt->key_r;
   }

   printf("txt->right is not null\n");
   return length_text( txt->right );
}

text_t *search_tree( text_t *txt, int index )
{
   printf("index: %d key_l: %d key_r: %d \n", index, txt->key_l, txt->key_r);
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

int minimum( int key_a, int key_b, int key_c )
{
   if ( key_a < key_b )
   {
      if ( key_a < key_c )
      {
         return key_a;
      }
      return key_c;
   }

   if ( key_b < key_c )
   {
      return key_b;
   }
   return key_c;
}

int maximum( int key_a, int key_b, int key_c )
{
   if ( key_a > key_b )
   {
      if ( key_a > key_c )
      {
         return key_a;
      }
      return key_c;
   }

   if ( key_b > key_c )
   {
      return key_b;
   }
   return key_c;
}

int middle( int key_a, int key_b, int key_c )
{
   int max = maximum( key_a, key_b, key_c );
   int min = minimum( key_a, key_b, key_c );

   return key_a != max && key_a != min ? key_a : key_b != max && key_b != min ? key_b : key_c;
}
