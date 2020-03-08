#ifndef MP_FUNCTOR_HPP
#define MP_FUNCTOR_HPP

#include <cmath>

class MultipliesFunctor
{
public:
  double operator()(const double& arg2);
private:
  const double arg1 = M_PI;
};

#endif //MP_FUNCTOR_HPP
