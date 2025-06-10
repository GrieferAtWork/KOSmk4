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
#ifndef GUARD_LIBVIDEO_GFX_GFX_NOBLEND_C_INL
#define GUARD_LIBVIDEO_GFX_GFX_NOBLEND_C_INL 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/param.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#include <libvideo/codec/api.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "../gfx.h"

DECL_BEGIN

#ifndef PRIdOFF
#define PRIdOFF PRIdN(__SIZEOF_VIDEO_OFFSET_T__)
#define PRIxOFF PRIxN(__SIZEOF_VIDEO_OFFSET_T__)
#define PRIuCRD PRIuN(__SIZEOF_VIDEO_COORD_T__)
#define PRIxCRD PRIxN(__SIZEOF_VIDEO_COORD_T__)
#define PRIuDIM PRIuN(__SIZEOF_VIDEO_DIM_T__)
#define PRIxDIM PRIxN(__SIZEOF_VIDEO_DIM_T__)
#define PRIxCOL PRIxN(__SIZEOF_VIDEO_COLOR_T__)
#endif /* !PRIdOFF */

#define video_gfx_getabscolor(self, abs_x, abs_y) \
	(*(self)->vx_xops.vgxo_getcolor)(self, abs_x, abs_y)
#define video_gfx_putabscolor(self, abs_x, abs_y, color) \
	(*(self)->vx_xops.vgxo_putcolor)(self, abs_x, abs_y, color)

#define video_gfx_getabspixel(self, abs_x, abs_y) \
	(*(self)->vx_xops.vgxo_getpixel)(self, abs_x, abs_y)
#define video_gfx_setabspixel(self, abs_x, abs_y, pixel) \
	(*(self)->vx_xops.vgxo_setpixel)(self, abs_x, abs_y, pixel)


/* Low-level, optimized GFX functions using `struct video_lock' (if available):
 * - *noblend*: Usable only when the relevant GFX's blend-mode is `GFX_BLENDMODE_OVERRIDE' */

PRIVATE ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_llhh__bypixel(struct video_gfx const *__restrict self,
                                            video_coord_t dst_x, video_coord_t dst_y,
                                            video_dim_t size_x, video_dim_t size_y,
                                            video_pixel_t pixel) {
	video_dim_t step;
	step = 0;
	if (size_x > size_y) {
		do {
			video_gfx_setabspixel(self,
			                      dst_x + step,
			                      dst_y + (video_dim_t)(((uint64_t)size_y * step) / size_x),
			                      pixel);
		} while (++step != size_x);
	} else if (size_x < size_y) {
		do {
			video_gfx_setabspixel(self,
			                      dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y),
			                      dst_y + step,
			                      pixel);
		} while (++step != size_y);
	} else {
		do {
			video_gfx_setabspixel(self,
			                      dst_x + step,
			                      dst_y + step,
			                      pixel);
		} while (++step != size_x);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_llhh(struct video_gfx const *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_dim_t size_x, video_dim_t size_y,
                                   video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_pixel_t pixel = buffer->vb_format.color2pixel(color);
	assert(size_x > 0);
	assert(size_y > 0);
	if likely(buffer->wlock(lock) == 0) {
		video_dim_t step;
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		step = 0;
		if (size_x > size_y) {
			void (LIBVIDEO_CODEC_CC *vc_linefill)(byte_t *__restrict line, video_coord_t dst_x,
			                                      video_pixel_t pixel, video_dim_t num_pixels);
			vc_linefill = buffer->vb_format.vf_codec->vc_linefill;
			do {
				video_dim_t row = (video_dim_t)(((uint64_t)size_y * step) / size_x);
				video_dim_t row_end_step, row_length;
				row_end_step = step + 1;
				while (row == (video_dim_t)(((uint64_t)size_y * row_end_step) / size_x) &&
				       row_end_step != size_x)
					++row_end_step;
				row_length = row_end_step - row;
				(*vc_linefill)(line, dst_x + step, pixel, row_length);
				step = row_end_step;
				line += lock.vl_stride;
			} while (step != size_x);
		} else {
			void (LIBVIDEO_CODEC_CC *vc_setpixel)(byte_t *__restrict line, video_coord_t dst_x, video_pixel_t pixel);
			vc_setpixel = buffer->vb_format.vf_codec->vc_setpixel;
			if (size_x < size_y) {
				do {
					(*vc_setpixel)(line, dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y), pixel);
					line += lock.vl_stride;
				} while (++step != size_y);
			} else {
				do {
					(*vc_setpixel)(line, dst_x + step, pixel);
					line += lock.vl_stride;
				} while (++step != size_y);
			}
		}
		buffer->unlock(lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_gfx_noblend__absline_llhh__bypixel(self, dst_x, dst_y, size_x, size_y, pixel);
	}
}

PRIVATE ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_lhhl__bypixel(struct video_gfx const *__restrict self,
                                            video_coord_t dst_x, video_coord_t dst_y,
                                            video_dim_t size_x, video_dim_t size_y,
                                            video_pixel_t pixel) {
	video_dim_t step;
	step = 0;
	if (size_x > size_y) {
		do {
			video_gfx_setabspixel(self,
			                      dst_x + step,
			                      dst_y - (video_dim_t)(((uint64_t)size_y * step) / size_x),
			                      pixel);
		} while (++step != size_x);
	} else if (size_x < size_y) {
		do {
			video_gfx_setabspixel(self,
			                      dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y),
			                      dst_y - step,
			                      pixel);
		} while (++step != size_y);
	} else {
		do {
			video_gfx_setabspixel(self,
			                      dst_x + step,
			                      dst_y - step,
			                      pixel);
		} while (++step != size_x);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_lhhl(struct video_gfx const *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_dim_t size_x, video_dim_t size_y,
                                   video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_pixel_t pixel = buffer->vb_format.color2pixel(color);
	assert(size_x > 0);
	assert(size_y > 0);
	if likely(buffer->wlock(lock) == 0) {
		video_dim_t step;
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		step = 0;
		if (size_x > size_y) {
			void (LIBVIDEO_CODEC_CC *vc_linefill)(byte_t *__restrict line, video_coord_t dst_x,
			                                      video_pixel_t pixel, video_dim_t num_pixels);
			vc_linefill = buffer->vb_format.vf_codec->vc_linefill;
			do {
				video_dim_t row = (video_dim_t)(((uint64_t)size_y * step) / size_x);
				video_dim_t row_end_step, row_length;
				row_end_step = step + 1;
				while (row == (video_dim_t)(((uint64_t)size_y * row_end_step) / size_x) &&
				       row_end_step != size_x)
					++row_end_step;
				row_length = row_end_step - row;
				(*vc_linefill)(line, dst_x + step, pixel, row_length);
				step = row_end_step;
				line -= lock.vl_stride;
			} while (step != size_x);
		} else {
			void (LIBVIDEO_CODEC_CC *vc_setpixel)(byte_t *__restrict line, video_coord_t dst_x, video_pixel_t pixel);
			vc_setpixel = buffer->vb_format.vf_codec->vc_setpixel;
			if (size_x < size_y) {
				do {
					(*vc_setpixel)(line, dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y), pixel);
					line -= lock.vl_stride;
				} while (++step != size_y);
			} else {
				do {
					(*vc_setpixel)(line, dst_x + step, pixel);
					line -= lock.vl_stride;
				} while (++step != size_y);
			}
		}
		buffer->unlock(lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_gfx_noblend__absline_lhhl__bypixel(self, dst_x, dst_y, size_x, size_y, pixel);
	}
}


PRIVATE ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_h__bypixel(struct video_gfx const *__restrict self,
                                         video_coord_t dst_x, video_coord_t dst_y,
                                         video_dim_t length, video_pixel_t pixel) {
	video_coord_t x = 0;
	do {
		video_gfx_setabspixel(self, dst_x + x, dst_y, pixel);
	} while (++x < length);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_h(struct video_gfx const *__restrict self,
                                video_coord_t dst_x, video_coord_t dst_y,
                                video_dim_t length, video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_pixel_t pixel = buffer->vb_format.color2pixel(color);
	if likely(buffer->wlock(lock) == 0) {
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		buffer->vb_format.linefill(line, dst_x, pixel, length);
		buffer->unlock(lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_gfx_noblend__absline_h__bypixel(self, dst_x, dst_y, length, pixel);
	}
}

PRIVATE ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_v__bypixel(struct video_gfx const *__restrict self,
                                         video_coord_t dst_x, video_coord_t dst_y,
                                         video_dim_t length, video_pixel_t pixel) {
	video_coord_t y = 0;
	do {
		video_gfx_setabspixel(self, dst_x, dst_y + y, pixel);
	} while (++y < length);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_v(struct video_gfx const *__restrict self,
                                video_coord_t dst_x, video_coord_t dst_y,
                                video_dim_t length, video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_pixel_t pixel = buffer->vb_format.color2pixel(color);
	if likely(buffer->wlock(lock) == 0) {
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		void (LIBVIDEO_CODEC_CC *vc_setpixel)(byte_t *__restrict line,
		                                      video_coord_t dst_x,
		                                      video_pixel_t pixel);
		vc_setpixel = buffer->vb_format.vf_codec->vc_setpixel;
		do {
			(*vc_setpixel)(line, dst_x, pixel);
			--length;
			line += lock.vl_stride;
		} while (length);
		buffer->unlock(lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_gfx_noblend__absline_v__bypixel(self, dst_x, dst_y, length, pixel);
	}
}

PRIVATE ATTR_IN(1) void CC
libvideo_gfx_noblend__absfill__bypixel(struct video_gfx const *__restrict self,
                                       video_coord_t dst_x, video_coord_t dst_y,
                                       video_dim_t size_x, video_dim_t size_y,
                                       video_pixel_t pixel) {
	video_coord_t y = 0;
	do {
		video_coord_t x = 0;
		do {
			(*self->vx_xops.vgxo_setpixel)(self, dst_x + x, dst_y + y, pixel);
		} while (++x < size_x);
	} while (++y < size_y);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend__absfill(struct video_gfx const *__restrict self,
                              video_coord_t dst_x, video_coord_t dst_y,
                              video_dim_t size_x, video_dim_t size_y,
                              video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_pixel_t pixel = buffer->vb_format.color2pixel(color);
	if likely(buffer->wlock(lock) == 0) {
		/* Use the low-level linefill operator from the video codec */
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		void (LIBVIDEO_CODEC_CC *vc_linefill)(byte_t *__restrict line, video_coord_t dst_x,
		                                      video_pixel_t pixel, video_dim_t num_pixels);
		vc_linefill = buffer->vb_format.vf_codec->vc_linefill;
		assert(size_x > 0);
		assert(size_y > 0);
		do {
			(*vc_linefill)(line, dst_x, pixel, size_x);
			line += lock.vl_stride;
		} while (--size_y);
		buffer->unlock(lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_gfx_noblend__absfill__bypixel(self, dst_x, dst_y, size_x, size_y, pixel);
	}
}


PRIVATE ATTR_IN(1) ATTR_IN(7) void CC
libvideo_gfx_noblend__bitfill__bypixel(struct video_gfx const *__restrict self,
                                       video_coord_t dst_x, video_coord_t dst_y,
                                       video_dim_t size_x, video_dim_t size_y,
                                       video_pixel_t pixel,
                                       struct video_bitmask const *__restrict bm) {
	uintptr_t bitskip = bm->vbm_skip;
	do {
		video_dim_t x = 0;
		uintptr_t row_bitskip = bitskip;
		byte_t const *row = (byte_t const *)bm->vbm_mask;
		do {
			video_dim_t count;
			byte_t byte;
			shift_t bits;
			if (row_bitskip >= NBBY) {
				row += row_bitskip / NBBY;
				row_bitskip %= NBBY;
			}
			byte = *row;
			bits = NBBY - row_bitskip;

			/* Skip over 0-bits */
			for (;;) {
				--bits;
				++row_bitskip;
				if (byte & ((byte_t)1 << bits))
					break;
				++x;
				if (x >= size_x)
					goto next_row;
				if (!bits) {
					++row;
					row_bitskip = 0;
					bits = NBBY;
				}
			}

			/* Count consecutive 1-bits */
			count = 1;
			while ((x + count) < size_x) {
				if (!bits) {
					++row;
					row_bitskip = 0;
					bits = NBBY;
				}
				--bits;
				if (!(byte & ((byte_t)1 << bits)))
					break;
				++row_bitskip;
				++count;
			}

			do {
				(*self->vx_xops.vgxo_setpixel)(self, dst_x + x, dst_y, pixel);
				++x;
			} while (--count);
		} while (x < size_x);
next_row:
		bitskip += bm->vbm_scan;
		++dst_y;
	} while (--size_y);
}

INTERN ATTR_IN(1) ATTR_IN(7) void CC
libvideo_gfx_noblend__bitfill(struct video_gfx const *__restrict self,
                              video_coord_t dst_x, video_coord_t dst_y,
                              video_dim_t size_x, video_dim_t size_y,
                              video_color_t color,
                              struct video_bitmask const *__restrict bm) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_pixel_t pixel = buffer->vb_format.color2pixel(color);
	TRACE_START("noblend__bitfill("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", bm: %p)\n",
	            dst_x, dst_y, size_x, size_y, color, bm);
	if likely(buffer->wlock(lock) == 0) {
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		void (LIBVIDEO_CODEC_CC *vc_linefill)(byte_t *__restrict line, video_coord_t dst_x,
		                                      video_pixel_t pixel, video_dim_t num_pixels);
		uintptr_t bitskip = bm->vbm_skip;
		vc_linefill = buffer->vb_format.vf_codec->vc_linefill;
		assert(size_x > 0);
		assert(size_y > 0);
		do {
			video_dim_t x = 0;
			uintptr_t row_bitskip = bitskip;
			byte_t const *row = (byte_t const *)bm->vbm_mask;
			do {
				video_dim_t count;
				byte_t byte;
				shift_t bits;
				if (row_bitskip >= NBBY) {
					row += row_bitskip / NBBY;
					row_bitskip %= NBBY;
				}
				byte = *row;
				bits = NBBY - row_bitskip;

				/* Skip over 0-bits */
				for (;;) {
					--bits;
					++row_bitskip;
					if (byte & ((byte_t)1 << bits))
						break;
					++x;
					if (x >= size_x)
						goto next_row;
					if (!bits) {
						++row;
						row_bitskip = 0;
						bits = NBBY;
					}
				}

				/* Count consecutive 1-bits */
				count = 1;
				while ((x + count) < size_x) {
					if (!bits) {
						++row;
						row_bitskip = 0;
						bits = NBBY;
					}
					--bits;
					if (!(byte & ((byte_t)1 << bits)))
						break;
					++row_bitskip;
					++count;
				}
				(*vc_linefill)(line, dst_x + x, pixel, count);
				x += count;
			} while (x < size_x);
next_row:
			bitskip += bm->vbm_scan;
			line += lock.vl_stride;
		} while (--size_y);
		buffer->unlock(lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_gfx_noblend__bitfill__bypixel(self, dst_x, dst_y, size_x, size_y, pixel, bm);
	}
	TRACE_END("noblend__bitfill()\n");
}

PRIVATE ATTR_IN(1) void CC
libvideo_gfx_noblend_samefmt__blit__bypixel(struct video_blit const *__restrict self,
                                            video_coord_t dst_x, video_coord_t dst_y,
                                            video_coord_t src_x, video_coord_t src_y,
                                            video_dim_t size_x, video_dim_t size_y) {
	video_dim_t x, y;
	struct video_gfx const *src = self->vb_src;
	struct video_gfx const *dst = self->vb_dst;
	for (y = 0; y < size_y; ++y) {
		for (x = 0; x < size_x; ++x) {
			video_pixel_t pixel;
			pixel = video_gfx_getabspixel(src, src_x + x, src_y + y);
			video_gfx_setabspixel(dst, dst_x + x, dst_y + y, pixel);
		}
	}
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend_samefmt__blit(struct video_blit const *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_coord_t src_x, video_coord_t src_y,
                                   video_dim_t size_x, video_dim_t size_y) {
	struct video_lock dst_lock;
	struct video_buffer *dst_buffer = self->vb_dst->vx_buffer;
	TRACE_START("noblend_samefmt__blit("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x, dst_y, src_x, src_y, size_x, size_y);
	if likely(dst_buffer->wlock(dst_lock) == 0) {
		struct video_lock src_lock;
		struct video_buffer *src_buffer = self->vb_src->vx_buffer;
		if likely(src_buffer->rlock(src_lock) == 0) {
			byte_t *dst_line = dst_lock.vl_data + dst_y * dst_lock.vl_stride;
			byte_t const *src_line = src_lock.vl_data + src_y * src_lock.vl_stride;
			void (LIBVIDEO_CODEC_CC *vc_linecopy)(byte_t *__restrict dst_line, video_coord_t dst_x,
			                                      byte_t const *__restrict src_line, video_coord_t src_x,
			                                      video_dim_t num_pixels);
			vc_linecopy = dst_buffer->vb_format.vf_codec->vc_linecopy;
			do {
				(*vc_linecopy)(dst_line, dst_x, src_line, src_x, size_x);
				dst_line += dst_lock.vl_stride;
				src_line += src_lock.vl_stride;
			} while (--size_y);
			src_buffer->unlock(src_lock);
			dst_buffer->unlock(dst_lock);
			goto done;
		}
		dst_buffer->unlock(dst_lock);
	}
	/* Use pixel-based rendering */
	libvideo_gfx_noblend_samefmt__blit__bypixel(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
done:
	TRACE_END("noblend_samefmt__blit()\n");
}

INTERN ATTR_IN(1) ATTR_IN(8) void CC
libvideo_gfx_noblend_samefmt__bitblit(struct video_blit const *__restrict self,
                                      video_coord_t dst_x, video_coord_t dst_y,
                                      video_coord_t src_x, video_coord_t src_y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      struct video_bitmask const *__restrict bm) {
	struct video_lock dst_lock;
	struct video_buffer *dst_buffer = self->vb_dst->vx_buffer;
	TRACE_START("noblend_samefmt__bitblit("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "}, bm: %p)\n",
	            dst_x, dst_y, src_x, src_y, size_x, size_y, bm);
	if likely(dst_buffer->wlock(dst_lock) == 0) {
		struct video_lock src_lock;
		struct video_buffer *src_buffer = self->vb_src->vx_buffer;
		if likely(src_buffer->rlock(src_lock) == 0) {
			uintptr_t bitskip = bm->vbm_skip + src_x + src_y * bm->vbm_scan;
			byte_t *dst_line = dst_lock.vl_data + dst_y * dst_lock.vl_stride;
			byte_t const *src_line = src_lock.vl_data + src_y * src_lock.vl_stride;
			void (LIBVIDEO_CODEC_CC *vc_linecopy)(byte_t *__restrict dst_line, video_coord_t dst_x,
			                                      byte_t const *__restrict src_line, video_coord_t src_x,
			                                      video_dim_t num_pixels);
			vc_linecopy = dst_buffer->vb_format.vf_codec->vc_linecopy;
			do {
				video_dim_t x = 0;
				uintptr_t row_bitskip = bitskip;
				byte_t const *row = (byte_t const *)bm->vbm_mask;
				do {
					video_dim_t count;
					byte_t byte;
					shift_t bits;
					if (row_bitskip >= NBBY) {
						row += row_bitskip / NBBY;
						row_bitskip %= NBBY;
					}
					byte = *row;
					bits = NBBY - row_bitskip;

					/* Skip over 0-bits */
					for (;;) {
						--bits;
						++row_bitskip;
						if (byte & ((byte_t)1 << bits))
							break;
						++x;
						if (x >= size_x)
							goto next_row;
						if (!bits) {
							++row;
							row_bitskip = 0;
							bits = NBBY;
						}
					}

					/* Count consecutive 1-bits */
					count = 1;
					while ((x + count) < size_x) {
						if (!bits) {
							++row;
							row_bitskip = 0;
							bits = NBBY;
						}
						--bits;
						if (!(byte & ((byte_t)1 << bits)))
							break;
						++row_bitskip;
						++count;
					}
					(*vc_linecopy)(dst_line, dst_x + x, src_line, src_x + x, count);
					x += count;
				} while (x < size_x);
next_row:
				bitskip += bm->vbm_scan;
				dst_line += dst_lock.vl_stride;
				src_line += src_lock.vl_stride;
			} while (--size_y);
			src_buffer->unlock(src_lock);
			dst_buffer->unlock(dst_lock);
			goto done;
		}
		dst_buffer->unlock(dst_lock);
	}
	libvideo_gfx_generic__bitblit(self, dst_x, dst_y, src_x, src_y,
	                              size_x, size_y, bm);
done:
	TRACE_END("noblend_samefmt__bitblit()\n");
}



INTERN ATTR_IN(1) ATTR_IN(9) void CC
libvideo_gfx_noblend__bitstretchfill_n(struct video_gfx const *__restrict self,
                                       video_coord_t dst_x, video_coord_t dst_y,
                                       video_dim_t dst_size_x, video_dim_t dst_size_y,
                                       video_color_t color,
                                       video_dim_t src_size_x, video_dim_t src_size_y,
                                       struct video_bitmask const *__restrict bm) {
	/* TODO */
	libvideo_gfx_generic__bitstretchfill_n(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                       color, src_size_x, src_size_y, bm);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend_samefmt__stretch_n(struct video_blit const *__restrict self,
                                        video_coord_t dst_x, video_coord_t dst_y,
                                        video_dim_t dst_size_x, video_dim_t dst_size_y,
                                        video_coord_t src_x, video_coord_t src_y,
                                        video_dim_t src_size_x, video_dim_t src_size_y) {
	/* TODO */
	libvideo_gfx_generic__stretch_n(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                src_x, src_y, src_size_x, src_size_y);
}

INTERN ATTR_IN(1) ATTR_IN(10) void CC
libvideo_gfx_noblend_samefmt__bitstretch_n(struct video_blit const *__restrict self,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_dim_t dst_size_x, video_dim_t dst_size_y,
                                           video_coord_t src_x, video_coord_t src_y,
                                           video_dim_t src_size_x, video_dim_t src_size_y,
                                           struct video_bitmask const *__restrict bm) {
	/* TODO */
	libvideo_gfx_generic__bitstretch_n(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                   src_x, src_y, src_size_x, src_size_y, bm);
}

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_libvideo_gfx_noblend__blitfrom_n
#include "noblend-blitfrom.c.inl"
#define DEFINE_libvideo_gfx_noblend__blitfrom_l
#include "noblend-blitfrom.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBVIDEO_GFX_GFX_NOBLEND_C_INL */
