#include <iostream>
using namespace std;

template <class T>
class TestClass {
  struct Node {
    T val;
    Node* next;

    Node(T _val) : val(_val), next(nullptr) {}
  }

  struct List {
    Node* first;
    Node* last;

    List() : first(nullptr), last(nullptr) {}
  }

  bool
  is_empty() {
    return first == nullptr;
  }

  void push_back(T _val) {
    Node* p = new Node(_val);

    if (is_empty()) {
      first = p;
      last = p;
    } else {
      last->next = p;
      last = p;
    }
  }

  void print() {
    bool flag = is_empty();
    while (p && flag) {
      cout << p->val << " ";
      p = p->next;
    }
    cout << endl;
  }
};
