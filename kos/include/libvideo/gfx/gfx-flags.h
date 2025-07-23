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
#ifndef _LIBVIDEO_GFX_GFX_FLAGS_H
#define _LIBVIDEO_GFX_GFX_FLAGS_H 1

#include "api.h"
/**/

#include <hybrid/typecore.h>


/* Video graphic flags. */
#define VIDEO_GFX_F_NORMAL   0x0000 /* Normal render flags. */
#define VIDEO_GFX_F_XWRAP    0x0001 /* OOB X coords wrap to the other side of the Clip Rect (else: coords are clamped) */
#define VIDEO_GFX_F_YWRAP    0x0002 /* OOB Y coords wrap to the other side of the Clip Rect (else: coords are clamped) */
#define VIDEO_GFX_F_XMIRROR  0x0004 /* X coords are horizontally mirrored relative to the Clip Rect */
#define VIDEO_GFX_F_YMIRROR  0x0008 /* Y coords are vertically mirrored relative to the Clip Rect */
#define VIDEO_GFX_F_XYSWAP   0x0010 /* Swap X/Y coords (width becoming height, and height becoming width)
                                     * WARNING: Do not alter this flag directly; use `video_gfx_xyswap()'
                                     * NOTE: Happens **after** VIDEO_GFX_F_XMIRROR/VIDEO_GFX_F_YMIRROR! */
#define VIDEO_GFX_F_NEAREST  0x0000 /* Use nearest interpolation for stretch() (flag used from src-gfx), lines, and floating-point pixel accesses */
#define VIDEO_GFX_F_LINEAR   0x0020 /* Use linear interpolation for stretch() (flag used from src-gfx), lines, and floating-point pixel accesses */
#define VIDEO_GFX_F_COLORKEY 0x0040 /* GFX uses a color-key; GFX blit operations will skip pixels matching the key */

#ifdef __CC__
__DECL_BEGIN

/* Set of `VIDEO_GFX_F*' */
typedef __UINT32_TYPE__ video_gfx_flag_t;

#define _VIDEO_GFX_FLAGS_X_TO_Y_LSHIFT 1
#define _VIDEO_GFX_FLAGS_Y_TO_X_RSHIFT _VIDEO_GFX_FLAGS_X_TO_Y_LSHIFT

#define _VIDEO_GFX_XFLAGS    (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_XMIRROR)
#define _VIDEO_GFX_YFLAGS    (VIDEO_GFX_F_YWRAP | VIDEO_GFX_F_YMIRROR)
#define _VIDEO_GFX_AND_FLAGS (0)
#define _VIDEO_GFX_OR_FLAGS  (VIDEO_GFX_F_LINEAR)
#define _VIDEO_GFX_XOR_FLAGS (~(_VIDEO_GFX_AND_FLAGS | _VIDEO_GFX_OR_FLAGS))

/* Combine pre-existing GFX flags `__old_flags' with `__more_flags' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED video_gfx_flag_t
video_gfx_flag_combine(video_gfx_flag_t __old_flags, video_gfx_flag_t __more_flags) {
	if (__old_flags & VIDEO_GFX_F_XYSWAP) {
		__more_flags = (__more_flags & ~(_VIDEO_GFX_XFLAGS | _VIDEO_GFX_YFLAGS)) |
		               ((__more_flags & _VIDEO_GFX_XFLAGS) << _VIDEO_GFX_FLAGS_X_TO_Y_LSHIFT) |
		               ((__more_flags & _VIDEO_GFX_YFLAGS) >> _VIDEO_GFX_FLAGS_Y_TO_X_RSHIFT);
	}
	return 0 |
#if _VIDEO_GFX_XOR_FLAGS != 0
	       ((__old_flags ^ __more_flags) & _VIDEO_GFX_XOR_FLAGS) |
#endif /* _VIDEO_GFX_XOR_FLAGS != 0 */
#if _VIDEO_GFX_OR_FLAGS != 0
	       ((__old_flags | __more_flags) & _VIDEO_GFX_OR_FLAGS) |
#endif /* _VIDEO_GFX_OR_FLAGS != 0 */
#if _VIDEO_GFX_AND_FLAGS != 0
	       ((__old_flags & __more_flags) & _VIDEO_GFX_AND_FLAGS) |
#endif /* _VIDEO_GFX_AND_FLAGS != 0 */
	       0;
}

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_GFX_FLAGS_H */
