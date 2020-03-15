#include "window.h"

#include <emscripten/emscripten.h>

namespace window {
/**
 * Temporary dummy window handle.
 */ 
struct HandleImpl {} DUMMY;

/**
 * Current redraw function.
 */
window::Redraw redraw = nullptr;

void em_redraw() {
	if (redraw) {
		if (redraw() == false) {
			redraw = nullptr;
			emscripten_cancel_main_loop();
		}
	}
}
}

//******************************** Public API ********************************/

window::Handle window::create(unsigned /*winW*/, unsigned /*winH*/, const char* /*name*/) {
	return &DUMMY;
}

void window::destroy(window::Handle /*wHnd*/) {}

void window::show(window::Handle /*wHnd*/, bool /*show*/) {}

void window::loop(window::Redraw func) {
	window::redraw = func;
	if (func) {
		emscripten_set_main_loop(window::em_redraw, 0, false);
	} else {
		emscripten_cancel_main_loop();
	}
}
