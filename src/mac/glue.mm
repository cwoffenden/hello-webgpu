#include "defines.h"

#include "glue.h"

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
AUTO_RELEASE_POOL_ACQUIRE;
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
AUTO_RELEASE_POOL_RELEASE;
	return retval;
}
