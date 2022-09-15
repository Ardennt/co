#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  int i;
  for ( i = 1 ; i < 5 ; i++ )
  {
    printf( "%2d %f %20.15f\n", i, sqrt(i), sqrt(i) );
    printf( "%2d %f %-20.15f\n", i, sqrt(i), sqrt(i) );
    printf( "%2d %f %-20.50f\n", i, sqrt(i), sqrt(i) );
  }

  float f = 100.0123151;
  printf("printf is fun %.0f%%\n", f);
}
