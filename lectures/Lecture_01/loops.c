/*
 Try compiling with different flags and running:
 ./loops.sh
*/

#include <stdio.h>

#define SIZE 5

/* K&R style of function definitions */
int foo(s, f)
  char* s;
  float f;
{
  return 5;
}

/* ANSI C and more recent style of function definitions */
int bar(char* s, float f) {
  return 5;
}

int main(void) {
  int i;
  for (i = 0; i < SIZE; ++i) {
    printf("i == %03d\n", i);
  }
  for (int j = 0; j < SIZE; ++j) {
    printf("j == %03d\n", j);
  }
  printf("foo() returned %d\n", foo("Hello", 2.5));
  printf("bar() returned %d\n", bar("World", 42));
}