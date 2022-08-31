#pragma once

#include "src/math/vec3.hpp"

template <typename T>
T random_T();

template <typename T>
T random_T(T min, T max);

template <typename T>
Vec3<T> random() {
  return Vec3<T>(random_T<T>(), random_T<T>(), random_T<T>());
}

template <typename T>
Vec3<T> random(T min, T max) {
  return Vec3<T>(random_T<T>(min, max), random_T<T>(min, max), random_T<T>(min, max));
}

// Generate point indside unit sphere using rejection algorithm
template <typename T>
Vec3<T> random_in_unit_sphere();

template <typename T>
Vec3<T> random_unit_vector() {
    return unit_vector(random_in_unit_sphere<T>());
}

template <typename T>
Vec3<T> random_in_unit_disk();
