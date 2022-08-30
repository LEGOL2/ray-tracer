#pragma once

#include "src/hittable.hpp"
#include "src/material.hpp"

template <typename T>
class Sphere : public Hittable<T> {
 public:
  Sphere() {}
  Sphere(Point3<T> center, T radius, std::shared_ptr<Material<T>> material) : center(center), radius(radius), material(material) {}

  virtual bool hit(const Ray<T>& r, T t_min, T t_max, HitRecord<T>& rec) const override {
    Vec3<T> oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto delta = half_b * half_b - a * c;

    if (delta < 0) {
      return false;
    }
    auto sqrt_d = sqrt(delta);

    auto root = (-half_b - sqrt_d) / a;
    if (root < t_min || root > t_max) {
      root = (-half_b + sqrt_d) / a;
      if (root < t_min || root > t_max) {
        return false;
      }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3<T> outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.material = material;

    return true;
  }

 private:
  Point3<T> center;
  T radius;
  std::shared_ptr<Material<T>> material;
};
