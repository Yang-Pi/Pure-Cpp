#include "rectangle.hpp"

#include <stdexcept>
#include <iostream>

Rectangle::Rectangle(const point_t & center, const double width, const double height):
  center_(center),
  width_(width),
  height_(height)
{
  if ((width_ <= 0.0) && (height_ <= 0.0)) {
    throw std::invalid_argument("Length of rectangle's sides must be positive");
  }
}

Rectangle::Rectangle(const point_t & center, const double width):
  center_(center),
  width_(width),
  height_(width)
{
  if (width_ <= 0.0) {
    throw std::invalid_argument("Length of square's sides must be positive");
  }
}

double Rectangle::getWidth() const
{
  return width_;
}

double Rectangle::getHeight() const
{
  return height_;
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {center_, width_, height_};
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::move(const point_t & pos)
{
  center_ = pos;
}

void Rectangle::printSpec() const
{
  std::cout << "Area of our rectangle is " << getArea() << " square units\n";
  rectangle_t frameRectangle = getFrameRect();
  std::cout << "Center of the frame rectangle with width = " << frameRectangle.width
      << " and height = " << frameRectangle.height
      << " is located in point (" << frameRectangle.pos.x << "; " << frameRectangle.pos.y << ")\n";
}
