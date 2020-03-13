#include "defines.h"

#import <Cocoa/Cocoa.h>

/**
 * Entry point for the 'real' application.
 *
 * \param[in] argc count of program arguments in argv
 * \param[in] argv program arguments (excluding the application)
 */
extern "C" int __main__(int argc, char* argv[]);

/*
 * Entry point.
 */
int main(int /*argc*/, const char* /*argv*/[]) {
	int retval = EXIT_FAILURE;
#if __MAC_OS_X_VERSION_MIN_REQUIRED < 1060
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
#else
	@autoreleasepool {
#endif
	[NSApplication sharedApplication];
	
	[NSApp activateIgnoringOtherApps:YES];
	[NSApp finishLaunching];
	
	/*
	 * Call the real main but, like all Cocoa apps, no clean-up is needed (since
	 * terminating will never get beyond here we only return for completeness).
	 *
	 * We *don't* [[NSRunLoop currentRunLoop] run] instead __main__ should
	 * gameloop-style yield().
	 */
	retval = __main__(0, NULLPTR);
#if __MAC_OS_X_VERSION_MIN_REQUIRED < 1060
	[pool release];
#else
	}
#endif
	return retval;
}
