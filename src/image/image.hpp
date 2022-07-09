#pragma once

#include <cstdint>
#include <vector>

#include "src/math/vec3.hpp"

void write_image(const char *path, int32_t width, int32_t height, uint8_t *data);
void write_image(const char *path, int32_t width, int32_t height, std::vector<color> &colors,
                 int samples_per_pixel);
