#include "bst_tree.hpp"

bst_tree<int> one;
bst_tree<int> two;
int main() {
  one.insert(10);
  one.insert(20);
  one.insert(30);
  one.insert(5);
  one.insert(7);
  one.insert(2);
  one.insert(25);

  one.by_plus();

  two.merge(one);
  two.by_plus();
  return 0;
}