#pragma once

#include "Vec3.h"
#include "Color.h"

class Light {
public:
    Light() = default;
    Light(const Vec3& pos, const Color& col) {
        position = pos;
        color = col;
    }

    Vec3 position;
    Color color;
};