/*
 * File: main.cpp
 * Project: ft_container
 * Created Date: 2023/02/26
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#include <sys/time.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

#include "../include/map.hpp"
#include "../include/stack.hpp"
#include "../include/vector.hpp"

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define RESET "\033[0m"
#define GRAY "\033[1;30m"
#define BOLD "\033[1m"

typedef long long ll;

#define SECONDS 1000000LL

#define VEC_SIZE 1000
#define STACK_SIZE 1000
#define MAP_SIZE 100

ll get_time(timeval start, timeval end) {
  return ((end.tv_sec - start.tv_sec) * SECONDS + (end.tv_usec - start.tv_usec));
}

int main(void) {
  timeval ft_start;
  timeval ft_end;
  timeval std_start;
  timeval std_end;
  ll ft_time;
  ll std_time;

  // vector
  std::cout << CYAN << BOLD << "\n\n============= vector ==============n\n" << RESET << std::endl;
  // vector push_back
  std::cout << YELLOW << BOLD << "------------- vector push_back -------------" << RESET
            << std::endl;
  /* ft::vector push_back */
  gettimeofday(&ft_start, NULL);
  {
    ft::vector<int> vector_int;
    vector_int.reserve(VEC_SIZE);
    for (int i = 0; i < VEC_SIZE; i++) vector_int.push_back(i);
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);
  /* ft::vector output */
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;

  /* std::vector push_back */
  gettimeofday(&std_start, NULL);
  {
    std::vector<int> std_vector_int;
    std_vector_int.reserve(VEC_SIZE);
    for (int i = 0; i < VEC_SIZE; i++) std_vector_int.push_back(i);
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);

  /* std::vector output */
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::vector - push_back is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::vector - push_back is OK" << RESET << std::endl;

  // vector pop_back
  std::cout << YELLOW << BOLD << "------------- vector pop_back -------------" << RESET
            << std::endl;
  /* ft::vector pop_back */
  gettimeofday(&ft_start, NULL);
  {
    ft::vector<int> vector_int(VEC_SIZE, 0);
    for (int i = 0; i < VEC_SIZE; i++) vector_int.pop_back();
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);
  /* ft::vector output */
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;

  /* std::vector pop_back */
  gettimeofday(&std_start, NULL);
  {
    std::vector<int> std_vector_int(VEC_SIZE, 0);
    for (int i = 0; i < VEC_SIZE; i++) std_vector_int.pop_back();
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);

  /* std::vector output */
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::vector - pop_back is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::vector - pop_back is OK" << RESET << std::endl;
  // vector insert
  std::cout << YELLOW << BOLD << "------------- vector insert -------------" << RESET << std::endl;
  /* ft::vector insert */
  gettimeofday(&ft_start, NULL);
  {
    ft::vector<int> vector_int;
    for (int i = 0; i < 10; i++) vector_int.insert(vector_int.begin(), i);
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);
  /* ft::vector output */
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  /* std::vector insert */
  gettimeofday(&std_start, NULL);
  {
    std::vector<int> std_vector_int;
    for (int i = 0; i < VEC_SIZE; i++) std_vector_int.insert(std_vector_int.begin(), i);
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);

  /* std::vector output */
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::vector - insert is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::vector - insert is OK" << RESET << std::endl;

  // vector erase
  std::cout << YELLOW << BOLD << "------------- vector erase -------------" << RESET << std::endl;
  /* ft::vector erase */
  gettimeofday(&ft_start, NULL);
  {
    ft::vector<int> vector_int(VEC_SIZE, 0);
    for (int i = 0; i < VEC_SIZE; i++) vector_int.erase(vector_int.begin());
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);
  /* ft::vector output */
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  /* std::vector erase */
  gettimeofday(&std_start, NULL);
  {
    std::vector<int> std_vector_int(VEC_SIZE, 0);
    for (int i = 0; i < VEC_SIZE; i++) std_vector_int.erase(std_vector_int.begin());
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);

  /* std::vector output */
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
  if (std_time && ft_time > 20 * std_time) {
  } else
    std::cout << GREEN << BOLD << "ft::vector - erase is OK" << RESET << std::endl;

  // vector swap
  std::cout << YELLOW << BOLD << "------------- vector swap -------------" << RESET << std::endl;
  /* ft::vector swap */
  gettimeofday(&ft_start, NULL);
  {
    ft::vector<int> vector_int(VEC_SIZE, 0);
    ft::vector<int> vector_int2(VEC_SIZE, 0);
    for (int i = 0; i < VEC_SIZE; i++) vector_int.swap(vector_int2);
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);
  /* ft::vector output */
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  /* std::vector swap */
  gettimeofday(&std_start, NULL);
  {
    std::vector<int> std_vector_int(VEC_SIZE, 0);
    std::vector<int> std_vector_int2(VEC_SIZE, 0);
    for (int i = 0; i < VEC_SIZE; i++) std_vector_int.swap(std_vector_int2);
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);

  /* std::vector output */
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::vector - swap is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::vector - swap is OK" << RESET << std::endl;

  // vector clear
  std::cout << YELLOW << BOLD << "------------- vector clear -------------" << RESET << std::endl;
  /* ft::vector clear */
  gettimeofday(&ft_start, NULL);
  {
    ft::vector<int> vector_int(VEC_SIZE, 0);
    for (int i = 0; i < VEC_SIZE; i++) vector_int.clear();
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);
  /* ft::vector output */
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  /* std::vector clear */
  gettimeofday(&std_start, NULL);
  {
    std::vector<int> std_vector_int(VEC_SIZE, 0);
    for (int i = 0; i < VEC_SIZE; i++) std_vector_int.clear();
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);

  /* std::vector output */
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::vector - clear is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::vector - clear is OK" << RESET << std::endl;

  // vector relational operators
  std::cout << YELLOW << BOLD << "------------- vector relational operators -------------" << RESET
            << std::endl;
  /* ft::vector relational operators */
  gettimeofday(&ft_start, NULL);
  {
    ft::vector<int> vector_int(VEC_SIZE, 0);
    ft::vector<int> vector_int2(VEC_SIZE, 0);
    for (int i = 0; i < VEC_SIZE; i++)
      if (vector_int != vector_int2) {
        std::cout << RED << BOLD << "ft::vector - relational operators is wrong" << RESET
                  << std::endl;
        //
      }
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);
  /* ft::vector output */
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  /* std::vector relational operators */
  gettimeofday(&std_start, NULL);
  {
    std::vector<int> std_vector_int(VEC_SIZE, 0);
    std::vector<int> std_vector_int2(VEC_SIZE, 0);
    for (int i = 0; i < VEC_SIZE; i++) {
      if (std_vector_int != std_vector_int2) {
        std::cout << RED << BOLD << "std::vector - relational operators is wrong" << RESET
                  << std::endl;
        //
      }
    }
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);

  /* std::vector output */
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::vector - relational operators is "
              << (double) ft_time / std_time << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::vector - relational operators is OK" << RESET << std::endl;

  // vector iterator
  std::cout << YELLOW << BOLD << "------------- vector iterator -------------" << RESET
            << std::endl;
  /* ft::vector iterator */
  gettimeofday(&ft_start, NULL);
  {
    ft::vector<int> vector_int(VEC_SIZE, 0);
    ft::vector<int>::iterator it = vector_int.begin();
    ft::vector<int>::iterator ite = vector_int.end();
    for (; it != ite; it++) *it = 0;
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);
  /* ft::vector output */
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  /* std::vector iterator */
  gettimeofday(&std_start, NULL);
  {
    std::vector<int> std_vector_int(VEC_SIZE, 0);
    std::vector<int>::iterator it = std_vector_int.begin();
    std::vector<int>::iterator ite = std_vector_int.end();
    for (; it != ite; it++) *it = 0;
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);

  /* std::vector output */
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::vector - iterator is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::vector - iterator is OK" << RESET << std::endl;

  // vector reverse iterator
  std::cout << YELLOW << BOLD << "------------- vector reverse iterator -------------" << RESET
            << std::endl;
  /* ft::vector reverse iterator */
  gettimeofday(&ft_start, NULL);
  {
    ft::vector<int> vector_int(VEC_SIZE, 0);
    ft::vector<int>::reverse_iterator it = vector_int.rbegin();
    ft::vector<int>::reverse_iterator ite = vector_int.rend();
    for (; it != ite; it++) *it = 0;
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);
  /* ft::vector output */
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  /* std::vector reverse iterator */
  gettimeofday(&std_start, NULL);
  {
    std::vector<int> std_vector_int(VEC_SIZE, 0);
    std::vector<int>::reverse_iterator it = std_vector_int.rbegin();
    std::vector<int>::reverse_iterator ite = std_vector_int.rend();
    for (; it != ite; it++) *it = 0;
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);

  /* std::vector output */
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::vector - reverse iterator is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::vector - reverse iterator is OK" << RESET << std::endl;

  // vector capacity
  std::cout << YELLOW << BOLD << "------------- vector capacity -------------" << RESET
            << std::endl;
  /* ft::vector capacity */
  gettimeofday(&ft_start, NULL);
  {
    ft::vector<int> vector_int;
    vector_int.reserve(VEC_SIZE);
    for (int i = 0; i < VEC_SIZE; i++) vector_int.push_back(i);
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);
  /* ft::vector output */
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  /* std::vector capacity */
  gettimeofday(&std_start, NULL);
  {
    std::vector<int> std_vector_int;
    std_vector_int.reserve(VEC_SIZE);
    for (int i = 0; i < VEC_SIZE; i++) std_vector_int.push_back(i);
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);

  /* std::vector output */
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::vector - capacity is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::vector - capacity is OK" << RESET << std::endl;

  // vector element access
  std::cout << YELLOW << BOLD << "------------- vector element access -------------" << RESET
            << std::endl;
  /* ft::vector element access */
  gettimeofday(&ft_start, NULL);
  {
    ft::vector<int> vector_int(VEC_SIZE, 0);
    for (int i = 0; i < VEC_SIZE; i++) vector_int[i] = i;
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);

  /* ft::vector output */
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  /* std::vector element access */
  gettimeofday(&std_start, NULL);
  {
    std::vector<int> std_vector_int(VEC_SIZE, 0);
    for (int i = 0; i < VEC_SIZE; i++) std_vector_int[i] = i;
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);

  /* std::vector output */
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::vector - element access is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::vector - element access is OK" << RESET << std::endl;

  // vector modifiers
  std::cout << YELLOW << BOLD << "------------- vector modifiers -------------" << RESET
            << std::endl;

  /* ft::vector modifiers */
  gettimeofday(&ft_start, NULL);
  {
    ft::vector<int> vector_int;
    vector_int.reserve(VEC_SIZE);
    for (int i = 0; i < VEC_SIZE; i++) vector_int.push_back(i);
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);

  /* ft::vector output */
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  /* std::vector modifiers */
  gettimeofday(&std_start, NULL);
  {
    std::vector<int> std_vector_int;
    std_vector_int.reserve(VEC_SIZE);
    for (int i = 0; i < VEC_SIZE; i++) std_vector_int.push_back(i);
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);

  /* std::vector output */
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::vector - modifiers is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::vector - modifiers is OK" << RESET << std::endl;

  // STACK TEST

  std::cout << CYAN << BOLD << "\n\n============= stack =============\n\n" << RESET << std::endl;

  // stack push
  std::cout << YELLOW << BOLD << "------------- stack push -------------" << RESET << std::endl;
  gettimeofday(&ft_start, NULL);
  {
    ft::stack<int> stack_int;
    for (int i = 0; i < STACK_SIZE; i++) stack_int.push(i);
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);

  gettimeofday(&std_start, NULL);
  {
    std::stack<int> std_stack_int;
    for (int i = 0; i < STACK_SIZE; i++) std_stack_int.push(i);
  }
  gettimeofday(&std_end, NULL);
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::stack - push is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::stack - push is OK" << RESET << std::endl;

  // stack pop
  std::cout << YELLOW << BOLD << "------------- stack pop -------------" << RESET << std::endl;

  gettimeofday(&ft_start, NULL);
  {
    ft::stack<int> stack_int;
    for (int i = 0; i < STACK_SIZE; i++) stack_int.push(i);
    for (int i = 0; i < STACK_SIZE; i++) stack_int.pop();
  }

  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);

  gettimeofday(&std_start, NULL);
  {
    std::stack<int> std_stack_int;
    for (int i = 0; i < STACK_SIZE; i++) std_stack_int.push(i);
    for (int i = 0; i < STACK_SIZE; i++) std_stack_int.pop();
  }
  gettimeofday(&std_end, NULL);
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::stack - pop is " << (double) ft_time / std_time << " times slow"
              << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::stack - pop is OK" << RESET << std::endl;

  // stack top
  std::cout << YELLOW << BOLD << "------------- stack top -------------" << RESET << std::endl;

  gettimeofday(&ft_start, NULL);
  {
    ft::stack<int> stack_int;
    for (int i = 0; i < STACK_SIZE; i++) stack_int.push(i);
    for (int i = 0; i < STACK_SIZE; i++) stack_int.top();
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);

  gettimeofday(&std_start, NULL);
  {
    std::stack<int> std_stack_int;
    for (int i = 0; i < STACK_SIZE; i++) std_stack_int.push(i);
    for (int i = 0; i < STACK_SIZE; i++) std_stack_int.top();
  }
  gettimeofday(&std_end, NULL);
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::stack - top is " << (double) ft_time / std_time << " times slow"
              << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::stack - top is OK" << RESET << std::endl;

  // stack empty
  std::cout << YELLOW << BOLD << "------------- stack empty -------------" << RESET << std::endl;

  gettimeofday(&ft_start, NULL);
  {
    ft::stack<int> stack_int;
    for (int i = 0; i < STACK_SIZE; i++) stack_int.push(i);
    for (int i = 0; i < STACK_SIZE; i++) stack_int.pop();
    if (!stack_int.empty())
      std::cout << RED << BOLD << "ft::stack - empty is not OK" << RESET << std::endl;
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);

  gettimeofday(&std_start, NULL);
  {
    std::stack<int> std_stack_int;
    for (int i = 0; i < STACK_SIZE; i++) std_stack_int.push(i);
    for (int i = 0; i < STACK_SIZE; i++) std_stack_int.pop();
    if (!std_stack_int.empty())
      std::cout << RED << BOLD << "std::stack - empty is not OK" << RESET << std::endl;
  }
  gettimeofday(&std_end, NULL);
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::stack - empty is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::stack - empty is OK" << RESET << std::endl;

  // stack relational operators
  std::cout << YELLOW << BOLD << "------------- stack relational operators -------------" << RESET
            << std::endl;

  gettimeofday(&ft_start, NULL);
  {
    ft::stack<int> stack_int;
    ft::stack<int> stack_int2;
    for (int i = 0; i < STACK_SIZE; i++) stack_int.push(i);
    for (int i = 0; i < STACK_SIZE; i++) stack_int2.push(i);
    if (stack_int != stack_int2)
      std::cout << RED << BOLD << "ft::stack - relational operators is not OK" << RESET
                << std::endl;
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);

  gettimeofday(&std_start, NULL);
  {
    std::stack<int> std_stack_int;
    std::stack<int> std_stack_int2;
    for (int i = 0; i < STACK_SIZE; i++) std_stack_int.push(i);
    for (int i = 0; i < STACK_SIZE; i++) std_stack_int2.push(i);
    if (std_stack_int != std_stack_int2)
      std::cout << RED << BOLD << "std::stack - relational operators is not OK" << RESET
                << std::endl;
  }
  gettimeofday(&std_end, NULL);
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::stack - relational operators is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::stack - relational operators is OK" << RESET << std::endl;

  // MAP TEST

  std::cout << CYAN << BOLD << "\n\n============= map ==============n\n" << RESET << std::endl;
  // map insert
  std::cout << YELLOW << BOLD << "------------- map insert -------------" << RESET << std::endl;
  gettimeofday(&ft_start, NULL);
  {
    ft::map<int, int> map_int;
    for (int i = 0; i < MAP_SIZE; i++) map_int.insert(ft::make_pair(i, i));
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);

  gettimeofday(&std_start, NULL);
  {
    std::map<int, int> std_map_int;
    for (int i = 0; i < MAP_SIZE; i++) std_map_int.insert(std::make_pair(i, i));
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::map - insert is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::map - insert is OK" << RESET << std::endl;

  // map find
  std::cout << YELLOW << BOLD << "------------- map find -------------" << RESET << std::endl;
  gettimeofday(&ft_start, NULL);
  {
    ft::map<int, int> map_int;
    for (int i = 0; i < MAP_SIZE; i++) map_int.insert(ft::make_pair(i, i));
    for (int i = 0; i < MAP_SIZE; i++) map_int.find(i);
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);

  gettimeofday(&std_start, NULL);
  {
    std::map<int, int> std_map_int;
    for (int i = 0; i < MAP_SIZE; i++) std_map_int.insert(std::make_pair(i, i));
    for (int i = 0; i < MAP_SIZE; i++) std_map_int.find(i);
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::map - find is " << (double) ft_time / std_time << " times slow"
              << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::map - find is OK" << RESET << std::endl;

  // map erase
  std::cout << YELLOW << BOLD << "------------- map erase -------------" << RESET << std::endl;
  gettimeofday(&ft_start, NULL);
  {
    ft::map<int, int> map_int;
    for (int i = 0; i < MAP_SIZE; i++) map_int.insert(ft::make_pair(i, i));
    for (int i = 0; i < MAP_SIZE; i++) map_int.erase(i);
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);

  gettimeofday(&std_start, NULL);
  {
    std::map<int, int> std_map_int;
    for (int i = 0; i < MAP_SIZE; i++) std_map_int.insert(std::make_pair(i, i));
    for (int i = 0; i < MAP_SIZE; i++) std_map_int.erase(i);
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::map - erase is " << (double) ft_time / std_time << " times slow"
              << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::map - erase is OK" << RESET << std::endl;

  // map relational operators
  std::cout << YELLOW << BOLD << "------------- map relational operators -------------" << RESET
            << std::endl;
  gettimeofday(&ft_start, NULL);
  {
    ft::map<int, int> map_int;
    ft::map<int, int> map_int2;
    ft::map<int, int> map_int3;
    for (int i = 0; i < MAP_SIZE; i++) {
      map_int.insert(ft::make_pair(i, i));
      map_int2.insert(ft::make_pair(i, i));
      map_int3.insert(ft::make_pair(i + 1, i + 1));
    }
    if (map_int != map_int2) {
      std::cout << RED << BOLD << "ft::map - relational operators(==) is not OK" << RESET
                << std::endl;
    }
    if (map_int > map_int3) {
      std::cout << RED << BOLD << "ft::map - relational operators(>) is not OK" << RESET
                << std::endl;
      //
    }
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);

  gettimeofday(&std_start, NULL);
  {
    std::map<int, int> std_map_int;
    std::map<int, int> std_map_int2;
    std::map<int, int> std_map_int3;
    for (int i = 0; i < MAP_SIZE; i++) {
      std_map_int.insert(std::make_pair(i, i));
      std_map_int2.insert(std::make_pair(i, i));
      std_map_int3.insert(std::make_pair(i + 1, i + 1));
    }
    if (std_map_int != std_map_int2) {
      std::cout << RED << BOLD << "std::map - relational operators(==) is not OK" << RESET
                << std::endl;
      //
    }
    if (std_map_int > std_map_int3) {
      std::cout << RED << BOLD << "std::map - relational operators(>) is not OK" << RESET
                << std::endl;
      //
    }
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::map - relational operators is " << (double) ft_time / std_time
              << " times slow" << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::map - relational operators is OK" << RESET << std::endl;

  // map swap
  std::cout << YELLOW << BOLD << "------------- map swap -------------" << RESET << std::endl;
  gettimeofday(&ft_start, NULL);
  {
    ft::map<int, int> map_int;
    ft::map<int, int> map_int2;
    for (int i = 0; i < MAP_SIZE; i++) {
      map_int.insert(ft::make_pair(i, i));
      map_int2.insert(ft::make_pair(i + 1, i + 1));
    }
    map_int.swap(map_int2);
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);

  gettimeofday(&std_start, NULL);
  {
    std::map<int, int> std_map_int;
    std::map<int, int> std_map_int2;
    for (int i = 0; i < MAP_SIZE; i++) {
      std_map_int.insert(std::make_pair(i, i));
      std_map_int2.insert(std::make_pair(i + 1, i + 1));
    }
    std_map_int.swap(std_map_int2);
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::map - swap is " << (double) ft_time / std_time << " times slow"
              << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::map - swap is OK" << RESET << std::endl;

  // map clear
  std::cout << YELLOW << BOLD << "------------- map clear -------------" << RESET << std::endl;
  gettimeofday(&ft_start, NULL);
  {
    ft::map<int, int> map_int;
    for (int i = 0; i < MAP_SIZE; i++) map_int.insert(ft::make_pair(i, i));
    map_int.clear();
  }
  gettimeofday(&ft_end, NULL);
  ft_time = get_time(ft_start, ft_end);

  gettimeofday(&std_start, NULL);
  {
    std::map<int, int> std_map_int;
    for (int i = 0; i < MAP_SIZE; i++) std_map_int.insert(std::make_pair(i, i));
    std_map_int.clear();
  }
  gettimeofday(&std_end, NULL);
  std_time = get_time(std_start, std_end);
  std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
  std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
  if (std_time && ft_time > 20 * std_time) {
    std::cout << RED << BOLD << "ft::map - clear is " << (double) ft_time / std_time << " times slow"
              << RESET << std::endl;
    //
  } else
    std::cout << GREEN << BOLD << "ft::map - clear is OK" << RESET << std::endl;

  std::cout << CYAN << BOLD << "\n\n============= LEAKS ==============n\n" << RESET << std::endl;
//
  system("leaks time_test");
//
  std::cout << GREEN << BOLD << "============= TEST is OK =============" << RESET << std::endl;
  return (0);
}