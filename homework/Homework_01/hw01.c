/* 
Assignment 1: NxM Matrix Multiplication 
CSCI-2500 Fall 2021
*/

/******************************************************************************/
/* Usual suspects to include  */
/******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

/******************************************************************************/
/* Function Calls */
/******************************************************************************/

typedef struct{
  double** data;
  int rows;
  int cols;
} matrix; 

int mm_alloc(matrix* mat);
int mm_free (matrix* mat);
int mm_print(matrix* mat);
int mm_read (char* filename, matrix* mat);
matrix* mm_matrix_mult(matrix* mat1, matrix* mat2);


int mm_alloc(matrix* mat)
{
/*
Notes:
  Allocate an array of pointers to a double
  Then, allocate an row/array of doubles and assign each double pointer that row
  Make sure you're allocating using mat->data in the matrix struct
  You can use calloc for allocation and zeroing out all the bytes
  - otherwise, you'd want to manually set all arrays to 0 (good practice)
  If your malloc/calloc returns null, the allocation failed
*/

  for (int i = 0; i < mat->rows; i++){
    mat->data[i] = (double*)calloc(mat->cols, sizeof(double));
    if (mat->data[i] == NULL){
      perror("mm_alloc: allocation failed.");
      exit(-1);
    }
  }
  
  return 0;
}

int mm_free(matrix* mat)
{
  /*
  Notes:
  Reverse the allocation process, but you'll be calling free() instead
  */
  for (int i = 0; i < mat->rows; i++){
    free(mat->data[i]);
    mat->data[i] = NULL;
  }

  return 0;
}

int mm_print(matrix* mat)
{
/*
Notes:
  Print all the data values in your matrix
  Go row by row
  At the end of each row, print a newline
  Between each data value, insert a tab
  Use 2 digits of precision after the decimal (use "%10.2lf\t" as format string)
  See output.txt for expected output formatting
*/

  for (int i = 0; i < mat->rows; i++){
    for (int j = 0; j < mat->cols; j++){
      printf("%10.2lf/t", mat->data[i][j]);
    }
    printf("\n");
  }
  
  return 0;
}

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
    perror("mm_read: failed to open file.");
    exit(-1);
  }

  // get rows and columns
  int r = -1;
  int c;
  // check if the rows and columns are read successfully
  if (fscanf(in_file, "%d %d", &r, &c) != 2) {
    perror("mm_read: failed to read matrix dimensions.");
    exit(-1);
  }
  // if r is not changed, then the file is empty
  if (r == -1) {
    perror("mm_read: failed to read from file.");
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
        perror("mm_read: failed to read matrix values.");
        exit(-1);
      }
      mat->data[i][j] = tmp;
    }
  }
  
  return 0;
}

matrix* mm_matrix_mult(matrix* mat1, matrix* mat2)
{
/*
Notes:
  First check that it is actually possible to multiply the two inputs
  If so, construct a result matrix
  Then perform the multiplication
  Then return a pointer to your result matrix
*/
  return result_matrix;
}

int main()
{
  /*
   * you must keep this function AS IS. 
   * you cannot modify it!
   */
  char filename_A[256];
  char filename_B[256];
  matrix* A = (matrix*)malloc(sizeof(matrix));
  matrix* B = (matrix*)malloc(sizeof(matrix));
  matrix* C = NULL;

  printf("Please enter the matrix A data file name: ");
  if (1 != scanf("%s", filename_A)) {
    printf("main: scanf failed to read filename\n");
    exit(-1);
  }
  mm_read(filename_A, A);
  mm_print(A);
  
  printf("Please enter the matrix B data file name: ");
  if (1 != scanf("%s", filename_B)) {
    printf("main: scanf failed to read filename\n");
    exit(-1);
  }
  mm_read(filename_B, B);
  mm_print(B);
  
  C = mm_matrix_mult(A, B);
  mm_print(C);

  mm_free(A);
  mm_free(B);
  mm_free(C);
  free(A);
  free(B);
  free(C);
  
  return 0;
}
