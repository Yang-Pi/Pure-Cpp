#include "shape.hpp"

Shape::Shape(const point_t& center) :
  center_(center)
{}

Shape::Shape(const int x, const int y) :
  center_({x, y})
{}

point_t Shape::getCenter() const
{
  return center_;
}

bool Shape::isMoreLeft(const Shape& shape) const
{
  return center_.x < shape.center_.x;
}

bool Shape::isUpper(const Shape& shape) const
{
  return center_.y > shape.center_.y;
}
