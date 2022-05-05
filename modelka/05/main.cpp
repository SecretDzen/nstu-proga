#include <math.h>
#include <stdio.h>

#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

#define SIZE 200

double func(double x) { return pow(2.0 * (x + 1.0), 3); }

int main() {
  double kx[SIZE] = {0};
  double ky[SIZE] = {0};

  double a = 0.0;
  double b = 0.316;

  double W = b;

  srand(time(NULL));

  for (int i = 0; i < SIZE; i++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    kx[i] = (double)rand() / RAND_MAX;
    ky[i] = (double)rand() / RAND_MAX;
  }

  for (int j = 0; j < SIZE; j++) {
    double x = a + kx[j] * (b - a);
    double y = W * ky[j];

    if (y <= func(x)) {
      std::cout << x << std::endl;
    }
  }

  return 0;
}
