#include "ray.hpp"
#include "util.hpp"
#include "vec3.hpp"
#include <fmt/format.h>

double hit_sphere(const point &center, double radius, const ray &r) {
    vec3 oc = r.orig - center;
    auto a = std::pow(r.dir, 2);
    auto b = 2.0 * r.dir * oc;
    auto c = std::pow(oc, 2) - std::pow(radius, 2);
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
}

color ray_color(const ray &r) {
    auto t = hit_sphere(point::from(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 normal = (r.at(t) - vec3::from(0, 0, -1)).unit();
        return 0.5 * color::from(normal.x + 1, normal.y + 1, normal.z + 1);
    }

    // Paint sky
    vec3 unit_direction = r.dir.unit();
    t = 0.5 * (unit_direction.y + 1.0);
    return lerp(color::from(1.0, 1.0, 1.0), color::from(0.5, 0.7, 1.0), t);
}

int main() {
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = image_width / aspect_ratio;

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point::from(0, 0, 0);
    auto horizontal = vec3::from(viewport_width, 0, 0);
    auto vertical = vec3::from(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3::from(0, 0, focal_length);

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
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            color pixel = ray_color(r);

            fmt::print("{}\n", pixel.ppm_string());
        }
    }
}
