#include "webgpu.h"

/*
 * On Mac Dawn should have been built with Metal support.
 */
#define DAWN_ENABLE_BACKEND_METAL

#include <dawn/dawn_proc.h>
#include <dawn/webgpu_cpp.h>
#include <dawn_native/MetalBackend.h>
#include <dawn_native/NullBackend.h>

#import <AppKit/NSWindow.h>
#import <QuartzCore/QuartzCore.h>


namespace impl {
/*
 * NOTE: keeping these here for a single device/window until I work out more.
 * NOTE: this will probably share a lot with the Windows implmentation
 */

/*
 * Chosen backend type for \c #device.
 */
WGPUBackendType backend;

/*
 * WebGPU graphics API-specific device, created from a \c dawn_native::Adapter
 * and optional feature requests. This should wrap the same underlying device
 * for the same configuration.
 */
WGPUDevice device;

/*
 * Something needs to hold onto this since the address is passed to the WebGPU
 * native API, exposing the type-specific swap chain implementation. The struct
 * gets filled out on calling the respective XXX::CreateNativeSwapChainImpl(),
 * binding the WebGPU device and native window, then its raw pointer is passed
 * into WebGPU as a 64-bit int. The browser API doesn't have an equivalent
 * (since the swap chain is created from the canvas directly).
 *
 * Is the struct copied or does it need holding for the lifecycle of the swap
 * chain, i.e. can it just be a temporary?
 *
 * After calling wgpuSwapChainRelease() does it also call swapImpl::Destroy()
 * to delete the underlying NativeSwapChainImpl(), invalidating this struct?
 */
static DawnSwapChainImplementation swapImpl;

/*
 * Preferred swap chain format, obtained in the browser via a promise to
 * GPUCanvasContext::getSwapChainPreferredFormat(). In Dawn we can call this
 * directly in NativeSwapChainImpl::GetPreferredFormat() (which is hard-coded
 * with D3D, for example, to RGBA8Unorm, but queried for others). For the D3D
 * back-end calling wgpuSwapChainConfigure ignores the passed preference and
 * asserts if it's not the preferred choice.
 */
static WGPUTextureFormat swapPref;

//********************************** Helpers *********************************/

/**
 * Work-in-progress. Metal swap chain implementation (pretty much taken from
 * Dawn's \c MetalBinding.mm)
 *
 * \todo why is this not in the Dawn repo like the D3D or Vulkan version?
 */
class MetalSwapChainImpl
{
public:
	MetalSwapChainImpl(NSWindow* window)
		: window  (window)
		, device  (nil)
		, queue   (nil)
		, layer   (nil)
		, drawable(nil)
		, texture (nil) {}
		
	void init(DawnWSIContextMetal* ctx) {
		device = ctx->device;
		queue  = ctx->queue;
	}
	DawnSwapChainError configure(WGPUTextureFormat format, WGPUTextureUsage usage, uint32_t w, uint32_t h) {
		CGSize size = {
			.width  = static_cast<CGFloat>(w),
			.height = static_cast<CGFloat>(h)
		};
		layer = CAMetalLayer.layer;
		layer.device       = device;
		layer.pixelFormat  = MTLPixelFormatBGRA8Unorm;
		layer.drawableSize = size;
		if (usage & (WGPUTextureUsage_RenderAttachment | WGPUTextureUsage_Present)) {
			layer.framebufferOnly = YES;
		}
		
		NSView* view = window.contentView;
		view.wantsLayer = YES;
		view.layer      = layer;
		
		return DAWN_SWAP_CHAIN_NO_ERROR;
	}
	DawnSwapChainError getNextTexture(DawnSwapChainNextTexture* next) {
		[drawable release];
		 drawable = layer.nextDrawable;
		[drawable retain];
		[texture release];
		 texture = drawable.texture;
		[texture retain];
		next->texture.ptr = reinterpret_cast<void*>(texture);
		return DAWN_SWAP_CHAIN_NO_ERROR;
	}
	DawnSwapChainError present() {
		id<MTLCommandBuffer> cmdBuf = [queue commandBuffer];
		[cmdBuf presentDrawable: drawable];
		[cmdBuf commit];
		return DAWN_SWAP_CHAIN_NO_ERROR;
	}
private:
	NSWindow* window;				///< Window the Metal \c #layer will be drawn in
	id<MTLDevice> device;			///< GPU interface
	id<MTLCommandQueue> queue;		///< Command queue used to present \c #drawable
	CAMetalLayer* layer;			///< Render layer attached to \c #window
	id<CAMetalDrawable> drawable;	///< Current \e drawable associated with the \c #layer (retained)
	id<MTLTexture> texture;			///< Texture of the current \c #drawable (retained)
};

/**
 * Helper to wrap \c #MetalSwapChainImpl in the required \c DawnSwapChainImplementation.
 */
DawnSwapChainImplementation createMetalSwapChain(NSWindow* window) {
	return DawnSwapChainImplementation {
		.Init           = [](void* userData, void* wsiContext) {
			static_cast<MetalSwapChainImpl*>(userData)->init(static_cast<DawnWSIContextMetal*>(wsiContext));
		},
		.Destroy        = [](void* userData) {
			delete static_cast<MetalSwapChainImpl*>(userData);
		},
		.Configure      = [](void* userData, WGPUTextureFormat format, WGPUTextureUsage usage, uint32_t w, uint32_t h) {
			return static_cast<MetalSwapChainImpl*>(userData)->configure(format, usage, w, h);
		},
		.GetNextTexture = [](void* userData, DawnSwapChainNextTexture* next) {
			return static_cast<MetalSwapChainImpl*>(userData)->getNextTexture(next);
		},
		.Present        = [](void* userData) {
			return static_cast<MetalSwapChainImpl*>(userData)->present();
		},
		.userData       = new MetalSwapChainImpl(window),
	};
}

/**
 * Analogous to the browser's \c GPU.requestAdapter().
 * \n
 * The returned \c Adapter is a wrapper around the underlying Dawn adapter (and
 * owned by the single Dawn instance).
 *
 * \todo we might be interested in whether the \c AdapterType is discrete or integrated for power-management reasons
 *
 * \param[in] type1st first choice of \e backend type (e.g. \c WGPUBackendType_D3D12)
 * \param[in] type2nd optional fallback \e backend type (or \c WGPUBackendType_Null to pick the first choice or nothing)
 * \return the best choice adapter or an empty adapter wrapper
 */
static dawn_native::Adapter requestAdapter(WGPUBackendType type1st, WGPUBackendType type2nd = WGPUBackendType_Null) {
	static dawn_native::Instance instance;
	instance.DiscoverDefaultAdapters();
	wgpu::AdapterProperties properties;
	std::vector<dawn_native::Adapter> adapters = instance.GetAdapters();
	for (auto it = adapters.begin(); it != adapters.end(); ++it) {
		it->GetProperties(&properties);
		if (static_cast<WGPUBackendType>(properties.backendType) == type1st) {
			return *it;
		}
	}
	if (type2nd) {
		for (auto it = adapters.begin(); it != adapters.end(); ++it) {
			it->GetProperties(&properties);
			if (static_cast<WGPUBackendType>(properties.backendType) == type2nd) {
				return *it;
			}
		}
	}
	return dawn_native::Adapter();
}

/**
 * Creates an API-specific swap chain implementation in \c #swapImpl and stores
 * the \c #swapPref.
 */
static void initSwapChain(WGPUBackendType backend, WGPUDevice device, window::Handle window) {
	switch (backend) {
	case WGPUBackendType_Metal:
		if (impl::swapImpl.userData == nullptr) {
			impl::swapImpl = createMetalSwapChain(reinterpret_cast<NSWindow*>(window));
			impl::swapPref = WGPUTextureFormat_BGRA8Unorm;
		}
		break;
	default:
		if (impl::swapImpl.userData == nullptr) {
			impl::swapImpl = dawn_native::null::CreateNativeSwapChainImpl();
			impl::swapPref = WGPUTextureFormat_Undefined;
		}
		break;
	}
}

/**
 * Dawn error handling callback (adheres to \c WGPUErrorCallback).
 *
 * \param[in] message error string
 */
static void printError(WGPUErrorType /*type*/, const char* message, void*) {
	puts(message);
}
} // impl

//******************************** Public API ********************************/

WGPUDevice webgpu::create(window::Handle window, WGPUBackendType type) {
	if (type > WGPUBackendType_OpenGLES) {
		type = WGPUBackendType_Metal;
	}
	if (dawn_native::Adapter adapter = impl::requestAdapter(type)) {
		wgpu::AdapterProperties properties;
		adapter.GetProperties(&properties);
		impl::backend = static_cast<WGPUBackendType>(properties.backendType);
		impl::device  = adapter.CreateDevice();
		impl::initSwapChain(impl::backend, impl::device, window);
		DawnProcTable procs(dawn_native::GetProcs());
		procs.deviceSetUncapturedErrorCallback(impl::device, impl::printError, nullptr);
		dawnProcSetProcs(&procs);
	}
	return impl::device;
}

WGPUSwapChain webgpu::createSwapChain(WGPUDevice device) {
	WGPUSwapChainDescriptor swapDesc = {};
	/*
	 * See the Windows implementation. This is mostly the same (find the docs
	 * re. Metal's preference for presenting immediately).
	 *
	swapDesc.usage  = WGPUTextureUsage_OutputAttachment;
	swapDesc.format = impl::swapPref;
	swapDesc.width  = 800;
	swapDesc.height = 450;
	swapDesc.presentMode = WGPUPresentMode_Immediate;
	 */
	swapDesc.implementation = reinterpret_cast<uintptr_t>(&impl::swapImpl);
	WGPUSwapChain swapchain = wgpuDeviceCreateSwapChain(device, nullptr, &swapDesc);
	/*
	 * Currently failing on hi-DPI (with Vulkan on Windows).
	 */
	wgpuSwapChainConfigure(swapchain, impl::swapPref, WGPUTextureUsage_RenderAttachment, 800, 450);
	return swapchain;
}

WGPUTextureFormat webgpu::getSwapChainFormat(WGPUDevice /*device*/) {
	return impl::swapPref;
}
