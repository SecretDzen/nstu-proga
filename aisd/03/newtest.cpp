
#include <time.h>

#include <cmath>
#include <iostream>

#include "avl_tree.hpp"
using namespace std;
typedef unsigned long long INT_64;

//переменная и константы генератора LineRand()
static INT_64 RRand = 15750;
const INT_64 mRand = (1ULL << 63) - 1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;

//функция установки первого случайного числа от часов компьютера
void sRand() {
  srand(time(0));
  RRand = (INT_64)rand();
}

//функция генерации случайного числа
//линейный конгруэнтный генератор    Xi+1=(a*Xi+c)%m
// habr.com/ru/post/208178
INT_64 LineRand() {
  INT_64 y1, y2;
  y1 = (aRand * RRand + cRand) % mRand;
  y2 = (aRand * y1 + cRand) % mRand;
  RRand = (y1 & 0xFFFFFFFF00000000LL) ^ (y2 & 0xFFFFFFFF00000000LL) >> 32;
  return RRand;
}

void test_rand_bts(int n) {
  //создание дерева для 64 – разрядных ключей типа INT_64
  bst_tree<INT_64> tree;
  //массив для ключей, которые присутствуют в дереве
  INT_64* m = new INT_64[n];
  //установка первого случайного числа
  sRand();
  //заполнение дерева и массива элементами со случайными ключами
  for (int i = 0; i < n; i++) {
    m[i] = LineRand();
    tree.insert(m[i]);
  }
  //вывод размера дерева до теста
  cout << "items count:" << tree.get_size() << endl;
  //обнуление счётчиков трудоёмкости вставки, удаления и поиска
  double I = 0;
  double D = 0;
  double S = 0;
  //генерация потока операций, 10% - промахи операций
  for (int i = 0; i < n / 2; i++)
    if (i % 10 == 0)  // 10% промахов
    {
      tree.erase(LineRand());
      D += tree.CountNodes();
      tree.insert(m[rand() % n]);
      I += tree.CountNodes();
      try {
        tree.find(LineRand());
        S += tree.CountNodes();
      }
      //обработка исключения при ошибке операции поиска
      catch (overflow_error& err) {
        S += tree.CountNodes();
      }
    } else  // 90% успешных операций
    {
      int ind = rand() % n;
      tree.erase(m[ind]);
      D += tree.CountNodes();
      INT_64 key = LineRand();
      tree.insert(key);
      I += tree.CountNodes();
      m[ind] = key;
      try {
        tree.find(m[rand() % n]);
        S += tree.CountNodes();
      }
      //обработка исключения при ошибке операции поиска
      catch (overflow_error& err) {
        S += tree.CountNodes();
      }
    }  //конец теста

  //вывод результатов:
  //вывод размера дерева после теста
  cout << "items count:" << tree.get_size() << endl;
  //теоретической оценки трудоёмкости операций BST
  cout << "1.39*log2(n)=" << 1.39 * (log((double)n) / log(2.0)) << endl;
  //экспериментальной оценки трудоёмкости вставки
  cout << "Count insert: " << I / (n / 2) << endl;
  //экспериментальной оценки трудоёмкости удаления
  cout << "Count erase: " << D / (n / 2) << endl;
  //экспериментальной оценки трудоёмкости поиска
  cout << "Count search: " << S / (n / 2) << endl;
  //освобождение памяти массива m[]
  delete[] m;
}

void test_rand_avl(int n) {
  //создание дерева для 64 – разрядных ключей типа INT_64
  avl<INT_64> tree;
  //массив для ключей, которые присутствуют в дереве
  INT_64* m = new INT_64[n];
  //установка первого случайного числа
  sRand();
  //заполнение дерева и массива элементами со случайными ключами
  for (int i = 0; i < n; i++) {
    m[i] = LineRand();
    tree.insert(m[i]);
  }
  //вывод размера дерева до теста
  cout << "items count:" << tree.get_size() << endl;
  //обнуление счётчиков трудоёмкости вставки, удаления и поиска
  double I = 0;
  double D = 0;
  double S = 0;
  //генерация потока операций, 10% - промахи операций
  for (int i = 0; i < n / 2; i++)
    if (i % 10 == 0)  // 10% промахов
    {
      tree.erase(LineRand());
      D += tree.CountNodes();
      tree.insert(m[rand() % n]);
      I += tree.CountNodes();
      try {
        tree.find(LineRand());
        S += tree.CountNodes();
      }
      //обработка исключения при ошибке операции поиска
      catch (overflow_error& err) {
        S += tree.CountNodes();
      }
    } else  // 90% успешных операций
    {
      int ind = rand() % n;
      tree.erase(m[ind]);
      D += tree.CountNodes();
      INT_64 key = LineRand();
      tree.insert(key);
      I += tree.CountNodes();
      m[ind] = key;
      try {
        tree.find(m[rand() % n]);
        S += tree.CountNodes();
      }
      //обработка исключения при ошибке операции поиска
      catch (overflow_error& err) {
        S += tree.CountNodes();
      }
    }  //конец теста

  //вывод результатов:
  //вывод размера дерева после теста
  cout << "items count:" << tree.get_size() << endl;
  //теоретической оценки трудоёмкости операций BST
  cout << "log2(n) + 0.25 =" << (log((double)n) / log(2.0)) + 0.25 << endl;
  //экспериментальной оценки трудоёмкости вставки
  cout << "Count insert: " << I / (n / 2) << endl;
  //экспериментальной оценки трудоёмкости удаления
  cout << "Count erase: " << D / (n / 2) << endl;
  //экспериментальной оценки трудоёмкости поиска
  cout << "Count search: " << S / (n / 2) << endl;
  //освобождение памяти массива m[]
  delete[] m;
}

void test_ord_bts(int n) {
  //создание дерева для 64 – разрядных ключей типа INT_64
  bst_tree<INT_64> tree;
  //массив для ключей, которые присутствуют в дереве
  INT_64* m = new INT_64[n];

  //заполнение дерева и массива элементами с возрастающими чётными //ключами на
  //интервале [0, 10000, 20000, ... ,10000*n]
  for (int i = 0; i < n; i++) {
    m[i] = i;
    tree.insert(m[i]);
  }
  //вывод размера дерева до теста
  cout << "items count:" << tree.get_size() << endl;
  //обнуление счётчиков трудоёмкости вставки, удаления и поиска
  double I = 0;
  double D = 0;
  double S = 0;
  //установка первого случайного числа
  sRand();
  //генерация потока операций, 10% - промахи операций
  for (int i = 0; i < n / 2; i++) {
    if (i % 10 == 0)  // 10% промахов
    {
      int k = LineRand() % (n);
      k = k + !(k % 2);  //случайный нечётный ключ
      tree.erase(k);
      D += tree.CountNodes();
      tree.insert(m[rand() % n]);
      I += tree.CountNodes();
      k = LineRand() % (n);
      k = k + !(k % 2);  // случайный нечётный ключ
      try {
        tree.find(k);
        S += tree.CountNodes();
      }
      //обработка исключения при ошибке операции поиска
      catch (overflow_error& err) {
        S += tree.CountNodes();
      }
    } else  // 90% успешных операций
    {
      int ind = rand() % n;
      tree.erase(m[ind]);
      D += tree.CountNodes();
      ;
      int k = LineRand() % (n);
      k = k + k % 2;  // случайный чётный ключ
      tree.insert(k);
      I += tree.CountNodes();
      ;
      m[ind] = k;
      try {
        tree.find(m[rand() % n]);
        S += tree.CountNodes();
        ;
      }
      //обработка исключения при ошибке операции поиска
      catch (overflow_error& err) {
        S += tree.CountNodes();
      }
    }
  }
  //вывод результатов:
  // вывод размера дерева после теста
  cout << "items count:" << tree.get_size() << endl;
  //теоретической оценки трудоёмкости операций BST
  cout << "n/2 =" << n / 2 << endl;
  //экспериментальной оценки трудоёмкости вставки
  cout << "Count insert: " << I / (n / 2) << endl;
  //экспериментальной оценки трудоёмкости удаления
  cout << "Count erase: " << D / (n / 2) << endl;
  //экспериментальной оценки трудоёмкости поиска
  cout << "Count search: " << S / (n / 2) << endl;
  //освобождение памяти массива m[]
  delete[] m;
}  //конец теста

void test_ord_avl(int n) {
  //создание дерева для 64 – разрядных ключей типа INT_64
  avl<INT_64> tree;
  //массив для ключей, которые присутствуют в дереве
  INT_64* m = new INT_64[n];

  //заполнение дерева и массива элементами с возрастающими чётными //ключами на
  //интервале [0, 10000, 20000, ... ,10000*n]
  for (int i = 0; i < n; i++) {
    m[i] = i;
    tree.insert(i);
  }
  //вывод размера дерева до теста
  cout << "items count:" << tree.get_size() << endl;
  //обнуление счётчиков трудоёмкости вставки, удаления и поиска
  double I = 0;
  double D = 0;
  double S = 0;
  //установка первого случайного числа
  sRand();
  //генерация потока операций, 10% - промахи операций
  for (int i = 0; i < n / 2; i++) {
    if (i % 10 == 0)  // 10% промахов
    {
      int k = LineRand() % (n);
      k = k + !(k % 2);  //случайный нечётный ключ
      tree.erase(k);
      D += tree.CountNodes();
      tree.insert(m[rand() % n]);
      tree.show_tree();

      I += tree.CountNodes();
      k = LineRand() % (n);
      k = k + !(k % 2);  // случайный нечётный ключ
      try {
        cout << "Because of k? k: " << k << endl;
        tree.show_tree();
        tree.find(k);
        S += tree.CountNodes();
      }
      //обработка исключения при ошибке операции поиска
      catch (overflow_error& err) {
        cout << "Are we drop here?\n";
        S += tree.CountNodes();
      }
    } else  // 90% успешных операций
    {
      int ind = rand() % n;
      tree.erase(m[ind]);
      D += tree.CountNodes();
      ;
      int k = LineRand() % (n);
      k = k + k % 2;  // случайный чётный ключ
      tree.insert(k);
      I += tree.CountNodes();
      ;
      m[ind] = k;
      try {
        tree.find(m[rand() % n]);
        S += tree.CountNodes();
        ;
      }
      //обработка исключения при ошибке операции поиска
      catch (overflow_error& err) {
        S += tree.CountNodes();
      }
    }
  }
  //вывод результатов:
  // вывод размера дерева после теста
  cout << "items count:" << tree.get_size() << endl;
  //теоретической оценки трудоёмкости операций BST
  cout << "log2(n) + 0.25 =" << (log((double)n) / log(2.0)) + 0.25 << endl;
  //экспериментальной оценки трудоёмкости вставки
  cout << "Count insert: " << I / (n / 2) << endl;
  //экспериментальной оценки трудоёмкости удаления
  cout << "Count erase: " << D / (n / 2) << endl;
  //экспериментальной оценки трудоёмкости поиска
  cout << "Count search: " << S / (n / 2) << endl;
  //освобождение памяти массива m[]
  delete[] m;
}  //конец теста

int main() {
  cout << "\n=== TEST ORD AVL ===\n";
  test_ord_avl(3);
  /*
  cout << "\n=== TEST ORD BTS ===\n";
  test_ord_bts(1);
  cout << "\n=== TEST RAND AVL ===\n";
  test_rand_avl(1);
  cout << "\n=== TEST RAND BTS ===\n";
  test_rand_bts(1 );
  */
  return 0;
}