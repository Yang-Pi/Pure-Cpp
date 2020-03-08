#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <iostream>
#include <iterator>

template < typename Collection >
struct AccessBySquareBrackets {
  static typename Collection::reference getElement(Collection & collection, std::size_t index)
  {
    return collection[index];
  }
  static std::size_t begin(const Collection &)
  {
    return 0;
  }
  static std::size_t end(const Collection & collection)
  {
    return collection.size();
  }
  static std::size_t next(std::size_t index)
  {
    return index + 1;
  }
};

template < typename Collection >
struct AccessByAt {
  static typename Collection::reference getElement(Collection & collection, std::size_t index)
  {
    return collection.at(index);
  }
  static std::size_t begin(const Collection &)
  {
    return 0;
  }
  static std::size_t end(const Collection & collection)
  {
    return collection.size();
  }
  static std::size_t next(std::size_t index)
  {
    return index + 1;
  }
};

template < typename Collection >
struct AccessByIterator {
  static typename Collection::reference getElement(Collection &, typename Collection::iterator iter)
  {
    return *iter;
  }
  static typename Collection::iterator begin(Collection & collection)
  {
    return collection.begin();
  }
  static typename Collection::iterator end(Collection & collection)
  {
    return collection.end();
  }
  static typename Collection::iterator next(typename Collection::iterator iter)
  {
    return ++iter;
  }
};

#endif
