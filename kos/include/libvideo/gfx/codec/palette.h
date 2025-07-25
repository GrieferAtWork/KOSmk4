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

#ifdef __CC__
__DECL_BEGIN

#define VIDEO_PALETTE_F_NORMAL 0x0000 /* Normal flags */
#define VIDEO_PALETTE_F_ALPHA  0x0001 /* Palette contains colors with `VIDEO_COLOR_GET_ALPHA(c) != VIDEO_CHANNEL_MAX' */
typedef __uint32_t video_palette_flag_t;

struct video_palette_tree;
struct video_palette {
	/* [1..1][const] Translate a color into the closest palette index. */
	__ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_IN_T(1) video_pixel_t
	__NOTHROW_T(LIBVIDEO_GFX_FCC *vp_color2pixel)(struct video_palette const *__restrict self,
	                                              video_color_t color);
	/* [1..1][const] Destruction callback (invoked when `vp_refcnt' reaches `0') */
	__ATTR_NONNULL_T((1)) void
	__NOTHROW_T(LIBVIDEO_GFX_FCC *vp_destroy)(struct video_palette *__restrict self);
	__uintptr_t                              vp_refcnt; /* Reference counter. */
	struct video_palette_tree              *_vp_tree;   /* [0..1] Internal cache used by `video_palette_optimize()' */
	video_palette_flag_t                     vp_flags;  /* [const] Video palette flags (filled in by `video_palette_optimize()') */
	video_pixel_t                            vp_cnt;    /* [const] # of colors (must be >= what is required by the associated codec) */
	/* TODO: Change `struct video_palette' such that `vp_pal' is at offset=0,
	 *       and all other fields above are at negative offsets (meaning that
	 *       the struct's reference base is right here). */
	__COMPILER_FLEXIBLE_ARRAY(video_color_t, vp_pal);   /* [vp_cnt] Palette colors */
};

#define video_palette_destroy(self) (*(self)->vp_destroy)(self)
#define video_palette_incref(self) \
	__hybrid_atomic_inc(&(self)->vp_refcnt, __ATOMIC_SEQ_CST)
#define video_palette_decref(self)                                           \
	(void)(__hybrid_atomic_decfetch(&(self)->vp_refcnt, __ATOMIC_SEQ_CST) || \
	       (video_palette_destroy(self), 0))
#define video_palette_xincref(self) (void)(!(self) || (video_palette_incref(self), 0))
#define video_palette_xdecref(self) (void)(!(self) || (video_palette_decref(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_palette, vp_refcnt, video_palette_destroy)


/* Return the best-matching pixel for a given color.
 * For  the purpose  of determining  the best  match, this algorithm
 * leans towards emphasizing  colors best viewed  by the human  eye,
 * thus producing the best-looking results for those bipedal fellas. */
#define video_palette_getpixel(self, color) \
	((*(self)->vp_color2pixel)(self, color))


/* Create a new (uninitialized) palette for `__count' colors.
 *
 * This function is allowed to allocate a larger palette  than
 * requested if doing  so improves  performances, though  when
 * this is done, all additional palette entries will have been
 * initialized to `0'
 *
 * On success, the caller must initialize:
 * - return->vp_pal[0]
 * - return->vp_pal[1]
 * - ...
 * - return->vp_pal[__count - 2]
 * - return->vp_pal[__count - 1]
 *
 * @return: * :   The newly created palette
 * @return: NULL: Out of memory */
typedef __ATTR_WUNUSED __REF struct video_palette *
(LIBVIDEO_GFX_FCC *PVIDEO_PALETTE_CREATE)(video_pixel_t __count);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_palette *
LIBVIDEO_GFX_FCC video_palette_create(video_pixel_t __count);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

/* Optimize lookup times for `self', making `self->vp_color2pixel'
 * execute in sub-linear time (if possible). This function must be
 * called whenever `vp_pal' was  modified, and was called  before.
 * Prior  to being called, `self->vp_color2pixel' still works, but
 * executed in linear time (so you really want to call this one to
 * speed up palette lookups)
 *
 * This  function  is NOT  thread-safe,  so `self->vp_color2pixel'
 * must not be called by other threads until this function returns
 * @return: * : The optimized color palette */
typedef __ATTR_RETNONNULL_T __ATTR_WUNUSED_T __ATTR_INOUT_T(1) __REF struct video_palette *
(LIBVIDEO_GFX_FCC *PVIDEO_PALETTE_OPTIMIZE)(/*inherited(always)*/ __REF struct video_palette *__restrict self);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INOUT(1) __REF struct video_palette *LIBVIDEO_GFX_FCC
video_palette_optimize(/*inherited(always)*/ __REF struct video_palette *__restrict self);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_CODEC_PALETTE_H */
