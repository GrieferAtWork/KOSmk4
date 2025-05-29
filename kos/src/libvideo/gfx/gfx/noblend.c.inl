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

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <stddef.h>
#include <stdint.h>

#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/codec/format.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/buffer.h>

#ifdef __INTELLISENSE__
#include "../gfx.c"
#endif /* __INTELLISENSE__ */

DECL_BEGIN

/* Low-level, optimized GFX functions using `struct video_lock' (if available):
 * - *noblend*: Usable only when the relevant GFX's blend-mode is `GFX_BLENDINFO_OVERRIDE' */
INTERN NONNULL((1)) void CC
libvideo_gfx_noblend__absline_llhh(struct video_gfx *__restrict self,
                                   video_coord_t x, video_coord_t y,
                                   video_dim_t size_x, video_dim_t size_y,
                                   video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	if likely(buffer->wlock(lock) == 0) {
		video_dim_t step;
		byte_t *line = lock.vl_data + y * lock.vl_stride;
		video_pixel_t pixel = buffer->vb_format.color2pixel(color);
		assert(size_x > 0);
		assert(size_y > 0);
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
				(*vc_linefill)(line, x + step, pixel, row_length);
				step = row_end_step;
				line += lock.vl_stride;
			} while (step != size_x);
		} else {
			void (LIBVIDEO_CODEC_CC *vc_setpixel)(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
			vc_setpixel = buffer->vb_format.vf_codec->vc_setpixel;
			if (size_x < size_y) {
				do {
					(*vc_setpixel)(line, x + (video_dim_t)(((uint64_t)size_x * step) / size_y), pixel);
					line += lock.vl_stride;
				} while (++step != size_y);
			} else {
				do {
					(*vc_setpixel)(line, x + step, pixel);
					line += lock.vl_stride;
				} while (++step != size_y);
			}
		}
		buffer->unlock(lock);
		return;
	}
	libvideo_gfx_generic__absline_llhh(self, x, y, size_x, size_y, color);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_noblend__absline_lhhl(struct video_gfx *__restrict self,
                                   video_coord_t x, video_coord_t y,
                                   video_dim_t size_x, video_dim_t size_y,
                                   video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	if likely(buffer->wlock(lock) == 0) {
		video_dim_t step;
		byte_t *line = lock.vl_data + y * lock.vl_stride;
		video_pixel_t pixel = buffer->vb_format.color2pixel(color);
		assert(size_x > 0);
		assert(size_y > 0);
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
				(*vc_linefill)(line, x + step, pixel, row_length);
				step = row_end_step;
				line -= lock.vl_stride;
			} while (step != size_x);
		} else {
			void (LIBVIDEO_CODEC_CC *vc_setpixel)(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
			vc_setpixel = buffer->vb_format.vf_codec->vc_setpixel;
			if (size_x < size_y) {
				do {
					(*vc_setpixel)(line, x + (video_dim_t)(((uint64_t)size_x * step) / size_y), pixel);
					line -= lock.vl_stride;
				} while (++step != size_y);
			} else {
				do {
					(*vc_setpixel)(line, x + step, pixel);
					line -= lock.vl_stride;
				} while (++step != size_y);
			}
		}
		buffer->unlock(lock);
		return;
	}
	libvideo_gfx_generic__absline_lhhl(self, x, y, size_x, size_y, color);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_noblend__absline_h(struct video_gfx *__restrict self,
                                video_coord_t x, video_coord_t y,
                                video_dim_t length, video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	if likely(buffer->wlock(lock) == 0) {
		byte_t *line = lock.vl_data + y * lock.vl_stride;
		video_pixel_t pixel = buffer->vb_format.color2pixel(color);
		buffer->vb_format.linefill(line, x, pixel, length);
		buffer->unlock(lock);
		return;
	}
	libvideo_gfx_generic__absline_h(self, x, y, length, color);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_noblend__absline_v(struct video_gfx *__restrict self,
                                video_coord_t x, video_coord_t y,
                                video_dim_t length, video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	if likely(buffer->wlock(lock) == 0) {
		byte_t *line = lock.vl_data + y * lock.vl_stride;
		video_pixel_t pixel = buffer->vb_format.color2pixel(color);
		void (LIBVIDEO_CODEC_CC *vc_setpixel)(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
		vc_setpixel = buffer->vb_format.vf_codec->vc_setpixel;
		do {
			(*vc_setpixel)(line, x, pixel);
			--length;
			line += lock.vl_stride;
		} while (length);
		buffer->unlock(lock);
		return;
	}
	libvideo_gfx_generic__absline_v(self, x, y, length, color);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_noblend__absfill(struct video_gfx *__restrict self,
                              video_coord_t dst_x, video_coord_t dst_y,
                              video_dim_t size_x, video_dim_t size_y,
                              video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	if likely(buffer->wlock(lock) == 0) {
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		video_pixel_t pixel = buffer->vb_format.color2pixel(color);
		void (LIBVIDEO_CODEC_CC *vc_linefill)(byte_t *__restrict line, video_coord_t dst_x,
		                                      video_pixel_t pixel, video_dim_t num_pixels);
		vc_linefill = buffer->vb_format.vf_codec->vc_linefill;
		assert(size_x > 0);
		assert(size_y > 0);
		do {
			(*vc_linefill)(line, dst_x, pixel, size_x);
			line += lock.vl_stride;
			--size_y;
		} while (size_y);
		buffer->unlock(lock);
		return;
	}
	libvideo_gfx_generic__absfill(self, dst_x, dst_y, size_x, size_y, color);
}

INTERN NONNULL((1, 7)) void CC
libvideo_gfx_noblend__bitfill(struct video_gfx *__restrict self,
                              video_coord_t dst_x, video_coord_t dst_y,
                              video_dim_t size_x, video_dim_t size_y,
                              video_color_t color,
                              void const *__restrict bitmask,
                              uintptr_t bitskip, size_t bitscan) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	if likely(buffer->wlock(lock) == 0) {
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		video_pixel_t pixel = buffer->vb_format.color2pixel(color);
		void (LIBVIDEO_CODEC_CC *vc_linefill)(byte_t *__restrict line, video_coord_t dst_x,
		                                      video_pixel_t pixel, video_dim_t num_pixels);
		vc_linefill = buffer->vb_format.vf_codec->vc_linefill;
		assert(size_x > 0);
		assert(size_y > 0);
		do {
			video_dim_t x = 0;
			uintptr_t row_bitskip = bitskip;
			byte_t const *row = (byte_t const *)bitmask;
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
			bitskip += bitscan;
			line += lock.vl_stride;
			--size_y;
		} while (size_y);
		buffer->unlock(lock);
		return;
	}
	libvideo_gfx_generic__bitfill(self, dst_x, dst_y, size_x, size_y, color, bitmask, bitskip, bitscan);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_noblend_samefmt__blit(struct video_blit *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_coord_t src_x, video_coord_t src_y,
                                   video_dim_t size_x, video_dim_t size_y) {
	struct video_lock dst_lock;
	struct video_buffer *dst_buffer = self->vb_dst->vx_buffer;
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
				--size_y;
				dst_line += dst_lock.vl_stride;
				src_line += src_lock.vl_stride;
			} while (size_y);
			src_buffer->unlock(src_lock);
			dst_buffer->unlock(dst_lock);
			return;
		}
		dst_buffer->unlock(dst_lock);
	}
	libvideo_gfx_generic__blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
}

INTERN NONNULL((1, 8)) void CC
libvideo_gfx_noblend_samefmt__bitblit(struct video_blit *__restrict self,
                                      video_coord_t dst_x, video_coord_t dst_y,
                                      video_coord_t src_x, video_coord_t src_y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      void const *__restrict bitmask,
                                      uintptr_t bitskip, size_t bitscan) {
	struct video_lock dst_lock;
	struct video_buffer *dst_buffer = self->vb_dst->vx_buffer;
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
				video_dim_t x = 0;
				uintptr_t row_bitskip = bitskip;
				byte_t const *row = (byte_t const *)bitmask;
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
				bitskip += bitscan;
				dst_line += dst_lock.vl_stride;
				src_line += src_lock.vl_stride;
				--size_y;
			} while (size_y);
			src_buffer->unlock(src_lock);
			dst_buffer->unlock(dst_lock);
			return;
		}
		dst_buffer->unlock(dst_lock);
	}
	libvideo_gfx_generic__bitblit(self, dst_x, dst_y, src_x, src_y,
	                              size_x, size_y, bitmask, bitskip, bitscan);
}

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_noblend__stretch_l
#include "noblend-stretch.c.inl"
#define DEFINE_noblend__stretch_n
#include "noblend-stretch.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBVIDEO_GFX_GFX_NOBLEND_C_INL */
