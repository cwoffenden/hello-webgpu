#include "webgpu.h"

WGPUDevice device;
WGPUQueue queue;
WGPUSwapChain swapchain;
WGPURenderPipeline pipeline;

/**
 * Vertex shader SPIR-V.
 * \code
 *	#version 450
 *	const vec2 pos[3] = vec2[3](vec2(0.0f, 0.5f), vec2(-0.5f, -0.5f), vec2(0.5f, -0.5f));
 *	void main() {
 *		gl_Position = vec4(pos[gl_VertexIndex], 0.0, 1.0);
 *	}
 * \endcode
 */
static uint32_t const triangle_vert[] = {
	0x07230203, 0x00010000, 0x00080008, 0x00000028, 0x00000000, 0x00020011, 0x00000001, 0x0006000b,
	0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001,
	0x0007000f, 0x00000000, 0x00000004, 0x6e69616d, 0x00000000, 0x0000000d, 0x0000001b, 0x00030003,
	0x00000002, 0x000001c2, 0x00040005, 0x00000004, 0x6e69616d, 0x00000000, 0x00060005, 0x0000000b,
	0x505f6c67, 0x65567265, 0x78657472, 0x00000000, 0x00060006, 0x0000000b, 0x00000000, 0x505f6c67,
	0x7469736f, 0x006e6f69, 0x00070006, 0x0000000b, 0x00000001, 0x505f6c67, 0x746e696f, 0x657a6953,
	0x00000000, 0x00070006, 0x0000000b, 0x00000002, 0x435f6c67, 0x4470696c, 0x61747369, 0x0065636e,
	0x00070006, 0x0000000b, 0x00000003, 0x435f6c67, 0x446c6c75, 0x61747369, 0x0065636e, 0x00030005,
	0x0000000d, 0x00000000, 0x00060005, 0x0000001b, 0x565f6c67, 0x65747265, 0x646e4978, 0x00007865,
	0x00050005, 0x0000001e, 0x65646e69, 0x6c626178, 0x00000065, 0x00050048, 0x0000000b, 0x00000000,
	0x0000000b, 0x00000000, 0x00050048, 0x0000000b, 0x00000001, 0x0000000b, 0x00000001, 0x00050048,
	0x0000000b, 0x00000002, 0x0000000b, 0x00000003, 0x00050048, 0x0000000b, 0x00000003, 0x0000000b,
	0x00000004, 0x00030047, 0x0000000b, 0x00000002, 0x00040047, 0x0000001b, 0x0000000b, 0x0000002a,
	0x00020013, 0x00000002, 0x00030021, 0x00000003, 0x00000002, 0x00030016, 0x00000006, 0x00000020,
	0x00040017, 0x00000007, 0x00000006, 0x00000004, 0x00040015, 0x00000008, 0x00000020, 0x00000000,
	0x0004002b, 0x00000008, 0x00000009, 0x00000001, 0x0004001c, 0x0000000a, 0x00000006, 0x00000009,
	0x0006001e, 0x0000000b, 0x00000007, 0x00000006, 0x0000000a, 0x0000000a, 0x00040020, 0x0000000c,
	0x00000003, 0x0000000b, 0x0004003b, 0x0000000c, 0x0000000d, 0x00000003, 0x00040015, 0x0000000e,
	0x00000020, 0x00000001, 0x0004002b, 0x0000000e, 0x0000000f, 0x00000000, 0x00040017, 0x00000010,
	0x00000006, 0x00000002, 0x0004002b, 0x00000008, 0x00000011, 0x00000003, 0x0004001c, 0x00000012,
	0x00000010, 0x00000011, 0x0004002b, 0x00000006, 0x00000013, 0x00000000, 0x0004002b, 0x00000006,
	0x00000014, 0x3f000000, 0x0005002c, 0x00000010, 0x00000015, 0x00000013, 0x00000014, 0x0004002b,
	0x00000006, 0x00000016, 0xbf000000, 0x0005002c, 0x00000010, 0x00000017, 0x00000016, 0x00000016,
	0x0005002c, 0x00000010, 0x00000018, 0x00000014, 0x00000016, 0x0006002c, 0x00000012, 0x00000019,
	0x00000015, 0x00000017, 0x00000018, 0x00040020, 0x0000001a, 0x00000001, 0x0000000e, 0x0004003b,
	0x0000001a, 0x0000001b, 0x00000001, 0x00040020, 0x0000001d, 0x00000007, 0x00000012, 0x00040020,
	0x0000001f, 0x00000007, 0x00000010, 0x0004002b, 0x00000006, 0x00000022, 0x3f800000, 0x00040020,
	0x00000026, 0x00000003, 0x00000007, 0x00050036, 0x00000002, 0x00000004, 0x00000000, 0x00000003,
	0x000200f8, 0x00000005, 0x0004003b, 0x0000001d, 0x0000001e, 0x00000007, 0x0004003d, 0x0000000e,
	0x0000001c, 0x0000001b, 0x0003003e, 0x0000001e, 0x00000019, 0x00050041, 0x0000001f, 0x00000020,
	0x0000001e, 0x0000001c, 0x0004003d, 0x00000010, 0x00000021, 0x00000020, 0x00050051, 0x00000006,
	0x00000023, 0x00000021, 0x00000000, 0x00050051, 0x00000006, 0x00000024, 0x00000021, 0x00000001,
	0x00070050, 0x00000007, 0x00000025, 0x00000023, 0x00000024, 0x00000013, 0x00000022, 0x00050041,
	0x00000026, 0x00000027, 0x0000000d, 0x0000000f, 0x0003003e, 0x00000027, 0x00000025, 0x000100fd,
	0x00010038
};

/**
 * Fragment shader SPIR-V.
 * \code
 *	#version 450
 *	layout(location = 0) out vec4 fragColor;
 *	void main() {
 *		fragColor = vec4(1.0, 0.0, 1.0, 1.0);
*	}
 * \endcode
 */
static uint32_t const triangle_frag[] = {
	0x07230203, 0x00010000, 0x00080008, 0x0000000d, 0x00000000, 0x00020011, 0x00000001, 0x0006000b,
	0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001,
	0x0006000f, 0x00000004, 0x00000004, 0x6e69616d, 0x00000000, 0x00000009, 0x00030010, 0x00000004,
	0x00000007, 0x00030003, 0x00000002, 0x000001c2, 0x00040005, 0x00000004, 0x6e69616d, 0x00000000,
	0x00050005, 0x00000009, 0x67617266, 0x6f6c6f43, 0x00000072, 0x00040047, 0x00000009, 0x0000001e,
	0x00000000, 0x00020013, 0x00000002, 0x00030021, 0x00000003, 0x00000002, 0x00030016, 0x00000006,
	0x00000020, 0x00040017, 0x00000007, 0x00000006, 0x00000004, 0x00040020, 0x00000008, 0x00000003,
	0x00000007, 0x0004003b, 0x00000008, 0x00000009, 0x00000003, 0x0004002b, 0x00000006, 0x0000000a,
	0x3f800000, 0x0004002b, 0x00000006, 0x0000000b, 0x00000000, 0x0007002c, 0x00000007, 0x0000000c,
	0x0000000a, 0x0000000b, 0x0000000a, 0x0000000a, 0x00050036, 0x00000002, 0x00000004, 0x00000000,
	0x00000003, 0x000200f8, 0x00000005, 0x0003003e, 0x00000009, 0x0000000c, 0x000100fd, 0x00010038
};

/**
 * Helper to create a shader from SPIR-V IR.
 * 
 * \param[in] code shader source (output using the \c -V \c -x options in \c glslangValidator)
 * \param[in] size size of \a code in bytes
 * \param[in] label optional shader name
 */
static WGPUShaderModule createShader(const uint32_t* code, uint32_t size, const char* label = nullptr) {
	WGPUShaderModuleDescriptor desc = {};
	desc.label    = label;
	desc.codeSize = size / sizeof(uint32_t);
	desc.code     = code;
	return wgpuDeviceCreateShaderModule(device, &desc);
}

/**
 * Bare minimum test code to draw the a triangle using the above shaders.
 */
static void createPipeline() {
	WGPUShaderModule vertMod = createShader(triangle_vert, sizeof triangle_vert);
	WGPUShaderModule fragMod = createShader(triangle_frag, sizeof triangle_frag);
	
	WGPURenderPipelineDescriptor desc = {};

	desc.vertexStage.module = vertMod;
	desc.vertexStage.entryPoint = "main";

	WGPUProgrammableStageDescriptor fragStage = {};
	fragStage.module = fragMod;
	fragStage.entryPoint = "main";
	desc.fragmentStage = &fragStage;

	desc.primitiveTopology = WGPUPrimitiveTopology_TriangleList;

	desc.sampleCount = 1;

	WGPUBlendDescriptor blendDesc = {};
	blendDesc.operation = WGPUBlendOperation_Add;
	blendDesc.srcFactor = WGPUBlendFactor_SrcAlpha;
	blendDesc.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
	WGPUColorStateDescriptor colorDesc = {};
	colorDesc.format = webgpu::getSwapChainFormat(device);
	colorDesc.alphaBlend = blendDesc;
	colorDesc.colorBlend = blendDesc;
	colorDesc.writeMask = WGPUColorWriteMask_All;

	desc.colorStateCount = 1;
	desc.colorStates = &colorDesc;

	desc.sampleMask = 0xFFFFFFFF;

	pipeline = wgpuDeviceCreateRenderPipeline(device, &desc);

	wgpuShaderModuleRelease(fragMod);
	wgpuShaderModuleRelease(vertMod);
}

static bool redraw() {
	WGPUTextureView backBufView = wgpuSwapChainGetCurrentTextureView(swapchain);			// create textureView

	WGPURenderPassColorAttachmentDescriptor colorDesc = {};
	colorDesc.attachment = backBufView;
	colorDesc.loadOp  = WGPULoadOp_Clear;
	colorDesc.storeOp = WGPUStoreOp_Store;
	colorDesc.clearColor.r = 0.3f;
	colorDesc.clearColor.g = 0.3f;
	colorDesc.clearColor.b = 0.3f;

	WGPURenderPassDescriptor renderpass = {};
	renderpass.colorAttachmentCount = 1;
	renderpass.colorAttachments = &colorDesc;

	WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device, nullptr);			// create encoder
	WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(encoder, &renderpass);	// create pass

	// draw the triangle (comment these two lines to simply clear the screen)
	wgpuRenderPassEncoderSetPipeline(pass, pipeline);
	wgpuRenderPassEncoderDraw(pass, 3, 1, 0, 0);

	wgpuRenderPassEncoderEndPass(pass);
	wgpuRenderPassEncoderRelease(pass);														// release pass
	WGPUCommandBuffer commands = wgpuCommandEncoderFinish(encoder, nullptr);				// create commands
	wgpuCommandEncoderRelease(encoder);														// release encoder

	wgpuQueueSubmit(queue, 1, &commands);
	wgpuCommandBufferRelease(commands);														// release commands
#ifndef __EMSCRIPTEN__
	/*
	 * TODO: wgpuSwapChainPresent is unsupported in Emscripten, so what do we do?
	 */
	wgpuSwapChainPresent(swapchain);
#endif
	wgpuTextureViewRelease(backBufView);													// release textureView

	return true;
}

extern "C" int __main__(int /*argc*/, char* /*argv*/[]) {
	if (window::Handle wHnd = window::create()) {
		if ((device = webgpu::create(wHnd))) {
			queue = wgpuDeviceCreateQueue(device);
			swapchain = webgpu::createSwapChain(device);
			createPipeline();

			window::show(wHnd);
			window::loop(redraw);

		#ifndef __EMSCRIPTEN__
			wgpuRenderPipelineRelease(pipeline);
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
