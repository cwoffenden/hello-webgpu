#include "webgpu.h"

/*
 * On Mac Dawn should have been built with Metal support.
 */
#define DAWN_ENABLE_BACKEND_METAL

#include <dawn/dawn_proc.h>
#include <dawn/webgpu_cpp.h>
#include "dawn/native/DawnNative.h"
//#include <dawn/native/MetalBackend.h>
//#include <dawn/native/NullBackend.h>

#import <AppKit/NSWindow.h>
#import <QuartzCore/QuartzCore.h>


namespace impl {
/*
 * NOTE: keeping these here for a single device/window until I work out more.
 * NOTE: this will probably share a lot with the Windows implmentation
 */

static dawn::native::Instance instance;

/*
 * Chosen backend type for \c #device.
 */
WGPUBackendType backend;

/*
 * WebGPU graphics API-specific device, created from a \c dawn::native::Adapter
 * and optional feature requests. This should wrap the same underlying device
 * for the same configuration.
 */
WGPUDevice device;

WGPUSurface surface;
WGPUSwapChain swapchain;

/*
 * Preferred swap chain format, obtained in the browser via a promise to
 * GPUCanvasContext::getSwapChainPreferredFormat(). In Dawn we can call this
 * directly in NativeSwapChainImpl::GetPreferredFormat() (which is hard-coded
 * with D3D, for example, to RGBA8Unorm, but queried for others). For the D3D
 * back-end calling wgpuSwapChainConfigure ignores the passed preference and
 * asserts if it's not the preferred choice.
 */
//static WGPUTextureFormat swapPref;

//********************************** Helpers *********************************/

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
static dawn::native::Adapter requestAdapter(WGPUBackendType type1st, WGPUBackendType type2nd = WGPUBackendType_Null) {
	 // TODO: lifecycle?
	WGPUAdapterProperties properties = {};
	std::vector<dawn::native::Adapter> adapters = instance.EnumerateAdapters();
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
	return dawn::native::Adapter();
}

/**
 * Creates an API-specific swap chain implementation in \c #swapImpl and stores
 * the \c #swapPref.
 */
/*
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
 */

/**
 * Dawn error handling callback (adheres to \c WGPUErrorCallback).
 *
 * \param[in] message error string
 */
static void __unused printError(WGPUErrorType /*type*/, const char* message, void*) {
	puts(message);
}
} // impl

//******************************** Public API ********************************/

WGPUDevice webgpu::create(window::Handle window, WGPUBackendType type) {
	if (type == WGPUBackendType_Undefined) {
		type  = WGPUBackendType_Metal;
	}
	if (dawn::native::Adapter adapter = impl::requestAdapter(type)) {
		WGPUAdapterProperties  properties = {};
		adapter.GetProperties(&properties);
		impl::backend = static_cast<WGPUBackendType>(properties.backendType);
		impl::device  = adapter.CreateDevice();
		
		// TODO: move to this callback API to match web
		//adapter.RequestDevice(nullptr, [](WGPURequestDeviceStatus status, WGPUDevice device, char const * message, void* userdata) {
		//	if (status == WGPURequestDeviceStatus_Success) {
		//		impl::device = device;
		
		DawnProcTable procs(dawn::native::GetProcs());
		procs.deviceSetUncapturedErrorCallback(impl::device, impl::printError, nullptr);
		dawnProcSetProcs(&procs);

		NSWindow* nsWindow = reinterpret_cast<NSWindow*>(window);
		NSView* view = nsWindow.contentView;
		view.wantsLayer = YES;
		view.layer      = [CAMetalLayer layer];
		view.layer.contentsScale = nsWindow.backingScaleFactor;

		// TODO: lifecycle of the chained structs?
		WGPUSurfaceDescriptorFromMetalLayer desc = {};
		desc.layer = view.layer;
		desc.chain.sType = WGPUSType_SurfaceDescriptorFromMetalLayer;
		desc.chain.next  = nullptr;

		WGPUSurfaceDescriptor surfaceDesc = {};
		surfaceDesc.nextInChain = reinterpret_cast<WGPUChainedStruct*>(&desc);

		impl::surface = wgpuInstanceCreateSurface(impl::instance.Get(), &surfaceDesc);
	}
	/*
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
	 */
	return impl::device;
}

WGPUSwapChain webgpu::createSwapChain(WGPUDevice device) {
	WGPUSwapChainDescriptor swapDesc = {};
	/*
	 * See the Windows implementation. This is mostly the same (find the docs
	 * re. Metal's preference for presenting immediately).
	 */
	swapDesc.usage  = WGPUTextureUsage_RenderAttachment;
	swapDesc.format = getSwapChainFormat(device);
	swapDesc.width  = 800;
	swapDesc.height = 450;
	swapDesc.presentMode = WGPUPresentMode_Immediate;

	impl::swapchain = wgpuDeviceCreateSwapChain(impl::device, impl::surface, &swapDesc);
	/*
	 * Currently failing on hi-DPI (with Vulkan on Windows).
	 */
	//wgpuSwapChainConfigure(impl::swapchain, WGPUTextureFormat_BGRA8Unorm, WGPUTextureUsage_RenderAttachment, 800, 450);
	return impl::swapchain;
}

WGPUTextureFormat webgpu::getSwapChainFormat(WGPUDevice /*device*/) {
	return WGPUTextureFormat_BGRA8Unorm;
}
