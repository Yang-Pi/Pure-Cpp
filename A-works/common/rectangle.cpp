#include "rectangle.hpp"
#include "shape_by_coordinates.hpp"

#include <stdexcept>
#include <iostream>

pylaev::Rectangle::Rectangle(const point_t & center, double width, double height):
  points_({ { center.x - width / 2, center.y - height / 2 },
      { center.x - width / 2, center.y + height / 2 },
      { center.x + width / 2, center.y + height / 2 },
      { center.x + width / 2, center.y - height / 2 } })
{
  if ((width <= 0.0) && (height <= 0.0)) {
    throw std::invalid_argument("Length of rectangle's sides must be positive");
  }
}

pylaev::Rectangle::Rectangle(const point_t & center, double width):
  Rectangle(center, width, width)
{ }

pylaev::Rectangle::Rectangle(const point_t & point1, const point_t & point2, const point_t & point3, const point_t & point4):
  points_({ point1, point2, point3, point4})
{
  if (!(pylaev::detail::ShapeByCoordinates< numVertices_ >::isConvex(points_))) {
    throw std::logic_error("It is not a convex rectangle");
  }
  for (size_t i = 0; i < numVertices_ - 1; i++) {
    vector_t vector1 = countVector(points_[i], points_[i+1]);
    vector_t vector2 = countVector(points_[i + 1 ], points_[(i+2) % numVertices_]);
    if (vector1.x * vector2.x + vector1.y * vector2.y != 0) {
      throw std::logic_error("It is not a rectangle");
    }
  }
}

double pylaev::Rectangle::getArea() const
{
  return pylaev::detail::ShapeByCoordinates< numVertices_ >::getArea(points_);
}

pylaev::point_t pylaev::Rectangle::getCenter() const
{
  return pylaev::detail::ShapeByCoordinates< numVertices_ >::getCenter(points_);
}

double pylaev::Rectangle::getWidth() const
{
  double x = points_[2].x - points_[1].x;
  double y = points_[2].y - points_[1].y;
  return sqrt(pow(x, 2) + pow(y, 2));
}

double pylaev::Rectangle::getHeight() const
{
  double x = points_[1].x - points_[0].x;
  double y = points_[1].y - points_[0].y;
  return sqrt(pow(x, 2) + pow(y, 2));
}

pylaev::rectangle_t pylaev::Rectangle::getFrameRect() const
{
  return pylaev::detail::ShapeByCoordinates< numVertices_ >::getFrameRect(points_);
}

void pylaev::Rectangle::move(double dx, double dy)
{
  pylaev::detail::ShapeByCoordinates< numVertices_ >::move(points_, dx, dy);
}

void pylaev::Rectangle::move(const point_t & pos)
{
  point_t center = getCenter();
  pylaev::detail::ShapeByCoordinates< numVertices_ >::move(points_, pos.x - center.x, pos.y - center.y);
}

void pylaev::Rectangle::scale(double kScaling)
{
  pylaev::detail::ShapeByCoordinates< numVertices_ >::scale(points_, getCenter(), kScaling);
}

void pylaev::Rectangle::rotate(double angle) {
  pylaev::detail::ShapeByCoordinates< numVertices_ >::rotate(points_, getCenter(), angle);
}

void pylaev::Rectangle::printSpec() const
{
  std::cout << "Area of our rectangle is " << getArea() << " square units\n";
  rectangle_t frameRectangle = getFrameRect();
  std::cout << "Center of the frame rectangle with width = " << frameRectangle.width
      << " and height = " << frameRectangle.height
      << " is located in point (" << frameRectangle.pos.x << "; " << frameRectangle.pos.y << ")\n";
}
