#include "factorial-container.hpp"

FactorialIterator FactorialContainer::begin()
{
  return FactorialIterator(MIN);
}

FactorialIterator FactorialContainer::end()
{
  return FactorialIterator(MAX);
}
