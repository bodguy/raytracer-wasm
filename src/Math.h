#pragma once

#include "Vec3.h"
#include <utility>
#include <limits>
#include <cmath>

class Math {
public:
  template <typename T> static bool equal(const T &a, const T &b);
  template <typename T> static constexpr auto max(const T &a, const T &b);
  template <typename T, typename... Ts>
  static constexpr auto max(const T &a, const T &b, const Ts &...ts);
  template <typename T> static constexpr auto min(const T &a, const T &b);
  template <typename T, typename... Ts>
  static constexpr auto min(const T &a, const T &b, const Ts &...ts);
  template <typename T> static bool zero(const T &a);

  static float ceil(float a) { return std::ceil(a); }
  static float floor(float a) { return std::floor(a); }
  static float sqrt(float a) { return std::sqrt(a); }
  static float abs(float a) { return std::abs(a); }
  static float pow(float a, float exp) { return std::pow(a, exp); }

  static constexpr float pi = float(3.14159265358979); // std::atan(1) * 4
  static constexpr int degrees = 360;
  static constexpr float deg2Rad = Math::pi / float(180);
  static constexpr float rad2Deg = float(180) / Math::pi;
};

template <typename T> bool Math::equal(const T &a, const T &b) {
  // Threshold denominator so we don't divide by zero
  static constexpr auto tolerance = std::numeric_limits<T>::epsilon();
  static constexpr auto threshold =
      std::numeric_limits<T>::min(); // A very small nonzero number!
  auto min = Math::min(Math::abs(a), Math::abs(b));
  if (Math::abs(min) == float(0.0)) {
    return Math::abs(a - b) < tolerance;
  }
  return (Math::abs(a - b) / Math::max(threshold, min)) < tolerance;
}

template <typename T> constexpr auto Math::max(const T &a, const T &b) {
  return (a < b) ? b : a;
}

template <typename T, typename... Ts>
constexpr auto Math::max(const T &a, const T &b, const Ts &...ts) {
  const auto m = a < b ? b : a;
  if constexpr (sizeof...(ts) > 0) {
    return max(m, ts...);
  }
  return m;
}

template <typename T> constexpr auto Math::min(const T &a, const T &b) {
  return (a < b) ? a : b;
}

template <typename T, typename... Ts>
constexpr auto Math::min(const T &a, const T &b, const Ts &...ts) {
  const auto m = a < b ? a : b;
  if constexpr (sizeof...(ts) > 0) {
    return min(m, ts...);
  }
  return m;
}

template <typename T> bool Math::zero(const T &a) {
  return equal(a, static_cast<const T>(0));
}