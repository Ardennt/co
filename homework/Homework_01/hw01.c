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
#include <ctype.h> // for isdigit()

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
  if (mat->rows == 0 || mat->cols == 0) {
    printf("mm_alloc: allocation failed.\n");
    exit(-1);
  }

  mat->data = (double**)calloc(mat->rows, sizeof(double*));
  if (mat->data == NULL) {
    printf("mm_alloc: allocation failed.\n");
    exit(-1);
  }

  for (int i = 0; i < mat->rows; i++){
    mat->data[i] = (double*)calloc(mat->cols, sizeof(double));
    if (mat->data[i] == NULL){
      printf("mm_alloc: allocation failed.\n");
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

  free(mat->data);

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

  printf("\n/******** START of 2-D Matrix **********************************/\n");

  for (int i = 0; i < mat->rows; i++){
    for (int j = 0; j < mat->cols; j++){
      printf("%10.2lf\t", mat->data[i][j]);
    }
    printf("\n");
  }

  printf("/******** END of 2-D Matrix ************************************/\n");
  
  return 0;
}

// checks whether the rows and columns are strictly integers
// int check_rows_columns(char rows[15], char columns[15]){

//   for (int i = 0; i < strlen(rows); i++){
//     if (isdigit(rows[i]) == 0) {
//       return 0;
//     }
//   }

//   for (int i = 0; i < strlen(columns); i++){
//     if (isdigit(columns[i]) == 0) {
//       return 0;
//     }
//   }

//   return 1;
// }

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

matrix* mm_matrix_mult(matrix* mat1, matrix* mat2)
{
/*
Notes:
  First check that it is actually possible to multiply the two inputs
  If so, construct a result matrix
  Then perform the multiplication
  Then return a pointer to your result matrix
*/

  // check if it is possible to multiply the inputs
  if (mat1->cols != mat2->rows){
    printf("mm_matrix_mult: dimension mismatch between matrices.\n");
    exit(-1);
  }

  // malloc space for resultmatrix
  matrix* result_matrix = (matrix*)malloc(sizeof(matrix));
  result_matrix->rows = mat1->rows;
  result_matrix->cols = mat2->cols;

  // calloc space for the matrix
  result_matrix->data = (double**)calloc(result_matrix->rows, sizeof(double*));
  for (int i = 0; i < mat1->rows; i++){
    result_matrix->data[i] = (double*)calloc(result_matrix->cols, sizeof(double));
    if (result_matrix->data[i] == NULL){
      printf("mm_alloc: allocation failed.\n");
      exit(-1);
    }
  }

  // multiply
  for (int i = 0; i < result_matrix->rows; i++){
    for (int j = 0; j < result_matrix->cols; j++){
      double sum = 0.0;
      for (int k = 0; k < mat1->cols; k++) {
        sum += mat1->data[i][k] * mat2->data[k][j];
      }

      result_matrix->data[i][j] = sum;
    }
  }


  // returl matrix_mult
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
