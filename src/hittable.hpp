#pragma once

#include "src/math/ray.hpp"

struct hit_record {
  point3 p;
  vec3 normal;
  double t;
  bool front_face;

  void set_face_normal(const ray& r, const vec3& outward_normal);
};

class hittable {
 public:
  virtual ~hittable() = default;
  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
