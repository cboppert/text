#include <stdio.h>
#include "bst.h"

TEXT_p_t create_text()
{
   TEXT_p_t txt;
   *txt.length = 3;
}

int length_text( TEXT_p_t txt )
{
   return txt->length;
}

char * get_line( TEXT_p_t txt, int index)
{
   return NULL;
}

void append_line( TEXT_p_t txt, char * new_line)
{

}

char * set_line( TEXT_p_t txt, int index, char * new_line)
{
   return NULL;
}

void insert_line( TEXT_p_t txt, int index, char * new_line )
{

}

char * delete_line( TEXT_p_t txt, int index)
{
   return NULL;
}
