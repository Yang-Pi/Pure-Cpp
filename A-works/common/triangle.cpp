#include "triangle.hpp"
#include "shape_by_coordinates.hpp"

#include <stdexcept>

pylaev::Triangle::Triangle(const point_t & pointA, const point_t & pointB, const point_t & pointC):
  points_({pointA, pointB, pointC})
{
  if (getArea() == 0) {
    throw std::logic_error("It's a stright line, coordinates of vertices can't be on one line");
  }
}

double pylaev::Triangle::getArea() const //by coordinates
{
  return pylaev::detail::ShapeByCoordinates< numVertices_ >::getArea(points_);
}

pylaev::point_t pylaev::Triangle::getCenter() const
{
  return pylaev::detail::ShapeByCoordinates< numVertices_ >::getCenter(points_);
}

double pylaev::Triangle::getSide(size_t index) const
{
  return pylaev::detail::ShapeByCoordinates< numVertices_ >::getSide(points_, index);
}

pylaev::rectangle_t pylaev::Triangle::getFrameRect() const
{
  return pylaev::detail::ShapeByCoordinates< numVertices_ >::getFrameRect(points_);
}

void pylaev::Triangle::move(double dx, double dy)
{
  pylaev::detail::ShapeByCoordinates< numVertices_ >::move(points_, dx, dy);
}

void pylaev::Triangle::move(const point_t & pos)
{
  point_t center = getCenter();
  pylaev::detail::ShapeByCoordinates< numVertices_ >::move(points_, pos.x - center.x, pos.y - center.y);
}

void pylaev::Triangle::scale(double kScaling)
{
  pylaev::detail::ShapeByCoordinates< numVertices_ >::scale(points_, getCenter(), kScaling);
}

void pylaev::Triangle::rotate(double angle)
{
  pylaev::detail::ShapeByCoordinates< numVertices_ >::rotate(points_, getCenter(), angle);
}

void pylaev::Triangle::printSpec() const
{
  std::cout << "Area of our triangle is " << getArea() << " square units\n";
  rectangle_t frameRectangle = getFrameRect();
  std::cout << "Center of the frame rectangle with width = " << frameRectangle.width
      << " and height = " << frameRectangle.height
      << " is located in point (" << frameRectangle.pos.x << "; " << frameRectangle.pos.y << ")\n";
}
