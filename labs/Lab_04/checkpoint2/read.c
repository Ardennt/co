#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "include/read.h"

int mm_read(char* filename, matrix* mat) 
{
/*
Notes:
  Use fopen to open the matrix file, then use fgets or getline to read lines
  The first line of the matrix contains integers for "#rows #columns"
  - Use these to allocate your arrays for matrix data
  Each subsequent line contains a single data value
  - You can use sscanf to parse each matrix entry
  - First value is data[0][0], next is data[0][1] ... data[#rows-1][#columns-1]
*/

  FILE *in_file = fopen(filename, "r");

  // if the file has not been read properly
  if (in_file == NULL) {
    printf("mm_read: failed to open file.\n");
    exit(-1);
  }

  // get rows and columns
  char row_and_col[50];
  fgets(row_and_col, sizeof(row_and_col), in_file);
  int r, c;
  
  int success = sscanf(row_and_col, "%d %d", &r, &c);
  // file is empty
  if (success == 0) {
    printf("mm_read: failed to read from file.\n");
    exit(-1);
  } else if (success != 2) {
    printf("mm_read: failed to read matrix dimensions.\n");
    exit(-1);
  }

  mat->rows = r;
  mat->cols = c;
  // allocate space
  mm_alloc(mat);

  // add matrix data
  for (int i = 0; i < r; i++){
    for (int j = 0; j < c; j++){
      double tmp;
      if (fscanf(in_file, "%lf", &tmp) != 1) {
        printf("mm_read: failed to read matrix values.\n");
        exit(-1);
      }
      mat->data[i][j] = tmp;
    }
  }
  fclose(in_file);
  return 0;
}