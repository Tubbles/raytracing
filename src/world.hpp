#pragma once

#include "hittable.hpp"
#include "ray.hpp"
#include <algorithm>
#include <vector>

struct world_t {
    std::vector<std::shared_ptr<hittable_i>> objects;

    void add(const std::shared_ptr<hittable_i> &obj) { objects.push_back(obj); }

    [[nodiscard]] auto hit(const ray_t &ray) const -> hit_record_t {
        hit_record_t rec;
        rec.t = std::numeric_limits<double>::infinity();

        for (const auto &object : objects) {
            if (const hit_record_t temp = object->hit(ray, 0, rec.t); temp) {
                rec = temp;
            }
        }

        return rec;
    }
};
