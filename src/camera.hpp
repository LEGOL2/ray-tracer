#pragma once

#include "src/math/ray.hpp"
#include "src/math/vec3.hpp"

class camera {
 public:
  camera();

  ray get_ray(double u, double v) const;

 private:
  point3 origin;
  point3 upper_left_corner;
  vec3 horizontal;
  vec3 vertical;
};
