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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_BITMASK_C
#define GUARD_LIBVIDEO_GFX_BUFFER_BITMASK_C 1
#define __VIDEO_BUFFER_const /* nothing */

/* TODO: REMOVE THIS FILE */

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libvideo/color.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/codec/palette.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "../buffer.h"
#include "../gfx.h"
#include "../swgfx.h"
#include "../codec/codec.h"
#include "../codec/palette.h"
#include "old-bitmask.h"

DECL_BEGIN

PRIVATE NONNULL((1)) void FCC
bitmask_destroy(struct video_buffer *__restrict self) {
	free(self);
}

#define bitmask_rlock bitmask_lock
#define bitmask_wlock bitmask_lock
PRIVATE ATTR_INOUT(1) ATTR_OUT(2) int FCC
bitmask_lock(struct video_buffer *__restrict self,
             struct video_lock *__restrict lock) {
	struct old_bitmask_buffer *me = (struct old_bitmask_buffer *)self;
	if ((me->bmb_bm.vbm_scan & 7) || me->bmb_bm.vbm_skip) {
		/* Not scanline-aligned -> cannot "lock" into memory */
		errno = ENOTSUP;
		return -1;
	}
	lock->vl_data   = (byte_t *)me->bmb_bm.vbm_mask;
	lock->vl_stride = me->bmb_bm.vbm_scan >> 3;
	return 0;
}

#define bitmask_rlockregion bitmask_lockregion
#define bitmask_wlockregion bitmask_lockregion
PRIVATE ATTR_INOUT(1) NONNULL((2)) int FCC
bitmask_lockregion(struct video_buffer *__restrict self,
                   struct video_regionlock *__restrict lock) {
	struct old_bitmask_buffer *me = (struct old_bitmask_buffer *)self;
	video_regionlock_assert(me, lock);
	if (me->bmb_bm.vbm_scan & 7) {
		/* Not scanline-aligned -> cannot "lock" into memory */
		errno = ENOTSUP;
		return -1;
	}
	lock->vrl_lock.vl_stride = me->bmb_bm.vbm_scan >> 3;
	lock->vrl_lock.vl_data   = (byte_t *)me->bmb_bm.vbm_mask;
	lock->vrl_lock.vl_data += lock->vrl_lock.vl_stride * lock->_vrl_rect.vcr_ymin;
	lock->vrl_xbas = me->bmb_bm.vbm_skip + lock->_vrl_rect.vcr_xmin;
	return 0;
}

PRIVATE ATTR_IN(1) video_pixel_t CC
bitmask_gfx__getpixel(struct video_gfx const *__restrict self,
                      video_coord_t x, video_coord_t y) {
	struct old_bitmask_buffer *me = (struct old_bitmask_buffer *)video_gfx_getbuffer(self);
	uintptr_t bitoff = me->bmb_bm.vbm_skip + x + y * me->bmb_bm.vbm_scan;
	byte_t const *bm = (byte_t const *)me->bmb_bm.vbm_mask;
	return (bm[bitoff >> 3] >> (7 - (bitoff & 7))) & 1;
}

PRIVATE ATTR_IN(1) void CC
bitmask_gfx__setpixel(struct video_gfx const *__restrict self,
                      video_coord_t x, video_coord_t y,
                      video_pixel_t pixel) {
	struct old_bitmask_buffer *me = (struct old_bitmask_buffer *)video_gfx_getbuffer(self);
	uintptr_t bitoff = me->bmb_bm.vbm_skip + x + y * me->bmb_bm.vbm_scan;
	byte_t mask, value, *bm = (byte_t *)me->bmb_bm.vbm_mask;
	bm += bitoff >> 3;
	bitoff &= 7;
	mask = 1 << (7 - bitoff);
	value = mask * (pixel & 1);
	*bm = (*bm & ~mask) | value;
}

#ifndef __OPTIMIZE_SIZE__
struct gfx_bitmaskdrv: gfx_swdrv {
	video_color_t gbmd_pal[2]; /* Copy of palette */
};
#define video_bitmaskgfx_getdrv(self) \
	((struct gfx_bitmaskdrv *)(self)->_vx_driver)
static_assert(sizeof(struct gfx_bitmaskdrv) <= (_VIDEO_GFX_N_DRIVER * sizeof(void *)),
              "sizeof(struct gfx_bitmaskdrv) too large for '_VIDEO_GFX_N_DRIVER'");

PRIVATE ATTR_IN(1) video_color_t CC
bitmask_gfx__getcolor(struct video_gfx const *__restrict self,
                      video_coord_t x, video_coord_t y) {
	struct gfx_bitmaskdrv *drv = video_bitmaskgfx_getdrv(self);
	video_pixel_t pixel = bitmask_gfx__getpixel(self, x, y);
	return drv->gbmd_pal[pixel];
}

PRIVATE ATTR_INOUT(1) void CC
bitmask_gfx_optimize(struct video_gfx *__restrict self) {
	/* When no blending is being done, speed up color lookup by directly translating bits */
	struct gfx_bitmaskdrv *drv = video_bitmaskgfx_getdrv(self);
	if likely(drv->xsw_getcolor == &libvideo_swgfx_generic__getcolor) {
		struct old_bitmask_buffer *me = (struct old_bitmask_buffer *)video_gfx_getbuffer(self);
		drv->xsw_getcolor = &bitmask_gfx__getcolor;
		drv->gbmd_pal[0] = me->bmb_pal[0];
		drv->gbmd_pal[1] = me->bmb_pal[1];
	}
}

PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
bitmask_updategfx(struct video_gfx *__restrict self, unsigned int what) {
	self = libvideo_buffer_swgfx_updategfx(self, what);
	bitmask_gfx_optimize(self);
	return self;
}
#else /* !__OPTIMIZE_SIZE__ */
#define bitmask_gfx_optimize(self) (void)0
#define bitmask_updategfx          libvideo_buffer_swgfx_updategfx
#endif /* __OPTIMIZE_SIZE__ */



PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
bitmask_initgfx(struct video_gfx *__restrict self) {
	struct gfx_swdrv *drv = video_swgfx_getdrv(self);
	libvideo_gfx_init_fullclip(self);

	/* Default pixel accessors */
	drv->xsw_getpixel = &bitmask_gfx__getpixel;
	drv->xsw_setpixel = &bitmask_gfx__setpixel;

	/* Load generic operator defaults */
	libvideo_swgfx_populate(self);

	/* Optimizations for color reads */
	bitmask_gfx_optimize(self);
	return self;
}




PRIVATE struct video_buffer_ops old_bitmask_ops = {};
PRIVATE ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _old_bitmask_ops(void) {
	if unlikely(!old_bitmask_ops.vi_destroy) {
		old_bitmask_ops.vi_rlock        = &bitmask_rlock;
		old_bitmask_ops.vi_wlock        = &bitmask_wlock;
		old_bitmask_ops.vi_unlock       = &libvideo_buffer_noop_unlock;
		old_bitmask_ops.vi_rlockregion  = &bitmask_rlockregion;
		old_bitmask_ops.vi_wlockregion  = &bitmask_wlockregion;
		old_bitmask_ops.vi_unlockregion = &libvideo_buffer_noop_unlockregion;
		old_bitmask_ops.vi_initgfx      = &bitmask_initgfx;
		old_bitmask_ops.vi_updategfx    = &bitmask_updategfx;
		COMPILER_WRITE_BARRIER();
		old_bitmask_ops.vi_destroy = &bitmask_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &old_bitmask_ops;
}


/* Initialize a "struct old_bitmask_buffer"
 * @return: * : Always re-returns `self' */
INTERN ATTR_RETNONNULL ATTR_OUT(1) ATTR_IN(4) ATTR_IN(5) struct old_bitmask_buffer *CC
old_bitmask_buffer_init(struct old_bitmask_buffer *__restrict self,
                        video_dim_t size_x, video_dim_t size_y,
                        struct video_bitmask const *__restrict bm,
                        video_color_t const bg_fg_colors[2]) {
	memcpy(&self->bmb_bm, bm, sizeof(struct video_bitmask));
	self->bmb_bm.vbm_mask = (byte_t const *)self->bmb_bm.vbm_mask + (self->bmb_bm.vbm_skip >> 3);
	self->bmb_bm.vbm_skip &= 7;
	self->bmb_pal[0] = bg_fg_colors[0];
	self->bmb_pal[1] = bg_fg_colors[1];
	self->vb_surf.vs_pal    = video_palette_fromcolors(self->bmb_pal);
	self->vb_surf.vs_buffer = self;
	self->vb_surf.vs_flags  = VIDEO_GFX_F_NORMAL; /* Note how `VIDEO_GFX_F_PALOBJ' isn't set here! */
	/*self->vb_surf.vs_colorkey = 0;*/
	self->vb_codec = libvideo_codec_lookup(VIDEO_CODEC_P1_MSB);
	assert(self->vb_codec);
	self->vb_ops  = _old_bitmask_ops();
	self->vb_xdim = size_x;
	self->vb_ydim = size_y;
#ifndef NDEBUG
	self->vb_refcnt = 0; /* To hopefully cause assert fault it someone tries to incref() */
	memset(&self->vb_domain, 0xcc, sizeof(self->vb_domain));
#endif /* !NDEBUG */
	return self;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_BITMASK_C */
