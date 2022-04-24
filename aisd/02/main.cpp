#include "bst_tree.hpp"

int main() {
  bst_tree<int> one;
  one.insert(4);
  one.insert(6);
  one.insert(2);
  one.insert(3);
  one.insert(9);
  one.insert(5);
  one.insert(-15);
  one.insert(-10);
  one.insert(-11);
  one.insert(-9);
  one.display();
  cout << "Size: " << one.get_size() << endl;
  one.by_plus();

  bst_tree<int> t2;

  t2.insert(12);
  t2.insert(21);
  t2.insert(-19);
  t2.insert(-10);
  t2.display();
  cout << "Size: " << t2.get_size() << endl;
  t2.by_plus();

  one.merge(t2);
  one.display();
  cout << "Size: " << one.get_size() << endl;

  return 0;
}
