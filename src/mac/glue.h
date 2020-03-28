/**
 * \file glue.h
 * Hidden magic that holds the Mac implementation together.
 * 
 * \author cw
 */
#pragma once

#import <Cocoa/Cocoa.h>

/*
 * When ARC is enabled we can't pass out the Obj-C handles (which we can work
 * around) but we'd have to also branch the (still compatible) pre-ARC code.
 */
#if __has_feature(objc_arc)
#error "Cannot build with ARC enabled"
#endif

/**
 * \def AUTO_RELEASE_POOL_ACQUIRE
 * Starts an auto-release pool block.
 */
#ifndef AUTO_RELEASE_POOL_ACQUIRE
#if __MAC_OS_X_VERSION_MIN_REQUIRED < 1060
#define AUTO_RELEASE_POOL_ACQUIRE NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
#else
#define AUTO_RELEASE_POOL_ACQUIRE @autoreleasepool {
#endif
#endif

/**
 * \def AUTO_RELEASE_POOL_RELEASE
 * Ends an auto-release pool block.
 */
#ifndef AUTO_RELEASE_POOL_RELEASE
#if __MAC_OS_X_VERSION_MIN_REQUIRED < 1060
#define AUTO_RELEASE_POOL_RELEASE [pool release];
#else
#define AUTO_RELEASE_POOL_RELEASE }
#endif
#endif
