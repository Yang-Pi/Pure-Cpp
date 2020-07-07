#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP


#include "shape.hpp"
#include <iostream>

namespace pylaev {
  class Triangle: public Shape {
  public:
    Triangle(const point_t &, const point_t &, const point_t &); //by coordinates

    double getArea() const override;
    point_t getCenter() const override;
    double getSide(size_t) const;
    rectangle_t getFrameRect() const override;

    void move(double, double) override;
    void move(const point_t &) override;
    void scale(double) override;
    void rotate(double) override;

    void printSpec() const override;

  private:
    constexpr static size_t numVertices_ = 3;
    point_t points_[3]; //array of vertices' coordinates
  };
}

#endif
