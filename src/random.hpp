#pragma once

#include <random>

// Returns a random real in [0.0, 1.0).
[[nodiscard]] inline auto random_double(uint64_t initial_seed = 0) -> double {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator(initial_seed);
    return distribution(generator);
}

// Returns a random real in [min, max).
[[nodiscard]] inline auto random_double(double min, double max) -> double {
    return min + (max - min) * random_double();
}
