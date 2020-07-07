#include <iostream>
#include <stdexcept>

#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

void exercisesAndPrintSpec(pylaev::Shape *);

int main(int, char * [])
{
  //Rectangle
  pylaev::Rectangle rectangle({ 0.0, 0.0 }, { 0.0, 2.0 }, { 4.0, 2.0 }, { 4.0, 0.0 });
  exercisesAndPrintSpec(&rectangle);

  pylaev::CompositeShape coShape; //Composite shape
  coShape.add(&rectangle);

  std::cout << std::endl;
  //Circle
  pylaev::point_t center = {2.0, 8.0};
  pylaev::Circle circle(center, 3.0);
  exercisesAndPrintSpec(&circle);

  coShape.add(&circle);

  std::cout << std::endl;
  //Triangle
  pylaev::point_t pointA = {0.0, 3.0};
  pylaev::point_t pointB = {0.0, 6.0};
  pylaev::point_t pointC = {4.0, 3.0};
  pylaev::Triangle triangle(pointA, pointB, pointC);
  exercisesAndPrintSpec(&triangle);

  coShape.add(&triangle);

  exercisesAndPrintSpec(&coShape);

  std::cout << "\n";
  pylaev::Matrix matrix = coShape.split();
  std::cout << "Matrix consists of " << matrix.getSize() << " figures which are arranged by " << matrix.getCountOfLayers() << " layers\n";

  return 0;
}

void exercisesAndPrintSpec(pylaev::Shape * shape)
{
  if (shape == nullptr) {
    throw std::invalid_argument("We can't do something with nothing");
  }
  //exercises: two types of moving, scaling and rotate figure
  shape->printSpec();

  const double dx = 1.0;
  const double dy = 1.0;
  std::cout << "---------- After moving by " << dx << "; " << dy << "\n";
  shape->move(dx, dy);
  shape->printSpec();

  const pylaev::point_t newPoint = {10.0, 10.0};
  std::cout << "---------- After moving to the point (" << newPoint.x << "; " << newPoint.y << ")\n";
  shape->move(newPoint);
  shape->printSpec();

  const double kScaling = 2.0;
  std::cout << "---------- After scaling by " << kScaling << "\n";
  shape->scale(kScaling);
  shape->printSpec();

  const double angle = 90.0;
  std::cout << "---------- After rotating by " << angle << " degrees" << "\n";
  shape->rotate(angle);
  shape->printSpec();
}
