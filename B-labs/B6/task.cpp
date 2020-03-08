#include <iterator>
#include <algorithm>
#include <iostream>

#include "functor.hpp"

void task()
{
  Functor functor;

  std::istream_iterator<long long> input(std::cin);
  functor = std::for_each(input, std::istream_iterator<long long>(), functor);

  if (!std::cin.eof()) {
    throw std::ios_base::failure("Reading from stream has faild!\n");
  }

//print task results
  if (functor.isEmpty()) {
    std::cout << "No Data\n";
  }
  else {
    std::cout << "Max: " << functor.getMax() << "\n";
    std::cout << "Min: " << functor.getMin() << "\n";
    std::cout << "Mean: " << std::fixed << functor.getMean() << "\n";
    std::cout << "Positive: " << functor.getNumberPositive() << "\n";
    std::cout << "Negative: " << functor.getNumberNegative() << "\n";
    std::cout << "Odd Sum: " << functor.getSumOdd() << "\n";
    std::cout << "Even Sum: " << functor.getSumEven() << "\n";
    std::cout << "First/Last Equal: " << (functor.isFirstEqLast() ? "yes" : "no") << "\n";
  }
}
