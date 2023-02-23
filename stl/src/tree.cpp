/*
 * File: tree.cpp
 * Project: ft_container
 * Created Date: 2023/02/23
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#include "tree.hpp"

namespace ft {

static _rb_tree_node_base *local_rb_tree_increment(_rb_tree_node_base *x) throw() {
  if (x->_m_right != 0) {
    x = x->_m_right;
    while (x->_m_left != 0)
      x = x->_m_left;
  } else {
    _rb_tree_node_base *_y = x->_m_parent;
    while (x == _y->_m_right) {
      x = _y;
      _y = _y->_m_parent;
    }
    if (x->_m_right != _y)
      x = _y;
  }
  return x;
}

_rb_tree_node_base *_rb_tree_increment(_rb_tree_node_base *x) throw() {
  return local_rb_tree_increment(x);
}
const _rb_tree_node_base *_rb_tree_increment(const _rb_tree_node_base *x) throw() {
  return local_rb_tree_increment(const_cast<_rb_tree_node_base *>(x));
}

static _rb_tree_node_base *local_rb_tree_decrement(_rb_tree_node_base *x) throw() {
  if (x->_m_color == _s_red && x->_m_parent->_m_parent == x) { // header 일 경우 - header 의 -- 는 rightmost
    x = x->_m_right;
  } else if (x->_m_left != 0) {
    x = x->_m_left;
    while (x->_m_right != 0)
      x = x->_m_right;
  } else {
    _rb_tree_node_base *_y = x->_m_parent;
    while (x == _y->_m_left) {
      x = _y;
      _y = _y->_m_parent;
    }
    x = _y;
  }
  return x;
}

_rb_tree_node_base *_rb_tree_decrement(_rb_tree_node_base *x) throw() {
  return local_rb_tree_decrement(x);
}
const _rb_tree_node_base *_rb_tree_decrement(const _rb_tree_node_base *x) throw() {
  return local_rb_tree_decrement(const_cast<_rb_tree_node_base *>(x));
}

}
