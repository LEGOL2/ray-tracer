#pragma once

#include "src/math/ray.hpp"

template <typename T>
class Material;

template <typename T>
struct HitRecord {
  Point3<T> p;
  Vec3<T> normal;
  std::shared_ptr<Material<T>> material;
  T t;
  bool front_face;

  void set_face_normal(const Ray<T>& r, const Vec3<T>& outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

template <typename T>
class Hittable {
 public:
  virtual ~Hittable() = default;
  virtual bool hit(const Ray<T>& r, T t_min, T t_max, HitRecord<T>& rec) const = 0;
};
