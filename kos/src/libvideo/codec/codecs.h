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
#ifndef GUARD_LIBVIDEO_CODEC_CODECS_H
#define GUARD_LIBVIDEO_CODEC_CODECS_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/__byteswap.h>
#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#include <kos/types.h>

#include <libvideo/codec/codecs.h>

DECL_BEGIN

#define MASKn(n) (((video_pixel_t)1 << (n)) - 1)

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define MASK4_BE(x) __hybrid_bswap32_c(__UINT32_C(x))
#define MASK3_BE(x) (__hybrid_bswap32_c(__UINT32_C(x)) >> 8)
#define MASK2_BE(x) __hybrid_bswap16_c(__UINT16_C(x))
#define MASK4_LE(x) __UINT32_C(x)
#define MASK3_LE(x) __UINT32_C(x)
#define MASK2_LE(x) __UINT16_C(x)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define MASK4_BE(x) __UINT32_C(x)
#define MASK3_BE(x) __UINT32_C(x)
#define MASK2_BE(x) __UINT16_C(x)
#define MASK4_LE(x) __hybrid_bswap32_c(__UINT32_C(x))
#define MASK3_LE(x) (__hybrid_bswap32_c(__UINT32_C(x)) >> 8)
#define MASK2_LE(x) __hybrid_bswap16_c(__UINT16_C(x))
#endif /* __BYTE_ORDER__ == ... */



/* Lookup the interface for a given codec, or return NULL if the codec isn't supported.
 * Don't declare as  ATTR_CONST; in  PIC-mode, needs  to do  one-time-init of  globals! */
INTDEF /*ATTR_CONST*/ WUNUSED struct video_codec const *CC
libvideo_codec_lookup(video_codec_t codec);

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
 * - vc_linefill
 * - vc_pixel2color
 * - vc_color2pixel
 * - vcc_*
 * As such, the caller need only initialize:
 * - vc_specs   (excluding the "vcs_pxsz" and "vcs_cbits" fields)
 *
 * @return: true:  Success -- all fields initialized
 * @return: false: Failure -- codec cannot be represented */
INTDEF WUNUSED NONNULL((1)) bool CC
libvideo_codec_populate_custom(struct video_codec_custom *__restrict self,
                               bool populate_noalign);

DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_CODECS_H */
