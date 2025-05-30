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
#ifndef _LIBVIDEO_CODEC_PALETTE_H
#define _LIBVIDEO_CODEC_PALETTE_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/__atomic.h>

#include <bits/types.h>
#include <kos/refcnt.h>

#include "pixel.h"

#ifdef __CC__
__DECL_BEGIN

struct video_palette_cache;
struct video_palette {
	/* [1..1][const] Destruction callback (invoked when `vp_refcnt' reaches `0') */
	__ATTR_NONNULL_T((1)) void
	__NOTHROW_T(LIBVIDEO_CODEC_CC *vp_destroy)(struct video_palette *__restrict self);
	__uintptr_t                            vp_refcnt; /* Reference counter. */
	struct video_palette_cache            *vp_cache;  /* [0..1][owned(malloc)][lock(WRITE_ONCE)] Color->pixel converter cache */
	__size_t                               vp_cnt;    /* [const] # of colors (must be >= what is required by the associated codec) */
	COMPILER_FLEXIBLE_ARRAY(video_color_t, vp_pal);   /* [vp_cnt] Palette colors */
};

#define video_palette_destroy(self) (*(self)->vp_destroy)(self)
#define video_palette_incref(self) \
	__hybrid_atomic_inc(&(self)->vp_refcnt, __ATOMIC_SEQ_CST)
#define video_palette_decref(self)                                           \
	(void)(__hybrid_atomic_decfetch(&(self)->vp_refcnt, __ATOMIC_SEQ_CST) || \
	       (video_palette_destroy(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_palette, vp_refcnt, video_palette_destroy)


/* Return the best-matching pixel for a given color.
 * For  the purpose  of determining  the best  match, this algorithm
 * leans towards emphasizing  colors best viewed  by the human  eye,
 * thus producing the best-looking results for those bipedal fellas.
 * NOTE: This function may lazily allocate `self->vp_cache', meaning
 *       that once  used, the  caller is  responsible to  eventually
 *       cleanup that field using `free(self->vp_cache)'. */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_pixel_t
(LIBVIDEO_CODEC_CC *PVIDEO_PALETTE_GETPIXEL)(struct video_palette *__restrict self, video_color_t color);
#ifdef LIBVIDEO_CODEC_WANT_PROTOTYPES
LIBVIDEO_CODEC_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) video_pixel_t LIBVIDEO_CODEC_CC
video_palette_getpixel(struct video_palette *__restrict self, video_color_t color);
#endif /* LIBVIDEO_CODEC_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_CODEC_PALETTE_H */
