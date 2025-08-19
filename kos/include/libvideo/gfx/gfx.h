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

#include <__crt.h> /* __FILE */
#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>
#include <kos/anno.h>

#include "../color.h"
#include "../types.h"
#include "blend.h" /* gfx_blendmode_t */
#include "gfx-flags.h"
#include "surface-defs.h"

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

#ifndef __INTELLISENSE__
#include "../crect.h"
#include "../rect.h"
#include "buffer.h"
#include "codec/codec.h"
#include "codec/palette.h"
#endif /* !__INTELLISENSE__ */

/* Flags for `video_gfx_update()' */
#define VIDEO_GFX_UPDATE_NOTHING  0 /* Nothing was changed */
#define VIDEO_GFX_UPDATE_BLEND    1 /* `struct video_gfx::vg_blend' might have been changed */
#define VIDEO_GFX_UPDATE_FLAGS    2 /* `struct video_gfx::vg_surf.vs_flags' might have been changed */
#define VIDEO_GFX_UPDATE_COLORKEY 4 /* `struct video_gfx::vg_surf.vs_colorkey' might have been changed, and `VIDEO_GFX_F_COLORKEY' is enabled */
#define VIDEO_GFX_UPDATE_PALETTE  8 /* `struct video_gfx::vg_surf.vs_pal' might have been changed */
#define VIDEO_GFX_UPDATE_ALL     \
	(VIDEO_GFX_UPDATE_BLEND |    \
	 VIDEO_GFX_UPDATE_FLAGS |    \
	 VIDEO_GFX_UPDATE_COLORKEY | \
	 VIDEO_GFX_UPDATE_PALETTE)


/* Possible values for `video_gfx_fillpoly()::method' */
#define VIDEO_GFX_FILLPOLY_METHOD_EVEN_ODD 0 /* Fill pixels of self-intersecting polygons where "(N_EDGES & 1) != 0" */
#define VIDEO_GFX_FILLPOLY_METHOD_NON_ZERO 1 /* Fill pixels of self-intersecting polygons where "N_EDGES > 0" */
#define VIDEO_GFX_FILLPOLY_METHOD_COUNT    2 /* # of polygon fill methods */

#ifdef __CC__
__DECL_BEGIN

struct video_buffer;
struct video_gfxclip;
struct video_gfx;
struct video_rect;
struct video_crect;
struct video_blitter;
struct video_blitter3;
struct video_regionlock;
struct video_polygon;

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
	 * >>     video_color_t b = gfx_blendcolors(d, s, __ctx->vbt3_rddst->vg_blend); // Use blending mode of "vbt3_rddst" here
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

	/* Fill an area described by a polygon with a solid color. */
	__ATTR_IN_T(1) __ATTR_NONNULL((4)) void
	(LIBVIDEO_GFX_CC *vgfo_fillpoly)(struct video_gfx const *__restrict __self,
	                                 video_offset_t __x, video_offset_t __y,
	                                 struct video_polygon *__restrict __poly,
	                                 video_color_t __color, unsigned int __method);

	/* Outline an area with a rectangle. */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *vgfo_rect)(struct video_gfx const *__restrict __self,
	                             video_offset_t __x, video_offset_t __y,
	                             video_dim_t __size_x, video_dim_t __size_y,
	                             video_color_t __color);

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

//TODO:	/* Same as operators above, but using "video_color64_t" instead of "video_color_t" */
//TODO:	__ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_IN_T(1) video_color64_t
//TODO:	(LIBVIDEO_GFX_CC *vgfo_getcolor64)(struct video_gfx const *__restrict __self,
//TODO:	                                   video_offset_t __x, video_offset_t __y);
//TODO:	__ATTR_IN_T(1) void
//TODO:	(LIBVIDEO_GFX_CC *vgfo_putcolor64)(struct video_gfx const *__restrict __self,
//TODO:	                                   video_offset_t __x, video_offset_t __y,
//TODO:	                                   video_color64_t __color);
//TODO:	__ATTR_IN_T(1) void
//TODO:	(LIBVIDEO_GFX_CC *vgfo_line64)(struct video_gfx const *__restrict __self,
//TODO:	                               video_offset_t __x1, video_offset_t __y1,
//TODO:	                               video_offset_t __x2, video_offset_t __y2,
//TODO:	                               video_color64_t __color);
//TODO:	__ATTR_IN_T(1) void
//TODO:	(LIBVIDEO_GFX_CC *vgfo_hline64)(struct video_gfx const *__restrict __self,
//TODO:	                                video_offset_t __x, video_offset_t __y,
//TODO:	                                video_dim_t __length, video_color64_t __color);
//TODO:	__ATTR_IN_T(1) void
//TODO:	(LIBVIDEO_GFX_CC *vgfo_vline64)(struct video_gfx const *__restrict __self,
//TODO:	                                video_offset_t __x, video_offset_t __y,
//TODO:	                                video_dim_t __length, video_color64_t __color);
//TODO:	__ATTR_IN_T(1) void
//TODO:	(LIBVIDEO_GFX_CC *vgfo_fill64)(struct video_gfx const *__restrict __self,
//TODO:	                               video_offset_t __x, video_offset_t __y,
//TODO:	                               video_dim_t __size_x, video_dim_t __size_y,
//TODO:	                               video_color64_t __color);
//TODO:	__ATTR_IN_T(1) void
//TODO:	(LIBVIDEO_GFX_CC *vgfo_rect64)(struct video_gfx const *__restrict __self,
//TODO:	                               video_offset_t __x, video_offset_t __y,
//TODO:	                               video_dim_t __size_x, video_dim_t __size_y,
//TODO:	                               video_color64_t __color);
//TODO:	__ATTR_IN_T(1) __ATTR_IN_T(6) void
//TODO:	(LIBVIDEO_GFX_CC *vgfo_gradient64)(struct video_gfx const *__restrict __self,
//TODO:	                                   video_offset_t __x, video_offset_t __y,
//TODO:	                                   video_dim_t __size_x, video_dim_t __size_y,
//TODO:	                                   video_color64_t const __colors[2][2]);
//TODO:	__ATTR_IN_T(1) void
//TODO:	(LIBVIDEO_GFX_CC *vgfo_hgradient64)(struct video_gfx const *__restrict __self,
//TODO:	                                    video_offset_t __x, video_offset_t __y,
//TODO:	                                    video_dim_t __size_x, video_dim_t __size_y,
//TODO:	                                    video_color64_t __locolor, video_color64_t __hicolor);
//TODO:	__ATTR_IN_T(1) void
//TODO:	(LIBVIDEO_GFX_CC *vgfo_vgradient64)(struct video_gfx const *__restrict __self,
//TODO:	                                    video_offset_t __x, video_offset_t __y,
//TODO:	                                    video_dim_t __size_x, video_dim_t __size_y,
//TODO:	                                    video_color64_t __locolor, video_color64_t __hicolor);

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



/* Wrapper  around `video_buffer_region()' that produces a buffer which,
 * when used to instantiate a GFX context, replicates an effective Clip-
 * and I/O-Rect that matches `__self', as well as has its buffer  format
 * initialized to reflect the current  palette, flags and color key,  as
 * set in `__self' at the time of this function being called.
 *
 * CAUTION: Just like with `video_buffer_region()', pixel  data
 *          of the returned buffer will be rotated in GFX-only!
 *
 * @return: * : The video buffer representing a wrapped and const-i-fied copy of `__self'
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=*] Failed to create wrapper for some other reason */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_GFX_ASBUFFER)(struct video_gfx const *__restrict __self);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_gfx_asbuffer(struct video_gfx const *__restrict __self);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */




/* Same as `video_surface_*save', but save pixel data from  the
 * Clip Rect of `__self'. Values written for pixels outside the
 * I/O Rect of `__self'  are format-specific, but those  pixels
 * are probably going to be either black, or transparent.
 *
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) int
(LIBVIDEO_GFX_CC *PVIDEO_GFX_FSAVE)(struct video_gfx const *__self, char const *__format,
                                    __FILE *__restrict __fp, char const *__options);
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) int
(LIBVIDEO_GFX_CC *PVIDEO_GFX_FDSAVE)(struct video_gfx const *__self, char const *__format,
                                     __fd_t __fd, char const *__options);
typedef /*__ATTR_WUNUSED_T*/ __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) int
(LIBVIDEO_GFX_CC *PVIDEO_GFX_SAVE)(struct video_gfx const *__self, char const *__filename,
                                   char const *__options);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_NONNULL((2)) int LIBVIDEO_GFX_CC
video_gfx_fsave(struct video_gfx const *__self, char const *__format,
                __FILE *__restrict __fp, char const *__options);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_NONNULL((2)) int LIBVIDEO_GFX_CC
video_gfx_fdsave(struct video_gfx const *__self, char const *__format,
                 __fd_t __fd, char const *__options);
LIBVIDEO_GFX_DECL /*__ATTR_WUNUSED*/ __ATTR_IN(1) __ATTR_NONNULL((2)) int LIBVIDEO_GFX_CC
video_gfx_save(struct video_gfx const *__self, char const *__filename,
               char const *__options);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Acquire read/write-locks to the Clip-  or I/O Rects of  `__self'.
 * Note that these functions simply wrap `video_buffer_*lockregion',
 * meaning that rotation/mirroring flags of `__self' are ignored.
 *
 * The locks created by these functions must be released via:
 * >> video_gfx_unlock(__self, __lock);
 * @return: 0 : Success
 * @return: -1: [errno=ERANGE] video_gfx_*lockclip: Clip rect does not cleanly map to buffer
 * @return: -1: [errno=*] Video lock cannot be acquired */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_OUT_T(2) int
(LIBVIDEO_GFX_FCC *PVIDEO_GFX_RLOCKCLIP)(struct video_gfx const *__restrict __self,
                                         /*out*/ struct video_regionlock *__restrict __lock);
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_OUT_T(2) int
(LIBVIDEO_GFX_FCC *PVIDEO_GFX_WLOCKCLIP)(struct video_gfx const *__restrict __self,
                                         /*out*/ struct video_regionlock *__restrict __lock);
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_OUT_T(2) int
(LIBVIDEO_GFX_FCC *PVIDEO_GFX_RLOCKIO)(struct video_gfx const *__restrict __self,
                                       /*out*/ struct video_regionlock *__restrict __lock);
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_OUT_T(2) int
(LIBVIDEO_GFX_FCC *PVIDEO_GFX_WLOCKIO)(struct video_gfx const *__restrict __self,
                                       /*out*/ struct video_regionlock *__restrict __lock);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) int LIBVIDEO_GFX_FCC
video_gfx_rlockclip(struct video_gfx const *__restrict __self,
                    /*out*/ struct video_regionlock *__restrict __lock);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) int LIBVIDEO_GFX_FCC
video_gfx_wlockclip(struct video_gfx const *__restrict __self,
                    /*out*/ struct video_regionlock *__restrict __lock);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) int LIBVIDEO_GFX_FCC
video_gfx_rlockio(struct video_gfx const *__restrict __self,
                  /*out*/ struct video_regionlock *__restrict __lock);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) int LIBVIDEO_GFX_FCC
video_gfx_wlockio(struct video_gfx const *__restrict __self,
                  /*out*/ struct video_regionlock *__restrict __lock);
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
typedef struct video_gfxclip video_gfx_clipinfo_t;


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

/* Update operators of `__self' after certain behavioral flags were changed:
 * - VIDEO_GFX_UPDATE_BLEND:    `__self->vg_blend' may have changed
 * - VIDEO_GFX_UPDATE_FLAGS:    `__self->vg_surf.vs_flags' may have changed
 * - VIDEO_GFX_UPDATE_COLORKEY: `__self->vg_surf.vs_colorkey' may have changed
 * - VIDEO_GFX_UPDATE_PALETTE:  `__self->vg_surf.vs_pal' may have changed
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
extern __ATTR_PURE __ATTR_IN(1) video_pixel_t video_gfx_getcolorkey(struct video_gfx const *__restrict __self);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *video_gfx_setcolorkey(struct video_gfx *__restrict __self, video_pixel_t __colorkey);

#ifdef __cplusplus
extern "C++" {
extern __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct video_surface *video_gfx_assurface(struct video_gfx *__restrict __self);
extern __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct video_surface const *video_gfx_assurface(struct video_gfx const *__restrict __self);
} /* extern "C++" */
#else /* __cplusplus */
#define video_gfx_assurface(self) (&(self)->vg_surf)
#endif /* !__cplusplus */
extern __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct video_domain const *video_gfx_getdomain(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct video_codec *video_gfx_getcodec(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct video_buffer *video_gfx_getbuffer(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_gfx_hasobjpalette(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) struct video_palette *video_gfx_getpalette(struct video_gfx const *__restrict __self);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) __ATTR_NONNULL((2)) struct video_gfx *video_gfx_setpalette(struct video_gfx *__restrict __self, struct video_palette *__palette, __BOOL __isobj);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_gfx_hascolorkey(struct video_gfx const *__restrict __self);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *video_gfx_enablecolorkey(struct video_gfx *__restrict __self, video_pixel_t __colorkey);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *video_gfx_disablecolorkey(struct video_gfx *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) struct video_palette *video_gfx_getdefaultpalette(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_gfx_flag_t video_gfx_getdefaultflags(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_pixel_t video_gfx_getdefaultcolorkey(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_gfx_hasdefaultcolorkey(struct video_gfx const *__restrict __self);

/* Return a lower bound for the # of colors that a palette linked to this GFX has to
 * have. If the GFX doesn't make use  of palettes, this returns an undefined  value. */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_pixel_t
video_gfx_getpalcolorcount(struct video_gfx const *__restrict __self);

/* Assign `__colors' to-be used as palette for `__self'. The caller must ensure that this array
 * of colors remains allocated until a different palette is assigned, or the gfx (and any video
 * buffer created from it) is disposed.
 *
 * Same as:
 * >> video_gfx_setpalette(__self, video_palette_fromcolors(__colors), false);
 *
 * CAUTION: By assigning a non-object-based color palette, GFX operations will be drastically
 *          slower, since the palette will have to be re-transmitted to the GPU or the window
 *          manager with every GFX operation. */
extern __ATTR_RETNONNULL __ATTR_INOUT(1) __ATTR_NONNULL((2)) struct video_gfx *
video_gfx_setpalcolors(struct video_gfx *__restrict __self,
                       video_color_t const __colors[]);

/* Return a pointer to the palette colors used by `__self', or `NULL' if no palette is being used. */
extern __ATTR_WUNUSED __ATTR_IN(1) video_color_t const *
video_gfx_getpalcolors(struct video_gfx const *__restrict __self);


/* Same as above, but don't automatically call `video_gfx_update()' (the caller is responsible for doing so) */
extern __ATTR_INOUT(1) void _video_gfx_setblend(struct video_gfx *__restrict __self, gfx_blendmode_t __mode);
extern __ATTR_INOUT(1) void _video_gfx_setflags(struct video_gfx *__restrict __self, video_gfx_flag_t __flags);
extern __ATTR_INOUT(1) void _video_gfx_toggleflags(struct video_gfx *__restrict __self, video_gfx_flag_t __flags);
extern __ATTR_INOUT(1) void _video_gfx_enableflags(struct video_gfx *__restrict __self, video_gfx_flag_t __flags);
extern __ATTR_INOUT(1) void _video_gfx_disableflags(struct video_gfx *__restrict __self, video_gfx_flag_t __flags);
extern __ATTR_INOUT(1) void _video_gfx_setcolorkey(struct video_gfx *__restrict __self, video_pixel_t __colorkey);
extern __ATTR_INOUT(1) __ATTR_NONNULL((2)) struct video_gfx *_video_gfx_setpalette(struct video_gfx *__restrict __self, struct video_palette *__palette, __BOOL __isobj);
extern __ATTR_INOUT(1) struct video_gfx *_video_gfx_enablecolorkey(struct video_gfx *__restrict __self, video_pixel_t __colorkey);
extern __ATTR_INOUT(1) struct video_gfx *_video_gfx_disablecolorkey(struct video_gfx *__restrict __self);
extern __ATTR_INOUT(1) __ATTR_NONNULL((2)) struct video_gfx *_video_gfx_setpalcolors(struct video_gfx *__restrict __self, video_color_t const __colors[]);


/* Release video locks previously acquired by `video_gfx_(r|w)lock(clip|io)' */
extern __ATTR_IN(1) __ATTR_NONNULL((2)) void
video_gfx_unlock(struct video_gfx const *__restrict __self,
                 struct video_regionlock *__restrict __lock);


/* Helpers for reading the coords of the GFX's Clip- / I/O-Rect, relative to the
 * GFX context's buffer/surface,  AFTER being  swapped by  `VIDEO_GFX_F_XYSWAP'.
 *
 * CAUTION: Please note that  the GFX's effective  `video_buffer' may NOT  actually
 *          be  the one that  was used to create  the GFX in  the first place. Some
 *          types of video buffers wrap others, and automatically unwrap themselves
 *          when  creating a GFX  context. In these cases,  the Clip- and I/O-Rects
 *          of the  produced GFX  have been  adjusted to  reference the  sub-region
 *          described by the wrapping buffer.
 *
 * We intentionally don't provide you  with setters for these; you  should
 * always use `video_gfx_clip()' to adjust your GFX's Clip- and I/O-Rects. */

/* CLIP: Clip-Rect coords, relative to surface */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_gfx_getclipxmin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_gfx_getclipymin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_gfx_getclipxend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_gfx_getclipyend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_gfx_getclipxdim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_gfx_getclipydim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) void video_gfx_getcliprect(struct video_gfx const *__restrict __self, struct video_rect *__restrict __result);

/* IO: I/O-Rect coords, relative to surface */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t video_gfx_getioxmin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t video_gfx_getioymin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t video_gfx_getioxend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t video_gfx_getioyend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_gfx_getioxdim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_gfx_getioydim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) void video_gfx_getiorect(struct video_gfx const *__restrict __self, struct video_crect *__restrict __result);

/* CLIPIO: I/O Rect coords, relative to Clip-Rect (may be useful, since I/O-Rect is always contains within Clip-Rect) */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t video_gfx_getclipioxmin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t video_gfx_getclipioymin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t video_gfx_getclipioxend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t video_gfx_getclipioyend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_gfx_getclipioxdim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_gfx_getclipioydim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) void video_gfx_getclipiorect(struct video_gfx const *__restrict __self, struct video_crect *__restrict __result);

/* IOCLIP: Clip Rect coords, relative to I/O-Rect (note that XMIN/YMIN here is
 * always `<= 0', since the I/O-Rect is always contained within the Clip-Rect) */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_gfx_getioclipxmin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_gfx_getioclipymin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_gfx_getioclipxend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_gfx_getioclipyend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_gfx_getioclipxdim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_gfx_getioclipydim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) void video_gfx_getiocliprect(struct video_gfx const *__restrict __self, struct video_rect *__restrict __result);

/* SURF: Surface coords, relative to itself (as such there is no XMIN/YMIN getter, since
 *       those are always be 0, and as a matter of fact: `video_gfx_getsurfrect()'  will
 *       just write `0' for x/y-min into the given rect) */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_gfx_getsurfxdim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_gfx_getsurfydim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) void video_gfx_getsurfrect(struct video_gfx const *__restrict __self, struct video_crect *__restrict __result);

/* _foo: Same as "foo" above, but the `VIDEO_GFX_F_XYSWAP' flag is NOT applied */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t _video_gfx_getclipxmin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t _video_gfx_getclipymin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t _video_gfx_getclipxend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t _video_gfx_getclipyend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t _video_gfx_getclipxdim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t _video_gfx_getclipydim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) void _video_gfx_getcliprect(struct video_gfx const *__restrict __self, struct video_rect *__restrict __result);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t _video_gfx_getioxmin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t _video_gfx_getioymin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t _video_gfx_getioxend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t _video_gfx_getioyend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t _video_gfx_getioxdim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t _video_gfx_getioydim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) void _video_gfx_getiorect(struct video_gfx const *__restrict __self, struct video_crect *__restrict __result);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t _video_gfx_getclipioxmin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t _video_gfx_getclipioymin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t _video_gfx_getclipioxend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t _video_gfx_getclipioyend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t _video_gfx_getclipioxdim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t _video_gfx_getclipioydim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) void _video_gfx_getclipiorect(struct video_gfx const *__restrict __self, struct video_crect *__restrict __result);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t _video_gfx_getioclipxmin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t _video_gfx_getioclipymin(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t _video_gfx_getioclipxend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t _video_gfx_getioclipyend(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t _video_gfx_getioclipxdim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t _video_gfx_getioclipydim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) void _video_gfx_getiocliprect(struct video_gfx const *__restrict __self, struct video_rect *__restrict __result);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t _video_gfx_getsurfxdim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t _video_gfx_getsurfydim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) void _video_gfx_getsurfrect(struct video_gfx const *__restrict __self, struct video_crect *__restrict __result);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t _video_gfx_getxdim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t _video_gfx_getydim(struct video_gfx const *__restrict __self);

/* Check if the GFX's Clip- / I/O-Rect / Surface Rect are equal one-another:
 * - video_gfx_isioclip:   video_gfx_getcliprect() == video_gfx_getiorect()
 * - video_gfx_issurfclip: video_gfx_getcliprect() == video_gfx_getsurfrect()
 * - video_gfx_issurfio:   video_gfx_getiorect() == video_gfx_getsurfrect() (implies video_gfx_isioclip() && video_gfx_issurfclip()) */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_gfx_isioclip(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_gfx_issurfio(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_gfx_issurfclip(struct video_gfx const *__restrict __self);

/* Check if different rects of `__self' are empty. Note the following implications:
 * - `video_gfx_issurfempty()' implies `video_gfx_isioempty()'
 * - `video_gfx_isclipempty()' implies `video_gfx_isioempty()' */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_gfx_isioempty(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_gfx_isclipempty(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_gfx_issurfempty(struct video_gfx const *__restrict __self);

/* Return the API-visible Clip Rect size in X or Y.
 * These are simply aliases for `video_gfx_getclipxdim()' and `video_gfx_getclipydim()' */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_gfx_getxdim(struct video_gfx const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_gfx_getydim(struct video_gfx const *__restrict __self);

/* Backup/restore the current Clip Rect of `self' */
extern __ATTR_IN(1) __ATTR_OUT(2) void
video_gfx_saveclip(struct video_gfx const *__restrict self,
                   video_gfx_clipinfo_t *__restrict backup);
extern __ATTR_IN(2) __ATTR_OUT(1) void
video_gfx_loadclip(struct video_gfx *__restrict self,
                   video_gfx_clipinfo_t const *__restrict backup);


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

/* Fill an area described by a polygon with a solid color. */
extern __ATTR_IN(1) __ATTR_NONNULL((4)) void
video_gfx_fillpoly(struct video_gfx const *__restrict __self,
                   video_offset_t __x, video_offset_t __y,
                   struct video_polygon *__restrict __poly,
                   video_color_t __color, unsigned int __method);

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

#define __video_gfx_xyswap(self, regular, swapped) \
	(__likely(!(video_gfx_getflags(self) & VIDEO_GFX_F_XYSWAP)) ? (regular) : (swapped))

#define video_gfx_saveclip(self, backup) (void)(*(backup) = (self)->vg_clip)
#define video_gfx_loadclip(self, backup) (void)((self)->vg_clip = *(backup))
#define video_gfx_getblend(self)      ((self)->vg_blend)
#define video_gfx_getflags(self)      ((self)->vg_surf.vs_flags)
#define video_gfx_getxdim(self)       (video_dim_t)(self)->vg_clip.vgc_cxdim
#define video_gfx_getydim(self)       (video_dim_t)(self)->vg_clip.vgc_cydim
#define video_gfx_getclipxmin(self)   (video_offset_t)(self)->vg_clip.vgc_cxoff
#define video_gfx_getclipymin(self)   (video_offset_t)(self)->vg_clip.vgc_cyoff
#define video_gfx_getclipxend(self)   (video_offset_t)((self)->vg_clip.vgc_cxoff + (self)->vg_clip.vgc_cxdim)
#define video_gfx_getclipyend(self)   (video_offset_t)((self)->vg_clip.vgc_cyoff + (self)->vg_clip.vgc_cydim)
#define video_gfx_getclipxdim(self)   (video_dim_t)(self)->vg_clip.vgc_cxdim
#define video_gfx_getclipydim(self)   (video_dim_t)(self)->vg_clip.vgc_cydim
#define video_gfx_getioxmin(self)     (video_coord_t)(self)->vg_clip.vgc_bxmin
#define video_gfx_getioymin(self)     (video_coord_t)(self)->vg_clip.vgc_bymin
#define video_gfx_getioxend(self)     (video_coord_t)(self)->vg_clip.vgc_bxend
#define video_gfx_getioyend(self)     (video_coord_t)(self)->vg_clip.vgc_byend
#define video_gfx_getioxdim(self)     (video_dim_t)((self)->vg_clip.vgc_bxend - (self)->vg_clip.vgc_bxmin)
#define video_gfx_getioydim(self)     (video_dim_t)((self)->vg_clip.vgc_byend - (self)->vg_clip.vgc_bymin)
#define video_gfx_getclipioxmin(self) (video_coord_t)((self)->vg_clip.vgc_bxmin - (self)->vg_clip.vgc_cxoff)
#define video_gfx_getclipioymin(self) (video_coord_t)((self)->vg_clip.vgc_bymin - (self)->vg_clip.vgc_cyoff)
#define video_gfx_getclipioxend(self) (video_coord_t)((self)->vg_clip.vgc_bxend - (self)->vg_clip.vgc_cxoff)
#define video_gfx_getclipioyend(self) (video_coord_t)((self)->vg_clip.vgc_byend - (self)->vg_clip.vgc_cyoff)
#define video_gfx_getclipioxdim(self) video_gfx_getioxdim(self)
#define video_gfx_getclipioydim(self) video_gfx_getioydim(self)
#define video_gfx_getioclipxmin(self) ((self)->vg_clip.vgc_cxoff - (video_offset_t)(self)->vg_clip.vgc_bxmin)
#define video_gfx_getioclipymin(self) ((self)->vg_clip.vgc_cyoff - (video_offset_t)(self)->vg_clip.vgc_bymin)
#define video_gfx_getioclipxend(self) ((self)->vg_clip.vgc_cxoff - (video_offset_t)(self)->vg_clip.vgc_bxend)
#define video_gfx_getioclipyend(self) ((self)->vg_clip.vgc_cxoff - (video_offset_t)(self)->vg_clip.vgc_byend)
#define video_gfx_getioclipxdim(self) (video_dim_t)(self)->vg_clip.vgc_cxdim
#define video_gfx_getioclipydim(self) (video_dim_t)(self)->vg_clip.vgc_cydim
#define video_gfx_getcliprect(self, result)                 \
	(void)((result)->vr_xmin = video_gfx_getclipxmin(self), \
	       (result)->vr_ymin = video_gfx_getclipymin(self), \
	       (result)->vr_xdim = video_gfx_getclipxdim(self), \
	       (result)->vr_ydim = video_gfx_getclipydim(self))
#define video_gfx_getiorect(self, result)                  \
	(void)((result)->vcr_xmin = video_gfx_getioxmin(self), \
	       (result)->vcr_ymin = video_gfx_getioymin(self), \
	       (result)->vcr_xdim = video_gfx_getioxdim(self), \
	       (result)->vcr_ydim = video_gfx_getioydim(self))
#define video_gfx_getclipiorect(self, result)                  \
	(void)((result)->vcr_xmin = video_gfx_getclipioxmin(self), \
	       (result)->vcr_ymin = video_gfx_getclipioymin(self), \
	       (result)->vcr_xdim = video_gfx_getclipioxdim(self), \
	       (result)->vcr_ydim = video_gfx_getclipioydim(self))
#define video_gfx_getiocliprect(self, result)                 \
	(void)((result)->vr_xmin = video_gfx_getioclipxmin(self), \
	       (result)->vr_ymin = video_gfx_getioclipymin(self), \
	       (result)->vr_xdim = video_gfx_getioclipxdim(self), \
	       (result)->vr_ydim = video_gfx_getioclipydim(self))
#define _video_gfx_getsurfxdim(self) video_buffer_getxdim(video_gfx_getbuffer(self))
#define _video_gfx_getsurfydim(self) video_buffer_getydim(video_gfx_getbuffer(self))
#define _video_gfx_getsurfrect(self, result)                  \
	(void)((result)->vcr_xmin = (result)->vcr_ymin = 0,         \
	       (result)->vcr_xdim = _video_gfx_getsurfxdim(self), \
	       (result)->vcr_ydim = _video_gfx_getsurfydim(self))
#define video_gfx_getsurfxdim(self) __video_gfx_xyswap(self, _video_gfx_getsurfxdim(self), _video_gfx_getsurfydim(self))
#define video_gfx_getsurfydim(self) __video_gfx_xyswap(self, _video_gfx_getsurfydim(self), _video_gfx_getsurfxdim(self))
#define video_gfx_getsurfrect(self, result)                  \
	(void)((result)->vcr_xmin = (result)->vcr_ymin = 0,      \
	       (result)->vcr_xdim = video_gfx_getsurfxdim(self), \
	       (result)->vcr_ydim = video_gfx_getsurfydim(self))
#define video_gfx_isioclip(self)                                                        \
	((self)->vg_clip.vgc_bxmin == (video_coord_t)(self)->vg_clip.vgc_cxoff &&             \
	 (self)->vg_clip.vgc_bymin == (video_coord_t)(self)->vg_clip.vgc_cyoff &&             \
	 (self)->vg_clip.vgc_bxend == (self)->vg_clip.vgc_bxmin + (self)->vg_clip.vgc_cxdim && \
	 (self)->vg_clip.vgc_byend == (self)->vg_clip.vgc_bymin + (self)->vg_clip.vgc_cydim)
#define video_gfx_issurfclip(self)                                     \
	((self)->vg_clip.vgc_cxoff == 0 && (self)->vg_clip.vgc_cyoff == 0 && \
	 (self)->vg_clip.vgc_cxdim == video_gfx_getsurfxdim(self) &&        \
	 (self)->vg_clip.vgc_cydim == video_gfx_getsurfydim(self))
#define video_gfx_issurfio(self)                                       \
	((self)->vg_clip.vgc_bxmin == 0 && (self)->vg_clip.vgc_bymin == 0 && \
	 (self)->vg_clip.vgc_bxend == video_gfx_getsurfxdim(self) &&        \
	 (self)->vg_clip.vgc_byend == video_gfx_getsurfydim(self))
#define video_gfx_isioempty(self)   (!video_gfx_getioxdim(self) || !video_gfx_getioydim(self))
#define video_gfx_isclipempty(self) (!video_gfx_getclipxdim(self) || !video_gfx_getclipydim(self))
#define video_gfx_issurfempty(self) (!_video_gfx_getsurfxdim(self) || !_video_gfx_getsurfydim(self))
#define __video_gfx_getcliprect_xyswap(self, result)        \
	(void)((result)->vr_xmin = video_gfx_getclipymin(self), \
	       (result)->vr_ymin = video_gfx_getclipxmin(self), \
	       (result)->vr_xdim = video_gfx_getclipydim(self), \
	       (result)->vr_ydim = video_gfx_getclipxdim(self))
#define __video_gfx_getiorect_xyswap(self, result)         \
	(void)((result)->vcr_xmin = video_gfx_getioymin(self), \
	       (result)->vcr_ymin = video_gfx_getioxmin(self), \
	       (result)->vcr_xdim = video_gfx_getioydim(self), \
	       (result)->vcr_ydim = video_gfx_getioxdim(self))
#define __video_gfx_getclipiorect_xyswap(self, result)         \
	(void)((result)->vcr_xmin = video_gfx_getclipioymin(self), \
	       (result)->vcr_ymin = video_gfx_getclipioxmin(self), \
	       (result)->vcr_xdim = video_gfx_getclipioydim(self), \
	       (result)->vcr_ydim = video_gfx_getclipioxdim(self))
#define __video_gfx_getiocliprect_xyswap(self, result)        \
	(void)((result)->vr_xmin = video_gfx_getioclipymin(self), \
	       (result)->vr_ymin = video_gfx_getioclipxmin(self), \
	       (result)->vr_xdim = video_gfx_getioclipydim(self), \
	       (result)->vr_ydim = video_gfx_getioclipxdim(self))
#define _video_gfx_getclipxmin(self)   __video_gfx_xyswap(self, video_gfx_getclipxmin(self), video_gfx_getclipymin(self))
#define _video_gfx_getclipymin(self)   __video_gfx_xyswap(self, video_gfx_getclipymin(self), video_gfx_getclipxmin(self))
#define _video_gfx_getclipxend(self)   __video_gfx_xyswap(self, video_gfx_getclipxend(self), video_gfx_getclipyend(self))
#define _video_gfx_getclipyend(self)   __video_gfx_xyswap(self, video_gfx_getclipyend(self), video_gfx_getclipxend(self))
#define _video_gfx_getclipxdim(self)   __video_gfx_xyswap(self, video_gfx_getclipxdim(self), video_gfx_getclipydim(self))
#define _video_gfx_getclipydim(self)   __video_gfx_xyswap(self, video_gfx_getclipydim(self), video_gfx_getclipxdim(self))
#define _video_gfx_getioxmin(self)     __video_gfx_xyswap(self, video_gfx_getioxmin(self), video_gfx_getioymin(self))
#define _video_gfx_getioymin(self)     __video_gfx_xyswap(self, video_gfx_getioymin(self), video_gfx_getioxmin(self))
#define _video_gfx_getioxend(self)     __video_gfx_xyswap(self, video_gfx_getioxend(self), video_gfx_getioyend(self))
#define _video_gfx_getioyend(self)     __video_gfx_xyswap(self, video_gfx_getioyend(self), video_gfx_getioxend(self))
#define _video_gfx_getioxdim(self)     __video_gfx_xyswap(self, video_gfx_getioxdim(self), video_gfx_getioydim(self))
#define _video_gfx_getioydim(self)     __video_gfx_xyswap(self, video_gfx_getioydim(self), video_gfx_getioxdim(self))
#define _video_gfx_getclipioxmin(self) __video_gfx_xyswap(self, video_gfx_getclipioxmin(self), video_gfx_getclipioymin(self))
#define _video_gfx_getclipioymin(self) __video_gfx_xyswap(self, video_gfx_getclipioymin(self), video_gfx_getclipioxmin(self))
#define _video_gfx_getclipioxend(self) __video_gfx_xyswap(self, video_gfx_getclipioxend(self), video_gfx_getclipioyend(self))
#define _video_gfx_getclipioyend(self) __video_gfx_xyswap(self, video_gfx_getclipioyend(self), video_gfx_getclipioxend(self))
#define _video_gfx_getclipioxdim(self) __video_gfx_xyswap(self, video_gfx_getclipioxdim(self), video_gfx_getclipioydim(self))
#define _video_gfx_getclipioydim(self) __video_gfx_xyswap(self, video_gfx_getclipioydim(self), video_gfx_getclipioxdim(self))
#define _video_gfx_getioclipxmin(self) __video_gfx_xyswap(self, video_gfx_getioclipxmin(self), video_gfx_getioclipymin(self))
#define _video_gfx_getioclipymin(self) __video_gfx_xyswap(self, video_gfx_getioclipymin(self), video_gfx_getioclipxmin(self))
#define _video_gfx_getioclipxend(self) __video_gfx_xyswap(self, video_gfx_getioclipxend(self), video_gfx_getioclipyend(self))
#define _video_gfx_getioclipyend(self) __video_gfx_xyswap(self, video_gfx_getioclipyend(self), video_gfx_getioclipxend(self))
#define _video_gfx_getioclipxdim(self) __video_gfx_xyswap(self, video_gfx_getioclipxdim(self), video_gfx_getioclipydim(self))
#define _video_gfx_getioclipydim(self) __video_gfx_xyswap(self, video_gfx_getioclipydim(self), video_gfx_getioclipxdim(self))
#define _video_gfx_getxdim(self)       __video_gfx_xyswap(self, video_gfx_getxdim(self), video_gfx_getydim(self))
#define _video_gfx_getydim(self)       __video_gfx_xyswap(self, video_gfx_getydim(self), video_gfx_getxdim(self))

#define _video_gfx_getcliprect(self, result)   __video_gfx_xyswap(self, video_gfx_getcliprect(self, result), __video_gfx_getcliprect_xyswap(self, result))
#define _video_gfx_getiorect(self, result)     __video_gfx_xyswap(self, video_gfx_getiorect(self, result), __video_gfx_getiorect_xyswap(self, result))
#define _video_gfx_getclipiorect(self, result) __video_gfx_xyswap(self, video_gfx_getclipiorect(self, result), __video_gfx_getclipiorect_xyswap(self, result))
#define _video_gfx_getiocliprect(self, result) __video_gfx_xyswap(self, video_gfx_getiocliprect(self, result), __video_gfx_getiocliprect_xyswap(self, result))

#define video_gfx_update(self, what) \
	(*(self)->vg_surf.vs_buffer->vb_ops->vi_updategfx)(self, what)
#define video_gfx_clip(self, clip_x, clip_y, size_x, size_y) \
	(*(self)->vg_clip.vgc_ops->vgfo_clip)(self, clip_x, clip_y, size_x, size_y)
#define video_gfx_cliprect(self, rect) \
	video_gfx_clip(self, (rect)->vr_xmin, (rect)->vr_ymin, (rect)->vr_xdim, (rect)->vr_ydim)
#define video_gfx_offset2coord(self, x, y, coords) \
	(*(self)->vg_clip.vgc_ops->vgfo_offset2coord)(self, x, y, coords)
#define video_gfx_coord2offset(self, x, y, offsets) \
	(*(self)->vg_clip.vgc_ops->vgfo_coord2offset)(self, x, y, offsets)
#define video_gfx_getcolorkey(self)            ((self)->vg_surf.vs_colorkey)
#define video_gfx_setblend(self, mode)         ((self)->vg_blend = (mode), video_gfx_update(self, VIDEO_GFX_UPDATE_BLEND))
#define video_gfx_setflags(self, flags)        ((self)->vg_surf.vs_flags = (flags), video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS))
#define video_gfx_toggleflags(self, flags)     ((self)->vg_surf.vs_flags ^= (flags), video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS))
#define video_gfx_enableflags(self, flags)     ((self)->vg_surf.vs_flags |= (flags), video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS))
#define video_gfx_disableflags(self, flags)    ((self)->vg_surf.vs_flags &= ~(flags), video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS))
#define video_gfx_setcolorkey(self, colorkey)  ((self)->vg_surf.vs_colorkey = (colorkey), video_gfx_update(self, VIDEO_GFX_UPDATE_COLORKEY))
#define _video_gfx_setblend(self, mode)        (void)((self)->vg_blend = (mode))
#define _video_gfx_setflags(self, flags)       (void)((self)->vg_surf.vs_flags = (flags))
#define _video_gfx_toggleflags(self, flags)    (void)((self)->vg_surf.vs_flags ^= (flags))
#define _video_gfx_enableflags(self, flags)    (void)((self)->vg_surf.vs_flags |= (flags))
#define _video_gfx_disableflags(self, flags)   (void)((self)->vg_surf.vs_flags &= ~(flags))
#define _video_gfx_setcolorkey(self, colorkey) (void)((self)->vg_surf.vs_colorkey = (colorkey))
#define _video_gfx_setpalette(self, palette, isobj)                                      \
	(void)((self)->vg_surf.vs_pal   = (palette),                                         \
	       (self)->vg_surf.vs_flags = ((self)->vg_surf.vs_flags & ~VIDEO_GFX_F_PALOBJ) | \
	                                  ((isobj) ? VIDEO_GFX_F_PALOBJ : 0))
#define _video_gfx_enablecolorkey(self, colorkey)            \
	(void)((self)->vg_surf.vs_flags |= VIDEO_GFX_F_COLORKEY, \
	       (self)->vg_surf.vs_colorkey = (colorkey))
#define _video_gfx_disablecolorkey(self) _video_gfx_disableflags(self, VIDEO_GFX_UPDATE_COLORKEY)
#define _video_gfx_setpalcolors(self, colors)                         \
	(void)((self)->vg_surf.vs_pal = video_palette_fromcolors(colors), \
	       (self)->vg_surf.vs_flags &= ~VIDEO_GFX_F_PALOBJ)
#define video_gfx_assurface(self)     (&(self)->vg_surf)
#define video_gfx_getdomain(self)     video_buffer_getdomain(video_gfx_getbuffer(self))
#define video_gfx_getcodec(self)      video_buffer_getcodec(video_gfx_getbuffer(self))
#define video_gfx_getbuffer(self)     (self)->vg_surf.vs_buffer
#define video_gfx_hasobjpalette(self) (((self)->vg_surf.vs_flags & VIDEO_GFX_F_PALOBJ) != 0)
#define video_gfx_getpalette(self)    (self)->vg_surf.vs_pal
#define video_gfx_setpalette(self, palette, isobj)                                 \
	((self)->vg_surf.vs_pal   = (palette),                                         \
	 (self)->vg_surf.vs_flags = ((self)->vg_surf.vs_flags & ~VIDEO_GFX_F_PALOBJ) | \
	                            ((isobj) ? VIDEO_GFX_F_PALOBJ : 0),                \
	 video_gfx_update(self, VIDEO_GFX_UPDATE_PALETTE))
#define video_gfx_hascolorkey(self) ((video_gfx_getflags(self) & VIDEO_GFX_F_COLORKEY) != 0)
#define video_gfx_enablecolorkey(self, colorkey)       \
	((self)->vg_surf.vs_flags |= VIDEO_GFX_F_COLORKEY, \
	 (self)->vg_surf.vs_colorkey = (colorkey),         \
	 video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS | VIDEO_GFX_UPDATE_COLORKEY))
#define video_gfx_disablecolorkey(self)    video_gfx_disableflags(self, VIDEO_GFX_UPDATE_COLORKEY)
#define video_gfx_getdefaultpalette(self)  ((self)->vg_surf.vs_buffer->vb_surf.vs_pal)
#define video_gfx_getdefaultflags(self)    ((self)->vg_surf.vs_buffer->vb_surf.vs_flags)
#define video_gfx_getdefaultcolorkey(self) ((self)->vg_surf.vs_buffer->vb_surf.vs_colorkey)
#define video_gfx_hasdefaultcolorkey(self) ((video_gfx_getdefaultflags(self) & VIDEO_GFX_F_COLORKEY) != 0)
#define video_gfx_getpalcolorcount(self)   video_codec_getpalcolors(video_gfx_getcodec(self))
#define video_gfx_setpalcolors(self, colors)                    \
	((self)->vg_surf.vs_pal = video_palette_fromcolors(colors), \
	 (self)->vg_surf.vs_flags &= ~VIDEO_GFX_F_PALOBJ,           \
	 video_gfx_update(self, VIDEO_GFX_UPDATE_PALETTE))
#define video_gfx_getpalcolors(self) video_palette_getcolors(video_gfx_getpalette(self))
#define video_gfx_unlock(self, lock) video_buffer_unlockregion(video_gfx_getbuffer(self), lock)
#define video_gfx_getcolor(self, x, y) \
	(*(self)->vg_clip.vgc_ops->vgfo_getcolor)(self, x, y)
#define video_gfx_putcolor(self, x, y, color) \
	(*(self)->vg_clip.vgc_ops->vgfo_putcolor)(self, x, y, color)
#define video_gfx_line(self, x1, y1, x2, y2, color) \
	(*(self)->vg_clip.vgc_ops->vgfo_line)(self, x1, y1, x2, y2, color)
#define video_gfx_hline(self, x, y, length, color) \
	(*(self)->vg_clip.vgc_ops->vgfo_hline)(self, x, y, length, color)
#define video_gfx_vline(self, x, y, length, color) \
	(*(self)->vg_clip.vgc_ops->vgfo_vline)(self, x, y, length, color)
#define video_gfx_fill(self, x, y, size_x, size_y, color) \
	(*(self)->vg_clip.vgc_ops->vgfo_fill)(self, x, y, size_x, size_y, color)
#define video_gfx_fillpoly(self, x, y, poly, color, method) \
	(*(self)->vg_clip.vgc_ops->vgfo_fillpoly)(self, x, y, poly, color, method)
#define video_gfx_fillall(self, color) \
	video_gfx_fill(self, 0, 0, VIDEO_DIM_MAX, VIDEO_DIM_MAX, color)
#define video_gfx_rect(self, x, y, size_x, size_y, color) \
	(*(self)->vg_clip.vgc_ops->vgfo_rect)(self, x, y, size_x, size_y, color)
#define video_gfx_gradient(self, x, y, size_x, size_y, colors) \
	(*(self)->vg_clip.vgc_ops->vgfo_gradient)(self, x, y, size_x, size_y, colors)
#define video_gfx_hgradient(self, x, y, size_x, size_y, locolor, hicolor) \
	(*(self)->vg_clip.vgc_ops->vgfo_hgradient)(self, x, y, size_x, size_y, locolor, hicolor)
#define video_gfx_vgradient(self, x, y, size_x, size_y, locolor, hicolor) \
	(*(self)->vg_clip.vgc_ops->vgfo_vgradient)(self, x, y, size_x, size_y, locolor, hicolor)
#define video_gfx_blitfrom(dst, src, ctx) \
	((ctx)->vbt_src = (src), (*((ctx)->vbt_dst = (dst))->vg_clip.vgc_ops->vgfo_blitfrom)(ctx))
#define video_gfx_blitto(src, dst, ctx) \
	((ctx)->vbt_src = (src), (*((ctx)->vbt_dst = (dst))->vg_clip.vgc_ops->vgfo_blitfrom)(ctx))
#define video_gfx_blitfrom3(wrdst, rddst, src, ctx)        \
	((ctx)->vbt3_src = (src), (ctx)->vbt3_rddst = (rddst), \
	 (*((ctx)->vbt3_wrdst = (wrdst))->vg_clip.vgc_ops->vgfo_blitfrom3)(ctx))
#define video_gfx_bitblit(dst, dst_x, dst_y, src, src_x, src_y, size_x, size_y) \
	(*(dst)->vg_clip.vgc_ops->vgfo_bitblit)(dst, dst_x, dst_y, src, src_x, src_y, size_x, size_y)
#define video_gfx_stretch(dst, dst_x, dst_y, dst_size_x, dst_size_y, src, src_x, src_y, src_size_x, src_size_y) \
	(*(dst)->vg_clip.vgc_ops->vgfo_stretch)(dst, dst_x, dst_y, dst_size_x, dst_size_y, src, src_x, src_y, src_size_x, src_size_y)
#define video_gfx_bitblit3(wrdst, wrdst_x, wrdst_y, rddst, rddst_x, rddst_y, src, src_x, src_y, size_x, size_y) \
	(*(wrdst)->vg_clip.vgc_ops->vgfo_bitblit3)(wrdst, wrdst_x, wrdst_y, rddst, rddst_x, rddst_y, src, src_x, src_y, size_x, size_y)
#define video_gfx_stretch3(wrdst, wrdst_x, wrdst_y, rddst, rddst_x, rddst_y, dst_size_x, dst_size_y, src, src_x, src_y, src_size_x, src_size_y) \
	(*(wrdst)->vg_clip.vgc_ops->vgfo_stretch3)(wrdst, wrdst_x, wrdst_y, rddst, rddst_x, rddst_y, dst_size_x, dst_size_y, src, src_x, src_y, src_size_x, src_size_y)
#endif /* !__INTELLISENSE__ */


#ifdef __cplusplus
__CXXDECL_BEGIN
#endif /* __cplusplus */

#ifndef _VIDEO_CONVERTER_N_YDRIVER
#define _VIDEO_CONVERTER_N_YDRIVER ((256 * __SIZEOF_VIDEO_PIXEL_T__) / __SIZEOF_POINTER__)
#endif /* !_VIDEO_CONVERTER_N_YDRIVER */
#if _VIDEO_CONVERTER_N_YDRIVER < 5
#undef _VIDEO_CONVERTER_N_YDRIVER
#define _VIDEO_CONVERTER_N_YDRIVER 5
#endif /* _VIDEO_CONVERTER_N_YDRIVER < 5 */

#define __VIDEO_BLITTER_N_DRIVER 8
#define _VIDEO_BLITTER_N_DRIVER (__VIDEO_BLITTER_N_DRIVER + 1 + _VIDEO_CONVERTER_N_YDRIVER)
#if _VIDEO_BLITTER_N_DRIVER < (__VIDEO_BLITTER_N_DRIVER + 3)
#undef _VIDEO_BLITTER_N_DRIVER
#define _VIDEO_BLITTER_N_DRIVER (__VIDEO_BLITTER_N_DRIVER + 3)
#endif /* _VIDEO_BLITTER_N_DRIVER < (__VIDEO_BLITTER_N_DRIVER + 3) */

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
 * >>     video_buffer_getgfx(dst, &dst_gfx, GFX_BLENDMODE_ALPHA);
 * >>     video_buffer_getgfx(src, &src_gfx, GFX_BLENDMODE_OVERRIDE); // Blend mode doesn't matter
 * >>     video_buffer_getgfx(mask, &mask_gfx, GFX_BLENDMODE_ALPHAMASK);
 * >>     video_gfx_bitblit3(&dst_gfx, 0, 0, &mask_gfx, 0, 0, &src_gfx, 0, 0,
 * >>                        video_gfx_getxdim(&src_gfx), video_gfx_getxdim(&dst_gfx));
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




struct video_gfxclip {
	struct video_gfx_ops const *vgc_ops; /* [1..1][const] GFX operators (use these) */

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
	 * - Buffer:    {xy: {0,0}, wh: video_buffer_getXYdim(vg_surf.vs_buffer)}
	 * - Clip Rect: {xy: {vgc_cxoff,vgc_cyoff}, wh: {vgc_cxdim,vgc_cydim}}
	 * - I/O Rect:  {xy: {vgc_bxmin,vgc_bymin}, wh: {vxh_bxsiz,vxh_bysiz}}
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
	 * >> if (vg_surf.vs_flags & VIDEO_GFX_F_XMIRROR)
	 * >>     x = (vgc_cxdim - 1) - x;
	 * >> if (vg_surf.vs_flags & VIDEO_GFX_F_YMIRROR)
	 * >>     y = (vgc_cydim - 1) - y;
	 * >> if (vg_surf.vs_flags & VIDEO_GFX_F_XWRAP)
	 * >>     x = wrap(x, vgc_cxdim); // wrap(x, dim) = ((x % dim) + dim) % dim
	 * >> if (vg_surf.vs_flags & VIDEO_GFX_F_YWRAP)
	 * >>     x = wrap(x, vgc_cxdim); // ...
	 * >> x += vgc_cxoff;
	 * >> y += vgc_cyoff;
	 * >> if (x < vgc_bxmin)
	 * >>     return VOID;
	 * >> if (y < vgc_bymin)
	 * >>     return VOID;
	 * >> if (x >= vgc_bxend)
	 * >>     return VOID;
	 * >> if (y >= vgc_byend)
	 * >>     return VOID;
	 * >> if (vg_surf.vs_flags & VIDEO_GFX_F_XYSWAP) {
	 * >>     temp = x;
	 * >>     x = y;
	 * >>     y = temp;
	 * >> }
	 * >> return {x,y};
	 */
	video_offset_t              vgc_cxoff;    /* Delta added to all X coords (as per clip-rect) to turn "video_offset_t" into "video_coord_t" */
	video_offset_t              vgc_cyoff;    /* Delta added to all Y coords (as per clip-rect) to turn "video_offset_t" into "video_coord_t" */
	video_dim_t                 vgc_cxdim;    /* Absolute width of the clip-rect (only relevant for `VIDEO_GFX_F*RAP') */
	video_dim_t                 vgc_cydim;    /* Absolute height of the clip-rect (only relevant for `VIDEO_GFX_F*RAP') */
	/* I/O Rect: these values control the (absolute) pixel area where read/writes do something
	 * NOTE: The I/O Rect is already pre-adjusted for VIDEO_GFX_F_XYSWAP */
	video_coord_t               vgc_bxmin;    /* [<= vgc_bxend][>= vgc_cxoff] Absolute buffer start coord in X (start of acc) */
	video_coord_t               vgc_bymin;    /* [<= vgc_byend][>= vgc_cyoff] Absolute buffer start coord in Y */
	video_coord_t               vgc_bxend;    /* [<= video_buffer_getxdim(:vg_surf.vs_buffer)] Absolute buffer end coord in X */
	video_coord_t               vgc_byend;    /* [<= video_buffer_getydim(:vg_surf.vs_buffer)] Absolute buffer end coord in Y */
//	video_dim_t                 vgc_bxdim;    /* [== vgc_bxend - vgc_bxmin][<= vgc_cxdim] I/O Rect width */
//	video_dim_t                 vgc_bydim;    /* [== vgc_byend - vgc_bymin][<= vgc_cydim] I/O Rect height */
};

struct video_gfx {
	struct video_surface vg_surf;  /* Video surface with which to interact. */
	struct video_gfxclip vg_clip;  /* GFX header (this part of the struct can be saved/restored in order to restore old Clip Rects) */
	gfx_blendmode_t      vg_blend; /* Blending mode. */
#define _VIDEO_GFX_N_DRIVER 20
	void *_vg_driver[_VIDEO_GFX_N_DRIVER]; /* [?..?] Driver-specific graphics data. */

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
