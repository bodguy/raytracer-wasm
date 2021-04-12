#pragma once

#include "Object.h"
#include "Vec3.h"
#include "Math.h"

class Sphere : public Object {
public:
  Sphere() = default;
  Sphere(const Vec3 &cen, float rad, const Color &col) {
    center = cen;
    radius = rad;
    color = col;
  }

  Vec3 getNormal(const Vec3 &point) {
    return (point + Vec3::negate(center)).makeNormalize();
  }

  float findIntersection(const Ray &ray) override {
    Vec3 dist = ray.origin - center;
    Vec3 dirDist = (dist * 2.f * ray.direction);
    float b = dirDist.x + dirDist.y + dirDist.z;
    Vec3 powDist = Vec3::pow(dist, 2.f);
    float c = powDist.x + powDist.y + powDist.z;
    float discriminant = b * b - 4 * c;

    if (discriminant > 0) {
        // ray intersects the sphere
        float root_1 = ((-1*b - Math::sqrt(discriminant))/2) - 0.000001;

        if (root_1 > 0) {
            return root_1;
        } else {
            float root_2 = ((Math::sqrt(discriminant) - b) / 2) - 0.000001;
            return root_2;
        }
    }
    
    // ray missed the sphere
    return -1;
  }

  Vec3 center;
  float radius{1};
};