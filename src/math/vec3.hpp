#pragma once

#include <cmath>
#include <cstdint>

class Vec3 {
 public:
  Vec3() : e{0, 0, 0} {}
  Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  double x() const;
  double y() const;
  double z() const;

  uint8_t r() const;
  void r(double t);
  uint8_t g() const;
  void g(double t);
  uint8_t b() const;
  void b(double t);

  Vec3 operator-() const;
  double operator[](int i) const;
  double& operator[](int i);

  Vec3& operator+=(const Vec3& v);

  Vec3& operator*=(const double scalar);

  Vec3& operator/=(const double t);

  double length_squared() const;

  double length() const;

 protected:
  double e[3];
};

Vec3 operator+(Vec3 lhs, const Vec3& rhs);

Vec3 operator-(Vec3 lhs, const Vec3& rhs);

Vec3 operator*(Vec3 lhs, const Vec3& rhs);
Vec3 operator*(const double t, const Vec3& v);
Vec3 operator*(const Vec3& v, const double t);

Vec3 operator/(Vec3 v, double t);

double dot(const Vec3& lhs, const Vec3& rhs);

Vec3 cross(const Vec3& lhs, const Vec3& rhs);

Vec3 unit_vector(Vec3 v);

using Point3 = Vec3;
using Color = Vec3;
