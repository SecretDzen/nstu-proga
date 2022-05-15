#include <unistd.h>

#include "bst_tree.hpp"

using namespace std;

void show_tree();
void show_menu();
void show_wrong();
void edit_step(int _param);
void tree_insert();
void tree_erase();
void show_min();
void show_max();
void show_root();
void show_size();

bst_tree<int> one;
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

  cout << "Exiting.." << endl;
  sleep(1);
  system("clear");

  return 0;
}

void show_min() {
  auto it = one.find_min();
  cout << "=================" << endl;
  if (it) {
    cout << "Minimal key: " << one.get_val(it) << endl;
  } else {
    cout << "Empty tree" << endl;
  }
  cout << "=================" << endl;
}

void show_max() {
  auto it = one.find_max();
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

    default:
      cout << "Wrong param given" << endl;
      break;
  }
}

void show_tree() {
  cout << "===Lt-Rt-t display===" << endl;
  one.display();
  cout << endl;
}

void show_menu() {
  cout << "===Program menu===" << endl;
  cout << "1) Insert Node" << endl;
  cout << "2) Erase Node" << endl;
  cout << "3) Show min key" << endl;
  cout << "4) Show max key" << endl;
  cout << "5) Show root key" << endl;
  cout << "6) Show size" << endl;
  cout << "0) Exit" << endl;
  cout << endl;
}
