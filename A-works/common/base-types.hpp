#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace pylaev {
  struct point_t {
    double x;
    double y;
  };

  struct vector_t {
    double x;
    double y;
  };
  vector_t countVector(const point_t &, const point_t &);
  double countVectorProduct(const vector_t &, const vector_t &);

  struct rectangle_t {
    point_t pos; //coordinates of center
    double width;
    double height;
  };
  bool intersection(const rectangle_t &, const rectangle_t &);

}

#endif
