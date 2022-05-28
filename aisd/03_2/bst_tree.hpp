#include <climits>
#include <iostream>
#include <vector>
using namespace std;
#pragma once

template <class T, class T_data>
class Tree {
 protected:
  template <class T_K, class T_d>
  class KnotTree {
   public:
    T key;
    T_data data;
    KnotTree* node_left = NULL;
    KnotTree* node_right = NULL;
  };

  KnotTree<T, T_data>* root_tree = NULL;
  int size = 0;
  static int count_node;

  void add_new_knot(KnotTree<T, T_data>* knot, const T_data& value,
                    const T& key);
  void delete_knot(KnotTree<T, T_data>* knot);
  void copy_tree(KnotTree<T, T_data>* receiver_knot,
                 KnotTree<T, T_data>* source_knot);
  void delete_tree(KnotTree<T, T_data>* knot);

  KnotTree<T, T_data>* search_begin(KnotTree<T, T_data>* knot);
  KnotTree<T, T_data>* search_end(KnotTree<T, T_data>* knot);
  KnotTree<T, T_data>* search_parent(KnotTree<T, T_data>* knot,
                                     KnotTree<T, T_data>* start_knot);
  KnotTree<T, T_data>* search_key(const T& key,
                                  KnotTree<T, T_data>* start_knot);

  void output_tree(const int& x, const int& y, KnotTree<T, T_data>* node);

 public:
  class Iterator {
   protected:
    Tree* pointer = NULL;
    KnotTree<T, T_data>* node = NULL;
    Iterator(Tree<T, T_data>* node_tree, KnotTree<T, T_data>* node);

    KnotTree<T, T_data>* i_search(KnotTree<T, T_data>* node,
                                  const bool& up_level);

   public:
    Iterator();
    Iterator(Tree* node_tree);

    T_data& operator*();
    void operator++();
    void operator--();
    bool operator!=(const Iterator& other);
    bool operator==(const Iterator& other);

    friend class Tree;
    friend class reverse_Iterator;
  };

  class reverse_Iterator {
   protected:
    Tree* pointer = NULL;
    KnotTree<T, T_data>* node = NULL;
    reverse_Iterator(Tree<T, T_data>* node_tree, KnotTree<T, T_data>* node);

    KnotTree<T, T_data>* ri_search(KnotTree<T, T_data>* node,
                                   const bool& up_level);

   public:
    reverse_Iterator();
    reverse_Iterator(Tree* node_tree);

    T_data& operator*();
    void operator++();
    void operator--();
    bool operator!=(const reverse_Iterator& other);
    bool operator==(const reverse_Iterator& other);

    friend class Tree;
    friend class Iterator;
  };

  Tree();
  Tree(const Tree* other);
  ~Tree();

  int CheckSize();
  int CheckEmpty();
  int CountNodes();
  void CheckTree();

  vector<T> getKeys();
  T_data& GetLink(const T& key);
  bool Add(const T_data& value, const T& key);
  bool Delete(const T& key);
  void DeleteTree();

  Tree<T, T_data>::Iterator Begin();
  Tree<T, T_data>::Iterator End();
  Tree<T, T_data>::reverse_Iterator R_Begin();
  Tree<T, T_data>::reverse_Iterator R_End();

  friend class Iterator;
};

template <class T, class T_data>
int Tree<T, T_data>::count_node = 0;

template <class T, class T_data>
void Tree<T, T_data>::add_new_knot(KnotTree<T, T_data>* knot,
                                   const T_data& value,
                                   const T& key) {  //���������� ���� � ������
  count_node++;
  if (key >= knot->key) {
    if (knot->node_right != NULL)
      add_new_knot(knot->node_right, value, key);
    else {
      knot->node_right = new KnotTree<T, T_data>;
      knot->node_right->key = key;
      knot->node_right->data = value;
    }
  } else {
    if (knot->node_left != NULL)
      add_new_knot(knot->node_left, value, key);
    else {
      knot->node_left = new KnotTree<T, T_data>;
      knot->node_left->key = key;
      knot->node_left->data = value;
    }
  }
}

template <class T, class T_data>
void Tree<T, T_data>::delete_knot(KnotTree<T, T_data>* knot) {
  count_node++;
  if ((knot->node_left == NULL) && (knot->node_right == NULL)) {
    KnotTree<T, T_data>* parent = search_parent(knot, root_tree);
    if (parent == NULL) return;
    if (parent->node_left == knot) parent->node_left = NULL;
    if (parent->node_right == knot) parent->node_right = NULL;
    delete knot;
  } else if ((knot->node_left != NULL) && (knot->node_right == NULL)) {
    KnotTree<T, T_data>* parent = search_parent(knot, root_tree);
    if (parent == NULL) return;
    if (parent->node_left == knot) parent->node_left = knot->node_left;
    if (parent->node_right == knot) parent->node_right = knot->node_left;
    delete knot;
  } else if ((knot->node_left == NULL) && (knot->node_right != NULL)) {
    KnotTree<T, T_data>* parent = search_parent(knot, root_tree);
    if (parent == NULL) return;
    if (parent->node_left == knot) parent->node_left = knot->node_right;
    if (parent->node_right == knot) parent->node_right = knot->node_right;
    delete knot;
  } else if ((knot->node_left != NULL) && (knot->node_right != NULL)) {
    KnotTree<T, T_data>* d_knot = this->search_end(knot->node_left);
    T reserve_key = d_knot->key;
    knot->data = d_knot->data;
    delete_knot(d_knot);
    knot->key = reserve_key;
  }
}

template <class T, class T_data>
void Tree<T, T_data>::copy_tree(KnotTree<T, T_data>* receiver_knot,
                                KnotTree<T, T_data>* source_knot) {
  receiver_knot = new KnotTree<T, T_data>;
  receiver_knot->key = source_knot->key;
  receiver_knot->data = source_knot->data;
  if (source_knot->node_left != NULL)
    copy_tree(receiver_knot->node_left, source_knot->node_left);
  if (source_knot->node_right != NULL)
    copy_tree(receiver_knot->node_right, source_knot->node_right);
}

template <class T, class T_data>
void Tree<T, T_data>::delete_tree(KnotTree<T, T_data>* knot) {
  if (knot->node_left != NULL) {
    if ((knot->node_left->node_left != NULL) ||
        (knot->node_left->node_right != NULL)) {
      delete_tree(knot->node_left);
      delete knot->node_left;
    } else
      delete knot->node_left;
  }
  if (knot->node_right != NULL) {
    if ((knot->node_right->node_left != NULL) ||
        (knot->node_right->node_right != NULL)) {
      delete_tree(knot->node_right);
      delete knot->node_right;
    } else
      delete knot->node_right;
  }
}

template <class T, class T_data>
Tree<T, T_data>::KnotTree<T, T_data>* Tree<T, T_data>::search_begin(
    KnotTree<T, T_data>* knot) {
  if (knot->node_left != NULL)
    return search_begin(knot->node_left);
  else
    return knot;
}

template <class T, class T_data>
Tree<T, T_data>::KnotTree<T, T_data>* Tree<T, T_data>::search_end(
    KnotTree<T, T_data>* knot) {
  if (knot->node_right != NULL)
    return search_end(knot->node_right);
  else
    return knot;
}

template <class T, class T_data>
Tree<T, T_data>::KnotTree<T, T_data>* Tree<T, T_data>::search_parent(
    KnotTree<T, T_data>* knot, KnotTree<T, T_data>* start_knot) {
  if (start_knot == NULL) return start_knot;
  if (knot == root_tree) return NULL;
  if ((knot == start_knot->node_left) || (knot == start_knot->node_right))
    return start_knot;
  if (start_knot->key <= knot->key)
    return search_parent(knot, start_knot->node_right);
  if (start_knot->key > knot->key)
    return search_parent(knot, start_knot->node_left);
  return NULL;
}

template <class T, class T_data>
Tree<T, T_data>::KnotTree<T, T_data>* Tree<T, T_data>::search_key(
    const T& key, KnotTree<T, T_data>* start_knot) {
  count_node++;
  if (start_knot->key == key) return start_knot;
  if (start_knot->node_right != NULL)
    if (key >= start_knot->key) return search_key(key, start_knot->node_right);
  if (start_knot->node_left != NULL)
    if (key < start_knot->key) return search_key(key, start_knot->node_left);
  return NULL;
}

template <class T, class T_data>
void Tree<T, T_data>::output_tree(const int& x, const int& y,
                                  KnotTree<T, T_data>* knot) {
  write(x, y, knot->key);
  int k;
  k = (int)((double)8 * ((double)3 / (double)y));
  if (knot->node_left != nullptr) output_tree(x - k, y + 1, knot->node_left);
  if (knot->node_right != nullptr) output_tree(x + k, y + 1, knot->node_right);
}

template <class T, class T_data>
Tree<T, T_data>::Tree() {
  // nothing
}

template <class T, class T_data>
Tree<T, T_data>::Tree(const Tree* other) {
  copy_tree(this->root_tree, other->root_tree);
}

template <class T, class T_data>
Tree<T, T_data>::~Tree() {
  DeleteTree();
}

template <class T, class T_data>
int Tree<T, T_data>::CheckSize() {
  return size;
}

template <class T, class T_data>
int Tree<T, T_data>::CheckEmpty() {
  return (size == 0);
}

template <class T, class T_data>
int Tree<T, T_data>::CountNodes() {
  return count_node;
}

template <class T, class T_data>
void Tree<T, T_data>::CheckTree() {
  if (root_tree == nullptr) return;
  this->output_tree(50, 1, root_tree);
}

template <class T, class T_data>
vector<T> Tree<T, T_data>::getKeys() {
  vector<T> l;
  if (this->size == 0) return l;
  auto i = Iterator(this);
  for (i; i != this->End(); ++i) {
    l.push_back(i.node->key);
  }
  return l;
}

template <class T, class T_data>
T_data& Tree<T, T_data>::GetLink(const T& key) {
  if (size == 0) throw overflow_error("������� ����������");
  ;
  count_node = 0;
  KnotTree<T, T_data>* searching_data = search_key(key, root_tree);
  if (searching_data == NULL)
    throw overflow_error("������� ����������");
  else
    return searching_data->data;
}

template <class T, class T_data>
bool Tree<T, T_data>::Add(const T_data& value, const T& key) {
  if (root_tree != NULL) {
    if (this->search_key(key, this->root_tree) != nullptr) return false;
    count_node = 0;
    add_new_knot(root_tree, value, key);
  } else {
    count_node = 1;
    root_tree = new KnotTree<T, T_data>;
    root_tree->key = key;
    root_tree->data = value;
  }
  size++;
  return true;
}

template <class T, class T_data>
bool Tree<T, T_data>::Delete(const T& key) {
  if (size == 0) return false;
  count_node = 0;
  KnotTree<T, T_data>* searching_key = search_key(key, root_tree);
  if (searching_key != NULL) {
    delete_knot(searching_key);
    size--;
    return true;
  } else
    return false;
};

template <class T, class T_data>
void Tree<T, T_data>::DeleteTree() {
  if (size == 0) return;
  delete_tree(root_tree);
  delete root_tree;
  root_tree = NULL;
  size = 0;
};

template <class T, class T_data>
typename Tree<T, T_data>::Iterator Tree<T, T_data>::Begin() {
  Tree<T, T_data>::Iterator i(this);
  return i;
}

template <class T, class T_data>
typename Tree<T, T_data>::Iterator Tree<T, T_data>::End() {
  Tree<T, T_data>::Iterator i(this);
  if (size != 0)
    i.node = search_end(root_tree)->node_right;
  else
    i.node = root_tree;
  return i;
}

template <class T, class T_data>
typename Tree<T, T_data>::reverse_Iterator Tree<T, T_data>::R_Begin() {
  Tree<T, T_data>::reverse_Iterator i(this);
  if (size != 0)
    i.node = search_end(root_tree);
  else
    i.node = root_tree;
  return i;
}

template <class T, class T_data>
typename Tree<T, T_data>::reverse_Iterator Tree<T, T_data>::R_End() {
  Tree<T, T_data>::reverse_Iterator i(this);
  if (size != 0)
    i.node = i.node->node_left;
  else
    i.node = root_tree;
  return i;
}

template <class T, class T_data>
Tree<T, T_data>::KnotTree<T, T_data>* Tree<T, T_data>::Iterator::i_search(
    KnotTree<T, T_data>* node,
    const bool& up_level) {  //������� ��������� ������ �� �����������
  T min;  //����������� �� ������ ������ ����
  if ((node == this->node) || (up_level))
    min = INT_MAX;  //���� ������� ������� ������ ��������� � ��������� �
                    //���������, ���� �� ������� � �������� (� ���������
                    //��������� ����������� ��������), �� min ���������������
                    //�������������������
  else
    min = node->key;  //����� ����������� ��������������� ��������� ���������
                      //����������� ����
  char mode = '5';  //����� ����������� ��������. �� ��������� 5 - �������
                    //�������� ����������� ��������� �� ����������
  if (node->node_left != NULL) {  //���� ���� ����� ���, �� �� ��������������� �
                                  //�������� ���������� ������������ �����
    if ((min > node->node_left->key) &&
        (node->node_left->key > this->node->key)) {
      mode = '1';
      min = node->node_left->key;
    }
  }
  if (pointer->search_parent(node, pointer->root_tree) !=
      NULL) {  //���� ���� ��������, �� �� ��������������� � �������� ����������
               //������������ �����
    if ((min > pointer->search_parent(node, pointer->root_tree)->key) &&
        (pointer->search_parent(node, pointer->root_tree)->key >
         this->node->key)) {
      mode = '2';
      min = pointer->search_parent(node, pointer->root_tree)->key;
    }
  }
  if (node->node_right != NULL) {  //���� ���� ������ ���, �� �� ���������������
                                   //� �������� ���������� ������������ �����
    if ((min > node->node_right->key) &&
        (node->node_right->key > this->node->key))
      mode = '3';
  }
  if (node->node_right != NULL)
    if ((this->node == node) && (node->node_right->key == node->key) &&
        (mode == '5'))
      return i_search(node->node_right, 0);  //������ �� ���������� ������
  if (((node == this->node) && (mode == '5')) || ((up_level) && (mode == '5')))
    mode =
        '4';  //���� �� ����� � ����� � �� ����� ����� ���������� ������������,
              //�� ��������� � �������� �� ��� ���, ���� �� �����
  switch (mode) {
    case '1':
      return i_search(node->node_left, 0);  //����������� - ����� ���
    case '2':
      return i_search(pointer->search_parent(node, pointer->root_tree),
                      0);  //����������� - ��������
    case '3':
      return i_search(node->node_right, 0);  //����������� - ������ ���
    case '4':
      return i_search(pointer->search_parent(node, pointer->root_tree),
                      1);  //����������� ������� - ���� ������� (��������� �
                           //�����������, �������������� � ��)
    default:
      return node;  //������� ������� - �����������
  }
}

template <class T, class T_data>
Tree<T, T_data>::Iterator::Iterator() {}

template <class T, class T_data>
Tree<T, T_data>::Iterator::Iterator(Tree<T, T_data>* node_tree,
                                    KnotTree<T, T_data>* node) {
  this->node = node;
  this->pointer = node_tree;
}

template <class T, class T_data>
Tree<T, T_data>::Iterator::Iterator(Tree<T, T_data>* node_tree) {
  if (node_tree->size != 0)
    node = node_tree->search_begin(node_tree->root_tree);
  else
    node = node_tree->root_tree;
  pointer = node_tree;
}

template <class T, class T_data>
T_data& Tree<T, T_data>::Iterator::operator*() {
  if (node != NULL)
    return this->node->data;
  else
    throw overflow_error("�������� �� ����������");
  ;
}

template <class T, class T_data>
void Tree<T, T_data>::Iterator::operator++() {
  if (node == NULL) throw overflow_error("������� ����������");
  ;
  if (node == pointer->search_end(pointer->root_tree)) {
    node = pointer->search_end(pointer->root_tree)->node_right;
    return;
  }
  node = i_search(node, 0);
}

template <class T, class T_data>
void Tree<T, T_data>::Iterator::operator--() {
  if ((node == NULL) || (node == pointer->search_begin(pointer->root_tree)))
    throw overflow_error("������� ����������");
  else {
    Tree<T, T_data>::reverse_Iterator i;
    i.node = this->node;
    i.pointer = this->pointer;
    ++i;
    this->node = i.node;
  }
}

template <class T, class T_data>
bool Tree<T, T_data>::Iterator::operator!=(const Iterator& other) {
  return ((this->node != other.node) || (this->pointer != other.pointer));
}

template <class T, class T_data>
bool Tree<T, T_data>::Iterator::operator==(const Iterator& other) {
  return ((this->node == other.node) && (this->pointer == other.pointer));
}

template <class T, class T_data>
Tree<T, T_data>::KnotTree<T, T_data>*
Tree<T, T_data>::reverse_Iterator::ri_search(
    KnotTree<T, T_data>* node,
    const bool&
        up_level) {  //������� �������� i_search. ���� ������������ �������
                     //����� ������������ ������������ �������� � ���������.
  T max;
  if ((node == this->node) || (up_level))
    max = INT_MIN;
  else
    max = node->key;
  char mode = '5';
  if (node->node_left != NULL) {
    if ((max < node->node_left->key) &&
        (node->node_left->key < this->node->key)) {
      mode = '1';
      max = node->node_left->key;
    }
  }
  if (pointer->search_parent(node, pointer->root_tree) != NULL) {
    if ((max < pointer->search_parent(node, pointer->root_tree)->key) &&
        (pointer->search_parent(node, pointer->root_tree)->key <
         this->node->key)) {
      mode = '2';
      max = pointer->search_parent(node, pointer->root_tree)->key;
    }
  }
  if (node->node_right != NULL) {
    if ((max < node->node_right->key) &&
        (node->node_right->key < this->node->key))
      mode = '3';
  }
  if (pointer->search_parent(node, pointer->root_tree) != NULL)
    if ((this->node == node) &&
        (pointer->search_parent(node, pointer->root_tree)->key == node->key) &&
        (mode == '5'))
      return ri_search(pointer->search_parent(node, pointer->root_tree), 0);
  if (((node == this->node) && (mode == '5')) || ((up_level) && (mode == '5')))
    mode = '4';
  switch (mode) {
    case '1':
      return ri_search(node->node_left, 0);
    case '2':
      return ri_search(pointer->search_parent(node, pointer->root_tree), 0);
    case '3':
      return ri_search(node->node_right, 0);
    case '4':
      return ri_search(pointer->search_parent(node, pointer->root_tree), 1);
    default:
      return node;
  }
}

template <class T, class T_data>
Tree<T, T_data>::reverse_Iterator::reverse_Iterator() {}

template <class T, class T_data>
Tree<T, T_data>::reverse_Iterator::reverse_Iterator(Tree<T, T_data>* node_tree,
                                                    KnotTree<T, T_data>* node) {
  this->node = node;
  this->pointer = node_tree;
}

template <class T, class T_data>
Tree<T, T_data>::reverse_Iterator::reverse_Iterator(Tree* node_tree) {
  if (node_tree->size != 0)
    node = node_tree->search_end(node_tree->root_tree);
  else
    node = node_tree->root_tree;
  pointer = node_tree;
}

template <class T, class T_data>
T_data& Tree<T, T_data>::reverse_Iterator::operator*() {
  if (node != NULL)
    return this->node->data;
  else
    throw overflow_error("�������� �� ����������");
  ;
}

template <class T, class T_data>
void Tree<T, T_data>::reverse_Iterator::operator++() {
  if (node == NULL) throw overflow_error("������� ����������");
  ;
  if (node == pointer->search_begin(pointer->root_tree)) {
    node = pointer->search_begin(pointer->root_tree)->node_left;
    return;
  }
  node = ri_search(node, 0);
}

template <class T, class T_data>
void Tree<T, T_data>::reverse_Iterator::operator--() {
  if ((node == NULL) || (node == pointer->search_end(pointer->root_tree)))
    throw overflow_error("������� ����������");
  else {
    Tree<T, T_data>::Iterator i;
    i.node = this->node;
    i.pointer = this->pointer;
    ++i;
    this->node = i.node;
  }
}

template <class T, class T_data>
bool Tree<T, T_data>::reverse_Iterator::operator!=(
    const reverse_Iterator& other) {
  return ((this->node != other.node) || (this->pointer != other.pointer));
}

template <class T, class T_data>
bool Tree<T, T_data>::reverse_Iterator::operator==(
    const reverse_Iterator& other) {
  return ((this->node == other.node) && (this->pointer == other.pointer));
}
