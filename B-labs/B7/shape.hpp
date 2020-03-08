#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <iostream>

struct point_t {
  int x;
  int y;
};

class Shape
{
public:
  Shape(const point_t& center);
  Shape(const int x, const int y);

  point_t getCenter() const;

  bool isMoreLeft(const Shape &shape) const;
  bool isUpper(const Shape &shape) const;

  virtual void draw() const = 0;

private:
  point_t center_;
};

#endif //SHAPE_HPP
