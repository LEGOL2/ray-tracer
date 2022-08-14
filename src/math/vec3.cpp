#include "src/math/vec3.hpp"

#include "src/math/utils.hpp"

double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

uint8_t vec3::r() const { return static_cast<uint8_t>(256 * clamp(e[0], 0.0, 0.999)); }
void vec3::r(double t) { e[0] = t; }

uint8_t vec3::g() const { return static_cast<uint8_t>(256 * clamp(e[1], 0.0, 0.999)); }
void vec3::g(double t) { e[1] = t; }

uint8_t vec3::b() const { return static_cast<uint8_t>(255 * clamp(e[2], 0.0, 0.999)); }
void vec3::b(double t) { e[2] = t; }

vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }

double vec3::operator[](int i) const { return e[i]; }
double& vec3::operator[](int i) { return e[i]; }

vec3& vec3::operator+=(const vec3& v) {
  e[0] += v.e[0];
  e[1] += v.e[1];
  e[2] += v.e[2];

  return *this;
}

vec3& vec3::operator*=(const double scalar) {
  e[0] *= scalar;
  e[1] *= scalar;
  e[2] *= scalar;

  return *this;
}

vec3& vec3::operator/=(const double t) { return *this *= 1 / t; }

double vec3::length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
double vec3::length() const { return std::sqrt(length_squared()); }

vec3 operator+(vec3 lhs, const vec3& rhs) { return vec3(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]); }

vec3 operator-(vec3 lhs, const vec3& rhs) { return vec3(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]); }

vec3 operator*(vec3 lhs, const vec3& rhs) { return vec3(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]); }
vec3 operator*(const double t, const vec3& v) { return vec3(t * v[0], t * v[1], t * v[2]); }
vec3 operator*(const vec3& v, const double t) { return t * v; }

vec3 operator/(vec3 v, double t) { return (1 / t) * v; }

double dot(const vec3& lhs, const vec3& rhs) { return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2]; }

vec3 cross(const vec3& lhs, const vec3& rhs) {
  return vec3(lhs[1] * rhs[2] - lhs[2] * rhs[1], lhs[2] * rhs[0] - lhs[0] * rhs[2], lhs[0] * rhs[1] - lhs[1] * rhs[0]);
}

vec3 unit_vector(vec3 v) { return v / v.length(); }
