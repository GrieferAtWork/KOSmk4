/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif(x -> x.startswith("-O"));
gcc_opt.append("-O3"); // Force _all_ optimizations because stuff in here is performance-critical
]]]*/
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
#ifndef GUARD_LIBVIDEO_GFX_GFX_HL_C
#define GUARD_LIBVIDEO_GFX_GFX_HL_C 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

/************************************************************************/
/* HIGH-LEVEL, GENERIC GFX OPERATOR IMPLS                               */
/************************************************************************/

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <libvideo/codec/types.h>
#include <libvideo/gfx/gfx.h>

DECL_BEGIN

INTERN ATTR_IN(1) ATTR_IN(4) void CC
libvideo_gfx_generic_bitblit(struct video_gfx const *__restrict dst,
                             video_offset_t dst_x, video_offset_t dst_y,
                             struct video_gfx const *__restrict src,
                             video_offset_t src_x, video_offset_t src_y,
                             video_dim_t size_x, video_dim_t size_y) {
	struct video_blitter blitter, *p_blitter;
	p_blitter = video_gfx_blitfrom(dst, src, &blitter);
	video_blitter_bitblit(p_blitter, dst_x, dst_y,
	                      src_x, src_y, size_x, size_y);
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
libvideo_gfx_generic_stretch(struct video_gfx const *__restrict dst,
                             video_offset_t dst_x, video_offset_t dst_y,
                             video_dim_t dst_size_x, video_dim_t dst_size_y,
                             struct video_gfx const *__restrict src,
                             video_offset_t src_x, video_offset_t src_y,
                             video_dim_t src_size_x, video_dim_t src_size_y) {
	struct video_blitter blitter, *p_blitter;
	p_blitter = video_gfx_blitfrom(dst, src, &blitter);
	video_blitter_stretch(p_blitter,
	                      dst_x, dst_y, dst_size_x, dst_size_y,
	                      src_x, src_y, src_size_x, src_size_y);
}

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_libvideo_gfx_generic_XXX
#include "gfx/hl_generic.c.inl"

#define DEFINE_libvideo_blitter_generic_blit
#include "gfx/hl_blit-nowrap.c.inl"
#define DEFINE_libvideo_blitter_generic_stretch
#include "gfx/hl_blit-nowrap.c.inl"
#define DEFINE_libvideo_blitter_generic_blit_wrap
#include "gfx/hl_blit.c.inl"

#define DEFINE_libvideo_gfx__blitfrom_n
#include "gfx/hl_blitfrom.c.inl"
#define DEFINE_libvideo_gfx__blitfrom_l
#include "gfx/hl_blitfrom.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBVIDEO_GFX_GFX_HL_C */
