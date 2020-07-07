#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace pylaev {
  class Circle: public Shape {
  public:
    Circle(const point_t &, double);

    double getArea() const override;
    point_t getCenter() const override;
    double getRadius() const;
    rectangle_t getFrameRect() const override;

    void move(double, double) override;
    void move(const point_t &) override;
    void scale(double) override;
    void rotate(double) override;

    void printSpec() const override;

  private:
    point_t center_;
    double radius_;
  };
}

#endif
