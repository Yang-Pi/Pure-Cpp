#ifndef FACTORIAL_ITERATOR_HPP
#define FACTORIAL_ITERATOR_HPP

#include <iterator>

class FactorialIterator: public
    std::iterator<std::bidirectional_iterator_tag, size_t>
{
public:
  FactorialIterator();
  FactorialIterator(size_t index);

  size_t &operator *();
  size_t *operator ->();

  FactorialIterator &operator ++();
  FactorialIterator operator ++(int);
  FactorialIterator &operator --();
  FactorialIterator operator --(int);

  bool operator ==(const FactorialIterator& iter) const;
  bool operator !=(const FactorialIterator& iter) const;

private:
  size_t index_;
  size_t factorial_;

  size_t getFactorial(size_t index) const;
};

#endif //FACTORIAL_ITERATOR_HPP
