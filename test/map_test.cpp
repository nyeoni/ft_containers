/*
 * File: map_test.cpp
 * Project: ft_container
 * Created Date: 2023/02/20
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#include "gtest/gtest.h"
#include "pair.hpp"
#include "map.hpp"

#include <map>
#include <iostream>

#define SHOW(...) \
    std::cout << std::setw(29) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

class MapTest : public ::testing::Test {
 protected:
  void SetUp() override {
    ft_map.insert(ft::pair<int, char>(1, '1'));
    ft_map.insert(ft::pair<int, char>(2, '2'));
    ft_map.insert(ft::pair<int, char>(3, '3'));
    ft_map.insert(ft::pair<int, char>(4, '4'));
  }

  ft::map<int, char> ft_map;
};

TEST_F(MapTest, insertTest) {
  ft_map.test();

  ft_map.insert(ft::pair<int, char>(5, '1'));
  ft_map.insert(ft::pair<int, char>(6, '2'));
  ft_map.insert(ft::pair<int, char>(7, '3'));
  ft_map.insert(ft::pair<int, char>(8, '4'));

  ft_map.test();
}

TEST_F(MapTest, iteratorTest) {
  ft::map<int, char>::iterator it = ft_map.begin();

  int i = 0;
  while (it != ft_map.end()) {
    std::cout << i << ": " << it->first << std::endl;
    it++;
    i++;
  }

  SHOW((--it)->first);
}

TEST (MAP_ITERATOR_TEST, iteratorTest) {
  std::map<int, int> first;

  first[1] = 10;
  first[4] = 30;
  first[2] = 50;
  first[3] = 70;

  std::map<int, int>::iterator it = first.begin();
  while (it != first.end()) {
    SHOW((it->first));
    it++;
  }
  it = first.end();
  SHOW((--it)->first);
}