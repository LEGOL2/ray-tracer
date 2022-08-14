#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

#include "src/camera.hpp"
#include "src/hittable_list.hpp"
#include "src/image/image.hpp"
#include "src/math/constants.hpp"
#include "src/math/random.hpp"
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
  constexpr uint32_t samples_per_pixel = 100;

  // World
  hittable_list world;
  world.add(std::make_shared<sphere>(point3(0, 0, -1.0), 0.5));
  world.add(std::make_shared<sphere>(point3(0, -100.5, -1.0), 100));

  // Camera
  camera camera;

  // Render
  auto start_time = std::chrono::high_resolution_clock::now();
  std::vector<color> colors(WIDTH * HEIGHT);
  for (uint32_t j = 0; j < HEIGHT; j++) {
    for (uint32_t i = 0; i < WIDTH; i++) {
      auto idx = j * WIDTH + i;
      color pixel_color(0, 0, 0);

      for (uint32_t s = 0; s < samples_per_pixel; s++) {
        auto u = static_cast<double>(i + random_double()) / (WIDTH - 1);
        auto v = static_cast<double>(j + random_double()) / (HEIGHT - 1);
        ray r(camera.get_ray(u, v));
        pixel_color += ray_color(r, world);
      }

      auto& c = colors[idx];
      c.r(pixel_color.x());
      c.g(pixel_color.y());
      c.b(pixel_color.z());
    }
  }
  auto end_time = std::chrono::high_resolution_clock::now();
  std::cout << "Render time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count()
            << "ms" << std::endl;

  write_image("image.png", WIDTH, HEIGHT, colors, samples_per_pixel);
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
