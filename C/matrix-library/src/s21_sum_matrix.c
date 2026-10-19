#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = OK;
  if (check_matrix(A) || check_matrix(B)) {
    code = INCORRECT_MATRIX;
  }
  if (code == OK) {
    if (!eq_matrix_size(A, B)) {
      code = CALCULATION_ERROR;
    }
  }
  if (code == OK) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && code == OK; i++) {
      for (int j = 0; j < A->columns && code == OK; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        if (!isfinite(result->matrix[i][j])) code = INCORRECT_MATRIX;
      }
    }
  }
  return code;
}