/*
4.2: Write a program like cp that, when used to copy a regular file that
contains holes (sequences of null bytes), also creates corresponding holes in
the target file.
------
- get cli args
  - first arg is source file, should be stat'd
  - second is dest path on fs; should call stat on basename/dirname
- open dest file, quit on error
- begin copying line by line

*/
#include <stdio.h>

#define PRINT_ERROR_AND_QUIT(errno) \
  char *msg = strerror(errno);      \
  perror(msg);                      \
  exit(-1);
