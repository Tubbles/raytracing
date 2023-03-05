#pragma once

#include "ray.hpp"
#include "vec3.hpp"

struct camera_t {
    constexpr static const double aspect_ratio = 16.0 / 9.0;
    constexpr static const int image_width = 400;
    constexpr static const int image_height = static_cast<int>(image_width / aspect_ratio);

    constexpr static const auto viewport_height = 2.0;
    constexpr static const auto viewport_width = aspect_ratio * viewport_height;
    constexpr static const auto focal_length = 1.0;

    constexpr static const point_t origin = point_t{0, 0, 0};
    constexpr static const vec3_t horizontal = vec3_t{viewport_width, 0.0, 0.0};
    constexpr static const vec3_t vertical = vec3_t{0.0, viewport_height, 0.0};
    constexpr static const point_t lower_left_corner =
        origin - horizontal / 2 - vertical / 2 - vec3_t{0, 0, focal_length};

    [[nodiscard]] constexpr static auto get_ray(double u, double v) -> ray_t {
        return {origin, lower_left_corner + u * horizontal + v * vertical - origin};
    }
};
