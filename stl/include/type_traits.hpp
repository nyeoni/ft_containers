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

/**
 * @brief Identify whether T has iterator_category or not
 * @tparam T type
 */
template<typename T>
struct has_iterator_category {
 private:
  typedef char yes;
  typedef long no;

  /**
   * @tparam U 들어오는 타입에 대한 추론을 하는 역할 (U *)
   * @return yes (char)
   */
  template<typename U, typename = typename enable_if<!is_integral<U>::value>::type>
  static yes test(const U, typename U::iterator_category * = 0);

  template<typename U>
  static yes test(const U *, typename iterator_traits<U *>::iterator_category * = 0);

  static no test(...);
 public:
  enum { value = sizeof(test(T())) == sizeof(yes) };
};

/**
 * @brief Traits class that identifies whether T is iterator or not
 * @tparam T type
 */
template<typename T, bool = has_iterator_category<T>::value>
struct is_iterator : public false_type {};

template<typename T>
struct is_iterator<T, true> : public true_type {};

template<typename T>
struct is_input_iterator :
    public integral_constant<bool, is_iterator<T>::value
        && (is_same<typename T::iterator_category, std::random_access_iterator_tag>::value)
        || is_same<typename T::iterator_category, std::bidirectional_iterator_tag>::value
        || is_same<typename T::iterator_category, std::forward_iterator_tag>::value
        || is_same<typename T::iterator_category, std::input_iterator_tag>::value> {
};

template<typename T>
struct is_output_iterator :
    public integral_constant<bool, is_iterator<T>::value
    &&(is_same<typename T::iterator_category, std::output_iterator_tag>::value)> {
};

template<typename T>
struct is_forward_iterator :
    public integral_constant<bool, is_iterator<T>::value
        && (is_same<typename T::iterator_category, std::random_access_iterator_tag>::value)
        || is_same<typename T::iterator_category, std::bidirectional_iterator_tag>::value
        || is_same<typename T::iterator_category, std::forward_iterator_tag>::value> {
};

template<typename T>
struct is_bidirectional_iterator :
    public integral_constant<bool, is_iterator<T>::value
        && (is_same<typename T::iterator_category, std::random_access_iterator_tag>::value)
        || is_same<typename T::iterator_category, std::bidirectional_iterator_tag>::value> {
};

template<typename T>
struct is_random_access_iterator :
    public integral_constant<bool, is_iterator<T>::value
    &&(is_same<typename T::iterator_category, std::random_access_iterator_tag>::value)> {
};

// Template Specialization (for pointer)

template<typename T>
struct is_input_iterator<T *> :
    public integral_constant<bool, is_iterator<T *>::value
        && (is_same<typename iterator_traits<T *>::iterator_category, std::random_access_iterator_tag>::value)
        || is_same<typename iterator_traits<T *>::iterator_category, std::bidirectional_iterator_tag>::value
        || is_same<typename iterator_traits<T *>::iterator_category, std::forward_iterator_tag>::value
        || is_same<typename iterator_traits<T *>::iterator_category, std::input_iterator_tag>::value> {
};

template<typename T>
struct is_output_iterator<T *> :
    public integral_constant<bool, is_iterator<T *>::value
    &&(is_same<typename iterator_traits<T *>::iterator_category, std::output_iterator_tag>::value)> {
};

template<typename T>
struct is_forward_iterator<T *> :
    public integral_constant<bool, is_iterator<T *>::value
        && (is_same<typename iterator_traits<T *>::iterator_category, std::random_access_iterator_tag>::value)
        || is_same<typename iterator_traits<T *>::iterator_category, std::bidirectional_iterator_tag>::value
        || is_same<typename iterator_traits<T *>::iterator_category, std::forward_iterator_tag>::value> {
};

template<typename T>
struct is_bidirectional_iterator<T *> :
    public integral_constant<bool, is_iterator<T *>::value
        && (is_same<typename iterator_traits<T *>::iterator_category, std::random_access_iterator_tag>::value)
        || is_same<typename iterator_traits<T *>::iterator_category, std::bidirectional_iterator_tag>::value> {
};

template<typename T>
struct is_random_access_iterator<T *> :
    public integral_constant<bool, is_iterator<T *>::value
    &&(is_same<typename iterator_traits<T *>::iterator_category, std::random_access_iterator_tag>::value)> {
};
}

#endif //TYPE_TRAITS_HPP_
