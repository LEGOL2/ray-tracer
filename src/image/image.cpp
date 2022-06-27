#include "src/image/image.hpp"

#include <fstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "src/image/stb_image_write.hpp"

void write_image(const char *path, int32_t width, int32_t height, uint8_t *data) {
  auto stride = 3 * width * sizeof(uint8_t);
  stbi_write_png(path, width, height, 3, data, stride);
}
