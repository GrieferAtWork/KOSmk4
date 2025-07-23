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
#ifndef _LIBVIDEO_GFX_CODEC_CONVERTER_H
#define _LIBVIDEO_GFX_CODEC_CONVERTER_H 1

#include "../api.h"
/**/

#include <__stdinc.h>

#include "../../color.h"

#ifndef __INTELLISENSE__
#include "codec.h"
#include "../buffer.h"
#include "../surface-defs.h"
#endif /* !__INTELLISENSE__ */

#ifdef __CC__
__DECL_BEGIN

struct video_surface;

#ifndef _VIDEO_CONVERTER_N_YDRIVER
#define _VIDEO_CONVERTER_N_YDRIVER ((256 * __SIZEOF_VIDEO_PIXEL_T__) / __SIZEOF_POINTER__)
#endif /* !_VIDEO_CONVERTER_N_YDRIVER */
#if _VIDEO_CONVERTER_N_YDRIVER < 5
#undef _VIDEO_CONVERTER_N_YDRIVER
#define _VIDEO_CONVERTER_N_YDRIVER 5
#endif /* _VIDEO_CONVERTER_N_YDRIVER < 5 */
#define _VIDEO_CONVERTER_N_XDRIVER (_VIDEO_CONVERTER_N_YDRIVER - 2)

/* Helper structure for directly converting from 1 pixel format to another.  */
struct video_converter;
struct video_converter {
	/* [1..1] Map pixel from `vcv_from' into the format used by `vcv_to'.
	 * Same as the following (but faster in many cases):
	 * >> video_color_t color = video_format_pixel2color(&vcv_from, __from_pixel);
	 * >> video_pixel_t to_pixel = video_format_color2pixel(&vcv_to, color); */
	__ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_IN_T(1) video_pixel_t
	(LIBVIDEO_GFX_FCC *vcv_mappixel)(struct video_converter const *__restrict __self,
	                                 video_pixel_t __from_pixel);
	union {
		struct {
			struct video_surface const *vcv_from; /* [1..1] Source video format (may be invalid after init) */
			struct video_surface const *vcv_to;   /* [1..1] Target video format (may be invalid after init) */
			void *_vcv_xdriver[_VIDEO_CONVERTER_N_XDRIVER]; /* Driver-specific data */
		};
		void *_vcv_ydriver[_VIDEO_CONVERTER_N_YDRIVER]; /* Driver-specific data */
	};
};


#ifdef __INTELLISENSE__
/* Initialize a video pixel format converter */
extern __ATTR_RETNONNULL __ATTR_NONNULL((1, 2, 3)) struct video_converter *
video_converter_init(struct video_converter *__restrict __self,
                     struct video_surface const *__from_surface,
                     struct video_surface const *__to_surface);

/* Map a given `__from_pixel' (as read from a GFX using `__self->vcv_from')
 * into  the pixel format described by `__self->vcv_to', and return the new
 * pixel. */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_pixel_t
video_converter_mappixel(struct video_converter const *__restrict __self,
                         video_pixel_t __from_pixel);
#else /* __INTELLISENSE__ */
#define video_converter_init(self, from_surface, to_surface) \
	((self)->vcv_to = (to_surface), (*((self)->vcv_from = (from_surface))->vs_buffer->vb_codec->vc_initconverter)(self))
#define video_converter_mappixel(self, from_pixel) \
	(*(self)->vcv_mappixel)(self, from_pixel)
#endif /* !__INTELLISENSE__ */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_CODEC_CONVERTER_H */
