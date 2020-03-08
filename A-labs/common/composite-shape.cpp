#include "composite-shape.hpp"

#include <utility>
#include <stdexcept>
#include <cmath>

pylaev::CompositeShape::CompositeShape():
  size_(0),
  freeCells_(0),
  shapesArray_()
{ }

pylaev::CompositeShape::CompositeShape(const CompositeShape & other):
  size_(other.size_),
  freeCells_(other.freeCells_),
  shapesArray_(new Shape *[other.size_])
{
  for (std::size_t i = 0; i < size_; i++) {
    shapesArray_[i] = other.shapesArray_[i];
  }
}

pylaev::CompositeShape::CompositeShape(CompositeShape && other):
  size_(other.size_),
  freeCells_(other.freeCells_),
  shapesArray_(std::move(other.shapesArray_))
{
  other.size_ = 0;
  other.freeCells_ = 0;
}

pylaev::CompositeShape::CompositeShape(std::size_t size):
  size_(0),
  freeCells_(size),
  shapesArray_(new Shape *[size])
{
  for (std::size_t i = 0; i < size_; i++) {
    shapesArray_[i] = nullptr;
  }
}

pylaev::CompositeShape & pylaev::CompositeShape::operator =(const CompositeShape & other)
{
  if (this != &other) {
    size_ = other.size_;
    freeCells_ = other.freeCells_;
    shapesArray_.reset(new Shape *[other.size_]);
    for (std::size_t i = 0; i < other.size_; i++) {
      shapesArray_[i] = other.shapesArray_[i];
    }
  }

  return *this;
}

pylaev::CompositeShape & pylaev::CompositeShape::operator =(CompositeShape && other)
{
  if (this != &other) {
    size_ = other.size_;
    freeCells_ = other.freeCells_;
    other.size_ = 0;
    other.freeCells_ = 0;
    shapesArray_ = std::move(other.shapesArray_);
  }

  return *this;
}

pylaev::Shape * pylaev::CompositeShape::operator [](std::size_t index) const
{
  if (index >= size_) {
    throw std::out_of_range("There are not so many figures here - index is out of range");
  }

  return shapesArray_[index];
}

void pylaev::CompositeShape::add(Shape * shape)
{
  if (shape == nullptr) {
    throw std::invalid_argument("There is no any figure to add - shape pointer is null");
  }

  std::size_t newSize = 0;
  if (freeCells_ > 0) {
    shapesArray_[size_] = shape;
    size_++;
    freeCells_--;
  }
  else {
    if (size_ > 0) {
      newSize = static_cast< int >(size_ * kMemory_);
    } else {
      newSize = 2;
  }

    CompositeShape tmpObject(newSize);
    for (std::size_t i = 0; i < size_; i++) {
      tmpObject.shapesArray_[i] = shapesArray_[i];
    }
    tmpObject.shapesArray_[size_] = shape;
    tmpObject.size_ = ++size_;
    tmpObject.freeCells_ = tmpObject.freeCells_ - tmpObject.size_;

    *this = std::move(tmpObject);
  }
}

void pylaev::CompositeShape::remove(std::size_t index)
{
  if (index >= size_) {
    throw std::out_of_range("There are not so many figures here - index is out of range");
  }
  for (std::size_t i = index; i < size_ - 1; i++) {
    shapesArray_[i] = shapesArray_[i + 1];
  }
  size_--;
  shapesArray_[size_] = nullptr;
  freeCells_++;
}

void pylaev::CompositeShape::remove(const Shape * shape)
{
  if (shape == nullptr) {
    throw std::invalid_argument("Nothing can not be deleted - shape pointer is null");
  }
  std::size_t i = 0;
  while ((i < size_) && (shape != shapesArray_[i])) {
    i++;
  }
  if (i == size_) {
    throw std::invalid_argument("There is not such figure in composite shape");
  }
  remove(i);
}

double pylaev::CompositeShape::getArea() const
{
  double area = 0.0;
  for (std::size_t i = 0; i < size_; i++) {
    area += shapesArray_[i]->getArea();
  }

  return area;
}

pylaev::point_t pylaev::CompositeShape::getCenter() const
{
  return getFrameRect().pos;
}

pylaev::rectangle_t pylaev::CompositeShape::getFrameRect() const
{
  if (size_ == 0) {
    throw std::logic_error("Composite shape is empty");
  }

  rectangle_t tmpFrameRec = shapesArray_[0]->getFrameRect();
  point_t maxCoordinates = {tmpFrameRec.pos.x + tmpFrameRec.width / 2, tmpFrameRec.pos.y + tmpFrameRec.height / 2};
  point_t minCoordinates = {tmpFrameRec.pos.x - tmpFrameRec.width / 2, tmpFrameRec.pos.y - tmpFrameRec.height / 2};

  for (std::size_t i = 1; i < size_; i++) {
    tmpFrameRec = shapesArray_[i]->getFrameRect();
    maxCoordinates.x = std::max(maxCoordinates.x, tmpFrameRec.pos.x + tmpFrameRec.width / 2);
    maxCoordinates.y = std::max(maxCoordinates.y, tmpFrameRec.pos.y + tmpFrameRec.height / 2);
    minCoordinates.x = std::min(minCoordinates.x, tmpFrameRec.pos.x - tmpFrameRec.width / 2);
    minCoordinates.y = std::min(minCoordinates.y, tmpFrameRec.pos.y - tmpFrameRec.height / 2);
  }

  double width = maxCoordinates.x - minCoordinates.x;
  double height = maxCoordinates.y - minCoordinates.y;
  point_t pos = {minCoordinates.x + width / 2, minCoordinates.y + height / 2};

  return { pos, width, height };
}

void pylaev::CompositeShape::move(double dx, double dy)
{
  if (size_ == 0) {
    throw std::invalid_argument("Composite shape is empty");
  }
  for (std::size_t i = 0; i < size_; i++) {
    shapesArray_[i]->move(dx, dy);
  }
}

void pylaev::CompositeShape::move(const point_t & pos)
{
  const point_t center = getCenter();
  move(pos.x - center.x, pos.y - center.y);
}

void pylaev::CompositeShape::scale(double kScaling)
{
  if (kScaling <= 0.0) {
    throw std::invalid_argument("Coefficient of scaling must be positive");
  }

  point_t pos = getCenter();
  for (std::size_t i = 0; i < size_; i++) {
    //get new coordnates of shape's center (where it will be after scaling)
    const point_t center = shapesArray_[i]->getCenter();
    double x = center.x * kScaling + pos.x * (1 - kScaling);
    double y = center.y * kScaling + pos.y * (1 - kScaling);
    shapesArray_[i]->move({x, y});

    shapesArray_[i]->scale(kScaling);
  }
}

void pylaev::CompositeShape::rotate(double angle)
{
  angle *= M_PI / 180.0;
  const double sin = std::sin(angle);
  const double cos = std::cos(angle);
  const point_t center = getCentroid();

  for (std::size_t i = 0; i < size_; i++) {
    const point_t shapeCenter = shapesArray_[i]->getCenter();
    double x = center.x + (shapeCenter.x - center.x) * cos + (shapeCenter.y - center.y) * sin;
    double y = center.y + (shapeCenter.y - center.y) * cos - (shapeCenter.x - center.x )* sin;
    shapesArray_[i]->move(x, y);

    shapesArray_[i]->rotate(angle);
  }
}

pylaev::Matrix pylaev::CompositeShape::split() const
{
  Matrix matrix;

  if (size_ == 0) {
    return matrix;
  }

  std::size_t shapesLayers[size_];
  for (std::size_t i = 0; i < size_; i++) {
    shapesLayers[i] = 0;
  }

  for (std::size_t i = 0; i < size_; i++) {
    matrix.add(shapesArray_[i], shapesLayers[i]);
    rectangle_t shapeFrameRect = shapesArray_[i]->getFrameRect();
    for (std::size_t j = i + 1; j < size_; j++) {
      if (intersection(shapeFrameRect, shapesArray_[j]->getFrameRect())) {
        shapesLayers[j] = std::max(shapesLayers[j], shapesLayers[i] + 1);
      }
    }
  }

  return matrix;
}

pylaev::point_t pylaev::CompositeShape::getCentroid() const
{
  if (size_ == 0) {
    throw std::logic_error("Composite shape is empty");
  }

  double x = 0.0;
  double y = 0.0;

  for (std::size_t i = 0; i < size_; i++) {
    const point_t center = shapesArray_[i]->getCenter();
    x += center.x;
    y += center.y;
  }

  return point_t {
      x / size_,
      y / size_
  };
}

std::size_t pylaev::CompositeShape::getSize() const
{
  return size_;
}

void pylaev::CompositeShape::printSpec() const
{
  if (size_ == 0) {
    std::cout << "Composite shape is empty\n";
  } else {
    std::cout << "\n ***** Composite shape consists of " << size_ << " figures\n"
        << "Frame rectangle's width and height are " << getFrameRect().width << " and " << getFrameRect().height
        << ", center is in point (" << getCenter().x << "; " << getCenter().y << ")"
        << "; area of composite shape is " << getArea() << "\n";
    for (std::size_t i = 0; i < size_; i++) {
      std::cout << "======= Figure " << i << "\n";
      shapesArray_[i]->printSpec();
    }
  }
}
