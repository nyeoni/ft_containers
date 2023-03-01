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
#include "type_traits.hpp"
#include "algorithm.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "ftexcept.hpp"

namespace ft {

/**
 * @class _vector_iterator
 * @namespace ft
 * @brief random_aft::vector_iterator for ft::vector
 * @tparam T value_type
 * @note _Iter 는 포인터 처럼 사용할 수 있음 (_Iter == T *) 그래서 iterator_traits<T *> 로 들어갈 예정임
 */
template<class Iter>
class _vector_iterator : public std::iterator<std::random_access_iterator_tag,
                                              typename iterator_traits<Iter>::value_type,
                                              typename iterator_traits<Iter>::difference_type,
                                              typename iterator_traits<Iter>::pointer,
                                              typename iterator_traits<Iter>::reference> {
 private:
  Iter _it;
 public:
  typedef Iter iterator_type;
  typedef typename iterator_traits<Iter>::difference_type difference_type;
  typedef typename iterator_traits<Iter>::reference reference;
  typedef typename iterator_traits<Iter>::pointer pointer;
  typedef typename iterator_traits<Iter>::iterator_category iterator_category;
  typedef typename iterator_traits<Iter>::value_type value_type;

  // constructor
  // _vector_iterator 에 explicit 뺀 이유 설명하기
  _vector_iterator() : _it() {}
  _vector_iterator(const Iter &it) : _it(it) {}
  template<typename U>
  _vector_iterator(const _vector_iterator<U> &u) : _it(u.base()) {}

  // member functions
  iterator_type base() const { return _it; }
  reference operator*() const {
    return *_it;
  } // *rit
  _vector_iterator operator+(difference_type n) const {
    return _vector_iterator(_it + n);
  } // rit + n
  _vector_iterator &operator++() {
    ++_it;
    return *this;
  } // ++rit
  _vector_iterator operator++(int) {
    _vector_iterator tmp(*this);
    ++_it;
    return tmp;
  } // rit++
  _vector_iterator &operator--() {
    --_it;
    return *this;
  } // --rit
  _vector_iterator operator--(int) {
    _vector_iterator tmp(*this);
    --_it;
    return tmp;
  } // rit--
  _vector_iterator &operator+=(difference_type n) {
    _it += n;
    return *this;
  }
  _vector_iterator operator-(difference_type n) const {
    return _vector_iterator(_it - n);
  } // rit - n
  _vector_iterator &operator-=(difference_type n) {
    _it -= n;
    return *this;
  }
  pointer operator->() const {
    return std::addressof(operator*());
  } // rit->member_var
  reference operator[](difference_type n) const {
    return *(*this + n);
  } // rit[n]
};

// non-member function
// relational operators
template<class Iter1, class Iter2>
bool operator==(const _vector_iterator<Iter1> &lhs, const _vector_iterator<Iter2> &rhs) {
  return lhs.base() == rhs.base();
}
template<class Iter1, class Iter2>
bool operator!=(const _vector_iterator<Iter1> &lhs, const _vector_iterator<Iter2> &rhs) {
  return lhs.base() != rhs.base();
}
template<class Iter1, class Iter2>
bool operator<(const _vector_iterator<Iter1> &lhs, const _vector_iterator<Iter2> &rhs) {
  return lhs.base() < rhs.base();
}
template<class Iter1, class Iter2>
bool operator<=(const _vector_iterator<Iter1> &lhs, const _vector_iterator<Iter2> &rhs) {
  return lhs.base() <= rhs.base();
}
template<class Iter1, class Iter2>
bool operator>(const _vector_iterator<Iter1> &lhs, const _vector_iterator<Iter2> &rhs) {
  return lhs.base() > rhs.base();
}
template<class Iter1, class Iter2>
bool operator>=(const _vector_iterator<Iter1> &lhs, const _vector_iterator<Iter2> &rhs) {
  return lhs.base() >= rhs.base();
}

// operator+ (_vector_iterator)
template<class Iter>
_vector_iterator<Iter> operator+(typename _vector_iterator<Iter>::difference_type n,
                                 const _vector_iterator<Iter> &rev_it) {
  return _vector_iterator<Iter>(rev_it.base() + n);
} // n + rit

// operator- (_vector_iterator)
template<class Iter1, class Iter2>
typename _vector_iterator<Iter1>::difference_type operator-(const _vector_iterator<Iter1> &lhs,
                                                            const _vector_iterator<Iter2> &rhs) {
  return lhs.base() - rhs.base();
} // iter1 - iter2

/**
 * @class _vector_base
 * @namespace ft
 * @brief vector_base manage vector memory (RAII pattern)
 * @tparam T
 * @tparam Allocator
 */
template<
    class T,
    class Allocator = std::allocator<T>
>
class _vector_base {
 public:
  typedef Allocator allocator_type;
 protected:
  allocator_type _m_data_allocator;
  T *_m_start; // pointer of first element
  T *_m_finish; // pointer of last element
  T *_m_end_of_storage; // pointer of last memory address + 1

 public:
  /**
   * @brief Default _vector_base constructor
   * @param alloc allocator
   */
  explicit _vector_base(const allocator_type &alloc)
      : _m_data_allocator(alloc), _m_start(NULL), _m_finish(NULL), _m_end_of_storage(NULL) {}
  /**
   * @brief Constructor that allocates memory as large as n
   * @param n memory size
   * @param alloc allocator
   */
  explicit _vector_base(size_t n, const allocator_type &alloc) : _m_data_allocator(alloc) {
    _m_start = _m_allocate(n);
    _m_finish = _m_start;
    _m_end_of_storage = _m_start + n;
  }
  /**:
   * @brief Destructor of _vector_base
   *
   * Release the memory allocated to the RAII pattern.
   */
  ~_vector_base() {
    _m_deallocate(_m_start, _m_end_of_storage - _m_start);
  }

  /**
   * @brief Allocate n amount of memory to allocator
   * @param n memory sie
   * @return start address of allocated memory space
   */
  T *_m_allocate(size_t n) { return _m_data_allocator.allocate(n); }
  /**
   * @brief Release allocated memory
   * @param p pointer
   * @param n size
   */
  void _m_deallocate(T *p, size_t n) { _m_data_allocator.deallocate(p, n); }

  /**
   * @brief Get vector allocator instance
   * @return Allocator
   */
  allocator_type get_allocator() const { return _m_data_allocator; }
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
class vector : protected _vector_base<T, Allocator> {
  typedef _vector_base<T, Allocator> Base;
  typedef vector<T, Allocator> vector_type;

 public:
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef ft::_vector_iterator<pointer> iterator;
  typedef ft::_vector_iterator<const_pointer> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

 protected:
  using Base::_m_data_allocator;
  using Base::_m_allocate;
  using Base::_m_deallocate;
  using Base::_m_start;
  using Base::_m_finish;
  using Base::_m_end_of_storage;

 public:
  /**
   * @brief empty container constructor
   * @param alloc allocator
   *
   * Constructs an empty container, with no elements.
   */
  explicit vector(const allocator_type &alloc = allocator_type()) : Base(alloc) {}
  /**
   * @brief fill constructor
   * @param n element size
   * @param val element value
   * @param alloc allocator
   *
   * Constructs a container with n elements. Each element is a copy of val.
   * vector(n), vector(n, val), vector(n, val, alloc) 다 가능한 형태의 생성자. default param 값을 지정해줌으로서.
   * _base(n, alloc) 함수를 통해서 alloc 을 통해 n 만큼의 벡터 메모리 공간을 할당받음
   * uninitialized_fill_n 함수를 통해서 새로 할당된 벡터 메모리 공간에 n 만큼 val 값을 채워줌
   */
  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type()) : Base(n, alloc) {
    _m_fill_elements_n(this->_m_start, n, val);
  }
  /**
   * @brief range constructor
   * @tparam InputIterator
   * @param first
   * @param last
   * @param alloc
   *
   * @todo assign 만들었을때 구현하기
   * Constructs a container with as many elements as the range [first,last),
   * with each element constructed from its corresponding element in that range, in the same order.
   * InputIterator 가 iterator 일때만 들어오도록 설정
   */
  template<class InputIterator>
  vector(InputIterator first,
         InputIterator last,
         const allocator_type &alloc = allocator_type(),
         typename ft::enable_if<ft::is_iterator<InputIterator>::value>::type * = 0) : Base(alloc) {
    _m_init_range(first, last, is_forward_iterator<InputIterator>());
  }
  /**
   * @brief copy constructor
   * @param x
   *
   * Constructs a container with a copy of each of the elements in x, in the same order.
   * 새로 생성된 벡터에 x 벡터의 값들을 uninitialized_copy 함수를 이용하여 복사한다. 값만 복사되고 메모리 복사는 일어나지 않는다.
   * _base(x.size(), x.get_allocator()) 함수를 통해서 새로 메모리 공간을 할당 받음
   * uninialized_copy 함수를 통해서 새로 할당 받은 메모리에 %x 벡터의 값들을 복사함
   */
  vector(const vector &x) : Base(x.size(), x.get_allocator()) {
    this->_m_finish = std::uninitialized_copy(x.begin(), x.end(), this->_m_start);
  }

  // destroy only erases the elements
  // todo : 메모리 관련 함수 만들어서 그거 이용해서 소멸해보기
  // 벡터 내부의 요소들을 destory 해주는 소멸자
  virtual ~vector() { _m_destroy_from_end(this->_m_start); };

  /**
   * @brief Vector assignment operator.
   * @param x
   * @return
   *
   * @todo 대입 연산자도 assign 을 이용해서 begin end 까지 할거기 때문에 assign 구현 후
   */
  vector &operator=(const vector &x) {
    if (this != &x) {
      assign(x.begin(), x.end());
    }
    return *this;
  }

  /* ****************************************************** */
  /*                      Iterators                         */
  /* ****************************************************** */

  /**
   * Returns iterator that points to the first element in the %vector
   */
  iterator begin() { return iterator(this->_m_start); };
  const_iterator begin() const { return const_iterator(this->_m_start); };

  /**
   * Returns iterator that points to the last element in the %vector
   */
  iterator end() { return iterator(this->_m_finish); };
  const_iterator end() const { return const_iterator(this->_m_finish); };

  /**
   * Returns reverse_iterator that points to one before the first element in the %vector
   */
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

  /**
   * Returns reverse_iterator that points to the last element in the %vector
   */
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

  /* ****************************************************** */
  /*                      Capacity                          */
  /* ****************************************************** */

  /**
   * @brief Returns the number of elements in the %vector
   * @return the number of elements
   */
  size_type size() const { return size_type(end() - begin()); }

  /**
   * @brief Returns the size() of the largest possible %vector.
   * @return size of largest possible %vector
   *
   * Returns the maximum number of elements that the vector can hold.
   * allocator 의 max_size 임 그거 리턴하면 됨
   */
  size_type max_size() const { return size_type(-1) / sizeof(value_type); }

  /**
   *
   * @param n
   * @param val
   *
   * 벡터의 크기를 바꾸는 함수
   * 새 크기가 기존 크기보다 작으면 초과분이 "제거"된다.
   * 새 크기가 기존 크기보다 크면 "재할당"이 일어난다.
   * 재할당 / 복사 가능
   * @todo test case 로 확인해보기
   */
  void resize(size_type n, value_type val = value_type()) {
    if (n < size()) {
      erase(begin() + n, end());
    } else {
      insert(end(), n - size(), val);
    }
  }

  /**
   * @brief the size of the storage space (vector allocated size)
   * @return the size of the storage space (vector allocated size)
   *
   * Returns the size of the storage space currently allocated for the vector,
   * expressed in terms of elements.
   * vector capacity 리턴해주는 함수
   */
  size_type capacity() const {
    return size_type(const_iterator(this->_m_end_of_storage) - begin());
  }

  /**
   * @brief Returns true if the %vector is empty.
   * @return true : empty, false : not empty
   *
   * 벡터가 비어있는지 확인 size 가 0인지 확인
   */
  bool empty() const { return begin() == end(); }

  /**
   * @brief 벡터 capacity 를 n 만큼 확보
   * @param n capacity size
   *
   * 벡터 capacity 가 n 이 되도록 만드는 함수
   * 용량이 증가 해야 하면 새로운 저장 공간을 재 할당 하고 기존 요소를 모두 새 공간 으로 복사
   * 재할당 / 복사 가능
   * @todo test
   */
  void reserve(size_type n) {
    // check %n length
    _length_check(n);
    // n 이 capacity 보다 크면 재할당 및 복사가 일어남
    if (n > capacity()) {
      _m_realloc(n);
    }
  }

  /* ****************************************************** */
  /*                   Element access                       */
  /* ****************************************************** */

  /**
   * @brief  Subscript access to the data contained in the %vector.
   * @param  n  The index of the element for which data should be accessed.
   * @return  Read/write reference to data.
   *
   * Returns a reference to the element at position n in the vector container.
   */
  reference operator[](size_type n) { return *(begin() + n); }
  /**
   * @brief  Subscript access to the data contained in the %vector.
   * @param  n  The index of the element for which data should be accessed.
   * @return  Read-only reference to data.
   *
   * Returns a reference to the element at position n in the vector container.
   */
  const_reference operator[](size_type n) const { return *(begin() + n); }

  /**
   * @brief Provides access to the data contained in the %vector
   * @param n index of the element
   * @return Read/Write data reference
   * @throw ft::out_of_range If %n is an invalid index
   *
   * 랜덤 액세스 처럼 접근할 수 있다.
   * Strong Guarantee - if an exception is thrown, there are no changes in the container.
   * It throws out_of_range if n is out of bounds.
   */
  reference at(size_type n) {
    _range_check(n);
    return (*this)[n];
  }

  /**
  * @brief Provides access to the data contained in the %vector
  * @param n index of the element
  * @return Read-only data reference
  * @throw ft::out_of_range If %n is an invalid index
  *
  * Strong Guarantee - if an exception is thrown, there are no changes in the container.
  * It throws out_of_range if n is out of bounds.
  */
  const_reference at(size_type n) const {
    _range_check(n);
    return (*this)[n];
  }

  /**
   * @brief Returns read/write reference to the data at the first element of the %vector.
   * @return Read/Write reference to the data at the first element of the %vector.
   *
   * Returns a reference to the first element in the vector.
   */
  reference front() { return *begin(); }
  /**
   * @brief Returns read-only (constant) reference to the data at the first element of the %vector.
   * @return Read-only reference to the data at the first element of the %vector.
   *
   * Returns a reference to the first element in the vector.
   */
  const_reference front() const { return *begin(); }

  /**
   * @brief Returns a read/write reference to the data at the last element of the %vector.
   * @return Read/Write data at the last element of vector
   */
  reference back() { return *(end() - 1); }

  /**
   * @brief Returns a read-only (constant) reference to the data at the last element of the %vector.
   * @return Read-only data at the last element of vector
   */
  const_reference back() const { return *(end() - 1); }

  /* ****************************************************** */
  /*                      Modifiers                          */
  /* ****************************************************** */

  /**
   * @brief Vector assign
   * @tparam InputIterator
   * @param first
   * @param last
   *
   * 백터에 새로 메모리 할당 / 복사 해줌
   * 메모리 할당 후 값 초기화
   * @todo 3등 구현함수
   */
  template<class InputIterator>
  void assign(InputIterator first,
              InputIterator last,
              typename ft::enable_if<ft::is_iterator<InputIterator>::value>::type * = 0) {
    _m_assign_dispatch(first, last, is_integral<InputIterator>());
  }

  /**
   *
   * @param n
   * @param val
   *
   * 벡터 n 번 만큼 요소반복 해서 data 넣어 주기
   * 재할당 / 복사 가능
   */
  void assign(size_type n, const value_type &val) {
    _m_fill_assign(n, val);
  }

  /**
   *
   * @param val
   * @todo 2등 구현 함수
   */
  void push_back(const value_type &val) {
    if (this->_m_finish != this->_m_end_of_storage) {
      _m_construct(this->_m_finish, val);
      ++this->_m_finish;
    } else {
      _m_insert_aux(end(), val);
    }
  }

  /**
   * 맨 뒤에 요소 삭제
   */
  void pop_back() {
    // todo 확인해봐야함
    _m_destroy_from_end(this->_m_finish - 1);
  }

  /**
   *
   * @param position
   * @param val
   * @return
   *
   * @see https://legacy.cplusplus.com/reference/vector/vector/insert/
   */
  // single element
  iterator insert(iterator position, const value_type &val) {
    return _m_insert_aux(position, val);
  }
  // fill
  // position 에 n 만큼 val 넣기
  void insert(iterator position, size_type n, const value_type &val) {
    _m_fill_insert(position, n, val);
  }
  // range
  // position 에 [first, last) 값 넣기
  template<class InputIterator>
  void insert(iterator position,
              InputIterator first,
              InputIterator last,
              typename ft::enable_if<ft::is_iterator<InputIterator>::value>::type * = 0) {
    _m_insert_dispatch(position, first, last, is_integral<InputIterator>());
  }

  /**
   * @brief  Remove element at given position.
   * @param  position  Iterator pointing to element to be erased.
   * @return  An iterator pointing to the next element (or end()).*
   *
   * 그 위치에 있는 함수 지워주는 함수
   * 다 지워주고 앞으로 땡겨주는 로직까지 처리해야함
   */
  iterator erase(iterator position) {
    pointer p = this->_m_start + (position - begin());
    _m_destroy(p);
    _m_relocate(position + 1, end(), p);
    return iterator(p);
  }

  /**
   * @brief  Remove a range of elements.
   * @param  first  Iterator pointing to the first element to be erased.
   * @param  last  Iterator pointing to one past the last element to be
   *               erased.
   * @return  An iterator pointing to the element pointed to by @a last
   *          prior to erasing (or end()).
   *
   * @todo --ep, ep-- 확인해보기 -> test 케이스 더 확인해봐야함
   */
  iterator erase(iterator first, iterator last) {
    pointer sp = this->_m_start + (first - begin());
    pointer ep = this->_m_start + (last - begin());

    while (sp != ep) {
      _m_destroy(--ep);
    }
    _m_relocate(last, end(), sp);
    return iterator(ep);
  }

  /**
   *
   * @param x
   */
  void swap(vector &x) {
    ft::swap(this->_m_start, x._m_start);
    ft::swap(this->_m_finish, x._m_finish);
    ft::swap(this->_m_end_of_storage, x._m_end_of_storage);
  }

  /**
   * @brief clear
   * 벡터의 모든 요소를 제거한다.
   * size 0 capacity 는 변하지 않는다.
   */
  void clear() { erase(begin(), end()); }

 protected:
  void _range_check(size_type n) const {
    if (n >= size()) {
      throw ft::out_of_range("vector");
    }
  }

  void _length_check(size_type n) const {
    if (n > max_size()) {
      throw ft::length_error("vector");
    }
  }

  /* ****************************************************** */
  /*               Memory util function                     */
  /* ****************************************************** */

  void _m_construct(T *p, const T &element) {
    this->_m_data_allocator.construct(p, element);
  }

  void _m_destroy(T *p) {
    this->_m_data_allocator.destroy(p);
  }

  void _m_destroy_from_end(T *p) {
    pointer _new_ep = _m_finish;
    while (p != _new_ep) {
      _m_destroy(--_new_ep);
    }
    // todo 이거 _m_finish 제대로 된 거 맞는지 확인하기
    this->_m_finish = _new_ep;
  }

  /**
 * @brief range_constructor 에서 불린다.
 * @tparam Integer
 * @param n
 * @param value
 *
 * range constructor 에서 iterator 받아서 내부 데이터를 초기화 해줄 때 사용하는 함수
 */
  template<class InputIterator>
  void _m_init_range(InputIterator first, InputIterator last, false_type) {
    // false_type -> input_iterator 일 때
    for (; first != last; ++first) {
      push_back(*first);
    }
  }

  template<class ForwardIterator>
  void _m_init_range(ForwardIterator first, ForwardIterator last, true_type) {
    // forward iterator 일 때
    size_type n = std::distance(first, last);
    this->_m_start = _m_allocate(n);
    this->_m_end_of_storage = this->_m_start + n;
    this->_m_finish = std::uninitialized_copy(first, last, this->_m_start);
  }

  // move mem data to x vector
  void _m_move(vector &x) {
    x._m_start = this->_m_start;
    x._m_finish = this->_m_finish;
    x._m_end_of_storage = this->_m_end_of_storage;
    this->_m_start = NULL;
    this->_m_finish = NULL;
    this->_m_end_of_storage = NULL;
  }

  // first 부터 x 를 n 만큼 채워넣어준다.
  // this->_m_finish += n 만큼 추가해준다. => first 에 들어오면 iterator 는 무조건 vector 의 iterator 여야 한다.
  template<class ForwardIterator, class Size, class U>
  void _m_fill_elements_n(ForwardIterator first, Size n, const U &x) {
    std::uninitialized_fill_n(first, n, x);
    this->_m_finish += n;
  }

  template<class InputIterator, class OutputIterator>
  void _m_relocate(InputIterator first, InputIterator last, OutputIterator result) {
    this->_m_finish = ft::copy(first, last, result);
  }

  void _m_realloc(size_t n) {
    pointer _new_start;
    try {
      _new_start = _m_allocate(n);
      this->_m_finish = ft::copy(this->_m_start, this->_m_finish, _new_start);
      _m_deallocate(this->_m_start, capacity());
      this->_m_start = _new_start;
      this->_m_end_of_storage = this->_m_start + n;
    } catch (std::exception &e) {
      _m_deallocate(_new_start, n);
      throw e;
    }
  }

  // delete every elements and reinit vector
  void _m_reinit(size_t n) {
    pointer _new_start;
    try {
      clear();
      _new_start = _m_allocate(n);
      _m_deallocate(this->_m_start, capacity());
      this->_m_start = _new_start;
      this->_m_finish = this->_m_start;
      this->_m_end_of_storage = this->_m_start + n;
    } catch (std::exception &e) {
      _m_deallocate(_new_start, n);
      throw e;
    }
  }

  /* ****************************************************** */
  /*              Internal assign function                  */
  /* ****************************************************** */

  template<class Integer>
  void _m_assign_dispatch(Integer n, Integer val, true_type) {
    _m_fill_assign(static_cast<size_type>(n), static_cast<value_type>(val));
  }

  template<class InputIterator>
  void _m_assign_dispatch(InputIterator first, InputIterator last, false_type) {
    _m_assign_aux(first, last, is_forward_iterator<InputIterator>());
  }

  template<class InputIterator>
  void _m_assign_aux(InputIterator first, InputIterator last, false_type) {
    // input iterator_traits assign logic
    clear();
    // @todo ++first 붙이는 이유 first++ 하는거 확인해보기
    for (; first != last; first++) {
      push_back(*first);
    }
  }

  template<class FowardIterator>
  void _m_assign_aux(FowardIterator first, FowardIterator last, true_type) {
    // foward iterator_traits assign logic
    size_type _n = std::distance(first, last);
    if (_n > capacity()) {
      _m_reinit(_n);
      this->_m_finish = std::uninitialized_copy(first, last, this->_m_start);
    } else {
      clear();
      this->_m_finish = std::uninitialized_copy(first, last, this->_m_start);
    }
  }

  // Called by assign(n, t)
  void _m_fill_assign(size_type n, const value_type &val) {
    if (n > capacity()) {
      _m_reinit(n);
      _m_fill_elements_n(this->_m_start, n, val);
    } else {
      clear();
      _m_fill_elements_n(this->_m_start, n, val);
    }
  }
  // _m_assign_dispatch -> assign(InputIter first, InputIter last) 에서 사용
  // _m_assign_dispatch(Integer n, Integer val, true_type)
  // _m_fill_assign -> assign(n, val) 에서 사용

  // assign 함수 구현
  // 1. assgin(size_type n, const value_type &val) -> _m_fill_assign(n, val) 로 바로 값 채워줌
  // 2. assign(InputIter first, InputIter last) -> _m_assign_dispatch(first, last, is_integer<InputIter>
  // 2-1.InputIterator -> _m_assign_aux()

  /* ****************************************************** */
  /*              Internal insert function                  */
  /* ****************************************************** */

  // range insert
  template<class Integer>
  void _m_insert_dispatch(iterator position, Integer n, Integer val, true_type) {
    // integer 일 때
    _m_fill_insert(position, static_cast<size_type>(n), static_cast<value_type>(val));
  }

  template<class InputIterator>
  void _m_insert_dispatch(iterator position, InputIterator first, InputIterator last, false_type) {
    // iterator 일 때
    _m_range_insert(position, first, last, is_forward_iterator<InputIterator>());
  }

  template<class InputIterator>
  void _m_range_insert(iterator position, InputIterator first, InputIterator last, false_type) {
    // input_iterator 일 때
    difference_type _pos_idx = position - begin();
    for (; first != last; first++) {
      // 재할당이 일어날 수 있음 -> position 이 무효화 됨
      insert(begin() + _pos_idx++, first);
    }
  }

  template<class ForwardIterator>
  void _m_range_insert(iterator position, ForwardIterator first, ForwardIterator last, true_type) {
    // forward_iterator 일 때
    // input iterator 는 it - it 를 지원하지 않음
    // std::distance 를 쓰면 If InputIterator is not at least a forward iterator, first and any iterators, pointers and references obtained from its value may be invalidated.
    // 위와 같은 위험이 있음
    size_type _n = size() + std::distance(first, last);
    difference_type _pos_idx = position - begin();
    if (_n > capacity()) {
      vector _tmp;
      _tmp._m_start = _tmp._m_allocate(_n);
      _tmp._m_finish = std::uninitialized_copy(this->_m_start, this->_m_start + _pos_idx, _tmp._m_start);
      _tmp._m_finish = std::uninitialized_copy(first, last, _tmp._m_finish);
      _tmp._m_finish = std::uninitialized_copy(this->_m_start + _pos_idx, this->_m_finish, _tmp._m_finish);
      _tmp._m_end_of_storage = _tmp._m_start + _n;
      _tmp._m_move(*this);
    } else {
      pointer _copy_ep = this->_m_finish + _n;
      pointer _copy_sp = this->_m_start + _pos_idx;
      while (_copy_ep != _copy_sp) {
        *_copy_ep = *(_copy_ep - _n);
        _copy_ep--;
      }
      this->_m_finish += _n;
      std::uninitialized_copy(first, last, _copy_sp);
    }
  }

  iterator _m_fill_insert(iterator position, size_type n, const value_type &val) {
    // position 위치에 n 만틈 val 삽입해주기
    size_type _n = size() + n;
    difference_type _pos_idx = position - begin();
    if (_n > capacity()) {
      vector _tmp;
      _tmp._m_start = _tmp._m_allocate(_n);
      _tmp._m_finish = std::uninitialized_copy(this->_m_start, this->_m_start + _pos_idx, _tmp._m_start);
      _tmp._m_fill_elements_n(_tmp._m_finish, n, val);
      _tmp._m_finish = std::uninitialized_copy(this->_m_start + _pos_idx, this->_m_finish, _tmp._m_finish);
      _tmp._m_end_of_storage = _tmp._m_start + _n;
      _tmp._m_move(*this);
    } else {
      pointer _copy_ep = this->_m_finish + n;
      pointer _copy_sp = this->_m_start + _pos_idx;
      while (_copy_ep != _copy_sp) {
        *_copy_ep = *(_copy_ep - n);
        _copy_ep--;
      }
      _m_fill_elements_n(_copy_sp, n, val);
    }
    return iterator(this->_m_start + _pos_idx);
  }

  // Called by insert(p, x)
  iterator _m_insert_aux(iterator position, const value_type &val) {
    return _m_fill_insert(position, 1, val);
  }

}; // vector

/**
 *  @brief  Vector equality comparison.
 *  @param  lhs  A %vector.
 *  @param  rhs  A %vector of the same type as @a lhs.
 *  @return  True iff the size and elements of the vectors are equal.
 *
 *  This is an equivalence relation.  It is linear in the size of the
 *  vectors.  Vectors are considered equivalent if their sizes are equal,
 *  and if corresponding elements compare equal.
 */
template<class T, class Alloc>
bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<class T, class Alloc>
bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(lhs == rhs);
}

template<class T, class Alloc>
bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<class T, class Alloc>
bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(rhs < lhs);
}

template<class T, class Alloc>
bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return (rhs < lhs);
}

template<class T, class Alloc>
bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(lhs < rhs);
}

template<class T, class Alloc>
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {
  x.swap(y);
}

}; // namespace ft

#endif //VECTOR_HPP_
