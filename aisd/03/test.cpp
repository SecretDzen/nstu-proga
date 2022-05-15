#include "avl_tree.hpp"

avl<int> one;
int main() {
  one.insert(10);
  one.insert(12);
  one.insert(13);
  one.insert(14);
  one.by_plus();

  one.display();


  std::cout << one.get_size() << std::endl;
  one.is_empty();

  return 0;
}