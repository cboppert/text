#ifndef BST_H_
#define BST_H_

typedef struct text_t
{
   int *length;
} TEXT_t *TEXT_p_t;

TEXT_p_t create_text();

int length_text( TEXT_p_t txt );

char * get_line( TEXT_p_t txt, int index);

void append_line( TEXT_p_t txt, char * new_line);

char * set_line( TEXT_p_t txt, int index, char * new_line);

void insert_line( TEXT_p_t txt, int index, char * new_line);

char * delete_line( TEXT_p_t txt, int index);

#endif // BST_H_
