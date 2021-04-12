#pragma once

#include "Vec3.h"

class Ray {
public:
  Ray() = default;
  Ray(const Vec3 &ori, const Vec3 &dir);
  Ray(const Ray &other) = default;
  Ray(Ray &&other);
  Ray &operator=(Ray other);

  Vec3 point(float distance);
  bool operator==(const Ray &other);
  bool operator!=(const Ray &other);

  Vec3 origin;
  Vec3 direction{1, 0, 0};

private:
  void swap(Ray &first, Ray &second);
};