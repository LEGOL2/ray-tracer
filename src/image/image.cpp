#include "src/image/image.hpp"

#include <fstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "src/image/stb_image_write.hpp"

void write_image(const char *path, int32_t width, int32_t height, uint8_t *data) {
  auto stride = 3 * width * sizeof(uint8_t);
  stbi_write_png(path, width, height, 3, data, stride);
}

void write_image(const char *path, int32_t width, int32_t height,
                 std::vector<color<uint8_t>> &colors) {
  auto stride = width * sizeof(color<uint8_t>);
  std::vector<uint8_t> data;
  for (auto &c : colors) {
    data.push_back(c.x());
    data.push_back(c.y());
    data.push_back(c.z());
  }

  stbi_write_png(path, width, height, 3, data.data(), stride);
}
