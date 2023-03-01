/*
 * File: test.cpp
 * Project: ft_container
 * Created Date: 2023/03/01
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#if STD
#include <map>
#include <vector>
#include <stack>
#define TEST_NAMESPACE std
#define NAMESPACE_STRING "std"
#else
#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"
#define TEST_NAMESPACE ft
#define NAMESPACE_STRING "ft"
#endif

#include <iostream>
#include <iomanip>
#include <string>

#define SHOW(...) \
    std::cout << std::setw(29) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

template<class Container>
void print_container_elements(Container container) {
  for (typename Container::iterator it = container.begin(); it != container.end(); it++) {
    std::cout << *it << std::endl;
  }
}

template<class Container>
void print_map_elements(Container container) {
  for (typename Container::iterator it = container.begin(); it != container.end(); it++) {
    std::cout << (*it).first << " : " << (*it).second << std::endl;
  }
}

void map_test() {
  std::cout << "MAP TEST" << std::endl;

  // constructor test
  TEST_NAMESPACE::map<char, int> default_map;
  default_map['a'] = 10;
  default_map['b'] = 30;
  default_map['c'] = 50;
  default_map['d'] = 70;

  TEST_NAMESPACE::map<char, int> range_map(default_map.begin(), default_map.end());
  TEST_NAMESPACE::map<char, int> copy_map(range_map);

  print_map_elements(default_map);
  print_map_elements(range_map);
  print_map_elements(copy_map);

  // begin
  SHOW(default_map.begin()->first);

  // end
  SHOW((--default_map.end())->first);

  // rbegin
  SHOW(default_map.rbegin()->first);

  // rend
  SHOW((--default_map.rend())->first);

  // empty
  TEST_NAMESPACE::map<char, int> tmp;
  SHOW(tmp.empty());

  SHOW(default_map.empty());

  // equal range
  SHOW(default_map.equal_range('b').first->first);

  // erase
  default_map.erase('b');
  print_map_elements(default_map);

  default_map.erase(default_map.begin());
  print_map_elements(default_map);

  default_map.erase(default_map.begin(), ++default_map.begin());
  print_map_elements(default_map);

  // find
  SHOW(range_map.find('a')->first);
  SHOW(range_map.find('b')->first);
  SHOW(range_map.find('c')->first);

  // insert
  copy_map.insert(TEST_NAMESPACE::pair<char, int>('f', 2));
  print_map_elements(copy_map);

  copy_map.insert(copy_map.begin(), TEST_NAMESPACE::pair<char, int>('g', 2));
  print_map_elements(copy_map);

  copy_map.insert(default_map.begin(), default_map.end());
  print_map_elements(copy_map);

  // key_comp
  TEST_NAMESPACE::map<char, int>::key_compare mycomp = copy_map.key_comp();
  char highest = copy_map.rbegin()->first;
  TEST_NAMESPACE::map<char, int>::iterator it = copy_map.begin();
  while (mycomp((*it++).first, highest)) {
    std::cout << it->first << "=>" << it->second << std::endl;
  }

  // lower_bound
  SHOW(copy_map.lower_bound('b')->first);

  // upper_bound
  SHOW(copy_map.upper_bound('b')->first);

  // max_size
  SHOW(copy_map.max_size());

  // operator[]
  SHOW(copy_map['a']);
  SHOW(copy_map['b']);
  SHOW(copy_map['c']);

  // size
  SHOW(copy_map.size());
  SHOW(default_map.size());

  // swap
  copy_map.swap(default_map);
  print_map_elements(copy_map);
  print_map_elements(default_map);

  // value_comp
  TEST_NAMESPACE::map<char, int>::value_compare myvalcomp = copy_map.value_comp();
  TEST_NAMESPACE::pair<char, int> highest_val = *copy_map.rbegin();
  TEST_NAMESPACE::map<char, int>::iterator it_val = copy_map.begin();
  while (copy_map.value_comp()(*it_val++, highest_val)) {
    std::cout << it_val->first << "=>" << it_val->second << std::endl;
  }
}

void stack_test() {
  std::cout << "STACK TEST" << std::endl;

  // constructor test
  TEST_NAMESPACE::stack<int> stack;
  TEST_NAMESPACE::stack<int> tmp;

  // empty
  SHOW(stack.empty());

  // push
  for (int i = 0; i < 10; i++)
    stack.push(i);

  // pop
  while (!stack.empty()) {
    SHOW(stack.top());
    stack.pop();
  }

  // size
  SHOW(stack.size());

  stack.push(4);
  SHOW(stack.size());

  // swap
  TEST_NAMESPACE::swap(stack, tmp);
  while (!stack.empty()) {
    SHOW(stack.top());
    stack.pop();
  }
  while (!tmp.empty()) {
    SHOW(tmp.top());
    tmp.pop();
  }
}

void vector_test() {
  std::cout << "VECTOR TEST" << std::endl;

  // constructor test
  TEST_NAMESPACE::vector<int> tmp_v;
  TEST_NAMESPACE::vector<int> default_v;
  TEST_NAMESPACE::vector<int> fill_v(4, 100); // 4번 100 이라는 element 넣는 vector
  TEST_NAMESPACE::vector<int> range_v(fill_v.begin(), fill_v.end());
  TEST_NAMESPACE::vector<int> copy_v(range_v);

  default_v.reserve(10);
  for (int i = 0; i < 10; i++)
    default_v.push_back(i);
  print_container_elements(default_v);
  print_container_elements(fill_v);
  print_container_elements(range_v);
  print_container_elements(copy_v);

  // assign test

  tmp_v.assign(range_v.begin(), range_v.begin() + 2);
  print_container_elements(tmp_v);

  tmp_v.assign(7, 100); // 7 ints with a value of 100
  print_container_elements(tmp_v);

  // at
  SHOW(default_v.at(0));
  SHOW(default_v.at(1));

  // operator[]
  SHOW(default_v[0]);
  SHOW(default_v[2]);

  // front
  SHOW(default_v.front());

  // back
  SHOW(default_v.back());

  // begin
  SHOW(*default_v.begin());

  // end
  SHOW(*default_v.end());

  // rbegin
  SHOW(*default_v.rbegin());

  // rend
  SHOW(*default_v.rend());

  // capacity
  SHOW(default_v.capacity());

  // clear
  tmp_v.clear();
  print_container_elements(tmp_v);

  // empty
  SHOW(tmp_v.empty());
  SHOW(default_v.empty());

  // erase
  default_v.erase(default_v.end() - 1);
  print_container_elements(default_v);

  default_v.erase(default_v.begin() + 1, default_v.end());
  print_container_elements(default_v);

  // insert
  tmp_v.insert(tmp_v.begin(), 4);
  print_container_elements(tmp_v);

  tmp_v.insert(tmp_v.begin(), 7, 4);
  print_container_elements(tmp_v);

  SHOW(tmp_v.size());
  tmp_v.insert(tmp_v.begin(), range_v.begin(), range_v.end());
  SHOW(tmp_v.size());
  print_container_elements(tmp_v);

  // max_size --> it can be different
  SHOW(tmp_v.max_size());

  // pop_back
  default_v.pop_back();
  print_container_elements(default_v);

  // push_back
  default_v.push_back(4);
  print_container_elements(default_v);

  // reserve
  default_v.reserve(100);
  print_container_elements(default_v);

  // resize
  default_v.resize(3);
  print_container_elements(default_v);

  // size
  SHOW(default_v.size());
  print_container_elements(default_v);

  // swap
  default_v.swap(tmp_v);
  print_container_elements(default_v);
  print_container_elements(tmp_v);
}

int main(int argc, char **argv) {
  // ./test vector
  // ./test map
  // ./test stack

  SHOW(NAMESPACE_STRING);

  if (argc == 1 || (argc == 2 && std::strcmp(argv[1], "all") == 0)) {
    vector_test();
    stack_test();
    map_test();
  } else if (std::strcmp(argv[1], "vector") == 0) {
    vector_test();
  } else if (std::strcmp(argv[1], "stack") == 0) {
    stack_test();
  } else if (std::strcmp(argv[1], "map") == 0) {
    map_test();
  } else {
    std::cout << "Command not found" << std::endl;
  }
  return 0;
}