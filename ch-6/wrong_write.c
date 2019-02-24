#include <stdio.h>

int main() {
#pragma clang diagnostic ignored "-Warray-bounds"
  char data[1];
  // printf("Accessing the 4095th byte from data...\n");
  // data[4095] = 'a';
  // printf("data[4095]: %c\n", data[4095]);
  printf(
      "Now trying address far from data (this will usually cause a SIGSEGV "
      "if above lines are commented out).\n");
  data[100000] = 'a';
  return 0;
}
