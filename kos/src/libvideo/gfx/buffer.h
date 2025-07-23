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

#define video_regionlock_assert(self, lock)                                                            \
	(__assertf(((lock)->_vrl_rect.vcr_xmin + (lock)->_vrl_rect.vcr_xdim) > (lock)->_vrl_rect.vcr_xmin, \
	           "video_regionlock: X+SX overflows, or SX=0 [X=%" PRIuCRD ",SX=%" PRIuDIM "]",           \
	           (lock)->_vrl_rect.vcr_xmin, (lock)->_vrl_rect.vcr_xdim),                                \
	 __assertf(((lock)->_vrl_rect.vcr_ymin + (lock)->_vrl_rect.vcr_ydim) > (lock)->_vrl_rect.vcr_ymin, \
	           "video_regionlock: Y+SY overflows, or SY=0 [Y=%" PRIuCRD ",SY=%" PRIuDIM "]",           \
	           (lock)->_vrl_rect.vcr_ymin, (lock)->_vrl_rect.vcr_ydim),                                \
	 __assertf(((lock)->_vrl_rect.vcr_xmin + (lock)->_vrl_rect.vcr_xdim) <= (self)->vb_xdim,           \
	           "video_regionlock: X+SX overflows exceeds buffer dimension "                            \
	           "[X=%" PRIuCRD ",SX=%" PRIuDIM ",X+SX=%" PRIuDIM ",DIM=%" PRIuDIM "]",                  \
	           (lock)->_vrl_rect.vcr_xmin, (lock)->_vrl_rect.vcr_xdim,                                 \
	           (lock)->_vrl_rect.vcr_xmin + (lock)->_vrl_rect.vcr_xdim, (self)->vb_xdim),              \
	 __assertf(((lock)->_vrl_rect.vcr_ymin + (lock)->_vrl_rect.vcr_ydim) <= (self)->vb_ydim,           \
	           "video_regionlock: Y+SY overflows exceeds buffer dimension "                            \
	           "[Y=%" PRIuCRD ",SY=%" PRIuDIM ",Y+SY=%" PRIuDIM ",DIM=%" PRIuDIM "]",                  \
	           (lock)->_vrl_rect.vcr_ymin, (lock)->_vrl_rect.vcr_ydim,                                 \
	           (lock)->_vrl_rect.vcr_ymin + (lock)->_vrl_rect.vcr_ydim, (self)->vb_ydim))

/* Generic implementations for video buffer operators. */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_buffer_swgfx_updategfx(struct video_gfx *__restrict self, unsigned int what);


#define libvideo_buffer_notsup_rlock libvideo_buffer_notsup_lock
#define libvideo_buffer_notsup_wlock libvideo_buffer_notsup_lock
INTDEF WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) int FCC
libvideo_buffer_notsup_lock(struct video_buffer *__restrict self,
                            struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC libvideo_buffer_noop_unlock)(struct video_buffer *__restrict self,
                                         struct video_lock *__restrict lock);

#define libvideo_buffer_notsup_rlockregion libvideo_buffer_notsup_lockregion
#define libvideo_buffer_notsup_wlockregion libvideo_buffer_notsup_lockregion
#define libvideo_buffer_notsup_lockregion (*(int (FCC *)(struct video_buffer *__restrict, struct video_regionlock *__restrict))&libvideo_buffer_notsup_lock)
#define libvideo_buffer_noop_unlockregion (*(void NOTHROW_T(FCC *)(struct video_buffer *__restrict, struct video_regionlock *__restrict))&libvideo_buffer_noop_unlock)

#define video_buffer_ops_set_LOCKOPS_like_NOTSUP(self)                    \
	(void)((self)->vi_rlock        = &libvideo_buffer_notsup_rlock,       \
	       (self)->vi_wlock        = &libvideo_buffer_notsup_wlock,       \
	       (self)->vi_unlock       = &libvideo_buffer_noop_unlock,        \
	       (self)->vi_rlockregion  = &libvideo_buffer_notsup_rlockregion, \
	       (self)->vi_wlockregion  = &libvideo_buffer_notsup_wlockregion, \
	       (self)->vi_unlockregion = &libvideo_buffer_noop_unlockregion)

#define DEFINE_VIDEO_BUFFER_TYPE(name, vi_destroy_, vi_initgfx_, vi_updategfx_, vi_rlock_, vi_wlock_, \
                                 vi_unlock_, vi_rlockregion_, vi_wlockregion_, vi_unlockregion_,      \
                                 vi_revoke_, vi_subregion_)                                           \
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
			COMPILER_WRITE_BARRIER();                                                                 \
			name.vi_destroy = &vi_destroy_;                                                           \
			COMPILER_WRITE_BARRIER();                                                                 \
		}                                                                                             \
		return &name;                                                                                 \
	}


INTDEF WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) int FCC
libvideo_buffer_generic_rlockregion(struct video_buffer *__restrict self,
                                    struct video_regionlock *__restrict lock);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) int FCC
libvideo_buffer_generic_wlockregion(struct video_buffer *__restrict self,
                                    struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC libvideo_buffer_generic_unlockregion)(struct video_buffer *__restrict self,
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
