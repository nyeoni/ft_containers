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

void _rb_tree_rotate_left(_rb_tree_node_base *x, _rb_tree_node_base *&root) {
  _rb_tree_node_base *_y = x->_m_right;
  x->_m_right = _y->_m_left;
  if (_y->_m_left != 0)
    _y->_m_left->_m_parent = x;
  _y->_m_parent = x->_m_parent;

  if (x == root)
    root = _y;
  else if (x == x->_m_parent->_m_left)
    x->_m_parent->_m_left = _y;
  else
    x->_m_parent->_m_right = _y;
  _y->_m_left = x;
  x->_m_parent = _y;
}

void _rb_tree_rotate_right(_rb_tree_node_base *x, _rb_tree_node_base *&root) {
  _rb_tree_node_base *_y = x->_m_left;
  x->_m_left = _y->_m_right;
  if (_y->_m_right != 0)
    _y->_m_right->_m_parent = x;
  _y->_m_parent = x->_m_parent;

  if (x == root)
    root = _y;
  else if (x == x->_m_parent->_m_right)
    x->_m_parent->_m_right = _y;
  else
    x->_m_parent->_m_left = _y;
  _y->_m_right = x;
  x->_m_parent = _y;
}

/**
 * @brief Reblance rb_tree
 * @param x new_node
 * @param root root_node
 */
void _rb_tree_rebalance(_rb_tree_node_base *x, _rb_tree_node_base *&root) {
  x->_m_color = _s_red;
  while (x != root && x->_m_parent->_m_color == _s_red) {
    if (x->_m_parent == x->_m_parent->_m_parent->_m_left) {
      // 부모 노드가 조상 노드의 왼쪽에 있는 경우
      _rb_tree_node_base *_y = x->_m_parent->_m_parent->_m_right;
      // 삼촌 노드 색 확인
      if (_y && _y->_m_color == _s_red) {
        // 삼촌 노드 색(빨강) -> Recoloring # case 1
        x->_m_parent->_m_color = _s_black;
        _y->_m_color = _s_black;
        x->_m_parent->_m_parent->_m_color = _s_red;
        x = x->_m_parent->_m_parent; // case 1 일때는 재귀적으로 할아버지 노드를 기준으로 확인해주어야 함
      } else {
        // 삼촌 노드 색(검정) -> Restructuring # case 2 or 3
        if (x == x->_m_parent->_m_right) {
          // # case 2
          x = x->_m_parent;
          _rb_tree_rotate_left(x, root);
        }
        // # case 3
        x->_m_parent->_m_color = _s_black;
        x->_m_parent->_m_parent->_m_color = _s_red;
        _rb_tree_rotate_right(x->_m_parent->_m_parent, root);
      }
    } else {
      // 부모 노드가 조상 노드의 오른쪽에 있는 경우
      _rb_tree_node_base *_y = x->_m_parent->_m_parent->_m_left;
      if (_y && _y->_m_color == _s_red) {
        x->_m_parent->_m_color = _s_black;
        _y->_m_color = _s_black;
        x->_m_parent->_m_parent->_m_color = _s_red;
        x = x->_m_parent->_m_parent;
      } else {
        if (x == x->_m_parent->_m_left) {
          x = x->_m_parent;
          _rb_tree_rotate_right(x, root);
        }
        x->_m_parent->_m_color = _s_black;
        x->_m_parent->_m_parent->_m_color = _s_red;
        _rb_tree_rotate_left(x->_m_parent->_m_parent, root);
      }
    }
  }
  root->_m_color = _s_black;
}

_rb_tree_node_base *_rb_tree_rebalance_for_erase(_rb_tree_node_base *z,
                                                 _rb_tree_node_base *&root,
                                                 _rb_tree_node_base *&leftmost,
                                                 _rb_tree_node_base *&rightmost) {
  _rb_tree_node_base *_y = z;
  _rb_tree_node_base *_x = 0;
  _rb_tree_node_base *_x_parent = 0;
  if (_y->_m_left == 0)
    _x = _y->_m_right;
  else if (_y->_m_right == 0)
    _x = _y->_m_left;
  else {
    _y = _y->_m_right;
    while (_y->_m_left != 0)
      _y = _y->_m_left;
    _x = _y->_m_right;
  }
  if (_y != z) {
    z->_m_left->_m_parent = _y;
    _y->_m_left = z->_m_left;
    if (_y != z->_m_right) {
      _x_parent = _y->_m_parent;
      if (_x) _x->_m_parent = _y->_m_parent;
      _y->_m_parent->_m_left = _x;
      _y->_m_right = z->_m_right;
      z->_m_right->_m_parent = _y;
    } else
      _x_parent = _y;
    if (root == z)
      root = _y;
    else if (z->_m_parent->_m_left == z)
      z->_m_parent->_m_left = _y;
    else
      z->_m_parent->_m_right = _y;
    _y->_m_parent = z->_m_parent;
    ft::swap(_y->_m_color, z->_m_color);
    _y = z;
  } else {
    _x_parent = _y->_m_parent;
    if (_x)
      _x->_m_parent = _y->_m_parent;
    if (root == z)
      root = _x;
    else if (z->_m_parent->_m_left == z)
      z->_m_parent->_m_left = _x;
    else
      z->_m_parent->_m_right = _x;
    if (leftmost == z) {
      if (z->_m_right == 0)
        leftmost = z->_m_parent;
      else
        leftmost = _rb_tree_node_base::_s_minimum(_x);
    }
    if (rightmost == z) {
      if (z->_m_left == 0)
        rightmost = z->_m_parent;
      else
        rightmost = _rb_tree_node_base::_s_maximum(_x);
    }
  }
  if (_y->_m_color != _s_red) {
    while (_x != root && (_x == 0 || _x->_m_color == _s_black))
      if (_x == _x_parent->_m_left) {
        _rb_tree_node_base *_w = _x_parent->_m_right;
        if (_w->_m_color == _s_red) {
          _w->_m_color = _s_black;
          _x_parent->_m_color = _s_red;
          _rb_tree_rotate_left(_x_parent, root);
          _w = _x_parent->_m_right;
        }
        if ((_w->_m_left == 0 ||
            _w->_m_left->_m_color == _s_black) &&
            (_w->_m_right == 0 ||
                _w->_m_right->_m_color == _s_black)) {
          _w->_m_color = _s_red;
          _x = _x_parent;
          _x_parent = _x_parent->_m_parent;
        } else {
          if (_w->_m_right == 0
              || _w->_m_right->_m_color == _s_black) {
            _w->_m_left->_m_color = _s_black;
            _w->_m_color = _s_red;
            _rb_tree_rotate_right(_w, root);
            _w = _x_parent->_m_right;
          }
          _w->_m_color = _x_parent->_m_color;
          _x_parent->_m_color = _s_black;
          if (_w->_m_right)
            _w->_m_right->_m_color = _s_black;
          _rb_tree_rotate_left(_x_parent, root);
          break;
        }
      } else {
        _rb_tree_node_base *_w = _x_parent->_m_left;
        if (_w->_m_color == _s_red) {
          _w->_m_color = _s_black;
          _x_parent->_m_color = _s_red;
          _rb_tree_rotate_right(_x_parent, root);
          _w = _x_parent->_m_left;
        }
        if ((_w->_m_right == 0 ||
            _w->_m_right->_m_color == _s_black) &&
            (_w->_m_left == 0 ||
                _w->_m_left->_m_color == _s_black)) {
          _w->_m_color = _s_red;
          _x = _x_parent;
          _x_parent = _x_parent->_m_parent;
        } else {
          if (_w->_m_left == 0 || _w->_m_left->_m_color == _s_black) {
            _w->_m_right->_m_color = _s_black;
            _w->_m_color = _s_red;
            _rb_tree_rotate_left(_w, root);
            _w = _x_parent->_m_left;
          }
          _w->_m_color = _x_parent->_m_color;
          _x_parent->_m_color = _s_black;
          if (_w->_m_left)
            _w->_m_left->_m_color = _s_black;
          _rb_tree_rotate_right(_x_parent, root);
          break;
        }
      }
    if (_x) _x->_m_color = _s_black;
  }
  return _y;
}

} // namespace ft