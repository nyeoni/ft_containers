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

// 지워야함
#include <map>

namespace ft {

template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> >>
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
      const allocator_type &alloc = allocator_type()) {}

  /**
   * @brief Map Copy constructor
   * @param x map
   *
   * Constructs a container with a copy of each of the elements in x.
   */
  map(const map &x) : _m_tree(x._m_tree) {}
};

} // namespace ft

#endif //MAP_HPP_
