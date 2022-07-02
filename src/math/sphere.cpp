#include "src/math/sphere.hpp"

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
  vec3 oc = r.origin() - center;
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
  vec3 outward_normal = (rec.p - center) / radius;
  rec.set_face_normal(r, outward_normal);

  return true;
}
