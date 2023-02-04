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
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

// 나중에 지우기
#include <vector>

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
  _vector_iterator() : _it() {}
  explicit _vector_iterator(const Iter &it) : _it(it) {}
  template<typename U>
  explicit _vector_iterator(const _vector_iterator<U> &u) : _it(u.base()) {}

  // member functions
  iterator_type base() const { return _it; }
  reference operator*() const {
    Iter tmp = _it;
    return *--tmp;
  } // *rit
  _vector_iterator operator+(difference_type n) const {
    return _vector_iterator(_it - n);
  } // rit + n
  _vector_iterator &operator++() {
    --_it;
    return *this;
  } // ++rit
  _vector_iterator operator++(int) {
    _vector_iterator tmp(*this);
    --_it;
    return tmp;
  } // rit++
  _vector_iterator &operator--() {
    ++_it;
    return *this;
  } // --rit
  _vector_iterator operator--(int) {
    _vector_iterator tmp(*this);
    ++_it;
    return tmp;
  } // rit--
  _vector_iterator &operator+=(difference_type n) {
    _it -= n;
    return *this;
  }
  _vector_iterator operator-(difference_type n) const {
    return _vector_iterator(_it + n);
  } // rit - n
  _vector_iterator &operator-=(difference_type n) {
    _it += n;
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
  return lhs.base() > rhs.base();
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
  return _vector_iterator<Iter>(rev_it.base() - n);
} // n + rit

// operator- (_vector_iterator)
template<class Iter>
_vector_iterator<Iter> operator-(typename _vector_iterator<Iter>::difference_type n,
                                 const _vector_iterator<Iter> &rev_it) {
  return _vector_iterator<Iter>(rev_it.base + n);
}

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
  T *_m_start;
  T *_m_finish;
  T *_m_end_of_storage;

 public:
  /**
   * @brief Default _vector_base constructor
   * @param a allocator
   */
  explicit _vector_base(const allocator_type &a)
      : _m_data_allocator(a), _m_start(NULL), _m_finish(NULL), _m_end_of_storage(NULL) {}
  /**
   * @brief Constructor that allocates memory as large as n
   * @param n memory size
   * @param a allocator
   */
  explicit _vector_base(size_t n, const allocator_type &a) : _m_data_allocator(a) {
    _m_start = _m_allocate(n);
    _m_finish = _m_start;
    _m_end_of_storage = _m_start + n;
  }
  /**
   * @brief Destructor of _vector_base
   *
   * Release the memory allocated to the RAII pattern.
   */
  ~_vector_base() {
    _m_deallocate(_m_start, _m_end_of_storage - _m_start);
  }

  /**
   * @brief Allocate n amount of memory to allocator
   * @param n memory size
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
   *
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
  typedef _vector_base<T, Allocator> base_type;
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
  using base_type::_m_allocate;
  using base_type::_m_deallocate;
  using base_type::_m_start;
  using base_type::_m_finish;
  using base_type::_m_end_of_storage;

 public:
  /**
   * @brief empty container constructor
   * @param alloc allocator
   *
   * Constructs an empty container, with no elements.
   */
  explicit vector(const allocator_type &alloc = allocator_type()) {}
  /**
   * @brief fill constructor
   * @param n element size
   * @param val element value
   * @param alloc allocator
   *
   * @todo 얘 1등
   * Constructs a container with n elements. Each element is a copy of val.
   */
  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type()) {}
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
   */
  template<class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type &alloc = allocator_type()) {}
  /**
   * @brief copy constructor
   * @param x
   *
   * Constructs a container with a copy of each of the elements in x, in the same order.
   * @todo 2등으로 구현하고 저 위에 있는 생성자는 나중에 구현하기 type_traits
   */
  vector(const vector &x) {}

  // destroy only erases the elements
  // todo : 걍 쉽게 구현 가능
  virtual ~vector() {};

  /**
   * @brief Vector assignment operator.
   * @param x
   * @return
   *
   * @todo 대입 연산자도 assign 을 이용해서 begin end 까지 할거기 때문에 assign 구현 후
   */
  vector &operator=(const vector &x) {}

  /**
   *
   * @param n
   * @return
   *
   * Returns a reference to the element at position n in the vector container.
   */
  reference operator[](size_type n) {}
  const_reference operator[] (size_type n) const

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
  void assign(InputIterator first, InputIterator last) {}

  /**
   *
   * @param n
   * @param val
   *
   * 벡터 n 번 만큼 요소반복 해서 data 넣어 주기
   * 재할당 / 복사 가능
   */
  void assign(size_type n, const value_type &val) {}

  /**
   * @brief 벡터 capacity 를 n 만큼 확보
   * @param n
   *
   * 벡터 capacity 가 n 이 되도록 만드는 함수
   * 용량이 증가 해야 하면 새로운 저장 공간을 재 할당 하고 기존 요소를 모두 새 공간 으로 복사
   * 재할당 / 복사 가능
   * @todo 첫번째로 구현하기
   */
  void reserve(size_type n) {}

  /**
   *
   * @param n
   * @param val
   *
   * 벡터의 크기를 바꾸는 함수
   * 새 크기가 기존 크기보다 작으면 초과분이 제거된다.
   * 새 크기가 기존 크기보다 크면 재할당이 일어난다.
   * 재할당 / 복사 가능
   */
  void resize(size_type n, value_type val = value_type()) {}

  /**
   * @brief clear
   * 벡터의 모든 요소를 제거한다.
   * size 0 capacity 는 변하지 않는다.
   */
  void clear() {}

  /**
   *
   * @param n
   * @return
   *
   * 랜덤 액세스 처럼 접근할 수 있다.
   */
  reference at(size_type n) {}

  /**
   *
   * @param n
   * @return
   *
   * 랜덤 액세스처럼 at(i) 로 접근 가눙
   * out_of_range 예외처리 해줘야 함
   * 반대로 꺽쇠는 예외처리 안해줘도 됨 ㅎㅋㅎㅋ
   */
  const_reference at(size_type n) const;

  /**
   *
   * @return
   *
   * 끝에 있는애 주소값 주는 애여서 걍 심심하면 구현하셈 개 쉬움 (by san)
   */
  reference back() {}
  const_reference back() const {}

  /**
   *
   * @return
   */
  iterator begin();
  const_iterator begin() const;

  /**
   *
   * @return
   *
   * iterator 맨 뒤에 있는거 반환
   */
  iterator end();
  const_iterator end() const;

  /**
   *
   * @return
   *
   * Returns the size of the storage space currently allocated for the vector,
   * expressed in terms of elements.
   * vector capacity 리턴해주는 함수
   */
  size_type capacity() const {}

  /**
   *
   * @return
   *
   * 벡터가 비어있는지 확인 size 가 0인지 확인
   */
  bool empty() const {}

  /**
   *
   * @param position
   * @return
   *
   * 그 위치에 있는 함수 지워주는 함수
   * 다 지워주고 앞으로 땡겨주는 로직까지 처리해야함
   * 리턴값이 좀 이상해서 확인요망 지워준 그 자리를 리턴
   */
  iterator erase(iterator position) {}
  iterator erase(iterator first, iterator last) {}

  /**
   *
   * @return
   *
   * Returns a reference to the first element in the vector.
   */
  reference front();
  const_reference front() const;

  /**
   *
   * @param val
   * @todo 2등 구현 함수
   */
  void push_back(const value_type &val) {}

  /**
   *
   * @param position
   * @param val
   * @return
   *
   * @see https://legacy.cplusplus.com/reference/vector/vector/insert/
   */
  iterator insert(iterator position, const value_type &val) {}
  void insert(iterator position, size_type n, const value_type &val) {}
  template<class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {}

  /**
   *
   * @return
   *
   * Returns the maximum number of elements that the vector can hold.
   * allocator 의 max_size 임 그거 리턴하면 됨
   */
  size_type max_size() const {}

  /**
   * 맨 뒤에 요소 삭제
   */
  void pop_back() {}

  /**
   *
   * @return
   *
   * Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning)
   */
  reverse_iterator rbegin() {}
  const_reverse_iterator rbegin() const {}

  /**
   *
   * @return
   */
  reverse_iterator rend() {}
  const_reverse_iterator rend() const {}

  /**
   *
   * @return
   */
  size_type size() const {}

  /**
   *
   * @param x
   */
  void swap (vector& x) {}
};

}; // namespace ft

#endif //VECTOR_HPP_
