#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  printf("hello world (pid:%d)\n", (int) getpid());
  int rc = fork();
  if (rc < 0) {
    // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child (new process)
    printf("hello, I am child (pid:%d)\n", (int) getpid());
  } else {
    // parent goes down this path (original process)
    printf("hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
  }
  return 0;
}

/*
gcc -o p1 p1.c

> ./p1
hello world (pid:81)
hello, I am parent of 82 (pid:81)
hello, I am child (pid:82)

Note the output should be non-deterministic because the processes are scheduled independently by the OS.
*/