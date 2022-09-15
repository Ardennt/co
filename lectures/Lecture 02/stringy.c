#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
  if (argc < 2) {
    printf( "Invalid usage - must supply a string\n" );
    return -1;
  }
  
  char* token = strtok(argv[1], " ");
  while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, " ");
  }
  printf("%s\n", argv[1]);
  
  return 0;
}