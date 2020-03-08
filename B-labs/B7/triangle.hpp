#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t& center);
  Triangle(const int x, const int y);

  virtual void draw() const;
};

#endif
