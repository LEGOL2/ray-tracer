#include "src/image/image.hpp"

#include <fstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "src/image/stb_image_write.hpp"

void write_image(const char *path, int32_t width, int32_t height, uint8_t *data) {
  auto stride = 3 * width * sizeof(uint8_t);
  stbi_write_png(path, width, height, 3, data, stride);
}

void write_image(const char *path, int32_t width, int32_t height, std::vector<Color> &colors, int samples_per_pixel) {
  auto stride = 3 * width * sizeof(uint8_t);
  auto scale = 1.0 / samples_per_pixel;

  std::vector<uint8_t> data(colors.size());
  for (auto &c : colors) {
    c[0] *= scale;
    c[1] *= scale;
    c[2] *= scale;

    data.push_back(c.r());
    data.push_back(c.g());
    data.push_back(c.b());
  }

  stbi_write_png(path, width, height, 3, data.data(), stride);
}
