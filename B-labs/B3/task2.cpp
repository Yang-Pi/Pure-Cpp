#include <iostream>
#include <algorithm>

#include "factorial-container.hpp"

void task2()
{
  FactorialContainer factorialCont;

  std::copy(factorialCont.begin(), factorialCont.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';

  std::reverse_copy(factorialCont.begin(), factorialCont.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
}
