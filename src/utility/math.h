#ifndef CONSTRUCT_UTILITY_MATH_H_
#define CONSTRUCT_UTILITY_MATH_H_

#include <cstring>
#include <cmath>

namespace construct {
namespace utility {
namespace math {

inline double LinearInterpolation(double x0, double x1,
                                  double y0, double y1,
                                  double x) {
  assert(x1 - x0 != 0.0);
  return ((x - x0)*y1 + (x1 - x)*y0)/(x1 - x0);
}

} // namespace math
} // namespace utility
} // namespace construct

#endif
