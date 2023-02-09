/*
 * File: algorithm.hpp
 * Project: ft_container
 * Created Date: 2023/02/05
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef ALGORITHM_HPP_
#define ALGORITHM_HPP_

namespace ft {
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

/**
 * @brief Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
 * @tparam InputIterator1
 * @tparam InputIterator2
 * @param first1
 * @param last1
 * @param first2
 * @param last2
 * @return true if the first range compares lexicographically less than the second. false otherwise (including when all the elements of both ranges are equivalent).
 *
 * 범위가 사전순으로 범위보다 작은 경우 true 를 반환.
 */
template<class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
  while (first1 != last1) {
    if (first2 == last2 || *first2 < *first1) return false;
    else if (*first1 < *first2) return true;
    ++first1;
    ++first2;
  }
  return (first2 != last2);
}

/**
 * @brief Exchanges the values of a and b.
 * @tparam T
 * @param a
 * @param b
 */
template<class T>
void swap(T &a, T &b) {
  T c(a);
  a = b;
  b = c;
}

/**
 * @brief Copies the elements in the range [first,last) into the range beginning at result.
 * @tparam InputIterator
 * @tparam OutputIterator
 * @param first
 * @param last
 * @param result
 * @return
 */
template<class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
  while (first != last) {
    *result = *first;
    ++result;
    ++first;
  }
  return result;
}

}

#endif //ALGORITHM_HPP_
