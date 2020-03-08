#include "mp-functor.hpp"

double MultipliesFunctor::operator()(const double& arg2)
{
  return arg1 * arg2;
}
