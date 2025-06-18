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

#include <hybrid/bit.h>
#include <hybrid/unaligned.h>

#include <kos/types.h>
#include <sys/param.h>

#include <stdint.h>

#include <libvideo/codec/api.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "../gfx.h"

DECL_BEGIN

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
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y + (video_dim_t)(((uint64_t)size_y * step) / size_x);
			video_gfx_x_setpixel(self, line_x, line_y, pixel);
		} while (++step != size_x);
	} else if (size_x < size_y) {
		do {
			video_coord_t line_x = dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y);
			video_coord_t line_y = dst_y + step;
			video_gfx_x_setpixel(self, line_x, line_y, pixel);
		} while (++step != size_y);
	} else {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y + step;
			video_gfx_x_setpixel(self, line_x, line_y, pixel);
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
	gfx_assert(size_x > 0);
	gfx_assert(size_y > 0);
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
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y - (video_dim_t)(((uint64_t)size_y * step) / size_x);
			video_gfx_x_setpixel(self, line_x, line_y, pixel);
		} while (++step != size_x);
	} else if (size_x < size_y) {
		do {
			video_coord_t line_x = dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y);
			video_coord_t line_y = dst_y - step;
			video_gfx_x_setpixel(self, line_x, line_y, pixel);
		} while (++step != size_y);
	} else {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y - step;
			video_gfx_x_setpixel(self, line_x, line_y, pixel);
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
	gfx_assert(size_x > 0);
	gfx_assert(size_y > 0);
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
	do {
		video_gfx_x_setpixel(self, dst_x, dst_y, pixel);
		++dst_x;
	} while (--length);
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
	do {
		video_gfx_x_setpixel(self, dst_x, dst_y, pixel);
		++dst_y;
	} while (--length);
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
			line += lock.vl_stride;
		} while (--length);
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
	do {
		video_coord_t x = 0;
		do {
			video_gfx_x_setpixel(self, dst_x + x, dst_y, pixel);
		} while (++x < size_x);
		++dst_y;
	} while (--size_y);
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
		gfx_assert(size_x > 0);
		gfx_assert(size_y > 0);
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
	byte_t const *bitmask = (byte_t const *)bm->vbm_mask;
	bitmask += bitskip / NBBY;
	bitskip = bitskip % NBBY;
	do {
		video_dim_t x;
		uintptr_t row_bitskip;
		byte_t const *row;
		byte_t byte;
		shift_t bits;
		row_bitskip = bitskip;
		row = bitmask;
		byte = *row;
		bits = NBBY - row_bitskip;
		for (x = 0;;) {
			--bits;
			++row_bitskip;
			if (byte & ((byte_t)1 << bits))
				video_gfx_x_setpixel(self, dst_x + x, dst_y, pixel);
			++x;
			if (x >= size_x)
				break;
			if (!bits) {
				byte = *++row;
				row_bitskip = 0;
				bits = NBBY;
			}
		}
		bitskip += bm->vbm_scan;
		bitmask += bitskip / NBBY;
		bitskip = bitskip % NBBY;
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
	            "color: %#" PRIxCOL ", bm: %p+%" PRIuPTR "\n",
	            dst_x, dst_y, size_x, size_y, color,
	            bm->vbm_mask, bm->vbm_skip);
	if likely(buffer->wlock(lock) == 0) {
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		void (LIBVIDEO_CODEC_CC *vc_linefill)(byte_t *__restrict line, video_coord_t dst_x,
		                                      video_pixel_t pixel, video_dim_t num_pixels);
		uintptr_t bitskip = bm->vbm_skip;
		byte_t const *bitmask = (byte_t const *)bm->vbm_mask;
		bitmask += bitskip / NBBY;
		bitskip = bitskip % NBBY;
		vc_linefill = buffer->vb_format.vf_codec->vc_linefill;
		gfx_assert(size_x > 0);
		gfx_assert(size_y > 0);
#ifndef __OPTIMIZE_SIZE__
		if likely(bitskip == 0 && !(bm->vbm_scan & 7)) {
			size_t bm_scanline = bm->vbm_scan >> 3;
			switch (size_x) {
#define DO_FIXED_WORD_RENDER(N)                                   \
				do {                                              \
					video_dim_t x = dst_x;                        \
					uint##N##_t word = UNALIGNED_GET##N(bitmask); \
					while (word) {                                \
						shift_t bits;                             \
						bits = CLZ((uint##N##_t)word);            \
						x += bits;                                \
						word <<= bits;                            \
						bits = CLZ((uint##N##_t)~word);           \
						gfx_assert(bits > 0);                     \
						(*vc_linefill)(line, x, pixel, bits);     \
						x += bits;                                \
						word <<= bits;                            \
					}                                             \
					line += lock.vl_stride;                       \
					bitmask += bm_scanline;                       \
				} while (--size_y)
			case 0 ... 8:
				DO_FIXED_WORD_RENDER(8);
				goto done;
			case 9 ... 16:
				DO_FIXED_WORD_RENDER(16);
				goto done;
			case 17 ... 32:
				DO_FIXED_WORD_RENDER(32);
				goto done;
#if __SIZEOF_REGISTER__ >= 8
			case 33 ... 64:
				DO_FIXED_WORD_RENDER(64);
				goto done;
#endif /* __SIZEOF_REGISTER__ >= 8 */
			default: break;
#undef DO_FIXED_WORD_RENDER
			}
		}
#endif /* !__OPTIMIZE_SIZE__ */
		do {
			video_dim_t x;
			uintptr_t row_bitskip;
			byte_t const *row;
			x = 0;
			row_bitskip = bitskip;
			row = bitmask;
			do {
				video_dim_t count;
				byte_t byte = *row;
				shift_t bits = NBBY - row_bitskip;

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
						byte = *++row;
						row_bitskip = 0;
						bits = NBBY;
					}
				}

				/* Count consecutive 1-bits */
				count = 1;
				while ((x + count) < size_x) {
					if (!bits) {
						byte = *++row;
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
			bitmask += bitskip / NBBY;
			bitskip = bitskip % NBBY;
		} while (--size_y);
		buffer->unlock(lock);
		goto done;
	}
	/* Use pixel-based rendering */
	libvideo_gfx_noblend__bitfill__bypixel(self, dst_x, dst_y, size_x, size_y, pixel, bm);
done:
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
			pixel = video_gfx_x_getpixel(src, src_x + x, src_y + y);
			video_gfx_x_setpixel(dst, dst_x + x, dst_y + y, pixel);
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
	            "dim: {%" PRIuDIM "x%" PRIuDIM "}, bm: %p+%" PRIuPTR "\n",
	            dst_x, dst_y, src_x, src_y, size_x, size_y,
	            bm->vbm_mask, bm->vbm_skip);
	if likely(dst_buffer->wlock(dst_lock) == 0) {
		struct video_lock src_lock;
		struct video_buffer *src_buffer = self->vb_src->vx_buffer;
		if likely(src_buffer->rlock(src_lock) == 0) {
			uintptr_t bitskip = bm->vbm_skip + src_x + src_y * bm->vbm_scan;
			byte_t *dst_line = dst_lock.vl_data + dst_y * dst_lock.vl_stride;
			byte_t const *src_line = src_lock.vl_data + src_y * src_lock.vl_stride;
			byte_t const *bitmask = (byte_t const *)bm->vbm_mask;
			void (LIBVIDEO_CODEC_CC *vc_linecopy)(byte_t *__restrict dst_line, video_coord_t dst_x,
			                                      byte_t const *__restrict src_line, video_coord_t src_x,
			                                      video_dim_t num_pixels);
			bitmask += bitskip / NBBY;
			bitskip = bitskip % NBBY;
			vc_linecopy = dst_buffer->vb_format.vf_codec->vc_linecopy;
#ifndef __OPTIMIZE_SIZE__
			if likely(bitskip == 0 && !(bm->vbm_scan & 7)) {
				size_t bm_scanline = bm->vbm_scan >> 3;
				switch (size_x) {
#define DO_FIXED_WORD_RENDER(N)                                        \
					do {                                               \
						video_dim_t x = 0;                             \
						uint##N##_t word = UNALIGNED_GET##N(bitmask);  \
						while (word) {                                 \
							shift_t bits;                              \
							bits = CLZ((uint##N##_t)word);             \
							x += bits;                                 \
							word <<= bits;                             \
							bits = CLZ((uint##N##_t)~word);            \
							gfx_assert(bits > 0);                      \
							(*vc_linecopy)(dst_line, dst_x + x,        \
							               src_line, src_x + x, bits); \
							x += bits;                                 \
							word <<= bits;                             \
						}                                              \
						dst_line += dst_lock.vl_stride;                \
						src_line += src_lock.vl_stride;                \
						bitmask += bm_scanline;                        \
					} while (--size_y)
				case 0 ... 8:
					DO_FIXED_WORD_RENDER(8);
					goto done;
				case 9 ... 16:
					DO_FIXED_WORD_RENDER(16);
					goto done;
				case 17 ... 32:
					DO_FIXED_WORD_RENDER(32);
					goto done;
#if __SIZEOF_REGISTER__ >= 8
				case 33 ... 64:
					DO_FIXED_WORD_RENDER(64);
					goto done;
#endif /* __SIZEOF_REGISTER__ >= 8 */
				default: break;
#undef DO_FIXED_WORD_RENDER
				}
			}
#endif /* !__OPTIMIZE_SIZE__ */
			do {
				video_dim_t x;
				uintptr_t row_bitskip;
				byte_t const *row;
				x = 0;
				row_bitskip = bitskip;
				row = bitmask;
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
							byte = *++row;
							row_bitskip = 0;
							bits = NBBY;
						}
					}

					/* Count consecutive 1-bits */
					count = 1;
					while ((x + count) < size_x) {
						if (!bits) {
							byte = *++row;
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
				bitmask += bitskip / NBBY;
				bitskip = bitskip % NBBY;
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

#endif /* !GUARD_LIBVIDEO_GFX_GFX_NOBLEND_C_INL */
