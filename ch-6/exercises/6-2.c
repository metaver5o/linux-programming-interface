/*
6-2. Write a program to see what happens if we try to longjmp() into a function
that has already returned.
*/

#include <setjmp.h>
#include <stdio.h>

static int func_a(jmp_buf jb) {
  int local_var = 15;
  int res = setjmp(jb);
  printf("func_a() | setjmp: %d\n", res);
  printf("func_a() | local_var: %d\n",
         local_var);  // This will print garbage after func_() returns
  return 0;
}

int main() {
  static int jumped = 0;
  jmp_buf jb;
  func_a(jb);
  if (jumped == 0) {
    jumped = 1;
    longjmp(jb, 1);
  }
  return 0;
}
