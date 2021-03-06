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
text_t *find_root( text_t *txt );
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
void shift_lines( text_t *txt, text_t *current_node, int index );

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
      bst->key_l = index;
      bst->line_l = new_line;
   }

   //Right node is empty
   else if ( bst->key_r == 0 )
   {
      if ( bst->key_l < index )
      {
         bst->key_r = index;
         bst->line_r = new_line;

         if ( bst->right != NULL && bst->right->key_l < index )
         {
            bst->middle = bst->right;
            bst->right = NULL;
         }
      }

      else if ( bst->key_l == index )
      {
         char *temp = bst->line_l;
         bst->line_l = new_line;
         insert_line( find_root( txt ), index + 1, temp );
      }

      else if ( bst->key_l > index )
      {
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
      if ( !check_for_index_exists( bst, index, new_line ))
      {
         create_four_node( bst, index, new_line );
         insert_into_three_node_under_two_node( bst );
      }
   }

   /* parent is a three node */
   else
   {
      if ( !check_for_index_exists( bst, index, new_line ) )
      {
         create_four_node( bst, index, new_line );

         insert_into_three_node_under_three_node( bst );
      }
   }
}

text_t *find_root( text_t *txt )
{
   return ( txt->parent != NULL ) ? find_root( txt->parent ) : txt;
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

         if ( txt->left != NULL )
         {
            left_node->left = txt->left;
            txt->left->parent = left_node;
         }

         if ( txt->middle != NULL )
         {
            left_node->right = txt->middle;
            txt->middle->parent = left_node;
         }

         if ( txt->right != NULL )
         {
            right_node->left = txt->right;
            txt->right->parent = right_node;
         }

         if ( txt->rightmost != NULL )
         {
            right_node->right = txt->rightmost;
            txt->rightmost->parent = right_node;
         }

         reset_four_node( txt );

         left_node->parent = txt;
         right_node->parent = txt;

         txt->left = left_node;
         txt->right = right_node;
}

void parent_switch( text_t *txt )
{
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
   right_node->left = txt->right;
   right_node->right = txt->rightmost;

   if ( txt->right != NULL )
   {
      txt->right->parent = right_node;
   }

   if ( txt->rightmost != NULL )
   {
      txt->rightmost->parent = right_node;
   }
   txt->key_r = 0;

   txt->parent->right = right_node;

   reset_four_node( txt );
   txt->parent->middle = txt;
}

void insert_into_three_node_under_three_node( text_t *txt )
{
   text_t *parent = txt->parent;
   create_four_node( parent, txt->key_m, txt->line_m );
   txt->key_m = 0;

   text_t *righter_node = create_text();
   righter_node->key_l = txt->key_r;
   righter_node->line_l = txt->line_r;
   righter_node->parent = parent;

   if ( txt->right != NULL )
   {
      righter_node->left = txt->right;
      txt->right->parent = righter_node;
   }

   if ( txt->rightmost != NULL )
   {
      righter_node->right = txt->rightmost;
      txt->rightmost->parent = righter_node;
   }
   txt->key_r = 0;

   if ( txt->key_l < parent->key_l )
   {
      parent->left = txt;
      parent->middle = righter_node;
   }

   else if ( txt->key_l < parent->key_m )
   {
      parent->middle = txt;
      parent->right = righter_node;
   }

   else
   {
      parent->right = txt;
      parent->rightmost = righter_node;
   }

   /*text_t *left = create_text();
   left->key_l = parent->key_l;
   left->line_l = parent->line_l;
   left->parent = parent;

   parent->left->parent = left;
   parent->middle->parent = left;

   left->left = parent->left;
   left->right = parent->middle;

   parent->left = left;
   parent->key_l = 0;

   text_t *right = create_text();
   right->key_l = parent->key_r;
   right->line_l = parent->line_r;
   right->parent = parent;

   txt->parent = right;

   text_t *rightmost = create_text();
   rightmost->key_l = txt->key_r;
   rightmost->line_l = txt->line_r;
   rightmost->parent = right;

   txt->key_r = 0;

   right->left = txt;
   right->right = rightmost;

   parent->right = right;

   parent->key_r = 0;

   reset_four_node( parent );*/
   reset_four_node( txt );

   parent_switch( parent );
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

char *delete_line( text_t *txt, int index )
{
   text_t *current_node = search_tree( txt, index );
   char *deleted_line = get_line( current_node, index );
   if ( deleted_line != NULL )
   {
      shift_lines( txt, current_node, index );
   }

   return deleted_line;
}

void shift_lines( text_t *txt, text_t *current_node, int index )
{
   text_t *next_node = search_tree( txt, index + 1 );
   char **line_to_update = ( current_node->key_l == index ) ? &current_node->line_l : &current_node->line_r;

   if ( next_node->key_l == index + 1 )
   {
      *line_to_update = next_node->line_l;
      shift_lines( txt, next_node, index + 1 );
   }

   else if ( next_node->key_r == index + 1 )
   {
      *line_to_update =  next_node->line_r;
      shift_lines( txt, next_node, index + 1 );
   }

   /* index is final key */
   else
   {
      if ( current_node->key_r == index )
      {
         current_node->key_r = 0;
         current_node->line_r = NULL;

         current_node->right = ( current_node->middle != NULL ) ? current_node->middle : NULL;
         current_node->middle = NULL;
      }

      else
      {
         if ( current_node->left != NULL )
         {
//            text_t **left = &current_node->left;
             
            swap_trees( current_node, current_node->left );
//            free( *left );
         }

         else if ( current_node->parent != NULL )
         {
            text_t *parent = current_node->parent;
            if ( parent->left == current_node )
            {
               parent->left = NULL;
            }

            else if ( parent->middle == current_node )
            {
               parent->middle = NULL;
            }

            else
            {
               parent->right = NULL;
            }

//            free ( current_node );
         }

         /* tree is now empty */
         else
         {
            current_node->key_l = 0;
            current_node->line_l = NULL;
         }
      }
   }
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

/*
 * Create four node doesn't manage branches below so if less than key_l need to set left and middle
 * if less than key_r need to set middle and right
 * and if greater than key_r need to set right and rightmost
 */
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
   {
      char *temp = txt->line_l;
      txt->line_l = new_line;
      insert_line( find_root( txt ), index + 1, temp );
      return 1;
   }

   else if ( index == txt->key_r )
   {
      char *temp = txt->line_r;
      txt->line_r = new_line;
      insert_line( find_root( txt ), index + 1, temp );
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
