/*
 * File: vector_test.cpp
 * Project: ft_container
 * Created Date: 2023/02/08
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#include "gtest/gtest.h"
#include "vector.hpp"

#include <vector>

#include <iostream>

#define SHOW(...) \
    std::cout << std::setw(29) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

TEST (VECTOR_ITERATOR_TEST, iteratorTest) {
  // create 5 element of value 100
  ft::vector<int> v(5, 100);

  SHOW(v.begin().base());
  SHOW(v.end().base());

  ft::vector<int>::iterator begin(v.begin());
  ft::vector<int>::iterator end(v.end());

  SHOW(end - begin);
}

TEST (VECTOR_CONTRUCTOR_TEST, constructorTest) {
  // check iterator;
  std::vector<int>::iterator it1;
  ft::vector<int>::iterator it2;

  // default constructor
  std::vector<int> default_v1;
  ft::vector<int> defautl_v2;

  // fill constructor
  std::vector<int> fill_v1(4, 100);
  ft::vector<int> fill_v2(4, 100);

  it1 = fill_v1.begin();
  it2 = fill_v2.begin();
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(*it1, *it2);
    it1++;
    it2++;
  }

  // range constructor
  std::vector<int> range_v1(fill_v1.begin(), fill_v1.end());
  ft::vector<int> range_v2(fill_v2.begin(), fill_v2.end());
  it1 = range_v1.begin();
  it2 = range_v2.begin();
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(*it1, *it2);
    it1++;
    it2++;
  }

  // copy constructor
  std::vector<int> copy_v1(range_v1);
  ft::vector<int> copy_v2(range_v2);
  it1 = copy_v1.begin();
  it2 = copy_v2.begin();
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(*it1, *it2);
    it1++;
    it2++;
  }
};

TEST (VECTOR_CAPACITY_TEST, capacityTest) {
  ft::vector<int> v(5, 100);

  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.empty(), false);
  EXPECT_EQ(v.capacity(), 5);

  std::vector<int> std_vec;
  std_vec.push_back(7);
  std_vec.push_back(7);
  // size 2

  for (int &it : std_vec) {
    std::cout << it << " ";
  }
  std::cout << std::endl;
  // n < size() && n < capacity() capacity 안지움
  std_vec.resize(1, 8);
  for (int &it : std_vec) {
    std::cout << it << " ";
  }
  SHOW(std_vec.size());
  SHOW(std_vec.capacity());

  // n > size()
//  std_vec.resize()

  std_vec.resize(5);
  SHOW(std_vec.size());
  SHOW(std_vec.capacity());
}

TEST(VECTOR_CAPACITY_TEST, assignTest) {
  std::vector<int> v1(4, 100);
  for (int &it : v1) {
    std::cout << it << " ";
  }
  v1.assign(7, 7);
  std::cout << std::endl;
  for (int &it : v1) {
    std::cout << it << " ";
  }
}

TEST(VECTOR_ERASE_TEST, eraseTest) {
  // erase(iterator it) test
  std::vector<int> v1(4, 100);
  ft::vector<int> v2(4, 100);
  auto r1 = v1.erase(v1.begin());
  auto r2 = v2.erase(v2.begin());
  EXPECT_EQ(r1 - v1.begin(), r2 - v2.begin());
  EXPECT_EQ(v1.size(), v2.size());
  for (int i = 0; i < v1.size(); i++) {
    EXPECT_EQ(v1[i], v2[i]);
  }

  // erase(iterator first, iterator last) test
  std::vector<int> v3(10, 100);
  ft::vector<int> v4(10, 100);
  auto r3 = v3.erase(v3.begin(), v3.begin() + 2);
  auto r4 = v4.erase(v4.begin(), v4.begin() + 2);
  EXPECT_EQ(r3 - v3.begin(), r4 - v4.begin());
  EXPECT_EQ(v3.size(), v4.size());
  for (int i = 0; i < v3.size(); i++) {
    EXPECT_EQ(v3[i], v4[i]);
  }
}
