/**
 * \file glue.h
 * Hidden magic that holds the Windows implementation together.
 * 
 * \author cw
 */
#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif
#include <SDKDDKVer.h>

#include <Windows.h>
#include <tchar.h>
