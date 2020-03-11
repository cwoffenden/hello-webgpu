#include "webgpu.h"

#include <emscripten/html5.h>

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
	/*
	 * Note: this struct differs between the Dawn and Emscripten headers. The
	 * 'sType' property in Dawn is a member of the WGPUChainedStruct (which is
	 * a member of 'chain'). The address offset (how Emscripten looks it up)
	 * should be the same regardless.
	 */
	WGPUSurfaceDescriptorFromHTMLCanvasId canvDesc = {};
	canvDesc.sType = WGPUSType_SurfaceDescriptorFromHTMLCanvasId;
	canvDesc.id = "canvas";
	
	WGPUSurfaceDescriptor surfDesc = {};
	surfDesc.nextInChain = reinterpret_cast<WGPUChainedStruct*>(&canvDesc);
	
	WGPUSurface surface = wgpuInstanceCreateSurface(nullptr, &surfDesc);
	
	WGPUSwapChainDescriptor swapDesc = {};
	swapDesc.usage  = WGPUTextureUsage_OutputAttachment;
	swapDesc.format = WGPUTextureFormat_BGRA8Unorm;
	swapDesc.width  = 800;
	swapDesc.height = 450;
	swapDesc.presentMode = WGPUPresentMode_VSync;
	
	WGPUSwapChain swapchain = wgpuDeviceCreateSwapChain(device, surface, &swapDesc);
	
	return swapchain;
}

WGPUTextureFormat webgpu::getSwapChainFormat(WGPUDevice /*device*/) {
	return WGPUTextureFormat_BGRA8Unorm;
}
