#include "vec3.hpp"
#include <fmt/format.h>

int main() {
    // Image
    const int image_width = 256;
    const int image_height = 256;

    // Render
    fmt::print("P3\n");
    fmt::print("{} {}\n", image_width, image_height);
    fmt::print("255\n");

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            color pixel(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
            fmt::print("{}\n", pixel.ppm_string());
        }
    }
}
