#include "s21_matrix.h"

// = 5;
// = -10000;

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int matrix_status = OK;
  if (result == NULL || rows < 1 || columns < 1)
    matrix_status = INCORRECT_MATRIX;
  if (matrix_status == OK) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = malloc(sizeof(double *) * rows);

    if (result->matrix == NULL) matrix_status = INCORRECT_MATRIX;

    for (int i = 0; i < rows && matrix_status == OK; i++) {
      result->matrix[i] = malloc(sizeof(double *) * columns);
      if (result->matrix == NULL) matrix_status = INCORRECT_MATRIX;
    }

    for (int i = 0; i < rows && matrix_status == OK; i++) {
      for (int j = 0; j < columns && matrix_status == OK; j++) {
        result->matrix[i][j] = 1;
      }
    }
  }

  return matrix_status;
}