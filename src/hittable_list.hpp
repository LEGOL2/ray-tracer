#pragma once

#include <memory>
#include <vector>

#include "src/hittable.hpp"

class HittableList : public Hittable {
 public:
  HittableList() {}
  HittableList(std::shared_ptr<Hittable> object);

  void clear();
  void add(std::shared_ptr<Hittable> object);

  virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;

 private:
  std::vector<std::shared_ptr<Hittable>> objects;
};
