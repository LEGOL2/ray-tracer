#pragma once

#include "src/math/vec3.hpp"
#include "src/math/ray.hpp"
#include "src/math/random.hpp"

template <typename T>
struct HitRecord;

template <typename T>
class Material {
  public:
    virtual ~Material() = default;
    virtual bool scatter(const Ray<T>& in_ray, const HitRecord<T>& rec, Color& attenuation, Ray<T>& scattered) const = 0;
};

template <typename T>
class Lambertian : public Material<T> {
  public:
    Lambertian(const Color& albedo) : albedo(albedo) {}

    virtual bool scatter(const Ray<T>& in_ray, const HitRecord<T>& rec, Color& attenuation, Ray<T>& scattered) const override {
      auto scatter_direction = rec.normal + random_unit_vector<T>();

      if (scatter_direction.near_zero())  {
        scatter_direction = rec.normal;
      }

      scattered = Ray<T>(rec.p, scatter_direction);
      attenuation = albedo;
      return true;
    }

  private:
    Color albedo;
};

template <typename T>
class Metal : public Material<T> {
  public:
    Metal(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    virtual bool scatter(const Ray<T>& in_ray, const HitRecord<T>& rec, Color& attenuation, Ray<T>& scattered) const override {
      Vec3<T> reflected = reflect<T>(unit_vector<T>(in_ray.direction()), rec.normal);
      scattered = Ray<T>(rec.p, reflected + fuzz * random_in_unit_sphere<T>());
      attenuation = albedo;
      return (dot<T>(scattered.direction(), rec.normal) > 0);
    }

  private:
    Color albedo;
    double fuzz;
};

template <typename T>
class Dielectric : public Material<T> {
  public:
    Dielectric(double index_of_refraction) : index_of_refraction(index_of_refraction) {}

    virtual bool scatter(const Ray<T>& in_ray, const HitRecord<T>& rec, Color& attenuation, Ray<T>& scattered) const override {
      attenuation = Color(1.0, 1.0, 1.0);
      double refraction_ratio = rec.front_face ? (1.0/index_of_refraction) : index_of_refraction;
      Vec3<T> unit_direction = unit_vector(in_ray.direction());
      double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
      double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
      
      bool cannot_refract = refraction_ratio * sin_theta > 1.0;
      Vec3<T> direction;

      if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_T<double>()) {
        direction = reflect(unit_direction, rec.normal);
      } else {
        direction = refract(unit_direction, rec.normal, refraction_ratio);
      }

      scattered = Ray<T>(rec.p, direction);
      return true;
    }
  
  private:
    static double reflectance(double cosine, double ref_idx) {
      // Schlick's approximation
      auto r0 = (1 - ref_idx) / (1 + ref_idx);
      r0 = r0*r0;
      
      return r0 + (1-r0) * pow((1-cosine), 5);
    }

    double index_of_refraction;
};
