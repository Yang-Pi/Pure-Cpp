#include <string>
#include <iostream>
#include <exception>
#include <cmath>
#include <boost/algorithm/string/trim.hpp>

#include "shape.hpp"

Shape readPoints(std::string line, std::size_t vertices)
{
  Shape shape;
  std::size_t posOpenBracket = std::string::npos;
  std::size_t posSemicolon = std::string::npos;
  std::size_t posCloseBracket = std::string::npos;

  for (std::size_t i = 0; i < vertices; i++) {
    if (line.empty()) {
      throw std::invalid_argument("Invalid number of vertices!\n");
    }
    boost::algorithm::trim_left(line);

    posOpenBracket = line.find_first_of('(');
    posSemicolon = line.find_first_of(';');
    posCloseBracket = line.find_first_of(')');

    if ((posOpenBracket == std::string::npos) || (posSemicolon == std::string::npos) || (posCloseBracket == std::string::npos)) {
      throw std::invalid_argument("Invalid point declaration!\n");
    }

    Point_t point {
        std::stoi(line.substr(posOpenBracket + 1, posSemicolon - posOpenBracket - 1)),
        std::stoi(line.substr(posSemicolon + 1, posCloseBracket - posSemicolon - 1)) };

    line.erase(0, posCloseBracket + 1);
    shape.push_back(point);
  }

  boost::algorithm::trim_left(line);
  if (!line.empty()) {
    throw std::invalid_argument("Too much points!\n");
  }

  return shape;
}

int getSquareDistance(const Point_t & lhs, const Point_t & rhs)
{
  return (lhs.x - rhs.x)*(lhs.x - rhs.x) + (lhs.y - rhs.y)*(lhs.y - rhs.y);
}

bool isRectangle(const Shape & shape)
{
  int diagonal1 = getSquareDistance(shape[0], shape[2]);
  int diagonal2 = getSquareDistance(shape[1], shape[3]);

  return diagonal1 == diagonal2;
}

bool isSquare(const Shape & shape)
{
  if (isRectangle(shape)) {
    int a = getSquareDistance(shape[0], shape[1]);
    int b = getSquareDistance(shape[1], shape[2]);
    int c = getSquareDistance(shape[2], shape[3]);
    int d = getSquareDistance(shape[3], shape[0]);

    if ((a == b) && (b == c) && (c == d)) {
      return true;
    }
  }
  return false;
}
