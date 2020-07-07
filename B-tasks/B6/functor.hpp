#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

class Functor
{
public:
  Functor();
  void operator()(const int& umber);

  long long getMax() const;
  long long getMin() const;

  double getMean() const;

  long long getNumberPositive() const;
  long long getNumberNegative() const;

  long long getSumEven() const;
  long long getSumOdd() const;

  bool isFirstEqLast() const;
  bool isEmpty() const;

private:
  long long max_;
  long long min_;

  long long nAll_;
  long long nPositive_;
  long long nNegative_;

  long long sumOdd_;
  long long sumEven_;

  long long first_;
  bool firstEqLast_;

  bool empty_;
};

#endif
