#include <iostream>
#include <stdexcept>
#include <cassert>

#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

void exercisesAndPrintSpec(pylaev::Shape *);

int main(int, char * [])
{
  //Rectangle
  pylaev::point_t center = {1.0, 1.0};
  pylaev::Rectangle rectangle_(center, 2.0);
  exercisesAndPrintSpec(&rectangle_);

  pylaev::CompositeShape coShape_;
  coShape_.add(&rectangle_); //Composite shape

  std::cout << std::endl;
  //Circle
  center = {5.0, 1.0};
  pylaev::Circle circle_(center, 2.0);
  exercisesAndPrintSpec(&circle_);

  coShape_.add(&circle_);

  std::cout << std::endl;
  //Triangle
  pylaev::point_t pointA = {2.0, 2.0};
  pylaev::point_t pointB = {2.0, 6.0};
  pylaev::point_t pointC = {5.0, 2.0};
  pylaev::Triangle triangle_(pointA, pointB, pointC);
  exercisesAndPrintSpec(&triangle_);

  coShape_.add(&triangle_);

  exercisesAndPrintSpec(&coShape_);

  return 0;
}

void exercisesAndPrintSpec(pylaev::Shape * shapePtr)
{
  assert(shapePtr != nullptr);
  //exercises: two types of moving and scaling figure
  const double dx = 1.0;
  const double dy = 1.0;
  const pylaev::point_t newPoint = {10.0, 10.0};
  const double kScaling = 2.0;

  shapePtr->printSpec();
  shapePtr->move(dx, dy);
  std::cout << "----------After moving by " << dx << "; " << dy << "\n";
  shapePtr->printSpec();
  shapePtr->move(newPoint);
  std::cout << "----------After moving to the point (" << newPoint.x << "; " << newPoint.y << ")\n";
  shapePtr->printSpec();
  std::cout << "----------After scaling by " << kScaling << "\n";
  try {
    shapePtr->scale(kScaling);
    shapePtr->printSpec();
  } catch(std::invalid_argument & err) {
    std::cerr << err.what();
  }
}
