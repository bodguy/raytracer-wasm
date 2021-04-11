#pragma once

#include "Vec3.h"

class Camera {
public:
    Camera() = default;
    Camera(const Vec3& pos, const Vec3& dir, const Vec3& r, const Vec3& d) { 
        position = pos;
        direction = dir;
        right = r;;
        down = d;
    }

    Vec3 position;
    Vec3 direction{0, 0, 1};
    Vec3 right;
    Vec3 down;
};