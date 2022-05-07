// Libraries
#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int MAX_THREADS_PER_BLOCK;

// Constants
#define startSize 100
#define maxSize 400
#define step 10

int N = (maxSize - startSize) / step + 1;  // quantity of elements
// Filling up matrix with elements in range [1, 100]
float* fillUpMatrix(int size) {
  float* matrix = (float*)malloc(size * size * sizeof(float));

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      matrix[i * size + j] = rand() % 100 + 1;
    }
  }

  return matrix;
}

__global__ void multiplyDetWithElement(long double* det, float* matrix,
                                       int currentDiagonalElemIndex) {
  *det *= matrix[currentDiagonalElemIndex];  // multiplying determinant with
                                             // diagonal element
}

__global__ void fillCoefsArray(float* coefs, float* matrix, int size,
                               int currentDiagonalElemIndex,
                               int startNumber = 0) {
  int i = startNumber + blockDim.x * blockIdx.x +
          threadIdx.x;  // unique index for each coefficient
  int elemToZeroIndex = currentDiagonalElemIndex +
                        size * (i + 1);  // element that we want to cast to null

  coefs[(elemToZeroIndex / size) - 1] =
      -matrix[elemToZeroIndex] / matrix[currentDiagonalElemIndex];
}

__global__ void multiplyElemWithCoef(float* matrix, int size,
                                     int currentDiagonalElemRow, float* coefs,
                                     int startNumber = 0) {
  int number = startNumber + blockDim.x * blockIdx.x + threadIdx.x;
  int columnsCount = size - currentDiagonalElemRow;

  int row = currentDiagonalElemRow + 1 + (number / columnsCount);
  int column = currentDiagonalElemRow + (number % columnsCount);

  matrix[row * size + column] +=
      coefs[row - 1] * matrix[currentDiagonalElemRow * size + column];
}

void getNumberOfBlocksAndThreads(int elemsCount, int* blocks, int* threads,
                                 int* remains) {
  if (elemsCount < MAX_THREADS_PER_BLOCK) {
    *blocks = 1;
    *threads = elemsCount;
  } else {
    *blocks = elemsCount / MAX_THREADS_PER_BLOCK;
    *threads = MAX_THREADS_PER_BLOCK;
  }
  *remains = elemsCount - *blocks * *threads;
}

cudaError_t allocateMemory(float* matrix, float** gpuMatrix, int size,
                           float** gpuCoefs, long double** gpuDet) {
  // Allocating memory on GPU for determinant, matrix(1-dimension), coefficients
  cudaError_t status = cudaMalloc(gpuMatrix, size * size * sizeof(float));
  status = cudaMemcpy(*gpuMatrix, matrix, size * size * sizeof(float),
                      cudaMemcpyHostToDevice);

  status = cudaMalloc(gpuCoefs, (size - 1) * sizeof(float));

  status = cudaMalloc(gpuDet, 1 * sizeof(long double));
  long double det = 1;
  status = cudaMemcpy(*gpuDet, &det, 1 * sizeof(long double),
                      cudaMemcpyHostToDevice);

  return status;
}

long double gaussMethod(float* matrix, int size) {
  long double det = 1;

  long double* _det = nullptr;
  float* _matrix = nullptr;
  float* _coefs = nullptr;
  int error = 0;

  if (allocateMemory(matrix, &_matrix, size, &_coefs, &_det) != cudaSuccess) {
    error = 1;
  }

  for (int i = 0; i < size && !error; i++) {
    int curDiagonalElemIndex =
        i * size + i;  // Index of current diagonal element
    multiplyDetWithElement<<<1, 1>>>(
        _det, _matrix,
        curDiagonalElemIndex);  // Multiplying determinant with diagonal element

    int blocksCount, threadsCount, remains;
    getNumberOfBlocksAndThreads(size - i - 1, &blocksCount, &threadsCount,
                                &remains);

    fillCoefsArray<<<blocksCount, threadsCount>>>(_coefs, _matrix, size,
                                                  curDiagonalElemIndex);
    fillCoefsArray<<<1, remains>>>(_coefs, _matrix, size, curDiagonalElemIndex,
                                   blocksCount * threadsCount);

    int elemsCount = (size - 1 - i) *
                     (size - i);  // Elems that will be affected by iteration
    getNumberOfBlocksAndThreads(elemsCount, &blocksCount, &threadsCount,
                                &remains);

    cudaDeviceSynchronize();  // waiting for GPU done calculations

    multiplyElemWithCoef<<<blocksCount, threadsCount>>>(_matrix, size, i,
                                                        _coefs);
    multiplyElemWithCoef<<<1, remains>>>(_matrix, size, i, _coefs,
                                         blocksCount * threadsCount);

    cudaDeviceSynchronize();  // waiting for GPU done calculations
  }

  cudaMemcpy(&det, &_det[0], sizeof(long double), cudaMemcpyDeviceToHost);

  cudaFree(_matrix);
  cudaFree(_det);
  cudaFree(_coefs);
  return det;
}

int main() {
  srand(time(NULL));
  cudaDeviceProp deviceProp;
  cudaGetDeviceProperties(&deviceProp, 0);  // getting blocks size from GPU
  MAX_THREADS_PER_BLOCK = deviceProp.maxThreadsDim[0];

  for (int size = startSize, i = 0; size <= maxSize; size += step, i++) {
    float* matrix = fillUpMatrix(size);  // filling up the matrix

    cudaEvent_t start, stop;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);  // CUDA timers for calculating time

    //------
    cudaEventRecord(start, 0);
    gaussMethod(matrix, size);  // processing Gauss-method
    cudaEventRecord(stop, 0);
    //------

    cudaEventSynchronize(stop);

    float time = 0;
    cudaEventElapsedTime(&time, start, stop);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    free(matrix);
    printf("%d ", size);                      // matrix size
    printf("%.3f\n", time / CLOCKS_PER_SEC);  // calculation time
  }
  return 0;
}
