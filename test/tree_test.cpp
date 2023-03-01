/*
 * File: tree_test.cpp
 * Project: ft_container
 * Created Date: 2023/02/21
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#include "gtest/gtest.h"
#include "tree.hpp"
#include "pair.hpp"

#include <iostream>
#include <string>

#define SHOW(...) \
    std::cout << std::setw(29) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

class RbTreeTest : public ::testing::Test {
  typedef int key_type;
  typedef int val_type;
  typedef ft::pair<key_type, val_type> value_type;
 protected:
  void SetUp() override {
    ft_tree.insert_unique(ft::pair<int, int>(1, 1));
    ft_tree.insert_unique(ft::pair<int, int>(2, 1));
    ft_tree.insert_unique(ft::pair<int, int>(3, 1));
    ft_tree.insert_unique(ft::pair<int, int>(4, 1));

    ft_tree2.insert_unique(ft::pair<int, int>(3, 1));
    ft_tree2.insert_unique(ft::pair<int, int>(4, 1));
  }

  ft::_rb_tree<key_type, value_type> ft_tree;
  ft::_rb_tree<key_type, value_type> ft_tree2;
};

TEST_F(RbTreeTest, insertSingleTest) {
  ft_tree.printBT();

  ft_tree.insert_unique(ft::pair<int, int>(5, 1));
  ft_tree.printBT();
  ft_tree.insert_unique(ft::pair<int, int>(6, 1));
  ft_tree.printBT();

  ft_tree.insert_unique(ft::pair<int, int>(7, 1));
  ft_tree.printBT();
  ft_tree.insert_unique(ft::pair<int, int>(8, 1));
  ft_tree.printBT();
}

TEST_F(RbTreeTest, boundsTest) {

}

TEST_F(RbTreeTest, iteratorTest) {

}

TEST_F(RbTreeTest, iteratorFunctionTest) {
  // tree.begin
  // tree.end
  // tree.rbegin
  // tree.rend;
}

TEST_F(RbTreeTest, capacityFunctionTest) {
  // tree.size
  // tree.max_size
  // tree.empty
}