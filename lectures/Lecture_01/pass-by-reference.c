#include <stdio.h>
#include <stdlib.h>
                               // C++ equivalent:
                               //
int foo( int * x )             // int foo(int & x)
{                              // {
  return (*x) * (*x);          //   return x * x;
}                              // }

int main()                     // int main()
{                              // {
  int y = 4;                   //   int y = 4;
  return foo( &y );            //   return foo(y);
}                              // }


