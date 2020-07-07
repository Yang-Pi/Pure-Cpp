#include "base-types.hpp"

#include <cmath>

pylaev::vector_t pylaev::countVector(const point_t & point1, const point_t & point2)
{
  return { point2.x - point1.x, point2.y - point1.y };
}
double pylaev::countVectorProduct(const vector_t & vector1, const vector_t & vector2)
{
  return vector1.x * vector2.y - vector1.y * vector2.x;
}

bool pylaev::intersection(const rectangle_t & rectangle1, const rectangle_t & rectangle2)
{
  if ((fabs(rectangle1.pos.x - rectangle2.pos.x) < rectangle1.width / 2 + rectangle2.width / 2) &&
      (fabs(rectangle1.pos.y - rectangle2.pos.y) < rectangle1.height / 2  + rectangle2.height / 2)) {
    return true;
  } else {
    return false;
  }
}
