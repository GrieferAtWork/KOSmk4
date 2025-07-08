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
#ifndef _LIBVIDEO_GFX_SCREEN_H
#define _LIBVIDEO_GFX_SCREEN_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>
#include <kos/anno.h>

#include <libvideo/codec/types.h>

#include "buffer.h"

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

#ifdef __CC__
__DECL_BEGIN

struct screen_buffer;
struct screen_buffer_ops {
	struct video_buffer_ops sbo_video; /* Basic video buffer operators. */
	/* NOTE: _ALL_ Callbacks are always [1..1] */

	/* Indicate to the video chipset that `rect' has changed and should be
	 * updated on-screen. Some chipsets require this call, though not  all
	 * do. Where this call isn't required, these are no-ops.
	 *
	 * This function will automatically clamp out-of-bounds parts of rects
	 * such that they are always in-bounds. */
	__ATTR_NONNULL_T((1, 2)) void
	(LIBVIDEO_GFX_CC *sbo_updaterect)(struct screen_buffer *__restrict self,
	                                  struct video_crect const *__restrict rect);

	/* Same as `sbo_updaterect()', but update multiple rects at once. */
	__ATTR_NONNULL_T((1, 2)) void
	(LIBVIDEO_GFX_CC *sbo_updaterects)(struct screen_buffer *__restrict self,
	                                   struct video_crect const *__restrict rects,
	                                   __size_t n_rects);
};


/* Return the custom operator table of "self" */
#define screen_buffer_getops(self) \
	((struct screen_buffer_ops *)(self)->_screen_buffer__sb_video vb_ops)
#define screen_buffer_updaterect(self, rect) \
	(*screen_buffer_getops(self)->sbo_updaterect)(self, rect)
#define screen_buffer_updaterects(self, rects, n_rects) \
	(*screen_buffer_getops(self)->sbo_updaterects)(self, rects, n_rects)


#ifdef __cplusplus
__CXXDECL_BEGIN
#endif /* __cplusplus */

struct screen_buffer
#ifdef __cplusplus
    : video_buffer
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct video_buffer sb_video; /* Underlying video controller */
#define _screen_buffer__sb_video sb_video.
#define screen_buffer_asvideo(self) (&(self)->sb_video)
#else /* __cplusplus */
#define _screen_buffer__sb_video /* nothing */
#define screen_buffer_asvideo(self) (self)
#endif /* !__cplusplus */

#ifdef __cplusplus
#ifndef GUARD_LIBVIDEO_GFX_API_H
	__CXX_DELETE_CTOR(screen_buffer);
	__CXX_DELETE_DTOR(screen_buffer);
	__CXX_DELETE_COPY(screen_buffer);
	__CXX_DELETE_COPY_ASSIGN(screen_buffer);
#endif /* !GUARD_LIBVIDEO_GFX_API_H */
public:

	__CXX_CLASSMEMBER __ATTR_NONNULL_CXX((1)) void LIBVIDEO_GFX_CC
	updaterect(struct video_crect const *__restrict rect) {
		screen_buffer_updaterect(this, rect);
	}

	__CXX_CLASSMEMBER __ATTR_NONNULL_CXX((1)) void LIBVIDEO_GFX_CC
	updaterect(video_coord_t x = 0, video_coord_t y = 0,
	           video_dim_t sx = VIDEO_DIM_MAX,
	           video_dim_t sy = VIDEO_DIM_MAX) {
		struct video_crect rect;
		rect.vcr_xmin = x;
		rect.vcr_ymin = y;
		rect.vcr_xdim = sx;
		rect.vcr_ydim = sy;
		screen_buffer_updaterect(this, &rect);
	}

	__CXX_CLASSMEMBER __ATTR_NONNULL_CXX((1)) void LIBVIDEO_GFX_CC
	updaterects(struct video_crect const *__restrict rects, __size_t n_rects) {
		screen_buffer_updaterects(this, rects, n_rects);
	}
#endif /* __cplusplus */
};

#ifdef __cplusplus
__CXXDECL_END
#endif /* __cplusplus */

struct screen_buffer_hint {
	video_dim_t    sbh_resx; /* Resolution in X */
	video_dim_t    sbh_resy; /* Resolution in Y */
	uint_least16_t sbh_hz;   /* Refresh rate */
	__SHIFT_TYPE__ sbh_bpp;  /* Color depth */
};


/* Creates+returns  a video buffer for the entire  screen (or return NULL and set
 * errno  on error). Note that screen buffer access requires `CAP_SYS_RAWIO', and
 * only  a single screen buffer can ever exist system-wide. If an attempt is made
 * to create a second screen buffer, this function will block until the first one
 * is destroyed, or the processing owning it exits.
 *
 * @param: hint: Hint regarding the intended video resolution (or "NULL" to  just
 *               use the same video mode as had already been set by whatever came
 *               before us). */
typedef __ATTR_WUNUSED_T __REF struct screen_buffer *
(LIBVIDEO_GFX_CC *PSCREEN_BUFFER_CREATE)(struct screen_buffer_hint *__hint);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct screen_buffer *LIBVIDEO_GFX_CC
screen_buffer_create(struct screen_buffer_hint *__hint);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_SCREEN_H */
