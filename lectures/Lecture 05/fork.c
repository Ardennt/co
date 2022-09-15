#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> /* EXIT_SUCCESS */

int main(void) 
{

  if (fork())
    printf("I am the parent %d\n", getpid());
  else
    printf("I am the child %d\n", getpid());
  printf("Who am I?");
  return EXIT_SUCCESS;
}