// #include "collection.hpp"
#include "test.hpp"

int main() {
  /*
  int num = 0;
  if (!(cin >> num)) {
    cout << "Wrong\n";
  } else {
    cout << "Num is: " << num << endl;
  }
  */

	TestClass<int> craft;
  craft.print();
  craft.push_back(1);
  craft.push_back(2);
  craft.print();

  return 0;
}
