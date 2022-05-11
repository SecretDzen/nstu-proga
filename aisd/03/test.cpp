#include "avl_tree.hpp"

avl<int> one;
avl<int> two;
int main() {
  one.insert(10);
  one.insert(5);
  one.insert(15);
  one.insert(-1);
  one.insert(8);
  one.insert(-5);
  one.by_plus();

  one.display();
}