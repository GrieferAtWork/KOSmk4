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
#ifndef _LIBVIDEO_CODEC_CODECS_H
#define _LIBVIDEO_CODEC_CODECS_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/__atomic.h>
#include <hybrid/typecore.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/refcnt.h>

#include "pixel.h"
#include "types.h"

__DECL_BEGIN

#define VIDEO_CODEC_NONE       0x0000 /* Invalid codec. */
#define VIDEO_CODEC_CUSTOM     0xffff /* Custom codec (not one of the built-in ones) */

/* Gray-scale */
#define VIDEO_CODEC_GRAY2_LSB  0x1001 /* 1-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b76543210" (e.g. x=1 is defined by "byte & 0x02") */
#define VIDEO_CODEC_GRAY2_MSB  0x1002 /* 1-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b01234567" (e.g. x=1 is defined by "byte & 0x40") */
#define VIDEO_CODEC_GRAY4_LSB  0x1003 /* 2-bit-per-pixel, 4-color grayscale (0=black; 3=white), left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_GRAY4_MSB  0x1004 /* 2-bit-per-pixel, 4-color grayscale (0=black; 3=white), left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_GRAY16_LSB 0x1005 /* 4-bit-per-pixel, 16-color grayscale (0=black; 15=white), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_GRAY16_MSB 0x1006 /* 4-bit-per-pixel, 16-color grayscale (0=black; 15=white), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_GRAY256    0x1007 /* 8-bit-per-pixel, 256-color grayscale (0=black; 255=white) */

/* Full-color */
#define VIDEO_CODEC_RGBA8888   0x2001
#define VIDEO_CODEC_RGBX8888   0x2002
#define VIDEO_CODEC_ARGB8888   0x2003
#define VIDEO_CODEC_XRGB8888   0x2004
#define VIDEO_CODEC_ABGR8888   0x2005
#define VIDEO_CODEC_XBGR8888   0x2006
#define VIDEO_CODEC_BGRA8888   0x2007
#define VIDEO_CODEC_BGRX8888   0x2008
#define VIDEO_CODEC_RGB888     0x2009
#define VIDEO_CODEC_BGR888     0x200a
#define VIDEO_CODEC_RGBA4444   0x2011
#define VIDEO_CODEC_RGBX4444   0x2012
#define VIDEO_CODEC_ARGB4444   0x2013
#define VIDEO_CODEC_XRGB4444   0x2014
#define VIDEO_CODEC_ABGR4444   0x2015
#define VIDEO_CODEC_XBGR4444   0x2016
#define VIDEO_CODEC_BGRA4444   0x2017
#define VIDEO_CODEC_BGRX4444   0x2018
#define VIDEO_CODEC_RGB565     0x2019
#define VIDEO_CODEC_BGR565     0x201a
#define VIDEO_CODEC_RGBA5551   0x2021
#define VIDEO_CODEC_RGBX5551   0x2022
#define VIDEO_CODEC_ARGB1555   0x2023
#define VIDEO_CODEC_XRGB1555   0x2024
#define VIDEO_CODEC_ABGR1555   0x2025
#define VIDEO_CODEC_XBGR1555   0x2026
#define VIDEO_CODEC_BGRA5551   0x2027
#define VIDEO_CODEC_BGRX5551   0x2028

/* Palette-driven */
#define VIDEO_CODEC_PAL2_LSB   0xf001 /* 2-color palette, (1-bit pixels), left->right pixels are encoded in a byte as "0b76543210" (e.g. x=1 is defined by "byte & 0x02") */
#define VIDEO_CODEC_PAL2_MSB   0xf002 /* 2-color palette, (1-bit pixels), left->right pixels are encoded in a byte as "0b01234567" (e.g. x=1 is defined by "byte & 0x40") */
#define VIDEO_CODEC_PAL4_LSB   0xf003 /* 4-color palette, (2-bit pixels), left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_PAL4_MSB   0xf004 /* 4-color palette, (2-bit pixels), left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_PAL16_LSB  0xf005 /* 16-color palette, (4-bit pixels), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_PAL16_MSB  0xf006 /* 16-color palette, (4-bit pixels), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_PAL256     0xf007 /* 256-color palette (8-bit pixels) */




/* Normal codec flags. */
#define VIDEO_CODEC_FLAG_NORMAL 0x0000 /* Normal flags */
#define VIDEO_CODEC_FLAG_PAL    0x0001 /* Does this codec use a palette? */
#define VIDEO_CODEC_FLAG_GRAY   0x0002 /* Is this a grayscale-mode codec? */
#define VIDEO_CODEC_FLAG_LSB    0x0000 /* When multiple pixels fit into a single byte, they are ordered as "0b76543210" (e.g. pixel at x=1 is defined by "byte & 0x02") */
#define VIDEO_CODEC_FLAG_MSB    0x0004 /* When multiple pixels fit into a single byte, they are ordered as "0b01234567" (e.g. pixel at x=1 is defined by "byte & 0x40") */

#ifdef __CC__
typedef __uint16_t video_codec_t; /* One of `VIDEO_CODEC_*' */

struct video_rambuffer_requirements {
	__size_t vbs_bufsize; /* Minimal buffer size (in bytes) */
	__size_t vbs_stride;  /* Minimal scanline stride (in bytes) */
};

struct video_codec_specs {
	__uint16_t vcs_flags; /* Set of `VIDEO_CODEC_FLAG_*' */
	__uint8_t  vcs_bpp;   /* # of bits per pixel (when not divisible by "8", pixels aren't aligned by byte-boundaries) */
	__uint8_t  vcs_cbits; /* [<= vcs_bpp] # of color  bits per pixel.  Usually same as  "vcs_bpp", except when  some bits  go
	                       * unused. In the  case of a  palette-driven codec, `1 << vcs_cbits'  is the size  of the  palette.
	                       * For normal codecs, this is always equal to `SUM(POPCOUNT(vcs_*mask))' (and includes "vcs_amask") */
	/* Color masks. For grayscale / palette-driven codecs, these are all identical and
	 * specify the mask of bits within a single pixel whose "PEXT" result is then used
	 * as palette index / grayscale-strength.
	 *
	 * For multi-byte codecs, these masks assume that you read a pixel as:
	 * >> uintN_t pixel = UNALIGNED_GET((uintN_t *)pixel_addr);
	 * iow: these masks are always in host-endian */
	__uint32_t vcs_rmask; /* Mask of bits in a pixel that make up red */
	__uint32_t vcs_gmask; /* Mask of bits in a pixel that make up green */
	__uint32_t vcs_bmask; /* Mask of bits in a pixel that make up blue */
	/* The alpha-mask does not participate in palette/grayscale lookup; it always functions as its own thing */
	__uint32_t vcs_amask; /* Mask of bits in a pixel that make up alpha */
};

struct video_format;
struct video_codec {
	/* Video format operations. */
	video_codec_t             vc_codec; /* [const] Video codec ID (One of `VIDEO_FORMAT_*') */
	struct video_codec_specs  vc_specs; /* [const] Video format flags (Set of `VIDEO_CODEC_FLAG_*') */
	__uint32_t                vc_align; /* [!0][const] Byte alignment requirements for base_addr/stride of buffers using this codec. */
	struct video_codec const *vc_nalgn; /* [1..1][const] Codec identical to this one, except with `vc_align == 1' */
	/* NOTE: _ALL_ Callbacks are always [1..1] */

	/* Calculate minimal ram-buffer requirements for a graphic with the given dimensions.
	 * Note that in addition, a ram-buffer needs a minimal alignment of `vc_align' bytes. */
	__ATTR_NONNULL_T((3)) void
	(LIBVIDEO_CODEC_CC *vc_rambuffer_requirements)(video_dim_t __size_x, video_dim_t __size_y,
	                                               struct video_rambuffer_requirements *__restrict __result);

	/* Get a pixel (The caller must ensure that the given x is in-bounds) */
	__ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_pixel_t
	(LIBVIDEO_CODEC_CC *vc_getpixel)(__byte_t const *__restrict __line, video_coord_t __x);

	/* Set a pixel (The caller must ensure that the given x is in-bounds) */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_CODEC_CC *vc_setpixel)(__byte_t *__restrict __line,
	                                 video_coord_t __x, video_pixel_t __pixel);

	/* Copy `num_pixels' neighboring (the caller must ensure that all coords are in-bounds) */
	__ATTR_NONNULL_T((1, 3)) void
	(LIBVIDEO_CODEC_CC *vc_linecopy)(__byte_t *__restrict __dst_line, video_coord_t __dst_x,
	                                 __byte_t const *__restrict __src_line, video_coord_t __src_x,
	                                 video_dim_t __num_pixels);

	/* Fill `num_pixels' neighboring (the caller must ensure that all coords are in-bounds) */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_CODEC_CC *vc_linefill)(__byte_t *__restrict __line, video_coord_t __dst_x,
	                                 video_pixel_t __pixel, video_dim_t __num_pixels);

	/* Convert between color and pixel values. */
	__ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_color_t
	(LIBVIDEO_CODEC_CC *vc_pixel2color)(struct video_format const *__restrict __self,
	                                    video_pixel_t __pixel);
	__ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_pixel_t
	(LIBVIDEO_CODEC_CC *vc_color2pixel)(struct video_format const *__restrict __self,
	                                    video_color_t __color);
};


/* Lookup the interface for a given codec, or return NULL if the codec isn't supported. */
typedef __ATTR_CONST_T __ATTR_WUNUSED_T struct video_codec const *
(LIBVIDEO_CODEC_CC *PVIDEO_CODEC_LOOKUP)(video_codec_t __codec);
#ifdef LIBVIDEO_CODEC_WANT_PROTOTYPES
LIBVIDEO_CODEC_DECL __ATTR_WUNUSED __ATTR_CONST struct video_codec const *
(LIBVIDEO_CODEC_CC video_codec_lookup)(video_codec_t __codec);
#endif /* LIBVIDEO_CODEC_WANT_PROTOTYPES */

/* Same as `video_codec_lookup()', and also only returns built-in codecs, but lookup
 * is  done via `specs', as opposed to the  caller having to provide the codec's ID. */
typedef __ATTR_CONST_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) struct video_codec const *
(LIBVIDEO_CODEC_CC *PVIDEO_CODEC_LOOKUP_SPECS)(struct video_codec_specs const *__restrict __specs);
#ifdef LIBVIDEO_CODEC_WANT_PROTOTYPES
LIBVIDEO_CODEC_DECL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) struct video_codec const *
(LIBVIDEO_CODEC_CC video_codec_lookup_specs)(struct video_codec_specs const *__restrict __specs);
#endif /* LIBVIDEO_CODEC_WANT_PROTOTYPES */


/* Anonymous descriptor for a (possibly) dynamically created codec. */
struct video_codec_handle {
	__uintptr_t              vch_refcnt; /* Reference counter. */
	void (LIBVIDEO_CODEC_CC *vch_destroy)(struct video_codec_handle *__restrict __self);
	/* Actual implementation data goes here */
};

#define video_codec_handle_destroy(self) (*(self)->vch_destroy)(self)
#define video_codec_handle_incref(self) \
	__hybrid_atomic_inc(&(self)->vch_refcnt, __ATOMIC_SEQ_CST)
#define video_codec_handle_decref(self)                                       \
	(void)(__hybrid_atomic_decfetch(&(self)->vch_refcnt, __ATOMIC_SEQ_CST) || \
	       (video_codec_handle_destroy(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_codec_handle, vch_refcnt, video_codec_handle_destroy)


/* Same as `video_codec_lookup_specs()', but can  also be used to  construct
 * new codecs on-the-fly (if supported/implemented by the host architecture)
 *
 * Because this function is able/allowed to create new codecs on-the-fly, the
 * caller must take ownership of a  reference to `*p_handle' on success,  and
 * keep that reference alive for as long as the returned codec is in-use.
 *
 * When the described codec is actually a built-in one, this function always
 * succeeds,  and a  reference to a  dummy object is  stored in `*p_handle'.
 *
 * @return: * :   The codec in question (`*p_handle' must be inherited in this case)
 * @return: NULL: [EINVAL] Impossible codec
 * @return: NULL: [ENOMEM] Out-of-memory or too many custom codecs allocated already
 * @return: NULL: [*] Error */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) struct video_codec const *
(LIBVIDEO_CODEC_CC *PVIDEO_CODEC_FROMSPECS)(struct video_codec_specs const *__restrict __specs,
                                            /*out*/ __REF struct video_codec_handle **__restrict __p_handle);
#ifdef LIBVIDEO_CODEC_WANT_PROTOTYPES
LIBVIDEO_CODEC_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) struct video_codec const *
(LIBVIDEO_CODEC_CC video_codec_fromspecs)(struct video_codec_specs const *__restrict __specs,
                                          /*out*/ __REF struct video_codec_handle **__restrict __p_handle);
#endif /* LIBVIDEO_CODEC_WANT_PROTOTYPES */


#endif /* __CC__ */


__DECL_END

#endif /* !_LIBVIDEO_CODEC_CODECS_H */
