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
#ifndef _LIBVIDEO_CODEC_FORMAT_H
#define _LIBVIDEO_CODEC_FORMAT_H 1

#include <__stdinc.h>

#include <hybrid/__assert.h>

#include <bits/types.h>

#include "api.h"
#include "pixel.h"
#include "types.h"

#ifdef __cplusplus
#include <__stdcxx.h>

#include "codecs.h"
#endif /* __cplusplus */

__DECL_BEGIN

#ifdef __CC__
struct video_codec;
struct video_palette;
struct video_format;

/* Helper macros for doing software-driven, low-level video data manipulations. */
#ifdef __INTELLISENSE__

/* Check if the given video-format can produce colors with a non-0xff alpha channel */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL
video_format_hasalpha(struct video_format const *__restrict __self);

/* Get a pixel (The caller must ensure that the given x is in-bounds) */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) video_pixel_t
video_format_getpixel(struct video_format const *__restrict __self,
                      __byte_t const *__restrict __line, video_coord_t __x);

/* Set a pixel (The caller must ensure that the given x is in-bounds) */
extern __ATTR_NONNULL((1, 2)) void
video_format_setpixel(struct video_format const *__restrict __self,
                      __byte_t *__restrict __line,
                      video_coord_t __x, video_pixel_t __pixel);

/* Convert between color and pixel values. */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) video_color_t
video_format_pixel2color(struct video_format const *__restrict __self,
                         video_pixel_t __pixel);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) video_pixel_t
video_format_color2pixel(struct video_format const *__restrict __self,
                         video_color_t __color);

/* Convenience wrappers to combine:
 * - video_format_getcolor = video_format_pixel2color(video_format_getpixel(...))
 * - video_format_setcolor = video_format_setpixel(video_format_color2pixel(...))
 */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) video_color_t
video_format_getcolor(struct video_format const *__restrict __self,
                      __byte_t const *__restrict __line, video_coord_t __x);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) void
video_format_setcolor(struct video_format const *__restrict __self,
                      __byte_t *__restrict __line,
                      video_coord_t __x, video_color_t __color);

/* Copy a rect of pixels. When src/dst overlap, results are weak-undefined.
 * @assume(IS_ALIGNED(__dst_line, __self->vf_codec->vc_align));
 * @assume(IS_ALIGNED(__src_line, __self->vf_codec->vc_align));
 * @assume(IS_ALIGNED(__dst_stride, __self->vf_codec->vc_align));
 * @assume(IS_ALIGNED(__src_stride, __self->vf_codec->vc_align));
 * @assume(__size_x > 0);
 * @assume(__size_y > 0); */
extern __ATTR_NONNULL((1, 2, 5)) void
video_format_rectcopy(struct video_format const *__restrict __self,
                      __byte_t *__restrict __dst_line, video_coord_t __dst_x, __size_t __dst_stride,
                      __byte_t const *__restrict __src_line, video_coord_t __src_x, __size_t __src_stride,
                      video_dim_t __size_x, video_dim_t __size_y);

/* Fill `num_pixels'  neighboring  pixels  horizontally.
 * The caller must ensure that all coords are in-bounds.
 * @assume(IS_ALIGNED(__line, __self->vf_codec->vc_align));
 * @assume(__num_pixels > 0); */
extern __ATTR_NONNULL((1, 2)) void
video_format_linefill(struct video_format const *__restrict __self,
                      __byte_t *__restrict __line, video_coord_t __x,
                      video_pixel_t __pixel, video_dim_t __num_pixels);

/* Fill a vertical line of pixels.
 * @assume(IS_ALIGNED(__line, __self->vf_codec->vc_align));
 * @assume(IS_ALIGNED(__stride, __self->vf_codec->vc_align));
 * @assume(__num_pixels > 0); */
extern __ATTR_NONNULL((1, 2)) void
video_format_vertfill(struct video_format const *__restrict __self,
                      __byte_t *__restrict __line, video_coord_t __x, __size_t __stride,
                      video_pixel_t __pixel, video_dim_t __num_pixels);


/* Fill a rect of pixels.
 * @assume(__size_x > 0);
 * @assume(__size_y > 0);
 * @assume(IS_ALIGNED(__line, __self->vf_codec->vc_align));
 * @assume(IS_ALIGNED(__stride, __self->vf_codec->vc_align)); */
extern __ATTR_NONNULL((1, 2)) void
video_format_rectfill(struct video_format const *__restrict __self,
                      __byte_t *__restrict __line, video_coord_t __x, __size_t __stride,
                      video_pixel_t __pixel, video_dim_t __size_x, video_dim_t __size_y);
#else /* __INTELLISENSE__ */
#define video_format_hasalpha(self)                                      \
	((self)->vf_pal ? ((self)->vf_pal->vp_flags & VIDEO_PALETTE_F_ALPHA) \
	                : ((self)->vf_codec->vc_specs.vcs_amask != 0))
#define video_format_getpixel(self, line, x)        (*(self)->vf_codec->vc_getpixel)(line, x)
#define video_format_setpixel(self, line, x, pixel) (*(self)->vf_codec->vc_setpixel)(line, x, pixel);
#define video_format_pixel2color(self, pixel)       (*(self)->vf_codec->vc_pixel2color)(self, pixel)
#define video_format_color2pixel(self, color)       (*(self)->vf_codec->vc_color2pixel)(self, color)
#define video_format_getcolor(self, line, x)        video_format_pixel2color(self, video_format_getpixel(self, line, x))
#define video_format_setcolor(self, line, x, color) video_format_setpixel(self, line, x, video_format_color2pixel(self, color))
#define video_format_rectcopy(self, dst_line, dst_x, dst_stride, src_line, src_x, src_stride, size_x, size_y) \
	(*(self)->vf_codec->vc_rectcopy)(dst_line, dst_x, dst_stride, src_line, src_x, src_stride, size_x, size_y)
#define video_format_linefill(self, dst_line, x, pixel, num_pixels) \
	(*(self)->vf_codec->vc_linefill)(dst_line, x, pixel, num_pixels)
#define video_format_vertfill(self, dst_line, x, stride, pixel, num_pixels) \
	(*(self)->vf_codec->vc_vertfill)(dst_line, x, stride, pixel, num_pixels)
#define video_format_rectfill(self, dst_line, x, stride, pixel, size_x, size_y) \
	(*(self)->vf_codec->vc_rectfill)(dst_line, x, stride, pixel, size_x, size_y)
#endif /* !__INTELLISENSE__ */

struct video_format {
	struct video_codec const     *vf_codec;  /* [1..1] Video codec. */
	/*REF*/ struct video_palette *vf_pal;    /* [0..1] Color palette (if applicable) */
#ifdef __cplusplus
public: /* Low-level, memory-based pixel accessor functions. */

	/* Get a pixel (The caller must ensure that the given x/y are in-bounds) */
	__CXX_CLASSMEMBER video_pixel_t LIBVIDEO_CODEC_CC getpixel(__byte_t const *__restrict __line, video_coord_t __x) const { return video_format_getpixel(this, __line, __x); }
	__CXX_CLASSMEMBER video_color_t LIBVIDEO_CODEC_CC getcolor(__byte_t const *__restrict __line, video_coord_t __x) const { return video_format_getcolor(this, __line, __x); }

	/* Set a pixel (The caller must ensure that the given x/y are in-bounds) */
	__CXX_CLASSMEMBER void LIBVIDEO_CODEC_CC setpixel(__byte_t *__restrict __line, video_coord_t __x, video_pixel_t __pixel) const { video_format_setpixel(this, __line, __x, __pixel); }
	__CXX_CLASSMEMBER void LIBVIDEO_CODEC_CC setcolor(__byte_t *__restrict __line, video_coord_t __x, video_color_t __color) const { video_format_setcolor(this, __line, __x, __color); }

	/* Convert between color and pixel values. */
	__CXX_CLASSMEMBER video_color_t LIBVIDEO_CODEC_CC pixel2color(video_pixel_t __pixel) const { return video_format_pixel2color(this, __pixel); }
	__CXX_CLASSMEMBER video_pixel_t LIBVIDEO_CODEC_CC color2pixel(video_color_t __color) const { return video_format_color2pixel(this, __color); }

	/* Copy a rect of pixels. When src/dst overlap, results are weak-undefined.
	 * @assume(IS_ALIGNED(__dst_line, vf_codec->vc_align));
	 * @assume(IS_ALIGNED(__src_line, vf_codec->vc_align));
	 * @assume(IS_ALIGNED(__dst_stride, vf_codec->vc_align));
	 * @assume(IS_ALIGNED(__src_stride, vf_codec->vc_align));
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__CXX_CLASSMEMBER void LIBVIDEO_CODEC_CC rectcopy(__byte_t *__restrict __dst_line, video_coord_t __dst_x, __size_t __dst_stride,
	                                                  __byte_t const *__restrict __src_line, video_coord_t __src_x, __size_t __src_stride,
	                                                  video_dim_t __size_x, video_dim_t __size_y) const {
		video_format_rectcopy(this, __dst_line, __dst_x, __dst_stride, __src_line, __src_x, __src_stride, __size_x, __size_y);
	}

	/* Fill `num_pixels'  neighboring  pixels  horizontally.
	 * The caller must ensure that all coords are in-bounds.
	 * @assume(IS_ALIGNED(__line, vf_codec->vc_align));
	 * @assume(__num_pixels > 0); */
	__CXX_CLASSMEMBER void LIBVIDEO_CODEC_CC linefill(__byte_t *__restrict __line, video_coord_t __x,
	                                                  video_pixel_t __pixel, video_dim_t __num_pixels) const {
		video_format_linefill(this, __line, __x, __pixel, __num_pixels);
	}

	/* Fill a vertical line of pixels.
	 * @assume(IS_ALIGNED(__line, vf_codec->vc_align));
	 * @assume(IS_ALIGNED(__stride, vf_codec->vc_align));
	 * @assume(__num_pixels > 0); */
	__CXX_CLASSMEMBER void LIBVIDEO_CODEC_CC vertfill(__byte_t *__restrict __line, video_coord_t __x, __size_t __stride,
	                                                  video_pixel_t __pixel, video_dim_t __num_pixels) const {
		video_format_vertfill(this, __line, __x, __stride, __pixel, __num_pixels);
	}

	/* Fill a rect of pixels.
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0);
	 * @assume(IS_ALIGNED(__line, vf_codec->vc_align));
	 * @assume(IS_ALIGNED(__stride, vf_codec->vc_align)); */
	__CXX_CLASSMEMBER void LIBVIDEO_CODEC_CC rectfill(__byte_t *__restrict __line, video_coord_t __x, __size_t __stride,
	                                                  video_pixel_t __pixel, video_dim_t __size_x, video_dim_t __size_y) const {
		video_format_rectfill(this, __line, __x, __stride, __pixel, __size_x, __size_y);
	}

#endif /* __cplusplus */
};



#define _VIDEO_CONVERTER_N_YDRIVER ((256 * __SIZEOF_VIDEO_PIXEL_T__) / __SIZEOF_POINTER__)
#if _VIDEO_CONVERTER_N_YDRIVER < 5
#undef _VIDEO_CONVERTER_N_YDRIVER
#define _VIDEO_CONVERTER_N_YDRIVER 5
#endif /* _VIDEO_CONVERTER_N_YDRIVER < 5 */
#define _VIDEO_CONVERTER_N_XDRIVER (_VIDEO_CONVERTER_N_YDRIVER - 4)

/* Helper structure for directly converting from 1 pixel format to another.  */
struct video_converter;
struct video_converter {
	/* [1..1] Map pixel from `vcv_from' into the format used by `vcv_to'.
	 * Same as the following (but faster in many cases):
	 * >> video_color_t color = vcv_from.pixel2color(__from_pixel);
	 * >> video_pixel_t to_pixel = vcv_to.color2pixel(color); */
	__ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_IN_T(1) video_pixel_t
	(LIBVIDEO_CODEC_CC *vcv_mappixel)(struct video_converter const *__restrict __self,
	                                  video_pixel_t __from_pixel);
	union {
		struct {
			struct video_format vcv_from; /* [OVERRIDE(.vf_pal, [NOT(REF)])] Source video format (may be invalid after init) */
			struct video_format vcv_to;   /* [OVERRIDE(.vf_pal, [NOT(REF)])] Target video format (may be invalid after init) */
			void *_vcv_xdriver[_VIDEO_CONVERTER_N_XDRIVER]; /* Driver-specific data */
		};
		void *_vcv_ydriver[_VIDEO_CONVERTER_N_YDRIVER]; /* Driver-specific data */
	};
};


#ifdef __INTELLISENSE__
/* Initialize a video pixel format converter */
extern __ATTR_RETNONNULL __ATTR_NONNULL((1, 2, 3, 4, 5)) struct video_converter *
video_converter_init_ex(struct video_converter *__restrict __self,
                        struct video_codec const *__from_codec, struct video_palette *__from_pal,
                        struct video_codec const *__to_codec, struct video_palette *__to_pal);
extern __ATTR_RETNONNULL __ATTR_NONNULL((1, 2, 3)) struct video_converter *
video_converter_init(struct video_converter *__restrict __self,
                     struct video_format const *__from_format,
                     struct video_format const *__to_format);

/* Map a given `__from_pixel' (as read from a GFX using `__self->vcv_from')
 * into  the pixel format described by `__self->vcv_to', and return the new
 * pixel. */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_pixel_t
video_converter_mappixel(struct video_converter const *__restrict __self,
                         video_pixel_t __from_pixel);
#else /* __INTELLISENSE__ */
#define video_converter_init_ex(self, from_codec, from_pal, to_codec, to_pal) \
	((self)->vcv_to.vf_pal = (to_pal), (self)->vcv_to.vf_codec = (to_codec),  \
	 (self)->vcv_from.vf_pal = (from_pal),                                    \
	 (*((self)->vcv_from.vf_codec = (from_codec))->vc_initconverter)(self))
#define video_converter_init(self, from_format, to_format)                        \
	video_converter_init_ex(self, (from_format)->vf_codec, (from_format)->vf_pal, \
	                        (to_format)->vf_codec, (to_format)->vf_pal)
#define video_converter_mappixel(self, from_pixel) \
	(*(self)->vcv_mappixel)(self, from_pixel)
#endif /* !__INTELLISENSE__ */


#endif /* __CC__ */


__DECL_END

#endif /* !_LIBVIDEO_CODEC_FORMAT_H */
