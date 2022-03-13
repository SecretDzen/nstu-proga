#include "test.hpp"

int main() {
  Collection<int> craft;

// Empty collection output
  cout << craft << endl;
// Fill collection
  craft.push_back(1);
  craft.push_back(2);
  craft.push_back(3);
  craft.push_back(4);

// Collection output
  cout << craft << endl;
  cout << craft[0] << endl;

// Find num in collection
  auto f = craft.find(3);

// Get size of the collection
  int a = craft.get_size();

// Results
  cout << "Size: " << a << endl;

  craft.insert(f, 5);
  cout << "Insert: " << craft << endl;

  craft.erase(f);
  cout << "Erase: " << craft << endl;

// Copy test
  Collection<int> newOne(craft);
  a = newOne.get_size();
  cout << newOne << endl;
  cout << "Size: " << a << endl;
  
// Clear test
  craft.clear();
  a = craft.get_size();
  cout << "Size: " << a << endl;
  return 0;
}
