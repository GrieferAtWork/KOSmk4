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
#define _KOS_SOURCE 1

#ifdef __INTELLISENSE__
//#define DEFINE_libvideo_swblitter3__blit__mask1msb
//#define DEFINE_libvideo_swblitter3__blit__mask1msb_blend1_samefmt
#define DEFINE_libvideo_swblitter3__blit__mask1msb_blend1_difffmt
#endif /* __INTELLISENSE__ */

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/bit.h>

#include <libvideo/color.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "../gfx-debug.h"
#include "../gfx-utils.h"
#include "../swgfx.h"
#include "ll.h"

#if (defined(DEFINE_libvideo_swblitter3__blit__mask1msb) +                \
     defined(DEFINE_libvideo_swblitter3__blit__mask1msb_blend1_samefmt) + \
     defined(DEFINE_libvideo_swblitter3__blit__mask1msb_blend1_difffmt)) != 1
#error "Must #define exactly one of these macros"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_libvideo_swblitter3__blit__mask1msb
#define LOCAL_libvideo_swblitter3__blit__mask1msb              libvideo_swblitter3__blit__mask1msb
#define LOCAL_libvideo_swblitter3__blit__mask1msb__vline       libvideo_swblitter3__blit__mask1msb__vline
#define LOCAL_libvideo_swblitter3__stretch__mask1msb_l         libvideo_swblitter3__stretch__mask1msb_l
#define LOCAL_libvideo_swblitter3__stretch__mask1msb_n         libvideo_swblitter3__stretch__mask1msb_n
#define LOCAL_libvideo_swblitter3__blit_imatrix__mask1msb      libvideo_swblitter3__blit_imatrix__mask1msb
#define LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_l libvideo_swblitter3__stretch_imatrix__mask1msb_l
#define LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_n libvideo_swblitter3__stretch_imatrix__mask1msb_n
#define LOCAL_LOGIDENT_swblitter3__blit__mask1msb              "swblitter3__blit__mask1msb"
#define LOCAL_LOGIDENT_swblitter3__stretch__mask1msb_l         "swblitter3__stretch__mask1msb_l"
#define LOCAL_LOGIDENT_swblitter3__stretch__mask1msb_n         "swblitter3__stretch__mask1msb_n"
#define LOCAL_LOGIDENT_swblitter3__blit_imatrix__mask1msb      "swblitter3__blit_imatrix__mask1msb"
#define LOCAL_LOGIDENT_swblitter3__stretch_imatrix__mask1msb_l "swblitter3__stretch_imatrix__mask1msb_l"
#define LOCAL_LOGIDENT_swblitter3__stretch_imatrix__mask1msb_n "swblitter3__stretch_imatrix__mask1msb_n"
#elif defined(DEFINE_libvideo_swblitter3__blit__mask1msb_blend1_samefmt)
#define LOCAL_libvideo_swblitter3__blit__mask1msb              libvideo_swblitter3__blit__mask1msb_blend1_samefmt
#define LOCAL_libvideo_swblitter3__blit__mask1msb__vline       libvideo_swblitter3__blit__mask1msb_blend1_samefmt__vline
#define LOCAL_libvideo_swblitter3__stretch__mask1msb_l         libvideo_swblitter3__stretch__mask1msb_blend1_samefmt_l
#define LOCAL_libvideo_swblitter3__stretch__mask1msb_n         libvideo_swblitter3__stretch__mask1msb_blend1_samefmt_n
#define LOCAL_libvideo_swblitter3__blit_imatrix__mask1msb      libvideo_swblitter3__blit_imatrix__mask1msb_blend1_samefmt
#define LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_l libvideo_swblitter3__stretch_imatrix__mask1msb_blend1_samefmt_l
#define LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_n libvideo_swblitter3__stretch_imatrix__mask1msb_blend1_samefmt_n
#define LOCAL_LOGIDENT_swblitter3__blit__mask1msb              "swblitter3__blit__mask1msb_blend1_samefmt"
#define LOCAL_LOGIDENT_swblitter3__stretch__mask1msb_l         "swblitter3__stretch__mask1msb_blend1_samefmt_l"
#define LOCAL_LOGIDENT_swblitter3__stretch__mask1msb_n         "swblitter3__stretch__mask1msb_blend1_samefmt_n"
#define LOCAL_LOGIDENT_swblitter3__blit_imatrix__mask1msb      "swblitter3__blit_imatrix__mask1msb_blend1_samefmt"
#define LOCAL_LOGIDENT_swblitter3__stretch_imatrix__mask1msb_l "swblitter3__stretch_imatrix__mask1msb_blend1_samefmt_l"
#define LOCAL_LOGIDENT_swblitter3__stretch_imatrix__mask1msb_n "swblitter3__stretch_imatrix__mask1msb_blend1_samefmt_n"
#define LOCAL_IS_BLEND1
#define LOCAL_IS_SAMEFMT
#elif defined(DEFINE_libvideo_swblitter3__blit__mask1msb_blend1_difffmt)
#define LOCAL_libvideo_swblitter3__blit__mask1msb              libvideo_swblitter3__blit__mask1msb_blend1_difffmt
#define LOCAL_libvideo_swblitter3__blit__mask1msb__vline       libvideo_swblitter3__blit__mask1msb_blend1_difffmt__vline
#define LOCAL_libvideo_swblitter3__stretch__mask1msb_l         libvideo_swblitter3__stretch__mask1msb_blend1_difffmt_l
#define LOCAL_libvideo_swblitter3__stretch__mask1msb_n         libvideo_swblitter3__stretch__mask1msb_blend1_difffmt_n
#define LOCAL_libvideo_swblitter3__blit_imatrix__mask1msb      libvideo_swblitter3__blit_imatrix__mask1msb_blend1_difffmt
#define LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_l libvideo_swblitter3__stretch_imatrix__mask1msb_blend1_difffmt_l
#define LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_n libvideo_swblitter3__stretch_imatrix__mask1msb_blend1_difffmt_n
#define LOCAL_LOGIDENT_swblitter3__blit__mask1msb              "swblitter3__blit__mask1msb_blend1_difffmt"
#define LOCAL_LOGIDENT_swblitter3__stretch__mask1msb_l         "swblitter3__stretch__mask1msb_blend1_difffmt_l"
#define LOCAL_LOGIDENT_swblitter3__stretch__mask1msb_n         "swblitter3__stretch__mask1msb_blend1_difffmt_n"
#define LOCAL_LOGIDENT_swblitter3__blit_imatrix__mask1msb      "swblitter3__blit_imatrix__mask1msb_blend1_difffmt"
#define LOCAL_LOGIDENT_swblitter3__stretch_imatrix__mask1msb_l "swblitter3__stretch_imatrix__mask1msb_blend1_difffmt_l"
#define LOCAL_LOGIDENT_swblitter3__stretch_imatrix__mask1msb_n "swblitter3__stretch_imatrix__mask1msb_blend1_difffmt_n"
#define LOCAL_IS_BLEND1
#define LOCAL_IS_DIFFFMT
#else /* ... */
#error "Invalid configuration"
#endif /* !... */

#define LOCAL_libvideo_swblitter3__blit__mask1msb__bypixel              PP_CAT2(LOCAL_libvideo_swblitter3__blit__mask1msb, __bypixel)
#define LOCAL_libvideo_swblitter3__stretch__mask1msb_l__bypixel         PP_CAT2(LOCAL_libvideo_swblitter3__stretch__mask1msb_l, __bypixel)
#define LOCAL_libvideo_swblitter3__stretch__mask1msb_n__bypixel         PP_CAT2(LOCAL_libvideo_swblitter3__stretch__mask1msb_n, __bypixel)
#define LOCAL_libvideo_swblitter3__blit_imatrix__mask1msb__bypixel      PP_CAT2(LOCAL_libvideo_swblitter3__blit_imatrix__mask1msb, __bypixel)
#define LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_l__bypixel PP_CAT2(LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_l, __bypixel)
#define LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_n__bypixel PP_CAT2(LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_n, __bypixel)

/* Same as versions above,  but `vbt3_rddst' is a  1bpp-msb
 * bitmask specifying which pixels to write in `vbt3_wrdst'
 * - The *_blend1* version then specifies that no further blending is done by `vbt3_wrdst'
 * - The *_samefmt* version then specifies that `vbt3_wrdst' and `vbt3_src' use the same codec */

#ifdef LOCAL_IS_DIFFFMT
#define LOCAL_load_conv struct video_converter const *conv = libvideo_swblitter3_generic__cconv(self)
#else /* LOCAL_IS_DIFFFMT */
#define LOCAL_load_conv (void)0
#endif /* !LOCAL_IS_DIFFFMT */

#ifndef LOCAL_IS_BLEND1
#define LOCAL_pixel_t               video_color_t
#define LOCAL_src_getpixel(x, y)    LL_getcolor(src, x, y)
#define LOCAL_out_setpixel(x, y, v) LL_putcolor(out, x, y, v)
#elif !defined(LOCAL_IS_SAMEFMT)
#define LOCAL_pixel_t               video_pixel_t
#define LOCAL_src_getpixel(x, y)    video_converter_mappixel(conv, LL_getpixel(src, x, y))
#define LOCAL_out_setpixel(x, y, v) LL_setpixel(out, x, y, v)
#else /* !LOCAL_IS_BLEND1 */
#define LOCAL_pixel_t               video_pixel_t
#define LOCAL_src_getpixel(x, y)    LL_getpixel(src, x, y)
#define LOCAL_out_setpixel(x, y, v) LL_setpixel(out, x, y, v)
#endif /* LOCAL_IS_BLEND1 */

#define BLIT_PIXEL(px_out_x, px_out_y, px_dst_x, px_dst_y, px_src_x, px_src_y) \
	{                                                                          \
		if (LL_getpixel(dst, px_dst_x, px_dst_y)) {                            \
			LOCAL_pixel_t p = LOCAL_src_getpixel(px_src_x, px_src_y);          \
			LOCAL_out_setpixel(px_out_x, px_out_y, p);                         \
		}                                                                      \
	}

PRIVATE ATTR_IN(1) void CC
LOCAL_libvideo_swblitter3__blit__mask1msb__bypixel(struct video_blitter3 const *__restrict self,
                                                   video_coord_t out_x, video_coord_t out_y,
                                                   video_coord_t dst_x, video_coord_t dst_y,
                                                   video_coord_t src_x, video_coord_t src_y,
                                                   video_dim_t size_x, video_dim_t size_y) {
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
	LOCAL_load_conv;
	GFX_BLIT_FOREACH3(out_x, out_y, dst_x, dst_y, src_x, src_y, size_x, size_y,
	                  BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}

PRIVATE ATTR_IN(1) void CC
LOCAL_libvideo_swblitter3__blit_imatrix__mask1msb__bypixel(struct video_blitter3 const *__restrict self,
                                                           video_coord_t out_x, video_coord_t out_y,
                                                           video_coord_t dst_x, video_coord_t dst_y,
                                                           video_imatrix2d_t dst_matrix,
                                                           video_coord_t src_x, video_coord_t src_y,
                                                           video_dim_t size_x, video_dim_t size_y,
                                                           video_imatrix2d_t src_matrix) {
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
	LOCAL_load_conv;
	GFX_BLIT_FOREACH3_IMATRIX(out_x, out_y, dst_x, dst_y, dst_matrix,
	                          src_x, src_y, size_x, size_y, src_matrix,
	                          BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}

PRIVATE ATTR_IN(1) void CC
LOCAL_libvideo_swblitter3__stretch__mask1msb_n__bypixel(struct video_blitter3 const *__restrict self,
                                                        video_coord_t out_x, video_coord_t out_y,
                                                        video_coord_t dst_x, video_coord_t dst_y,
                                                        video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                        video_coord_t src_x, video_coord_t src_y,
                                                        video_dim_t src_size_x, video_dim_t src_size_y) {
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
	LOCAL_load_conv;
	GFX_NEAREST_STRETCH3(out_x, out_y,
	                     dst_x, dst_y, dst_size_x, dst_size_y,
	                     src_x, src_y, src_size_x, src_size_y,
	                     BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}

PRIVATE ATTR_IN(1) void CC
LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_n__bypixel(struct video_blitter3 const *__restrict self,
                                                                video_coord_t out_x, video_coord_t out_y,
                                                                video_coord_t dst_x, video_coord_t dst_y,
                                                                video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                                video_imatrix2d_t dst_matrix,
                                                                video_coord_t src_x, video_coord_t src_y,
                                                                video_dim_t src_size_x, video_dim_t src_size_y,
                                                                video_imatrix2d_t src_matrix) {
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
	LOCAL_load_conv;
	gfx_assert_imatrix2d(&dst_matrix);
	gfx_assert_imatrix2d(&src_matrix);
	GFX_NEAREST_STRETCH3_IMATRIX(out_x, out_y,
	                             dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix,
	                             src_x, src_y, src_size_x, src_size_y, src_matrix,
	                             BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}

PRIVATE ATTR_IN(1) void CC
LOCAL_libvideo_swblitter3__stretch__mask1msb_l__bypixel(struct video_blitter3 const *__restrict self,
                                                        video_coord_t out_x, video_coord_t out_y,
                                                        video_coord_t dst_x, video_coord_t dst_y,
                                                        video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                        video_coord_t src_x, video_coord_t src_y,
                                                        video_dim_t src_size_x, video_dim_t src_size_y) {
	/* TODO */
	LOCAL_libvideo_swblitter3__stretch__mask1msb_n__bypixel(self, out_x, out_y,
	                                                        dst_x, dst_y, dst_size_x, dst_size_y,
	                                                        src_x, src_y, src_size_x, src_size_y);
}

PRIVATE ATTR_IN(1) void CC
LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_l__bypixel(struct video_blitter3 const *__restrict self,
                                                                video_coord_t out_x, video_coord_t out_y,
                                                                video_coord_t dst_x, video_coord_t dst_y,
                                                                video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                                video_imatrix2d_t dst_matrix,
                                                                video_coord_t src_x, video_coord_t src_y,
                                                                video_dim_t src_size_x, video_dim_t src_size_y,
                                                                video_imatrix2d_t src_matrix) {
	gfx_assert_imatrix2d(&dst_matrix);
	gfx_assert_imatrix2d(&src_matrix);
	/* TODO */
	LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_n__bypixel(self, out_x, out_y,
	                                                                dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix,
	                                                                src_x, src_y, src_size_x, src_size_y, src_matrix);
}
#undef BLIT_PIXEL
#undef LOCAL_pixel_t
#undef LOCAL_src_getpixel
#undef LOCAL_out_setpixel




#ifdef LOCAL_IS_BLEND1
PRIVATE ATTR_IN(1) void CC
LOCAL_libvideo_swblitter3__blit__mask1msb__vline(struct video_blitter3 const *__restrict self,
                                                 byte_t *out_line, size_t out_stride, video_coord_t out_x,
                                                 byte_t const *src_line, size_t src_stride, video_coord_t src_x,
                                                 byte_t const *dst_line, size_t dst_stride,
                                                 byte_t dst_mask, video_dim_t size_y) {
#ifdef LOCAL_IS_SAMEFMT
	video_codec_linecopy_t vc_linecopy = video_gfx_getcodec(self->vbt3_wrdst)->vc_linecopy;
#else /* LOCAL_IS_SAMEFMT */
	video_codec_setpixel_t vc_setpixel = video_gfx_getcodec(self->vbt3_wrdst)->vc_setpixel;
	video_codec_getpixel_t vc_getpixel = video_gfx_getcodec(self->vbt3_src)->vc_getpixel;
#endif /* !LOCAL_IS_SAMEFMT */
	LOCAL_load_conv;
	gfx_assert(dst_mask != 0);
	gfx_assert(dst_mask != 0xff);
	do {
		byte_t mask = *dst_line & dst_mask;
		video_coord_t out_line_x = out_x;
		video_coord_t src_line_x = src_x;
		while (mask) {
			shift_t skip = CLZ(mask);
			out_line_x += skip;
			src_line_x += skip;
			mask <<= skip;
			/* Copy "n" pixels from "src_line" to "dst_line" */
#ifdef LOCAL_IS_SAMEFMT
			{
				shift_t set = CLZ((byte_t)~mask);
				gfx_assert(set);
				(*vc_linecopy)(out_line, out_line_x, src_line, src_line_x, set);
				out_line_x += set;
				src_line_x += set;
				mask <<= set;
			}
#else /* LOCAL_IS_SAMEFMT */
			do {
				video_pixel_t sp = (*vc_getpixel)(src_line, src_line_x);
				video_pixel_t op = video_converter_mappixel(conv, sp);
				(*vc_setpixel)(out_line, out_line_x, op);
				++out_line_x;
				++src_line_x;
				mask <<= 1;
			} while (mask & 0x80);
#endif /* !LOCAL_IS_SAMEFMT */
		}
		src_line += src_stride;
		dst_line += dst_stride;
		out_line += out_stride;
	} while (--size_y);
}
#endif /* LOCAL_IS_BLEND1 */

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter3__blit__mask1msb(struct video_blitter3 const *__restrict self,
                                          video_coord_t out_x, video_coord_t out_y,
                                          video_coord_t dst_x, video_coord_t dst_y,
                                          video_coord_t src_x, video_coord_t src_y,
                                          video_dim_t size_x, video_dim_t size_y) {
#ifdef LOCAL_IS_BLEND1
	struct video_regionlock out_lock;
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
#endif /* LOCAL_IS_BLEND1 */
	TRACE_START(LOCAL_LOGIDENT_swblitter3__blit__mask1msb "("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            out_x, out_y, dst_x, dst_y, src_x, src_y, size_x, size_y);
#ifdef LOCAL_IS_BLEND1
	if (LL_wlockregion(video_gfx_getbuffer(out), &out_lock, out_x, out_y, size_x, size_y)) {
		struct video_regionlock dst_lock;
		if (LL_rlockregion(video_gfx_getbuffer(dst), &dst_lock, dst_x, dst_y, size_x, size_y)) {
			struct video_regionlock src_lock;
			if (LL_rlockregion(video_gfx_getbuffer(src), &src_lock, src_x, src_y, size_x, size_y)) {
				/* Use video locks */
				video_coord_t used_src_x = video_regionlock_getxbase(&src_lock);
				video_coord_t used_dst_x = video_regionlock_getxbase(&dst_lock);
				video_coord_t used_out_x = video_regionlock_getxbase(&out_lock);
				byte_t const *src_line   = video_regionlock_getdata(&src_lock);
				byte_t const *dst_line   = video_regionlock_getdata(&dst_lock);
				byte_t *out_line         = video_regionlock_getdata(&out_lock);
#ifdef LOCAL_IS_SAMEFMT
				video_codec_linecopy_t vc_linecopy = video_gfx_getcodec(out)->vc_linecopy;
#else  /* LOCAL_IS_SAMEFMT */
				video_codec_setpixel_t vc_setpixel = video_gfx_getcodec(out)->vc_setpixel;
				video_codec_getpixel_t vc_getpixel = video_gfx_getcodec(src)->vc_getpixel;
#endif /* !LOCAL_IS_SAMEFMT */
				LOCAL_load_conv;

				/* Deal with unaligned leading bits */
				if (used_dst_x) {
					dst_line += (used_dst_x >> 3);
					used_dst_x &= 7;
					if (used_dst_x) {
						byte_t leading_mask;
						shift_t leading_unaligned = 8 - (shift_t)used_dst_x;
						if (leading_unaligned > size_x)
							leading_unaligned = (shift_t)size_x;
						/* used_dst_x = 1, leading_unaligned = 7: leading_mask = 0x7f
						 * used_dst_x = 2, leading_unaligned = 6: leading_mask = 0x3f
						 * used_dst_x = 2, leading_unaligned = 5: leading_mask = 0x3e
						 * used_dst_x = 2, leading_unaligned = 4: leading_mask = 0x3c
						 * ... */
						leading_mask = (((byte_t)1 << leading_unaligned) - 1)
						               << (8 - (used_dst_x + leading_unaligned));
						LOCAL_libvideo_swblitter3__blit__mask1msb__vline(self,
						                                                 out_line, video_regionlock_getstride(&out_lock), used_out_x,
						                                                 src_line, video_regionlock_getstride(&src_lock), used_src_x,
						                                                 dst_line, video_regionlock_getstride(&dst_lock), leading_mask, size_y);
						if unlikely(leading_unaligned >= size_x)
							goto done_lock; /* Blit consisted of **only** unaligned bits. */
						used_out_x += leading_unaligned;
						used_src_x += leading_unaligned;
						size_x -= leading_unaligned;
						/*used_dst_x = 0;*/
						gfx_assert(size_x != 0);
					}
				}

				/* Deal with unaligned trailing bits */
				if (size_x & 7) {
					shift_t trailing_unaligned = (shift_t)(size_x & 7);
					byte_t trailing_mask = ~(0xff >> trailing_unaligned);
					LOCAL_libvideo_swblitter3__blit__mask1msb__vline(self,
					                                                 out_line, video_regionlock_getstride(&out_lock), used_out_x + (size_x & ~7),
					                                                 src_line, video_regionlock_getstride(&src_lock), used_src_x + (size_x & ~7),
					                                                 dst_line + (size_x >> 3), video_regionlock_getstride(&dst_lock), trailing_mask, size_y);
					size_x &= ~7;
					if unlikely(!size_x)
						return;
				}

				/* Copy pixels specified by byte-aligned bitmask */
				size_x >>= 3;
				gfx_assert(size_x);
				do {
					byte_t const *dst_iter = dst_line;
					video_dim_t iter_x_byte = 0;
					video_coord_t out_line_x = used_out_x;
					video_coord_t src_line_x = used_src_x;
					do {
						byte_t mask = *dst_iter++;
						shift_t skip;
						++iter_x_byte;
						if (!mask) {
							out_line_x += 8;
							src_line_x += 8;
						} else {
							skip = CLZ(mask);
#ifdef LOCAL_IS_SAMEFMT
							if (mask == (((byte_t)1 << (8 - skip)) - 1)) {
								video_dim_t n = 8 - skip;
								out_line_x += skip;
								src_line_x += skip;
								/* Optimize for cross-byte continuous masks. */
								while (iter_x_byte < size_x && (*dst_iter == 0xff)) {
									++iter_x_byte;
									++dst_iter;
									n += 8;
								}
								(*vc_linecopy)(out_line, out_line_x, src_line, src_line_x, n);
								if (iter_x_byte >= size_x)
									break;
								out_line_x += n;
								src_line_x += n;
							} else
#endif /* LOCAL_IS_SAMEFMT */
							{
								video_coord_t out_word_x = out_line_x;
								video_coord_t src_word_x = src_line_x;
								for (;;) {
									mask <<= skip;
									out_word_x += skip;
									src_word_x += skip;
#ifdef LOCAL_IS_SAMEFMT
									gfx_assert(mask != 0xff);
									{
										shift_t set = CLZ((byte_t)~mask);
										(*vc_linecopy)(out_line, out_word_x, src_line, src_word_x, set);
										out_word_x += set;
										src_word_x += set;
										mask <<= set;
									}
#else /* LOCAL_IS_SAMEFMT */
									do {
										video_pixel_t sp = (*vc_getpixel)(src_line, src_word_x);
										video_pixel_t op = video_converter_mappixel(conv, sp);
										(*vc_setpixel)(out_line, out_word_x, op);
										++out_word_x;
										++src_word_x;
										mask <<= 1;
									} while (mask & 0x80);
#endif /* !LOCAL_IS_SAMEFMT */
									if (!mask)
										break;
									skip = CLZ(mask);
								}
								out_line_x += 8;
								src_line_x += 8;
							}
						}
					} while (iter_x_byte < size_x);
					out_line += video_regionlock_getstride(&out_lock);
					src_line += video_regionlock_getstride(&src_lock);
					dst_line += video_regionlock_getstride(&dst_lock);
				} while (--size_y);
done_lock:
				LL_unlockregion(video_gfx_getbuffer(src), &src_lock);
				LL_unlockregion(video_gfx_getbuffer(dst), &dst_lock);
				LL_unlockregion(video_gfx_getbuffer(out), &out_lock);
				goto done;
			}
			LL_unlockregion(video_gfx_getbuffer(dst), &dst_lock);
		}
		LL_unlockregion(video_gfx_getbuffer(out), &out_lock);
	}
#endif /* LOCAL_IS_BLEND1 */
	LOCAL_libvideo_swblitter3__blit__mask1msb__bypixel(self, out_x, out_y, dst_x, dst_y,
	                                                   src_x, src_y, size_x, size_y);
#ifdef LOCAL_IS_BLEND1
done:
#endif /* LOCAL_IS_BLEND1 */
	TRACE_END(LOCAL_LOGIDENT_swblitter3__blit__mask1msb "()\n");
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter3__blit_imatrix__mask1msb(struct video_blitter3 const *__restrict self,
                                                  video_coord_t out_x, video_coord_t out_y,
                                                  video_coord_t dst_x, video_coord_t dst_y,
                                                  video_imatrix2d_t dst_matrix,
                                                  video_coord_t src_x, video_coord_t src_y,
                                                  video_dim_t size_x, video_dim_t size_y,
                                                  video_imatrix2d_t src_matrix) {
	gfx_assert_imatrix2d(&dst_matrix);
	gfx_assert_imatrix2d(&src_matrix);

	/* Fast-pass for known matrices */
	if (src_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1) &&
	    dst_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1)) {
		LOCAL_libvideo_swblitter3__blit__mask1msb(self, out_x, out_y, dst_x, dst_y,
		                                          src_x, src_y, size_x, size_y);
		return;
	}

	TRACE_START(LOCAL_LOGIDENT_swblitter3__blit_imatrix__mask1msb "("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", matrix: {{%d,%d},{%d,%d}}}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", matrix: {{%d,%d},{%d,%d}}}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            out_x, out_y,
	            dst_x, dst_y,
	            (int)video_imatrix2d_get(&dst_matrix, 0, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 0, 1),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 1),
	            src_x, src_y,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1),
	            size_x, size_y);

	/* TODO: Use video locks */
	LOCAL_libvideo_swblitter3__blit_imatrix__mask1msb__bypixel(self, out_x, out_y, dst_x, dst_y, dst_matrix,
	                                                           src_x, src_y, size_x, size_y, src_matrix);
	TRACE_END(LOCAL_LOGIDENT_swblitter3__blit_imatrix__mask1msb "()\n");
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter3__stretch__mask1msb_l(struct video_blitter3 const *__restrict self,
                                               video_coord_t out_x, video_coord_t out_y,
                                               video_coord_t dst_x, video_coord_t dst_y,
                                               video_dim_t dst_size_x, video_dim_t dst_size_y,
                                               video_coord_t src_x, video_coord_t src_y,
                                               video_dim_t src_size_x, video_dim_t src_size_y) {
	TRACE_START(LOCAL_LOGIDENT_swblitter3__stretch__mask1msb_l "("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            out_x, out_y,
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            src_x, src_y, src_size_x, src_size_y);

	/* TODO: Use video locks */
	LOCAL_libvideo_swblitter3__stretch__mask1msb_l__bypixel(self, out_x, out_y,
	                                                        dst_x, dst_y, dst_size_x, dst_size_y,
	                                                        src_x, src_y, src_size_x, src_size_y);
	TRACE_END(LOCAL_LOGIDENT_swblitter3__stretch__mask1msb_l "()\n");
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter3__stretch__mask1msb_n(struct video_blitter3 const *__restrict self,
                                               video_coord_t out_x, video_coord_t out_y,
                                               video_coord_t dst_x, video_coord_t dst_y,
                                               video_dim_t dst_size_x, video_dim_t dst_size_y,
                                               video_coord_t src_x, video_coord_t src_y,
                                               video_dim_t src_size_x, video_dim_t src_size_y) {
	TRACE_START(LOCAL_LOGIDENT_swblitter3__stretch__mask1msb_n "("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            out_x, out_y,
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            src_x, src_y, src_size_x, src_size_y);

	/* TODO: Use video locks */
	LOCAL_libvideo_swblitter3__stretch__mask1msb_n__bypixel(self, out_x, out_y,
	                                                        dst_x, dst_y, dst_size_x, dst_size_y,
	                                                        src_x, src_y, src_size_x, src_size_y);
	TRACE_END(LOCAL_LOGIDENT_swblitter3__stretch__mask1msb_n "()\n");
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_l(struct video_blitter3 const *__restrict self,
                                                       video_coord_t out_x, video_coord_t out_y,
                                                       video_coord_t dst_x, video_coord_t dst_y,
                                                       video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                       video_imatrix2d_t dst_matrix,
                                                       video_coord_t src_x, video_coord_t src_y,
                                                       video_dim_t src_size_x, video_dim_t src_size_y,
                                                       video_imatrix2d_t src_matrix) {
	gfx_assert_imatrix2d(&dst_matrix);
	gfx_assert_imatrix2d(&src_matrix);

	/* Fast-pass for known matrices */
	if (src_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1) &&
	    dst_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1)) {
		LOCAL_libvideo_swblitter3__stretch__mask1msb_l(self, out_x, out_y,
		                                               dst_x, dst_y, dst_size_x, dst_size_y,
		                                               src_x, src_y, src_size_x, src_size_y);
		return;
	}

	TRACE_START(LOCAL_LOGIDENT_swblitter3__stretch_imatrix__mask1msb_l "("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM ", matrix: {{%d,%d},{%d,%d}}}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM ", matrix: {{%d,%d},{%d,%d}}})\n",
	            out_x, out_y,
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            (int)video_imatrix2d_get(&dst_matrix, 0, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 0, 1),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 1),
	            src_x, src_y, src_size_x, src_size_y,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1));

	/* TODO: Use video locks */
	LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_l__bypixel(self, out_x, out_y,
	                                                                dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix,
	                                                                src_x, src_y, src_size_x, src_size_y, src_matrix);
	TRACE_END(LOCAL_LOGIDENT_swblitter3__stretch_imatrix__mask1msb_l "()");
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_n(struct video_blitter3 const *__restrict self,
                                                       video_coord_t out_x, video_coord_t out_y,
                                                       video_coord_t dst_x, video_coord_t dst_y,
                                                       video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                       video_imatrix2d_t dst_matrix,
                                                       video_coord_t src_x, video_coord_t src_y,
                                                       video_dim_t src_size_x, video_dim_t src_size_y,
                                                       video_imatrix2d_t src_matrix) {
	gfx_assert_imatrix2d(&dst_matrix);
	gfx_assert_imatrix2d(&src_matrix);

	/* Fast-pass for known matrices */
	if (src_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1) &&
	    dst_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1)) {
		LOCAL_libvideo_swblitter3__stretch__mask1msb_n(self, out_x, out_y,
		                                               dst_x, dst_y, dst_size_x, dst_size_y,
		                                               src_x, src_y, src_size_x, src_size_y);
		return;
	}

	TRACE_START(LOCAL_LOGIDENT_swblitter3__stretch_imatrix__mask1msb_n "("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM ", matrix: {{%d,%d},{%d,%d}}}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM ", matrix: {{%d,%d},{%d,%d}}})\n",
	            out_x, out_y,
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            (int)video_imatrix2d_get(&dst_matrix, 0, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 0, 1),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 1),
	            src_x, src_y, src_size_x, src_size_y,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1));

	/* TODO: Use video locks */
	LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_n__bypixel(self, out_x, out_y,
	                                                                dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix,
	                                                                src_x, src_y, src_size_x, src_size_y, src_matrix);
	TRACE_END(LOCAL_LOGIDENT_swblitter3__stretch_imatrix__mask1msb_l "()");
}

#undef LOCAL_load_conv

#undef LOCAL_libvideo_swblitter3__blit__mask1msb__bypixel
#undef LOCAL_libvideo_swblitter3__stretch__mask1msb_l__bypixel
#undef LOCAL_libvideo_swblitter3__stretch__mask1msb_n__bypixel
#undef LOCAL_libvideo_swblitter3__blit_imatrix__mask1msb__bypixel
#undef LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_l__bypixel
#undef LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_n__bypixel

#undef LOCAL_libvideo_swblitter3__blit__mask1msb
#undef LOCAL_libvideo_swblitter3__blit__mask1msb__vline
#undef LOCAL_libvideo_swblitter3__stretch__mask1msb_l
#undef LOCAL_libvideo_swblitter3__stretch__mask1msb_n
#undef LOCAL_libvideo_swblitter3__blit_imatrix__mask1msb
#undef LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_l
#undef LOCAL_libvideo_swblitter3__stretch_imatrix__mask1msb_n
#undef LOCAL_LOGIDENT_swblitter3__blit__mask1msb
#undef LOCAL_LOGIDENT_swblitter3__stretch__mask1msb_l
#undef LOCAL_LOGIDENT_swblitter3__stretch__mask1msb_n
#undef LOCAL_LOGIDENT_swblitter3__blit_imatrix__mask1msb
#undef LOCAL_LOGIDENT_swblitter3__stretch_imatrix__mask1msb_l
#undef LOCAL_LOGIDENT_swblitter3__stretch_imatrix__mask1msb_n
#undef LOCAL_IS_BLEND1
#undef LOCAL_IS_SAMEFMT
#undef LOCAL_IS_DIFFFMT

DECL_END

#undef DEFINE_libvideo_swblitter3__blit__mask1msb
#undef DEFINE_libvideo_swblitter3__blit__mask1msb_blend1_samefmt
#undef DEFINE_libvideo_swblitter3__blit__mask1msb_blend1_difffmt
