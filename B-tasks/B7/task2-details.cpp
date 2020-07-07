#include <boost/algorithm/string/trim.hpp>
#include <exception>
#include <sstream>

#include "task2.hpp"

void details::parseShapeData(const std::string originLine, shapeData_t& shape)
{
  std::string line = originLine;
  std::stringstream shapeStrStream(line);

  std::string tmpShape = "";
  int x, y;
  std::string trash = "";

  std::getline(shapeStrStream >> std::ws, tmpShape, '(');
  boost::algorithm::trim(tmpShape);

  shapeStrStream >> x;
  std::getline(shapeStrStream, trash, ';');
  shapeStrStream >> y;
  std::getline(shapeStrStream, trash, ')');

  if (shapeStrStream.fail()) {
    throw std::invalid_argument("Incorrect input");
  }

  shape.name = tmpShape;
  shape.center = {x, y};
}

bool details::identifyShape(const shapeData_t& shape, shape_ptr& shapePtr)
{
  bool shapeIsAvailable = false;

  if (shape.name == "CIRCLE") {
    shapePtr = std::make_shared<Circle>(shape.center);
    shapeIsAvailable = true;
  }
  else if (shape.name == "SQUARE") {
    shapePtr = std::make_shared<Square>(shape.center);
    shapeIsAvailable = true;
  }
  else if (shape.name == "TRIANGLE") {
    shapePtr = std::make_shared<Triangle>(shape.center);
    shapeIsAvailable = true;
  }

  return shapeIsAvailable;
}
