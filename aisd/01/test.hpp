#include <iostream>
using namespace std;

template <class T>
class TestClass {
 public:
  struct Node {
   public:
    Node(T _val) : val(_val), next(nullptr) {}
    Node(T _val, Node* _next) : val(_val), next(_next) {}

    T val;
    Node* next;
  };

  struct Iterator {
   public:
    Iterator(Node* _node) : m_node(_node) {}

    Node* m_node;
  };

  bool is_empty() { return head == nullptr; }

  void push_back(T _val) {
    size++;

    if (is_empty()) {
      head = tail = new Node(_val);
    } else {
      tail = new Node(_val, head);
    }
  }

 private:
  Node* head = nullptr;
  Node* tail = nullptr;
  int size = 0;
};
