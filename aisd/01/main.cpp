#include <unistd.h>

#include "collection.hpp"

void menu();
void print_menu();
int get_option(int choise);
void get_menu_opt(int choise);
void show_all_Collections();
void work_with_Collection();
void collection_menu(int param);
void print_coll_menu();
void get_coll_menu_opt(int choise, Collection<int>* coll);
void add_Node(Collection<int>* coll, int param);
void del_Node(Collection<int>* coll, int param);

Collection<int> first;
Collection<int> second;

int main() {
  menu();
  return 0;
}

void menu() {
  int choise = 0;

  do {
    print_menu();
    choise = get_option(choise);
    system("clear");
    get_menu_opt(choise);
    sleep(1);
  } while (choise);
}

void print_menu() {
  cout << "1) Show all Collections" << endl;
  cout << "2) Work with Collection.." << endl;
  cout << "0) End program" << endl;
}

int get_option(int choise) {
  int param = 0;

  do {
    cout << ": ";
    param = !(cin >> choise);
  } while (param);

  return choise;
}

void get_menu_opt(int choise) {
  switch (choise) {
    case 1:
      show_all_Collections();
      break;

    case 2:
      work_with_Collection();
      break;

    case 0:
      cout << "Exiting.." << endl;
      break;

    default:
      cout << "Wrong param" << endl;
      break;
  }
}

void show_all_Collections() {
  cout << "===Collection one===" << endl;
  cout << first << endl;
  cout << "===Collection two===" << endl;
  cout << second << endl;
}

void work_with_Collection() {
  int param;
  show_all_Collections();
  cout << "Which Collection to work with?\nChoise: " << endl;

  if (!(cin >> param) && (param != 1 || param != 2)) {
    cout << "Wrong collection number" << endl;
  } else {
    system("clear");
    collection_menu(param);
  }
}

void collection_menu(int param) {
  int choise = 0;

  do {
    if (param == 1) {
      cout << first << endl;
    } else {
      cout << second << endl;
    }

    print_coll_menu();
    choise = get_option(choise);
    system("clear");

    if (param == 1) {
      get_coll_menu_opt(choise, &first);
    } else {
      get_coll_menu_opt(choise, &second);
    }

    sleep(1);

  } while (choise);
}

void print_coll_menu() {
  cout << "1) Add new Node (in the End)" << endl;
  cout << "2) Add new Node (in beggining)" << endl;
  cout << "3) Delete Node (from beggining)" << endl;
  cout << "4) Delete Node (from end)" << endl;
  cout << "5) Insert Node" << endl;
  cout << "6) Erase Node (by num)" << endl;
  cout << "0) Stop working with Collection" << endl;
}

void get_coll_menu_opt(int choise, Collection<int>* coll) {
  system("clear");
  switch (choise) {
    case 1:
      add_Node(coll, 1);
      break;

    case 2:
      add_Node(coll, 0);
      break;

    case 3:
      del_Node(coll, 1);
      break;

    case 4:
      del_Node(coll, 0);
      break;

    case 5:
      add_Node(coll, 2);
      break;

    case 6:
      del_Node(coll, 2);
      break;

    case 0:
      cout << "Exiting.." << endl;
      break;

    default:
      cout << "Wrong param" << endl;
      break;
  }
}

void add_Node(Collection<int>* coll, int param) {
  cout << "===Enter valid int num===" << endl;

  int opt = 0;
  opt = get_option(opt);

  if (param == 1) {
    coll->push_back(opt);
  } else if (param == 2) {
    cout << "===Choose where to place===" << endl;
    int place = 0;
    place = get_option(opt);
    auto it = coll->find(place);
    coll->insert(it, opt);

  } else {
    coll->push_front(opt);
  }
}

void del_Node(Collection<int>* coll, int param) {
  cout << "Proceeding.." << endl;
  if (param == 1) {
    coll->pop_front();
  } else if (param == 2) {
    cout << "===Choose what num to delete===" << endl;
    int val = 0;
    val = get_option(val);
    coll->erase(val);
  } else {
    coll->pop_back();
  }
}
