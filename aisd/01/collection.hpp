#include <iostream>
using namespace std;

template <class T>
class Collection {
 public:
  struct Node {
    friend class Collection;

    Node() {}
    Node(T _val) : val(_val), next(nullptr) {}
    Node(T _val, Node* _next) : val(_val), next(_next) {}

   private:
    T val;
    Node* next;
  };

  struct Iterator {
    friend class Collection;

    Iterator(Node* _node) : m_node(_node) {}

    T& operator*() { return m_node->val; }
    T& operator->() { return &m_node->val; }

    Iterator& operator++() {
      m_node = m_node->next;
      return *this;
    }

    Iterator operator++(int) {
      Iterator old = *this;
      ++(*this);
      return old;
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
      return lhs.m_node == rhs.m_node;
    }

    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
      return lhs.m_node != rhs.m_node;
    }

   private:
    Node* m_node;
  };

  Collection() {
    border = new Node();
    border->next = head;
  }

  ~Collection() {
    clear();
    delete border;
  }

  Collection(const Collection& list) : Collection() {
    for (auto it = list.begin(); it != list.end(); it++) {
      push_back(*it);
    }
  }

  Iterator begin() const { return Iterator(head); }
  Iterator end() const { return Iterator(border); }
  Iterator find_tail() const { return Iterator(tail); }
  Iterator find(const T& value) { return find(begin(), end(), value); }

  Iterator find(Iterator head, Iterator tail, const T& val) {
    for (auto it = head; it != border; it++) {
      if (*it == val) return it;
    }

    return tail;
  }

  Iterator insert(Iterator pos, const T& _val) {
    if (pos == begin()) {
      push_front(_val);
      return Iterator(head);
    } else if (pos == end()) {
      push_back(_val);
      return Iterator(tail);
    }

    Node* p = new Node(_val, pos.m_node);
    auto prev_elem = get_prev_elem(pos);

    prev_elem.m_node->next = p;
    size++;

    return Iterator(p);
  }

  Iterator erase(Iterator pos) {
    if (pos == end()) return pos;

    if (pos.m_node == head) {
      pop_front();
      return begin();
    } else if (pos.m_node == tail) {
      pop_back();
      return end();
    }

    auto to_del = pos.m_node;
    Node* nextOne = pos.m_node->next;
    auto prev_elem = get_prev_elem(pos);
    prev_elem.m_node->next = nextOne;

    delete(to_del);
    size--;

    return Iterator(nextOne);
  }

  Iterator get_prev_elem(Iterator pos) {
    auto prev_elem = begin();
    for (auto it = begin(); it != end() && it != pos; it++) prev_elem = it;
    return prev_elem;
  }

  Iterator erase(const T& _val) { return erase(find(_val)); }

  T& operator[](int pos) {
    if (pos >= size) {
      throw std::out_of_range("Out of range");
    }

    for (auto it = begin(); it != end(); it++) {
      if (pos-- == 0) return *it;
    }

    // never returns
    return *end();
  }

  T& operator=(const Collection& list) {
    clear();

    for (auto it = list.begin(); it != list.end(); it++) {
      push_back(*it);
    }
  }

  bool is_empty() { return head == nullptr; }

  void push_back(const T& _val) {
    size++;

    if (is_empty()) {
      head = tail = new Node(_val, border);
      border->next = head;
    } else {
      tail->next = new Node(_val, border);
      tail = tail->next;
    }
  }

  void push_front(const T& _val) {
    size++;

    if (size == 0) {
      head = tail = new Node(_val, border);
      border->next = head;
    } else {
      border->next = new Node(_val, head);
      head = border->next;
    }
  }

  void pop_front() {
    if (size == 0) return;

    if (size == 1) {
      tail = head = nullptr;
      border = new Node();
      border->next = head;
      size = 0;
    } else {
      head = head->next;
      border->next = head;
      size--;
    }
  }

  void pop_back() {
    if (size == 0) return;

    if (size == 1) {
      tail = head = nullptr;
      border = new Node();
      border->next = head;
      size = 0;
    } else {
      auto prev_elem = get_prev_elem(find_tail());
      tail = prev_elem.m_node;
      tail->next = border;
      size--;
    }
  }

  int get_size() const { return size; }

  void clear() {
    if (size == 0) return;
    auto ptr = head;

    while (ptr != border) {
      auto to_del = ptr;
      ptr = ptr->next;
      delete to_del;
    }

    size = 0;
  }

  friend std::ostream& operator<<(std::ostream& os, Collection& rhs) {
    int n = 0;
    os << "[";
    if (rhs.get_size() < 1) {
      os << " ]";
      return os;
    }
    for (const auto& item : rhs) {
      os << item;
      if (++n < rhs.get_size()) os << ", ";
    }

    os << "]";
    return os;
  }

 private:
  Node* head = nullptr;
  Node* tail = nullptr;
  Node* border = nullptr;
  int size = 0;
};
