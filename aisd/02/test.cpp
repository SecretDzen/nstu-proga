#include <stdlib.h>

#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

#include "bst_tree.hpp"

using namespace std;
bst_tree<int> one;
bst_tree<int> two;

#define N 100

int main() {
  srand(time(NULL));
  clock_t start;

  start = clock();
    int count = 0;
  while (true) {
    count++;
    int key = rand() % (N * 10);
    one.insert(key);
    if (one.get_size() >= N) break;
    this_thread::sleep_for(chrono::milliseconds(1));
  }
  cout << "Time insert: " << (clock() - start) / ((double)count * 100.0) << " ms" << endl;

  int key = 0;
  start = clock();
  while (key < N) two.insert(key++);
  cout << "Time insert: " << (clock() - start) / (100.0) << " ms" << endl;

  int key_to_del = rand() % (N * 10);

  start = clock();
  one.erase(key_to_del);
  cout << "Time erase: " << (clock() - start) / (100.0) << " ms" << endl;

  start = clock();
  two.erase(key_to_del);
  cout << "Time erase: " << (clock() - start) / (100.0) << " ms" << endl;

  start = clock();
  int key_to_find = rand() % (N * 10);
  one.find(key_to_find);
  cout << "Time find: " << (clock() - start) / (100.0) << " ms" << endl;

  start = clock();
  two.find(key_to_find);
  cout << "Time find: " << (clock() - start) / (100.0) << " ms" << endl;

  return 0;
}
