#pragma once

#include "ray.hpp"
#include "util.hpp"
#include "vec3.hpp"

struct hit_record_t {
    point_t point;
    vec3_t normal;
    double t = 0.0;
    bool has_hit = false;
    bool front_face = false;

    inline void set_face_normal(const ray_t &r, const vec3_t &outward_normal) {
        front_face = r.direction.dot(outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }

    [[nodiscard]] explicit operator bool() const { return has_hit; }
};

struct hittable_i {
    INTERFACE(hittable_i);
    [[nodiscard]] virtual auto hit(const ray_t &r, double t_min, double t_max) const -> hit_record_t = 0;
};
