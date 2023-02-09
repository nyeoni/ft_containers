/*
 * File: type_traits_test.cpp
 * Project: ft_container
 * Created Date: 2023/02/07
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#include "type_traits.hpp"
#include "gtest/gtest.h"
#include "vector.hpp"
#include <iostream>

#define SHOW(...) \
    std::cout << std::setw(29) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

template<typename T>
class IsIntegralTest : public ft::is_integral<T>, public ::testing::Test {};

class A {};

using IntegralTypes = ::testing::Types<bool,
                                       char,
                                       char16_t,
                                       char32_t,
                                       signed char,
                                       unsigned char,
                                       wchar_t,
                                       short,
                                       unsigned short,
                                       int, unsigned int, long, unsigned long, long long, unsigned long long>;
TYPED_TEST_SUITE(IsIntegralTest, IntegralTypes);

TYPED_TEST(IsIntegralTest, IsIntegralCorrect) {
  typename TestFixture::value_type val = TestFixture::value;
  EXPECT_EQ(val, 1);
}

// is_integral test
TEST(IS_ITEGRAL_TEST, IsIntegralWrong) {
  SHOW(ft::is_integral<bool>::value);
  bool result = ft::is_integral<bool>::value;
  EXPECT_EQ(result, 1);

  SHOW(ft::is_integral<int>::value);
  result = ft::is_integral<int>::value;
  EXPECT_EQ(result, 1);

  class A {};
  SHOW(ft::is_integral<A>::value);
  bool wrong_result = ft::is_integral<A>::value;
  EXPECT_EQ(wrong_result, 0);
}

// is_iterator_test
TEST(IS_ITERATOR_TEST, IsIteratorTest) {
  SHOW(ft::is_iterator<ft::_vector_iterator<int *>>::value);

  class A {};
  SHOW(ft::is_iterator<A>::value);
  SHOW(ft::is_iterator<bool>::value);

  SHOW(ft::is_iterator<int *>::value);
}

// is_forward_iterator
TEST(IS_FORWARD_ITERATOR, IsForwardIteratorTest) {
  SHOW(ft::is_forward_iterator<ft::_vector_iterator<int *>>::value);
}

// is_random_access_test
TEST(IS_RANDOM_ACCESS_TEST, IsRandomAccessTest) {
  SHOW(ft::is_random_access_iterator<ft::_vector_iterator<int *>>::value);

}