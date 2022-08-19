#pragma once

#include "src/math/ray.hpp"
#include "src/math/vec3.hpp"

class Camera {
 public:
  Camera();

  Ray<double> get_ray(double u, double v) const;

 private:
  Point3<double> origin;
  Point3<double> upper_left_corner;
  Vec3<double> horizontal;
  Vec3<double> vertical;
};
