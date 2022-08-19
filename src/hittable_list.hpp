#pragma once

#include <memory>
#include <vector>

#include "src/hittable.hpp"

template <typename T>
class HittableList : public Hittable<T> {
 public:
  HittableList() {}
  HittableList(std::shared_ptr<Hittable<T>> object) { add(object); }

  void clear() { objects.clear(); }
  void add(std::shared_ptr<Hittable<T>> object) { objects.push_back(object); }

  virtual bool hit(const Ray<T>& r, T t_min, T t_max, HitRecord<T>& rec) const {
    HitRecord<T> temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
      if (object->hit(r, t_min, closest_so_far, temp_rec)) {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        rec = temp_rec;
      }
    }

    return hit_anything;
  }

 private:
  std::vector<std::shared_ptr<Hittable<T>>> objects;
};
