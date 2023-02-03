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
 * @class iterator_traits
 * @namespace ft
 * @brief
 * std::iterator_traits is the type trait class that provides uniform interface
 * to the properties of LegacyIterator types. This makes it possible to
 * implement algorithms only in terms of iterators.
 *
 * @see https://en.cppreference.com/w/cpp/iterator/iterator_traits
 */

namespace ft {
template<typename Iter>
struct iterator_traits {
  typedef typename Iter::difference_type difference_type;
  typedef typename Iter::value_type value_type;
  typedef typename Iter::pointer pointer;
  typedef typename Iter::reference reference;
  typedef typename Iter::iterator_category iterator_category;
};

template<typename Tp>
struct iterator_traits<Tp *> {
  typedef std::ptrdiff_t difference_type;
  typedef Tp value_type;
  typedef Tp *pointer;
  typedef Tp &reference;
  typedef std::random_access_iterator_tag iterator_category;
};

template<typename Tp>
struct iterator_traits<const Tp *> {
  typedef std::ptrdiff_t difference_type;
  typedef Tp value_type;
  typedef const Tp *pointer;
  typedef const Tp &reference;
  typedef std::random_access_iterator_tag iterator_category;
};

}  // namespace ft


#endif //ITERATOR_TRAITS_HPP_
