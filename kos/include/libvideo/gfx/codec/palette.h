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
#ifndef _LIBVIDEO_GFX_CODEC_PALETTE_H
#define _LIBVIDEO_GFX_CODEC_PALETTE_H 1

#include "../api.h"
/**/

#include <__stdinc.h>

#include <hybrid/__atomic.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/refcnt.h>

#include "../../color.h"

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

#ifdef __CC__
__DECL_BEGIN

#define VIDEO_PALETTE_F_NORMAL 0x0000 /* Normal flags */
#define VIDEO_PALETTE_F_ALPHA  0x0001 /* Palette contains colors with `VIDEO_COLOR_GET_ALPHA(c) != VIDEO_CHANNEL_MAX' */
typedef __uint32_t video_palette_flag_t;

struct video_palette_cache;
struct video_palette_object;
struct video_palette;

struct video_palette_ops {
	/* Destruction callback */
	__ATTR_NONNULL_T((1)) void
	__NOTHROW_T(LIBVIDEO_GFX_CC *vpo_destroy)(struct video_palette *__restrict __self);

	/* Optimize color2pixel conversion for the specified palette
	 * @return: * : Always re-returns `__self' */
	__ATTR_RETNONNULL_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __REF struct video_palette *
	(LIBVIDEO_GFX_CC *vpo_optimize)(__REF struct video_palette *__restrict __self);
};

struct video_palette_object {
	/* Sub-class-specific fields go here... */
	struct video_palette_cache    *_vp_cache;  /* [0..1] Internal cache (updated by `video_palette_optimize()') */
	struct video_palette_ops const *vp_ops;    /* [1..1][const] Operator table */
	struct video_domain const      *vp_domain; /* [1..1][const] Domain used to allocate this palette */
	__uintptr_t                     vp_refcnt; /* Reference counter. */

	/* [1..1] Translate a color into the closest palette index (updated by `video_palette_optimize()') */
	__ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_IN_T(1) video_pixel_t
	__NOTHROW_T(LIBVIDEO_GFX_FCC *vp_color2pixel)(struct video_palette const *__restrict __self,
	                                              video_color_t __color);

	video_palette_flag_t            vp_flags; /* Video palette flags (updated by `video_palette_optimize()') */
	video_pixel_t                   vp_cnt;   /* [const] # of colors (must be >= what is required by the associated codec) */
	__COMPILER_FLEXIBLE_ARRAY(video_color_t, vp_pal); /* [vp_cnt] Palette colors */
};




/* "raw" (possibly not object-based palette).
 * If a palette is "raw" cannot be determined by the palette alone. Instead, the user of a
 * palette needs to be aware of "raw"  palettes themselves. When not otherwise noted,  all
 * palettes can be considered as object-based (i.e. having a header).
 *
 * @see VIDEO_GFX_F_RAWPAL */
struct video_palette {
	video_color_t vp_pal[0x1000]; /* Palette colors ("0x1000" is  arbitrary here, but "C"  doesn't
	                               * allow the first member of a structure to be a flexible array) */
#ifdef __cplusplus
	__CXX_DELETE_DTOR(video_palette);
#endif /* __cplusplus */
};

#ifdef __INTELLISENSE__

/* Convert an array of colors into a (raw) `struct video_palette' */
extern __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct video_palette const *
video_palette_fromcolors(video_color_t const __colors[]);

/* Return a pointer to the array of colors described by `__self' */
#ifdef __cplusplus
extern "C++" {
extern __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) video_color_t const *
video_palette_getcolors(struct video_palette const *__restrict __self);
extern __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) video_color_t *
video_palette_getcolors(struct video_palette *__restrict __self);
} /* extern "C++" */
#else /* __cplusplus */
#define video_palette_getcolors(self) ((self)->vp_pal)
#endif /* !__cplusplus */

/* Return the full palette object associated with `__self' */
extern __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct video_palette_object *
video_palette_asobject(struct video_palette const *__restrict __self);

/* Return the simple palette object associated with `__self' */
extern __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct video_palette *
video_palette_fromobject(struct video_palette_object const *__restrict __self);

/* Convert a given `__pixel' to its equivalent color.
 * The caller must ensure that `pixel' isn't greater than the size of the palette. */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_color_t
video_palette_pixel2color(/*raw*/struct video_palette const *__restrict __self, video_pixel_t __pixel);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_color64_t
video_palette_pixel2color64(/*raw*/struct video_palette const *__restrict __self, video_pixel64_t __pixel);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

/* Return the best-matching pixel for a given color.
 * For  the purpose  of determining  the best  match, this algorithm
 * leans towards emphasizing  colors best viewed  by the human  eye,
 * thus producing the best-looking results for those bipedal fellas.
 *
 * Note  that  unlike  `video_palette_pixel2color()',  this   function
 * requires `__self' to be an object (meaning that "raw" palettes must
 * NOT be used here) */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_pixel_t
video_palette_color2pixel(/*obj*/struct video_palette const *__restrict __self, video_color_t __color);
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_pixel64_t
video_palette_color2pixel64(/*obj*/struct video_palette const *__restrict __self, video_color64_t __color);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

/* (Re-)optimize the given object-based video palette, and propagate
 * any modifications made to the video hardware (in case `__self' is
 * a hardware-based, or remote video palette)
 *
 * @return: * : Always re-returns `__self' */
extern __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __REF /*obj*/struct video_palette *
video_palette_optimize(__REF /*obj*/struct video_palette *__restrict __self);

/* Control the reference counter of an object-based video palette */
extern __ATTR_NONNULL((1)) void video_palette_incref(/*obj*/struct video_palette const *__restrict __self);
extern __ATTR_NONNULL((1)) void video_palette_decref(/*obj*/struct video_palette const *__restrict __self);
#else /* __INTELLISENSE__ */
#define video_palette_fromcolors(colors) \
	((struct video_palette const *)(colors))
#define video_palette_getcolors(self) ((self)->vp_pal)
#define video_palette_asobject(self) \
	((struct video_palette_object *)((__BYTE_TYPE__ *)(self) - __builtin_offsetof(struct video_palette_object, vp_pal)))
#define video_palette_fromobject(self) \
	((struct video_palette *)(self)->vp_pal)
#define video_palette_pixel2color(self, pixel) (self)->vp_pal[pixel]
#define video_palette_color2pixel(self, color) \
	((*video_palette_asobject(self)->vp_color2pixel)(self, color))
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
#define video_palette_pixel2color64(self, pixel) \
	VIDEO_COLOR64_FROM_COLOR((self)->vp_pal[pixel])
#define video_palette_color2pixel64(self, color) \
	((*video_palette_asobject(self)->vp_color2pixel)(self, VIDEO_COLOR_FROM_COLOR64(color)))
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
#define video_palette_optimize(self) (*video_palette_asobject(self)->vp_ops->vpo_optimize)(self)
#define video_palette_incref(self)   video_palette_object_incref(video_palette_asobject(self))
#define video_palette_decref(self)   video_palette_object_decref(video_palette_asobject(self))
#endif /* !__INTELLISENSE__ */


#define video_palette_object_destroy(self) (*(self)->vp_ops->vpo_destroy)(video_palette_fromobject(self))
#define video_palette_object_incref(self) \
	__hybrid_atomic_inc(&(self)->vp_refcnt, __ATOMIC_SEQ_CST)
#define video_palette_object_decref(self)                                    \
	(void)(__hybrid_atomic_decfetch(&(self)->vp_refcnt, __ATOMIC_SEQ_CST) || \
	       (video_palette_object_destroy(self), 0))
#define video_palette_object_xincref(self) (void)(!(self) || (video_palette_object_incref(self), 0))
#define video_palette_object_xdecref(self) (void)(!(self) || (video_palette_object_decref(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_palette_object, vp_refcnt, video_palette_object_destroy)



/* Generic (slow/fallback) pixel->color conversion function */
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_pixel_t
(LIBVIDEO_GFX_CC *PVIDEO_PALETTE_COLOR2PIXEL_GENERIC)(struct video_palette const *__restrict __self,
                                                      video_pixel_t __n_colors, video_color_t __color);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) video_pixel_t LIBVIDEO_GFX_CC
video_palette_color2pixel_generic(struct video_palette const *__restrict __self,
                                  video_pixel_t __n_colors, video_color_t __color);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_CODEC_PALETTE_H */
