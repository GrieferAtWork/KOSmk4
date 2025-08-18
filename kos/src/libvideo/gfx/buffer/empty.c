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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_EMPTY_C
#define GUARD_LIBVIDEO_GFX_BUFFER_EMPTY_C 1
#define __VIDEO_BUFFER_const /* nothing */
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <sys/param.h>

#include <assert.h>
#include <malloc.h>
#include <string.h>

#include <libvideo/color.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/buffer/empty.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "../buffer.h"
#include "../codec/codec.h"
#include "../ramdomain.h"
#include "empty.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Empty GFX operators */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC
libvideo_emptygfx__blitfrom(struct video_blitter *__restrict ctx) {
	ctx->vbt_ops = _libvideo_emptyblitter_ops();
	return ctx;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter3 *FCC
libvideo_emptygfx__blitfrom3(struct video_blitter3 *__restrict ctx) {
	ctx->vbt3_ops = _libvideo_emptyblitter3_ops();
	return ctx;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *CC
libvideo_emptygfx__clip(struct video_gfx *__restrict self,
                        video_offset_t clip_x, video_offset_t clip_y,
                        video_dim_t size_x, video_dim_t size_y) {
	gfx_assert(video_gfx_getioxdim(self) == 0);
	gfx_assert(video_gfx_getioydim(self) == 0);
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
libvideo_emptygfx__offset2coord(struct video_gfx const *__restrict self,
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
libvideo_emptygfx__getcolor(struct video_gfx const *__restrict UNUSED(self),
                            video_offset_t UNUSED(x), video_offset_t UNUSED(y)) {
	COMPILER_IMPURE();
	return 0;
}

INTERN ATTR_IN(1) void CC
libvideo_emptygfx__putcolor(struct video_gfx const *__restrict UNUSED(self),
                            video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                            video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

DEFINE_INTERN_ALIAS(libvideo_emptygfx__vline, libvideo_emptygfx__hline);
INTERN ATTR_IN(1) void CC
libvideo_emptygfx__hline(struct video_gfx const *__restrict UNUSED(self),
                         video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                         video_dim_t UNUSED(length), video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) void CC
libvideo_emptygfx__line(struct video_gfx const *__restrict UNUSED(self),
                        video_offset_t UNUSED(x1), video_offset_t UNUSED(y1),
                        video_offset_t UNUSED(x2), video_offset_t UNUSED(y2),
                        video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}

DEFINE_INTERN_ALIAS(libvideo_emptygfx__rect, libvideo_emptygfx__fill);
#if __SIZEOF_VIDEO_DIM_T__ == __SIZEOF_VIDEO_OFFSET_T__
DEFINE_INTERN_ALIAS(libvideo_emptygfx__fill, libvideo_emptygfx__line);
#else  /* __SIZEOF_VIDEO_DIM_T__ == __SIZEOF_VIDEO_OFFSET_T__ */
INTERN ATTR_IN(1) void CC
libvideo_emptygfx__fill(struct video_gfx const *__restrict UNUSED(self),
                        video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                        video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                        video_color_t UNUSED(color)) {
	COMPILER_IMPURE();
}
#endif /* __SIZEOF_VIDEO_DIM_T__ != __SIZEOF_VIDEO_OFFSET_T__ */

INTERN ATTR_IN(1) ATTR_IN(6) void CC
libvideo_emptygfx__gradient(struct video_gfx const *__restrict UNUSED(self),
                            video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                            video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                            video_color_t const UNUSED2(colors, [2][2])) {
	COMPILER_IMPURE();
}

DEFINE_INTERN_ALIAS(libvideo_emptygfx__vgradient, libvideo_emptygfx__hgradient);
INTERN ATTR_IN(1) void CC
libvideo_emptygfx__hgradient(struct video_gfx const *__restrict UNUSED(self),
                             video_offset_t UNUSED(x), video_offset_t UNUSED(y),
                             video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y),
                             video_color_t UNUSED(locolor), video_color_t UNUSED(hicolor)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(4) void CC
libvideo_emptygfx__bitblit(struct video_gfx const *UNUSED(dst),
                           video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                           struct video_gfx const *UNUSED(src),
                           video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                           video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
libvideo_emptygfx__stretch(struct video_gfx const *UNUSED(dst),
                           video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                           video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                           struct video_gfx const *UNUSED(src),
                           video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                           video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(4) ATTR_IN(7) void CC
libvideo_emptygfx__bitblit3(struct video_gfx const *UNUSED(wrdst),
                            video_offset_t UNUSED(wrdst_x), video_offset_t UNUSED(wrdst_y),
                            struct video_gfx const *UNUSED(rddst),
                            video_offset_t UNUSED(rddst_x), video_offset_t UNUSED(rddst_y),
                            struct video_gfx const *UNUSED(src),
                            video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                            video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) ATTR_IN(4) ATTR_IN(9) void CC
libvideo_emptygfx__stretch3(struct video_gfx const *UNUSED(wrdst),
                            video_offset_t UNUSED(wrdst_x), video_offset_t UNUSED(wrdst_y),
                            struct video_gfx const *UNUSED(rddst),
                            video_offset_t UNUSED(rddst_x), video_offset_t UNUSED(rddst_y),
                            video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                            struct video_gfx const *UNUSED(src),
                            video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                            video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y)) {
	COMPILER_IMPURE();
}


INTERN struct video_gfx_ops libvideo_emptygfx_ops = {};
DEFINE_PUBLIC_ALIAS(video_emptygfx_ops, _libvideo_emptygfx_ops);
INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_emptygfx_ops(void) {
	if unlikely(!libvideo_emptygfx_ops.vgfo_getcolor) {
		libvideo_emptygfx_ops.vgfo_blitfrom     = &libvideo_emptygfx__blitfrom;
		libvideo_emptygfx_ops.vgfo_blitfrom3    = &libvideo_emptygfx__blitfrom3;
		libvideo_emptygfx_ops.vgfo_clip         = &libvideo_emptygfx__clip;
		libvideo_emptygfx_ops.vgfo_coord2offset = &libvideo_emptygfx__coord2offset;
		libvideo_emptygfx_ops.vgfo_offset2coord = &libvideo_emptygfx__offset2coord;
		libvideo_emptygfx_ops.vgfo_bitblit      = &libvideo_emptygfx__bitblit;
		libvideo_emptygfx_ops.vgfo_stretch      = &libvideo_emptygfx__stretch;
		libvideo_emptygfx_ops.vgfo_bitblit3     = &libvideo_emptygfx__bitblit3;
		libvideo_emptygfx_ops.vgfo_stretch3     = &libvideo_emptygfx__stretch3;
		libvideo_emptygfx_ops.vgfo_vgradient    = &libvideo_emptygfx__vgradient;
		libvideo_emptygfx_ops.vgfo_hgradient    = &libvideo_emptygfx__hgradient;
		libvideo_emptygfx_ops.vgfo_gradient     = &libvideo_emptygfx__gradient;
		libvideo_emptygfx_ops.vgfo_rect         = &libvideo_emptygfx__rect;
		libvideo_emptygfx_ops.vgfo_fill         = &libvideo_emptygfx__fill;
		libvideo_emptygfx_ops.vgfo_vline        = &libvideo_emptygfx__vline;
		libvideo_emptygfx_ops.vgfo_hline        = &libvideo_emptygfx__hline;
		libvideo_emptygfx_ops.vgfo_line         = &libvideo_emptygfx__line;
		libvideo_emptygfx_ops.vgfo_putcolor     = &libvideo_emptygfx__putcolor;
		COMPILER_WRITE_BARRIER();
		libvideo_emptygfx_ops.vgfo_getcolor = &libvideo_emptygfx__getcolor;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_emptygfx_ops;
}

/* Empty blit operators */
INTERN ATTR_IN(1) void CC
libvideo_emptyblitter__blit(struct video_blitter const *__restrict UNUSED(self),
                            video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                            video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                            video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) void CC
libvideo_emptyblitter__stretch(struct video_blitter const *__restrict UNUSED(self),
                               video_offset_t UNUSED(dst_x), video_offset_t UNUSED(dst_y),
                               video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                               video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                               video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y)) {
	COMPILER_IMPURE();
}

INTERN struct video_blitter_ops libvideo_emptyblitter_ops = {};
DEFINE_PUBLIC_ALIAS(video_emptyblitter_ops, _libvideo_emptyblitter_ops);
INTERN ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_emptyblitter_ops(void) {
	if unlikely(!libvideo_emptyblitter_ops.vbto_bitblit) {
		libvideo_emptyblitter_ops.vbto_stretch = &libvideo_emptyblitter__stretch;
		COMPILER_WRITE_BARRIER();
		libvideo_emptyblitter_ops.vbto_bitblit = &libvideo_emptyblitter__blit;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_emptyblitter_ops;
}



/* Empty blit3 operators */
INTERN ATTR_IN(1) void CC
libvideo_emptyblitter3__blit(struct video_blitter3 const *__restrict UNUSED(self),
                             video_offset_t UNUSED(wrdst_x), video_offset_t UNUSED(wrdst_y),
                             video_offset_t UNUSED(rddst_x), video_offset_t UNUSED(rddst_y),
                             video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                             video_dim_t UNUSED(size_x), video_dim_t UNUSED(size_y)) {
	COMPILER_IMPURE();
}

INTERN ATTR_IN(1) void CC
libvideo_emptyblitter3__stretch(struct video_blitter3 const *__restrict UNUSED(self),
                                video_offset_t UNUSED(wrdst_x), video_offset_t UNUSED(wrdst_y),
                                video_offset_t UNUSED(rddst_x), video_offset_t UNUSED(rddst_y),
                                video_dim_t UNUSED(dst_size_x), video_dim_t UNUSED(dst_size_y),
                                video_offset_t UNUSED(src_x), video_offset_t UNUSED(src_y),
                                video_dim_t UNUSED(src_size_x), video_dim_t UNUSED(src_size_y)) {
	COMPILER_IMPURE();
}

INTERN struct video_blitter3_ops libvideo_emptyblitter3_ops = {};
DEFINE_PUBLIC_ALIAS(video_emptyblitter3_ops, _libvideo_emptyblitter3_ops);
INTERN ATTR_RETNONNULL WUNUSED struct video_blitter3_ops const *CC _libvideo_emptyblitter3_ops(void) {
	if unlikely(!libvideo_emptyblitter3_ops.vbt3o_bitblit) {
		libvideo_emptyblitter3_ops.vbt3o_stretch = &libvideo_emptyblitter3__stretch;
		COMPILER_WRITE_BARRIER();
		libvideo_emptyblitter3_ops.vbt3o_bitblit = &libvideo_emptyblitter3__blit;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_emptyblitter3_ops;
}



/* Empty video buffer. */
INTERN WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
libvideo_emptybuffer__lock(struct video_buffer *__restrict UNUSED(self),
                           struct video_lock *__restrict lock) {
	lock->vl_data = (byte_t *)lock;
	lock->vl_stride = 1;
	return 0;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
libvideo_emptybuffer__lockregion(struct video_buffer *__restrict self,
                                 struct video_regionlock *__restrict lock) {
	lock->vrl_xbas = 0;
	return libvideo_emptybuffer__lock(self, &lock->vrl_lock);
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
libvideo_emptybuffer__subregion(struct video_surface const *__restrict self,
                                struct video_crect const *__restrict phys_rect) {
	return libvideo_makeemptybuffer_like(self,
	                                     video_crect_getxdim(phys_rect),
	                                     video_crect_getydim(phys_rect));
}
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_emptybuffer__initgfx(struct video_gfx *__restrict self) {
	self->vg_clip.vgc_ops = _libvideo_emptygfx_ops();
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_emptybuffer__updategfx(struct video_gfx *__restrict self,
                                unsigned int UNUSED(what)) {
	COMPILER_IMPURE();
	return self;
}


INTERN struct video_buffer_ops libvideo_emptybuffer_ops = {};
DEFINE_PUBLIC_ALIAS(video_emptybuffer_ops, _libvideo_emptybuffer_ops);
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _libvideo_emptybuffer_ops(void) {
	if (!libvideo_emptybuffer_ops.vi_initgfx) {
		libvideo_emptybuffer_ops.vi_rlock        = &libvideo_emptybuffer__lock;
		libvideo_emptybuffer_ops.vi_wlock        = &libvideo_emptybuffer__lock;
		libvideo_emptybuffer_ops.vi_unlock       = &libvideo_buffer_noop__unlock;
		libvideo_emptybuffer_ops.vi_rlockregion  = &libvideo_emptybuffer__lockregion;
		libvideo_emptybuffer_ops.vi_wlockregion  = &libvideo_emptybuffer__lockregion;
		libvideo_emptybuffer_ops.vi_unlockregion = &libvideo_buffer_noop__unlockregion;
		libvideo_emptybuffer_ops.vi_updategfx    = &libvideo_emptybuffer__updategfx;
		libvideo_emptybuffer_ops.vi_subregion    = &libvideo_emptybuffer__subregion;
		libvideo_emptybuffer_ops.vi_revoke       = &libvideo_emptybuffer__revoke;
		COMPILER_WRITE_BARRIER();
		libvideo_emptybuffer_ops.vi_initgfx = &libvideo_emptybuffer__initgfx;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_emptybuffer_ops;
}


INTERN struct video_buffer libvideo_emptybuffer = {
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

DEFINE_PUBLIC_ALIAS(video_emptybuffer, _libvideo_emptybuffer);
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer *CC _libvideo_emptybuffer(void) {
	if (!libvideo_emptybuffer.vb_ops) {
		libvideo_emptybuffer.vb_domain = _libvideo_ramdomain();
		libvideo_emptybuffer.vb_codec  = libvideo_codec_lookup(VIDEO_CODEC_RGBA8888);
		assertf(libvideo_emptybuffer.vb_codec, "Built-in codec should have been recognized");
		libvideo_emptybuffer.vb_surf.vs_buffer = &libvideo_emptybuffer;
		COMPILER_WRITE_BARRIER();
		libvideo_emptybuffer.vb_ops = _libvideo_emptybuffer_ops();
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_emptybuffer;
}

DEFINE_PUBLIC_ALIAS(video_emptybufferref, _libvideo_emptybufferref);
INTERN ATTR_RETNONNULL WUNUSED REF struct video_buffer *CC
_libvideo_emptybufferref(void) {
	struct video_buffer *result = _libvideo_emptybuffer();
	video_buffer_incref(result);
	return result;
}



/* Construct (or re-using an existing) empty video buffer with the given dimension
 * The returned buffer always uses `video_ramdomain(3V)' as its associated domain.
 * @param: buffer_xdim, buffer_ydim: Dimensions of the returned buffer (**NOT** swapped if VIDEO_GFX_F_XYSWAP is set)
 * @return: * : A reference to a video buffer without any backing
 *              storage, and  dimensions  matching  those  given.
 * @return: NULL: [errno=ENOMEM] Out of memory. */
PRIVATE WUNUSED REF struct video_buffer *CC
libvideo_makeemptybuffer_impl(video_dim_t xdim, video_dim_t ydim) {
	REF struct video_buffer *result;
	result = (REF struct video_buffer *)malloc(sizeof(struct video_buffer));
	if unlikely(!result)
		goto err;
	__video_buffer_init_dim(result, xdim, ydim);
	__video_buffer_init_ops(result, _libvideo_emptybuffer_ops());
	__video_buffer_init_domain(result, _libvideo_ramdomain());
	return result;
err:
	return NULL;
}

DEFINE_PUBLIC_ALIAS(video_makeemptybuffer, libvideo_makeemptybuffer);
INTERN WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_makeemptybuffer(struct video_buffer_format const *__restrict format,
                         video_dim_t xdim, video_dim_t ydim) {
	REF struct video_buffer *result;
	if (xdim == 0 && ydim == 0 &&
	    format->vbf_codec->vc_codec == VIDEO_CODEC_RGBA8888 &&
	    format->vbf_flags == VIDEO_GFX_F_NORMAL)
		return _libvideo_emptybufferref();
	result = libvideo_makeemptybuffer_impl(xdim, ydim);
	if unlikely(!result)
		goto err;
	__video_buffer_init_format(result, format);
	__video_buffer_init_common(result);
	return result;
err:
	return NULL;
}

DEFINE_PUBLIC_ALIAS(video_makeemptybuffer_like, libvideo_makeemptybuffer_like);
INTERN WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_makeemptybuffer_like(struct video_surface const *__restrict surf,
                              video_dim_t xdim, video_dim_t ydim) {
	REF struct video_buffer *result;
	if (xdim == 0 && ydim == 0 &&
	    video_surface_getcodec(surf)->vc_codec == VIDEO_CODEC_RGBA8888 &&
	    video_surface_getflags(surf) == VIDEO_GFX_F_NORMAL)
		return _libvideo_emptybufferref();
	result = libvideo_makeemptybuffer_impl(xdim, ydim);
	if unlikely(!result)
		goto err;
	result->vb_surf.vs_pal      = surf->vs_pal;
	result->vb_surf.vs_flags    = surf->vs_flags;
	result->vb_surf.vs_colorkey = surf->vs_colorkey;
	result->vb_codec = video_surface_getcodec(surf);
	__video_buffer_init_dim(result, xdim, ydim);
	__video_buffer_init_common(result);
	return result;
err:
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_EMPTY_C */
