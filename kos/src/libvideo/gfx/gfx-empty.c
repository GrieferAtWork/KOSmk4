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
#define _KOS_SOURCE 1

#include "api.h"

#include <hybrid/compiler.h>

#include <stddef.h>

#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
/**/

#include "gfx-empty.h"

DECL_BEGIN

DEFINE_INTERN_ALIAS(libvideo_gfx_empty_getcolor, libvideo_gfx_empty__getcolor);
INTERN ATTR_CONST NONNULL((1)) video_color_t CC
libvideo_gfx_empty__getcolor(struct video_gfx const *__restrict UNUSED(self),
                             video_coord_t UNUSED(x), video_coord_t UNUSED(y)) {
	return 0;
}

DEFINE_INTERN_ALIAS(libvideo_gfx_empty_putcolor, libvideo_gfx_empty__putcolor);
INTERN NONNULL((1)) void CC
libvideo_gfx_empty__putcolor(struct video_gfx *__restrict UNUSED(self),
                             video_coord_t UNUSED(x), video_coord_t UNUSED(y),
                             video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

DEFINE_INTERN_ALIAS(libvideo_gfx_empty__absline_lhhl, libvideo_gfx_empty__absline_llhh);
DEFINE_INTERN_ALIAS(libvideo_gfx_empty__absfill, libvideo_gfx_empty__absline_llhh);
INTERN NONNULL((1)) void CC
libvideo_gfx_empty__absline_llhh(struct video_gfx *__restrict UNUSED(self),
                                 video_coord_t UNUSED(x), video_coord_t UNUSED(y),
                                 video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                                 video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

DEFINE_INTERN_ALIAS(libvideo_gfx_empty_hline, libvideo_gfx_empty__absline_h);
DEFINE_INTERN_ALIAS(libvideo_gfx_empty_vline, libvideo_gfx_empty__absline_v);
DEFINE_INTERN_ALIAS(libvideo_gfx_empty__absline_v, libvideo_gfx_empty__absline_h);
INTERN NONNULL((1)) void CC
libvideo_gfx_empty__absline_h(struct video_gfx *__restrict UNUSED(self),
                              video_coord_t UNUSED(x), video_coord_t UNUSED(y),
                              video_dim_t UNUSED(length), video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

INTERN NONNULL((1, 7)) void CC
libvideo_gfx_empty__bitfill(struct video_gfx *__restrict UNUSED(self),
                            video_coord_t UNUSED(dst_x), video_coord_t UNUSED(dst_y),
                            video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                            video_color_t UNUSED(color),
                            void const *__restrict UNUSED(bitmask),
                            uintptr_t UNUSED(bitskip), size_t UNUSED(bitscan)) {
	COMPILER_IMPURE();
}

INTERN NONNULL((1, 9)) void CC
libvideo_gfx_empty__bitstretchfill(struct video_gfx *__restrict UNUSED(self),
                                   video_coord_t UNUSED(dst_x), video_coord_t UNUSED(dst_y),
                                   video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                                   video_color_t UNUSED(color),
                                   video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y),
                                   void const *__restrict UNUSED(bitmask), uintptr_t UNUSED(bitskip),
                                   video_dim_t UNUSED(bitmask_size_x), video_dim_t UNUSED(bitmask_size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_RETNONNULL NONNULL((1)) struct video_blit *CC
libvideo_gfx_empty__blitfrom(struct video_blit *__restrict ctx) {
	ctx->vb_ops = &libvideo_blit_empty_ops;
	ctx->vb_xops.vbxo_blit       = &libvideo_gfx_empty__blit;
	ctx->vb_xops.vbxo_stretch    = &libvideo_gfx_empty__stretch;
	ctx->vb_xops.vbxo_bitblit    = &libvideo_gfx_empty__bitblit;
	ctx->vb_xops.vbxo_bitstretch = &libvideo_gfx_empty__bitstretch;
	return ctx;
}

INTERN NONNULL((1)) void CC
libvideo_gfx_empty__blit(struct video_blit *__restrict UNUSED(self),
                         video_coord_t UNUSED(dst_x), video_coord_t UNUSED(dst_y),
                         video_coord_t UNUSED(src_x), video_coord_t UNUSED(src_y),
                         video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y)) {
	COMPILER_IMPURE();
}

INTERN NONNULL((1)) void CC
libvideo_gfx_empty__stretch(struct video_blit *__restrict UNUSED(self),
                            video_coord_t UNUSED(dst_x), video_coord_t UNUSED(dst_y),
                            video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                            video_coord_t UNUSED(src_x), video_coord_t UNUSED(src_y),
                            video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y)) {
	COMPILER_IMPURE();
}

INTERN NONNULL((1, 8)) void CC
libvideo_gfx_empty__bitblit(struct video_blit *__restrict UNUSED(self),
                            video_coord_t UNUSED(dst_x), video_coord_t UNUSED(dst_y),
                            video_coord_t UNUSED(src_x), video_coord_t UNUSED(src_y),
                            video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                            void const *__restrict UNUSED(bitmask),
                            uintptr_t UNUSED(bitskip), size_t UNUSED(bitscan)) {
	COMPILER_IMPURE();
}

INTERN NONNULL((1, 10)) void CC
libvideo_gfx_empty__bitstretch(struct video_blit *__restrict UNUSED(self),
                               video_coord_t UNUSED(dst_x), video_coord_t UNUSED(dst_y),
                               video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                               video_coord_t UNUSED(src_x), video_coord_t UNUSED(src_y),
                               video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y),
                               void const *__restrict UNUSED(bitmask), uintptr_t UNUSED(bitskip),
                               video_dim_t UNUSED(bitmask_size_x), video_dim_t UNUSED(bitmask_size_y)) {
	COMPILER_IMPURE();
}

/* Empty GFX operators */
INTERN NONNULL((1)) void CC
libvideo_gfx_empty_line(struct video_gfx *__restrict UNUSED(self),
                        video_offset_t UNUSED(x1), video_offset_t UNUSED(y1),
                        video_offset_t UNUSED(x2), video_offset_t UNUSED(y2),
                        video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

DEFINE_INTERN_ALIAS(libvideo_gfx_empty_rect, libvideo_gfx_empty_fill);
INTERN NONNULL((1)) void CC
libvideo_gfx_empty_fill(struct video_gfx *__restrict UNUSED(self),
                        video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                        video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                        video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

INTERN NONNULL((1, 7)) void CC
libvideo_gfx_empty_bitfill(struct video_gfx *__restrict UNUSED(self),
                           video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                           video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                           video_color_t UNUSED(color),
                           void const *__restrict UNUSED(bitmask),
                           uintptr_t UNUSED(bitskip), size_t UNUSED(bitscan)) {
	COMPILER_IMPURE();
}

INTERN NONNULL((1, 9)) void CC
libvideo_gfx_empty_bitstretchfill(struct video_gfx *__restrict UNUSED(self),
                                  video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                                  video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                                  video_color_t UNUSED(color),
                                  video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y),
                                  void const *__restrict UNUSED(bitmask),
                                  uintptr_t UNUSED(bitskip), size_t UNUSED(bitscan)) {
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
INTERN NONNULL((1)) void CC
libvideo_gfx_empty_blit(struct video_blit *__restrict UNUSED(self),
                        video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                        video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                        video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y)) {
	COMPILER_IMPURE();
}

INTERN NONNULL((1)) void CC
libvideo_gfx_empty_stretch(struct video_blit *__restrict UNUSED(self),
                           video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                           video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                           video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                           video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y)) {
	COMPILER_IMPURE();
}

INTERN NONNULL((1, 8)) void CC
libvideo_gfx_empty_bitblit(struct video_blit *__restrict UNUSED(self),
                           video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                           video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                           video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                           void const *__restrict UNUSED(bitmask),
                           uintptr_t UNUSED(bitskip), size_t UNUSED(bitscan)) {
	COMPILER_IMPURE();
}

INTERN NONNULL((1, 10)) void CC
libvideo_gfx_empty_bitstretch(struct video_blit *__restrict UNUSED(self),
                              video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                              video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                              video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                              video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y),
                              void const *__restrict UNUSED(bitmask),
                              uintptr_t UNUSED(bitskip), size_t UNUSED(bitscan)) {
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
INTERN NONNULL((1, 2)) int CC
libvideo_buffer_empty_lock(struct video_buffer *__restrict UNUSED(self),
                           struct video_lock *__restrict result) {
	result->vl_data   = (byte_t *)result;
	result->vl_size   = 0;
	result->vl_stride = 0;
	return 0;
}

INTERN NONNULL((1, 2)) void
NOTHROW(CC libvideo_buffer_empty_unlock)(struct video_buffer *__restrict UNUSED(self),
                                         struct video_lock *__restrict UNUSED(lock)) {
	COMPILER_IMPURE();
}

INTERN ATTR_RETNONNULL NONNULL((1, 2)) struct video_gfx *CC
libvideo_buffer_empty_getgfx(struct video_buffer *__restrict self,
                             struct video_gfx *__restrict result,
                             gfx_blendmode_t blendmode,
                             uintptr_t flags, video_color_t colorkey) {
	result->vx_buffer   = self;
	result->vx_blend    = blendmode;
	result->vx_flags    = flags;
	result->vx_colorkey = colorkey;
	libvideo_gfx_setempty(result);
	return result;
}


#undef libvideo_buffer_empty_ops
PRIVATE struct video_buffer_ops libvideo_buffer_empty_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _libvideo_buffer_empty_ops(void) {
	if (!libvideo_buffer_empty_ops.vi_getgfx) {
		libvideo_buffer_empty_ops.vi_rlock  = &libvideo_buffer_empty_lock;
		libvideo_buffer_empty_ops.vi_wlock  = &libvideo_buffer_empty_lock;
		libvideo_buffer_empty_ops.vi_unlock = &libvideo_buffer_empty_unlock;
		COMPILER_WRITE_BARRIER();
		libvideo_buffer_empty_ops.vi_getgfx = &libvideo_buffer_empty_getgfx;
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


/* Assign "empty" operators to "self". Initializes:
 * - self->vx_xops.*
 * - self->vx_ops
 * - self->vx_offt_x
 * - self->vx_offt_y
 * - self->vx_xmin
 * - self->vx_ymin
 * - self->vx_xend
 * - self->vx_yend */
INTERN NONNULL((1)) void CC
libvideo_gfx_setempty(struct video_gfx *__restrict self) {
	self->vx_xops.vgxo_blitfrom       = &libvideo_gfx_empty__blitfrom;
	self->vx_xops.vgxo_getcolor       = &libvideo_gfx_empty__getcolor;
	self->vx_xops.vgxo_putcolor       = &libvideo_gfx_empty__putcolor;
	self->vx_xops.vgxo_absline_llhh   = &libvideo_gfx_empty__absline_llhh;
	self->vx_xops.vgxo_absline_lhhl   = &libvideo_gfx_empty__absline_lhhl;
	self->vx_xops.vgxo_absline_h      = &libvideo_gfx_empty__absline_h;
	self->vx_xops.vgxo_absline_v      = &libvideo_gfx_empty__absline_v;
	self->vx_xops.vgxo_absfill        = &libvideo_gfx_empty__absfill;
	self->vx_xops.vgxo_bitfill        = &libvideo_gfx_empty__bitfill;
	self->vx_xops.vgxo_bitstretchfill = &libvideo_gfx_empty__bitstretchfill;

	self->vx_ops    = &libvideo_gfx_empty_ops;
	self->vx_offt_x = 0;
	self->vx_offt_y = 0;
	self->vx_xmin   = 0;
	self->vx_ymin   = 0;
	self->vx_xend   = 0;
	self->vx_yend   = 0;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_EMPTY_C */
