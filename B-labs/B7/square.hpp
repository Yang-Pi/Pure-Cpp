#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "shape.hpp"

class Square : public Shape
{
public:
  Square(const point_t& center);
  Square(const int x, const int y);

  virtual void draw() const;
};

#endif //SQUARE_HPP
