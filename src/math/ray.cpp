#include "src/math/ray.hpp"

Point3 Ray::origin() const { return orig; }
Vec3 Ray::direction() const { return dir; }

Point3 Ray::at(double t) const { return orig + t * dir; }
