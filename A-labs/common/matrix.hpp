#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"

#include <iostream>
#include <memory>

namespace pylaev {
  class Matrix {
  public:
    class Layer {
    public:
      Layer(Shape **, std::size_t);
      Shape * operator [](std::size_t) const;
      std::size_t getSize();
    private:
      std::unique_ptr< Shape *[] > shapes_;
      std::size_t size_;
    };

    Matrix();
    Matrix(const Matrix &);
    Matrix(Matrix &&);

    ~Matrix() = default;

    Matrix & operator =(const Matrix &);
    Matrix & operator =(Matrix &&);
    Layer operator [](std::size_t) const;

    void add(Shape *, std::size_t);

    std::size_t getSize() const; //how many figures in the matrix
    std::size_t getCountOfLayers() const;

  private:
    std::unique_ptr< Shape *[] > shapesMatrix_;
    std::size_t countOfLayers_; //one row is a one layer
    std::unique_ptr< std::size_t [] > sizeOfLayers_;
  };
}

#endif
