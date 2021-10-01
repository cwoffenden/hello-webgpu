#include "webgpu.h"

#include <cstdio>

/*
 * We need an up-to-date version of Emscripten for the API support.
 *
 * TODO: needs 2.0.31 or higher
 */
#if __EMSCRIPTEN_major__ == 1 && (__EMSCRIPTEN_minor__ < 40 || (__EMSCRIPTEN_minor__ == 40 && __EMSCRIPTEN_tiny__ < 1))
#error "Emscripten 1.40.1 or higher required"
#endif

//#include <emscripten/html5_webgpu.h>

//******************************** Public API ********************************/

void webgpu::create(window::Handle /*window*/, Created callback, WGPUBackendType /*type*/) {
	static const WGPUInstance instance = nullptr;
	WGPURequestAdapterOptions aOpt = {};
	aOpt.powerPreference = WGPUPowerPreference_HighPerformance;
	wgpuInstanceRequestAdapter(instance, &aOpt, [](WGPURequestAdapterStatus status, WGPUAdapter adapter, const char* /*message*/, void* userData) {
		if (status == WGPURequestAdapterStatus_Success) {
			wgpuAdapterRequestDevice(adapter, nullptr, [](WGPURequestDeviceStatus status, WGPUDevice device, const char* /*message*/, void* userData) {
				if (status == WGPURequestDeviceStatus_Success) {
					if (userData) {
						reinterpret_cast<Created>(userData)(device);
					} else {
						printf("wgpuAdapterRequestDevice: %08x\n", (unsigned) device);
					}
				} else {
					printf("No WebGPU device; not starting\n");
				}
			}, userData);
		} else {
			printf("No WebGPU adapter; not starting\n");
		}
	}, reinterpret_cast<void*>(callback));
}

WGPUSwapChain webgpu::createSwapChain(WGPUDevice device) {
	WGPUSurfaceDescriptorFromCanvasHTMLSelector canvDesc = {};
	canvDesc.chain.sType = WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector;
	canvDesc.selector = "canvas";
	
	WGPUSurfaceDescriptor surfDesc = {};
	surfDesc.nextInChain = reinterpret_cast<WGPUChainedStruct*>(&canvDesc);
	
	WGPUSurface surface = wgpuInstanceCreateSurface(nullptr, &surfDesc);
	
	WGPUSwapChainDescriptor swapDesc = {};
	swapDesc.usage  = WGPUTextureUsage_RenderAttachment;
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
