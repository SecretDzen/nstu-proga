#include <iomanip>
#include <iostream>

#include "../02/bst_tree.hpp"
template <class T>
class avl : public bst_tree<T> {
 public:
  using base = bst_tree<T>;
  using type_node = typename base::Node;

  void insert(const T& _val) {
    if (base::root == nullptr) {
      base::root = new type_node(_val);
      base::size++;
    } else {
      insert(base::root, _val);
    }
  }

  void insert(typename base::Node* leaf, const T& _val) {
    base::insert(leaf, _val);
    base::steps = 0;
    typename base::Node* prt = base::find(_val).get_node();

    while (prt != base::root) {
      type_node* nextParent = prt->get_P();
      prt = balance(prt);
      prt = nextParent;
    }

    base::root = balance(prt);
  }

  void erase(const T& value) { erase(base::find(value)); }

  void erase(typename base::Iterator pos) {
    if (pos == base::end()) return;
    type_node* prt = pos.get_node()->get_P();
    base::erase(pos);

    while (prt && prt != base::root) {
      type_node* nextParent = prt->get_P();
      prt = balance(prt);
      prt = nextParent;
    }
    if (prt) base::root = balance(prt);
  }

  int get_size() { return base::get_size(); }

  void by_plus() {
    using std::cout;
    for (auto it = base::begin(); it != base::end(); it++) {
      cout << *it << " ";
    }
    cout << std::endl;
  }

  unsigned char get_height(typename base::Node* leaf) {
    return leaf ? leaf->get_H() : 0;
  }

  int bfactor(typename base::Node* leaf) {
    return get_height(leaf->get_R()) - get_height(leaf->get_L());
  }

  void fix_height(typename base::Node* leaf) {
    unsigned char hl = get_height(leaf->get_L());
    unsigned char hr = get_height(leaf->get_R());
    leaf->set_H((hl > hr ? hl : hr) + 1);
  }

  typename base::Node* rotate_right(typename base::Node* x) {
    type_node* y = x->get_L();
    type_node* x_parent = x->get_P();
    type_node* z2 = y->get_R();
    x->set_L(z2);
    x->set_P(y);
    y->set_R(x);
    y->set_P(x_parent);
    if (x_parent) x_parent->set_L(y);
    if (z2) z2->set_P(x);

    fix_height(x);
    fix_height(y);

    return y;
  }

  typename base::Node* rotate_left(typename base::Node* y) {
    type_node* x = y->get_R();
    type_node* y_parent = y->get_P();
    type_node* z2 = x->get_L();
    x->set_L(y);
    x->set_P(y_parent);
    y->set_R(z2);
    y->set_P(x);
    if (y_parent) y_parent->set_R(x);
    if (z2) z2->set_P(y);

    fix_height(y);
    fix_height(x);

    return x;
  }

  typename base::Node* balance(typename base::Node* leaf) {
    fix_height(leaf);

    if (bfactor(leaf) > 1) {
      if (leaf->get_R() && bfactor(leaf->get_R()) < 0)
        leaf->set_R(rotate_right(leaf->get_R()));
      return rotate_left(leaf);
    }

    if (bfactor(leaf) < -1) {
      if (leaf->get_L() && bfactor(leaf->get_L()) > 0)
        leaf->set_L(rotate_left(leaf->get_L()));
      return rotate_right(leaf);
    }
    return leaf;
  }

  void show_tree(type_node* p, int indent = 0) {
    if (p != nullptr) {
      if (p->get_R()) show_tree(p->get_R(), indent + 4);
      if (indent) std::cout << std::setw(indent) << ' ';
      if (p->get_R()) std::cout << " /\n" << std::setw(indent) << ' ';

      std::cout << p->get_val() << "(" << bfactor(p) << ")"
                << "\n ";

      if (p->get_L()) {
        std::cout << std::setw(indent) << ' ' << "\\\n";
        show_tree(p->get_L(), indent + 4);
      }
    }
  }

  void show_tree() { show_tree(base::root, 0); }
};