#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
  int duration;
  printf("sleepy.c is starting\n");
  sscanf(argv[1], "%d", &duration);
  sleep(duration);
  printf("sleepy.c is done\n");
}