#pragma once

#include <cmath>
#include <cstdint>

class vec3 {
 public:
  vec3() : e{0, 0, 0} {}
  vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  double x() const;
  double y() const;
  double z() const;

  uint8_t r() const;
  void r(double t);
  uint8_t g() const;
  void g(double t);
  uint8_t b() const;
  void b(double t);

  vec3 operator-() const;
  double operator[](int i) const;
  double& operator[](int i);

  vec3& operator+=(const vec3& v);

  vec3& operator*=(const double scalar);

  vec3& operator/=(const double t);

  double length_squared() const;

  double length() const;

 protected:
  double e[3];
};

vec3 operator+(vec3 lhs, const vec3& rhs);

vec3 operator-(vec3 lhs, const vec3& rhs);

vec3 operator*(vec3 lhs, const vec3& rhs);
vec3 operator*(const double t, const vec3& v);
vec3 operator*(const vec3& v, const double t);

vec3 operator/(vec3 v, double t);

double dot(const vec3& lhs, const vec3& rhs);

vec3 cross(const vec3& lhs, const vec3& rhs);

vec3 unit_vector(vec3 v);

using point3 = vec3;
using color = vec3;
