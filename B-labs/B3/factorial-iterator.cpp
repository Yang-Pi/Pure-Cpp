#include "factorial-iterator.hpp"
#include "factorial-container.hpp"

FactorialIterator::FactorialIterator() :
    FactorialIterator(1)
{}

FactorialIterator::FactorialIterator(size_t index) :
    index_(index),
    factorial_(getFactorial(index))
{}

size_t* FactorialIterator::operator ->()
{
  return &factorial_;
}

size_t& FactorialIterator::operator *()
{
  return factorial_;
}

FactorialIterator& FactorialIterator::operator ++()
{
  if (index_ <= FactorialContainer::MAX) {
    ++index_;
    factorial_ *= index_;
  }
  else {
    throw std::out_of_range("Index is out of range!\n");
  }

  return *this;
}

FactorialIterator FactorialIterator::operator ++(int)
{
  FactorialIterator iterator = *this;
  ++(iterator);

  return iterator;
}

FactorialIterator& FactorialIterator::operator --()
{
  if (index_ >= FactorialContainer::MIN) {
    factorial_ /= index_;
    --index_;
  }
  else {
    throw std::out_of_range("Index is out of range!\n");
  }

  return *this;
}

FactorialIterator FactorialIterator::operator --(int)
{
  FactorialIterator iterator = *this;
  --(iterator);

  return iterator;
}

bool FactorialIterator::operator ==(const FactorialIterator& iterator) const
{
  return (index_ == iterator.index_);
}

bool FactorialIterator::operator !=(const FactorialIterator& iterator) const
{
  return !(*this == iterator);
}

size_t FactorialIterator::getFactorial(size_t index) const
{
  if ( (index < FactorialContainer::MIN - 1) || (index > FactorialContainer::MAX) ) {
    throw std::out_of_range("Index is out of range!\n");
  }

  size_t factorial = 1;
  for (size_t i = 1; i < index + 1; ++i)
  {
    factorial *= i;
  }

  return factorial;
}
