#include <stdio.h>
#include "bst.h"

int main(void) {
   TEXT_t txt;
   txt = create_text();
   printf("%d\n", length_text( &txt ) );

   return 0;
}
