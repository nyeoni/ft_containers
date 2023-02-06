/*
 * File: type_traits_test.cpp
 * Project: ft_container
 * Created Date: 2023/02/07
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#include "type_traits.hpp"
#include "gtest/gtest.h"
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

TYPED_TEST(IsIntegralTest, is_integral_test) {
  typename TestFixture::value_type val = TestFixture::value;
  EXPECT_EQ(val, 1);
}

TEST(IS_ITEGRAL_TEST, bool_test) {
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

