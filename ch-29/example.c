#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define COUNT 10

typedef struct thread_ret {
  int status;
} thread_ret;

static thread_ret* hello_world(void* args) {
  (void)args;
  printf("Hello, multithreaded world!\n");
  thread_ret* tr = malloc(sizeof(thread_ret));
  tr->status = 4;
  return tr;
}

int main() {
  pthread_t thread_ids[COUNT] = {0};
  pthread_attr_t thread_attrs[COUNT] = {{{0}}};
  thread_ret* tr = NULL;

  for (int i = 0; i < COUNT - 1; i++) {
    pthread_create(&thread_ids[i], &thread_attrs[i], hello_world, NULL);
    printf("%d\n", tr->status);
    free(tr);
  }

  return 0;
}
