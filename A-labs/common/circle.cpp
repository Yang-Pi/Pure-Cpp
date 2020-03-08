#define _USE_MATH_DEFINES

#include "circle.hpp"

#include <stdexcept>
#include <cmath>
#include <iostream>

pylaev::Circle::Circle(const point_t & center, double radius):
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

double pylaev::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

pylaev::point_t pylaev::Circle::getCenter() const
{
  return center_;
}

double pylaev::Circle::getRadius() const
{
  return radius_;
}

pylaev::rectangle_t pylaev::Circle::getFrameRect() const
{
  return {center_, radius_ * 2, radius_ * 2};
}

void pylaev::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
};

void pylaev::Circle::move(const point_t &pos)
{
  center_ = pos;
}

void pylaev::Circle::scale(double kScaling)
{
  if (kScaling <= 0.0) {
    throw std::invalid_argument("Coefficient of scaling must be positive");
  }
  radius_ *= kScaling;
}

void pylaev::Circle::rotate(double)
{ }

void pylaev::Circle::printSpec() const
{
  std::cout << "Area of our circle with radius = " << radius_ << " is " << getArea() << " square units\n";
  rectangle_t frameRectangle = getFrameRect();
  std::cout << "Center of the frame rectangle with width = " << frameRectangle.width
      << " and height = " << frameRectangle.height
      << " is located in point (" << frameRectangle.pos.x << "; " << frameRectangle.pos.y << ")\n";
}
