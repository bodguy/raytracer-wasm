#include "Ray.h"
#include "Math.h"

Ray::Ray(const Vec3 &ori, const Vec3 &dir)
    : origin{ori}, direction{dir} {}

Ray::Ray(Ray &&other) : Ray{} { Ray::swap(*this, other); }

Ray &Ray::operator=(Ray other) {
  // copy and swap idiom (effective c++ section 11)
  Ray::swap(*this, other);
  return *this;
}

Vec3 Ray::point(float distance) { return origin + direction * distance; }

bool Ray::operator==(const Ray &other) {
  return ((origin == other.origin) && (direction == other.direction));
}

bool Ray::operator!=(const Ray &other) { return !(*this == other); }

void Ray::swap(Ray &first, Ray &second) {
  using std::swap;

  swap(first.origin, second.origin);
  swap(first.direction, second.direction);
}