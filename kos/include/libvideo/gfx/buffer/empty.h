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
#ifndef _LIBVIDEO_GFX_BUFFER_EMPTY_H
#define _LIBVIDEO_GFX_BUFFER_EMPTY_H 1

#include "../api.h"
/**/

#include <__stdinc.h>

#include <bits/types.h>
#include <kos/anno.h>

#include "../../types.h"
#include "../buffer.h"

#ifdef LIBVIDEO_GFX_EXPOSE_INTERNALS
#ifdef __CC__
__DECL_BEGIN

struct video_gfx_ops;
struct video_buffer_ops;
struct video_blitter_ops;
struct video_blitter3_ops;
struct video_buffer;
struct video_buffer_format;

/* Operator tables for video components representing 0 pixels */
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_gfx_ops const *(LIBVIDEO_GFX_CC *PVIDEO_EMPTYGFX_OPS)(void);
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_buffer_ops const *(LIBVIDEO_GFX_CC *PVIDEO_EMPTYBUFFER_OPS)(void);
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_blitter_ops const *(LIBVIDEO_GFX_CC *PVIDEO_EMPTYBLITTER_OPS)(void);
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_blitter3_ops const *(LIBVIDEO_GFX_CC *PVIDEO_EMPTYBLITTER3_OPS)(void);
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_buffer *(LIBVIDEO_GFX_CC *PVIDEO_EMPTYBUFFER)(void);
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T __REF struct video_buffer *(LIBVIDEO_GFX_CC *PVIDEO_EMPTYBUFFERREF)(void);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct video_gfx_ops const *LIBVIDEO_GFX_CC video_emptygfx_ops(void);
LIBVIDEO_GFX_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct video_buffer_ops const *LIBVIDEO_GFX_CC video_emptybuffer_ops(void);
LIBVIDEO_GFX_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct video_blitter_ops const *LIBVIDEO_GFX_CC video_emptyblitter_ops(void);
LIBVIDEO_GFX_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct video_blitter3_ops const *LIBVIDEO_GFX_CC video_emptyblitter3_ops(void);
LIBVIDEO_GFX_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct video_buffer *LIBVIDEO_GFX_CC video_emptybuffer(void);
LIBVIDEO_GFX_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED __REF struct video_buffer *LIBVIDEO_GFX_CC video_emptybufferref(void);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

/* Construct (or re-using an existing) empty video buffer with the given dimension
 * The returned buffer always uses `video_ramdomain(3V)' as its associated domain.
 * @param: __buffer_xdim, __buffer_ydim: Dimensions of the returned buffer (**NOT** swapped if VIDEO_GFX_F_XYSWAP is set)
 * @return: * : A reference to a video buffer without any backing
 *              storage, and  dimensions  matching  those  given.
 * @return: NULL: [errno=ENOMEM] Out of memory. */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_MAKEEMPTYBUFFER)(struct video_buffer_format const *__restrict __format,
                                          video_dim_t __buffer_xdim, video_dim_t __buffer_ydim);
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_MAKEEMPTYBUFFER_LIKE)(struct video_surface const *__restrict __surf,
                                               video_dim_t __buffer_xdim, video_dim_t __buffer_ydim);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_makeemptybuffer(struct video_buffer_format const *__restrict __format,
                      video_dim_t __buffer_xdim, video_dim_t __buffer_ydim);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_makeemptybuffer_like(struct video_surface const *__restrict __surf,
                           video_dim_t __buffer_xdim, video_dim_t __buffer_ydim);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */
#endif /* LIBVIDEO_GFX_EXPOSE_INTERNALS */

#endif /* !_LIBVIDEO_GFX_BUFFER_EMPTY_H */
