#pragma once

#include "src/math/ray.hpp"
#include "src/math/vec3.hpp"

class Camera {
 public:
  Camera();

  Ray get_ray(double u, double v) const;

 private:
  Point3 origin;
  Point3 upper_left_corner;
  Vec3 horizontal;
  Vec3 vertical;
};
