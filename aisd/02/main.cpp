#include "bst_tree.hpp"

int main() {
  bst_tree<int> one;
  one.insert(4);
  one.insert(6);
  one.insert(2);
  one.insert(3);
  one.insert(-15);
  one.insert(-10);
  one.insert(-11);
  one.insert(-9);
  one.display();
  cout << "Size: " << one.get_size() << endl;

  one.by_plus();
  
  return 0;
}
