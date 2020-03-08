#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t& center);
  Circle(const int x, const int y);

  virtual void draw() const;
};

#endif
