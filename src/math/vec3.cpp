#include "src/math/vec3.hpp"

#include "src/math/utils.hpp"

double Vec3::x() const { return e[0]; }
double Vec3::y() const { return e[1]; }
double Vec3::z() const { return e[2]; }

uint8_t Vec3::r() const { return static_cast<uint8_t>(256 * clamp(e[0], 0.0, 0.999)); }
void Vec3::r(double t) { e[0] = t; }

uint8_t Vec3::g() const { return static_cast<uint8_t>(256 * clamp(e[1], 0.0, 0.999)); }
void Vec3::g(double t) { e[1] = t; }

uint8_t Vec3::b() const { return static_cast<uint8_t>(255 * clamp(e[2], 0.0, 0.999)); }
void Vec3::b(double t) { e[2] = t; }

Vec3 Vec3::operator-() const { return Vec3(-e[0], -e[1], -e[2]); }

double Vec3::operator[](int i) const { return e[i]; }
double& Vec3::operator[](int i) { return e[i]; }

Vec3& Vec3::operator+=(const Vec3& v) {
  e[0] += v.e[0];
  e[1] += v.e[1];
  e[2] += v.e[2];

  return *this;
}

Vec3& Vec3::operator*=(const double scalar) {
  e[0] *= scalar;
  e[1] *= scalar;
  e[2] *= scalar;

  return *this;
}

Vec3& Vec3::operator/=(const double t) { return *this *= 1 / t; }

double Vec3::length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
double Vec3::length() const { return std::sqrt(length_squared()); }

Vec3 operator+(Vec3 lhs, const Vec3& rhs) { return Vec3(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]); }

Vec3 operator-(Vec3 lhs, const Vec3& rhs) { return Vec3(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]); }

Vec3 operator*(Vec3 lhs, const Vec3& rhs) { return Vec3(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]); }
Vec3 operator*(const double t, const Vec3& v) { return Vec3(t * v[0], t * v[1], t * v[2]); }
Vec3 operator*(const Vec3& v, const double t) { return t * v; }

Vec3 operator/(Vec3 v, double t) { return (1 / t) * v; }

double dot(const Vec3& lhs, const Vec3& rhs) { return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2]; }

Vec3 cross(const Vec3& lhs, const Vec3& rhs) {
  return Vec3(lhs[1] * rhs[2] - lhs[2] * rhs[1], lhs[2] * rhs[0] - lhs[0] * rhs[2], lhs[0] * rhs[1] - lhs[1] * rhs[0]);
}

Vec3 unit_vector(Vec3 v) { return v / v.length(); }
