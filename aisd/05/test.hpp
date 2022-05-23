#include <iostream>

template <class T>
class Base {
 public:
  class BaseNode {
   public:
    friend class Base;
    BaseNode(T _val) { val = _val; }
    BaseNode() { val = 0; }

   private:
    T val;
  };

  BaseNode* set_head(T _val) {
    timesReplaced++;
    return head = new BaseNode(_val);
  }

  T get_head() { return head->val; }

  int how_many() { return timesReplaced; }

  Base() {
    head = nullptr;
    timesReplaced = 0;
  }

  ~Base() { delete head; }

 private:
  BaseNode* head;
  int timesReplaced;
};

template <class T>
class Derived : Base<T> {
 public:
  class DeriveNode : Base<T>::BaseNode {
   public:
    friend class Derived;
    DeriveNode() { Base<T>::BaseNode(); }
  };

  T get_head() { return Base<T>::get_head(); }
  DeriveNode* set_head(T initial) {
    return (DeriveNode*)Base<T>::set_head(initial);
  }

  int how_many() { return Base<T>::how_many(); }
  Derived() { timesReplaced = 0; }

 private:
  int timesReplaced;
};