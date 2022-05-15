#include "bst_tree.hpp"

using namespace std;
bst_tree<int> one;
bst_tree<int> two;
int main() {
  one.insert(10);
  one.insert(5);
  one.insert(0);
  one.insert(2);
  one.insert(15);
  one.insert(12);
  one.insert(18);
  one.erase(15);

  cout << "By plus" << endl;
  one.by_plus();
  cout << "By minus" << endl;
  one.by_minus();

  two = one;

  cout << "By plus" << endl;
  two.by_plus();
  cout << "By minus" << endl;
  two.by_minus();
  return 0;
}