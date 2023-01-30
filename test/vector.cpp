/*
 * File: vector.cpp
 * Project: ft_container
 * Created Date: 2023/01/30
 * Author: nkim
 * Copyright (c) 2022 nkim
 */

#include <iostream>
#include <vector>

int main() {
  // empty vector
  std::vector<int> v;
  std::cout << v.size() << std::endl << v.capacity() << std::endl;

  // vector using reverse_iterator
  std::vector<int> vr(4, 7); // 4 int with value "7"
  std::vector<int>::reverse_iterator itv = vr.rbegin();
  while (itv != vr.rend()) {
    std::cout << "reverse_iterator: " << *itv << std::endl;
    itv++;
  }

  // vector using iterator
  std::vector<int> vi(4, 3); // 4 int with value "3"
  for (std::vector<int>::iterator it = vi.begin(); it != vi.end(); it++) {
    std::cout << "iterator: " << *it << std::endl;
  }

  return 1;
}
