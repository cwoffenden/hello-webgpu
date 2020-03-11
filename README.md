# Hello WebGPU/Dawn

Starter project for C++ [WebGPU](//gpuweb.github.io/gpuweb/)/[Emscripten](//emscripten.org) and [Dawn](//dawn.googlesource.com/dawn). Build using Visual Studio from 2015 onwards. Build for Emscripten using (on Windows) `build-ems.bat` (CMake project to follow).

The included `libdawn` is pre-built for Windows/MSVC; [see instructions](lib/README.md) if you wish to build it yourself (out of the box Dawn on Windows builds with [Depot Tools](https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools.html)/Clang so MSVC's linker fails with the exposed `std` types).

Dawn is Apache 2.0 licensed (see [LICENSE](lib/dawn/LICENSE)). The example code is released under a [Creative Commons Zero license](//creativecommons.org/publicdomain/zero/1.0/) (or Public Domain, whichever is applicable in your jurisdiction).
