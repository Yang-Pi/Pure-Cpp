#ifndef SORT_HPP
#define SORT_HPP

#include <functional>
#include <cstring>

template <typename T>
std::function< bool (T, T) > getDirection(const char * direction)
{
  if (std::strcmp(direction, "ascending") == 0) {
    return [] (T lhs, T rhs) { return lhs < rhs; };
  }

  if (std::strcmp(direction, "descending") == 0) {
    return [] (T lhs, T rhs) { return lhs > rhs; };
  }
  throw std::invalid_argument("No such direction\n");
}

template < template < class Collection > class AccessStrategy, typename Collection >
void sort(Collection & collection, std::function< bool (typename Collection::value_type, typename Collection::value_type) > direction)
{
  using Strategy = AccessStrategy < Collection >;
  const auto begin = Strategy::begin(collection);
  const auto end = Strategy::end(collection);

  for (auto i = begin; i != end; i++) {
    for (auto j = Strategy::next(i); j != end; j++) {
      typename Collection::value_type & elementJ = Strategy::getElement(collection, j);
      typename Collection::value_type & elementI = Strategy::getElement(collection, i);
      if (direction(elementJ, elementI)) {
        std::swap(elementJ, elementI);
      }
    }
  }
};

#endif
