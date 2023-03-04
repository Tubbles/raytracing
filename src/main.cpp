#include "camera.hpp"
#include "hittable.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "util.hpp"
#include "vec3.hpp"
#include <fmt/format.h>
#include <vector>

static auto ray_color(const ray_t &ray, const std::vector<std::shared_ptr<hittable_i>> &world) -> color_t {
    // See if we hit any objects first
    hit_record_t rec;
    hit_record_t temp_rec;
    bool hit_anything = false;
    auto closest_so_far = std::numeric_limits<double>::infinity();

    for (const auto &object : world) {
        if (temp_rec = object->hit(ray, 0, closest_so_far); temp_rec) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    if (hit_anything) {
        return 0.5 * (rec.normal + color_t::from(1, 1, 1));
    }

    // Else we paint the sky
    const vec3_t unit_direction = ray.direction.unit();
    const auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * color_t::from(1.0, 1.0, 1.0) + t * color_t::from(0.5, 0.7, 1.0);
}

auto main(int argc, char *argv[]) -> int {
    const std::vector<std::string> args(argv + 1, argv + argc); // cppcheck-suppress unreadVariable

    // Image
    const int samples_per_pixel = 30;

    // World
    std::vector<std::shared_ptr<hittable_i>> world;
    world.push_back(std::make_shared<sphere_t>(point_t::from(0, 0, -1), 0.5));
    world.push_back(std::make_shared<sphere_t>(point_t::from(-0.1, 0.1, -0.6), 0.2));
    world.push_back(std::make_shared<sphere_t>(point_t::from(0, -100.5, -1), 100));

    // Camera
    camera_t camera;

    // Render
    fmt::print("P3\n");
    fmt::print("{} {}\n", camera.image_width, camera.image_height);
    fmt::print("255\n");

    for (int j = camera.image_height - 1; j >= 0; --j) {
        for (int i = 0; i < camera.image_width; ++i) {
            color_t pixel = color_t::from(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (camera.image_width - 1);
                auto v = (j + random_double()) / (camera.image_height - 1);
                ray_t ray = camera.get_ray(u, v);
                pixel += ray_color(ray, world);
            }

            fmt::print("{}\n", pixel.ppm_string(1.0 / static_cast<double>(samples_per_pixel)));
        }
    }
}
