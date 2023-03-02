#pragma once

#include "vec3.hpp"

double lerp(double start, double end, double t) { return (1.0 - t) * start + t * end; }

vec3 lerp(vec3 start, vec3 end, double t) { return (1.0 - t) * start + t * end; }
