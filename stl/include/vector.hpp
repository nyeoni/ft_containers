/*
 * File: vector.hpp
 * Project: ft_container
 * Created Date: 2023/01/31
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <memory>
#include <iterator>
#include "type_traits.hpp"
#include "iterator_traits.hpp"

// 나중에 지우기
#include <vector>

namespace ft {

/**
 * @class _vector_iterator
 * @namespace ft
 * @brief random_aft::vector_iterator for ft::vector
 * @tparam T value_type
 * @note Iter 는 포인터 처럼 사용할 수 있음 (Iter == T *) 그래서 iterator_traits<T *> 로 들어갈 예정임
 */
template<class Iter>
class _vector_iterator : public std::iterator<std::random_access_iterator_tag,
                                              typename iterator_traits<Iter>::value_type,
                                              typename iterator_traits<Iter>::difference_type,
                                              typename iterator_traits<Iter>::pointer,
                                              typename iterator_traits<Iter>::reference> {
 private:
  Iter _it;
 public:
  typedef Iter iterator_type;
  typedef typename iterator_traits<Iter>::difference_type difference_type;
  typedef typename iterator_traits<Iter>::reference reference;
  typedef typename iterator_traits<Iter>::pointer pointer;
  typedef typename iterator_traits<Iter>::iterator_category iterator_category;
  typedef typename iterator_traits<Iter>::value_type value_type;

  // constructor
  _vector_iterator() : _it() {}
  explicit _vector_iterator(const Iter &it) : _it(it) {}
  template<typename U>
  explicit _vector_iterator(const _vector_iterator<U> &u) : _it(u.base()) {}

  // member functions
  iterator_type base() const { return _it; }
  reference operator*() const {
    Iter tmp = _it;
    return *--tmp;
  } // *rit
  _vector_iterator operator+(difference_type n) const {
    return _vector_iterator(_it - n);
  } // rit + n
  _vector_iterator &operator++() {
    --_it;
    return *this;
  } // ++rit
  _vector_iterator operator++(int) {
    _vector_iterator tmp(*this);
    --_it;
    return tmp;
  } // rit++
  _vector_iterator &operator--() {
    ++_it;
    return *this;
  } // --rit
  _vector_iterator operator--(int) {
    _vector_iterator tmp(*this);
    ++_it;
    return tmp;
  } // rit--
  _vector_iterator &operator+=(difference_type n) {
    _it -= n;
    return *this;
  }
  _vector_iterator operator-(difference_type n) const {
    return _vector_iterator(_it + n);
  } // rit - n
  _vector_iterator &operator-=(difference_type n) {
    _it += n;
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
bool operator==(const _vector_iterator<Iter> &lhs, const _vector_iterator<Iter> &rhs) {
  return lhs.base() == rhs.base();
}
template<class Iter>
bool operator!=(const _vector_iterator<Iter> &lhs, const _vector_iterator<Iter> &rhs) {
  return lhs.base() != rhs.base();
}
template<class Iter>
bool operator<(const _vector_iterator<Iter> &lhs, const _vector_iterator<Iter> &rhs) {
  return lhs.base() > rhs.base();
}
template<class Iter>
bool operator<=(const _vector_iterator<Iter> &lhs, const _vector_iterator<Iter> &rhs) {
  return lhs.base() <= rhs.base();
}
template<class Iter>
bool operator>(const _vector_iterator<Iter> &lhs, const _vector_iterator<Iter> &rhs) {
  return lhs.base() > rhs.base();
}
template<class Iter>
bool operator>=(const _vector_iterator<Iter> &lhs, const _vector_iterator<Iter> &rhs) {
  return lhs.base() >= rhs.base();
}

// operator+ (_vector_iterator)
template<class Iter>
_vector_iterator<Iter> operator+(typename _vector_iterator<Iter>::difference_type n,
                                 const _vector_iterator<Iter> &rev_it) {
  return _vector_iterator<Iter>(rev_it.base() - n);
} // n + rit

// operator- (_vector_iterator)
template<class Iter>
_vector_iterator<Iter> operator-(typename _vector_iterator<Iter>::difference_type n,
                                 const _vector_iterator<Iter> &rev_it) {
  return _vector_iterator<Iter>(rev_it.base + n);
}
};

/**
 * @class _vector_base
 * @namespace ft
 * @brief vector_base manage vector memory (RAII pattern)
 * @tparam T
 * @tparam Allocator
 */
template<
    class T,
    class Allocator = std::allocator<T>
>
class _vector_base {

};

/**
 * @class vector
 * @namespace ft
 * @brief Sequence containers representing arrays that can change in size
 * @note allocator 뒤에 스페이스 안붙여서 컴파일 에러 날 수 있음. >> 연속으로 오면 안됨 > > 이렇게 되어야 함
 */
template<
    class T,
    class Allocator = std::allocator<T>
>
 class vector : protected ft::_vector_base<T, Allocator> {
 public:
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef ft::_vector_iterator<pointer> iterator;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

};

}

#endif //VECTOR_HPP_
