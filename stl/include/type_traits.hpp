/*
 * File: type_traits.hpp
 * Project: ft_container
 * Created Date: 2023/02/02
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef TYPE_TRAITS_HPP_
#define TYPE_TRAITS_HPP_

#include "iterator_traits.hpp"

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
 * @brief Traits class that identifies whether T is the same type as U
 * @tparam T type1
 * @tparam U type2
 */
template<typename T, typename U>
struct is_same : false_type {};

template<typename T>
struct is_same<T, T> : true_type {};

template<typename T>
struct is_iterator {
 private:
  typedef char yes;
  typedef long no;

  /**
   * @tparam U 들어오는 타입에 대한 추론을 하는 역할 (U *)
   * @return yes (char)
   */
  template<typename U>
  static yes test(U *, typename U::iterator_category * = 0);

  static no test(...);
 public:
  enum { value = sizeof(test(static_cast<T *>(0))) == sizeof(yes) };
};

//typedef iterator_constant<bool, true> true_type;
//typedef iterator_constant<bool, false> false_type;

//template<class T>
//struct is_iterator : public false_type {};
//
//template<>
//struct is_iterator< : public true_type {};
}

#endif //TYPE_TRAITS_HPP_
