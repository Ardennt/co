#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  float x;
  printf( "Enter a number: ");
  scanf("%f", &x);
  printf( "The square root of %f is %f\n", x, sqrt( x ) );
}

