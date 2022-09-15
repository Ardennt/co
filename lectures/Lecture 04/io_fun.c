#include <stdio.h>
#include <stdlib.h>

int main()
{
  char buffer[256];
  scanf("%s", buffer);

  FILE* my_file = fopen("io_fun.txt", "w");

  // write to file
  fprintf(my_file, "%s\n", buffer);
  fclose(my_file);

  // write to standard output
  fprintf(stdout, "%s\n", buffer);
  printf("%s\n", buffer); // this is the same as above

  // write to standard error
  fprintf(stderr, "%s\n", buffer);

  return 0;
}
