/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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

#define GFX_BLENDINFO_GET_SRCRGB(info) (__CCAST(__uint8_t)((info)&0xf))        /* Source color (One of `GFX_BLENDMODE_*') */
#define GFX_BLENDINFO_GET_SRCA(info)   (__CCAST(__uint8_t)(((info)>>4)&0xf))   /* Source alpha (One of `GFX_BLENDMODE_*') */
#define GFX_BLENDINFO_GET_DSTRGB(info) (__CCAST(__uint8_t)(((info)>>8)&0xf))   /* Destination color (One of `GFX_BLENDMODE_*') */
#define GFX_BLENDINFO_GET_DSTA(info)   (__CCAST(__uint8_t)(((info)>>12)&0xf))  /* Destination alpha (One of `GFX_BLENDMODE_*') */
#define GFX_BLENDINFO_GET_FUNRGB(info) (__CCAST(__uint8_t)(((info)>>15)&0x7))  /* Color blend function (One of `GFX_BLENDFUNC_*') */
#define GFX_BLENDINFO_GET_FUNA(info)   (__CCAST(__uint8_t)(((info)>>18)&0x7))  /* Alpha blend function (One of `GFX_BLENDFUNC_*') */
#define GFX_BLENDINFO_GET_CR(info)     (__CCAST(__uint8_t)(((info)>>56)&0xff)) /* Constant color red */
#define GFX_BLENDINFO_GET_CG(info)     (__CCAST(__uint8_t)(((info)>>48)&0xff)) /* Constant color green */
#define GFX_BLENDINFO_GET_CB(info)     (__CCAST(__uint8_t)(((info)>>40)&0xff)) /* Constant color blue */
#define GFX_BLENDINFO_GET_CA(info)     (__CCAST(__uint8_t)(((info)>>32)&0xff)) /* Constant color alpha */

/* Helper macros for creating blend modes.
 * @param: src:  Source color/alpha (One of `GFX_BLENDMODE_*')
 * @param: dst:  Destination color/alpha (One of `GFX_BLENDMODE_*')
 * @param: func: Color/alpha blend function (One of `GFX_BLENDFUNC_*') */
#define GFX_BLENDINFO(src, dst, func) \
	GFX_BLENDINFO_EX(src, src, dst, dst, func, func, 0, 0, 0, 0)
#define GFX_BLENDINFO_EX(rgb_src, a_src, rgb_dst, a_dst, \
                         rgb_fun, a_fun, cr, cg, cb, ca) \
	(__CCAST(gfx_blendmode_t)((rgb_src)&0xf) |           \
	 (__CCAST(gfx_blendmode_t)((a_src)&0xf) << 4) |      \
	 (__CCAST(gfx_blendmode_t)((rgb_dst)&0xf) << 8) |    \
	 (__CCAST(gfx_blendmode_t)((a_dst)&0xf) << 12) |     \
	 (__CCAST(gfx_blendmode_t)((rgb_fun)&0x7) << 15) |   \
	 (__CCAST(gfx_blendmode_t)((a_fun)&0x7) << 18) |     \
	 (__CCAST(gfx_blendmode_t)((cr)&0xff) << 56) |       \
	 (__CCAST(gfx_blendmode_t)((cg)&0xff) << 48) |       \
	 (__CCAST(gfx_blendmode_t)((cb)&0xff) << 40) |       \
	 (__CCAST(gfx_blendmode_t)((ca)&0xff) << 32))
#ifdef __CC__
typedef __uint64_t gfx_blendmode_t;
#endif /* __CC__ */

/* Conventional alpha blending */
#define GFX_BLENDINFO_ALPHA \
	GFX_BLENDINFO(GFX_BLENDMODE_SRC_ALPHA, GFX_BLENDMODE_ONE_MINUS_SRC_ALPHA, GFX_BLENDFUNC_ADD)

/* Override destination (no blending done) */
#define GFX_BLENDINFO_OVERRIDE \
	GFX_BLENDINFO(GFX_BLENDMODE_ONE, GFX_BLENDMODE_ZERO, GFX_BLENDFUNC_ADD)



/* Video graphic flags. */
#define VIDEO_GFX_FNORMAL     0x0000 /* Normal render flags. */
#define VIDEO_GFX_FAALINES    0x0001 /* Render smooth lines. */
#define VIDEO_GFX_FLINEARBLIT 0x0002 /* Use linear interpolation for stretch() (else: use nearest) */


#ifdef __CC__
struct video_buffer;
struct video_buffer_gfx;

struct video_gfx_ops {
	/* All of the following callbacks are [1..1] */

	/* Get the color of a pixel */
	video_color_t (LIBVIDEO_GFX_CC *fxo_getcolor)(struct video_buffer_gfx *__restrict self,
	                                              __uintptr_t x, __uintptr_t y);
	/* Place a colored pixel ontop of the graphic */
	void (LIBVIDEO_GFX_CC *fxo_putcolor)(struct video_buffer_gfx *__restrict self,
	                                     __uintptr_t x, __uintptr_t y, video_color_t color);
	/* Draw a line */
	void (LIBVIDEO_GFX_CC *fxo_line)(struct video_buffer_gfx *__restrict self,
	                                 __intptr_t x1, __intptr_t y1,
	                                 __intptr_t x2, __intptr_t y2,
	                                 video_color_t color);
	/* Vertical line */
	void (LIBVIDEO_GFX_CC *fxo_vline)(struct video_buffer_gfx *__restrict self, __uintptr_t x,
	                                  __uintptr_t y1, __uintptr_t y2, video_color_t color);
	/* Horizontal line */
	void (LIBVIDEO_GFX_CC *fxo_hline)(struct video_buffer_gfx *__restrict self, __uintptr_t y,
	                                  __uintptr_t x1, __uintptr_t x2, video_color_t color);
	/* Fill an area with a solid color. */
	void (LIBVIDEO_GFX_CC *fxo_fill)(struct video_buffer_gfx *__restrict self,
	                                 __uintptr_t x, __uintptr_t y,
	                                 __size_t size_x, __size_t size_y,
	                                 video_color_t color);
	/* Outline an area with a rectangle. */
	void (LIBVIDEO_GFX_CC *fxo_rect)(struct video_buffer_gfx *__restrict self,
	                                 __uintptr_t x, __uintptr_t y,
	                                 __size_t size_x, __size_t size_y,
	                                 video_color_t color);
	/* Blit the contents of another video buffer into this one. */
	void (LIBVIDEO_GFX_CC *fxo_blit)(struct video_buffer_gfx *__restrict self,
	                                 __intptr_t dst_x, __intptr_t dst_y,
	                                 struct video_buffer_gfx *__restrict src,
	                                 __intptr_t src_x, __intptr_t src_y,
	                                 __size_t size_x, __size_t size_y);
	/* Same as `fxo_blit', but stretch the contents */
	void (LIBVIDEO_GFX_CC *fxo_stretch)(struct video_buffer_gfx *__restrict self,
	                                    __intptr_t dst_x, __intptr_t dst_y,
	                                    __size_t dst_size_x, __size_t dst_size_y,
	                                    struct video_buffer_gfx *__restrict src,
	                                    __intptr_t src_x, __intptr_t src_y,
	                                    __size_t src_size_x, __size_t src_size_y);
};

/* Default GFX functions (using get/put pixel) */
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_LINE)(struct video_buffer_gfx *__restrict self, __intptr_t x1, __intptr_t y1, __intptr_t x2, __intptr_t y2, video_color_t color);
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_VLINE)(struct video_buffer_gfx *__restrict self, __uintptr_t x, __uintptr_t y1, __uintptr_t y2, video_color_t color);
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_HLINE)(struct video_buffer_gfx *__restrict self, __uintptr_t y, __uintptr_t x1, __uintptr_t x2, video_color_t color);
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_FILL)(struct video_buffer_gfx *__restrict self, __uintptr_t x, __uintptr_t y, __size_t size_x, __size_t size_y, video_color_t color);
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_RECT)(struct video_buffer_gfx *__restrict self, __uintptr_t x, __uintptr_t y, __size_t size_x, __size_t size_y, video_color_t color);
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_BLIT)(struct video_buffer_gfx *__restrict self, __intptr_t dst_x, __intptr_t dst_y, struct video_buffer_gfx *__restrict src, __intptr_t src_x, __intptr_t src_y, __size_t size_x, __size_t size_y);
typedef void (LIBVIDEO_GFX_CC *PVIDEO_GFX_DEFAULTGFX_STRETCH)(struct video_buffer_gfx *__restrict self, __intptr_t dst_x, __intptr_t dst_y, __size_t dst_size_x, __size_t dst_size_y, struct video_buffer_gfx *__restrict src, __intptr_t src_x, __intptr_t src_y, __size_t src_size_x, __size_t src_size_y);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_line(struct video_buffer_gfx *__restrict self, __intptr_t x1, __intptr_t y1, __intptr_t x2, __intptr_t y2, video_color_t color);
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_vline(struct video_buffer_gfx *__restrict self, __uintptr_t x, __uintptr_t y1, __uintptr_t y2, video_color_t color);
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_hline(struct video_buffer_gfx *__restrict self, __uintptr_t y, __uintptr_t x1, __uintptr_t x2, video_color_t color);
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_fill(struct video_buffer_gfx *__restrict self, __uintptr_t x, __uintptr_t y, __size_t size_x, __size_t size_y, video_color_t color);
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_rect(struct video_buffer_gfx *__restrict self, __uintptr_t x, __uintptr_t y, __size_t size_x, __size_t size_y, video_color_t color);
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_blit(struct video_buffer_gfx *__restrict self, __intptr_t dst_x, __intptr_t dst_y, struct video_buffer_gfx *__restrict src, __intptr_t src_x, __intptr_t src_y, __size_t size_x, __size_t size_y);
LIBVIDEO_GFX_DECL void LIBVIDEO_GFX_CC video_gfx_defaultgfx_stretch(struct video_buffer_gfx *__restrict self, __intptr_t dst_x, __intptr_t dst_y, __size_t dst_size_x, __size_t dst_size_y, struct video_buffer_gfx *__restrict src, __intptr_t src_x, __intptr_t src_y, __size_t src_size_x, __size_t src_size_y);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


#ifdef __cplusplus
extern "C++" {
#endif /* __cplusplus */

struct video_buffer_gfx {
	struct video_gfx_ops bfx_ops;       /* [const] Graphics operations. */
	struct video_buffer *bfx_buffer;    /* [1..1][const] The associated buffer. */
	gfx_blendmode_t      bfx_blend;     /* [const] Blending mode. */
	__uintptr_t          bfx_flags;     /* [const] Additional rendering flags (Set of `VIDEO_GFX_F*'). */
	video_color_t        bfx_colorkey;  /* [const] Transparent color key (or any color with alpha=0 when disabled). */
	void                *bfx_driver[4]; /* [?..?] Driver-specific graphics data. */

#ifdef __cplusplus
public:
	/* Get a pixel */
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<T>::value, video_color_t>::type
	LIBVIDEO_GFX_CC getcolor(T x, T y) {
		return (*bfx_ops.fxo_getcolor)(this, (__uintptr_t)x, (__uintptr_t)y);
	}
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<T>::value, video_color_t>::type
	LIBVIDEO_GFX_CC getcolor(T x, T y) {
		typedef typename std::make_unsigned<T>::type TU;
		if (x < 0 || y < 0)
			return 0;
		return getcolor<TU>((TU)x, (TU)y);
	}

	/* Place a colored pixel ontop of the graphic */
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<T>::value, void>::type
	LIBVIDEO_GFX_CC putcolor(T x, T y, video_color_t color) {
		(*bfx_ops.fxo_putcolor)(this, (__uintptr_t)x, (__uintptr_t)y, color);
	}
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<T>::value, void>::type
	putcolor(T x, T y, video_color_t color) {
		typedef typename std::make_unsigned<T>::type TU;
		if (x >= 0 && y >= 0)
			putcolor<TU>((TU)x, (TU)y, color);
	}

	/* Draw a line */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC line(__intptr_t x1, __intptr_t y1,
	                                            __intptr_t x2, __intptr_t y2,
	                                            video_color_t color) {
		(*bfx_ops.fxo_line)(this, x1, y1, x2, y2, color);
	}

	/* Vertical line */
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<T>::value, void>::type
	LIBVIDEO_GFX_CC vline(T x, T y1, T y2, video_color_t color) {
		(*bfx_ops.fxo_vline)(this, (__uintptr_t)x, (__uintptr_t)y1, (__uintptr_t)y2, color);
	}
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<TX>::value && std::is_unsigned<TY>::value, void>::type
	LIBVIDEO_GFX_CC vline(TX x, TY y1, TY y2, video_color_t color) {
		if (x < 0)
			return;
		vline((__uintptr_t)x, (__uintptr_t)y1, (__uintptr_t)y2, color);
	}
	template<class TX, class TY>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<TX>::value && std::is_signed<TY>::value, void>::type
	LIBVIDEO_GFX_CC vline(TX x, TY y1, TY y2, video_color_t color) {
		if (y1 < 0)
			y1 = 0;
		if (y2 < 0)
			y2 = 0;
		vline((__uintptr_t)x, (__uintptr_t)y1, (__uintptr_t)y2, color);
	}
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<T>::value, void>::type
	LIBVIDEO_GFX_CC vline(T x, T y1, T y2, video_color_t color) {
		typedef typename std::make_unsigned<T>::type TU;
		if (x < 0)
			return;
		vline((TU)x, y1, y2, color);
	}

	/* Horizontal line */
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<T>::value, void>::type
	LIBVIDEO_GFX_CC hline(T y, T x1, T x2, video_color_t color) {
		(*bfx_ops.fxo_hline)(this, (__uintptr_t)y, (__uintptr_t)x1, (__uintptr_t)x2, color);
	}
	template<class TY, class TX>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<TY>::value && std::is_unsigned<TX>::value, void>::type
	LIBVIDEO_GFX_CC hline(TY y, TX x1, TX x2, video_color_t color) {
		if (y < 0)
			return;
		hline((__uintptr_t)y, (__uintptr_t)x1, (__uintptr_t)x2, color);
	}
	template<class TY, class TX>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_unsigned<TY>::value && std::is_signed<TX>::value, void>::type
	LIBVIDEO_GFX_CC hline(TY y, TX x1, TX x2, video_color_t color) {
		if (x1 < 0)
			x1 = 0;
		if (x2 < 0)
			x2 = 0;
		hline((__uintptr_t)y, (__uintptr_t)x1, (__uintptr_t)x2, color);
	}
	template<class T>
	__CXX_CLASSMEMBER typename std::enable_if<std::is_signed<T>::value, void>::type
	LIBVIDEO_GFX_CC hline(T y, T x1, T x2, video_color_t color) {
		typedef typename std::make_unsigned<T>::type TU;
		if (y < 0)
			return;
		hline((TU)y, x1, x2, color);
	}

	/* Fill an area with a solid color. */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC fill(__uintptr_t x, __uintptr_t y,
	                                            __size_t size_x, __size_t size_y,
	                                            video_color_t color) {
		(*bfx_ops.fxo_fill)(this, x, y, size_x, size_y, color);
	}
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC fill(__intptr_t x, __intptr_t y,
	                                            __size_t size_x, __size_t size_y,
	                                            video_color_t color) {
		if (x < 0) {
			x = -x;
			if (size_x <= (__uintptr_t)x)
				return;
			size_x -= (__uintptr_t)x;
			x = 0;
		}
		if (y < 0) {
			y = -y;
			if (size_y <= (__uintptr_t)y)
				return;
			size_y -= (__uintptr_t)y;
			y = 0;
		}
		fill((__uintptr_t)x, (__uintptr_t)y, size_x, size_y, color);
	}

	/* Outline an area with a rectangle. */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC rect(__uintptr_t x, __uintptr_t y,
	                                            __size_t size_x, __size_t size_y,
	                                            video_color_t color) {
		(*bfx_ops.fxo_rect)(this, x, y, size_x, size_y, color);
	}
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC rect(__intptr_t x, __intptr_t y,
	                                            __size_t size_x, __size_t size_y,
	                                            video_color_t color) {
		if (x < 0) {
			x = -x;
			if (size_x <= (__uintptr_t)x)
				return;
			size_x -= (__uintptr_t)x;
			x = 0;
		}
		if (y < 0) {
			y = -y;
			if (size_y <= (__uintptr_t)y)
				return;
			size_y -= (__uintptr_t)y;
			y = 0;
		}
		rect((__uintptr_t)x, (__uintptr_t)y, size_x, size_y, color);
	}

	/* Blit the contents of another video buffer into this one. */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC blit(__intptr_t dst_x, __intptr_t dst_y,
	                                            struct video_buffer_gfx *__restrict src,
	                                            __intptr_t src_x, __intptr_t src_y,
	                                            __size_t size_x, __size_t size_y) {
		(*bfx_ops.fxo_blit)(this, dst_x, dst_y,
		                    src, src_x, src_y,
		                    size_x, size_y);
	}

	/* Same as `fxo_blit', but stretch the contents */
	__CXX_CLASSMEMBER void LIBVIDEO_GFX_CC stretch(__intptr_t dst_x, __intptr_t dst_y,
	                                               __size_t dst_size_x, __size_t dst_size_y,
	                                               struct video_buffer_gfx *__restrict src,
	                                               __intptr_t src_x, __intptr_t src_y,
	                                               __size_t src_size_x, __size_t src_size_y) {
		(*bfx_ops.fxo_stretch)(this, dst_x, dst_y, dst_size_x, dst_size_y,
		                       src, src_x, src_y, src_size_x, src_size_y);
	}

#endif /* __cplusplus */
};

#ifdef __cplusplus
} /* extern "C++" */
#endif /* __cplusplus */
#endif /* __CC__ */



__DECL_END

#endif /* !_LIBVIDEO_GFX_GFX_H */
