#pragma once

#include "Vec3.h"

class Ray {
public:
  Ray() = default;
  ~Ray() = default;
  Ray(const Vec3 &origin, const Vec3 &direction);
  Ray(const Ray &other) = default;
  Ray(Ray &&other);
  Ray &operator=(Ray other);

  Vec3 point(float distance);
  bool operator==(const Ray &other);
  bool operator!=(const Ray &other);

  Vec3 mOrigin;
  Vec3 mDirection{1, 0, 0};
  Vec3 mInvDirection{Vec3::inverse(mDirection)};

private:
  void swap(Ray &first, Ray &second);
};