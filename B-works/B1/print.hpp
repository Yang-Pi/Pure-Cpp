#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>

template < typename Collection >
void print(const Collection & collection)
{
  for (const auto & element : collection) {
    std::cout << element << " ";
  }
  std::cout << '\n';
}

#endif
