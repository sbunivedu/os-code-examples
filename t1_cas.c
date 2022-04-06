#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "common.h"
#include "common_threads.h"

int max;
volatile int counter = 0; // shared global variable

typedef struct __lock_t {
  int flag;
} lock_t;

lock_t mylock;

void init(lock_t *mutex){
  // 0 -> lock is available, 1 -> held
  mutex->flag = 0;
}

char CompareAndSwap(int *ptr, int old, int new) {
  unsigned char ret;

  // Note that sete sets a ’byte’ not the word
  __asm__ __volatile__ (
    " lock\n"
    " cmpxchgl %2,%1\n"
    " sete %0\n"
    : "=q" (ret), "=m" (*ptr)
    : "r" (new), "m" (*ptr), "a" (old)
    : "memory");
  return ret;
}

void lock(lock_t *mutex){
  while(CompareAndSwap(&mutex->flag, 0, 1) == 1); //spin
}

void unlock(lock_t *mutex){
  mutex->flag = 0;
}

void *mythread(void *arg) {
  char *letter = arg;
  int i; // stack (private per thread)
  printf("%s: begin [addr of i: %p]\n", letter, &i);
  for (i = 0; i < max; i++) {
    lock(&mylock);
    counter = counter + 1; // shared: only one
    unlock(&mylock);
  }
  printf("%s: done\n", letter);
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: main-first <loopcount>\n");
    exit(1);
  }
  max = atoi(argv[1]);

  pthread_t p1, p2;
  printf("main: begin [counter = %d] [%x]\n", counter,
    (unsigned int) &counter);
  Pthread_create(&p1, NULL, mythread, "A");
  Pthread_create(&p2, NULL, mythread, "B");
  // join waits for the threads to finish
  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);
  printf("main: done\n [counter: %d]\n [should: %d]\n",
    counter, max*2);
  return 0;
}

/*
gcc -o t1_cas t1_cas.c -Wall -pthread
./t1_cas 16000
*/
