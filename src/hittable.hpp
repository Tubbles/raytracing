#pragma once

#include "ray.hpp"

struct hit_record {
    bool has_hit;
    point p;
    vec3 normal;
    double t;

    operator bool() { return has_hit; }
};

class hittable {
public:
    virtual ~hittable() {}
    virtual auto hit(const ray &r, double t_min, double t_max) -> hit_record const = 0;
};
