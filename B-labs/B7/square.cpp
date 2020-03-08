#include "square.hpp"

Square::Square(const point_t& center) :
  Shape(center)
{}

Square::Square(const int x, const int y) :
  Shape(x, y)
{}

void Square::draw() const
{
  point_t center = getCenter();
  std::cout << "SQUARE (" << center.x << ";" << center.y << ")\n";
}
