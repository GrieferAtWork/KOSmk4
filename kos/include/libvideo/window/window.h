/* Copyright (c) 2019-2024 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBVIDEO_WINDOW_WINDOW_H
#define _LIBVIDEO_WINDOW_WINDOW_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <hybrid/typecore.h>

#include "api.h"

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

__DECL_BEGIN

/* Window decoration flag. */
#define VIDEO_WINDOW_DECORATION_DEFAULT     0x0000  /* Default window flags. */
#define VIDEO_WINDOW_DECORATION_BORDERLESS  0x0001  /* Don't surround the window with a border. */
#define VIDEO_WINDOW_DECORATION_NORESIZE    0x0002  /* Don't allow user-driver window resizing. */
#define VIDEO_WINDOW_DECORATION_NOMOVE      0x0004  /* Don't allow the window to be moved with ALT+mouse. */
/* NOTE: When all of the following flags are given, the title bar get completely hidden. */
#define VIDEO_WINDOW_DECORATION_NOTITLE     0x0010  /* Don't show the window title. */
#define VIDEO_WINDOW_DECORATION_NOMINIMIZE  0x0020  /* Don't show the minimize-button */
#define VIDEO_WINDOW_DECORATION_NOMAXIMIZE  0x0040  /* Don't show the maximize-button */
#define VIDEO_WINDOW_DECORATION_NOCLOSE     0x0080  /* Don't show the close-button */
#define VIDEO_WINDOW_DECORATION_NOICON      0x0100  /* Don't show the clickable application icon. */

/* Flags for a window without any special features. */
#define VIDEO_WINDOW_DECORATION_FEATURELESS \
	(VIDEO_WINDOW_DECORATION_BORDERLESS | VIDEO_WINDOW_DECORATION_NORESIZE |   \
	 VIDEO_WINDOW_DECORATION_NOMOVE | VIDEO_WINDOW_DECORATION_NOTITLE |        \
	 VIDEO_WINDOW_DECORATION_NOMINIMIZE | VIDEO_WINDOW_DECORATION_NOMAXIMIZE | \
	 VIDEO_WINDOW_DECORATION_NOCLOSE | VIDEO_WINDOW_DECORATION_NOICON)

/* Window positioning. */
#define VIDEO_WINDOW_POSITION_NORMAL       0 /* Normal window positioning. */
#define VIDEO_WINDOW_POSITION_STAYONTOP    1 /* Keep the window on top. */
#define VIDEO_WINDOW_POSITION_STAYINBACK   2 /* Keep the window in the back. */

/* Window state. */
#define VIDEO_WINDOW_STATE_SHOWN      0 /* Show window */
#define VIDEO_WINDOW_STATE_MINIMIZED  1 /* Hide, but show in task bar */
#define VIDEO_WINDOW_STATE_HIDDEN     2 /* Hide window */

/* Window features. */
#define VIDEO_WINDOW_FEATURE_NORMAL 0x0000 /* Normal window features. */
#define VIDEO_WINDOW_FEATURE_ALPHA  0x0001 /* Window surface has an alpha-channel. */



#ifdef __CC__
struct video_buffer;
struct video_window {
	void                *vw_handle;     /* [?..?] Abstract handle for the window within the window server. */
	struct video_buffer *vw_surface;    /* [1..1][EVENT_VOLATILE] Window surface buffer. */
	__intptr_t           vw_pos_x;      /* [EVENT_VOLATILE] X-position of the window (0,0 being the top-left corner of the primary monitor) */
	__intptr_t           vw_pos_y;      /* [EVENT_VOLATILE] Y-position of the window (0,0 being the top-left corner of the primary monitor) */
	__uintptr_t          vw_decoration; /* Window decoration (Set of `VIDEO_WINDOW_DECORATION_*') */
	__uintptr_t          vw_features;   /* Window features (Set of `VIDEO_WINDOW_FEATURE_*') */
	__uintptr_t          vw_order;      /* Window Z-order (One of `VIDEO_WINDOW_POSITION_*') */
	__uintptr_t          vw_state;      /* [EVENT_VOLATILE] Window state (One of `VIDEO_WINDOW_STATE_*') */
};


/* Create  and  return a  new window,  or return  NULL and  set `errno'
 * NOTE: The preferred video format is determined by the window server.
 * @param: title:      Initial window title (or `NULL' to default to the `readlink("/proc/self/exe")')
 * @param: pos_x:      Initial X position of the new window's top-left corner
 * @param: pos_y:      Initial Y position of the new window's top-left corner
 * @param: size_x:     Initial width of the new window (in pixels, including decorations)
 * @param: size_y:     Initial height of the new window (in pixels, including decorations)
 * @param: decoration: Initial window decoration (Set of `VIDEO_WINDOW_DECORATION_*')
 * @param: features:   Initial window features (Set of `VIDEO_WINDOW_FEATURE_*')
 * @param: order:      Initial window Z-order (One of `VIDEO_WINDOW_POSITION_*')
 * @param: state:      Initial window state (One of `VIDEO_WINDOW_STATE_*')
 * @param: icon:       Initial window icon (or `NULL' to search use a default icon) */
LIBVIDEO_WINDOW_DECL struct video_window *LIBVIDEO_WINDOW_CC
video_window_create(char const *title,
                    __intptr_t pos_x, __intptr_t pos_y,
                    __size_t size_x, __size_t size_y,
                    __uintptr_t decoration, __uintptr_t features,
                    __uintptr_t order, __uintptr_t state,
                    struct video_buffer *icon);

/* Destroy a given window */
LIBVIDEO_WINDOW_DECL void LIBVIDEO_WINDOW_CC
video_window_destroy(struct video_window *__restrict window);



/* Adjust a  window  position/size  such  that previously  referring  to  a  window's
 * content area,  the  addition  of  decoration will  adjust  the  window's  position
 * and size such that a newly created window will have IN(<args...>) as content area.
 * NULL may be passed for arguments that can be ignored. */
LIBVIDEO_WINDOW_DECL void LIBVIDEO_WINDOW_CC
video_window_adjust_region_add_decorations(__uintptr_t decoration,
                                           __intptr_t *ppos_x, __intptr_t *ppos_y,
                                           __size_t *psize_x, __size_t *psize_y);
/* Reverse the effects of `video_window_adjust_region_add_decorations()' */
LIBVIDEO_WINDOW_DECL void LIBVIDEO_WINDOW_CC
video_window_adjust_region_remove_decorations(__uintptr_t decoration,
                                              __intptr_t *ppos_x, __intptr_t *ppos_y,
                                              __size_t *psize_x, __size_t *psize_y);


/* Alter specific aspects about the given window.
 * This function can be used to do pretty much everything. - e.g.:
 * >> int showWindow(struct video_window *window) {
 * >>	return video_window_alter(window,
 * >>	                          VIDEO_WINDOW_ALTER_STATE,
 * >>	                          0, 0, 0, 0, 0, 0, 0,
 * >>	                          VIDEO_WINDOW_STATE_SHOWN);
 * >> }
 * @param: pos_x:      New X position of the window's top-left corner
 * @param: pos_y:      New Y position of the window's top-left corner
 * @param: size_x:     New width of the window (in pixels, including decorations)
 * @param: size_y:     New height of the window (in pixels, including decorations)
 * @param: decoration: New window decoration (Set of `VIDEO_WINDOW_DECORATION_*')
 * @param: features:   New window features (Set of `VIDEO_WINDOW_FEATURE_*')
 * @param: order:      New window Z-order (One of `VIDEO_WINDOW_POSITION_*')
 * @param: state:      New window state (One of `VIDEO_WINDOW_STATE_*')
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
LIBVIDEO_WINDOW_DECL int LIBVIDEO_WINDOW_CC
video_window_alter(struct video_window *__restrict window,
                   unsigned int what, char const *title,
                   __intptr_t pos_x, __intptr_t pos_y,
                   __size_t size_x, __size_t size_y,
                   __uintptr_t decoration, __uintptr_t features,
                   __intptr_t order, __uintptr_t state,
                   struct video_buffer *icon);
#define VIDEO_WINDOW_ALTER_TITLE      0x0001 /* Apply `title' */
#define VIDEO_WINDOW_ALTER_POSITION   0x0002 /* Apply `pos_x' and `pos_y' */
#define VIDEO_WINDOW_ALTER_SIZE       0x0004 /* Apply `size_x' and `size_y' */
#define VIDEO_WINDOW_ALTER_DECORATION 0x0008 /* Apply `decoration' */
#define VIDEO_WINDOW_ALTER_FEATURES   0x0010 /* Apply `features' */
#define VIDEO_WINDOW_ALTER_ORDER      0x0020 /* Apply `order' */
#define VIDEO_WINDOW_ALTER_STATE      0x0040 /* Apply `state' */
#define VIDEO_WINDOW_ALTER_ICON       0x0080 /* Apply `icon' */





#endif /* __CC__ */

__DECL_END

#endif /* !_LIBVIDEO_WINDOW_WINDOW_H */
