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
#ifndef GUARD_LIBVIDEO_GFX_RAMFDDOMAIN_H
#define GUARD_LIBVIDEO_GFX_RAMFDDOMAIN_H 1

#include "api.h"
/**/

#include <libvideo/gfx/api.h>

#ifdef CONFIG_LIBVIDEO_HAVE_RAMFD
#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <stdbool.h>

#include <libvideo/crect.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/surface.h>
#include <libvideo/types.h>

DECL_BEGIN

/************************************************************************/
/* RAM DOMAIN                                                           */
/************************************************************************/

/* Video buffer types used to represent ram-fd buffers.
 * NOTE: None of these ever look at `video_buffer::vb_domain',
 *       so you're free to  re-use these at the  driver-level! */
INTDEF struct video_buffer_ops ramfdbuffer_ops;
INTDEF struct video_buffer_ops ramfdbuffer_subregion_ops;
INTDEF struct video_buffer_ops ramfdbuffer_subregion_rem_ops;

INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _ramfdbuffer_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _ramfdbuffer_subregion_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _ramfdbuffer_subregion_rem_ops(void);


/************************************************************************/
/* RAMFDBUFFER OPERATORS                                                */
/************************************************************************/

/* DESTROY */
INTDEF NONNULL((1)) void FCC ramfdbuffer__destroy(struct video_buffer *__restrict self);
INTDEF NONNULL((1)) void FCC ramfdbuffer_subregion_rem__destroy(struct video_buffer *__restrict self);

/* REVOKE+SUBREGION */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC ramfdbuffer_subregion__revoke)(struct video_buffer *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC ramfdbuffer_subregion_rem__revoke)(struct video_buffer *__restrict self);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC ramfdbuffer__subregion(struct video_surface const *__restrict self, struct video_crect const *__restrict rect);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC ramfdbuffer_subregion_rem__subregion(struct video_surface const *__restrict self, struct video_crect const *__restrict rect);

/* LOCK */
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC ramfdbuffer_subregion_rem__lockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);

/* GFX */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC ramfdbuffer_subregion_rem__initgfx(struct video_gfx *__restrict self);
#define ramfdbuffer_subregion_rem__updategfx (*(struct video_gfx *(FCC *)(struct video_gfx *__restrict, unsigned int))(void *)-1)

/* FDINFO */
#ifdef CONFIG_LIBVIDEO_HAVE_SERIALIZATION
INTDEF ATTR_INOUT(1) ATTR_OUT(2) void FCC
ramfdbuffer__fdinfo(struct video_buffer *__restrict self,
                    struct video_buffer_fdinfo *__restrict info);
INTDEF ATTR_INOUT(1) ATTR_OUT(2) void FCC
ramfdbuffer_subregion_rem__fdinfo(struct video_buffer *__restrict self,
                                  struct video_buffer_fdinfo *__restrict info);
#endif /* CONFIG_LIBVIDEO_HAVE_SERIALIZATION */

/* RAMFD DOMAIN OPERATORS */
INTDEF WUNUSED NONNULL((1)) ATTR_IN(2) REF struct video_buffer *CC
libvideo_ramfddomain_newbuffer(struct video_domain const *__restrict self,
                               struct video_buffer_format const *__restrict format,
                               video_dim_t xdim, video_dim_t ydim, unsigned int flags);
/************************************************************************/


/* Returns the default, built-in "RAM-FD" video domain. */
INTDEF /*ATTR_CONST*/ ATTR_RETNONNULL WUNUSED struct video_domain const *CC _libvideo_ramfddomain(void);
INTDEF struct video_domain libvideo_ramfddomain;

DECL_END
#endif /* CONFIG_LIBVIDEO_HAVE_RAMFD */

#endif /* !GUARD_LIBVIDEO_GFX_RAMFDDOMAIN_H */
