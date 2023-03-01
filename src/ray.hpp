#pragma once

#include "vec3.hpp"

struct ray {
    ray() {}
    ray(const point &origin, const vec3 &direction) : orig(origin), dir(direction) {}

    point at(double t) const { return orig + t * dir; }

    point orig;
    vec3 dir;
};
