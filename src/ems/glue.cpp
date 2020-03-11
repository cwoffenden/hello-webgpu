#include <emscripten/em_js.h>
#include <emscripten/emscripten.h>

/**
 * \def KEEP_IN_MODULE
 * Marks a function to be kept in the \c Module and exposed to script. An
 * alternative to Emscripten's \c bind or \c cwrap.
 * \code
 *	// C++
 *	KEEP_IN_MODULE int getValue() {
 *		return 42;
 *	}
 *	// JavaScript
 *	console.log(Module._getValue());
 * \endcode
 */
#ifndef KEEP_IN_MODULE
#define KEEP_IN_MODULE extern "C" __attribute__((used, visibility("default")))
#endif

/**
 * Entry point for the 'real' application.
 *
 * \param[in] argc count of program arguments in argv
 * \param[in] argv program arguments (excluding the application)
 */
extern "C" int __main__(int /*argc*/, char* /*argv*/[]);

//****************************************************************************/

namespace impl {
EM_JS(void, glue_preint_webgpu, (), {
	var entry = Module["__glue_main_"];
	if (entry) {
		navigator.gpu.requestAdapter().then(function (adapter) {
			adapter.requestDevice().then(function (device) {
				Module.preinitializedWebGPUDevice = device;
				entry();
			});
		});
	} else {
		console.error("Entry point not found; unable to start");
	}
});
}

//****************************************************************************/

/**
 * Redirector to call \c __main__() (exposed to Emscripten's \c Module).
 * 
 * \todo pass URL query string for args
 */
KEEP_IN_MODULE void _glue_main_() {
	__main__(0, nullptr);
}

/**
 * Entry point. Workaround for Emscripten needing an \c async start.
 */
int main(int /*argc*/, char* /*argv*/[]) {
    impl::glue_preint_webgpu();
	emscripten_exit_with_live_runtime();
	return 0;
}
