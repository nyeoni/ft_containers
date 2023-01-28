/*
 * File: iterator_traits.hpp
 * Project: ft_containers
 * Created Date: 2023/01/28
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef ITERATOR_TRAITS_HPP_
#define ITERATOR_TRAITS_HPP_

#include <array>
#include <cstddef>

/**
 * @brief
 * std::iterator_traits is the type trait class that provides uniform interface
 * to the properties of LegacyIterator types. This makes it possible to
 * implement algorithms only in terms of iterators.
 *
 * https://en.cppreference.com/w/cpp/iterator/iterator_traits
 */

namespace ft {
template <class _Iterator>
struct iterator_traits {
  typedef typename _Iterator::difference_type difference_type;
  typedef typename _Iterator::value_type value_type;
  typedef typename _Iterator::pointer pointer;
  typedef typename _Iterator::reference reference;
  typedef typename _Iterator::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T*> {
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T*> {
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T* pointer;
  typedef const T& reference;
  typedef std::random_access_iterator_tag iterator_category;
};

}  // namespace ft


#endif //ITERATOR_TRAITS_HPP_
