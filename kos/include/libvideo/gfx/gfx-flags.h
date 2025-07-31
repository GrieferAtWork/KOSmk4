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
/*!replace_with_include <libvideo/gfx/gfx.h>*/
#ifndef _LIBVIDEO_GFX_GFX_FLAGS_H
#define _LIBVIDEO_GFX_GFX_FLAGS_H 1

#include "api.h"
/**/

#include <hybrid/typecore.h>


/* Video graphic flags. */
#define VIDEO_GFX_F_NORMAL   0x0000 /* Normal render flags. */
#define VIDEO_GFX_F_XYSWAP   0x0001 /* Swap X/Y coords (width becoming height, and height becoming width)
                                     * WARNING: Do not alter this flag directly; use `video_gfx_xyswap()'
                                     * NOTE: Happens **after** VIDEO_GFX_F_XMIRROR/VIDEO_GFX_F_YMIRROR! */
#define VIDEO_GFX_F_COLORKEY 0x0002 /* GFX uses a color-key; GFX blit operations will skip pixels matching the key */
#define VIDEO_GFX_F_XMIRROR  0x0004 /* X coords are horizontally mirrored relative to the Clip Rect */
#define VIDEO_GFX_F_YMIRROR  0x0008 /* Y coords are vertically mirrored relative to the Clip Rect */
#define VIDEO_GFX_F_XWRAP    0x0010 /* OOB X coords wrap to the other side of the Clip Rect (else: coords are clamped) */
#define VIDEO_GFX_F_YWRAP    0x0020 /* OOB Y coords wrap to the other side of the Clip Rect (else: coords are clamped) */
#define VIDEO_GFX_F_NEAREST  0x0000 /* Use nearest interpolation for stretch() (flag used from src-gfx), lines, and floating-point pixel accesses */
#define VIDEO_GFX_F_LINEAR   0x0040 /* Use linear interpolation for stretch() (flag used from src-gfx), lines, and floating-point pixel accesses */
#define VIDEO_GFX_F_PALOBJ   0x0080 /* The palette being used is non-NULL and object-based */



#define _VIDEO_GFX_FLAGS_X_TO_Y_LSHIFT 1
#define _VIDEO_GFX_FLAGS_Y_TO_X_RSHIFT _VIDEO_GFX_FLAGS_X_TO_Y_LSHIFT

#define _VIDEO_GFX_F_XFLAGS   (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_XMIRROR)
#define _VIDEO_GFX_F_YFLAGS   (VIDEO_GFX_F_YWRAP | VIDEO_GFX_F_YMIRROR)
#define _VIDEO_GFX_F_ANDFLAGS (0)
#define _VIDEO_GFX_F_ORFLAGS  (VIDEO_GFX_F_LINEAR | VIDEO_GFX_F_PALOBJ)
#define _VIDEO_GFX_F_XORFLAGS (~(_VIDEO_GFX_F_ANDFLAGS | _VIDEO_GFX_F_ORFLAGS))

#if ((_VIDEO_GFX_F_XFLAGS << _VIDEO_GFX_FLAGS_X_TO_Y_LSHIFT) != _VIDEO_GFX_F_YFLAGS || \
     (_VIDEO_GFX_F_YFLAGS >> _VIDEO_GFX_FLAGS_Y_TO_X_RSHIFT) != _VIDEO_GFX_F_XFLAGS)
#error "Bad values for flags (X/Y-swap isn't configured properly)"
#endif /* ... */

/* Swap X/Y-specific flags in `f' with their counterpart */
#define _VIDEO_GFX_F_XYSWAP_FLAGS(f)                                   \
	(((f) & ~(_VIDEO_GFX_F_XFLAGS | _VIDEO_GFX_F_YFLAGS)) |            \
	 (((f) & _VIDEO_GFX_F_XFLAGS) << _VIDEO_GFX_FLAGS_X_TO_Y_LSHIFT) | \
	 (((f) & _VIDEO_GFX_F_YFLAGS) >> _VIDEO_GFX_FLAGS_Y_TO_X_RSHIFT))


/* High-level helper macros to apply transformations to `VIDEO_GFX_F_*'
 * These should only be used to set the flags of `video_surface'.  When
 * doing  these transformation operations on `video_gfx', the dedicated
 * methods of the same names (but lowercase) should be used.
 *
 * >> struct video_gfx gfx;
 * >> struct video_surface surf = *video_buffer_assurface(buffer);
 * >> video_surface_setflags(&surf, VIDEO_GFX_LROT90(video_surface_getflags(&surf)));
 * >> video_surface_getgfx(&surf, &gfx); // "gfx" comes pre-LROT90-tated relative to "buffer" */
#define VIDEO_GFX_XYSWAP(f)     (_VIDEO_GFX_F_XYSWAP_FLAGS(f) ^ VIDEO_GFX_F_XYSWAP)
#define VIDEO_GFX_LROT90(f)     (_VIDEO_GFX_F_XYSWAP_FLAGS(f) ^ (VIDEO_GFX_F_XYSWAP | VIDEO_GFX_F_YMIRROR))
#define VIDEO_GFX_RROT90(f)     (_VIDEO_GFX_F_XYSWAP_FLAGS(f) ^ (VIDEO_GFX_F_XYSWAP | VIDEO_GFX_F_XMIRROR))
#define VIDEO_GFX_ROT180(f)     ((f) ^ (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR))
#define VIDEO_GFX_HMIRROR(f)    ((f) ^ VIDEO_GFX_F_XMIRROR)
#define VIDEO_GFX_VMIRROR(f)    ((f) ^ VIDEO_GFX_F_YMIRROR)
#define VIDEO_GFX_LROT90n(f, n) (((n) & 3) == 3 ? VIDEO_GFX_RROT90(f) : (((n) & 3) == 2 ? VIDEO_GFX_ROT180(f) : (((n) & 3) == 1 ? VIDEO_GFX_LROT90(f) : (f))))
#define VIDEO_GFX_RROT90n(f, n) (((n) & 3) == 3 ? VIDEO_GFX_LROT90(f) : (((n) & 3) == 2 ? VIDEO_GFX_ROT180(f) : (((n) & 3) == 1 ? VIDEO_GFX_RROT90(f) : (f))))


#ifdef __CC__
__DECL_BEGIN

/* Set of `VIDEO_GFX_F*' */
typedef __UINT32_TYPE__ video_gfx_flag_t;

/* Combine pre-existing GFX flags `__old_flags' with `__more_flags' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED video_gfx_flag_t
video_gfx_flag_combine(video_gfx_flag_t __old_flags, video_gfx_flag_t __more_flags) {
	if (__old_flags & VIDEO_GFX_F_XYSWAP) {
		/* If `__old_flags' indicate that X/Y  should be swapped, then the  initial
		 * set of X/Y-flags of `__more_flags' must still be applied in the  context
		 * of coordinate  transformations happening  **after** any  transformations
		 * currently done by `__old_flags'. Since those coords are already swapped,
		 * anything fed into `__more_flags' comes pre-swapped.
		 *
		 * Since we want to flatten these transformations, we must apply this pre-
		 * swapping by inverting X/Y-flags  in `__more_flags' prior to  combining. */
		__more_flags = _VIDEO_GFX_F_XYSWAP_FLAGS(__more_flags);
	}
	return 0 |
#if _VIDEO_GFX_F_XORFLAGS != 0
	       ((__old_flags ^ __more_flags) & _VIDEO_GFX_F_XORFLAGS) |
#endif /* _VIDEO_GFX_F_XORFLAGS != 0 */
#if _VIDEO_GFX_F_ORFLAGS != 0
	       ((__old_flags | __more_flags) & _VIDEO_GFX_F_ORFLAGS) |
#endif /* _VIDEO_GFX_F_ORFLAGS != 0 */
#if _VIDEO_GFX_F_ANDFLAGS != 0
	       ((__old_flags & __more_flags) & _VIDEO_GFX_F_ANDFLAGS) |
#endif /* _VIDEO_GFX_F_ANDFLAGS != 0 */
	       0;
}

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_GFX_FLAGS_H */
