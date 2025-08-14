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
#ifndef GUARD_LIBVIDEO_GFX_SWGFX_LL_C
#define GUARD_LIBVIDEO_GFX_SWGFX_LL_C 1
#define __VIDEO_BUFFER_const /* nothing */
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include "swgfx.h"

/************************************************************************/
/* LOW-LEVEL, GENERIC SW-GFX OPERATOR IMPLS                             */
/************************************************************************/

DECL_BEGIN

/* Shape rendering operator groups */
#define DEFINE_GFX_SWDRV_SHAPEOPS(name,                                                \
                                  xsws_line_llhh_,                                     \
                                  xsws_line_lhhl_,                                     \
                                  xsws_line_h_,                                        \
                                  xsws_line_v_,                                        \
                                  xsws_fill_,                                          \
                                  xsws_gradient_,                                      \
                                  xsws_gradient_h_,                                    \
                                  xsws_gradient_v_)                                    \
	PRIVATE struct gfx_swdrv_shapeops name = {};                                       \
	INTERN ATTR_RETNONNULL WUNUSED struct gfx_swdrv_shapeops const *CC _##name(void) { \
		if (!name.xsws_line_llhh) {                                                    \
			name.xsws_gradient_v = xsws_gradient_v_;                                   \
			name.xsws_gradient_h = xsws_gradient_h_;                                   \
			name.xsws_gradient   = xsws_gradient_;                                     \
			name.xsws_fill       = xsws_fill_;                                         \
			name.xsws_line_v     = xsws_line_v_;                                       \
			name.xsws_line_h     = xsws_line_h_;                                       \
			name.xsws_line_lhhl  = xsws_line_lhhl_;                                    \
			COMPILER_WRITE_BARRIER();                                                  \
			name.xsws_line_llhh = xsws_line_llhh_;                                     \
			COMPILER_WRITE_BARRIER();                                                  \
		}                                                                              \
		return &name;                                                                  \
	}

DEFINE_GFX_SWDRV_SHAPEOPS(libvideo_swgfx_shapeops__noblend,
                          libvideo_swgfx_noblend__line_llhh,
                          libvideo_swgfx_noblend__line_lhhl,
                          libvideo_swgfx_noblend__line_h,
                          libvideo_swgfx_noblend__line_v,
                          libvideo_swgfx_noblend__fill,
                          libvideo_swgfx_generic__gradient,
                          libvideo_swgfx_generic__gradient_h,
                          libvideo_swgfx_generic__gradient_v);
DEFINE_GFX_SWDRV_SHAPEOPS(libvideo_swgfx_shapeops__noblend_l,
                          libvideo_swgfx_noblend__line_llhh_l,
                          libvideo_swgfx_noblend__line_lhhl_l,
                          libvideo_swgfx_noblend__line_h,
                          libvideo_swgfx_noblend__line_v,
                          libvideo_swgfx_noblend__fill,
                          libvideo_swgfx_generic__gradient,
                          libvideo_swgfx_generic__gradient_h,
                          libvideo_swgfx_generic__gradient_v);
DEFINE_GFX_SWDRV_SHAPEOPS(libvideo_swgfx_shapeops__noblend_interp8888,
                          libvideo_swgfx_noblend__line_llhh,
                          libvideo_swgfx_noblend__line_lhhl,
                          libvideo_swgfx_noblend__line_h,
                          libvideo_swgfx_noblend__line_v,
                          libvideo_swgfx_noblend__fill,
                          libvideo_swgfx_noblend_interp8888__gradient,
                          libvideo_swgfx_noblend_interp8888__gradient_h,
                          libvideo_swgfx_noblend_interp8888__gradient_v);
DEFINE_GFX_SWDRV_SHAPEOPS(libvideo_swgfx_shapeops__noblend_interp8888_l,
                          libvideo_swgfx_noblend__line_llhh_l,
                          libvideo_swgfx_noblend__line_lhhl_l,
                          libvideo_swgfx_noblend__line_h,
                          libvideo_swgfx_noblend__line_v,
                          libvideo_swgfx_noblend__fill,
                          libvideo_swgfx_noblend_interp8888__gradient,
                          libvideo_swgfx_noblend_interp8888__gradient_h,
                          libvideo_swgfx_noblend_interp8888__gradient_v);

#define DEFINE_libvideo_swgfx_shapeops__preblend_FOO(name, mode, preblend_name, preblend) \
	DEFINE_GFX_SWDRV_SHAPEOPS(libvideo_swgfx_shapeops__preblend_##name,                   \
	                          libvideo_swgfx_preblend__line_llhh__##name,                 \
	                          libvideo_swgfx_preblend__line_lhhl__##name,                 \
	                          libvideo_swgfx_preblend__line_h__##name,                    \
	                          libvideo_swgfx_preblend__line_v__##name,                    \
	                          libvideo_swgfx_preblend__fill__##name,                      \
	                          libvideo_swgfx_preblend__gradient__##name,                  \
	                          libvideo_swgfx_preblend__gradient_h__##name,                \
	                          libvideo_swgfx_preblend__gradient_v__##name);               \
	DEFINE_GFX_SWDRV_SHAPEOPS(libvideo_swgfx_shapeops__preblend_##name##_l,               \
	                          libvideo_swgfx_preblend__line_llhh_l__##name,               \
	                          libvideo_swgfx_preblend__line_lhhl_l__##name,               \
	                          libvideo_swgfx_preblend__line_h__##name,                    \
	                          libvideo_swgfx_preblend__line_v__##name,                    \
	                          libvideo_swgfx_preblend__fill__##name,                      \
	                          libvideo_swgfx_preblend__gradient__##name,                  \
	                          libvideo_swgfx_preblend__gradient_h__##name,                \
	                          libvideo_swgfx_preblend__gradient_v__##name);
GFX_FOREACH_DEDICATED_PREBLENDMODE(DEFINE_libvideo_swgfx_shapeops__preblend_FOO)
#undef DEFINE_libvideo_swgfx_shapeops__preblend_FOO

DEFINE_GFX_SWDRV_SHAPEOPS(libvideo_swgfx_shapeops__generic,
                          libvideo_swgfx_generic__line_llhh,
                          libvideo_swgfx_generic__line_lhhl,
                          libvideo_swgfx_generic__line_h,
                          libvideo_swgfx_generic__line_v,
                          libvideo_swgfx_generic__fill,
                          libvideo_swgfx_generic__gradient,
                          libvideo_swgfx_generic__gradient_h,
                          libvideo_swgfx_generic__gradient_v);
DEFINE_GFX_SWDRV_SHAPEOPS(libvideo_swgfx_shapeops__generic_l,
                          libvideo_swgfx_generic__line_llhh_l,
                          libvideo_swgfx_generic__line_lhhl_l,
                          libvideo_swgfx_generic__line_h,
                          libvideo_swgfx_generic__line_v,
                          libvideo_swgfx_generic__fill,
                          libvideo_swgfx_generic__gradient,
                          libvideo_swgfx_generic__gradient_h,
                          libvideo_swgfx_generic__gradient_v);

DECL_END

#ifndef __INTELLISENSE__
#include "swgfx/ll_generic.c.inl"
/**/
#include "swgfx/ll_blit.c.inl"
#include "swgfx/ll_blit3.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_LL_C */
