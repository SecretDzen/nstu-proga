#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define MIN_SIZE 50
#define MAX_SIZE 2000
#define STEP 50

int N = (MAX_SIZE - MIN_SIZE) / STEP + 1;

double* create_matrix(int size) {
  double* matrix = (double*)malloc(sizeof(double) * size * size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrix[i * size + j] = rand() % 100 + 1;
    }
  }

  return matrix;
}

double get_det_gpu(double* matrix, int size) {
    dim3 BLOCKS_1D(16);
  dim3 THREADS_1D(32);
  dim3 BLOCKS_2D(16, 16);
  dim3 THREADS_2D(32, 32);

  double det = 1.0;
  double dev_det = 1.0;
  double* dev_matrix;
  int swap_count = 0;

  cudaMalloc(&dev_matrix, sizeof(double) * size * size);
  cudaMemcpy(dev_matrix, matrix, sizeof(double) * size * size,
             cudaMemcpyHostToDevice);

  for (int i = 0; i < size; i++) {
    max_in_column<<<1, 1>>>(dev_matrix, size, i);
    swap_lines<<<BLOCKS_1D, THREADS_1D>>>(dev_matrix, size, i);
    subtract_below<<<BLOCKS_2D, THREADS_2D>>>(dev_matrix, dev_identity, n, i);
    nullify_below<<<BLOCKS_1D, THREADS_1D>>>(dev_matrix, n, i);
    cudaDeviceSynchronize();

  }

  cudaMemcpy(&det, &dev_det, sizeof(long double), cudaMemcpyDeviceToHost);

  cudaFree(dev_matrix);
  return det * pow(-1, swap_count);
}

int main() {
  srand(time(NULL));

  for (int size = MIN_SIZE, i = 0; size <= MAX_SIZE; size += STEP, i++) {
    double* matrix = create_matrix(size);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start, 0);
    get_det_gpu(matrix, size);
    cudaEventRecord(stop, 0);

    cudaEventSynchronize(stop);

    float time;
    cudaEventElapsedTime(&time, start, stop);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    free(matrix);
    printf("%d ", size);
    printf("%.3f\n", time / CLOCKS_PER_SEC);
  }
  return 0;
}
