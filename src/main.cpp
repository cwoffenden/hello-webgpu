#include "webgpu.h"

#include <string.h>
#include <stdio.h>

WGPUDevice device;
WGPUQueue queue;
WGPUSwapChain swapchain;

WGPURenderPipeline pipeline;
WGPUBuffer vertBuf; // vertex buffer with triangle position and colours
WGPUBuffer indxBuf; // index buffer
WGPUBuffer uRotBuf; // uniform buffer (containing the rotation angle)
WGPUBindGroup bindGroup;

/**
 * Current rotation angle (in degrees, updated per frame).
 */
float rotDeg = 0.0f;

/**
 * Vertex shader SPIR-V.
 * \code
 *	// glslc -Os -mfmt=num -o - -c in.vert
 *	#version 450
 *	layout(set = 0, binding = 0) uniform Rotation {
 *		float uRot;
 *	};
 *	layout(location = 0) in  vec2 aPos;
 *	layout(location = 1) in  vec3 aCol;
 *	layout(location = 0) out vec3 vCol;
 *	void main() {
 *		float cosA = cos(radians(uRot));
 *		float sinA = sin(radians(uRot));
 *		mat3 rot = mat3(cosA, sinA, 0.0,
 *					   -sinA, cosA, 0.0,
 *						0.0,  0.0,  1.0);
 *		gl_Position = vec4(rot * vec3(aPos, 1.0), 1.0);
 *		vCol = aCol;
 *	}
 * \endcode
 */
static uint32_t const triangle_vert[] = {
	0x07230203, 0x00010000, 0x000d0008, 0x00000043, 0x00000000, 0x00020011, 0x00000001, 0x0006000b,
	0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001,
	0x0009000f, 0x00000000, 0x00000004, 0x6e69616d, 0x00000000, 0x0000002d, 0x00000031, 0x0000003e,
	0x00000040, 0x00050048, 0x00000009, 0x00000000, 0x00000023, 0x00000000, 0x00030047, 0x00000009,
	0x00000002, 0x00040047, 0x0000000b, 0x00000022, 0x00000000, 0x00040047, 0x0000000b, 0x00000021,
	0x00000000, 0x00050048, 0x0000002b, 0x00000000, 0x0000000b, 0x00000000, 0x00050048, 0x0000002b,
	0x00000001, 0x0000000b, 0x00000001, 0x00050048, 0x0000002b, 0x00000002, 0x0000000b, 0x00000003,
	0x00050048, 0x0000002b, 0x00000003, 0x0000000b, 0x00000004, 0x00030047, 0x0000002b, 0x00000002,
	0x00040047, 0x00000031, 0x0000001e, 0x00000000, 0x00040047, 0x0000003e, 0x0000001e, 0x00000000,
	0x00040047, 0x00000040, 0x0000001e, 0x00000001, 0x00020013, 0x00000002, 0x00030021, 0x00000003,
	0x00000002, 0x00030016, 0x00000006, 0x00000020, 0x0003001e, 0x00000009, 0x00000006, 0x00040020,
	0x0000000a, 0x00000002, 0x00000009, 0x0004003b, 0x0000000a, 0x0000000b, 0x00000002, 0x00040015,
	0x0000000c, 0x00000020, 0x00000001, 0x0004002b, 0x0000000c, 0x0000000d, 0x00000000, 0x00040020,
	0x0000000e, 0x00000002, 0x00000006, 0x00040017, 0x00000018, 0x00000006, 0x00000003, 0x00040018,
	0x00000019, 0x00000018, 0x00000003, 0x0004002b, 0x00000006, 0x0000001e, 0x00000000, 0x0004002b,
	0x00000006, 0x00000022, 0x3f800000, 0x00040017, 0x00000027, 0x00000006, 0x00000004, 0x00040015,
	0x00000028, 0x00000020, 0x00000000, 0x0004002b, 0x00000028, 0x00000029, 0x00000001, 0x0004001c,
	0x0000002a, 0x00000006, 0x00000029, 0x0006001e, 0x0000002b, 0x00000027, 0x00000006, 0x0000002a,
	0x0000002a, 0x00040020, 0x0000002c, 0x00000003, 0x0000002b, 0x0004003b, 0x0000002c, 0x0000002d,
	0x00000003, 0x00040017, 0x0000002f, 0x00000006, 0x00000002, 0x00040020, 0x00000030, 0x00000001,
	0x0000002f, 0x0004003b, 0x00000030, 0x00000031, 0x00000001, 0x00040020, 0x0000003b, 0x00000003,
	0x00000027, 0x00040020, 0x0000003d, 0x00000003, 0x00000018, 0x0004003b, 0x0000003d, 0x0000003e,
	0x00000003, 0x00040020, 0x0000003f, 0x00000001, 0x00000018, 0x0004003b, 0x0000003f, 0x00000040,
	0x00000001, 0x0006002c, 0x00000018, 0x00000042, 0x0000001e, 0x0000001e, 0x00000022, 0x00050036,
	0x00000002, 0x00000004, 0x00000000, 0x00000003, 0x000200f8, 0x00000005, 0x00050041, 0x0000000e,
	0x0000000f, 0x0000000b, 0x0000000d, 0x0004003d, 0x00000006, 0x00000010, 0x0000000f, 0x0006000c,
	0x00000006, 0x00000011, 0x00000001, 0x0000000b, 0x00000010, 0x0006000c, 0x00000006, 0x00000012,
	0x00000001, 0x0000000e, 0x00000011, 0x0006000c, 0x00000006, 0x00000017, 0x00000001, 0x0000000d,
	0x00000011, 0x0004007f, 0x00000006, 0x00000020, 0x00000017, 0x00060050, 0x00000018, 0x00000023,
	0x00000012, 0x00000017, 0x0000001e, 0x00060050, 0x00000018, 0x00000024, 0x00000020, 0x00000012,
	0x0000001e, 0x00060050, 0x00000019, 0x00000026, 0x00000023, 0x00000024, 0x00000042, 0x0004003d,
	0x0000002f, 0x00000032, 0x00000031, 0x00050051, 0x00000006, 0x00000033, 0x00000032, 0x00000000,
	0x00050051, 0x00000006, 0x00000034, 0x00000032, 0x00000001, 0x00060050, 0x00000018, 0x00000035,
	0x00000033, 0x00000034, 0x00000022, 0x00050091, 0x00000018, 0x00000036, 0x00000026, 0x00000035,
	0x00050051, 0x00000006, 0x00000037, 0x00000036, 0x00000000, 0x00050051, 0x00000006, 0x00000038,
	0x00000036, 0x00000001, 0x00050051, 0x00000006, 0x00000039, 0x00000036, 0x00000002, 0x00070050,
	0x00000027, 0x0000003a, 0x00000037, 0x00000038, 0x00000039, 0x00000022, 0x00050041, 0x0000003b,
	0x0000003c, 0x0000002d, 0x0000000d, 0x0003003e, 0x0000003c, 0x0000003a, 0x0004003d, 0x00000018,
	0x00000041, 0x00000040, 0x0003003e, 0x0000003e, 0x00000041, 0x000100fd, 0x00010038
};

/**
 * Fragment shader SPIR-V.
 * \code
 *	// glslc -Os -mfmt=num -o - -c in.frag
 *	#version 450
 *	layout(location = 0) in  vec3 vCol;
 *	layout(location = 0) out vec4 fragColor;
 *	void main() {
 *		fragColor = vec4(vCol, 1.0);
 *	}
 * \endcode
 */
static uint32_t const triangle_frag[] = {
	0x07230203, 0x00010000, 0x000d0007, 0x00000013, 0x00000000, 0x00020011, 0x00000001, 0x0006000b,
	0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001,
	0x0007000f, 0x00000004, 0x00000004, 0x6e69616d, 0x00000000, 0x00000009, 0x0000000c, 0x00030010,
	0x00000004, 0x00000007, 0x00040047, 0x00000009, 0x0000001e, 0x00000000, 0x00040047, 0x0000000c,
	0x0000001e, 0x00000000, 0x00020013, 0x00000002, 0x00030021, 0x00000003, 0x00000002, 0x00030016,
	0x00000006, 0x00000020, 0x00040017, 0x00000007, 0x00000006, 0x00000004, 0x00040020, 0x00000008,
	0x00000003, 0x00000007, 0x0004003b, 0x00000008, 0x00000009, 0x00000003, 0x00040017, 0x0000000a,
	0x00000006, 0x00000003, 0x00040020, 0x0000000b, 0x00000001, 0x0000000a, 0x0004003b, 0x0000000b,
	0x0000000c, 0x00000001, 0x0004002b, 0x00000006, 0x0000000e, 0x3f800000, 0x00050036, 0x00000002,
	0x00000004, 0x00000000, 0x00000003, 0x000200f8, 0x00000005, 0x0004003d, 0x0000000a, 0x0000000d,
	0x0000000c, 0x00050051, 0x00000006, 0x0000000f, 0x0000000d, 0x00000000, 0x00050051, 0x00000006,
	0x00000010, 0x0000000d, 0x00000001, 0x00050051, 0x00000006, 0x00000011, 0x0000000d, 0x00000002,
	0x00070050, 0x00000007, 0x00000012, 0x0000000f, 0x00000010, 0x00000011, 0x0000000e, 0x0003003e,
	0x00000009, 0x00000012, 0x000100fd, 0x00010038
};

/**
 * Helper to create a shader from SPIR-V IR.
 *
 * \param[in] code shader source (output using the \c -V \c -x options in \c glslangValidator)
 * \param[in] size size of \a code in bytes
 * \param[in] label optional shader name
 */
static WGPUShaderModule createShader(const uint32_t* code, uint32_t size, const char* label = nullptr) {
	WGPUShaderModuleSPIRVDescriptor spirv = {};
	spirv.chain.sType = WGPUSType_ShaderModuleSPIRVDescriptor;
	spirv.codeSize = size / sizeof(uint32_t);
	spirv.code = code;
	WGPUShaderModuleDescriptor desc = {};
	desc.nextInChain = reinterpret_cast<WGPUChainedStruct*>(&spirv);
	desc.label = label;
	return wgpuDeviceCreateShaderModule(device, &desc);
}

/**
 * Helper to create a buffer.
 *
 * \param[in] data pointer to the start of the raw data
 * \param[in] size number of bytes in \a data
 * \param[in] usage type of buffer
 */
static WGPUBuffer createBuffer(const void* data, size_t size, WGPUBufferUsage usage) {
	WGPUBufferDescriptor desc = {};
	desc.usage = WGPUBufferUsage_CopyDst | usage;
	desc.size  = size;
	WGPUBuffer buffer = wgpuDeviceCreateBuffer(device, &desc);
	wgpuBufferSetSubData(buffer, 0, size, data);
	return buffer;
}

/**
 * Bare minimum pipeline to draw a triangle using the above shaders.
 */
static void createPipelineAndBuffers() {
	// compile shaders
	
	WGPUShaderModule vertMod = createShader(triangle_vert, sizeof triangle_vert);
	WGPUShaderModule fragMod = createShader(triangle_frag, sizeof triangle_frag);

	// bind group layout (used by both the pipeline layout and uniform bind group, released at the end of this function)
	WGPUBindGroupLayoutEntry bglEntry = {};
	bglEntry.binding = 0;
	bglEntry.visibility = WGPUShaderStage_Vertex;
	bglEntry.type = WGPUBindingType_UniformBuffer;

	WGPUBindGroupLayoutDescriptor bglDesc = {};
	bglDesc.entryCount = 1;
	bglDesc.entries = &bglEntry;
	WGPUBindGroupLayout bindGroupLayout = wgpuDeviceCreateBindGroupLayout(device, &bglDesc);

	// pipeline layout (used by the render pipeline, released after its creation)
	WGPUPipelineLayoutDescriptor layoutDesc = {};
	layoutDesc.bindGroupLayoutCount = 1;
	layoutDesc.bindGroupLayouts = &bindGroupLayout;
	WGPUPipelineLayout pipelineLayout = wgpuDeviceCreatePipelineLayout(device, &layoutDesc);
	
	// begin pipeline set-up
	WGPURenderPipelineDescriptor desc = {};

	desc.layout = pipelineLayout;

	desc.vertexStage.module = vertMod;
	desc.vertexStage.entryPoint = "main";

	WGPUProgrammableStageDescriptor fragStage = {};
	fragStage.module = fragMod;
	fragStage.entryPoint = "main";
	desc.fragmentStage = &fragStage;

	// describe buffer layouts
	WGPUVertexAttributeDescriptor vertAttrs[2] = {};
	vertAttrs[0].format = WGPUVertexFormat_Float2;
	vertAttrs[0].offset = 0;
	vertAttrs[0].shaderLocation = 0;
	vertAttrs[1].format = WGPUVertexFormat_Float3;
	vertAttrs[1].offset = 2 * sizeof(float);
	vertAttrs[1].shaderLocation = 1;
	WGPUVertexBufferLayoutDescriptor vertDesc = {};
	vertDesc.arrayStride = 5 * sizeof(float);
	vertDesc.attributeCount = 2;
	vertDesc.attributes = vertAttrs;
	WGPUVertexStateDescriptor vertState = {};
	vertState.indexFormat = WGPUIndexFormat_Uint16;
	vertState.vertexBufferCount = 1;
	vertState.vertexBuffers = &vertDesc;

	desc.vertexState = &vertState;
	desc.primitiveTopology = WGPUPrimitiveTopology_TriangleList;

	desc.sampleCount = 1;

	// describe blend
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

	desc.sampleMask = 0xFFFFFFFF; //<-- Note: this currently causes Emscripten to fail (sampleMask ends up as -1, which trips an assert)

	pipeline = wgpuDeviceCreateRenderPipeline(device, &desc);

	// partial clean-up (just move to the end, no?)
	wgpuPipelineLayoutRelease(pipelineLayout);

	wgpuShaderModuleRelease(fragMod);
	wgpuShaderModuleRelease(vertMod);

	// create the buffers (x, y, r, g, b)
	float const vertData[] = {
		-0.8f, -0.8f, 0.0f, 0.0f, 1.0f, // BL
		 0.8f, -0.8f, 0.0f, 1.0f, 0.0f, // BR
		-0.0f,  0.8f, 1.0f, 0.0f, 0.0f, // top
	};
	uint16_t const indxData[] = {
		0, 1, 2,
		0 // padding (better way of doing this?)
	};
	vertBuf = createBuffer(vertData, sizeof(vertData), WGPUBufferUsage_Vertex);
	indxBuf = createBuffer(indxData, sizeof(indxData), WGPUBufferUsage_Index);

	// create the uniform bind group (note 'rotDeg' is copied here, not bound in any way)
	uRotBuf = createBuffer(&rotDeg, sizeof(rotDeg), WGPUBufferUsage_Uniform);

	WGPUBindGroupEntry bgEntry = {};
	bgEntry.binding = 0;
	bgEntry.buffer = uRotBuf;
	bgEntry.offset = 0;
	bgEntry.size = sizeof(rotDeg);

	WGPUBindGroupDescriptor bgDesc = {};
	bgDesc.layout = bindGroupLayout;
	bgDesc.entryCount = 1;
	bgDesc.entries = &bgEntry;

	bindGroup = wgpuDeviceCreateBindGroup(device, &bgDesc);

	// last bit of clean-up
	wgpuBindGroupLayoutRelease(bindGroupLayout);
}

/**
 * Draws using the above pipeline and buffers.
 */
static bool redraw() {
	WGPUTextureView backBufView = wgpuSwapChainGetCurrentTextureView(swapchain);			// create textureView

	WGPURenderPassColorAttachmentDescriptor colorDesc = {};
	colorDesc.attachment = backBufView;
	colorDesc.loadOp  = WGPULoadOp_Clear;
	colorDesc.storeOp = WGPUStoreOp_Store;
	colorDesc.clearColor.r = 0.3f;
	colorDesc.clearColor.g = 0.3f;
	colorDesc.clearColor.b = 0.3f;
	colorDesc.clearColor.a = 1.0f;

	WGPURenderPassDescriptor renderPass = {};
	renderPass.colorAttachmentCount = 1;
	renderPass.colorAttachments = &colorDesc;

	WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device, nullptr);			// create encoder
	WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(encoder, &renderPass);	// create pass

	// update the rotation
	rotDeg += 0.1f;
	wgpuBufferSetSubData(uRotBuf, 0, sizeof(rotDeg), &rotDeg);

	// draw the triangle (comment these five lines to simply clear the screen)
	wgpuRenderPassEncoderSetPipeline(pass, pipeline);
	wgpuRenderPassEncoderSetBindGroup(pass, 0, bindGroup, 0, 0);
	wgpuRenderPassEncoderSetVertexBuffer(pass, 0, vertBuf, 0, 0);
	wgpuRenderPassEncoderSetIndexBuffer(pass, indxBuf, 0, 0);
	wgpuRenderPassEncoderDrawIndexed(pass, 3, 1, 0, 0, 0);

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

static void helloTriangle(window::Handle wHnd) {
	if ((device = webgpu::create(wHnd))) {
		queue = wgpuDeviceGetDefaultQueue(device);
		swapchain = webgpu::createSwapChain(device);
		createPipelineAndBuffers();

		window::show(wHnd);
		window::loop(wHnd, redraw);

#ifndef __EMSCRIPTEN__
		wgpuBindGroupRelease(bindGroup);
		wgpuBufferRelease(uRotBuf);
		wgpuBufferRelease(indxBuf);
		wgpuBufferRelease(vertBuf);
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

// Refer to https://developers.google.com/web/updates/2019/08/get-started-with-gpu-compute-on-the-web
/*
#version 450

layout(std430, set = 0, binding = 0) readonly buffer FirstMatrix {
  vec2 size;
  float numbers[];
} firstMatrix;

layout(std430, set = 0, binding = 1) readonly buffer SecondMatrix {
  vec2 size;
  float numbers[];
} secondMatrix;

layout(std430, set = 0, binding = 2) buffer ResultMatrix {
  vec2 size;
  float numbers[];
} resultMatrix;

void main() {
  resultMatrix.size = vec2(firstMatrix.size.x, secondMatrix.size.y);

  ivec2 resultCell = ivec2(gl_GlobalInvocationID.x, gl_GlobalInvocationID.y);
  float result = 0.0;
  for (int i = 0; i < firstMatrix.size.y; i++) {
	int a = i + resultCell.x * int(firstMatrix.size.y);
	int b = resultCell.y + i * int(secondMatrix.size.y);
	result += firstMatrix.numbers[a] * secondMatrix.numbers[b];
  }

  int index = resultCell.y + resultCell.x * int(secondMatrix.size.y);
  resultMatrix.numbers[index] = result;
}
*/
const unsigned int matmul_comp[705] = {
	0x07230203,0x00010000,0x00080008,0x0000006a,0x00000000,0x00020011,0x00000001,0x0006000b,
	0x00000001,0x4c534c47,0x6474732e,0x3035342e,0x00000000,0x0003000e,0x00000000,0x00000001,
	0x0006000f,0x00000005,0x00000004,0x6e69616d,0x00000000,0x00000026,0x00060010,0x00000004,
	0x00000011,0x00000001,0x00000001,0x00000001,0x00030003,0x00000002,0x000001c2,0x00040005,
	0x00000004,0x6e69616d,0x00000000,0x00060005,0x00000009,0x75736552,0x614d746c,0x78697274,
	0x00000000,0x00050006,0x00000009,0x00000000,0x657a6973,0x00000000,0x00050006,0x00000009,
	0x00000001,0x626d756e,0x00737265,0x00060005,0x0000000b,0x75736572,0x614d746c,0x78697274,
	0x00000000,0x00050005,0x0000000f,0x73726946,0x74614d74,0x00786972,0x00050006,0x0000000f,
	0x00000000,0x657a6973,0x00000000,0x00050006,0x0000000f,0x00000001,0x626d756e,0x00737265,
	0x00050005,0x00000011,0x73726966,0x74614d74,0x00786972,0x00060005,0x00000018,0x6f636553,
	0x614d646e,0x78697274,0x00000000,0x00050006,0x00000018,0x00000000,0x657a6973,0x00000000,
	0x00050006,0x00000018,0x00000001,0x626d756e,0x00737265,0x00060005,0x0000001a,0x6f636573,
	0x614d646e,0x78697274,0x00000000,0x00050005,0x00000023,0x75736572,0x6543746c,0x00006c6c,
	0x00080005,0x00000026,0x475f6c67,0x61626f6c,0x766e496c,0x7461636f,0x496e6f69,0x00000044,
	0x00040005,0x00000030,0x75736572,0x0000746c,0x00030005,0x00000033,0x00000069,0x00030005,
	0x0000003f,0x00000061,0x00030005,0x00000048,0x00000062,0x00040005,0x0000005d,0x65646e69,
	0x00000078,0x00040047,0x00000008,0x00000006,0x00000004,0x00050048,0x00000009,0x00000000,
	0x00000023,0x00000000,0x00050048,0x00000009,0x00000001,0x00000023,0x00000008,0x00030047,
	0x00000009,0x00000003,0x00040047,0x0000000b,0x00000022,0x00000000,0x00040047,0x0000000b,
	0x00000021,0x00000002,0x00040047,0x0000000e,0x00000006,0x00000004,0x00040048,0x0000000f,
	0x00000000,0x00000018,0x00050048,0x0000000f,0x00000000,0x00000023,0x00000000,0x00040048,
	0x0000000f,0x00000001,0x00000018,0x00050048,0x0000000f,0x00000001,0x00000023,0x00000008,
	0x00030047,0x0000000f,0x00000003,0x00040047,0x00000011,0x00000022,0x00000000,0x00040047,
	0x00000011,0x00000021,0x00000000,0x00040047,0x00000017,0x00000006,0x00000004,0x00040048,
	0x00000018,0x00000000,0x00000018,0x00050048,0x00000018,0x00000000,0x00000023,0x00000000,
	0x00040048,0x00000018,0x00000001,0x00000018,0x00050048,0x00000018,0x00000001,0x00000023,
	0x00000008,0x00030047,0x00000018,0x00000003,0x00040047,0x0000001a,0x00000022,0x00000000,
	0x00040047,0x0000001a,0x00000021,0x00000001,0x00040047,0x00000026,0x0000000b,0x0000001c,
	0x00020013,0x00000002,0x00030021,0x00000003,0x00000002,0x00030016,0x00000006,0x00000020,
	0x00040017,0x00000007,0x00000006,0x00000002,0x0003001d,0x00000008,0x00000006,0x0004001e,
	0x00000009,0x00000007,0x00000008,0x00040020,0x0000000a,0x00000002,0x00000009,0x0004003b,
	0x0000000a,0x0000000b,0x00000002,0x00040015,0x0000000c,0x00000020,0x00000001,0x0004002b,
	0x0000000c,0x0000000d,0x00000000,0x0003001d,0x0000000e,0x00000006,0x0004001e,0x0000000f,
	0x00000007,0x0000000e,0x00040020,0x00000010,0x00000002,0x0000000f,0x0004003b,0x00000010,
	0x00000011,0x00000002,0x00040015,0x00000012,0x00000020,0x00000000,0x0004002b,0x00000012,
	0x00000013,0x00000000,0x00040020,0x00000014,0x00000002,0x00000006,0x0003001d,0x00000017,
	0x00000006,0x0004001e,0x00000018,0x00000007,0x00000017,0x00040020,0x00000019,0x00000002,
	0x00000018,0x0004003b,0x00000019,0x0000001a,0x00000002,0x0004002b,0x00000012,0x0000001b,
	0x00000001,0x00040020,0x0000001f,0x00000002,0x00000007,0x00040017,0x00000021,0x0000000c,
	0x00000002,0x00040020,0x00000022,0x00000007,0x00000021,0x00040017,0x00000024,0x00000012,
	0x00000003,0x00040020,0x00000025,0x00000001,0x00000024,0x0004003b,0x00000025,0x00000026,
	0x00000001,0x00040020,0x00000027,0x00000001,0x00000012,0x00040020,0x0000002f,0x00000007,
	0x00000006,0x0004002b,0x00000006,0x00000031,0x00000000,0x00040020,0x00000032,0x00000007,
	0x0000000c,0x00020014,0x0000003d,0x0004002b,0x0000000c,0x00000051,0x00000001,0x00050036,
	0x00000002,0x00000004,0x00000000,0x00000003,0x000200f8,0x00000005,0x0004003b,0x00000022,
	0x00000023,0x00000007,0x0004003b,0x0000002f,0x00000030,0x00000007,0x0004003b,0x00000032,
	0x00000033,0x00000007,0x0004003b,0x00000032,0x0000003f,0x00000007,0x0004003b,0x00000032,
	0x00000048,0x00000007,0x0004003b,0x00000032,0x0000005d,0x00000007,0x00060041,0x00000014,
	0x00000015,0x00000011,0x0000000d,0x00000013,0x0004003d,0x00000006,0x00000016,0x00000015,
	0x00060041,0x00000014,0x0000001c,0x0000001a,0x0000000d,0x0000001b,0x0004003d,0x00000006,
	0x0000001d,0x0000001c,0x00050050,0x00000007,0x0000001e,0x00000016,0x0000001d,0x00050041,
	0x0000001f,0x00000020,0x0000000b,0x0000000d,0x0003003e,0x00000020,0x0000001e,0x00050041,
	0x00000027,0x00000028,0x00000026,0x00000013,0x0004003d,0x00000012,0x00000029,0x00000028,
	0x0004007c,0x0000000c,0x0000002a,0x00000029,0x00050041,0x00000027,0x0000002b,0x00000026,
	0x0000001b,0x0004003d,0x00000012,0x0000002c,0x0000002b,0x0004007c,0x0000000c,0x0000002d,
	0x0000002c,0x00050050,0x00000021,0x0000002e,0x0000002a,0x0000002d,0x0003003e,0x00000023,
	0x0000002e,0x0003003e,0x00000030,0x00000031,0x0003003e,0x00000033,0x0000000d,0x000200f9,
	0x00000034,0x000200f8,0x00000034,0x000400f6,0x00000036,0x00000037,0x00000000,0x000200f9,
	0x00000038,0x000200f8,0x00000038,0x0004003d,0x0000000c,0x00000039,0x00000033,0x0004006f,
	0x00000006,0x0000003a,0x00000039,0x00060041,0x00000014,0x0000003b,0x00000011,0x0000000d,
	0x0000001b,0x0004003d,0x00000006,0x0000003c,0x0000003b,0x000500b8,0x0000003d,0x0000003e,
	0x0000003a,0x0000003c,0x000400fa,0x0000003e,0x00000035,0x00000036,0x000200f8,0x00000035,
	0x0004003d,0x0000000c,0x00000040,0x00000033,0x00050041,0x00000032,0x00000041,0x00000023,
	0x00000013,0x0004003d,0x0000000c,0x00000042,0x00000041,0x00060041,0x00000014,0x00000043,
	0x00000011,0x0000000d,0x0000001b,0x0004003d,0x00000006,0x00000044,0x00000043,0x0004006e,
	0x0000000c,0x00000045,0x00000044,0x00050084,0x0000000c,0x00000046,0x00000042,0x00000045,
	0x00050080,0x0000000c,0x00000047,0x00000040,0x00000046,0x0003003e,0x0000003f,0x00000047,
	0x00050041,0x00000032,0x00000049,0x00000023,0x0000001b,0x0004003d,0x0000000c,0x0000004a,
	0x00000049,0x0004003d,0x0000000c,0x0000004b,0x00000033,0x00060041,0x00000014,0x0000004c,
	0x0000001a,0x0000000d,0x0000001b,0x0004003d,0x00000006,0x0000004d,0x0000004c,0x0004006e,
	0x0000000c,0x0000004e,0x0000004d,0x00050084,0x0000000c,0x0000004f,0x0000004b,0x0000004e,
	0x00050080,0x0000000c,0x00000050,0x0000004a,0x0000004f,0x0003003e,0x00000048,0x00000050,
	0x0004003d,0x0000000c,0x00000052,0x0000003f,0x00060041,0x00000014,0x00000053,0x00000011,
	0x00000051,0x00000052,0x0004003d,0x00000006,0x00000054,0x00000053,0x0004003d,0x0000000c,
	0x00000055,0x00000048,0x00060041,0x00000014,0x00000056,0x0000001a,0x00000051,0x00000055,
	0x0004003d,0x00000006,0x00000057,0x00000056,0x00050085,0x00000006,0x00000058,0x00000054,
	0x00000057,0x0004003d,0x00000006,0x00000059,0x00000030,0x00050081,0x00000006,0x0000005a,
	0x00000059,0x00000058,0x0003003e,0x00000030,0x0000005a,0x000200f9,0x00000037,0x000200f8,
	0x00000037,0x0004003d,0x0000000c,0x0000005b,0x00000033,0x00050080,0x0000000c,0x0000005c,
	0x0000005b,0x00000051,0x0003003e,0x00000033,0x0000005c,0x000200f9,0x00000034,0x000200f8,
	0x00000036,0x00050041,0x00000032,0x0000005e,0x00000023,0x0000001b,0x0004003d,0x0000000c,
	0x0000005f,0x0000005e,0x00050041,0x00000032,0x00000060,0x00000023,0x00000013,0x0004003d,
	0x0000000c,0x00000061,0x00000060,0x00060041,0x00000014,0x00000062,0x0000001a,0x0000000d,
	0x0000001b,0x0004003d,0x00000006,0x00000063,0x00000062,0x0004006e,0x0000000c,0x00000064,
	0x00000063,0x00050084,0x0000000c,0x00000065,0x00000061,0x00000064,0x00050080,0x0000000c,
	0x00000066,0x0000005f,0x00000065,0x0003003e,0x0000005d,0x00000066,0x0004003d,0x0000000c,
	0x00000067,0x0000005d,0x0004003d,0x00000006,0x00000068,0x00000030,0x00060041,0x00000014,
	0x00000069,0x0000000b,0x00000051,0x00000067,0x0003003e,0x00000069,0x00000068,0x000100fd,
	0x00010038
};

float const firstMatrix[] = {
	2 /* rows */, 4 /* columns */,
	1, 2, 3, 4, 5, 6, 7, 8
};

float const secondMatrix[] = {
	4 /* rows */, 2 /* columns */,
	1, 2, 3, 4, 5, 6, 7, 8
};

WGPUComputePipeline computePipeline;
size_t resultMatrixBufferSize;
WGPUBuffer gpuBufferFirstMatrix;
WGPUBuffer gpuBufferSecondMatrix;
WGPUBuffer resultMatrixBuffer;
WGPUBuffer gpuReadBuffer;

void gpuReadBufferMapReadCallback(WGPUBufferMapAsyncStatus status,
	const void* ptr,
	uint64_t dataLength,
	void* userdata) {
	(void)status;
	(void)userdata;
	printf("resultMatrix: [");
	size_t num = dataLength / sizeof(float);
	for (size_t i = 0; i < num; ++i) {
		printf("%f", ((const float*)ptr)[i]);
		if (i != num - 1)
			printf(", ");
	}
	printf("]\n");
}

static bool compute() {
	WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device, nullptr);			// create encoder
	WGPUComputePassDescriptor computePass = {};
	WGPUComputePassEncoder pass = wgpuCommandEncoderBeginComputePass(encoder, &computePass);	// create pass

	wgpuComputePassEncoderSetPipeline(pass, computePipeline);
	wgpuComputePassEncoderSetBindGroup(pass, 0, bindGroup, 0, 0);
	wgpuComputePassEncoderDispatch(pass, uint32_t(firstMatrix[0]), uint32_t(secondMatrix[1]), 1);
	wgpuComputePassEncoderEndPass(pass);

	wgpuCommandEncoderCopyBufferToBuffer(encoder, resultMatrixBuffer, 0, gpuReadBuffer, 0, resultMatrixBufferSize);

	WGPUCommandBuffer commands = wgpuCommandEncoderFinish(encoder, nullptr);				// create commands
	wgpuQueueSubmit(queue, 1, &commands);

	wgpuBufferMapReadAsync(gpuReadBuffer, gpuReadBufferMapReadCallback, NULL);

	wgpuComputePassEncoderRelease(pass);														// release pass
	wgpuCommandEncoderRelease(encoder);														// release encoder

	return false;
}

static void createComputePipelineAndBuffers() {
	// bind group layout (used by both the pipeline layout and uniform bind group, released at the end of this function)
	WGPUBindGroupLayoutEntry bindings[3] = {
		{0, WGPUShaderStage_Compute, WGPUBindingType_ReadonlyStorageBuffer},
		{1, WGPUShaderStage_Compute, WGPUBindingType_ReadonlyStorageBuffer},
		{2, WGPUShaderStage_Compute, WGPUBindingType_StorageBuffer},
	};

	WGPUBindGroupLayoutDescriptor bglDesc = {};
	bglDesc.entryCount = 3;
	bglDesc.entries = bindings;
	WGPUBindGroupLayout bindGroupLayout = wgpuDeviceCreateBindGroupLayout(device, &bglDesc);

	WGPUBufferDescriptor firstMatrixDesc = {};
	firstMatrixDesc.usage = WGPUBufferUsage_Storage | WGPUBufferUsage_CopyDst;
	firstMatrixDesc.size = sizeof(firstMatrix);
	gpuBufferFirstMatrix = wgpuDeviceCreateBuffer(device, &firstMatrixDesc);
	wgpuBufferSetSubData(gpuBufferFirstMatrix, 0, sizeof(firstMatrix), firstMatrix);

	WGPUBufferDescriptor secondMatrixDesc = {};
	secondMatrixDesc.usage = WGPUBufferUsage_Storage | WGPUBufferUsage_CopyDst;
	secondMatrixDesc.size = sizeof(secondMatrix);
	gpuBufferSecondMatrix = wgpuDeviceCreateBuffer(device, &secondMatrixDesc);
	wgpuBufferSetSubData(gpuBufferSecondMatrix, 0, sizeof(secondMatrix), secondMatrix);

	resultMatrixBufferSize = sizeof(float) * (2 + uint64_t(firstMatrix[0]) * uint64_t(secondMatrix[1]));
	WGPUBufferDescriptor resultMatrixDesc = {};
	resultMatrixDesc.usage = WGPUBufferUsage_Storage | WGPUBufferUsage_CopySrc;
	resultMatrixDesc.size = resultMatrixBufferSize;
	resultMatrixBuffer = wgpuDeviceCreateBuffer(device, &resultMatrixDesc);

	WGPUBufferDescriptor readBufferDesc = {};
	readBufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_MapRead;
	readBufferDesc.size = resultMatrixBufferSize;
	gpuReadBuffer = wgpuDeviceCreateBuffer(device, &readBufferDesc);

	WGPUBindGroupEntry bgEntries[3] = {
		{0, gpuBufferFirstMatrix, 0, sizeof(firstMatrix)},
		{1, gpuBufferSecondMatrix, 0, sizeof(secondMatrix)},
		{2, resultMatrixBuffer, 0, resultMatrixBufferSize}
	};

	WGPUBindGroupDescriptor bgDesc = {};
	bgDesc.layout = bindGroupLayout;
	bgDesc.entryCount = 3;
	bgDesc.entries = bgEntries;

	bindGroup = wgpuDeviceCreateBindGroup(device, &bgDesc);

	// compile shader
	WGPUShaderModule compMod = createShader(matmul_comp, sizeof(matmul_comp));

	// pipeline layout (used by the compute pipeline, released after its creation)
	WGPUPipelineLayoutDescriptor layoutDesc = {};
	layoutDesc.bindGroupLayoutCount = 1;
	layoutDesc.bindGroupLayouts = &bindGroupLayout;
	WGPUPipelineLayout pipelineLayout = wgpuDeviceCreatePipelineLayout(device, &layoutDesc);

	// begin pipeline set-up
	WGPUComputePipelineDescriptor desc = {};

	desc.layout = pipelineLayout;

	desc.computeStage.module = compMod;
	desc.computeStage.entryPoint = "main";

	computePipeline = wgpuDeviceCreateComputePipeline(device, &desc);

	// partial clean-up (just move to the end, no?)
	wgpuPipelineLayoutRelease(pipelineLayout);

	wgpuShaderModuleRelease(compMod);

	// last bit of clean-up
	wgpuBindGroupLayoutRelease(bindGroupLayout);
}

static void helloCompute(window::Handle wHnd) {
	if ((device = webgpu::create(wHnd))) {
		queue = wgpuDeviceGetDefaultQueue(device);
		createComputePipelineAndBuffers();
		window::show(wHnd);
		window::loop(wHnd, compute);
#ifndef __EMSCRIPTEN__
		wgpuBindGroupRelease(bindGroup);
		wgpuBufferRelease(gpuBufferFirstMatrix);
		wgpuBufferRelease(gpuBufferSecondMatrix);
		wgpuBufferRelease(resultMatrixBuffer);
		wgpuBufferRelease(gpuReadBuffer);
		wgpuComputePipelineRelease(computePipeline);
		wgpuQueueRelease(queue);
		wgpuDeviceRelease(device);
#endif
	}
#ifndef __EMSCRIPTEN__
	window::destroy(wHnd);
#endif
}

extern "C" int __main__(int /*argc*/, char* /*argv*/[]) {
	if (window::Handle wHnd = window::create()) {
#ifndef HELLO_COMPUTE
		helloTriangle(wHnd);
#else
		helloCompute(wHnd);
#endif
	}
	return 0;
}
