/* lab03-cp1.c */
#include <stdio.h>
#include <stdlib.h>

/* Type your includes here. */

int main()
{
  FILE* file = fopen("lab03-data.dat", "r");  // man fopen 
  if (file == NULL) {
    perror("fopen() failed"); // use this if errno is set (see man page)
    return EXIT_FAILURE;
  }

  /* Type your code here. */

  int *intArr = calloc(744, sizeof(int));
  fread(intArr, sizeof(int), 744, file);
  
  for (int i = 0; i < 744; i++){
    printf("Data point #%3d: %d\n", i, intArr[i]);
  }
  
  fclose(file);

  return EXIT_SUCCESS;
}
