#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "include/mult.h"

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