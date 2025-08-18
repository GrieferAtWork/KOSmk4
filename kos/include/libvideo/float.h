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
#ifndef _LIBVIDEO_FLOAT_H
#define _LIBVIDEO_FLOAT_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include "types.h"

#ifdef __CC__
__DECL_BEGIN

#define VIDEO_FCOORD_NFRAC 16 /* # of fractional bits in `video_fcoord_t' / `video_fcoord_t' */
typedef __INT_FAST64_TYPE__ video_foffset_t;      /* video_offset_t with fixed fractional part */
typedef __UINT_FAST64_TYPE__ video_fcoord_t;      /* video_coord_t with fixed fractional part */
typedef __UINT_FAST16_TYPE__ video_fcoord_frac_t; /* uint_fast{VIDEO_FCOORD_NFRAC}_t */
#define VIDEO_FOFFSET(whole, frac) (((video_foffset_t)(whole) << VIDEO_FCOORD_NFRAC) + (frac))
#define VIDEO_FOFFSET_WHOLE(fp)    ((video_offset_t)(fp) >> VIDEO_FCOORD_NFRAC)
#define VIDEO_FOFFSET_FRAC(fp)     ((video_fcoord_frac_t)(fp) & (video_fcoord_frac_t)(VIDEO_FOFFSET(1, 0) - 1))
#define VIDEO_FCOORD(whole, frac)  (((video_fcoord_t)(whole) << VIDEO_FCOORD_NFRAC) + (frac))
#define VIDEO_FCOORD_WHOLE(fp)     ((video_coord_t)(fp) >> VIDEO_FCOORD_NFRAC)
#define VIDEO_FCOORD_FRAC(fp)      ((video_fcoord_frac_t)(fp) & (video_fcoord_frac_t)(VIDEO_FCOORD(1, 0) - 1))
#if VIDEO_FCOORD_NFRAC == 8 || VIDEO_FCOORD_NFRAC == 16 || VIDEO_FCOORD_NFRAC == 32
#define VIDEO_FCOORD_FRAC_CAST(v)  ((video_fcoord_frac_t)(v))
#else /* VIDEO_FCOORD_NFRAC == ... */
#define VIDEO_FCOORD_FRAC_CAST(v)  ((video_fcoord_frac_t)(v) & (((video_fcoord_frac_t)1 << VIDEO_FCOORD_NFRAC) - 1))
#endif /* VIDEO_FCOORD_NFRAC != ... */
#define VIDEO_FOFFSET_FRAC_CAST VIDEO_FCOORD_FRAC_CAST

#ifdef __NO_FPU
typedef video_foffset_t video_float_t;
#define VIDEO_FLOAT_ONE              VIDEO_FOFFSET(1, 0)
#define VIDEO_FLOAT(whole, frac)     VIDEO_FOFFSET(whole, frac)
#define VIDEO_FLOAT_AS_FOFFSET(fp)   (video_foffset_t)(fp)
#define VIDEO_FLOAT_AS_FCOORD(fp)    (video_fcoord_t)(fp)
#define VIDEO_FLOAT_FROM_FOFFSET(fp) (video_foffset_t)(fp)
#define VIDEO_FLOAT_FROM_FCOORD(fp)  (video_fcoord_t)(fp)
#else /* __NO_FPU */
typedef float video_float_t;
#define VIDEO_FLOAT_ONE          1.0
#define VIDEO_FLOAT(whole, frac) ((float)(whole) + (frac))
#define VIDEO_FLOAT_AS_FOFFSET(fp) \
	((video_foffset_t)(fp) + VIDEO_FOFFSET_FRAC_CAST((float)(fp) * VIDEO_FCOORD(1, 0)))
#define VIDEO_FLOAT_AS_FCOORD(fp) \
	((video_fcoord_t)(fp) + VIDEO_FCOORD_FRAC_CAST((float)(fp) * VIDEO_FCOORD(1, 0)))
#define VIDEO_FLOAT_FROM_FOFFSET(fp) \
	((float)VIDEO_FOFFSET_WHOLE(fp) + ((float)VIDEO_FOFFSET_FRAC(fp) / (float)VIDEO_FOFFSET(1, 0)))
#define VIDEO_FLOAT_FROM_FCOORD(fp) \
	((float)VIDEO_FCOORD_WHOLE(fp) + ((float)VIDEO_FCOORD_FRAC(fp) / (float)VIDEO_FCOORD(1, 0)))
#endif /* !__NO_FPU */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_FLOAT_H */
