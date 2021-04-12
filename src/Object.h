#pragma once

#include "Color.h"
#include "Ray.h"

class Object {
public:
    Object() = default;

    virtual float findIntersection(const Ray& ray) = 0;

    Color color{0.5, 0.5, 0.5, 0};
};