#pragma once

#include <random>

#define ARR_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

#define INTERFACE(name)                                                                                                \
    name() = default;                               /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */   \
    name(const name &) = default;                   /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */   \
    name(name &&) = default;                        /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */   \
    auto operator=(const name &)->name & = default; /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */   \
    auto operator=(name &&)->name & = default;      /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */   \
    virtual ~name() = default                       /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */

[[nodiscard]] inline auto clamp(double min, double x, double max) -> double {
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}

[[nodiscard]] inline auto lerp(double start, double end, double t) -> double { return (1.0 - t) * start + t * end; }

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
