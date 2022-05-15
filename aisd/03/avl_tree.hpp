#include <iostream>

#include "../02/bst_tree.hpp"
template <class T>
class avl : public bst_tree<T> {
 public:
  using bst_tree<T>::bst_tree;
  class Node : public bst_tree<T>::Node {
   public:
    friend class avl;
    using bst_tree<T>::Node::Node;
  };

  class Iterator : public bst_tree<T>::Iterator {
    friend class avl;
    using bst_tree<T>::Iterator::Iterator;
  };

  Iterator begin() const { return Iterator(this->find_min(root)); }
  Iterator end() const { return Iterator(nullptr); }

  Iterator find(const T& _val) {
    for (auto iter = begin(); iter != end(); iter++) {
      if (*iter == _val) return iter;
    }
    return end();
  }

  void insert(Node* leaf, const T& _val) {
    Node* p = new Node(_val);
    Node* child = leaf;
    Node* parent = nullptr;

    while (child) {
      parent = child;
      if (_val < child->val) {
        child = (Node*)child->L_tree;
      } else if (_val > child->val) {
        child = (Node*)child->R_tree;
      } else {
        break;
      }
    }

    p->Parent = parent;

    if (_val < parent->val) {
      parent->L_tree = p;
      size++;
    } else if (_val > parent->val) {
      parent->R_tree = p;
      size++;
    }

    Node* prt = parent;

    while (prt != root) {
      Node* nextParent = (Node*)prt->Parent;
      prt = balance(prt);
      prt = nextParent;
    }

    root = balance(prt);
  }

  void insert(const T& _val) {
    if (!root) {
      root = new Node(_val);
      root->Parent = nullptr;
      size++;
    } else {
      insert(root, _val);
    }
  }

  void erase(const T& value) { erase(find(value)); }

  void erase(Iterator pos) {
    if (pos == end()) return;

    Node* node = (Node*)pos.m_node;
    Node* parent = (Node*)node->Parent;
    int cleared = 0;

    if (!parent) {
      if (root->R_tree) root = (Node*)root->R_tree;
      if (root->L_tree) root = (Node*)root->L_tree;
      if (!root->L_tree && !root->R_tree) cleared = 1;
    }

    if (!node->L_tree && !node->R_tree && !cleared) {
      (node == parent->L_tree ? parent->L_tree : parent->R_tree) = nullptr;
    } else if (node->L_tree && node->R_tree) {
      Node* newParent = (Node*)this->find_min(node->R_tree);

      newParent->L_tree = node->L_tree;
      newParent->L_tree->setParent(newParent);
      node->R_tree->setParent(parent);
      if (parent) {
        (node == parent->L_tree ? parent->L_tree : parent->R_tree) =
            node->R_tree;
      }
    } else if (parent) {
      Node* child =
          (Node*)(node->L_tree == nullptr ? node->R_tree : node->L_tree);
      child->Parent = parent;
      (node == parent->L_tree ? parent->L_tree : parent->R_tree) = child;
    }

    size--;
    delete node;

    Node* prt = parent;

    while (prt != root) {
      Node* nextParent = (Node*)prt->Parent;
      prt = balance(prt);
      prt = nextParent;
    }

    root = balance(prt);
  }

  int get_size() { return size; }
  Node* get_root() { return !root ? nullptr : root; }

  void by_plus() {
    using std::cout;
    for (auto it = begin(); it != end(); it++) {
      cout << "Key: " << *it << " ";
      Node* parent = (Node*)it.m_node->getParent();

      if (parent) {
        if (parent->R_tree == it.m_node) cout << "Right child";
        if (parent->L_tree == it.m_node) cout << "Left child";
      } else {
        cout << "Root";
      }
      cout << std::endl;
    }
    cout << std::endl;
  }

  unsigned char get_height(Node* leaf) { return leaf ? leaf->height : 0; }

  int bfactor(Node* leaf) {
    return get_height((Node*)leaf->R_tree) - get_height((Node*)leaf->L_tree);
  }

  void fix_height(Node* leaf) {
    unsigned char hl = get_height((Node*)leaf->L_tree);
    unsigned char hr = get_height((Node*)leaf->R_tree);
    leaf->height = (hl > hr ? hl : hr) + 1;
  }

  Node* rotate_right(Node* leaf) {
    Node* prt = (Node*)leaf->Parent;
    Node* p = (Node*)leaf->L_tree;
    leaf->L_tree = p->R_tree;
    if (leaf->L_tree) leaf->L_tree->setParent(leaf);
    p->R_tree = leaf;
    fix_height(leaf);
    fix_height(p);

    if (prt) {
      prt->L_tree == leaf ? prt->L_tree = p : prt->R_tree = p;
    }

    p->Parent = leaf->Parent;
    leaf->Parent = p;
    return p;
  }

  Node* rotate_left(Node* leaf) {
    Node* p = (Node*)leaf->R_tree;
    leaf->R_tree = p->L_tree;
    if (leaf->R_tree) leaf->R_tree->setParent(leaf);
    p->L_tree = leaf;
    fix_height(leaf);
    fix_height(p);

    p->Parent = leaf->Parent;
    leaf->Parent = p;
    return p;
  }

  Node* balance(Node* leaf) {
    fix_height(leaf);

    if (bfactor(leaf) > 1) {
      if (bfactor((Node*)leaf->R_tree) < 0)
        leaf->R_tree = rotate_right((Node*)leaf->R_tree);
      return rotate_left(leaf);
    }

    if (bfactor(leaf) < -1) {
      if (bfactor((Node*)leaf->L_tree) > 0)
        leaf->L_tree = rotate_left((Node*)leaf->L_tree);
      return rotate_right(leaf);
    }
    return leaf;
  }

 protected:
  Node* root;
  int size;
};

// ===========================================================================
// ===========================================================================
// ===========================================================================

/*
using namespace std;

template <class T>
class avl_tree {
 public:
  class Node {
   public:
    friend class avl_tree;

    Node(){};
    Node(T _val)
        : val(_val),
          Parent(nullptr),
          L_tree(nullptr),
          R_tree(nullptr),
          height(1){};
    Node(T _val, Node* L_tree, Node* R_tree)
        : val(_val),
          L_tree(L_tree),
          R_tree(R_tree),
          height(get_height(*this)){};

    T& operator*() { return val; }

   private:
    T val;
    Node* Parent;
    Node* L_tree;
    Node* R_tree;
    unsigned char height;
  };

  class Iterator {
   public:
    friend class avl_tree;

    Iterator(Node* _node) : m_node(_node) {}

    T& operator*() { return m_node->val; }
    T& operator->() { return &m_node->val; }

    Iterator& operator++() {
      if (m_node->R_tree) {
        m_node = m_node->R_tree;

        while (m_node->L_tree) {
          m_node = m_node->L_tree;
        }
      } else {
        Node* parent = m_node->Parent;
        Node* lastOne = m_node;

        while (parent != nullptr && m_node == parent->R_tree) {
          m_node = parent;
          parent = m_node->Parent;
        }

        lastOne = m_node;
        if (parent != nullptr && m_node->R_tree != parent) m_node = parent;
        if (m_node == lastOne) m_node = nullptr;
      }

      return *this;
    }

    Iterator operator++(int) {
      auto old = *this;
      ++(*this);
      return old;
    }

    Iterator& operator--() {
      if (m_node->L_tree) {
        Node* prev = m_node->L_tree;
        while (prev->R_tree) prev = prev->R_tree;
        m_node = prev;
      } else {
        Node* parent = m_node->Parent;

        while (parent && m_node == parent->L_tree) {
          m_node = parent;
          parent = parent->Parent;
        }
        m_node = parent;
      }

      return *this;
    }

    Iterator operator--(int) {
      auto old = *this;
      --(*this);
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

  Iterator begin() const { return Iterator(find_min(root)); }
  Iterator rbegin() const { return Iterator(find_max(root)); }
  Iterator end() const { return Iterator(nullptr); }
  Iterator find(const T& _val) {
    for (auto iter = begin(); iter != end(); iter++) {
      if (*iter == _val) return iter;
    }
    return end();
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
      } else {
        break;
      }
    }

    return parent;
  }

  Node* get_first(Node* pr) {
    while (pr->L_tree != nullptr) pr = pr->L_tree;
    return pr;
  }

  Node* get_root() { return !root ? nullptr : root; }

  void insert(Node* leaf, const T& _val) {
    Node* p = new Node(_val);
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

    p->Parent = parent;

    if (_val < parent->val) {
      parent->L_tree = p;
      size++;
    } else if (_val > parent->val) {
      parent->R_tree = p;
      size++;
    }

    Node* prt = parent;
    while (prt != root) {
      Node* nextParent = prt->Parent;
      prt = balance(prt);
      prt = nextParent;
    }
    root = balance(root);
  }

  void insert(const T& _val) {
    if (!root) {
      root = new Node(_val);
      root->Parent = nullptr;
      size++;
    } else {
      insert(root, _val);
    }
  }

  void erase(const T& value) { erase(find(value)); }

  void erase(Iterator pos) {
    if (pos == end()) return;

    Node* node = pos.m_node;
    Node* parent = node->Parent;

    if (!parent) root = root->R_tree;

    if (!node->L_tree && !node->R_tree) {
      (node == parent->L_tree ? parent->L_tree : parent->R_tree) = nullptr;
    } else if (node->L_tree && node->R_tree) {
      Node* newParent = get_first(node->R_tree);

      newParent->L_tree = node->L_tree;
      newParent->L_tree->Parent = newParent;
      node->R_tree->Parent = parent;
      if (parent) {
        (node == parent->L_tree ? parent->L_tree : parent->R_tree) =
            node->R_tree;
      }
    } else if (parent) {
      Node* child = (node->L_tree == nullptr ? node->R_tree : node->L_tree);
      child->Parent = parent;
      (node == parent->L_tree ? parent->L_tree : parent->R_tree) = child;
    }

    size--;
    delete node;
  }

  void inorder(Node* leaf) {
    if (leaf != nullptr) {
      inorder(leaf->L_tree);
      cout << leaf->val << " ";
      inorder(leaf->R_tree);
    }
  }

  void display() {
    inorder(root);
    cout << endl;
  }

  void by_plus() {
    for (auto it = begin(); it != end(); it++) {
      cout << "Key: " << *it << " ";
      Node* parent = it.m_node->Parent;

      if (parent) {
        if (parent->R_tree == it.m_node) cout << "Right child";
        if (parent->L_tree == it.m_node) cout << "Left child";
      } else {
        cout << "Root";
      }

      cout << endl;
    }
    cout << endl;
  }

  void clear(Node* leaf) {
    if (leaf != nullptr) {
      clear(leaf->L_tree);
      clear(leaf->R_tree);
      delete leaf;
    }
    size = 0;
  }

  const T& get_val(Node* leaf) { return leaf->val; }
  const T& get_val(Iterator leaf) { return leaf.m_node->val; }

  int get_size() { return size; }
  int is_empty() { return root == nullptr; }

  void merge(const avl_tree& src) {
    for (auto it = src.begin(); it != src.end(); it++) {
      insert(*it);
    }
  }

  unsigned char get_height(Node* leaf) { return leaf ? leaf->height : 0; }

  int bfactor(Node* leaf) {
    return get_height(leaf->R_tree) - get_height(leaf->L_tree);
  }

  void fix_height(Node* leaf) {
    unsigned char hl = get_height(leaf->L_tree);
    unsigned char hr = get_height(leaf->R_tree);
    leaf->height = (hl > hr ? hl : hr) + 1;
  }

  Node* rotate_right(Node* leaf) {
    Node* prt = leaf->Parent;
    Node* p = leaf->L_tree;
    cout << "Rotoscoping right: " << leaf->val << endl;

    leaf->L_tree = p->R_tree;
    if (leaf->L_tree) leaf->L_tree->Parent = leaf;
    p->R_tree = leaf;
    fix_height(leaf);
    fix_height(p);

    if (prt) {
      prt->L_tree == leaf ? prt->L_tree = p : prt->R_tree = p;
    }
    p->Parent = leaf->Parent;
    leaf->Parent = p;
    return p;
  }

  Node* rotate_left(Node* leaf) {
    Node* p = leaf->R_tree;
    cout << "Rotoscoping left: " << leaf->val << endl;

    leaf->R_tree = p->L_tree;
    if (leaf->R_tree) leaf->R_tree->Parent = leaf;
    p->L_tree = leaf;
    fix_height(leaf);
    fix_height(p);

    p->Parent = leaf->Parent;
    leaf->Parent = p;
    return p;
  }

  Node* balance(Node* leaf) {
    fix_height(leaf);

    if (bfactor(leaf) > 1) {
      cout << "Rotoscoping above 1" << endl;
      if (bfactor(leaf->R_tree) < 0) leaf->R_tree = rotate_right(leaf->R_tree);
      return rotate_left(leaf);
    }

    if (bfactor(leaf) < -1) {
      cout << "Rotoscoping below -1" << endl;
      if (bfactor(leaf->L_tree) > 0) leaf->L_tree = rotate_left(leaf->L_tree);
      return rotate_right(leaf);
    }
    return leaf;
  }

  avl_tree& operator=(const avl_tree& src) {
    clear(root);
    size = 0;
    root = nullptr;

    for (auto item = src.get_root(); item != src.end(); ++item) {
      insert(*item);
    }
    for (auto item = src.begin(); item != src.get_root(); ++item) {
      insert(*item);
    }

    return *this;
  }

 private:
  Node* root;
  int size;
};

*/
