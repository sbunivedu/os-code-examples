#include <stdio.h>

int main(){
  foo:
  printf("the code: %p\n" , &&foo);
  fgetc(stdin);
  return 0 ;
}

/*
source: https://people.kth.se/~johanmon/ose/assignments/stack.pdf

> gcc -o code code.c
> ./code
the code: 0x401050

this is the address of the foo label

> ./code&
[1] 130
the code: 0x401050

> cat /proc/130/maps
*/