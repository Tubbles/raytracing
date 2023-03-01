#pragma once

#include <cmath>
#include <fmt/format.h>
#include <string>

struct vec3 {
    union {
        double e[3];
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

    vec3() : e{0.0, 0.0, 0.0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    constexpr double operator[](size_t i) const { return e[i]; }
    constexpr double &operator[](size_t i) { return e[i]; }

    vec3 &operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3 &operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 &operator/=(const double t) { return *this *= 1 / t; }

    vec3 operator+(const vec3 &other) const {
        return vec3(this->e[0] + other.e[0], this->e[1] + other.e[1], this->e[2] + other.e[2]);
    }

    vec3 operator-(const vec3 &other) const {
        return vec3(this->e[0] - other.e[0], this->e[1] - other.e[1], this->e[2] - other.e[2]);
    }

    vec3 operator*(const vec3 &other) const {
        return vec3(this->e[0] * other.e[0], this->e[1] * other.e[1], this->e[2] * other.e[2]);
    }

    vec3 operator*(double t) const { return vec3(t * this->e[0], t * this->e[1], t * this->e[2]); }

    vec3 operator/(double t) const { return *this * (1 / t); }

    constexpr double length() const { return std::sqrt(length_squared()); }

    constexpr double length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

    vec3 unit() const { return *this / this->length(); }

    constexpr double dot(const vec3 &other) const {
        return this->e[0] * other.e[0] + this->e[1] * other.e[1] + this->e[2] * other.e[2];
    }

    vec3 cross(const vec3 &other) const {
        return vec3(this->e[1] * other.e[2] - this->e[2] * other.e[1],
                    this->e[2] * other.e[0] - this->e[0] * other.e[2],
                    this->e[0] * other.e[1] - this->e[1] * other.e[0]);
    }

    operator std::string() const { return fmt::format("({}, {}, {})", e[0], e[1], e[2]); }

    std::string ppm_string() const {
        return fmt::format("{} {} {}", static_cast<uint8_t>(255.999 * this->r), static_cast<uint8_t>(255.999 * this->g),
                           static_cast<uint8_t>(255.999 * this->b));
    }
};

inline vec3 operator*(double t, const vec3 &v) { return v * t; }

using point = vec3;
using color = vec3;
