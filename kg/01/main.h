#ifndef  SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#define EPS 1e-7

typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;

matrix_t s21_create_matrix(int rows, int columns);
void s21_remove_matrix(matrix_t *A);

#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_mult_number(matrix_t *A, double number);
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_transpose(matrix_t *A);
matrix_t s21_calc_complements(matrix_t *A);
double s21_determinant(matrix_t *A);
matrix_t s21_inverse_matrix(matrix_t *A);

// ADDITIONAL FUNCTIONS

double **fill_matrix(int rows, int cols);
void print_matrix(matrix_t A);
int valid_matrix(matrix_t *A);
int compare_matrix(matrix_t *A, matrix_t *B);
int set_matrix_type(matrix_t *A);
void set_to_incorrect(matrix_t *A);
matrix_t get_matrix_minor(matrix_t *A, int row, int col);
void print_matrix(matrix_t A);

#endif  // SRC_S21_MATRIX_H_
