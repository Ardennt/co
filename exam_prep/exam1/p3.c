#include <stdlib.h>
#include <stdio.h>

// 3) Construct a function passin_sums() that takes 3 arguments. The first two arguments 
// should be added and saved to the third argument **within** the function passin_sums(). 
// See below - the value of c printed out should be 3 after returning from the function.

void passin_sums(int* one, int* two, int* three)
{
  *three = *one + *two;
}

void main()
{
  int a = 1;
  int b = 2;
  int c = 0;
  passin_sums(&a, &b, &c);
  printf("%d\n", c); // the value printed must be 3
}