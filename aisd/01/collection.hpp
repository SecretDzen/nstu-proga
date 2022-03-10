#include <iostream>
using namespace std;

/*
[x] конструктор,
[x] конструктор копирования,
[x] деструктор,
[ ] опрос размера списка,
[ ] очистка списка,
[ ] проверка списка на пустоту,
[ ] опрос наличия заданного значения,
[ ] чтение значения с заданным номером в списке,
[ ] изменение значения с заданным номером в списке,
[ ] получение позиции в списке для заданного значения,
[ ] включение нового значения,
[ ] включение нового значения в позицию с заданным номером,
[ ] удаление заданного значения из списка,
[ ] удаление значения из позиции с заданным номером
*/

template <class T>
class Collection {
 protected:
  class Node {
   public:
    T item;
    Node *next;
    Node *prev;
    Node(T item);
  };

  int coll_size; // Элементы внутри
  int coll_capacity; // Размер коллекции в памяти

  Collection();     // Конструктор
  Collection(...);  // Конструктор с параметрами
  Collection(const Collection<T>&);  // Конструктор копирования
  ~Collection();                      // Деструктор

  class Iterator {
    Collection *p;  // Указатель на объект коллекции
    Node *cur;      // Адрес тек элем
   public:
    Iterator();
    Iterator(Node *);

    iterator &operator++() {
      m_ptr = m_ptr->next;
      return *this;
    }

    iterator &operator++(int) {
      iterator old = *this;
      --(*this);
      return old;
    }

    iterator operator--(int) {
      iterator old = *this;
      --(*this);
      return old;
    }

    reference operator*() { return m_ptr->value; }

    pointer operator->() { return &m_ptr->value; }

    friend bool operator==(const iterator &lhs, const iterator &rhs) {
      return lhs.m_ptr == rhs.m_ptr;
    }

    friend bool operator!=(const iterator &lhs, const iterator &rhs) {
      return lhs.m_ptr != rhs.m_ptr;
    }
  };

  friend class Iterator;
  iterator begin();
  iterator end();
};
