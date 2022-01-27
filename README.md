# "Hello, Triangle" WebGPU and Dawn

[![MSVC workflow](https://github.com/cwoffenden/hello-webgpu/actions/workflows/msbuild.yml/badge.svg)](https://github.com/cwoffenden/hello-webgpu/actions/workflows/msbuild.yml) [![Xcode workflow](https://github.com/cwoffenden/hello-webgpu/actions/workflows/xcode.yml/badge.svg)](https://github.com/cwoffenden/hello-webgpu/actions/workflows/xcode.yml) [![Emscripten workflow](https://github.com/cwoffenden/hello-webgpu/actions/workflows/emscripten.yml/badge.svg)](https://github.com/cwoffenden/hello-webgpu/actions/workflows/emscripten.yml)

Starter project for C++ [WebGPU](//gpuweb.github.io/gpuweb/)/[Emscripten](//emscripten.org) and [Dawn](//dawn.googlesource.com/dawn). Build for Windows using Visual Studio from 2015 onwards. Build for Emscripten using CMake (or on Windows using `build-web.bat`). Build for Mac using the Xcode project (tested with Xcode 11 & 12 and macOS 10.14, 10.15 & 11 beta).

Due to the changing nature of the API, browser compatibility is usually limited to the version as of the latest commit. Currently [tested and working](//wip.numfum.com/cw/2022-01-26/index.html) with Chrome Canary 100.0.4851.0 (with the `--enable-unsafe-webgpu` flag) and Emscripten 3.1.2.

The included `libdawn` is pre-built for Windows/MSVC and Mac; [see instructions](lib/README.md) if you wish to build it yourself for Windows (out of the box Dawn on Windows builds with [Depot Tools](//commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools.html)/Clang so MSVC's linker fails with the exposed `std` types).

![Chrome and native side-by-side](screenshot.png)

Dawn is Apache 2.0 licensed (see [LICENSE](lib/dawn/LICENSE)). The example code is released under a [Creative Commons Zero license](//creativecommons.org/publicdomain/zero/1.0/) (or Public Domain, whichever is applicable in your jurisdiction).
