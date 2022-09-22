#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv, char **envp)
{
  long i;
  printf("slow.c is starting\n");
  for (i = 0; i < 1000000000; ++i) sin(i);
  printf("slow.c is done\n");
  return EXIT_SUCCESS;
}