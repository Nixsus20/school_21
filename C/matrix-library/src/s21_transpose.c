#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int code = OK;
  if (check_matrix(A)) code = INCORRECT_MATRIX;
  if (code == OK) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows && code == OK; i++) {
      for (int j = 0; j < A->columns && code == OK; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return code;
}