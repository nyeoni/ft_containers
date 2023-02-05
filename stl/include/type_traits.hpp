/*
 * File: type_traits.hpp
 * Project: ft_container
 * Created Date: 2023/02/02
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef TYPE_TRAITS_HPP_
#define TYPE_TRAITS_HPP_

namespace ft {

/**
 * @brief The type T is enabled as member type enable_if::type if Cond is true. Otherwise, enable_if::type is not defined.
 * @tparam T type
 *
 * This is useful to hide signatures on compile time when a particular condition is not met, since in this case, the member enable_if::type will not be defined and attempting to compile using it should fail.

 */
template<bool, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

template<class T, T v>
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T, v> type;
  operator T() const { return v; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

/**
 * @brief Trait class that identifies whether T is an integral type
 * @tparam T type
 */
template<class T>
struct is_integral : public false_type {};

template<>
struct is_integral<bool> : public true_type {};

template<>
struct is_integral<char> : public true_type {};

template<>
struct is_integral<char16_t> : public true_type {};

template<>
struct is_integral<char32_t> : public true_type {};

template<>
struct is_integral<signed char> : public true_type {};

template<>
struct is_integral<unsigned char> : public true_type {};

template<>
struct is_integral<wchar_t> : public true_type {};

template<>
struct is_integral<short> : public true_type {};

template<>
struct is_integral<unsigned short> : public true_type {};

template<>
struct is_integral<int> : public true_type {};

template<>
struct is_integral<unsigned int> : public true_type {};

template<>
struct is_integral<long> : public true_type {};

template<>
struct is_integral<unsigned long> : public true_type {};

template<>
struct is_integral<long long> : public true_type {};

template<>
struct is_integral<unsigned long long> : public true_type {};

/**
 * @brief Compares the elements in the range [first1,last1) with those in the range beginning at first2, and returns true if all of the elements in both ranges match.
 * @tparam InputIterator1
 * @tparam InputIterator2
 * @param first1
 * @param last1
 * @param first2
 * @return true if all the elements in the range [first1,last1) compare equal to those of the range starting at first2, and false otherwise.
 */
template<class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
  while (first1 != last1) {
    if (*first1 != *first2)
      return false;
    ++first1;
    ++first2;
  }
  return true;
}
}

#endif //TYPE_TRAITS_HPP_
