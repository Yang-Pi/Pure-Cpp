#include <vector>
#include <forward_list>
#include <stdexcept>

#include "tasks.hpp"
#include "sort.hpp"
#include "print.hpp"
#include "strategy.hpp"

void task1(const char * direction)
{
  auto dir = getDirection< int >(direction);

  std::vector< int > vectorBrackets;

  int current = 0;
  while (std::cin >> current, !std::cin.eof()) {
    if (!std::cin.eof() && std::cin.fail()) {
      throw std::runtime_error("Input failed\n");
    }
    vectorBrackets.push_back(current);
  }
  if (vectorBrackets.empty()) {
    return;
  }

  std::vector< int > vectorAt(vectorBrackets);
  std::forward_list< int > forwardList(vectorBrackets.begin(), vectorBrackets.end());

  sort< AccessBySquareBrackets >(vectorBrackets, dir);
  sort< AccessByAt >(vectorAt, dir);
  sort< AccessByIterator >(forwardList, dir);
  
  print(vectorBrackets);
  print(vectorAt);
  print(forwardList);
}
