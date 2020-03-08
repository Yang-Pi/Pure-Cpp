#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

class Rectangle: public Shape {
public:
  Rectangle(point_t const &, double, double);
  Rectangle(point_t const &, double); //square

  double getWidth() const;
  double getHeight() const;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const double, const double) override;
  void move(const point_t &) override;
  void printSpec() const override;

private:
  point_t center_;
  double width_;
  double height_;
};

#endif
