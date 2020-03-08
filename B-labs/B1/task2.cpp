#include <fstream>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <stdexcept>

#include "tasks.hpp"
#include "print.hpp"

const double KMEMORY = 1.6;

void task2(const char * fileName)
{
  std::ifstream input(fileName);
  if (!input) {
    throw std::ios_base::failure("Failed opening the file\n");
  }

  int capacity = 10;
  std::unique_ptr< char [], decltype(&free) > arrayC(static_cast< char * >(calloc(capacity, sizeof(char))), free);
  if (!arrayC) {
    throw std::runtime_error("Failed allocating memory\n");
  }

  int numCharacters = 0;
  while (input) {
    input.read(&arrayC[numCharacters], capacity - numCharacters);
    numCharacters += input.gcount();

    if (!numCharacters) { //have read nothing
      return;
    }

    if (numCharacters == capacity) {
      capacity = static_cast< int >(capacity * KMEMORY);
      std::unique_ptr< char [], decltype(&free) > tmpArray(static_cast< char * >(realloc(arrayC.get(),  capacity)), free);
      if (!tmpArray) {
        throw std::runtime_error("Failed allocating memory\n");
      }
      arrayC.release();
      std::swap(arrayC, tmpArray);
    }
    if ( (!input.eof()) && (input.fail()) ) {
      std::ios_base::failure("Failed reading data");
    }
  }
  std::vector< char > vector(&arrayC[0], &arrayC[numCharacters]);
  for (const auto & elementOut : vector){
    std::cout << elementOut;
  }
}
