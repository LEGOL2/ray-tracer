#pragma once

#include "src/hittable.hpp"

class Sphere : public Hittable {
 public:
  Sphere() {}
  Sphere(Point3 cen, double r) : center(cen), radius(r) {}

  virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

 private:
  Point3 center;
  double radius;
};
