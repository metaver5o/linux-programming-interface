/*
Aside from the absence of error checking and various variable and structure
declarations, what is the problem with the following program?
-------------------
It doesn't look like the program waits for threadFunc() to complete. My guess is
that this would exit immediately after the thread had been started.
(reviewed the chapter)
Given that pthread_exit() is called with NULL, the other threads will continue
to execute, but they will become zombie threads given that they weren't
detatched correctly.
*/
#include <pthread.h>
#include <stdio.h>

struct someStruct {
  int data;
};

static void *threadFunc(void *arg) {
  struct someStruct *pbuf = (struct someStruct *)arg;
  // Do some work with structure pointed to by 'pbuf'
}

int main(int argc, char *argv[]) {
  pthread_t thr;
  struct someStruct buf;
  pthread_create(&thr, NULL, threadFunc, (void *)&buf);
  pthread_exit(NULL);
}
