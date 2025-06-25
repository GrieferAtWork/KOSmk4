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
#include "../gfx.c"
#define DEFINE_libvideo_gfx__blitfrom_n
//#define DEFINE_libvideo_gfx__blitfrom_l
#endif /* __INTELLISENSE__ */

#include <hybrid/compiler.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "../api.h"
#include "../gfx.h"

#if (defined(DEFINE_libvideo_gfx__blitfrom_n) + \
     defined(DEFINE_libvideo_gfx__blitfrom_l)) != 1
#error "Must #define exactly one of these"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_libvideo_gfx__blitfrom_n
#define LOCAL_IS_NEAREST
#elif defined(DEFINE_libvideo_gfx__blitfrom_l)
#define LOCAL_IS_LINEAR
#else /* ... */
#error "Invalid configuration"
#endif /* !... */

#ifdef LOCAL_IS_NEAREST
#define LOCAL_Xnl(x) x##_n
#else /* LOCAL_IS_NEAREST */
#define LOCAL_Xnl(x) x##_l
#endif /* !LOCAL_IS_NEAREST */

#define LOCAL_libvideo_blitter_samebuf__stretch_X                 LOCAL_Xnl(libvideo_blitter_samebuf__stretch)
#define LOCAL_libvideo_blitter_noblend_samefmt__stretch_X         LOCAL_Xnl(libvideo_blitter_noblend_samefmt__stretch)
#define LOCAL_libvideo_blitter_noblend_difffmt__stretch_X         LOCAL_Xnl(libvideo_blitter_noblend_difffmt__stretch)
#define LOCAL_libvideo_blitter_generic__stretch_X                 LOCAL_Xnl(libvideo_blitter_generic__stretch)
#define LOCAL_libvideo_blitter_samebuf__stretch_imatrix_X         LOCAL_Xnl(libvideo_blitter_samebuf__stretch_imatrix)
#define LOCAL_libvideo_blitter_noblend_samefmt__stretch_imatrix_X LOCAL_Xnl(libvideo_blitter_noblend_samefmt__stretch_imatrix)
#define LOCAL_libvideo_blitter_noblend_difffmt__stretch_imatrix_X LOCAL_Xnl(libvideo_blitter_noblend_difffmt__stretch_imatrix)
#define LOCAL_libvideo_blitter_generic__stretch_imatrix_X         LOCAL_Xnl(libvideo_blitter_generic__stretch_imatrix)
#define LOCAL_libvideo_gfx_noblend__blitfrom_X                    LOCAL_Xnl(libvideo_gfx_noblend__blitfrom)
#define LOCAL_libvideo_gfx_generic__blitfrom_X                    LOCAL_Xnl(libvideo_gfx_generic__blitfrom)

#ifndef DEFINED_noblend_blit_compatible
#define DEFINED_noblend_blit_compatible
LOCAL ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) bool FCC
noblend_blit_compatible(struct video_codec const *dst,
                        struct video_codec const *src) {
	if (dst == src)
		return true;

	/* Certain codecs can still be blit onto each other without color conversion.
	 * This  is possible  whenever all color  channels present in  "dst" are also
	 * present at the same positions in "src".
	 *
	 * This is usually the case when "dst" lacks an alpha-channel and instead
	 * features some unused padding in its place. */
#ifndef __OPTIMIZE_SIZE__
	switch (dst->vc_codec) {
	case VIDEO_CODEC_RGBX8888:
		return src->vc_codec == VIDEO_CODEC_RGBA8888;
	case VIDEO_CODEC_XRGB8888:
		return src->vc_codec == VIDEO_CODEC_ARGB8888;
	case VIDEO_CODEC_XBGR8888:
		return src->vc_codec == VIDEO_CODEC_ABGR8888;
	case VIDEO_CODEC_BGRX8888:
		return src->vc_codec == VIDEO_CODEC_BGRA8888;
	case VIDEO_CODEC_RGBX4444:
		return src->vc_codec == VIDEO_CODEC_RGBA4444;
	case VIDEO_CODEC_XRGB4444:
		return src->vc_codec == VIDEO_CODEC_ARGB4444;
	case VIDEO_CODEC_XBGR4444:
		return src->vc_codec == VIDEO_CODEC_ABGR4444;
	case VIDEO_CODEC_BGRX4444:
		return src->vc_codec == VIDEO_CODEC_BGRA4444;
	case VIDEO_CODEC_RGBX5551:
		return src->vc_codec == VIDEO_CODEC_RGBA5551;
	case VIDEO_CODEC_XRGB1555:
		return src->vc_codec == VIDEO_CODEC_ARGB1555;
	case VIDEO_CODEC_XBGR1555:
		return src->vc_codec == VIDEO_CODEC_ABGR1555;
	case VIDEO_CODEC_BGRX5551:
		return src->vc_codec == VIDEO_CODEC_BGRA5551;
	default:
		break;
	}
#endif /* !__OPTIMIZE_SIZE__ */
	if ((dst->vc_specs.vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM)) ==
	    (src->vc_specs.vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM))) {
		if ((dst->vc_specs.vcs_rmask == 0 || dst->vc_specs.vcs_rmask == src->vc_specs.vcs_rmask) &&
		    (dst->vc_specs.vcs_gmask == 0 || dst->vc_specs.vcs_gmask == src->vc_specs.vcs_gmask) &&
		    (dst->vc_specs.vcs_bmask == 0 || dst->vc_specs.vcs_bmask == src->vc_specs.vcs_bmask) &&
		    (dst->vc_specs.vcs_amask == 0 || dst->vc_specs.vcs_amask == src->vc_specs.vcs_amask))
			return true;
	}
	return false;
}
#endif /* !DEFINED_noblend_blit_compatible */

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC
LOCAL_libvideo_gfx_noblend__blitfrom_X(struct video_blitter *__restrict ctx) {
	struct video_buffer const *src_buffer = ctx->vbt_src->vx_buffer;
	struct video_buffer const *dst_buffer = ctx->vbt_dst->vx_buffer;
	video_blit_setops(ctx);

	/* Check for special case: source and target buffers are the same */
	if (src_buffer == dst_buffer) {
		ctx->_vbt_xops.vbtx_stretch         = &LOCAL_libvideo_blitter_samebuf__stretch_X;
		ctx->_vbt_xops.vbtx_stretch_imatrix = &LOCAL_libvideo_blitter_samebuf__stretch_imatrix_X;
		if ((ctx->vbt_src->vx_flags & VIDEO_GFX_FBLUR) == 0 &&
		    VIDEO_COLOR_ISTRANSPARENT(ctx->vbt_src->vx_colorkey)) {
			ctx->_vbt_xops.vbtx_blit         = &libvideo_blitter_noblend_samebuf__blit;
			ctx->_vbt_xops.vbtx_blit_imatrix = &libvideo_blitter_noblend_samebuf__blit_imatrix;
		} else {
			ctx->_vbt_xops.vbtx_blit         = &libvideo_blitter_samebuf__blit;
			ctx->_vbt_xops.vbtx_blit_imatrix = &libvideo_blitter_samebuf__blit_imatrix;
		}
	} else {
		if ((ctx->vbt_src->vx_flags & VIDEO_GFX_FBLUR) == 0 &&
		    VIDEO_COLOR_ISTRANSPARENT(ctx->vbt_src->vx_colorkey)) {
			if (noblend_blit_compatible(dst_buffer->vb_format.vf_codec,
			                            src_buffer->vb_format.vf_codec) &&
			    src_buffer->vb_format.vf_pal == dst_buffer->vb_format.vf_pal) {
				/* Special optimization when not doing any blending, and both GFX contexts
				 * share the same codec: in this case,  we can try to directly copy  pixel
				 * data, either through video locks, or by directly reading/writing pixels */
				ctx->_vbt_xops.vbtx_blit            = &libvideo_blitter_noblend_samefmt__blit;
				ctx->_vbt_xops.vbtx_stretch         = &LOCAL_libvideo_blitter_noblend_samefmt__stretch_X;
				ctx->_vbt_xops.vbtx_blit_imatrix    = &libvideo_blitter_noblend_samefmt__blit_imatrix;
				ctx->_vbt_xops.vbtx_stretch_imatrix = &LOCAL_libvideo_blitter_noblend_samefmt__stretch_imatrix_X;
			} else {
				/* Special optimization when not doing any blending, and both GFX contexts
				 * share the same codec: in this case,  we can try to directly copy  pixel
				 * data, either through video locks, or by directly reading/writing pixels */
				video_converter_init(libvideo_blitter_generic__conv(ctx),
				                     &src_buffer->vb_format,
				                     &dst_buffer->vb_format);
				ctx->_vbt_xops.vbtx_blit            = &libvideo_blitter_noblend_difffmt__blit;
				ctx->_vbt_xops.vbtx_stretch         = &LOCAL_libvideo_blitter_noblend_difffmt__stretch_X;
				ctx->_vbt_xops.vbtx_blit_imatrix    = &libvideo_blitter_noblend_difffmt__blit_imatrix;
				ctx->_vbt_xops.vbtx_stretch_imatrix = &LOCAL_libvideo_blitter_noblend_difffmt__stretch_imatrix_X;
			}
		} else {
			ctx->_vbt_xops.vbtx_blit            = &libvideo_blitter_generic__blit;
			ctx->_vbt_xops.vbtx_stretch         = &LOCAL_libvideo_blitter_generic__stretch_X;
			ctx->_vbt_xops.vbtx_blit_imatrix    = &libvideo_blitter_generic__blit_imatrix;
			ctx->_vbt_xops.vbtx_stretch_imatrix = &LOCAL_libvideo_blitter_generic__stretch_imatrix_X;
		}
	}
	return ctx;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC
LOCAL_libvideo_gfx_generic__blitfrom_X(struct video_blitter *__restrict ctx) {
	struct video_buffer const *src_buffer = ctx->vbt_src->vx_buffer;
	struct video_buffer const *dst_buffer = ctx->vbt_dst->vx_buffer;
	video_blit_setops(ctx);
	if (src_buffer == dst_buffer) {
		/* Need to use different impls here that essentially do a "memmove"-style blit,
		 * rather  than the usual  "memcpy"-style one (since in  this case, writing new
		 * pixels in an  incorrect order might  clobber other pixels  that have yet  to
		 * be read) */
		ctx->_vbt_xops.vbtx_blit            = &libvideo_blitter_samebuf__blit;
		ctx->_vbt_xops.vbtx_stretch         = &LOCAL_libvideo_blitter_samebuf__stretch_X;
		ctx->_vbt_xops.vbtx_blit_imatrix    = &libvideo_blitter_samebuf__blit_imatrix;
		ctx->_vbt_xops.vbtx_stretch_imatrix = &LOCAL_libvideo_blitter_samebuf__stretch_imatrix_X;
	} else {
		ctx->_vbt_xops.vbtx_blit            = &libvideo_blitter_generic__blit;
		ctx->_vbt_xops.vbtx_stretch         = &LOCAL_libvideo_blitter_generic__stretch_X;
		ctx->_vbt_xops.vbtx_blit_imatrix    = &libvideo_blitter_generic__blit_imatrix;
		ctx->_vbt_xops.vbtx_stretch_imatrix = &LOCAL_libvideo_blitter_generic__stretch_imatrix_X;
	}
	return ctx;
}

#undef LOCAL_libvideo_blitter_samebuf__stretch_X
#undef LOCAL_libvideo_blitter_noblend_samefmt__stretch_X
#undef LOCAL_libvideo_blitter_noblend_difffmt__stretch_X
#undef LOCAL_libvideo_blitter_generic__stretch_X
#undef LOCAL_libvideo_blitter_samebuf__stretch_imatrix_X
#undef LOCAL_libvideo_blitter_noblend_samefmt__stretch_imatrix_X
#undef LOCAL_libvideo_blitter_noblend_difffmt__stretch_imatrix_X
#undef LOCAL_libvideo_blitter_generic__stretch_imatrix_X
#undef LOCAL_libvideo_gfx_noblend__blitfrom_X
#undef LOCAL_libvideo_gfx_generic__blitfrom_X

#undef LOCAL_Xnl

#undef LOCAL_IS_LINEAR
#undef LOCAL_IS_NEAREST

DECL_END

#undef DEFINE_libvideo_gfx__blitfrom_n
#undef DEFINE_libvideo_gfx__blitfrom_l
