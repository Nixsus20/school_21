#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int code = OK;
  if (check_matrix(A)) code = INCORRECT_MATRIX;
  if (code == OK) {
    if (A->rows != A->columns) code = CALCULATION_ERROR;
    double determinant;
    s21_determinant(A, &determinant);
    if (determinant == 0) code = CALCULATION_ERROR;
    if (code == OK) {
      matrix_t complements, transposed;
      s21_create_matrix(A->rows, A->columns, &complements);
      s21_create_matrix(A->rows, A->columns, &transposed);
      s21_calc_complements(A, &complements);
      s21_transpose(&complements, &transposed);
      s21_mult_number(&transposed, 1.0 / determinant, result);
      s21_remove_matrix(&complements);
      s21_remove_matrix(&transposed);
    }
  }
  return code;
}
