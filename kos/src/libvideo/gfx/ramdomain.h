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
#ifndef GUARD_LIBVIDEO_GFX_RAMDOMAIN_H
#define GUARD_LIBVIDEO_GFX_RAMDOMAIN_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <stdbool.h>
#include <stddef.h>

#include <libvideo/codec/format.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>

DECL_BEGIN


/* Return the video domain to-be-used for a wrapper of `base' */
#if 1
#define video_buffer_domain_for_wrapper(base) (base)->vb_domain
#else
#define video_buffer_domain_for_wrapper(base) libvideo_ramdomain()
#endif


/************************************************************************/
/* RAM DOMAIN OPERATORS                                                 */
/************************************************************************/

INTDEF WUNUSED ATTR_IN(4) NONNULL((1)) REF struct video_buffer *CC
libvideo_ramdomain_newbuffer(struct video_domain const *__restrict self,
                             video_dim_t xdim, video_dim_t ydim,
                             struct video_format const *format,
                             unsigned int flags);
INTDEF WUNUSED ATTR_IN(4) NONNULL((1)) REF struct video_buffer *CC
libvideo_ramdomain_newbuffer_ex(struct video_domain const *__restrict self,
                                video_dim_t xdim, video_dim_t ydim,
                                struct video_codec_specs const *__restrict codec_specs,
                                struct video_palette *palette, unsigned int flags);
INTDEF WUNUSED ATTR_IN(4) NONNULL((1, 5)) REF struct video_buffer *CC
libvideo_ramdomain_formem(struct video_domain const *__restrict self, video_dim_t xdim, video_dim_t ydim,
                          struct video_format const *format, void *mem, size_t stride,
                          void (CC *release_mem)(void *cookie, void *mem),
                          void *release_mem_cookie, unsigned int flags);
INTDEF WUNUSED ATTR_IN(4) NONNULL((1, 6)) REF struct video_buffer *CC
libvideo_ramdomain_formem_ex(struct video_domain const *__restrict self, video_dim_t xdim, video_dim_t ydim,
                             struct video_codec_specs const *__restrict codec_specs,
                             struct video_palette *palette, void *mem, size_t stride,
                             void (CC *release_mem)(void *cookie, void *mem),
                             void *release_mem_cookie, unsigned int flags);
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(2) NONNULL((1)) struct video_codec const *CC
libvideo_ramdomain_fitting_codec(struct video_domain const *__restrict self,
                                 struct video_codec const *__restrict codec);
/************************************************************************/





/* Returns the default, built-in "RAM" video domain.
 *
 * Video buffers allocated by / using this domain are driven
 * by  software-only  (without  any  hardware  acceleration)
 *
 * On the plus side: these buffers are generally able to do
 * much more than buffers from hardware domains, given that
 * they can support **any** video codec. */
INTDEF /*ATTR_CONST*/ ATTR_RETNONNULL WUNUSED struct video_domain const *CC libvideo_ramdomain(void);
INTDEF struct video_domain libvideo_ramdomain_;

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_RAMDOMAIN_H */
