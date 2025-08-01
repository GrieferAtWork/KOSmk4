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
#ifdef __INTELLISENSE__
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define DEFINE_BPP 2
//#define DEFINE_LSB
#define DEFINE_MSB
#endif /* __INTELLISENSE__ */

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <stddef.h>
#include <string.h>

#include <libvideo/color.h>
#include <libvideo/gfx/api.h>
#include <libvideo/types.h>

#include "codec-utils.h"

#if !(DEFINE_BPP == 1 || DEFINE_BPP == 2 || DEFINE_BPP == 4)
#error "Must '#define DEFINE_BPP' as 1, 2 or 4"
#endif /* ... */

#if (defined(DEFINE_LSB) + defined(DEFINE_MSB)) != 1
#error "Must #define excatly one of `DEFINE_LSB' or `DEFINE_MSB'"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_LSB
#define LOCAL_FUNC(x) PP_CAT3(x, DEFINE_BPP, _lsb)
#else /* DEFINE_LSB */
#define LOCAL_FUNC(x) PP_CAT3(x, DEFINE_BPP, _msb)
#endif /* !DEFINE_LSB */

#if DEFINE_BPP == 1
#define LOCAL_BPP_LOG2             0 /* x1 */
#define LOCAL_PIXELS_PER_BYTE      8
#define LOCAL_PIXELS_PER_BYTE_LOG2 3
#define LOCAL_PIXELS_PER_BYTE_MASK 7
#define LOCAL_PIXELS_MASK          0x1
#define LOCAL_PIXELS_MUL           0xff /* 0b11111111 */
#elif DEFINE_BPP == 2
#define LOCAL_BPP_LOG2             1 /* x2 */
#define LOCAL_PIXELS_PER_BYTE      4
#define LOCAL_PIXELS_PER_BYTE_LOG2 2
#define LOCAL_PIXELS_PER_BYTE_MASK 3
#define LOCAL_PIXELS_MASK          0x3
#define LOCAL_PIXELS_MUL           0x55 /* 0b01010101 */
#elif DEFINE_BPP == 4
#define LOCAL_BPP_LOG2             2 /* x4 */
#define LOCAL_PIXELS_PER_BYTE      2
#define LOCAL_PIXELS_PER_BYTE_LOG2 1
#define LOCAL_PIXELS_PER_BYTE_MASK 1
#define LOCAL_PIXELS_MASK          0xf
#define LOCAL_PIXELS_MUL           0x11 /* 0b00010001 */
#else /* DEFINE_BPP == ... */
#define LOCAL_BPP_LOG2             log2(DEFINE_BPP)
#define LOCAL_PIXELS_PER_BYTE      (NBBY / DEFINE_BPP)
#define LOCAL_PIXELS_PER_BYTE_LOG2 log2(LOCAL_PIXELS_PER_BYTE)
#define LOCAL_PIXELS_PER_BYTE_MASK (LOCAL_PIXELS_PER_BYTE - 1)
#define LOCAL_PIXELS_MASK          ((1 << DEFINE_BPP) - 1)
#endif /* DEFINE_BPP != ... */


/* Returns a mask for the least significant "n" pixels in a byte:
 * BPP n=0 n=1 n=2 n=3 n=4 n=5 n=6 n=7 n=8
 * 1     -      0x01   0x03   0x07   0x0f   0x1f   0x3f   0x7f   0xff
 * 2     -      0x03   0x0f   0x3f   0xff   -      -      -      -
 * 4     -      0x0f   0xff   -      -      -      -      -      - */
#if 1
#define _LSB_PXMASK(n) ((byte_t)(0xff >> ((LOCAL_PIXELS_PER_BYTE - (n)) << LOCAL_BPP_LOG2)))
#else
#define _LSB_PXMASK(n) (((byte_t)1 << ((n) << LOCAL_BPP_LOG2)) - 1)
#endif

/* Returns a mask for the most significant "n" pixels in a byte:
 * BPP n=0 n=1 n=2 n=3 n=4 n=5 n=6 n=7 n=8
 * 1     -      0x80   0xc0   0xe0   0xf0   0xf8   0xfc   0xfe   0xff
 * 2     -      0xc0   0xf0   0xfc   0xff   -      -      -      -
 * 4     -      0xf0   0xff   -      -      -      -      -      - */
#if 1
#define _MSB_PXMASK(n) ((byte_t)(0xff << ((LOCAL_PIXELS_PER_BYTE - (n)) << LOCAL_BPP_LOG2)))
#else
#define _MSB_PXMASK(n) ((((byte_t)1 << ((n) << LOCAL_BPP_LOG2)) - 1) << ((LOCAL_PIXELS_PER_BYTE - (n)) << LOCAL_BPP_LOG2))
#endif

/* Returns the inverse mask for the least significant "n" pixels in a byte,
 * but  also  works  for  "n=0",  but  not  for  "n=LOCAL_PIXELS_PER_BYTE":
 * BPP n=0 n=1 n=2 n=3 n=4 n=5 n=6 n=7 n=8
 * 1     0xff   0xfe   0xfc   0xf8   0xf0   0xe0   0xc0   0x80   -
 * 2     0xff   0xfc   0xf0   0xc0   -      -      -      -      -
 * 4     0xff   0xf0   -      -      -      -      -      -      - */
#define _LSB_PXMASK_I(n) ((byte_t)0xff << ((shift_t)(n) << LOCAL_BPP_LOG2))

/* Returns the inverse mask for the most significant "n" pixels in a byte,
 * but also  works  for  "n=0",  but  not  for  "n=LOCAL_PIXELS_PER_BYTE":
 * BPP n=0 n=1 n=2 n=3 n=4 n=5 n=6 n=7 n=8
 * 1     0xff   0x7f   0x3f   0x1f   0x0f   0x07   0x03   0x01   -
 * 2     0xff   0x3f   0x0f   0x03   -      -      -      -      -
 * 4     0xff   0x0f   -      -      -      -      -      -      - */
#define _MSB_PXMASK_I(n) ((byte_t)0xff >> ((shift_t)(n) << LOCAL_BPP_LOG2))


/* Aliases that automatically select function based on current LSB/MSB config */
#ifdef DEFINE_LSB
#define _PXMASK(n)   _LSB_PXMASK(n)
#define _PXMASK_I(n) _LSB_PXMASK_I(n)
#else /* DEFINE_LSB */
#define _PXMASK(n)   _MSB_PXMASK(n)
#define _PXMASK_I(n) _MSB_PXMASK_I(n)
#endif /* !DEFINE_LSB */


/************************************************************************/
/* PIXEL GETTER                                                         */
/************************************************************************/
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
LOCAL_FUNC(getpixel)(byte_t const *__restrict line, video_coord_t x) {
	line += x >> LOCAL_PIXELS_PER_BYTE_LOG2;
#ifdef DEFINE_LSB
	return (*line >> ((x & LOCAL_PIXELS_PER_BYTE_MASK) << LOCAL_BPP_LOG2)) & LOCAL_PIXELS_MASK;
#else /* DEFINE_LSB */
#if 1
	return (*line >> (((~x) & LOCAL_PIXELS_PER_BYTE_MASK) << LOCAL_BPP_LOG2)) & LOCAL_PIXELS_MASK;
#else
	return (*line >> ((LOCAL_PIXELS_PER_BYTE_MASK - (x & LOCAL_PIXELS_PER_BYTE_MASK)) << LOCAL_BPP_LOG2)) & LOCAL_PIXELS_MASK;
#endif
#endif /* !DEFINE_LSB */
}




/************************************************************************/
/* PIXEL SETTER                                                         */
/************************************************************************/
PRIVATE NONNULL((1)) void FCC
LOCAL_FUNC(setpixel)(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	byte_t value;
	shift_t shift;
	line += x >> LOCAL_PIXELS_PER_BYTE_LOG2;
#ifdef DEFINE_LSB
	shift = (x & LOCAL_PIXELS_PER_BYTE_MASK) << LOCAL_BPP_LOG2;
#else /* DEFINE_LSB */
#if 1
	shift = (shift_t)((~x) & LOCAL_PIXELS_PER_BYTE_MASK) << LOCAL_BPP_LOG2;
#else
	shift = (LOCAL_PIXELS_PER_BYTE_MASK - (x & LOCAL_PIXELS_PER_BYTE_MASK)) << LOCAL_BPP_LOG2;
#endif
#endif /* !DEFINE_LSB */
	value = *line;
	value &= ~(LOCAL_PIXELS_MASK << shift);
	value |= ((pixel & LOCAL_PIXELS_MASK) << shift);
	*line = value;
}

#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC
LOCAL_FUNC(rp3_setpixel)(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	byte_t value;
	shift_t shift;
	line += x >> LOCAL_PIXELS_PER_BYTE_LOG2;
#ifdef DEFINE_LSB
	shift = (x & LOCAL_PIXELS_PER_BYTE_MASK) << LOCAL_BPP_LOG2;
#else /* DEFINE_LSB */
#if 1
	shift = (shift_t)((~x) & LOCAL_PIXELS_PER_BYTE_MASK) << LOCAL_BPP_LOG2;
#else
	shift = (LOCAL_PIXELS_PER_BYTE_MASK - (x & LOCAL_PIXELS_PER_BYTE_MASK)) << LOCAL_BPP_LOG2;
#endif
#endif /* !DEFINE_LSB */
	value = *line;
	value &= ~(LOCAL_PIXELS_MASK << shift);
	value |= ((pixel & LOCAL_PIXELS_MASK) << shift);
	*line = value;
}
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */



/************************************************************************/
/* LINE FILL                                                            */
/************************************************************************/
PRIVATE NONNULL((1)) void FCC
LOCAL_FUNC(linefill)(byte_t *__restrict line, video_coord_t x,
                     video_pixel_t pixel, video_dim_t num_pixels) {
	byte_t word = (byte_t)LOCAL_PIXELS_MUL * (byte_t)(pixel & LOCAL_PIXELS_MASK);
	codec_assert(num_pixels > 0);
	line += x >> LOCAL_PIXELS_PER_BYTE_LOG2;
	x &= LOCAL_PIXELS_PER_BYTE_MASK;
	if (x) {
#if LOCAL_PIXELS_PER_BYTE == 2
		/* Given: x >= 1 && x <= 1    (because LOCAL_PIXELS_PER_BYTE_MASK==1)
		 *        -> x == 1
		 * Since LOCAL_PIXELS_PER_BYTE == 2, we know that "max_write == 1" */
		byte_t value;
		/* All pixels to write are within the first byte */
		value = *line;
#ifdef DEFINE_LSB
		value &= ~0xf0;
		value |= word & 0xf0;
#else /* DEFINE_LSB */
		value &= ~0x0f;
		value |= word & 0x0f;
#endif /* !DEFINE_LSB */
		*line = value;
		if (num_pixels <= 1)
			return;
		/*x += 1;*/
		num_pixels -= 1;
		++line;
#else /* LOCAL_PIXELS_PER_BYTE == 2 */
		byte_t mask, value;
		shift_t max_write = LOCAL_PIXELS_PER_BYTE - (shift_t)x;
		if (max_write >= num_pixels) {
			/* All pixels to write are within the first byte */
			mask = _PXMASK(num_pixels) >> ((shift_t)x << LOCAL_BPP_LOG2);
			value = *line;
			value &= ~mask;
			value |= word & mask;
			*line = value;
			return;
		}

		/* All bits from the first byte are part of the pixel */
		mask  = _PXMASK_I(x);
		value = *line;
		value &= ~mask;
		value |= word & mask;
		*line = value;
		/*x += max_write;*/
		num_pixels -= max_write;
		++line;
#endif /* LOCAL_PIXELS_PER_BYTE != 2 */
	}

	codec_assert(num_pixels > 0);
	line = mempsetb(line, word, num_pixels >> LOCAL_PIXELS_PER_BYTE_LOG2);
	num_pixels &= LOCAL_PIXELS_PER_BYTE_MASK;
	if (num_pixels) {
		/* Write leading pixels of last byte */
		byte_t mask, value;
		mask  = _PXMASK(num_pixels);
		value = *line;
		value &= ~mask;
		value |= word & mask;
		*line = value;
	}
}



/************************************************************************/
/* VERTICAL FILL                                                        */
/************************************************************************/
PRIVATE NONNULL((1)) void FCC
LOCAL_FUNC(vertfill)(byte_t *__restrict line, video_coord_t x, size_t stride,
                     video_pixel_t pixel, video_dim_t num_pixels) {
	byte_t mask, word;
	shift_t shift;
	codec_assert(num_pixels > 0);
	line += x >> LOCAL_PIXELS_PER_BYTE_LOG2;
#ifdef DEFINE_LSB
	shift = (shift_t)(x & LOCAL_PIXELS_PER_BYTE_MASK) << LOCAL_BPP_LOG2;
#else /* DEFINE_LSB */
#if 1
	shift = (shift_t)((~x) & LOCAL_PIXELS_PER_BYTE_MASK) << LOCAL_BPP_LOG2;
#else
	shift = (LOCAL_PIXELS_PER_BYTE_MASK - (x & LOCAL_PIXELS_PER_BYTE_MASK)) << LOCAL_BPP_LOG2;
#endif
#endif /* !DEFINE_LSB */
	mask = ~(byte_t)(LOCAL_PIXELS_MASK << shift);
	word = (byte_t)(pixel & LOCAL_PIXELS_MASK) << shift;
	do {
		*line = (*line & mask) | word;
		line += stride;
	} while (--num_pixels);
}



/************************************************************************/
/* RECTANGLE FILL                                                       */
/************************************************************************/
PRIVATE NONNULL((1)) void FCC
LOCAL_FUNC(rectfill)(byte_t *__restrict line, video_coord_t x, size_t stride,
                     video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	byte_t word = (byte_t)LOCAL_PIXELS_MUL * (byte_t)(pixel & LOCAL_PIXELS_MASK);
	byte_t value;
	byte_t head_mask;
	byte_t head_word;
	byte_t tail_mask;
	byte_t tail_word;
	shift_t head_skip; /* # of bits to skip in the first byte */
	shift_t head_fill; /* # of bits to fill in the first byte */
	shift_t tail_fill; /* # of bits to fill in the last byte */
	video_dim_t full_words;
	video_dim_t after_head; /* # of pixels after */
	line += x >> LOCAL_PIXELS_PER_BYTE_LOG2;
	head_skip = x & LOCAL_PIXELS_PER_BYTE_MASK;
	if (size_x <= (video_dim_t)(LOCAL_PIXELS_PER_BYTE - head_skip)) {
		/* Head only */
#ifdef DEFINE_LSB
		head_mask = _LSB_PXMASK(size_x) << (head_skip << LOCAL_BPP_LOG2);
#else /* DEFINE_LSB */
		head_mask = _MSB_PXMASK(size_x) >> (head_skip << LOCAL_BPP_LOG2);
#endif /* !DEFINE_LSB */
		head_word = word & head_mask;
		head_mask = ~head_mask;
		do {
			value = *line;
			value &= head_mask;
			value |= head_word;
			*line = value;
			line += stride;
		} while (--size_y);
		return;
	}

	/* Fill-mode for the head-byte */
	head_fill = (LOCAL_PIXELS_PER_BYTE - head_skip) & LOCAL_PIXELS_PER_BYTE_MASK;

	/* Figure out how many "whole" words there are in a line */
	after_head = size_x - head_fill;
	full_words = after_head >> LOCAL_PIXELS_PER_BYTE_LOG2;

	/* Figure out how many pixels must be written to a tail-byte */
	tail_fill = after_head & LOCAL_PIXELS_PER_BYTE_MASK;
	tail_mask = _PXMASK(tail_fill);
	tail_word = word & tail_mask;
	tail_mask = ~tail_mask;

	/* Select fill loop based on presence of head/tail */
	if (head_skip) {
		head_mask = _PXMASK_I(head_skip);
		head_word = word & head_mask;
		head_mask = ~head_mask;
		if (tail_fill) {
#ifndef __OPTIMIZE_SIZE__
			if (!full_words) {
				do {
					line[0] = (line[0] & head_mask) | head_word;
					line[1] = (line[1] & tail_mask) | tail_word;
					line += stride;
				} while (--size_y);
			} else
#endif /* !__OPTIMIZE_SIZE__ */
			{
				stride -= (full_words + 1);
				do {
					*line = (*line & head_mask) | head_word;
					++line;
					line = mempsetb(line, word, full_words);
					*line = (*line & tail_mask) | tail_word;
					line += stride;
				} while (--size_y);
			}
		} else {
#ifndef __OPTIMIZE_SIZE__
			if (!full_words) {
				do {
					*line = (*line & head_mask) | head_word;
					line += stride;
				} while (--size_y);
			} else
#endif /* !__OPTIMIZE_SIZE__ */
			{
				stride -= (full_words + 1);
				do {
					*line = (*line & head_mask) | head_word;
					++line;
					line = mempsetb(line, word, full_words);
					line += stride;
				} while (--size_y);
			}
		}
	} else if (tail_fill) {
#ifndef __OPTIMIZE_SIZE__
		if (!full_words) {
			do {
				*line = (*line & tail_mask) | tail_word;
				line += stride;
			} while (--size_y);
		} else
#endif /* !__OPTIMIZE_SIZE__ */
		{
			stride -= full_words;
			do {
				line = mempsetb(line, word, full_words);
				*line = (*line & tail_mask) | tail_word;
				line += stride;
			} while (--size_y);
		}
	} else {
		stride -= full_words;
		codec_assert(full_words > 0);
		do {
			line = mempsetb(line, word, full_words);
			line += stride;
		} while (--size_y);
	}
}



/************************************************************************/
/* RECTANGLE COPY                                                       */
/************************************************************************/
LOCAL NONNULL((1, 3)) void FCC
LOCAL_FUNC(rectcopy_same_bitoff)(byte_t *__restrict dst_line, size_t dst_stride,
                                 byte_t const *__restrict src_line, size_t src_stride,
                                 shift_t head_skip, video_dim_t size_x, video_dim_t size_y) {
	byte_t value;
	byte_t head_mask;
	byte_t head_mask_i;
	byte_t tail_mask;
	byte_t tail_mask_i;
	shift_t head_fill; /* # of bits to fill in the first byte */
	shift_t tail_fill; /* # of bits to fill in the last byte */
	video_dim_t full_words;
	video_dim_t after_head; /* # of pixels after */

	if (size_x <= (video_dim_t)(LOCAL_PIXELS_PER_BYTE - head_skip)) {
		/* Head only */
		head_mask = _PXMASK(size_x) >> (head_skip << LOCAL_BPP_LOG2);
		head_mask_i = ~head_mask;
		do {
			value = *dst_line;
			value &= head_mask_i;
			value |= *src_line & head_mask;
			*dst_line = value;
			dst_line += dst_stride;
			src_line += src_stride;
		} while (--size_y);
		return;
	}

	/* Fill-mode for the head-byte */
	head_fill = (LOCAL_PIXELS_PER_BYTE - head_skip) & LOCAL_PIXELS_PER_BYTE_MASK;

	/* Figure out how many "whole" words there are in a line */
	after_head = size_x - head_fill;
	full_words = after_head >> LOCAL_PIXELS_PER_BYTE_LOG2;

	/* Figure out how many pixels must be written to a tail-byte */
	tail_fill = after_head & LOCAL_PIXELS_PER_BYTE_MASK;
	tail_mask = _PXMASK(tail_fill);
	tail_mask_i = ~tail_mask;

	/* Select fill loop based on presence of head/tail */
	if (head_skip) {
		head_mask = _PXMASK_I(head_skip);
		head_mask_i = ~head_mask;
		if (tail_fill) {
#ifndef __OPTIMIZE_SIZE__
			if (!full_words) {
				do {
					dst_line[0] = (dst_line[0] & head_mask_i) | (src_line[0] & head_mask);
					dst_line[1] = (dst_line[1] & tail_mask_i) | (src_line[1] & tail_mask);
					dst_line += dst_stride;
					src_line += src_stride;
				} while (--size_y);
			} else
#endif /* !__OPTIMIZE_SIZE__ */
			{
				dst_stride -= (full_words + 1);
				src_stride -= (full_words + 1);
				do {
					*dst_line = (*dst_line & head_mask_i) | (*src_line & head_mask);
					++dst_line;
					++src_line;
					dst_line = mempcpyb(dst_line, src_line, full_words);
					src_line += full_words;
					*dst_line = (*dst_line & tail_mask_i) | (*src_line & tail_mask);
					dst_line += dst_stride;
					src_line += src_stride;
				} while (--size_y);
			}
		} else {
#ifndef __OPTIMIZE_SIZE__
			if (!full_words) {
				do {
					*dst_line = (*dst_line & head_mask_i) | (*src_line & head_mask);
					dst_line += dst_stride;
					src_line += src_stride;
				} while (--size_y);
			} else
#endif /* !__OPTIMIZE_SIZE__ */
			{
				dst_stride -= (full_words + 1);
				src_stride -= 1;
				do {
					*dst_line = (*dst_line & head_mask_i) | (*src_line & head_mask);
					++dst_line;
					++src_line;
					dst_line = mempcpyb(dst_line, src_line, full_words);
					dst_line += dst_stride;
					src_line += src_stride;
				} while (--size_y);
			}
		}
	} else if (tail_fill) {
#ifndef __OPTIMIZE_SIZE__
		if (!full_words) {
			do {
				*dst_line = (*dst_line & tail_mask_i) | (*src_line & tail_mask);
				dst_line += dst_stride;
				src_line += src_stride;
			} while (--size_y);
		} else
#endif /* !__OPTIMIZE_SIZE__ */
		{
			dst_stride -= full_words;
			src_stride -= full_words;
			do {
				dst_line = mempcpyb(dst_line, src_line, full_words);
				src_line += full_words;
				*dst_line = (*dst_line & tail_mask_i) | (*src_line & tail_mask);
				dst_line += dst_stride;
				src_line += src_stride;
			} while (--size_y);
		}
	} else {
		dst_stride -= full_words;
		codec_assert(full_words > 0);
		do {
			dst_line = mempcpyb(dst_line, src_line, full_words);
			dst_line += dst_stride;
			src_line += src_stride;
		} while (--size_y);
	}
}

LOCAL NONNULL((1, 4)) void FCC
LOCAL_FUNC(rectcopy_bitwise)(byte_t *__restrict dst_line, shift_t dst_head_skip, size_t dst_stride,
                             byte_t const *__restrict src_line, shift_t src_head_skip, size_t src_stride,
                             video_dim_t size_x, video_dim_t size_y) {
	do {
		video_dim_t x = 0;
		do {
			video_pixel_t pixel = (LOCAL_FUNC(getpixel)(src_line, src_head_skip + x));
			(LOCAL_FUNC(setpixel)(dst_line, dst_head_skip + x, pixel));
		} while (++x < size_x);
		dst_line += dst_stride;
		src_line += src_stride;
	} while (--size_y);
}

PRIVATE NONNULL((1, 4)) void FCC
LOCAL_FUNC(rectcopy)(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
                     byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
                     video_dim_t size_x, video_dim_t size_y) {
	shift_t dst_head_skip; /* # of bits to skip in the first byte */
	shift_t src_head_skip; /* # of bits to skip in the first byte */
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);

	dst_line += dst_x >> LOCAL_PIXELS_PER_BYTE_LOG2;
	dst_head_skip = dst_x & LOCAL_PIXELS_PER_BYTE_MASK;
	src_line += src_x >> LOCAL_PIXELS_PER_BYTE_LOG2;
	src_head_skip = src_x & LOCAL_PIXELS_PER_BYTE_MASK;

	/* Simple case: source and destination have the same bit-alignment */
	if (dst_head_skip == src_head_skip) {
		(LOCAL_FUNC(rectcopy_same_bitoff)(dst_line, dst_stride, src_line, src_stride,
		                                  dst_head_skip, size_x, size_y));
		return;
	}

	/* TODO: More optimizations */

	(LOCAL_FUNC(rectcopy_bitwise)(dst_line, dst_head_skip, dst_stride,
	                              src_line, src_head_skip, src_stride,
	                              size_x, size_y));
}



/************************************************************************/
/* RECTANGLE MOVE                                                       */
/************************************************************************/
LOCAL NONNULL((1, 3)) void FCC
LOCAL_FUNC(rectcopy_same_bitoff__rev)(byte_t *__restrict dst_line, size_t dst_stride,
                                      byte_t const *__restrict src_line, size_t src_stride,
                                      shift_t head_skip, video_dim_t size_x, video_dim_t size_y) {
	byte_t value;
	byte_t head_mask;
	byte_t head_mask_i;
	byte_t tail_mask;
	byte_t tail_mask_i;
	shift_t head_fill; /* # of bits to fill in the first byte */
	shift_t tail_fill; /* # of bits to fill in the last byte */
	video_dim_t full_words;
	video_dim_t after_head; /* # of pixels after */

	dst_line += size_y * dst_stride;
	src_line += size_y * src_stride;
	if (size_x <= (video_dim_t)(LOCAL_PIXELS_PER_BYTE - head_skip)) {
		/* Head only */
		head_mask = _PXMASK(size_x) >> (head_skip << LOCAL_BPP_LOG2);
		head_mask_i = ~head_mask;
		do {
			dst_line -= dst_stride;
			src_line -= src_stride;
			value = *dst_line;
			value &= head_mask_i;
			value |= *src_line & head_mask;
			*dst_line = value;
		} while (--size_y);
		return;
	}

	/* Fill-mode for the head-byte */
	head_fill = (LOCAL_PIXELS_PER_BYTE - head_skip) & LOCAL_PIXELS_PER_BYTE_MASK;

	/* Figure out how many "whole" words there are in a line */
	after_head = size_x - head_fill;
	full_words = after_head >> LOCAL_PIXELS_PER_BYTE_LOG2;

	/* Figure out how many pixels must be written to a tail-byte */
	tail_fill = after_head & LOCAL_PIXELS_PER_BYTE_MASK;
	tail_mask = _PXMASK(tail_fill);
	tail_mask_i = ~tail_mask;

	/* Select fill loop based on presence of head/tail */
	if (head_skip) {
		head_mask = _PXMASK_I(head_skip);
		head_mask_i = ~head_mask;
		if (tail_fill) {
			do {
				dst_line -= dst_stride;
				src_line -= src_stride;
				dst_line[full_words + 1] = (dst_line[full_words + 1] & tail_mask_i) |
				                           (src_line[full_words + 1] & tail_mask);
				memmoveupb(dst_line + 1, src_line + 1, full_words);
				*dst_line = (*dst_line & head_mask_i) | (*src_line & head_mask);
			} while (--size_y);
		} else {
			do {
				dst_line -= dst_stride;
				src_line -= src_stride;
				memmoveupb(dst_line + 1, src_line + 1, full_words);
				*dst_line = (*dst_line & head_mask_i) | (*src_line & head_mask);
			} while (--size_y);
		}
	} else if (tail_fill) {
		do {
			dst_line -= dst_stride;
			src_line -= src_stride;
			dst_line[full_words] = (dst_line[full_words] & tail_mask_i) |
			                       (src_line[full_words] & tail_mask);
			memmoveupb(dst_line, src_line, full_words);
		} while (--size_y);
	} else {
		codec_assert(full_words > 0);
		do {
			dst_line -= dst_stride;
			src_line -= src_stride;
			memmoveupb(dst_line, src_line, full_words);
		} while (--size_y);
	}
}

LOCAL NONNULL((1, 4)) void FCC
LOCAL_FUNC(rectcopy_bitwise__rev)(byte_t *__restrict dst_line, shift_t dst_head_skip, size_t dst_stride,
                                  byte_t const *__restrict src_line, shift_t src_head_skip, size_t src_stride,
                                  video_dim_t size_x, video_dim_t size_y) {
	dst_line += size_y * dst_stride;
	src_line += size_y * src_stride;
	do {
		video_dim_t x;
		dst_line -= dst_stride;
		src_line -= src_stride;
		x = size_x;
		do {
			video_pixel_t pixel = (LOCAL_FUNC(getpixel)(src_line, src_head_skip + x));
			(LOCAL_FUNC(setpixel)(dst_line, dst_head_skip + x, pixel));
		} while (--x);
	} while (--size_y);
}

PRIVATE NONNULL((1, 3)) void FCC
LOCAL_FUNC(rectmove)(byte_t *__restrict dst_line, video_coord_t dst_x,
                     byte_t const *__restrict src_line, video_coord_t src_x,
                     size_t stride, video_dim_t size_x, video_dim_t size_y) {
	shift_t dst_head_skip; /* # of bits to skip in the first byte */
	shift_t src_head_skip; /* # of bits to skip in the first byte */
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);

	dst_line += dst_x >> LOCAL_PIXELS_PER_BYTE_LOG2;
	dst_head_skip = dst_x & LOCAL_PIXELS_PER_BYTE_MASK;
	src_line += src_x >> LOCAL_PIXELS_PER_BYTE_LOG2;
	src_head_skip = src_x & LOCAL_PIXELS_PER_BYTE_MASK;

	/* Simple case: source and destination have the same bit-alignment */
	if (dst_head_skip == src_head_skip) {
		if (dst_line <= src_line) {
			(LOCAL_FUNC(rectcopy_same_bitoff)(dst_line, stride, src_line, stride,
			                                  dst_head_skip, size_x, size_y));
		} else {
			(LOCAL_FUNC(rectcopy_same_bitoff__rev)(dst_line, stride, src_line, stride,
			                                       dst_head_skip, size_x, size_y));
		}
		return;
	}

	/* TODO: More optimizations */

	if (dst_line < src_line || (dst_line == src_line && dst_head_skip <= src_head_skip)) {
		(LOCAL_FUNC(rectcopy_bitwise)(dst_line, dst_head_skip, stride,
		                              src_line, src_head_skip, stride,
		                              size_x, size_y));
	} else {
		(LOCAL_FUNC(rectcopy_bitwise__rev)(dst_line, dst_head_skip, stride,
		                                   src_line, src_head_skip, stride,
		                                   size_x, size_y));
	}
}


/************************************************************************/
/* LINE COPY                                                            */
/************************************************************************/
LOCAL NONNULL((1, 2)) void FCC
LOCAL_FUNC(linecopy_same_bitoff)(byte_t *__restrict dst_line,
                                 byte_t const *__restrict src_line,
                                 shift_t head_skip, video_dim_t size_x) {
	byte_t value;
	byte_t head_mask;
	byte_t head_mask_i;
	byte_t tail_mask;
	byte_t tail_mask_i;
	shift_t head_fill; /* # of bits to fill in the first byte */
	shift_t tail_fill; /* # of bits to fill in the last byte */
	video_dim_t full_words;
	video_dim_t after_head; /* # of pixels after */

	if (size_x <= (video_dim_t)(LOCAL_PIXELS_PER_BYTE - head_skip)) {
		/* Head only */
		head_mask = _PXMASK(size_x) >> (head_skip << LOCAL_BPP_LOG2);
		head_mask_i = ~head_mask;
		value = *dst_line;
		value &= head_mask_i;
		value |= *src_line & head_mask;
		*dst_line = value;
		return;
	}

	/* Fill-mode for the head-byte */
	head_fill = (LOCAL_PIXELS_PER_BYTE - head_skip) & LOCAL_PIXELS_PER_BYTE_MASK;

	/* Figure out how many "whole" words there are in a line */
	after_head = size_x - head_fill;
	full_words = after_head >> LOCAL_PIXELS_PER_BYTE_LOG2;

	/* Figure out how many pixels must be written to a tail-byte */
	tail_fill = after_head & LOCAL_PIXELS_PER_BYTE_MASK;
	tail_mask = _PXMASK(tail_fill);
	tail_mask_i = ~tail_mask;

	/* Select fill loop based on presence of head/tail */
	if (head_skip) {
		head_mask = _PXMASK_I(head_skip);
		head_mask_i = ~head_mask;
		if (tail_fill) {
#ifndef __OPTIMIZE_SIZE__
			if (!full_words) {
				dst_line[0] = (dst_line[0] & head_mask_i) | (src_line[0] & head_mask);
				dst_line[1] = (dst_line[1] & tail_mask_i) | (src_line[1] & tail_mask);
			} else
#endif /* !__OPTIMIZE_SIZE__ */
			{
				*dst_line = (*dst_line & head_mask_i) | (*src_line & head_mask);
				++dst_line;
				++src_line;
				dst_line = mempcpyb(dst_line, src_line, full_words);
				src_line += full_words;
				*dst_line = (*dst_line & tail_mask_i) | (*src_line & tail_mask);
			}
		} else {
#ifndef __OPTIMIZE_SIZE__
			if (!full_words) {
				*dst_line = (*dst_line & head_mask_i) | (*src_line & head_mask);
			} else
#endif /* !__OPTIMIZE_SIZE__ */
			{
				*dst_line = (*dst_line & head_mask_i) | (*src_line & head_mask);
				++dst_line;
				++src_line;
				memcpyb(dst_line, src_line, full_words);
			}
		}
	} else if (tail_fill) {
#ifndef __OPTIMIZE_SIZE__
		if (!full_words) {
			*dst_line = (*dst_line & tail_mask_i) | (*src_line & tail_mask);
		} else
#endif /* !__OPTIMIZE_SIZE__ */
		{
			dst_line = mempcpyb(dst_line, src_line, full_words);
			src_line += full_words;
			*dst_line = (*dst_line & tail_mask_i) | (*src_line & tail_mask);
		}
	} else {
		codec_assert(full_words > 0);
		dst_line = mempcpyb(dst_line, src_line, full_words);
	}
}

LOCAL NONNULL((1, 3)) void FCC
LOCAL_FUNC(linecopy_bitwise)(byte_t *__restrict dst_line, shift_t dst_head_skip,
                             byte_t const *__restrict src_line, shift_t src_head_skip,
                             video_dim_t size_x) {
	video_dim_t x = 0;
	do {
		video_pixel_t pixel = (LOCAL_FUNC(getpixel)(src_line, src_head_skip + x));
		(LOCAL_FUNC(setpixel)(dst_line, dst_head_skip + x, pixel));
	} while (++x < size_x);
}

PRIVATE NONNULL((1, 3)) void FCC
LOCAL_FUNC(linecopy)(byte_t *__restrict dst_line, video_coord_t dst_x,
                     byte_t const *__restrict src_line, video_coord_t src_x,
                     video_dim_t size_x) {
	shift_t dst_head_skip; /* # of bits to skip in the first byte */
	shift_t src_head_skip; /* # of bits to skip in the first byte */
	codec_assert(size_x > 0);

	dst_line += dst_x >> LOCAL_PIXELS_PER_BYTE_LOG2;
	dst_head_skip = dst_x & LOCAL_PIXELS_PER_BYTE_MASK;
	src_line += src_x >> LOCAL_PIXELS_PER_BYTE_LOG2;
	src_head_skip = src_x & LOCAL_PIXELS_PER_BYTE_MASK;

	/* Simple case: source and destination have the same bit-alignment */
	if (dst_head_skip == src_head_skip) {
		(LOCAL_FUNC(linecopy_same_bitoff)(dst_line, src_line,
		                                  dst_head_skip, size_x));
		return;
	}

	/* TODO: More optimizations */

	(LOCAL_FUNC(linecopy_bitwise)(dst_line, dst_head_skip,
	                              src_line, src_head_skip,
	                              size_x));
}



#undef _PXMASK
#undef _PXMASK_I
#undef _LSB_PXMASK
#undef _MSB_PXMASK
#undef _LSB_PXMASK_I
#undef _MSB_PXMASK_I

#undef LOCAL_PIXELS_MUL
#undef LOCAL_PIXELS_MASK
#undef LOCAL_PIXELS_PER_BYTE_MASK
#undef LOCAL_PIXELS_PER_BYTE_LOG2
#undef LOCAL_PIXELS_PER_BYTE
#undef LOCAL_BPP_LOG2
#undef LOCAL_FUNC

DECL_END

#undef DEFINE_BPP
#undef DEFINE_MSB
#undef DEFINE_LSB
