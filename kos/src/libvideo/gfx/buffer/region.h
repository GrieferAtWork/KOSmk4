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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_REGION_H
#define GUARD_LIBVIDEO_GFX_BUFFER_REGION_H 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <libvideo/crect.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

DECL_BEGIN

struct video_rect;
struct region_buffer;

struct region_buffer: video_buffer {     /* vb_ops == &region_buffer_ops || vb_ops == &region_buffer_xoff_ops */
	video_offset_t           rbf_cxoff; /* [const] Starting X offset of Clip Rect in `rbf_base' */
	video_offset_t           rbf_cyoff; /* [const] Starting Y offset of Clip Rect in `rbf_base' */
	REF struct video_buffer *rbf_base;  /* [const] Underlying video buffer. */
};

INTDEF struct video_buffer_ops region_buffer_ops;
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _region_buffer_ops(void);


/* Operators for region buffers, as seen above */

/* DESTROY */
INTDEF NONNULL((1)) void FCC region_buffer__destroy(struct video_buffer *__restrict self);

/* REVOKE+SUBREGION */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC region_buffer__revoke)(struct video_buffer *__restrict self);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC region_buffer__subregion(struct video_surface const *__restrict self, struct video_crect const *__restrict rect);

/* LOCK */
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC region_buffer__rlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC region_buffer__wlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW(FCC region_buffer__unlockregion)(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);

/* GFX */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC region_buffer__initgfx(struct video_gfx *__restrict self);
#define region_buffer__updategfx (*(struct video_gfx *(FCC *)(struct video_gfx *__restrict, unsigned int))(void *)-1)



/* Create a new region-relative-proxy of `self', that interacts with the same
 * pixel data, both during GFX operations, as well when creating video locks.
 *
 * You can also use this function to create regions at negative offsets, or
 * ones that are larger than `self'.
 *
 * Then returned buffer always behaves properly when it comes to being able to
 * be  revoked, after which point it will never again make any access to pixel
 * data of `self'.
 *
 * When  the  given `rect'  is actually  a sub-region  of `self',  then this
 * function will simply make use of `video_surface_subregion()' and call the
 * dedicated video buffer operator for creating sub-regions.
 *
 * When the returned buffer isn't created as a true sub-region of  `self',
 * its `vb_domain' will be set to the return value of `video_ramdomain()'.
 *
 * @param: self: Video buffer to create a region of
 * @param: rect: region rect of `self' to-be returned
 * @return: * : The newly created region buffer
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=*] Failed to create region for some other reason */
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *CC
libvideo_surface_region(struct video_surface const *__restrict self,
                        struct video_rect const *__restrict rect);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *CC
libvideo_surface_region_distinct(struct video_surface const *__restrict self,
                                 struct video_rect const *__restrict rect);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *CC
_libvideo_surface_region(struct video_surface const *__restrict self,
                         struct video_rect const *__restrict buffer_rect);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *CC
_libvideo_surface_region_distinct(struct video_surface const *__restrict self,
                                  struct video_rect const *__restrict buffer_rect);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_REGION_H */
