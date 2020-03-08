#include <vector>
#include <cstdlib>
#include <stdexcept>

#include "tasks.hpp"
#include "sort.hpp"
#include "print.hpp"
#include "strategy.hpp"

void fillRandom(double * array, int size)
{
  const double a = -1.0;
  const double b = 1.0;
  for (int i = 0; i < size; i++) {
    array[i] = a + rand() * (b - a) / RAND_MAX;
  }
}

void task4(const char * direction, int size)
{
  if (size < 0) {
    throw std::invalid_argument("Negative array size\n");
  }
  if (!size) {
    return;
  }
  auto dir = getDirection< double >(direction);

  std::vector< double > vector(size);
  fillRandom(&vector[0], size);

  print(vector);
  sort< AccessBySquareBrackets >(vector, dir);
  print(vector);
}
