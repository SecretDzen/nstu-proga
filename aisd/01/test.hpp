#include <iostream>
using namespace std;

template <class T>
class TestClass {
 public:
  struct Node {
   public:
    Node(T _val) : val(_val), next(nullptr) {}

   private:
    T val;
    Node* next;
  };

  struct List {
   public:
    List() : head(nullptr), tail(nullptr), size(0) {}

   private:
    Node* head;
    Node* tail;
    int size;
  };

  bool is_empty() { return head == nullptr; }

  void push_back(T _val) {
    Node* p = new Node(_val);
    size++;

    if (is_empty()) {
      head = p;
      tail = p;
    } else {
      tail->next = head;
      tail = p;
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
