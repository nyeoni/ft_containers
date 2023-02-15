/*
 * File: stack.hpp
 * Project: ft_container
 * Created Date: 2023/02/15
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef STACK_HPP_
#define STACK_HPP_

#include "vector.hpp"

namespace ft {
/**
 * @brief LIFO stack
 * @tparam T type
 * @tparam Container type of the internal underlying container object
 */
template<class T, class Container = vector<T> >
class stack {
 public:
  typedef typename Container::value_type value_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;
  typedef typename Container::size_type size_type;
  typedef Container container_type;

 protected:
  Container _c;

 public:
  /**
   * @brief Default constructor creates no elements
   * @param c container
   */
  explicit stack(const Container &c = container_type()) : _c(c) {}

  /**
   * @brief Returns true if the %stack is empty
   */
  bool empty() const {
    return _c.empty();
  };

  /**
   * @brief Returns the number of elements in the %stack
   */
  size_type size() const {
    return _c.size();
  }

  /**
   * @brief Returns a read/write reference to the data at the first element of the %stack
   */
  value_type &top() {
    return _c.back();
  }

  /**
   * @brief Returns a read-only (constant) reference to the data at the first element of the %stack
   */
  const value_type &top() const {
    return _c.back();
  }

  /**
   * @brief Add data to the top of the %stack
   * @param val data to be added
   */
  void push(const value_type &val) {
    _c.push_back(val);
  }

  /**
   * @brief Removes first elements
   *
   * stack 이니까 기본 컨테이너 벡터의 pop_back 을 하게 되면 스택의 마지막으로 들어온 요소(= 첫번째 요소) 가 제거된다.
   */
  void pop() {
    _c.pop_back();
  }
};
} // namespace ft

#endif //STACK_HPP_
