#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>

struct Point_t
{
  int x, y;
};

using Shape = std::vector< Point_t >;

#endif //SHAPE_HPP
