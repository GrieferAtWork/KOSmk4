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
#ifndef GUARD_LIBVIDEO_GFX_CODEC_CODEC_UTILS_H
#define GUARD_LIBVIDEO_GFX_CODEC_CODEC_UTILS_H 1

#include "../api.h"
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

#include <libvideo/color.h>
#include <libvideo/gfx/api.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/surface-defs.h>
#include <libvideo/types.h>

DECL_BEGIN

#if defined(NDEBUG) || defined(NDEBUG_CODEC) || 1
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

#ifndef CONFIG_LIBVIDEO_HAVE_PIXEL64
#define video_channel16_t video_channel_t
#define video_pixel64_t   video_pixel_t
#define video_color64_t   video_color_t
#define DEFINE_PIXEL2COLOR64_WRAPPER32(decl, foo_pixel2color, foo_pixel2color64) /* nothing */
#define DEFINE_COLOR2PIXEL64_WRAPPER32(decl, foo_color2pixel, foo_color2pixel64) /* nothing */
#define DEFINE_PIXEL64_IO_WRAPPERS(f, f_, f64, f64_)                             /* nothing */
#else /* !CONFIG_LIBVIDEO_HAVE_PIXEL64 */
#define DEFINE_PIXEL2COLOR64_WRAPPER32(decl, foo_pixel2color, foo_pixel2color64)               \
	decl WUNUSED NONNULL((1)) video_color64_t FCC                                              \
	foo_pixel2color64(struct video_surface const *__restrict surface, video_pixel64_t pixel) { \
		video_color_t c = foo_pixel2color(surface, (video_pixel_t)pixel);                      \
		return VIDEO_COLOR64_FROM_COLOR(c);                                                    \
	}
#define DEFINE_COLOR2PIXEL64_WRAPPER32(decl, foo_color2pixel, foo_color2pixel64)               \
	decl WUNUSED NONNULL((1)) video_pixel64_t FCC                                              \
	foo_color2pixel64(struct video_surface const *__restrict surface, video_color64_t color) { \
		video_color_t c = VIDEO_COLOR_FROM_COLOR64(color);                                     \
		return (video_pixel64_t)foo_color2pixel(surface, c);                                   \
	}
#define DEFINE_PIXEL64_IO_WRAPPERS(decl, f, f_, f64, f64_)                                 \
	decl ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC                      \
	f64(f64_, getpixel)(byte_t const *__restrict line, video_coord_t x) {                  \
		return (video_pixel64_t)f(f_, getpixel)(line, x);                                  \
	}                                                                                      \
	decl ATTR_COLD NONNULL((1)) void FCC                                                   \
	f64(f64_, setpixel)(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel) { \
		f(f_, setpixel)(line, x, (video_pixel_t)pixel);                                    \
	}                                                                                      \
	decl ATTR_COLD NONNULL((1)) void FCC                                                   \
	f64(f64_, linefill)(byte_t *__restrict line, video_coord_t x,                          \
	                    video_pixel64_t pixel, video_dim_t num_pixels) {                   \
		f(f_, linefill)(line, x, (video_pixel_t)pixel, num_pixels);                        \
	}                                                                                      \
	decl ATTR_COLD NONNULL((1)) void FCC                                                   \
	f64(f64_, vertfill)(byte_t *__restrict line, video_coord_t x, size_t stride,           \
	                    video_pixel64_t pixel, video_dim_t num_pixels) {                   \
		f(f_, vertfill)(line, x, stride, (video_pixel_t)pixel, num_pixels);                \
	}                                                                                      \
	decl ATTR_COLD NONNULL((1)) void FCC                                                   \
	f64(f64_, rectfill)(byte_t *__restrict line, video_coord_t x, size_t stride,           \
	                    video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y) {   \
		f(f_, rectfill)(line, x, stride, (video_pixel_t)pixel, size_x, size_y);            \
	}
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
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





#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
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
#else /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
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
#endif /* !CONFIG_LIBVIDEO_HAVE_PIXEL64 */

#if defined(CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3) && defined(VIDEO_CODEC_HAVE__VC_SETPIXEL3_DUMMY)
#define SET_vc_setpixel3_STATIC_INITIALIZER(x) (rp3_##x, NULL),
#define SET_vc_setpixel3_INITIALIZER(p, v)     rp3_##x; p._vc_setpixel3 = NULL;
#elif defined(CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3)
#define SET_vc_setpixel3_STATIC_INITIALIZER(x) &rp3_##x,
#define SET_vc_setpixel3_INITIALIZER(p, v)     p._vc_setpixel3 = &rp3_##v;
#else /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */
#define SET_vc_setpixel3_STATIC_INITIALIZER(x) /* nothing */
#define SET_vc_setpixel3_INITIALIZER(p, v)     /* nothing */
#endif /* !CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */

#ifdef NDEBUG
#define static__vc_refcnt 0x7fff
#else /* NDEBUG */
#define static__vc_refcnt 1
#endif /* !NDEBUG */
#define undefined__vc_destroy ((void (LIBVIDEO_GFX_FCC *)(struct video_codec *__restrict))(void *)-1)


#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
#define _UNPACK_CODEC_SPECS(flags, bpp, cbits, rmask, gmask, bmask, amask) \
	{ flags, CEILDIV(bpp, NBBY), bpp, cbits, 0, rmask, gmask, bmask, amask }
#else /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
#define _UNPACK_CODEC_SPECS(flags, bpp, cbits, rmask, gmask, bmask, amask) \
	{ flags, CEILDIV(bpp, NBBY), bpp, cbits, rmask, gmask, bmask, amask }
#endif /* !CONFIG_LIBVIDEO_HAVE_PIXEL64 */
#if defined(__KERNEL__) || !defined(__pic__)
#define _DEFINE_CODEC_AL1(name, codec, specs,                             \
                          rambuffer_requirements, coord2bytes,            \
                          getpixel, setpixel, rectcopy, rectmove,         \
                          linecopy, linefill, vertfill, rectfill,         \
                          pixel2color, color2pixel, initconverter)        \
		PRIVATE struct video_codec name = {                               \
			/* .vc_refcnt                 = */ static__vc_refcnt,         \
			/* .vc_destroy                = */ undefined__vc_destroy,     \
			/* .vc_codec                  = */ codec,                     \
			/* .vc_specs                  = */ _UNPACK_CODEC_SPECS specs, \
			/* .vc_align                  = */ 1,                         \
			/* .vc_nalgn                  = */ &name,                     \
			/* .vc_rambuffer_requirements = */ &rambuffer_requirements,   \
			/* .vc_coord2bytes            = */ &coord2bytes,              \
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
			/* .vc_linecopy               = */ &linecopy,                 \
			SET_vc_pixel2color64_STATIC_INITIALIZER(&pixel2color##64)     \
			SET_vc_color2pixel64_STATIC_INITIALIZER(&color2pixel##64)     \
			SET_vc_getpixel64_STATIC_INITIALIZER(&getpixel##_64)          \
			SET_vc_setpixel64_STATIC_INITIALIZER(&setpixel##_64)          \
			SET_vc_linefill64_STATIC_INITIALIZER(&linefill##_64)          \
			SET_vc_vertfill64_STATIC_INITIALIZER(&vertfill##_64)          \
			SET_vc_rectfill64_STATIC_INITIALIZER(&rectfill##_64)          \
		}
#define _DEFINE_CODEC_ALX(name, codec, specs, align,                      \
                          rambuffer_requirements, coord2bytes,            \
                          getpixel, setpixel, rectcopy, rectmove,         \
                          linecopy, linefill, vertfill, rectfill,         \
                          unaligned_getpixel, unaligned_setpixel,         \
                          unaligned_rectcopy, unaligned_rectmove,         \
                          unaligned_linecopy, unaligned_linefill,         \
                          unaligned_vertfill, unaligned_rectfill,         \
                          pixel2color, color2pixel, initconverter)        \
		PRIVATE struct video_codec unaligned_##name = {                   \
			/* .vc_refcnt                 = */ static__vc_refcnt,         \
			/* .vc_destroy                = */ undefined__vc_destroy,     \
			/* .vc_codec                  = */ codec,                     \
			/* .vc_specs                  = */ _UNPACK_CODEC_SPECS specs, \
			/* .vc_align                  = */ 1,                         \
			/* .vc_nalgn                  = */ &unaligned_##name,         \
			/* .vc_rambuffer_requirements = */ &rambuffer_requirements,   \
			/* .vc_coord2bytes            = */ &coord2bytes,              \
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
			/* .vc_linecopy               = */ &unaligned_linecopy,       \
			SET_vc_pixel2color64_STATIC_INITIALIZER(&pixel2color##64)     \
			SET_vc_color2pixel64_STATIC_INITIALIZER(&color2pixel##64)     \
			SET_vc_getpixel64_STATIC_INITIALIZER(&unaligned_getpixel##_64) \
			SET_vc_setpixel64_STATIC_INITIALIZER(&unaligned_setpixel##_64) \
			SET_vc_linefill64_STATIC_INITIALIZER(&unaligned_linefill##_64) \
			SET_vc_vertfill64_STATIC_INITIALIZER(&unaligned_vertfill##_64) \
			SET_vc_rectfill64_STATIC_INITIALIZER(&unaligned_rectfill##_64) \
		};                                                                \
		PRIVATE struct video_codec name = {                               \
			/* .vc_refcnt                 = */ static__vc_refcnt,         \
			/* .vc_destroy                = */ undefined__vc_destroy,     \
			/* .vc_codec                  = */ codec,                     \
			/* .vc_specs                  = */ _UNPACK_CODEC_SPECS specs, \
			/* .vc_align                  = */ align,                     \
			/* .vc_nalgn                  = */ &unaligned_##name,         \
			/* .vc_rambuffer_requirements = */ &rambuffer_requirements,   \
			/* .vc_coord2bytes            = */ &coord2bytes,              \
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
			/* .vc_linecopy               = */ &linecopy,                 \
			SET_vc_pixel2color64_STATIC_INITIALIZER(&pixel2color##64)     \
			SET_vc_color2pixel64_STATIC_INITIALIZER(&color2pixel##64)     \
			SET_vc_getpixel64_STATIC_INITIALIZER(&getpixel##_64)          \
			SET_vc_setpixel64_STATIC_INITIALIZER(&setpixel##_64)          \
			SET_vc_linefill64_STATIC_INITIALIZER(&linefill##_64)          \
			SET_vc_vertfill64_STATIC_INITIALIZER(&vertfill##_64)          \
			SET_vc_rectfill64_STATIC_INITIALIZER(&rectfill##_64)          \
		}
#else /* __KERNEL__ || !__pic__ */
#define _DEFINE_CODEC_AL1(name, codec, specs,                           \
                          rambuffer_requirements, coord2bytes,          \
                          getpixel, setpixel, rectcopy, rectmove,       \
                          linecopy, linefill, vertfill, rectfill,       \
                          pixel2color, color2pixel, initconverter)      \
		PRIVATE struct video_codec name = {                             \
			/* .vc_refcnt  = */ static__vc_refcnt,                      \
			/* .vc_destroy = */ undefined__vc_destroy,                  \
			/* .vc_codec   = */ codec,                                  \
			/* .vc_specs   = */ _UNPACK_CODEC_SPECS specs,              \
			/* .vc_align   = */ 1,                                      \
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
			name.vc_linecopy      = &linecopy;                          \
			SET_vc_pixel2color64_INITIALIZER(name, &pixel2color##64)    \
			SET_vc_color2pixel64_INITIALIZER(name, &color2pixel##64)    \
			SET_vc_getpixel64_INITIALIZER(name, &getpixel##_64)         \
			SET_vc_setpixel64_INITIALIZER(name, &setpixel##_64)         \
			SET_vc_linefill64_INITIALIZER(name, &linefill##_64)         \
			SET_vc_vertfill64_INITIALIZER(name, &vertfill##_64)         \
			SET_vc_rectfill64_INITIALIZER(name, &rectfill##_64)         \
			name.vc_coord2bytes = &coord2bytes;                         \
			COMPILER_WRITE_BARRIER();                                   \
			name.vc_rambuffer_requirements = &rambuffer_requirements;   \
			COMPILER_WRITE_BARRIER();                                   \
		}
#define _DEFINE_CODEC_ALX(name, codec, specs, align,                              \
                          rambuffer_requirements, coord2bytes,                    \
                          getpixel, setpixel, rectcopy, rectmove,                 \
                          linecopy, linefill, vertfill, rectfill,                 \
                          unaligned_getpixel, unaligned_setpixel,                 \
                          unaligned_rectcopy, unaligned_rectmove,                 \
                          unaligned_linecopy, unaligned_linefill,                 \
                          unaligned_vertfill, unaligned_rectfill,                 \
                          pixel2color, color2pixel, initconverter)                \
		PRIVATE struct video_codec unaligned_##name = {                           \
			/* .vc_refcnt  = */ static__vc_refcnt,                                \
			/* .vc_destroy = */ undefined__vc_destroy,                            \
			/* .vc_codec   = */ codec,                                            \
			/* .vc_specs   = */ _UNPACK_CODEC_SPECS specs,                        \
			/* .vc_align   = */ 1,                                                \
		};                                                                        \
		PRIVATE struct video_codec name = {                                       \
			/* .vc_refcnt  = */ static__vc_refcnt,                                \
			/* .vc_destroy = */ undefined__vc_destroy,                            \
			/* .vc_codec   = */ codec,                                            \
			/* .vc_specs   = */ _UNPACK_CODEC_SPECS specs,                        \
			/* .vc_align   = */ align,                                            \
		};                                                                        \
		if (!name.vc_rambuffer_requirements) {                                    \
			unaligned_##name.vc_nalgn                  = &unaligned_##name;       \
			unaligned_##name.vc_rambuffer_requirements = &rambuffer_requirements; \
			unaligned_##name.vc_coord2bytes            = &coord2bytes;            \
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
			unaligned_##name.vc_linecopy               = &unaligned_linecopy;     \
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
			name.vc_linecopy                           = &linecopy;               \
			SET_vc_pixel2color64_INITIALIZER(name, &pixel2color##64)              \
			SET_vc_color2pixel64_INITIALIZER(name, &color2pixel##64)              \
			SET_vc_getpixel64_INITIALIZER(name, &getpixel##_64)                   \
			SET_vc_setpixel64_INITIALIZER(name, &setpixel##_64)                   \
			SET_vc_linefill64_INITIALIZER(name, &linefill##_64)                   \
			SET_vc_vertfill64_INITIALIZER(name, &vertfill##_64)                   \
			SET_vc_rectfill64_INITIALIZER(name, &rectfill##_64)                   \
			name.vc_coord2bytes = &coord2bytes;                                   \
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

#define DEFINE_GENERIC_linefill__with__setpixel(decl, linefill, setpixel) \
	decl NONNULL((1)) void FCC                                            \
	linefill(byte_t *__restrict line, video_coord_t x,                    \
	         video_pixel_t pixel, video_dim_t num_pixels) {               \
		do {                                                              \
			setpixel(line, x, pixel);                                     \
			++x;                                                          \
		} while (--num_pixels);                                           \
	}
#define DEFINE_GENERIC_vertfill__with__setpixel(decl, vertfill, setpixel) \
	decl NONNULL((1)) void FCC                                            \
	vertfill(byte_t *__restrict line, video_coord_t x, size_t stride,     \
	         video_pixel_t pixel, video_dim_t num_pixels) {               \
		do {                                                              \
			setpixel(line, x, pixel);                                     \
			line += stride;                                               \
		} while (--num_pixels);                                           \
	}
#define DEFINE_GENERIC_rectfill__with__linefill(decl, rectfill, linefill)   \
	decl NONNULL((1)) void FCC                                              \
	rectfill(byte_t *__restrict line, video_coord_t x, size_t stride,       \
	         video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) { \
		do {                                                                \
			linefill(line, x, pixel, size_x);                               \
			line += stride;                                                 \
		} while (--size_y);                                                 \
	}
#define DEFINE_GENERIC_linecopy__with__getpixel__and__setpixel(decl, linecopy, getpixel, setpixel) \
	decl NONNULL((1, 3)) void FCC                                                                  \
	linecopy(byte_t *__restrict dst_line, video_coord_t dst_x,                                     \
	         byte_t const *__restrict src_line, video_coord_t src_x,                               \
	         video_dim_t size_x) {                                                                 \
		do {                                                                                       \
			video_pixel_t pixel;                                                                   \
			pixel = getpixel(src_line, src_x);                                                     \
			setpixel(dst_line, dst_x, pixel);                                                      \
			++dst_x;                                                                               \
			++src_x;                                                                               \
		} while (--size_x);                                                                        \
	}
#define DEFINE_GENERIC_rectcopy__with__getpixel__and__setpixel(decl, rectcopy, getpixel, setpixel) \
	decl NONNULL((1, 4)) void FCC                                                                  \
	rectcopy(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,                  \
	         byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,            \
	         video_dim_t size_x, video_dim_t size_y) {                                             \
		do {                                                                                       \
			video_dim_t iter_x = 0;                                                                \
			do {                                                                                   \
				video_pixel_t pixel;                                                               \
				pixel = getpixel(src_line, src_x + iter_x);                                        \
				setpixel(dst_line, dst_x + iter_x, pixel);                                         \
			} while (++iter_x < size_x);                                                           \
			dst_line += dst_stride;                                                                \
			src_line += src_stride;                                                                \
		} while (--size_y);                                                                        \
	}
#define DEFINE_GENERIC_rectmove__with__getpixel__and__setpixel(decl, rectmove, getpixel, setpixel) \
	decl NONNULL((1, 3)) void FCC                                                                  \
	rectmove(byte_t *__restrict dst_line, video_coord_t dst_x,                                     \
	         byte_t const *__restrict src_line, video_coord_t src_x,                               \
	         size_t stride, video_dim_t size_x, video_dim_t size_y) {                              \
		if (dst_line < src_line || (dst_line == src_line && dst_x <= src_x)) {                     \
			do {                                                                                   \
				video_dim_t iter_x = 0;                                                            \
				do {                                                                               \
					video_pixel_t pixel;                                                           \
					pixel = getpixel(src_line, src_x + iter_x);                                    \
					setpixel(dst_line, dst_x + iter_x, pixel);                                     \
				} while (++iter_x < size_x);                                                       \
				dst_line += stride;                                                                \
				src_line += stride;                                                                \
			} while (--size_y);                                                                    \
		} else {                                                                                   \
			dst_line += stride * size_y;                                                           \
			src_line += stride * size_y;                                                           \
			do {                                                                                   \
				video_dim_t iter_x;                                                                \
				dst_line -= stride;                                                                \
				src_line -= stride;                                                                \
				iter_x = size_x;                                                                   \
				do {                                                                               \
					video_pixel_t pixel;                                                           \
					--iter_x;                                                                      \
					pixel = getpixel(src_line, src_x + iter_x);                                    \
					setpixel(dst_line, dst_x + iter_x, pixel);                                     \
				} while (iter_x);                                                                  \
			} while (--size_y);                                                                    \
		}                                                                                          \
	}
#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
#define DEFINE_GENERIC_setpixel3__with__setpixel(decl, setpixel3, setpixel)    \
	decl NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC                            \
	setpixel3(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) { \
		setpixel(line, x, pixel);                                              \
	}
#else /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */
#define DEFINE_GENERIC_setpixel3__with__setpixel(decl, setpixel3, setpixel) /* nothing */
#endif /* !CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */


#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define MASK8_BE(x) __hybrid_bswap64_c(__UINT64_C(x))
#define MASK7_BE(x) (__hybrid_bswap64_c(__UINT64_C(x)) >> 8)
#define MASK6_BE(x) (__hybrid_bswap64_c(__UINT64_C(x)) >> 16)
#define MASK5_BE(x) (__hybrid_bswap64_c(__UINT64_C(x)) >> 24)
#define MASK4_BE(x) __hybrid_bswap32_c(__UINT32_C(x))
#define MASK3_BE(x) (__hybrid_bswap32_c(__UINT32_C(x)) >> 8)
#define MASK2_BE(x) __hybrid_bswap16_c(__UINT16_C(x))
#define MASK8_LE(x) __UINT64_C(x)
#define MASK7_LE(x) __UINT64_C(x)
#define MASK6_LE(x) __UINT64_C(x)
#define MASK5_LE(x) __UINT64_C(x)
#define MASK4_LE(x) __UINT32_C(x)
#define MASK3_LE(x) __UINT32_C(x)
#define MASK2_LE(x) __UINT16_C(x)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define MASK8_BE(x) __UINT64_C(x)
#define MASK7_BE(x) __UINT64_C(x)
#define MASK6_BE(x) __UINT64_C(x)
#define MASK5_BE(x) __UINT64_C(x)
#define MASK4_BE(x) __UINT32_C(x)
#define MASK3_BE(x) __UINT32_C(x)
#define MASK2_BE(x) __UINT16_C(x)
#define MASK8_LE(x) __hybrid_bswap64_c(__UINT64_C(x))
#define MASK7_LE(x) (__hybrid_bswap64_c(__UINT64_C(x)) >> 8)
#define MASK6_LE(x) (__hybrid_bswap64_c(__UINT64_C(x)) >> 16)
#define MASK5_LE(x) (__hybrid_bswap64_c(__UINT64_C(x)) >> 24)
#define MASK4_LE(x) __hybrid_bswap32_c(__UINT32_C(x))
#define MASK3_LE(x) (__hybrid_bswap32_c(__UINT32_C(x)) >> 8)
#define MASK2_LE(x) __hybrid_bswap16_c(__UINT16_C(x))
#endif /* __BYTE_ORDER__ == ... */






/************************************************************************/
/* GENERIC CODEC FUNCTIONS                                              */
/************************************************************************/

#define identity_pixel2color identity_color2pixel
INTDEF ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC identity_color2pixel(struct video_surface const *__restrict surface, video_color_t value);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC pal_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC pal_color2pixel(struct video_surface const *__restrict surface, video_color_t color);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
#define identity_pixel2color64 identity_color2pixel64
INTDEF ATTR_CONST WUNUSED NONNULL((1)) video_pixel64_t FCC identity_color2pixel64(struct video_surface const *__restrict surface, video_color64_t value);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_color64_t FCC pal_pixel2color64(struct video_surface const *__restrict surface, video_pixel64_t pixel);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC pal_color2pixel64(struct video_surface const *__restrict surface, video_color64_t color);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

INTDEF ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC rgbx8888_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTDEF ATTR_CONST WUNUSED NONNULL((1)) video_color64_t FCC rgbx8888_pixel2color64(struct video_surface const *__restrict surface, video_pixel64_t pixel);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */


INTDEF ATTR_OUT(3) void NOTHROW(FCC buffer1_requirements)(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF ATTR_OUT(3) void NOTHROW(FCC buffer2_requirements)(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF ATTR_OUT(3) void NOTHROW(FCC buffer4_requirements)(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF ATTR_OUT(3) void NOTHROW(FCC buffer8_requirements)(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF ATTR_OUT(3) void NOTHROW(FCC buffer16_requirements)(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF ATTR_OUT(3) void NOTHROW(FCC buffer24_requirements)(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF ATTR_OUT(3) void NOTHROW(FCC buffer32_requirements)(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);

INTDEF WUNUSED ATTR_INOUT(1) size_t NOTHROW(FCC buffer1_coord2bytes)(video_coord_t *__restrict p_coord);
INTDEF WUNUSED ATTR_INOUT(1) size_t NOTHROW(FCC buffer2_coord2bytes)(video_coord_t *__restrict p_coord);
INTDEF WUNUSED ATTR_INOUT(1) size_t NOTHROW(FCC buffer4_coord2bytes)(video_coord_t *__restrict p_coord);
INTDEF WUNUSED ATTR_INOUT(1) size_t NOTHROW(FCC buffer8_coord2bytes)(video_coord_t *__restrict p_coord);
INTDEF WUNUSED ATTR_INOUT(1) size_t NOTHROW(FCC buffer16_coord2bytes)(video_coord_t *__restrict p_coord);
INTDEF WUNUSED ATTR_INOUT(1) size_t NOTHROW(FCC buffer24_coord2bytes)(video_coord_t *__restrict p_coord);
INTDEF WUNUSED ATTR_INOUT(1) size_t NOTHROW(FCC buffer32_coord2bytes)(video_coord_t *__restrict p_coord);


/************************************************************************/
/* SUB-8-BPP PIXEL OPERATORS                                            */
/************************************************************************/
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel1_msb(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel1_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void FCC linefill1_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill1_msb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill1_msb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy1_msb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove1_msb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy1_msb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel1_msb_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel1_msb_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill1_msb_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill1_msb_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill1_msb_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel1_lsb(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel1_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void FCC linefill1_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill1_lsb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill1_lsb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy1_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove1_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy1_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel1_lsb_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel1_lsb_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill1_lsb_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill1_lsb_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill1_lsb_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel2_msb(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel2_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void FCC linefill2_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill2_msb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill2_msb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy2_msb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove2_msb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy2_msb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel2_msb_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel2_msb_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill2_msb_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill2_msb_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill2_msb_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel2_lsb(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel2_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void FCC linefill2_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill2_lsb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill2_lsb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy2_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove2_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy2_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel2_lsb_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel2_lsb_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill2_lsb_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill2_lsb_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill2_lsb_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel4_msb(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel4_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void FCC linefill4_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill4_msb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill4_msb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy4_msb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove4_msb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy4_msb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel4_msb_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel4_msb_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill4_msb_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill4_msb_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill4_msb_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel4_lsb(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel4_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void FCC linefill4_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill4_lsb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill4_lsb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy4_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove4_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy4_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel4_lsb_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel4_lsb_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill4_lsb_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill4_lsb_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill4_lsb_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */


INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel8(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel8(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void FCC linefill8(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill8(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill8(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy8(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove8(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy8(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel8_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel8_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill8_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill8_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill8_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel16(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel16(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void FCC linefill16(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill16(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill16(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy16(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove16(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy16(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel16_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel16_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill16_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill16_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill16_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel24(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel24(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void FCC linefill24(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill24(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill24(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy24(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove24(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy24(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel24_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel24_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill24_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill24_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill24_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel32(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel32(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void FCC linefill32(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill32(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill32(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy32(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove32(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy32(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel32_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel32_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill32_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill32_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill32_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#define unaligned_getpixel16 getpixel16
#define unaligned_setpixel16 setpixel16
#define unaligned_linefill16 linefill16
#define unaligned_vertfill16 vertfill16
#define unaligned_rectfill16 rectfill16
#define unaligned_rectcopy16 rectcopy16
#define unaligned_rectmove16 rectmove16
#define unaligned_linecopy16 linecopy16
#define unaligned_getpixel32 getpixel32
#define unaligned_setpixel32 setpixel32
#define unaligned_linefill32 linefill32
#define unaligned_vertfill32 vertfill32
#define unaligned_rectfill32 rectfill32
#define unaligned_rectcopy32 rectcopy32
#define unaligned_rectmove32 rectmove32
#define unaligned_linecopy32 linecopy32
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
#define unaligned_getpixel16_64 getpixel16_64
#define unaligned_setpixel16_64 setpixel16_64
#define unaligned_linefill16_64 linefill16_64
#define unaligned_vertfill16_64 vertfill16_64
#define unaligned_rectfill16_64 rectfill16_64
#define unaligned_getpixel32_64 getpixel32_64
#define unaligned_setpixel32_64 setpixel32_64
#define unaligned_linefill32_64 linefill32_64
#define unaligned_vertfill32_64 vertfill32_64
#define unaligned_rectfill32_64 rectfill32_64
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC unaligned_getpixel16(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC unaligned_setpixel16(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void FCC unaligned_linefill16(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC unaligned_vertfill16(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC unaligned_rectfill16(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC unaligned_rectcopy16(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC unaligned_rectmove16(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC unaligned_linecopy16(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC unaligned_getpixel32(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC unaligned_setpixel32(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void FCC unaligned_linefill32(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC unaligned_vertfill32(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC unaligned_rectfill32(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC unaligned_rectcopy32(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC unaligned_rectmove32(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC unaligned_linecopy32(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC unaligned_getpixel16_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC unaligned_setpixel16_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC unaligned_linefill16_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC unaligned_vertfill16_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC unaligned_rectfill16_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC unaligned_getpixel32_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC unaligned_setpixel32_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC unaligned_linefill32_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC unaligned_vertfill32_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC unaligned_rectfill32_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */


#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel1_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel1_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel2_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel2_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel4_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel4_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel8(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel16(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel24(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel32(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#define rp3_unaligned_setpixel16 rp3_setpixel16
#define rp3_unaligned_setpixel32 rp3_setpixel32
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_unaligned_setpixel16(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_unaligned_setpixel32(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */


/* Pixel I/O for formats with >32bpp (e.g. 64bpp) */
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTDEF ATTR_OUT(3) void NOTHROW(FCC buffer40_requirements)(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF ATTR_OUT(3) void NOTHROW(FCC buffer48_requirements)(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF ATTR_OUT(3) void NOTHROW(FCC buffer56_requirements)(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF ATTR_OUT(3) void NOTHROW(FCC buffer64_requirements)(video_dim_t size_x, video_dim_t size_y, struct video_rambuffer_requirements *__restrict result);
INTDEF WUNUSED ATTR_INOUT(1) size_t NOTHROW(FCC buffer40_coord2bytes)(video_coord_t *__restrict p_coord);
INTDEF WUNUSED ATTR_INOUT(1) size_t NOTHROW(FCC buffer48_coord2bytes)(video_coord_t *__restrict p_coord);
INTDEF WUNUSED ATTR_INOUT(1) size_t NOTHROW(FCC buffer56_coord2bytes)(video_coord_t *__restrict p_coord);
INTDEF WUNUSED ATTR_INOUT(1) size_t NOTHROW(FCC buffer64_coord2bytes)(video_coord_t *__restrict p_coord);

INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel40_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel40_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill40_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill40_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill40_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy40(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove40(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy40(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);

/* TODO: pixel48 can have a 2-byte aligned version that does 3*16-bit accesses */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel48_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel48_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill48_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill48_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill48_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy48(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove48(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy48(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);

INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel56_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel56_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill56_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill56_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill56_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy56(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove56(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy56(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);

INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC getpixel64_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC setpixel64_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC linefill64_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC vertfill64_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC rectfill64_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC rectcopy64(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC rectmove64(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC linecopy64(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);

#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#define unaligned_getpixel64_64 getpixel64_64
#define unaligned_setpixel64_64 setpixel64_64
#define unaligned_linefill64_64 linefill64_64
#define unaligned_vertfill64_64 vertfill64_64
#define unaligned_rectfill64_64 rectfill64_64
#define unaligned_rectcopy64    rectcopy64
#define unaligned_rectmove64    rectmove64
#define unaligned_linecopy64    linecopy64
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel64_t FCC unaligned_getpixel64_64(byte_t const *__restrict line, video_coord_t x);
INTDEF NONNULL((1)) void FCC unaligned_setpixel64_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel);
INTDEF NONNULL((1)) void FCC unaligned_linefill64_64(byte_t *__restrict line, video_coord_t x, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC unaligned_vertfill64_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t num_pixels);
INTDEF NONNULL((1)) void FCC unaligned_rectfill64_64(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel64_t pixel, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 4)) void FCC unaligned_rectcopy64(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC unaligned_rectmove64(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1, 3)) void FCC unaligned_linecopy64(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_CODEC_CODEC_UTILS_H */
