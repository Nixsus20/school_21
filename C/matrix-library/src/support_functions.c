#include "s21_matrix.h"

int eq_matrix_size(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (A->rows != B->rows || A->columns != B->columns) result = FAILURE;
  return result;
}

int check_matrix(matrix_t *matrix) {
  int result = OK;
  if (matrix == NULL || matrix->matrix == NULL || matrix->rows < 1 ||
      matrix->columns < 1)
    result = INCORRECT_MATRIX;
  return result;
}
