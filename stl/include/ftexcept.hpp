/*
 * File: ftexcept.hpp
 * Project: ft_container
 * Created Date: 2023/02/05
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef FTEXCEPT_HPP_
#define FTEXCEPT_HPP_

#include <exception>

namespace ft {
class out_of_range : public std::exception {
  const char *_target;
 public:
  out_of_range(const char *target) throw(): _target(target) {}

  const char *what() const throw() {
    return _target;
  }
};

class length_error : public std::exception {
  const char *_target;
 public:
  length_error(const char *target) throw(): _target(target) {}

  const char *what() const throw() {
    return _target;
  }
};
}; // namespace ft

#endif //FTEXCEPT_HPP_
