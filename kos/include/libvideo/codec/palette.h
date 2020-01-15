/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef _LIBVIDEO_CODEC_PALETTE_H
#define _LIBVIDEO_CODEC_PALETTE_H 1

#include "api.h"

#include <__stdinc.h>
#include <features.h>

#include <hybrid/atomic.h>

#include <bits/types.h>
#include <kos/ioctl/video.h>

#include "pixel.h"

__DECL_BEGIN

/* Video palette colors. */
#define VIDEO_PALCOLOR_BLACK         0x0 /* RGBA(0x00, 0x00, 0x00, 0xff) */
#define VIDEO_PALCOLOR_NAVY          0x1 /* RGBA(0x00, 0x00, 0xa8, 0xff) */
#define VIDEO_PALCOLOR_GREEN         0x2 /* RGBA(0x00, 0xa8, 0x00, 0xff) */
#define VIDEO_PALCOLOR_TEAL          0x3 /* RGBA(0x00, 0xa8, 0xa8, 0xff) */
#define VIDEO_PALCOLOR_MAROON        0x4 /* RGBA(0xa8, 0x00, 0x00, 0xff) */
#define VIDEO_PALCOLOR_PURPLE        0x5 /* RGBA(0xa8, 0x00, 0xa8, 0xff) */
#define VIDEO_PALCOLOR_OLIVE         0x6 /* RGBA(0xa8, 0x57, 0x00, 0xff) */
#define VIDEO_PALCOLOR_SILVER        0x7 /* RGBA(0xa8, 0xa8, 0xa8, 0xff) */
#define VIDEO_PALCOLOR_GREY          0x8 /* RGBA(0x57, 0x57, 0x57, 0xff) */
#define VIDEO_PALCOLOR_BLUE          0x9 /* RGBA(0x57, 0x57, 0xff, 0xff) */
#define VIDEO_PALCOLOR_LIME          0xa /* RGBA(0x57, 0xff, 0x57, 0xff) */
#define VIDEO_PALCOLOR_AQUA          0xb /* RGBA(0x57, 0xff, 0xff, 0xff) */
#define VIDEO_PALCOLOR_RED           0xc /* RGBA(0xff, 0x57, 0x57, 0xff) */
#define VIDEO_PALCOLOR_FUCHSIA       0xd /* RGBA(0xff, 0x57, 0xff, 0xff) */
#define VIDEO_PALCOLOR_YELLOW        0xe /* RGBA(0xff, 0xff, 0x57, 0xff) */
#define VIDEO_PALCOLOR_WHITE         0xf /* RGBA(0xff, 0xff, 0xff, 0xff) */
#define VIDEO_PALCOLOR_LIGHT_GRAY    VIDEO_PALCOLOR_SILVER
#define VIDEO_PALCOLOR_DARK_GRAY     VIDEO_PALCOLOR_GREY


#ifdef __CC__

struct video_palette {
	/* [1..1][const] Destruction callback (invoked when `vp_refcnt' reaches `0') */
	__ATTR_NONNULL((1)) void
	(LIBVIDEO_CODEC_CC *vp_destroy)(struct video_palette *__restrict self);
	__uintptr_t       vp_refcnt;     /* Reference counter. */
	video_pixel_t     vp_colors[16]; /* Pre-computed palette indices for the best match for one of `VIDEO_PALCOLOR_*'
	                                  * These are lazily populated when `video_palette_getpixel()' is called. */
	__size_t          vp_cnt;        /* [const] # of colors (== VIDEO_CODEC_PALSIZ(...)). */
	struct vd_palette vp_pal;        /* [const] OS palette data. */
};

#define video_palette_incref(self) \
	__hybrid_atomic_fetchinc((self)->vp_refcnt, __ATOMIC_SEQ_CST)
#define video_palette_decref(self)                                    \
	(__hybrid_atomic_decfetch((self)->vp_refcnt, __ATOMIC_SEQ_CST) || \
	 ((*(self)->vp_destroy)(self), 0))

#if defined(__cplusplus) && defined(__USE_KOS)
extern "C++" {
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) struct video_palette *
(LIBVIDEO_CODEC_CC incref)(struct video_palette *__restrict self) {
	video_palette_incref(self);
	return self;
}

__FORCELOCAL __ATTR_NONNULL((1)) void
(LIBVIDEO_CODEC_CC decref)(struct video_palette *__restrict self) {
	video_palette_decref(self);
}
}
#endif /* __cplusplus && __USE_KOS */



/* Return the best-matching pixel for a given color.
 * For the purpose of determining the best match, this algorithm
 * leans towards emphasizing colors best viewed by the human eye,
 * thus producing the best-looking results for those bipedal fellas.
 * NOTE: If the given `color' is one of `VIDEO_COLOR_*', `vp_colors'
 *       is used to quickly lookup the associated palette index.
 *       If the associated index is set to `(video_pixel_t)-1', the
 *       index will be calculated like any other color given would,
 *       and the result will be cached within the `vp_colors' vector. */
typedef __ATTR_NONNULL((1)) video_pixel_t
(LIBVIDEO_CODEC_CC *PVIDEO_PALETTE_GETPIXEL)(struct video_palette *__restrict self, video_color_t color);
#ifdef LIBVIDEO_CODEC_WANT_PROTOTYPES
LIBVIDEO_CODEC_DECL __ATTR_NONNULL((1)) video_pixel_t LIBVIDEO_CODEC_CC
video_palette_getpixel(struct video_palette *__restrict self, video_color_t color);
#endif /* LIBVIDEO_CODEC_WANT_PROTOTYPES */

#endif /* __CC__ */


__DECL_END

#endif /* !_LIBVIDEO_CODEC_PALETTE_H */
