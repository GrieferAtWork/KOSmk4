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
#include <bits/types.h>

#include <libvideo/gfx/display.h>

#include "../types.h"

__DECL_BEGIN

#ifdef __CC__

struct video_adapter;

struct video_monitor_mode {
	__REF struct video_codec *vmm_codec; /* [1..1] Video codec */
	video_dim_t               vmm_xres;  /* Resolution in X */
	video_dim_t               vmm_yres;  /* Resolution in Y */
	__UINT_LEAST16_TYPE__     vmm_hz;    /* Refresh rate (frames per second) */
};

#define video_monitor_mode_fini(self) video_codec_decref((self)->vmm_codec)

/* Enumeration callback for `video_monitor_lsmodes()' */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(2) __ssize_t
(LIBVIDEO_DRIVER_CC *video_monitor_lsmodes_cb_t)(void *__cookie, struct video_monitor_mode const *__restrict __mode);

struct video_monitor_ops {
	struct video_display_ops vmo_display; /* Display operators */

	/* Enumerate supported video modes
	 * @return: >= 0: [errno=*] Sum of all return values of `__cb'
	 * @return: -1:   [errno=*] Either `__cb' returned `-1', or enumeration failed
	 * @return: < 0:  `__cb' returned this same negative value */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_NONNULL_T((2)) __ssize_t
	(LIBVIDEO_DRIVER_CC *vmo_lsmodes)(struct video_monitor *__restrict __self,
	                                  video_monitor_lsmodes_cb_t __cb, void *__cookie);

	/* Get the currently set video mode
	 * @return: 0 : Success
	 * @return: -1: Error (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_OUT_T(2) int
	(LIBVIDEO_DRIVER_CC *vmo_getmode)(struct video_monitor *__restrict __self,
	                                  struct video_monitor_mode *__restrict __mode);

	/* Set the video mode to-be used. After a call to this function,
	 * you  are probably going to have to re-acquire a new reference
	 * to the monitor's display buffer.
	 * @return: 0 : Success
	 * @return: -1: Error (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_IN_T(2) int
	(LIBVIDEO_DRIVER_CC *vmo_setmode)(struct video_monitor *__restrict __self,
	                                  struct video_monitor_mode const *__restrict __mode);
};

#ifdef __INTELLISENSE__
/* Enumerate supported video modes
 * @return: >= 0: [errno=*] Sum of all return values of `__cb'
 * @return: -1:   [errno=*] Either `__cb' returned `-1', or enumeration failed
 * @return: < 0:  `__cb' returned this same negative value */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_NONNULL((2)) __ssize_t
video_monitor_lsmodes(struct video_monitor *__restrict __self,
                      video_monitor_lsmodes_cb_t __cb, void *__cookie);

/* Get the currently set video mode
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) int
video_monitor_getmode(struct video_monitor *__restrict __self,
                      struct video_monitor_mode *__restrict __mode);

/* Set the video mode to-be used. After a call to this function,
 * you  are probably going to have to re-acquire a new reference
 * to the monitor's display buffer.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN(2) int
video_monitor_setmode(struct video_monitor *__restrict __self,
                      struct video_monitor_mode const *__restrict __mode);

/* Helpers for performing video-display operations */
extern __ATTR_WUNUSED __ATTR_INOUT((1)) __REF struct video_buffer *
video_monitor_getbuffer(struct video_monitor *__restrict __self);
extern __ATTR_INOUT(1) __ATTR_IN(2) void
video_monitor_updaterect(struct video_monitor *__restrict __self,
                         struct video_rect const *__restrict __rect);
extern __ATTR_INOUT(1) __ATTR_INS(2, 3) void
video_monitor_updaterects(struct video_monitor *__restrict __self,
                          struct video_rect const *__restrict __rects,
                          __size_t __n_rects);

/* Return the domain/adapter associated with `__self' */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) struct video_domain const *
video_monitor_getdomain(struct video_monitor const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) struct video_adapter const *
video_monitor_getadapter(struct video_monitor const *__restrict __self);
#else /* __INTELLISENSE__ */
#define video_monitor_lsmodes(self, cb, cookie)         (*_video_monitor_getops(self)->vmo_lsmodes)(self, cb, cookie)
#define video_monitor_getmode(self, mode)               (*_video_monitor_getops(self)->vmo_getmode)(self, mode)
#define video_monitor_setmode(self, mode)               (*_video_monitor_getops(self)->vmo_setmode)(self, mode)
#define video_monitor_getbuffer(self)                   video_display_getbuffer(video_monitor_asdisplay(self))
#define video_monitor_updaterect(self, rect)            video_display_updaterect(video_monitor_asdisplay(self), rect)
#define video_monitor_updaterects(self, rects, n_rects) video_display_updaterects(video_monitor_asdisplay(self), rects, n_rects)
#define video_monitor_getdomain(self)                   video_display_getdomain(video_monitor_asdisplay(self))
#define video_monitor_getadapter(self)                  ((struct video_adapter const *)video_monitor_getdomain(self))
#endif /* !__INTELLISENSE__ */

struct video_monitor
#ifdef __cplusplus
    : video_display /* Underlying display */
#define _video_monitor__vm_display /* nothing */
#define video_monitor_asdisplay    /* nothing */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct video_display vm_display; /* Underlying display */
#define _video_monitor__vm_display vm_display.
#define video_monitor_asdisplay(x) (&(x)->vm_display)
#endif /* __cplusplus */
};

#define _video_monitor_getops(self) \
	((struct video_monitor_ops const *)(self)->_video_monitor__vm_display vd_ops)
#define video_monitor_incref(self) video_display_incref(video_monitor_asdisplay(self))
#define video_monitor_decref(self) video_display_decref(video_monitor_asdisplay(self))

#endif /* __CC__ */

__DECL_END

#endif /* !_LIBVIDEO_DRIVER_MONITOR_H */
