#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int stack = 0;
  printf("%p\n", &stack);
  return 0; 
}


/*
This code prints out the (virtual) address 
of a variable on the stack. 
In non-ASLR systems, this value world be
the same each time.
*/
