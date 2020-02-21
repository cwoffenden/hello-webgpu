#include "webgpu.h"

WGPUDevice device;
WGPUQueue queue;
WGPUSwapChain swapchain;

bool redraw() {
	WGPUTextureView textureView = wgpuSwapChainGetCurrentTextureView(swapchain);			// create textureView

	WGPURenderPassColorAttachmentDescriptor colorDesc = {};
	colorDesc.attachment = textureView;
	colorDesc.loadOp  = WGPULoadOp_Clear;
	colorDesc.storeOp = WGPUStoreOp_Store;
	colorDesc.clearColor.r = 1.0f;
	colorDesc.clearColor.b = 1.0f;

	WGPURenderPassDescriptor renderpass = {};
	renderpass.colorAttachmentCount = 1;
	renderpass.colorAttachments = &colorDesc;

	WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device, nullptr);			// create encoder
	WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(encoder, &renderpass);	// create pass
	wgpuRenderPassEncoderEndPass(pass);
	wgpuRenderPassEncoderRelease(pass);														// release pass
	WGPUCommandBuffer commands = wgpuCommandEncoderFinish(encoder, nullptr);				// create commands
	wgpuCommandEncoderRelease(encoder);														// release encoder

	wgpuQueueSubmit(queue, 1, &commands);
	wgpuCommandBufferRelease(commands);														// release commands
	wgpuSwapChainPresent(swapchain);
	wgpuTextureViewRelease(textureView);													// release textureView

	return true;
}

int main(int /*argc*/, char* /*argv*/[]) {
	if (window::Handle wHnd = window::create()) {
		if ((device = webgpu::create(wHnd))) {
			queue = wgpuDeviceCreateQueue(device);
			
			WGPUSwapChainDescriptor swapDesc = {};
			swapDesc.implementation = webgpu::getSwapChainImpl(device);
			swapchain = wgpuDeviceCreateSwapChain(device, nullptr, &swapDesc);
			wgpuSwapChainConfigure(swapchain,
				webgpu::getSwapChainFormat(device),
					WGPUTextureUsage_OutputAttachment, 800, 450);
			
			window::show(wHnd);
			window::loop(redraw);

		#ifndef __EMSCRIPTEN__
			wgpuSwapChainRelease(swapchain);
			wgpuQueueRelease(queue);
			wgpuDeviceRelease(device);
		#endif
		}
	#ifndef __EMSCRIPTEN__
		window::destroy(wHnd);
	#endif
	}
	return 0;
}
