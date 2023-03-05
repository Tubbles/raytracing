#pragma once

#include "util.hpp"
#include "vec3.hpp"

struct ray_t {
    [[nodiscard]] constexpr ray_t() = default;
    // The "origin - direction" memory rule is pretty widely adopted and the order makes a lot of sense
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    [[nodiscard]] constexpr ray_t(const point_t &_origin, const vec3_t &_direction)
        : origin(_origin), direction(_direction) {}

    [[nodiscard]] auto project(double t) const -> point_t { return origin + t * direction; }

    point_t origin = {};
    vec3_t direction = {};
};
