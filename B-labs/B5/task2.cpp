#include <iostream>
#include <exception>
#include <string>
#include <algorithm>
#include <boost/algorithm/string/trim.hpp>

#include "shape.hpp"

const int VERTICES_OF_TRIANGLE = 3;
const int VERTICES_OF_RECTANGLE = 4;
const int VERTICES_OF_PENTAGON = 5;

Shape readPoints(std::string line, std::size_t vertices);
bool isSquare(const Shape & shape);
bool isRectangle(const Shape & shape);

void task2()
{
  std::vector<Shape> shapesVect;

//1. fill container with shapes
  std::string line = "";
  while (std::getline(std::cin, line)) {
    if (std::cin.fail()) {
      throw std::ios_base::failure("Reading failed!\n");
    }

    boost::algorithm::trim_left(line);
    if (line.empty()) {
      continue;
    }

    std::size_t pos = line.find_first_of('(');
    if (pos == std::string::npos) {
      throw std::invalid_argument("Invalid view of shape description!\n");
    }
    //get number of vertices
    std::size_t nVertices = std::stoi(line.substr(0, pos));
    line.erase(0, pos);
    if (nVertices < VERTICES_OF_TRIANGLE) {
      throw std::invalid_argument("Incorrect number of vertices!\n");
    }

    Shape shape = readPoints(line, nVertices);
    shapesVect.push_back(shape);
  }

//2-3. count sum of all shapes' vertices and count of different shapes
  std::size_t countAllVertices = 0;

  std::size_t countTriangles = 0;
  std::size_t countSquares = 0;
  std::size_t countRectangles = 0;

  std::for_each(shapesVect.begin(), shapesVect.end(), [&](const Shape & shape) {
      countAllVertices += shape.size();
      if (shape.size() == VERTICES_OF_TRIANGLE) {
        ++countTriangles;
      }
      else if (shape.size() == VERTICES_OF_RECTANGLE) {
        if (isRectangle(shape)) {
          ++countRectangles;

          if (isSquare(shape)) {
            ++countSquares;
          }
        }
      }
  });

//4. Delete all pentagones
  shapesVect.erase(std::remove_if(shapesVect.begin(), shapesVect.end(),
      [](const Shape & shape) { return shape.size() == VERTICES_OF_PENTAGON; }), shapesVect.end());

//5. Create new container (vector) and write here one point of appropriate index
  Shape points(shapesVect.size());
  std::transform(shapesVect.begin(), shapesVect.end(), points.begin(),
    [](const Shape & shape) { return shape[0]; });

//6. Sort container: first - triangles, second - qquares, then - rectangles
  std::sort(shapesVect.begin(), shapesVect.end(), [](const Shape & lhs, const Shape & rhs) {
      if (lhs.size() < rhs.size()) {
        return true;
      }
      if ((lhs.size() == VERTICES_OF_RECTANGLE) && (rhs.size() == VERTICES_OF_RECTANGLE)) {
        if (isSquare(lhs)) {
          if (isSquare(rhs)) {
            return lhs[0].x < rhs[0].x;
          }
          return true;
        }
      }
      return false;
  });

//7. Print the results
  std::cout << "Vertices: " << countAllVertices << '\n';
  std::cout << "Triangles: " << countTriangles << '\n';
  std::cout << "Squares: " << countSquares << '\n';
  std::cout << "Rectangles: " << countRectangles << '\n';

  std::cout << "Points: ";
  for (const auto& point : points) {
    std::cout << '(' << point.x << ';' << point.y << ") ";
  }
  std::cout << '\n';

  std::cout << "Shapes: \n";
  for (const auto & shape : shapesVect) {
    std::cout << shape.size();
    for (const auto& point : shape) {
      std::cout << " (" << point.x << ';' << point.y << ") ";
    }
    std::cout << '\n';
  }
}
