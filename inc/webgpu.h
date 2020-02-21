/**
 * \file webgpu.h
 * WebGPU/Dawn wrapper.
 */
#pragma once

#ifdef __EMSCRIPTEN__
#include <webgpu/webgpu.h>
#else
#include <dawn/webgpu.h>
#endif

#include "window.h"

namespace webgpu {
WGPUDevice create(window::Handle window, WGPUBackendType type = WGPUBackendType_Force32);

/**
 * Temporary: replace will a call to create the swap chain directly. The
 * browser creates the swap chain from the canvas (which is the window in our
 * analogy) so this needs a rethink outside of Dawn.
 */
uintptr_t getSwapChainImpl(WGPUDevice device);

/**
 * See \c #getSwapChainImpl();
 */
WGPUTextureFormat getSwapChainFormat(WGPUDevice device);
}
