/*
 * File: map.hpp
 * Project: ft_container
 * Created Date: 2023/02/15
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <functional>
#include "pair.hpp"
#include "function.hpp"
#include "tree.hpp"

// 지워야함
#include <map>

namespace ft {

template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef pair<const Key, T> value_type;
  typedef Compare key_compare;

  class value_compare : public std::binary_function<value_type, value_type, bool> {
    friend class map<Key, T, Compare, Alloc>;
   protected:
    Compare _comp;
    /**
     * @brief Returns a comparison object that can be used to compare two elements to get whether the key of the first one goes before the second
     *
     * explict 붙이면 안됨
     * https://legacy.cplusplus.com/reference/map/map/value_comp/
     */
    value_compare(Compare c) : _comp(c) {}
   public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type &x, const value_type &y) const {
      return _comp(x.first, y.first);
    }
  };

 private:
  typedef _rb_tree<key_type, value_type, Select1st<value_type>, key_compare, Alloc> rep_type;
  rep_type _m_tree;

 public:
  typedef typename rep_type::allocator_type allocator_type;
  typedef typename rep_type::reference reference;
  typedef typename rep_type::const_reference const_reference;
  typedef typename rep_type::iterator iterator;
  typedef typename rep_type::const_iterator const_iterator;
  typedef typename rep_type::size_type size_type;
  typedef typename rep_type::difference_type difference_type;
  typedef typename rep_type::pointer pointer;
  typedef typename rep_type::const_pointer const_pointer;
  typedef typename rep_type::reverse_iterator reverse_iterator;
  typedef typename rep_type::const_reverse_iterator const_reverse_iterator;

  /**
   * @brief Default constructor creates no elements
   */
  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type()) : _m_tree(comp, alloc) {}

  /**
   * @brief Range constructor
   * @tparam InputIterator
   * @param first
   * @param last
   * @param comp
   * @param alloc
   *
   * Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range.
   */
  template<class InputIterator>
  map(InputIterator first,
      InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type()) : _m_tree(comp, alloc) {
    _m_tree.insert_unique(first, last);
  }

  /**
   * @brief Map Copy constructor
   * @param x map
   *
   * Constructs a container with a copy of each of the elements in x.
   */
  map(const map &x) : _m_tree(x._m_tree) {}

  /**
   * @brief Destroys the container object
   *
   * This destroys all container elements, and deallocates all the storage capacity allocated by the map container using its allocator.
   */
  ~map() {}

  /**
   *  @brief  Map assignment operator.
   *  @param  x  A %map of identical element and allocator types.
   *
   *  All the elements of @a x are copied, but unlike the copy constructor,
   *  the allocator object is not copied.
   */
  map &operator=(const map &x) {
    _m_tree = x._m_tree;
    return *this;
  }

  // Get a copy of the memory allocation object.
  allocator_type
  get_allocator() const { return _m_tree.get_allocator(); }

  /* ****************************************************** */
  /*                      Iterators                         */
  /* ****************************************************** */

  /**
   * Returns iterator that points to the first element in the %vector
   */
  iterator begin() { return _m_tree.begin(); };
  const_iterator begin() const { return _m_tree.begin(); };

  /**
   * Returns iterator that points to the last element in the %vector
   */
  iterator end() { return _m_tree.end(); };
  const_iterator end() const { return _m_tree.end(); };

  /**
   * Returns reverse_iterator that points to one before the first element in the %vector
   */
  reverse_iterator rbegin() { return _m_tree.rbegin(); }
  const_reverse_iterator rbegin() const { return _m_tree.rbegin(); }

  /**
   * Returns reverse_iterator that points to the last element in the %vector
   */
  reverse_iterator rend() { return _m_tree.rend(); }
  const_reverse_iterator rend() const { return _m_tree.rend(); }

  /* ****************************************************** */
  /*                      Capacity                          */
  /* ****************************************************** */

  /**
   * @brief Returns the number of elements in the %vector
   * @return the number of elements
   */
  size_type size() const { return _m_tree.size(); }

  /**
   * @brief Returns the size() of the largest possible %vector.
   * @return size of largest possible %vector
   *
   * Returns the maximum number of elements that the vector can hold.
   * allocator 의 max_size 임 그거 리턴하면 됨
   */
  size_type max_size() const { return _m_tree.max_size(); }

  /**
   * @brief Returns true if the %vector is empty.
   * @return true : empty, false : not empty
   *
   * 벡터가 비어있는지 확인 size 가 0인지 확인
   */
  bool empty() const { return _m_tree.empty();; }

  void test() { _m_tree.printBT(); }
  void test() const { _m_tree.printBT(); }

  /* ****************************************************** */
  /*                   Element access                       */
  /* ****************************************************** */

  /**
   * @brief If %k matches the key of an element in the container, the function returns a reference to its mapped value.
   * @param key
   * @return
   *
   * 만약 key 가 없다면 insert
   * 있다면 값 return
   */
  mapped_type &operator[](const key_type &k) {
    iterator _i = lower_bound(k);
    if (_i == end() || key_comp()(k, (*_i).first)) {
      _i = insert(_i, value_type(k, mapped_type()));
    }
    return (*_i).second;
  }

  /* ****************************************************** */
  /*                      Modifiers                          */
  /* ****************************************************** */

  // insert
  // single element
  pair<iterator, bool> insert(const value_type &val) {
    // _m_tree.insert_unique(val) 밑에 insert 함수도 각 overlaod 함수에 맞는 insert_unique 함수로 구현되어 있음
    return _m_tree.insert_unique(val);
  }
  // with hint
  iterator insert(iterator position, const value_type &val) {
    return _m_tree.insert_unique(position, val);
  }
  // range
  template<class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    _m_tree.insert_unique(first, last);
  }

  // erase
  void erase(iterator position) {
    _m_tree.erase(position);
  }
  size_type erase(const key_type &key) {
    return _m_tree.erase(key);
  }
  void erase(iterator first, iterator last) {
    _m_tree.erase(first, last);
  }

  // swap
  void swap(map &x) { _m_tree.swap(x._m_tree); }

  // clear
  void clear() { _m_tree.clear(); }

  /* ****************************************************** */
  /*                      Observers                         */
  /* ****************************************************** */

  // key_comp
  /**
   * @brief Returns a copy of the comparison object used by the container to compare keys
   * @return
   */
  key_compare key_comp() const { return _m_tree.key_comp(); }

  /**
   * @brief Returns a comparsion object that can be used to compare two elements to get whether the key of th first one goes before the second
   * @return
   *
   * mymap.value_comp()(*it, begin()) 이런식으로 쓸 수 있음
   */
  value_compare value_comp() const { return value_compare(_m_tree.key_comp()); }

  /* ****************************************************** */
  /*                      Operations                        */
  /* ****************************************************** */

  /**
   * @brief Searches the container for an element with a key equal to k and returns an iterator to it if found, otherwise returns map::end
   * @param key
   * @return
   */
  iterator find(const key_type &k) { return _m_tree.find(k); }
  const_iterator find(const key_type &k) const { return _m_tree.find(k); }

  /**
   * @brief Searches the container for elements with a key equal to k and returns the number of matches
   * @param k
   * @return 1 if the container contains an element whose key is equivalent to k, or zero otherwise.
   */
  size_type count(const key_type &k) const {
    return _m_tree.find(k) == _m_tree.end() ? 0 : 1;
  }

  /**
   * @brief
   * @param k
   * @return
   *
   * Returns an iterator pointing to the first element in the container whose key is not considered to go before k
   * key_comp 를 사용하여 구현한다.
   */
  iterator lower_bound(const key_type &k) { return _m_tree.lower_bound(k); }
  const_iterator lower_bound(const key_type &k) const { return _m_tree.lower_bound(k); }

  /**
   * @brief Returns an iterator pointing to the first element in the container whose key is considered to go after k.
   * @param k
   * @return
   */
  iterator upper_bound(const key_type &k) { return _m_tree.upper_bound(k); }
  const_iterator upper_bound(const key_type &k) const { return _m_tree.upper_bound(k); }

  /**
   * @brief Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
   * @param k
   * @return
   */
  pair<const_iterator, const_iterator> equal_range(const key_type &k) const { return _m_tree.equal_range(k); }
  pair<iterator, iterator> equal_range(const key_type &k) { return _m_tree.equal_range(k); }

  template<class Key1, class T1, class Compare1, class Alloc1>
  friend bool operator==(const map<Key1, T1, Compare1, Alloc1> &lhs,
                         const map<Key1, T1, Compare1, Alloc1> &rhs);

  template<class Key1, class T1, class Compare1, class Alloc1>
  friend bool operator<(const map<Key1, T1, Compare1, Alloc1> &lhs,
                        const map<Key1, T1, Compare1, Alloc1> &rhs);
};

template<class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs) {
  return lhs._m_tree == rhs._m_tree;
}

template<class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs) {
  return !(lhs == rhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc> &lhs,
               const map<Key, T, Compare, Alloc> &rhs) {
  return lhs._m_tree < rhs._m_tree;
}

template<class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs) {
  return !(rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc> &lhs,
               const map<Key, T, Compare, Alloc> &rhs) {
  return (rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs) {
  return !(lhs < rhs);
}

// swap
template<class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {
  x.swap(y);
}

} // namespace ft

#endif //MAP_HPP_
