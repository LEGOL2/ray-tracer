#include "src/math/utils.hpp"

#include "src/math/constants.hpp"

double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }

double clamp(double x, double min, double max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}
