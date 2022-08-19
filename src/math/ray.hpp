#pragma once

#include "src/math/vec3.hpp"

template <typename T>
class Ray {
 public:
  Ray() {}
  Ray(const Point3<T>& origin, const Vec3<T>& direction) : orig(origin), dir(direction) {}

  Point3<T> origin() const { return orig; }
  Vec3<T> direction() const { return dir; }

  Point3<T> at(double t) const { return orig + t * dir; }

 private:
  Point3<T> orig;
  Vec3<T> dir;
};
