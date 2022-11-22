// 30. Вычислить произведение двух заданных полиномов N переменных
#include <iostream>
#include <limits.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int MAX_DEG = 1; //максимальное значение степени полинома
int MAX_COEF = 100; //максимальное значение коэффициентов

/*
Введём вероятносный фактор:
в 30% степень будет равна 0
ещё в 30% степень будет равна 1
в оставшихся 40% степень равна произвольному числу из диапазона 0..MAX_DEG
*/
int rand_deg() {
  int c = rand() % 10;

  if (c < 3)
    return 0;
  if (c < 6)
    return 1;

  return rand() % MAX_DEG + 1;
}

/*
Инициализация полинома
p - матрица полинома, в которой каждая строка представляет моном, 0-й элемент в
строке означает коэффициент перед мономом, а все последующие элементы строки
означают степени при отдельных переменных в мономе pn - количество мономов
(строк) n - количество переменных + 1 (столбцов)
*/
void pinit(int *p, int pn, int n) {
  for (int i = 0; i < pn; i++) {
    p[i * n] = rand() % MAX_COEF;
    for (int j = 1; j < n; j++)
      p[i * n + j] = rand_deg();
  }
}

/*
Проверка двух мономов на подобность
(начинаем с 1-го элемента т.к. в 0-м хранится коеффициент)
*/
bool is_sim(int *p, int frst, int scnd, int n) {
  for (int i = 1; i < n; i++) {
    if (p[frst + i] != p[scnd + i])
      return false;
  }
  return true;
}

void pprint(int *p, int mon, int varn) {
  fprintf(stdout, "\n");
  for (int i = 0; i < mon; i++) {
    if (p[i * varn] != INT_MAX) {
      for (int j = 0; j < varn; j++) {
        fprintf(stdout, "%d ", p[i * varn + j]);
      }
      fprintf(stdout, "\n");
    }
  }
}

bool compare(int *p1, int *p2, int var_n, int mon_n) {
  for (int i = 0; i < mon_n; i++) {
    for (int j = 0; j < var_n; j++) {
      if (p1[i * var_n + j] != p2[i * var_n + j])
        return false;
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  int myid, numprocs, namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  char *p, *p2;

  int var_n = strtol(argv[1], &p, 10), mon_n = strtol(argv[2], &p2, 10);
  double st, fn;
  int err;

  fprintf(stdout, "%d \n", var_n);

  int *poly1 = new int[mon_n * var_n];
  int *poly2 = new int[mon_n * var_n];
  int *result = new int[mon_n * mon_n * var_n];
  int *presult = new int[mon_n * mon_n * var_n];
  pinit(poly1, mon_n, var_n);
  pinit(poly2, mon_n, var_n);

  err = MPI_Init(&argc, &argv);
  if (err != MPI_SUCCESS) {
    fprintf(stdout, "Init failed\n");
    fflush(stdout);
  }

  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Get_processor_name(processor_name, &namelen);

  err = MPI_Barrier(MPI_COMM_WORLD);
  if (err != MPI_SUCCESS) {
    fprintf(stdout, "Barrier failed: %d\n", myid);
    fflush(stdout);
  }

  if (myid == 0)
    st = MPI_Wtime();

  //параллельные вычисления
  for (int _i = myid; _i < mon_n; _i += numprocs) {
    for (int _j = 0; _j < mon_n; _j++) {
      presult[(_i * mon_n + _j) * var_n] =
          poly1[_i * var_n] * poly2[_j * var_n];
      for (int v = 1; v < var_n; v++) {
        presult[(_i * mon_n + _j) * var_n + v] =
            poly1[_i * var_n + v] + poly2[_j * var_n + v];
      }
    }
  }

  for (int i = 0; i < mon_n * mon_n - 1; i++) {
    if (presult[i * var_n] != INT_MAX) {
      for (int j = i + 1; j < mon_n * mon_n; j++) {
        if (presult[j * var_n] != INT_MAX) {
          if (is_sim(presult, i * var_n, j * var_n, var_n)) {
            presult[i * var_n] += presult[j * var_n];
            presult[j * var_n] = INT_MAX;
          }
        }
      }
    }
  }

  if (myid == 0) {
    fn = MPI_Wtime();
    pprint(presult, mon_n, var_n);
    fprintf(stdout, "parallel time: %f\n", fn - st);
    fflush(stdout);
  }

  //Последовательные вычисления
  if (myid == 0) {
    st = MPI_Wtime();
    for (int _i = 0; _i < mon_n; _i++) {
      for (int _j = 0; _j < mon_n; _j++) {
        result[(_i * mon_n + _j) * var_n] =
            poly1[_i * var_n] * poly2[_j * var_n];
        for (int v = 1; v < var_n; v++) {
          result[(_i * mon_n + _j) * var_n + v] =
              poly1[_i * var_n + v] + poly2[_j * var_n + v];
        }
      }
    }

    for (int i = 0; i < mon_n * mon_n - 1; i++) {
      if (result[i * var_n] != INT_MAX) {
        for (int j = i + 1; j < mon_n * mon_n; j++) {
          if (result[j * var_n] != INT_MAX) {
            if (is_sim(result, i * var_n, j * var_n, var_n)) {
              result[i * var_n] += result[j * var_n];
              result[j * var_n] = INT_MAX;
            }
          }
        }
      }
    }

    fn = MPI_Wtime();
    pprint(result, mon_n, var_n);
    fprintf(stdout, "time: %f\n", fn - st);
    fflush(stdout);

    if (compare(result, presult, var_n, mon_n)) {
      fprintf(stdout, "results is equals!\n");
      fflush(stdout);
    } else {
      fprintf(stdout, "results is not equals!\n");
      fflush(stdout);
    }
  }
  MPI_Barrier(MPI_COMM_WORLD);

  err = MPI_Finalize();
  if (err != MPI_SUCCESS) {
    fprintf(stdout, "Finalize failed\n");
    fflush(stdout);
  }

  //освобождение памяти
  delete[] poly1;
  delete[] poly2;
  delete[] result;
  delete[] presult;
  return 0;
}