#pragma once

#include <cstdint>
#include <vector>

#include "src/math/vec.hpp"

void write_image(const char *path, int32_t width, int32_t height, uint8_t *data);
void write_image(const char *path, int32_t width, int32_t height,
                 std::vector<color<uint8_t>> &colors);
