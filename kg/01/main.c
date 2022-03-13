#include "main.h"

int main() {
  srand(time(NULL));
  matrix_t A = s21_create_matrix(10000, 10000);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = rand() % 100;
    }
  }

  printf("Counting...\n");
  double det = s21_determinant(&A);
  printf("Det is: %f\n", det);
  s21_remove_matrix(&A);
  return 0;
}

/**
 * @brief Вывод матрицы в консоль
 * @param A матрица, которую нужно вывести
 */
void print_matrix(matrix_t A) {
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      printf("%.2f", A.matrix[i][j]);
      printf(" ");
    }
    printf("\n");
  }
}

/**
 * @brief Инициализация нулевой матрицы
 * @param rows Столбцы (которые вниз)
 * @param columns Строки (которые вбок)
 * @return Пустую матрицу при верно переданных параметрах
 */
matrix_t s21_create_matrix(int rows, int columns) {
  matrix_t A;

  if (rows > 0 && columns > 0) {
    A.columns = columns;
    A.rows = rows;
    A.matrix_type = ZERO_MATRIX;
    A.matrix = fill_matrix(rows, columns);
  } else {
    set_to_incorrect(&A);
  }

  return A;
}

/**
 * @brief Удаление матрицы. Освобождение пространства
 * @param A матрица к обработке
 */
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix_type != INCORRECT_MATRIX) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix != NULL) free(A->matrix[i]);
    }

    if (A->matrix != NULL) free(A->matrix);
    A->matrix_type = INCORRECT_MATRIX;
  }
}
/**
 * @brief Являются ли матрицы идентичными
 * @param A первая матрица
 * @param B вторая матрица
 * @return 1 - одинаковы, 0 - разные
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;

  if (compare_matrix(A, B)) {
    for (int i = 0; i < A->rows && res; i++) {
      for (int j = 0; j < A->columns && res; j++) {
        double sub_num = (A->matrix[i][j]) - (B->matrix[i][j]);
        if (fabs(sub_num) >= EPS) res = FAILURE;
      }
    }
  } else {
    res = FAILURE;
  }

  return res;
}

/**
 * @brief Складываем матрицы
 * @param A первая матрица
 * @param B вторая матрица
 * @return Результат сложения
 */
matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B) {
  matrix_t res;

  if (compare_matrix(A, B)) {
    res = s21_create_matrix(A->rows, A->columns);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        res.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
    res.matrix_type = set_matrix_type(&res);
  } else {
    set_to_incorrect(&res);
  }

  return res;
}

/**
 * @brief Вычитание двух матриц
 * @param A первая матрица
 * @param B вторая матрица
 * @return Результат вычитания
 */
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {
  matrix_t res;

  if (compare_matrix(A, B)) {
    res = s21_create_matrix(A->rows, A->columns);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        res.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
    res.matrix_type = set_matrix_type(&res);
  } else {
    set_to_incorrect(&res);
  }

  return res;
}

/**
 * @brief Умножение матрицы на число
 * @param A матрица к обработке
 * @param number число, на которое надо умножить матрицу
 * @return Результат умножения
 */
matrix_t s21_mult_number(matrix_t *A, double number) {
  matrix_t res;

  if (valid_matrix(A)) {
    res = s21_create_matrix(A->rows, A->columns);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        res.matrix[i][j] = A->matrix[i][j] * number;
      }
    }
    res.matrix_type = set_matrix_type(&res);
  } else {
    set_to_incorrect(&res);
  }

  return res;
}

/**
 * @brief Умножение двух матриц
 * @param A первая матрица
 * @param B вторая матрица
 * @return Результат умножения
 */
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
  matrix_t res;

  if (valid_matrix(A) && valid_matrix(B) && A->columns == B->rows) {
    res = s21_create_matrix(A->rows, B->columns);

    for (int i = 0; i < res.rows; i++) {
      for (int j = 0; j < res.columns; j++) {
        double mul = 0.0;
        for (int k = 0; k < A->columns; k++) {
          mul += A->matrix[i][k] * B->matrix[k][j];
        }
        res.matrix[i][j] = mul;
      }
    }

    res.matrix_type = set_matrix_type(&res);
  } else {
    set_to_incorrect(&res);
  }

  return res;
}

/**
 * @brief Транспонирование матрицы
 * @param A матрица над которой будут совершена операция
 * @return Результат транспонирования
 */
matrix_t s21_transpose(matrix_t *A) {
  matrix_t res;

  if (valid_matrix(A)) {
    res = s21_create_matrix(A->columns, A->rows);

    for (int i = 0; i < res.rows; i++) {
      for (int j = 0; j < res.columns; j++) {
        res.matrix[i][j] = A->matrix[j][i];
      }
    }

    res.matrix_type = set_matrix_type(&res);
  } else {
    set_to_incorrect(&res);
  }

  return res;
}

/**
 * @brief Поиск алгебраических дополнений
 * @param A матрица над которой будут совершена операция
 * @return Результат поиска
 */
matrix_t s21_calc_complements(matrix_t *A) {
  matrix_t res;

  if (valid_matrix(A)) {
    res = s21_create_matrix(A->columns, A->rows);

    for (int i = 0; i < res.rows; i++) {
      for (int j = 0; j < res.columns; j++) {
        matrix_t minor = get_matrix_minor(A, i, j);
        res.matrix[i][j] = pow(-1, i + j) * s21_determinant(&minor);
        s21_remove_matrix(&minor);
      }
    }

    res.matrix_type = set_matrix_type(&res);
  } else {
    set_to_incorrect(&res);
  }

  return res;
}

/**
 * @brief Поиск определителя матрицы
 * @param A матрица над которой будут совершена операция
 * @return Определитель, если существует, иначе - 0.0
 */
double s21_determinant(matrix_t *A) {
  double res = 0.0;

  if (valid_matrix(A) && A->rows == A->columns) {
    if (A->rows == 1) res = A->matrix[0][0];
    if (A->rows == 2) {
      res = (A->matrix[0][0] * A->matrix[1][1]) -
            (A->matrix[0][1] * A->matrix[1][0]);
    }

    if (A->rows > 2) {
      for (int i = 0; i < A->rows; i++) {
        matrix_t minor = get_matrix_minor(A, i, 0);
        res += A->matrix[i][0] * pow(-1, i) * s21_determinant(&minor);
        s21_remove_matrix(&minor);
      }
    }
  }

  return res;
}

/**
 * @brief Инверсия матрицы
 * @param A матрица над которой будут совершена операция
 * @return Результат инверсии
 */
matrix_t s21_inverse_matrix(matrix_t *A) {
  matrix_t res;
  double determ = s21_determinant(A);

  if (fabs(determ) > EPS) {
    matrix_t minor = s21_calc_complements(A);
    matrix_t transp = s21_transpose(&minor);

    res = s21_mult_number(&transp, 1.0 / determ);
    s21_remove_matrix(&minor);
    s21_remove_matrix(&transp);
  } else {
    set_to_incorrect(&res);
  }

  return res;
}

/**
 * @brief Получение минора матрицы
 * @param A матрица над которой будут совершена операция
 * @param row Столбец к вычеркиванию
 * @param col Строка к вычеркиванию
 * @return Минор матрицы
 */
matrix_t get_matrix_minor(matrix_t *A, int row, int col) {
  matrix_t res = s21_create_matrix(A->rows - 1, A->columns - 1);

  for (int i = 0, a = 0; i < A->rows; i++) {
    if (i == row) continue;
    for (int j = 0, b = 0; j < A->columns; j++) {
      if (j == col) continue;
      res.matrix[a][b] = A->matrix[i][j];
      b++;
    }
    a++;
  }

  res.matrix_type = set_matrix_type(&res);
  return res;
}

/**
 * @brief Заполнение матрицы
 * @param rows Столбцы (которые вниз)
 * @param columns Строки (которые вбок)
 * @return Значения внутри матрицы
 */
double **fill_matrix(int rows, int cols) {
  double **nums = calloc(rows, sizeof(double *));

  for (int i = 0; i < rows; i++) {
    nums[i] = calloc(cols, sizeof(double));
  }

  return nums;
}

/**
 * @brief Является ли матрица валидной
 * @param A матрица проверка
 * @return 1 - валидная, 0 - неверная
 */
int valid_matrix(matrix_t *A) {
  int valid = A->matrix_type != INCORRECT_MATRIX ? 1 : 0;
  valid = (valid && A->rows > 0 && A->columns > 0) ? 1 : 0;
  valid = (valid && A != NULL) ? 1 : 0;
  valid = (valid && A->matrix != NULL) ? 1 : 0;

  return valid;
}

/**
 * @brief Являются ли размеры и типы матриц одинаковыми
 * @param A первая матрица
 * @param B вторая матрица
 * @return 1 - являются, 0 - не являются
 */
int compare_matrix(matrix_t *A, matrix_t *B) {
  int valid = valid_matrix(A);
  valid = (valid && valid_matrix(B)) ? 1 : 0;
  valid = (valid && A->columns == B->columns) ? 1 : 0;
  valid = (valid && A->rows == B->rows) ? 1 : 0;

  return valid;
}

/**
 * @brief Установка типа матрицы (использовать после сделанных вычислений)
 * @param A проверка матрицы
 * @return Какой тип необходимо установить
 */
int set_matrix_type(matrix_t *A) {
  int type = CORRECT_MATRIX;
  int is_zero = 1;
  int is_diag = 1;

  if (valid_matrix(A)) {
    if (A->columns == A->rows) {
      for (int i = 0; i < A->rows && is_diag; i++) {
        for (int j = 0; j < A->columns && is_diag; j++) {
          if (i == j && fabs(A->matrix[i][j] - 1.0) > EPS) is_diag = 0;
          if (i != j && fabs(A->matrix[i][j]) > EPS) is_diag = 0;
        }
      }
    } else {
      is_diag = 0;
    }

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j]) > EPS) is_zero = 0;
      }
    }
  } else {
    type = INCORRECT_MATRIX;
  }

  if (type != INCORRECT_MATRIX) {
    if (is_diag) type = IDENTITY_MATRIX;
    if (is_zero) type = ZERO_MATRIX;
  }

  return type;
}

/**
 * @brief Установка матрицы как невернозаданной
 * @param A матрица над которой будет совершена операция
 */
void set_to_incorrect(matrix_t *A) {
  A->columns = 0;
  A->rows = 0;
  A->matrix = 0;
  A->matrix_type = INCORRECT_MATRIX;
}
