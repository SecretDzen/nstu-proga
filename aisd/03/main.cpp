#include "avl_tree.hpp"

using namespace std;
void show_tree();
void show_menu();
void iterator_menu();
void show_wrong();
void edit_step(int _param);
void tree_insert();
void tree_erase();
void show_min();
void show_max();
void show_root();
void show_size();

avl<int> one;
int curr_val = 0;

int main() {
  int param = 0;

  do {
    show_tree();
    show_menu();

    cout << "Enter: ";
    cin >> param;

    system("clear");

    if (param) edit_step(param);
  } while (param);

  return 0;
}

void show_min() {
  auto it = one.find_min(one.get_root());
  cout << "=================" << endl;
  if (it) {
    cout << "Minimal key: " << one.get_val(it) << endl;
  } else {
    cout << "Empty tree" << endl;
  }
  cout << "=================" << endl;
}

void show_max() {
  auto it = one.find_max(one.get_root());
  cout << "=================" << endl;
  if (it) {
    cout << "Max key: " << one.get_val(it) << endl;
  } else {
    cout << "Empty tree" << endl;
  }
  cout << "=================" << endl;
}

void show_root() {
  auto it = one.get_root();
  cout << "=================" << endl;
  if (it) {
    cout << "Root key: " << one.get_val(it) << endl;
  } else {
    cout << "Empty tree" << endl;
  }
  cout << "=================" << endl;
}

void show_size() {
  int it = one.get_size();
  cout << "=================" << endl;
  cout << "Tree size: " << it << endl;
  cout << "=================" << endl;
}

void show_wrong() {
  cout << "================================" << endl;
  cout << "You entered wrong key. Try again" << endl;
  cout << "================================" << endl;
}

void tree_insert() {
  int key = 0;

  do {
    cin.clear();
    cin.ignore(80, '\n');

    cout << "Enter key to insert: ";
    cin >> key;

    system("clear");
    if (cin.fail()) show_wrong();

  } while (cin.fail());

  one.insert(key);
}

void tree_erase() {
  int key = 0;

  do {
    cin.clear();
    cin.ignore(80, '\n');

    cout << "Enter key to erase: ";
    cin >> key;

    system("clear");
    if (cin.fail()) show_wrong();

  } while (cin.fail());

  one.erase(key);
}

void edit_step(int _param) {
  switch (_param) {
    case 1:
      tree_insert();
      break;

    case 2:
      tree_erase();
      break;

    case 3:
      show_min();
      break;

    case 4:
      show_max();
      break;

    case 5:
      show_root();
      break;

    case 6:
      show_size();
      break;

    case 7:
      iterator_menu();
      break;

    default:
      cout << "Wrong param given" << endl;
      break;
  }
}

void show_tree() {
  cout << "===Lt-t-Rt display===" << endl;
  one.show_tree();
  cout << endl;
}

void show_menu() {
  cout << "===Program menu===" << endl;
  cout << "1) Insert Node" << endl;
  cout << "2) Erase Node" << endl;
  cout << "3) Show min key" << endl;
  cout << "4) Show max key" << endl;
  cout << "5) Show root" << endl;
  cout << "6) Show size" << endl;
  cout << "7) Iterator menu" << endl;
  cout << "0) Exit" << endl;
  cout << endl;
}

void iterator_menu() {
  system("clear");

  auto it = one.begin();
  auto it_node = it.get_node();
  if (it_node) {
    cout << "Key: " << it_node->get_val() << endl;
    cout << "Parent: ";
    if (it_node->get_P()) {
      auto prt = it_node->get_P();
      cout << prt->get_val() << endl;
    } else {
      cout << "nullptr" << endl;
    }

    cout << "Right tree: ";
    if (it_node->get_R()) {
      auto prt = it_node->get_R();
      cout << prt->get_val() << endl;
    } else {
      cout << "nullptr" << endl;
    }

    cout << "Left tree: ";
    if (it_node->get_L()) {
      auto prt = it_node->get_L();
      cout << prt->get_val() << endl;
    } else {
      cout << "nullptr" << endl;
    }
  }

  int backward = 0;
  while (true) {
    cout << "=== Menu ===" << endl;
    cout << "1) Next" << endl;
    cout << "2) Back" << endl;
    cout << "3) begin" << endl;
    cout << "4) rbegin" << endl;
    cout << "5) end" << endl;
    cout << "6) rend" << endl;
    cout << "0) Back" << endl;
    int key;
    int error = 0;

    do {
      cin.clear();
      cin.ignore(80, '\n');

      cout << "Enter param: ";
      cin >> key;

      system("clear");
      if (cin.fail()) show_wrong();

    } while (cin.fail());

    switch (key) {
      case 1:
        if (it_node) {
          if (backward) {
            it--;
            it_node = it.get_node();
          } else {
            it++;
            it_node = it.get_node();
          }
        }
        break;

      case 2:
        if (it_node) {
          if (backward) {
            it--;
            it_node = it.get_node();
          } else {
            it++;
            it_node = it.get_node();
          }
        }
        break;

      case 3:
        it = one.begin();
        backward = 0;
        it_node = it.get_node();
        break;

      case 4:
        it = one.rbegin();
        backward = 1;
        it_node = it.get_node();
        break;

      case 5:
        it = one.end();
        backward = 0;
        it_node = it.get_node();
        break;

      case 6:
        it = one.rend();
        backward = 1;
        it_node = it.get_node();
        break;

      default:
        cout << "Wrong key given" << endl;
        error = 1;
        break;
    }

    if (error) break;

    if (it_node) {
      cout << "Key: " << it_node->get_val() << endl;
      cout << "Parent: ";
      if (it_node->get_P()) {
        auto prt = it_node->get_P();
        cout << prt->get_val() << endl;
      } else {
        cout << "nullptr" << endl;
      }

      cout << "Right tree: ";
      if (it_node->get_R()) {
        auto prt = it_node->get_R();
        cout << prt->get_val() << endl;
      } else {
        cout << "nullptr" << endl;
      }

      cout << "Left tree: ";
      if (it_node->get_L()) {
        auto prt = it_node->get_L();
        cout << prt->get_val() << endl;
      } else {
        cout << "nullptr" << endl;
      }
    } else {
      cout << "End of the tree" << endl;
    }
  }
}
