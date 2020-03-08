#include "circle.hpp"

Circle::Circle(const point_t& center) :
  Shape(center)
{}

Circle::Circle(const int x, const int y) :
  Shape(x, y)
{}

void Circle::draw() const
{
  point_t center = getCenter();
  std::cout << "CIRCLE (" << center.x << ";" << center.y << ")\n";
}
