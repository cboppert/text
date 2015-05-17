#ifndef BST_H_
#define BST_H_

typedef struct text
{
   int key_l;
   int key_r;

   //80 is standard column for programming +1 for end line
   char *line_l;
   char *line_r;

   struct text *left;
   struct text *middle;
   struct text *right;

   //For inserting into 3 nodes
   int key_m;
   struct text *parent;
} text_t;

text_t *create_text( void );

char *get_line( text_t *txt, int index );

char *set_line( text_t *txt, int index, char *new_line );

void insert_line( text_t *txt, int index, char *new_line );

void append_line( text_t *txt, char *new_line );

char *delete_line( text_t *txt, int index );

int length_text( text_t *txt );

#endif // BST_H_
