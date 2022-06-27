#pragma once

#include <cmath>

template <typename T>
class vec3 {
 public:
  vec3() : e{0, 0, 0} {}
  vec3(T e0, T e1, T e2) : e{e0, e1, e2} {}

  T x() const { return e[0]; }
  T y() const { return e[1]; }
  T z() const { return e[2]; }

  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  T& operator[](int i) { return e[i]; }

  vec3& operator+=(const vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];

    return *this;
  }

  vec3& operator*=(const T& scalar) {
    e[0] *= scalar;
    e[1] *= scalar;
    e[2] *= scalar;

    return *this;
  }

  vec3& operator/=(const T t) { return *this *= 1 / t; }

  vec3 operator+(const vec3& v) { return vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]); }

  vec3 operator-(const vec3& v) { return vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]); }

  vec3 operator*(const vec3& v) { return vec3(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]); }

  vec3 operator*(T t) { return vec3(t * e[0], t * e[1], t * e[2]); }

  vec3 operator*=(T t) { return t * this; }

  vec3 operator/(T t) { return (1 / t) * this; }

  T dot(const vec3& lhs, const vec3& rhs) {
    return lhs.e[0] * rhs.e[0] + lhs.e[1] * rhs.e[1] + lhs.e[2] * rhs.e[2];
  }

  vec3 cross(const vec3& lhs, const vec3& rhs) {
    return vec3(lhs.e[1] * rhs.e[2] - lhs.e[2] * rhs.e[1],
                lhs.e[2] * rhs.e[0] - lhs.e[0] * rhs.e[2],
                lhs.e[0] * rhs.e[1] - lhs.e[1] * rhs.e[0]);
  }

  vec3 unit_vector(const vec3& v) { return v / v.length(); }

  double length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

  double length() const { return std::sqrt(length_squared()); }

 protected:
  T e[3];
};

template <typename T>
class point3 : public vec3<T> {
 public:
  point3() : vec3<T>() {}
  point3(T e0, T e1, T e2) : vec3<T>(e0, e1, e2) {}
};

template <typename T>
class color : public vec3<T> {
 public:
  color() : vec3<T>() {}
  color(T e0, T e1, T e2) : vec3<T>(e0, e1, e2) {}

  T r() const { return this->e[0]; }
  void r(double t) { this->e[0] = static_cast<int>(255.999 * t); }
  T g() const { return this->e[1]; }
  void g(double t) { this->e[1] = static_cast<int>(255.999 * t); }
  T b() const { return this->e[2]; }
  void b(double t) { this->e[2] = static_cast<int>(255.999 * t); }
};
