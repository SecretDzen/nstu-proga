#include <iostream>
using namespace std;

/*
[x] конструктор
[ ] конструктор копирования
[ ] деструктор
[x] опрос размера дерева
[ ] очистка дерева
[x] проверка дерева на пустоту
[ ] доступ по чтению/записи к данным по ключу
[x] включение данных с заданным ключом
[ ] удаление данных с заданным ключом
[ ] формирование списка ключей в дереве в порядке обхода узлов по
схеме, заданной в варианте задания
[ ] дополнительная операция, заданная в варианте задания
[x] запрос прямого итератора, установленного на узел дерева с мини-
мальным ключом begin()
[ ] запрос обратного итератора, установленного на узел дерева с мак-
симальным ключом rbegin()
[x] запрос «неустановленного» прямого итератора end()
[ ] запрос «неустановленного» обратного итератора rend().
Операции прямого и обратного итератора выполняются по схеме
симметричного обхода элементов дерева L → t → R:
[x] операция доступа по чтению и записи к данным текущего узла *
[ ] операция перехода к следующему по ключу узлу в дереве ++
[ ] операция перехода к предыдущему по ключу узлу в дереве --
[x] проверка равенства однотипных итераторов ==
[x] проверка неравенства однотипных итераторов !=
*/

template <class T>
class bst_tree {
 public:
  class Node {
   public:
    friend class bst_tree;

    Node(){};
    Node(T _val) : val(_val), L_tree(nullptr), R_tree(nullptr){};
    Node(T _val, Node* _left, Node* _right)
        : val(_val), L_tree(_left), R_tree(_right){};

   private:
    T val;
    Node* L_tree;
    Node* R_tree;
  };

  class Iterator {
   public:
    friend class bst_tree;

    Iterator(Node* _node) : m_node(_node) {}

    T& operator*() { return m_node->val; }
    T& operator->() { return &m_node->val; }

    Iterator& operator++() {
      if (m_node->R_tree) {
        m_node = m_node->R_tree;
        while (m_node->L_tree) m_node = m_node->L_tree;
      } else {
        m_node = get_parent(m_node);
      }
      return *this;
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

  Iterator begin() const { return Iterator(find_min(root)); }
  Iterator end() const { return Iterator(find_max(root)); }

  Iterator find(const T& _val) { return find(begin(), end(), _val); }

  Iterator get_parent(Node* leaf) {
    Node* parent = leaf;
    Node* rt = get_root();

    while (1) {
      if (parent->val < rt->val) {
        if (rt->L_tree->val == parent->val) break;
        rt = rt->L_tree;
      } else if (parent->val > rt->val) {
        if (rt->R_tree->val == parent->val) break;
        rt = rt->R_tree;
      } else {
        break;
      }
    }

    return rt;
  }

  Node* find_min() const { return find_min(root); }
  Node* find_max() const { return find_max(root); }

  Node* find_min(Node* leaf) const {
    Node* child = leaf;
    Node* parent = nullptr;

    while (child) {
      parent = child;
      if (child->L_tree) {
        child = child->L_tree;
      } else if (child->R_tree) {
        child = child->R_tree;
      } else {
        break;
      }
    }

    return parent;
  }

  Node* find_max(Node* leaf) const {
    Node* child = leaf;
    Node* parent = nullptr;

    while (child) {
      parent = child;
      if (child->R_tree) {
        child = child->R_tree;
      } else if (child->L_tree) {
        child = child->L_tree;
      } else {
        break;
      }
    }

    return parent;
  }

  void insert(Node* leaf, const T& _val) {
    Node* p = new Node(_val);

    if (!leaf) {
      leaf = p;
      size++;
    } else {
      Node* child = leaf;
      Node* parent = nullptr;

      while (child) {
        parent = child;
        if (_val < child->val) {
          child = child->L_tree;
        } else if (_val > child->val) {
          child = child->R_tree;
        } else {
          break;
        }
      }

      if (_val < parent->val) {
        parent->L_tree = p;
        size++;
      } else if (_val > parent->val) {
        parent->R_tree = p;
        size++;
      }
    }
  }

  void insert(const T& _val) {
    if (!root) {
      root = new Node(_val);
      size++;
    } else {
      insert(root, _val);
    }
  }

  void inorder(Node* leaf) {
    if (leaf != nullptr) {
      inorder(leaf->L_tree);
      inorder(leaf->R_tree);
      cout << leaf->val << " ";
    }
  }

  void by_plus() {
    int i = 0;
    for(auto it = begin(); it != end(); ++it) {
      cout << it.m_node->val;
      if(i >= size) break;
      i++;

    }
    cout << endl;
  }

  void display() {
    inorder(root);
    cout << endl;
  }

  void clear(Node* leaf) { delete leaf; }

  Node* get_root() { return !root ? nullptr : root; }

  const T& get_val(Node* leaf) { return leaf->val; }
  const T& get_val(Iterator leaf) { return leaf.m_node->val; }

  int get_size() { return size; }
  int is_empty() { return root == nullptr; }

  bst_tree() {
    root = nullptr;
    size = 0;
  };

  ~bst_tree() { clear(root); };

 private:
  Node* root;
  int size;
};
