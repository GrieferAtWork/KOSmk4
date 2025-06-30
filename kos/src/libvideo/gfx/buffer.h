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

#define video_regionlock_assert(self, lock)                                                  \
	(__assertf(((lock)->_vrl_xmin + (lock)->_vrl_xdim) > (lock)->_vrl_xmin,                  \
	           "video_regionlock: X+SX overflows, or SX=0 [X=%" PRIuCRD ",SX=%" PRIuDIM "]", \
	           (lock)->_vrl_xmin, (lock)->_vrl_xdim),                                        \
	 __assertf(((lock)->_vrl_ymin + (lock)->_vrl_ydim) > (lock)->_vrl_ymin,                  \
	           "video_regionlock: Y+SY overflows, or SY=0 [Y=%" PRIuCRD ",SY=%" PRIuDIM "]", \
	           (lock)->_vrl_ymin, (lock)->_vrl_ydim),                                        \
	 __assertf(((lock)->_vrl_xmin + (lock)->_vrl_xdim) <= (self)->vb_xdim,                   \
	           "video_regionlock: X+SX overflows exceeds buffer dimension "                  \
	           "[X=%" PRIuCRD ",SX=%" PRIuDIM ",X+SX=%" PRIuDIM ",DIM=%" PRIuDIM "]",        \
	           (lock)->_vrl_xmin, (lock)->_vrl_xdim,                                         \
	           (lock)->_vrl_xmin + (lock)->_vrl_xdim, (self)->vb_xdim),                      \
	 __assertf(((lock)->_vrl_ymin + (lock)->_vrl_ydim) <= (self)->vb_ydim,                   \
	           "video_regionlock: Y+SY overflows exceeds buffer dimension "                  \
	           "[Y=%" PRIuCRD ",SY=%" PRIuDIM ",Y+SY=%" PRIuDIM ",DIM=%" PRIuDIM "]",        \
	           (lock)->_vrl_ymin, (lock)->_vrl_ydim,                                         \
	           (lock)->_vrl_ymin + (lock)->_vrl_ydim, (self)->vb_ydim))

/* Generic implementations for video buffer operators. */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_buffer_generic_updategfx(struct video_gfx *__restrict self, unsigned int what);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_buffer_generic_noblend(struct video_gfx *__restrict self);


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
#define libvideo_buffer_noop_unlockregion (*(void __NOTHROW_T(FCC *)(struct video_buffer *__restrict, struct video_regionlock *__restrict))&libvideo_buffer_noop_unlock)

#define video_buffer_ops_set_LOCKOPS_like_NOTSUP(self)                    \
	(void)((self)->vi_rlock        = &libvideo_buffer_notsup_rlock,       \
	       (self)->vi_wlock        = &libvideo_buffer_notsup_wlock,       \
	       (self)->vi_unlock       = &libvideo_buffer_noop_unlock,        \
	       (self)->vi_rlockregion  = &libvideo_buffer_notsup_rlockregion, \
	       (self)->vi_wlockregion  = &libvideo_buffer_notsup_wlockregion, \
	       (self)->vi_unlockregion = &libvideo_buffer_noop_unlockregion)


INTDEF WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) int FCC
libvideo_buffer_generic_rlockregion(struct video_buffer *__restrict self,
                                    struct video_regionlock *__restrict lock);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) int FCC
libvideo_buffer_generic_wlockregion(struct video_buffer *__restrict self,
                                    struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC libvideo_buffer_generic_unlockregion)(struct video_buffer *__restrict self,
                                                  struct video_regionlock *__restrict lock);




/* Convert `self' into the specified format.
 * @param: type: The type of buffer to-be returned (one of `VIDEO_BUFFER_*'). */
INTDEF WUNUSED NONNULL((1, 2)) REF struct video_buffer *CC
libvideo_buffer_convert(struct video_buffer *__restrict self,
                        struct video_codec const *codec,
                        struct video_palette *palette,
                        unsigned int type);

/* Same as `video_buffer_convert()', but always return a distinct buffer, even if formats match */
INTDEF WUNUSED NONNULL((1, 2)) REF struct video_buffer *CC
libvideo_buffer_convert_or_copy(struct video_buffer *__restrict self,
                                struct video_codec const *codec,
                                struct video_palette *palette,
                                unsigned int type);

/* Create a video buffer, or return NULL and set errno if creation failed.
 * NOTE: When the given `size_x' or `size_y' is ZERO(0), an empty buffer is returned
 *       which may not necessarily use the  given, or default `codec' and  `palette'
 * @param: codec:   The preferred video codec, or NULL to use `video_preferred_format()'.
 * @param: palette: The palette to use (only needed if used by `codec') */
INTDEF WUNUSED REF struct video_buffer *CC
libvideo_buffer_create(unsigned int type, video_dim_t size_x, video_dim_t size_y,
                       struct video_codec const *codec, struct video_palette *palette);

/* Return the preferred video format.
 * If  possible, this format will match the format used by the host's graphics card.
 * If no graphics card exists, or the card isn't clear on its preferred format, some
 * other, common format will be returned instead. */
INTDEF ATTR_RETNONNULL WUNUSED struct video_format const *CC libvideo_preferred_format(void);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_H */
