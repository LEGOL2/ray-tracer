#pragma once

#include <memory>
#include <vector>

#include "src/hittable.hpp"

class hittable_list : public hittable {
 public:
  hittable_list() {}
  hittable_list(std::shared_ptr<hittable> object);

  void clear();
  void add(std::shared_ptr<hittable> object);

  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;

 private:
  std::vector<std::shared_ptr<hittable>> objects;
};
