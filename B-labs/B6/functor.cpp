#include "functor.hpp"

Functor::Functor() :
  max_(0),
  min_(0),
  nAll_(0),
  nPositive_(0),
  nNegative_(0),
  sumOdd_(0),
  sumEven_(0),
  first_ (0),
  firstEqLast_(false),
  empty_(true)
{}

void Functor::operator()(const int& number)
{
  //works for first one
  if (empty_) {
    first_ = number;
    //state normal max and min
    min_ = number;
    max_ = number;

    empty_ = false;
  }

  if (number > max_) {
    max_ = number;
  }

  if (number < min_) {
    min_ = number;
  }

  if (number > 0) {
    ++nPositive_;
  }

  if (number < 0) {
    ++nNegative_;
  }

  if (number % 2 == 0) {
    sumEven_ += number;
  }
  else {
    sumOdd_ += number;
  }

  firstEqLast_ = (first_ == number);
  ++nAll_;
}

long long Functor::getMax() const
{
  return max_;
}

long long Functor::getMin() const
{
  return min_;
}

double Functor::getMean() const
{
  return (static_cast<double>(sumOdd_ + sumEven_) / nAll_);
}

long long Functor::getNumberPositive() const
{
  return nPositive_;
}

long long Functor::getNumberNegative() const
{
  return nNegative_;
}

long long Functor::getSumEven() const
{
  return sumEven_;
}

long long Functor::getSumOdd() const
{
  return sumOdd_;
}

bool Functor::isFirstEqLast() const
{
  return firstEqLast_;
}

bool Functor::isEmpty() const
{
  return empty_;
}
