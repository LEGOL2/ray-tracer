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

Color ray_color(const Ray<double>& r, const Hittable<double>& world);
double hit_sphere(const Point3<double>& center, double radius, const Ray<double>& r);

int main() {
  // Image info
  constexpr double ASPECT_RATIO = 16.0 / 9.0;
  constexpr uint32_t WIDTH = 800;
  constexpr uint32_t HEIGHT = WIDTH / ASPECT_RATIO;
  constexpr uint32_t samples_per_pixel = 100;
  constexpr uint32_t progress_reporter = HEIGHT / 10;

  // World
  HittableList<double> world;
  world.add(std::make_shared<Sphere<double>>(Point3<double>(0.0, 0.0, -1.0), 0.5));
  world.add(std::make_shared<Sphere<double>>(Point3<double>(0.0, -100.5, -1.0), 100));

  // Camera
  Camera Camera;

  // Render
  auto start_time = std::chrono::high_resolution_clock::now();
  std::vector<Color> colors(WIDTH * HEIGHT);
  for (uint32_t j = 0; j < HEIGHT; j++) {
    for (uint32_t i = 0; i < WIDTH; i++) {
      auto idx = j * WIDTH + i;
      Color pixel_color(0, 0, 0);

      for (uint32_t s = 0; s < samples_per_pixel; s++) {
        auto u = static_cast<double>(i + random_double()) / (WIDTH - 1);
        auto v = static_cast<double>(j + random_double()) / (HEIGHT - 1);
        Ray r(Camera.get_ray(u, v));
        pixel_color += ray_color(r, world);
      }

      auto& c = colors[idx];
      c.r(pixel_color.x());
      c.g(pixel_color.y());
      c.b(pixel_color.z());
    }

    if (j % progress_reporter == 0) {
      std::cout << "Progress: " << static_cast<double>(j) / HEIGHT << std::endl;
    }
  }
  auto end_time = std::chrono::high_resolution_clock::now();
  std::cout << "Done. Render time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << "ms"
            << std::endl;

  write_image("image.png", WIDTH, HEIGHT, colors, samples_per_pixel);
}

Color ray_color(const Ray<double>& r, const Hittable<double>& world) {
  HitRecord<double> rec;
  if (world.hit(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + Color(1, 1, 1));
  }

  Vec3 unit_direction = unit_vector<double>(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

double hit_sphere(const Point3<double>& center, double radius, const Ray<double>& r) {
  Vec3<double> oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot<double>(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;
  auto delta = half_b * half_b - a * c;

  if (delta < 0) {
    return -1.0f;
  } else {
    return (-half_b - sqrt(delta)) / a;
  }
}
