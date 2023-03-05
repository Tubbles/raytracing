#pragma once

#include "hittable.hpp"
#include "vec3.hpp"

struct sphere_t : public hittable_i {
    sphere_t() = default;
    sphere_t(const point_t &_center, double _radius) : center(_center), radius(_radius) {}

    [[nodiscard]] auto hit(const ray_t &r, double t_min, double t_max) const -> hit_record_t override;

    point_t center = {};
    double radius = 0.0;
};

[[nodiscard]] inline auto sphere_t::hit(const ray_t &ray, double t_min, double t_max) const -> hit_record_t {
    const vec3_t oc = ray.origin - center;
    const auto a = ray.direction.length_squared();
    const auto half_b = oc.dot(ray.direction);
    const auto c = oc.length_squared() - radius * radius;

    const auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) {
        return {};
    }
    const auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root) {
            return {};
        }
    }

    const auto point = ray.project(root);
    const vec3_t outward_normal = (point - center) / radius;

    hit_record_t out = {
        .point = point,
        .normal = outward_normal,
        .t = root,
        .has_hit = true,
    };

    out.set_face_normal(ray, outward_normal);

    return out;
}
