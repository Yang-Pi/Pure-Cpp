#ifndef SHAPE_BY_COORDINATES_HPP
#define SHAPE_BY_COORDINATES_HPP

#include <iostream>
#include <cmath>

#include "base-types.hpp"

namespace pylaev {
  namespace detail {
    template < const std::size_t numVertices >
    class ShapeByCoordinates {
    public:
      static double getArea(const point_t * points);
      static point_t getCenter(const point_t * points);
      static double getSide(const point_t * points, std::size_t index);
      static rectangle_t getFrameRect(const point_t * points);

      static bool isConvex(const point_t * points);

      static void move(point_t * points, double dx, double dy);
      static void scale(point_t * points, const point_t & center, double kScaling);
      static void rotate(point_t * points, const point_t & center, double angle);
    };
  }
}

    template < std::size_t numVertices >
    double pylaev::detail::ShapeByCoordinates< numVertices >::getArea(const point_t * points)
    {
      if (points == nullptr) {
        throw std::invalid_argument("Pointer on array with figure's vertices is null");
      }
      double area = 0.0;
      for (std::size_t i = 0; i < numVertices; i++) {
        area += points[i].x * points[(i + 1) % numVertices].y -
            points[i].y * points[(i + 1) % numVertices].x;
      }

      return fabs(area) / 2;
    }

    template < std::size_t numVertices >
    pylaev::point_t pylaev::detail::ShapeByCoordinates< numVertices >::getCenter(const point_t * points)
    {
      if (points == nullptr) {
        throw std::invalid_argument("Pointer on array with figure's vertices is null");
      }
      double x = 0.0;
      double y = 0.0;
      for (std::size_t i = 0; i < numVertices; i++) {
        x += points[i].x;
        y += points[i].y;
      }

      return point_t {
          x / numVertices,
          y / numVertices
      };
    }

    template < std::size_t numVertices >
    double pylaev::detail::ShapeByCoordinates< numVertices >::getSide(const point_t * points, std::size_t index)
    {
      if (points == nullptr) {
        throw std::invalid_argument("Pointer on array with figure's vertices is null");
      }
      if (index >= numVertices) {
        throw std::out_of_range("Index of side is more than count of sides");
      }

      return sqrt(pow(points[(index + 1) % numVertices].x - points[index].x, 2)
          + pow(points[(index + 1) % numVertices].y - points[index].y, 2));
    }

    template < std::size_t numVertices >
    pylaev::rectangle_t pylaev::detail::ShapeByCoordinates< numVertices >::getFrameRect(const point_t * points)
    {
      if (points == nullptr) {
        throw std::invalid_argument("Pointer on array with figure's vertices is null");
      }
      //max/min coordinates of triangle (left top and rigth bottom)
      point_t maxCoordinates = points[0];
      point_t minCoordinates = points[0];
      for (std::size_t i = 1; i < numVertices; i++) {
        maxCoordinates.x = std::max(points[i].x, maxCoordinates.x);
        maxCoordinates.y = std::max(points[i].y, maxCoordinates.y);
        minCoordinates.x = std::min(points[i].x, minCoordinates.x);
        minCoordinates.y = std::min(points[i].y, minCoordinates.y);
      }
      double width = maxCoordinates.x - minCoordinates.x;
      double height = maxCoordinates.y - minCoordinates.y;
      point_t pos = {width / 2 + minCoordinates.x, height / 2 + minCoordinates.y};

      return { pos, width, height };
    }

    template < std::size_t numVertices >
    bool pylaev::detail::ShapeByCoordinates< numVertices >::isConvex(const point_t * points)
    {
      if (numVertices < 3) {
        throw std::invalid_argument("Polygon can not have less than three vertices");
      }
      if (points == nullptr) {
        throw std::invalid_argument("Pointer on array with figure's vertices is null");
      }

      int turn = 0;
      std::size_t index = 0;
      //define direction of passage
      for (std::size_t i = 0; i < numVertices; i++) {
        index++;
        vector_t vector1 = countVector(points[i], points[(i + 1) % numVertices]);
        vector_t vector2 = countVector(points[(i + 1) % numVertices], points[(i + 2) % numVertices]);
        if (countVectorProduct(vector1, vector2) > 0) {
          turn = 1;
          break;
        }
        if (countVectorProduct(vector1, vector2) < 0) {
          turn = -1;
          break;
        }
      }
      if (turn == 0) {
        throw std::logic_error("It's a stright line, coordinates of all vertices can't be on one line");
      }

      for (std::size_t i = index; i < numVertices; i++) {
        vector_t vector1 = countVector(points[i], points[(i + 1) % numVertices]);
        vector_t vector2 = countVector(points[(i + 1) % numVertices], points[(i + 2) % numVertices]);
        if (countVectorProduct(vector1, vector2) == 0) {
          continue; //it is a line segment by three points
        }
        if ((vector1.x * vector2.y - vector1.y * vector2.x) * turn  <= turn) {
          return false;
        }

        //check crossing sides (loops)
        for (std::size_t j = 0; j < i - 1; j++) {
          vector_t vector1 = countVector(points[i], points[(i + 1) % numVertices]);
          vector_t vector2 = countVector(points[j], points[i]);
          vector_t vector3 = countVector(points[j], points[(i + 1) % numVertices]);
          if (countVectorProduct(vector1, vector2) * countVectorProduct(vector1, vector3) < 0) {
            return false;
          }
          vector1 = countVector(points[j], points[j + 1]);
          vector2 = countVector(points[i], points[j]);
          vector3 = countVector(points[i], points[j + 1]);
          if (countVectorProduct(vector1, vector2) * countVectorProduct(vector1, vector3) < 0) {
            return false;
          }
        }
      }

      return true;
    }

    template < std::size_t numVertices >
    void pylaev::detail::ShapeByCoordinates< numVertices >::move(point_t * points, double dx, double dy)
    {
      if (points == nullptr) {
        throw std::invalid_argument("Pointer on array with figure's vertices is null");
      }

      for (std::size_t i = 0; i < numVertices; i++) {
        points[i].x += dx;
        points[i].y += dy;
      }
    }

    template < std::size_t numVertices >
    void pylaev::detail::ShapeByCoordinates< numVertices >::scale(point_t * points, const point_t & center, double kScaling)
    {
      if (points == nullptr) {
        throw std::invalid_argument("Pointer on array with figure's vertices is null");
      }
      if (kScaling <= 0.0) {
        throw std::invalid_argument("Coefficient of scaling must be positive");
      }

      for (std::size_t i = 0; i < numVertices; i++) {
        points[i].x = points[i].x * kScaling + center.x * (1 - kScaling);
        points[i].y = points[i].y * kScaling + center.y * (1 - kScaling);
      }
    }

    template < std::size_t numVertices >
    void pylaev::detail::ShapeByCoordinates< numVertices >::rotate(point_t * points, const point_t & center, double angle)
    {
      if (points == nullptr) {
        throw std::invalid_argument("Pointer on array with figure's vertices is null");
      }

      angle *= M_PI / 180.0;
      const double sin = std::sin(angle);
      const double cos = std::cos(angle);

      for (std::size_t i = 0; i < numVertices; i++) {
        const double x = points[i].x - center.x;
        const double y = points[i].y - center.y;

        points[i].x = center.x + x * cos + y * sin;
        points[i].y = center.y + y * cos - x * sin;
      }
    }

#endif
