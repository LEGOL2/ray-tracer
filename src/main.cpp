#include <cstdint>
#include <iostream>
#include <vector>

#include "src/image/image.hpp"
#include "src/math/ray.hpp"
#include "src/math/vec3.hpp"

color ray_color(const ray& r) {
  vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  // return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
  return (1.0 - t) * color(0.92, 0.25, 0.2) + t * color(0.25, 0.92, 0.2);
}

int main() {
  // Image info
  constexpr double ASPECT_RATIO = 16.0 / 9.0;
  constexpr uint32_t WIDTH = 800;
  constexpr uint32_t HEIGHT = WIDTH / ASPECT_RATIO;

  // Camera
  auto viewport_height = 2.0;
  auto viewport_width = ASPECT_RATIO * viewport_height;
  auto focal_length = 1.0;

  auto origin = point3(0, 0, 0);
  auto horizontal = vec3(viewport_width, 0, 0);
  auto vertical = vec3(0, viewport_height, 0);
  auto upper_left_corner = origin - horizontal / 2 + vertical / 2 - vec3(0, 0, focal_length);

  // Render
  std::vector<color> colors(WIDTH * HEIGHT);
  for (uint32_t j = 0; j < HEIGHT; j++) {
    for (uint32_t i = 0; i < WIDTH; i++) {
      auto idx = j * WIDTH + i;
      auto u = static_cast<double>(i) / (WIDTH - 1);
      auto v = static_cast<double>(j) / (HEIGHT - 1);

      vec3 direction = upper_left_corner + u * horizontal - v * vertical - origin;
      ray r(origin, direction);
      color pixel_color = ray_color(r);

      auto& c = colors[idx];
      c.r(pixel_color.x());
      c.g(pixel_color.y());
      c.b(pixel_color.z());
    }
  }

  write_image("image.png", WIDTH, HEIGHT, colors);
}
