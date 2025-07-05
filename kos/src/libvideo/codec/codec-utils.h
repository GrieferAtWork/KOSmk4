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
#ifndef GUARD_LIBVIDEO_CODEC_CODEC_UTILS_H
#define GUARD_LIBVIDEO_CODEC_CODEC_UTILS_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/__byteswap.h>
#include <hybrid/align.h>
#include <hybrid/byteorder.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <kos/types.h>
#include <sys/param.h>

#include <stddef.h>

#include <libvideo/codec/api.h>
#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>

DECL_BEGIN

#if defined(NDEBUG) || 1
#if 1 /* Turn codec assertions into compile-time assumptions for max speed */
#ifdef __CRT_UBSAN_BUILTIN_UNREACHABLE
#undef __CRT_UBSAN_BUILTIN_UNREACHABLE
#undef __builtin_unreachable /* Disable binding of "__ubsan_handle_builtin_unreachable" */
#endif /* __CRT_UBSAN_BUILTIN_UNREACHABLE */
#define codec_assert(x)       __builtin_assume(x)
#define codec_assertf(x, ...) __builtin_assume(x)
#else
#define codec_assert(x)       (void)0
#define codec_assertf(x, ...) (void)0
#endif
#else /* ... */
#include <assert.h>
#define codec_assert  assert
#define codec_assertf assertf
#endif /* !... */

#undef video_codec_setpixel_t
#undef vc_setpixel

/************************************************************************/
/* CODEC DEFINITION UTILS                                               */
/************************************************************************/

#ifndef VIDEO_CODEC_SETPIXEL3_CC
#define VIDEO_CODEC_SETPIXEL3_CC /* nothing */
#endif /* !VIDEO_CODEC_SETPIXEL3_CC */

#ifndef CONFIG_VIDEO_CODEC_HAVE_PIXEL64
#define video_channel16_t video_channel_t
#define video_pixel64_t   video_pixel_t
#define video_color64_t   video_color_t
#define DEFINE_PIXEL2COLOR64_WRAPPER32(decl, foo_pixel2color, foo_pixel2color64) /* nothing */
#define DEFINE_COLOR2PIXEL64_WRAPPER32(decl, foo_color2pixel, foo_color2pixel64) /* nothing */
#define DEFINE_PIXEL64_IO_WRAPPERS(f, f_, f64, f64_)                             /* nothing */
#else /* !CONFIG_VIDEO_CODEC_HAVE_PIXEL64 */
#define DEFINE_PIXEL2COLOR64_WRAPPER32(decl, foo_pixel2color, foo_pixel2color64)             \
	decl WUNUSED NONNULL((1)) video_color64_t CC                                             \
	foo_pixel2color64(struct video_format const *__restrict format, video_pixel64_t pixel) { \
		video_color_t c = foo_pixel2color(format, (video_pixel_t)pixel);                     \
		return VIDEO_COLOR64_FROM_COLOR(c);                                                  \
	}
#define DEFINE_COLOR2PIXEL64_WRAPPER32(decl, foo_color2pixel, foo_color2pixel64)             \
	decl WUNUSED NONNULL((1)) video_pixel64_t CC                                             \
	foo_color2pixel64(struct video_format const *__restrict format, video_color64_t color) { \
		video_color_t c = VIDEO_COLOR_FROM_COLOR64(color);                                   \
		return (video_pixel64_t)foo_color2pixel(format, c);                                  \
	}
#define DEFINE_PIXEL64_IO_WRAPPERS(decl, f, f_, f64, f64_)                                 \
	decl ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t CC                       \
	f64(f64_, getpixel)(byte_t const *__restrict line, video_coord_t x) {                  \
		return (video_pixel64_t)f(f_, getpixel)(line, x);                                  \
	}                                                                                      \
	decl ATTR_COLD NONNULL((1)) void CC                                                    \
	f64(f64_, setpixel)(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel) { \
		f(f_, setpixel)(line, x, (video_pixel_t)pixel);                                    \
	}                                                                                      \
	decl ATTR_COLD NONNULL((1)) void CC                                                    \
	f64(f64_, linefill)(byte_t *__restrict line, video_coord_t x,                          \
	                    video_pixel64_t pixel, video_dim_t num_pixels) {                   \
		f(f_, linefill)(line, x, (video_pixel_t)pixel, num_pixels);                        \
	}                                                                                      \
	decl ATTR_COLD NONNULL((1)) void CC                                                    \
	f64(f64_, vertfill)(byte_t *__restrict line, video_coord_t x, size_t stride,           \
	                    video_pixel64_t pixel, video_dim_t num_pixels) {                   \
		f(f_, vertfill)(line, x, stride, (video_pixel_t)pixel, num_pixels);                \
	}                                                                                      \
	decl ATTR_COLD NONNULL((1)) void CC                                                    \
	f64(f64_, rectfill)(byte_t *__restrict line, video_coord_t x, size_t stride,           \
	                    video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y) {   \
		f(f_, rectfill)(line, x, stride, (video_pixel_t)pixel, size_x, size_y);            \
	}
#endif /* CONFIG_VIDEO_CODEC_HAVE_PIXEL64 */
#define DEFINE_PIXEL64_WRAPPERS(decl, foo)                                       \
	DEFINE_PIXEL2COLOR64_WRAPPER32(decl, foo##_pixel2color, foo##_pixel2color64) \
	DEFINE_COLOR2PIXEL64_WRAPPER32(decl, foo##_color2pixel, foo##_color2pixel64)


#define DEFINE_PIXEL64_IO_WRAPPERS__WITH_PREFIX__MAP_IO(prefix, x)   prefix##x
#define DEFINE_PIXEL64_IO_WRAPPERS__WITH_PREFIX__MAP_IO64(prefix, x) prefix##x##_64
#define DEFINE_PIXEL64_IO_WRAPPERS__WITH_PREFIX(decl, prefix)                                 \
	DEFINE_PIXEL64_IO_WRAPPERS(decl, DEFINE_PIXEL64_IO_WRAPPERS__WITH_PREFIX__MAP_IO, prefix, \
	                           DEFINE_PIXEL64_IO_WRAPPERS__WITH_PREFIX__MAP_IO64, prefix)

#define DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX__MAP_IO(suffix, x)   x##suffix
#define DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX__MAP_IO64(suffix, x) x##suffix##_64
#define DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX(decl, suffix)                                 \
	DEFINE_PIXEL64_IO_WRAPPERS(decl, DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX__MAP_IO, suffix, \
	                           DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX__MAP_IO64, suffix)





#ifdef CONFIG_VIDEO_CODEC_HAVE_PIXEL64
#define SET_vc_pixel2color64_STATIC_INITIALIZER(v) v,
#define SET_vc_color2pixel64_STATIC_INITIALIZER(v) v,
#define SET_vc_getpixel64_STATIC_INITIALIZER(v)    v,
#define SET_vc_setpixel64_STATIC_INITIALIZER(v)    v,
#define SET_vc_linefill64_STATIC_INITIALIZER(v)    v,
#define SET_vc_vertfill64_STATIC_INITIALIZER(v)    v,
#define SET_vc_rectfill64_STATIC_INITIALIZER(v)    v,
#define SET_vc_pixel2color64_INITIALIZER(p, v)     p.vc_pixel2color64 = v;
#define SET_vc_color2pixel64_INITIALIZER(p, v)     p.vc_color2pixel64 = v;
#define SET_vc_getpixel64_INITIALIZER(p, v)        p.vc_getpixel64 = v;
#define SET_vc_setpixel64_INITIALIZER(p, v)        p.vc_setpixel64 = v;
#define SET_vc_linefill64_INITIALIZER(p, v)        p.vc_linefill64 = v;
#define SET_vc_vertfill64_INITIALIZER(p, v)        p.vc_vertfill64 = v;
#define SET_vc_rectfill64_INITIALIZER(p, v)        p.vc_rectfill64 = v;
#else /* CONFIG_VIDEO_CODEC_HAVE_PIXEL64 */
#define SET_vc_pixel2color64_STATIC_INITIALIZER(v) /* nothing */
#define SET_vc_color2pixel64_STATIC_INITIALIZER(v) /* nothing */
#define SET_vc_getpixel64_STATIC_INITIALIZER(v)    /* nothing */
#define SET_vc_setpixel64_STATIC_INITIALIZER(v)    /* nothing */
#define SET_vc_linefill64_STATIC_INITIALIZER(v)    /* nothing */
#define SET_vc_vertfill64_STATIC_INITIALIZER(v)    /* nothing */
#define SET_vc_rectfill64_STATIC_INITIALIZER(v)    /* nothing */
#define SET_vc_pixel2color64_INITIALIZER(p, v)     /* nothing */
#define SET_vc_color2pixel64_INITIALIZER(p, v)     /* nothing */
#define SET_vc_getpixel64_INITIALIZER(p, v)        /* nothing */
#define SET_vc_setpixel64_INITIALIZER(p, v)        /* nothing */
#define SET_vc_linefill64_INITIALIZER(p, v)        /* nothing */
#define SET_vc_vertfill64_INITIALIZER(p, v)        /* nothing */
#define SET_vc_rectfill64_INITIALIZER(p, v)        /* nothing */
#endif /* !CONFIG_VIDEO_CODEC_HAVE_PIXEL64 */

#if defined(VIDEO_CODEC_HAVE__VC_SETPIXEL3) && defined(VIDEO_CODEC_HAVE__VC_SETPIXEL3_DUMMY)
#define SET_vc_setpixel3_STATIC_INITIALIZER(x) (rp3_##x, NULL),
#define SET_vc_setpixel3_INITIALIZER(p, v)     rp3_##x; p._vc_setpixel3 = NULL;
#elif defined(VIDEO_CODEC_HAVE__VC_SETPIXEL3)
#define SET_vc_setpixel3_STATIC_INITIALIZER(x) &rp3_##x,
#define SET_vc_setpixel3_INITIALIZER(p, v)     p._vc_setpixel3 = &rp3_##v;
#else /* VIDEO_CODEC_HAVE__VC_SETPIXEL3 */
#define SET_vc_setpixel3_STATIC_INITIALIZER(x) /* nothing */
#define SET_vc_setpixel3_INITIALIZER(p, v)     /* nothing */
#endif /* !VIDEO_CODEC_HAVE__VC_SETPIXEL3 */

#define _UNPACK_CODEC_SPECS(flags, bpp, cbits, rmask, gmask, bmask, amask) \
	{ flags, CEILDIV(bpp, NBBY), bpp, cbits, rmask, gmask, bmask, amask }
#if defined(__KERNEL__) || !defined(__pic__)
#define _DEFINE_CODEC_AL1(name, codec, specs, rambuffer_requirements,     \
                          getpixel, setpixel, rectcopy, rectmove,         \
                          linefill, vertfill, rectfill,                   \
                          pixel2color, color2pixel, initconverter)        \
		PRIVATE struct video_codec const name = {                         \
			/* .vc_codec                  = */ codec,                     \
			/* .vc_specs                  = */ _UNPACK_CODEC_SPECS specs, \
			/* .vc_align                  = */ 1,                         \
			/* .vc_nalgn                  = */ &name,                     \
			/* .vc_rambuffer_requirements = */ &rambuffer_requirements,   \
			/* .vc_pixel2color            = */ &pixel2color,              \
			/* .vc_color2pixel            = */ &color2pixel,              \
			/* .vc_initconverter          = */ &initconverter,            \
			/* .vc_getpixel               = */ &getpixel,                 \
			/* .vc_setpixel               = */ &setpixel,                 \
			SET_vc_setpixel3_STATIC_INITIALIZER(setpixel)                 \
			/* .vc_linefill               = */ &linefill,                 \
			/* .vc_vertfill               = */ &vertfill,                 \
			/* .vc_rectfill               = */ &rectfill,                 \
			/* .vc_rectcopy               = */ &rectcopy,                 \
			/* .vc_rectmove               = */ &rectmove,                 \
			SET_vc_pixel2color64_STATIC_INITIALIZER(&pixel2color##64)     \
			SET_vc_color2pixel64_STATIC_INITIALIZER(&color2pixel##64)     \
			SET_vc_getpixel64_STATIC_INITIALIZER(&getpixel##_64)          \
			SET_vc_setpixel64_STATIC_INITIALIZER(&setpixel##_64)          \
			SET_vc_linefill64_STATIC_INITIALIZER(&linefill##_64)          \
			SET_vc_vertfill64_STATIC_INITIALIZER(&vertfill##_64)          \
			SET_vc_rectfill64_STATIC_INITIALIZER(&rectfill##_64)          \
		}
#define _DEFINE_CODEC_ALX(name, codec, specs,                             \
                          align, rambuffer_requirements,                  \
                          getpixel, setpixel, rectcopy, rectmove,         \
                          linefill, vertfill, rectfill,                   \
                          unaligned_getpixel, unaligned_setpixel,         \
                          unaligned_rectcopy, unaligned_rectmove,         \
                          unaligned_linefill, unaligned_vertfill,         \
                          unaligned_rectfill,                             \
                          pixel2color, color2pixel, initconverter)        \
		PRIVATE struct video_codec const unaligned_##name = {             \
			/* .vc_codec                  = */ codec,                     \
			/* .vc_specs                  = */ _UNPACK_CODEC_SPECS specs, \
			/* .vc_align                  = */ 1,                         \
			/* .vc_nalgn                  = */ &unaligned_##name,         \
			/* .vc_rambuffer_requirements = */ &rambuffer_requirements,   \
			/* .vc_pixel2color            = */ &pixel2color,              \
			/* .vc_color2pixel            = */ &color2pixel,              \
			/* .vc_initconverter          = */ &initconverter,            \
			/* .vc_getpixel               = */ &unaligned_getpixel,       \
			/* .vc_setpixel               = */ &unaligned_setpixel,       \
			SET_vc_setpixel3_STATIC_INITIALIZER(setpixel)                 \
			/* .vc_linefill               = */ &unaligned_linefill,       \
			/* .vc_vertfill               = */ &unaligned_vertfill,       \
			/* .vc_rectfill               = */ &unaligned_rectfill,       \
			/* .vc_rectcopy               = */ &unaligned_rectcopy,       \
			/* .vc_rectmove               = */ &unaligned_rectmove,       \
			SET_vc_pixel2color64_STATIC_INITIALIZER(&pixel2color##64)     \
			SET_vc_color2pixel64_STATIC_INITIALIZER(&color2pixel##64)     \
			SET_vc_getpixel64_STATIC_INITIALIZER(&unaligned_getpixel##_64) \
			SET_vc_setpixel64_STATIC_INITIALIZER(&unaligned_setpixel##_64) \
			SET_vc_linefill64_STATIC_INITIALIZER(&unaligned_linefill##_64) \
			SET_vc_vertfill64_STATIC_INITIALIZER(&unaligned_vertfill##_64) \
			SET_vc_rectfill64_STATIC_INITIALIZER(&unaligned_rectfill##_64) \
		};                                                                \
		PRIVATE struct video_codec const name = {                         \
			/* .vc_codec                  = */ codec,                     \
			/* .vc_specs                  = */ _UNPACK_CODEC_SPECS specs, \
			/* .vc_align                  = */ align,                     \
			/* .vc_nalgn                  = */ &unaligned_##name,         \
			/* .vc_rambuffer_requirements = */ &rambuffer_requirements,   \
			/* .vc_pixel2color            = */ &pixel2color,              \
			/* .vc_color2pixel            = */ &color2pixel,              \
			/* .vc_initconverter          = */ &initconverter,            \
			/* .vc_getpixel               = */ &getpixel,                 \
			/* .vc_setpixel               = */ &setpixel,                 \
			SET_vc_setpixel3_STATIC_INITIALIZER(setpixel)                 \
			/* .vc_linefill               = */ &linefill,                 \
			/* .vc_vertfill               = */ &vertfill,                 \
			/* .vc_rectfill               = */ &rectfill,                 \
			/* .vc_rectcopy               = */ &rectcopy,                 \
			/* .vc_rectmove               = */ &rectmove,                 \
			SET_vc_pixel2color64_STATIC_INITIALIZER(&pixel2color##64)     \
			SET_vc_color2pixel64_STATIC_INITIALIZER(&color2pixel##64)     \
			SET_vc_getpixel64_STATIC_INITIALIZER(&getpixel##_64)          \
			SET_vc_setpixel64_STATIC_INITIALIZER(&setpixel##_64)          \
			SET_vc_linefill64_STATIC_INITIALIZER(&linefill##_64)          \
			SET_vc_vertfill64_STATIC_INITIALIZER(&vertfill##_64)          \
			SET_vc_rectfill64_STATIC_INITIALIZER(&rectfill##_64)          \
		}
#else /* __KERNEL__ || !__pic__ */
#define _DEFINE_CODEC_AL1(name, codec, specs, rambuffer_requirements,   \
                          getpixel, setpixel, rectcopy, rectmove,       \
                          linefill, vertfill, rectfill,                 \
                          pixel2color, color2pixel, initconverter)      \
		PRIVATE struct video_codec name = {                             \
			/* .vc_codec = */ codec,                                    \
			/* .vc_specs = */ _UNPACK_CODEC_SPECS specs,                \
			/* .vc_align = */ 1,                                        \
		};                                                              \
		if (!name.vc_rambuffer_requirements) {                          \
			name.vc_nalgn         = &name;                              \
			name.vc_pixel2color   = &pixel2color;                       \
			name.vc_color2pixel   = &color2pixel;                       \
			name.vc_initconverter = &initconverter;                     \
			name.vc_getpixel      = &getpixel;                          \
			name.vc_setpixel      = &setpixel;                          \
			SET_vc_setpixel3_INITIALIZER(name, setpixel)                \
			name.vc_linefill      = &linefill;                          \
			name.vc_vertfill      = &vertfill;                          \
			name.vc_rectfill      = &rectfill;                          \
			name.vc_rectcopy      = &rectcopy;                          \
			name.vc_rectmove      = &rectmove;                          \
			SET_vc_pixel2color64_INITIALIZER(name, &pixel2color##64)    \
			SET_vc_color2pixel64_INITIALIZER(name, &color2pixel##64)    \
			SET_vc_getpixel64_INITIALIZER(name, &getpixel##_64)         \
			SET_vc_setpixel64_INITIALIZER(name, &setpixel##_64)         \
			SET_vc_linefill64_INITIALIZER(name, &linefill##_64)         \
			SET_vc_vertfill64_INITIALIZER(name, &vertfill##_64)         \
			SET_vc_rectfill64_INITIALIZER(name, &rectfill##_64)         \
			COMPILER_WRITE_BARRIER();                                   \
			name.vc_rambuffer_requirements = &rambuffer_requirements;   \
			COMPILER_WRITE_BARRIER();                                   \
		}
#define _DEFINE_CODEC_ALX(name, codec, specs,                                     \
                          align, rambuffer_requirements,                          \
                          getpixel, setpixel, rectcopy, rectmove,                 \
                          linefill, vertfill, rectfill,                           \
                          unaligned_getpixel, unaligned_setpixel,                 \
                          unaligned_rectcopy, unaligned_rectmove,                 \
                          unaligned_linefill, unaligned_vertfill,                 \
                          unaligned_rectfill,                                     \
                          pixel2color, color2pixel, initconverter)                \
		PRIVATE struct video_codec unaligned_##name = {                           \
			/* .vc_codec = */ codec,                                              \
			/* .vc_specs = */ _UNPACK_CODEC_SPECS specs,                          \
			/* .vc_align = */ 1,                                                  \
		};                                                                        \
		PRIVATE struct video_codec name = {                                       \
			/* .vc_codec = */ codec,                                              \
			/* .vc_specs = */ _UNPACK_CODEC_SPECS specs,                          \
			/* .vc_align = */ align,                                              \
		};                                                                        \
		if (!name.vc_rambuffer_requirements) {                                    \
			unaligned_##name.vc_nalgn                  = &unaligned_##name;       \
			unaligned_##name.vc_rambuffer_requirements = &rambuffer_requirements; \
			unaligned_##name.vc_pixel2color            = &pixel2color;            \
			unaligned_##name.vc_color2pixel            = &color2pixel;            \
			unaligned_##name.vc_initconverter          = &initconverter;          \
			unaligned_##name.vc_getpixel               = &unaligned_getpixel;     \
			unaligned_##name.vc_setpixel               = &unaligned_setpixel;     \
			SET_vc_setpixel3_INITIALIZER(unaligned_##name, unaligned_setpixel)    \
			unaligned_##name.vc_linefill               = &unaligned_linefill;     \
			unaligned_##name.vc_vertfill               = &unaligned_vertfill;     \
			unaligned_##name.vc_rectfill               = &unaligned_rectfill;     \
			unaligned_##name.vc_rectcopy               = &unaligned_rectcopy;     \
			unaligned_##name.vc_rectmove               = &unaligned_rectmove;     \
			SET_vc_pixel2color64_INITIALIZER(unaligned_##name, &pixel2color##64)  \
			SET_vc_color2pixel64_INITIALIZER(unaligned_##name, &color2pixel##64)  \
			SET_vc_getpixel64_INITIALIZER(unaligned_##name, &unaligned_getpixel##_64) \
			SET_vc_setpixel64_INITIALIZER(unaligned_##name, &unaligned_setpixel##_64) \
			SET_vc_linefill64_INITIALIZER(unaligned_##name, &unaligned_linefill##_64) \
			SET_vc_vertfill64_INITIALIZER(unaligned_##name, &unaligned_vertfill##_64) \
			SET_vc_rectfill64_INITIALIZER(unaligned_##name, &unaligned_rectfill##_64) \
			name.vc_nalgn                              = &unaligned_##name;       \
			name.vc_pixel2color                        = &pixel2color;            \
			name.vc_color2pixel                        = &color2pixel;            \
			name.vc_initconverter                      = &initconverter;          \
			name.vc_getpixel                           = &getpixel;               \
			name.vc_setpixel                           = &setpixel;               \
			SET_vc_setpixel3_INITIALIZER(name, setpixel)                          \
			name.vc_linefill                           = &linefill;               \
			name.vc_vertfill                           = &vertfill;               \
			name.vc_rectfill                           = &rectfill;               \
			name.vc_rectcopy                           = &rectcopy;               \
			name.vc_rectmove                           = &rectmove;               \
			SET_vc_pixel2color64_INITIALIZER(name, &pixel2color##64)              \
			SET_vc_color2pixel64_INITIALIZER(name, &color2pixel##64)              \
			SET_vc_getpixel64_INITIALIZER(name, &getpixel##_64)                   \
			SET_vc_setpixel64_INITIALIZER(name, &setpixel##_64)                   \
			SET_vc_linefill64_INITIALIZER(name, &linefill##_64)                   \
			SET_vc_vertfill64_INITIALIZER(name, &vertfill##_64)                   \
			SET_vc_rectfill64_INITIALIZER(name, &rectfill##_64)                   \
			COMPILER_WRITE_BARRIER();                                             \
			name.vc_rambuffer_requirements = &rambuffer_requirements;             \
			COMPILER_WRITE_BARRIER();                                             \
		}
#endif /* !__KERNEL__ && __pic__ */






/************************************************************************/
/* CODEC CALCULATION UTILS                                              */
/************************************************************************/

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






/************************************************************************/
/* CODEC IMPLEMENTATION UTILS                                           */
/************************************************************************/

#define DEFINE_GENERIC_linefill__with__setpixel(linefill, setpixel) \
	PRIVATE NONNULL((1)) void CC                                    \
	linefill(byte_t *__restrict line, video_coord_t x,              \
	         video_pixel_t pixel, video_dim_t num_pixels) {         \
		do {                                                        \
			setpixel(line, x, pixel);                               \
			++x;                                                    \
		} while (--num_pixels);                                     \
	}
#define DEFINE_GENERIC_vertfill__with__setpixel(vertfill, setpixel)   \
	PRIVATE NONNULL((1)) void CC                                      \
	vertfill(byte_t *__restrict line, video_coord_t x, size_t stride, \
	         video_pixel_t pixel, video_dim_t num_pixels) {           \
		do {                                                          \
			setpixel(line, x, pixel);                                 \
			line += stride;                                           \
		} while (--num_pixels);                                       \
	}
#define DEFINE_GENERIC_rectfill__with__linefill(rectfill, linefill)         \
	PRIVATE NONNULL((1)) void CC                                            \
	rectfill(byte_t *__restrict line, video_coord_t x, size_t stride,       \
	         video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) { \
		do {                                                                \
			linefill(line, x, pixel, size_x);                               \
			line += stride;                                                 \
		} while (--size_y);                                                 \
	}
#define DEFINE_GENERIC_rectcopy__with__getpixel__and__setpixel(rectcopy, getpixel, setpixel) \
	PRIVATE NONNULL((1, 4)) void CC                                                          \
	rectcopy(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,            \
	         byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,      \
	         video_dim_t size_x, video_dim_t size_y) {                                       \
		do {                                                                                 \
			video_dim_t iter_x = 0;                                                          \
			do {                                                                             \
				video_pixel_t pixel;                                                         \
				pixel = getpixel(src_line, src_x + iter_x);                                  \
				setpixel(dst_line, dst_x + iter_x, pixel);                                   \
			} while (++iter_x < size_x);                                                     \
			dst_line += dst_stride;                                                          \
			src_line += src_stride;                                                          \
		} while (--size_y);                                                                  \
	}
#define DEFINE_GENERIC_rectmove__with__getpixel__and__setpixel(rectmove, getpixel, setpixel) \
	PRIVATE NONNULL((1, 3)) void CC                                                          \
	rectmove(byte_t *__restrict dst_line, video_coord_t dst_x,                               \
	         byte_t const *__restrict src_line, video_coord_t src_x,                         \
	         size_t stride, video_dim_t size_x, video_dim_t size_y) {                        \
		if (dst_line < src_line || (dst_line == src_line && dst_x <= src_x)) {               \
			do {                                                                             \
				video_dim_t iter_x = 0;                                                      \
				do {                                                                         \
					video_pixel_t pixel;                                                     \
					pixel = getpixel(src_line, src_x + iter_x);                              \
					setpixel(dst_line, dst_x + iter_x, pixel);                               \
				} while (++iter_x < size_x);                                                 \
				dst_line += stride;                                                          \
				src_line += stride;                                                          \
			} while (--size_y);                                                              \
		} else {                                                                             \
			dst_line += stride * size_y;                                                     \
			src_line += stride * size_y;                                                     \
			do {                                                                             \
				video_dim_t iter_x;                                                          \
				dst_line -= stride;                                                          \
				src_line -= stride;                                                          \
				iter_x = size_x;                                                             \
				do {                                                                         \
					video_pixel_t pixel;                                                     \
					--iter_x;                                                                \
					pixel = getpixel(src_line, src_x + iter_x);                              \
					setpixel(dst_line, dst_x + iter_x, pixel);                               \
				} while (iter_x);                                                            \
			} while (--size_y);                                                              \
		}                                                                                    \
	}
#ifdef VIDEO_CODEC_HAVE__VC_SETPIXEL3
#define DEFINE_GENERIC_setpixel3__with__setpixel(setpixel3, setpixel)          \
	PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC                         \
	setpixel3(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) { \
		setpixel(line, x, pixel);                                              \
	}
#else /* VIDEO_CODEC_HAVE__VC_SETPIXEL3 */
#define DEFINE_GENERIC_setpixel3__with__setpixel(setpixel3, setpixel) /* nothing */
#endif /* !VIDEO_CODEC_HAVE__VC_SETPIXEL3 */


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






/************************************************************************/
/* GENERIC CODEC FUNCTIONS                                              */
/************************************************************************/

#define identity_pixel2color identity_color2pixel
INTDEF ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC identity_color2pixel(struct video_format const *__restrict format, video_color_t value);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC pal_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC pal_color2pixel(struct video_format const *__restrict format, video_color_t color);
#ifdef CONFIG_VIDEO_CODEC_HAVE_PIXEL64
#define identity_pixel2color64 identity_color2pixel64
INTDEF ATTR_CONST WUNUSED NONNULL((1)) video_pixel64_t CC identity_color2pixel64(struct video_format const *__restrict format, video_color64_t value);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_color64_t CC pal_pixel2color64(struct video_format const *__restrict format, video_pixel64_t pixel);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t CC pal_color2pixel64(struct video_format const *__restrict format, video_color64_t color);
#endif /* CONFIG_VIDEO_CODEC_HAVE_PIXEL64 */

INTDEF ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC rgbx8888_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel);
#ifdef CONFIG_VIDEO_CODEC_HAVE_PIXEL64
INTDEF ATTR_CONST WUNUSED NONNULL((1)) video_color64_t CC rgbx8888_pixel2color64(struct video_format const *__restrict format, video_pixel64_t pixel);
#endif /* CONFIG_VIDEO_CODEC_HAVE_PIXEL64 */


INTDEF NONNULL((3)) void CC buffer1_requirements(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF NONNULL((3)) void CC buffer2_requirements(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF NONNULL((3)) void CC buffer4_requirements(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF NONNULL((3)) void CC buffer8_requirements(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF NONNULL((3)) void CC buffer16_requirements(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF NONNULL((3)) void CC buffer24_requirements(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF NONNULL((3)) void CC buffer32_requirements(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);

DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_CODEC_UTILS_H */
