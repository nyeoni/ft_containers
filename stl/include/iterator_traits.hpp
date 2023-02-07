/*
 * File: iterator.hpp
 * Project: ft_containers
 * Created Date: 2023/01/28
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_

#include <array>
#include <cstddef>

/**
 * @class iterator
 * @namespace ft
 * @brief
 * std::iterator is the type trait class that provides uniform interface
 * to the properties of LegacyIterator types. This makes it possible to
 * implement algorithms only in terms of iterators.
 *
 * @see https://en.cppreference.com/w/cpp/iterator/iterator
 */

namespace ft {
template<typename Iter>
struct iterator {
  typedef typename Iter::difference_type difference_type;
  typedef typename Iter::value_type value_type;
  typedef typename Iter::pointer pointer;
  typedef typename Iter::reference reference;
  typedef typename Iter::iterator_category iterator_category;
};

template<typename Tp>
struct iterator<Tp *> {
  typedef std::ptrdiff_t difference_type;
  typedef Tp value_type;
  typedef Tp *pointer;
  typedef Tp &reference;
  typedef std::random_access_iterator_tag iterator_category;
};

template<typename Tp>
struct iterator<const Tp *> {
  typedef std::ptrdiff_t difference_type;
  typedef Tp value_type;
  typedef const Tp *pointer;
  typedef const Tp &reference;
  typedef std::random_access_iterator_tag iterator_category;
};

template <typename Iter,

}  // namespace ft


#endif //ITERATOR_HPP_
