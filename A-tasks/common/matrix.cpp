#include "matrix.hpp"

pylaev::Matrix::Matrix():
  shapesMatrix_(),
  countOfLayers_(0),
  sizeOfLayers_()
{ }

pylaev::Matrix::Matrix(const Matrix & other):
  shapesMatrix_(new Shape *[other.getSize()]),
  countOfLayers_(other.countOfLayers_),
  sizeOfLayers_(new std::size_t [countOfLayers_])
{
  std::size_t size = other.getSize();
  for (std::size_t i = 0; i < size; i++) {
    shapesMatrix_[i] = other.shapesMatrix_[i];
  }
  for (std::size_t i = 0; i < countOfLayers_; i++) {
    sizeOfLayers_[i] = other.sizeOfLayers_[i];
  }
}

pylaev::Matrix::Matrix(Matrix && other):
  shapesMatrix_(std::move(other.shapesMatrix_)),
  countOfLayers_(other.countOfLayers_),
  sizeOfLayers_(std::move(other.sizeOfLayers_))
{
  other.countOfLayers_ = 0;
}

pylaev::Matrix & pylaev::Matrix::operator =(const Matrix & other)
{
  if (this != &other) {
    std::size_t countOfFigures = other.getSize();
    shapesMatrix_.reset(new Shape *[countOfFigures]);
    for (std::size_t i = 0; i < countOfFigures; i++) {
      shapesMatrix_[i] = other.shapesMatrix_[i];
    }

    countOfLayers_ = other.countOfLayers_;

    sizeOfLayers_.reset(new std::size_t [countOfLayers_]);
    for (std::size_t i = 0; i < countOfLayers_; i++) {
      sizeOfLayers_[i] = other.sizeOfLayers_[i];
    }
  }

  return *this;
}

pylaev::Matrix & pylaev::Matrix::operator =(Matrix && other)
{
  if (this != &other) {
    shapesMatrix_ = std::move(other.shapesMatrix_);
    countOfLayers_ = other.countOfLayers_;
    sizeOfLayers_ = std::move(other.sizeOfLayers_);

    other.countOfLayers_ = 0;
  }

  return *this;
}

pylaev::Matrix::Layer pylaev::Matrix::operator [](std::size_t index) const
{
  if (index >= countOfLayers_) {
    throw std::out_of_range("There are not so many layers in the matrix");
  }

  std::size_t indexFirstFigure = 0;
  for (std::size_t i = 0; i < index; i++) {
    indexFirstFigure += sizeOfLayers_[i];
  }
  Shape * shapesArray[sizeOfLayers_[index]];
  for (std::size_t i = 0; i < sizeOfLayers_[index]; i++) {
    shapesArray[i] = shapesMatrix_[indexFirstFigure + i];
  }

  return Layer(shapesArray, sizeOfLayers_[index]);
}

void pylaev::Matrix::add(Shape * shape, std::size_t layer)
{
  if (shape == nullptr) {
    throw std::invalid_argument("There is no any figure to add - shape pointer is null");
  }

  std::size_t index = 0;
  for (std::size_t i = 0; i < layer; i++) {
    index += sizeOfLayers_[i]; //where figure should be inserted
  }
  if (layer != countOfLayers_) {
    index += sizeOfLayers_[layer];
    sizeOfLayers_[layer]++;
  } else { //create new layer
    std::unique_ptr< std::size_t [] > tmpArray(new std::size_t [countOfLayers_ + 1]); //create new layer
    for (std::size_t i = 0; i < countOfLayers_; i++) {
      tmpArray[i] = sizeOfLayers_[i];
    }
    tmpArray[layer] = 1;
    countOfLayers_++;
    sizeOfLayers_ = std::move(tmpArray);
  }

  std::size_t newSize = getSize();
  std::unique_ptr< Shape *[] > tmpMatrix(new Shape *[newSize]);

  for (std::size_t i = 0; i < index; i++) {
    tmpMatrix[i] = shapesMatrix_[i];
  }
  tmpMatrix[index] = shape;
  for (std::size_t i = index + 1; i < newSize; i++) {
    tmpMatrix[i] = shapesMatrix_[i - 1];
  }
  shapesMatrix_ = std::move(tmpMatrix);

}

std::size_t pylaev::Matrix::getSize() const
{
  std::size_t size = 0;
  for (std::size_t i = 0; i < countOfLayers_; i++) {
    size += sizeOfLayers_[i];
  }

  return size;
}

std::size_t pylaev::Matrix::getCountOfLayers() const
{
  return countOfLayers_;
}

pylaev::Matrix::Layer::Layer(Shape ** shapes, std::size_t size):
  shapes_(new Shape *[size]),
  size_(size)
{
  if (shapes == nullptr) {
    throw std::invalid_argument("Pointer on array with layer's figures is null");
  }

  for (std::size_t i = 0; i < size_; i++) {
    shapes_[i] = shapes[i];
  }
}

pylaev::Shape * pylaev::Matrix::Layer::operator [](std::size_t index) const
{
  if (index >= size_) {
    throw std::out_of_range("There are not so many figures on the layer");
  }

  return shapes_[index];
}

std::size_t pylaev::Matrix::Layer::getSize()
{
  return size_;
}
