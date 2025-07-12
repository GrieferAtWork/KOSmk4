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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_CUSTOM_C
#define GUARD_LIBVIDEO_GFX_BUFFER_CUSTOM_C 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stddef.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/palette.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/api.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "../buffer.h"
#include "../gfx.h"
#include "../swgfx.h"
#include "custom.h"
#include "utils.h"

DECL_BEGIN

PRIVATE WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
custom_rlock(struct video_buffer *__restrict self,
             struct video_lock *__restrict lock) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	if (me->cb_rlock)
		return (*me->cb_rlock)(me->cb_cookie, lock);
	errno = ENOTSUP;
	return -1;
}

PRIVATE WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
custom_wlock(struct video_buffer *__restrict self,
             struct video_lock *__restrict lock) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	if (me->cb_wlock)
		return (*me->cb_wlock)(me->cb_cookie, lock);
	errno = ENOTSUP;
	return -1;
}

PRIVATE ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC custom_unlock)(struct video_buffer *__restrict self,
                           struct video_lock *__restrict lock) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	if (me->cb_unlock)
		(*me->cb_unlock)(me->cb_cookie, lock);
}


PRIVATE WUNUSED ATTR_INOUT(1) NONNULL((2)) int FCC
custom_rlockregion(struct video_buffer *__restrict self,
                   struct video_regionlock *__restrict lock) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	video_regionlock_assert(me, lock);
	if (me->cb_rlockregion)
		return (*me->cb_rlockregion)(me->cb_cookie, lock);
	if (me->cb_rlock) {
		int ok;
		size_t xoff;
		video_codec_xcoord_to_offset(self->vb_format.vf_codec,
		                             lock->_vrl_xmin, &xoff,
		                             &lock->vrl_xbas);
		ok = (*me->cb_rlock)(me->cb_cookie, &lock->vrl_lock);
		lock->vrl_lock.vl_data += lock->_vrl_ymin * lock->vrl_lock.vl_stride;
		lock->vrl_lock.vl_data += xoff;
		return ok;
	}
	errno = ENOTSUP;
	return -1;
}

PRIVATE WUNUSED ATTR_INOUT(1) NONNULL((2)) int FCC
custom_wlockregion(struct video_buffer *__restrict self,
                   struct video_regionlock *__restrict lock) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	video_regionlock_assert(me, lock);
	if (me->cb_wlockregion)
		return (*me->cb_wlockregion)(me->cb_cookie, lock);
	if (me->cb_wlock) {
		int ok;
		size_t xoff;
		video_codec_xcoord_to_offset(self->vb_format.vf_codec,
		                             lock->_vrl_xmin, &xoff,
		                             &lock->vrl_xbas);
		ok = (*me->cb_wlock)(me->cb_cookie, &lock->vrl_lock);
		lock->vrl_lock.vl_data += lock->_vrl_ymin * lock->vrl_lock.vl_stride;
		lock->vrl_lock.vl_data += xoff;
		return ok;
	}
	errno = ENOTSUP;
	return -1;
}

PRIVATE ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC custom_unlockregion)(struct video_buffer *__restrict self,
                                 struct video_regionlock *__restrict lock) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	video_regionlock_assert(me, lock);
	if (me->cb_unlockregion) {
		(*me->cb_unlockregion)(me->cb_cookie, lock);
	} else if (me->cb_unlock) {
		size_t xoff;
		video_coord_t xrem;
		video_codec_xcoord_to_offset(self->vb_format.vf_codec,
		                             lock->_vrl_xmin, &xoff, &xrem);
		assert(xrem == lock->vrl_xbas);
		lock->vrl_lock.vl_data -= lock->_vrl_ymin * lock->vrl_lock.vl_stride;
		lock->vrl_lock.vl_data -= xoff;
		(*me->cb_unlock)(me->cb_cookie, &lock->vrl_lock);
	}
}


/* Indices for driver-specific data of "custom" video buffers. */
struct gfx_customdrv: gfx_swdrv {
	video_buffer_custom_getpixel_t gcd_getpixel; /* [1..1][const] ... */
	video_buffer_custom_setpixel_t gcd_setpixel; /* [1..1][const] ... */
	void                          *gcd_cookie;   /* [?..?][const] ... */
};
#define video_customgfx_getdrv(self) \
	((struct gfx_customdrv *)(self)->_vx_driver)
static_assert(sizeof(struct gfx_customdrv) <= (_VIDEO_GFX_N_DRIVER * sizeof(void *)),
              "sizeof(struct gfx_customdrv) too large for '_VIDEO_GFX_N_DRIVER'");

PRIVATE ATTR_IN(1) video_pixel_t CC
custom_gfx__getpixel(struct video_gfx const *__restrict self,
                     video_coord_t abs_x, video_coord_t abs_y) {
	struct gfx_customdrv *drv = video_customgfx_getdrv(self);
	return (*drv->gcd_getpixel)(drv->gcd_cookie, abs_x, abs_y);
}

PRIVATE ATTR_IN(1) void CC
custom_gfx__setpixel(struct video_gfx const *__restrict self,
                     video_coord_t abs_x, video_coord_t abs_y,
                     video_pixel_t pixel) {
	struct gfx_customdrv *drv = video_customgfx_getdrv(self);
	(*drv->gcd_setpixel)(drv->gcd_cookie, abs_x, abs_y, pixel);
}


PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
custom_initgfx(struct video_gfx *__restrict self) {
	struct custom_buffer *me = (struct custom_buffer *)self->vx_buffer;
	struct gfx_customdrv *drv = video_customgfx_getdrv(self);
	libvideo_gfx_init_fullclip(self);
	drv->gcd_getpixel = me->cb_getpixel;
	drv->gcd_setpixel = me->cb_setpixel;
	drv->gcd_cookie   = me->cb_cookie;

	/* Default pixel accessors */
	drv->xsw_getpixel = &custom_gfx__getpixel;
	drv->xsw_setpixel = &custom_gfx__setpixel;

	/* Load generic operator defaults */
	libvideo_swgfx_populate(self);
	return self;
}

PRIVATE NONNULL((1)) void FCC
custom_destroy(struct video_buffer *__restrict self) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	if (me->cb_destroy)
		(*me->cb_destroy)(me->cb_cookie);
	free(self);
}


#undef custom_ops
PRIVATE struct video_buffer_ops custom_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _custom_ops(void) {
	if unlikely(!custom_ops.vi_destroy) {
		custom_ops.vi_rlock        = &custom_rlock;
		custom_ops.vi_wlock        = &custom_wlock;
		custom_ops.vi_unlock       = &custom_unlock;
		custom_ops.vi_rlockregion  = &custom_rlockregion;
		custom_ops.vi_wlockregion  = &custom_wlockregion;
		custom_ops.vi_unlockregion = &custom_unlockregion;
		custom_ops.vi_initgfx      = &custom_initgfx;
		custom_ops.vi_updategfx    = &libvideo_buffer_swgfx_updategfx;
		custom_ops.vi_noblendgfx   = &libvideo_buffer_swgfx_noblend;
		COMPILER_WRITE_BARRIER();
		custom_ops.vi_destroy = &custom_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &custom_ops;
}
#define custom_ops (*_custom_ops())


/* Construct a special video buffer which, rather than being backed by memory
 * or implemented using hardware acceleration,  does all its pixel I/O  using
 * the provided function pointers.
 *
 * WARNING: The  given  `getpixel'  / `setpixel'  callbacks  better be
 *          fast, or any GFX on the returned buffer will take forever!
 *
 * @param: size_x:   X dimension of the returned video buffer
 * @param: size_y:   Y dimension of the returned video buffer
 * @param: codec:    [1..1] Video codec used for color<=>pixel conversion, as
 *                          well  as  pixel  I/O (when  rlock/wlock  is given
 *                          and returns `0')
 * @param: palette:      [0..1] Palette to-be used with `codec' (if needed)
 * @param: getpixel:     [1..1] Mandatory pixel read operator (passed coords are absolute and guarantied in-bounds)
 * @param: setpixel:     [1..1] Mandatory pixel write operator (passed coords are absolute and guarantied in-bounds)
 * @param: destroy:      [0..1] Optional callback invoked when the returned buffer is destroyed
 * @param: rlock:        [0..1] Optional callback to lock video memory for reading (when missing, or doesn't return `0', `getpixel' is always used)
 * @param: wlock:        [0..1] Optional callback to lock video memory for writing (when missing, or doesn't return `0', `setpixel' is always used)
 * @param: unlock:       [0..1] Optional callback invoked to release video locks previously acquired by `rlock' or `wlock'
 * @param: rlockregion:  [0..1] Optional extension to `rlock' (when not supplied, implemented in terms of `rlock')
 * @param: wlockregion:  [0..1] Optional extension to `wlock' (when not supplied, implemented in terms of `wlock')
 * @param: unlockregion: [0..1] Optional extension to `unlock' (when not supplied, implemented in terms of `unlock')
 * @param: cookie:       [?..?] Cookie argument passed to all user-supplied operators */
DEFINE_PUBLIC_ALIAS(video_buffer_forcustom, libvideo_buffer_forcustom);
INTERN WUNUSED NONNULL((3, 5, 6)) REF struct video_buffer *CC
libvideo_buffer_forcustom(video_dim_t size_x, video_dim_t size_y,
                          struct video_codec const *codec, struct video_palette *palette,
                          video_buffer_custom_getpixel_t getpixel,
                          video_buffer_custom_setpixel_t setpixel,
                          video_buffer_custom_destroy_t destroy,
                          video_buffer_custom_lock_t rlock,
                          video_buffer_custom_lock_t wlock,
                          video_buffer_custom_unlock_t unlock,
                          video_buffer_custom_lockregion_t rlockregion,
                          video_buffer_custom_lockregion_t wlockregion,
                          video_buffer_custom_unlockregion_t unlockregion,
                          void *cookie) {
	REF struct custom_buffer *result;
	result = (REF struct custom_buffer *)malloc(sizeof(struct custom_buffer));
	if unlikely(!result)
		goto err;
	if (!(codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL))
		palette = NULL;
	result->vb_ops = &custom_ops;
	result->vb_format.vf_codec = codec;
	result->vb_format.vf_pal   = palette;
	if (palette)
		video_palette_incref(palette);
	result->vb_xdim         = size_x;
	result->vb_ydim         = size_y;
	result->vb_refcnt       = 1;
	result->cb_getpixel     = getpixel;
	result->cb_setpixel     = setpixel;
	result->cb_destroy      = destroy;
	result->cb_rlock        = rlock ? rlock : wlock;
	result->cb_wlock        = wlock;
	result->cb_unlock       = unlock;
	result->cb_rlockregion  = rlockregion ? rlockregion : wlockregion;
	result->cb_wlockregion  = wlockregion;
	result->cb_unlockregion = unlockregion;
	result->cb_cookie       = cookie;
	return result;
err:
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_CUSTOM_C */
