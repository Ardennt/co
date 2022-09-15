#include <unistd.h>    /* exec, getcwd */
#include <stdio.h>     /* printf */
#include <sys/types.h> /* need for wait */
#include <sys/wait.h>  /* wait() */
#include <stdlib.h> /* EXIT_SUCCESS */

void child(void) {
  int pid = getpid();

  printf("Child process PID is %d\n", pid);
  printf("Child now ready to exec ls\n");
  execl("/bin/ls", "ls", NULL);

}

void parent(void) {
  int pid = getpid();
  int stat;

  printf("Parent process PID is %d\n", pid);
  printf("Parent is waiting for child\n");
  wait(&stat);
  printf("Child is done. Parent is now transporting to surface\n");

}

int main(void) {
  printf("In main - starting things with a fork()\n");
  pid_t f_pid = fork();
  if (f_pid) {
    printf("In parent - fork() returned %d\n", f_pid);
    parent();
  } else {
    printf("In child - fork() returned %d\n", f_pid);
    child();
  }
  printf("Done in main()\n");

  return EXIT_SUCCESS;
}