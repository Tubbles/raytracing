#pragma once

#include "util.hpp"
#include "vec3.hpp"

struct ray {
    ray() = default;
    // The "origin - direction" memory rule is pretty widely adopted and the order makes a lot of sense
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    ray(const point &origin, const vec3 &direction) : orig(origin), dir(direction) {}

    [[nodiscard]] auto at(double t) const -> point { return orig + t * dir; }

    point orig;
    vec3 dir;
};
