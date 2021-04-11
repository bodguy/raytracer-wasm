#pragma once

class Color {
public:
  Color() = default;
  ~Color() = default;
  Color(float _r, float _g, float _b);
  Color(float _r, float _g, float _b, float _a);
  Color(const Color &other) = default;
  Color(Color &&other) noexcept;
  Color &operator=(Color other); // copy and swap idiom

  bool operator==(const Color &rhs) const;
  bool operator!=(const Color &rhs) const;

  static unsigned char toByte(float value);

  static Color white;
  static Color grey;
  static Color black;
  static Color red;
  static Color green;
  static Color blue;
  static Color yellow;
  static Color orange;
  static Color purple;

  float r{1.0}, g{1.0}, b{1.0}, a{1.0};

private:
  static void swap(Color &first, Color &second);
  static constexpr float invConverter = float(1) / float(255);
};