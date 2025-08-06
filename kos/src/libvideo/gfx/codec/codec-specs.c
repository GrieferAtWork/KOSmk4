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
#ifndef GUARD_LIBVIDEO_GFX_CODEC_CODEC_SPECS_C
#define GUARD_LIBVIDEO_GFX_CODEC_CODEC_SPECS_C 1
#define __VIDEO_CODEC_const /* nothing */
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include <kos/anno.h>

#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libvideo/gfx/codec/codec.h>

#include "codec-specs.h"
#include "codec-utils.h"
#include "codec.h"

DECL_BEGIN

#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
#define lpixel_t video_pixel64_t
#else /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
#define lpixel_t video_pixel_t
#endif /* !CONFIG_LIBVIDEO_HAVE_PIXEL64 */

/* Same as `video_codec_lookup()', and also only returns built-in codecs, but lookup
 * is  done via `specs', as opposed to the  caller having to provide the codec's ID.
 *
 * NOTE: This function doesn't need `vcs_pxsz' or `vcs_cbits' to be initialized. */
DEFINE_PUBLIC_ALIAS(video_codec_lookup_specs, libvideo_codec_lookup_specs);
INTERN WUNUSED ATTR_PURE ATTR_IN(1) struct video_codec *FCC
libvideo_codec_lookup_specs(struct video_codec_specs const *__restrict specs) {
#define IS_RMASK8_LE(v) (specs->vcs_rmask == MASK8_LE(v))
#define IS_GMASK8_LE(v) (specs->vcs_gmask == MASK8_LE(v))
#define IS_BMASK8_LE(v) (specs->vcs_bmask == MASK8_LE(v))
#define IS_AMASK8_LE(v) (specs->vcs_amask == MASK8_LE(v))
#define IS_RMASK4_LE(v) (specs->vcs_rmask == MASK4_LE(v))
#define IS_GMASK4_LE(v) (specs->vcs_gmask == MASK4_LE(v))
#define IS_BMASK4_LE(v) (specs->vcs_bmask == MASK4_LE(v))
#define IS_AMASK4_LE(v) (specs->vcs_amask == MASK4_LE(v))
#define IS_RMASK3_LE(v) (specs->vcs_rmask == MASK3_LE(v))
#define IS_GMASK3_LE(v) (specs->vcs_gmask == MASK3_LE(v))
#define IS_BMASK3_LE(v) (specs->vcs_bmask == MASK3_LE(v))
#define IS_AMASK3_LE(v) (specs->vcs_amask == MASK3_LE(v))
#define IS_RMASK2_LE(v) (specs->vcs_rmask == MASK2_LE(v))
#define IS_GMASK2_LE(v) (specs->vcs_gmask == MASK2_LE(v))
#define IS_BMASK2_LE(v) (specs->vcs_bmask == MASK2_LE(v))
#define IS_AMASK2_LE(v) (specs->vcs_amask == MASK2_LE(v))
#define IS_RMASK1(v)    (specs->vcs_rmask == v)
#define IS_GMASK1(v)    (specs->vcs_gmask == v)
#define IS_BMASK1(v)    (specs->vcs_bmask == v)
#define IS_AMASK1(v)    (specs->vcs_amask == v)
#define IS_AMASK0()     (specs->vcs_amask == 0)
#define IS_LMASK4_LE    IS_RMASK4_LE
#define IS_LMASK3_LE    IS_RMASK3_LE
#define IS_LMASK2_LE    IS_RMASK2_LE
#define IS_LMASK1       IS_RMASK1
#define IS_LMASK0()     IS_LMASK1(0)
	video_codec_t codec = VIDEO_CODEC_NONE;
	if (specs->vcs_flags & (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_PAL)) {
		/* Grayscale (luminance) or palette */
		if (specs->vcs_gmask == specs->vcs_rmask &&
		    specs->vcs_bmask == specs->vcs_rmask) {
			if (specs->vcs_rmask == (((lpixel_t)1 << specs->vcs_bpp) - 1) && IS_AMASK0()) {
				/* No alpha channel */
				switch (specs->vcs_bpp) {
				case 1: codec = VIDEO_CODEC_L1_MSB; break;
				case 2: codec = VIDEO_CODEC_L2_MSB; break;
				case 4: codec = VIDEO_CODEC_L4_MSB; break;
				case 8: codec = VIDEO_CODEC_L8; break;
				case 16: codec = VIDEO_CODEC_L16; break;
				default: goto nope;
				}
				static_assert((VIDEO_CODEC_L1_MSB + 1) == VIDEO_CODEC_L1_LSB);
				static_assert((VIDEO_CODEC_L2_MSB + 1) == VIDEO_CODEC_L2_LSB);
				static_assert((VIDEO_CODEC_L4_MSB + 1) == VIDEO_CODEC_L4_LSB);
				if (VIDEO_CODEC_FLAG_ISLSB(specs->vcs_flags) && specs->vcs_bpp < 8)
					++codec;
			} else if (!IS_AMASK0() && IS_LMASK0()) {
				if (specs->vcs_amask == (((lpixel_t)1 << specs->vcs_bpp) - 1)) {
					/* Alpha-only */
					switch (specs->vcs_bpp) {
					case 1: codec = VIDEO_CODEC_A1_MSB; break;
					case 2: codec = VIDEO_CODEC_A2_MSB; break;
					case 4: codec = VIDEO_CODEC_A4_MSB; break;
					case 8: codec = VIDEO_CODEC_A8; break;
					case 16: codec = VIDEO_CODEC_A16; break;
					default: goto nope;
					}
					static_assert((VIDEO_CODEC_A1_MSB + 1) == VIDEO_CODEC_A1_LSB);
					static_assert((VIDEO_CODEC_A2_MSB + 1) == VIDEO_CODEC_A2_LSB);
					static_assert((VIDEO_CODEC_A4_MSB + 1) == VIDEO_CODEC_A4_LSB);
					if (VIDEO_CODEC_FLAG_ISLSB(specs->vcs_flags) && specs->vcs_bpp < 8)
						++codec;
				}
			} else {
				/* With alpha channel */
				switch (specs->vcs_bpp) {

				case 2: {
					if (IS_LMASK1(0x1) && IS_AMASK1(0x2)) {
						codec = VIDEO_CODEC_LA11_MSB;
					} else if (IS_LMASK1(0x2) && IS_AMASK1(0x1)) {
						codec = VIDEO_CODEC_AL11_MSB;
					} else {
						goto nope;
					}
					static_assert((VIDEO_CODEC_AL11_MSB + 1) == VIDEO_CODEC_AL11_LSB);
					static_assert((VIDEO_CODEC_LA11_MSB + 1) == VIDEO_CODEC_LA11_LSB);
					if (VIDEO_CODEC_FLAG_ISLSB(specs->vcs_flags))
						++codec;
				}	break;

				case 4: {
					if (IS_LMASK1(0x3) && IS_AMASK1(0xc)) {
						codec = VIDEO_CODEC_LA22_MSB;
					} else if (IS_LMASK1(0xc) && IS_AMASK1(0x3)) {
						codec = VIDEO_CODEC_AL22_MSB;
					} else if (IS_LMASK1(0x7) && IS_AMASK1(0x8)) {
						codec = VIDEO_CODEC_LA31_MSB;
					} else if (IS_LMASK1(0xe) && IS_AMASK1(0x1)) {
						codec = VIDEO_CODEC_AL13_MSB;
					} else {
						goto nope;
					}
					static_assert((VIDEO_CODEC_LA22_MSB + 1) == VIDEO_CODEC_LA22_LSB);
					static_assert((VIDEO_CODEC_AL22_MSB + 1) == VIDEO_CODEC_AL22_LSB);
					static_assert((VIDEO_CODEC_LA31_MSB + 1) == VIDEO_CODEC_LA31_LSB);
					static_assert((VIDEO_CODEC_AL13_MSB + 1) == VIDEO_CODEC_AL13_LSB);
					if (VIDEO_CODEC_FLAG_ISLSB(specs->vcs_flags))
						++codec;
				}	break;

				case 8: {
					if (IS_LMASK1(0x0f) && IS_AMASK1(0xf0)) {
						codec = VIDEO_CODEC_LA44;
					} else if (IS_LMASK1(0xf0) && IS_AMASK1(0x0f)) {
						codec = VIDEO_CODEC_AL44;
					} else if (IS_LMASK1(0x7f) && IS_AMASK1(0x80)) {
						codec = VIDEO_CODEC_LA71;
					} else if (IS_LMASK1(0xfe) && IS_AMASK1(0x01)) {
						codec = VIDEO_CODEC_AL17;
					} else {
						goto nope;
					}
				}	break;

				case 16: {
					if (IS_LMASK2_LE(0x00ff) && IS_AMASK2_LE(0xff00)) {
						codec = VIDEO_CODEC_LA88;
					} else if (IS_LMASK2_LE(0xff00) && IS_AMASK2_LE(0x00ff)) {
						codec = VIDEO_CODEC_AL88;
					} else if (IS_LMASK2_LE(0xffff) && IS_AMASK0()) {
						codec = VIDEO_CODEC_L16;
					} else if (IS_LMASK0() && IS_AMASK2_LE(0xffff)) {
						codec = VIDEO_CODEC_A16;
					} else {
						goto nope;
					}
				}	break;

				default: goto nope;
				}
			}
		}
		if (codec != VIDEO_CODEC_NONE && (specs->vcs_flags & VIDEO_CODEC_FLAG_PAL)) {
			/* Convert luminance codec to its palette equivalent */
#define LUM2PAL_OFFSET (VIDEO_CODEC_P1_MSB - VIDEO_CODEC_L1_MSB)
#define LUM2PAL(id)    ((id) + LUM2PAL_OFFSET)
			static_assert(LUM2PAL(VIDEO_CODEC_L1_MSB) == VIDEO_CODEC_P1_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_L1_LSB) == VIDEO_CODEC_P1_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_L2_MSB) == VIDEO_CODEC_P2_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_L2_LSB) == VIDEO_CODEC_P2_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_L4_MSB) == VIDEO_CODEC_P4_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_L4_LSB) == VIDEO_CODEC_P4_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_L8) == VIDEO_CODEC_P8);
			static_assert(LUM2PAL(VIDEO_CODEC_L16) == VIDEO_CODEC_P16);
			static_assert(LUM2PAL(VIDEO_CODEC_LA11_MSB) == VIDEO_CODEC_PA11_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_LA11_LSB) == VIDEO_CODEC_PA11_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_AL11_MSB) == VIDEO_CODEC_AP11_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_AL11_LSB) == VIDEO_CODEC_AP11_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_LA22_MSB) == VIDEO_CODEC_PA22_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_LA22_LSB) == VIDEO_CODEC_PA22_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_AL22_MSB) == VIDEO_CODEC_AP22_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_AL22_LSB) == VIDEO_CODEC_AP22_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_LA31_MSB) == VIDEO_CODEC_PA31_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_LA31_LSB) == VIDEO_CODEC_PA31_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_AL13_MSB) == VIDEO_CODEC_AP13_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_AL13_LSB) == VIDEO_CODEC_AP13_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_LA44) == VIDEO_CODEC_PA44);
			static_assert(LUM2PAL(VIDEO_CODEC_AL44) == VIDEO_CODEC_AP44);
			static_assert(LUM2PAL(VIDEO_CODEC_LA71) == VIDEO_CODEC_PA71);
			static_assert(LUM2PAL(VIDEO_CODEC_AL17) == VIDEO_CODEC_AP17);
			static_assert(LUM2PAL(VIDEO_CODEC_LA88) == VIDEO_CODEC_PA88);
			static_assert(LUM2PAL(VIDEO_CODEC_AL88) == VIDEO_CODEC_AP88);
			static_assert(LUM2PAL(VIDEO_CODEC_LA1616) == VIDEO_CODEC_PA1616);
			static_assert(LUM2PAL(VIDEO_CODEC_AL1616) == VIDEO_CODEC_AP1616);
			codec = LUM2PAL(codec);
#undef LUM2PAL_OFFSET
#undef LUM2PAL
		}
	} else {
#define SET_CODEC(c) do{codec = (c); goto return_codec;}__WHILE0
		switch (specs->vcs_bpp) {

#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
		case 64:
			if (IS_RMASK8_LE(0x000000000000ffff)) {
				if (IS_GMASK8_LE(0x00000000ffff0000) && IS_BMASK8_LE(0x0000ffff00000000)) {
					if (IS_AMASK8_LE(0xffff000000000000))
						SET_CODEC(VIDEO_CODEC_RGBA16161616);
					if (IS_AMASK0())
						SET_CODEC(VIDEO_CODEC_RGBX16161616);
				}
			} else if (IS_RMASK8_LE(0x00000000ffff0000)) {
				if (IS_GMASK8_LE(0x0000ffff00000000) && IS_BMASK8_LE(0xffff000000000000)) {
					if (IS_AMASK8_LE(0x000000000000ffff))
						SET_CODEC(VIDEO_CODEC_ARGB16161616);
					if (IS_AMASK0())
						SET_CODEC(VIDEO_CODEC_XRGB16161616);
				}
			} else if (IS_RMASK8_LE(0x0000ffff00000000)) {
				if (IS_GMASK8_LE(0x00000000ffff0000) && IS_BMASK8_LE(0x000000000000ffff)) {
					if (IS_AMASK8_LE(0xffff000000000000))
						SET_CODEC(VIDEO_CODEC_BGRA16161616);
					if (IS_AMASK0())
						SET_CODEC(VIDEO_CODEC_BGRX16161616);
				}
			} else if (IS_RMASK8_LE(0xffff000000000000)) {
				if (IS_GMASK8_LE(0x0000ffff00000000) && IS_BMASK8_LE(0x00000000ffff0000)) {
					if (IS_AMASK8_LE(0x000000000000ffff))
						SET_CODEC(VIDEO_CODEC_ABGR16161616);
					if (IS_AMASK0())
						SET_CODEC(VIDEO_CODEC_XBGR16161616);
				}
			}
			break;
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

		case 32:
			if (IS_RMASK4_LE(0x000000ff)) {
				if (IS_GMASK4_LE(0x0000ff00) && IS_BMASK4_LE(0x00ff0000)) {
					if (IS_AMASK4_LE(0xff000000)) {
						SET_CODEC(VIDEO_CODEC_RGBA8888);
					} else if (IS_AMASK0()) {
						SET_CODEC(VIDEO_CODEC_RGBX8888);
					}
				}
			} else if (IS_AMASK4_LE(0x000000ff)) {
				if (IS_GMASK4_LE(0x00ff0000)) {
					if (IS_RMASK4_LE(0x0000ff00) && IS_BMASK4_LE(0xff000000)) {
						SET_CODEC(VIDEO_CODEC_ARGB8888);
					} else if (IS_RMASK4_LE(0xff000000) &&
					           IS_BMASK4_LE(0x0000ff00)) {
						SET_CODEC(VIDEO_CODEC_ABGR8888);
					}
				}
			} else if (IS_BMASK4_LE(0x000000ff)) {
				if (IS_GMASK4_LE(0x0000ff00) && IS_RMASK4_LE(0x00ff0000)) {
					if (IS_AMASK4_LE(0xff000000)) {
						SET_CODEC(VIDEO_CODEC_BGRA8888);
					} else if (IS_AMASK0()) {
						SET_CODEC(VIDEO_CODEC_BGRX8888);
					}
				}
			} else if (IS_RMASK4_LE(0x0000ff00)) {
				if (IS_GMASK4_LE(0x00ff0000) && IS_BMASK4_LE(0xff000000) && IS_AMASK0())
					SET_CODEC(VIDEO_CODEC_XRGB8888);
			} else if (IS_BMASK4_LE(0x0000ff00)) {
				if (IS_GMASK4_LE(0x00ff0000) && IS_RMASK4_LE(0xff000000) && IS_AMASK0())
					SET_CODEC(VIDEO_CODEC_XBGR8888);
			} else {
				/* 32bpp HDR codecs */
				if (IS_AMASK0()) {
					if (IS_RMASK4_LE(0x000007ff)) {
						if (IS_GMASK4_LE(0x003ff800) && IS_BMASK4_LE(0xffc00000))
							SET_CODEC(VIDEO_CODEC_RGB111110);
						if (IS_GMASK4_LE(0x001ff800) && IS_BMASK4_LE(0xffe00000))
							SET_CODEC(VIDEO_CODEC_RGB111011);
					} else if (IS_GMASK4_LE(0x001ffc00)) {
						if (IS_RMASK4_LE(0x000003ff) && IS_BMASK4_LE(0xffe00000))
							SET_CODEC(VIDEO_CODEC_RGB101111);
						if (IS_RMASK4_LE(0xffe00000) && IS_BMASK4_LE(0x000003ff))
							SET_CODEC(VIDEO_CODEC_BGR101111);
					} else if (IS_BMASK4_LE(0x000007ff)) {
						if (IS_RMASK4_LE(0xffc00000) && IS_GMASK4_LE(0x003ff800))
							SET_CODEC(VIDEO_CODEC_BGR111110);
						if (IS_RMASK4_LE(0xffe00000) && IS_GMASK4_LE(0x001ff800))
							SET_CODEC(VIDEO_CODEC_BGR111011);
					} else if (IS_GMASK4_LE(0x000ffc00)) {
						if (IS_RMASK4_LE(0x000003ff) && IS_BMASK4_LE(0x3ff00000))
							SET_CODEC(VIDEO_CODEC_RGBX1010102);
						if (IS_RMASK4_LE(0x3ff00000) && IS_BMASK4_LE(0x000003ff))
							SET_CODEC(VIDEO_CODEC_BGRX1010102);
					} else if (IS_GMASK4_LE(0x003ff000)) {
						if (IS_RMASK4_LE(0x00000ffc) && IS_BMASK4_LE(0xffc00000))
							SET_CODEC(VIDEO_CODEC_XRGB2101010);
						if (IS_RMASK4_LE(0xffc00000) && IS_BMASK4_LE(0x00000ffc))
							SET_CODEC(VIDEO_CODEC_XBGR2101010);
					}
				} else if (IS_AMASK4_LE(0xc0000000)) {
					if (IS_GMASK4_LE(0x000ffc00)) {
						if (IS_RMASK4_LE(0x000003ff) && IS_BMASK4_LE(0x3ff00000))
							SET_CODEC(VIDEO_CODEC_RGBA1010102);
						if (IS_RMASK4_LE(0x3ff00000) && IS_BMASK4_LE(0x000003ff))
							SET_CODEC(VIDEO_CODEC_BGRA1010102);
					}
				} else if (IS_AMASK4_LE(0x00000003)) {
					if (IS_GMASK4_LE(0x003ff000)) {
						if (IS_RMASK4_LE(0x00000ffc) && IS_BMASK4_LE(0xffc00000))
							SET_CODEC(VIDEO_CODEC_ARGB2101010);
						if (IS_RMASK4_LE(0xffc00000) && IS_BMASK4_LE(0x00000ffc))
							SET_CODEC(VIDEO_CODEC_ABGR2101010);
					}
				}
			}
			break;

		case 24:
			if (IS_AMASK0() && IS_GMASK3_LE(0x00ff00)) {
				if (IS_RMASK3_LE(0x0000ff) && IS_BMASK3_LE(0xff0000)) {
					SET_CODEC(VIDEO_CODEC_RGB888);
				} else if (IS_RMASK3_LE(0xff0000) && IS_BMASK3_LE(0x0000ff)) {
					SET_CODEC(VIDEO_CODEC_BGR888);
				}
			}
			break;

		case 16:
			if (IS_RMASK2_LE(0x000f)) {
				if (IS_GMASK2_LE(0x00f0) && IS_BMASK2_LE(0x0f00)) {
					if (IS_AMASK2_LE(0xf000)) {
						SET_CODEC(VIDEO_CODEC_RGBA4444);
					} else if (IS_AMASK0()) {
						SET_CODEC(VIDEO_CODEC_RGBX4444);
					}
				}
			} else if (IS_BMASK2_LE(0x000f)) {
				if (IS_GMASK2_LE(0x00f0) && IS_RMASK2_LE(0x0f00)) {
					if (IS_AMASK2_LE(0xf000)) {
						SET_CODEC(VIDEO_CODEC_BGRA4444);
					} else if (IS_AMASK0()) {
						SET_CODEC(VIDEO_CODEC_BGRX4444);
					}
				}
			} else if (IS_AMASK2_LE(0x000f)) {
				if (IS_GMASK2_LE(0x0f00)) {
					if (IS_RMASK2_LE(0x00f0) && IS_BMASK2_LE(0xf000)) {
						SET_CODEC(VIDEO_CODEC_ARGB4444);
					} else if (IS_RMASK2_LE(0xf000) && IS_BMASK2_LE(0x00f0)) {
						SET_CODEC(VIDEO_CODEC_ABGR4444);
					}
				}
			} else if (IS_AMASK0()) {
				if (IS_GMASK2_LE(0x0f00)) {
					if (IS_RMASK2_LE(0x00f0) && IS_BMASK2_LE(0xf000)) {
						SET_CODEC(VIDEO_CODEC_XRGB4444);
					} else if (IS_RMASK2_LE(0xf000) && IS_BMASK2_LE(0x00f0)) {
						SET_CODEC(VIDEO_CODEC_XBGR4444);
					}
				}
			}

			if (IS_AMASK0() && IS_GMASK2_LE(0x07e0)) {
				if (IS_RMASK2_LE(0x001f)) {
					if (IS_BMASK2_LE(0xf800))
						SET_CODEC(VIDEO_CODEC_RGB565);
				} else if (IS_BMASK2_LE(0x001f)) {
					if (IS_RMASK2_LE(0xf800))
						SET_CODEC(VIDEO_CODEC_BGR565);
				}
			}

			if (IS_RMASK2_LE(0x001f)) {
				if (IS_GMASK2_LE(0x03e0) && IS_BMASK2_LE(0x7c00)) {
					if (IS_AMASK2_LE(0x8000)) {
						SET_CODEC(VIDEO_CODEC_RGBA5551);
					} else if (IS_AMASK0()) {
						SET_CODEC(VIDEO_CODEC_RGBX5551);
					}
				}
			} else if (IS_AMASK2_LE(0x0001)) {
				if (IS_GMASK2_LE(0x07c0)) {
					if (IS_RMASK2_LE(0x003e) && IS_BMASK2_LE(0xf800)) {
						SET_CODEC(VIDEO_CODEC_ARGB1555);
					} else if (IS_BMASK2_LE(0x003e) &&
					           IS_RMASK2_LE(0xf800)) {
						SET_CODEC(VIDEO_CODEC_ABGR1555);
					}
				}
			} else if (IS_BMASK2_LE(0x001f)) {
				if (IS_GMASK2_LE(0x03e0) && IS_RMASK2_LE(0x7c00)) {
					if (IS_AMASK2_LE(0x8000)) {
						SET_CODEC(VIDEO_CODEC_BGRA5551);
					} else if (IS_AMASK0()) {
						SET_CODEC(VIDEO_CODEC_BGRX5551);
					}
				}
			} else if (IS_AMASK0()) {
				if (IS_GMASK2_LE(0x07c0)) {
					if (IS_RMASK2_LE(0x003e) && IS_BMASK2_LE(0xf800)) {
						SET_CODEC(VIDEO_CODEC_XRGB1555);
					} else if (IS_BMASK2_LE(0x003e) && IS_RMASK2_LE(0xf800)) {
						SET_CODEC(VIDEO_CODEC_XBGR1555);
					}
				}
			}
			break;

		case 8:
			/* 1-byte, direct-color codecs */
			if (IS_AMASK0()) {
				switch (specs->vcs_rmask) {

				case 0xe0:
					if (IS_GMASK1(0x1c) && IS_BMASK1(0x03))
						SET_CODEC(VIDEO_CODEC_RGB332);
					if (IS_GMASK1(0x18) && IS_BMASK1(0x07))
						SET_CODEC(VIDEO_CODEC_RGB323);
					break;

				case 0xc0:
					if (IS_GMASK1(0x38) && IS_BMASK1(0x07))
						SET_CODEC(VIDEO_CODEC_RGB233);
					if (IS_GMASK1(0x30) && IS_BMASK1(0x0c))
						SET_CODEC(VIDEO_CODEC_RGBX2222);
					break;

				case 0x30:
					if (IS_GMASK1(0x0c) && IS_BMASK1(0x03))
						SET_CODEC(VIDEO_CODEC_XRGB2222);
					break;

				case 0x0c:
					if (IS_GMASK1(0x30) && IS_BMASK1(0xc0))
						SET_CODEC(VIDEO_CODEC_BGRX2222);
					break;

				case 0x07:
					if (IS_GMASK1(0x18) && IS_BMASK1(0xe0))
						SET_CODEC(VIDEO_CODEC_BGR323);
					if (IS_GMASK1(0x38) && IS_BMASK1(0xc0))
						SET_CODEC(VIDEO_CODEC_BGR233);
					break;

				case 0x03:
					if (IS_GMASK1(0x1c) && IS_BMASK1(0xe0))
						SET_CODEC(VIDEO_CODEC_BGR332);
					if (IS_GMASK1(0x0c) && IS_BMASK1(0x30))
						SET_CODEC(VIDEO_CODEC_XBGR2222);
					break;

				default: goto nope;
				}
			} else {
				switch (specs->vcs_rmask) {

				case 0xc0:
					if (IS_GMASK1(0x30) && IS_BMASK1(0x0c) && IS_AMASK1(0x03))
						SET_CODEC(VIDEO_CODEC_RGBA2222);
					break;

				case 0x30:
					if (IS_GMASK1(0x0c) && IS_BMASK1(0x03) && IS_AMASK1(0xc0))
						SET_CODEC(VIDEO_CODEC_ARGB2222);
					break;

				case 0x0c:
					if (IS_GMASK1(0x30) && IS_BMASK1(0xc0) && IS_AMASK1(0x03))
						SET_CODEC(VIDEO_CODEC_BGRA2222);
					break;

				case 0x03:
					if (IS_GMASK1(0x0c) && IS_BMASK1(0x30) && IS_AMASK1(0xc0))
						SET_CODEC(VIDEO_CODEC_ABGR2222);
					break;

				default: goto nope;
				}
			}
			break;

		default: goto nope;
		}
	}
return_codec:
	return libvideo_codec_lookup(codec);
nope:
	return NULL;
#undef IS_RMASK8_LE
#undef IS_GMASK8_LE
#undef IS_BMASK8_LE
#undef IS_AMASK8_LE
#undef IS_RMASK4_LE
#undef IS_GMASK4_LE
#undef IS_BMASK4_LE
#undef IS_AMASK4_LE
#undef IS_RMASK3_LE
#undef IS_GMASK3_LE
#undef IS_BMASK3_LE
#undef IS_AMASK3_LE
#undef IS_RMASK2_LE
#undef IS_GMASK2_LE
#undef IS_BMASK2_LE
#undef IS_AMASK2_LE
#undef IS_RMASK1
#undef IS_GMASK1
#undef IS_BMASK1
#undef IS_AMASK1
#undef IS_AMASK0
#undef IS_LMASK4_LE
#undef IS_LMASK3_LE
#undef IS_LMASK2_LE
#undef IS_LMASK1
#undef IS_LMASK0
}


PRIVATE NONNULL((1)) void FCC
custom_codec_destroy(struct video_codec *__restrict self) {
	struct video_codec_custom *me = (struct video_codec_custom *)self;
	if (me->vc_nalgn != me)
		video_codec_decref(me->vc_nalgn);
	free(me);
}



/* Same as `video_codec_lookup_specs()', but can also be used to construct
 * new codecs on-the-fly. Because this function is able/allowed to  create
 * new codecs on-the-fly, the caller must take ownership of a reference to
 * `*p_handle'  on success, and  keep that reference alive  for as long as
 * the returned codec is in-use.
 *
 * When the described codec is actually a built-in one, this function always
 * succeeds,  and a  reference to a  dummy object is  stored in `*p_handle'.
 *
 * NOTE: This function doesn't need `vcs_pxsz' or `vcs_cbits' to be initialized.
 *
 * @return: * :   The codec in question (`*p_handle' must be inherited in this case)
 * @return: NULL: [EINVAL] Impossible codec
 * @return: NULL: [ENOMEM] Out-of-memory
 * @return: NULL: [*] Error */
DEFINE_PUBLIC_ALIAS(video_codec_fromspecs, libvideo_codec_fromspecs);
INTERN WUNUSED ATTR_IN(1) REF struct video_codec *FCC
libvideo_codec_fromspecs(struct video_codec_specs const *__restrict specs) {
	struct video_codec *builtin;
	REF struct video_codec_custom *result;

	/* Check if the codec is available as a built-in */
	builtin = libvideo_codec_lookup_specs(specs);
	if (builtin) {
		video_codec_incref(builtin);
		return builtin;
	}

	/* Allocate a custom codec handle (aligned-only for now) */
	result = (struct video_codec_custom *)malloc(sizeof(struct video_codec_custom));
	if unlikely(!result)
		goto err;

	/* Populate the new codec's specs. */
	memcpy(&result->vc_specs, specs, sizeof(struct video_codec_specs));
	if unlikely(!libvideo_codec_populate_custom(result, false))
		goto err_inval;

	/* Check if we also need the unaligned version of the codec. */
	if (result->vc_nalgn == NULL) {
		REF struct video_codec_custom *nalign_result;
		nalign_result = (struct video_codec_custom *)malloc(sizeof(struct video_codec_custom));
		if unlikely(!nalign_result) {
			free(result);
			return NULL;
		}
		memcpy(&nalign_result->vc_specs, specs, sizeof(struct video_codec_specs));
		if unlikely(!libvideo_codec_populate_custom(nalign_result, true)) {
			free(nalign_result);
			goto err_inval;
		}
		assert(nalign_result->vc_nalgn == nalign_result);
		result->vc_nalgn = nalign_result;
		nalign_result->vc_refcnt  = 1;
		nalign_result->vc_destroy = &custom_codec_destroy;
	}

	/* Finish initialization & return the aligned version of the codec. */
	result->vc_destroy = &custom_codec_destroy;
	result->vc_refcnt  = 1;
	return result;
err_inval:
	free(result);
	errno = EINVAL;
err:
	return NULL;
}



DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_CODEC_CODEC_SPECS_C */
