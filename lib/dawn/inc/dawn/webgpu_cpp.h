#ifdef __EMSCRIPTEN__
#error "Do not include this header. Emscripten already provides headers needed for WebGPU."
#endif
#ifndef WEBGPU_CPP_H_
#define WEBGPU_CPP_H_

#include "webgpu/webgpu.h"
#include "webgpu/webgpu_cpp_chained_struct.h"
#include "webgpu/webgpu_enum_class_bitmasks.h"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>

namespace wgpu {

    namespace detail {
        constexpr size_t ConstexprMax(size_t a, size_t b) {
            return a > b ? a : b;
        }
    }  // namespace detail

    static constexpr uint32_t kArrayLayerCountUndefined = WGPU_ARRAY_LAYER_COUNT_UNDEFINED;
    static constexpr uint32_t kCopyStrideUndefined = WGPU_COPY_STRIDE_UNDEFINED;
    static constexpr uint32_t kDepthSliceUndefined = WGPU_DEPTH_SLICE_UNDEFINED;
    static constexpr uint32_t kLimitU32Undefined = WGPU_LIMIT_U32_UNDEFINED;
    static constexpr uint64_t kLimitU64Undefined = WGPU_LIMIT_U64_UNDEFINED;
    static constexpr uint32_t kMipLevelCountUndefined = WGPU_MIP_LEVEL_COUNT_UNDEFINED;
    static constexpr uint32_t kQuerySetIndexUndefined = WGPU_QUERY_SET_INDEX_UNDEFINED;
    static constexpr size_t kWholeMapSize = WGPU_WHOLE_MAP_SIZE;
    static constexpr uint64_t kWholeSize = WGPU_WHOLE_SIZE;

    enum class WGSLFeatureName : uint32_t {
        Undefined = 0x00000000,
        ReadonlyAndReadwriteStorageTextures = 0x00000001,
        Packed4x8IntegerDotProduct = 0x00000002,
        UnrestrictedPointerParameters = 0x00000003,
        PointerCompositeAccess = 0x00000004,
        ChromiumTestingUnimplemented = 0x000003E8,
        ChromiumTestingUnsafeExperimental = 0x000003E9,
        ChromiumTestingExperimental = 0x000003EA,
        ChromiumTestingShippedWithKillswitch = 0x000003EB,
        ChromiumTestingShipped = 0x000003EC,
    };

    enum class AdapterType : uint32_t {
        DiscreteGPU = 0x00000001,
        IntegratedGPU = 0x00000002,
        CPU = 0x00000003,
        Unknown = 0x00000004,
    };

    enum class AddressMode : uint32_t {
        Undefined = 0x00000000,
        ClampToEdge = 0x00000001,
        Repeat = 0x00000002,
        MirrorRepeat = 0x00000003,
    };

    enum class AlphaMode : uint32_t {
        Opaque = 0x00000001,
        Premultiplied = 0x00000002,
        Unpremultiplied = 0x00000003,
    };

    enum class BackendType : uint32_t {
        Undefined = 0x00000000,
        Null = 0x00000001,
        WebGPU = 0x00000002,
        D3D11 = 0x00000003,
        D3D12 = 0x00000004,
        Metal = 0x00000005,
        Vulkan = 0x00000006,
        OpenGL = 0x00000007,
        OpenGLES = 0x00000008,
    };

    enum class BlendFactor : uint32_t {
        Undefined = 0x00000000,
        Zero = 0x00000001,
        One = 0x00000002,
        Src = 0x00000003,
        OneMinusSrc = 0x00000004,
        SrcAlpha = 0x00000005,
        OneMinusSrcAlpha = 0x00000006,
        Dst = 0x00000007,
        OneMinusDst = 0x00000008,
        DstAlpha = 0x00000009,
        OneMinusDstAlpha = 0x0000000A,
        SrcAlphaSaturated = 0x0000000B,
        Constant = 0x0000000C,
        OneMinusConstant = 0x0000000D,
        Src1 = 0x0000000E,
        OneMinusSrc1 = 0x0000000F,
        Src1Alpha = 0x00000010,
        OneMinusSrc1Alpha = 0x00000011,
    };

    enum class BlendOperation : uint32_t {
        Undefined = 0x00000000,
        Add = 0x00000001,
        Subtract = 0x00000002,
        ReverseSubtract = 0x00000003,
        Min = 0x00000004,
        Max = 0x00000005,
    };

    enum class BufferBindingType : uint32_t {
        Undefined = 0x00000000,
        Uniform = 0x00000001,
        Storage = 0x00000002,
        ReadOnlyStorage = 0x00000003,
    };

    enum class BufferMapAsyncStatus : uint32_t {
        Success = 0x00000000,
        InstanceDropped = 0x00000001,
        ValidationError = 0x00000002,
        Unknown = 0x00000003,
        DeviceLost = 0x00000004,
        DestroyedBeforeCallback = 0x00000005,
        UnmappedBeforeCallback = 0x00000006,
        MappingAlreadyPending = 0x00000007,
        OffsetOutOfRange = 0x00000008,
        SizeOutOfRange = 0x00000009,
    };

    enum class BufferMapState : uint32_t {
        Unmapped = 0x00000001,
        Pending = 0x00000002,
        Mapped = 0x00000003,
    };

    enum class CallbackMode : uint32_t {
        WaitAnyOnly = 0x00000000,
        AllowProcessEvents = 0x00000001,
        AllowSpontaneous = 0x00000002,
    };

    enum class CompareFunction : uint32_t {
        Undefined = 0x00000000,
        Never = 0x00000001,
        Less = 0x00000002,
        Equal = 0x00000003,
        LessEqual = 0x00000004,
        Greater = 0x00000005,
        NotEqual = 0x00000006,
        GreaterEqual = 0x00000007,
        Always = 0x00000008,
    };

    enum class CompilationInfoRequestStatus : uint32_t {
        Success = 0x00000000,
        InstanceDropped = 0x00000001,
        Error = 0x00000002,
        DeviceLost = 0x00000003,
        Unknown = 0x00000004,
    };

    enum class CompilationMessageType : uint32_t {
        Error = 0x00000001,
        Warning = 0x00000002,
        Info = 0x00000003,
    };

    enum class CreatePipelineAsyncStatus : uint32_t {
        Success = 0x00000000,
        InstanceDropped = 0x00000001,
        ValidationError = 0x00000002,
        InternalError = 0x00000003,
        DeviceLost = 0x00000004,
        DeviceDestroyed = 0x00000005,
        Unknown = 0x00000006,
    };

    enum class CullMode : uint32_t {
        Undefined = 0x00000000,
        None = 0x00000001,
        Front = 0x00000002,
        Back = 0x00000003,
    };

    enum class DeviceLostReason : uint32_t {
        Undefined = 0x00000000,
        Destroyed = 0x00000001,
    };

    enum class ErrorFilter : uint32_t {
        Validation = 0x00000001,
        OutOfMemory = 0x00000002,
        Internal = 0x00000003,
    };

    enum class ErrorType : uint32_t {
        NoError = 0x00000000,
        Validation = 0x00000001,
        OutOfMemory = 0x00000002,
        Internal = 0x00000003,
        Unknown = 0x00000004,
        DeviceLost = 0x00000005,
    };

    enum class ExternalTextureRotation : uint32_t {
        Rotate0Degrees = 0x00000000,
        Rotate90Degrees = 0x00000001,
        Rotate180Degrees = 0x00000002,
        Rotate270Degrees = 0x00000003,
    };

    enum class FeatureName : uint32_t {
        Undefined = 0x00000000,
        DepthClipControl = 0x00000001,
        Depth32FloatStencil8 = 0x00000002,
        TimestampQuery = 0x00000003,
        TextureCompressionBC = 0x00000004,
        TextureCompressionETC2 = 0x00000005,
        TextureCompressionASTC = 0x00000006,
        IndirectFirstInstance = 0x00000007,
        ShaderF16 = 0x00000008,
        RG11B10UfloatRenderable = 0x00000009,
        BGRA8UnormStorage = 0x0000000A,
        Float32Filterable = 0x0000000B,
        DawnInternalUsages = 0x000003EA,
        DawnMultiPlanarFormats = 0x000003EB,
        DawnNative = 0x000003EC,
        ChromiumExperimentalTimestampQueryInsidePasses = 0x000003EE,
        ImplicitDeviceSynchronization = 0x000003EF,
        SurfaceCapabilities = 0x000003F0,
        TransientAttachments = 0x000003F1,
        MSAARenderToSingleSampled = 0x000003F2,
        DualSourceBlending = 0x000003F3,
        D3D11MultithreadProtected = 0x000003F4,
        ANGLETextureSharing = 0x000003F5,
        ChromiumExperimentalSubgroups = 0x000003F6,
        ChromiumExperimentalSubgroupUniformControlFlow = 0x000003F7,
        PixelLocalStorageCoherent = 0x000003F9,
        PixelLocalStorageNonCoherent = 0x000003FA,
        Norm16TextureFormats = 0x000003FB,
        MultiPlanarFormatExtendedUsages = 0x000003FC,
        MultiPlanarFormatP010 = 0x000003FD,
        HostMappedPointer = 0x000003FE,
        MultiPlanarRenderTargets = 0x000003FF,
        MultiPlanarFormatNv12a = 0x00000400,
        FramebufferFetch = 0x00000401,
        BufferMapExtendedUsages = 0x00000402,
        AdapterPropertiesMemoryHeaps = 0x00000403,
        AdapterPropertiesD3D = 0x00000404,
        R8UnormStorage = 0x00000405,
        SharedTextureMemoryVkDedicatedAllocation = 0x0000044C,
        SharedTextureMemoryAHardwareBuffer = 0x0000044D,
        SharedTextureMemoryDmaBuf = 0x0000044E,
        SharedTextureMemoryOpaqueFD = 0x0000044F,
        SharedTextureMemoryZirconHandle = 0x00000450,
        SharedTextureMemoryDXGISharedHandle = 0x00000451,
        SharedTextureMemoryD3D11Texture2D = 0x00000452,
        SharedTextureMemoryIOSurface = 0x00000453,
        SharedTextureMemoryEGLImage = 0x00000454,
        SharedFenceVkSemaphoreOpaqueFD = 0x000004B0,
        SharedFenceVkSemaphoreSyncFD = 0x000004B1,
        SharedFenceVkSemaphoreZirconHandle = 0x000004B2,
        SharedFenceDXGISharedHandle = 0x000004B3,
        SharedFenceMTLSharedEvent = 0x000004B4,
        SharedBufferMemoryD3D12Resource = 0x000004B5,
    };

    enum class FilterMode : uint32_t {
        Undefined = 0x00000000,
        Nearest = 0x00000001,
        Linear = 0x00000002,
    };

    enum class FrontFace : uint32_t {
        Undefined = 0x00000000,
        CCW = 0x00000001,
        CW = 0x00000002,
    };

    enum class IndexFormat : uint32_t {
        Undefined = 0x00000000,
        Uint16 = 0x00000001,
        Uint32 = 0x00000002,
    };

    enum class LoadOp : uint32_t {
        Undefined = 0x00000000,
        Clear = 0x00000001,
        Load = 0x00000002,
    };

    enum class LoggingType : uint32_t {
        Verbose = 0x00000001,
        Info = 0x00000002,
        Warning = 0x00000003,
        Error = 0x00000004,
    };

    enum class MipmapFilterMode : uint32_t {
        Undefined = 0x00000000,
        Nearest = 0x00000001,
        Linear = 0x00000002,
    };

    enum class PopErrorScopeStatus : uint32_t {
        Success = 0x00000000,
        InstanceDropped = 0x00000001,
    };

    enum class PowerPreference : uint32_t {
        Undefined = 0x00000000,
        LowPower = 0x00000001,
        HighPerformance = 0x00000002,
    };

    enum class PresentMode : uint32_t {
        Fifo = 0x00000001,
        Immediate = 0x00000003,
        Mailbox = 0x00000004,
    };

    enum class PrimitiveTopology : uint32_t {
        Undefined = 0x00000000,
        PointList = 0x00000001,
        LineList = 0x00000002,
        LineStrip = 0x00000003,
        TriangleList = 0x00000004,
        TriangleStrip = 0x00000005,
    };

    enum class QueryType : uint32_t {
        Occlusion = 0x00000001,
        Timestamp = 0x00000002,
    };

    enum class QueueWorkDoneStatus : uint32_t {
        Success = 0x00000000,
        InstanceDropped = 0x00000001,
        Error = 0x00000002,
        Unknown = 0x00000003,
        DeviceLost = 0x00000004,
    };

    enum class RequestAdapterStatus : uint32_t {
        Success = 0x00000000,
        InstanceDropped = 0x00000001,
        Unavailable = 0x00000002,
        Error = 0x00000003,
        Unknown = 0x00000004,
    };

    enum class RequestDeviceStatus : uint32_t {
        Success = 0x00000000,
        InstanceDropped = 0x00000001,
        Error = 0x00000002,
        Unknown = 0x00000003,
    };

    enum class SType : uint32_t {
        Invalid = 0x00000000,
        SurfaceDescriptorFromMetalLayer = 0x00000001,
        SurfaceDescriptorFromWindowsHWND = 0x00000002,
        SurfaceDescriptorFromXlibWindow = 0x00000003,
        SurfaceDescriptorFromCanvasHTMLSelector = 0x00000004,
        ShaderModuleSPIRVDescriptor = 0x00000005,
        ShaderModuleWGSLDescriptor = 0x00000006,
        PrimitiveDepthClipControl = 0x00000007,
        SurfaceDescriptorFromWaylandSurface = 0x00000008,
        SurfaceDescriptorFromAndroidNativeWindow = 0x00000009,
        SurfaceDescriptorFromWindowsCoreWindow = 0x0000000B,
        ExternalTextureBindingEntry = 0x0000000C,
        ExternalTextureBindingLayout = 0x0000000D,
        SurfaceDescriptorFromWindowsSwapChainPanel = 0x0000000E,
        RenderPassDescriptorMaxDrawCount = 0x0000000F,
        DepthStencilStateDepthWriteDefinedDawn = 0x00000010,
        TextureBindingViewDimensionDescriptor = 0x00000011,
        DawnTextureInternalUsageDescriptor = 0x000003E8,
        DawnEncoderInternalUsageDescriptor = 0x000003EB,
        DawnInstanceDescriptor = 0x000003EC,
        DawnCacheDeviceDescriptor = 0x000003ED,
        DawnAdapterPropertiesPowerPreference = 0x000003EE,
        DawnBufferDescriptorErrorInfoFromWireClient = 0x000003EF,
        DawnTogglesDescriptor = 0x000003F0,
        DawnShaderModuleSPIRVOptionsDescriptor = 0x000003F1,
        RequestAdapterOptionsLUID = 0x000003F2,
        RequestAdapterOptionsGetGLProc = 0x000003F3,
        RequestAdapterOptionsD3D11Device = 0x000003F4,
        DawnMultisampleStateRenderToSingleSampled = 0x000003F5,
        DawnRenderPassColorAttachmentRenderToSingleSampled = 0x000003F6,
        RenderPassPixelLocalStorage = 0x000003F7,
        PipelineLayoutPixelLocalStorage = 0x000003F8,
        BufferHostMappedPointer = 0x000003F9,
        DawnExperimentalSubgroupLimits = 0x000003FA,
        AdapterPropertiesMemoryHeaps = 0x000003FB,
        AdapterPropertiesD3D = 0x000003FC,
        DawnComputePipelineFullSubgroups = 0x000003FD,
        DawnWireWGSLControl = 0x000003FE,
        DawnWGSLBlocklist = 0x000003FF,
        SharedTextureMemoryVkImageDescriptor = 0x0000044C,
        SharedTextureMemoryVkDedicatedAllocationDescriptor = 0x0000044D,
        SharedTextureMemoryAHardwareBufferDescriptor = 0x0000044E,
        SharedTextureMemoryDmaBufDescriptor = 0x0000044F,
        SharedTextureMemoryOpaqueFDDescriptor = 0x00000450,
        SharedTextureMemoryZirconHandleDescriptor = 0x00000451,
        SharedTextureMemoryDXGISharedHandleDescriptor = 0x00000452,
        SharedTextureMemoryD3D11Texture2DDescriptor = 0x00000453,
        SharedTextureMemoryIOSurfaceDescriptor = 0x00000454,
        SharedTextureMemoryEGLImageDescriptor = 0x00000455,
        SharedTextureMemoryInitializedBeginState = 0x000004B0,
        SharedTextureMemoryInitializedEndState = 0x000004B1,
        SharedTextureMemoryVkImageLayoutBeginState = 0x000004B2,
        SharedTextureMemoryVkImageLayoutEndState = 0x000004B3,
        SharedFenceVkSemaphoreOpaqueFDDescriptor = 0x000004B4,
        SharedFenceVkSemaphoreOpaqueFDExportInfo = 0x000004B5,
        SharedFenceVkSemaphoreSyncFDDescriptor = 0x000004B6,
        SharedFenceVkSemaphoreSyncFDExportInfo = 0x000004B7,
        SharedFenceVkSemaphoreZirconHandleDescriptor = 0x000004B8,
        SharedFenceVkSemaphoreZirconHandleExportInfo = 0x000004B9,
        SharedFenceDXGISharedHandleDescriptor = 0x000004BA,
        SharedFenceDXGISharedHandleExportInfo = 0x000004BB,
        SharedFenceMTLSharedEventDescriptor = 0x000004BC,
        SharedFenceMTLSharedEventExportInfo = 0x000004BD,
        SharedBufferMemoryD3D12ResourceDescriptor = 0x000004BE,
    };

    enum class SamplerBindingType : uint32_t {
        Undefined = 0x00000000,
        Filtering = 0x00000001,
        NonFiltering = 0x00000002,
        Comparison = 0x00000003,
    };

    enum class SharedFenceType : uint32_t {
        Undefined = 0x00000000,
        VkSemaphoreOpaqueFD = 0x00000001,
        VkSemaphoreSyncFD = 0x00000002,
        VkSemaphoreZirconHandle = 0x00000003,
        DXGISharedHandle = 0x00000004,
        MTLSharedEvent = 0x00000005,
    };

    enum class StencilOperation : uint32_t {
        Undefined = 0x00000000,
        Keep = 0x00000001,
        Zero = 0x00000002,
        Replace = 0x00000003,
        Invert = 0x00000004,
        IncrementClamp = 0x00000005,
        DecrementClamp = 0x00000006,
        IncrementWrap = 0x00000007,
        DecrementWrap = 0x00000008,
    };

    enum class StorageTextureAccess : uint32_t {
        Undefined = 0x00000000,
        WriteOnly = 0x00000001,
        ReadOnly = 0x00000002,
        ReadWrite = 0x00000003,
    };

    enum class StoreOp : uint32_t {
        Undefined = 0x00000000,
        Store = 0x00000001,
        Discard = 0x00000002,
    };

    enum class TextureAspect : uint32_t {
        Undefined = 0x00000000,
        All = 0x00000001,
        StencilOnly = 0x00000002,
        DepthOnly = 0x00000003,
        Plane0Only = 0x00000004,
        Plane1Only = 0x00000005,
        Plane2Only = 0x00000006,
    };

    enum class TextureDimension : uint32_t {
        Undefined = 0x00000000,
        e1D = 0x00000001,
        e2D = 0x00000002,
        e3D = 0x00000003,
    };

    enum class TextureFormat : uint32_t {
        Undefined = 0x00000000,
        R8Unorm = 0x00000001,
        R8Snorm = 0x00000002,
        R8Uint = 0x00000003,
        R8Sint = 0x00000004,
        R16Uint = 0x00000005,
        R16Sint = 0x00000006,
        R16Float = 0x00000007,
        RG8Unorm = 0x00000008,
        RG8Snorm = 0x00000009,
        RG8Uint = 0x0000000A,
        RG8Sint = 0x0000000B,
        R32Float = 0x0000000C,
        R32Uint = 0x0000000D,
        R32Sint = 0x0000000E,
        RG16Uint = 0x0000000F,
        RG16Sint = 0x00000010,
        RG16Float = 0x00000011,
        RGBA8Unorm = 0x00000012,
        RGBA8UnormSrgb = 0x00000013,
        RGBA8Snorm = 0x00000014,
        RGBA8Uint = 0x00000015,
        RGBA8Sint = 0x00000016,
        BGRA8Unorm = 0x00000017,
        BGRA8UnormSrgb = 0x00000018,
        RGB10A2Uint = 0x00000019,
        RGB10A2Unorm = 0x0000001A,
        RG11B10Ufloat = 0x0000001B,
        RGB9E5Ufloat = 0x0000001C,
        RG32Float = 0x0000001D,
        RG32Uint = 0x0000001E,
        RG32Sint = 0x0000001F,
        RGBA16Uint = 0x00000020,
        RGBA16Sint = 0x00000021,
        RGBA16Float = 0x00000022,
        RGBA32Float = 0x00000023,
        RGBA32Uint = 0x00000024,
        RGBA32Sint = 0x00000025,
        Stencil8 = 0x00000026,
        Depth16Unorm = 0x00000027,
        Depth24Plus = 0x00000028,
        Depth24PlusStencil8 = 0x00000029,
        Depth32Float = 0x0000002A,
        Depth32FloatStencil8 = 0x0000002B,
        BC1RGBAUnorm = 0x0000002C,
        BC1RGBAUnormSrgb = 0x0000002D,
        BC2RGBAUnorm = 0x0000002E,
        BC2RGBAUnormSrgb = 0x0000002F,
        BC3RGBAUnorm = 0x00000030,
        BC3RGBAUnormSrgb = 0x00000031,
        BC4RUnorm = 0x00000032,
        BC4RSnorm = 0x00000033,
        BC5RGUnorm = 0x00000034,
        BC5RGSnorm = 0x00000035,
        BC6HRGBUfloat = 0x00000036,
        BC6HRGBFloat = 0x00000037,
        BC7RGBAUnorm = 0x00000038,
        BC7RGBAUnormSrgb = 0x00000039,
        ETC2RGB8Unorm = 0x0000003A,
        ETC2RGB8UnormSrgb = 0x0000003B,
        ETC2RGB8A1Unorm = 0x0000003C,
        ETC2RGB8A1UnormSrgb = 0x0000003D,
        ETC2RGBA8Unorm = 0x0000003E,
        ETC2RGBA8UnormSrgb = 0x0000003F,
        EACR11Unorm = 0x00000040,
        EACR11Snorm = 0x00000041,
        EACRG11Unorm = 0x00000042,
        EACRG11Snorm = 0x00000043,
        ASTC4x4Unorm = 0x00000044,
        ASTC4x4UnormSrgb = 0x00000045,
        ASTC5x4Unorm = 0x00000046,
        ASTC5x4UnormSrgb = 0x00000047,
        ASTC5x5Unorm = 0x00000048,
        ASTC5x5UnormSrgb = 0x00000049,
        ASTC6x5Unorm = 0x0000004A,
        ASTC6x5UnormSrgb = 0x0000004B,
        ASTC6x6Unorm = 0x0000004C,
        ASTC6x6UnormSrgb = 0x0000004D,
        ASTC8x5Unorm = 0x0000004E,
        ASTC8x5UnormSrgb = 0x0000004F,
        ASTC8x6Unorm = 0x00000050,
        ASTC8x6UnormSrgb = 0x00000051,
        ASTC8x8Unorm = 0x00000052,
        ASTC8x8UnormSrgb = 0x00000053,
        ASTC10x5Unorm = 0x00000054,
        ASTC10x5UnormSrgb = 0x00000055,
        ASTC10x6Unorm = 0x00000056,
        ASTC10x6UnormSrgb = 0x00000057,
        ASTC10x8Unorm = 0x00000058,
        ASTC10x8UnormSrgb = 0x00000059,
        ASTC10x10Unorm = 0x0000005A,
        ASTC10x10UnormSrgb = 0x0000005B,
        ASTC12x10Unorm = 0x0000005C,
        ASTC12x10UnormSrgb = 0x0000005D,
        ASTC12x12Unorm = 0x0000005E,
        ASTC12x12UnormSrgb = 0x0000005F,
        R16Unorm = 0x00000060,
        RG16Unorm = 0x00000061,
        RGBA16Unorm = 0x00000062,
        R16Snorm = 0x00000063,
        RG16Snorm = 0x00000064,
        RGBA16Snorm = 0x00000065,
        R8BG8Biplanar420Unorm = 0x00000066,
        R10X6BG10X6Biplanar420Unorm = 0x00000067,
        R8BG8A8Triplanar420Unorm = 0x00000068,
    };

    enum class TextureSampleType : uint32_t {
        Undefined = 0x00000000,
        Float = 0x00000001,
        UnfilterableFloat = 0x00000002,
        Depth = 0x00000003,
        Sint = 0x00000004,
        Uint = 0x00000005,
    };

    enum class TextureViewDimension : uint32_t {
        Undefined = 0x00000000,
        e1D = 0x00000001,
        e2D = 0x00000002,
        e2DArray = 0x00000003,
        Cube = 0x00000004,
        CubeArray = 0x00000005,
        e3D = 0x00000006,
    };

    enum class VertexFormat : uint32_t {
        Undefined = 0x00000000,
        Uint8x2 = 0x00000001,
        Uint8x4 = 0x00000002,
        Sint8x2 = 0x00000003,
        Sint8x4 = 0x00000004,
        Unorm8x2 = 0x00000005,
        Unorm8x4 = 0x00000006,
        Snorm8x2 = 0x00000007,
        Snorm8x4 = 0x00000008,
        Uint16x2 = 0x00000009,
        Uint16x4 = 0x0000000A,
        Sint16x2 = 0x0000000B,
        Sint16x4 = 0x0000000C,
        Unorm16x2 = 0x0000000D,
        Unorm16x4 = 0x0000000E,
        Snorm16x2 = 0x0000000F,
        Snorm16x4 = 0x00000010,
        Float16x2 = 0x00000011,
        Float16x4 = 0x00000012,
        Float32 = 0x00000013,
        Float32x2 = 0x00000014,
        Float32x3 = 0x00000015,
        Float32x4 = 0x00000016,
        Uint32 = 0x00000017,
        Uint32x2 = 0x00000018,
        Uint32x3 = 0x00000019,
        Uint32x4 = 0x0000001A,
        Sint32 = 0x0000001B,
        Sint32x2 = 0x0000001C,
        Sint32x3 = 0x0000001D,
        Sint32x4 = 0x0000001E,
        Unorm10_10_10_2 = 0x0000001F,
    };

    enum class VertexStepMode : uint32_t {
        Undefined = 0x00000000,
        VertexBufferNotUsed = 0x00000001,
        Vertex = 0x00000002,
        Instance = 0x00000003,
    };

    enum class WaitStatus : uint32_t {
        Success = 0x00000000,
        TimedOut = 0x00000001,
        UnsupportedTimeout = 0x00000002,
        UnsupportedCount = 0x00000003,
        UnsupportedMixedSources = 0x00000004,
        Unknown = 0x00000005,
    };


    enum class BufferUsage : uint32_t {
        None = 0x00000000,
        MapRead = 0x00000001,
        MapWrite = 0x00000002,
        CopySrc = 0x00000004,
        CopyDst = 0x00000008,
        Index = 0x00000010,
        Vertex = 0x00000020,
        Uniform = 0x00000040,
        Storage = 0x00000080,
        Indirect = 0x00000100,
        QueryResolve = 0x00000200,
    };

    enum class ColorWriteMask : uint32_t {
        None = 0x00000000,
        Red = 0x00000001,
        Green = 0x00000002,
        Blue = 0x00000004,
        Alpha = 0x00000008,
        All = 0x0000000F,
    };

    enum class HeapProperty : uint32_t {
        Undefined = 0x00000000,
        DeviceLocal = 0x00000001,
        HostVisible = 0x00000002,
        HostCoherent = 0x00000004,
        HostUncached = 0x00000008,
        HostCached = 0x00000010,
    };

    enum class MapMode : uint32_t {
        None = 0x00000000,
        Read = 0x00000001,
        Write = 0x00000002,
    };

    enum class ShaderStage : uint32_t {
        None = 0x00000000,
        Vertex = 0x00000001,
        Fragment = 0x00000002,
        Compute = 0x00000004,
    };

    enum class TextureUsage : uint32_t {
        None = 0x00000000,
        CopySrc = 0x00000001,
        CopyDst = 0x00000002,
        TextureBinding = 0x00000004,
        StorageBinding = 0x00000008,
        RenderAttachment = 0x00000010,
        TransientAttachment = 0x00000020,
        StorageAttachment = 0x00000040,
    };


    using BufferMapCallback = WGPUBufferMapCallback;
    using Callback = WGPUCallback;
    using CompilationInfoCallback = WGPUCompilationInfoCallback;
    using CreateComputePipelineAsyncCallback = WGPUCreateComputePipelineAsyncCallback;
    using CreateRenderPipelineAsyncCallback = WGPUCreateRenderPipelineAsyncCallback;
    using DawnLoadCacheDataFunction = WGPUDawnLoadCacheDataFunction;
    using DawnStoreCacheDataFunction = WGPUDawnStoreCacheDataFunction;
    using DeviceLostCallback = WGPUDeviceLostCallback;
    using ErrorCallback = WGPUErrorCallback;
    using LoggingCallback = WGPULoggingCallback;
    using PopErrorScopeCallback = WGPUPopErrorScopeCallback;
    using Proc = WGPUProc;
    using QueueWorkDoneCallback = WGPUQueueWorkDoneCallback;
    using RequestAdapterCallback = WGPURequestAdapterCallback;
    using RequestDeviceCallback = WGPURequestDeviceCallback;

    class Adapter;
    class BindGroup;
    class BindGroupLayout;
    class Buffer;
    class CommandBuffer;
    class CommandEncoder;
    class ComputePassEncoder;
    class ComputePipeline;
    class Device;
    class ExternalTexture;
    class Instance;
    class PipelineLayout;
    class QuerySet;
    class Queue;
    class RenderBundle;
    class RenderBundleEncoder;
    class RenderPassEncoder;
    class RenderPipeline;
    class Sampler;
    class ShaderModule;
    class SharedBufferMemory;
    class SharedFence;
    class SharedTextureMemory;
    class Surface;
    class SwapChain;
    class Texture;
    class TextureView;

    struct AdapterProperties;
    struct AdapterPropertiesD3D;
    struct BindGroupEntry;
    struct BlendComponent;
    struct BufferBindingLayout;
    struct BufferDescriptor;
    struct BufferHostMappedPointer;
    struct BufferMapCallbackInfo;
    struct Color;
    struct CommandBufferDescriptor;
    struct CommandEncoderDescriptor;
    struct CompilationInfoCallbackInfo;
    struct CompilationMessage;
    struct ComputePassTimestampWrites;
    struct ConstantEntry;
    struct CopyTextureForBrowserOptions;
    struct CreateComputePipelineAsyncCallbackInfo;
    struct CreateRenderPipelineAsyncCallbackInfo;
    struct DawnWGSLBlocklist;
    struct DawnAdapterPropertiesPowerPreference;
    struct DawnBufferDescriptorErrorInfoFromWireClient;
    struct DawnCacheDeviceDescriptor;
    struct DawnComputePipelineFullSubgroups;
    struct DawnEncoderInternalUsageDescriptor;
    struct DawnExperimentalSubgroupLimits;
    struct DawnMultisampleStateRenderToSingleSampled;
    struct DawnRenderPassColorAttachmentRenderToSingleSampled;
    struct DawnShaderModuleSPIRVOptionsDescriptor;
    struct DawnTextureInternalUsageDescriptor;
    struct DawnTogglesDescriptor;
    struct DawnWireWGSLControl;
    struct DepthStencilStateDepthWriteDefinedDawn;
    struct Extent2D;
    struct Extent3D;
    struct ExternalTextureBindingEntry;
    struct ExternalTextureBindingLayout;
    struct Future;
    struct InstanceFeatures;
    struct Limits;
    struct MemoryHeapInfo;
    struct MultisampleState;
    struct Origin2D;
    struct Origin3D;
    struct PipelineLayoutDescriptor;
    struct PipelineLayoutStorageAttachment;
    struct PopErrorScopeCallbackInfo;
    struct PrimitiveDepthClipControl;
    struct PrimitiveState;
    struct QuerySetDescriptor;
    struct QueueDescriptor;
    struct QueueWorkDoneCallbackInfo;
    struct RenderBundleDescriptor;
    struct RenderBundleEncoderDescriptor;
    struct RenderPassDepthStencilAttachment;
    struct RenderPassDescriptorMaxDrawCount;
    struct RenderPassTimestampWrites;
    struct RequestAdapterCallbackInfo;
    struct RequestAdapterOptions;
    struct RequestDeviceCallbackInfo;
    struct SamplerBindingLayout;
    struct SamplerDescriptor;
    struct ShaderModuleSPIRVDescriptor;
    struct ShaderModuleWGSLDescriptor;
    struct ShaderModuleDescriptor;
    struct SharedBufferMemoryBeginAccessDescriptor;
    struct SharedBufferMemoryDescriptor;
    struct SharedBufferMemoryEndAccessState;
    struct SharedBufferMemoryProperties;
    struct SharedFenceDXGISharedHandleDescriptor;
    struct SharedFenceDXGISharedHandleExportInfo;
    struct SharedFenceMTLSharedEventDescriptor;
    struct SharedFenceMTLSharedEventExportInfo;
    struct SharedFenceDescriptor;
    struct SharedFenceExportInfo;
    struct SharedFenceVkSemaphoreOpaqueFDDescriptor;
    struct SharedFenceVkSemaphoreOpaqueFDExportInfo;
    struct SharedFenceVkSemaphoreSyncFDDescriptor;
    struct SharedFenceVkSemaphoreSyncFDExportInfo;
    struct SharedFenceVkSemaphoreZirconHandleDescriptor;
    struct SharedFenceVkSemaphoreZirconHandleExportInfo;
    struct SharedTextureMemoryDXGISharedHandleDescriptor;
    struct SharedTextureMemoryEGLImageDescriptor;
    struct SharedTextureMemoryIOSurfaceDescriptor;
    struct SharedTextureMemoryAHardwareBufferDescriptor;
    struct SharedTextureMemoryBeginAccessDescriptor;
    struct SharedTextureMemoryDescriptor;
    struct SharedTextureMemoryDmaBufPlane;
    struct SharedTextureMemoryEndAccessState;
    struct SharedTextureMemoryOpaqueFDDescriptor;
    struct SharedTextureMemoryVkDedicatedAllocationDescriptor;
    struct SharedTextureMemoryVkImageLayoutBeginState;
    struct SharedTextureMemoryVkImageLayoutEndState;
    struct SharedTextureMemoryZirconHandleDescriptor;
    struct StencilFaceState;
    struct StorageTextureBindingLayout;
    struct SurfaceDescriptor;
    struct SurfaceDescriptorFromAndroidNativeWindow;
    struct SurfaceDescriptorFromCanvasHTMLSelector;
    struct SurfaceDescriptorFromMetalLayer;
    struct SurfaceDescriptorFromWaylandSurface;
    struct SurfaceDescriptorFromWindowsHWND;
    struct SurfaceDescriptorFromWindowsCoreWindow;
    struct SurfaceDescriptorFromWindowsSwapChainPanel;
    struct SurfaceDescriptorFromXlibWindow;
    struct SwapChainDescriptor;
    struct TextureBindingLayout;
    struct TextureBindingViewDimensionDescriptor;
    struct TextureDataLayout;
    struct TextureViewDescriptor;
    struct VertexAttribute;
    struct AdapterPropertiesMemoryHeaps;
    struct BindGroupDescriptor;
    struct BindGroupLayoutEntry;
    struct BlendState;
    struct CompilationInfo;
    struct ComputePassDescriptor;
    struct DepthStencilState;
    struct ExternalTextureDescriptor;
    struct FutureWaitInfo;
    struct ImageCopyBuffer;
    struct ImageCopyExternalTexture;
    struct ImageCopyTexture;
    struct InstanceDescriptor;
    struct PipelineLayoutPixelLocalStorage;
    struct ProgrammableStageDescriptor;
    struct RenderPassColorAttachment;
    struct RenderPassStorageAttachment;
    struct RequiredLimits;
    struct SharedTextureMemoryDmaBufDescriptor;
    struct SharedTextureMemoryProperties;
    struct SharedTextureMemoryVkImageDescriptor;
    struct SupportedLimits;
    struct TextureDescriptor;
    struct VertexBufferLayout;
    struct BindGroupLayoutDescriptor;
    struct ColorTargetState;
    struct ComputePipelineDescriptor;
    struct DeviceDescriptor;
    struct RenderPassDescriptor;
    struct RenderPassPixelLocalStorage;
    struct VertexState;
    struct FragmentState;
    struct RenderPipelineDescriptor;


    // Special class for booleans in order to allow implicit conversions.
    class Bool {
      public:
        constexpr Bool() = default;
        // NOLINTNEXTLINE(runtime/explicit) allow implicit construction
        constexpr Bool(bool value) : mValue(static_cast<WGPUBool>(value)) {}
        // NOLINTNEXTLINE(runtime/explicit) allow implicit construction
        Bool(WGPUBool value): mValue(value) {}

        constexpr operator bool() const { return static_cast<bool>(mValue); }

      private:
        friend struct std::hash<Bool>;
        // Default to false.
        WGPUBool mValue = static_cast<WGPUBool>(false);
    };

    template<typename Derived, typename CType>
    class ObjectBase {
      public:
        ObjectBase() = default;
        ObjectBase(CType handle): mHandle(handle) {
            if (mHandle) Derived::WGPUReference(mHandle);
        }
        ~ObjectBase() {
            if (mHandle) Derived::WGPURelease(mHandle);
        }

        ObjectBase(ObjectBase const& other)
            : ObjectBase(other.Get()) {
        }
        Derived& operator=(ObjectBase const& other) {
            if (&other != this) {
                if (mHandle) Derived::WGPURelease(mHandle);
                mHandle = other.mHandle;
                if (mHandle) Derived::WGPUReference(mHandle);
            }

            return static_cast<Derived&>(*this);
        }

        ObjectBase(ObjectBase&& other) {
            mHandle = other.mHandle;
            other.mHandle = 0;
        }
        Derived& operator=(ObjectBase&& other) {
            if (&other != this) {
                if (mHandle) Derived::WGPURelease(mHandle);
                mHandle = other.mHandle;
                other.mHandle = 0;
            }

            return static_cast<Derived&>(*this);
        }

        ObjectBase(std::nullptr_t) {}
        Derived& operator=(std::nullptr_t) {
            if (mHandle != nullptr) {
                Derived::WGPURelease(mHandle);
                mHandle = nullptr;
            }
            return static_cast<Derived&>(*this);
        }

        bool operator==(std::nullptr_t) const {
            return mHandle == nullptr;
        }
        bool operator!=(std::nullptr_t) const {
            return mHandle != nullptr;
        }

        explicit operator bool() const {
            return mHandle != nullptr;
        }
        CType Get() const {
            return mHandle;
        }
        CType MoveToCHandle() {
            CType result = mHandle;
            mHandle = 0;
            return result;
        }
        static Derived Acquire(CType handle) {
            Derived result;
            result.mHandle = handle;
            return result;
        }

      protected:
        CType mHandle = nullptr;
    };



    class Adapter : public ObjectBase<Adapter, WGPUAdapter> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        Device CreateDevice(DeviceDescriptor const * descriptor = nullptr) const;
        size_t EnumerateFeatures(FeatureName * features) const;
        Instance GetInstance() const;
        Bool GetLimits(SupportedLimits * limits) const;
        void GetProperties(AdapterProperties * properties) const;
        Bool HasFeature(FeatureName feature) const;
        void RequestDevice(DeviceDescriptor const * descriptor, RequestDeviceCallback callback, void * userdata) const;
        Future RequestDevice(DeviceDescriptor const * options, RequestDeviceCallbackInfo callbackInfo) const;

      private:
        friend ObjectBase<Adapter, WGPUAdapter>;
        static void WGPUReference(WGPUAdapter handle);
        static void WGPURelease(WGPUAdapter handle);
    };

    class BindGroup : public ObjectBase<BindGroup, WGPUBindGroup> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<BindGroup, WGPUBindGroup>;
        static void WGPUReference(WGPUBindGroup handle);
        static void WGPURelease(WGPUBindGroup handle);
    };

    class BindGroupLayout : public ObjectBase<BindGroupLayout, WGPUBindGroupLayout> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<BindGroupLayout, WGPUBindGroupLayout>;
        static void WGPUReference(WGPUBindGroupLayout handle);
        static void WGPURelease(WGPUBindGroupLayout handle);
    };

    class Buffer : public ObjectBase<Buffer, WGPUBuffer> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void Destroy() const;
        void const * GetConstMappedRange(size_t offset = 0, size_t size = WGPU_WHOLE_MAP_SIZE) const;
        BufferMapState GetMapState() const;
        void * GetMappedRange(size_t offset = 0, size_t size = WGPU_WHOLE_MAP_SIZE) const;
        uint64_t GetSize() const;
        BufferUsage GetUsage() const;
        void MapAsync(MapMode mode, size_t offset, size_t size, BufferMapCallback callback, void * userdata) const;
        Future MapAsync(MapMode mode, size_t offset, size_t size, BufferMapCallbackInfo callbackInfo) const;
        void SetLabel(char const * label) const;
        void Unmap() const;

      private:
        friend ObjectBase<Buffer, WGPUBuffer>;
        static void WGPUReference(WGPUBuffer handle);
        static void WGPURelease(WGPUBuffer handle);
    };

    class CommandBuffer : public ObjectBase<CommandBuffer, WGPUCommandBuffer> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<CommandBuffer, WGPUCommandBuffer>;
        static void WGPUReference(WGPUCommandBuffer handle);
        static void WGPURelease(WGPUCommandBuffer handle);
    };

    class CommandEncoder : public ObjectBase<CommandEncoder, WGPUCommandEncoder> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        ComputePassEncoder BeginComputePass(ComputePassDescriptor const * descriptor = nullptr) const;
        RenderPassEncoder BeginRenderPass(RenderPassDescriptor const * descriptor) const;
        void ClearBuffer(Buffer const& buffer, uint64_t offset = 0, uint64_t size = WGPU_WHOLE_SIZE) const;
        void CopyBufferToBuffer(Buffer const& source, uint64_t sourceOffset, Buffer const& destination, uint64_t destinationOffset, uint64_t size) const;
        void CopyBufferToTexture(ImageCopyBuffer const * source, ImageCopyTexture const * destination, Extent3D const * copySize) const;
        void CopyTextureToBuffer(ImageCopyTexture const * source, ImageCopyBuffer const * destination, Extent3D const * copySize) const;
        void CopyTextureToTexture(ImageCopyTexture const * source, ImageCopyTexture const * destination, Extent3D const * copySize) const;
        CommandBuffer Finish(CommandBufferDescriptor const * descriptor = nullptr) const;
        void InjectValidationError(char const * message) const;
        void InsertDebugMarker(char const * markerLabel) const;
        void PopDebugGroup() const;
        void PushDebugGroup(char const * groupLabel) const;
        void ResolveQuerySet(QuerySet const& querySet, uint32_t firstQuery, uint32_t queryCount, Buffer const& destination, uint64_t destinationOffset) const;
        void SetLabel(char const * label) const;
        void WriteBuffer(Buffer const& buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) const;
        void WriteTimestamp(QuerySet const& querySet, uint32_t queryIndex) const;

      private:
        friend ObjectBase<CommandEncoder, WGPUCommandEncoder>;
        static void WGPUReference(WGPUCommandEncoder handle);
        static void WGPURelease(WGPUCommandEncoder handle);
    };

    class ComputePassEncoder : public ObjectBase<ComputePassEncoder, WGPUComputePassEncoder> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void DispatchWorkgroups(uint32_t workgroupCountX, uint32_t workgroupCountY = 1, uint32_t workgroupCountZ = 1) const;
        void DispatchWorkgroupsIndirect(Buffer const& indirectBuffer, uint64_t indirectOffset) const;
        void End() const;
        void InsertDebugMarker(char const * markerLabel) const;
        void PopDebugGroup() const;
        void PushDebugGroup(char const * groupLabel) const;
        void SetBindGroup(uint32_t groupIndex, BindGroup const& group, size_t dynamicOffsetCount = 0, uint32_t const * dynamicOffsets = nullptr) const;
        void SetLabel(char const * label) const;
        void SetPipeline(ComputePipeline const& pipeline) const;
        void WriteTimestamp(QuerySet const& querySet, uint32_t queryIndex) const;

      private:
        friend ObjectBase<ComputePassEncoder, WGPUComputePassEncoder>;
        static void WGPUReference(WGPUComputePassEncoder handle);
        static void WGPURelease(WGPUComputePassEncoder handle);
    };

    class ComputePipeline : public ObjectBase<ComputePipeline, WGPUComputePipeline> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        BindGroupLayout GetBindGroupLayout(uint32_t groupIndex) const;
        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<ComputePipeline, WGPUComputePipeline>;
        static void WGPUReference(WGPUComputePipeline handle);
        static void WGPURelease(WGPUComputePipeline handle);
    };

    class Device : public ObjectBase<Device, WGPUDevice> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        BindGroup CreateBindGroup(BindGroupDescriptor const * descriptor) const;
        BindGroupLayout CreateBindGroupLayout(BindGroupLayoutDescriptor const * descriptor) const;
        Buffer CreateBuffer(BufferDescriptor const * descriptor) const;
        CommandEncoder CreateCommandEncoder(CommandEncoderDescriptor const * descriptor = nullptr) const;
        ComputePipeline CreateComputePipeline(ComputePipelineDescriptor const * descriptor) const;
        void CreateComputePipelineAsync(ComputePipelineDescriptor const * descriptor, CreateComputePipelineAsyncCallback callback, void * userdata) const;
        Future CreateComputePipelineAsync(ComputePipelineDescriptor const * descriptor, CreateComputePipelineAsyncCallbackInfo callbackInfo) const;
        Buffer CreateErrorBuffer(BufferDescriptor const * descriptor) const;
        ExternalTexture CreateErrorExternalTexture() const;
        ShaderModule CreateErrorShaderModule(ShaderModuleDescriptor const * descriptor, char const * errorMessage) const;
        Texture CreateErrorTexture(TextureDescriptor const * descriptor) const;
        ExternalTexture CreateExternalTexture(ExternalTextureDescriptor const * externalTextureDescriptor) const;
        PipelineLayout CreatePipelineLayout(PipelineLayoutDescriptor const * descriptor) const;
        QuerySet CreateQuerySet(QuerySetDescriptor const * descriptor) const;
        RenderBundleEncoder CreateRenderBundleEncoder(RenderBundleEncoderDescriptor const * descriptor) const;
        RenderPipeline CreateRenderPipeline(RenderPipelineDescriptor const * descriptor) const;
        void CreateRenderPipelineAsync(RenderPipelineDescriptor const * descriptor, CreateRenderPipelineAsyncCallback callback, void * userdata) const;
        Future CreateRenderPipelineAsync(RenderPipelineDescriptor const * descriptor, CreateRenderPipelineAsyncCallbackInfo callbackInfo) const;
        Sampler CreateSampler(SamplerDescriptor const * descriptor = nullptr) const;
        ShaderModule CreateShaderModule(ShaderModuleDescriptor const * descriptor) const;
        SwapChain CreateSwapChain(Surface const& surface, SwapChainDescriptor const * descriptor) const;
        Texture CreateTexture(TextureDescriptor const * descriptor) const;
        void Destroy() const;
        size_t EnumerateFeatures(FeatureName * features) const;
        void ForceLoss(DeviceLostReason type, char const * message) const;
        Adapter GetAdapter() const;
        Bool GetLimits(SupportedLimits * limits) const;
        Queue GetQueue() const;
        TextureUsage GetSupportedSurfaceUsage(Surface const& surface) const;
        Bool HasFeature(FeatureName feature) const;
        SharedBufferMemory ImportSharedBufferMemory(SharedBufferMemoryDescriptor const * descriptor) const;
        SharedFence ImportSharedFence(SharedFenceDescriptor const * descriptor) const;
        SharedTextureMemory ImportSharedTextureMemory(SharedTextureMemoryDescriptor const * descriptor) const;
        void InjectError(ErrorType type, char const * message) const;
        void PopErrorScope(ErrorCallback oldCallback, void * userdata) const;
        Future PopErrorScope(PopErrorScopeCallbackInfo callbackInfo) const;
        void PushErrorScope(ErrorFilter filter) const;
        void SetDeviceLostCallback(DeviceLostCallback callback, void * userdata) const;
        void SetLabel(char const * label) const;
        void SetLoggingCallback(LoggingCallback callback, void * userdata) const;
        void SetUncapturedErrorCallback(ErrorCallback callback, void * userdata) const;
        void Tick() const;
        void ValidateTextureDescriptor(TextureDescriptor const * descriptor) const;

      private:
        friend ObjectBase<Device, WGPUDevice>;
        static void WGPUReference(WGPUDevice handle);
        static void WGPURelease(WGPUDevice handle);
    };

    class ExternalTexture : public ObjectBase<ExternalTexture, WGPUExternalTexture> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void Destroy() const;
        void Expire() const;
        void Refresh() const;
        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<ExternalTexture, WGPUExternalTexture>;
        static void WGPUReference(WGPUExternalTexture handle);
        static void WGPURelease(WGPUExternalTexture handle);
    };

    class Instance : public ObjectBase<Instance, WGPUInstance> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        Surface CreateSurface(SurfaceDescriptor const * descriptor) const;
        size_t EnumerateWGSLLanguageFeatures(WGSLFeatureName * features) const;
        Bool HasWGSLLanguageFeature(WGSLFeatureName feature) const;
        void ProcessEvents() const;
        void RequestAdapter(RequestAdapterOptions const * options, RequestAdapterCallback callback, void * userdata) const;
        Future RequestAdapter(RequestAdapterOptions const * options, RequestAdapterCallbackInfo callbackInfo) const;
        WaitStatus WaitAny(size_t futureCount, FutureWaitInfo * futures, uint64_t timeoutNS) const;

      private:
        friend ObjectBase<Instance, WGPUInstance>;
        static void WGPUReference(WGPUInstance handle);
        static void WGPURelease(WGPUInstance handle);
    };

    class PipelineLayout : public ObjectBase<PipelineLayout, WGPUPipelineLayout> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<PipelineLayout, WGPUPipelineLayout>;
        static void WGPUReference(WGPUPipelineLayout handle);
        static void WGPURelease(WGPUPipelineLayout handle);
    };

    class QuerySet : public ObjectBase<QuerySet, WGPUQuerySet> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void Destroy() const;
        uint32_t GetCount() const;
        QueryType GetType() const;
        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<QuerySet, WGPUQuerySet>;
        static void WGPUReference(WGPUQuerySet handle);
        static void WGPURelease(WGPUQuerySet handle);
    };

    class Queue : public ObjectBase<Queue, WGPUQueue> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void CopyExternalTextureForBrowser(ImageCopyExternalTexture const * source, ImageCopyTexture const * destination, Extent3D const * copySize, CopyTextureForBrowserOptions const * options) const;
        void CopyTextureForBrowser(ImageCopyTexture const * source, ImageCopyTexture const * destination, Extent3D const * copySize, CopyTextureForBrowserOptions const * options) const;
        void OnSubmittedWorkDone(QueueWorkDoneCallback callback, void * userdata) const;
        Future OnSubmittedWorkDone(QueueWorkDoneCallbackInfo callbackInfo) const;
        void SetLabel(char const * label) const;
        void Submit(size_t commandCount, CommandBuffer const * commands) const;
        void WriteBuffer(Buffer const& buffer, uint64_t bufferOffset, void const * data, size_t size) const;
        void WriteTexture(ImageCopyTexture const * destination, void const * data, size_t dataSize, TextureDataLayout const * dataLayout, Extent3D const * writeSize) const;

      private:
        friend ObjectBase<Queue, WGPUQueue>;
        static void WGPUReference(WGPUQueue handle);
        static void WGPURelease(WGPUQueue handle);
    };

    class RenderBundle : public ObjectBase<RenderBundle, WGPURenderBundle> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<RenderBundle, WGPURenderBundle>;
        static void WGPUReference(WGPURenderBundle handle);
        static void WGPURelease(WGPURenderBundle handle);
    };

    class RenderBundleEncoder : public ObjectBase<RenderBundleEncoder, WGPURenderBundleEncoder> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void Draw(uint32_t vertexCount, uint32_t instanceCount = 1, uint32_t firstVertex = 0, uint32_t firstInstance = 0) const;
        void DrawIndexed(uint32_t indexCount, uint32_t instanceCount = 1, uint32_t firstIndex = 0, int32_t baseVertex = 0, uint32_t firstInstance = 0) const;
        void DrawIndexedIndirect(Buffer const& indirectBuffer, uint64_t indirectOffset) const;
        void DrawIndirect(Buffer const& indirectBuffer, uint64_t indirectOffset) const;
        RenderBundle Finish(RenderBundleDescriptor const * descriptor = nullptr) const;
        void InsertDebugMarker(char const * markerLabel) const;
        void PopDebugGroup() const;
        void PushDebugGroup(char const * groupLabel) const;
        void SetBindGroup(uint32_t groupIndex, BindGroup const& group, size_t dynamicOffsetCount = 0, uint32_t const * dynamicOffsets = nullptr) const;
        void SetIndexBuffer(Buffer const& buffer, IndexFormat format, uint64_t offset = 0, uint64_t size = WGPU_WHOLE_SIZE) const;
        void SetLabel(char const * label) const;
        void SetPipeline(RenderPipeline const& pipeline) const;
        void SetVertexBuffer(uint32_t slot, Buffer const& buffer, uint64_t offset = 0, uint64_t size = WGPU_WHOLE_SIZE) const;

      private:
        friend ObjectBase<RenderBundleEncoder, WGPURenderBundleEncoder>;
        static void WGPUReference(WGPURenderBundleEncoder handle);
        static void WGPURelease(WGPURenderBundleEncoder handle);
    };

    class RenderPassEncoder : public ObjectBase<RenderPassEncoder, WGPURenderPassEncoder> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void BeginOcclusionQuery(uint32_t queryIndex) const;
        void Draw(uint32_t vertexCount, uint32_t instanceCount = 1, uint32_t firstVertex = 0, uint32_t firstInstance = 0) const;
        void DrawIndexed(uint32_t indexCount, uint32_t instanceCount = 1, uint32_t firstIndex = 0, int32_t baseVertex = 0, uint32_t firstInstance = 0) const;
        void DrawIndexedIndirect(Buffer const& indirectBuffer, uint64_t indirectOffset) const;
        void DrawIndirect(Buffer const& indirectBuffer, uint64_t indirectOffset) const;
        void End() const;
        void EndOcclusionQuery() const;
        void ExecuteBundles(size_t bundleCount, RenderBundle const * bundles) const;
        void InsertDebugMarker(char const * markerLabel) const;
        void PixelLocalStorageBarrier() const;
        void PopDebugGroup() const;
        void PushDebugGroup(char const * groupLabel) const;
        void SetBindGroup(uint32_t groupIndex, BindGroup const& group, size_t dynamicOffsetCount = 0, uint32_t const * dynamicOffsets = nullptr) const;
        void SetBlendConstant(Color const * color) const;
        void SetIndexBuffer(Buffer const& buffer, IndexFormat format, uint64_t offset = 0, uint64_t size = WGPU_WHOLE_SIZE) const;
        void SetLabel(char const * label) const;
        void SetPipeline(RenderPipeline const& pipeline) const;
        void SetScissorRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const;
        void SetStencilReference(uint32_t reference) const;
        void SetVertexBuffer(uint32_t slot, Buffer const& buffer, uint64_t offset = 0, uint64_t size = WGPU_WHOLE_SIZE) const;
        void SetViewport(float x, float y, float width, float height, float minDepth, float maxDepth) const;
        void WriteTimestamp(QuerySet const& querySet, uint32_t queryIndex) const;

      private:
        friend ObjectBase<RenderPassEncoder, WGPURenderPassEncoder>;
        static void WGPUReference(WGPURenderPassEncoder handle);
        static void WGPURelease(WGPURenderPassEncoder handle);
    };

    class RenderPipeline : public ObjectBase<RenderPipeline, WGPURenderPipeline> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        BindGroupLayout GetBindGroupLayout(uint32_t groupIndex) const;
        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<RenderPipeline, WGPURenderPipeline>;
        static void WGPUReference(WGPURenderPipeline handle);
        static void WGPURelease(WGPURenderPipeline handle);
    };

    class Sampler : public ObjectBase<Sampler, WGPUSampler> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<Sampler, WGPUSampler>;
        static void WGPUReference(WGPUSampler handle);
        static void WGPURelease(WGPUSampler handle);
    };

    class ShaderModule : public ObjectBase<ShaderModule, WGPUShaderModule> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void GetCompilationInfo(CompilationInfoCallback callback, void * userdata) const;
        Future GetCompilationInfo(CompilationInfoCallbackInfo callbackInfo) const;
        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<ShaderModule, WGPUShaderModule>;
        static void WGPUReference(WGPUShaderModule handle);
        static void WGPURelease(WGPUShaderModule handle);
    };

    class SharedBufferMemory : public ObjectBase<SharedBufferMemory, WGPUSharedBufferMemory> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        Bool BeginAccess(Buffer const& buffer, SharedBufferMemoryBeginAccessDescriptor const * descriptor) const;
        Buffer CreateBuffer(BufferDescriptor const * descriptor = nullptr) const;
        Bool EndAccess(Buffer const& buffer, SharedBufferMemoryEndAccessState * descriptor) const;
        void GetProperties(SharedBufferMemoryProperties * properties) const;
        Bool IsDeviceLost() const;
        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<SharedBufferMemory, WGPUSharedBufferMemory>;
        static void WGPUReference(WGPUSharedBufferMemory handle);
        static void WGPURelease(WGPUSharedBufferMemory handle);
    };

    class SharedFence : public ObjectBase<SharedFence, WGPUSharedFence> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void ExportInfo(SharedFenceExportInfo * info) const;

      private:
        friend ObjectBase<SharedFence, WGPUSharedFence>;
        static void WGPUReference(WGPUSharedFence handle);
        static void WGPURelease(WGPUSharedFence handle);
    };

    class SharedTextureMemory : public ObjectBase<SharedTextureMemory, WGPUSharedTextureMemory> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        Bool BeginAccess(Texture const& texture, SharedTextureMemoryBeginAccessDescriptor const * descriptor) const;
        Texture CreateTexture(TextureDescriptor const * descriptor = nullptr) const;
        Bool EndAccess(Texture const& texture, SharedTextureMemoryEndAccessState * descriptor) const;
        void GetProperties(SharedTextureMemoryProperties * properties) const;
        Bool IsDeviceLost() const;
        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<SharedTextureMemory, WGPUSharedTextureMemory>;
        static void WGPUReference(WGPUSharedTextureMemory handle);
        static void WGPURelease(WGPUSharedTextureMemory handle);
    };

    class Surface : public ObjectBase<Surface, WGPUSurface> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        TextureFormat GetPreferredFormat(Adapter const& adapter) const;

      private:
        friend ObjectBase<Surface, WGPUSurface>;
        static void WGPUReference(WGPUSurface handle);
        static void WGPURelease(WGPUSurface handle);
    };

    class SwapChain : public ObjectBase<SwapChain, WGPUSwapChain> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        Texture GetCurrentTexture() const;
        TextureView GetCurrentTextureView() const;
        void Present() const;

      private:
        friend ObjectBase<SwapChain, WGPUSwapChain>;
        static void WGPUReference(WGPUSwapChain handle);
        static void WGPURelease(WGPUSwapChain handle);
    };

    class Texture : public ObjectBase<Texture, WGPUTexture> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        TextureView CreateErrorView(TextureViewDescriptor const * descriptor = nullptr) const;
        TextureView CreateView(TextureViewDescriptor const * descriptor = nullptr) const;
        void Destroy() const;
        uint32_t GetDepthOrArrayLayers() const;
        TextureDimension GetDimension() const;
        TextureFormat GetFormat() const;
        uint32_t GetHeight() const;
        uint32_t GetMipLevelCount() const;
        uint32_t GetSampleCount() const;
        TextureUsage GetUsage() const;
        uint32_t GetWidth() const;
        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<Texture, WGPUTexture>;
        static void WGPUReference(WGPUTexture handle);
        static void WGPURelease(WGPUTexture handle);
    };

    class TextureView : public ObjectBase<TextureView, WGPUTextureView> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void SetLabel(char const * label) const;

      private:
        friend ObjectBase<TextureView, WGPUTextureView>;
        static void WGPUReference(WGPUTextureView handle);
        static void WGPURelease(WGPUTextureView handle);
    };


    Instance CreateInstance(InstanceDescriptor const * descriptor = nullptr);
    Bool GetInstanceFeatures(InstanceFeatures * features);
    Proc GetProcAddress(Device device, char const * procName);

    struct AdapterProperties {
        AdapterProperties() = default;
        ~AdapterProperties();
        AdapterProperties(const AdapterProperties&) = delete;
        AdapterProperties& operator=(const AdapterProperties&) = delete;
        AdapterProperties(AdapterProperties&&);
        AdapterProperties& operator=(AdapterProperties&&);
        ChainedStructOut  * nextInChain = nullptr;
        uint32_t const vendorID = {};
        char const * const vendorName = nullptr;
        char const * const architecture = nullptr;
        uint32_t const deviceID = {};
        char const * const name = nullptr;
        char const * const driverDescription = nullptr;
        AdapterType const adapterType = {};
        BackendType const backendType = {};
        Bool const compatibilityMode = false;
    };

    // Can be chained in AdapterProperties
    struct AdapterPropertiesD3D : ChainedStructOut {
        AdapterPropertiesD3D() {
            sType = SType::AdapterPropertiesD3D;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(uint32_t ));
        alignas(kFirstMemberAlignment) uint32_t shaderModel;
    };

    struct BindGroupEntry {
        ChainedStruct const * nextInChain = nullptr;
        uint32_t binding;
        Buffer buffer = nullptr;
        uint64_t offset = 0;
        uint64_t size = WGPU_WHOLE_SIZE;
        Sampler sampler = nullptr;
        TextureView textureView = nullptr;
    };

    struct BlendComponent {
        BlendOperation operation = BlendOperation::Add;
        BlendFactor srcFactor = BlendFactor::One;
        BlendFactor dstFactor = BlendFactor::Zero;
    };

    struct BufferBindingLayout {
        ChainedStruct const * nextInChain = nullptr;
        BufferBindingType type = BufferBindingType::Undefined;
        Bool hasDynamicOffset = false;
        uint64_t minBindingSize = 0;
    };

    struct BufferDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        BufferUsage usage;
        uint64_t size;
        Bool mappedAtCreation = false;
    };

    // Can be chained in BufferDescriptor
    struct BufferHostMappedPointer : ChainedStruct {
        BufferHostMappedPointer() {
            sType = SType::BufferHostMappedPointer;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * pointer;
        Callback disposeCallback;
        void * userdata;
    };

    struct BufferMapCallbackInfo {
        ChainedStruct const * nextInChain = nullptr;
        CallbackMode mode;
        BufferMapCallback callback;
        void * userdata;
    };

    struct Color {
        double r;
        double g;
        double b;
        double a;
    };

    struct CommandBufferDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct CommandEncoderDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct CompilationInfoCallbackInfo {
        ChainedStruct const * nextInChain = nullptr;
        CallbackMode mode;
        CompilationInfoCallback callback;
        void * userdata = nullptr;
    };

    struct CompilationMessage {
        ChainedStruct const * nextInChain = nullptr;
        char const * message = nullptr;
        CompilationMessageType type;
        uint64_t lineNum;
        uint64_t linePos;
        uint64_t offset;
        uint64_t length;
        uint64_t utf16LinePos;
        uint64_t utf16Offset;
        uint64_t utf16Length;
    };

    struct ComputePassTimestampWrites {
        QuerySet querySet;
        uint32_t beginningOfPassWriteIndex = WGPU_QUERY_SET_INDEX_UNDEFINED;
        uint32_t endOfPassWriteIndex = WGPU_QUERY_SET_INDEX_UNDEFINED;
    };

    struct ConstantEntry {
        ChainedStruct const * nextInChain = nullptr;
        char const * key;
        double value;
    };

    struct CopyTextureForBrowserOptions {
        ChainedStruct const * nextInChain = nullptr;
        Bool flipY = false;
        Bool needsColorSpaceConversion = false;
        AlphaMode srcAlphaMode = AlphaMode::Unpremultiplied;
        float const * srcTransferFunctionParameters = nullptr;
        float const * conversionMatrix = nullptr;
        float const * dstTransferFunctionParameters = nullptr;
        AlphaMode dstAlphaMode = AlphaMode::Unpremultiplied;
        Bool internalUsage = false;
    };

    struct CreateComputePipelineAsyncCallbackInfo {
        ChainedStruct const * nextInChain = nullptr;
        CallbackMode mode;
        CreateComputePipelineAsyncCallback callback;
        void * userdata;
    };

    struct CreateRenderPipelineAsyncCallbackInfo {
        ChainedStruct const * nextInChain = nullptr;
        CallbackMode mode;
        CreateRenderPipelineAsyncCallback callback;
        void * userdata;
    };

    // Can be chained in InstanceDescriptor
    struct DawnWGSLBlocklist : ChainedStruct {
        DawnWGSLBlocklist() {
            sType = SType::DawnWGSLBlocklist;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(size_t ));
        alignas(kFirstMemberAlignment) size_t blocklistedFeatureCount = 0;
        const char* const * blocklistedFeatures;
    };

    // Can be chained in AdapterProperties
    struct DawnAdapterPropertiesPowerPreference : ChainedStructOut {
        DawnAdapterPropertiesPowerPreference() {
            sType = SType::DawnAdapterPropertiesPowerPreference;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(PowerPreference ));
        alignas(kFirstMemberAlignment) PowerPreference powerPreference = PowerPreference::Undefined;
    };

    // Can be chained in BufferDescriptor
    struct DawnBufferDescriptorErrorInfoFromWireClient : ChainedStruct {
        DawnBufferDescriptorErrorInfoFromWireClient() {
            sType = SType::DawnBufferDescriptorErrorInfoFromWireClient;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(Bool ));
        alignas(kFirstMemberAlignment) Bool outOfMemory = false;
    };

    // Can be chained in DeviceDescriptor
    struct DawnCacheDeviceDescriptor : ChainedStruct {
        DawnCacheDeviceDescriptor() {
            sType = SType::DawnCacheDeviceDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(char const * ));
        alignas(kFirstMemberAlignment) char const * isolationKey = "";
        DawnLoadCacheDataFunction loadDataFunction = nullptr;
        DawnStoreCacheDataFunction storeDataFunction = nullptr;
        void * functionUserdata = nullptr;
    };

    // Can be chained in ComputePipelineDescriptor
    struct DawnComputePipelineFullSubgroups : ChainedStruct {
        DawnComputePipelineFullSubgroups() {
            sType = SType::DawnComputePipelineFullSubgroups;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(Bool ));
        alignas(kFirstMemberAlignment) Bool requiresFullSubgroups = false;
    };

    // Can be chained in CommandEncoderDescriptor
    struct DawnEncoderInternalUsageDescriptor : ChainedStruct {
        DawnEncoderInternalUsageDescriptor() {
            sType = SType::DawnEncoderInternalUsageDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(Bool ));
        alignas(kFirstMemberAlignment) Bool useInternalUsages = false;
    };

    // Can be chained in SupportedLimits
    struct DawnExperimentalSubgroupLimits : ChainedStructOut {
        DawnExperimentalSubgroupLimits() {
            sType = SType::DawnExperimentalSubgroupLimits;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(uint32_t ));
        alignas(kFirstMemberAlignment) uint32_t minSubgroupSize = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxSubgroupSize = WGPU_LIMIT_U32_UNDEFINED;
    };

    // Can be chained in MultisampleState
    struct DawnMultisampleStateRenderToSingleSampled : ChainedStruct {
        DawnMultisampleStateRenderToSingleSampled() {
            sType = SType::DawnMultisampleStateRenderToSingleSampled;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(Bool ));
        alignas(kFirstMemberAlignment) Bool enabled = false;
    };

    // Can be chained in RenderPassColorAttachment
    struct DawnRenderPassColorAttachmentRenderToSingleSampled : ChainedStruct {
        DawnRenderPassColorAttachmentRenderToSingleSampled() {
            sType = SType::DawnRenderPassColorAttachmentRenderToSingleSampled;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(uint32_t ));
        alignas(kFirstMemberAlignment) uint32_t implicitSampleCount = 1;
    };

    // Can be chained in ShaderModuleDescriptor
    struct DawnShaderModuleSPIRVOptionsDescriptor : ChainedStruct {
        DawnShaderModuleSPIRVOptionsDescriptor() {
            sType = SType::DawnShaderModuleSPIRVOptionsDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(Bool ));
        alignas(kFirstMemberAlignment) Bool allowNonUniformDerivatives = false;
    };

    // Can be chained in TextureDescriptor
    struct DawnTextureInternalUsageDescriptor : ChainedStruct {
        DawnTextureInternalUsageDescriptor() {
            sType = SType::DawnTextureInternalUsageDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(TextureUsage ));
        alignas(kFirstMemberAlignment) TextureUsage internalUsage = TextureUsage::None;
    };

    // Can be chained in InstanceDescriptor
    // Can be chained in RequestAdapterOptions
    // Can be chained in DeviceDescriptor
    struct DawnTogglesDescriptor : ChainedStruct {
        DawnTogglesDescriptor() {
            sType = SType::DawnTogglesDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(size_t ));
        alignas(kFirstMemberAlignment) size_t enabledToggleCount = 0;
        const char* const * enabledToggles;
        size_t disabledToggleCount = 0;
        const char* const * disabledToggles;
    };

    // Can be chained in InstanceDescriptor
    struct DawnWireWGSLControl : ChainedStruct {
        DawnWireWGSLControl() {
            sType = SType::DawnWireWGSLControl;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(Bool ));
        alignas(kFirstMemberAlignment) Bool enableExperimental = false;
        Bool enableUnsafe = false;
        Bool enableTesting = false;
    };

    // Can be chained in DepthStencilState
    struct DepthStencilStateDepthWriteDefinedDawn : ChainedStruct {
        DepthStencilStateDepthWriteDefinedDawn() {
            sType = SType::DepthStencilStateDepthWriteDefinedDawn;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(Bool ));
        alignas(kFirstMemberAlignment) Bool depthWriteDefined;
    };

    struct Extent2D {
        uint32_t width;
        uint32_t height;
    };

    struct Extent3D {
        uint32_t width;
        uint32_t height = 1;
        uint32_t depthOrArrayLayers = 1;
    };

    // Can be chained in BindGroupEntry
    struct ExternalTextureBindingEntry : ChainedStruct {
        ExternalTextureBindingEntry() {
            sType = SType::ExternalTextureBindingEntry;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(ExternalTexture ));
        alignas(kFirstMemberAlignment) ExternalTexture externalTexture;
    };

    // Can be chained in BindGroupLayoutEntry
    struct ExternalTextureBindingLayout : ChainedStruct {
        ExternalTextureBindingLayout() {
            sType = SType::ExternalTextureBindingLayout;
        }
    };

    struct Future {
        uint64_t id;
    };

    struct InstanceFeatures {
        ChainedStruct const * nextInChain = nullptr;
        Bool timedWaitAnyEnable = false;
        size_t timedWaitAnyMaxCount = 0;
    };

    struct Limits {
        uint32_t maxTextureDimension1D = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxTextureDimension2D = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxTextureDimension3D = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxTextureArrayLayers = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxBindGroups = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxBindGroupsPlusVertexBuffers = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxBindingsPerBindGroup = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxDynamicUniformBuffersPerPipelineLayout = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxDynamicStorageBuffersPerPipelineLayout = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxSampledTexturesPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxSamplersPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxStorageBuffersPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxStorageTexturesPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxUniformBuffersPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
        uint64_t maxUniformBufferBindingSize = WGPU_LIMIT_U64_UNDEFINED;
        uint64_t maxStorageBufferBindingSize = WGPU_LIMIT_U64_UNDEFINED;
        uint32_t minUniformBufferOffsetAlignment = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t minStorageBufferOffsetAlignment = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxVertexBuffers = WGPU_LIMIT_U32_UNDEFINED;
        uint64_t maxBufferSize = WGPU_LIMIT_U64_UNDEFINED;
        uint32_t maxVertexAttributes = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxVertexBufferArrayStride = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxInterStageShaderComponents = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxInterStageShaderVariables = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxColorAttachments = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxColorAttachmentBytesPerSample = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxComputeWorkgroupStorageSize = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxComputeInvocationsPerWorkgroup = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxComputeWorkgroupSizeX = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxComputeWorkgroupSizeY = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxComputeWorkgroupSizeZ = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxComputeWorkgroupsPerDimension = WGPU_LIMIT_U32_UNDEFINED;
    };

    struct MemoryHeapInfo {
        HeapProperty properties;
        uint64_t size;
    };

    struct MultisampleState {
        ChainedStruct const * nextInChain = nullptr;
        uint32_t count = 1;
        uint32_t mask = 0xFFFFFFFF;
        Bool alphaToCoverageEnabled = false;
    };

    struct Origin2D {
        uint32_t x = 0;
        uint32_t y = 0;
    };

    struct Origin3D {
        uint32_t x = 0;
        uint32_t y = 0;
        uint32_t z = 0;
    };

    struct PipelineLayoutDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        size_t bindGroupLayoutCount;
        BindGroupLayout const * bindGroupLayouts;
    };

    struct PipelineLayoutStorageAttachment {
        ChainedStruct const * nextInChain = nullptr;
        uint64_t offset = 0;
        TextureFormat format;
    };

    struct PopErrorScopeCallbackInfo {
        ChainedStruct const * nextInChain = nullptr;
        CallbackMode mode;
        PopErrorScopeCallback callback;
        ErrorCallback oldCallback;
        void * userdata = nullptr;
    };

    // Can be chained in PrimitiveState
    struct PrimitiveDepthClipControl : ChainedStruct {
        PrimitiveDepthClipControl() {
            sType = SType::PrimitiveDepthClipControl;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(Bool ));
        alignas(kFirstMemberAlignment) Bool unclippedDepth = false;
    };

    struct PrimitiveState {
        ChainedStruct const * nextInChain = nullptr;
        PrimitiveTopology topology = PrimitiveTopology::TriangleList;
        IndexFormat stripIndexFormat = IndexFormat::Undefined;
        FrontFace frontFace = FrontFace::CCW;
        CullMode cullMode = CullMode::None;
    };

    struct QuerySetDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        QueryType type;
        uint32_t count;
    };

    struct QueueDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct QueueWorkDoneCallbackInfo {
        ChainedStruct const * nextInChain = nullptr;
        CallbackMode mode;
        QueueWorkDoneCallback callback;
        void * userdata;
    };

    struct RenderBundleDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct RenderBundleEncoderDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        size_t colorFormatCount;
        TextureFormat const * colorFormats;
        TextureFormat depthStencilFormat = TextureFormat::Undefined;
        uint32_t sampleCount = 1;
        Bool depthReadOnly = false;
        Bool stencilReadOnly = false;
    };

    struct RenderPassDepthStencilAttachment {
        TextureView view;
        LoadOp depthLoadOp = LoadOp::Undefined;
        StoreOp depthStoreOp = StoreOp::Undefined;
        float depthClearValue = NAN;
        Bool depthReadOnly = false;
        LoadOp stencilLoadOp = LoadOp::Undefined;
        StoreOp stencilStoreOp = StoreOp::Undefined;
        uint32_t stencilClearValue = 0;
        Bool stencilReadOnly = false;
    };

    // Can be chained in RenderPassDescriptor
    struct RenderPassDescriptorMaxDrawCount : ChainedStruct {
        RenderPassDescriptorMaxDrawCount() {
            sType = SType::RenderPassDescriptorMaxDrawCount;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(uint64_t ));
        alignas(kFirstMemberAlignment) uint64_t maxDrawCount = 50000000;
    };

    struct RenderPassTimestampWrites {
        QuerySet querySet;
        uint32_t beginningOfPassWriteIndex = WGPU_QUERY_SET_INDEX_UNDEFINED;
        uint32_t endOfPassWriteIndex = WGPU_QUERY_SET_INDEX_UNDEFINED;
    };

    struct RequestAdapterCallbackInfo {
        ChainedStruct const * nextInChain = nullptr;
        CallbackMode mode;
        RequestAdapterCallback callback;
        void * userdata;
    };

    struct RequestAdapterOptions {
        ChainedStruct const * nextInChain = nullptr;
        Surface compatibleSurface = nullptr;
        PowerPreference powerPreference = PowerPreference::Undefined;
        BackendType backendType = BackendType::Undefined;
        Bool forceFallbackAdapter = false;
        Bool compatibilityMode = false;
    };

    struct RequestDeviceCallbackInfo {
        ChainedStruct const * nextInChain = nullptr;
        CallbackMode mode;
        RequestDeviceCallback callback;
        void * userdata;
    };

    struct SamplerBindingLayout {
        ChainedStruct const * nextInChain = nullptr;
        SamplerBindingType type = SamplerBindingType::Undefined;
    };

    struct SamplerDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        AddressMode addressModeU = AddressMode::ClampToEdge;
        AddressMode addressModeV = AddressMode::ClampToEdge;
        AddressMode addressModeW = AddressMode::ClampToEdge;
        FilterMode magFilter = FilterMode::Nearest;
        FilterMode minFilter = FilterMode::Nearest;
        MipmapFilterMode mipmapFilter = MipmapFilterMode::Nearest;
        float lodMinClamp = 0.0f;
        float lodMaxClamp = 32.0f;
        CompareFunction compare = CompareFunction::Undefined;
        uint16_t maxAnisotropy = 1;
    };

    // Can be chained in ShaderModuleDescriptor
    struct ShaderModuleSPIRVDescriptor : ChainedStruct {
        ShaderModuleSPIRVDescriptor() {
            sType = SType::ShaderModuleSPIRVDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(uint32_t ));
        alignas(kFirstMemberAlignment) uint32_t codeSize;
        uint32_t const * code;
    };

    // Can be chained in ShaderModuleDescriptor
    struct ShaderModuleWGSLDescriptor : ChainedStruct {
        ShaderModuleWGSLDescriptor() {
            sType = SType::ShaderModuleWGSLDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(char const * ));
        alignas(kFirstMemberAlignment) char const * code;
    };

    struct ShaderModuleDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct SharedBufferMemoryBeginAccessDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        Bool initialized;
        size_t fenceCount;
        SharedFence const * fences;
        uint64_t const * signaledValues;
    };

    struct SharedBufferMemoryDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct SharedBufferMemoryEndAccessState {
        SharedBufferMemoryEndAccessState() = default;
        ~SharedBufferMemoryEndAccessState();
        SharedBufferMemoryEndAccessState(const SharedBufferMemoryEndAccessState&) = delete;
        SharedBufferMemoryEndAccessState& operator=(const SharedBufferMemoryEndAccessState&) = delete;
        SharedBufferMemoryEndAccessState(SharedBufferMemoryEndAccessState&&);
        SharedBufferMemoryEndAccessState& operator=(SharedBufferMemoryEndAccessState&&);
        ChainedStructOut  * nextInChain = nullptr;
        Bool const initialized = {};
        size_t const fenceCount = {};
        SharedFence const * const fences = {};
        uint64_t const * const signaledValues = {};
    };

    struct SharedBufferMemoryProperties {
        ChainedStructOut  * nextInChain = nullptr;
        BufferUsage usage;
        uint64_t size;
    };

    // Can be chained in SharedFenceDescriptor
    struct SharedFenceDXGISharedHandleDescriptor : ChainedStruct {
        SharedFenceDXGISharedHandleDescriptor() {
            sType = SType::SharedFenceDXGISharedHandleDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * handle;
    };

    // Can be chained in SharedFenceExportInfo
    struct SharedFenceDXGISharedHandleExportInfo : ChainedStructOut {
        SharedFenceDXGISharedHandleExportInfo() {
            sType = SType::SharedFenceDXGISharedHandleExportInfo;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * handle;
    };

    // Can be chained in SharedFenceDescriptor
    struct SharedFenceMTLSharedEventDescriptor : ChainedStruct {
        SharedFenceMTLSharedEventDescriptor() {
            sType = SType::SharedFenceMTLSharedEventDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * sharedEvent;
    };

    // Can be chained in SharedFenceExportInfo
    struct SharedFenceMTLSharedEventExportInfo : ChainedStructOut {
        SharedFenceMTLSharedEventExportInfo() {
            sType = SType::SharedFenceMTLSharedEventExportInfo;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * sharedEvent;
    };

    struct SharedFenceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct SharedFenceExportInfo {
        ChainedStructOut  * nextInChain = nullptr;
        SharedFenceType type;
    };

    // Can be chained in SharedFenceDescriptor
    struct SharedFenceVkSemaphoreOpaqueFDDescriptor : ChainedStruct {
        SharedFenceVkSemaphoreOpaqueFDDescriptor() {
            sType = SType::SharedFenceVkSemaphoreOpaqueFDDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(int ));
        alignas(kFirstMemberAlignment) int handle;
    };

    // Can be chained in SharedFenceExportInfo
    struct SharedFenceVkSemaphoreOpaqueFDExportInfo : ChainedStructOut {
        SharedFenceVkSemaphoreOpaqueFDExportInfo() {
            sType = SType::SharedFenceVkSemaphoreOpaqueFDExportInfo;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(int ));
        alignas(kFirstMemberAlignment) int handle;
    };

    // Can be chained in SharedFenceDescriptor
    struct SharedFenceVkSemaphoreSyncFDDescriptor : ChainedStruct {
        SharedFenceVkSemaphoreSyncFDDescriptor() {
            sType = SType::SharedFenceVkSemaphoreSyncFDDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(int ));
        alignas(kFirstMemberAlignment) int handle;
    };

    // Can be chained in SharedFenceExportInfo
    struct SharedFenceVkSemaphoreSyncFDExportInfo : ChainedStructOut {
        SharedFenceVkSemaphoreSyncFDExportInfo() {
            sType = SType::SharedFenceVkSemaphoreSyncFDExportInfo;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(int ));
        alignas(kFirstMemberAlignment) int handle;
    };

    // Can be chained in SharedFenceDescriptor
    struct SharedFenceVkSemaphoreZirconHandleDescriptor : ChainedStruct {
        SharedFenceVkSemaphoreZirconHandleDescriptor() {
            sType = SType::SharedFenceVkSemaphoreZirconHandleDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(uint32_t ));
        alignas(kFirstMemberAlignment) uint32_t handle;
    };

    // Can be chained in SharedFenceExportInfo
    struct SharedFenceVkSemaphoreZirconHandleExportInfo : ChainedStructOut {
        SharedFenceVkSemaphoreZirconHandleExportInfo() {
            sType = SType::SharedFenceVkSemaphoreZirconHandleExportInfo;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(uint32_t ));
        alignas(kFirstMemberAlignment) uint32_t handle;
    };

    // Can be chained in SharedTextureMemoryDescriptor
    struct SharedTextureMemoryDXGISharedHandleDescriptor : ChainedStruct {
        SharedTextureMemoryDXGISharedHandleDescriptor() {
            sType = SType::SharedTextureMemoryDXGISharedHandleDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * handle;
        Bool useKeyedMutex;
    };

    // Can be chained in SharedTextureMemoryDescriptor
    struct SharedTextureMemoryEGLImageDescriptor : ChainedStruct {
        SharedTextureMemoryEGLImageDescriptor() {
            sType = SType::SharedTextureMemoryEGLImageDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * image;
    };

    // Can be chained in SharedTextureMemoryDescriptor
    struct SharedTextureMemoryIOSurfaceDescriptor : ChainedStruct {
        SharedTextureMemoryIOSurfaceDescriptor() {
            sType = SType::SharedTextureMemoryIOSurfaceDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * ioSurface;
    };

    // Can be chained in SharedTextureMemoryDescriptor
    struct SharedTextureMemoryAHardwareBufferDescriptor : ChainedStruct {
        SharedTextureMemoryAHardwareBufferDescriptor() {
            sType = SType::SharedTextureMemoryAHardwareBufferDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * handle;
    };

    struct SharedTextureMemoryBeginAccessDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        Bool concurrentRead;
        Bool initialized;
        size_t fenceCount;
        SharedFence const * fences;
        uint64_t const * signaledValues;
    };

    struct SharedTextureMemoryDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    struct SharedTextureMemoryDmaBufPlane {
        int fd;
        uint64_t offset;
        uint32_t stride;
    };

    struct SharedTextureMemoryEndAccessState {
        SharedTextureMemoryEndAccessState() = default;
        ~SharedTextureMemoryEndAccessState();
        SharedTextureMemoryEndAccessState(const SharedTextureMemoryEndAccessState&) = delete;
        SharedTextureMemoryEndAccessState& operator=(const SharedTextureMemoryEndAccessState&) = delete;
        SharedTextureMemoryEndAccessState(SharedTextureMemoryEndAccessState&&);
        SharedTextureMemoryEndAccessState& operator=(SharedTextureMemoryEndAccessState&&);
        ChainedStructOut  * nextInChain = nullptr;
        Bool const initialized = {};
        size_t const fenceCount = {};
        SharedFence const * const fences = {};
        uint64_t const * const signaledValues = {};
    };

    // Can be chained in SharedTextureMemoryDescriptor
    struct SharedTextureMemoryOpaqueFDDescriptor : ChainedStruct {
        SharedTextureMemoryOpaqueFDDescriptor() {
            sType = SType::SharedTextureMemoryOpaqueFDDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void const * ));
        alignas(kFirstMemberAlignment) void const * vkImageCreateInfo;
        int memoryFD;
        uint32_t memoryTypeIndex;
        uint64_t allocationSize;
        Bool dedicatedAllocation;
    };

    // Can be chained in SharedTextureMemoryDescriptor
    struct SharedTextureMemoryVkDedicatedAllocationDescriptor : ChainedStruct {
        SharedTextureMemoryVkDedicatedAllocationDescriptor() {
            sType = SType::SharedTextureMemoryVkDedicatedAllocationDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(Bool ));
        alignas(kFirstMemberAlignment) Bool dedicatedAllocation;
    };

    // Can be chained in SharedTextureMemoryBeginAccessDescriptor
    struct SharedTextureMemoryVkImageLayoutBeginState : ChainedStruct {
        SharedTextureMemoryVkImageLayoutBeginState() {
            sType = SType::SharedTextureMemoryVkImageLayoutBeginState;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(int32_t ));
        alignas(kFirstMemberAlignment) int32_t oldLayout;
        int32_t newLayout;
    };

    // Can be chained in SharedTextureMemoryEndAccessState
    struct SharedTextureMemoryVkImageLayoutEndState : ChainedStructOut {
        SharedTextureMemoryVkImageLayoutEndState() {
            sType = SType::SharedTextureMemoryVkImageLayoutEndState;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(int32_t ));
        alignas(kFirstMemberAlignment) int32_t oldLayout;
        int32_t newLayout;
    };

    // Can be chained in SharedTextureMemoryDescriptor
    struct SharedTextureMemoryZirconHandleDescriptor : ChainedStruct {
        SharedTextureMemoryZirconHandleDescriptor() {
            sType = SType::SharedTextureMemoryZirconHandleDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(uint32_t ));
        alignas(kFirstMemberAlignment) uint32_t memoryFD;
        uint64_t allocationSize;
    };

    struct StencilFaceState {
        CompareFunction compare = CompareFunction::Always;
        StencilOperation failOp = StencilOperation::Keep;
        StencilOperation depthFailOp = StencilOperation::Keep;
        StencilOperation passOp = StencilOperation::Keep;
    };

    struct StorageTextureBindingLayout {
        ChainedStruct const * nextInChain = nullptr;
        StorageTextureAccess access = StorageTextureAccess::Undefined;
        TextureFormat format = TextureFormat::Undefined;
        TextureViewDimension viewDimension = TextureViewDimension::e2D;
    };

    struct SurfaceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
    };

    // Can be chained in SurfaceDescriptor
    struct SurfaceDescriptorFromAndroidNativeWindow : ChainedStruct {
        SurfaceDescriptorFromAndroidNativeWindow() {
            sType = SType::SurfaceDescriptorFromAndroidNativeWindow;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * window;
    };

    // Can be chained in SurfaceDescriptor
    struct SurfaceDescriptorFromCanvasHTMLSelector : ChainedStruct {
        SurfaceDescriptorFromCanvasHTMLSelector() {
            sType = SType::SurfaceDescriptorFromCanvasHTMLSelector;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(char const * ));
        alignas(kFirstMemberAlignment) char const * selector;
    };

    // Can be chained in SurfaceDescriptor
    struct SurfaceDescriptorFromMetalLayer : ChainedStruct {
        SurfaceDescriptorFromMetalLayer() {
            sType = SType::SurfaceDescriptorFromMetalLayer;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * layer;
    };

    // Can be chained in SurfaceDescriptor
    struct SurfaceDescriptorFromWaylandSurface : ChainedStruct {
        SurfaceDescriptorFromWaylandSurface() {
            sType = SType::SurfaceDescriptorFromWaylandSurface;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * display;
        void * surface;
    };

    // Can be chained in SurfaceDescriptor
    struct SurfaceDescriptorFromWindowsHWND : ChainedStruct {
        SurfaceDescriptorFromWindowsHWND() {
            sType = SType::SurfaceDescriptorFromWindowsHWND;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * hinstance;
        void * hwnd;
    };

    // Can be chained in SurfaceDescriptor
    struct SurfaceDescriptorFromWindowsCoreWindow : ChainedStruct {
        SurfaceDescriptorFromWindowsCoreWindow() {
            sType = SType::SurfaceDescriptorFromWindowsCoreWindow;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * coreWindow;
    };

    // Can be chained in SurfaceDescriptor
    struct SurfaceDescriptorFromWindowsSwapChainPanel : ChainedStruct {
        SurfaceDescriptorFromWindowsSwapChainPanel() {
            sType = SType::SurfaceDescriptorFromWindowsSwapChainPanel;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * swapChainPanel;
    };

    // Can be chained in SurfaceDescriptor
    struct SurfaceDescriptorFromXlibWindow : ChainedStruct {
        SurfaceDescriptorFromXlibWindow() {
            sType = SType::SurfaceDescriptorFromXlibWindow;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(void * ));
        alignas(kFirstMemberAlignment) void * display;
        uint64_t window;
    };

    struct SwapChainDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        TextureUsage usage;
        TextureFormat format;
        uint32_t width;
        uint32_t height;
        PresentMode presentMode;
    };

    struct TextureBindingLayout {
        ChainedStruct const * nextInChain = nullptr;
        TextureSampleType sampleType = TextureSampleType::Undefined;
        TextureViewDimension viewDimension = TextureViewDimension::e2D;
        Bool multisampled = false;
    };

    // Can be chained in TextureDescriptor
    struct TextureBindingViewDimensionDescriptor : ChainedStruct {
        TextureBindingViewDimensionDescriptor() {
            sType = SType::TextureBindingViewDimensionDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(TextureViewDimension ));
        alignas(kFirstMemberAlignment) TextureViewDimension textureBindingViewDimension = TextureViewDimension::Undefined;
    };

    struct TextureDataLayout {
        ChainedStruct const * nextInChain = nullptr;
        uint64_t offset = 0;
        uint32_t bytesPerRow = WGPU_COPY_STRIDE_UNDEFINED;
        uint32_t rowsPerImage = WGPU_COPY_STRIDE_UNDEFINED;
    };

    struct TextureViewDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        TextureFormat format = TextureFormat::Undefined;
        TextureViewDimension dimension = TextureViewDimension::Undefined;
        uint32_t baseMipLevel = 0;
        uint32_t mipLevelCount = WGPU_MIP_LEVEL_COUNT_UNDEFINED;
        uint32_t baseArrayLayer = 0;
        uint32_t arrayLayerCount = WGPU_ARRAY_LAYER_COUNT_UNDEFINED;
        TextureAspect aspect = TextureAspect::All;
    };

    struct VertexAttribute {
        VertexFormat format;
        uint64_t offset;
        uint32_t shaderLocation;
    };

    // Can be chained in AdapterProperties
    struct AdapterPropertiesMemoryHeaps : ChainedStructOut {
        AdapterPropertiesMemoryHeaps() {
            sType = SType::AdapterPropertiesMemoryHeaps;
        }
        ~AdapterPropertiesMemoryHeaps();
        AdapterPropertiesMemoryHeaps(const AdapterPropertiesMemoryHeaps&) = delete;
        AdapterPropertiesMemoryHeaps& operator=(const AdapterPropertiesMemoryHeaps&) = delete;
        AdapterPropertiesMemoryHeaps(AdapterPropertiesMemoryHeaps&&);
        AdapterPropertiesMemoryHeaps& operator=(AdapterPropertiesMemoryHeaps&&);
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(size_t ));
        alignas(kFirstMemberAlignment) size_t const heapCount = {};
        MemoryHeapInfo const * const heapInfo = {};
    };

    struct BindGroupDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        BindGroupLayout layout;
        size_t entryCount;
        BindGroupEntry const * entries;
    };

    struct BindGroupLayoutEntry {
        ChainedStruct const * nextInChain = nullptr;
        uint32_t binding;
        ShaderStage visibility;
        BufferBindingLayout buffer;
        SamplerBindingLayout sampler;
        TextureBindingLayout texture;
        StorageTextureBindingLayout storageTexture;
    };

    struct BlendState {
        BlendComponent color;
        BlendComponent alpha;
    };

    struct CompilationInfo {
        ChainedStruct const * nextInChain = nullptr;
        size_t messageCount;
        CompilationMessage const * messages;
    };

    struct ComputePassDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        ComputePassTimestampWrites const * timestampWrites = nullptr;
    };

    struct DepthStencilState {
        ChainedStruct const * nextInChain = nullptr;
        TextureFormat format;
        Bool depthWriteEnabled = false;
        CompareFunction depthCompare = CompareFunction::Undefined;
        StencilFaceState stencilFront;
        StencilFaceState stencilBack;
        uint32_t stencilReadMask = 0xFFFFFFFF;
        uint32_t stencilWriteMask = 0xFFFFFFFF;
        int32_t depthBias = 0;
        float depthBiasSlopeScale = 0.0f;
        float depthBiasClamp = 0.0f;
    };

    struct ExternalTextureDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        TextureView plane0;
        TextureView plane1 = nullptr;
        Origin2D visibleOrigin;
        Extent2D visibleSize;
        Bool doYuvToRgbConversionOnly = false;
        float const * yuvToRgbConversionMatrix = nullptr;
        float const * srcTransferFunctionParameters;
        float const * dstTransferFunctionParameters;
        float const * gamutConversionMatrix;
        Bool flipY = false;
        Bool mirrored = false;
        ExternalTextureRotation rotation = ExternalTextureRotation::Rotate0Degrees;
    };

    struct FutureWaitInfo {
        Future future;
        Bool completed = false;
    };

    struct ImageCopyBuffer {
        ChainedStruct const * nextInChain = nullptr;
        TextureDataLayout layout;
        Buffer buffer;
    };

    struct ImageCopyExternalTexture {
        ChainedStruct const * nextInChain = nullptr;
        ExternalTexture externalTexture;
        Origin3D origin;
        Extent2D naturalSize;
    };

    struct ImageCopyTexture {
        ChainedStruct const * nextInChain = nullptr;
        Texture texture;
        uint32_t mipLevel = 0;
        Origin3D origin;
        TextureAspect aspect = TextureAspect::All;
    };

    struct InstanceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        InstanceFeatures features;
    };

    // Can be chained in PipelineLayoutDescriptor
    struct PipelineLayoutPixelLocalStorage : ChainedStruct {
        PipelineLayoutPixelLocalStorage() {
            sType = SType::PipelineLayoutPixelLocalStorage;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(uint64_t ));
        alignas(kFirstMemberAlignment) uint64_t totalPixelLocalStorageSize;
        size_t storageAttachmentCount = 0;
        PipelineLayoutStorageAttachment const * storageAttachments;
    };

    struct ProgrammableStageDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        ShaderModule module;
        char const * entryPoint = nullptr;
        size_t constantCount = 0;
        ConstantEntry const * constants;
    };

    struct RenderPassColorAttachment {
        ChainedStruct const * nextInChain = nullptr;
        TextureView view = nullptr;
        uint32_t depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
        TextureView resolveTarget = nullptr;
        LoadOp loadOp;
        StoreOp storeOp;
        Color clearValue;
    };

    struct RenderPassStorageAttachment {
        ChainedStruct const * nextInChain = nullptr;
        uint64_t offset = 0;
        TextureView storage;
        LoadOp loadOp;
        StoreOp storeOp;
        Color clearValue;
    };

    struct RequiredLimits {
        ChainedStruct const * nextInChain = nullptr;
        Limits limits;
    };

    // Can be chained in SharedTextureMemoryDescriptor
    struct SharedTextureMemoryDmaBufDescriptor : ChainedStruct {
        SharedTextureMemoryDmaBufDescriptor() {
            sType = SType::SharedTextureMemoryDmaBufDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(Extent3D ));
        alignas(kFirstMemberAlignment) Extent3D size;
        uint32_t drmFormat;
        uint64_t drmModifier;
        size_t planeCount;
        SharedTextureMemoryDmaBufPlane const * planes;
    };

    struct SharedTextureMemoryProperties {
        ChainedStructOut  * nextInChain = nullptr;
        TextureUsage usage;
        Extent3D size;
        TextureFormat format;
    };

    // Can be chained in SharedTextureMemoryDescriptor
    struct SharedTextureMemoryVkImageDescriptor : ChainedStruct {
        SharedTextureMemoryVkImageDescriptor() {
            sType = SType::SharedTextureMemoryVkImageDescriptor;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(int32_t ));
        alignas(kFirstMemberAlignment) int32_t vkFormat;
        int32_t vkUsageFlags;
        Extent3D vkExtent3D;
    };

    struct SupportedLimits {
        ChainedStructOut  * nextInChain = nullptr;
        Limits limits;
    };

    struct TextureDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        TextureUsage usage;
        TextureDimension dimension = TextureDimension::e2D;
        Extent3D size;
        TextureFormat format;
        uint32_t mipLevelCount = 1;
        uint32_t sampleCount = 1;
        size_t viewFormatCount = 0;
        TextureFormat const * viewFormats;
    };

    struct VertexBufferLayout {
        uint64_t arrayStride;
        VertexStepMode stepMode = VertexStepMode::Vertex;
        size_t attributeCount;
        VertexAttribute const * attributes;
    };

    struct BindGroupLayoutDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        size_t entryCount;
        BindGroupLayoutEntry const * entries;
    };

    struct ColorTargetState {
        ChainedStruct const * nextInChain = nullptr;
        TextureFormat format;
        BlendState const * blend = nullptr;
        ColorWriteMask writeMask = ColorWriteMask::All;
    };

    struct ComputePipelineDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        PipelineLayout layout = nullptr;
        ProgrammableStageDescriptor compute;
    };

    struct DeviceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        size_t requiredFeatureCount = 0;
        FeatureName const * requiredFeatures = nullptr;
        RequiredLimits const * requiredLimits = nullptr;
        QueueDescriptor defaultQueue;
        DeviceLostCallback deviceLostCallback = nullptr;
        void * deviceLostUserdata = nullptr;
    };

    struct RenderPassDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        size_t colorAttachmentCount;
        RenderPassColorAttachment const * colorAttachments;
        RenderPassDepthStencilAttachment const * depthStencilAttachment = nullptr;
        QuerySet occlusionQuerySet = nullptr;
        RenderPassTimestampWrites const * timestampWrites = nullptr;
    };

    // Can be chained in RenderPassDescriptor
    struct RenderPassPixelLocalStorage : ChainedStruct {
        RenderPassPixelLocalStorage() {
            sType = SType::RenderPassPixelLocalStorage;
        }
        static constexpr size_t kFirstMemberAlignment = detail::ConstexprMax(alignof(ChainedStruct), alignof(uint64_t ));
        alignas(kFirstMemberAlignment) uint64_t totalPixelLocalStorageSize;
        size_t storageAttachmentCount = 0;
        RenderPassStorageAttachment const * storageAttachments;
    };

    struct VertexState {
        ChainedStruct const * nextInChain = nullptr;
        ShaderModule module;
        char const * entryPoint = nullptr;
        size_t constantCount = 0;
        ConstantEntry const * constants;
        size_t bufferCount = 0;
        VertexBufferLayout const * buffers;
    };

    struct FragmentState {
        ChainedStruct const * nextInChain = nullptr;
        ShaderModule module;
        char const * entryPoint = nullptr;
        size_t constantCount = 0;
        ConstantEntry const * constants;
        size_t targetCount;
        ColorTargetState const * targets;
    };

    struct RenderPipelineDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        PipelineLayout layout = nullptr;
        VertexState vertex;
        PrimitiveState primitive;
        DepthStencilState const * depthStencil = nullptr;
        MultisampleState multisample;
        FragmentState const * fragment = nullptr;
    };

}  // namespace wgpu

namespace wgpu {
    template<>
    struct IsWGPUBitmask<wgpu::BufferUsage> {
        static constexpr bool enable = true;
    };

    template<>
    struct IsWGPUBitmask<wgpu::ColorWriteMask> {
        static constexpr bool enable = true;
    };

    template<>
    struct IsWGPUBitmask<wgpu::HeapProperty> {
        static constexpr bool enable = true;
    };

    template<>
    struct IsWGPUBitmask<wgpu::MapMode> {
        static constexpr bool enable = true;
    };

    template<>
    struct IsWGPUBitmask<wgpu::ShaderStage> {
        static constexpr bool enable = true;
    };

    template<>
    struct IsWGPUBitmask<wgpu::TextureUsage> {
        static constexpr bool enable = true;
    };

} // namespace wgpu

namespace std {
// Custom boolean class needs corresponding hash function so that it appears as a transparent bool.
template <>
struct hash<wgpu::Bool> {
  public:
    size_t operator()(const wgpu::Bool &v) const {
        return hash<bool>()(v);
    }
};
}  // namespace std

#endif // WEBGPU_CPP_H_
