#include "camera.hpp"
#include "hittable.hpp"
#include "random.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "util.hpp"
#include "vec3.hpp"
#include "world.hpp"
#include <fmt/format.h>
#include <vector>

static auto ray_color(const ray_t &ray, const world_t &world) -> color_t {
    // See if we hit any objects first
    if (const hit_record_t rec = world.hit(ray); rec) {
        return 0.5 * (rec.normal + color_t{1, 1, 1});
    }

    // Else we paint the sky
    const vec3_t unit_direction = ray.direction.unit();
    const auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * color_t{1.0, 1.0, 1.0} + t * color_t{0.5, 0.7, 1.0};
}

auto main(int argc, char *argv[]) -> int {
    const std::vector<std::string> args(argv + 1, argv + argc); // cppcheck-suppress unreadVariable

    // Image
    const bool use_anti_alias = true;
    const int samples_per_pixel = 100;

    // World
    world_t world;
    world.add(std::make_shared<sphere_t>(point_t{0, 0, -1}, 0.5));
    world.add(std::make_shared<sphere_t>(point_t{-0.1, 0.1, -0.6}, 0.2));
    world.add(std::make_shared<sphere_t>(point_t{0, -100.5, -1}, 100));

    // // Camera
    // camera_t camera;

    // Render
    fmt::print("P3\n");
    fmt::print("{} {}\n", camera_t::image_width, camera_t::image_height);
    fmt::print("255\n");

    for (int j = camera_t::image_height - 1; j >= 0; --j) {
        for (int i = 0; i < camera_t::image_width; ++i) {
            color_t pixel{};

            if (use_anti_alias) {
                for (int s = 0; s < samples_per_pixel; ++s) {
                    auto u = (i + random_double()) / (camera_t::image_width - 1);
                    auto v = (j + random_double()) / (camera_t::image_height - 1);
                    const ray_t ray = camera_t::get_ray(u, v);
                    pixel += ray_color(ray, world);
                }
                pixel *= 1.0 / static_cast<double>(samples_per_pixel);
            } else {
                auto u = static_cast<double>(i) / (camera_t::image_width - 1);
                auto v = static_cast<double>(j) / (camera_t::image_height - 1);
                const ray_t ray = camera_t::get_ray(u, v);
                pixel = ray_color(ray, world);
            }

            fmt::print("{}\n", pixel.ppm_string());
        }
    }
}
