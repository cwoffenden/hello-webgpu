#include "webgpu.h"

//******************************** Public API ********************************/

WGPUDevice webgpu::create(window::Handle /*window*/, WGPUBackendType /*type*/) {
	return nullptr;
}

uintptr_t webgpu::getSwapChainImpl(WGPUDevice /*device*/) {
	return 0;
}

WGPUTextureFormat webgpu::getSwapChainFormat(WGPUDevice /*device*/) {
	return WGPUTextureFormat_Undefined;
}
