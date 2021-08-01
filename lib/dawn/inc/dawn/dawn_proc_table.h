
#ifndef DAWN_DAWN_PROC_TABLE_H_
#define DAWN_DAWN_PROC_TABLE_H_

#include "dawn/webgpu.h"

// Note: Often allocated as a static global. Do not add a complex constructor.
typedef struct DawnProcTable {
    WGPUProcGetProcAddress getProcAddress;
    WGPUProcCreateInstance createInstance;

    WGPUProcBindGroupReference bindGroupReference;
    WGPUProcBindGroupRelease bindGroupRelease;

    WGPUProcBindGroupLayoutReference bindGroupLayoutReference;
    WGPUProcBindGroupLayoutRelease bindGroupLayoutRelease;

    WGPUProcBufferDestroy bufferDestroy;
    WGPUProcBufferGetConstMappedRange bufferGetConstMappedRange;
    WGPUProcBufferGetMappedRange bufferGetMappedRange;
    WGPUProcBufferMapAsync bufferMapAsync;
    WGPUProcBufferUnmap bufferUnmap;
    WGPUProcBufferReference bufferReference;
    WGPUProcBufferRelease bufferRelease;

    WGPUProcCommandBufferReference commandBufferReference;
    WGPUProcCommandBufferRelease commandBufferRelease;

    WGPUProcCommandEncoderBeginComputePass commandEncoderBeginComputePass;
    WGPUProcCommandEncoderBeginRenderPass commandEncoderBeginRenderPass;
    WGPUProcCommandEncoderCopyBufferToBuffer commandEncoderCopyBufferToBuffer;
    WGPUProcCommandEncoderCopyBufferToTexture commandEncoderCopyBufferToTexture;
    WGPUProcCommandEncoderCopyTextureToBuffer commandEncoderCopyTextureToBuffer;
    WGPUProcCommandEncoderCopyTextureToTexture commandEncoderCopyTextureToTexture;
    WGPUProcCommandEncoderFinish commandEncoderFinish;
    WGPUProcCommandEncoderInjectValidationError commandEncoderInjectValidationError;
    WGPUProcCommandEncoderInsertDebugMarker commandEncoderInsertDebugMarker;
    WGPUProcCommandEncoderPopDebugGroup commandEncoderPopDebugGroup;
    WGPUProcCommandEncoderPushDebugGroup commandEncoderPushDebugGroup;
    WGPUProcCommandEncoderResolveQuerySet commandEncoderResolveQuerySet;
    WGPUProcCommandEncoderWriteTimestamp commandEncoderWriteTimestamp;
    WGPUProcCommandEncoderReference commandEncoderReference;
    WGPUProcCommandEncoderRelease commandEncoderRelease;

    WGPUProcComputePassEncoderDispatch computePassEncoderDispatch;
    WGPUProcComputePassEncoderDispatchIndirect computePassEncoderDispatchIndirect;
    WGPUProcComputePassEncoderEndPass computePassEncoderEndPass;
    WGPUProcComputePassEncoderInsertDebugMarker computePassEncoderInsertDebugMarker;
    WGPUProcComputePassEncoderPopDebugGroup computePassEncoderPopDebugGroup;
    WGPUProcComputePassEncoderPushDebugGroup computePassEncoderPushDebugGroup;
    WGPUProcComputePassEncoderSetBindGroup computePassEncoderSetBindGroup;
    WGPUProcComputePassEncoderSetPipeline computePassEncoderSetPipeline;
    WGPUProcComputePassEncoderWriteTimestamp computePassEncoderWriteTimestamp;
    WGPUProcComputePassEncoderReference computePassEncoderReference;
    WGPUProcComputePassEncoderRelease computePassEncoderRelease;

    WGPUProcComputePipelineGetBindGroupLayout computePipelineGetBindGroupLayout;
    WGPUProcComputePipelineReference computePipelineReference;
    WGPUProcComputePipelineRelease computePipelineRelease;

    WGPUProcDeviceCreateBindGroup deviceCreateBindGroup;
    WGPUProcDeviceCreateBindGroupLayout deviceCreateBindGroupLayout;
    WGPUProcDeviceCreateBuffer deviceCreateBuffer;
    WGPUProcDeviceCreateCommandEncoder deviceCreateCommandEncoder;
    WGPUProcDeviceCreateComputePipeline deviceCreateComputePipeline;
    WGPUProcDeviceCreateComputePipelineAsync deviceCreateComputePipelineAsync;
    WGPUProcDeviceCreateErrorBuffer deviceCreateErrorBuffer;
    WGPUProcDeviceCreateExternalTexture deviceCreateExternalTexture;
    WGPUProcDeviceCreatePipelineLayout deviceCreatePipelineLayout;
    WGPUProcDeviceCreateQuerySet deviceCreateQuerySet;
    WGPUProcDeviceCreateRenderBundleEncoder deviceCreateRenderBundleEncoder;
    WGPUProcDeviceCreateRenderPipeline deviceCreateRenderPipeline;
    WGPUProcDeviceCreateRenderPipeline2 deviceCreateRenderPipeline2;
    WGPUProcDeviceCreateRenderPipelineAsync deviceCreateRenderPipelineAsync;
    WGPUProcDeviceCreateSampler deviceCreateSampler;
    WGPUProcDeviceCreateShaderModule deviceCreateShaderModule;
    WGPUProcDeviceCreateSwapChain deviceCreateSwapChain;
    WGPUProcDeviceCreateTexture deviceCreateTexture;
    WGPUProcDeviceGetQueue deviceGetQueue;
    WGPUProcDeviceInjectError deviceInjectError;
    WGPUProcDeviceLoseForTesting deviceLoseForTesting;
    WGPUProcDevicePopErrorScope devicePopErrorScope;
    WGPUProcDevicePushErrorScope devicePushErrorScope;
    WGPUProcDeviceSetDeviceLostCallback deviceSetDeviceLostCallback;
    WGPUProcDeviceSetLoggingCallback deviceSetLoggingCallback;
    WGPUProcDeviceSetUncapturedErrorCallback deviceSetUncapturedErrorCallback;
    WGPUProcDeviceTick deviceTick;
    WGPUProcDeviceReference deviceReference;
    WGPUProcDeviceRelease deviceRelease;

    WGPUProcExternalTextureDestroy externalTextureDestroy;
    WGPUProcExternalTextureReference externalTextureReference;
    WGPUProcExternalTextureRelease externalTextureRelease;

    WGPUProcInstanceCreateSurface instanceCreateSurface;
    WGPUProcInstanceReference instanceReference;
    WGPUProcInstanceRelease instanceRelease;

    WGPUProcPipelineLayoutReference pipelineLayoutReference;
    WGPUProcPipelineLayoutRelease pipelineLayoutRelease;

    WGPUProcQuerySetDestroy querySetDestroy;
    WGPUProcQuerySetReference querySetReference;
    WGPUProcQuerySetRelease querySetRelease;

    WGPUProcQueueCopyTextureForBrowser queueCopyTextureForBrowser;
    WGPUProcQueueOnSubmittedWorkDone queueOnSubmittedWorkDone;
    WGPUProcQueueSubmit queueSubmit;
    WGPUProcQueueWriteBuffer queueWriteBuffer;
    WGPUProcQueueWriteTexture queueWriteTexture;
    WGPUProcQueueReference queueReference;
    WGPUProcQueueRelease queueRelease;

    WGPUProcRenderBundleReference renderBundleReference;
    WGPUProcRenderBundleRelease renderBundleRelease;

    WGPUProcRenderBundleEncoderDraw renderBundleEncoderDraw;
    WGPUProcRenderBundleEncoderDrawIndexed renderBundleEncoderDrawIndexed;
    WGPUProcRenderBundleEncoderDrawIndexedIndirect renderBundleEncoderDrawIndexedIndirect;
    WGPUProcRenderBundleEncoderDrawIndirect renderBundleEncoderDrawIndirect;
    WGPUProcRenderBundleEncoderFinish renderBundleEncoderFinish;
    WGPUProcRenderBundleEncoderInsertDebugMarker renderBundleEncoderInsertDebugMarker;
    WGPUProcRenderBundleEncoderPopDebugGroup renderBundleEncoderPopDebugGroup;
    WGPUProcRenderBundleEncoderPushDebugGroup renderBundleEncoderPushDebugGroup;
    WGPUProcRenderBundleEncoderSetBindGroup renderBundleEncoderSetBindGroup;
    WGPUProcRenderBundleEncoderSetIndexBuffer renderBundleEncoderSetIndexBuffer;
    WGPUProcRenderBundleEncoderSetPipeline renderBundleEncoderSetPipeline;
    WGPUProcRenderBundleEncoderSetVertexBuffer renderBundleEncoderSetVertexBuffer;
    WGPUProcRenderBundleEncoderReference renderBundleEncoderReference;
    WGPUProcRenderBundleEncoderRelease renderBundleEncoderRelease;

    WGPUProcRenderPassEncoderBeginOcclusionQuery renderPassEncoderBeginOcclusionQuery;
    WGPUProcRenderPassEncoderDraw renderPassEncoderDraw;
    WGPUProcRenderPassEncoderDrawIndexed renderPassEncoderDrawIndexed;
    WGPUProcRenderPassEncoderDrawIndexedIndirect renderPassEncoderDrawIndexedIndirect;
    WGPUProcRenderPassEncoderDrawIndirect renderPassEncoderDrawIndirect;
    WGPUProcRenderPassEncoderEndOcclusionQuery renderPassEncoderEndOcclusionQuery;
    WGPUProcRenderPassEncoderEndPass renderPassEncoderEndPass;
    WGPUProcRenderPassEncoderExecuteBundles renderPassEncoderExecuteBundles;
    WGPUProcRenderPassEncoderInsertDebugMarker renderPassEncoderInsertDebugMarker;
    WGPUProcRenderPassEncoderPopDebugGroup renderPassEncoderPopDebugGroup;
    WGPUProcRenderPassEncoderPushDebugGroup renderPassEncoderPushDebugGroup;
    WGPUProcRenderPassEncoderSetBindGroup renderPassEncoderSetBindGroup;
    WGPUProcRenderPassEncoderSetBlendColor renderPassEncoderSetBlendColor;
    WGPUProcRenderPassEncoderSetBlendConstant renderPassEncoderSetBlendConstant;
    WGPUProcRenderPassEncoderSetIndexBuffer renderPassEncoderSetIndexBuffer;
    WGPUProcRenderPassEncoderSetPipeline renderPassEncoderSetPipeline;
    WGPUProcRenderPassEncoderSetScissorRect renderPassEncoderSetScissorRect;
    WGPUProcRenderPassEncoderSetStencilReference renderPassEncoderSetStencilReference;
    WGPUProcRenderPassEncoderSetVertexBuffer renderPassEncoderSetVertexBuffer;
    WGPUProcRenderPassEncoderSetViewport renderPassEncoderSetViewport;
    WGPUProcRenderPassEncoderWriteTimestamp renderPassEncoderWriteTimestamp;
    WGPUProcRenderPassEncoderReference renderPassEncoderReference;
    WGPUProcRenderPassEncoderRelease renderPassEncoderRelease;

    WGPUProcRenderPipelineGetBindGroupLayout renderPipelineGetBindGroupLayout;
    WGPUProcRenderPipelineReference renderPipelineReference;
    WGPUProcRenderPipelineRelease renderPipelineRelease;

    WGPUProcSamplerReference samplerReference;
    WGPUProcSamplerRelease samplerRelease;

    WGPUProcShaderModuleGetCompilationInfo shaderModuleGetCompilationInfo;
    WGPUProcShaderModuleReference shaderModuleReference;
    WGPUProcShaderModuleRelease shaderModuleRelease;

    WGPUProcSurfaceReference surfaceReference;
    WGPUProcSurfaceRelease surfaceRelease;

    WGPUProcSwapChainConfigure swapChainConfigure;
    WGPUProcSwapChainGetCurrentTextureView swapChainGetCurrentTextureView;
    WGPUProcSwapChainPresent swapChainPresent;
    WGPUProcSwapChainReference swapChainReference;
    WGPUProcSwapChainRelease swapChainRelease;

    WGPUProcTextureCreateView textureCreateView;
    WGPUProcTextureDestroy textureDestroy;
    WGPUProcTextureReference textureReference;
    WGPUProcTextureRelease textureRelease;

    WGPUProcTextureViewReference textureViewReference;
    WGPUProcTextureViewRelease textureViewRelease;

} DawnProcTable;

#endif  // DAWN_DAWN_PROC_TABLE_H_
