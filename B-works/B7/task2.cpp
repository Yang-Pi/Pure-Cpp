#include <list>
#include <algorithm>
#include <iterator>
#include <exception>
#include <memory>
#include <sstream>
#include <boost/algorithm/string/trim.hpp>

#include "shape.hpp"
#include "circle.hpp"
#include "square.hpp"
#include "triangle.hpp"

using shape_ptr = std::shared_ptr<Shape>;

void parseShapeData(const std::string originLine, std::string& shape, point_t& center);

void task2()
{
  std::list<shape_ptr> shapeList;

  std::string line = "";
  while (std::getline(std::cin >> std::ws, line)) {
    if (line.empty()) {
      continue;
    }

    std::string shape = "";
    point_t center;
    parseShapeData(line, shape, center);

    shape_ptr shapePtr = nullptr;
    bool shapeIsAvailable = false;

    if (shape == "CIRCLE") {
      shapePtr = std::make_shared<Circle>(center);
      shapeIsAvailable = true;
    }
    else if (shape == "SQUARE") {
      shapePtr = std::make_shared<Square>(center);
      shapeIsAvailable = true;
    }
    else if (shape == "TRIANGLE") {
      shapePtr = std::make_shared<Triangle>(center);
      shapeIsAvailable = true;
    }

    if (shapeIsAvailable) {
      shapeList.push_back(shapePtr);
    }
    else {
      throw std::invalid_argument("Invalid type of shape!");
    }
  }

  std::cout << "Original:\n";
  std::for_each(shapeList.begin(),shapeList.end(), [](const shape_ptr& ptr) { ptr->draw(); });

  std::cout << "Left-Right:\n";
  shapeList.sort([](const shape_ptr& lhs, const shape_ptr& rhs)
        { return lhs->isMoreLeft(*rhs); });
  std::for_each(shapeList.begin(),shapeList.end(), [](const shape_ptr& ptr) { ptr->draw(); });

  std::cout << "Right-Left:\n";
  shapeList.sort([](const shape_ptr& lhs, const shape_ptr& rhs)
        { return rhs->isMoreLeft(*lhs); });
  std::for_each(shapeList.begin(),shapeList.end(), [](const shape_ptr& ptr) { ptr->draw(); });

  std::cout << "Top-Bottom:\n";
  shapeList.sort([](const shape_ptr& lhs, const shape_ptr& rhs)
        { return lhs->isUpper(*rhs); });
  std::for_each(shapeList.begin(),shapeList.end(), [](const shape_ptr& ptr) { ptr->draw(); });

  std::cout << "Bottom-Top:\n";
  shapeList.sort([](const shape_ptr& lhs, const shape_ptr& rhs)
        { return rhs->isUpper(*lhs); });
  std::for_each(shapeList.begin(),shapeList.end(), [](const shape_ptr& ptr) { ptr->draw(); });
}

void parseShapeData(const std::string originLine, std::string& shape, point_t& center)
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

  shape = tmpShape;
  center = {x, y};
}
