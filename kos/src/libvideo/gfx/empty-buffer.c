/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVIDEO_GFX_EMPTY_BUFFER_C
#define GUARD_LIBVIDEO_GFX_EMPTY_BUFFER_C 1
#define _KOS_SOURCE 1

#include "empty-buffer.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "buffer.h"
#include "gfx.h"

DECL_BEGIN

/* Stub GFX functions for the empty video buffer. */
INTERN ATTR_CONST NONNULL((1)) video_color_t CC
video_gfx_empty_getcolor(struct video_gfx const *__restrict UNUSED(self),
                         uintptr_t UNUSED(x), uintptr_t UNUSED(y)) {
	return 0;
}

INTERN NONNULL((1)) void CC
video_gfx_empty_putcolor(struct video_gfx *__restrict UNUSED(self),
                         uintptr_t UNUSED(x), uintptr_t UNUSED(y),
                         video_color_t UNUSED(color)) {
}

PRIVATE NONNULL((1)) void CC
video_gfx_empty_line(struct video_gfx *__restrict UNUSED(self),
                     intptr_t UNUSED(x1), intptr_t UNUSED(y1),
                     intptr_t UNUSED(x2), intptr_t UNUSED(y2),
                     video_color_t UNUSED(color)) {
}

PRIVATE NONNULL((1)) void CC
video_gfx_empty_vhline(struct video_gfx *__restrict UNUSED(self),
                       intptr_t UNUSED(x), intptr_t UNUSED(y),
                       size_t UNUSED(length), video_color_t UNUSED(color)) {
}

PRIVATE NONNULL((1)) void CC
video_gfx_empty_fill(struct video_gfx *__restrict UNUSED(self),
                     intptr_t UNUSED(x), intptr_t UNUSED(y),
                     size_t UNUSED(size_x), size_t UNUSED(size_y),
                     video_color_t UNUSED(color)) {
}

PRIVATE NONNULL((1)) void CC
video_gfx_empty_rect(struct video_gfx *__restrict UNUSED(self),
                     intptr_t UNUSED(x), intptr_t UNUSED(y),
                     size_t UNUSED(size_x), size_t UNUSED(size_y),
                     video_color_t UNUSED(color)) {
}

PRIVATE NONNULL((1, 4)) void CC
video_gfx_empty_blit(struct video_gfx *UNUSED(self),
                     intptr_t UNUSED(dst_x), intptr_t UNUSED(dst_y),
                     struct video_gfx const *UNUSED(src),
                     intptr_t UNUSED(src_x), intptr_t UNUSED(src_y),
                     size_t UNUSED(size_x), size_t UNUSED(size_y)) {
}

PRIVATE NONNULL((1, 6)) void CC
video_gfx_empty_stretch(struct video_gfx *UNUSED(self),
                        intptr_t UNUSED(dst_x), intptr_t UNUSED(dst_y),
                        size_t UNUSED(dst_size_x), size_t UNUSED(dst_size_y),
                        struct video_gfx const *UNUSED(src),
                        intptr_t UNUSED(src_x), intptr_t UNUSED(src_y),
                        size_t UNUSED(src_size_x), size_t UNUSED(src_size_y)) {
}

PRIVATE NONNULL((1, 7)) void CC
video_gfx_empty_bitfill(struct video_gfx *__restrict UNUSED(self),
                        intptr_t UNUSED(x), intptr_t UNUSED(y),
                        video_color_t UNUSED(color),
                        size_t UNUSED(size_x), size_t UNUSED(size_y),
                        void const *__restrict UNUSED(bitmask),
                        uintptr_t UNUSED(bitskip), size_t UNUSED(bitscan)) {
}

PRIVATE NONNULL((1, 4, 9)) void CC
video_gfx_empty_bitblit(struct video_gfx *UNUSED(self),
                        intptr_t UNUSED(dst_x), intptr_t UNUSED(dst_y),
                        struct video_gfx const *UNUSED(src),
                        intptr_t UNUSED(src_x), intptr_t UNUSED(src_y),
                        size_t UNUSED(size_x), size_t UNUSED(size_y),
                        void const *__restrict UNUSED(bitmask),
                        uintptr_t UNUSED(bitskip), size_t UNUSED(bitscan)) {
}

PRIVATE NONNULL((1, 9)) void CC
video_gfx_empty_bitstretchfill(struct video_gfx *__restrict UNUSED(self),
                               intptr_t UNUSED(dst_x), intptr_t UNUSED(dst_y),
                               size_t UNUSED(dst_size_x), size_t UNUSED(dst_size_y),
                               video_color_t UNUSED(color),
                               size_t UNUSED(src_size_x), size_t UNUSED(src_size_y),
                               void const *__restrict UNUSED(bitmask),
                               uintptr_t UNUSED(bitskip), size_t UNUSED(bitscan)) {
}

PRIVATE NONNULL((1, 6, 11)) void CC
video_gfx_empty_bitstretchblit(struct video_gfx *UNUSED(self),
                               intptr_t UNUSED(dst_x), intptr_t UNUSED(dst_y),
                               size_t UNUSED(dst_size_x), size_t UNUSED(dst_size_y),
                               struct video_gfx const *UNUSED(src),
                               intptr_t UNUSED(src_x), intptr_t UNUSED(src_y),
                               size_t UNUSED(src_size_x), size_t UNUSED(src_size_y),
                               void const *__restrict UNUSED(bitmask),
                               uintptr_t UNUSED(bitskip), size_t UNUSED(bitscan)) {
}




PRIVATE struct video_gfx_ops video_gfx_empty_ops = {};

/* Return GFX operators for an empty video buffer. */
INTERN ATTR_RETNONNULL WUNUSED
struct video_gfx_ops *CC libvideo_getemptygfxops(void) {
	if unlikely(!video_gfx_empty_ops.fxo_line) {
		video_gfx_empty_ops.fxo_vline          = &video_gfx_empty_vhline;
		video_gfx_empty_ops.fxo_hline          = &video_gfx_empty_vhline;
		video_gfx_empty_ops.fxo_fill           = &video_gfx_empty_fill;
		video_gfx_empty_ops.fxo_rect           = &video_gfx_empty_rect;
		video_gfx_empty_ops.fxo_blit           = &video_gfx_empty_blit;
		video_gfx_empty_ops.fxo_stretch        = &video_gfx_empty_stretch;
		video_gfx_empty_ops.fxo_bitfill        = &video_gfx_empty_bitfill;
		video_gfx_empty_ops.fxo_bitblit        = &video_gfx_empty_bitblit;
		video_gfx_empty_ops.fxo_bitstretchfill = &video_gfx_empty_bitstretchfill;
		video_gfx_empty_ops.fxo_bitstretchblit = &video_gfx_empty_bitstretchblit;
		COMPILER_WRITE_BARRIER();
		video_gfx_empty_ops.fxo_line = &video_gfx_empty_line;
		COMPILER_WRITE_BARRIER();
	}
	return &video_gfx_empty_ops;
}




PRIVATE NONNULL((1)) void LIBVIDEO_GFX_CC
video_buffer_empty_destroy(struct video_buffer *__restrict self) {
	(void)self;
	assert_failed("Must never get here!");
}

PRIVATE byte_t const video_buffer_empty_data[1] = { 0 };

PRIVATE NONNULL((1, 2)) int CC
video_buffer_empty_lock(struct video_buffer *__restrict UNUSED(self),
                        struct video_lock *__restrict result) {
	/* Must   assign   a  valid,   non-NULL,  but   empty  buffer.
	 * Technically, any arbitrary non-NULL address would work, but
	 * set an actual, read-only buffer so-as to catch bad  writes. */
	result->vl_data   = (byte_t *)video_buffer_empty_data;
	result->vl_size   = 0;
	result->vl_stride = 0;
	return 0;
}

PRIVATE NONNULL((1, 2)) void
NOTHROW(CC video_buffer_empty_unlock)(struct video_buffer *__restrict UNUSED(self),
                                      struct video_lock const *__restrict lock) {
	assert(lock->vl_data == (byte_t *)video_buffer_empty_data);
	assert(lock->vl_size == 0);
	assert(lock->vl_stride == 0);
	(void)lock;
}

PRIVATE NONNULL((1, 2)) void CC
video_buffer_empty_getgfx(struct video_buffer *__restrict self,
                          struct video_gfx *__restrict result,
                          gfx_blendmode_t blendmode, uintptr_t flags,
                          video_color_t colorkey,
                          struct video_buffer_rect const *UNUSED(clip)) {
	result->vx_pxops.fxo_getcolor = &video_gfx_empty_getcolor;
	result->vx_pxops.fxo_putcolor = &video_gfx_empty_putcolor;
	result->vx_ops                = libvideo_getemptygfxops();
	result->vx_buffer             = self;
	result->vx_blend              = blendmode;
	result->vx_flags              = flags;
	result->vx_colorkey           = colorkey;
	result->vx_offt_x             = 0;
	result->vx_offt_y             = 0;
	result->vx_xmin               = 0;
	result->vx_ymin               = 0;
	result->vx_xend               = 0;
	result->vx_yend               = 0;
}

PRIVATE NONNULL((1, 2)) void CC
video_buffer_empty_clipgfx(struct video_gfx const *gfx,
                           struct video_gfx *result,
                           intptr_t UNUSED(start_x), intptr_t UNUSED(start_y),
                           size_t UNUSED(size_x), size_t UNUSED(size_y)) {
	result->vx_pxops.fxo_getcolor = &video_gfx_empty_getcolor;
	result->vx_pxops.fxo_putcolor = &video_gfx_empty_putcolor;
	result->vx_ops                = libvideo_getemptygfxops();
	result->vx_buffer             = gfx->vx_buffer;
	result->vx_blend              = gfx->vx_blend;
	result->vx_flags              = gfx->vx_flags;
	result->vx_colorkey           = gfx->vx_colorkey;
	result->vx_offt_x             = 0;
	result->vx_offt_y             = 0;
	result->vx_xmin               = 0;
	result->vx_ymin               = 0;
	result->vx_xend               = 0;
	result->vx_yend               = 0;
}

PRIVATE struct video_buffer_ops video_buffer_empty_ops = {};

/* Return operators for an empty video buffer. */
INTDEF ATTR_RETNONNULL WUNUSED
struct video_buffer_ops *CC libvideo_getemptybufferops(void) {
	if unlikely(!video_buffer_empty_ops.vi_getgfx) {
		video_buffer_empty_ops.vi_destroy = &video_buffer_empty_destroy;
		video_buffer_empty_ops.vi_lock    = &video_buffer_empty_lock;
		video_buffer_empty_ops.vi_unlock  = &video_buffer_empty_unlock;
		video_buffer_empty_ops.vi_clipgfx = &video_buffer_empty_clipgfx;
		COMPILER_WRITE_BARRIER();
		video_buffer_empty_ops.vi_getgfx = &video_buffer_empty_getgfx;
		COMPILER_WRITE_BARRIER();
	}
	return &video_buffer_empty_ops;
}


PRIVATE struct video_buffer video_buffer_empty = {};

INTERN ATTR_RETNONNULL WUNUSED
struct video_buffer *CC libvideo_getemptybuffer(void) {
	if unlikely(!video_buffer_empty.vb_ops) {
		struct video_buffer_ops *ops;
		video_buffer_empty.vb_refcnt = 1;
		video_buffer_empty.vb_size_x = 0;
		video_buffer_empty.vb_size_y = 0;
		/* The codec doesn't really matter, but use the most common one (RGBA8888) */
		video_buffer_empty.vb_format.vf_codec = video_codec_lookup(VIDEO_CODEC_RGBA8888);
		video_buffer_empty.vb_format.vf_pal   = NULL;
		ops = libvideo_getemptybufferops();
		COMPILER_WRITE_BARRIER();
		video_buffer_empty.vb_ops = ops;
		COMPILER_WRITE_BARRIER();
	}
	return &video_buffer_empty;
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_EMPTY_BUFFER_C */
