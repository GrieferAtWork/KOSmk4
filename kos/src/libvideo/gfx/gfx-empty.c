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
#define __VIDEO_BUFFER_const /* nothing */
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <libvideo/color.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "buffer.h"
#include "codec/codec.h"
#include "gfx-empty.h"
#include "ramdomain.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Empty GFX operators */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC
libvideo_emptygfx_blitfrom(struct video_blitter *__restrict ctx) {
	ctx->vbt_ops = &libvideo_emptyblitter_ops;
	return ctx;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter3 *FCC
libvideo_emptygfx_blitfrom3(struct video_blitter3 *__restrict ctx) {
	ctx->vbt3_ops = &libvideo_emptyblitter3_ops;
	return ctx;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *CC
libvideo_emptygfx_clip(struct video_gfx *__restrict self,
                       video_offset_t clip_x, video_offset_t clip_y,
                       video_dim_t size_x, video_dim_t size_y) {
	self->vg_clip.vgc_cxoff += clip_x;
	self->vg_clip.vgc_cyoff += clip_y;
	if (video_gfx_getflags(self) & VIDEO_GFX_F_XMIRROR)
		self->vg_clip.vgc_cxoff -= 2 * clip_x;
	if (video_gfx_getflags(self) & VIDEO_GFX_F_YMIRROR)
		self->vg_clip.vgc_cyoff -= 2 * clip_y;
	self->vg_clip.vgc_cxdim = size_x;
	self->vg_clip.vgc_cydim = size_y;
	return self;
}

INTERN WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC
libvideo_emptygfx_offset2coord(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y,
                               video_coord_t coords[2]) {
	/* GFX is empty, so there are no valid offsets/coords */
	(void)self;
	(void)x;
	(void)y;
	(void)coords;
	COMPILER_IMPURE();
	return false;
}

INTERN ATTR_IN(1) video_color_t CC
libvideo_emptygfx_getcolor(struct video_gfx const *__restrict UNUSED(self),
                            video_offset_t UNUSED(x), video_offset_t UNUSED(y)) {
	COMPILER_IMPURE();
	return 0;
}

INTERN ATTR_IN(1) void CC
libvideo_emptygfx_putcolor(struct video_gfx const *__restrict UNUSED(self),
                            video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                            video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

DEFINE_INTERN_ALIAS(libvideo_emptygfx_vline, libvideo_emptygfx_hline);
INTERN ATTR_IN(1) void CC
libvideo_emptygfx_hline(struct video_gfx const *__restrict UNUSED(self),
                         video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                         video_dim_t UNUSED(length), video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) void CC
libvideo_emptygfx_line(struct video_gfx const *__restrict UNUSED(self),
                        video_offset_t UNUSED(x1), video_offset_t UNUSED(y1),
                        video_offset_t UNUSED(x2), video_offset_t UNUSED(y2),
                        video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

DEFINE_INTERN_ALIAS(libvideo_emptygfx_rect, libvideo_emptygfx_fill);
INTERN ATTR_IN(1) void CC
libvideo_emptygfx_fill(struct video_gfx const *__restrict UNUSED(self),
                        video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                        video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                        video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
libvideo_emptygfx_gradient(struct video_gfx const *__restrict UNUSED(self),
                            video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                            video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                            video_color_t const UNUSED2(colors, [2][2])) {
	COMPILER_IMPURE();
}

DEFINE_INTERN_ALIAS(libvideo_emptygfx_vgradient, libvideo_emptygfx_hgradient);
INTERN ATTR_IN(1) void CC
libvideo_emptygfx_hgradient(struct video_gfx const *__restrict UNUSED(self),
                             video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                             video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                             video_color_t UNUSED(locolor), video_color_t UNUSED(hicolor)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(4) void CC
libvideo_emptygfx_bitblit(struct video_gfx const *UNUSED(dst),
                           video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                           struct video_gfx const *UNUSED(src),
                           video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                           video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
libvideo_emptygfx_stretch(struct video_gfx const *UNUSED(dst),
                           video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                           video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                           struct video_gfx const *UNUSED(src),
                           video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                           video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(4) ATTR_IN(7) void CC
libvideo_emptygfx_bitblit3(struct video_gfx const *UNUSED(wrdst),
                           video_offset_t UNUSED(wrdst_x), video_offset_t UNUSED(wrdst_y),
                           struct video_gfx const *UNUSED(rddst),
                           video_offset_t UNUSED(rddst_x), video_offset_t UNUSED(rddst_y),
                           struct video_gfx const *UNUSED(src),
                           video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                           video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(4) ATTR_IN(9) void CC
libvideo_emptygfx_stretch3(struct video_gfx const *UNUSED(wrdst),
                           video_offset_t UNUSED(wrdst_x), video_offset_t UNUSED(wrdst_y),
                           struct video_gfx const *UNUSED(rddst),
                           video_offset_t UNUSED(rddst_x), video_offset_t UNUSED(rddst_y),
                           video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                           struct video_gfx const *UNUSED(src),
                           video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                           video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y)) {
	COMPILER_IMPURE();
}


#undef libvideo_emptygfx_ops
PRIVATE struct video_gfx_ops libvideo_emptygfx_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_emptygfx_ops(void) {
	if unlikely(!libvideo_emptygfx_ops.vgfo_getcolor) {
		libvideo_emptygfx_ops.vgfo_blitfrom     = &libvideo_emptygfx_blitfrom;
		libvideo_emptygfx_ops.vgfo_blitfrom3    = &libvideo_emptygfx_blitfrom3;
		libvideo_emptygfx_ops.vgfo_clip         = &libvideo_emptygfx_clip;
		libvideo_emptygfx_ops.vgfo_coord2offset = &libvideo_emptygfx_coord2offset;
		libvideo_emptygfx_ops.vgfo_offset2coord = &libvideo_emptygfx_offset2coord;
		libvideo_emptygfx_ops.vgfo_bitblit      = &libvideo_emptygfx_bitblit;
		libvideo_emptygfx_ops.vgfo_stretch      = &libvideo_emptygfx_stretch;
		libvideo_emptygfx_ops.vgfo_bitblit3     = &libvideo_emptygfx_bitblit3;
		libvideo_emptygfx_ops.vgfo_stretch3     = &libvideo_emptygfx_stretch3;
		libvideo_emptygfx_ops.vgfo_vgradient    = &libvideo_emptygfx_vgradient;
		libvideo_emptygfx_ops.vgfo_hgradient    = &libvideo_emptygfx_hgradient;
		libvideo_emptygfx_ops.vgfo_gradient     = &libvideo_emptygfx_gradient;
		libvideo_emptygfx_ops.vgfo_rect         = &libvideo_emptygfx_rect;
		libvideo_emptygfx_ops.vgfo_fill         = &libvideo_emptygfx_fill;
		libvideo_emptygfx_ops.vgfo_vline        = &libvideo_emptygfx_vline;
		libvideo_emptygfx_ops.vgfo_hline        = &libvideo_emptygfx_hline;
		libvideo_emptygfx_ops.vgfo_line         = &libvideo_emptygfx_line;
		libvideo_emptygfx_ops.vgfo_putcolor     = &libvideo_emptygfx_putcolor;
		COMPILER_WRITE_BARRIER();
		libvideo_emptygfx_ops.vgfo_getcolor = &libvideo_emptygfx_getcolor;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_emptygfx_ops;
}
#define libvideo_emptygfx_ops (*_libvideo_emptygfx_ops())

/* Empty blit operators */
INTERN ATTR_IN(1) void CC
libvideo_emptyblitter_blit(struct video_blitter const *__restrict UNUSED(self),
                            video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                            video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                            video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) void CC
libvideo_emptyblitter_stretch(struct video_blitter const *__restrict UNUSED(self),
                               video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                               video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                               video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                               video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y)) {
	COMPILER_IMPURE();
}

#undef libvideo_emptyblitter_ops
PRIVATE struct video_blitter_ops libvideo_emptyblitter_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_emptyblitter_ops(void) {
	if unlikely(!libvideo_emptyblitter_ops.vbto_bitblit) {
		libvideo_emptyblitter_ops.vbto_stretch = &libvideo_emptyblitter_stretch;
		COMPILER_WRITE_BARRIER();
		libvideo_emptyblitter_ops.vbto_bitblit = &libvideo_emptyblitter_blit;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_emptyblitter_ops;
}
#define libvideo_emptyblitter_ops (*_libvideo_emptyblitter_ops())



/* Empty blit3 operators */
INTERN ATTR_IN(1) void CC
libvideo_emptyblitter3_blit(struct video_blitter3 const *__restrict UNUSED(self),
                            video_offset_t UNUSED(wrdst_x), video_offset_t UNUSED(wrdst_y),
                            video_offset_t UNUSED(rddst_x), video_offset_t UNUSED(rddst_y),
                            video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                            video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) void CC
libvideo_emptyblitter3_stretch(struct video_blitter3 const *__restrict UNUSED(self),
                               video_offset_t UNUSED(wrdst_x), video_offset_t UNUSED(wrdst_y),
                               video_offset_t UNUSED(rddst_x), video_offset_t UNUSED(rddst_y),
                               video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                               video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                               video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y)) {
	COMPILER_IMPURE();
}

#undef libvideo_emptyblitter3_ops
PRIVATE struct video_blitter3_ops libvideo_emptyblitter3_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_blitter3_ops const *CC _libvideo_emptyblitter3_ops(void) {
	if unlikely(!libvideo_emptyblitter3_ops.vbt3o_bitblit) {
		libvideo_emptyblitter3_ops.vbt3o_stretch = &libvideo_emptyblitter3_stretch;
		COMPILER_WRITE_BARRIER();
		libvideo_emptyblitter3_ops.vbt3o_bitblit = &libvideo_emptyblitter3_blit;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_emptyblitter3_ops;
}
#define libvideo_emptyblitter3_ops (*_libvideo_emptyblitter3_ops())



/* Empty video buffer. */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_emptybuffer_initgfx(struct video_gfx *__restrict self) {
	self->vg_clip.vgc_ops = &libvideo_emptygfx_ops;
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_emptybuffer_updategfx(struct video_gfx *__restrict self,
                                unsigned int UNUSED(what)) {
	COMPILER_IMPURE();
	return self;
}


INTERN struct video_buffer_ops libvideo_emptybuffer_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _libvideo_emptybuffer_ops(void) {
	if (!libvideo_emptybuffer_ops.vi_initgfx) {
		/* NOTE: It is  important  that  an  empty  buffer doesn't  support  video  locks  of  any  kind.
		 *       Reason is that `old_bigregion_buffer_r::brbr_orig' / `old_subregion_buffer_r::srbr_orig'
		 *       do  not  get updated  when the  empty buffer  is  assigned during  revoke, and  the impl
		 *       assumes that  **ONLY**  the  original  buffer  can  create  video  locks,  meaning  that
		 *       **ONLY** locked created by **IT** can possible by released (for which it always
		 *       just uses the original buffer). */
		libvideo_emptybuffer_ops.vi_rlock        = &libvideo_buffer_notsup_rlock;
		libvideo_emptybuffer_ops.vi_wlock        = &libvideo_buffer_notsup_wlock;
		libvideo_emptybuffer_ops.vi_unlock       = &libvideo_buffer_noop_unlock;
		libvideo_emptybuffer_ops.vi_rlockregion  = &libvideo_buffer_notsup_rlockregion;
		libvideo_emptybuffer_ops.vi_wlockregion  = &libvideo_buffer_notsup_wlockregion;
		libvideo_emptybuffer_ops.vi_unlockregion = &libvideo_buffer_noop_unlockregion;
		libvideo_emptybuffer_ops.vi_updategfx    = &libvideo_emptybuffer_updategfx;
		COMPILER_WRITE_BARRIER();
		libvideo_emptybuffer_ops.vi_initgfx    = &libvideo_emptybuffer_initgfx;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_emptybuffer_ops;
}


#undef libvideo_emptybuffer
PRIVATE struct video_buffer libvideo_emptybuffer = {
	.vb_surf = {
		.vs_pal      = NULL,
		.vs_buffer   = NULL, /* Initialized lazily */
		.vs_flags    = VIDEO_GFX_F_NORMAL,
		.vs_colorkey = 0,
	},
	.vb_codec  = NULL, /* Initialized lazily */
	.vb_ops    = NULL, /* Initialized lazily */
	.vb_domain = NULL, /* Initialized lazily */
	.vb_dim    = { 0, 0 },
	.vb_refcnt = 0x7fff,
};

INTERN ATTR_RETNONNULL WUNUSED struct video_buffer *CC _libvideo_emptybuffer(void) {
	if (!libvideo_emptybuffer.vb_ops) {
		libvideo_emptybuffer.vb_domain = _libvideo_ramdomain();
		libvideo_emptybuffer.vb_codec = libvideo_codec_lookup(VIDEO_CODEC_RGBA8888);
		assertf(libvideo_emptybuffer.vb_codec, "Built-in codec should have been recognized");
		libvideo_emptybuffer.vb_surf.vs_buffer = &libvideo_emptybuffer;
		COMPILER_WRITE_BARRIER();
		libvideo_emptybuffer.vb_ops = _libvideo_emptybuffer_ops();
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_emptybuffer;
}
#define libvideo_emptybuffer (*_libvideo_emptybuffer())

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_EMPTY_C */
