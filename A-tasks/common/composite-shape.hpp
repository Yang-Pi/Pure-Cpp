#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include "matrix.hpp"

#include <iostream>
#include <memory>


namespace pylaev {
  class CompositeShape: public Shape {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape &);
    CompositeShape(CompositeShape &&);
    CompositeShape(std::size_t);

    ~CompositeShape() = default;

    CompositeShape & operator =(const CompositeShape &);
    CompositeShape & operator =(CompositeShape &&);
    Shape * operator [](std::size_t) const;

    void add(Shape *);
    void remove(std::size_t);
    void remove(const Shape *);

    double getArea() const override;
    point_t getCenter() const override;
    rectangle_t getFrameRect() const override;

    void move(double, double) override;
    void move(const point_t &) override;
    void scale(double) override;
    void rotate(double) override;
    Matrix split() const;

    point_t getCentroid() const;
    std::size_t getSize() const;
    void printSpec() const override;

  private:
    std::size_t size_;
    std::size_t freeCells_;
    const double kMemory_ = 1.6;
    std::unique_ptr< Shape *[] > shapesArray_;
  };
}

#endif
