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
/**/

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libvideo/codec/format.h>

#include "../color.h"
#include "../types.h"
#include "blend.h" /* gfx_blendmode_t */

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

#ifndef __INTELLISENSE__
#include "../rect.h"
#include <libc/string.h>
#endif /* !__INTELLISENSE__ */

/* Video graphic flags.
 * [r]: Indicates a flag that affects the results when the associated
 *      GFX  context is used  as source, or  when reading pixel data.
 * [w]: Indicates a flag that affects the results of graphics operations
 *      that use  the associated  GFX context  as destination,  or  when
 *      writing pixel data. */
#define VIDEO_GFX_F_NORMAL  0x0000 /* Normal render flags. */
#define VIDEO_GFX_F_XWRAP   0x0001 /* [rw] OOB X coords wrap to the other side of the Clip Rect (else: coords are clamped) */
#define VIDEO_GFX_F_YWRAP   0x0002 /* [rw] OOB Y coords wrap to the other side of the Clip Rect (else: coords are clamped) */
#define VIDEO_GFX_F_XMIRROR 0x0004 /* [rw] X coords are horizontally mirrored relative to the Clip Rect */
#define VIDEO_GFX_F_YMIRROR 0x0008 /* [rw] Y coords are vertically mirrored relative to the Clip Rect */
#define VIDEO_GFX_F_XYSWAP  0x0010 /* [rw] Swap X/Y coords (width becoming height, and height becoming width)
                                    * WARNING: Do not alter this flag directly; use `video_gfx_xyswap()'
                                    * NOTE: Happens **after** VIDEO_GFX_F_XMIRROR/VIDEO_GFX_F_YMIRROR! */
#define VIDEO_GFX_F_NEAREST 0x0000 /* [rw] Use nearest interpolation for stretch() (flag used from src-gfx), lines, and floating-point pixel accesses */
#define VIDEO_GFX_F_LINEAR  0x8000 /* [rw] Use linear interpolation for stretch() (flag used from src-gfx), lines, and floating-point pixel accesses */




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


/* Set of `VIDEO_GFX_F*' */
typedef __UINT32_TYPE__ video_gfx_flag_t;


#define _VIDEO_GFX_FLAGS_X_TO_Y_LSHIFT 1
#define _VIDEO_GFX_FLAGS_Y_TO_X_RSHIFT _VIDEO_GFX_FLAGS_X_TO_Y_LSHIFT

#define _VIDEO_GFX_XFLAGS    (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_XMIRROR)
#define _VIDEO_GFX_YFLAGS    (VIDEO_GFX_F_YWRAP | VIDEO_GFX_F_YMIRROR)
#define _VIDEO_GFX_AND_FLAGS (0)
#define _VIDEO_GFX_OR_FLAGS  (VIDEO_GFX_F_LINEAR)
#define _VIDEO_GFX_XOR_FLAGS (~(_VIDEO_GFX_AND_FLAGS | _VIDEO_GFX_OR_FLAGS))

/* Combine pre-existing GFX flags `__old_flags' with `__more_flags' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED video_gfx_flag_t
video_gfx_flag_combine(video_gfx_flag_t __old_flags, video_gfx_flag_t __more_flags) {
	if (__old_flags & VIDEO_GFX_F_XYSWAP) {
		__more_flags = (__more_flags & ~(_VIDEO_GFX_XFLAGS | _VIDEO_GFX_YFLAGS)) |
		               ((__more_flags & _VIDEO_GFX_XFLAGS) << _VIDEO_GFX_FLAGS_X_TO_Y_LSHIFT) |
		               ((__more_flags & _VIDEO_GFX_YFLAGS) >> _VIDEO_GFX_FLAGS_Y_TO_X_RSHIFT);
	}
	return 0 |
#if _VIDEO_GFX_XOR_FLAGS != 0
	       ((__old_flags ^ __more_flags) & _VIDEO_GFX_XOR_FLAGS) |
#endif /* _VIDEO_GFX_XOR_FLAGS != 0 */
#if _VIDEO_GFX_OR_FLAGS != 0
	       ((__old_flags | __more_flags) & _VIDEO_GFX_OR_FLAGS) |
#endif /* _VIDEO_GFX_OR_FLAGS != 0 */
#if _VIDEO_GFX_AND_FLAGS != 0
	       ((__old_flags & __more_flags) & _VIDEO_GFX_AND_FLAGS) |
#endif /* _VIDEO_GFX_AND_FLAGS != 0 */
	       0;
}

struct video_buffer;
struct video_gfxhdr;
struct video_gfx;
struct video_blitter;
struct video_blitter3;

/* Video bitmask descriptor.
 *
 * Bitmasks can be used to mask filling of pixels in fill/stretch
 * operations, such that the corresponding bit selects the source
 * color used for that pixel during the fill/stretch.
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

	/* TODO: Some way to rotate and flip pixels during blits (using precise angles,
	 *       rather than the mere 90° rotations possible via  `VIDEO_GFX_F_XYSWAP') */

	/* More driver-specific operators go here... */
};



struct video_blitter3_ops {
	/* Blit the contents of another video buffer into this one. */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vbt3o_bitblit)(struct video_blitter3 const *__restrict __self,
	                                 video_offset_t __wrdst_x, video_offset_t __wrdst_y,
	                                 video_offset_t __rddst_x, video_offset_t __rddst_y,
	                                 video_offset_t __src_x, video_offset_t __src_y,
	                                 video_dim_t __size_x, video_dim_t __size_y);

	/* Same as `vbt3o_bitblit', but stretch the contents */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vbt3o_stretch)(struct video_blitter3 const *__restrict __self,
	                                 video_offset_t __wrdst_x, video_offset_t __wrdst_y,
	                                 video_offset_t __rddst_x, video_offset_t __rddst_y,
	                                 video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                 video_offset_t __src_x, video_offset_t __src_y,
	                                 video_dim_t __src_size_x, video_dim_t __src_size_y);

	/* More driver-specific operators go here... */
};



struct video_gfx_ops {
	/* All of the following callbacks are [1..1] */

	/* Initialize a blitting context that reads from `__ctx->vbt_src' and writes to `__ctx->vbt_dst'.
	 * The caller must have already initialized:
	 * - __ctx->vbt_src
	 * - __ctx->vbt_dst
	 * This operator must be called for `__ctx->vbt_dst'
	 * @return: * : Always re-returns `__ctx' */
	__ATTR_RETNONNULL __ATTR_INOUT_T(1) struct video_blitter *
	(LIBVIDEO_GFX_FCC *vgfo_blitfrom)(struct video_blitter *__restrict __ctx);

	/* Same as "vgfo_blitfrom", but when it comes  to blending, pixels are read from  "vbt3_rddst"
	 * rather than read+inplace-modified within "vbt3_wrdst", allowing for pixel data from 2 video
	 * buffers to be  blended together, before  then being (optionally)  blended again when  being
	 * written to "vbt3_wrdst"
	 * >> foreach (x, y in INTERSECTION_OF_RECTS(dst, src, out)) {
	 * >>     video_color_t s = __ctx->vbt3_src->getcolor(src_x + x, src_y + y);
	 * >>     video_color_t d = __ctx->vbt3_rddst->getcolor(dst_x + x, dst_y + y);
	 * >>     video_color_t b = gfx_blendcolors(d, s, __ctx->vbt3_rddst->vx_blend); // Use blending mode of "vbt3_rddst" here
	 * >>     __ctx->vbt3_wrdst->putcolor(dst_x + x, dst_y + y, b);                 // Optional second blend using "vbt3_wrdst"
	 * >> }
	 *
	 * This operator must be called for `__ctx->vbt3_wrdst' */
	__ATTR_RETNONNULL __ATTR_INOUT_T(1) struct video_blitter3 *
	(LIBVIDEO_GFX_FCC *vgfo_blitfrom3)(struct video_blitter3 *__restrict __ctx);

	/* Apply a clipping  rect to "self",  shrinking the  pixel
	 * area relative to offsets specified by the given coords.
	 *
	 * Note that the clip area can  only ever be shrunk. To  go
	 * back to the initial clip area, either keep a copy of the
	 * original GFX  context, or  create a  new context  (which
	 * always starts  out with  its clipping  area set  to  the
	 * associated buffer's entire surface)
	 *
	 * @param: __clip_x: Delta to add to the Clip Rect starting X coord.
	 *                   When negative, extend clip rect with void-pixels to the left
	 * @param: __clip_y: Delta to add to the Clip Rect starting Y coord.
	 *                   When negative, extend clip rect with void-pixels to the top
	 * @param: __size_x: New width of the clip rect. When greater than the old  clip
	 *                   rect width, extend clip rect with void-pixels to the right.
	 * @param: __size_y: New height of the clip rect.  When greater than the old  clip
	 *                   rect height, extend clip rect with void-pixels to the bottom.
	 * @return: * : Always re-returns `__self' */
	__ATTR_RETNONNULL_T __ATTR_INOUT_T(1) struct video_gfx *
	(LIBVIDEO_GFX_CC *vgfo_clip)(struct video_gfx *__restrict __self,
	                             video_offset_t __clip_x, video_offset_t __clip_y,
	                             video_dim_t __size_x, video_dim_t __size_y);

	/* Translate virtual (offset) pixel coords to physical (coord) coords.
	 * @param: __x:      Virtual pixel X offset
	 * @param: __y:      Virtual pixel Y offset
	 * @param: __coords: The absolute (physical) coords of the pixel are stored here
	 * @return: true:  Translation was successful
	 * @return: false: The given __x/__y lie outside the I/O Rect of `__self' */
	__ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_OUT_T(4) __BOOL
	(LIBVIDEO_GFX_CC *vgfo_offset2coord)(struct video_gfx const *__restrict __self,
	                                     video_offset_t __x, video_offset_t __y,
	                                     video_coord_t __coords[2]);

	/* Translate physical (coord) pixel coords to virtual (offset) coords.
	 * @param: __x:       Physical pixel X coord
	 * @param: __y:       Physical pixel Y coord
	 * @param: __offsets: The offset (virtual) coords of the pixel are stored here
	 * @return: true:  Translation was successful
	 * @return: false: The given __x/__y lie outside the I/O Rect of `__self' */
	__ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_OUT_T(4) __BOOL
	(LIBVIDEO_GFX_CC *vgfo_coord2offset)(struct video_gfx const *__restrict __self,
	                                     video_coord_t __x, video_coord_t __y,
	                                     video_offset_t __offsets[2]);

	/* Get the color of a pixel */
	__ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_IN_T(1) video_color_t
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
	 * This function is mainly here to facilitate the rendering of glyphs (s.a. fonts/tlft.h) */

	/* TODO: This  operator needs to  go away; mask-fills need  to happen using blits,
	 *       and `video_buffer_forbitmask()' needs to go away, also. Instead, bitmasks
	 *       need to use `video_buffer_formem()', which in turn also needs the ability
	 *       to be allocated in V-RAM. */
	__ATTR_IN_T(1) __ATTR_IN_T(6) __ATTR_IN_T(7) void
	(LIBVIDEO_GFX_CC *vgfo_fillmask)(struct video_gfx const *__restrict __self,
	                                 video_offset_t __x, video_offset_t __y,
	                                 video_dim_t __size_x, video_dim_t __size_y,
	                                 video_color_t const __bg_fg_colors[2],
	                                 struct video_bitmask const *__restrict __bm);

	/* Same as `vgfo_fillmask()', however perform the blit while up-scaling the given bitmask. */
	/* TODO: This one needs to go away, too */
	__ATTR_IN_T(1) __ATTR_IN_T(6) __ATTR_IN_T(9) void
	(LIBVIDEO_GFX_CC *vgfo_fillstretchmask)(struct video_gfx const *__restrict __self,
	                                        video_offset_t __dst_x, video_offset_t __dst_y,
	                                        video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                        video_color_t const __bg_fg_colors[2],
	                                        video_dim_t __src_size_x, video_dim_t __src_size_y,
	                                        struct video_bitmask const *__restrict __bm);

	/* Same as `vgfo_fill', but do so via gradient with colors[y][x] being used
	 * to essentially do a  VIDEO_GFX_F_LINEAR stretch-blit into the  specified
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

	/* Helper wrapper that creates a temporary blitter and then does a blit */
	__ATTR_IN_T(1) __ATTR_IN_T(4) void
	(LIBVIDEO_GFX_CC *vgfo_bitblit)(struct video_gfx const *__dst,
	                                video_offset_t __dst_x, video_offset_t __dst_y,
	                                struct video_gfx const *__src,
	                                video_offset_t __src_x, video_offset_t __src_y,
	                                video_dim_t __size_x, video_dim_t __size_y);

	/* Helper wrapper that creates a temporary blitter and then does a stretch */
	__ATTR_IN_T(1) __ATTR_IN_T(6) void
	(LIBVIDEO_GFX_CC *vgfo_stretch)(struct video_gfx const *__dst,
	                                video_offset_t __dst_x, video_offset_t __dst_y,
	                                video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                struct video_gfx const *__src,
	                                video_offset_t __src_x, video_offset_t __src_y,
	                                video_dim_t __src_size_x, video_dim_t __src_size_y);

	/* Helper wrapper that creates a temporary blitter3 and then does a blit */
	__ATTR_IN_T(1) __ATTR_IN_T(4) __ATTR_IN_T(7) void
	(LIBVIDEO_GFX_CC *vgfo_bitblit3)(struct video_gfx const *__wrdst,
	                                 video_offset_t __wrdst_x, video_offset_t __wrdst_y,
	                                 struct video_gfx const *__rddst,
	                                 video_offset_t __rddst_x, video_offset_t __rddst_y,
	                                 struct video_gfx const *__src,
	                                 video_offset_t __src_x, video_offset_t __src_y,
	                                 video_dim_t __size_x, video_dim_t __size_y);

	/* Helper wrapper that creates a temporary blitter3 and then does a stretch */
	__ATTR_IN_T(1) __ATTR_IN_T(4) __ATTR_IN_T(9) void
	(LIBVIDEO_GFX_CC *vgfo_stretch3)(struct video_gfx const *__wrdst,
	                                 video_offset_t __wrdst_x, video_offset_t __wrdst_y,
	                                 struct video_gfx const *__rddst,
	                                 video_offset_t __rddst_x, video_offset_t __rddst_y,
	                                 video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                 struct video_gfx const *__src,
	                                 video_offset_t __src_x, video_offset_t __src_y,
	                                 video_dim_t __src_size_x, video_dim_t __src_size_y);

	/* TODO: Repeats of all above operators, using floats instead of "video_offset_t" */

	/* More driver-specific operators go here... */
};



/* Perform geometric transformations on the contents of the current  clip
 * rect of `self'. Note that none of these functions alter pixel data  of
 * the underlying buffer; they only affect how the given `self' interacts
 * with pixel data of the underlying buffer.
 *
 * - video_gfx_xyswap:  Swap x/y coords (mirror pixel data along a diagonal starting in the top-left)
 * - video_gfx_hmirror: Mirror pixel data horizontally
 * - video_gfx_vmirror: Mirror pixel data vertically
 * - video_gfx_lrot90:  Rotate pixel data left 90°
 * - video_gfx_rrot90:  Rotate pixel data right 90°
 * - video_gfx_rot180:  Rotate pixel data 180°
 * - video_gfx_nrot90n: Rotate pixel data by left by 90*n°
 * - video_gfx_rrot90n: Rotate pixel data by right by 90*n° */
typedef __ATTR_INOUT_T(1) struct video_gfx *(LIBVIDEO_GFX_FCC *PVIDEO_GFX_XYSWAP)(struct video_gfx *__restrict __self);
typedef __ATTR_INOUT_T(1) struct video_gfx *(LIBVIDEO_GFX_FCC *PVIDEO_GFX_HMIRROR)(struct video_gfx *__restrict __self);
typedef __ATTR_INOUT_T(1) struct video_gfx *(LIBVIDEO_GFX_FCC *PVIDEO_GFX_VMIRROR)(struct video_gfx *__restrict __self);
typedef __ATTR_INOUT_T(1) struct video_gfx *(LIBVIDEO_GFX_FCC *PVIDEO_GFX_LROT90)(struct video_gfx *__restrict __self);
typedef __ATTR_INOUT_T(1) struct video_gfx *(LIBVIDEO_GFX_FCC *PVIDEO_GFX_RROT90)(struct video_gfx *__restrict __self);
typedef __ATTR_INOUT_T(1) struct video_gfx *(LIBVIDEO_GFX_FCC *PVIDEO_GFX_ROT180)(struct video_gfx *__restrict __self);
typedef __ATTR_INOUT_T(1) struct video_gfx *(LIBVIDEO_GFX_FCC *PVIDEO_GFX_LROT90N)(struct video_gfx *__restrict __self, int __n);
typedef __ATTR_INOUT_T(1) struct video_gfx *(LIBVIDEO_GFX_FCC *PVIDEO_GFX_RROT90N)(struct video_gfx *__restrict __self, int __n);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_INOUT(1) struct video_gfx *LIBVIDEO_GFX_FCC video_gfx_xyswap(struct video_gfx *__restrict __self);
LIBVIDEO_GFX_DECL __ATTR_INOUT(1) struct video_gfx *LIBVIDEO_GFX_FCC video_gfx_hmirror(struct video_gfx *__restrict __self);
LIBVIDEO_GFX_DECL __ATTR_INOUT(1) struct video_gfx *LIBVIDEO_GFX_FCC video_gfx_vmirror(struct video_gfx *__restrict __self);
LIBVIDEO_GFX_DECL __ATTR_INOUT(1) struct video_gfx *LIBVIDEO_GFX_FCC video_gfx_lrot90(struct video_gfx *__restrict __self);
LIBVIDEO_GFX_DECL __ATTR_INOUT(1) struct video_gfx *LIBVIDEO_GFX_FCC video_gfx_rrot90(struct video_gfx *__restrict __self);
LIBVIDEO_GFX_DECL __ATTR_INOUT(1) struct video_gfx *LIBVIDEO_GFX_FCC video_gfx_rot180(struct video_gfx *__restrict __self);
LIBVIDEO_GFX_DECL __ATTR_INOUT(1) struct video_gfx *LIBVIDEO_GFX_FCC video_gfx_lrot90n(struct video_gfx *__restrict __self, int __n);
LIBVIDEO_GFX_DECL __ATTR_INOUT(1) struct video_gfx *LIBVIDEO_GFX_FCC video_gfx_rrot90n(struct video_gfx *__restrict __self, int __n);
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


/* GFX  clip data container (for backup+restore using
 * `video_gfx_saveclip()' and `video_gfx_loadclip()') */
typedef struct video_gfxhdr video_gfx_clipinfo_t;


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

/* Same as `video_blitter_bitblit', but stretch the contents */
extern __ATTR_IN(1) void
video_blitter_stretch(struct video_blitter const *__restrict __self,
                      video_offset_t __dst_x, video_offset_t __dst_y,
                      video_dim_t __dst_size_x, video_dim_t __dst_size_y,
                      video_offset_t __src_x, video_offset_t __src_y,
                      video_dim_t __src_size_x, video_dim_t __src_size_y);




/************************************************************************/
/* VIDEO_BLIT3                                                          */
/************************************************************************/

/* Blit the contents of another video buffer into this one.
 * The given __dst_x/__dst_y are used for both "vbt3_rddst" and "vbt3_wrdst" */
extern __ATTR_IN(1) void
video_blitter3_bitblit(struct video_blitter3 const *__restrict __self,
                       video_offset_t __wrdst_x, video_offset_t __wrdst_y,
                       video_offset_t __rddst_x, video_offset_t __rddst_y,
                       video_offset_t __src_x, video_offset_t __src_y,
                       video_dim_t __size_x, video_dim_t __size_y);

/* Same as `video_blitter3_bitblit', but stretch the contents
 * The given __dst_x/__dst_y are used for both "vbt3_rddst" and "vbt3_wrdst" */
extern __ATTR_IN(1) void
video_blitter3_stretch(struct video_blitter3 const *__restrict __self,
                       video_offset_t __wrdst_x, video_offset_t __wrdst_y,
                       video_offset_t __rddst_x, video_offset_t __rddst_y,
                       video_dim_t __dst_size_x, video_dim_t __dst_size_y,
                       video_offset_t __src_x, video_offset_t __src_y,
                       video_dim_t __src_size_x, video_dim_t __src_size_y);




/************************************************************************/
/* VIDEO_GFX                                                            */
/************************************************************************/

/* Return the API-visible Clip Rect size in X or Y */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t
video_gfx_getclipw(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t
video_gfx_getcliph(struct video_gfx const *__restrict __self);

/* Backup/restore the current Clip Rect of `self' */
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

/* Get/set GFX modes for `__self'. If you want to set multiple of these at once,
 * you should directly assign  the respective members, and  then make a call  to
 * `video_gfx_update()' specifying exactly what changed. */
extern __ATTR_RETNONNULL __ATTR_PURE __ATTR_IN(1) gfx_blendmode_t video_gfx_getblend(struct video_gfx const *__restrict __self);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *video_gfx_setblend(struct video_gfx *__restrict __self, gfx_blendmode_t __mode);
extern __ATTR_RETNONNULL __ATTR_PURE __ATTR_IN(1) video_gfx_flag_t video_gfx_getflags(struct video_gfx const *__restrict __self);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *video_gfx_setflags(struct video_gfx *__restrict __self, video_gfx_flag_t __flags);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *video_gfx_toggleflags(struct video_gfx *__restrict __self, video_gfx_flag_t __flags);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *video_gfx_enableflags(struct video_gfx *__restrict __self, video_gfx_flag_t __flags);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *video_gfx_disableflags(struct video_gfx *__restrict __self, video_gfx_flag_t __flags);
extern __ATTR_RETNONNULL __ATTR_PURE __ATTR_IN(1) video_color_t video_gfx_getcolorkey(struct video_gfx const *__restrict __self);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *video_gfx_setcolorkey(struct video_gfx *__restrict __self, video_color_t __colorkey);

/* Apply a clipping  rect to "self",  shrinking the  pixel
 * area relative to offsets specified by the given coords.
 *
 * Note that the clip area can  only ever be shrunk. To  go
 * back to the initial clip area, either keep a copy of the
 * original GFX  context, or  create a  new context  (which
 * always starts  out with  its clipping  area set  to  the
 * associated buffer's entire surface)
 *
 * @param: __clip_x: Delta to add to the Clip Rect starting X coord.
 *                   When negative, extend clip rect with void-pixels to the left
 * @param: __clip_y: Delta to add to the Clip Rect starting Y coord.
 *                   When negative, extend clip rect with void-pixels to the top
 * @param: __size_x: New width of the clip rect. When greater than the old  clip
 *                   rect width, extend clip rect with void-pixels to the right.
 * @param: __size_y: New height of the clip rect.  When greater than the old  clip
 *                   rect height, extend clip rect with void-pixels to the bottom.
 * @return: * : Always re-returns `__self' */
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *
video_gfx_clip(struct video_gfx *__restrict __self,
               video_offset_t __clip_x, video_offset_t __clip_y,
               video_dim_t __size_x, video_dim_t __size_y);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) __ATTR_IN(2) struct video_gfx *
video_gfx_cliprect(struct video_gfx *__restrict __self,
                   struct video_rect const *__restrict __rect);


/* Translate virtual (offset) pixel coords to physical (coord) coords.
 * @param: __x:      Virtual pixel X offset
 * @param: __y:      Virtual pixel Y offset
 * @param: __coords: The absolute (physical) coords of the pixel are stored here
 * @return: true:  Translation was successful
 * @return: false: The given __x/__y lie outside the I/O Rect of `__self' */
extern __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(4) __BOOL
video_gfx_offset2coord(struct video_gfx const *__restrict __self,
                       video_offset_t __x, video_offset_t __y,
                       video_coord_t __coords[2]);

/* Translate physical (coord) pixel coords to virtual (offset) coords.
 * @param: __x:       Physical pixel X coord
 * @param: __y:       Physical pixel Y coord
 * @param: __offsets: The offset (virtual) coords of the pixel are stored here
 * @return: true:  Translation was successful
 * @return: false: The given __x/__y lie outside the I/O Rect of `__self' */
extern __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(4) __BOOL
video_gfx_coord2offset(struct video_gfx const *__restrict __self,
                       video_coord_t __x, video_coord_t __y,
                       video_offset_t __offsets[2]);



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
                      video_color_t const __bg_fg_colors[2],
                      struct video_bitmask const *__restrict __bm);

/* Same as `video_gfx_absfillmask()', however perform the blit while up-scaling the given bitmask. */
extern __ATTR_IN(1) __ATTR_IN(9) void
video_gfx_absfillstretchmask(struct video_gfx const *__restrict __self,
                             video_offset_t __dst_x, video_offset_t __dst_y,
                             video_dim_t __dst_size_x, video_dim_t __dst_size_y,
                             video_color_t const __bg_fg_colors[2],
                             video_dim_t __src_size_x, video_dim_t __src_size_y,
                             struct video_bitmask const *__restrict __bm);

/* Same as `video_gfx_fill', but do so via gradient with colors[y][x] being
 * used to  essentially  do  a  VIDEO_GFX_F_LINEAR  stretch-blit  into  the
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

/* Initialize bitting contexts to rendering between 3 given GFX contexts. */
extern __ATTR_RETNONNULL __ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3) __ATTR_OUT(4) struct video_blitter3 *
video_gfx_blitfrom3(struct video_gfx const *__wrdst,
                    struct video_gfx const *__rddst,
                    struct video_gfx const *__src,
                    struct video_blitter3 *__ctx);


/* Directly do blitting between 2 GFX contexts (helpers to wrap "struct video_blitter") */
extern __ATTR_IN(1) __ATTR_IN(4) void
video_gfx_bitblit(struct video_gfx const *__dst, video_offset_t __dst_x, video_offset_t __dst_y,
                  struct video_gfx const *__src, video_offset_t __src_x, video_offset_t __src_y,
                  video_dim_t __size_x, video_dim_t __size_y);
extern __ATTR_IN(1) __ATTR_IN(6) void
video_gfx_stretch(struct video_gfx const *__dst, video_offset_t __dst_x, video_offset_t __dst_y, video_dim_t __dst_size_x, video_dim_t __dst_size_y,
                  struct video_gfx const *__src, video_offset_t __src_x, video_offset_t __src_y, video_dim_t __src_size_x, video_dim_t __src_size_y);

/* Directly do blitting between 3 GFX contexts (helpers to wrap "struct video_blitter3") */
extern __ATTR_IN(1) __ATTR_IN(4) __ATTR_IN(7) void
video_gfx_bitblit3(struct video_gfx const *__wrdst, video_offset_t __wrdst_x, video_offset_t __wrdst_y,
                   struct video_gfx const *__rddst, video_offset_t __rddst_x, video_offset_t __rddst_y,
                   struct video_gfx const *__src, video_offset_t __src_x, video_offset_t __src_y,
                   video_dim_t __size_x, video_dim_t __size_y);
extern __ATTR_IN(1) __ATTR_IN(4) __ATTR_IN(9) void
video_gfx_stretch3(struct video_gfx const *__wrdst, video_offset_t __wrdst_x, video_offset_t __wrdst_y,
                   struct video_gfx const *__rddst, video_offset_t __rddst_x, video_offset_t __rddst_y,
                   video_dim_t __dst_size_x, video_dim_t __dst_size_y,
                   struct video_gfx const *__src, video_offset_t __src_x, video_offset_t __src_y,
                   video_dim_t __src_size_x, video_dim_t __src_size_y);
#else /* __INTELLISENSE__ */
#define video_blitter_bitblit(self, dst_x, dst_y, src_x, src_y, size_x, size_y) \
	(*(self)->vbt_ops->vbto_bitblit)(self, dst_x, dst_y, src_x, src_y, size_x, size_y)
#define video_blitter_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y) \
	(*(self)->vbt_ops->vbto_stretch)(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y)
#define video_blitter3_bitblit(self, wrdst_x, wrdst_y, rddst_x, rddst_y, src_x, src_y, size_x, size_y) \
	(*(self)->vbt3_ops->vbt3o_bitblit)(self, wrdst_x, wrdst_y, rddst_x, rddst_y, src_x, src_y, size_x, size_y)
#define video_blitter3_stretch(self, wrdst_x, wrdst_y, rddst_x, rddst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y) \
	(*(self)->vbt3_ops->vbt3o_stretch)(self, wrdst_x, wrdst_y, rddst_x, rddst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y)

#define video_gfx_getclipw(self) (self)->vx_hdr.vxh_cxsiz
#define video_gfx_getcliph(self) (self)->vx_hdr.vxh_cysiz
#define video_gfx_saveclip(self, backup) (void)__libc_memcpy(backup, &(self)->vx_hdr, sizeof(video_gfx_clipinfo_t))
#define video_gfx_loadclip(self, backup) (void)__libc_memcpy(&(self)->vx_hdr, backup, sizeof(video_gfx_clipinfo_t))
#define video_gfx_update(self, what) \
	(*(self)->vx_buffer->vb_ops->vi_updategfx)(self, what)
#define video_gfx_getblend(self)              ((self)->vx_blend)
#define video_gfx_getflags(self)              ((self)->vx_flags)
#define video_gfx_clip(self, clip_x, clip_y, size_x, size_y) \
	(*(self)->vx_hdr.vxh_ops->vgfo_clip)(self, clip_x, clip_y, size_x, size_y)
#define video_gfx_cliprect(self, rect) \
	video_gfx_clip(self, (rect)->vr_xmin, (rect)->vr_ymin, (rect)->vr_xdim, (rect)->vr_ydim)
#define video_gfx_offset2coord(self, x, y, coords) \
	(*(self)->vx_hdr.vxh_ops->vgfo_offset2coord)(self, x, y, coords)
#define video_gfx_coord2offset(self, x, y, offsets) \
	(*(self)->vx_hdr.vxh_ops->vgfo_coord2offset)(self, x, y, offsets)
#define video_gfx_getcolorkey(self)           ((self)->vx_colorkey)
#define video_gfx_setblend(self, mode)        ((self)->vx_blend = (mode), video_gfx_update(self, VIDEO_GFX_UPDATE_BLEND))
#define video_gfx_setflags(self, flags)       ((self)->vx_flags = (flags), video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS))
#define video_gfx_toggleflags(self, flags)    ((self)->vx_flags ^= (flags), video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS))
#define video_gfx_enableflags(self, flags)    ((self)->vx_flags |= (flags), video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS))
#define video_gfx_disableflags(self, flags)   ((self)->vx_flags &= ~(flags), video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS))
#define video_gfx_setcolorkey(self, colorkey) ((self)->vx_colorkey = (colorkey), video_gfx_update(self, VIDEO_GFX_UPDATE_COLORKEY))
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
#define video_gfx_absfillmask(self, x, y, size_x, size_y, bg_fg_colors, bigtmask) \
	(*(self)->vx_hdr.vxh_ops->vgfo_fillmask)(self, x, y, size_x, size_y, bg_fg_colors, bigtmask)
#define video_gfx_absfillstretchmask(self, dst_x, dst_y, dst_sizex, dst_sizey, bg_fg_colors, src_size_x, src_size_y, bigtmask) \
	(*(self)->vx_hdr.vxh_ops->vgfo_fillstretchmask)(self, dst_x, dst_y, dst_sizex, dst_sizey, bg_fg_colors, src_size_x, src_size_y, bigtmask)
#define video_gfx_gradient(self, x, y, size_x, size_y, colors) \
	(*(self)->vx_hdr.vxh_ops->vgfo_gradient)(self, x, y, size_x, size_y, colors)
#define video_gfx_hgradient(self, x, y, size_x, size_y, locolor, hicolor) \
	(*(self)->vx_hdr.vxh_ops->vgfo_hgradient)(self, x, y, size_x, size_y, locolor, hicolor)
#define video_gfx_vgradient(self, x, y, size_x, size_y, locolor, hicolor) \
	(*(self)->vx_hdr.vxh_ops->vgfo_vgradient)(self, x, y, size_x, size_y, locolor, hicolor)
#define video_gfx_blitfrom(dst, src, ctx) \
	((ctx)->vbt_src = (src), (*((ctx)->vbt_dst = (dst))->vx_hdr.vxh_ops->vgfo_blitfrom)(ctx))
#define video_gfx_blitto(src, dst, ctx) \
	((ctx)->vbt_src = (src), (*((ctx)->vbt_dst = (dst))->vx_hdr.vxh_ops->vgfo_blitfrom)(ctx))
#define video_gfx_blitfrom3(wrdst, rddst, src, ctx)        \
	((ctx)->vbt3_src = (src), (ctx)->vbt3_rddst = (rddst), \
	 (*((ctx)->vbt3_wrdst = (wrdst))->vx_hdr.vxh_ops->vgfo_blitfrom3)(ctx))
#define video_gfx_bitblit(dst, dst_x, dst_y, src, src_x, src_y, size_x, size_y) \
	(*(dst)->vx_hdr.vxh_ops->vgfo_bitblit)(dst, dst_x, dst_y, src, src_x, src_y, size_x, size_y)
#define video_gfx_stretch(dst, dst_x, dst_y, dst_size_x, dst_size_y, src, src_x, src_y, src_size_x, src_size_y) \
	(*(dst)->vx_hdr.vxh_ops->vgfo_stretch)(dst, dst_x, dst_y, dst_size_x, dst_size_y, src, src_x, src_y, src_size_x, src_size_y)
#define video_gfx_bitblit3(wrdst, wrdst_x, wrdst_y, rddst, rddst_x, rddst_y, src, src_x, src_y, size_x, size_y) \
	(*(wrdst)->vx_hdr.vxh_ops->vgfo_bitblit3)(wrdst, wrdst_x, wrdst_y, rddst, rddst_x, rddst_y, src, src_x, src_y, size_x, size_y)
#define video_gfx_stretch3(wrdst, wrdst_x, wrdst_y, rddst, rddst_x, rddst_y, dst_size_x, dst_size_y, src, src_x, src_y, src_size_x, src_size_y) \
	(*(wrdst)->vx_hdr.vxh_ops->vgfo_stretch3)(wrdst, wrdst_x, wrdst_y, rddst, rddst_x, rddst_y, dst_size_x, dst_size_y, src, src_x, src_y, src_size_x, src_size_y)
#endif /* !__INTELLISENSE__ */



#ifdef __cplusplus
__CXXDECL_BEGIN
#endif /* __cplusplus */

#define __VIDEO_BLITTER_N_DRIVER 8
#define _VIDEO_BLITTER_N_DRIVER (__VIDEO_BLITTER_N_DRIVER + 1 + _VIDEO_CONVERTER_N_YDRIVER)
#if _VIDEO_BLITTER_N_DRIVER < (__VIDEO_BLITTER_N_DRIVER + 6)
#undef _VIDEO_BLITTER_N_DRIVER
#define _VIDEO_BLITTER_N_DRIVER (__VIDEO_BLITTER_N_DRIVER + 6)
#endif /* _VIDEO_BLITTER_N_DRIVER < (__VIDEO_BLITTER_N_DRIVER + 6) */

struct video_blitter {
	struct video_blitter_ops const *vbt_ops;    /* Blitter operators */
	/* WARNING: After initialization, the following fields must no longer be accessed by the user! */
	struct video_gfx const         *vbt_dst;    /* [1..1][const] Destination GFX context */
	struct video_gfx const         *vbt_src;    /* [1..1][const] Source GFX context */
	void *_vbt_driver[_VIDEO_BLITTER_N_DRIVER]; /* [?..?] Driver-specific graphics data. */

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
		video_blitter_stretch(this, __dst_x, __dst_y, __dst_size_x, __dst_size_y,
		                      __src_x, __src_y, __src_size_x, __src_size_y);
	}
#endif /* __cplusplus */
};


#define _VIDEO_BLITTER3_N_DRIVER (_VIDEO_BLITTER_N_DRIVER - 1)

/* 3-way video blitter. Meant to be used to perform a blit  whilst
 * retaining/enforcing some sort of overlay whose dimensions match
 * that of the blit (write-)destination.
 *
 * NOTE: Only the intersection of rects in "vbt3_rddst" / "vbt3_wrdst"
 *       actually gets blitted!
 *
 * NOTE: In  order to perform  a marked blit (iow:  a blit where only
 *       pixels that appear as 1-bits in some pixel mask are copied),
 *       store the mask  as a  video_buffer using  VIDEO_CODEC_A1_MSB
 *       as pixel codec, and then blit as follows:
 * >> void masked_blit(struct video_buffer *dst,
 * >>                  struct video_buffer *mask,
 * >>                  struct video_buffer *src) {
 * >>     struct video_gfx dst_gfx;
 * >>     struct video_gfx src_gfx;
 * >>     struct video_gfx mask_gfx;
 * >>     video_buffer_getgfx(dst, &dst_gfx, GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
 * >>     video_buffer_getgfx(src, &src_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0); // Blend mode doesn't matter
 * >>     video_buffer_getgfx(mask, &mask_gfx, GFX_BLENDMODE_ALPHAMASK, VIDEO_GFX_F_NORMAL, 0);
 * >>     video_gfx_bitblit3(&dst_gfx, 0, 0, &mask_gfx, 0, 0, &src_gfx, 0, 0,
 * >>                        video_gfx_getclipw(&src_gfx), video_gfx_getclipw(&dst_gfx));
 * >> }
 *
 * An optimizing video blitter implementation will detect this config
 * of GFX contexts and provide dedicated optimizations for this case. */
struct video_blitter3 {
	struct video_blitter3_ops const *vbt3_ops;    /* Blitter operators */
	/* WARNING: After initialization, the following fields must no longer be accessed by the user! */
	struct video_gfx const          *vbt3_wrdst;  /* [1..1][const] Output GFX context */
	struct video_gfx const          *vbt3_src;    /* [1..1][const] Source GFX context */
	struct video_gfx const          *vbt3_rddst;  /* [1..1][const] Destination GFX context */
	void *_vbt3_driver[_VIDEO_BLITTER3_N_DRIVER]; /* [?..?] Driver-specific graphics data. */

#ifdef __cplusplus
public:
	/* Blit the contents of another video buffer into this one. */
	__CXX_CLASSMEMBER void blit(video_offset_t __wrdst_x, video_offset_t __wrdst_y,
	                            video_offset_t __rddst_x, video_offset_t __rddst_y,
	                            video_offset_t __src_x, video_offset_t __src_y,
	                            video_dim_t __size_x, video_dim_t __size_y) const {
		video_blitter3_bitblit(this, __wrdst_x, __wrdst_y, __rddst_x, __rddst_y,
		                       __src_x, __src_y, __size_x, __size_y);
	}

	/* Same as `blit', but stretch the contents */
	__CXX_CLASSMEMBER void stretch(video_offset_t __wrdst_x, video_offset_t __wrdst_y,
	                               video_offset_t __rddst_x, video_offset_t __rddst_y,
	                               video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                               video_offset_t __src_x, video_offset_t __src_y,
	                               video_dim_t __src_size_x, video_dim_t __src_size_y) const {
		video_blitter3_stretch(this, __wrdst_x, __wrdst_y, __rddst_x, __rddst_y,
		                       __dst_size_x, __dst_size_y,
		                       __src_x, __src_y, __src_size_x, __src_size_y);
	}
#endif /* __cplusplus */
};




struct video_gfxhdr {
	struct video_gfx_ops const *vxh_ops; /* [1..1][const] GFX operators (use these) */

	/* Clip Rect area (pixel area used for pixel clamping/wrapping, and accepted):
	 *
	 ***********************************************************************************
	 *  ╔═════════════════════════════════╗                                            *
	 *  ║ Buffer                          ║                                            *
	 *  ║                                 ║                                            *
	 *  ║   ╔═══════════════════════╗─────╫─────────────────┬───────────────────────┐  *
	 *  ║   ║ Clip Rect             ║ Clip Rect             │ Clip Rect             │  *
	 *  ║   ║                       ║     ║                 │                       │  *
	 *  ║   ║                       ║     ║                 │                       │  *
	 *  ║   ║  ╔═════════════════╗  ║  ┌─────────────────┐  │  ┌─────────────────┐  │  *
	 *  ║   ║  ║ I/O Rect        ║  ║  │ I/O Rect (alias)│  │  │ I/O Rect (alias)│  │  *
	 *  ║   ║  ║                 ║  ║  │  ║              │  │  │                 │  │  *
	 *  ║   ║  ╚═════════════════╝  ║  └─────────────────┘  │  └─────────────────┘  │  *
	 *  ║   ║                       ║     ║                 │                       │  *
	 *  ║   ╚═══════════════════════╝─────╫─────────────────┴───────────────────────┘  *
	 *  ║   │ Clip Rect             │     ║                 ·                       ·  *
	 *  ╚═══╪═══════════════════════╪═════╝                 ·                       ·  *
	 *      │                       │                       ·                       ·  *
	 *      │  ┌─────────────────┐  │  ···················  ·  ···················  ·  *
	 *      │  │ I/O Rect (alias)│  │  ·                 ·  ·  ·                 ·  ·  *
	 *      │  │                 │  │  ·                 ·  ·  ·                 ·  ·  *
	 *      │  └─────────────────┘  │  ···················  ·  ···················  ·  *
	 *      │                       │                       ·                       ·  *
	 *      ├───────────────────────┤················································  *
	 *      │ Clip Rect             │                       ·                       ·  *
	 *      │                       │                       ·                       ·  *
	 *      │                       │                       ·                       ·  *
	 *      │  ┌─────────────────┐  │  ···················  ·  ···················  ·  *
	 *      │  │ I/O Rect (alias)│  │  ·                 ·  ·  ·                 ·  ·  *
	 *      │  │                 │  │  ·                 ·  ·  ·                 ·  ·  *
	 *      │  └─────────────────┘  │  ···················  ·  ···················  ·  *
	 *      │                       │                       ·                       ·  *
	 *      └───────────────────────┘················································  *
	 *                                                                                 *
	 ***********************************************************************************
	 *
	 * Invariants:
	 * - "I/O Rect" ⊆ "Clip Rect", "I/O Rect" ⊆ "Buffer"
	 * - VIDEO_GFX_F_XWRAP/*Y are wrapped around "Clip Rect"
	 * - Only pixels within the "I/O Rect" can be read/written
	 * - VIDEO_GFX_F_XMIRROR/*Y mirror the "I/O Rect"
	 *
	 * Coords of these rects are (in absolute "video_coord_t" coords):
	 * - Buffer:    {xy: {0,0}, wh: {vx_buffer->vb_xdim,vx_buffer->vb_ydim}}
	 * - Clip Rect: {xy: {vxh_cxoff,vxh_cyoff}, wh: {vxh_cxsiz,vxh_cysiz}}
	 * - I/O Rect:  {xy: {vxh_bxmin,vxh_bymin}, wh: {vxh_bxsiz,vxh_bysiz}}
	 *
	 * When using any of the  publicly exposed functions, you always  operate
	 * in the coord-space defined by the "Clip Rect", with pixel reads/writes
	 * restricted to those within the "I/O Rect". Pixel coords that go beyond
	 * the  "Clip Rect", are either clamped, or wrapped (based on GFX flags),
	 * before  then being clamped  again to the  "I/O Rect". You might notice
	 * that  when pixel  wrapping is disabled,  the first clamp  can (and is)
	 * skipped.
	 *
	 * When changing the Clip Rect, coords are still relative to the old  clip
	 * rect, but negative  coords can  be given to  make the  Clip Rect  grow.
	 * However, the "I/O Rect"  is always the  intersection of "Buffer",  with
	 * any "Clip Rect" ever  set for  the GFX  context, meaning  it cannot  be
	 * made to grow without obtaining a fresh GFX context (which always starts
	 * out with all 3 areas set to match each other).
	 *
	 * Virtual -> Physical coord translation (currently) happens as follows.
	 * Do no rely on this translation behavior; always use APIs to modify or
	 * otherwise interact with Clip Rect infos.
	 * >> if (vx_flags & VIDEO_GFX_F_XMIRROR)
	 * >>     x = (vxh_cxsiz - 1) - x;
	 * >> if (vx_flags & VIDEO_GFX_F_YMIRROR)
	 * >>     y = (vxh_cysiz - 1) - y;
	 * >> if (vx_flags & VIDEO_GFX_F_XWRAP)
	 * >>     x = wrap(x, vxh_cxsiz); // wrap(x, dim) = ((x % dim) + dim) % dim
	 * >> if (vx_flags & VIDEO_GFX_F_YWRAP)
	 * >>     x = wrap(x, vxh_cxsiz); // ...
	 * >> x += vxh_cxoff;
	 * >> y += vxh_cyoff;
	 * >> if (x < vxh_bxmin)
	 * >>     return VOID;
	 * >> if (y < vxh_bymin)
	 * >>     return VOID;
	 * >> if (x >= vxh_bxend)
	 * >>     return VOID;
	 * >> if (y >= vxh_byend)
	 * >>     return VOID;
	 * >> if (vx_flags & VIDEO_GFX_F_XYSWAP) {
	 * >>     temp = x;
	 * >>     x = y;
	 * >>     y = temp;
	 * >> }
	 * >> return {x,y};
	 */
	video_offset_t              vxh_cxoff;    /* [const] Delta added to all X coords (as per clip-rect) to turn "video_offset_t" into "video_coord_t" */
	video_offset_t              vxh_cyoff;    /* [const] Delta added to all Y coords (as per clip-rect) to turn "video_offset_t" into "video_coord_t" */
	video_dim_t                 vxh_cxsiz;    /* [const] Absolute width of the clip-rect (only relevant for `VIDEO_GFX_F*RAP') */
	video_dim_t                 vxh_cysiz;    /* [const] Absolute height of the clip-rect (only relevant for `VIDEO_GFX_F*RAP') */
	/* I/O Rect: these values control the (absolute) pixel area where read/writes do something
	 * NOTE: The I/O Rect is already pre-adjusted for VIDEO_GFX_F_XMIRROR/VIDEO_GFX_F_YMIRROR */
	video_coord_t               vxh_bxmin;    /* [const][<= vxh_bxend][>= vxh_cxoff] Absolute buffer start coord in X (start of acc) */
	video_coord_t               vxh_bymin;    /* [const][<= vxh_byend][>= vxh_cyoff] Absolute buffer start coord in Y */
	video_coord_t               vxh_bxend;    /* [const][<= vx_buffer->vb_xdim] Absolute buffer end coord in X (<= `vx_buffer->vb_xdim') */
	video_coord_t               vxh_byend;    /* [const][<= vx_buffer->vb_ydim] Absolute buffer end coord in Y (<= `vx_buffer->vb_ydim') */
//	video_dim_t                 vxh_bxsiz;    /* [const][== vxh_bxend - vxh_bxmin][<= vxh_cxsiz] I/O Rect width */
//	video_dim_t                 vxh_bysiz;    /* [const][== vxh_byend - vxh_bymin][<= vxh_cysiz] I/O Rect height */
};

#define _video_gfxhdr_bxsiz(self) ((self)->vxh_bxend - (self)->vxh_bxmin)
#define _video_gfxhdr_bysiz(self) ((self)->vxh_byend - (self)->vxh_bymin)

struct video_gfx {
	struct video_gfxhdr  vx_hdr;      /* GFX header (this part of the struct can be saved/restored in order to restore old Clip Rects) */
	struct video_buffer *vx_buffer;   /* [1..1][const] The associated buffer. */
	/* TODO: To get rid of "vgfo_fillmask" and "vgfo_fillstretchmask":
	 * TLFT fonts will need to:
	 * - load their character bitmasks using `video_domain_formem()' with:
	 *   >> xdim = character_width
	 *   >> ydim = num_characters * character_height
	 *   >> codec = video_codec_lookup(VIDEO_CODEC_P1_MSB);
	 * - render the I'th characters using:
	 *   >> video_gfx_bitblit(dst, x, y, FONT_BUFFER, src_x: 0, src_y: I * character_height);
	 *   But to do this render using custom colors,  there needs to be a way for doing  blits
	 *   using custom source color palettes.
	 * Currently, in order to do custom color blits, the font would need to re-load its entire
	 * video buffer. Even more  general, palette-drive video buffers  should be able of  being
	 * assigned a new video_palette **DURING** their  live-time, so just allowing a  different
	 * palette to be used for singular GFX operations wouldn't even be enough here!
	 *
	 * The more I think about this, only the CODEC of a video buffer has to remain constant for
	 * the duration of that buffer's life-time. The palette should be interchangeable as  often
	 * as one pleases... Yet  that brings up the  problem that palettes are  reference-counted,
	 * and yet they would **really** need to be stored in `struct video_gfx'. But I also really
	 * don't  want to give `struct video_gfx' a finalizer, though it'd need one for the current
	 * color palette if it couldn't rely on the associated buffer's palette remaining constant.
	 *
	 * ------------
	 *
	 * Thinking about this, the only *real* solution is to NOT have this field, but simply have
	 * a second version of `video_blitter_bitblit()` that takes a source palette override as an
	 * argument.
	 */
//	struct video_palette *vx_rdpalette; /* [0..1][(!= NULL) == (vx_buffer->vb_format.vf_pal != NULL)][const] Palette used for color reads and bitblit sources */
	gfx_blendmode_t      vx_blend;    /* Blending mode. */
	video_gfx_flag_t     vx_flags;    /* Additional rendering flags (Set of `VIDEO_GFX_F*'). */
	/* TODO: Get rid of "vx_colorkey":
	 * - Color keys must be represented as `video_pixel_t'
	 * - Color keys must be defined by `video_buffer' (somehow?)
	 * - Color keys only become relevant for `struct video_blitter[3]'
	 *
	 * TODO: There needs to be another intermediate layer between  `struct video_buffer'
	 *       and `struct video_gfx': `struct video_surface'. This layer then defines all
	 *       the runtime changeable attributes of a video buffer:
	 * >> struct video_palette *vs_palette;  // [0..1] Color palette for use with `vs_buffer' (keep at offset=0, for faster pixel<=>color conversion)
	 * >> struct video_buffer  *vs_buffer;   // [1..1][const] Linked buffer
	 * >> video_pixel_t         vs_colorkey; // [valid_if(vs_flags & VIDEO_SURFACE_F_COLORKEY)] Color key
	 * >> uint32_t              vs_flags;    // Set of `VIDEO_SURFACE_F_*'
	 *
	 * This structure is  managed by the  user on the  stack, just like  `video_gfx',
	 * and  as a matter of fact, `video_gfx'  should just contain an inlined instance
	 * of  this structure. This  structure is then passed  to codecs for pixel2color,
	 * instead of `struct video_format', preventing the need for an extra indirection
	 * when GFX wants  to access pixel  data, and also  allowing `vs_flags' above  to
	 * also contain `vx_flags' of the GFX context.
	 *
	 * This way, `struct video_buffer' can easily define [const] default values for
	 * stuff like palette or color-key, while still allowing the user to operate on
	 * the buffer using non-default values for all of these.
	 *
	 * When the palette/color-key of the `video_surface' embedded within `video_gfx'
	 * is changed, `VIDEO_GFX_UPDATE_PALETTE' and `VIDEO_GFX_UPDATE_COLOR_KEY'  must
	 * be used to propagate such changes to the driver.
	 */
	video_color_t        vx_colorkey; /* [const] Transparent color key (or any color with alpha=0 when disabled). */
#define _VIDEO_GFX_N_DRIVER 20
	void *_vx_driver[_VIDEO_GFX_N_DRIVER]; /* [?..?] Driver-specific graphics data. */

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

	/* Same as `fill', but do so via gradient with colors[y][x] being
	 * used  to essentially do a VIDEO_GFX_F_LINEAR stretch-blit into
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
	                                video_color_t const __bg_fg_colors[2],
	                                struct video_bitmask const *__restrict __bm) const {
		video_gfx_absfillmask(this, __x, __y, __size_x, __size_y, __bg_fg_colors, __bm);
	}

	/* Same as `vgfo_fillmask()', however perform the blit while up-scaling the given bitmask. */
	__CXX_CLASSMEMBER void fillstretchmask(video_offset_t __dst_x, video_offset_t __dst_y,
	                                       video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                       video_color_t const __bg_fg_colors[2],
	                                       video_dim_t __src_size_x, video_dim_t __src_size_y,
	                                       struct video_bitmask const *__restrict __bm) const {
		video_gfx_absfillstretchmask(this, __dst_x, __dst_y, __dst_size_x, __dst_size_y,
		                             __bg_fg_colors, __src_size_x, __src_size_y, __bm);
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
