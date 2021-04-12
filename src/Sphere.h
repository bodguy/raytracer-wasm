#pragma once

#include "Object.h"
#include "Vec3.h"

class Sphere : public Object {
public:
    Sphere() = default;
    Sphere(const Vec3& cen, float rad, const Color& col) {
        center = cen;
        radius = rad;
        color = col;
    }

    float findIntersection(const Ray& ray) override {
        return 0;
    }

    Vec3 center;
    float radius{1};
};