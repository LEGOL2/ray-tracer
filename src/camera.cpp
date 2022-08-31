#include "src/camera.hpp"
#include "src/math/random.hpp"

Camera::Camera(Point3<double>& lookfrom, Point3<double>& lookat, Vec3<double>& vup, double vfov, double aspect_ratio, double aperture, double focus_dist) {
  auto theta = degrees_to_radians(vfov);
  auto h = tan(theta/2);
  auto viewport_height = 2.0 * h;
  auto viewport_width = aspect_ratio * viewport_height;
  // constexpr double focal_length = 1.0;

  w = unit_vector<double>(lookfrom - lookat);
  u = unit_vector<double>(cross<double>(vup, w));
  v = cross<double>(w, u);

  origin = lookfrom;
  horizontal = focus_dist * viewport_width * u;
  vertical = focus_dist * viewport_height * v;
  upper_left_corner = origin - horizontal / 2.0 + vertical / 2.0 - focus_dist * w;
  lens_radius = aperture / 2.0;
}

Ray<double> Camera::get_ray(double s, double t) const {
  Vec3<double> rd = lens_radius * random_in_unit_disk<double>();
  Vec3<double> offset = u * rd.x() + v * rd.y();

  return Ray<double>(origin + offset, upper_left_corner + s * horizontal - t * vertical - origin - offset);
}
