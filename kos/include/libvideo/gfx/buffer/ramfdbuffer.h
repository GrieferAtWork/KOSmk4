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
#ifndef _LIBVIDEO_GFX_BUFFER_RAMFDBUFFER_H
#define _LIBVIDEO_GFX_BUFFER_RAMFDBUFFER_H 1

#include "../api.h"
/**/

#ifdef CONFIG_LIBVIDEO_HAVE_RAMFD
#include <__stdinc.h>

#include <bits/types.h>
#include <kos/anno.h>

#include "../../types.h"
#include "../buffer.h"
#include "rambuffer.h"

#ifdef LIBVIDEO_GFX_EXPOSE_INTERNALS
#ifdef __CC__
__DECL_BEGIN

struct video_ramfdbuffer
#ifdef __cplusplus
    : video_rambuffer
#endif /* __cplusplus */
{
	/* >> vb_ops == &video_ramfdbuffer_ops ||
	 * >> vb_ops == &video_ramfdbuffer_subregion_ops */
#ifndef __cplusplus
	struct video_rambuffer rfdb_buffer;
#endif /* !__cplusplus */
	__size_t rfdb_total; /* [const] Total # of bytes that are being mapped (may be slightly less than "YDIM * STRIDE"
	                      * in  sub-regions where the last line doesn't need to be mapped). Just like "rb_data", this
	                      * value is NOT page-aligned! */
	__fd_t   rfdb_fd;    /* [const] memfd_create()'ed file descriptor, or `FILE_IOC_SUBREGION' for sub-regions
	                      * In either case, `rfdb_buffer.rb_data' is the result of mmap'ing this fd, with sub-
	                      * page byte offsets as per `video_buffer_fdinfo::vbfdi_bxoff' stored in the PAGEMASK
	                      * of `rfdb_buffer.rb_data'. */
};

struct video_ramfdbuffer_subregion_rem
#ifdef __cplusplus
    : video_buffer
#endif /* __cplusplus */
{
	/* >> vb_ops == &video_ramfdbuffer_subregion_rem_ops */
	__REF struct video_ramfdbuffer *rfdbsr_base;  /* [1..1][const] Underlying sub-region buffer with access to an extra "rfdbsr_bxrem" pixels on the left side */
	video_coord_t                   rfdbsr_bxrem; /* [!= 0][const] Extra (sub-byte) X-offset added to all pixel coords */
};


/* Return operator tables for different types of ramfd-buffers, as seen above */
typedef __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_buffer_ops const *(LIBVIDEO_GFX_CC *PVIDEO_RAMFDBUFFER_OPS)(void);
typedef __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_buffer_ops const *(LIBVIDEO_GFX_CC *PVIDEO_RAMFDBUFFER_SUBREGION_OPS)(void);
typedef __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_buffer_ops const *(LIBVIDEO_GFX_CC *PVIDEO_RAMFDBUFFER_SUBREGION_REM_OPS)(void);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_RETNONNULL __ATTR_WUNUSED struct video_buffer_ops const *LIBVIDEO_GFX_CC video_ramfdbuffer_ops(void);
LIBVIDEO_GFX_DECL __ATTR_RETNONNULL __ATTR_WUNUSED struct video_buffer_ops const *LIBVIDEO_GFX_CC video_ramfdbuffer_subregion_ops(void);
LIBVIDEO_GFX_DECL __ATTR_RETNONNULL __ATTR_WUNUSED struct video_buffer_ops const *LIBVIDEO_GFX_CC video_ramfdbuffer_subregion_rem_ops(void);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */
#endif /* LIBVIDEO_GFX_EXPOSE_INTERNALS */
#endif /* CONFIG_LIBVIDEO_HAVE_RAMFD */

#endif /* !_LIBVIDEO_GFX_BUFFER_RAMFDBUFFER_H */
