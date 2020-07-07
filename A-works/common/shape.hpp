#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace pylaev {
  class Shape {
  public:
    virtual ~Shape() = default; //distructor

    virtual double getArea() const = 0;
    virtual point_t getCenter() const = 0;
    virtual rectangle_t getFrameRect() const = 0;

    virtual void printSpec() const = 0;

    virtual void move(double, double) = 0;
    virtual void move(const point_t &) = 0; //move figure to new center
    virtual void scale(double) = 0;
    virtual void rotate(double) = 0; //rotate figure about center (by degrees)
  };
}

#endif
