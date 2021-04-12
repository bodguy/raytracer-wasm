#pragma once

class Vec3 {
public:
  Vec3() = default;
  explicit Vec3(float _x);
  Vec3(float _x, float _y);
  Vec3(float _x, float _y, float _z);
  Vec3(Vec3 &&other) noexcept;
  Vec3(const Vec3 &other) = default;
  Vec3 &operator=(Vec3 other); // copy and swap idiom

  Vec3 operator+(const Vec3 &other) const;
  Vec3 &operator+=(const Vec3 &other);

  Vec3 operator-(const Vec3 &other) const;
  Vec3 &operator-=(const Vec3 &other);

  Vec3 operator*(const Vec3 &other) const;
  Vec3 &operator*=(const Vec3 &other);

  Vec3 operator/(const Vec3 &other) const;
  Vec3 &operator/=(const Vec3 &other);

  Vec3 operator+(float scalar) const;
  Vec3 &operator+=(float scalar);

  Vec3 operator-(float scalar) const;
  Vec3 &operator-=(float scalar);

  Vec3 operator*(float scalar) const;
  Vec3 &operator*=(float scalar);

  Vec3 operator/(float scalar) const;
  Vec3 &operator/=(float scalar);

  bool operator==(const Vec3 &other) const;
  bool operator!=(const Vec3 &other) const;

  Vec3 operator-() const;
  Vec3 operator+() const;
  
  Vec3& makeNegate();
  Vec3 makeNormalize();

  float length() const;
  float squaredLength() const;

  static Vec3 cross(const Vec3 &a, const Vec3 &b);
  static float dot(const Vec3 &a, const Vec3 &b);
  static Vec3 normalize(const Vec3 &v);
  static Vec3 inverse(const Vec3& v);
  static Vec3 negate(const Vec3& v);
  static Vec3 pow(const Vec3& v, float exp);

  float x{0.0}, y{0.0}, z{0.0};
  static const Vec3 up, down, left, right, forward, backward, zero;

private:
  static void swap(Vec3 &first, Vec3 &second);
};