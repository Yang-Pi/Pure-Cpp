#include <vector>
#include <stdexcept>
#include <iostream>

#include "tasks.hpp"
#include "print.hpp"

void task3()
{
  std::vector<int> vector;

  int current = -1;
  while (std::cin >> current) {
    if (current == 0) {
      break;
    }
    vector.push_back(current);
  }
  if (!std::cin.eof() && std::cin.fail()) {
    throw std::ios_base::failure("Reading from std::cin failed\n");
  }
  if (vector.empty()) {
    return;
  }
  if (current != 0) {
    throw std::runtime_error("Expected zero at the end of input");
  }
  
  switch (vector.back()) {
    case 1: {
      auto iter = vector.begin();
      while (iter != vector.end()) {
        iter = ((*iter) % 2 == 0) ? vector.erase(iter) : ++iter;
      }
      break;
    }
    case 2: {
      auto iter = vector.begin();
      while (iter != vector.end()) {
        iter = ((*iter) % 3 == 0) ? (vector.insert(++iter, 3, 1) + 3) : ++iter;
      }
      break;
    }
  }

  print(vector);
}
