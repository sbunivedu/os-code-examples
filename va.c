#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  printf("location of code : %p\n", main);
  char* ptr = malloc(4096);
  printf("location of heap : %p\n", ptr);
  ptr = malloc(4096);
  printf("location of next allocation : %p\n", ptr);
  free(ptr);
  printf("location of next allocation : %p\n", malloc(4096));
  printf("location of next allocation : %p\n", malloc(4096));
  printf("location of next allocation : %p\n", malloc(4096));
  int x = 3;
  printf("location of stack: %p\n", &x);
  printf("location of x: %p\n", &x);
  int y = 3;
  printf("location of y: %p\n", &y);
  return 0;
}

/*
This example shows the directions in which heap and stack grow.
It also shows that malloc allocates more space to store 
the header information for each allocated memory block.
*/
