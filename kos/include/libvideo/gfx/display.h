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
#ifndef _LIBVIDEO_GFX_DISPLAY_H
#define _LIBVIDEO_GFX_DISPLAY_H 1

#include "api.h"
/**/

#include <__stdinc.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/refcnt.h>

#ifdef __CC__
__DECL_BEGIN

struct video_rect;
struct video_display;

struct video_display_ops {
	/* NOTE: _ALL_ Callbacks are always [1..1] */

	/* Called when the display's reference counter hits 0 */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_CC *vdo_destroy)(struct video_display *__restrict self);

	/* Return  a  reference to  the video  buffer that  can be  used to
	 * read/write the currently  active display.  That returned  buffer
	 * can be used indefinitely, but video locks might become unusable,
	 * and pixel access might break if the display changes  resolution.
	 *
	 * This function should be called either:
	 * - Whenever some other system indicates that display memory (may)
	 *   have changed:
	 *   - When `__self' is a `video_monitor': the monitor's resolution was changed
	 *   - When `__self' is a `video_window': the window was resized, or the compositor
	 *     indicated that the window's buffer should be reloaded (the later can  happen
	 *     even without the window being resized, as a result of an overlapping  window
	 *     appearing or disappearing)
	 * - Or just whenever you're about to start rendering
	 *
	 * @return: * :   The currently active video buffer
	 * @return: NULL: Video I/O access failed (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T((1)) __REF struct video_buffer *
	(LIBVIDEO_GFX_CC *vdo_getbuffer)(struct video_display *__restrict __self);

	/* TODO: Operator for changing/updating the palette used by `vdo_getbuffer' */
	/* TODO: Operator to test if display is in V-blank right now (non-monitor-buffers always return "true" here)
	 *       Using  this operator, code can then wait for  V-blank to happen in order to prevent screen-tearing. */

	/* Indicate  that the contents of a given physical rect have changed.
	 * Chipset drivers might need this  to propagate changes to  actually
	 * appear on-screen, and a compositor might need this to do its thing
	 * and composite the specified rects and make them visible. */
	__ATTR_INOUT_T(1) __ATTR_IN_T(2) void
	(LIBVIDEO_GFX_CC *vdo_updaterect)(struct video_display *__restrict __self,
	                                  struct video_rect const *__restrict __rect);

	/* Same as `vdo_updaterect()', but update multiple rects at once. */
	__ATTR_INOUT_T(1) __ATTR_INS_T(2, 3) void
	(LIBVIDEO_GFX_CC *vdo_updaterects)(struct video_display *__restrict __self,
	                                   struct video_rect const *__restrict __rects,
	                                   __size_t __n_rects);
};



#ifdef __INTELLISENSE__
/* Return  a  reference to  the video  buffer that  can be  used to
 * read/write the currently  active display.  That returned  buffer
 * can be used indefinitely, but video locks might become unusable,
 * and pixel access might break if the display changes  resolution.
 *
 * This function should be called either:
 * - Whenever some other system indicates that display memory (may)
 *   have changed:
 *   - When `__self' is a `video_monitor': the monitor's resolution was changed
 *   - When `__self' is a `video_window': the window was resized, or the compositor
 *     indicated that the window's buffer should be reloaded (the later can  happen
 *     even without the window being resized, as a result of an overlapping  window
 *     appearing or disappearing)
 * - Or just whenever you're about to start rendering
 *
 * @return: * :   The currently active video buffer
 * @return: NULL: Video I/O access failed (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT((1)) __REF struct video_buffer *
video_display_getbuffer(struct video_display *__restrict __self);

/* Indicate  that the contents of a given physical rect have changed.
 * Chipset drivers might need this  to propagate changes to  actually
 * appear on-screen, and a compositor might need this to do its thing
 * and composite the specified rects and make them visible. */
extern __ATTR_INOUT(1) __ATTR_IN(2) void
video_display_updaterect(struct video_display *__restrict __self,
                         struct video_rect const *__restrict __rect);

/* Same as `video_display_updaterect()', but update multiple rects at once. */
extern __ATTR_INOUT(1) __ATTR_INS(2, 3) void
video_display_updaterects(struct video_display *__restrict __self,
                          struct video_rect const *__restrict __rects,
                          __size_t __n_rects);

/* Return the domain associated with `__self' */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) struct video_domain const *
video_display_getdomain(struct video_display const *__restrict __self);
#else /* __INTELLISENSE__ */
#define video_display_getbuffer(self)                   (*(self)->vd_ops->vdo_getbuffer)(self)
#define video_display_updaterect(self, rect)            (*(self)->vd_ops->vdo_updaterect)(self, rect)
#define video_display_updaterects(self, rects, n_rects) (*(self)->vd_ops->vdo_updaterects)(self, rects, n_rects)
#define video_display_getdomain(self)                   (self)->vd_domain
#endif /* !__INTELLISENSE__ */


/************************************************************************/
/* VIDEO_DISPLAY: Common base for video_monitor and video_window        */
/************************************************************************/
struct video_display {
	struct video_display_ops const *vd_ops;    /* [1..1][const] Display operators */
	struct video_domain const      *vd_domain; /* [1..1][const] Display domain */
	__uintptr_t                     vd_refcnt; /* Reference counter. */
};

#define video_display_destroy(self) (*(self)->vd_ops->vdo_destroy)(self)
#define video_display_incref(self) \
	__hybrid_atomic_inc(&(self)->vd_refcnt, __ATOMIC_SEQ_CST)
#define video_display_decref(self)                                           \
	(void)(__hybrid_atomic_decfetch(&(self)->vd_refcnt, __ATOMIC_SEQ_CST) || \
	       (video_display_destroy(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_display, vd_refcnt, video_display_destroy)



/* Create a video_display wrapper for a simple video buffer.
 * - `video_display_getbuffer()' always returns `__buffer' and never fails
 * - `video_display_updaterect()' is a no-op
 * - `video_display_updaterects()' is a no-op
 *
 * @return: * :   The display wrapper for `__buffer'
 * @return: NULL: [errno=ENOMEM] Out of memory. */
typedef __ATTR_WUNUSED_T __ATTR_INOUT_T(1) __REF struct video_display *
(LIBVIDEO_GFX_CC *PVIDEO_DISPLAY_FORBUFFER)(struct video_buffer *__restrict __buffer);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_INOUT(1) __REF struct video_display *LIBVIDEO_GFX_CC
video_display_forbuffer(struct video_buffer *__restrict __buffer);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_DISPLAY_H */
