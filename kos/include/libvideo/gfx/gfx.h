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

#include <__stdinc.h>

#include <bits/types.h>

#include <libvideo/codec/pixel.h>

#ifdef __cplusplus
#include <type_traits>
#endif /* __cplusplus */

#include "api.h"

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

__DECL_BEGIN


/* Surface blend definitions. */
#define GFX_BLENDMODE_ZERO                     0x00 /* 0 */
#define GFX_BLENDMODE_ONE                      0x01 /* 1  (max intensity; channel=0xff) */
#define GFX_BLENDMODE_SRC_COLOR                0x02 /* source_color */
#define GFX_BLENDMODE_ONE_MINUS_SRC_COLOR      0x03 /* 1 - source_color */
#define GFX_BLENDMODE_DST_COLOR                0x04 /* destination_color */
#define GFX_BLENDMODE_ONE_MINUS_DST_COLOR      0x05 /* 1 - destination_color */
#define GFX_BLENDMODE_SRC_ALPHA                0x06 /* source_alpha */
#define GFX_BLENDMODE_ONE_MINUS_SRC_ALPHA      0x07 /* 1 - source_alpha */
#define GFX_BLENDMODE_DST_ALPHA                0x08 /* destination_alpha */
#define GFX_BLENDMODE_ONE_MINUS_DST_ALPHA      0x09 /* 1 - destination_alpha */
#define GFX_BLENDMODE_SRC_ALPHA_SATURATE       0x0a /* min(source_alpha, 1 - destination_alpha) */
#define GFX_BLENDMODE_CONSTANT_COLOR           0x0b /* CR/CG/CB */
#define GFX_BLENDMODE_ONE_MINUS_CONSTANT_COLOR 0x0c /* 1 - CR/CG/CB */
#define GFX_BLENDMODE_CONSTANT_ALPHA           0x0d /* CA */
#define GFX_BLENDMODE_ONE_MINUS_CONSTANT_ALPHA 0x0e /* 1 - CA */
/*      GFX_BLENDMODE_...                      0x0f  * ... */

#define GFX_BLENDFUNC_ADD                      0x00 /* a + b */
#define GFX_BLENDFUNC_SUBTRACT                 0x01 /* a - b */
#define GFX_BLENDFUNC_REVERSE_SUBTRACT         0x02 /* b - a */
#define GFX_BLENDFUNC_MIN                      0x03 /* a < b ? a : b */
#define GFX_BLENDFUNC_MAX                      0x04 /* a > b ? a : b */
/*      GFX_BLENDFUNC_...                      0x05  * ... */
/*      GFX_BLENDFUNC_...                      0x06  * ... */
/*      GFX_BLENDFUNC_...                      0x07  * ... */

#define GFX_BLENDINFO_GET_SRCRGB(info) (__CCAST(__uint8_t)((info) & 0xf))          /* Source color (One of `GFX_BLENDMODE_*') */
#define GFX_BLENDINFO_GET_SRCA(info)   (__CCAST(__uint8_t)(((info) >> 4) & 0xf))   /* Source alpha (One of `GFX_BLENDMODE_*') */
#define GFX_BLENDINFO_GET_DSTRGB(info) (__CCAST(__uint8_t)(((info) >> 8) & 0xf))   /* Destination color (One of `GFX_BLENDMODE_*') */
#define GFX_BLENDINFO_GET_DSTA(info)   (__CCAST(__uint8_t)(((info) >> 12) & 0xf))  /* Destination alpha (One of `GFX_BLENDMODE_*') */
#define GFX_BLENDINFO_GET_FUNRGB(info) (__CCAST(__uint8_t)(((info) >> 15) & 0x7))  /* Color blend function (One of `GFX_BLENDFUNC_*') */
#define GFX_BLENDINFO_GET_FUNA(info)   (__CCAST(__uint8_t)(((info) >> 18) & 0x7))  /* Alpha blend function (One of `GFX_BLENDFUNC_*') */
#define GFX_BLENDINFO_GET_CR(info)     (__CCAST(__uint8_t)(((info) >> 56) & 0xff)) /* Constant color red */
#define GFX_BLENDINFO_GET_CG(info)     (__CCAST(__uint8_t)(((info) >> 48) & 0xff)) /* Constant color green */
#define GFX_BLENDINFO_GET_CB(info)     (__CCAST(__uint8_t)(((info) >> 40) & 0xff)) /* Constant color blue */
#define GFX_BLENDINFO_GET_CA(info)     (__CCAST(__uint8_t)(((info) >> 32) & 0xff)) /* Constant color alpha */

/* Helper macros for creating blend modes.
 * @param: src:  Source color/alpha (One of `GFX_BLENDMODE_*')
 * @param: dst:  Destination color/alpha (One of `GFX_BLENDMODE_*')
 * @param: func: Color/alpha blend function (One of `GFX_BLENDFUNC_*') */
#define GFX_BLENDINFO(src, dst, func) \
	GFX_BLENDINFO_EX(src, src, dst, dst, func, func, 0, 0, 0, 0)
#define GFX_BLENDINFO_EX(rgb_src, a_src, rgb_dst, a_dst, \
                         rgb_fun, a_fun, cr, cg, cb, ca) \
	(__CCAST(gfx_blendmode_t)((rgb_src) & 0xf) |         \
	 (__CCAST(gfx_blendmode_t)((a_src) & 0xf) << 4) |    \
	 (__CCAST(gfx_blendmode_t)((rgb_dst) & 0xf) << 8) |  \
	 (__CCAST(gfx_blendmode_t)((a_dst) & 0xf) << 12) |   \
	 (__CCAST(gfx_blendmode_t)((rgb_fun) & 0x7) << 15) | \
	 (__CCAST(gfx_blendmode_t)((a_fun) & 0x7) << 18) |   \
	 (__CCAST(gfx_blendmode_t)((cr) & 0xff) << 56) |     \
	 (__CCAST(gfx_blendmode_t)((cg) & 0xff) << 48) |     \
	 (__CCAST(gfx_blendmode_t)((cb) & 0xff) << 40) |     \
	 (__CCAST(gfx_blendmode_t)((ca) & 0xff) << 32))
#ifdef __CC__
typedef __uint64_t gfx_blendmode_t;
#endif /* __CC__ */

/* Conventional alpha blending */
#define GFX_BLENDINFO_ALPHA \
	GFX_BLENDINFO(GFX_BLENDMODE_SRC_ALPHA, GFX_BLENDMODE_ONE_MINUS_SRC_ALPHA, GFX_BLENDFUNC_ADD)

/* Override destination (no blending done) */
#define GFX_BLENDINFO_OVERRIDE \
	GFX_BLENDINFO(GFX_BLENDMODE_ONE, GFX_BLENDMODE_ZERO, GFX_BLENDFUNC_ADD)



/* Video graphic flags.
 * [READ]:  Indicates a flag that affects the results when the associated
 *          GFX  context is used  as source, or  when reading pixel data.
 * [WRITE]: Indicates a flag that affects the results of graphics operations
 *          that use  the associated  GFX context  as destination,  or  when
 *          writing pixel data. */
#define VIDEO_GFX_FNORMAL      0x0000 /* Normal render flags. */
#define VIDEO_GFX_FAALINES     0x0001 /* [WRITE] Render smooth lines. */
#define VIDEO_GFX_FNEARESTBLIT 0x0000 /* [WRITE] Use nearest interpolation for stretch() */
#define VIDEO_GFX_FLINEARBLIT  0x0002 /* [WRITE] Use linear interpolation for stretch() (else: use nearest) */
#define VIDEO_GFX_FBLUR        0x0004 /* [READ]  Pixel reads will return the average of the surrounding 9 pixels.
                                       *         For this purpose, out-of-bounds pixels are ignored (and not part of the average taken)
                                       * The behavior is weak undefined if this flag is used alongside a non-zero color key */


#ifdef __CC__
struct video_buffer;
struct video_gfx;

struct video_gfx_pxops {
	/* All of the following callbacks are [1..1]
	 * WARNING: None  of these functions will add `vx_offt_(x|y)' to the given X/Y,
	 *          as well as always assume that the given coords are in-bounds of the
	 *          underlying buffer. */
	/* Get the color of a pixel */
	__ATTR_NONNULL_T((1)) video_color_t
	(LIBVIDEO_GFX_CC *fxo_getcolor)(struct video_gfx const *__restrict __self,
	                                __uintptr_t __abs_x, __uintptr_t __abs_y);

	/* Place a colored pixel ontop of the graphic */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_CC *fxo_putcolor)(struct video_gfx *__restrict __self,
	                                __uintptr_t __abs_x, __uintptr_t __abs_y,
	                                video_color_t __color);
};

struct video_gfx_ops {
	/* All of the following callbacks are [1..1] */

	/* Draw a line */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_CC *fxo_line)(struct video_gfx *__restrict __self,
	                            __intptr_t __x1, __intptr_t __y1,
	                            __intptr_t __x2, __intptr_t __y2,
	                            video_color_t __color);

	/* Vertical line */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_CC *fxo_vline)(struct video_gfx *__restrict __self,
	                             __intptr_t __x, __intptr_t __y,
	                             __size_t __length, video_color_t __color);

	/* Horizontal line */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_CC *fxo_hline)(struct video_gfx *__restrict __self,
	                             __intptr_t __x, __intptr_t __y,
	                             __size_t __length, video_color_t __color);

	/* Fill an area with a solid color. */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_CC *fxo_fill)(struct video_gfx *__restrict __self,
	                            __intptr_t __x, __intptr_t __y,
	                            __size_t __size_x, __size_t __size_y,
	                            video_color_t __color);

	/* Outline an area with a rectangle. */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_CC *fxo_rect)(struct video_gfx *__restrict __self,
	                            __intptr_t __x, __intptr_t __y,
	                            __size_t __size_x, __size_t __size_y,
	                            video_color_t __color);

	/* Blit the contents of another video buffer into this one. */
	__ATTR_NONNULL_T((1, 4)) void
	(LIBVIDEO_GFX_CC *fxo_blit)(struct video_gfx *__self,
	                            __intptr_t __dst_x, __intptr_t __dst_y,
	                            struct video_gfx const *__src,
	                            __intptr_t __src_x, __intptr_t __src_y,
	                            __size_t __size_x, __size_t __size_y);

	/* Same as `fxo_blit', but stretch the contents */
	__ATTR_NONNULL_T((1, 6)) void
	(LIBVIDEO_GFX_CC *fxo_stretch)(struct video_gfx *__self,
	                               __intptr_t __dst_x, __intptr_t __dst_y,
	                               __size_t __dst_size_x, __size_t __dst_size_y,
	                               struct video_gfx const *__src,
	                               __intptr_t __src_x, __intptr_t __src_y,
	                               __size_t __src_size_x, __size_t __src_size_y);

	/* Same as `fxo_fill()', but only fill in a pixel if:
	 * >> offset = bitskip + (<final_y> - dst_y) * bitscan + (<final_x> - dst_x);
	 * >> if ((((u8 *)bitmask)[offset / 8] & (1 << (7 - (offset % 8)))) != 0) {
	 * >>     FILL_PIXEL();
	 * >> }
	 * @param: bitskip: Number of leading bits to skip
	 * @param: bitscan: Length of a scanline within `bitmask' (in bits)
	 * This function is mainly here to facilitate the rendering of glyphs (s.a. fonts/tlft.h) */
	__ATTR_NONNULL_T((1, 7)) void
	(LIBVIDEO_GFX_CC *fxo_bitfill)(struct video_gfx *__restrict __self,
	                               __intptr_t __x, __intptr_t __y,
	                               video_color_t __color,
	                               __size_t __size_x, __size_t __size_y,
	                               void const *__restrict __bitmask,
	                               __uintptr_t __bitskip, __size_t __bitscan);

	/* Same as `fxo_bitfill()', but take source colors from `src' */
	__ATTR_NONNULL_T((1, 4, 9)) void
	(LIBVIDEO_GFX_CC *fxo_bitblit)(struct video_gfx *__self,
	                               __intptr_t __dst_x, __intptr_t __dst_y,
	                               struct video_gfx const *__src,
	                               __intptr_t __src_x, __intptr_t __src_y,
	                               __size_t __size_x, __size_t __size_y,
	                               void const *__restrict __bitmask,
	                               __uintptr_t __bitskip, __size_t __bitscan);

	/* Same as `fxo_bitfill()', however perform the blit while up-scaling the given bitmask.
	 * The  resulting  image   will  be   similar  (but  not   necessarily  identical)   to:
	 * >> struct video_buffer *temp;
	 * >> struct video_gfx temp_gfx;
	 * >> temp = video_buffer_create(VIDEO_BUFFER_AUTO, src_size_x, src_size_y,
	 * >>                            video_codec_lookup(VIDEO_CODEC_RGBA8888),
	 * >>                            NULL);
	 * >> temp->gfx(temp_gfx, GFX_BLENDINFO_OVERRIDE);
	 * >> temp_gfx.bitfill(0, 0, src_size_x, src_size_y, color, bitmask, bitskip);
	 * >> // NOTE: Pixels that aren't masked by `bitmask' may not necessary get blended during this call!
	 * >> self->stretch(dst_x, dst_y, dst_size_x, dst_size_y, &temp_gfx, 0, 0, src_size_x, src_size_y);
	 * >> destroy(temp); */
	__ATTR_NONNULL_T((1, 9)) void
	(LIBVIDEO_GFX_CC *fxo_bitstretchfill)(struct video_gfx *__restrict __self,
	                                      __intptr_t __dst_x, __intptr_t __dst_y,
	                                      __size_t __dst_size_x, __size_t __dst_size_y,
	                                      video_color_t __color,
	                                      __size_t __src_size_x, __size_t __src_size_y,
	                                      void const *__restrict __bitmask,
	                                      __uintptr_t __bitskip, __size_t __bitscan);

	/* Same as `fxo_bitstretchfill()' is for `fxo_bitfill()', but instead here for `fxo_bitblit()' */
	__ATTR_NONNULL_T((1, 6, 11)) void
	(LIBVIDEO_GFX_CC *fxo_bitstretchblit)(struct video_gfx *__self,
	                                      __intptr_t __dst_x, __intptr_t __dst_y,
	                                      __size_t __dst_size_x, __size_t __dst_size_y,
	                                      struct video_gfx const *__src,
	                                      __intptr_t __src_x, __intptr_t __src_y,
	                                      __size_t __src_size_x, __size_t __src_size_y,
	                                      void const *__restrict __bitmask,
	                                      __uintptr_t __bitskip, __size_t __bitscan);
};




#ifdef __cplusplus
__CXXDECL_BEGIN
#endif /* __cplusplus */

struct video_gfx {
	struct video_gfx_pxops vx_pxops;     /* [1..1][const] Graphics pixel operations. */
	struct video_gfx_ops  *vx_ops;       /* [1..1][const] Graphics operations. */
	struct video_buffer   *vx_buffer;    /* [1..1][const] The associated buffer. */
	gfx_blendmode_t        vx_blend;     /* [const] Blending mode. */
	__uintptr_t            vx_flags;     /* [const] Additional rendering flags (Set of `VIDEO_GFX_F*'). */
	video_color_t          vx_colorkey;  /* [const] Transparent color key (or any color with alpha=0 when disabled). */
	__intptr_t             vx_offt_x;    /* [const] Buffer starting offset in X (<= `vx_buffer->vb_size_x') */
	__intptr_t             vx_offt_y;    /* [const] Buffer starting offset in Y (<= `vx_buffer->vb_size_y') */
	__uintptr_t            vx_xmin;      /* [const] == vx_offt_x <= 0 ? 0 : vx_offt_x */
	__uintptr_t            vx_ymin;      /* [const] == vx_offt_y <= 0 ? 0 : vx_offt_y */
	__uintptr_t            vx_xend;      /* [const] Absolute buffer end coord in X (<= `vx_buffer->vb_size_x') */
	__uintptr_t            vx_yend;      /* [const] Absolute buffer end coord in Y (<= `vx_buffer->vb_size_y') */
	void                  *vx_driver[4]; /* [?..?] Driver-specific graphics data. */

	/* Return the API-visible clip rect offset in X or Y */
#define video_gfx_startx(self) (self)->vx_offt_x
#define video_gfx_starty(self) (self)->vx_offt_y
	/* Return the API-visible clip rect size in X or Y */
#define video_gfx_sizex(self)  ((__size_t)((__intptr_t)(self)->vx_xend - (self)->vx_offt_x))
#define video_gfx_sizey(self)  ((__size_t)((__intptr_t)(self)->vx_yend - (self)->vx_offt_y))


#define video_gfx_clip(self, result, start_x, start_y, size_x, size_y) \
	(*(self)->vx_buffer->vb_ops->vi_clipgfx)(self, result, start_x, start_y, size_x, size_y)
#define _video_gfx_getcolor(self, x, y) \
	(*(self)->vx_pxops.fxo_getcolor)(self, x, y)
#define _video_gfx_putcolor(self, x, y, color) \
	(*(self)->vx_pxops.fxo_putcolor)(self, x, y, color)
#define video_gfx_line(self, x1, y1, x2, y2, color) \
	(*(self)->vx_ops->fxo_line)(self, x1, y1, x2, y2, color)
#define video_gfx_vline(self, x, y, length, color) \
	(*(self)->vx_ops->fxo_vline)(self, x, y, length, color)
#define video_gfx_hline(self, x, y, length, color) \
	(*(self)->vx_ops->fxo_hline)(self, x, y, length, color)
#define video_gfx_fill(self, x, y, size_x, size_y, color) \
	(*(self)->vx_ops->fxo_fill)(self, x, y, size_x, size_y, color)
#define video_gfx_fillall(self, color) \
	video_gfx_fill(self, 0, 0, (__size_t)-1, (__size_t)-1, color)
#define video_gfx_rect(self, x, y, size_x, size_y, color) \
	(*(self)->vx_ops->fxo_rect)(self, x, y, size_x, size_y, color)
#define video_gfx_blit(self, dst_x, dst_y, src, src_x, src_y, size_x, size_y) \
	(*(self)->vx_ops->fxo_blit)(self, dst_x, dst_y, src, src_x, src_y, size_x, size_y)
#define video_gfx_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src, src_x, src_y, src_size_x, src_size_y) \
	(*(self)->vx_ops->fxo_stretch)(self, dst_x, dst_y, dst_size_x, dst_size_y, src, src_x, src_y, src_size_x, src_size_y)
#define video_gfx_bitfill(self, x, y, color, size_x, size_y, bigtmask, bitskip, bitscan) \
	(*(self)->vx_ops->fxo_bitfill)(self, x, y, color, size_x, size_y, bigtmask, bitskip, bitscan)
#define video_gfx_bitblit(self, dst_x, dst_y, src, src_x, src_y, size_x, size_y, bigtmask, bitskip, bitscan) \
	(*(self)->vx_ops->fxo_bitblit)(self, dst_x, dst_y, src, src_x, src_y, size_x, size_y, bigtmask, bitskip, bitscan)
#define video_gfx_bitstretchfill(self, dst_x, dst_y, dst_sizex, dst_sizey, color, src_size_x, src_size_y, bigtmask, bitskip, bitscan) \
	(*(self)->vx_ops->fxo_bitstretchfill)(self, dst_x, dst_y, dst_sizex, dst_sizey, color, src_size_x, src_size_y, bigtmask, bitskip, bitscan)
#define video_gfx_bitstretchblit(self, dst_x, dst_y, dst_sizex, dst_sizey, src, src_x, src_y, src_size_x, src_size_y, bigtmask, bitskip, bitscan) \
	(*(self)->vx_ops->fxo_bitstretchblit)(self, dst_x, dst_y, dst_sizex, dst_sizey, src, src_x, src_y, src_size_x, src_size_y, bigtmask, bitskip, bitscan)

#ifdef __cplusplus
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("clip")
#pragma push_macro("getcolor")
#pragma push_macro("putcolor")
#pragma push_macro("line")
#pragma push_macro("vline")
#pragma push_macro("hline")
#pragma push_macro("fill")
#pragma push_macro("rect")
#pragma push_macro("blit")
#pragma push_macro("stretch")
#pragma push_macro("bitfill")
#pragma push_macro("bitblit")
#pragma push_macro("bitstretchfill")
#pragma push_macro("bitstretchblit")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef clip
#undef getcolor
#undef putcolor
#undef line
#undef vline
#undef hline
#undef fill
#undef rect
#undef blit
#undef stretch
#undef bitfill
#undef bitblit
#undef bitstretchfill
#undef bitstretchblit

public:
	/* Create a secondary GFX context for a given clip  rectangle
	 * that is interpreted relative to the clip rectangle of this
	 * GFX object.
	 * NOTE: Implemented in ./buffer.h because the implementation
	 *       requires use of `struct video_buffer', which may not
	 *       have been defined yet at this point! */
	__CXX_CLASSMEMBER struct video_gfx &
	LIBVIDEO_GFX_CC clip(struct video_gfx &__result,
	                     __intptr_t __start_x, __intptr_t __start_y,
	                     __size_t __size_x, __size_t __size_y) const;
	/* Modify the clip-rect of `this' GFX context. (always returns `*this') */
	__CXX_CLASSMEMBER struct video_gfx &
	LIBVIDEO_GFX_CC clip(__intptr_t __start_x, __intptr_t __start_y,
	                     __size_t __size_x, __size_t __size_y);


	/* Get a pixel */
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<(std::is_signed<TX>::value || std::is_unsigned<TX>::value) &&
	                                          (std::is_signed<TY>::value || std::is_unsigned<TY>::value),
	                                          video_color_t>::type
	LIBVIDEO_GFX_CC getcolor(TX __x, TY __y) const {
		__intptr_t __used_x = (__intptr_t)__x + vx_offt_x;
		__intptr_t __used_y = (__intptr_t)__y + vx_offt_y;
		if __unlikely(__used_x < (__intptr_t)vx_xmin || __used_y < (__intptr_t)vx_ymin ||
		              __used_x >= (__intptr_t)vx_xend || __used_y >= (__intptr_t)vx_yend)
			return 0;
		return _video_gfx_getcolor(this, (__uintptr_t)__used_x, (__uintptr_t)__used_y);
	}

	/* Place a colored pixel ontop of the graphic */
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<(std::is_signed<TX>::value || std::is_unsigned<TX>::value) &&
	                                          (std::is_signed<TY>::value || std::is_unsigned<TY>::value),
	                                          void>::type
	LIBVIDEO_GFX_CC putcolor(TX __x, TY __y, video_color_t __color) {
		__intptr_t __used_x = (__intptr_t)__x + vx_offt_x;
		__intptr_t __used_y = (__intptr_t)__y + vx_offt_y;
		if __unlikely(__used_x < (__intptr_t)vx_xmin || __used_y < (__intptr_t)vx_ymin ||
		              __used_x >= (__intptr_t)vx_xend || __used_y >= (__intptr_t)vx_yend)
			return;
		_video_gfx_putcolor(this, (__uintptr_t)__used_x, (__uintptr_t)__used_y, __color);
	}

	/* Draw a line */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC line(__intptr_t __x1, __intptr_t __y1,
	                                            __intptr_t __x2, __intptr_t __y2,
	                                            video_color_t __color) {
		video_gfx_line(this, __x1, __y1, __x2, __y2, __color);
	}

	/* Vertical line */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC vline(__intptr_t __x, __intptr_t __y,
	                                             __size_t __length, video_color_t __color) {
		video_gfx_vline(this, __x, __y, __length, __color);
	}

	/* Horizontal line */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC hline(__intptr_t __x, __intptr_t __y,
	                                             __size_t __length, video_color_t __color) {
		video_gfx_hline(this, __x, __y, __length, __color);
	}

	/* Fill an area with a solid color. */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC fill(__intptr_t __x, __intptr_t __y,
	                                            __size_t __size_x, __size_t __size_y,
	                                            video_color_t __color) {
		video_gfx_fill(this, __x, __y, __size_x, __size_y, __color);
	}
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC fill(video_color_t __color) {
		video_gfx_fillall(this, __color);
	}

	/* Outline an area with a rectangle. */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC
	rect(__intptr_t __x, __intptr_t __y, __size_t __size_x, __size_t __size_y, video_color_t __color) {
		video_gfx_rect(this, __x, __y, __size_x, __size_y, __color);
	}

	/* Blit the contents of another video buffer into this one. */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC blit(__intptr_t __dst_x, __intptr_t __dst_y,
	                                            struct video_gfx const &__src,
	                                            __intptr_t __src_x, __intptr_t __src_y,
	                                            __size_t __size_x, __size_t __size_y) {
		video_gfx_blit(this, __dst_x, __dst_y,
		               &__src, __src_x, __src_y,
		               __size_x, __size_y);
	}

	/* Same as `fxo_blit', but stretch the contents */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC stretch(__intptr_t __dst_x, __intptr_t __dst_y,
	                                               __size_t __dst_size_x, __size_t __dst_size_y,
	                                               struct video_gfx const &__src,
	                                               __intptr_t __src_x, __intptr_t __src_y,
	                                               __size_t __src_size_x, __size_t __src_size_y) {
		video_gfx_stretch(this, __dst_x, __dst_y, __dst_size_x, __dst_size_y,
		                  &__src, __src_x, __src_y, __src_size_x, __src_size_y);
	}

	/* Fill an area with a solid color. */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC bitfill(__intptr_t __x, __intptr_t __y,
	                                               video_color_t __color,
	                                               __size_t __size_x, __size_t __size_y,
	                                               void const *__restrict __bitmask,
	                                               __uintptr_t __bitskip, __size_t __bitscan) {
		video_gfx_bitfill(this, __x, __y, __color, __size_x, __size_y,
		                  __bitmask, __bitskip, __bitscan);
	}

	/* Blit the contents of another video buffer into this one. */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC bitblit(__intptr_t __dst_x, __intptr_t __dst_y,
	                                               struct video_gfx const &__src,
	                                               __intptr_t __src_x, __intptr_t __src_y,
	                                               __size_t __size_x, __size_t __size_y,
	                                               void const *__restrict __bitmask,
	                                               __uintptr_t __bitskip, __size_t __bitscan) {
		video_gfx_bitblit(this, __dst_x, __dst_y, &__src, __src_x, __src_y,
		                  __size_x, __size_y, __bitmask, __bitskip, __bitscan);
	}

	/* Same as `fxo_bitfill()', however perform the blit while up-scaling the given bitmask. */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC bitstretchfill(__intptr_t __dst_x, __intptr_t __dst_y,
	                                                      __size_t __dst_size_x, __size_t __dst_size_y,
	                                                      video_color_t __color,
	                                                      __size_t __src_size_x, __size_t __src_size_y,
	                                                      void const *__restrict __bitmask,
	                                                      __uintptr_t __bitskip, __size_t __bitscan) {
		video_gfx_bitstretchfill(this, __dst_x, __dst_y, __dst_size_x, __dst_size_y,
		                         __color, __src_size_x, __src_size_y,
		                         __bitmask, __bitskip, __bitscan);
	}

	/* Same as `fxo_bitstretchfill()' is for `fxo_bitfill()', but instead here for `fxo_bitblit()' */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC bitstretchblit(__intptr_t __dst_x, __intptr_t __dst_y,
	                                                      __size_t __dst_size_x, __size_t __dst_size_y,
	                                                      struct video_gfx const *__src,
	                                                      __intptr_t __src_x, __intptr_t __src_y,
	                                                      __size_t __src_size_x, __size_t __src_size_y,
	                                                      void const *__restrict __bitmask,
	                                                      __uintptr_t __bitskip, __size_t __bitscan) {
		video_gfx_bitstretchblit(this, __dst_x, __dst_y, __dst_size_x, __dst_size_y,
		                         __src, __src_x, __src_y, __src_size_x, __src_size_y,
		                         __bitmask, __bitskip, __bitscan);
	}


#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("bitstretchblit")
#pragma pop_macro("bitstretchfill")
#pragma pop_macro("bitblit")
#pragma pop_macro("bitfill")
#pragma pop_macro("stretch")
#pragma pop_macro("blit")
#pragma pop_macro("rect")
#pragma pop_macro("fill")
#pragma pop_macro("hline")
#pragma pop_macro("vline")
#pragma pop_macro("line")
#pragma pop_macro("putcolor")
#pragma pop_macro("getcolor")
#pragma pop_macro("clip")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __cplusplus */
};




#ifdef __cplusplus
__CXXDECL_END
#endif /* __cplusplus */
#endif /* __CC__ */



__DECL_END

#endif /* !_LIBVIDEO_GFX_GFX_H */
