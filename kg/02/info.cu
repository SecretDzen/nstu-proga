#include <cuda.h>

#include <iostream>

int main() {
  cudaDeviceProp dev_prop;
  cudaGetDeviceProperties(&dev_prop, 0);
  printf("Device name: %s\n", dev_prop.name);

  printf("Max threads dimensions: x = %d, y = %d, z = %d\n",
         dev_prop.maxThreadsDim[0], dev_prop.maxThreadsDim[1],
         dev_prop.maxThreadsDim[2]);

  printf("Max grid size: x = %d, y = %d, z = %d\n", dev_prop.maxGridSize[0],
         dev_prop.maxGridSize[1], dev_prop.maxGridSize[2]);
}