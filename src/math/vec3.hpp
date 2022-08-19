#pragma once

#include <cmath>
#include <cstdint>

#include "src/math/utils.hpp"

template <typename T>
class Vec3 {
 public:
  Vec3() = default;
  Vec3(T x, T y, T z) : e{std::move(x), std::move(y), std::move(z)} {}

  T x() const { return e[0]; }
  T y() const { return e[1]; }
  T z() const { return e[2]; }

  uint8_t r() const { return static_cast<uint8_t>(256 * clamp<T>(e[0], 0.0, 0.999)); }
  void r(T t) { e[0] = t; }

  uint8_t g() const { return static_cast<uint8_t>(256 * clamp<T>(e[1], 0.0, 0.999)); }
  void g(T t) { e[1] = t; }

  uint8_t b() const { return static_cast<uint8_t>(256 * clamp<T>(e[2], 0.0, 0.999)); }
  void b(T t) { e[2] = t; }

  Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }

  T operator[](int i) const { return e[i]; }
  T &operator[](int i) { return e[i]; }

  Vec3 &operator+=(const Vec3 &&v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];

    return *this;
  }

  Vec3 &operator*=(const T scalar) {
    e[0] *= scalar;
    e[1] *= scalar;
    e[2] *= scalar;

    return *this;
  }

  Vec3 &operator/=(const T t) { return *this *= 1 / t; }

  T length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

  T length() const { return std::sqrt(length_squared()); }

 private:
  T e[3];
};

template <typename T>
Vec3<T> operator+(const Vec3<T> &lhs, const Vec3<T> &rhs) {
  return Vec3<T>(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}

template <typename T>
Vec3<T> operator-(const Vec3<T> &lhs, const Vec3<T> &rhs) {
  return Vec3<T>(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
}

template <typename T>
Vec3<T> operator*(const Vec3<T> &lhs, const Vec3<T> &rhs) {
  return Vec3<T>(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]);
}

template <typename T>
Vec3<T> operator*(const T &t, const Vec3<T> &v) {
  return Vec3<T>(t * v[0], t * v[1], t * v[2]);
}

template <typename T>
Vec3<T> operator*(const Vec3<T> &v, const T &t) {
  return t * v;
}

template <typename T>
Vec3<T> operator/(const Vec3<T> &v, T &t) {
  return (1 / t) * v;
}

template <typename T>
Vec3<T> operator/(const Vec3<T> &v, T &&t) {
  return (1 / t) * v;
}

template <typename T>
Vec3<T> operator/(const Vec3<T> &v, const T &t) {
  return (1 / t) * v;
}

template <typename T>
T dot(const Vec3<T> &lhs, const Vec3<T> &rhs) {
  return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}

template <typename T>
Vec3<T> cross(const Vec3<T> &lhs, const Vec3<T> &rhs) {
  return Vec3<T>(lhs[1] * rhs[2] - lhs[2] * rhs[1], lhs[2] * rhs[0] - lhs[0] * rhs[2],
                 lhs[0] * rhs[1] - lhs[1] * rhs[0]);
}

template <typename T>
Vec3<T> unit_vector(const Vec3<T> &v) {
  return v / v.length();
}

template <typename T>
using Point3 = Vec3<T>;

using Color = Vec3<double>;
