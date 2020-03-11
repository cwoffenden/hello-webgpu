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

WGPUSwapChain createSwapChain(WGPUDevice device);

/**
 * See \c #createSwapChain();
 */
WGPUTextureFormat getSwapChainFormat(WGPUDevice device);
}
