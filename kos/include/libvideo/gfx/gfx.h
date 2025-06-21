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
#ifndef _LIBVIDEO_GFX_GFX_H
#define _LIBVIDEO_GFX_GFX_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/codec/format.h>

#include "blend.h" /* gfx_blendmode_t */

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

#ifndef __INTELLISENSE__
#include <libc/string.h>
#endif /* !__INTELLISENSE__ */

/* Video graphic flags.
 * [READ]:  Indicates a flag that affects the results when the associated
 *          GFX  context is used  as source, or  when reading pixel data.
 * [WRITE]: Indicates a flag that affects the results of graphics operations
 *          that use  the associated  GFX context  as destination,  or  when
 *          writing pixel data. */
#define VIDEO_GFX_FNORMAL      0x0000 /* Normal render flags. */
#define VIDEO_GFX_FNEARESTBLIT 0x0000 /* [WRITE] Use nearest interpolation for stretch() */
#define VIDEO_GFX_FLINEARBLIT  0x0001 /* [WRITE] Use linear interpolation for stretch() (else: use nearest) */
#define VIDEO_GFX_FAALINES     0x0002 /* [WRITE] Render smooth lines. */
#define VIDEO_GFX_FWRXWRAP     0x0004 /* [WRITE] X coords <0 or >=width wrap to the other side during writes (else: coords are clamped) */
#define VIDEO_GFX_FWRYWRAP     0x0008 /* [WRITE] Y coords <0 or >=height wrap to the other side during writes (else: coords are clamped) */
#define VIDEO_GFX_FBLUR        0x0100 /* [READ]  Pixel reads will return the average of the surrounding 9 pixels.
                                       *         For this purpose, out-of-bounds pixels are ignored (and not part of the average taken)
                                       * The behavior is weak undefined if this flag is used alongside a non-zero color key */
#define VIDEO_GFX_FRDXWRAP     0x0400 /* [READ]  X coords <0 or >=width wrap to the other side during reads (else: coords are clamped) */
#define VIDEO_GFX_FRDYWRAP     0x0800 /* [READ]  Y coords <0 or >=height wrap to the other side during reads (else: coords are clamped) */


/* Flags for `video_gfx_update()' */
#define VIDEO_GFX_UPDATE_NOTHING  0 /* Nothing was changed */
#define VIDEO_GFX_UPDATE_BLEND    1 /* `struct video_gfx::vx_blend' might have been changed */
#define VIDEO_GFX_UPDATE_FLAGS    2 /* `struct video_gfx::vx_flags' might have been changed */
#define VIDEO_GFX_UPDATE_COLORKEY 4 /* `struct video_gfx::vx_colorkey' might have been changed */
#define VIDEO_GFX_UPDATE_ALL     \
	(VIDEO_GFX_UPDATE_COLORKEY | \
	 VIDEO_GFX_UPDATE_FLAGS |    \
	 VIDEO_GFX_UPDATE_BLEND)

#ifdef __CC__
__DECL_BEGIN

struct video_buffer;
struct video_gfxhdr;
struct video_gfx;
struct video_blitter;

/* Video bitmask descriptor.
 *
 * Bitmasks can be used to mask blitting/filling of pixels in
 * fill/blit/stretch  operations, such that only pixels where
 * the corresponding bit is "1"  in the used bitmask will  be
 * copied/filled.
 *
 * Bitmasks are expected to encode their bits similar to
 * `VIDEO_CODEC_L1_MSB', except  that `vbm_skip'  allows
 * the user to specify a bit-perfect starting offset.
 *
 * USAGE:
 * - Bitmasks are meant for rendering of simple terminal fonts,
 *   as well as emulation of hardware VGA fonts. As a matter of
 *   fact: the default VGA terminal font can be rendered when
 *   treated as a bitmask.
 *
 * The status of a pixel is calculated as:
 * >> uintptr_t bitno = vbm_skip + x + y * vbm_scan;
 * >> byte_t byte = ((byte_t const *)vbm_mask)[bitno / NBBY];
 * >> shift_t bit = bitno % NBBY;
 * >> bool status = (byte >> (NBBY - 1 - bit)) & 1;
 */
struct video_bitmask {
	void const *vbm_mask; /* [1..1] Bitmask base pointer */
	__uintptr_t vbm_skip; /* # of leading bits to skip */
	__size_t    vbm_scan; /* # of bits that make up a scanline */
};


struct video_blitter_xops {
	/* All of the following callbacks are [1..1]
	 * WARNING: None of these functions will NOT add `vx_offt_(x|y)' to the given X/Y,
	 *          as well as always  assume that the given  coords are in-bounds of  the
	 *          underlying buffer.
	 * WARNING: Don't use these operators; only use `struct video_gfx_ops' */

#define _VIDEO_BLIT_XOPS__N_INTERNAL 8
#ifndef LIBVIDEO_GFX_EXPOSE_INTERNALS
	void (*_vbtx_internal[_VIDEO_BLIT_XOPS__N_INTERNAL])(void);
#else /* !LIBVIDEO_GFX_EXPOSE_INTERNALS */
	/* Blit the contents of another video buffer into this one.
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vbtx_blit)(struct video_blitter const *__restrict __self,
	                             video_coord_t __dst_x, video_coord_t __dst_y,
	                             video_coord_t __src_x, video_coord_t __src_y,
	                             video_dim_t __size_x, video_dim_t __size_y);

	/* Same as `vbtx_blit', but stretch the contents
	 * @assume(__dst_size_x > 0);
	 * @assume(__dst_size_y > 0);
	 * @assume(__src_size_x > 0);
	 * @assume(__src_size_y > 0);
	 * @assume(__dst_size_x != __src_size_x);
	 * @assume(__dst_size_y != __src_size_y); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vbtx_stretch)(struct video_blitter const *__restrict __self,
	                                video_coord_t __dst_x, video_coord_t __dst_y,
	                                video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                video_coord_t __src_x, video_coord_t __src_y,
	                                video_dim_t __src_size_x, video_dim_t __src_size_y);

	void (*_vbtx_pad[6])(void);
#endif /* LIBVIDEO_GFX_EXPOSE_INTERNALS */
};

struct video_blitter_ops {
	/* Blit the contents of another video buffer into this one. */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vbto_bitblit)(struct video_blitter const *__restrict __self,
	                                video_offset_t __dst_x, video_offset_t __dst_y,
	                                video_offset_t __src_x, video_offset_t __src_y,
	                                video_dim_t __size_x, video_dim_t __size_y);

	/* Same as `vbto_bitblit', but stretch the contents */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vbto_stretch)(struct video_blitter const *__restrict __self,
	                                video_offset_t __dst_x, video_offset_t __dst_y,
	                                video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                video_offset_t __src_x, video_offset_t __src_y,
	                                video_dim_t __src_size_x, video_dim_t __src_size_y);

	/* More driver-specific operators go here... */
};



struct video_gfx_xops {
#define _VIDEO_GFX_XOPS__N_INTERNAL 15
#ifndef LIBVIDEO_GFX_EXPOSE_INTERNALS
	void (*_vgfx_internal[_VIDEO_GFX_XOPS__N_INTERNAL])(void);
#else /* !LIBVIDEO_GFX_EXPOSE_INTERNALS */
	/* All of the following callbacks are [1..1]
	 * WARNING: None of these functions will NOT add `vx_offt_(x|y)' to the given X/Y,
	 *          as well as always  assume that the given  coords are in-bounds of  the
	 *          underlying buffer.
	 * WARNING: Don't use these operators; only use `struct video_gfx_ops' */

	/* Get the color of a pixel */
	__ATTR_IN_T(1) video_color_t
	(LIBVIDEO_GFX_CC *vgfx_getcolor)(struct video_gfx const *__restrict __self,
	                                 video_coord_t __abs_x, video_coord_t __abs_y);

	/* Place a colored pixel ontop of the graphic (whilst also performing blending) */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfx_putcolor)(struct video_gfx const *__restrict __self,
	                                 video_coord_t __abs_x, video_coord_t __abs_y,
	                                 video_color_t __color);

	/* Get the raw data of a pixel (no blending is done) */
	__ATTR_IN_T(1) video_pixel_t
	(LIBVIDEO_GFX_CC *vgfx_getpixel)(struct video_gfx const *__restrict __self,
	                                 video_coord_t __abs_x, video_coord_t __abs_y);

	/* Set the raw data of a pixel (no blending is done) */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfx_setpixel)(struct video_gfx const *__restrict __self,
	                                 video_coord_t __abs_x, video_coord_t __abs_y,
	                                 video_pixel_t __pixel);

	/* Diagonal line from top-left -> bottom-right
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfx_absline_llhh)(struct video_gfx const *__restrict __self,
	                                     video_coord_t __x, video_coord_t y,
	                                     video_dim_t __size_x, video_dim_t __size_y,
	                                     video_color_t __color);

	/* Diagonal line from bottom-left -> top-right
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfx_absline_lhhl)(struct video_gfx const *__restrict __self,
	                                     video_coord_t __x, video_coord_t __y,
	                                     video_dim_t __size_x, video_dim_t __size_y,
	                                     video_color_t __color);

	/* Horizontal line
	 * @assume(__length > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfx_absline_h)(struct video_gfx const *__restrict __self,
	                                  video_coord_t __x, video_coord_t __y,
		                              video_dim_t __length, video_color_t __color);

	/* Vertical line
	 * @assume(__length > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfx_absline_v)(struct video_gfx const *__restrict __self,
		                              video_coord_t __x, video_coord_t __y,
		                              video_dim_t __length, video_color_t __color);

	/* Rect fill
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfx_absfill)(struct video_gfx const *__restrict __self,
	                                video_coord_t __x, video_coord_t __y,
	                                video_dim_t __size_x, video_dim_t __size_y,
	                                video_color_t __color);

	/* Paint masked pixels
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) __ATTR_IN_T(7) void
	(LIBVIDEO_GFX_CC *vgfx_absfillmask)(struct video_gfx const *__restrict __self,
	                                    video_coord_t __dst_x, video_coord_t __dst_y,
	                                    video_dim_t __size_x, video_dim_t __size_y,
	                                    video_color_t __color,
	                                    struct video_bitmask const *__restrict __bm);

	/* Stretch and paint masked pixels
	 * @assume(__dst_size_x > 0);
	 * @assume(__dst_size_y > 0);
	 * @assume(__src_size_x > 0);
	 * @assume(__src_size_y > 0);
	 * @assume(__dst_size_x != __src_size_x);
	 * @assume(__dst_size_y != __src_size_y); */
	__ATTR_IN_T(1) __ATTR_IN_T(9) void
	(LIBVIDEO_GFX_CC *vgfx_absfillstretchmask)(struct video_gfx const *__restrict __self,
	                                           video_coord_t __dst_x, video_coord_t __dst_y,
	                                           video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                           video_color_t __color,
	                                           video_dim_t __src_size_x, video_dim_t __src_size_y,
	                                           struct video_bitmask const *__restrict __bm);

	/* Same as `vgfx_absfill', but do so via gradient with colors[y][x] being used
	 * to essentially do a  VIDEO_GFX_FLINEARBLIT stretch-blit into the  specified
	 * destination rect.
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) __ATTR_IN_T(6) void
	(LIBVIDEO_GFX_CC *vgfx_absgradient)(struct video_gfx const *__restrict __self,
	                                    video_coord_t __x, video_coord_t __y,
	                                    video_dim_t __size_x, video_dim_t __size_y,
	                                    video_color_t const __colors[2][2]);
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfx_absgradient_h)(struct video_gfx const *__restrict __self,
	                                      video_coord_t __x, video_coord_t __y,
	                                      video_dim_t __size_x, video_dim_t __size_y,
	                                      video_color_t __locolor, video_color_t __hicolor);
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfx_absgradient_v)(struct video_gfx const *__restrict __self,
	                                      video_coord_t __x, video_coord_t __y,
	                                      video_dim_t __size_x, video_dim_t __size_y,
	                                      video_color_t __locolor, video_color_t __hicolor);

	void (*_vbtx_pad[1])(void);
#endif /* LIBVIDEO_GFX_EXPOSE_INTERNALS */
};

struct video_gfx_ops {
	/* All of the following callbacks are [1..1] */

	/* Get the color of a pixel */
	__ATTR_IN_T(1) video_color_t
	(LIBVIDEO_GFX_CC *vgfo_getcolor)(struct video_gfx const *__restrict __self,
	                                 video_offset_t __x, video_offset_t __y);

	/* Place a colored pixel ontop of the graphic */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfo_putcolor)(struct video_gfx const *__restrict __self,
	                                 video_offset_t __x, video_offset_t __y,
	                                 video_color_t __color);

	/* Draw a line */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfo_line)(struct video_gfx const *__restrict __self,
	                             video_offset_t __x1, video_offset_t __y1,
	                             video_offset_t __x2, video_offset_t __y2,
	                             video_color_t __color);

	/* Horizontal line */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfo_hline)(struct video_gfx const *__restrict __self,
	                              video_offset_t __x, video_offset_t __y,
	                              video_dim_t __length, video_color_t __color);

	/* Vertical line */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfo_vline)(struct video_gfx const *__restrict __self,
	                              video_offset_t __x, video_offset_t __y,
	                              video_dim_t __length, video_color_t __color);

	/* Fill an area with a solid color. */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfo_fill)(struct video_gfx const *__restrict __self,
	                             video_offset_t __x, video_offset_t __y,
	                             video_dim_t __size_x, video_dim_t __size_y,
	                             video_color_t __color);

	/* Outline an area with a rectangle. */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfo_rect)(struct video_gfx const *__restrict __self,
	                             video_offset_t __x, video_offset_t __y,
	                             video_dim_t __size_x, video_dim_t __size_y,
	                             video_color_t __color);

	/* Same as `vgfo_fill()', but only fill in a pixel if masked by `__bm'
	 * This function is mainly here to facilitate the rendering of glyphs (s.a. fonts/tlft.h)
	 * TODO: This function should take 2 colors: foreground/background. Same also goes
	 *       for `vgfo_fillstretchmask' */
	__ATTR_IN_T(1) __ATTR_IN_T(7) void
	(LIBVIDEO_GFX_CC *vgfo_fillmask)(struct video_gfx const *__restrict __self,
	                                 video_offset_t __x, video_offset_t __y,
	                                 video_dim_t __size_x, video_dim_t __size_y,
	                                 video_color_t __color,
	                                 struct video_bitmask const *__restrict __bm);

	/* Same as `vgfo_fillmask()', however perform the blit while up-scaling the given bitmask. */
	__ATTR_IN_T(1) __ATTR_IN_T(9) void
	(LIBVIDEO_GFX_CC *vgfo_fillstretchmask)(struct video_gfx const *__restrict __self,
	                                        video_offset_t __dst_x, video_offset_t __dst_y,
	                                        video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                        video_color_t __color,
	                                        video_dim_t __src_size_x, video_dim_t __src_size_y,
	                                        struct video_bitmask const *__restrict __bm);

	/* Same as `vgfo_fill', but do so via gradient with colors[y][x] being  used
	 * to essentially do a VIDEO_GFX_FLINEARBLIT stretch-blit into the specified
	 * destination rect. */
	__ATTR_IN_T(1) __ATTR_IN_T(6) void
	(LIBVIDEO_GFX_CC *vgfo_gradient)(struct video_gfx const *__restrict __self,
	                                 video_offset_t __x, video_offset_t __y,
	                                 video_dim_t __size_x, video_dim_t __size_y,
	                                 video_color_t const __colors[2][2]);
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfo_hgradient)(struct video_gfx const *__restrict __self,
			                          video_offset_t __x, video_offset_t __y,
			                          video_dim_t __size_x, video_dim_t __size_y,
			                          video_color_t __locolor, video_color_t __hicolor);
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfo_vgradient)(struct video_gfx const *__restrict __self,
			                          video_offset_t __x, video_offset_t __y,
			                          video_dim_t __size_x, video_dim_t __size_y,
			                          video_color_t __locolor, video_color_t __hicolor);

	/* More driver-specific operators go here... */
};



typedef struct video_gfxhdr video_gfx_clipinfo_t;

/* Apply a clipping  rect to "self",  shrinking the  pixel
 * area relative to offsets specified by the given coords.
 *
 * Note that the clip area can  only ever be shrunk. To  go
 * back to the initial clip area, either keep a copy of the
 * original GFX  context, or  create a  new context  (which
 * always starts  out with  its clipping  area set  to  the
 * associated buffer's entire surface) */
typedef __ATTR_INOUT_T(1) struct video_gfxhdr *
(LIBVIDEO_GFX_CC *PVIDEO_GFXHDR_CLIP)(struct video_gfxhdr *__restrict __self,
                                      video_offset_t __clip_x, video_offset_t __clip_y,
                                      video_dim_t __size_x, video_dim_t __size_y);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_INOUT(1) struct video_gfxhdr *LIBVIDEO_GFX_CC
video_gfxhdr_clip(struct video_gfxhdr *__restrict __self,
                  video_offset_t __clip_x, video_offset_t __clip_y,
                  video_dim_t __size_x, video_dim_t __size_y);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Possible values for `video_gfx_palettize()'s `__method' argument.
 * - "n": # of pixels in clip region
 * - "k": The given `__palsize' */
#define VIDEO_GFX_PALETTIZE_METHOD_AUTO       0x0000 /* Automatically determine palettization method */
#define VIDEO_GFX_PALETTIZE_METHOD_HISTOGRAM  0x0001 /* Fastest (O(n + k)), but very bad results when `self' uses many different colors */
#define VIDEO_GFX_PALETTIZE_METHOD_MEDIAN_CUT 0x0002 /* Medium-speed (O(n log n)), but good enough decent results for most cases; Only usable for 2^N palette sizes */
#define VIDEO_GFX_PALETTIZE_METHOD_K_MEANS    0x0a03 /* Slowest (O(n * k * max_iters=10)), but best results; Never used automatically */
#define VIDEO_GFX_PALETTIZE_METHOD_F_ALPHA    0x0080 /* Flag: Include  alpha  values in  the  produced palette.
                                                      * Not supported by `VIDEO_GFX_PALETTIZE_METHOD_HISTOGRAM' */


/* Construct a (visually pleasing) palette from the pixel area  denoted
 * by the I/O region of `__self'. The produced palette is stored in the
 * provided buffer `__pal' and consists of exactly `__palsize' colors.
 * @param: __method: How to calculate the palette
 * @return: 0 : Success
 * @return: -1: [errno=ENOMEM] Insufficient memory for temporaries needed during calculation
 * @return: -1: [errno=EINVAL] Attempted to use "VIDEO_GFX_PALETTIZE_METHOD_F_ALPHA" with
 *                             a  palettization method that doesn't support alpha values.
 * @return: -1: [errno=EINVAL] Invalid `method' and/or `palsize' */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_OUTS_T(3, 2) int
(LIBVIDEO_GFX_CC *PVIDEO_GFX_PALETTIZE)(struct video_gfx const *__restrict __self,
                                        video_pixel_t __palsize, video_color_t *__pal,
                                        unsigned int __method);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUTS(3, 2) int LIBVIDEO_GFX_CC
video_gfx_palettize(struct video_gfx const *__restrict __self,
                    video_pixel_t __palsize, video_color_t *__pal,
                    unsigned int __method);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */



#ifdef __INTELLISENSE__

/************************************************************************/
/* VIDEO_BLIT                                                           */
/************************************************************************/

/* Blit the contents of another video buffer into this one. */
extern __ATTR_IN(1) void
video_blitter_bitblit(struct video_blitter const *__restrict __self,
                video_offset_t __dst_x, video_offset_t __dst_y,
                video_offset_t __src_x, video_offset_t __src_y,
                video_dim_t __size_x, video_dim_t __size_y);

/* Same as `vbto_bitblit', but stretch the contents */
extern __ATTR_IN(1) void
video_blitter_stretch(struct video_blitter const *__restrict __self,
                   video_offset_t __dst_x, video_offset_t __dst_y,
                   video_dim_t __dst_size_x, video_dim_t __dst_size_y,
                   video_offset_t __src_x, video_offset_t __src_y,
                   video_dim_t __src_size_x, video_dim_t __src_size_y);




/************************************************************************/
/* VIDEO_GFX                                                            */
/************************************************************************/

/* Return the API-visible clip rect offset in X or Y */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t
video_gfx_getclipx(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t
video_gfx_getclipy(struct video_gfx const *__restrict __self);

/* Return the API-visible clip rect size in X or Y */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t
video_gfx_getclipw(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t
video_gfx_getcliph(struct video_gfx const *__restrict __self);

#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
/* Apply a clipping  rect to "self",  shrinking the  pixel
 * area relative to offsets specified by the given coords.
 *
 * Note that the clip area can  only ever be shrunk. To  go
 * back to the initial clip area, either keep a copy of the
 * original GFX  context, or  create a  new context  (which
 * always starts  out with  its clipping  area set  to  the
 * associated buffer's entire surface) */
extern __ATTR_INOUT(1) struct video_gfx *
video_gfx_clip(struct video_gfx *__restrict __self,
               video_offset_t __clip_x, video_offset_t __clip_y,
               video_dim_t __size_x, video_dim_t __size_y);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

/* Backup/restore the current clip rect of `self' */
extern __ATTR_IN(1) __ATTR_OUT(2) void
video_gfx_saveclip(struct video_gfx const *__restrict self,
                   video_gfx_clipinfo_t *__restrict backup);
extern __ATTR_IN(2) __ATTR_OUT(1) void
video_gfx_loadclip(struct video_gfx *__restrict self,
                   video_gfx_clipinfo_t const *__restrict backup);


/* Update operators of `__self' after certain behavioral flags were changed:
 * - VIDEO_GFX_UPDATE_BLEND:    `__self->vx_blend' may have changed
 * - VIDEO_GFX_UPDATE_FLAGS:    `__self->vx_flags' may have changed
 * - VIDEO_GFX_UPDATE_COLORKEY: `__self->vx_colorkey' may have changed
 * @param: __what: Set of `VIDEO_GFX_UPDATE_*'
 *
 * CAUTION: Do not use this operator when `__self' may be used by other threads! */
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *
video_gfx_update(struct video_gfx *__restrict __self, unsigned int __what);

/* Set GFX modes for `__self'. If you want to set multiple of these at once,
 * you should directly assign the respective  members, and then make a  call
 * to `video_gfx_update()' specifying exactly what changed. */
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *
video_gfx_setblend(struct video_gfx *__restrict __self, gfx_blendmode_t __mode);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *
video_gfx_setflags(struct video_gfx *__restrict __self, __uintptr_t __flags);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *
video_gfx_setcolorkey(struct video_gfx *__restrict __self, video_color_t __colorkey);

/* Disable  blending  for  `__self'.  Same   as:
 * >> __self->vx_blend = GFX_BLENDMODE_OVERRIDE;
 * >> __self->vx_flags &= ~VIDEO_GFX_FBLUR;
 * >> __self->vx_colorkey = 0;
 * >> video_gfx_update(__self, VIDEO_GFX_UPDATE_ALL);
 *
 * CAUTION: Do not use this operator when `__self' may be used by other threads! */
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *
video_gfx_noblend(struct video_gfx *__restrict __self);

/* Get/put(blend) the color of a singular pixel */
extern __ATTR_WUNUSED __ATTR_IN(1) video_color_t
video_gfx_getcolor(struct video_gfx const *__self,
                   video_offset_t __x, video_offset_t __y);
extern __ATTR_IN(1) void
video_gfx_putcolor(struct video_gfx const *__self,
                   video_offset_t __x, video_offset_t __y,
                   video_color_t __color);


/* Draw a line */
extern __ATTR_IN(1) void
video_gfx_line(struct video_gfx const *__restrict __self,
               video_offset_t __x1, video_offset_t __y1,
               video_offset_t __x2, video_offset_t __y2,
               video_color_t __color);

/* Horizontal line */
extern __ATTR_IN(1) void
video_gfx_hline(struct video_gfx const *__restrict __self,
                video_offset_t __x, video_offset_t __y,
                video_dim_t __length, video_color_t __color);

/* Vertical line */
extern __ATTR_IN(1) void
video_gfx_vline(struct video_gfx const *__restrict __self,
                video_offset_t __x, video_offset_t __y,
                video_dim_t __length, video_color_t __color);

/* Fill an area with a solid color. */
extern __ATTR_IN(1) void
video_gfx_fill(struct video_gfx const *__restrict __self,
               video_offset_t __x, video_offset_t __y,
               video_dim_t __size_x, video_dim_t __size_y,
               video_color_t __color);

/* Fill the entire clip-area with a solid color. */
extern __ATTR_IN(1) void
video_gfx_fillall(struct video_gfx const *__restrict __self,
                  video_color_t __color);


/* Outline an area with a rectangle. */
extern __ATTR_IN(1) void
video_gfx_rect(struct video_gfx const *__restrict __self,
               video_offset_t __x, video_offset_t __y,
               video_dim_t __size_x, video_dim_t __size_y,
               video_color_t __color);

/* Same as `vgfo_fill()', but only fill in a pixel if masked by `__bm'
 * This function is mainly here to facilitate the rendering of glyphs (s.a. fonts/tlft.h) */
extern __ATTR_IN(1) __ATTR_IN(7) void
video_gfx_absfillmask(struct video_gfx const *__restrict __self,
                   video_offset_t __x, video_offset_t __y,
                   video_dim_t __size_x, video_dim_t __size_y,
                   video_color_t __color,
                   struct video_bitmask const *__restrict __bm);

/* Same as `vgfo_fillmask()', however perform the blit while up-scaling the given bitmask. */
extern __ATTR_IN(1) __ATTR_IN(9) void
video_gfx_absfillstretchmask(struct video_gfx const *__restrict __self,
                          video_offset_t __dst_x, video_offset_t __dst_y,
                          video_dim_t __dst_size_x, video_dim_t __dst_size_y,
                          video_color_t __color,
                          video_dim_t __src_size_x, video_dim_t __src_size_y,
                          struct video_bitmask const *__restrict __bm);

/* Same as `video_gfx_fill', but do so via gradient with colors[y][x] being
 * used to  essentially do  a VIDEO_GFX_FLINEARBLIT  stretch-blit into  the
 * specified destination rect. */
extern __ATTR_IN(1) __ATTR_IN(6) void
video_gfx_gradient(struct video_gfx const *__restrict __self,
                   video_offset_t __x, video_offset_t __y,
                   video_dim_t __size_x, video_dim_t __size_y,
                   video_color_t const __colors[2][2]);
extern __ATTR_IN(1) void
video_gfx_hgradient(struct video_gfx const *__restrict __self,
                    video_offset_t __x, video_offset_t __y,
                    video_dim_t __size_x, video_dim_t __size_y,
                    video_color_t __locolor, video_color_t __hicolor);
extern __ATTR_IN(1) void
video_gfx_vgradient(struct video_gfx const *__restrict __self,
                    video_offset_t __x, video_offset_t __y,
                    video_dim_t __size_x, video_dim_t __size_y,
                    video_color_t __locolor, video_color_t __hicolor);

/* Initialize bitting contexts to rendering between 2 given GFX contexts. */
extern __ATTR_RETNONNULL __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) struct video_blitter *
video_gfx_blitfrom(struct video_gfx const *__dst,
                   struct video_gfx const *__src,
                   struct video_blitter *__ctx);
extern __ATTR_RETNONNULL __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) struct video_blitter *
video_gfx_blitto(struct video_gfx const *__src,
                 struct video_gfx const *__dst,
                 struct video_blitter *__ctx);

/* Directly do blitting between 2 GFX contexts (helpers to wrap "struct video_blitter") */
extern __ATTR_IN(1) __ATTR_IN(4) void
video_gfx_bitblit(struct video_gfx const *__dst, video_offset_t __dst_x, video_offset_t __dst_y,
                  struct video_gfx const *__src, video_offset_t __src_x, video_offset_t __src_y,
                  video_dim_t __size_x, video_dim_t __size_y);
extern __ATTR_IN(1) __ATTR_IN(6) void
video_gfx_stretch(struct video_gfx const *__dst, video_offset_t __dst_x, video_offset_t __dst_y, video_dim_t __dst_size_x, video_dim_t __dst_size_y,
                  struct video_gfx const *__src, video_offset_t __src_x, video_offset_t __src_y, video_dim_t __src_size_x, video_dim_t __src_size_y);
#else /* __INTELLISENSE__ */
#define video_blitter_bitblit(self, dst_x, dst_y, src_x, src_y, size_x, size_y) \
	(*(self)->vbt_ops->vbto_bitblit)(self, dst_x, dst_y, src_x, src_y, size_x, size_y)
#define video_blitter_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y) \
	(*(self)->vbt_ops->vbto_stretch)(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y)

#define video_gfx_getclipx(self) (self)->vx_hdr.vxh_cxoff
#define video_gfx_getclipy(self) (self)->vx_hdr.vxh_cyoff
#define video_gfx_getclipw(self) (self)->vx_hdr.vxh_cxsiz
#define video_gfx_getcliph(self) (self)->vx_hdr.vxh_cysiz
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
#define video_gfx_clip(self, start_x, start_y, size_x, size_y) \
	((struct video_gfx *)video_gfxhdr_clip(&(self)->vx_hdr, start_x, start_y, size_x, size_y))
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */
#define video_gfx_saveclip(self, backup) (void)__libc_memcpy(backup, &(self)->vx_hdr, sizeof(video_gfx_clipinfo_t))
#define video_gfx_loadclip(self, backup) (void)__libc_memcpy(&(self)->vx_hdr, backup, sizeof(video_gfx_clipinfo_t))
#define video_gfx_update(self, what) \
	(*(self)->vx_buffer->vb_ops->vi_updategfx)(self, what)
#define video_gfx_setblend(self, mode) \
	((self)->vx_blend = (mode), video_gfx_update(self, VIDEO_GFX_UPDATE_BLEND))
#define video_gfx_setflags(self, flags) \
	((self)->vx_flags = (flags), video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS))
#define video_gfx_setcolorkey(self, colorkey) \
	((self)->vx_colorkey = (colorkey), video_gfx_update(self, VIDEO_GFX_UPDATE_COLORKEY))
#define video_gfx_noblend(self) \
	(*(self)->vx_buffer->vb_ops->vi_noblendgfx)(self)
#define video_gfx_getcolor(self, x, y) \
	(*(self)->vx_hdr.vxh_ops->vgfo_getcolor)(self, x, y)
#define video_gfx_putcolor(self, x, y, color) \
	(*(self)->vx_hdr.vxh_ops->vgfo_putcolor)(self, x, y, color)
#define video_gfx_line(self, x1, y1, x2, y2, color) \
	(*(self)->vx_hdr.vxh_ops->vgfo_line)(self, x1, y1, x2, y2, color)
#define video_gfx_hline(self, x, y, length, color) \
	(*(self)->vx_hdr.vxh_ops->vgfo_hline)(self, x, y, length, color)
#define video_gfx_vline(self, x, y, length, color) \
	(*(self)->vx_hdr.vxh_ops->vgfo_vline)(self, x, y, length, color)
#define video_gfx_fill(self, x, y, size_x, size_y, color) \
	(*(self)->vx_hdr.vxh_ops->vgfo_fill)(self, x, y, size_x, size_y, color)
#define video_gfx_fillall(self, color) \
	video_gfx_fill(self, 0, 0, VIDEO_DIM_MAX, VIDEO_DIM_MAX, color)
#define video_gfx_rect(self, x, y, size_x, size_y, color) \
	(*(self)->vx_hdr.vxh_ops->vgfo_rect)(self, x, y, size_x, size_y, color)
#define video_gfx_absfillmask(self, x, y, size_x, size_y, color, bigtmask) \
	(*(self)->vx_hdr.vxh_ops->vgfo_fillmask)(self, x, y, size_x, size_y, color, bigtmask)
#define video_gfx_absfillstretchmask(self, dst_x, dst_y, dst_sizex, dst_sizey, color, src_size_x, src_size_y, bigtmask) \
	(*(self)->vx_hdr.vxh_ops->vgfo_fillstretchmask)(self, dst_x, dst_y, dst_sizex, dst_sizey, color, src_size_x, src_size_y, bigtmask)
#define video_gfx_gradient(self, x, y, size_x, size_y, colors) \
	(*(self)->vx_hdr.vxh_ops->vgfo_gradient)(self, x, y, size_x, size_y, colors)
#define video_gfx_hgradient(self, x, y, size_x, size_y, locolor, hicolor) \
	(*(self)->vx_hdr.vxh_ops->vgfo_hgradient)(self, x, y, size_x, size_y, locolor, hicolor)
#define video_gfx_vgradient(self, x, y, size_x, size_y, locolor, hicolor) \
	(*(self)->vx_hdr.vxh_ops->vgfo_vgradient)(self, x, y, size_x, size_y, locolor, hicolor)
#define video_gfx_blitfrom(dst, src, ctx) \
	((ctx)->vbt_src = (src), (*((ctx)->vbt_dst = (dst))->vx_hdr.vxh_blitfrom)(ctx))
#define video_gfx_blitto(src, dst, ctx) \
	((ctx)->vbt_src = (src), (*((ctx)->vbt_dst = (dst))->vx_hdr.vxh_blitfrom)(ctx))
#define video_gfx_bitblit(dst, dst_x, dst_y, src, src_x, src_y, size_x, size_y) \
	__XBLOCK({ struct video_blitter _vgb_blit, *_vgb_blit_ptr = video_gfx_blitfrom(dst, src, &_vgb_blit); video_blitter_bitblit(_vgb_blit_ptr, dst_x, dst_y, src_x, src_y, size_x, size_y); })
#define video_gfx_stretch(dst, dst_x, dst_y, dst_size_x, dst_size_y, src, src_x, src_y, src_size_x, src_size_y) \
	__XBLOCK({ struct video_blitter _vgs_blit, *_vgs_blit_ptr = video_gfx_blitfrom(dst, src, &_vgs_blit); video_blitter_stretch(_vgs_blit_ptr, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y); })
#endif /* !__INTELLISENSE__ */



#ifdef __cplusplus
__CXXDECL_BEGIN
#endif /* __cplusplus */

struct video_blitter {
	struct video_blitter_ops const *vbt_ops;  /* Blitter operators */
	struct video_gfx const         *vbt_dst;  /* [1..1][const] Destination GFX context */
	struct video_gfx const         *vbt_src;  /* [1..1][const] Source GFX context */
	struct video_blitter_xops      _vbt_xops; /* Internal blit operators */
#define _VIDEO_BLIT_N_DRIVER 6
	void *_vbt_driver[_VIDEO_BLIT_N_DRIVER]; /* [?..?] Driver-specific graphics data. */

#ifdef __cplusplus
public:
	/* Blit the contents of another video buffer into this one. */
	__CXX_CLASSMEMBER void blit(video_offset_t __dst_x, video_offset_t __dst_y,
	                            video_offset_t __src_x, video_offset_t __src_y,
	                            video_dim_t __size_x, video_dim_t __size_y) const {
		video_blitter_bitblit(this, __dst_x, __dst_y, __src_x, __src_y, __size_x, __size_y);
	}

	/* Same as `blit', but stretch the contents */
	__CXX_CLASSMEMBER void stretch(video_offset_t __dst_x, video_offset_t __dst_y,
	                               video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                               video_offset_t __src_x, video_offset_t __src_y,
	                               video_dim_t __src_size_x, video_dim_t __src_size_y) const {
		video_blitter_stretch(this, __dst_x, __dst_y, __dst_size_y, __dst_size_y,
		                      __src_x, __src_y, __src_size_y, __src_size_y);
	}
#endif /* __cplusplus */
};

struct video_gfxhdr {
	struct video_gfx_ops const *vxh_ops; /* [1..1][const] GFX operations (use these) */

	/* [1..1][const]
	 * Initialize a blitting context that reads from `__ctx->vbt_src' and writes to  `__ctx->vbt_dst'.
	 * The caller must have already initialized `__ctx->vbt_src' and `__ctx->vbt_dst', and the invoked
	 * operator here must be the one of `__ctx->vbt_dst'
	 * @return: * : Always re-returns `__ctx' */
	__ATTR_RETNONNULL __ATTR_INOUT_T(1) struct video_blitter *
	(LIBVIDEO_GFX_FCC *vxh_blitfrom)(struct video_blitter *__restrict __ctx);

	/* Clip rect area (pixel area used for pixel clamping/wrapping, and accepted):
	 * >> +---------------------------------+
	 * >> | Buffer                          |
	 * >> |                                 |
	 * >> |   +-----------------------+.......................+
	 * >> |   | Clip Rect             | Clip Rect             .
	 * >> |   |                       | (VIDEO_GFX_FRDXWRAP)  .
	 * >> |   |                       | (VIDEO_GFX_FWRXWRAP)  .
	 * >> |   |  +-----------------+  |                       .
	 * >> |   |  | I/O Area        |  |                       .
	 * >> |   |  |                 |  |                       .
	 * >> |   |  +-----------------+  |                       .
	 * >> |   |                       |                       .
	 * >> |   +-----------------------+.......................+
	 * >> |                                 |
	 * >> +---------------------------------+
	 *
	 * Coords of these rects are (in absolute "video_coord_t" coords):
	 * - Buffer:    {xy: {0,0}, wh: {vxh_buffer->vb_xdim,vxh_buffer->vb_ydim}}
	 * - Clip Rect: {xy: {vxh_cxoff,vxh_cyoff}, wh: {vxh_cxsiz,vxh_cysiz}}
	 * - I/O Area:  {xy: {vxh_bxmin,vxh_bymin}, wh: {vxh_bxsiz,vxh_bysiz}}
	 *
	 * When using any of the  publicly exposed functions, you always  operate
	 * in the coord-space defined by the "Clip Rect", with pixel reads/writes
	 * restricted to those within the "I/O Area". Pixel coords that go beyond
	 * the "Clip Rect", are either clamped, or wrapped (based on the size  of
	 * the "Clip Rect"), before then being  clamped again to the  "I/O Area".
	 * You might notice that when pixel wrapping is disabled, the first clamp
	 * can (and is) skipped.
	 *
	 * When changing the clip rect, coords are still relative to the old  clip
	 * rect, but negative  coords can  be given to  make the  clip rect  grow.
	 * However, the "I/O Area"  is always the  intersection of "Buffer",  with
	 * any "Clip Rect" ever  set for  the GFX  context, meaning  it cannot  be
	 * made to grow without obtaining a fresh GFX context (which always starts
	 * out with all 3 areas set to match each other). */
	video_offset_t              vxh_cxoff;    /* [const] Delta added to all X coords (as per clip-rect) to turn "video_offset_t" into "video_coord_t" */
	video_offset_t              vxh_cyoff;    /* [const] Delta added to all Y coords (as per clip-rect) to turn "video_offset_t" into "video_coord_t" */
	video_dim_t                 vxh_cxsiz;    /* [const] Absolute width of the clip-rect (only relevant for `VIDEO_GFX_F*RAP') */
	video_dim_t                 vxh_cysiz;    /* [const] Absolute height of the clip-rect (only relevant for `VIDEO_GFX_F*RAP') */
	/* Buffer I/O area: these values control the (absolute) pixel area where read/writes do something */
	video_coord_t               vxh_bxmin;    /* [const][<= vxh_bxend][>= vxh_cxoff] Absolute buffer start coord in X (start of acc) */
	video_coord_t               vxh_bymin;    /* [const][<= vxh_byend][>= vxh_cyoff] Absolute buffer start coord in Y */
	video_coord_t               vxh_bxend;    /* [const][<= vxh_buffer->vb_xdim] Absolute buffer end coord in X (<= `vxh_buffer->vb_xdim') */
	video_coord_t               vxh_byend;    /* [const][<= vxh_buffer->vb_ydim] Absolute buffer end coord in Y (<= `vxh_buffer->vb_ydim') */
//	video_dim_t                 vxh_bxsiz;    /* [const][== vxh_bxend - vxh_bxmin][<= vxh_cxsiz] Absolute buffer I/O width */
//	video_dim_t                 vxh_bysiz;    /* [const][== vxh_byend - vxh_bymin][<= vxh_cysiz] Absolute buffer I/O height */
};

struct video_gfx {
	struct video_gfxhdr         vx_hdr;      /* GFX header (this part of the struct can be saved/restored in order to restore old clip rects) */
	struct video_buffer        *vx_buffer;   /* [1..1][const] The associated buffer. */
	gfx_blendmode_t             vx_blend;    /* [const] Blending mode. */
	__uintptr_t                 vx_flags;    /* [const] Additional rendering flags (Set of `VIDEO_GFX_F*'). */
	video_color_t               vx_colorkey; /* [const] Transparent color key (or any color with alpha=0 when disabled). */
//	video_dim_t                 vx_bysiz;    /* [const][== vx_hdr.vxh_byend - vx_hdr.vxh_bymin][<= vx_hdr.vxh_cysiz] Absolute buffer I/O height */
	struct video_gfx_xops      _vx_xops;     /* [1..1][const] Internal GFX operators (do not use directly) */
#define _VIDEO_GFX_N_DRIVER 4
	void *_vx_driver[_VIDEO_GFX_N_DRIVER];    /* [?..?] Driver-specific graphics data. */

#ifdef __cplusplus
public:

	/* Apply a clipping  rect to "self",  shrinking the  pixel
	 * area relative to offsets specified by the given coords.
	 *
	 * Note that the clip area can  only ever be shrunk. To  go
	 * back to the initial clip area, either keep a copy of the
	 * original GFX  context, or  create a  new context  (which
	 * always starts  out with  its clipping  area set  to  the
	 * associated buffer's entire surface) */
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
	__CXX_CLASSMEMBER struct video_gfx &
	clip(video_offset_t __start_x, video_offset_t __start_y,
	                     video_dim_t __size_x, video_dim_t __size_y) {
		return *video_gfx_clip(this, __start_x, __start_y, __size_x, __size_y);
	}
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

	/* Get a pixel */
	__CXX_CLASSMEMBER video_color_t getcolor(video_offset_t __x, video_offset_t __y) const {
		return video_gfx_getcolor(this, __x, __y);
	}

	/* Place a colored pixel ontop of the graphic */
	__CXX_CLASSMEMBER void putcolor(video_offset_t __x, video_offset_t __y, video_color_t __color) const {
		video_gfx_putcolor(this, __x, __y, __color);
	}

	/* Draw a line */
	__CXX_CLASSMEMBER void line(video_offset_t __x1, video_offset_t __y1,
	                            video_offset_t __x2, video_offset_t __y2,
	                            video_color_t __color) const {
		video_gfx_line(this, __x1, __y1, __x2, __y2, __color);
	}

	/* Horizontal line */
	__CXX_CLASSMEMBER void hline(video_offset_t __x, video_offset_t __y,
	                             video_dim_t __length, video_color_t __color) const {
		video_gfx_hline(this, __x, __y, __length, __color);
	}

	/* Vertical line */
	__CXX_CLASSMEMBER void vline(video_offset_t __x, video_offset_t __y,
	                             video_dim_t __length, video_color_t __color) const {
		video_gfx_vline(this, __x, __y, __length, __color);
	}

	/* Fill an area with a solid color. */
	__CXX_CLASSMEMBER void fill(video_offset_t __x, video_offset_t __y,
	                            video_dim_t __size_x, video_dim_t __size_y,
	                            video_color_t __color) const {
		video_gfx_fill(this, __x, __y, __size_x, __size_y, __color);
	}

	/* Fill the entire clip-area with a solid color. */
	__CXX_CLASSMEMBER void fill(video_color_t __color) const {
		video_gfx_fillall(this, __color);
	}

	/* Same as `fill', but do  so via gradient with colors[y][x]  being
	 * used to essentially do a VIDEO_GFX_FLINEARBLIT stretch-blit into
	 * the specified destination rect. */
	__CXX_CLASSMEMBER void gradient(video_offset_t __x, video_offset_t __y,
	                                video_dim_t __size_x, video_dim_t __size_y,
	                                video_color_t const __colors[2][2]) const {
		video_gfx_gradient(this, __x, __y, __size_x, __size_y, __colors);
	}
	__CXX_CLASSMEMBER void hgradient(video_offset_t __x, video_offset_t __y,
	                                 video_dim_t __size_x, video_dim_t __size_y,
	                                 video_color_t __locolor, video_color_t __hicolor) const {
		video_gfx_hgradient(this, __x, __y, __size_x, __size_y, __locolor, __hicolor);
	}
	__CXX_CLASSMEMBER void vgradient(video_offset_t __x, video_offset_t __y,
	                                 video_dim_t __size_x, video_dim_t __size_y,
	                                 video_color_t __locolor, video_color_t __hicolor) const {
		video_gfx_vgradient(this, __x, __y, __size_x, __size_y, __locolor, __hicolor);
	}

	/* Outline an area with a rectangle. */
	__CXX_CLASSMEMBER void rect(video_offset_t __x, video_offset_t __y,
	                            video_dim_t __size_x, video_dim_t __size_y,
	                            video_color_t __color) const {
		video_gfx_rect(this, __x, __y, __size_x, __size_y, __color);
	}

	/* Fill an area with a solid color. */
	__CXX_CLASSMEMBER void fillmask(video_offset_t __x, video_offset_t __y,
	                               video_dim_t __size_x, video_dim_t __size_y,
	                               video_color_t __color,
	                               struct video_bitmask const *__restrict __bm) const {
		video_gfx_absfillmask(this, __x, __y, __size_x, __size_y, __color, __bm);
	}

	/* Same as `vgfo_fillmask()', however perform the blit while up-scaling the given bitmask. */
	__CXX_CLASSMEMBER void fillstretchmask(video_offset_t __dst_x, video_offset_t __dst_y,
	                                       video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                       video_color_t __color,
	                                       video_dim_t __src_size_x, video_dim_t __src_size_y,
	                                       struct video_bitmask const *__restrict __bm) const {
		video_gfx_absfillstretchmask(this, __dst_x, __dst_y, __dst_size_x, __dst_size_y,
		                          __color, __src_size_x, __src_size_y, __bm);
	}


	/************************************************************************/
	/* GFX->GFX blitting via context                                        */
	/************************************************************************/
	__CXX_CLASSMEMBER struct video_blitter &blitfrom(struct video_gfx const &__src,
	                                                 struct video_blitter &__ctx) const {
		video_gfx_blitfrom(this, &__src, &__ctx);
		return __ctx;
	}

	__CXX_CLASSMEMBER struct video_blitter blitfrom(struct video_gfx const &__src) const {
		struct video_blitter __result;
		video_gfx_blitfrom(this, &__src, &__result);
		return __result;
	}

	__CXX_CLASSMEMBER struct video_blitter &blitto(struct video_gfx const &__dst,
	                                            struct video_blitter &__ctx) const {
		video_gfx_blitto(this, &__dst, &__ctx);
		return __ctx;
	}

	__CXX_CLASSMEMBER struct video_blitter blitto(struct video_gfx const &__dst) const {
		struct video_blitter __result;
		video_gfx_blitto(this, &__dst, &__result);
		return __result;
	}


	/************************************************************************/
	/* Convenience aliases for blitting functions                           */
	/************************************************************************/

	/* Blit the contents of another video buffer into this one. */
	__CXX_CLASSMEMBER void bitblit(video_offset_t __dst_x, video_offset_t __dst_y,
	                               struct video_gfx const &__src,
	                               video_offset_t __src_x, video_offset_t __src_y,
	                               video_dim_t __size_x, video_dim_t __size_y) const {
		video_gfx_bitblit(this, __dst_x, __dst_y, &__src, __src_x, __src_y, __size_x, __size_y);
	}

	/* Stretch the contents of another video buffer into this one. */
	__CXX_CLASSMEMBER void stretch(video_offset_t __dst_x, video_offset_t __dst_y,
	                               video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                               struct video_gfx const &__src,
	                               video_offset_t __src_x, video_offset_t __src_y,
	                               video_dim_t __src_size_x, video_dim_t __src_size_y) const {
		video_gfx_stretch(this, __dst_x, __dst_y, __dst_size_y, __dst_size_y,
		                  &__src, __src_x, __src_y, __src_size_y, __src_size_y);
	}
#endif /* __cplusplus */
};

#ifdef __cplusplus
__CXXDECL_END
#endif /* __cplusplus */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_GFX_H */
