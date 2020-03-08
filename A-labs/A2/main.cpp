#include <iostream>
#include <stdexcept>
#include <cassert>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

void exercisesAndPrintSpec(pylaev::Shape *);

int main(int, char * [])
{
  //Rectangle
  std::cout << "----------Work with the rectangle\n";
  pylaev::point_t center = {1.0, 8.0};
  try {
    pylaev::Rectangle rectangle_(center, 5.0, 9.0);
    exercisesAndPrintSpec(&rectangle_);
  }
  catch (std::invalid_argument & err) {
    std::cerr << err.what();
  }

  std::cout << std::endl;
  //Circle
  std::cout << "----------Work with the circle\n";
  center = {10.0, 80.0};
  try {
    pylaev::Circle circle_(center, 18.0);
    exercisesAndPrintSpec(&circle_);
  }
  catch (std::invalid_argument & err) {
    std::cerr << err.what();
  }

  std::cout << std::endl;
  //Triangle
  std::cout << "----------Work with the triangle\n";
  pylaev::point_t pointA = {0.0, 10.0};
  pylaev::point_t pointB = {0.0, 5.0};
  pylaev::point_t pointC = {5.0, 1.0};
  try {
    pylaev::Triangle triangle_(pointA, pointB, pointC);
    exercisesAndPrintSpec(&triangle_);
  }
  catch(std::invalid_argument & err) {
    std::cerr << err.what();
  }

  return 0;
}

void exercisesAndPrintSpec(pylaev::Shape * shapePtr)
{
  assert(shapePtr != nullptr);
  //exercises: two types of moving and scaling figure
  const double dx = 3.5;
  const double dy = 5.5;
  const pylaev::point_t newPoint = {10.0, 10.0};
  const double kScaling = 1.5;

  shapePtr->printSpec();
  shapePtr->move(dx, dy);
  std::cout << "After moving by " << dx << "; " << dy << "\n";
  shapePtr->printSpec();
  shapePtr->move(newPoint);
  std::cout << "After moving to the point (" << newPoint.x << "; " << newPoint.y << ")\n";
  shapePtr->printSpec();
  std::cout << "After scaling by " << kScaling << "\n";
  try {
    shapePtr->scale(kScaling);
    shapePtr->printSpec();
  } catch(std::invalid_argument & err) {
    std::cerr << err.what();
  }
}
