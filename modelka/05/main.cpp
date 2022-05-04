#include <math.h>
#include <stdio.h>

#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

#define SIZE 200

double func(double x) { return pow(2.0 * x + 1.0, 0.25) - 1.0; }

int main() {
  double kx[SIZE] = {0};
  double ky[SIZE] = {0};

  double a = 0.0;
  double b = 0.316;

  double W = 0.0;

  srand(time(NULL));

  for (int i = 0; i < SIZE; i++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    kx[i] = (double)rand() / RAND_MAX;
    ky[i] = (double)rand() / RAND_MAX;
  }

  for (int i = 0; i < SIZE; i++) {
    double W_temp = func(ky[i]);
    if (W < W_temp) W = W_temp;
  }

  for (int j = 0; j < SIZE; j++) {
    double x = a * kx[j] + (b - a);
    double y = W * ky[j];

    if (y <= func(x)) {
      std::cout << y << std::endl;
    }
  }

  return 0;
}
