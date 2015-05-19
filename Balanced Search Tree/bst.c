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
int get_max_key( text_t *txt );
int check_for_index_exists( text_t *txt, int index, char *new_line );

text_t *get_node(void);
text_t *search_tree( text_t *txt, int index );
int is_empty( text_t *txt );
int get_height( text_t *txt );

void insert_into_single_three_node( text_t *txt );
void insert_into_three_node_under_two_node( text_t *txt );
void insert_into_three_node_under_three_node( text_t *txt );
void insert_into_root_with_children( text_t *txt );
void parent_switch( text_t *txt );
void split_the_root( text_t *txt );

void create_four_node( text_t *txt, int index, char *new_line );
void reset_four_node( text_t *txt );
void swap_trees( text_t *txt, text_t *new );

text_t *create_text(void)
{
   text_t *txt;
   txt = get_node();

   txt->line_l = NULL;
   txt->line_m = NULL;
   txt->line_r = NULL;

   txt->parent = NULL;
   txt->left = NULL;
   txt->middle = NULL;
   txt->right = NULL;
   txt->rightmost = NULL;

   txt->key_l = 0,
   txt->key_m = 0;
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

void insert_line( text_t *txt, int index, char *new_line )
{
   text_t *bst = search_tree( txt, index );

   //Empty tree
   if ( bst->key_l == 0 )
   {
      printf("1 key_l: %d \n", index);
      bst->key_l = index;
      bst->line_l = new_line;
   }

   //Right node is empty
   else if ( bst->key_r == 0 )
   {
      if ( bst->key_l < index )
      {      printf("2, key_l: %d index: %d \n", bst->key_l, index);

         bst->key_r = index;
         bst->line_r = new_line;

         if ( bst->right != NULL && bst->right->key_l < index )
         {
            bst->middle = bst->right;
            bst->right = NULL;
         }
      }

      else if ( bst->key_l == index )
      {      printf("3\n");

         char *temp = bst->line_l;
         bst->line_l = new_line;
         insert_line( bst->parent == NULL ? bst : bst->parent , index + 1, temp );
      }

      else if ( bst->key_l > index )
      {      printf("4\n");

         bst->key_r = bst->key_l;
         bst->key_l = index;
         bst->line_r = bst->line_l;
         bst->line_l = new_line;

         if ( bst->left != NULL )
         {
            bst->middle = bst->left;
            bst->left = NULL;
         }
      }
   }

   //Parent is empty and 3 node
   else if ( bst->parent == NULL )
   {
      if (!check_for_index_exists( bst, index, new_line ))
      {
         if ( bst->left == NULL && bst->middle == NULL && bst->right == NULL)
         {
            create_four_node( bst, index, new_line );
            insert_into_single_three_node( bst );
         }

         else
         {
            create_four_node( bst, index, new_line );
            insert_into_root_with_children( bst );
         }
      }
   }

   /*  Parent is a 2 nope */
   else if ( bst->parent->key_r == 0 )
   {
      printf("Parent is a two node index: %d \n", index);
      if ( !check_for_index_exists( bst, index, new_line ))
      {
         create_four_node( bst, index, new_line );
         insert_into_three_node_under_two_node( bst );
      }
   }

   /* parent is a three node */
   else
   {
      printf("Parent is a three node index %d \n", index);
      if ( !check_for_index_exists( bst, index, new_line ) )
      {
         create_four_node( bst, index, new_line );

         printf("four node created. bst->key_l: %d bst->key_m: %d bst->key_r: %d \n", bst->key_l, bst->key_m, bst->key_r);
         insert_into_three_node_under_three_node( bst );
      }
   }


   printf("Got to end of insert, index: %d \n", index);
}

/* Equals cases covered before this is called */
void insert_into_single_three_node( text_t *txt )
{
         text_t *left_node = create_text();
         text_t *right_node = create_text();

         left_node->key_l = txt->key_l;
         left_node->line_l = txt->line_l;

         txt->key_l = 0;

         right_node->key_l = txt->key_r;
         right_node->line_l = txt->line_r;

         txt->key_r = 0;

         left_node->left = ( txt->left != NULL ) ? txt->left : NULL;
         left_node->right = ( txt->middle != NULL ) ? txt->middle : NULL;
         right_node->left = ( txt->right != NULL ) ? txt->right : NULL;
         right_node->right = ( txt->rightmost != NULL ) ? txt->rightmost : NULL;

         reset_four_node( txt );

         left_node->parent = txt;
         right_node->parent = txt;

         txt->left = left_node;
         txt->right = right_node;

         printf("insert into single three node finish \n");
}

void parent_switch( text_t *txt )
{
   printf("insert into parent switch\n");

   if ( txt->parent == NULL )
   {
      //insert_into_root_with_children( txt );
      insert_into_single_three_node( txt );
   }

   else if ( txt-> parent->key_r == 0 )
   {
      insert_into_three_node_under_two_node( txt );
   }

   else
   {
      insert_into_three_node_under_three_node( txt );
   }
}

void split_the_root( text_t *txt )
{
   printf("split the root\n");

   insert_into_single_three_node( txt );

}

void insert_into_three_node_under_two_node( text_t *txt )
{
   txt->parent->key_r = txt->key_m;
   txt->parent->line_r = txt->line_m;
   txt->key_m = 0;

   text_t *right_node = create_text();
   right_node->parent = txt->parent;

   right_node->key_l = txt->key_r;
   right_node->line_l = txt->line_r;
   txt->key_r = 0;

   txt->parent->right = right_node;

   reset_four_node( txt );
   txt->parent->middle = txt;
}

void insert_into_three_node_under_three_node( text_t *txt )
{
   create_four_node( txt->parent, txt->key_m, txt->line_m );
   txt->key_m = 0;

   text_t *rightmost = create_text();
   rightmost->parent = txt->parent;

   rightmost->key_l = txt->key_r;
   rightmost->line_l = txt->line_r;
   txt->key_r = 0;

   txt->parent->right = txt;
   txt->parent->rightmost = rightmost;

   reset_four_node( txt );
   parent_switch( txt->parent );
}

void insert_into_root_with_children( text_t *txt )
{
   text_t *left_node = create_text();
   text_t *right_node = create_text();

   left_node->parent = txt;
   right_node->parent = txt;

   txt->left = left_node;
   txt->right = right_node;

   left_node->key_l = txt->key_l;
   left_node->line_l = txt->line_l;
   txt->key_l = 0;

   right_node->key_l = txt->key_r;
   right_node->line_l = txt->line_r;
   txt->key_r = 0;

   reset_four_node( txt );
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

/*
 * Here I am returning a new text_t so that branches may be closer in memory to their parents
 * but it would be interesting to see if it actually makes any difference
 * */
void create_four_node( text_t *txt, int index, char *new_line )
{

   text_t *four_node = create_text();
   four_node->parent = txt->parent;

   if ( index < txt->key_l )
   {
      four_node->key_l = index;
      four_node->line_l = new_line;

      four_node->key_m = txt->key_l;
      four_node->line_m = txt->line_l;

      four_node->key_r = txt->key_r;
      four_node->line_r = txt->line_r;

      four_node->right = ( txt->middle == NULL ) ? NULL : txt->middle;
      four_node->rightmost = ( txt->right == NULL ) ? NULL : txt->right;
   }

   else if ( index < txt->key_r )
   {
      four_node->key_l = txt->key_l;
      four_node->line_l = txt->line_l;

      four_node->key_m = index;
      four_node->line_m = new_line;

      four_node->key_r = txt->key_r;
      four_node->line_r = txt->line_r;

      four_node->left = txt->left;
      four_node->rightmost = txt->right;
   }

   else
   {
      four_node->key_l = txt->key_l;
      four_node->line_l = txt->line_l;

      four_node->key_m = txt->key_r;
      four_node->line_m = txt->line_r;

      four_node->key_r = index;
      four_node->line_r = new_line;

      four_node->left = txt->left;
      four_node->middle = txt->middle;
   }

   swap_trees( txt, four_node );
   free ( four_node );
}

int get_max_key( text_t *txt )
{
   return ( txt->key_r == 0 ) ? txt->key_l : txt->key_r;
}

int check_for_index_exists( text_t *txt, int index, char *new_line )
{
   if ( index == txt->key_l )
   {      printf("5\n");
      char *temp = txt->line_l;
      txt->line_l = new_line;
      insert_line( txt->parent == NULL ? txt : txt->parent, index + 1, temp );
      return 1;
   }

   else if ( index == txt->key_r )
   {      printf("6 index/bst->key_r: %d \n", index);
      char *temp = txt->line_r;
      txt->line_r = new_line;
      insert_line( txt->parent == NULL ? txt : txt->parent, index + 1, temp );
      return 1;
   }

   return 0;
}

void reset_four_node( text_t *txt )
{
   text_t *normal_node = create_text();
   normal_node->parent = txt->parent;

   if ( txt->key_l != 0 )
   {
      normal_node->key_l = txt->key_l;
      normal_node->line_l = txt->line_l;

      normal_node->left = txt->left;

      if ( txt->key_m != 0 )
      {
         normal_node->key_r = txt->key_m;
         normal_node->line_r = txt->line_m;

         normal_node->middle = txt->middle;

         normal_node->right = ( txt->right != NULL ) ? txt->right : txt->rightmost;
      }

      else if ( txt->key_r != 0 )
      {
         normal_node->key_r = txt->key_r;
         normal_node->line_r = txt->line_r;

         normal_node->middle = ( txt->middle != NULL ) ? txt->middle : txt->right;

         normal_node->right = txt->rightmost;
      }

      else
      {
         normal_node->right = ( txt->middle != NULL ) ? txt->middle : ( txt->right != NULL ) ? txt->right : txt->rightmost;
      }
   }

   else if ( txt->key_m != 0 )
   {
      normal_node->key_l = txt->key_m;
      normal_node->line_l = txt->line_m;

      normal_node->left = ( txt->left != NULL ) ? txt->left : txt->middle;

      if ( txt->key_r != 0 )
      {
         normal_node->key_r = txt->key_r;
         normal_node->line_r = txt->line_r;

         normal_node->middle = txt->right;

         normal_node->right = txt->rightmost;
      }

      else
      {
         normal_node->right = ( txt->right != NULL ) ? txt->right : txt->rightmost;
      }
   }

   else
   {
      normal_node->key_l = txt->key_r;
      normal_node->line_l = txt->line_r;

      normal_node->left = ( txt->left == NULL ) ? txt->left : ( txt->middle == NULL ) ? txt->middle : txt->right;
      normal_node->right = txt->rightmost;
   }

   swap_trees( txt, normal_node );
   free ( normal_node );
}

/* This should be refactored out but it'd make the four node methods really ugly with lots of temp variables currently */
void swap_trees( text_t *txt, text_t *new )
{
   txt->key_l = new->key_l;
   txt->key_m = new->key_m;
   txt->key_r = new->key_r;

   txt->line_l = new->line_l;
   txt->line_m = new->line_m;
   txt->line_r = new->line_r;

   txt->left = new->left;
   txt->middle = new->middle;
   txt->right = new->right;
   txt->rightmost = new->rightmost;
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
