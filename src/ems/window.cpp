#include "window.h"

#include <emscripten/html5.h>

namespace window {
/**
 * Temporary dummy window handle.
 */ 
struct HandleImpl {} DUMMY;

EM_BOOL em_redraw(double /*time*/, void *userData) {
	window::Redraw redraw = (window::Redraw)userData;
	return redraw(); // If this returns true, rAF() will continue, otherwise it will terminate
}

}

//******************************** Public API ********************************/

window::Handle window::create(unsigned /*winW*/, unsigned /*winH*/, const char* /*name*/) {
	return &DUMMY;
}

void window::destroy(window::Handle /*wHnd*/) {}

void window::show(window::Handle /*wHnd*/, bool /*show*/) {}

void window::loop(window::Handle /*wHnd*/, window::Redraw func) {
	emscripten_request_animation_frame_loop(window::em_redraw, (void*)func);
}
