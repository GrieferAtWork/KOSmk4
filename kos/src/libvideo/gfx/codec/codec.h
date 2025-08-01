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
#ifndef GUARD_LIBVIDEO_GFX_CODEC_CODEC_H
#define GUARD_LIBVIDEO_GFX_CODEC_CODEC_H 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libvideo/color.h>
#include <libvideo/gfx/codec/codec.h>

DECL_BEGIN

/* Lookup the interface for a given codec, or return NULL if the codec isn't supported.
 * Don't declare as  ATTR_CONST; in  PIC-mode, needs  to do  one-time-init of  globals! */
INTDEF /*ATTR_CONST*/ WUNUSED struct video_codec *FCC
libvideo_codec_lookup(video_codec_t codec);

/* Same as `libvideo_codec_lookup()', but used for "extra" codecs */
INTDEF /*ATTR_CONST*/ WUNUSED struct video_codec *FCC
libvideo_codec_lookup_extra(video_codec_t codec);

struct video_codec_custom: video_codec {
	video_pixel_t vcc_used_rmask; /* Most significant up-to 8 bits of r-mask */
	video_pixel_t vcc_used_gmask; /* Most significant up-to 8 bits of g-mask */
	video_pixel_t vcc_used_bmask; /* Most significant up-to 8 bits of b-mask */
	video_pixel_t vcc_used_amask; /* Most significant up-to 8 bits of a-mask */
	video_pixel_t vcc_xtra_rmask; /* Mask of remaining r-bits not in "vcc_used_rmask" */
	video_pixel_t vcc_xtra_gmask; /* Mask of remaining g-bits not in "vcc_used_gmask" */
	video_pixel_t vcc_xtra_bmask; /* Mask of remaining b-bits not in "vcc_used_bmask" */
	video_pixel_t vcc_xtra_amask; /* Mask of remaining a-bits not in "vcc_used_amask" */
	shift_t       vcc_miss_rbits; /* [== 8 - POPCOUNT(vcc_used_rmask)] # of r-bits lost during encode */
	shift_t       vcc_miss_gbits; /* [== 8 - POPCOUNT(vcc_used_gmask)] # of g-bits lost during encode */
	shift_t       vcc_miss_bbits; /* [== 8 - POPCOUNT(vcc_used_bmask)] # of b-bits lost during encode */
	shift_t       vcc_miss_abits; /* [== 8 - POPCOUNT(vcc_used_amask)] # of a-bits lost during encode */
	shift_t       vcc_shft_rmask; /* `CTZ(vcc_used_rmask)' if `vcc_xtra_rmask == 0' and bits of `vcc_used_rmask' are continuous; else, `(shift_t)-1' */
	shift_t       vcc_shft_gmask; /* `CTZ(vcc_used_gmask)' if `vcc_xtra_gmask == 0' and bits of `vcc_used_gmask' are continuous; else, `(shift_t)-1' */
	shift_t       vcc_shft_bmask; /* `CTZ(vcc_used_bmask)' if `vcc_xtra_bmask == 0' and bits of `vcc_used_bmask' are continuous; else, `(shift_t)-1' */
	shift_t       vcc_shft_amask; /* `CTZ(vcc_used_amask)' if `vcc_xtra_amask == 0' and bits of `vcc_used_amask' are continuous; else, `(shift_t)-1' */
//TODO:#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
//TODO:	video_pixel64_t vcc_used_rmask64; /* Most significant up-to 16 bits of r-mask */
//TODO:	video_pixel64_t vcc_used_gmask64; /* Most significant up-to 16 bits of g-mask */
//TODO:	video_pixel64_t vcc_used_bmask64; /* Most significant up-to 16 bits of b-mask */
//TODO:	video_pixel64_t vcc_used_amask64; /* Most significant up-to 16 bits of a-mask */
//TODO:	video_pixel64_t vcc_xtra_rmask64; /* Mask of remaining r-bits not in "vcc_used_rmask" */
//TODO:	video_pixel64_t vcc_xtra_gmask64; /* Mask of remaining g-bits not in "vcc_used_gmask" */
//TODO:	video_pixel64_t vcc_xtra_bmask64; /* Mask of remaining b-bits not in "vcc_used_bmask" */
//TODO:	video_pixel64_t vcc_xtra_amask64; /* Mask of remaining a-bits not in "vcc_used_amask" */
//TODO:	shift_t         vcc_miss_rbits64; /* [== 16 - POPCOUNT(vcc_used_rmask)] # of r-bits lost during encode64 */
//TODO:	shift_t         vcc_miss_gbits64; /* [== 16 - POPCOUNT(vcc_used_gmask)] # of g-bits lost during encode64 */
//TODO:	shift_t         vcc_miss_bbits64; /* [== 16 - POPCOUNT(vcc_used_bmask)] # of b-bits lost during encode64 */
//TODO:	shift_t         vcc_miss_abits64; /* [== 16 - POPCOUNT(vcc_used_amask)] # of a-bits lost during encode64 */
//TODO:#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
};


/* Try to populate the following fields of `self' based on `self->vc_specs':
 * - vc_specs.vcs_pxsz
 * - vc_specs.vcs_cbits
 * - vc_codec  (always set `VIDEO_CODEC_CUSTOM')
 * - vc_nalgn  (set to "NULL" if an extra codec is needed here)
 * - vc_align
 * - vc_rambuffer_requirements
 * - vc_getpixel
 * - vc_setpixel
 * - vc_linecopy
 * - vc_vertcopy
 * - vc_rectcopy
 * - vc_linefill
 * - vc_vertfill
 * - vc_rectfill
 * - vc_pixel2color
 * - vc_color2pixel
 * - vcc_*
 * As such, the caller need only initialize:
 * - vc_specs   (excluding the "vcs_pxsz" and "vcs_cbits" fields)
 *
 * @return: true:  Success -- all fields initialized
 * @return: false: Failure -- codec cannot be represented */
INTDEF WUNUSED NONNULL((1)) bool FCC
libvideo_codec_populate_custom(struct video_codec_custom *__restrict self,
                               bool populate_noalign);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_CODEC_CODEC_H */
