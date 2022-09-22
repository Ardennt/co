#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
  int* tmp;
  tmp = (int*)malloc(10*sizeof(int)); // allocate 10 integer array
  //  equivalent in C++ to int* tmp = new int[10];
 
  tmp[9] = 1;

  printf("at index %d is %d\n", 9, tmp[9]);

  free(tmp);
  // equivalent in C++ to delete [] tmp;

  return 0;
}
