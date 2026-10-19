#include "s21_matrix.h"

void get_minor(const matrix_t *A, matrix_t *minor, int row, int col) {
  int m_row = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == row) continue;
    int m_col = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == col) continue;
      minor->matrix[m_row][m_col] = A->matrix[i][j];
      m_col++;
    }
    m_row++;
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int code = OK;
  if (check_matrix(A)) {
    code = INCORRECT_MATRIX;
  } else {
    if (A->rows != A->columns) code = CALCULATION_ERROR;
    if (A->rows == 1 || A->columns == 1) code = CALCULATION_ERROR;
    if (code == OK) {
      s21_create_matrix(A->rows, A->columns, result);
      matrix_t minor;
      s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
      for (int i = 0; i < A->rows && code == OK; i++) {
        for (int j = 0; j < A->columns && code == OK; j++) {
          get_minor(A, &minor, i, j);
          double minor_determinant = 0;
          s21_determinant(&minor, &minor_determinant);
          int sign = ((i + j) % 2 == 0) ? 1 : -1;
          result->matrix[i][j] = sign * minor_determinant;
        }
      }
      s21_remove_matrix(&minor);
    }
  }
  return code;
}