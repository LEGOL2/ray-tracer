#include <cstdint>
#include <iostream>
#include <vector>

#include "src/image/image.hpp"

int main() {
  constexpr uint32_t WIDTH = 256;
  constexpr uint32_t HEIGHT = 256;

  std::vector<uint8_t> data(WIDTH * HEIGHT * 3);
  for (uint32_t j = 0; j < HEIGHT; j++) {
    for (uint32_t i = 0; i < WIDTH; i++) {
      auto r = double(i) / (WIDTH - 1);
      auto g = double(j) / (HEIGHT - 1);
      auto b = 0.25;

      auto idx = (j * HEIGHT + i) * 3;
      data[idx + 0] = static_cast<int>(255.999 * r);
      data[idx + 1] = static_cast<int>(255.999 * g);
      data[idx + 2] = static_cast<int>(255.999 * b);
    }
    std::cout << std::endl;
  }

  write_image("image.png", WIDTH, HEIGHT, data.data());
}
