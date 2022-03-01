#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int* x = NULL;
  int y = *x;
}

/*
gcc null.c -o null
./null

gcc null.c -o null -g
gdb null

valgrind --leak-check=yes ./null
 
*/
