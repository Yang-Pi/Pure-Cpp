#include "shape.hpp"
#include "circle.hpp"
#include "square.hpp"
#include "triangle.hpp"

#include <memory>

void task2();

namespace details {
  using shape_ptr = std::shared_ptr<Shape>;

  struct shapeData_t {
    std::string name;
    point_t center;
  };

  void parseShapeData(const std::string originLine, shapeData_t& shape);
  bool identifyShape(const shapeData_t& shape, shape_ptr& shapePtr);
}
