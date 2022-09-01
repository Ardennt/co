#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  FILE* my_file  = NULL;
  char* filename = argv[1];
  char buffer[256];
  
  if (NULL == (my_file = fopen(filename, "r"))) {
    printf("womp: failed to open %s\n", filename);
    exit(-1);
  }
  
  while (fgets(buffer, 256, my_file) != NULL) {
    char name[256];
    int age = 0;
    float height = 0.0;
    if (3 != sscanf(buffer, "%s %d %f", name, &age, &height)) {
      printf("womp: failed to parse line\n");
      exit(-1);
    }
    printf("%s is %d years old and %f feet tall.\n", name, age, height);
  }
  
  fclose(my_file);
  
  return 0;
}