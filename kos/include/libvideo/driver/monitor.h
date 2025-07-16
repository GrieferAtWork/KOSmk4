/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBVIDEO_DRIVER_MONITOR_H
#define _LIBVIDEO_DRIVER_MONITOR_H 1

#include "api.h"
/**/

#include <__stdinc.h>

#include <libvideo/gfx/display.h>

#include "../types.h"

__DECL_BEGIN

#ifdef __CC__

struct video_monitor_mode {
	video_dim_t           vmm_xres; /* Resolution in X */
	video_dim_t           vmm_yres; /* Resolution in Y */
	__UINT_LEAST16_TYPE__ vmm_hz;   /* Refresh rate (frames per second) */
	__SHIFT_TYPE__        vmm_bpp;  /* Color depth */
};

/* TODO: `struct video_domain': allocator for `struct video_buffer' (including custom operators if needed) */
/* TODO: `struct video_domain': generic implementation for ram-buffers */
/* TODO: `struct video_adapter': enumerate `struct video_monitor' and extends `struct video_domain' */

struct video_monitor_ops {
	struct video_display_ops vmo_display; /* Display operators */

//TODO:	/* Get the currently set video mode */
//TODO:	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_OUT_T(2) int
//TODO:	(LIBVIDEO_DRIVER_CC *vmo_getmode)(struct video_monitor *__restrict __self,
//TODO:	                                  struct video_monitor_mode *__restrict __mode);
//TODO:
//TODO:	/* Set a new video mode () */
//TODO:	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_OUT_T(2) int
//TODO:	(LIBVIDEO_DRIVER_CC *vmo_setmode)(struct video_monitor *__restrict __self,
//TODO:	                                  struct video_monitor_mode *__restrict __mode);
};

struct video_monitor
#ifdef __cplusplus
    : video_display
#endif /* __cplusplus */
{
};




#endif /* __CC__ */

__DECL_END

#endif /* !_LIBVIDEO_DRIVER_MONITOR_H */
