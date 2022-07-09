#include "src/camera.hpp"

camera::camera() {
  constexpr double aspect_ratio = 16.0 / 9.0;
  constexpr double viewport_height = 2.0;
  constexpr double viewport_width = aspect_ratio * viewport_height;
  constexpr double focal_length = 1.0;

  origin = point3(0, 0, 0);
  horizontal = vec3(viewport_width, 0.0, 0.0);
  vertical = vec3(0.0, viewport_height, 0.0);
  upper_left_corner = origin - horizontal / 2 + vertical / 2 - vec3(0, 0, focal_length);
}

ray camera::get_ray(double u, double v) const {
  return ray(origin, upper_left_corner + u * horizontal - v * vertical - origin);
}
