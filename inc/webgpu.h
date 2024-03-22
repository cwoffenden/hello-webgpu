/**
 * \file webgpu.h
 * WebGPU/Dawn wrapper.
 */
#pragma once

#include <webgpu/webgpu.h>

#include "window.h"

namespace webgpu {
/**
 * Device creation callback signature.
 *
 * \param[in] device created WebGPU device (or \c null if creation failed)
 */
typedef void (*Created) (WGPUDevice device);

/**
 * Creates a WebGPU device.
 *
 * \param[in] window window handle
 * \param[in] type optional backend type (defaulting to the best choice for the system)
 */
WGPUDevice create(window::Handle window, WGPUBackendType type = WGPUBackendType_Undefined);

WGPUSwapChain createSwapChain(WGPUDevice device);

/**
 * See \c #createSwapChain();
 */
WGPUTextureFormat getSwapChainFormat(WGPUDevice device);
}
