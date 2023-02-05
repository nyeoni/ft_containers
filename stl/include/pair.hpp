/*
 * File: pair.hpp
 * Project: ft_container
 * Created Date: 2023/02/05
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef PAIR_HPP_
#define PAIR_HPP_

namespace ft {
/**
 * @brief This class couples together a pair of values, which may be of different types (T1 and T2). The individual values can be accessed through its public members first and second.
 * @tparam T1 first element
 * @tparam T2 second element
 */
template<class T1, class T2>
struct pair {
  typedef T1 first_type;
  typedef T2 second_type;

  first_type first;
  second_type second;

  pair() : first(), second() {}
  template<class U, class V>
  explicit pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}
  pair(const first_type &a, const second_type &b) : first(a), second(b) {}

  pair &operator=(const pair &pr) {
    first = pr.first;
    second = pr.second;
    return *this;
  }
};

template<class T1, class T2>
bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<class T1, class T2>
bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs == rhs); }

template<class T1, class T2>
bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template<class T1, class T2>
bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(rhs < lhs); }

template<class T1, class T2>
bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return rhs < lhs; }

template<class T1, class T2>
bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs < rhs); }

/**
 * Constructs a pair object with its first element set to x and its second element set to y.
 * @tparam T1
 * @tparam T2
 * @param x
 * @param y
 * @return A pair object whose elements first and second are set to x and y respectivelly. The template parameters can be implicitly deduced.
 */
template<class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y) {
  return (pair<T1, T2>(x, y));
}
}

#endif //PAIR_HPP_
