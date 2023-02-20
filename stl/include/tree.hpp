/*
 * File: tree.hpp
 * Project: ft_container
 * Created Date: 2023/02/15
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef TREE_HPP_
#define TREE_HPP_

#include "iterator_traits.hpp"
#include <memory>

// 나중에 지워야 함
#include <map>

namespace ft {

/**
 * @brief rb_tree color constant
 */
enum _rb_tree_color {
  _s_red = false,
  _s_black = true
};

/**
 * @brief base class of node
 *
 * 부모, 자식(오른쪽, 왼쪽)에 대한 정보
 * 해당 노드를 중심으로 max, min 값 구하는 멤버함수들
 */
struct _rb_tree_node_base {
  typedef _rb_tree_node_base *_base_ptr;
  typedef const _rb_tree_node_base *_const_base_ptr;

  _rb_tree_color _m_color;
  _base_ptr _m_parent;
  _base_ptr _m_left;
  _base_ptr _m_right;

  static _base_ptr _s_minimum(_base_ptr x) {
    while (x->_m_left != 0) x = x->_m_left;
    return x;
  }
  static _const_base_ptr _s_minimum(_const_base_ptr x) {
    while (x->_m_left != 0) x = x->_m_left;
    return x;
  }
  static _base_ptr _s_maximum(_base_ptr x) {
    while (x->_m_right != 0) x = x->_m_right;
    return x;
  }
  static _const_base_ptr _s_maximum(_const_base_ptr x) {
    while (x->_m_right != 0) x = x->_m_right;
    return x;
  }
};

template<class Val>
struct _rb_tree_node : public _rb_tree_node_base {
  typedef _rb_tree_node<Val> *_link_type;

  Val _m_value_field;

  Val *_m_valptr() {
    return std::addressof(_m_value_field);
  }
  const Val *_m_valptr() const {
    return std::addressof(_m_value_field);
  }
};

struct _rb_tree_header {
  _rb_tree_node_base _m_header;
  size_t _m_node_count; // keeps track of size of tree

  _rb_tree_header() : _m_header(), _m_node_count() {
    _m_header._m_color = _s_red;
    _m_reset();
  }

  void _m_reset() {
    _m_header._m_parent = NULL;
    _m_header._m_left = &_m_header;
    _m_header._m_right = &_m_header;
    _m_node_count = 0;
  }
};

template<class T, class Alloc = std::allocator<T> >
class _rb_tree_impl {
 public:
  typedef Alloc allocator_type;

  _rb_tree_impl(const allocator_type &a) : _m_node_allocator(a) {}

  allocator_type get_allocator() const { return _m_node_allocator; }

 protected:
  allocator_type _m_node_allocator;

  _rb_tree_node_base _m_header;

  _rb_tree_node<T> *_m_get_node() { return _m_node_allocator.allocate(1); }

  // todo: _m_put_node 무슨 함수인지 분석해야함
  void _m_put_node(_rb_tree_node<T> *p) { _m_node_allocator.deallocate(p, 1); }
};

// ft rb_tree static function
_rb_tree_node_base *
_rb_tree_increment(_rb_tree_node_base *x) throw();

const _rb_tree_node_base *
_rb_tree_increment(const _rb_tree_node_base *x) throw();

_rb_tree_node_base *
_rb_tree_decrement(_rb_tree_node_base *x) throw();

const _rb_tree_node_base *
_rb_tree_decrement(const _rb_tree_node_base *x) throw();

template<typename T>
struct _rb_tree_iterator : public std::iterator<std::bidirectional_iterator_tag,
                                                typename iterator_traits<T>::value_type,
                                                typename iterator_traits<T>::difference_type,
                                                typename iterator_traits<T>::pointer,
                                                typename iterator_traits<T>::reference> {
  typedef _rb_tree_iterator<T> iterator;
  typedef typename iterator_traits<T>::difference_type difference_type;
  typedef typename iterator_traits<T>::reference reference;
  typedef typename iterator_traits<T>::pointer pointer;
  typedef typename iterator_traits<T>::value_type value_type;
  typedef std::bidirectional_iterator_tag iterator_category;

  typedef _rb_tree_iterator<T> _self;
  typedef _rb_tree_node_base::_base_ptr _base_ptr;
  typedef _rb_tree_node<T> *_link_type;

  _base_ptr _m_node;

  _rb_tree_iterator() : _m_node() {}
  _rb_tree_iterator(_base_ptr x) : _m_node(x) {}
  _rb_tree_iterator(const iterator &it) : _m_node(it._m_node) {}

  // const rb_iterator to non-const rb_iterator
  iterator _m_const_cast() const {
    return iterator(const_cast<typename iterator::_base_ptr>(_m_node));
  }

  pointer operator->() const {
    return static_cast<_link_type>(_m_node)->_m_valptr();
  } // node->var
  reference operator*() const {
    return *static_cast<_link_type>(_m_node)->_m_valptr();
  } // *node
  _self &operator++() {
    _m_node = _rb_tree_increment(_m_node);
    return *this;
  } // ++node
  _self operator++(int) {
    _self _tmp = *this;
    _m_node = _rb_tree_increment(_m_node);
    return _tmp;
  } // node++
  _self &operator--() {
    _m_node = _rb_tree_decrement(_m_node);
    return *this;
  } // --node
  _self operator--(int) {
    _self _tmp = *this;
    _m_node = _rb_tree_decrement(_m_node);
    return _tmp;
  } // node--

  friend bool operator==(const _self &x, const _self &y) {
    return x._m_node == y._m_node;
  }
  friend bool operator!=(const _self &x, const _self &y) {
    return x._m_node != y._m_node;
  }
};

template<class Key, class Val, class KeyOfValue, class Compare, class Alloc = std::allocator<Val> >
class _rb_tree {
  typedef typename Alloc::template rebind<_rb_tree_node<Val> >::other _node_allocator;
  typedef _rb_tree_impl<Val, Alloc> _base;

 protected:
  typedef _rb_tree_node_base *_base_ptr;
  typedef _rb_tree_node<Val> _rb_tree_node;

 public:
  typedef Key key_type;
  typedef Val value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef _rb_tree_node *link_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename _base::allocator_type allocator_type;
  allocator_type get_allocator() const { return _base::get_allocator(); }
};

} // namespace ft

#endif //TREE_HPP_
