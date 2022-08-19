#include "src/camera.hpp"

Camera::Camera() {
  constexpr double aspect_ratio = 16.0 / 9.0;
  constexpr double viewport_height = 2.0;
  constexpr double viewport_width = aspect_ratio * viewport_height;
  constexpr double focal_length = 1.0;

  origin = Point3<double>(0.0, 0.0, 0.0);
  horizontal = Vec3(viewport_width, 0.0, 0.0);
  vertical = Vec3(0.0, viewport_height, 0.0);
  upper_left_corner = origin - horizontal / 2.0 + vertical / 2.0 - Vec3(0.0, 0.0, focal_length);
}

Ray<double> Camera::get_ray(double u, double v) const {
  return Ray<double>(origin, upper_left_corner + u * horizontal - v * vertical - origin);
}
