/* lab03-cp3.c */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
/* Type your includes here. */

int main()
{

  // Open up the text file
  FILE* file = fopen("book-1984.txt", "r");
  if (file == NULL) {
    perror("fopen() failed");
    return EXIT_FAILURE;
  }

  /* Type your code here. */
  char line[128];

  while (fgets(line, 128, file)){
    if (strlen(line) == 1) continue;

    char* line_copy = calloc(128, sizeof(char));
    char *counter = line_copy;
    for (char* i = line; *i != '\0'; i++){
        if (isalnum(*i)) {
            *counter = *i;
            counter++;
        }
    }
    if (strcmp(line_copy, "Chapter2") == 0) break;
    printf("%s ", line_copy);
    printf("[%d alnum chars]\n", (int)strlen(line_copy));

  }
  
  fclose(file);

  return EXIT_SUCCESS;
}
