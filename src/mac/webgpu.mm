#include "webgpu.h"

//******************************** Public API ********************************/

WGPUDevice webgpu::create(window::Handle /*window*/, WGPUBackendType /*type*/) {
	return nullptr;
}

WGPUSwapChain webgpu::createSwapChain(WGPUDevice /*device*/) {
	return nullptr;
}

WGPUTextureFormat webgpu::getSwapChainFormat(WGPUDevice /*device*/) {
	return WGPUTextureFormat_Undefined;
}
