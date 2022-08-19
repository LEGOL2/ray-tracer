#pragma once

#include "src/math/ray.hpp"

struct HitRecord {
  Point3 p;
  Vec3 normal;
  double t;
  bool front_face;

  void set_face_normal(const Ray& r, const Vec3& outward_normal);
};

class Hittable {
 public:
  virtual ~Hittable() = default;
  virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};
