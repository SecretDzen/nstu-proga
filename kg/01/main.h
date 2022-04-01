#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EPS 1e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

matrix_t s21_create_matrix(int rows, int columns);
void s21_remove_matrix(matrix_t *A);
double **fill_matrix(int rows, int cols);
double get_det(matrix_t *A);
void print_me(matrix_t A);
int gauss_elim(matrix_t *A);
void save_to_file(matrix_t A);

#endif  // SRC_S21_MATRIX_H_
