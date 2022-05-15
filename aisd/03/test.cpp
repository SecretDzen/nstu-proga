#include "avl_tree.hpp"

avl_tree<int> one;
int main() {
  one.insert(10);
  one.insert(12);
  one.insert(8);
  one.insert(5);
  one.insert(3);
  one.by_plus();

  one.display();


  std::cout << one.get_size() << std::endl;
  one.is_empty();

  return 0;
}