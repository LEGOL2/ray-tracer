#include "src/camera.hpp"

Camera::Camera(Point3<double> lookfrom, Point3<double> lookat, Vec3<double> vup, double vfov, double aspect_ratio) {
  auto theta = degrees_to_radians(vfov);
  auto h = tan(theta/2);
  auto viewport_height = 2.0 * h;
  auto viewport_width = aspect_ratio * viewport_height;
  // constexpr double focal_length = 1.0;

  auto w = unit_vector<double>(lookfrom - lookat);
  auto u = unit_vector<double>(cross<double>(vup, w));
  auto v = cross<double>(w, u);

  origin = lookfrom;
  horizontal = viewport_width * u;
  vertical = viewport_height * v;
  upper_left_corner = origin - horizontal / 2.0 + vertical / 2.0 - w;
}

Ray<double> Camera::get_ray(double u, double v) const {
  return Ray<double>(origin, upper_left_corner + u * horizontal - v * vertical - origin);
}
