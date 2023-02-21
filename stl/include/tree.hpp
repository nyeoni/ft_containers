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

// Val = pair<key, value>
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

    _rb_tree_impl() : _node_allocator() {}
    // 이거 x 만 받아도 다형성에 의해서 작동되는지 확인해보기
    _rb_tree_impl(const _rb_tree_impl &x)
        : _node_allocator(x), _base_key_compare(x._m_key_compare), _rb_tree_header() {}
    _rb_tree_impl(const Key_Compare &comp, const _node_allocator &alloc)
        : _node_allocator(alloc), _base_key_compare(comp) {}
  };

  // member variables
  _rb_tree_impl<Compare> _m_impl;

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

  // insert_unique(inputiter first, inputiter last)

  // insert_uniqueue : key 중복 방지해주면서 insert 를 하는거
  // find_pos 를 해서 position 을 찾는다.
  // 중복체크하고
  // _m_insert : 진짜 찐으로 넣어주는 함수 / restructring

  // copy_tree : 복사 생성자에서 등등에서 사용함

  // restructuring 할 때 rotate_left / right 를 사용한다.




  // size
};

} // namespace ft

#endif //TREE_HPP_
