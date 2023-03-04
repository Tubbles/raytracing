#pragma once

#define ARR_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

[[nodiscard]] inline auto lerp(double start, double end, double t) -> double { return (1.0 - t) * start + t * end; }
