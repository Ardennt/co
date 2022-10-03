#include <stdlib.h>
#include <stdio.h>

// The code below outputs several memory addresses with printf(). For each output, 
// identify if the printed address would be a location in the heap, stack, or 
// text/code segments of process memory.

void print_output(int n) {
  printf("Hello World: %d\n", n);
}

void main()
{
  int x = 10;
  char * s = calloc( x, sizeof( char ) );
  char * t = "Memory is fun!";
  void (*fun_ptr)(int) = &print_output;
  printf("%p\n", &x); // stack
  printf("%p\n", s); // heap
  printf("%p\n", t); // text
  printf("%p\n", fun_ptr); // text code segment
  printf("%p\n", &fun_ptr); // stack
}