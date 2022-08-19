#pragma once

double degrees_to_radians(double degrees);

template <typename T>
T clamp(const T& x, const T& min, const T& max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}
