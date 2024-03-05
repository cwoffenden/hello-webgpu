
#ifndef DAWN_DAWN_PROC_TABLE_H_
#define DAWN_DAWN_PROC_TABLE_H_

#include "dawn/webgpu.h"

// Note: Often allocated as a static global. Do not add a complex constructor.
typedef struct DawnProcTable {
    WGPUProcAdapterPropertiesFreeMembers adapterPropertiesFreeMembers;
    WGPUProcAdapterPropertiesMemoryHeapsFreeMembers adapterPropertiesMemoryHeapsFreeMembers;
    WGPUProcCreateInstance createInstance;
    WGPUProcGetInstanceFeatures getInstanceFeatures;
    WGPUProcGetProcAddress getProcAddress;
    WGPUProcSharedBufferMemoryEndAccessStateFreeMembers sharedBufferMemoryEndAccessStateFreeMembers;
    WGPUProcSharedTextureMemoryEndAccessStateFreeMembers sharedTextureMemoryEndAccessStateFreeMembers;

    WGPUProcAdapterCreateDevice adapterCreateDevice;
    WGPUProcAdapterEnumerateFeatures adapterEnumerateFeatures;
    WGPUProcAdapterGetInstance adapterGetInstance;
    WGPUProcAdapterGetLimits adapterGetLimits;
    WGPUProcAdapterGetProperties adapterGetProperties;
    WGPUProcAdapterHasFeature adapterHasFeature;
    WGPUProcAdapterRequestDevice adapterRequestDevice;
    WGPUProcAdapterRequestDeviceF adapterRequestDeviceF;
    WGPUProcAdapterReference adapterReference;
    WGPUProcAdapterRelease adapterRelease;

    WGPUProcBindGroupSetLabel bindGroupSetLabel;
    WGPUProcBindGroupReference bindGroupReference;
    WGPUProcBindGroupRelease bindGroupRelease;

    WGPUProcBindGroupLayoutSetLabel bindGroupLayoutSetLabel;
    WGPUProcBindGroupLayoutReference bindGroupLayoutReference;
    WGPUProcBindGroupLayoutRelease bindGroupLayoutRelease;

    WGPUProcBufferDestroy bufferDestroy;
    WGPUProcBufferGetConstMappedRange bufferGetConstMappedRange;
    WGPUProcBufferGetMapState bufferGetMapState;
    WGPUProcBufferGetMappedRange bufferGetMappedRange;
    WGPUProcBufferGetSize bufferGetSize;
    WGPUProcBufferGetUsage bufferGetUsage;
    WGPUProcBufferMapAsync bufferMapAsync;
    WGPUProcBufferMapAsyncF bufferMapAsyncF;
    WGPUProcBufferSetLabel bufferSetLabel;
    WGPUProcBufferUnmap bufferUnmap;
    WGPUProcBufferReference bufferReference;
    WGPUProcBufferRelease bufferRelease;

    WGPUProcCommandBufferSetLabel commandBufferSetLabel;
    WGPUProcCommandBufferReference commandBufferReference;
    WGPUProcCommandBufferRelease commandBufferRelease;

    WGPUProcCommandEncoderBeginComputePass commandEncoderBeginComputePass;
    WGPUProcCommandEncoderBeginRenderPass commandEncoderBeginRenderPass;
    WGPUProcCommandEncoderClearBuffer commandEncoderClearBuffer;
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
    WGPUProcCommandEncoderSetLabel commandEncoderSetLabel;
    WGPUProcCommandEncoderWriteBuffer commandEncoderWriteBuffer;
    WGPUProcCommandEncoderWriteTimestamp commandEncoderWriteTimestamp;
    WGPUProcCommandEncoderReference commandEncoderReference;
    WGPUProcCommandEncoderRelease commandEncoderRelease;

    WGPUProcComputePassEncoderDispatchWorkgroups computePassEncoderDispatchWorkgroups;
    WGPUProcComputePassEncoderDispatchWorkgroupsIndirect computePassEncoderDispatchWorkgroupsIndirect;
    WGPUProcComputePassEncoderEnd computePassEncoderEnd;
    WGPUProcComputePassEncoderInsertDebugMarker computePassEncoderInsertDebugMarker;
    WGPUProcComputePassEncoderPopDebugGroup computePassEncoderPopDebugGroup;
    WGPUProcComputePassEncoderPushDebugGroup computePassEncoderPushDebugGroup;
    WGPUProcComputePassEncoderSetBindGroup computePassEncoderSetBindGroup;
    WGPUProcComputePassEncoderSetLabel computePassEncoderSetLabel;
    WGPUProcComputePassEncoderSetPipeline computePassEncoderSetPipeline;
    WGPUProcComputePassEncoderWriteTimestamp computePassEncoderWriteTimestamp;
    WGPUProcComputePassEncoderReference computePassEncoderReference;
    WGPUProcComputePassEncoderRelease computePassEncoderRelease;

    WGPUProcComputePipelineGetBindGroupLayout computePipelineGetBindGroupLayout;
    WGPUProcComputePipelineSetLabel computePipelineSetLabel;
    WGPUProcComputePipelineReference computePipelineReference;
    WGPUProcComputePipelineRelease computePipelineRelease;

    WGPUProcDeviceCreateBindGroup deviceCreateBindGroup;
    WGPUProcDeviceCreateBindGroupLayout deviceCreateBindGroupLayout;
    WGPUProcDeviceCreateBuffer deviceCreateBuffer;
    WGPUProcDeviceCreateCommandEncoder deviceCreateCommandEncoder;
    WGPUProcDeviceCreateComputePipeline deviceCreateComputePipeline;
    WGPUProcDeviceCreateComputePipelineAsync deviceCreateComputePipelineAsync;
    WGPUProcDeviceCreateComputePipelineAsyncF deviceCreateComputePipelineAsyncF;
    WGPUProcDeviceCreateErrorBuffer deviceCreateErrorBuffer;
    WGPUProcDeviceCreateErrorExternalTexture deviceCreateErrorExternalTexture;
    WGPUProcDeviceCreateErrorShaderModule deviceCreateErrorShaderModule;
    WGPUProcDeviceCreateErrorTexture deviceCreateErrorTexture;
    WGPUProcDeviceCreateExternalTexture deviceCreateExternalTexture;
    WGPUProcDeviceCreatePipelineLayout deviceCreatePipelineLayout;
    WGPUProcDeviceCreateQuerySet deviceCreateQuerySet;
    WGPUProcDeviceCreateRenderBundleEncoder deviceCreateRenderBundleEncoder;
    WGPUProcDeviceCreateRenderPipeline deviceCreateRenderPipeline;
    WGPUProcDeviceCreateRenderPipelineAsync deviceCreateRenderPipelineAsync;
    WGPUProcDeviceCreateRenderPipelineAsyncF deviceCreateRenderPipelineAsyncF;
    WGPUProcDeviceCreateSampler deviceCreateSampler;
    WGPUProcDeviceCreateShaderModule deviceCreateShaderModule;
    WGPUProcDeviceCreateSwapChain deviceCreateSwapChain;
    WGPUProcDeviceCreateTexture deviceCreateTexture;
    WGPUProcDeviceDestroy deviceDestroy;
    WGPUProcDeviceEnumerateFeatures deviceEnumerateFeatures;
    WGPUProcDeviceForceLoss deviceForceLoss;
    WGPUProcDeviceGetAdapter deviceGetAdapter;
    WGPUProcDeviceGetLimits deviceGetLimits;
    WGPUProcDeviceGetQueue deviceGetQueue;
    WGPUProcDeviceGetSupportedSurfaceUsage deviceGetSupportedSurfaceUsage;
    WGPUProcDeviceHasFeature deviceHasFeature;
    WGPUProcDeviceImportSharedBufferMemory deviceImportSharedBufferMemory;
    WGPUProcDeviceImportSharedFence deviceImportSharedFence;
    WGPUProcDeviceImportSharedTextureMemory deviceImportSharedTextureMemory;
    WGPUProcDeviceInjectError deviceInjectError;
    WGPUProcDevicePopErrorScope devicePopErrorScope;
    WGPUProcDevicePopErrorScopeF devicePopErrorScopeF;
    WGPUProcDevicePushErrorScope devicePushErrorScope;
    WGPUProcDeviceSetDeviceLostCallback deviceSetDeviceLostCallback;
    WGPUProcDeviceSetLabel deviceSetLabel;
    WGPUProcDeviceSetLoggingCallback deviceSetLoggingCallback;
    WGPUProcDeviceSetUncapturedErrorCallback deviceSetUncapturedErrorCallback;
    WGPUProcDeviceTick deviceTick;
    WGPUProcDeviceValidateTextureDescriptor deviceValidateTextureDescriptor;
    WGPUProcDeviceReference deviceReference;
    WGPUProcDeviceRelease deviceRelease;

    WGPUProcExternalTextureDestroy externalTextureDestroy;
    WGPUProcExternalTextureExpire externalTextureExpire;
    WGPUProcExternalTextureRefresh externalTextureRefresh;
    WGPUProcExternalTextureSetLabel externalTextureSetLabel;
    WGPUProcExternalTextureReference externalTextureReference;
    WGPUProcExternalTextureRelease externalTextureRelease;

    WGPUProcInstanceCreateSurface instanceCreateSurface;
    WGPUProcInstanceEnumerateWGSLLanguageFeatures instanceEnumerateWGSLLanguageFeatures;
    WGPUProcInstanceHasWGSLLanguageFeature instanceHasWGSLLanguageFeature;
    WGPUProcInstanceProcessEvents instanceProcessEvents;
    WGPUProcInstanceRequestAdapter instanceRequestAdapter;
    WGPUProcInstanceRequestAdapterF instanceRequestAdapterF;
    WGPUProcInstanceWaitAny instanceWaitAny;
    WGPUProcInstanceReference instanceReference;
    WGPUProcInstanceRelease instanceRelease;

    WGPUProcPipelineLayoutSetLabel pipelineLayoutSetLabel;
    WGPUProcPipelineLayoutReference pipelineLayoutReference;
    WGPUProcPipelineLayoutRelease pipelineLayoutRelease;

    WGPUProcQuerySetDestroy querySetDestroy;
    WGPUProcQuerySetGetCount querySetGetCount;
    WGPUProcQuerySetGetType querySetGetType;
    WGPUProcQuerySetSetLabel querySetSetLabel;
    WGPUProcQuerySetReference querySetReference;
    WGPUProcQuerySetRelease querySetRelease;

    WGPUProcQueueCopyExternalTextureForBrowser queueCopyExternalTextureForBrowser;
    WGPUProcQueueCopyTextureForBrowser queueCopyTextureForBrowser;
    WGPUProcQueueOnSubmittedWorkDone queueOnSubmittedWorkDone;
    WGPUProcQueueOnSubmittedWorkDoneF queueOnSubmittedWorkDoneF;
    WGPUProcQueueSetLabel queueSetLabel;
    WGPUProcQueueSubmit queueSubmit;
    WGPUProcQueueWriteBuffer queueWriteBuffer;
    WGPUProcQueueWriteTexture queueWriteTexture;
    WGPUProcQueueReference queueReference;
    WGPUProcQueueRelease queueRelease;

    WGPUProcRenderBundleSetLabel renderBundleSetLabel;
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
    WGPUProcRenderBundleEncoderSetLabel renderBundleEncoderSetLabel;
    WGPUProcRenderBundleEncoderSetPipeline renderBundleEncoderSetPipeline;
    WGPUProcRenderBundleEncoderSetVertexBuffer renderBundleEncoderSetVertexBuffer;
    WGPUProcRenderBundleEncoderReference renderBundleEncoderReference;
    WGPUProcRenderBundleEncoderRelease renderBundleEncoderRelease;

    WGPUProcRenderPassEncoderBeginOcclusionQuery renderPassEncoderBeginOcclusionQuery;
    WGPUProcRenderPassEncoderDraw renderPassEncoderDraw;
    WGPUProcRenderPassEncoderDrawIndexed renderPassEncoderDrawIndexed;
    WGPUProcRenderPassEncoderDrawIndexedIndirect renderPassEncoderDrawIndexedIndirect;
    WGPUProcRenderPassEncoderDrawIndirect renderPassEncoderDrawIndirect;
    WGPUProcRenderPassEncoderEnd renderPassEncoderEnd;
    WGPUProcRenderPassEncoderEndOcclusionQuery renderPassEncoderEndOcclusionQuery;
    WGPUProcRenderPassEncoderExecuteBundles renderPassEncoderExecuteBundles;
    WGPUProcRenderPassEncoderInsertDebugMarker renderPassEncoderInsertDebugMarker;
    WGPUProcRenderPassEncoderPixelLocalStorageBarrier renderPassEncoderPixelLocalStorageBarrier;
    WGPUProcRenderPassEncoderPopDebugGroup renderPassEncoderPopDebugGroup;
    WGPUProcRenderPassEncoderPushDebugGroup renderPassEncoderPushDebugGroup;
    WGPUProcRenderPassEncoderSetBindGroup renderPassEncoderSetBindGroup;
    WGPUProcRenderPassEncoderSetBlendConstant renderPassEncoderSetBlendConstant;
    WGPUProcRenderPassEncoderSetIndexBuffer renderPassEncoderSetIndexBuffer;
    WGPUProcRenderPassEncoderSetLabel renderPassEncoderSetLabel;
    WGPUProcRenderPassEncoderSetPipeline renderPassEncoderSetPipeline;
    WGPUProcRenderPassEncoderSetScissorRect renderPassEncoderSetScissorRect;
    WGPUProcRenderPassEncoderSetStencilReference renderPassEncoderSetStencilReference;
    WGPUProcRenderPassEncoderSetVertexBuffer renderPassEncoderSetVertexBuffer;
    WGPUProcRenderPassEncoderSetViewport renderPassEncoderSetViewport;
    WGPUProcRenderPassEncoderWriteTimestamp renderPassEncoderWriteTimestamp;
    WGPUProcRenderPassEncoderReference renderPassEncoderReference;
    WGPUProcRenderPassEncoderRelease renderPassEncoderRelease;

    WGPUProcRenderPipelineGetBindGroupLayout renderPipelineGetBindGroupLayout;
    WGPUProcRenderPipelineSetLabel renderPipelineSetLabel;
    WGPUProcRenderPipelineReference renderPipelineReference;
    WGPUProcRenderPipelineRelease renderPipelineRelease;

    WGPUProcSamplerSetLabel samplerSetLabel;
    WGPUProcSamplerReference samplerReference;
    WGPUProcSamplerRelease samplerRelease;

    WGPUProcShaderModuleGetCompilationInfo shaderModuleGetCompilationInfo;
    WGPUProcShaderModuleGetCompilationInfoF shaderModuleGetCompilationInfoF;
    WGPUProcShaderModuleSetLabel shaderModuleSetLabel;
    WGPUProcShaderModuleReference shaderModuleReference;
    WGPUProcShaderModuleRelease shaderModuleRelease;

    WGPUProcSharedBufferMemoryBeginAccess sharedBufferMemoryBeginAccess;
    WGPUProcSharedBufferMemoryCreateBuffer sharedBufferMemoryCreateBuffer;
    WGPUProcSharedBufferMemoryEndAccess sharedBufferMemoryEndAccess;
    WGPUProcSharedBufferMemoryGetProperties sharedBufferMemoryGetProperties;
    WGPUProcSharedBufferMemoryIsDeviceLost sharedBufferMemoryIsDeviceLost;
    WGPUProcSharedBufferMemorySetLabel sharedBufferMemorySetLabel;
    WGPUProcSharedBufferMemoryReference sharedBufferMemoryReference;
    WGPUProcSharedBufferMemoryRelease sharedBufferMemoryRelease;

    WGPUProcSharedFenceExportInfo sharedFenceExportInfo;
    WGPUProcSharedFenceReference sharedFenceReference;
    WGPUProcSharedFenceRelease sharedFenceRelease;

    WGPUProcSharedTextureMemoryBeginAccess sharedTextureMemoryBeginAccess;
    WGPUProcSharedTextureMemoryCreateTexture sharedTextureMemoryCreateTexture;
    WGPUProcSharedTextureMemoryEndAccess sharedTextureMemoryEndAccess;
    WGPUProcSharedTextureMemoryGetProperties sharedTextureMemoryGetProperties;
    WGPUProcSharedTextureMemoryIsDeviceLost sharedTextureMemoryIsDeviceLost;
    WGPUProcSharedTextureMemorySetLabel sharedTextureMemorySetLabel;
    WGPUProcSharedTextureMemoryReference sharedTextureMemoryReference;
    WGPUProcSharedTextureMemoryRelease sharedTextureMemoryRelease;

    WGPUProcSurfaceGetPreferredFormat surfaceGetPreferredFormat;
    WGPUProcSurfaceReference surfaceReference;
    WGPUProcSurfaceRelease surfaceRelease;

    WGPUProcSwapChainGetCurrentTexture swapChainGetCurrentTexture;
    WGPUProcSwapChainGetCurrentTextureView swapChainGetCurrentTextureView;
    WGPUProcSwapChainPresent swapChainPresent;
    WGPUProcSwapChainReference swapChainReference;
    WGPUProcSwapChainRelease swapChainRelease;

    WGPUProcTextureCreateErrorView textureCreateErrorView;
    WGPUProcTextureCreateView textureCreateView;
    WGPUProcTextureDestroy textureDestroy;
    WGPUProcTextureGetDepthOrArrayLayers textureGetDepthOrArrayLayers;
    WGPUProcTextureGetDimension textureGetDimension;
    WGPUProcTextureGetFormat textureGetFormat;
    WGPUProcTextureGetHeight textureGetHeight;
    WGPUProcTextureGetMipLevelCount textureGetMipLevelCount;
    WGPUProcTextureGetSampleCount textureGetSampleCount;
    WGPUProcTextureGetUsage textureGetUsage;
    WGPUProcTextureGetWidth textureGetWidth;
    WGPUProcTextureSetLabel textureSetLabel;
    WGPUProcTextureReference textureReference;
    WGPUProcTextureRelease textureRelease;

    WGPUProcTextureViewSetLabel textureViewSetLabel;
    WGPUProcTextureViewReference textureViewReference;
    WGPUProcTextureViewRelease textureViewRelease;


} DawnProcTable;

#endif  // DAWN_DAWN_PROC_TABLE_H_
