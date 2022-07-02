#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

#include "src/hittable_list.hpp"
#include "src/image/image.hpp"
#include "src/math/constants.h"
#include "src/math/ray.hpp"
#include "src/math/sphere.hpp"
#include "src/math/vec3.hpp"

color ray_color(const ray& r, const hittable& world);
double hit_sphere(const point3& center, double radius, const ray& r);

int main() {
  // Image info
  constexpr double ASPECT_RATIO = 16.0 / 9.0;
  constexpr uint32_t WIDTH = 800;
  constexpr uint32_t HEIGHT = WIDTH / ASPECT_RATIO;

  // World
  hittable_list world;
  world.add(std::make_shared<sphere>(point3(0, 0, -1.0), 0.5));
  world.add(std::make_shared<sphere>(point3(0, -100.5, -1.0), 100));

  // Camera
  auto viewport_height = 2.0;
  auto viewport_width = ASPECT_RATIO * viewport_height;
  auto focal_length = 1.0;

  auto origin = point3(0, 0, 0);
  auto horizontal = vec3(viewport_width, 0, 0);
  auto vertical = vec3(0, viewport_height, 0);
  auto upper_left_corner = origin - horizontal / 2 + vertical / 2 - vec3(0, 0, focal_length);

  // Render
  auto start_time = std::chrono::high_resolution_clock::now();
  std::vector<color> colors(WIDTH * HEIGHT);
  for (uint32_t j = 0; j < HEIGHT; j++) {
    for (uint32_t i = 0; i < WIDTH; i++) {
      auto idx = j * WIDTH + i;
      auto u = static_cast<double>(i) / (WIDTH - 1);
      auto v = static_cast<double>(j) / (HEIGHT - 1);

      vec3 direction = upper_left_corner + u * horizontal - v * vertical - origin;
      ray r(origin, direction);
      color pixel_color = ray_color(r, world);

      auto& c = colors[idx];
      c.r(pixel_color.x());
      c.g(pixel_color.y());
      c.b(pixel_color.z());
    }
  }
  auto end_time = std::chrono::high_resolution_clock::now();
  std::cout << "Render time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count()
            << "ms" << std::endl;

  write_image("image.png", WIDTH, HEIGHT, colors);
}

color ray_color(const ray& r, const hittable& world) {
  hit_record rec;
  if (world.hit(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + color(1, 1, 1));
  }

  vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

double hit_sphere(const point3& center, double radius, const ray& r) {
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;
  auto delta = half_b * half_b - a * c;

  if (delta < 0) {
    return -1.0f;
  } else {
    return (-half_b - sqrt(delta)) / a;
  }
}
