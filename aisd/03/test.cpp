#include "avl_tree.hpp"
using namespace std;

avl<int> one;
int main() {
  one.insert(10);
  one.insert(5);
  one.insert(3);
  cout << one.get_size() << endl;
  auto rt = one.get_root();
  cout << rt->get_val() << endl;
  one.by_plus();
  return 0;
}