#include "webgpu.h"

#include <dawn/dawn_proc.h>
#include <dawn/webgpu_cpp.h>
#include <dawn_native/MetalBackend.h>
#include <dawn_native/NullBackend.h>

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
			// do the magic here...
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

WGPUSwapChain webgpu::createSwapChain(WGPUDevice /*device*/) {
	return nullptr;
}

WGPUTextureFormat webgpu::getSwapChainFormat(WGPUDevice /*device*/) {
	return impl::swapPref;
}
