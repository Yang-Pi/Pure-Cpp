#define _USE_MATH_DEFINES

#include "circle.hpp"

#include <stdexcept>
#include <cmath>
#include <iostream>

Circle::Circle(const point_t & center, double radius):
  center_(center),
  radius_(radius)
{
  if (radius_ == 0.0) {
    throw std::invalid_argument("It is a point");
  }
  if (radius_ < 0.0) {
    throw std::invalid_argument("Length of radius must be positive");
  }
}

double Circle::getRadius() const
{
  return radius_;
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {center_, radius_ * 2, radius_ * 2};
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
};

void Circle::move(const point_t & pos)
{
  center_ = pos;
}

void Circle::printSpec() const
{
  std::cout << "Area of our circle with radius = " << getRadius() << " is " << getArea() << " square units\n";
  rectangle_t frameRectangle = getFrameRect();
  std::cout << "Center of the frame rectangle with width = " << frameRectangle.width
      << " and height = " << frameRectangle.height
      << " is located in point (" << frameRectangle.pos.x << "; " << frameRectangle.pos.y << ")\n";
}
