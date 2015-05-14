CC=clang
CFLAGS=-I.

bst: bst.o main.o
   $(CC) -o bst bst.o main.o std='c89' -I.
