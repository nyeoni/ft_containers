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
#include "algorithm.hpp"
#include <memory>

//#include <iostream>

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

_rb_tree_node_base *_rb_tree_increment(_rb_tree_node_base *x) throw();
const _rb_tree_node_base *_rb_tree_increment(const _rb_tree_node_base *x) throw();
_rb_tree_node_base *_rb_tree_decrement(_rb_tree_node_base *x) throw();
const _rb_tree_node_base *_rb_tree_decrement(const _rb_tree_node_base *x) throw();

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
  explicit _rb_tree_iterator(_base_ptr x) : _m_node(x) {}
  _rb_tree_iterator(const _self &src) : _m_node(src._m_node) {}

  // const rb_iterator to non-const rb_iterator
  iterator _m_const_cast() const {
    return iterator(const_cast<typename iterator::_base_ptr>(_m_node));
  }

  _self &operator=(const _self &src) {
    _m_node = src._m_node;
    return *this;
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

template<typename T>
struct _rb_tree_const_iterator {
  typedef _rb_tree_iterator<T> iterator;
  typedef ptrdiff_t difference_type;
  typedef const T &reference;
  typedef const T *pointer;
  typedef T value_type;
  typedef std::bidirectional_iterator_tag iterator_category;

  typedef _rb_tree_const_iterator<T> _self;
  typedef _rb_tree_node_base::_const_base_ptr _base_ptr;
  typedef const _rb_tree_node<T> *_link_type;

  _base_ptr _m_node;

  _rb_tree_const_iterator() : _m_node() {}
  explicit _rb_tree_const_iterator(_base_ptr x) : _m_node(x) {}
  _rb_tree_const_iterator(const iterator &it) : _m_node(it._m_node) {}

  // const rb_iterator to non-const rb_iterator
  iterator _m_const_cast() const {
    return iterator(const_cast<typename iterator::_base_ptr>(_m_node));
  }

  _self &operator=(const _self &src) {
    _m_node = src._m_node;
    return *this;
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
    _link_type _tmp = _m_create_node(x->_m_value_field);
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
        : _node_allocator(alloc), _base_key_compare(comp), _rb_tree_header() {}
  };

  // member variables
  _rb_tree_impl<Compare> _m_impl;

// public:
//  void printBT(const std::string &prefix, _link_type node, bool isLeft) const {
//    if (node != nullptr) {
//      std::cout << prefix;
//
//      std::cout << (isLeft ? "├──" : "└──");
//
//      // print the value of the node
//      std::cout << KeyOfValue()(node->_m_value_field) << std::endl;
//
//      // enter the next tree level - left and right branch
//      printBT(prefix + (isLeft ? "│   " : "    "), (_link_type) node->_m_left, true);
//      printBT(prefix + (isLeft ? "│   " : "    "), (_link_type) node->_m_right, false);
//    }
//  }
//
//  void printBT() const {
//    std::cout << "hihi fuckyou" << std::endl;
//    printBT("", (_link_type) _m_impl._m_header._m_parent, false);
//  }

 protected:
  // 여기서는 _rb_node_base pointer 를 리턴해줌
  _base_ptr &_m_root() { return this->_m_impl._m_header._m_parent; }
  _const_base_ptr _m_root() const { return this->_m_impl._m_header._m_parent; }

  _base_ptr &_m_leftmost() { return this->_m_impl._m_header._m_left; }
  _const_base_ptr _m_leftmost() const { return this->_m_impl._m_header._m_left; }

  _base_ptr &_m_rightmost() { return this->_m_impl._m_header._m_right; }
  _const_base_ptr _m_rightmost() const { return this->_m_impl._m_header._m_right; }

  // 여기는 _rb_node<Val> 를 리턴해줌
  // 여기 필요하면 쓰고 아니면 버리기
  _link_type _m_begin() { return static_cast<_link_type>(this->_m_impl._m_header._m_parent); }
  _const_link_type _m_begin() const { return static_cast<_link_type>(this->_m_impl._m_header._m_parent); }

  _link_type _m_end() { return (_link_type) &(this->_m_impl._m_header); }
  _const_base_ptr _m_end() const { return &(this->_m_impl._m_header); }

  static _link_type &_s_left(_base_ptr x) { return (_link_type &) (x->_m_left); }
  static _const_link_type &_s_left(_const_base_ptr x) { return (_const_link_type &) (x->_m_left); }

  static _link_type &_s_right(_base_ptr x) { return (_link_type &) (x->_m_right); }
  static _const_link_type &_s_right(_const_base_ptr x) { return (_const_link_type &) (x->_m_right); }

  static _link_type &_s_parent(_link_type x) { return (_link_type &) (x->_m_parent); }
  static _const_link_type &_s_parent(_const_link_type x) { return (_const_link_type &) (x->_m_parent); }

  static Key _s_key(_base_ptr x) { return KeyOfValue()(((_link_type) x)->_m_value_field); }

 public:
  typedef _rb_tree_iterator<value_type> iterator;
  typedef _rb_tree_const_iterator<value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  _rb_tree() : _m_impl() {}

  _rb_tree(const Compare &comp, const allocator_type &alloc = _node_allocator())
      : _m_impl(comp, _node_allocator(alloc)) {}

  _rb_tree(const _rb_tree &x) : _m_impl(x._m_impl) {
    if (x._m_root() != 0) {
      _m_root() = _m_copy((_link_type) x._m_root(), _m_end());
      _m_impl._m_header._m_parent->_m_parent = &_m_impl._m_header;
      _m_impl._m_header._m_left = _rb_tree_node_base::_s_minimum(_m_root());
      _m_impl._m_header._m_right = _rb_tree_node_base::_s_maximum(_m_root());
      _m_impl._m_node_count = x._m_impl._m_node_count;
    }
  }

  ~_rb_tree() { clear(); }

  _rb_tree &operator=(const _rb_tree &x) {
    if (this != &x) {
      clear();
      _m_impl._m_key_compare = x._m_impl._m_key_compare;
      if (x._m_root() != 0) {
        _m_root() = _m_copy((_link_type) x._m_root(), _m_end());
        _m_impl._m_header._m_parent->_m_parent = &_m_impl._m_header;
        _m_impl._m_header._m_left = _rb_tree_node_base::_s_minimum(_m_root());
        _m_impl._m_header._m_right = _rb_tree_node_base::_s_maximum(_m_root());
        _m_impl._m_node_count = x._m_impl._m_node_count;
      }
    }
    return *this;
  }

  Compare key_comp() const { return _m_impl._m_key_compare; }

  iterator begin() { return iterator(this->_m_impl._m_header._m_left); }
  const_iterator begin() const { return const_iterator(this->_m_impl._m_header._m_left); }

  iterator end() { return iterator(&this->_m_impl._m_header); }
  const_iterator end() const { return const_iterator(&this->_m_impl._m_header); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

  size_type size() const { return _m_impl._m_node_count; }

  size_type max_size() const { return _m_impl.max_size(); }

  bool empty() const { return _m_impl._m_node_count == 0; }

  void swap(_rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &t) {
    if (_m_root() == 0) {
      if (t._m_root() != 0) {
        _m_root() = t._m_root();
        _m_leftmost() = t._m_leftmost();
        _m_rightmost() = t._m_rightmost();
        _m_root()->_m_parent = _m_end();

        t._m_root() = 0;
        t._m_leftmost() = t._m_end();
        t._m_rightmost() = t._m_end();
      }
    } else if (t._m_root() == 0) {
      t._m_root() = _m_root();
      t._m_leftmost() = _m_leftmost();
      t._m_rightmost() = _m_rightmost();
      t._m_root()->_m_parent = t._m_end();

      _m_root() = 0;
      _m_leftmost() = _m_end();
      _m_rightmost() = _m_end();
    } else {
      ft::swap(_m_root(), t._m_root());
      ft::swap(_m_leftmost(), t._m_leftmost());
      ft::swap(_m_rightmost(), t._m_rightmost());

      _m_root()->_m_parent = _m_end();
      t._m_root()->_m_parent = t._m_end();
    }
    // No need to swap header's color as it does not change.
    ft::swap(this->_m_impl._m_node_count, t._m_impl._m_node_count);
    ft::swap(this->_m_impl._m_key_compare, t._m_impl._m_key_compare);
  }

  iterator find(const key_type &k) {
    iterator _j = lower_bound(k);
    return (_j == end() || _m_impl._m_key_compare(k, KeyOfValue()(*_j))) ? end() : _j;
  }

  const_iterator find(const key_type &k) const {
    const_iterator _j = lower_bound(k);
    return (_j == end() || _m_impl._m_key_compare(k, KeyOfValue()(*_j))) ? end() : _j;
  }

  size_type count(const key_type &k) const {
    pair<const_iterator, const_iterator> _p = equal_range(k);
    size_type _n = std::distance(_p.first, _p.second);
    return _n;
  }

  iterator lower_bound(const key_type &k) {
    // node >= k 를 만족하는 가장 첫 번째 node 반환
    _link_type _y = (_link_type) _m_end(); // header
    _link_type _x = (_link_type) _m_root(); // root

    while (_x != 0) {
      if (!_m_impl._m_key_compare(_s_key(_x), k)) {
        _y = _x;
        _x = _s_left(_x);
      } else {
        _x = _s_right(_x);
      }
    }
    return iterator(_y);
  }

  const_iterator lower_bound(const key_type &k) const {
    // node >= k 를 만족하는 가장 첫 번째 node 반환
    _link_type _y = (_link_type) _m_end(); // header
    _link_type _x = (_link_type) _m_root(); // root

    while (_x != 0) {
      if (!_m_impl._m_key_compare(_s_key(_x), k)) {
        _y = _x;
        _x = _s_left(_x);
      } else {
        _x = _s_right(_x);
      }
    }
    return const_iterator(_y);
  }

  iterator upper_bound(const key_type &k) {
    // upper_bound 초과
    _link_type _y = (_link_type) _m_end(); // header
    _link_type _x = (_link_type) _m_root(); // root

    while (_x != 0) {
      if (_m_impl._m_key_compare(k, _s_key(_x))) {
        _y = _x;
        _x = _s_left(_x);
      } else {
        _x = _s_right(_x);
      }
    }
    return iterator(_y);
  }

  const_iterator upper_bound(const key_type &k) const {
    // upper_bound 초과
    _link_type _y = (_link_type) _m_end(); // header
    _link_type _x = (_link_type) _m_root(); // root

    while (_x != 0) {
      if (_m_impl._m_key_compare(k, _s_key(_x))) {
        _y = _x;
        _x = _s_left(_x);
      } else {
        _x = _s_right(_x);
      }
    }
    return const_iterator(_y);
  }

  /**
   * @param k
   * @return the bounds of a range that includes all elements in the container which have a key equivalent to k
   * 만약 key 가 없다면 0 을 리턴
   */
  pair<iterator, iterator> equal_range(const key_type &k) {
    return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
  }

  pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
    return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
  }

  /**
   * @brief for map.insert(const value_type)
   * @param val pair<key, value>
   * @return if the key unique, return <iterator: new element, true> else return <iterator: same key element, false>
   */
  pair<iterator, bool> insert_unique(const value_type &val) {
    _link_type _x = _m_begin();
    _link_type _y = (_link_type) _m_end();
    bool _comp = true;

    while (_x != 0) {
      _y = _x;
      _comp = _m_impl._m_key_compare(KeyOfValue()(val), KeyOfValue()(_x->_m_value_field));
      _x = _comp ? _s_left(_x) : _s_right(_x);
    }
    iterator _j = iterator(_y);
    if (_comp) {
      // if _x is left side of parent(_y)
      if (_j == begin()) // root 노드가 없을 때
        return ::ft::make_pair(_m_insert(_x, _y, val), true);
      else
        --_j; // left side 일 때 확인
    }
    // 중복된 키가 없을 경우
    if (_m_impl._m_key_compare(_s_key(_j._m_node), KeyOfValue()(val))) {
      iterator _it = _m_insert(_x, _y, val);
      return ::ft::make_pair(_it, true);
    }
    return ::ft::make_pair(_j, false);
  }

  /**
   * @brief hint for the position where element can be inserted
   * @param position hint
   * @param val value
   * @return iterator pointing to either the newly inserted element or to the element that already had an equivalent key in the map.
   */
  iterator insert_unique(const_iterator position, const value_type &val) {
    iterator pos = position._m_const_cast();

    if (pos._m_node == this->_m_impl._m_header._m_left) {
      if (size() > 0 &&
          _m_impl._m_key_compare(KeyOfValue()(val), _s_key(pos._m_node)))
        return _m_insert(pos._m_node, pos._m_node, val);
      else
        return insert_unique(val).first;
    } else if (pos._m_node == &this->_m_impl._m_header) {
      if (_m_impl._m_key_compare(_s_key(_m_rightmost()), KeyOfValue()(val)))
        return _m_insert(0, _m_rightmost(), val);
      else
        return insert_unique(val).first;
    } else {
      iterator _before = pos;
      --_before;
      if (_m_impl._m_key_compare(_s_key(_before._m_node), KeyOfValue()(val))
          && _m_impl._m_key_compare(KeyOfValue()(val), _s_key(pos._m_node))) {
        if (_s_right(_before._m_node) == 0)
          return _m_insert(0, _before._m_node, val);
        else
          return _m_insert(pos._m_node, pos._m_node, val);
      } else
        return insert_unique(val).first;
    }
  }

  template<class InputIterator>
  void insert_unique(InputIterator first, InputIterator last) {
    for (; first != last; ++first) {
      insert_unique(*first);
    }
  }

  void erase(iterator position) {
    _link_type _y = (_link_type) _rb_tree_rebalance_for_erase(position._m_node,
                                                              _m_impl._m_header._m_parent,
                                                              _m_impl._m_header._m_left,
                                                              _m_impl._m_header._m_right);
    _m_drop_node(_y);
    --_m_impl._m_node_count;
  }

  /**
   * @brief remove key of the element from map
   * @param k key
   * @return number of element erased
   */
  size_type erase(const key_type &k) {
    pair<iterator, iterator> _p = equal_range(k);
    size_type _n = std::distance(_p.first, _p.second);
    erase(_p.first, _p.second);
    return _n;
  }

  void erase(iterator first, iterator last) {
    if (first == begin() && last == end()) {
      clear();
    } else {
      while (first != last) erase(first++);
    }
  }

  void clear() {
    if (_m_impl._m_node_count != 0) {
      _m_erase(static_cast<_link_type>(_m_root()));
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
   *
   * insert 는 항상 leaf node 에 된다. -> bst insert 와 같은 원리
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

  //
  _link_type _m_copy(_link_type x, _link_type p) {
    // top node clone
    // insert 문으로 하게 되면 -> rebalance 하는데에 너무 많은 리소스가 들어가게됨
    _link_type _top = _m_clone_node(x);
    _top->_m_parent = p;

    try {
      if (x->_m_right) {
        _top->_m_right = _m_copy(_s_right(x), _top);
      }
      p = _top;
      x = _s_left(x);

      while (x != 0) {
        _link_type _y = _m_clone_node(x);
        p->_m_left = _y;
        _y->_m_parent = p;
        if (x->_m_right)
          _y->_m_right = _m_copy(_s_right(x), _y);
        p = _y;
        x = _s_left(x);
      }
    } catch (std::exception &e) {
      _m_erase(_top);
      throw e;
    }
    return _top;
  }

  void _m_erase(_link_type x) {
    // erase without rebalancing
    while (x != 0) {
      _m_erase(_s_right(x));
      _link_type _y = _s_left(x);
      _m_drop_node(x);
      x = _y;
    }
  }

  friend bool operator==(const _rb_tree &lhs, const _rb_tree &rhs) {
    return lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin());
  }

  friend bool operator<(const _rb_tree &lhs, const _rb_tree &rhs) {
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  }
};

void _rb_tree_rotate_left(_rb_tree_node_base *x, _rb_tree_node_base *&root);
void _rb_tree_rotate_right(_rb_tree_node_base *x, _rb_tree_node_base *&root);
void _rb_tree_rebalance(_rb_tree_node_base *x, _rb_tree_node_base *&root);
_rb_tree_node_base *_rb_tree_rebalance_for_erase(_rb_tree_node_base *z,
                                                 _rb_tree_node_base *&root,
                                                 _rb_tree_node_base *&leftmost,
                                                 _rb_tree_node_base *&rightmost);

} // namespace ft

#endif //TREE_HPP_
