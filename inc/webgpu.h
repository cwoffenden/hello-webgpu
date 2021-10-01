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
 * \param[in] callback device creation callback
 * \param[in] type optional backend type (defaulting to the best choice for the system)
 */
void create(window::Handle window, Created callback, WGPUBackendType type = WGPUBackendType_Force32);

/**
 * Creates a swapchain for the passed-in device.
 *
 * \param[in] device WebGPU device
 */
WGPUSwapChain createSwapChain(WGPUDevice device);

/**
 * See \c #createSwapChain()
 *
 * \param[in] device WebGPU device
 */
WGPUTextureFormat getSwapChainFormat(WGPUDevice device);
}
