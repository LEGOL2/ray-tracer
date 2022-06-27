#include <cstdint>
#include <iostream>
#include <vector>

#include "src/image/image.hpp"
#include "src/math/vec.hpp"

int main() {
  constexpr uint32_t WIDTH = 256;
  constexpr uint32_t HEIGHT = 256;

  std::vector<color<uint8_t>> colors(WIDTH * HEIGHT);
  for (uint32_t j = 0; j < HEIGHT; j++) {
    for (uint32_t i = 0; i < WIDTH; i++) {
      auto idx = j * HEIGHT + i;
      auto &c = colors[idx];
      c.r(double(i) / (WIDTH - 1));
      c.g(double(j) / (HEIGHT - 1));
      c.b(0.25);
    }
  }

  write_image("image.png", WIDTH, HEIGHT, colors);
}
