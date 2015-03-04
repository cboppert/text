#ifndef BST_H_
#define BST_H_

typedef struct text
{
   int key_l;
   int key_r;

   //80 is standard column for programming +1 for end line
   char line_l[81];
   char line_r[81];

   struct text *left;
   struct text *middle;
   struct text *right;
} text_t;

text_t *create_text(void);

int length_text( text_t *txt );

char *get_line( text_t *txt, int index );

void append_line( text_t *txt, char * new_line );

char *set_line( text_t *txt, int index, char * new_line );

void insert_line( text_t *txt, int index, char * new_line );

char *delete_line( text_t *txt, int index );

text_t *get_node(void);

int is_empty( text_t *txt );

int get_height( text_t *txt );

#endif // BST_H_
