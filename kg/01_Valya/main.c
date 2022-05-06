#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double get_det(double** matrix, int size);
double** diagonal(double** matrix, int* swap_count, int size);
double** swap_lines(double** matrix, int i, int j, int size);
double** zeroing(double** matrix, int i, int size);
double** create_matrix(int rows, int cols);

#define M 25

int main() {
  srand(time(NULL));
  double** anwser = create_matrix(M, 2);

  for (int size = 100, n = 0; n < M; size += 100, n++) {
    double** matrix = create_matrix(size, size);

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        matrix[i][j] = rand() % 100 + 1;
      }
    }
    clock_t time = clock();
    get_det(matrix, size);
    anwser[n][0] = size;
    anwser[n][1] = (clock() - time) * 1.0 / CLOCKS_PER_SEC;

    for (int i = 0; i < size; i++) free(matrix[i]);
    free(matrix);
  }

  FILE *fp = fopen("data.txt", "w");
  for (int i = 0; i < M; i++) {
    fprintf(fp, "%.0f %.3f\n", anwser[i][0], anwser[i][1]);
  }
  fclose(fp);

  for (int i = 0; i < M; i++) free(anwser[i]);
  free(anwser);

  return 0;
}

double** create_matrix(int rows, int cols) {
  double** matrix = calloc(rows, sizeof(double*));
  for (int i = 0; i < rows; i++) {
    matrix[i] = calloc(cols, sizeof(double));
  }
  return matrix;
}

double get_det(double** matrix, int size) {
  double det = 1.0;
  int swap_count = 0;
  diagonal(matrix, &swap_count, size);
  for (int i = 0; i < size; i++) det = det * matrix[i][i];
  return det * pow(-1, swap_count);
}

double** diagonal(double** matrix, int* swap_count, int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = i + 1; j < size; j++) {
      if (fabs(matrix[i][i]) < fabs(matrix[j][i])) {
        (*swap_count)++;
        matrix = swap_lines(matrix, i, j, size);
      }
    }
    matrix = zeroing(matrix, i, size);
  }
  return matrix;
}

double** swap_lines(double** matrix, int i, int j, int size) {
  for (int k = 0; k < size; k++) {
    double temp;
    temp = matrix[i][k];
    matrix[i][k] = matrix[j][k];
    matrix[j][k] = temp;
  }
  return matrix;
}

double** zeroing(double** matrix, int i, int size) {
  for (int j = i + 1; j < size; j++) {
    double term = matrix[j][i] / matrix[i][i];
    for (int k = 0; k < size; k++) {
      matrix[j][k] = matrix[j][k] - term * matrix[i][k];
    }
  }
  return matrix;
}
