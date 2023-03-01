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

TEST(VECTOR_MODIFIERS_TEST, eraseTest) {
  // erase(iterator it) test
  std::vector<int> v1(4, 100);
  ft::vector<int> v2(4, 100);
  auto r1 = v1.erase(v1.begin());
  auto r2 = v2.erase(v2.begin());
  EXPECT_EQ(r1 - v1.begin(), r2 - v2.begin());
  EXPECT_EQ(v1.size(), v2.size());
  for (size_t i = 0; i < v1.size(); i++) {
    EXPECT_EQ(v1[i], v2[i]);
  }

  // erase(iterator first, iterator last) test
  std::vector<int> v3(10, 100);
  ft::vector<int> v4(10, 100);
  auto r3 = v3.erase(v3.begin(), v3.begin() + 2);
  auto r4 = v4.erase(v4.begin(), v4.begin() + 2);
  EXPECT_EQ(r3 - v3.begin(), r4 - v4.begin());
  SHOW(r3 - v3.begin());
  EXPECT_EQ(v3.size(), v4.size());
  for (size_t i = 0; i < v3.size(); i++) {
    EXPECT_EQ(v3[i], v4[i]);
  }

  // erase(iterator first, iterator last) test
  std::vector<int> v5(10, 100);
  ft::vector<int> v6(10, 100);
  auto r5 = v5.erase(v5.begin() + 3, v5.begin() + 6);
  auto r6 = v6.erase(v6.begin() + 3, v6.begin() + 6);
  EXPECT_EQ(r5 - v5.begin(), r6 - v6.begin());
  EXPECT_EQ(v5.size(), v6.size());
  for (size_t i = 0; i < 12; i++) {
    EXPECT_EQ(v5[i], v6[i]);
  }

  // erase(iterator first, iterator last) end() 포함하는 test
  std::vector<int> v7(5, 100);
  ft::vector<int> v8(5, 100);
  auto r7 = v7.erase(v7.begin() + 3, v7.begin() + 5);
  auto r8 = v8.erase(v8.begin() + 3, v8.begin() + 5);
  EXPECT_EQ(r7 - v7.begin(), r8 - v8.begin());
  EXPECT_EQ(v7.size(), v8.size());
  for (size_t i = 0; i < v7.capacity(); i++) {
    std::cout << i << std::endl;
    EXPECT_EQ(v7[i], v8[i]);
  }

  // erase(iterator first, iterator last) 처음부터 끝까지 다 지우는 테케
  std::vector<int> v9(5, 1);
  ft::vector<int> v10(5, 1);
  auto r9 = v9.erase(v9.begin(), v9.end());
  auto r10 = v10.erase(v10.begin(), v10.end());
  EXPECT_EQ(r9 - v9.begin(), r10 - v10.begin());
  EXPECT_EQ(v9.size(), v10.size());
  for (size_t i = 0; i < v9.size(); i++) {
    std::cout << i << ": " << v9[i] << ", " << v10[i] << std::endl;
    EXPECT_EQ(v9[i], v10[i]);
  }
}

TEST(VECTOR_MODIFIERS_TEST, assginTest) {
  std::vector<int> v1(4, 100);
  ft::vector<int> v2(4, 100);

  v1.assign(5, 1);
  v2.assign(5, 1);

  for (size_t i = 0; i < v1.size(); i++) {
    std::cout << i << ": " << v1[i] << ", " << v2[i] << std::endl;
  }
}

TEST(VECTOR_MODIFIERS_TEST, insertTest) {
  std::vector<int> v1(4, 100);
  ft::vector<int> v2(4, 100);

  // single insert test
  v1.insert(v1.begin(), 1);
  v2.insert(v2.begin(), 1);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(*v1.end(), *v2.end());
  SHOW(*v2.end());
  for (size_t i = 0; i < v1.size(); i++) {
    EXPECT_EQ(v1[i], v2[i]);
  }

  // fill insert test
  v1.insert(v1.begin() + 3, 4, 4);
  v2.insert(v2.begin() + 3, 4, 4);
  EXPECT_EQ(v1.size(), v2.size());
  for (size_t i = 0; i < v1.size(); i++) {
    EXPECT_EQ(v1[i], v2[i]);
  }

  // range insert test
  int arr[] = {11, 12, 13, 14};
  v1.insert(v1.begin() + 1, arr, arr + 4);
  v2.insert(v2.begin() + 1, arr, arr + 4);
  for (size_t i = 0; i < v1.size(); i++) {
    std::cout << i << ": " << v1[i] << ", " << v2[i] << std::endl;
  }
}
