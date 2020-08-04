#include "webgpu.h"

/*
 * We need an up-to-date version of Emscripten for the API support.
 */
#if __EMSCRIPTEN_major__ == 1 && (__EMSCRIPTEN_minor__ < 40 || (__EMSCRIPTEN_minor__ == 40 && __EMSCRIPTEN_tiny__ < 1))
#error "Emscripten 1.40.1 or higher required"
#endif

#include <emscripten/html5_webgpu.h>

//******************************** Public API ********************************/

WGPUDevice webgpu::create(window::Handle /*window*/, WGPUBackendType /*type*/) {
	/*
	 * Before calling this needs to have the WebGPU device pre-inited from JS,
	 * which is an async call so needs some magic to delay running the main()
	 * until after the promise is resolved.
	 */
	return emscripten_webgpu_get_device();
}

WGPUSwapChain webgpu::createSwapChain(WGPUDevice device) {
	WGPUSurfaceDescriptorFromCanvasHTMLSelector canvDesc = {};
	canvDesc.chain.sType = WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector;
	canvDesc.selector = "canvas";
	
	WGPUSurfaceDescriptor surfDesc = {};
	surfDesc.nextInChain = reinterpret_cast<WGPUChainedStruct*>(&canvDesc);
	
	WGPUSurface surface = wgpuInstanceCreateSurface(nullptr, &surfDesc);
	
	WGPUSwapChainDescriptor swapDesc = {};
	swapDesc.usage  = WGPUTextureUsage_OutputAttachment;
	swapDesc.format = WGPUTextureFormat_BGRA8Unorm;
	swapDesc.width  = 800;
	swapDesc.height = 450;
	swapDesc.presentMode = WGPUPresentMode_Fifo;
	
	WGPUSwapChain swapchain = wgpuDeviceCreateSwapChain(device, surface, &swapDesc);
	
	return swapchain;
}

WGPUTextureFormat webgpu::getSwapChainFormat(WGPUDevice /*device*/) {
	return WGPUTextureFormat_BGRA8Unorm;
}
