#include "main.h"

#define SIZE_M 20

int main() {
  srand(time(NULL));
  matrix_t B = s21_create_matrix(SIZE_M, 2);

  for (int i = 100, j = 0; j < SIZE_M; i += 100, j++) {
    matrix_t A = s21_create_matrix(i, i);

    for (int i = 0; i < A.rows; i++) {
      for (int j = 0; j < A.columns; j++) {
        A.matrix[i][j] = rand() % 100 + 1;
      }
    }

    clock_t start_time = clock();
    double det = get_det(&A);
    double end_time = (clock() - start_time) / 1000000.0;

    B.matrix[j][0] = i;
    B.matrix[j][1] = end_time;

    s21_remove_matrix(&A);
  }

  save_to_file(B);
  s21_remove_matrix(&B);

  return 0;
}

void save_to_file(matrix_t A) {
  time_t times = time(NULL);
  struct tm *ptr = localtime(&times);
  char *name = asctime(ptr);

  FILE *fp = fopen(name, "w");

  for (int i = 0; i < SIZE_M; i++) {
    fprintf(fp, "%.2f %.2f\n", A.matrix[i][0], A.matrix[i][1]);
  }

  fclose(fp);
}

double get_det(matrix_t *A) {
  double det = 1.0;

  int swapCount = gauss_elim(A);
  for (int i = 0; i < A->rows; i++) {
    det = det * A->matrix[i][i];
  }
  return det * pow(-1, swapCount);
}

int gauss_elim(matrix_t *A) {
  int i, j, k;
  int swapCount = 0;
  for (i = 0; i < A->rows - 1; i++) {
    for (k = i + 1; k < A->rows; k++) {
      if (fabs(A->matrix[i][i]) < fabs(A->matrix[k][i])) {
        swapCount++;

        for (j = 0; j < A->rows; j++) {
          double temp;
          temp = A->matrix[i][j];
          A->matrix[i][j] = A->matrix[k][j];
          A->matrix[k][j] = temp;
        }
      }
    }

    for (k = i + 1; k < A->rows; k++) {
      double term = A->matrix[k][i] / A->matrix[i][i];
      for (j = 0; j < A->rows; j++) {
        A->matrix[k][j] = A->matrix[k][j] - term * A->matrix[i][j];
      }
    }
  }

  return swapCount;
}

matrix_t s21_create_matrix(int rows, int columns) {
  matrix_t A;

  if (rows > 0 && columns > 0) {
    A.columns = columns;
    A.rows = rows;
    A.matrix = fill_matrix(rows, columns);
  }

  return A;
}

double **fill_matrix(int rows, int cols) {
  double **nums = calloc(rows, sizeof(double *));

  for (int i = 0; i < rows; i++) {
    nums[i] = calloc(cols, sizeof(double));
  }

  return nums;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    if (A->matrix != NULL) free(A->matrix[i]);
  }
  if (A->matrix != NULL) free(A->matrix);
}
