/*
 * File: vector.hpp
 * Project: ft_container
 * Created Date: 2023/01/31
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <memory>

#include <iterator>

#include <vector>
#include "iterator_traits.hpp"

namespace ft {

/**
 * @section vector_base
 * @brief vector_base manage vector memory (RAII pattern)
 *
 * @tparam T
 * @tparam Allocator
 */
template<
    class T,
    class Allocator = std::allocator<T>
>
class vector_base {
 protected:
  T *mStart;
};

template<class T>
class vector_iterator : public std::iterator<std::random_access_iterator_tag, T> {
 public:
  typedef typename ft::iterator_traits<T *> iterator_traits_type;
  typedef typename iterator_traits_type::difference_type difference_type;
  typedef typename iterator_traits_type::value_type value_type;
  typedef typename iterator_traits_type::pointer pointer;
  typedef typename iterator_traits_type::reference reference;
  typedef typename iterator_traits_type::iterator_category iterator_category;

};

/**
 * @class vector
 * @namespace ft
 * @brief Sequence containers representing arrays that can change in size
 * @note allocator 뒤에 스페이스 안붙여서 컴파일 에러 날 수 있음. >> 연속으로 오면 안됨 > > 이렇게 되어야 함
 */
template<
    class T,
    class Allocator = std::allocator<T>
>
class vector : protected vector_base<T, Allocator> {
 public:
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef vector_iterator<value_type> iterator;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
};

}

#endif //VECTOR_HPP_
