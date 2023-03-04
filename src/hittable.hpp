#pragma once

#include "ray.hpp"
#include "vec3.hpp"

struct hit_record {
    bool has_hit;
    point p;
    vec3 normal;
    double t;

    [[nodiscard]] explicit operator bool() { return has_hit; }
};

class hittable {
public:
    virtual ~hittable() {}
    [[nodiscard]] virtual auto hit(const ray &r, double t_min, double t_max) const -> hit_record = 0;
};
