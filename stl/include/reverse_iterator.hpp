/*
 * File: reverse_iterator.hpp
 * Project: ft_containers
 * Created Date: 2023/01/28
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef REVERSE_ITERATOR_HPP_
#define REVERSE_ITERATOR_HPP_

#include <iterator>
#include "iterator_traits.hpp"

namespace ft {

/**
 * @class reverse_iterator
 * @namespace ft
 * @brief reverse_iterator
 * @tparam Iter iterator
 */
template<class Iter>
class reverse_iterator : public std::iterator<typename iterator_traits<Iter>::iterator_category,
                                              typename iterator_traits<Iter>::value_type,
                                              typename iterator_traits<Iter>::difference_type,
                                              typename iterator_traits<Iter>::pointer,
                                              typename iterator_traits<Iter>::reference> {
 protected:
  Iter current;
 public:
  // typedef
  typedef Iter iterator_type;
  typedef typename iterator_traits<Iter>::difference_type difference_type;
  typedef typename iterator_traits<Iter>::reference reference;
  typedef typename iterator_traits<Iter>::pointer pointer;
  typedef typename iterator_traits<Iter>::iterator_category iterator_category;
  typedef typename iterator_traits<Iter>::value_type value_type;

  /**
   * default constructor
   */
  reverse_iterator() : current() {}
  /**
   * initialization constructor
   * @param it iterator
   */
  explicit reverse_iterator(Iter it) : current(it) {}
  /**
   * copy constructor
   * @tparam U Iterator
   * @param u reverse_iterator
   */
  template<typename U>
  explicit reverse_iterator(const reverse_iterator<U> &u) : current(u.base()) {} // copy

  // member functions
  iterator_type base() const { return current; }
  reference operator*() const {
    Iter tmp = current;
    return *--tmp;
  } // *rit
  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(current - n);
  } // rit + n
  reverse_iterator &operator++() {
    --current;
    return *this;
  } // ++rit
  reverse_iterator operator++(int) {
    reverse_iterator tmp(*this);
    --current;
    return tmp;
  } // rit++
  reverse_iterator &operator--() {
    ++current;
    return *this;
  } // --rit
  reverse_iterator operator--(int) {
    reverse_iterator tmp(*this);
    ++current;
    return tmp;
  } // rit--
  reverse_iterator &operator+=(difference_type n) {
    current -= n;
    return *this;
  }
  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(current + n);
  } // rit - n
  reverse_iterator &operator-=(difference_type n) {
    current += n;
    return *this;
  }
  pointer operator->() const {
    return std::addressof(operator*());
  } // rit->member_var
  reference operator[](difference_type n) const {
    return *(*this + n);
  } // rit[n]
};

// non-member function
// relational operators
template<class Iter>
bool operator==(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs) {
  return lhs.base() == rhs.base();
}
template<class Iter>
bool operator!=(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs) {
  return lhs.base() != rhs.base();
}
template<class Iter>
bool operator<(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs) {
  return lhs.base() > rhs.base();
}
template<class Iter>
bool operator<=(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs) {
  return lhs.base() <= rhs.base();
}
template<class Iter>
bool operator>(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs) {
  return lhs.base() > rhs.base();
}
template<class Iter>
bool operator>=(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs) {
  return lhs.base() >= rhs.base();
}

// operator+ (reverse_iterator)
template<class Iter>
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
                                 const reverse_iterator<Iter> &rev_it) {
  return reverse_iterator<Iter>(rev_it.base() - n);
} // n + rit

// operator- (reverse_iterator)
template<class Iter>
reverse_iterator<Iter> operator-(typename reverse_iterator<Iter>::difference_type n,
                                 const reverse_iterator<Iter> &rev_it) {
  return reverse_iterator<Iter>(rev_it.base + n);
}

} // namespace ft

#endif //REVERSE_ITERATOR_HPP_
