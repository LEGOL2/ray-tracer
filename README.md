# Ray-Tracer

This is my effort to create a CPU based ray tracer, based on book [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) by Peter Shirley.

Goal of this project is to improve my knowledge about 3D graphics, ray tracing and modern C++.

## Build
Requires [Meson](https://mesonbuild.com/) build system, [ninja](https://ninja-build.org/) and C++17 compatible compiler (I'm using `gcc 11`).
```
meson build
ninja -C build
./ray-tracer
```

## License
This repository is licensed under MIT. Please refer to [LICENSE.md](LICENSE.md)

`stb_image_write.hpp` is a header-only library that allows for writing images to `.png` format. It's licensed under MIT. [Repository](https://github.com/nothings/stb)
