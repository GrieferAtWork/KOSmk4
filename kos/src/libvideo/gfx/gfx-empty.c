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
#ifndef GUARD_LIBVIDEO_GFX_GFX_EMPTY_C
#define GUARD_LIBVIDEO_GFX_GFX_EMPTY_C 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
/**/

#include "gfx-empty.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_blit *CC
libvideo_gfx_empty__blitfrom(struct video_blit *__restrict ctx) {
	ctx->vb_ops = &libvideo_blit_empty_ops;
	DBG_memset(&ctx->vb_xops, 0xcc, sizeof(ctx->vb_xops));
	return ctx;
}

/* Empty GFX operators */
INTERN ATTR_IN(1) video_color_t CC
libvideo_gfx_empty_getcolor(struct video_gfx const *__restrict UNUSED(self),
                            video_offset_t UNUSED(x), video_offset_t UNUSED(y)) {
	COMPILER_IMPURE();
	return 0;
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_empty_putcolor(struct video_gfx const *__restrict UNUSED(self),
                            video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                            video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

DEFINE_INTERN_ALIAS(libvideo_gfx_empty_vline, libvideo_gfx_empty_hline);
INTERN ATTR_IN(1) void CC
libvideo_gfx_empty_hline(struct video_gfx const *__restrict UNUSED(self),
                         video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                         video_dim_t UNUSED(length), video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_empty_line(struct video_gfx const *__restrict UNUSED(self),
                        video_offset_t UNUSED(x1), video_offset_t UNUSED(y1),
                        video_offset_t UNUSED(x2), video_offset_t UNUSED(y2),
                        video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

DEFINE_INTERN_ALIAS(libvideo_gfx_empty_rect, libvideo_gfx_empty_fill);
INTERN ATTR_IN(1) void CC
libvideo_gfx_empty_fill(struct video_gfx const *__restrict UNUSED(self),
                        video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                        video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                        video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(7) void CC
libvideo_gfx_empty_bitfill(struct video_gfx const *__restrict UNUSED(self),
                           video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                           video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                           video_color_t UNUSED(color),
                           struct video_bitmask const *__restrict UNUSED(bm)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(9) void CC
libvideo_gfx_empty_bitstretchfill(struct video_gfx const *__restrict UNUSED(self),
                                  video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                                  video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                                  video_color_t UNUSED(color),
                                  video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y),
                                  struct video_bitmask const *__restrict UNUSED(bm)) {
	COMPILER_IMPURE();
}

#undef libvideo_gfx_empty_ops
PRIVATE struct video_gfx_ops libvideo_gfx_empty_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_empty_ops(void) {
	if unlikely(!libvideo_gfx_empty_ops.fxo_bitstretchfill) {
		libvideo_gfx_empty_ops.fxo_line    = &libvideo_gfx_empty_line;
		libvideo_gfx_empty_ops.fxo_hline   = &libvideo_gfx_empty_hline;
		libvideo_gfx_empty_ops.fxo_vline   = &libvideo_gfx_empty_vline;
		libvideo_gfx_empty_ops.fxo_fill    = &libvideo_gfx_empty_fill;
		libvideo_gfx_empty_ops.fxo_rect    = &libvideo_gfx_empty_rect;
		libvideo_gfx_empty_ops.fxo_bitfill = &libvideo_gfx_empty_bitfill;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_empty_ops.fxo_bitstretchfill = &libvideo_gfx_empty_bitstretchfill;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_gfx_empty_ops;
}
#define libvideo_gfx_empty_ops (*_libvideo_gfx_empty_ops())

/* Empty blit operators */
INTERN ATTR_IN(1) void CC
libvideo_gfx_empty_blit(struct video_blit const *__restrict UNUSED(self),
                        video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                        video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                        video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_empty_stretch(struct video_blit const *__restrict UNUSED(self),
                           video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                           video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                           video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                           video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(8) void CC
libvideo_gfx_empty_bitblit(struct video_blit const *__restrict UNUSED(self),
                           video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                           video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                           video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                           struct video_bitmask const *__restrict UNUSED(bm)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(10) void CC
libvideo_gfx_empty_bitstretch(struct video_blit const *__restrict UNUSED(self),
                              video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                              video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                              video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                              video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y),
                              struct video_bitmask const *__restrict UNUSED(bm)) {
	COMPILER_IMPURE();
}

#undef libvideo_blit_empty_ops
PRIVATE struct video_blit_ops libvideo_blit_empty_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_blit_ops const *CC _libvideo_blit_empty_ops(void) {
	if unlikely(!libvideo_blit_empty_ops.vbo_bitstretch) {
		libvideo_blit_empty_ops.vbo_blit    = &libvideo_gfx_empty_blit;
		libvideo_blit_empty_ops.vbo_stretch = &libvideo_gfx_empty_stretch;
		libvideo_blit_empty_ops.vbo_bitblit = &libvideo_gfx_empty_bitblit;
		COMPILER_WRITE_BARRIER();
		libvideo_blit_empty_ops.vbo_bitstretch = &libvideo_gfx_empty_bitstretch;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_blit_empty_ops;
}
#define libvideo_blit_empty_ops (*_libvideo_blit_empty_ops())



/* Empty video buffer. */
INTERN WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int CC
libvideo_buffer_empty_lock(struct video_buffer *__restrict UNUSED(self),
                           struct video_lock *__restrict result) {
	result->vl_data   = (byte_t *)result;
	result->vl_size   = 0;
	result->vl_stride = 0;
	return 0;
}

INTERN ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(CC libvideo_buffer_empty_unlock)(struct video_buffer *__restrict UNUSED(self),
                                         struct video_lock *__restrict UNUSED(lock)) {
	COMPILER_IMPURE();
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *CC
libvideo_buffer_empty_noblend(struct video_gfx *__restrict self) {
	COMPILER_IMPURE();
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *CC
libvideo_buffer_empty_initgfx(struct video_gfx *__restrict self) {
	video_gfxhdr_setempty(&self->vx_hdr);
	DBG_memset(&self->vx_xops, 0xcc, sizeof(self->vx_xops));
	return self;
}


#undef libvideo_buffer_empty_ops
PRIVATE struct video_buffer_ops libvideo_buffer_empty_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _libvideo_buffer_empty_ops(void) {
	if (!libvideo_buffer_empty_ops.vi_initgfx) {
		libvideo_buffer_empty_ops.vi_gfx_noblend = &libvideo_buffer_empty_noblend;
		libvideo_buffer_empty_ops.vi_rlock       = &libvideo_buffer_empty_lock;
		libvideo_buffer_empty_ops.vi_wlock       = &libvideo_buffer_empty_lock;
		libvideo_buffer_empty_ops.vi_unlock      = &libvideo_buffer_empty_unlock;
		COMPILER_WRITE_BARRIER();
		libvideo_buffer_empty_ops.vi_initgfx = &libvideo_buffer_empty_initgfx;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_buffer_empty_ops;
}
#define libvideo_buffer_empty_ops (*_libvideo_buffer_empty_ops())


#undef libvideo_buffer_empty
PRIVATE struct video_buffer libvideo_buffer_empty = {
	.vb_refcnt = 0x7fff,
	.vb_ops    = NULL, /* Initialized lazily */
	.vb_format = {
		.vf_codec = NULL, /* Initialized lazily */
		.vf_pal   = NULL,
	},
	.vb_size_x = 0,
	.vb_size_y = 0,
};

INTERN ATTR_RETNONNULL WUNUSED struct video_buffer *CC _libvideo_buffer_empty(void) {
	if (!libvideo_buffer_empty.vb_ops) {
		libvideo_buffer_empty.vb_format.vf_codec = video_codec_lookup(VIDEO_CODEC_RGBA8888);
		COMPILER_WRITE_BARRIER();
		libvideo_buffer_empty.vb_ops = &libvideo_buffer_empty_ops;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_buffer_empty;
}
#define libvideo_buffer_empty (*_libvideo_buffer_empty())

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_EMPTY_C */
