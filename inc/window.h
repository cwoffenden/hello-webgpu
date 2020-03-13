/**
 * \file window.h
 * Abstraction for creating and managing windows.
 */
#pragma once

#include "defines.h"

namespace window {
/**
 * \typedef Handle
 * Opaque window handle.
 */
typedef struct HandleImpl* Handle;

/**
 * Function prototype for the redraw callback. See \c #loop().
 */
typedef bool (*Redraw) ();

//****************************************************************************/

/**
 * Creates a new window.
 *
 * \param[in] winW optional internal width (or zero to use the default width)
 * \param[in] winH optional internal height (or zero to use the default height)
 * \param[in] name optional window title (alternatively repurposed as the element ID for web-based implementations)
 */
Handle _NULLABLE create(unsigned winW = 0, unsigned winH = 0, const char* _NULLABLE name = nullptr);

/**
 * Destroys a window, freeing any resources.
 *
 * \param[in] wHnd window to destroy
 */
void destroy(Handle _NONNULL wHnd);

/**
 * Shows or hides a window.
 *
 * \param[in] wHnd window to show or hide
 * \param[in] show \c true to show, \c false to hide
 */
void show(Handle _NONNULL wHnd, bool show = true);

/**
 * Registers the redraw function to be called each frame.
 *
 * \todo rethink this - what do we do for multiple windows?
 *
 * \param[in] func function to be called each \e frame (or \c null to do nothing)
 */
void loop(Redraw _NULLABLE func = nullptr);
}
