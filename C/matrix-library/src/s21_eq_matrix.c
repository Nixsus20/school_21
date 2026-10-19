#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (!eq_matrix_size(A, B)) result = FAILURE;
  for (int i = 0; i < A->rows && result == SUCCESS; i++) {
    for (int j = 0; j < A->columns && result == SUCCESS; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > S21_EPS) result = FAILURE;
    }
  }
  return result;
}