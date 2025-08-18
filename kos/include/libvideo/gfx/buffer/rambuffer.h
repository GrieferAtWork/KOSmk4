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
#ifndef _LIBVIDEO_GFX_BUFFER_RAMBUFFER_H
#define _LIBVIDEO_GFX_BUFFER_RAMBUFFER_H 1

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

struct video_rambuffer
#ifdef __cplusplus
    : video_buffer
#endif /* __cplusplus */
{
	/* >> vb_ops == &video_rambuffer_ops */
#ifndef __cplusplus
	struct video_buffer rb_buffer;
#endif /* !__cplusplus */
	/* This type is sufficient for doing simple GFX */
	__byte_t *rb_data;   /* [1..1][owned][const] Buffer data */
	__size_t  rb_stride; /* [const] Buffer stride */
};

struct video_rambuffer_formem
#ifdef __cplusplus
    : video_rambuffer
#endif /* __cplusplus */
{
	/* >> vb_ops == &video_rambuffer_formem_ops */
#ifndef __cplusplus
	struct video_rambuffer rbfm_rambuffer;
#endif /* !__cplusplus */
	void (LIBVIDEO_GFX_CC *rbfm_release_mem)(void *__cookie, void *__mem); /* [1..1][const] Callback invoked the first time `rbrv_dummy' is written to `rbrv_data' */
	void                  *rbfm_release_mem_cookie;                        /* [?..?][const] Cookie for `rbfm_release_mem' */
};

struct video_rambuffer_subregion
#ifdef __cplusplus
    : video_rambuffer
#endif /* __cplusplus */
{
	/* >> vb_ops == &video_rambuffer_subregion_ops ||
	 * >> vb_ops == &video_rambuffer_subregion_norem_ops */
#ifndef __cplusplus
	struct video_rambuffer rbs_rambuffer;
#endif /* !__cplusplus */
	__REF struct video_rambuffer *rbs_base;  /* [0..1][lock(ATOMIC && CLEAR_ONCE)] Underlying base buffer */
	video_coord_t                 rbs_bxrem; /* [const] Extra (sub-byte) X-offset added to all pixel coords */
	video_coord_t                 rbs_xoff;  /* [const] GFX X-offset */
	video_coord_t                 rbs_yoff;  /* [const] GFX Y-offset */
	video_coord_t                 rbs_xend;  /* [const] GFX X-end-offset */
	video_coord_t                 rbs_yend;  /* [const] GFX Y-end-offset */
};


/* Return operator tables for different types of ram-buffers, as seen above */
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_buffer_ops const *(LIBVIDEO_GFX_CC *PVIDEO_RAMBUFFER_OPS)(void);
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_buffer_ops const *(LIBVIDEO_GFX_CC *PVIDEO_RAMBUFFER_FORMEM_OPS)(void);
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_buffer_ops const *(LIBVIDEO_GFX_CC *PVIDEO_RAMBUFFER_SUBREGION_OPS)(void);
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_buffer_ops const *(LIBVIDEO_GFX_CC *PVIDEO_RAMBUFFER_SUBREGION_NOREM_OPS)(void);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct video_buffer_ops const *LIBVIDEO_GFX_CC video_rambuffer_ops(void);
LIBVIDEO_GFX_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct video_buffer_ops const *LIBVIDEO_GFX_CC video_rambuffer_formem_ops(void);
LIBVIDEO_GFX_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct video_buffer_ops const *LIBVIDEO_GFX_CC video_rambuffer_subregion_ops(void);
LIBVIDEO_GFX_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct video_buffer_ops const *LIBVIDEO_GFX_CC video_rambuffer_subregion_norem_ops(void);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */
#endif /* LIBVIDEO_GFX_EXPOSE_INTERNALS */

#endif /* !_LIBVIDEO_GFX_BUFFER_RAMBUFFER_H */
