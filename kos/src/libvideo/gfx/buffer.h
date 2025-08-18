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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_H
#define GUARD_LIBVIDEO_GFX_BUFFER_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <assert.h>

#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
#include "gfx-utils.h"

DECL_BEGIN

#define _video_buffer_assert_rect(context, self, rect)                                \
	(__assertf(((rect)->vcr_xmin + (rect)->vcr_xdim) > (rect)->vcr_xmin,              \
	           context ": X+SX overflows, or SX=0 [X=%" PRIuCRD ",SX=%" PRIuDIM "]",  \
	           (rect)->vcr_xmin, (rect)->vcr_xdim),                                   \
	 __assertf(((rect)->vcr_ymin + (rect)->vcr_ydim) > (rect)->vcr_ymin,              \
	           context ": Y+SY overflows, or SY=0 [Y=%" PRIuCRD ",SY=%" PRIuDIM "]",  \
	           (rect)->vcr_ymin, (rect)->vcr_ydim),                                   \
	 __assertf(((rect)->vcr_xmin + (rect)->vcr_xdim) <= video_buffer_getxdim(self),   \
	           context ": X+SX overflows exceeds buffer dimension "                   \
	           "[X=%" PRIuCRD ",SX=%" PRIuDIM ",X+SX=%" PRIuDIM ",DIM=%" PRIuDIM "]", \
	           (rect)->vcr_xmin, (rect)->vcr_xdim,                                    \
	           (rect)->vcr_xmin + (rect)->vcr_xdim, video_buffer_getxdim(self)),      \
	 __assertf(((rect)->vcr_ymin + (rect)->vcr_ydim) <= video_buffer_getydim(self),   \
	           context ": Y+SY overflows exceeds buffer dimension "                   \
	           "[Y=%" PRIuCRD ",SY=%" PRIuDIM ",Y+SY=%" PRIuDIM ",DIM=%" PRIuDIM "]", \
	           (rect)->vcr_ymin, (rect)->vcr_ydim,                                    \
	           (rect)->vcr_ymin + (rect)->vcr_ydim, video_buffer_getydim(self)))
#define video_buffer_assert_rect(self, rect) \
	_video_buffer_assert_rect("assert_rect", self, rect)
#define video_regionlock_assert(self, lock) \
	_video_buffer_assert_rect("video_regionlock", self, &(lock)->_vrl_rect)

/* Generic implementations for video buffer operators. */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_buffer_swgfx_updategfx(struct video_gfx *__restrict self, unsigned int what);


#define libvideo_buffer_notsup__rlock libvideo_buffer_notsup__lock
#define libvideo_buffer_notsup__wlock libvideo_buffer_notsup__lock
INTDEF WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) int FCC
libvideo_buffer_notsup__lock(struct video_buffer *__restrict self,
                             struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC libvideo_buffer_noop__unlock)(struct video_buffer *__restrict self,
                                          struct video_lock *__restrict lock);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC libvideo_buffer_noop__revoke)(struct video_buffer *__restrict self);


#define libvideo_buffer_notsup__rlockregion libvideo_buffer_notsup__lockregion
#define libvideo_buffer_notsup__wlockregion libvideo_buffer_notsup__lockregion
#define libvideo_buffer_notsup__lockregion (*(int (FCC *)(struct video_buffer *__restrict, struct video_regionlock *__restrict))&libvideo_buffer_notsup__lock)
#define libvideo_buffer_noop__unlockregion (*(void NOTHROW_T(FCC *)(struct video_buffer *__restrict, struct video_regionlock *__restrict))&libvideo_buffer_noop__unlock)

#ifdef CONFIG_LIBVIDEO_HAVE_SERIALIZATION
#define __video_buffer_ops_set_fdinfo(self, cb) (void)((self)->vi_fdinfo = (cb))
#else /* CONFIG_LIBVIDEO_HAVE_SERIALIZATION */
#define __video_buffer_ops_set_fdinfo(self, cb) (void)0
#endif /* !CONFIG_LIBVIDEO_HAVE_SERIALIZATION */

#define DEFINE_VIDEO_BUFFER_TYPE(name, vi_destroy_, vi_initgfx_, vi_updategfx_, vi_rlock_, vi_wlock_, \
                                 vi_unlock_, vi_rlockregion_, vi_wlockregion_, vi_unlockregion_,      \
                                 vi_fdinfo_, vi_revoke_, vi_subregion_)                               \
	INTERN struct video_buffer_ops name = {};                                                         \
	INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _##name(void) {                  \
		if unlikely(!name.vi_destroy) {                                                               \
			name.vi_initgfx      = vi_initgfx_;                                                       \
			name.vi_updategfx    = vi_updategfx_;                                                     \
			name.vi_rlock        = vi_rlock_;                                                         \
			name.vi_wlock        = vi_wlock_;                                                         \
			name.vi_unlock       = vi_unlock_;                                                        \
			name.vi_rlockregion  = vi_rlockregion_;                                                   \
			name.vi_wlockregion  = vi_wlockregion_;                                                   \
			name.vi_unlockregion = vi_unlockregion_;                                                  \
			name.vi_revoke       = vi_revoke_;                                                        \
			name.vi_subregion    = vi_subregion_;                                                     \
			__video_buffer_ops_set_fdinfo(&name, vi_fdinfo_);                                         \
			COMPILER_WRITE_BARRIER();                                                                 \
			name.vi_destroy = vi_destroy_;                                                            \
			COMPILER_WRITE_BARRIER();                                                                 \
		}                                                                                             \
		return &name;                                                                                 \
	}


INTDEF WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) int FCC
libvideo_buffer_generic__rlockregion(struct video_buffer *__restrict self,
                                     struct video_regionlock *__restrict lock);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) int FCC
libvideo_buffer_generic__wlockregion(struct video_buffer *__restrict self,
                                     struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC libvideo_buffer_generic__unlockregion)(struct video_buffer *__restrict self,
                                                   struct video_regionlock *__restrict lock);


/* Convert `self' into the specified domain and format.
 *
 * If `self' specifies rotation/etc. in its GFX flags, and that rotation  differs
 * from whatever is specified by `format' (including the case where the state  of
 * the `VIDEO_GFX_F_XYSWAP' flag  differs, meaning dimensions  of `self' and  the
 * returned buffer won't match up), that rotation info is materialized, such that
 * this function can also be  used to rotate the actual  V-mem of a video  buffer
 * whilst at the same time copying/converting it into a different format.
 *
 * @return: * : The converted video buffer.
 * @return: NULL: [errno=ENOMEM]  Insufficient memory (either regular RAM, or V-RAM)
 * @return: NULL: [errno=ENOTSUP] Given `format->vbf_codec' is not supported by `domain ?: video_surface_getdomain(self)'
 * @return: NULL: [errno=*] Failed to convert buffer for some reason (s.a. `errno') */
INTDEF WUNUSED ATTR_IN(1) NONNULL((2)) ATTR_IN(3) REF struct video_buffer *CC
libvideo_surface_convert(struct video_surface const *__restrict self,
                         struct video_domain const *domain,
                         struct video_buffer_format const *format);
INTDEF WUNUSED ATTR_IN(1) NONNULL((2)) ATTR_IN(3) REF struct video_buffer *CC
libvideo_surface_convert_distinct(struct video_surface const *__restrict self,
                                  struct video_domain const *domain,
                                  struct video_buffer_format const *format);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_H */
