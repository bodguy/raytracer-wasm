#include "Color.h"
#include "Math.h"

Color::Color(float _r, float _g, float _b) : r{_r}, g{_g}, b{_b}, a{0.0} {}

Color::Color(float _r, float _g, float _b, float _a) : r{_r}, g{_g}, b{_b}, a{_a} {}

Color::Color(Color &&other) noexcept : Color{} { Color::swap(*this, other); }

Color &Color::operator=(Color other) {
  // copy and swap idiom (effective c++ section 11)
  Color::swap(*this, other);
  return *this;
}

bool Color::operator==(const Color &rhs) const {
  return Math::equal(r, rhs.r) && Math::equal(g, rhs.g) &&
         Math::equal(b, rhs.b) && Math::equal(a, rhs.a);
}

bool Color::operator!=(const Color &rhs) const { return !(*this == rhs); }

unsigned char Color::toByte(float value) {
  float f2 = Math::max(float(0.0), Math::min(float(1.0), value));
  return static_cast<unsigned char>(
      Math::floor(f2 == float(1.0) ? 255 : f2 * 256));
}

void Color::swap(Color &first, Color &second) {
  using std::swap;

  swap(first.r, second.r);
  swap(first.g, second.g);
  swap(first.b, second.b);
  swap(first.a, second.a);
}

Color Color::white = Color(1., 1.0, 1.0, 1.0);
Color Color::grey = Color(0.5, 0.5, 0.5, 1.0);
Color Color::black = Color(0.0, 0.0, 0.0, 1.0);
Color Color::red = Color(1.0, 0.0, 0.0, 1.0);
Color Color::green = Color(0.0, 1.0, 0.0, 1.0);
Color Color::blue = Color(0.0, 0.0, 1.0, 1.0);
Color Color::yellow = Color(1.0, 1.0, 0.0, 1.0);
Color Color::orange = Color(1.0, 0.5, 0.0, 1.0);
Color Color::purple = Color(0.5, 0.0, 1.0, 1.0);