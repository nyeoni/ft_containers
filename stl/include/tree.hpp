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
#include "reverse_iterator.hpp"
#include "function.hpp"
#include "pair.hpp"
#include <memory>

// 나중에 지워야 함
#include <map>
#include <iostream>

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
 * todo : 맨 처음에 값 어떻게 초기화 되는 확인해볼 것
 */
struct _rb_tree_node_base {
  typedef _rb_tree_node_base *_base_ptr;
  typedef const _rb_tree_node_base *_const_base_ptr;

  bool _m_color;
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

// Helper type offering value initialization guarantee on the compare functor
template<typename Key_Compare>
struct _rb_tree_key_compare {
  Key_Compare _m_key_compare;

  _rb_tree_key_compare() : _m_key_compare() {}
  _rb_tree_key_compare(const Key_Compare &comp) : _m_key_compare(comp) {}
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

// Helper type to manage default initialization of node count and header.
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
struct _rb_tree_iterator {
  typedef _rb_tree_iterator<T> iterator;
  typedef ptrdiff_t difference_type;
  typedef T &reference;
  typedef T *pointer;
  typedef T value_type;
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

/**
 * @brief Red-Black tree
 * @tparam Key key
 * @tparam Val pair<key, value>
 * @tparam KeyOfValue template class that select key of value (functor)
 * @tparam Compare key_compare type (functor class)
 * @tparam Alloc allocator type
 */
template<class Key, class Val, class KeyOfValue = ft::Select1st<Val>,
    class Compare = ft::less<Key>, class Alloc = std::allocator<Val> >
class _rb_tree {
  typedef typename Alloc::template rebind<_rb_tree_node<Val> >::other _node_allocator;

 protected:
  typedef _rb_tree_node_base *_base_ptr;
  typedef const _rb_tree_node_base *_const_base_ptr;
  typedef _rb_tree_node<Val> *_link_type;
  typedef const _rb_tree_node<Val> *_const_link_type;

 public:
  // member types
  typedef Key key_type;
  typedef Val value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef Alloc allocator_type;

  /* ****************************************************** */
  /*                       Memory                           */
  /* ****************************************************** */

  // allocate 관련한 함수들 모음
  // 트리 자료구조의 node 할당 및 트리 할당 및 해제 관련한 로직들 놓기
  allocator_type get_allocator() const {
    return allocator_type(_m_get_node_allocator());
  }

 protected:
  _node_allocator &_m_get_node_allocator() { return this->_m_impl; };
  const _node_allocator &_m_get_node_allocator() const { return this->_m_impl; };

  _link_type _m_alloc_node() { return _m_get_node_allocator().allocate(1); }

  void _m_dealloc_node(_link_type p) { _m_get_node_allocator().deallocate(p, 1); }

  void _m_construct_node(_link_type node, const value_type &x) {
    try {
      get_allocator().construct(node->_m_valptr(), x);
    } catch (std::exception &e) {
      _m_dealloc_node(node);
      throw e;
    }
  }

  void _m_destroy_node(_link_type p) { get_allocator().destroy(p->_m_valptr()); }

  _link_type _m_create_node(const value_type &x) {
    _link_type _tmp = _m_alloc_node();
    _m_construct_node(_tmp, x);
    return _tmp;
  }

  void _m_drop_node(_link_type p) {
    _m_destroy_node(p);
    _m_dealloc_node(p);
  }

  _link_type _m_clone_node(_link_type x) {
    _link_type _tmp = _m_create_node(x);
    _tmp->_m_color = x->_m_color;
    _tmp->_m_left = x->_m_left;
    _tmp->_m_right = x->_m_right;
    return _tmp;
  }

  // 실질적인 레드블랙트리의 header 및 메모리 관련한 모든 로직들은 이 클래스를 기반으로 구현될 것임
  template<typename Key_Compare>
  class _rb_tree_impl :
      public _node_allocator,
      public _rb_tree_key_compare<Key_Compare>,
      public _rb_tree_header {
   public:
    typedef _node_allocator _base_node_allocator;
    typedef _rb_tree_key_compare<Key_Compare> _base_key_compare;

    _rb_tree_impl() : _node_allocator(), _base_key_compare(), _rb_tree_header() {}
    // 이거 x 만 받아도 다형성에 의해서 작동되는지 확인해보기
    _rb_tree_impl(const _rb_tree_impl &x)
        : _node_allocator(x), _base_key_compare(x._m_key_compare), _rb_tree_header() {}
    _rb_tree_impl(const Key_Compare &comp, const _node_allocator &alloc)
        : _node_allocator(alloc), _base_key_compare(comp) {}
  };

  // member variables
  _rb_tree_impl<Compare> _m_impl;

 public:
  // test code TODO : delete
  void printBT(const std::string &prefix, _link_type node, bool isLeft) {
    if (node != nullptr) {
      std::cout << prefix;

      std::cout << (isLeft ? "├──" : "└──");

      // print the value of the node
      std::cout << KeyOfValue()(node->_m_value_field) << std::endl;

      // enter the next tree level - left and right branch
      printBT(prefix + (isLeft ? "│   " : "    "), (_link_type) node->_m_left, true);
      printBT(prefix + (isLeft ? "│   " : "    "), (_link_type) node->_m_right, false);
    }
  }

  void printBT() {
    printBT("", (_link_type) _m_impl._m_header._m_parent, false);
  }

 protected:
  // 여기서는 _rb_node_base pointer 를 리턴해줌
  _base_ptr &_m_root() { return this->_m_impl._m_header._m_parent; }
  _const_base_ptr &_m_root() const { return this->_m_impl._m_header._m_parent; }

  _base_ptr &_m_leftmost() { return this->_m_impl._m_header._m_left; }
  _const_base_ptr &_m_leftmost() const { return this->_m_impl._m_header._m_left; }

  _base_ptr &_m_rightmost() { return this->_m_impl._m_header._m_right; }
  _const_base_ptr &_m_rightmost() const { return this->_m_impl._m_header._m_right; }

  // 여기는 _rb_node<Val> 를 리턴해줌
  // 여기 필요하면 쓰고 아니면 버리기
  _link_type _m_begin() { return static_cast<_link_type>(this->_m_impl._m_header._m_parent); }
  _const_link_type _m_begin() const { return static_cast<_link_type>(this->_m_impl._m_header._m_parent); }

  _base_ptr _m_end() { return &(this->_m_impl._m_header); }
  _const_base_ptr _m_end() const { return &(this->_m_impl._m_header); }

  static _link_type &_s_left(_base_ptr x) { return (_link_type &) (x->_m_left); }
  static _const_link_type &_s_left(_const_base_ptr x) { return (_const_link_type &) (x->_m_left); }

  static _link_type &_s_right(_base_ptr x) { return (_link_type &) (x->_m_right); }
  static _const_link_type &_s_right(_const_base_ptr x) { return (_const_link_type &) (x->_m_right); }

  static _link_type &_s_parent(_link_type x) { return (_link_type &) (x->_m_parent); }
  static _const_link_type &_s_parent(_const_link_type x) { return (_const_link_type &) (x->_m_parent); }

  static Key &_s_key(_base_ptr x) { return KeyOfValue()(x->_m_parent); }

 public:
  typedef _rb_tree_iterator<value_type> iterator;
  typedef _rb_tree_iterator<const value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  _rb_tree() {}
  _rb_tree(const Compare &comp, const allocator_type &alloc = _node_allocator())
      : _m_impl(comp, _node_allocator(alloc)) {}
  _rb_tree(const _rb_tree &x) : _m_impl(x._m_impl) {
    // todo : 이거 이해하기
//    if (x._m_root() != 0) _m_root() = _m_copy(x);
  }

  ~_rb_tree() {
    // todo 구현하기
  }

  _rb_tree &operator=(const _rb_tree &x) {
    // todo 구현하기
    if (this != &x) {
      //  clear();
      _m_impl._m_key_compare = x._m_impl._m_key_compare;
      if (x._m_root() != NULL) {
        // _m_copy_tree(x);
      }
    }
    return *this;
  }

  Compare key_comp() const { return _m_impl._m_key_compare; }

  iterator begin() { return iterator(this->_m_impl._m_header._m_left); }
  const_iterator begin() const { return iterator(this->_m_impl._m_header._m_left); }

  iterator end() { return iterator(&this->_m_impl._m_header); }
  const_iterator end() const { return iterator(&this->_m_impl._m_header); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return reverse_iterator(end()); }

  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return reverse_iterator(begin()); }

  size_type size() const { return _m_impl._m_node_count; }

  size_type max_size() const { return _m_impl.max_size(); }

  bool empty() const { return _m_impl._m_node_count == 0; }

  void swap(_rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &t) {}

  iterator find(const key_type &k) {
    _link_type _y = _m_end();
    _link_type _x = _m_root();

    while (_x != 0) {
      if (!_m_impl._m_key_compare(_s_key(_x), k)) {
        _y = _x;
        _x = _s_left(_x);
      } else {
        _x = _s_right(_x);
      }
    }
    iterator _j = iterator(_y);
    return (_j == end() || _m_impl._m_key_compare(k, _s_key(_j._m_node))) ? end() : _j;
  }

  const_iterator find(const key_type &k) const {
    _link_type _y = _m_end();
    _link_type _x = _m_root();

    while (_x != 0) {
      if (!_m_impl._m_key_compare(_s_key(_x), k)) {
        _y = _x;
        _x = _s_left(_x);
      } else {
        _x = _s_right(_x);
      }
    }
    const_iterator _j = const_iterator(_y);
    return (_j == end() || _m_impl._m_key_compare(k, _s_key(_j._m_node))) ? end() : _j;
  }

  size_type count(const key_type &k) const {
    pair<const_iterator, const_iterator> _p = equal_range(k);
    size_type _n = std::distance(_p.first, _p.second);
    return _n;
  }

  iterator lower_bound(const key_type &k) {
    // node >= k 를 만족하는 가장 첫 번째 node 반환
    _link_type _y = _m_end(); // header
    _link_type _x = _m_root(); // root

    while (_x != 0) {
      if (!_m_impl._m_key_compare(k, _s_key(_x))) {
        _y = _x;
        _x = _s_left(_x);
      } else {
        _x = _s_right(_x);
      }
    }
    return iterator(_x);
  }

  const_iterator lower_bound(const key_type &k) const {
    // node >= k 를 만족하는 가장 첫 번째 node 반환
    _link_type _y = _m_end(); // header
    _link_type _x = _m_root(); // root

    while (_x != 0) {
      if (!_m_impl._m_key_compare(k, _s_key(_x))) {
        _y = _x;
        _x = _s_left(_x);
      } else {
        _x = _s_right(_x);
      }
    }
    return const_iterator(_x);
  }

  iterator upper_bound(const key_type &k) {
    // upper_bound 초과
    _link_type _y = _m_end(); // header
    _link_type _x = _m_root(); // root

    while (_x != 0) {
      if (_m_impl._m_key_compare(k, _s_key(_x))) {
        _y = _x;
        _x = _s_left(_x);
      } else {
        _x = _s_right(_x);
      }
    }
    return iterator(_x);
  }

  const_iterator upper_bound(const key_type &k) const {
    // upper_bound 초과
    _link_type _y = _m_end(); // header
    _link_type _x = _m_root(); // root

    while (_x != 0) {
      if (_m_impl._m_key_compare(k, _s_key(_x))) {
        _y = _x;
        _x = _s_left(_x);
      } else {
        _x = _s_right(_x);
      }
    }
    return const_iterator(_x);
  }

  pair<iterator, iterator> equal_range(const key_type &k) {
    return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
  }

  pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
    return pair<const_iterator, const_iterator>(lower_bound(k), uper_bound(k));
  }

  // insert_unique
  /**
   * @brief for map.insert(const value_type)
   * @param val pair<key, value>
   * @return if the key unique, return <iterator: new element, true> else return <iterator: same key element, false>
   */
  pair<iterator, bool> insert_unique(const value_type &val) {
    // _m_tree.insert_unique(val) 밑에 insert 함수도 각 overlaod 함수에 맞는 insert_unique 함수로 구현되어 있음

    // 1. val 를 어디에 삽입할지 position 을 찾는다. (found_pos)
    // 1-1. 이진트리 처럼 대소비교를 하면서 맨 끝의 위치를 찾기
    // 1-2. return pos 는 iterator <- or base_ptr
    // 1-3. 여기서 직전에 중복키 있는지 확인해도 될 듯
    // 2. 만약 중복키가 없다면, 찐 insert or return

    pair<_base_ptr, _base_ptr> _pos = _m_get_insert_unique_pos(KeyOfValue()(val));
    if (_pos.second) {
      iterator _it = _m_insert(_pos.first, _pos.second, val);
      return ::ft::make_pair(_it, true);
    } else {
      return ::ft::make_pair(_pos.first, false);
    }
  }
  // with hint
  iterator insert_unique(iterator position, const value_type &val) {
    if (position._m_node == this->_m_impl._m_header._m_left) {
      // begin()
      if (size() > 0 &&
          _m_key_compare(KeyOfValue()(val), _s_key(position._m_node)))
        return _m_insert(position._m_node, position._m_node, val);
        // first argument just needs to be non-null
      else
        return insert_unique(val).first;
    } else if (position._m_node == &this->_m_impl._m_header) {
      // end()
      if (_m_key_compare(_s_key(_m_rightmost()), KeyOfValue()(val)))
        return _m_insert(0, _m_rightmost(), val);
      else
        return insert_unique(val).first;
    } else {
      iterator _before = position;
      --_before;
      if (_m_key_compare(_s_key(_before._m_node), KeyOfValue()(val))
          && _m_key_compare(KeyOfValue()(val), _s_key(position._m_node))) {
        if (_s_right(_before._m_node) == 0)
          return _m_insert(0, _before._m_node, val);
        else
          return _m_insert(position._m_node, position._m_node, val);
        // first argument just needs to be non-null
      } else
        return insert_unique(val).first;
    }
  }
  // range
  template<class InputIterator>
  void insert_unique(InputIterator first, InputIterator last) {
    for (; first != last; ++first) {
      insert_unique(*first);
    }
  }

  size_type erase(const key_type &x) {}

  void erase(iterator first, iterator last) {}

  void erase(const key_type *first, const key_type *last) {}

  void clear() {
    if (_m_impl._m_node_count != 0) {
      _m_erase(_m_root());
      _m_leftmost() = _m_end();
      _m_root() = 0;
      _m_rightmost() = _m_end();
      _m_impl._m_node_count = 0;
    }
  }

  /**
   * @brief insert node and rebalance tree
   * @param x target node position
   * @param y target node parent position
   * @param val value of target node
   * @return target node iterator
   */
  iterator _m_insert(_base_ptr x, _base_ptr y, const value_type &val) {
    _link_type _x = (_link_type) x;
    _link_type _y = (_link_type) y;
    _link_type _z;

    if (_y == &this->_m_impl._m_header || _x != 0
        || _m_impl._m_key_compare(KeyOfValue()(val), KeyOfValue()(_y->_m_value_field))) {
      // root 노드가 없는 경우
      // val 의 키 값이 부모 노드의 키 값보다 작은 경우 (val < parent)
      _z = _m_create_node(val);
      _s_left(_y) = _z;
      if (_y == &this->_m_impl._m_header) {
        _m_root() = _z;
        _m_rightmost() = _z;
      } else if (_y == _m_leftmost()) {
        _m_leftmost() = _z;
      }
    } else {
      // val 의 키 값이 부모 노드의 키 값보다 큰 경우 (val > parent)
      _z = _m_create_node(val);
      _s_right(_y) = _z;
      if (_y == _m_rightmost()) {
        _m_rightmost() = _z;
      }
    }
    _s_parent(_z) = _y;
    _s_left(_z) = 0;
    _s_right(_z) = 0;
    _rb_tree_rebalance(_z, this->_m_impl._m_header._m_parent);
    ++(this->_m_impl._m_node_count);
    return iterator(_z);
  }

  // return <pos_base_ptr, parent_base_ptr>
  // base_p
  pair<_base_ptr, _base_ptr> _m_get_insert_unique_pos(const key_type &k) {
    _link_type _x = _m_begin();
    _base_ptr _y = _m_end();
    bool _comp = true;

    while (_x != 0) {
      _y = _x;
      _comp = _m_impl._m_key_compare(k, KeyOfValue()(_x->_m_value_field));
      _x = _comp ? _s_left(_x) : _s_right(_x);
    }
    iterator _j = iterator(_y);
    if (_comp) {
      // if _x is left side of parent(_y)
      if (_j == begin()) // root 노드가 없을 때
        return ::ft::make_pair(_x, _y);
      else
        --_j; // left side 일 때 확인
    }
    // 중복된 키가 없을 경우
    if (_m_impl._m_key_compare(KeyOfValue()(static_cast<_link_type>(_j._m_node)->_m_value_field), k))
      return ::ft::make_pair(_x, _y);
    // 중복된 키가 있을 경우
    return ::ft::make_pair(_j._m_node, (_base_ptr) 0);
  }


  // copy_tree : 복사 생성자에서 등등에서 사용함

  // restructuring 할 때 rotate_left / right 를 사용한다.




  // size
};

inline void _rb_tree_rotate_left(_rb_tree_node_base *x, _rb_tree_node_base *&root) {
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
inline void _rb_tree_rotate_right(_rb_tree_node_base *x, _rb_tree_node_base *&root) {
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
inline void _rb_tree_rebalance(_rb_tree_node_base *x, _rb_tree_node_base *&root) {
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

} // namespace ft

#endif //TREE_HPP_
