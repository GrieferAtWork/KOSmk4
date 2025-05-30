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
#ifdef __INTELLISENSE__
#include "noblend.c.inl"
#define DEFINE_noblend__stretch_l
//#define DEFINE_noblend__stretch_n
#endif /* __INTELLISENSE__ */

#include <hybrid/compiler.h>

#include <stddef.h>
#include <stdint.h>

#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "../api.h"
#include "../gfx.h"

#if (defined(DEFINE_noblend__stretch_l) + \
     defined(DEFINE_noblend__stretch_n)) != 1
#error "Must #define exactly one of these macros"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_noblend__stretch_l
#define LOCAL_libvideo_gfx_noblend__bitstretchfill     libvideo_gfx_noblend__bitstretchfill_l
#define LOCAL_libvideo_gfx_generic__bitstretchfill     libvideo_gfx_generic__bitstretchfill_l
#define LOCAL_libvideo_gfx_generic_samebuf__stretch    libvideo_gfx_generic_samebuf__stretch_l
#define LOCAL_libvideo_gfx_generic_samebuf__bitstretch libvideo_gfx_generic_samebuf__bitstretch_l
#define LOCAL_libvideo_gfx_noblend_samefmt__stretch    libvideo_gfx_noblend_samefmt__stretch_l
#define LOCAL_libvideo_gfx_generic__stretch            libvideo_gfx_generic__stretch_l
#define LOCAL_libvideo_gfx_noblend_samefmt__bitstretch libvideo_gfx_noblend_samefmt__bitstretch_l
#define LOCAL_libvideo_gfx_generic__bitstretch         libvideo_gfx_generic__bitstretch_l
#define LOCAL_libvideo_gfx_noblend__blitfrom           libvideo_gfx_noblend__blitfrom_l
#else /* DEFINE_noblend__stretch_l */
#define LOCAL_libvideo_gfx_noblend__bitstretchfill     libvideo_gfx_noblend__bitstretchfill_n
#define LOCAL_libvideo_gfx_generic__bitstretchfill     libvideo_gfx_generic__bitstretchfill_n
#define LOCAL_libvideo_gfx_generic_samebuf__stretch    libvideo_gfx_generic_samebuf__stretch_n
#define LOCAL_libvideo_gfx_generic_samebuf__bitstretch libvideo_gfx_generic_samebuf__bitstretch_n
#define LOCAL_libvideo_gfx_noblend_samefmt__stretch    libvideo_gfx_noblend_samefmt__stretch_n
#define LOCAL_libvideo_gfx_generic__stretch            libvideo_gfx_generic__stretch_n
#define LOCAL_libvideo_gfx_noblend_samefmt__bitstretch libvideo_gfx_noblend_samefmt__bitstretch_n
#define LOCAL_libvideo_gfx_generic__bitstretch         libvideo_gfx_generic__bitstretch_n
#define LOCAL_libvideo_gfx_noblend__blitfrom           libvideo_gfx_noblend__blitfrom_n
#endif /* !DEFINE_noblend__stretch_l */

INTERN NONNULL((1, 9)) void CC
LOCAL_libvideo_gfx_noblend__bitstretchfill(struct video_gfx *__restrict self,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_dim_t dst_size_x, video_dim_t dst_size_y,
                                           video_color_t color,
                                           video_dim_t src_size_x, video_dim_t src_size_y,
                                           void const *__restrict bitmask,
                                           uintptr_t bitskip, size_t bitscan) {
	/* TODO */
	LOCAL_libvideo_gfx_generic__bitstretchfill(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                           color, src_size_x, src_size_y,
	                                           bitmask, bitskip, bitscan);
}

#include <kos/kernel/printk.h>

INTERN NONNULL((1)) void CC
LOCAL_libvideo_gfx_noblend_samefmt__stretch(struct video_blit *__restrict self,
                                            video_coord_t dst_x, video_coord_t dst_y,
                                            video_dim_t dst_size_x, video_dim_t dst_size_y,
                                            video_coord_t src_x, video_coord_t src_y,
                                            video_dim_t src_size_x, video_dim_t src_size_y) {
	printk(KERN_DEBUG "In: LOCAL_libvideo_gfx_noblend_samefmt__stretch\n");
	/* TODO */
	LOCAL_libvideo_gfx_generic__stretch(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                    src_x, src_y, src_size_x, src_size_y);
}

INTERN NONNULL((1, 10)) void CC
LOCAL_libvideo_gfx_noblend_samefmt__bitstretch(struct video_blit *__restrict self,
                                               video_coord_t dst_x, video_coord_t dst_y,
                                               video_dim_t dst_size_x, video_dim_t dst_size_y,
                                               video_coord_t src_x, video_coord_t src_y,
                                               video_dim_t src_size_x, video_dim_t src_size_y,
                                               void const *__restrict bitmask,
                                               uintptr_t bitskip, size_t bitscan) {
	/* TODO */
	LOCAL_libvideo_gfx_generic__bitstretch(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                       src_x, src_y, src_size_x, src_size_y,
	                                       bitmask, bitskip, bitscan);
}


INTERN ATTR_RETNONNULL NONNULL((1)) struct video_blit *CC
LOCAL_libvideo_gfx_noblend__blitfrom(struct video_blit *__restrict ctx) {
	struct video_buffer const *src_buffer = ctx->vb_src->vx_buffer;
	struct video_buffer const *dst_buffer = ctx->vb_dst->vx_buffer;
	ctx->vb_ops = &libvideo_blit_generic_ops;
	if (src_buffer == dst_buffer) {
		ctx->vb_xops.vbxo_blit       = &libvideo_gfx_generic_samebuf__blit;
		ctx->vb_xops.vbxo_bitblit    = &libvideo_gfx_generic_samebuf__bitblit;
		ctx->vb_xops.vbxo_stretch    = &LOCAL_libvideo_gfx_generic_samebuf__stretch;
		ctx->vb_xops.vbxo_bitstretch = &LOCAL_libvideo_gfx_generic_samebuf__bitstretch;
	} else if (src_buffer->vb_format.vf_codec == dst_buffer->vb_format.vf_codec &&
	           src_buffer->vb_format.vf_pal == dst_buffer->vb_format.vf_pal &&
	           (ctx->vb_src->vx_flags & VIDEO_GFX_FBLUR) == 0 &&
	           (ctx->vb_src->vx_colorkey & VIDEO_COLOR_ALPHA_MASK) == 0) {
		ctx->vb_xops.vbxo_blit       = &libvideo_gfx_noblend_samefmt__blit;
		ctx->vb_xops.vbxo_bitblit    = &libvideo_gfx_noblend_samefmt__bitblit;
		ctx->vb_xops.vbxo_stretch    = &LOCAL_libvideo_gfx_noblend_samefmt__stretch;
		ctx->vb_xops.vbxo_bitstretch = &LOCAL_libvideo_gfx_noblend_samefmt__bitstretch;
	} else {
		ctx->vb_xops.vbxo_blit       = &libvideo_gfx_generic__blit;
		ctx->vb_xops.vbxo_bitblit    = &libvideo_gfx_generic__bitblit;
		ctx->vb_xops.vbxo_stretch    = &LOCAL_libvideo_gfx_generic__stretch;
		ctx->vb_xops.vbxo_bitstretch = &LOCAL_libvideo_gfx_generic__bitstretch;
	}
	return ctx;
}

#undef LOCAL_libvideo_gfx_noblend__bitstretchfill
#undef LOCAL_libvideo_gfx_generic__bitstretchfill
#undef LOCAL_libvideo_gfx_generic_samebuf__stretch
#undef LOCAL_libvideo_gfx_generic_samebuf__bitstretch
#undef LOCAL_libvideo_gfx_noblend_samefmt__stretch
#undef LOCAL_libvideo_gfx_generic__stretch
#undef LOCAL_libvideo_gfx_noblend_samefmt__bitstretch
#undef LOCAL_libvideo_gfx_generic__bitstretch
#undef LOCAL_libvideo_gfx_noblend__blitfrom

DECL_END

#undef DEFINE_noblend__stretch_l
#undef DEFINE_noblend__stretch_n
