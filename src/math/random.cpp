#include "src/math/random.hpp"

#include <random>

template <>
double random_T<double>() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;

  return distribution(generator);
}

template <>
double random_T<double>(double min, double max) {
  return min + (max - min) * random_T<double>();
}

template <>
Vec3<double> random_in_unit_sphere<double>() {
  while (true) {
    Vec3<double> p = random<double>(-1.0, 1.0);
    if (p.length_squared() >= 1.0) continue;

    return p;
  }
}


template <>
Vec3<double> random_in_unit_disk() {
  while(true) {
    auto p = Vec3<double>(random_T<double>(-1.0, 1.0), random_T<double>(-1.0, 1.0), 0);
    if (p.length_squared() >= 1.0) continue;

    return p;
  }
}
