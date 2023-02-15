/*
 * File: function.hpp
 * Project: ft_container
 * Created Date: 2023/02/15
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

namespace ft {

template<typename Arg, typename Result>
struct unary_function {
  typedef Arg argument_type;
  typedef Result result_type;
};

template<class Pair>
struct Select1st : public unary_function<Pair, typename Pair::first_type> {
  typename Pair::first_type &operator()(Pair &x) const {
    return x.first;
  }
  const typename Pair::first_type &operator()(const Pair &x) const {
    return x.first;
  }
};

template<class Pair>
struct Select2nd : public unary_function<Pair, typename Pair::second_type> {
  typename Pair::second_type &operator()(Pair &x) const {
    return x.second;
  }
  const typename Pair::second_type &operator()(const Pair &x) const {
    return x.second;
  }
};
}

#endif //FUNCTION_HPP_
