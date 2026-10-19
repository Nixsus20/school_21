#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int code = OK;
  if (check_matrix(A)) code = INCORRECT_MATRIX;
  if (code == OK) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && code == OK; i++) {
      for (int j = 0; j < A->columns && code == OK; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
        if (!isfinite(result->matrix[i][j])) code = INCORRECT_MATRIX;
      }
    }
  }

  return code;
}