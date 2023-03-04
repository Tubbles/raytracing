#include "ray.hpp"
#include "util.hpp"
#include "vec3.hpp"
#include <fmt/format.h>
#include <vector>

static auto hit_sphere(const point &center, double radius, const ray &r) -> double {
    const vec3 oc = r.orig - center;
    const auto a = std::pow(r.dir, 2);
    const auto b = 2.0 * r.dir * oc;
    const auto c = std::pow(oc, 2) - std::pow(radius, 2);
    const auto discriminant = b * b - 4 * a * c;
    double out = 0.0;
    if (discriminant < 0) {
        out = -1.0;
    } else {
        out = (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
    return out;
}

static auto ray_color(const ray &r) -> color {
    auto t = hit_sphere(point::from(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        const vec3 normal = (r.at(t) - vec3::from(0, 0, -1)).unit();
        return 0.5 * color::from(normal.x + 1, normal.y + 1, normal.z + 1);
    }

    // Paint sky
    const vec3 unit_direction = r.dir.unit();
    t = 0.5 * (unit_direction.y + 1.0);
    return lerp(color::from(1.0, 1.0, 1.0), color::from(0.5, 0.7, 1.0), t);
}

auto main(int argc, char *argv[]) -> int {
    const std::vector<std::string> args(argv + 1, argv + argc); // cppcheck-suppress unreadVariable

    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    const auto viewport_height = 2.0;
    const auto viewport_width = aspect_ratio * viewport_height;
    const auto focal_length = 1.0;

    const auto origin = point::from(0, 0, 0);
    const auto horizontal = vec3::from(viewport_width, 0, 0);
    const auto vertical = vec3::from(0, viewport_height, 0);
    const auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3::from(0, 0, focal_length);

    // auto p = vec3::from(4, 5, 6);
    // auto c = vec3::from(3, 2, 1);
    // fmt::print("{}\n", std::pow(p - c, 2));
    // fmt::print("{}\n", (p.x - c.x) * (p.x - c.x) + (p.y - c.y) * (p.y - c.y) + (p.z - c.z) * (p.z - c.z));
    // fmt::print("{}\n", std::pow(p.x - c.x, 2) + std::pow(p.y - c.y, 2) + std::pow(p.z - c.z, 2));
    // fmt::print("{}\n", vec3::from(1, 2, 3).to_string());

    // Render
    fmt::print("P3\n");
    fmt::print("{} {}\n", image_width, image_height);
    fmt::print("255\n");

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            const auto u = static_cast<double>(i) / (image_width - 1);
            const auto v = static_cast<double>(j) / (image_height - 1);
            const ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            const color pixel = ray_color(r);

            fmt::print("{}\n", pixel.ppm_string());
        }
    }
}
