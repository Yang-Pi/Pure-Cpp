 #include <iterator>
#include <iostream>
#include <algorithm>

#include "mp-functor.hpp"

void task1()
{
  using dInputIterator = std::istream_iterator<double>;
  dInputIterator inIterFirst = dInputIterator(std::cin);
  dInputIterator inIterLast = dInputIterator();

  std::ostream_iterator<double> outIter = std::ostream_iterator<double>(std::cout, " ");

  MultipliesFunctor mpFunctor;
  std::transform(inIterFirst, inIterLast, outIter, mpFunctor);

  if (!std::cin.eof()) {
    throw std::ios_base::failure("Faild reading from stream!\n");
  }
}
