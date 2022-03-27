#include <ostream>

#include "collection.hpp"
#include "gtest/gtest.h"

using namespace std;

Collection<int> make_list(const int size);

TEST(copy, ctor) {
  const int items_count = 10;
  auto list1 = make_list(items_count);

  Collection<int> list2(list1);
  ASSERT_EQ(list1.get_size(), list2.get_size());

  for (int n = 0; n < items_count; n++) {
    ASSERT_EQ(list1[n], list2[n]);
  }
}

TEST(init_list, ctor) {
  const int items_count = 4;
  auto list = {0, 1, 2, 3};
  int value = 0;

  for (auto it = list.begin(); it != list.end(); it++) {
    ASSERT_EQ(*it, value++);
  }

  ASSERT_EQ(list.size(), value);
}

TEST(push_front, methods) {
  const int items_count = 10;

  Collection<int> list;
  for (int n = 0; n < items_count; n++) {
    list.push_front(n);
    ASSERT_EQ(list.begin(), n);
  }
}

TEST(push_back, methods) {
  const int items_count = 10;

  Collection<int> list;
  for (int n = 0; n < items_count; n++) {
    list.push_back(n);
    ASSERT_EQ(list.find_tail(), n);
  }
}

TEST(pop_front, methods) {
  const int items_count = 10;

  auto list = make_list(items_count);
  for (int n = 0; n < items_count; n++) {
    list.pop_front();

    if (list.get_size() > 0) {
      ASSERT_EQ(list.begin(), n + 1);
    }
  }
  ASSERT_EQ(list.get_size(), 0);
}

TEST(pop_back, methods) {
  const int items_count = 10;

  auto list = make_list(items_count);
  for (int n = 0; n < items_count; n++) {
    list.pop_back();

    if (list.get_size() > 0) {
      ASSERT_EQ(list.find_tail(), items_count - n - 2);
    }
  }
  ASSERT_EQ(list.get_size(), 0);
}

TEST(size, methods) {
  const int items_count = 10;
  const auto list = make_list(items_count);

  ASSERT_EQ(list.get_size(), items_count);
}

TEST(clear, methods) {
  const int items_count = 10;

  auto list = make_list(items_count);
  ASSERT_EQ(items_count, list.get_size());

  list.clear();
  ASSERT_EQ(0, list.get_size());
}

TEST(find, methods) {
  const int items_count = 10;

  auto list = make_list(items_count);

  for (auto it = list.begin(); it != list.end(); it++) {
    auto target = list.find(list.begin(), list.end(), *it);
    ASSERT_EQ(*target, *it);
  }
}

TEST(insert, methods) {
  int items_count = 10;
  Collection<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);
  list1.push_back(4);

  Collection<int> list2;
  list2.push_back(1);
  list2.push_back(2);
  list2.push_back(5);
  list2.push_back(3);
  list2.push_back(4);

  Collection<int> list3;

  auto it = list1.find(3);
  list1.insert(it, 5);

  ASSERT_EQ(list1.get_size(), list2.get_size());
  ASSERT_EQ(list1, list2);

  for (int n = 0; n < items_count; n++) {
    list3.insert(list3.end(), n);
    ASSERT_EQ(list3.find_tail(), n);
    ASSERT_EQ(list3.get_size(), n + 1);
  }
}

TEST(erase, methods) {
  const int items_count = 10;

  auto list1 = make_list(items_count);
  for (int n = 0; n < items_count; n++) {
    auto next = list1.erase(n);
    ASSERT_EQ(next, (list1.get_size() == 0 ? list1.end() : list1.begin()));
  }
  ASSERT_EQ(list1.get_size(), 0);

  auto list2 = make_list(items_count);
  for (int n = items_count - 1; n >= 0; n--) {
    auto next = list2.erase(n);
    ASSERT_EQ(next, list2.end());
  }
  ASSERT_EQ(list2.get_size(), 0);
}

TEST(forward, iterators) {
  const int items_count = 10;
  auto list = make_list(items_count);
  int value = 0;

  for (auto it = list.begin(); it != list.end(); it++) {
    ASSERT_EQ(*it, value++);
  }

  ASSERT_EQ(value, items_count);
}

TEST(index_write, operator) {
  const int items_count = 10;
  auto list = make_list(items_count);

  for (int n = 0; n < list.get_size(); n++) {
    list[n] = 0;
  }

  for (auto it = list.begin(); it != list.end(); it++) {
    ASSERT_EQ(*it, 0);
  }
}

TEST(index_read, operator) {
  const int items_count = 10;
  int value = 0;

  auto list = make_list(items_count);
  for (int n = 0; n < list.get_size(); n++) {
    ASSERT_EQ(list[n], value++);
  }
}

TEST(copy, operator) {
  const int items_count = 10;
  auto list1 = make_list(items_count);
  auto list2 = list1;

  ASSERT_EQ(list1.get_size(), list2.get_size());

  for (int n = 0; n < items_count; n++) {
    ASSERT_EQ(list1[n], list2[n]);
  }

  list1.clear();
  for (int n = 0; n < items_count; n++) {
    ASSERT_EQ(list2[n], n);
  }
}

TEST(compare, operator) {
  const int items_count = 10;
  auto list1 = make_list(items_count);
  auto list2 = make_list(items_count);
  auto list3 = make_list(items_count);

  list3[0] = list3[1];
  ASSERT_EQ(list1, list2);
  ASSERT_NE(list2, list3);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

Collection<int> make_list(const int size) {
  Collection<int> list;
  for (int n = 0; n < size; n++) {
    list.push_back(n);
  }

  return list;
}
