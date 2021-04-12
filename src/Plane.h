#pragma once

#include "Object.h"

class Plane : public Object {
public:
    Plane() = default;
    Plane(const Vec3& norm, float dist, const Color& col) {
        normal = norm;
        distance = dist;
        color = col;
    }

    float findIntersection(const Ray& ray) override {
        Vec3 rayDir = ray.direction;

        float a = Vec3::dot(rayDir, normal);
        if (a == 0) {
            // ray and the plane are parallel
            return -1;
        }

        float b = Vec3::dot(normal, ray.origin + (normal * distance).makeNegate());
        return -1 * b / a;
    }

    Vec3 normal{1, 0, 0};
    float distance{0};
};