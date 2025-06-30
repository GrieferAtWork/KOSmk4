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

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC
libvideo_gfx_empty__blitto(struct video_blitter *__restrict ctx) {
	ctx->vbt_ops = &libvideo_blit_empty_ops;
	DBG_memset(&ctx->_vbt_xops, 0xcc, sizeof(ctx->_vbt_xops));
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

INTERN ATTR_IN(1) ATTR_IN(6) void CC
libvideo_gfx_empty_gradient(struct video_gfx const *__restrict UNUSED(self),
                            video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                            video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                            video_color_t const UNUSED2(colors, [2][2])) {
	COMPILER_IMPURE();
}

DEFINE_INTERN_ALIAS(libvideo_gfx_empty_vgradient, libvideo_gfx_empty_hgradient);
INTERN ATTR_IN(1) void CC
libvideo_gfx_empty_hgradient(struct video_gfx const *__restrict UNUSED(self),
                             video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                             video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                             video_color_t UNUSED(locolor), video_color_t UNUSED(hicolor)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC
libvideo_gfx_empty_fillmask(struct video_gfx const *__restrict UNUSED(self),
                            video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                            video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                            video_color_t const UNUSED2(bg_fg_colors, [2]),
                            struct video_bitmask const *__restrict UNUSED(bm)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
libvideo_gfx_empty_fillstretchmask(struct video_gfx const *__restrict UNUSED(self),
                                   video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                                   video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                                   video_color_t const UNUSED2(bg_fg_colors, [2]),
                                   video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y),
                                   struct video_bitmask const *__restrict UNUSED(bm)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(4) void CC
libvideo_gfx_empty_bitblit(struct video_gfx const *__restrict UNUSED(dst),
                           video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                           struct video_gfx const *__restrict UNUSED(src),
                           video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                           video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
libvideo_gfx_empty_stretch(struct video_gfx const *__restrict UNUSED(dst),
                           video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                           video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                           struct video_gfx const *__restrict UNUSED(src),
                           video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                           video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y)) {
	COMPILER_IMPURE();
}


#undef libvideo_gfx_empty_ops
PRIVATE struct video_gfx_ops libvideo_gfx_empty_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_empty_ops(void) {
	if unlikely(!libvideo_gfx_empty_ops.vgfo_getcolor) {
		libvideo_gfx_empty_ops.vgfo_bitblit         = &libvideo_gfx_empty_bitblit;
		libvideo_gfx_empty_ops.vgfo_stretch         = &libvideo_gfx_empty_stretch;
		libvideo_gfx_empty_ops.vgfo_vgradient       = &libvideo_gfx_empty_vgradient;
		libvideo_gfx_empty_ops.vgfo_hgradient       = &libvideo_gfx_empty_hgradient;
		libvideo_gfx_empty_ops.vgfo_gradient        = &libvideo_gfx_empty_gradient;
		libvideo_gfx_empty_ops.vgfo_fillstretchmask = &libvideo_gfx_empty_fillstretchmask;
		libvideo_gfx_empty_ops.vgfo_fillmask        = &libvideo_gfx_empty_fillmask;
		libvideo_gfx_empty_ops.vgfo_rect            = &libvideo_gfx_empty_rect;
		libvideo_gfx_empty_ops.vgfo_fill            = &libvideo_gfx_empty_fill;
		libvideo_gfx_empty_ops.vgfo_vline           = &libvideo_gfx_empty_vline;
		libvideo_gfx_empty_ops.vgfo_hline           = &libvideo_gfx_empty_hline;
		libvideo_gfx_empty_ops.vgfo_line            = &libvideo_gfx_empty_line;
		libvideo_gfx_empty_ops.vgfo_putcolor        = &libvideo_gfx_empty_putcolor;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_empty_ops.vgfo_getcolor = &libvideo_gfx_empty_getcolor;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_gfx_empty_ops;
}
#define libvideo_gfx_empty_ops (*_libvideo_gfx_empty_ops())

/* Empty blit operators */
INTERN ATTR_IN(1) void CC
libvideo_blitter_empty_blit(struct video_blitter const *__restrict UNUSED(self),
                            video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                            video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                            video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) void CC
libvideo_blitter_empty_stretch(struct video_blitter const *__restrict UNUSED(self),
                               video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                               video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                               video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                               video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y)) {
	COMPILER_IMPURE();
}

#undef libvideo_blit_empty_ops
PRIVATE struct video_blitter_ops libvideo_blit_empty_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_blit_empty_ops(void) {
	if unlikely(!libvideo_blit_empty_ops.vbto_bitblit) {
		libvideo_blit_empty_ops.vbto_stretch = &libvideo_blitter_empty_stretch;
		COMPILER_WRITE_BARRIER();
		libvideo_blit_empty_ops.vbto_bitblit = &libvideo_blitter_empty_blit;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_blit_empty_ops;
}
#define libvideo_blit_empty_ops (*_libvideo_blit_empty_ops())



/* Empty video buffer. */
INTERN WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
libvideo_buffer_empty_lock(struct video_buffer *__restrict UNUSED(self),
                           struct video_lock *__restrict lock) {
	lock->vl_data   = (byte_t *)lock;
	lock->vl_stride = 0;
	return 0;
}

INTERN ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC libvideo_buffer_empty_unlock)(struct video_buffer *__restrict UNUSED(self),
                                         struct video_lock *__restrict UNUSED(lock)) {
	COMPILER_IMPURE();
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_buffer_empty_initgfx(struct video_gfx *__restrict self) {
	video_gfxhdr_setempty(&self->vx_hdr);
	DBG_memset(&self->_vx_xops, 0xcc, sizeof(self->_vx_xops));
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_buffer_empty_updategfx(struct video_gfx *__restrict self,
                                unsigned int UNUSED(what)) {
	COMPILER_IMPURE();
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_buffer_empty_noblend(struct video_gfx *__restrict self) {
	COMPILER_IMPURE();
	return self;
}


INTERN struct video_buffer_ops libvideo_buffer_empty_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _libvideo_buffer_empty_ops(void) {
	if (!libvideo_buffer_empty_ops.vi_rlock) {
		libvideo_buffer_empty_ops.vi_wlock      = &libvideo_buffer_empty_lock;
		libvideo_buffer_empty_ops.vi_unlock     = &libvideo_buffer_empty_unlock;
		libvideo_buffer_empty_ops.vi_initgfx    = &libvideo_buffer_empty_initgfx;
		libvideo_buffer_empty_ops.vi_updategfx  = &libvideo_buffer_empty_updategfx;
		libvideo_buffer_empty_ops.vi_noblendgfx = &libvideo_buffer_empty_noblend;
		COMPILER_WRITE_BARRIER();
		libvideo_buffer_empty_ops.vi_rlock = &libvideo_buffer_empty_lock;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_buffer_empty_ops;
}


#undef libvideo_buffer_empty
PRIVATE struct video_buffer libvideo_buffer_empty = {
	.vb_ops    = NULL, /* Initialized lazily */
	.vb_format = {
		.vf_codec = NULL, /* Initialized lazily */
		.vf_pal   = NULL,
	},
	.vb_xdim = 0,
	.vb_ydim = 0,
	.vb_refcnt = 0x7fff,
};

INTERN ATTR_RETNONNULL WUNUSED struct video_buffer *CC _libvideo_buffer_empty(void) {
	if (!libvideo_buffer_empty.vb_ops) {
		libvideo_buffer_empty.vb_format.vf_codec = video_codec_lookup(VIDEO_CODEC_RGBA8888);
		COMPILER_WRITE_BARRIER();
		libvideo_buffer_empty.vb_ops = _libvideo_buffer_empty_ops();
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_buffer_empty;
}
#define libvideo_buffer_empty (*_libvideo_buffer_empty())

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_EMPTY_C */
