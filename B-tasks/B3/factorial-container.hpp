#ifndef FACTORIAL_CONTAINER_HPP
#define FACTORIAL_CONTAINER_HPP

#include "factorial-iterator.hpp"

class FactorialContainer
{
public:
  static const int MIN = 1;
  static const int MAX = 11;

  FactorialContainer() = default;

  FactorialIterator begin();
  FactorialIterator end();
};

#endif //FACTORIAL_CONTAINER_HPP
