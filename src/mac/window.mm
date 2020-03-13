#include "window.h"

#import <Cocoa/Cocoa.h>

/**
 * Default window width.
 */
#ifndef WINDOW_WIN_W
#define WINDOW_WIN_W 800
#endif

/**
 * Default window height.
 */
#ifndef WINDOW_WIN_H
#define WINDOW_WIN_H 450
#endif

/**
 * Default window title.
 */
#ifndef WINDOW_WIN_NAME
#define WINDOW_WIN_NAME "Demo"
#endif

/**
 * Set if the window should be resizable (otherwise it is fixed to the width
 * and height defined above).
 *
 * \todo disable arbitrary resize and support fixed options?
 */
#ifndef WINDOW_WIN_RESIZE
#define WINDOW_WIN_RESIZE 0
#endif

/*
 * Sleep period for the yield. Currently undergoing experimentation (the vblank
 * wait should do away with this requirement).
 */
#ifndef WINDOW_SLEEP_PERIOD
#define WINDOW_SLEEP_PERIOD 2
#endif

/**
 * Window style flags passed to window creation call.
 */
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 101200
#if (WINDOW_WIN_RESIZE)
#define WINDOW_NS_WIN_FLAGS NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable
#else
#define WINDOW_NS_WIN_FLAGS NSWindowStyleMaskTitled | NSWindowStyleMaskClosable
#endif
#else
#if (WINDOW_WIN_RESIZE)
#define WINDOW_NS_WIN_FLAGS NSTitledWindowMask | NSClosableWindowMask| NSMiniaturizableWindowMask | NSResizableWindowMask
#else
#define WINDOW_NS_WIN_FLAGS NSTitledWindowMask | NSClosableWindowMask| NSMiniaturizableWindowMask
#endif
#endif

//****************************************************************************/

#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 1070
@interface WindowImpl : NSWindow<NSWindowDelegate, NSDraggingDestination>
#else
@interface WindowImpl : NSWindow
#endif
@end

/**
 * Single application window.
 */
@implementation WindowImpl
/**
 * \copydoc NSWindow#initWithContentRect
 */
- (id)initWithContentRect:(NSRect)rect styleMask:(NSUInteger)style backing:(NSBackingStoreType)type defer:(BOOL)flag {
	if ((self = [super initWithContentRect:rect styleMask:style backing:type defer:flag])) {
		/*
		 * Note: added as a notification instead of an NSWindowDelegate,
		 * allowing other parts of metal to add their own.
		 */
		[[NSNotificationCenter defaultCenter] addObserver:self
			selector:@selector(windowWillClose:)
				name:NSWindowWillCloseNotification object:self];
	}
	return self;
}

/**
 * Called when the window is about to close.
 *
 * \note Added via \c NSNotificationCenter not as a \c NSWindowDelegate.
 * \todo maintain a list of windows and don't just expect this to be the only one
 */
- (void)windowWillClose:(NSNotification*)__unused notification {
	/*
	 * The user closed the window so we kill the app (after which, our window
	 * instance will have been released, unless it was retained otherwise).
	 */
	[NSApp terminate:nil];
}
@end

namespace impl {
/*
 * Temporary bad yield...
 */
bool yield() {
	/*
	 * In testing, anything other than an 'untilDate' of 'distantPast' uses
	 * more CPU time (it's a percent or so but it's still more).
	 * 
	 * Note: we need to still the OS to deal with most of these events (e.g.
	 * mouse clicks are used to close the window, click buttons, etc.). There's
	 * probably a middleground of intercepting some, though.
	 * 
	 * TODO: do we need the [NSApp updateWindows] call after each event?
	 */
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	while (true) {
		NSEvent* e = [NSApp nextEventMatchingMask:NSEventMaskAny
			untilDate:[NSDate distantPast]
				inMode:NSDefaultRunLoopMode dequeue:YES];
		if (e) {
			switch ([e type]) {
			/*
			 * All of the events we're interested in go here.
			 */
			default:
				break;
			}
			[NSApp sendEvent:e];
		} else {
			break;
		}
	}
	[NSThread sleepForTimeInterval:WINDOW_SLEEP_PERIOD / 1000.0];
	[pool release];
	/*
	 * We always return true here, regardless of whether termination has been
	 * requested. At the point where [NSApp terminate] is called, the app won't
	 * continue, so any code afterwards won't be run anyway.
	 */
	return true;
}
}

//******************************** Public API ********************************/

window::Handle window::create(unsigned /*winW*/, unsigned /*winH*/, const char* /*name*/) {
	WindowImpl* win = [[WindowImpl alloc]
		initWithContentRect:NSMakeRect(0, 0, WINDOW_WIN_W, WINDOW_WIN_H)
			styleMask:WINDOW_NS_WIN_FLAGS
				backing:NSBackingStoreBuffered defer:NO];
	[win center];
	[win makeKeyAndOrderFront:win];
	[win makeMainWindow];
	return reinterpret_cast<window::Handle>(win);
}

void window::destroy(window::Handle /*wHnd*/) {}

void window::show(window::Handle /*wHnd*/, bool /*show*/) {}

void window::loop(window::Redraw func) {
	while (impl::yield()) {
		if (func) {
			if (!func()) {
				break;
			}
		}
	}
}
