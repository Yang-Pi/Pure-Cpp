#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <iostream>
#include "shape.hpp"

namespace pylaev {
  class Rectangle: public Shape {
  public:
    Rectangle(point_t const &, double, double);
    Rectangle(point_t const &, double); //square
    Rectangle(const point_t &, const point_t &, const point_t &, const point_t &);

    double getArea() const override;
    point_t getCenter() const override;
    double getWidth() const;
    double getHeight() const;
    rectangle_t getFrameRect() const override;

    void move(double, double) override;
    void move(const point_t &) override;
    void scale(double) override;
    void rotate(double) override;

    void printSpec() const override;

  private:
    constexpr static size_t numVertices_ = 4;
    point_t points_[4];
  };
}

#endif
