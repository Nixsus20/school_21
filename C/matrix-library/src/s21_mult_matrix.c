#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = OK;
  if (check_matrix(A) || check_matrix(B)) {
    code = INCORRECT_MATRIX;
  }
  if (code == OK) {
    if (A->columns != B->rows) {
      code = CALCULATION_ERROR;
    }
  }
  if (code == OK) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows && code == OK; i++) {
      for (int j = 0; j < B->columns && code == OK; j++) {
        double res = 0;
        for (int k = 0; k < A->columns; k++) {
          res += A->matrix[i][k] * B->matrix[k][j];
        }
        result->matrix[i][j] = res;
      }
    }
  }
  return code;
}