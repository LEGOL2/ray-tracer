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
#include "src/material.hpp"

Color ray_color(const Ray<double>& r, const Hittable<double>& world, int depth);
double hit_sphere(const Point3<double>& center, double radius, const Ray<double>& r);

int main() {
  // Image info
  constexpr double ASPECT_RATIO = 16.0 / 9.0;
  constexpr uint32_t WIDTH = 800;
  constexpr uint32_t HEIGHT = WIDTH / ASPECT_RATIO;
  constexpr uint32_t samples_per_pixel = 100;
  constexpr uint32_t progress_reporter = HEIGHT / 10;
  constexpr int max_depth = 50;

  // World
  HittableList<double> world;

  auto material_ground = std::make_shared<Lambertian<double>>(Color(0.8, 0.8, 0.0));
  auto material_center = std::make_shared<Lambertian<double>>(Color(0.1, 0.2, 0.5));
  auto material_left   = std::make_shared<Dielectric<double>>(1.5);
  auto material_right  = std::make_shared<Metal<double>>(Color(0.8, 0.6, 0.2), 0.1);

  world.add(std::make_shared<Sphere<double>>(Point3<double>( 0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(std::make_shared<Sphere<double>>(Point3<double>( 0.0,    0.0, -1.0),   0.5, material_center));
  world.add(std::make_shared<Sphere<double>>(Point3<double>(-1.0,    0.0, -1.0),   0.5, material_left));
  world.add(std::make_shared<Sphere<double>>(Point3<double>(-1.0,    0.0, -1.0),  -0.4, material_left));
  world.add(std::make_shared<Sphere<double>>(Point3<double>( 1.0,    0.0, -1.0),   0.5, material_right));

  // Camera
  Camera camera;

  // Render
  auto start_time = std::chrono::high_resolution_clock::now();
  std::vector<Color> colors(WIDTH * HEIGHT);
  for (uint32_t j = 0; j < HEIGHT; j++) {
    for (uint32_t i = 0; i < WIDTH; i++) {
      auto idx = j * WIDTH + i;
      Color pixel_color(0, 0, 0);

      for (uint32_t s = 0; s < samples_per_pixel; s++) {
        auto u = static_cast<double>(i + random_T<double>()) / (WIDTH - 1);
        auto v = static_cast<double>(j + random_T<double>()) / (HEIGHT - 1);
        Ray<double> r(camera.get_ray(u, v));
        pixel_color += ray_color(r, world, max_depth);
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

Color ray_color(const Ray<double>& r, const Hittable<double>& world, int depth) {
  HitRecord<double> rec;

  if (depth <= 0) {
    return Color(0.0, 0.0, 0.0);
  }

  if (world.hit(r, 0.001, infinity, rec)) {
    Ray<double> scattered;
    Color attenuation;
    if (rec.material->scatter(r, rec, attenuation, scattered)) {
      return attenuation * ray_color(scattered, world, depth-1);
    }

    return Color(0.0, 0.0, 0.0);
    }

  Vec3<double> unit_direction = unit_vector<double>(r.direction());
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
