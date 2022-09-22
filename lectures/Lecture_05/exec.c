#include <unistd.h>  /* exec, getcwd */
#include <stdio.h>   /* printf */
#include <stdlib.h> /* EXIT_SUCCESS */

/* Exec example code */
/* This program simply execs "/bin/ls" */

int main(void) {
  char buf[1000];

  printf("Here are the files in %s\n", getcwd(buf, 1000));
  execl("/bin/ls", "ls", "-al", NULL);
  printf("If exec works, this line won't be printed\n");

  return EXIT_SUCCESS;
}