#include "triangle.hpp"

Triangle::Triangle(const point_t& center) :
  Shape(center)
{}

Triangle::Triangle(const int x, const int y) :
  Shape(x, y)
{}

void Triangle::draw() const
{
  point_t center = getCenter();
  std::cout << "TRIANGLE (" << center.x << ";" << center.y << ")\n";
}
