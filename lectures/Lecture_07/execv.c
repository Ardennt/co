#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
{
  char* argument_list[] = {"ls", "-al", NULL};
  if (!fork()) {
    execvp("ls", argument_list);
  }
  else {
    printf("Parent\n");
    //sleep(1);
  }
  printf("Unreachable\n");
  return EXIT_SUCCESS;







/*  pid_t pid;
  int status;
  char* argument_list[] = {"ls", "-al", NULL};

  if ((pid = fork()) < 0) {
    printf("*** ERROR: forking child process failed\n");
    return EXIT_FAILURE;
  }
  else if (pid == 0) {
    if (execvp(argument_list[0], argument_list) < 0) {
      printf("*** ERROR: exec failed\n");
      return EXIT_FAILURE;
    }
  }
  else {
    printf("Parent\n");
    while (wait(&status) != pid) ;
  }
  printf("Unreachable\n");
  return EXIT_SUCCESS;*/



/*    char* command = "ls";
    char* argument_list[] = {"ls", "-l", NULL};
 
    printf("Before calling execvp()\n");
 
    printf("Creating another process using fork()...\n");
 
    if (fork() == 0) {
        // Newly spawned child Process. This will be taken over by "ls -l"
        int status_code = execvp(command, argument_list);
 
        printf("ls -l has taken control of this child process. This won't execute unless it terminates abnormally!\n");
 
        if (status_code == -1) {
            printf("Terminated Incorrectly\n");
            return 1;
        }
    }
    else {
        // Old Parent process. The C program will come here
        printf("This line will be printed\n");
    }
 
    return 0;*/


}