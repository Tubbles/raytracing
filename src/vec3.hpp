#pragma once

#include "util.hpp"
#include <cassert>
#include <cmath>
#include <fmt/format.h>
#include <string>

// Members initialized through union
// NOLINTNEXTLINE(hicpp-member-init)
struct vec3_t {
    union {
        // Array is appropriate, std::array is not
        // NOLINTNEXTLINE(modernize-avoid-c-arrays)
        double e[3] = {0.0, 0.0, 0.0};
        struct {
            double x;
            double y;
            double z;
        };
        struct {
            double r;
            double g;
            double b;
        };
    };

    // Members initialized through union
    // NOLINTNEXTLINE(hicpp-member-init)
    [[nodiscard]] constexpr vec3_t(double e0, double e1, double e2) : e{e0, e1, e2} {}

    // Blanket rule of 5
    // Members initialized through union
    // NOLINTNEXTLINE(hicpp-member-init)
    [[nodiscard]] constexpr vec3_t() = default;
    // [[nodiscard]] constexpr vec3_t(const vec3_t &) = default;
    // [[nodiscard]] constexpr vec3_t(vec3_t &&) = default;
    // constexpr auto operator=(const vec3_t &) -> vec3_t & = default;
    // constexpr auto operator=(vec3_t &&) -> vec3_t & = default;

    [[nodiscard]] constexpr auto operator-() const -> vec3_t { return vec3_t{-e[0], -e[1], -e[2]}; }

    [[nodiscard]] constexpr auto operator[](size_t i) const -> double {
        assert(i < ARR_LEN(e));
        return e[i]; // Array subscript checked, NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
    }

    [[nodiscard]] constexpr auto operator[](size_t i) -> double & {
        assert(i < ARR_LEN(e));
        return e[i]; // Array subscript checked, NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
    }

    constexpr auto operator+=(const vec3_t &v) -> vec3_t & {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    constexpr auto operator*=(const double t) -> vec3_t & {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    constexpr auto operator/=(const double t) -> vec3_t & { return *this *= 1 / t; }

    [[nodiscard]] constexpr auto operator+(const vec3_t &other) const -> vec3_t {
        return vec3_t{this->e[0] + other.e[0], this->e[1] + other.e[1], this->e[2] + other.e[2]};
    }

    [[nodiscard]] constexpr auto operator-(const vec3_t &other) const -> vec3_t {
        return vec3_t{this->e[0] - other.e[0], this->e[1] - other.e[1], this->e[2] - other.e[2]};
    }

    [[nodiscard]] constexpr auto operator*(const vec3_t &other) const -> double {
        return this->e[0] * other.e[0] + this->e[1] * other.e[1] + this->e[2] * other.e[2];
    }

    [[nodiscard]] constexpr auto elem_mult(const vec3_t &other) const -> vec3_t {
        return vec3_t{this->e[0] * other.e[0], this->e[1] * other.e[1], this->e[2] * other.e[2]};
    }

    [[nodiscard]] constexpr auto operator*(double t) const -> vec3_t {
        return vec3_t{t * this->e[0], t * this->e[1], t * this->e[2]};
    }

    [[nodiscard]] constexpr auto operator/(double t) const -> vec3_t { return *this * (1 / t); }

    [[nodiscard]] constexpr auto length_squared() const -> double { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

    [[nodiscard]] constexpr auto length() const -> double { return std::sqrt(length_squared()); }

    [[nodiscard]] constexpr auto unit() const -> vec3_t { return *this / this->length(); }

    [[nodiscard]] constexpr auto dot(const vec3_t &other) const -> double { return this->operator*(other); }

    [[nodiscard]] constexpr auto cross(const vec3_t &other) const -> vec3_t {
        return vec3_t{this->e[1] * other.e[2] - this->e[2] * other.e[1],
                      this->e[2] * other.e[0] - this->e[0] * other.e[2],
                      this->e[0] * other.e[1] - this->e[1] * other.e[0]};
    }

    [[nodiscard]] explicit operator std::string() const { return fmt::format("({}, {}, {})", e[0], e[1], e[2]); }

    [[nodiscard]] auto to_string() const -> std::string { return std::string{*this}; }

    [[nodiscard]] auto ppm_string() const -> std::string {
        // clang-format off
        return fmt::format(
            "{} {} {}",
            static_cast<uint8_t>(256 * clamp(0.0, this->r, 0.999)),
            static_cast<uint8_t>(256 * clamp(0.0, this->g, 0.999)),
            static_cast<uint8_t>(256 * clamp(0.0, this->b, 0.999))
        );
        // clang-format on
    }
};

[[nodiscard]] inline constexpr auto operator*(double t, const vec3_t &v) -> vec3_t { return v * t; }

namespace std {
[[nodiscard]] inline constexpr auto pow(const vec3_t &v, double p) -> double {
    return ::std::pow(::std::sqrt(v.dot(v)), p);
};

[[nodiscard]] inline constexpr auto sqrt(const vec3_t &v) -> double { return ::std::pow(v, 0.5); };
} // namespace std

[[nodiscard]] inline auto lerp(const vec3_t &start, const vec3_t &end, double t) -> vec3_t {
    return (1.0 - t) * start + t * end;
}

using point_t = vec3_t;
using color_t = vec3_t;
