#include <stdio.h>

int foo(int& x)
{
  return x * x;
}

int main()
{
  int y = 4;
  printf("%d\n", foo(y));
}

