#include "Vec3.h"
#include "Math.h"

Vec3::Vec3(float _x) : x{_x}, y{0.0}, z{0.0} {}

Vec3::Vec3(const float _x, const float _y) : x{_x}, y{_y}, z{0.0} {}

Vec3::Vec3(const float _x, const float _y, const float _z)
    : x{_x}, y{_y}, z{_z} {}

Vec3::Vec3(Vec3 &&other) noexcept : Vec3{} { Vec3::swap(*this, other); }

Vec3 &Vec3::operator=(Vec3 other) {
  // copy and swap idiom (effective c++ section 11)
  Vec3::swap(*this, other);
  return *this;
}

Vec3 Vec3::operator+(const Vec3 &other) const {
  // using op= (more effective c++ section 22)
  return Vec3(*this) += other;
}

Vec3 &Vec3::operator+=(const Vec3 &other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

Vec3 Vec3::operator-(const Vec3 &other) const { return Vec3(*this) -= other; }

Vec3 &Vec3::operator-=(const Vec3 &other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

Vec3 Vec3::operator*(const Vec3 &other) const { return Vec3(*this) *= other; }

Vec3 &Vec3::operator*=(const Vec3 &other) {
  x *= other.x;
  y *= other.y;
  z *= other.z;
  return *this;
}

Vec3 Vec3::operator/(const Vec3 &other) const { return Vec3(*this) /= other; }

Vec3 &Vec3::operator/=(const Vec3 &other) {
  x /= other.x;
  y /= other.y;
  z /= other.z;
  return *this;
}

Vec3 Vec3::operator+(const float scalar) const { return Vec3(*this) += scalar; }

Vec3 &Vec3::operator+=(const float scalar) {
  x += scalar;
  y += scalar;
  z += scalar;
  return *this;
}

Vec3 Vec3::operator-(const float scalar) const { return Vec3(*this) -= scalar; }

Vec3 &Vec3::operator-=(const float scalar) {
  x -= scalar;
  y -= scalar;
  z -= scalar;
  return *this;
}

Vec3 Vec3::operator*(const float scalar) const { return Vec3(*this) *= scalar; }

Vec3 &Vec3::operator*=(const float scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

Vec3 Vec3::operator/(const float scalar) const { return Vec3(*this) /= scalar; }

Vec3 &Vec3::operator/=(const float scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
  return *this;
}

bool Vec3::operator==(const Vec3 &other) const {
  return (Math::equal(x, other.x) && Math::equal(y, other.y) &&
          Math::equal(z, other.z));
}

bool Vec3::operator!=(const Vec3 &other) const { return !(*this == other); }

Vec3 Vec3::operator-() const { return Vec3{-x, -y, -z}; }

Vec3 Vec3::operator+() const {
  return Vec3{x < 0 ? -x : x, y < 0 ? -y : y, z < 0 ? -z : z};
}

Vec3& Vec3::makeNegate() {
    x = -x;
    y = -y;
    z = -z;
    return *this;
  }

Vec3 Vec3::makeNormalize() {
  float len = length();
  if (Math::zero(len) || Math::equal(len, static_cast<float>(1.0))) {
    return {*this};
  }

  float inv = 1 / len;
  *this *= inv;
  return {*this};
}

float Vec3::length() const { return Math::sqrt(squaredLength()); }

float Vec3::squaredLength() const { return x * x + y * y + z * z; }

Vec3 Vec3::cross(const Vec3 &a, const Vec3 &b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

float Vec3::dot(const Vec3 &a, const Vec3 &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Vec3::normalize(const Vec3 &v) {
  float len = v.length();
  if (Math::zero(len) || Math::equal(len, static_cast<float>(1.0))) {
    return {v};
  }

  float inv = 1 / len;
  return {v * inv};
}

Vec3 Vec3::inverse(const Vec3 &v) {
  return {float(1.0) / v.x, float(1.0) / v.y, float(1.0) / v.z};
}

Vec3 Vec3::negate(const Vec3& v) {
  return Vec3{-v.x, -v.y, -v.z};
}

Vec3 Vec3::pow(const Vec3& v, float exp) { 
  return Vec3{Math::pow(v.x, exp), Math::pow(v.y, exp), Math::pow(v.z, exp)};
}

void Vec3::swap(Vec3 &first, Vec3 &second) {
  using std::swap;

  swap(first.x, second.x);
  swap(first.y, second.y);
  swap(first.z, second.z);
}

const Vec3 Vec3::up = Vec3{0.0, 1.0, 0.0};
const Vec3 Vec3::down = Vec3{0.0, -1.0, 0.0};
const Vec3 Vec3::left = Vec3{-1.0, 0.0, 0.0};
const Vec3 Vec3::right = Vec3{1.0, 0.0, 0.0};
const Vec3 Vec3::forward = Vec3{0.0, 0.0, 1.0};
const Vec3 Vec3::backward = Vec3{0.0, 0.0, -1.0};
const Vec3 Vec3::zero = Vec3{0.0, 0.0, 0.0};