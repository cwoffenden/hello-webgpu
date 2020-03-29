#include "window.h"

#import <CoreVideo/CoreVideo.h>

#include "glue.h"

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

/**
 * Helper to convert a \c Handle to a window.
 */
#define TO_HND(win) reinterpret_cast<window::Handle>(win)
/**
 * Helper to convert a window to a \c Handle.
 */
#define TO_WIN(hnd) reinterpret_cast<WindowImpl*>(hnd)

namespace impl {
/**
 * \c true if the application is still running.
 *
 * \todo the currenty only works for a single window
 */
bool running = true;

/**
 * Display link callback (with the \c CVDisplayLinkOutputCallback signature).
 *
 * \param[in] dispLink display link requesting the frame
 * \param[in] callTime time now of the current call
 * \param[in] drawTime time the frame will be displayed
 * \param[in] user user defined data (currently the owning \c WindowImpl pointer)
 */
static CVReturn update(CVDisplayLinkRef dispLink, const CVTimeStamp* callTime, const CVTimeStamp* drawTime, CVOptionFlags, CVOptionFlags*, void* user);
}

#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 1070
@interface WindowImpl : NSWindow<NSWindowDelegate, NSDraggingDestination>
#else
@interface WindowImpl : NSWindow
#endif
{
/**
 * Display link compatible with all displays.
 *
 * \todo assign to the window's display (does this guarantee the correct refresh on multi-monitor systems?)
 * \todo track the window moving monitors
 */
CVDisplayLinkRef dispLink;

/**
 * Registered redraw function to call each frame via \c #dispLink.
 */
window::Redraw redrawFunc;
}
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
		CVDisplayLinkCreateWithActiveCGDisplays(&dispLink);
		CVDisplayLinkSetOutputCallback(dispLink, &impl::update, self);
		redrawFunc = NULLPTR;
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
 * \copydoc NSWindow#dealloc
 */
- (void)dealloc {
	CVDisplayLinkRelease(dispLink);
	[super dealloc];
}

/**
 * Hmm, hackily sets the redraw function called by the display link.
 *
 * \todo tidy!
 *
 * \param[in] func redraw function (\c null to stop the redraw callbacks)
 */
- (void)setRedraw:(window::Redraw) func {
	if (func) {
		redrawFunc = func;
		CVDisplayLinkStart(dispLink);
	} else {
		impl::running = false;
		CVDisplayLinkStop(dispLink);
		redrawFunc = NULLPTR;
	}
}

/**
 * Called by the \c impl#update() redirector to call and handle \c #redrawFunc.
 */
- (void)doRedraw {
AUTO_RELEASE_POOL_ACQUIRE;
	if (!(redrawFunc && redrawFunc())) {
		[self setRedraw:NULLPTR];
	}
AUTO_RELEASE_POOL_RELEASE;
}

/**
 * Called when the window is about to close.
 *
 * \note Added via \c NSNotificationCenter not as a \c NSWindowDelegate.
 * \todo maintain a list of windows and don't just expect this to be the only one
 */
- (void)windowWillClose:(NSNotification*)__unused notification {
	/*
	 * The user closed the window so we kill the app (by removing its display
	 * link callback, which then stop the global 'running', eventually exiting
	 * the yield).
	 */
	[self setRedraw:NULLPTR];
	
}
@end

namespace impl {
static CVReturn update(CVDisplayLinkRef dispLink, const CVTimeStamp* callTime, const CVTimeStamp* drawTime, CVOptionFlags, CVOptionFlags*, void* user) {
	[TO_WIN(user)
		performSelectorOnMainThread:@selector(doRedraw)
			withObject:nil waitUntilDone:YES];
	/*
	NSLog(@"callTime:%lldms, drawTime:%lldms",
		  callTime->videoTime / (callTime->videoTimeScale / 1000),
		  drawTime->videoTime / (drawTime->videoTimeScale / 1000));
	 */
	return kCVReturnSuccess;
}

/*
 * Blocks waiting for events (processing each). Eventually exiting when \c
 * #running is \c false.
 *
 * \note This seems to run as expected, with 0.1% CPU as long as the display
 * link callback doesn't draw anything.
 */
void wait() {
AUTO_RELEASE_POOL_ACQUIRE;
	/*
	 * TODO: do we need the [NSApp updateWindows] call after each event?
	 */
	while (impl::running) {
		NSEvent* e = [NSApp nextEventMatchingMask:NSEventMaskAny
			untilDate:[NSDate distantFuture]
				inMode:NSDefaultRunLoopMode dequeue:YES];
		if (e) {
			switch ([e type]) {
			/*
			 * Any of the events we're interested in go here.
			 */
			default:
				break;
			}
			[NSApp sendEvent:e];
			[NSApp updateWindows];
		}
	}
AUTO_RELEASE_POOL_RELEASE;
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
	return TO_HND(win);
}

void window::destroy(window::Handle wHnd) {
	[TO_WIN(wHnd) close];
}

void window::show(window::Handle /*wHnd*/, bool /*show*/) {}

void window::loop(window::Handle wHnd, window::Redraw func) {
	/*
	 * Starts with an initial call to the draw function (which, for example,
	 * clears the screen early).
	 */
	if (func && func()) {
		[TO_WIN(wHnd) setRedraw:func];
		impl::wait();
	}
}
