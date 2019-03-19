/*
29-1. What possible outcomes might there be if a thread executes the following
code: `pthread_join(pthread_self(), NULL);` Write a program to see what actually
happens on Linux. If we have a variable, tid, containing a thread ID, how can a
thread prevent itself from making a call, pthread_join(tid, NULL), that is
equivalent to the above statement?
------
I expect this to hang forever - pthread_join() will wait on itself.
(tried it)
It actually quits immediately! Not expecting that. To prevent this behavior,
you can save the thread id and then do a check to see if it would join with
itself, skipping if so.
*/
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_ERROR_AND_QUIT(errno) \
  printf("%d", errno);              \
  char *msg = strerror(errno);      \
  perror(msg);                      \
  exit(-1);

int main() {
  // int tid = 0;
  printf("Preparing to self-join...\n");
  if (pthread_join(pthread_self(), NULL) != 0) {
    PRINT_ERROR_AND_QUIT(errno);
  }
}
