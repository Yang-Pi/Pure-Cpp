#include "triangle.hpp"

#include <stdexcept>
#include <math.h>
#include <iostream>

Triangle::Triangle(const point_t & pointA, const point_t & pointB, const point_t & pointC):
  coordinates_({pointA, pointB, pointC}),
  center_(getCenter())
{
  if (getArea() == 0.0) {
    throw std::invalid_argument("It's a stright line, coordinates of tops can't be on one line");
  }
}

point_t Triangle::getCenter() const
{
  return {(coordinates_[0].x + coordinates_[1].x + coordinates_[2].x) / 3,
      (coordinates_[0].y + coordinates_[1].y + coordinates_[2].y) / 3};
}

double Triangle::getArea() const //by coordinates
{
  point_t side0 = {coordinates_[1].x - coordinates_[0].x, coordinates_[1].y - coordinates_[0].y}; //like vectors
  point_t side2 = {coordinates_[2].x - coordinates_[0].x, coordinates_[2].y - coordinates_[0].y};

  return (fabs((side0.x * side2.y - side0.y * side2.x)) / 2);
}

rectangle_t Triangle::getFrameRect() const
{
  //max/min coordinates of triangle (left top and rigth bottom)
  point_t maxCoordinates {std::max(coordinates_[0].x, std::max(coordinates_[1].x, coordinates_[2].x)),
      std::max(coordinates_[0].y, std::max(coordinates_[1].y, coordinates_[2].y))};
  point_t minCoordinates {std::min(coordinates_[0].x, std::min(coordinates_[1].x, coordinates_[2].x)),
      std::min(coordinates_[0].y, std::min(coordinates_[1].y, coordinates_[2].y))};

  double width = maxCoordinates.x - minCoordinates.x;
  double height = maxCoordinates.y - minCoordinates.y;
  point_t pos = {width / 2 + minCoordinates.x, height / 2 + minCoordinates.y};

  return {pos, width, height};
}

void Triangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
  for (int i = 0; i < nTops_; i++) {
    coordinates_[i].x += dx;
    coordinates_[i].y += dy;
  }
}

void Triangle::move(const point_t & pos)
{
  move(pos.x - center_.x, pos.y - center_.y);
}

void Triangle::printSpec() const
{
  std::cout << "Area of our triangle is " << getArea() << " square units\n";
  rectangle_t frameRectangle = getFrameRect();
  std::cout << "Center of the frame rectangle with width = " << frameRectangle.width
      << " and height = " << frameRectangle.height
      << " is located in point (" << frameRectangle.pos.x << "; " << frameRectangle.pos.y << ")\n";
}
