#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int code = OK;
  if (A->rows != A->columns) code = INCORRECT_MATRIX;
  if (check_matrix(A)) code = INCORRECT_MATRIX;
  if (A->rows == 1)
    *result = A->matrix[0][0];
  else if (A->rows == 2)
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  else {
    double determinant = 0.0;
    matrix_t minor;
    s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
    for (int j = 0; j < A->columns; j++) {
      get_minor(A, &minor, 0, j);
      double minor_determinant;
      s21_determinant(&minor, &minor_determinant);
      int sign = (j % 2 == 0) ? 1 : -1;
      determinant += sign * A->matrix[0][j] * minor_determinant;
    }
    s21_remove_matrix(&minor);
    *result = determinant;
  }
  return code;
}