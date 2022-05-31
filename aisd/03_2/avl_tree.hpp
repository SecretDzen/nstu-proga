#include <iomanip>
#include <iostream>

#include "bst_tree.hpp"
#pragma once
using namespace std;
template <class T, class T_data>
class AVL_Tree : public Tree<T, T_data> {
 protected:
  void balancing(
      typename Tree<T, T_data>::template KnotTree<T, T_data>* inspecting_knot);
  void rotate_right(
      typename Tree<T, T_data>::template KnotTree<T, T_data>* knot);
  void rotate_left(
      typename Tree<T, T_data>::template KnotTree<T, T_data>* knot);
  void output_tree(typename Tree<T, T_data>::template KnotTree<T, T_data>* node,
                   int indent);
  int search_height(
      typename Tree<T, T_data>::template KnotTree<T, T_data>* knot, int height);

 public:
  bool Add(const T_data& value, const T& key);
  bool Delete(const T& key);
  void Print();
  T_data& GetLink(const T& key);
  int search_height_forprint(
      typename Tree<T, T_data>::template KnotTree<T, T_data>* knot, int height);
};

template <class T, class T_data>
int AVL_Tree<T, T_data>::search_height(
    typename Tree<T, T_data>::template KnotTree<T, T_data>* knot, int height) {
  if (knot == NULL) return 0;
  int left_h = 0, right_h = 0;
  if ((knot->node_left == NULL) && (knot->node_right == NULL)) return height;
  if (knot->node_left != NULL)
    left_h = search_height(knot->node_left, height + 1);
  if (knot->node_right != NULL)
    right_h = search_height(knot->node_right, height + 1);
  if (left_h >= right_h)
    return left_h;
  else
    return right_h;
}

template <class T, class T_data>
int AVL_Tree<T, T_data>::search_height_forprint(
    typename Tree<T, T_data>::template KnotTree<T, T_data>* knot, int height) {
  if (knot == NULL) return -1;
  int left_h = 0, right_h = 0;
  if ((knot->node_left == NULL) && (knot->node_right == NULL)) return height;
  if (knot->node_left != NULL)
    left_h = search_height(knot->node_left, height + 1);
  if (knot->node_right != NULL)
    right_h = search_height(knot->node_right, height + 1);
  if (left_h >= right_h)
    return left_h;
  else
    return right_h;
}

template <class T, class T_data>
void AVL_Tree<T, T_data>::balancing(
    typename Tree<T, T_data>::template KnotTree<T, T_data>* inspecting_knot) {
  int hl = 0, hr = 0;
  while (inspecting_knot != NULL) {
    hr = search_height(inspecting_knot->node_right, 1);
    hl = search_height(inspecting_knot->node_left, 1);
    if ((hr - hl) >= 2) {
      if (search_height(inspecting_knot->node_right->node_left, 1) <=
          search_height(inspecting_knot->node_right->node_right, 1))
        rotate_left(inspecting_knot);
      else {
        rotate_right(inspecting_knot->node_right);
        rotate_left(inspecting_knot);
      }
    } else if ((hl - hr) >= 2) {
      if (search_height(inspecting_knot->node_left->node_right, 1) <=
          search_height(inspecting_knot->node_left->node_left, 1))
        rotate_right(inspecting_knot);
      else {
        rotate_left(inspecting_knot->node_left);
        rotate_right(inspecting_knot);
      }
    }
    inspecting_knot =
        Tree<T, T_data>::search_parent(inspecting_knot, this->root_tree);
  }
}

template <class T, class T_data>
void AVL_Tree<T, T_data>::rotate_right(
    typename Tree<T, T_data>::template KnotTree<T, T_data>* knot) {
  typename Tree<T, T_data>::template KnotTree<T, T_data>* left_son =
      knot->node_left;
  if (knot != this->root_tree) {
    typename Tree<T, T_data>::template KnotTree<T, T_data>* parent =
        Tree<T, T_data>::search_parent(knot, this->root_tree);
    if (parent == nullptr) return;
    if (knot == parent->node_right)
      parent->node_right = left_son;
    else
      parent->node_left = left_son;
  } else
    this->root_tree = left_son;
  knot->node_left = left_son->node_right;
  left_son->node_right = knot;
}

template <class T, class T_data>
void AVL_Tree<T, T_data>::rotate_left(
    typename Tree<T, T_data>::template KnotTree<T, T_data>* knot) {
  typename Tree<T, T_data>::template KnotTree<T, T_data>* right_son =
      knot->node_right;
  if (knot != this->root_tree) {
    typename Tree<T, T_data>::template KnotTree<T, T_data>* parent =
        Tree<T, T_data>::search_parent(knot, this->root_tree);
    if (knot == parent->node_right)
      parent->node_right = right_son;
    else
      parent->node_left = right_son;
  } else
    this->root_tree = right_son;
  knot->node_right = right_son->node_left;
  right_son->node_left = knot;
}

template <class T, class T_data>
void AVL_Tree<T, T_data>::output_tree(
    typename Tree<T, T_data>::template KnotTree<T, T_data>* p, int indent) {
  if (p != NULL) {
    if (p->node_right) {
      output_tree(p->node_right, indent + 4);
    }
    if (indent) {
      std::cout << std::setw(indent) << ' ';
    }
    if (p->node_right) std::cout << " /\n" << std::setw(indent) << ' ';
    std::cout << p->key << "("
              << this->search_height_forprint(p->node_right, 0) -
                     this->search_height_forprint(p->node_left, 0)
              << ")"
              << "\n ";
    if (p->node_left) {
      std::cout << std::setw(indent) << ' ' << " \\\n";
      output_tree(p->node_left, indent + 4);
    }
  }
}

template <class T, class T_data>
bool AVL_Tree<T, T_data>::Add(const T_data& value, const T& key) {
  if (this->size != 0) {
    if (this->search_key(key, this->root_tree) != nullptr) return false;
    this->count_node = 0;
    typename Tree<T, T_data>::template KnotTree<T, T_data>* Insert_knot =
        this->root_tree;
    bool knot_found = false;
    while (!knot_found) {
      this->count_node++;
      if (key >= Insert_knot->key) {
        if (Insert_knot->node_right != NULL) {
          Insert_knot = Insert_knot->node_right;
          continue;
        } else {
          Insert_knot->node_right =
              new typename Tree<T, T_data>::template KnotTree<T, T_data>;
          Insert_knot->node_right->key = key;
          Insert_knot->node_right->data = value;
          knot_found = true;
          Insert_knot = Insert_knot->node_right;
        }
      } else {
        if (Insert_knot->node_left != NULL) {
          Insert_knot = Insert_knot->node_left;
          continue;
        } else {
          Insert_knot->node_left =
              new typename Tree<T, T_data>::template KnotTree<T, T_data>;
          Insert_knot->node_left->key = key;
          Insert_knot->node_left->data = value;
          knot_found = true;
          Insert_knot = Insert_knot->node_left;
        }
      }
    }
    balancing(Insert_knot);
  } else {
    this->count_node = 1;
    this->root_tree =
        new typename Tree<T, T_data>::template KnotTree<T, T_data>;
    this->root_tree->key = key;
    this->root_tree->data = value;
  }
  this->size++;
  return true;
}

template <class T, class T_data>
bool AVL_Tree<T, T_data>::Delete(const T& key) {
  this->count_node = 0;
  if (this->size == 0) return false;
  typename Tree<T, T_data>::template KnotTree<T, T_data>
      *searching_key = Tree<T, T_data>::search_key(key, this->root_tree),
     *balancer = NULL;
  typename Tree<T, T_data>::template KnotTree<T, T_data>* parent_with_2_son =
      nullptr;
  bool parent_with_two_son = false;
  T d_key = 0;
  T_data d_data = 0;
  while (searching_key != NULL) {
    if ((searching_key->node_left == NULL) &&
        (searching_key->node_right == NULL)) {
      typename Tree<T, T_data>::template KnotTree<T, T_data>* parent =
          Tree<T, T_data>::search_parent(searching_key, this->root_tree);
      if (parent != NULL) {
        if (parent->node_left == searching_key) parent->node_left = NULL;
        if (parent->node_right == searching_key) parent->node_right = NULL;
        delete searching_key;
        balancer = parent;
      } else {
        searching_key = NULL;
      }
    } else if ((searching_key->node_left != NULL) &&
               (searching_key->node_right == NULL)) {
      typename Tree<T, T_data>::template KnotTree<T, T_data>* parent =
          Tree<T, T_data>::search_parent(searching_key, this->root_tree);
      if (parent != NULL) {
        if (parent->node_left == searching_key)
          parent->node_left = searching_key->node_left;
        if (parent->node_right == searching_key)
          parent->node_right = searching_key->node_left;
        balancer = parent;
      } else {
        this->root_tree = searching_key->node_left;
        balancer = this->root_tree;
      }
      delete searching_key;
    } else if ((searching_key->node_left == NULL) &&
               (searching_key->node_right != NULL)) {
      typename Tree<T, T_data>::template KnotTree<T, T_data>* parent =
          Tree<T, T_data>::search_parent(searching_key, this->root_tree);
      if (parent != NULL) {
        if (parent->node_left == searching_key)
          parent->node_left = searching_key->node_right;
        if (parent->node_right == searching_key)
          parent->node_right = searching_key->node_right;
        balancer = parent;
      } else {
        this->root_tree = searching_key->node_right;
        balancer = this->root_tree;
      }
      delete searching_key;
    } else {
      typename Tree<T, T_data>::template KnotTree<T, T_data>* substituent =
          Tree<T, T_data>::search_end(searching_key->node_left);
      parent_with_two_son = true;
      parent_with_2_son = searching_key;
      d_key = substituent->key;
      d_data = substituent->data;
      searching_key = substituent;
      continue;
    }
    if (parent_with_two_son) {
      parent_with_2_son->key = d_key;
      parent_with_2_son->data = d_data;
    }
    balancing(balancer);
    this->size--;
    return true;
  }
  return false;
}

template <class T, class T_data>
void AVL_Tree<T, T_data>::Print() {
  if (this->size != 0)
    output_tree(this->root_tree, 0);
  else
    cout << "������ ������" << endl;
}

template <class T, class T_data>
T_data& AVL_Tree<T, T_data>::GetLink(const T& key) {
  this->count_node = 1;
  if (this->root_tree == NULL) throw overflow_error("������� ����������");
  ;
  typename Tree<T, T_data>::template KnotTree<T, T_data>* searching_knot =
      this->root_tree;
  while ((searching_knot != NULL) && (searching_knot->key != key)) {
    this->count_node++;
    if (key >= searching_knot->key) {
      searching_knot = searching_knot->node_right;
      continue;
    } else {
      searching_knot = searching_knot->node_left;
      continue;
    }
  }
  if (searching_knot == NULL)
    throw overflow_error("������� ����������");
  else
    return searching_knot->data;
}
