#include "test.hpp"
using namespace std;

int main() {
  Derived<int> foo;
  cout << "Replaces: " << foo.how_many() << endl;
  foo.set_head(2);
  cout << "Replaces: " << foo.how_many() << endl;
  cout << "Value: " << foo.get_head() << endl;
  foo.set_head(5);
  cout << "Replaces: " << foo.how_many() << endl;
  cout << "Value: " << foo.get_head() << endl;
};