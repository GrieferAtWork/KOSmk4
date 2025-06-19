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
#ifndef GUARD_LIBVIDEO_CODEC_CODECS_C
#define GUARD_LIBVIDEO_CODEC_CODECS_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/__bitfield.h>
#include <hybrid/align.h>
#include <hybrid/bit.h>
#include <hybrid/byteorder.h>
#include <hybrid/host.h>
#include <hybrid/unaligned.h>

#include <kos/kernel/types.h>
#include <kos/types.h>
#include <sys/param.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/palette.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>

#include "codec-specs.h"
#include "codecs.h"
#include "converter.h"
#include "palette.h"

#if defined(NDEBUG) || 1
#if 1 /* Turn codec assertions into compile-time assumptions for max speed */
#ifdef __CRT_UBSAN_BUILTIN_UNREACHABLE
#undef __CRT_UBSAN_BUILTIN_UNREACHABLE
#undef __builtin_unreachable /* Disable binding of "__ubsan_handle_builtin_unreachable" */
#endif /* __CRT_UBSAN_BUILTIN_UNREACHABLE */
#define codec_assert(x)       __builtin_assume(x)
#define codec_assertf(x, ...) __builtin_assume(x)
#else
#define codec_assert(x)       (void)0
#define codec_assertf(x, ...) (void)0
#endif
#else /* ... */
#include <assert.h>
#define codec_assert  assert
#define codec_assertf assertf
#endif /* !... */

DECL_BEGIN

union word32 {
	uint32_t dword;
	uint16_t words[2];
	byte_t   bytes[4];
};

union word16 {
	uint16_t word;
	byte_t   bytes[2];
};

/************************************************************************/
/* PIXEL OPERATIONS                                                     */
/************************************************************************/

LOCAL ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel1_inbyte_lsb(byte_t const *__restrict byte,
                     shift_t shift) {
	assert(shift < NBBY);
	return (*byte >> shift) & 1;
}

LOCAL NONNULL((1)) void CC
setpixel1_inbyte_lsb(byte_t *__restrict byte,
                     shift_t shift,
                     video_pixel_t pixel) {
	byte_t newbyte;
	assert(shift < NBBY);
	newbyte = *byte;
	newbyte &= ~((byte_t)1 << shift);
	newbyte |= ((byte_t)(pixel & 1) << shift);
	*byte = newbyte;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel1_inbyte_msb(byte_t const *__restrict byte,
                     shift_t shift) {
	assert(shift < NBBY);
	return getpixel1_inbyte_lsb(byte, (NBBY - 1) - shift);
}

LOCAL NONNULL((1)) void CC
setpixel1_inbyte_msb(byte_t *__restrict byte,
                     shift_t shift,
                     video_pixel_t pixel) {
	assert(shift < NBBY);
	setpixel1_inbyte_lsb(byte, (NBBY - 1) - shift, pixel);
}


LOCAL ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel2_inbyte_lsb(byte_t const *__restrict byte,
                     shift_t shift) {
	assert(shift < 4);
	return (*byte >> (shift * 2)) & 3;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel2_inbyte_msb(byte_t const *__restrict byte,
                     shift_t shift) {
	assert(shift < 4);
	return (*byte >> (6 - (shift * 2))) & 3;
}

LOCAL NONNULL((1)) void CC
setpixel2_inbyte_lsb(byte_t *__restrict byte,
                     shift_t shift,
                     video_pixel_t pixel) {
	byte_t newbyte;
	assert(shift < 4);
	newbyte = *byte;
	shift = (shift_t)(shift * 2);
	newbyte &= ~(3 << shift);
	newbyte |= ((uint8_t)(pixel & 3) << shift);
	*byte = newbyte;
}

LOCAL NONNULL((1)) void CC
setpixel2_inbyte_msb(byte_t *__restrict byte,
                     shift_t shift,
                     video_pixel_t pixel) {
	byte_t newbyte;
	assert(shift < 4);
	newbyte = *byte;
	shift = (shift_t)(6 - (shift * 2));
	newbyte &= ~(3 << shift);
	newbyte |= ((uint8_t)(pixel & 3) << shift);
	*byte = newbyte;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel4_inbyte_lsb(byte_t const *__restrict byte,
                     shift_t shift) {
	assert(shift < 2);
	return (*byte >> (shift * 4)) & 7;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel4_inbyte_msb(byte_t const *__restrict byte,
                     shift_t shift) {
	assert(shift < 2);
	return (*byte >> (4 - (shift * 4))) & 7;
}

LOCAL NONNULL((1)) void CC
setpixel4_inbyte_lsb(byte_t *__restrict byte,
                     shift_t shift,
                     video_pixel_t pixel) {
	byte_t newbyte;
	assert(shift < 2);
	newbyte = *byte;
	shift = (shift_t)(shift * 4);
	newbyte &= ~(7 << shift);
	newbyte |= ((uint8_t)(pixel & 7) << shift);
	*byte = newbyte;
}

LOCAL NONNULL((1)) void CC
setpixel4_inbyte_msb(byte_t *__restrict byte,
                     shift_t shift,
                     video_pixel_t pixel) {
	byte_t newbyte;
	assert(shift < 2);
	newbyte = *byte;
	shift = (shift_t)(4 - (shift * 4));
	newbyte &= ~(7 << shift);
	newbyte |= ((uint8_t)(pixel & 7) << shift);
	*byte = newbyte;
}




PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel1_lsb(byte_t const *__restrict line, video_coord_t x) {
	return getpixel1_inbyte_lsb(line + (x / NBBY), (shift_t)(x % NBBY));
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel1_msb(byte_t const *__restrict line, video_coord_t x) {
	return getpixel1_inbyte_msb(line + (x / NBBY), (shift_t)(x % NBBY));
}

PRIVATE NONNULL((1)) void CC
setpixel1_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	setpixel1_inbyte_lsb(line + (x / NBBY), (shift_t)(x % NBBY), pixel);
}

PRIVATE NONNULL((1)) void CC
setpixel1_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	setpixel1_inbyte_msb(line + (x / NBBY), (shift_t)(x % NBBY), pixel);
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel2_lsb(byte_t const *__restrict line, video_coord_t x) {
	return getpixel2_inbyte_lsb(line + (x / 4), x % 4);
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel2_msb(byte_t const *__restrict line, video_coord_t x) {
	return getpixel2_inbyte_msb(line + (x / 4), x % 4);
}

PRIVATE NONNULL((1)) void CC
setpixel2_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	setpixel2_inbyte_lsb(line + (x / 4), x % 4, pixel);
}

PRIVATE NONNULL((1)) void CC
setpixel2_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	setpixel2_inbyte_msb(line + (x / 4), x % 4, pixel);
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel4_lsb(byte_t const *__restrict line, video_coord_t x) {
	return getpixel4_inbyte_lsb(line + (x / 2), x % 2);
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel4_msb(byte_t const *__restrict line, video_coord_t x) {
	return getpixel4_inbyte_msb(line + (x / 2), x % 2);
}

PRIVATE NONNULL((1)) void CC
setpixel4_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	setpixel4_inbyte_lsb(line + (x / 2), x % 2, pixel);
}

PRIVATE NONNULL((1)) void CC
setpixel4_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	setpixel4_inbyte_msb(line + (x / 2), x % 2, pixel);
}




PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel8(byte_t const *__restrict line, video_coord_t x) {
	return ((uint8_t const *)line)[x];
}

PRIVATE NONNULL((1)) void CC
setpixel8(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	((uint8_t *)line)[x] = (uint8_t)pixel;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel16(byte_t const *__restrict line, video_coord_t x) {
	return ((uint16_t const *)line)[x];
}

PRIVATE NONNULL((1)) void CC
setpixel16(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	((uint16_t *)line)[x] = (uint16_t)pixel;
}

#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#define unaligned_getpixel16 getpixel16
#define unaligned_setpixel16 setpixel16
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
unaligned_getpixel16(byte_t const *__restrict line, video_coord_t x) {
	return UNALIGNED_GET16(&((uint16_t const *)line)[x]);
}

PRIVATE NONNULL((1)) void CC
unaligned_setpixel16(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	UNALIGNED_SET16(&((uint16_t *)line)[x], (uint16_t)pixel);
}
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */


PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel24(byte_t const *__restrict line, video_coord_t x) {
	union word32 result;
	line += x * 3;
	result.bytes[0] = line[0];
	result.bytes[1] = line[1];
	result.bytes[2] = line[2];
	result.bytes[3] = 0;
	return result.dword;
}

PRIVATE NONNULL((1)) void CC
setpixel24(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	union word32 data;
	data.dword = pixel;
	line += x * 3;
	line[0] = data.bytes[0];
	line[1] = data.bytes[1];
	line[2] = data.bytes[2];
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel32(byte_t const *__restrict line, video_coord_t x) {
	return ((uint32_t const *)line)[x];
}

PRIVATE NONNULL((1)) void CC
setpixel32(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	((uint32_t *)line)[x] = (uint32_t)pixel;
}

#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#define unaligned_getpixel32 getpixel32
#define unaligned_setpixel32 setpixel32
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
unaligned_getpixel32(byte_t const *__restrict line, video_coord_t x) {
	return UNALIGNED_GET32(&((uint32_t const *)line)[x]);
}

PRIVATE NONNULL((1)) void CC
unaligned_setpixel32(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	UNALIGNED_SET32(&((uint32_t *)line)[x], (uint32_t)pixel);
}
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */



PRIVATE NONNULL((1, 4)) void CC
rectcopy8(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
          byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
          video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x;
	src_line += src_x;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
	do {
		memcpyb(dst_line, src_line, size_x);
		dst_line += dst_stride;
		src_line += src_stride;
	} while (--size_y);
}

PRIVATE NONNULL((1, 4)) void CC
rectcopy16(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
           byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
           video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x << 1;
	src_line += src_x << 1;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	codec_assert(!(dst_stride & 1));
	codec_assert(!(src_stride & 1));
	codec_assert(!((uintptr_t)dst_line & 1));
	codec_assert(!((uintptr_t)src_line & 1));
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	do {
		memcpyw(dst_line, src_line, size_x);
		dst_line += dst_stride;
		src_line += src_stride;
	} while (--size_y);
}

PRIVATE NONNULL((1, 4)) void CC
rectcopy24(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
           byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
           video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x * 3;
	src_line += src_x * 3;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
	size_x *= 3;
	do {
		memcpy(dst_line, src_line, size_x);
		dst_line += dst_stride;
		src_line += src_stride;
	} while (--size_y);
}

PRIVATE NONNULL((1, 4)) void CC
rectcopy32(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
           byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
           video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x << 2;
	src_line += src_x << 2;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	codec_assert(!(dst_stride & 3));
	codec_assert(!(src_stride & 3));
	codec_assert(!((uintptr_t)dst_line & 3));
	codec_assert(!((uintptr_t)src_line & 3));
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	do {
		memcpyl(dst_line, src_line, size_x);
		dst_line += dst_stride;
		src_line += src_stride;
	} while (--size_y);
}

#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#define unaligned_rectcopy16 rectcopy16
#define unaligned_rectcopy32 rectcopy32
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
PRIVATE NONNULL((1, 4)) void CC
unaligned_rectcopy16(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
                     byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
                     video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x << 1;
	src_line += src_x << 1;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
	size_x <<= 1;
	do {
		memcpy(dst_line, src_line, size_x);
		dst_line += dst_stride;
		src_line += src_stride;
	} while (--size_y);
}

PRIVATE NONNULL((1, 4)) void CC
unaligned_rectcopy32(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
                     byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
                     video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x << 2;
	src_line += src_x << 2;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
	size_x <<= 2;
	do {
		memcpy(dst_line, src_line, size_x);
		dst_line += dst_stride;
		src_line += src_stride;
	} while (--size_y);
}
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */




PRIVATE NONNULL((1)) void CC
linefill8(byte_t *__restrict line, video_coord_t x,
          video_pixel_t pixel, video_dim_t num_pixels) {
	line += x;
	codec_assert(num_pixels > 0);
	memsetb(line, (uint8_t)pixel, num_pixels);
}

PRIVATE NONNULL((1)) void CC
vertfill8(byte_t *__restrict line, video_coord_t x, size_t stride,
          video_pixel_t pixel, video_dim_t num_pixels) {
	line += x;
	codec_assert(num_pixels > 0);
	do {
		*(uint8_t *)line = (uint8_t)pixel;
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void CC
rectfill8(byte_t *__restrict line, video_coord_t x, size_t stride,
          video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	line += x;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
	do {
		memset(line, (uint8_t)pixel, size_x);
		line += stride;
	} while (--size_y);
}



PRIVATE NONNULL((1)) void CC
linefill16(byte_t *__restrict line, video_coord_t x,
           video_pixel_t pixel, video_dim_t num_pixels) {
	line += x << 1;
	codec_assert(num_pixels > 0);
	memsetw(line, (uint16_t)pixel, num_pixels);
}

PRIVATE NONNULL((1)) void CC
vertfill16(byte_t *__restrict line, video_coord_t x, size_t stride,
           video_pixel_t pixel, video_dim_t num_pixels) {
	line += x << 1;
	codec_assert(num_pixels > 0);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	codec_assert(!(stride & 1));
	codec_assert(!((uintptr_t)line & 1));
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	do {
		*(uint16_t *)line = (uint16_t)pixel;
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void CC
rectfill16(byte_t *__restrict line, video_coord_t x, size_t stride,
           video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	line += x << 1;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	codec_assert(!(stride & 1));
	codec_assert(!((uintptr_t)line & 1));
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	do {
		memsetw(line, (uint16_t)pixel, size_x);
		line += stride;
	} while (--size_y);
}



PRIVATE NONNULL((1)) void CC
linefill24(byte_t *__restrict line, video_coord_t x,
           video_pixel_t pixel, video_dim_t num_pixels) {
#ifdef __OPTIMIZE_SIZE__
	union word32 data;
	data.dword = pixel;
	line += x * 3;
	codec_assert(num_pixels > 0);
	do {
		line[0] = data.bytes[0];
		line[1] = data.bytes[1];
		line[2] = data.bytes[2];
		line += 3;
	} while (--num_pixels);
#else /* __OPTIMIZE_SIZE__ */
	union word32 data, abc[3];
	data.dword = pixel;
	codec_assert(num_pixels > 0);

	/* Try to write in chunks of 4 pixels, by having 3 control words A,B and C:
	 * >>  111222333444
	 * >>  AAAABBBBCCCC
	 */
	abc[0].bytes[0] = data.bytes[0];
	abc[0].bytes[1] = data.bytes[1];
	abc[0].bytes[2] = data.bytes[2];
	abc[0].bytes[3] = data.bytes[0];
	abc[1].bytes[0] = data.bytes[1];
	abc[1].bytes[1] = data.bytes[2];
	abc[1].bytes[2] = data.bytes[0];
	abc[1].bytes[3] = data.bytes[1];
	abc[2].bytes[0] = data.bytes[2];
	abc[2].bytes[1] = data.bytes[0];
	abc[2].bytes[2] = data.bytes[1];
	abc[2].bytes[3] = data.bytes[2];

	line += x * 3;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	if ((uintptr_t)line & 3) {
		while (num_pixels >= 4) {
			*line++ = abc[0].bytes[0];
			*line++ = abc[0].bytes[1];
			*line++ = abc[0].bytes[2];
			*line++ = abc[0].bytes[3];
			*line++ = abc[1].bytes[0];
			*line++ = abc[1].bytes[1];
			*line++ = abc[1].bytes[2];
			*line++ = abc[1].bytes[3];
			*line++ = abc[2].bytes[0];
			*line++ = abc[2].bytes[1];
			*line++ = abc[2].bytes[2];
			*line++ = abc[2].bytes[3];
			num_pixels -= 4;
		}
	} else
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	{
		while (num_pixels >= 4) {
			*(uint32_t *)line = abc[0].dword;
			line += 4;
			*(uint32_t *)line = abc[1].dword;
			line += 4;
			*(uint32_t *)line = abc[2].dword;
			line += 4;
			num_pixels -= 4;
		}
	}

	/* Write remaining pixels */
	switch (num_pixels) {
	case 3:
		*line++ = data.bytes[0];
		*line++ = data.bytes[1];
		*line++ = data.bytes[2];
		ATTR_FALLTHROUGH
	case 2:
		*line++ = data.bytes[0];
		*line++ = data.bytes[1];
		*line++ = data.bytes[2];
		ATTR_FALLTHROUGH
	case 1:
		*line++ = data.bytes[0];
		*line++ = data.bytes[1];
		*line++ = data.bytes[2];
		ATTR_FALLTHROUGH
	case 0:
		break;
	default: __builtin_unreachable();
	}
#endif /* !__OPTIMIZE_SIZE__ */
}

PRIVATE NONNULL((1)) void CC
vertfill24(byte_t *__restrict line, video_coord_t x, size_t stride,
           video_pixel_t pixel, video_dim_t num_pixels) {
	union word32 data;
	data.dword = pixel;
	line += x * 3;
	codec_assert(num_pixels > 0);
	do {
		line[0] = data.bytes[0];
		line[1] = data.bytes[1];
		line[2] = data.bytes[2];
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void CC
rectfill24(byte_t *__restrict line, video_coord_t x, size_t stride,
           video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
#ifdef __OPTIMIZE_SIZE__
	union word32 data;
	data.dword = pixel;
	line += x * 3;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
	stride -= size_x * 3;
	do {
		video_dim_t iter_x = size_x;
		do {
			line[0] = data.bytes[0];
			line[1] = data.bytes[1];
			line[2] = data.bytes[2];
			line += 3;
		} while (--iter_x);
		line += stride;
	} while (--num_pixels);
#else /* __OPTIMIZE_SIZE__ */
	video_dim_t dword_x;
	union word32 data, abc[3];
	data.dword = pixel;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);

	line += x * 3;
	dword_x = size_x >> 2;
	if (!dword_x) {
		/* Special case: lines consist of **ONLY** trailing, unaligned data.
		 * In this case, we are unable to write pixels in chunks of  dwords. */
		codec_assert(size_x >= 1 && size_x <= 3);
		switch (size_x) {

		case 1: {
			do {
				line[0] = data.bytes[0];
				line[1] = data.bytes[1];
				line[2] = data.bytes[2];
				line += stride;
			} while (--size_y);
		}	break;

		case 2: {
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
			if ((stride & 3) || ((uintptr_t)line & 3)) {
				if (!(stride & 1) && !((uintptr_t)line & 1)) {
					union word16 w1, w2, w3;
					w1.bytes[0] = data.bytes[0];
					w1.bytes[1] = data.bytes[1];
					w2.bytes[0] = data.bytes[2];
					w2.bytes[1] = data.bytes[0];
					w3.bytes[0] = data.bytes[1];
					w3.bytes[1] = data.bytes[2];
					do {
						((uint16_t *)line)[0] = w1.word;
						((uint16_t *)line)[1] = w2.word;
						((uint16_t *)line)[2] = w3.word;
						line += stride;
					} while (--size_y);
				} else {
					stride -= 6;
					do {
						*line++ = data.bytes[0];
						*line++ = data.bytes[1];
						*line++ = data.bytes[2];
						*line++ = data.bytes[0];
						*line++ = data.bytes[1];
						*line++ = data.bytes[2];
						line += stride;
					} while (--size_y);
				}
			} else
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
			{
				union word32 w1;
				union word16 w2;
				w1.bytes[0] = data.bytes[0];
				w1.bytes[1] = data.bytes[1];
				w1.bytes[2] = data.bytes[2];
				w1.bytes[3] = data.bytes[0];
				w2.bytes[0] = data.bytes[1];
				w2.bytes[1] = data.bytes[2];
				do {
					*(uint32_t *)(line + 0) = w1.dword;
					*(uint16_t *)(line + 4) = w2.word;
					line += stride;
				} while (--size_y);
			}
		}	break;

		case 3: {
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
			if ((stride & 3) || ((uintptr_t)line & 3)) {
				if (!(stride & 1) && !((uintptr_t)line & 1)) {
					union word16 w1, w2, w3, w4;
					w1.bytes[0] = data.bytes[0];
					w1.bytes[1] = data.bytes[1];
					w2.bytes[0] = data.bytes[2];
					w2.bytes[1] = data.bytes[0];
					w3.bytes[0] = data.bytes[1];
					w3.bytes[1] = data.bytes[2];
					w4.bytes[0] = data.bytes[0];
					w4.bytes[1] = data.bytes[1];
					do {
						*(uint16_t *)(line + 0) = w1.word;
						*(uint16_t *)(line + 2) = w2.word;
						*(uint16_t *)(line + 4) = w3.word;
						*(uint16_t *)(line + 6) = w4.word;
						*(uint8_t *)(line + 8) = data.bytes[2];
						line += stride;
					} while (--size_y);
				} else {
					stride -= 9;
					do {
						*line++ = data.bytes[0];
						*line++ = data.bytes[1];
						*line++ = data.bytes[2];
						*line++ = data.bytes[0];
						*line++ = data.bytes[1];
						*line++ = data.bytes[2];
						*line++ = data.bytes[0];
						*line++ = data.bytes[1];
						*line++ = data.bytes[2];
						line += stride;
					} while (--size_y);
				}
			} else
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
			{
				union word32 w1;
				union word32 w2;
				w1.bytes[0] = data.bytes[0];
				w1.bytes[1] = data.bytes[1];
				w1.bytes[2] = data.bytes[2];
				w1.bytes[3] = data.bytes[0];
				w2.bytes[0] = data.bytes[1];
				w2.bytes[1] = data.bytes[2];
				w2.bytes[2] = data.bytes[0];
				w2.bytes[3] = data.bytes[1];
				do {
					*(uint32_t *)(line + 0) = w1.dword;
					*(uint32_t *)(line + 4) = w2.dword;
					*(uint8_t *)(line + 8) = data.bytes[2];
					line += stride;
				} while (--size_y);
			}
		}	break;

		default: __builtin_unreachable();
		}
		return;
	}


	/* Try to write in chunks of 4 pixels, by having 3 control words A,B and C:
	 * >>  111222333444
	 * >>  AAAABBBBCCCC
	 */
	abc[0].bytes[0] = data.bytes[0];
	abc[0].bytes[1] = data.bytes[1];
	abc[0].bytes[2] = data.bytes[2];
	abc[0].bytes[3] = data.bytes[0];
	abc[1].bytes[0] = data.bytes[1];
	abc[1].bytes[1] = data.bytes[2];
	abc[1].bytes[2] = data.bytes[0];
	abc[1].bytes[3] = data.bytes[1];
	abc[2].bytes[0] = data.bytes[2];
	abc[2].bytes[1] = data.bytes[0];
	abc[2].bytes[2] = data.bytes[1];
	abc[2].bytes[3] = data.bytes[2];

	stride -= size_x * 3;
	if (!(size_x & 3)) {
		/* Aligned to dword repeat boundaries */
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		if ((uintptr_t)line & 3) {
			do {
				video_dim_t iter_x = dword_x;
				do {
					*line++ = abc[0].bytes[0];
					*line++ = abc[0].bytes[1];
					*line++ = abc[0].bytes[2];
					*line++ = abc[0].bytes[3];
					*line++ = abc[1].bytes[0];
					*line++ = abc[1].bytes[1];
					*line++ = abc[1].bytes[2];
					*line++ = abc[1].bytes[3];
					*line++ = abc[2].bytes[0];
					*line++ = abc[2].bytes[1];
					*line++ = abc[2].bytes[2];
					*line++ = abc[2].bytes[3];
				} while (--iter_x);
				line += stride;
			} while (--size_y);
		} else
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		{
			do {
				video_dim_t iter_x = dword_x;
				do {
					*(uint32_t *)line = abc[0].dword;
					line += 4;
					*(uint32_t *)line = abc[1].dword;
					line += 4;
					*(uint32_t *)line = abc[2].dword;
					line += 4;
				} while (--iter_x);
				line += stride;
			} while (--size_y);
		}
	} else {
		/* Lines have trailing, unaligned data */
		uint_fast8_t tail = size_x & 3;
		codec_assert(tail >= 1 && tail <= 3);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		if ((uintptr_t)line & 3) {
			do {
				video_dim_t iter_x = dword_x;
				do {
					*line++ = abc[0].bytes[0];
					*line++ = abc[0].bytes[1];
					*line++ = abc[0].bytes[2];
					*line++ = abc[0].bytes[3];
					*line++ = abc[1].bytes[0];
					*line++ = abc[1].bytes[1];
					*line++ = abc[1].bytes[2];
					*line++ = abc[1].bytes[3];
					*line++ = abc[2].bytes[0];
					*line++ = abc[2].bytes[1];
					*line++ = abc[2].bytes[2];
					*line++ = abc[2].bytes[3];
				} while (--iter_x);
				switch (tail) {
				case 3:
					*line++ = data.bytes[0];
					*line++ = data.bytes[1];
					*line++ = data.bytes[2];
					ATTR_FALLTHROUGH
				case 2:
					*line++ = data.bytes[0];
					*line++ = data.bytes[1];
					*line++ = data.bytes[2];
					ATTR_FALLTHROUGH
				case 1:
					*line++ = data.bytes[0];
					*line++ = data.bytes[1];
					*line++ = data.bytes[2];
					break;
				default: __builtin_unreachable();
				}
				line += stride;
			} while (--size_y);
		} else
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		{
			do {
				video_dim_t iter_x = dword_x;
				do {
					*(uint32_t *)line = abc[0].dword;
					line += 4;
					*(uint32_t *)line = abc[1].dword;
					line += 4;
					*(uint32_t *)line = abc[2].dword;
					line += 4;
				} while (--iter_x);
				switch (tail) {
				case 3:
					*line++ = data.bytes[0];
					*line++ = data.bytes[1];
					*line++ = data.bytes[2];
					ATTR_FALLTHROUGH
				case 2:
					*line++ = data.bytes[0];
					*line++ = data.bytes[1];
					*line++ = data.bytes[2];
					ATTR_FALLTHROUGH
				case 1:
					*line++ = data.bytes[0];
					*line++ = data.bytes[1];
					*line++ = data.bytes[2];
					break;
				default: __builtin_unreachable();
				}
				line += stride;
			} while (--size_y);
		}
	}
#endif /* !__OPTIMIZE_SIZE__ */
}



PRIVATE NONNULL((1)) void CC
linefill32(byte_t *__restrict line, video_coord_t x,
           video_pixel_t pixel, video_dim_t num_pixels) {
	line += x << 2;
	codec_assert(num_pixels > 0);
	memsetl(line, (uint32_t)pixel, num_pixels);
}

PRIVATE NONNULL((1)) void CC
vertfill32(byte_t *__restrict line, video_coord_t x, size_t stride,
           video_pixel_t pixel, video_dim_t num_pixels) {
	line += x << 2;
	codec_assert(num_pixels > 0);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	codec_assert(!(stride & 3));
	codec_assert(!((uintptr_t)line & 3));
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	do {
		*(uint32_t *)line = (uint32_t)pixel;
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void CC
rectfill32(byte_t *__restrict line, video_coord_t x, size_t stride,
           video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	line += x << 2;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	codec_assert(!(stride & 3));
	codec_assert(!((uintptr_t)line & 3));
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	do {
		memsetl(line, (uint16_t)pixel, size_x);
		line += stride;
	} while (--size_y);
}

#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#define unaligned_linefill16 linefill16
#define unaligned_vertfill16 vertfill16
#define unaligned_rectfill16 rectfill16
#define unaligned_linefill32 linefill32
#define unaligned_vertfill32 vertfill32
#define unaligned_rectfill32 rectfill32
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
PRIVATE NONNULL((1)) void CC
unaligned_linefill16(byte_t *__restrict line, video_coord_t x,
                     video_pixel_t pixel, video_dim_t num_pixels) {
#ifndef __OPTIMIZE_SIZE__
	if (((uintptr_t)line & 1) == 0) {
		linefill16(line, x, pixel, num_pixels);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		union word16 data;
		data.word = (uint16_t)pixel;
		line += x << 1;
		do {
			*line++ = data.bytes[0];
			*line++ = data.bytes[1];
		} while (--num_pixels);
	}
}

PRIVATE NONNULL((1)) void CC
unaligned_vertfill16(byte_t *__restrict line, video_coord_t x, size_t stride,
                     video_pixel_t pixel, video_dim_t num_pixels) {
	line += x << 1;
	codec_assert(num_pixels > 0);
	do {
		UNALIGNED_SET16(line, (uint16_t)pixel);
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void CC
unaligned_rectfill16(byte_t *__restrict line, video_coord_t x, size_t stride,
                     video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	union word16 data;
	data.word = (uint16_t)pixel;
	line += x << 1;
	stride -= size_x << 1;
	do {
		video_dim_t iter_x = size_x;
		do {
			*line++ = data.bytes[0];
			*line++ = data.bytes[1];
		} while (--iter_x);
		line += stride;
	} while (--size_y);
}


PRIVATE NONNULL((1)) void CC
unaligned_linefill32(byte_t *__restrict line, video_coord_t x,
                     video_pixel_t pixel, video_dim_t num_pixels) {
#ifndef __OPTIMIZE_SIZE__
	if (((uintptr_t)line & 3) == 0) {
		linefill32(line, x, pixel, num_pixels);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		union word32 data;
		data.dword = (uint32_t)pixel;
		line += x << 2;
		do {
			*line++ = data.bytes[0];
			*line++ = data.bytes[1];
			*line++ = data.bytes[2];
			*line++ = data.bytes[3];
		} while (--num_pixels);
	}
}

PRIVATE NONNULL((1)) void CC
unaligned_vertfill32(byte_t *__restrict line, video_coord_t x, size_t stride,
                     video_pixel_t pixel, video_dim_t num_pixels) {
	line += x << 2;
	codec_assert(num_pixels > 0);
	do {
		UNALIGNED_SET32(line, (uint32_t)pixel);
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void CC
unaligned_rectfill32(byte_t *__restrict line, video_coord_t x, size_t stride,
                     video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	union word32 data;
	data.dword = (uint32_t)pixel;
	line += x << 2;
	stride -= size_x << 2;
	do {
		video_dim_t iter_x = size_x;
		do {
			*line++ = data.bytes[0];
			*line++ = data.bytes[1];
			*line++ = data.bytes[2];
			*line++ = data.bytes[3];
		} while (--iter_x);
		line += stride;
	} while (--size_y);
}
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */


LOCAL NONNULL((1, 3)) void CC
_rowcopy1_lsb(byte_t *__restrict dst_line, video_coord_t dst_x,
              byte_t const *__restrict src_line, video_coord_t src_x,
              video_dim_t num_pixels) {
	codec_assert(num_pixels > 0);
	dst_line += dst_x / 8;
	src_line += src_x / 8;
	dst_x %= 8;
	src_x %= 8;
	if (dst_x == src_x) {
		/* Same sub-byte offset (can use memcpy for larger areas) */
		if (dst_x != 0) {
			while (dst_x < 8) {
				video_pixel_t pixel;
				pixel = getpixel1_inbyte_lsb(src_line, (shift_t)src_x);
				setpixel1_inbyte_lsb(dst_line, (shift_t)dst_x, pixel);
				++src_x;
				++dst_x;
				--num_pixels;
				if (!num_pixels)
					return;
			}
		}

		/* Directly copy pixel data. */
		codec_assert(num_pixels > 0);
		memcpy(dst_line, src_line, num_pixels / 8);
		src_x += num_pixels & ~(8 - 1);
		dst_x += num_pixels & ~(8 - 1);
		src_x %= 8;
		dst_x %= 8;
		dst_line += num_pixels / 8;
		src_line += num_pixels / 8;
		num_pixels %= 8;
	}
	while (num_pixels) {
		video_pixel_t pixel;
		pixel = getpixel1_inbyte_lsb(src_line, (shift_t)src_x);
		setpixel1_inbyte_lsb(dst_line, (shift_t)dst_x, pixel);
		--num_pixels;
		if (++dst_x >= 8) {
			++dst_line;
			dst_x = 0;
		}
		if (++src_x >= 8) {
			++src_line;
			src_x = 0;
		}
	}
}

LOCAL NONNULL((1, 3)) void CC
_rowcopy1_msb(byte_t *__restrict dst_line, video_coord_t dst_x,
              byte_t const *__restrict src_line, video_coord_t src_x,
              video_dim_t num_pixels) {
	codec_assert(num_pixels > 0);
	dst_line += dst_x / 8;
	src_line += src_x / 8;
	dst_x %= 8;
	src_x %= 8;
	if (dst_x == src_x) {
		/* Same sub-byte offset (can use memcpy for larger areas) */
		if (dst_x != 0) {
			while (dst_x < 8) {
				video_pixel_t pixel;
				pixel = getpixel1_inbyte_msb(src_line, (shift_t)src_x);
				setpixel1_inbyte_msb(dst_line, (shift_t)dst_x, pixel);
				++src_x;
				++dst_x;
				--num_pixels;
				if (!num_pixels)
					return;
			}
		}

		/* Directly copy pixel data. */
		codec_assert(num_pixels > 0);
		memcpy(dst_line, src_line, num_pixels / 8);
		src_x += num_pixels & ~(8 - 1);
		dst_x += num_pixels & ~(8 - 1);
		src_x %= 8;
		dst_x %= 8;
		dst_line += num_pixels / 8;
		src_line += num_pixels / 8;
		num_pixels %= 8;
	}
	while (num_pixels) {
		video_pixel_t pixel;
		pixel = getpixel1_inbyte_msb(src_line, (shift_t)src_x);
		setpixel1_inbyte_msb(dst_line, (shift_t)dst_x, pixel);
		--num_pixels;
		if (++dst_x >= 8) {
			++dst_line;
			dst_x = 0;
		}
		if (++src_x >= 8) {
			++src_line;
			src_x = 0;
		}
	}
}

PRIVATE NONNULL((1, 4)) void CC
rectcopy1_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
              byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
              video_dim_t size_x, video_dim_t size_y) {
	/* TODO: Re-use byte-masks across lines */
	do {
		_rowcopy1_lsb(dst_line, dst_x, src_line, src_x, size_x);
		dst_line += dst_stride;
		src_line += src_stride;
	} while (--size_y);
}

PRIVATE NONNULL((1, 4)) void CC
rectcopy1_msb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
              byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
              video_dim_t size_x, video_dim_t size_y) {
	/* TODO: Re-use byte-masks across lines */
	do {
		_rowcopy1_msb(dst_line, dst_x, src_line, src_x, size_x);
		dst_line += dst_stride;
		src_line += src_stride;
	} while (--size_y);
}



LOCAL NONNULL((1, 3)) void CC
_rowcopy2_lsb(byte_t *__restrict dst_line, video_coord_t dst_x,
              byte_t const *__restrict src_line, video_coord_t src_x,
              video_dim_t num_pixels) {
	codec_assert(num_pixels > 0);
	dst_line += dst_x / 4;
	src_line += src_x / 4;
	dst_x %= 4;
	src_x %= 4;
	if (dst_x == src_x) {
		/* Same sub-byte offset (can use memcpy for larger areas) */
		if (dst_x != 0) {
			while (dst_x < 4) {
				video_pixel_t pixel;
				pixel = getpixel2_inbyte_lsb(src_line, (shift_t)src_x);
				setpixel2_inbyte_lsb(dst_line, (shift_t)dst_x, pixel);
				++src_x;
				++dst_x;
				--num_pixels;
				if (!num_pixels)
					return;
			}
		}

		/* Directly copy pixel data. */
		codec_assert(num_pixels > 0);
		memcpy(dst_line, src_line, num_pixels / 4);
		src_x += num_pixels & ~(4 - 1);
		dst_x += num_pixels & ~(4 - 1);
		src_x %= 4;
		dst_x %= 4;
		dst_line += num_pixels / 4;
		src_line += num_pixels / 4;
		num_pixels %= 4;
	}
	while (num_pixels) {
		video_pixel_t pixel;
		pixel = getpixel2_inbyte_lsb(src_line, (shift_t)src_x);
		setpixel2_inbyte_lsb(dst_line, (shift_t)dst_x, pixel);
		--num_pixels;
		if (++dst_x >= 4) {
			++dst_line;
			dst_x = 0;
		}
		if (++src_x >= 4) {
			++src_line;
			src_x = 0;
		}
	}
}

LOCAL NONNULL((1, 3)) void CC
_rowcopy2_msb(byte_t *__restrict dst_line, video_coord_t dst_x,
              byte_t const *__restrict src_line, video_coord_t src_x,
              video_dim_t num_pixels) {
	codec_assert(num_pixels > 0);
	dst_line += dst_x / 4;
	src_line += src_x / 4;
	dst_x %= 4;
	src_x %= 4;
	if (dst_x == src_x) {
		/* Same sub-byte offset (can use memcpy for larger areas) */
		if (dst_x != 0) {
			while (dst_x < 4) {
				video_pixel_t pixel;
				pixel = getpixel2_inbyte_msb(src_line, (shift_t)src_x);
				setpixel2_inbyte_msb(dst_line, (shift_t)dst_x, pixel);
				++src_x;
				++dst_x;
				--num_pixels;
				if (!num_pixels)
					return;
			}
		}

		/* Directly copy pixel data. */
		codec_assert(num_pixels > 0);
		memcpy(dst_line, src_line, num_pixels / 4);
		src_x += num_pixels & ~(4 - 1);
		dst_x += num_pixels & ~(4 - 1);
		src_x %= 4;
		dst_x %= 4;
		dst_line += num_pixels / 4;
		src_line += num_pixels / 4;
		num_pixels %= 4;
	}
	while (num_pixels) {
		video_pixel_t pixel;
		pixel = getpixel2_inbyte_msb(src_line, (shift_t)src_x);
		setpixel2_inbyte_msb(dst_line, (shift_t)dst_x, pixel);
		--num_pixels;
		if (++dst_x >= 4) {
			++dst_line;
			dst_x = 0;
		}
		if (++src_x >= 4) {
			++src_line;
			src_x = 0;
		}
	}
}

PRIVATE NONNULL((1, 4)) void CC
rectcopy2_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
              byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
              video_dim_t size_x, video_dim_t size_y) {
	/* TODO: Re-use byte-masks across lines */
	do {
		_rowcopy2_lsb(dst_line, dst_x, src_line, src_x, size_x);
		dst_line += dst_stride;
		src_line += src_stride;
	} while (--size_y);
}

PRIVATE NONNULL((1, 4)) void CC
rectcopy2_msb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
              byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
              video_dim_t size_x, video_dim_t size_y) {
	/* TODO: Re-use byte-masks across lines */
	do {
		_rowcopy2_msb(dst_line, dst_x, src_line, src_x, size_x);
		dst_line += dst_stride;
		src_line += src_stride;
	} while (--size_y);
}


LOCAL NONNULL((1, 3)) void CC
_rowcopy4_lsb(byte_t *__restrict dst_line, video_coord_t dst_x,
              byte_t const *__restrict src_line, video_coord_t src_x,
              video_dim_t num_pixels) {
	codec_assert(num_pixels > 0);
	dst_line += dst_x / 2;
	src_line += src_x / 2;
	dst_x %= 2;
	src_x %= 2;
	if (dst_x == src_x) {
		/* Same sub-byte offset (can use memcpy for larger areas) */
		if (dst_x != 0) {
			video_pixel_t pixel;
			assert(dst_x == 1);
			pixel = getpixel4_inbyte_lsb(src_line, (shift_t)src_x);
			setpixel4_inbyte_lsb(dst_line, (shift_t)dst_x, pixel);
			++src_x;
			++dst_x;
			--num_pixels;
			if (!num_pixels)
				return;
		}

		/* Directly copy pixel data. */
		codec_assert(num_pixels > 0);
		memcpy(dst_line, src_line, num_pixels / 2);
		src_x += num_pixels & ~(2 - 1);
		dst_x += num_pixels & ~(2 - 1);
		src_x %= 2;
		dst_x %= 2;
		dst_line += num_pixels / 2;
		src_line += num_pixels / 2;
		num_pixels %= 2;
	}
	while (num_pixels) {
		video_pixel_t pixel;
		pixel = getpixel4_inbyte_lsb(src_line, (shift_t)src_x);
		setpixel4_inbyte_lsb(dst_line, (shift_t)dst_x, pixel);
		--num_pixels;
		if (++dst_x >= 2) {
			++dst_line;
			dst_x = 0;
		}
		if (++src_x >= 2) {
			++src_line;
			src_x = 0;
		}
	}
}

LOCAL NONNULL((1, 3)) void CC
_rowcopy4_msb(byte_t *__restrict dst_line, video_coord_t dst_x,
              byte_t const *__restrict src_line, video_coord_t src_x,
              video_dim_t num_pixels) {
	codec_assert(num_pixels > 0);
	dst_line += dst_x / 2;
	src_line += src_x / 2;
	dst_x %= 2;
	src_x %= 2;
	if (dst_x == src_x) {
		/* Same sub-byte offset (can use memcpy for larger areas) */
		if (dst_x != 0) {
			video_pixel_t pixel;
			assert(dst_x == 1);
			pixel = getpixel4_inbyte_msb(src_line, (shift_t)src_x);
			setpixel4_inbyte_msb(dst_line, (shift_t)dst_x, pixel);
			++src_x;
			++dst_x;
			--num_pixels;
			if (!num_pixels)
				return;
		}

		/* Directly copy pixel data. */
		codec_assert(num_pixels > 0);
		memcpy(dst_line, src_line, num_pixels / 2);
		src_x += num_pixels & ~(2 - 1);
		dst_x += num_pixels & ~(2 - 1);
		src_x %= 2;
		dst_x %= 2;
		dst_line += num_pixels / 2;
		src_line += num_pixels / 2;
		num_pixels %= 2;
	}
	while (num_pixels) {
		video_pixel_t pixel;
		pixel = getpixel4_inbyte_msb(src_line, (shift_t)src_x);
		setpixel4_inbyte_msb(dst_line, (shift_t)dst_x, pixel);
		--num_pixels;
		if (++dst_x >= 2) {
			++dst_line;
			dst_x = 0;
		}
		if (++src_x >= 2) {
			++src_line;
			src_x = 0;
		}
	}
}

PRIVATE NONNULL((1, 4)) void CC
rectcopy4_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
              byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
              video_dim_t size_x, video_dim_t size_y) {
	/* TODO: Re-use byte-masks across lines */
	do {
		_rowcopy4_lsb(dst_line, dst_x, src_line, src_x, size_x);
		dst_line += dst_stride;
		src_line += src_stride;
	} while (--size_y);
}

PRIVATE NONNULL((1, 4)) void CC
rectcopy4_msb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
              byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
              video_dim_t size_x, video_dim_t size_y) {
	/* TODO: Re-use byte-masks across lines */
	do {
		_rowcopy4_msb(dst_line, dst_x, src_line, src_x, size_x);
		dst_line += dst_stride;
		src_line += src_stride;
	} while (--size_y);
}



PRIVATE NONNULL((1)) void CC
linefill1_lsb(byte_t *__restrict line, video_coord_t dst_x,
              video_pixel_t pixel, video_dim_t num_pixels) {
	codec_assert(num_pixels > 0);
	line += dst_x / 8;
	dst_x %= 8;
	if (dst_x & 7) {
		do {
			setpixel1_inbyte_lsb(line, dst_x, pixel);
			--num_pixels;
			if (!num_pixels)
				return;
		} while ((++dst_x) & 7);
		++line;
	}
	codec_assert(num_pixels > 0);
	line = mempsetb(line,
	                    0xff * (pixel & 0x1),
	                    num_pixels / 4);
	if (num_pixels & 7) {
		num_pixels &= 7;
		for (dst_x = 0; dst_x < num_pixels; ++dst_x)
			setpixel1_inbyte_lsb(line, dst_x, pixel);
	}
}

PRIVATE NONNULL((1)) void CC
linefill1_msb(byte_t *__restrict line, video_coord_t dst_x,
              video_pixel_t pixel, video_dim_t num_pixels) {
	codec_assert(num_pixels > 0);
	line += dst_x / 8;
	dst_x %= 8;
	if (dst_x & 7) {
		do {
			setpixel1_inbyte_msb(line, dst_x, pixel);
			--num_pixels;
			if (!num_pixels)
				return;
		} while ((++dst_x) & 7);
		++line;
	}
	codec_assert(num_pixels > 0);
	line = mempsetb(line, 0xff * (pixel & 0x1), num_pixels / 4);
	if (num_pixels & 7) {
		num_pixels &= 7;
		for (dst_x = 0; dst_x < num_pixels; ++dst_x)
			setpixel1_inbyte_msb(line, dst_x, pixel);
	}
}

PRIVATE NONNULL((1)) void CC
vertfill1_lsb(byte_t *__restrict line, video_coord_t x, size_t stride,
              video_pixel_t pixel, video_dim_t num_pixels) {
	/* TODO: Re-use byte-masks across lines */
	do {
		setpixel1_lsb(line, x, pixel);
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void CC
vertfill1_msb(byte_t *__restrict line, video_coord_t x, size_t stride,
              video_pixel_t pixel, video_dim_t num_pixels) {
	/* TODO: Re-use byte-masks across lines */
	do {
		setpixel1_msb(line, x, pixel);
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void CC
rectfill1_lsb(byte_t *__restrict line, video_coord_t x, size_t stride,
              video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	/* TODO: Re-use byte-masks across lines */
	do {
		linefill1_lsb(line, x, pixel, size_x);
		line += stride;
	} while (--size_y);
}

PRIVATE NONNULL((1)) void CC
rectfill1_msb(byte_t *__restrict line, video_coord_t x, size_t stride,
              video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	/* TODO: Re-use byte-masks across lines */
	do {
		linefill1_msb(line, x, pixel, size_x);
		line += stride;
	} while (--size_y);
}


PRIVATE NONNULL((1)) void CC
linefill2_lsb(byte_t *__restrict line, video_coord_t dst_x,
              video_pixel_t pixel, video_dim_t num_pixels) {
	codec_assert(num_pixels > 0);
	line += dst_x / 4;
	dst_x %= 4;
	if (dst_x & 3) {
		do {
			setpixel2_inbyte_lsb(line, dst_x, pixel);
			--num_pixels;
			if (!num_pixels)
				return;
		} while ((++dst_x) & 3);
		++line;
	}
	codec_assert(num_pixels > 0);
	line = mempsetb(line, 0x55 * (pixel & 0x3), num_pixels / 4);
	if (num_pixels & 3) {
		num_pixels &= 3;
		for (dst_x = 0; dst_x < num_pixels; ++dst_x)
			setpixel2_inbyte_lsb(line, dst_x, pixel);
	}
}

PRIVATE NONNULL((1)) void CC
linefill2_msb(byte_t *__restrict line, video_coord_t dst_x,
              video_pixel_t pixel, video_dim_t num_pixels) {
	codec_assert(num_pixels > 0);
	line += dst_x / 4;
	dst_x %= 4;
	if (dst_x & 3) {
		do {
			setpixel2_inbyte_msb(line, dst_x, pixel);
			--num_pixels;
			if (!num_pixels)
				return;
		} while ((++dst_x) & 3);
		++line;
	}
	codec_assert(num_pixels > 0);
	line = mempsetb(line,
	                    0x55 * (pixel & 0x3),
	                    num_pixels / 4);
	if (num_pixels & 3) {
		num_pixels &= 3;
		for (dst_x = 0; dst_x < num_pixels; ++dst_x)
			setpixel2_inbyte_msb(line, dst_x, pixel);
	}
}

PRIVATE NONNULL((1)) void CC
vertfill2_lsb(byte_t *__restrict line, video_coord_t x, size_t stride,
              video_pixel_t pixel, video_dim_t num_pixels) {
	/* TODO: Re-use byte-masks across lines */
	do {
		setpixel2_lsb(line, x, pixel);
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void CC
vertfill2_msb(byte_t *__restrict line, video_coord_t x, size_t stride,
              video_pixel_t pixel, video_dim_t num_pixels) {
	/* TODO: Re-use byte-masks across lines */
	do {
		setpixel2_msb(line, x, pixel);
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void CC
rectfill2_lsb(byte_t *__restrict line, video_coord_t x, size_t stride,
              video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	/* TODO: Re-use byte-masks across lines */
	do {
		linefill2_lsb(line, x, pixel, size_x);
		line += stride;
	} while (--size_y);
}

PRIVATE NONNULL((1)) void CC
rectfill2_msb(byte_t *__restrict line, video_coord_t x, size_t stride,
              video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	/* TODO: Re-use byte-masks across lines */
	do {
		linefill2_msb(line, x, pixel, size_x);
		line += stride;
	} while (--size_y);
}


PRIVATE NONNULL((1)) void CC
linefill4_lsb(byte_t *__restrict line, video_coord_t dst_x,
              video_pixel_t pixel, video_dim_t num_pixels) {
	codec_assert(num_pixels > 0);
	line += dst_x / 2;
	dst_x %= 2;
	if (dst_x & 1) {
		setpixel4_inbyte_lsb(line, 1, pixel);
		++line;
		--num_pixels;
		if (!num_pixels)
			return;
	}
	codec_assert(num_pixels > 0);
	line = mempsetb(line, pixel | (pixel << 4), num_pixels / 2);
	if (num_pixels & 1) {
		setpixel4_inbyte_lsb(line, 0, pixel);
	}
}

PRIVATE NONNULL((1)) void CC
linefill4_msb(byte_t *__restrict line, video_coord_t dst_x,
              video_pixel_t pixel, video_dim_t num_pixels) {
	codec_assert(num_pixels > 0);
	line += dst_x / 2;
	dst_x %= 2;
	if (dst_x & 1) {
		setpixel4_inbyte_msb(line, 1, pixel);
		++line;
		--num_pixels;
		if (!num_pixels)
			return;
	}
	codec_assert(num_pixels > 0);
	line = mempsetb(line, pixel | (pixel << 4), num_pixels / 2);
	if (num_pixels & 1) {
		setpixel4_inbyte_msb(line, 0, pixel);
	}
}

PRIVATE NONNULL((1)) void CC
vertfill4_lsb(byte_t *__restrict line, video_coord_t x, size_t stride,
              video_pixel_t pixel, video_dim_t num_pixels) {
	/* TODO: Re-use byte-masks across lines */
	do {
		setpixel4_lsb(line, x, pixel);
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void CC
vertfill4_msb(byte_t *__restrict line, video_coord_t x, size_t stride,
              video_pixel_t pixel, video_dim_t num_pixels) {
	/* TODO: Re-use byte-masks across lines */
	do {
		setpixel4_msb(line, x, pixel);
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void CC
rectfill4_lsb(byte_t *__restrict line, video_coord_t x, size_t stride,
              video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	/* TODO: Re-use byte-masks across lines */
	do {
		linefill4_lsb(line, x, pixel, size_x);
		line += stride;
	} while (--size_y);
}

PRIVATE NONNULL((1)) void CC
rectfill4_msb(byte_t *__restrict line, video_coord_t x, size_t stride,
              video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	/* TODO: Re-use byte-masks across lines */
	do {
		linefill4_msb(line, x, pixel, size_x);
		line += stride;
	} while (--size_y);
}






















/************************************************************************/
/* COLOR CONVERSION                                                     */
/************************************************************************/


union color_data {
	video_color_t color;
	struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		uint8_t a;
		uint8_t b;
		uint8_t g;
		uint8_t r;
#endif /* __BYTE_ORDER__ == ... */
	};
};


#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define BIGENDIAN_SHL(x, n) ((x) >> (n))
#define BIGENDIAN_SHR(x, n) ((x) << (n))
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define BIGENDIAN_SHL(x, n) ((x) << (n))
#define BIGENDIAN_SHR(x, n) ((x) >> (n))
#endif


#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define PIXEL_RD0(pixel)         ((pixel) & 0xff)
#define PIXEL_RD1(pixel)         (((pixel) >> 8) & 0xff)
#define PIXEL_RD2(pixel)         (((pixel) >> 16) & 0xff)
#define PIXEL_RD3(pixel)         (((pixel) >> 24) & 0xff)
#define PIXEL_WR0(pixel, byte)   ((pixel) = ((pixel) & ~UINT32_C(0x000000ff)) | (byte))
#define PIXEL_WR1(pixel, byte)   ((pixel) = ((pixel) & ~UINT32_C(0x0000ff00)) | ((byte) << 8))
#define PIXEL_WR2(pixel, byte)   ((pixel) = ((pixel) & ~UINT32_C(0x00ff0000)) | ((byte) << 16))
#define PIXEL_WR3(pixel, byte)   ((pixel) = ((pixel) & ~UINT32_C(0xff000000)) | ((byte) << 24))
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define PIXEL_RD3(pixel)         ((pixel) & 0xff)
#define PIXEL_RD2(pixel)         (((pixel) >> 8) & 0xff)
#define PIXEL_RD1(pixel)         (((pixel) >> 16) & 0xff)
#define PIXEL_RD0(pixel)         (((pixel) >> 24) & 0xff)
#define PIXEL_WR3(pixel, byte)   ((pixel) = ((pixel) & ~UINT32_C(0x000000ff)) | (byte))
#define PIXEL_WR2(pixel, byte)   ((pixel) = ((pixel) & ~UINT32_C(0x0000ff00)) | ((byte) << 8))
#define PIXEL_WR1(pixel, byte)   ((pixel) = ((pixel) & ~UINT32_C(0x00ff0000)) | ((byte) << 16))
#define PIXEL_WR0(pixel, byte)   ((pixel) = ((pixel) & ~UINT32_C(0xff000000)) | ((byte) << 24))
#endif /* __BYTE_ORDER__ == ... */


/* Shift "chan" left "n" times, populating those "n" bits with copies of "chan & 1" */
LOCAL ATTR_CONST video_channel_t CC
repeat_lsb(video_channel_t chan, shift_t n) {
#if 1 /* Same as other impl, but without if-statements */
	chan = (chan << n) |
	       ((video_channel_t)(chan & 1) *
	        (((video_channel_t)1 << n) - 1));
#else
	if (n) {
		if (chan & 1) {
			chan <<= n;
			chan |= ((video_channel_t)1 << n) - 1;
		} else {
			chan <<= n;
		}
	}
#endif
	return chan;
}



#define identity_pixel2color identity_color2pixel
INTERN ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
identity_color2pixel(struct video_format const *__restrict UNUSED(format),
                     video_color_t value) {
	return value;
}

INTERN ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
rgbx8888_pixel2color(struct video_format const *__restrict UNUSED(format),
                     video_pixel_t pixel) {
	return pixel | VIDEO_COLOR_ALPHA_MASK;
}

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define rgb888_pixel2color rgbx8888_pixel2color
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
rgb888_pixel2color(struct video_format const *__restrict UNUSED(format),
                   video_pixel_t pixel) {
	return (pixel << 8) | VIDEO_COLOR_ALPHA_MASK;
}
#endif /* __BYTE_ORDER__ == ... */

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define rgb888_color2pixel identity_color2pixel
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
rgb888_color2pixel(struct video_format const *__restrict UNUSED(format),
                   video_color_t color) {
	return color >> 8;
}
#endif /* __BYTE_ORDER__ == ... */



PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
argb8888_pixel2color(struct video_format const *__restrict UNUSED(format),
                     video_pixel_t pixel) {
	return BIGENDIAN_SHL((uint32_t)pixel, 8) | BIGENDIAN_SHR((uint32_t)pixel, 24);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
argb8888_color2pixel(struct video_format const *__restrict UNUSED(format),
                     video_color_t color) {
	return BIGENDIAN_SHR((uint32_t)color, 8) | BIGENDIAN_SHL((uint32_t)color, 24);
}


PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
xrgb8888_pixel2color(struct video_format const *__restrict UNUSED(format),
                     video_pixel_t pixel) {
	return BIGENDIAN_SHL((uint32_t)pixel, 8) | VIDEO_COLOR_ALPHA_MASK;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
xrgb8888_color2pixel(struct video_format const *__restrict UNUSED(format),
                     video_color_t color) {
	return BIGENDIAN_SHR((uint32_t)color, 8);
}


PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
abgr8888_pixel2color(struct video_format const *__restrict UNUSED(format),
                     video_pixel_t pixel) {
	union color_data result;
	result.a = PIXEL_RD0(pixel);
	result.r = PIXEL_RD1(pixel);
	result.g = PIXEL_RD2(pixel);
	result.b = PIXEL_RD3(pixel);
	return result.color;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
abgr8888_color2pixel(struct video_format const *__restrict UNUSED(format),
                     video_color_t color) {
	union color_data data;
	video_pixel_t result = 0;
	data.color = color;
	PIXEL_WR0(result, data.a);
	PIXEL_WR1(result, data.b);
	PIXEL_WR2(result, data.g);
	PIXEL_WR3(result, data.r);
	return result;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
xbgr8888_pixel2color(struct video_format const *__restrict UNUSED(format),
                     video_pixel_t pixel) {
	union color_data result;
	result.a = 0xff;
	result.b = PIXEL_RD1(pixel);
	result.g = PIXEL_RD2(pixel);
	result.r = PIXEL_RD3(pixel);
	return result.color;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
xbgr8888_color2pixel(struct video_format const *__restrict UNUSED(format),
                     video_color_t color) {
	union color_data data;
	video_pixel_t result = 0;
	data.color = color;
	PIXEL_WR1(result, data.b);
	PIXEL_WR2(result, data.g);
	PIXEL_WR3(result, data.r);
	return result;
}


PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
bgra8888_pixel2color(struct video_format const *__restrict UNUSED(format),
                     video_pixel_t pixel) {
	union color_data result;
	result.b = PIXEL_RD0(pixel);
	result.g = PIXEL_RD1(pixel);
	result.r = PIXEL_RD2(pixel);
	result.a = PIXEL_RD3(pixel);
	return result.color;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
bgra8888_color2pixel(struct video_format const *__restrict UNUSED(format),
                     video_color_t color) {
	union color_data data;
	video_pixel_t result = 0;
	data.color = color;
	PIXEL_WR0(result, data.b);
	PIXEL_WR1(result, data.g);
	PIXEL_WR2(result, data.r);
	PIXEL_WR3(result, data.a);
	return result;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
bgrx8888_pixel2color(struct video_format const *__restrict UNUSED(format),
                     video_pixel_t pixel) {
	union color_data result;
	result.b = PIXEL_RD0(pixel);
	result.g = PIXEL_RD1(pixel);
	result.r = PIXEL_RD2(pixel);
	result.a = 0xff;
	return result.color;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
bgrx8888_color2pixel(struct video_format const *__restrict UNUSED(format),
                     video_color_t color) {
	union color_data data;
	video_pixel_t result = 0;
	data.color = color;
	PIXEL_WR0(result, data.b);
	PIXEL_WR1(result, data.g);
	PIXEL_WR2(result, data.r);
	return result;
}


#define bgr888_pixel2color bgrx8888_pixel2color
#define bgr888_color2pixel bgrx8888_color2pixel

PRIVATE video_color_t const l3_to_color[8] = {
/*[[[deemon
for (local x: [:8]) {
	local chan = (((x * 255) + (7 / 2)) / 7);
	local chanH = chan.hex(2);
	print("	[", x, "] = VIDEO_COLOR_RGBA(", chanH, ", ", chanH, ", ", chanH, ", 0), /" "* ", chan.bin(8), " *" "/");
}
]]]*/
	[0] = VIDEO_COLOR_RGBA(0x00, 0x00, 0x00, 0), /* 0b00000000 */
	[1] = VIDEO_COLOR_RGBA(0x24, 0x24, 0x24, 0), /* 0b00100100 */
	[2] = VIDEO_COLOR_RGBA(0x49, 0x49, 0x49, 0), /* 0b01001001 */
	[3] = VIDEO_COLOR_RGBA(0x6d, 0x6d, 0x6d, 0), /* 0b01101101 */
	[4] = VIDEO_COLOR_RGBA(0x92, 0x92, 0x92, 0), /* 0b10010010 */
	[5] = VIDEO_COLOR_RGBA(0xb6, 0xb6, 0xb6, 0), /* 0b10110110 */
	[6] = VIDEO_COLOR_RGBA(0xdb, 0xdb, 0xdb, 0), /* 0b11011011 */
	[7] = VIDEO_COLOR_RGBA(0xff, 0xff, 0xff, 0), /* 0b11111111 */
/*[[[end]]]*/
};

#ifdef __OPTIMIZE_SIZE__
#define l7_to_color(x)                                       \
	(((video_color_t)0x01010101 & (VIDEO_COLOR_RED_MASK |    \
	                               VIDEO_COLOR_GREEN_MASK |  \
	                               VIDEO_COLOR_BLUE_MASK)) * \
	 (((x) << 1) | ((x) & 1)))
#else /* __OPTIMIZE_SIZE__ */
#define l7_to_color(x) l7_to_color[x]
PRIVATE video_color_t const l7_to_color[128] = {
/*[[[deemon
for (local x: [:128]) {
	local chan = (((x * 255) + (127 / 2)) / 127);
	local chanH = chan.hex(2);
	print("	[", x.hex(2), "] = VIDEO_COLOR_RGBA(", chanH, ", ", chanH, ", ", chanH, ", 0), /" "* 0b", chan.bin(8), " *" "/");
}
]]]*/
	[0x00] = VIDEO_COLOR_RGBA(0x00, 0x00, 0x00, 0), /* 0b0b00000000 */
	[0x01] = VIDEO_COLOR_RGBA(0x02, 0x02, 0x02, 0), /* 0b0b00000010 */
	[0x02] = VIDEO_COLOR_RGBA(0x04, 0x04, 0x04, 0), /* 0b0b00000100 */
	[0x03] = VIDEO_COLOR_RGBA(0x06, 0x06, 0x06, 0), /* 0b0b00000110 */
	[0x04] = VIDEO_COLOR_RGBA(0x08, 0x08, 0x08, 0), /* 0b0b00001000 */
	[0x05] = VIDEO_COLOR_RGBA(0x0a, 0x0a, 0x0a, 0), /* 0b0b00001010 */
	[0x06] = VIDEO_COLOR_RGBA(0x0c, 0x0c, 0x0c, 0), /* 0b0b00001100 */
	[0x07] = VIDEO_COLOR_RGBA(0x0e, 0x0e, 0x0e, 0), /* 0b0b00001110 */
	[0x08] = VIDEO_COLOR_RGBA(0x10, 0x10, 0x10, 0), /* 0b0b00010000 */
	[0x09] = VIDEO_COLOR_RGBA(0x12, 0x12, 0x12, 0), /* 0b0b00010010 */
	[0x0a] = VIDEO_COLOR_RGBA(0x14, 0x14, 0x14, 0), /* 0b0b00010100 */
	[0x0b] = VIDEO_COLOR_RGBA(0x16, 0x16, 0x16, 0), /* 0b0b00010110 */
	[0x0c] = VIDEO_COLOR_RGBA(0x18, 0x18, 0x18, 0), /* 0b0b00011000 */
	[0x0d] = VIDEO_COLOR_RGBA(0x1a, 0x1a, 0x1a, 0), /* 0b0b00011010 */
	[0x0e] = VIDEO_COLOR_RGBA(0x1c, 0x1c, 0x1c, 0), /* 0b0b00011100 */
	[0x0f] = VIDEO_COLOR_RGBA(0x1e, 0x1e, 0x1e, 0), /* 0b0b00011110 */
	[0x10] = VIDEO_COLOR_RGBA(0x20, 0x20, 0x20, 0), /* 0b0b00100000 */
	[0x11] = VIDEO_COLOR_RGBA(0x22, 0x22, 0x22, 0), /* 0b0b00100010 */
	[0x12] = VIDEO_COLOR_RGBA(0x24, 0x24, 0x24, 0), /* 0b0b00100100 */
	[0x13] = VIDEO_COLOR_RGBA(0x26, 0x26, 0x26, 0), /* 0b0b00100110 */
	[0x14] = VIDEO_COLOR_RGBA(0x28, 0x28, 0x28, 0), /* 0b0b00101000 */
	[0x15] = VIDEO_COLOR_RGBA(0x2a, 0x2a, 0x2a, 0), /* 0b0b00101010 */
	[0x16] = VIDEO_COLOR_RGBA(0x2c, 0x2c, 0x2c, 0), /* 0b0b00101100 */
	[0x17] = VIDEO_COLOR_RGBA(0x2e, 0x2e, 0x2e, 0), /* 0b0b00101110 */
	[0x18] = VIDEO_COLOR_RGBA(0x30, 0x30, 0x30, 0), /* 0b0b00110000 */
	[0x19] = VIDEO_COLOR_RGBA(0x32, 0x32, 0x32, 0), /* 0b0b00110010 */
	[0x1a] = VIDEO_COLOR_RGBA(0x34, 0x34, 0x34, 0), /* 0b0b00110100 */
	[0x1b] = VIDEO_COLOR_RGBA(0x36, 0x36, 0x36, 0), /* 0b0b00110110 */
	[0x1c] = VIDEO_COLOR_RGBA(0x38, 0x38, 0x38, 0), /* 0b0b00111000 */
	[0x1d] = VIDEO_COLOR_RGBA(0x3a, 0x3a, 0x3a, 0), /* 0b0b00111010 */
	[0x1e] = VIDEO_COLOR_RGBA(0x3c, 0x3c, 0x3c, 0), /* 0b0b00111100 */
	[0x1f] = VIDEO_COLOR_RGBA(0x3e, 0x3e, 0x3e, 0), /* 0b0b00111110 */
	[0x20] = VIDEO_COLOR_RGBA(0x40, 0x40, 0x40, 0), /* 0b0b01000000 */
	[0x21] = VIDEO_COLOR_RGBA(0x42, 0x42, 0x42, 0), /* 0b0b01000010 */
	[0x22] = VIDEO_COLOR_RGBA(0x44, 0x44, 0x44, 0), /* 0b0b01000100 */
	[0x23] = VIDEO_COLOR_RGBA(0x46, 0x46, 0x46, 0), /* 0b0b01000110 */
	[0x24] = VIDEO_COLOR_RGBA(0x48, 0x48, 0x48, 0), /* 0b0b01001000 */
	[0x25] = VIDEO_COLOR_RGBA(0x4a, 0x4a, 0x4a, 0), /* 0b0b01001010 */
	[0x26] = VIDEO_COLOR_RGBA(0x4c, 0x4c, 0x4c, 0), /* 0b0b01001100 */
	[0x27] = VIDEO_COLOR_RGBA(0x4e, 0x4e, 0x4e, 0), /* 0b0b01001110 */
	[0x28] = VIDEO_COLOR_RGBA(0x50, 0x50, 0x50, 0), /* 0b0b01010000 */
	[0x29] = VIDEO_COLOR_RGBA(0x52, 0x52, 0x52, 0), /* 0b0b01010010 */
	[0x2a] = VIDEO_COLOR_RGBA(0x54, 0x54, 0x54, 0), /* 0b0b01010100 */
	[0x2b] = VIDEO_COLOR_RGBA(0x56, 0x56, 0x56, 0), /* 0b0b01010110 */
	[0x2c] = VIDEO_COLOR_RGBA(0x58, 0x58, 0x58, 0), /* 0b0b01011000 */
	[0x2d] = VIDEO_COLOR_RGBA(0x5a, 0x5a, 0x5a, 0), /* 0b0b01011010 */
	[0x2e] = VIDEO_COLOR_RGBA(0x5c, 0x5c, 0x5c, 0), /* 0b0b01011100 */
	[0x2f] = VIDEO_COLOR_RGBA(0x5e, 0x5e, 0x5e, 0), /* 0b0b01011110 */
	[0x30] = VIDEO_COLOR_RGBA(0x60, 0x60, 0x60, 0), /* 0b0b01100000 */
	[0x31] = VIDEO_COLOR_RGBA(0x62, 0x62, 0x62, 0), /* 0b0b01100010 */
	[0x32] = VIDEO_COLOR_RGBA(0x64, 0x64, 0x64, 0), /* 0b0b01100100 */
	[0x33] = VIDEO_COLOR_RGBA(0x66, 0x66, 0x66, 0), /* 0b0b01100110 */
	[0x34] = VIDEO_COLOR_RGBA(0x68, 0x68, 0x68, 0), /* 0b0b01101000 */
	[0x35] = VIDEO_COLOR_RGBA(0x6a, 0x6a, 0x6a, 0), /* 0b0b01101010 */
	[0x36] = VIDEO_COLOR_RGBA(0x6c, 0x6c, 0x6c, 0), /* 0b0b01101100 */
	[0x37] = VIDEO_COLOR_RGBA(0x6e, 0x6e, 0x6e, 0), /* 0b0b01101110 */
	[0x38] = VIDEO_COLOR_RGBA(0x70, 0x70, 0x70, 0), /* 0b0b01110000 */
	[0x39] = VIDEO_COLOR_RGBA(0x72, 0x72, 0x72, 0), /* 0b0b01110010 */
	[0x3a] = VIDEO_COLOR_RGBA(0x74, 0x74, 0x74, 0), /* 0b0b01110100 */
	[0x3b] = VIDEO_COLOR_RGBA(0x76, 0x76, 0x76, 0), /* 0b0b01110110 */
	[0x3c] = VIDEO_COLOR_RGBA(0x78, 0x78, 0x78, 0), /* 0b0b01111000 */
	[0x3d] = VIDEO_COLOR_RGBA(0x7a, 0x7a, 0x7a, 0), /* 0b0b01111010 */
	[0x3e] = VIDEO_COLOR_RGBA(0x7c, 0x7c, 0x7c, 0), /* 0b0b01111100 */
	[0x3f] = VIDEO_COLOR_RGBA(0x7e, 0x7e, 0x7e, 0), /* 0b0b01111110 */
	[0x40] = VIDEO_COLOR_RGBA(0x81, 0x81, 0x81, 0), /* 0b0b10000001 */
	[0x41] = VIDEO_COLOR_RGBA(0x83, 0x83, 0x83, 0), /* 0b0b10000011 */
	[0x42] = VIDEO_COLOR_RGBA(0x85, 0x85, 0x85, 0), /* 0b0b10000101 */
	[0x43] = VIDEO_COLOR_RGBA(0x87, 0x87, 0x87, 0), /* 0b0b10000111 */
	[0x44] = VIDEO_COLOR_RGBA(0x89, 0x89, 0x89, 0), /* 0b0b10001001 */
	[0x45] = VIDEO_COLOR_RGBA(0x8b, 0x8b, 0x8b, 0), /* 0b0b10001011 */
	[0x46] = VIDEO_COLOR_RGBA(0x8d, 0x8d, 0x8d, 0), /* 0b0b10001101 */
	[0x47] = VIDEO_COLOR_RGBA(0x8f, 0x8f, 0x8f, 0), /* 0b0b10001111 */
	[0x48] = VIDEO_COLOR_RGBA(0x91, 0x91, 0x91, 0), /* 0b0b10010001 */
	[0x49] = VIDEO_COLOR_RGBA(0x93, 0x93, 0x93, 0), /* 0b0b10010011 */
	[0x4a] = VIDEO_COLOR_RGBA(0x95, 0x95, 0x95, 0), /* 0b0b10010101 */
	[0x4b] = VIDEO_COLOR_RGBA(0x97, 0x97, 0x97, 0), /* 0b0b10010111 */
	[0x4c] = VIDEO_COLOR_RGBA(0x99, 0x99, 0x99, 0), /* 0b0b10011001 */
	[0x4d] = VIDEO_COLOR_RGBA(0x9b, 0x9b, 0x9b, 0), /* 0b0b10011011 */
	[0x4e] = VIDEO_COLOR_RGBA(0x9d, 0x9d, 0x9d, 0), /* 0b0b10011101 */
	[0x4f] = VIDEO_COLOR_RGBA(0x9f, 0x9f, 0x9f, 0), /* 0b0b10011111 */
	[0x50] = VIDEO_COLOR_RGBA(0xa1, 0xa1, 0xa1, 0), /* 0b0b10100001 */
	[0x51] = VIDEO_COLOR_RGBA(0xa3, 0xa3, 0xa3, 0), /* 0b0b10100011 */
	[0x52] = VIDEO_COLOR_RGBA(0xa5, 0xa5, 0xa5, 0), /* 0b0b10100101 */
	[0x53] = VIDEO_COLOR_RGBA(0xa7, 0xa7, 0xa7, 0), /* 0b0b10100111 */
	[0x54] = VIDEO_COLOR_RGBA(0xa9, 0xa9, 0xa9, 0), /* 0b0b10101001 */
	[0x55] = VIDEO_COLOR_RGBA(0xab, 0xab, 0xab, 0), /* 0b0b10101011 */
	[0x56] = VIDEO_COLOR_RGBA(0xad, 0xad, 0xad, 0), /* 0b0b10101101 */
	[0x57] = VIDEO_COLOR_RGBA(0xaf, 0xaf, 0xaf, 0), /* 0b0b10101111 */
	[0x58] = VIDEO_COLOR_RGBA(0xb1, 0xb1, 0xb1, 0), /* 0b0b10110001 */
	[0x59] = VIDEO_COLOR_RGBA(0xb3, 0xb3, 0xb3, 0), /* 0b0b10110011 */
	[0x5a] = VIDEO_COLOR_RGBA(0xb5, 0xb5, 0xb5, 0), /* 0b0b10110101 */
	[0x5b] = VIDEO_COLOR_RGBA(0xb7, 0xb7, 0xb7, 0), /* 0b0b10110111 */
	[0x5c] = VIDEO_COLOR_RGBA(0xb9, 0xb9, 0xb9, 0), /* 0b0b10111001 */
	[0x5d] = VIDEO_COLOR_RGBA(0xbb, 0xbb, 0xbb, 0), /* 0b0b10111011 */
	[0x5e] = VIDEO_COLOR_RGBA(0xbd, 0xbd, 0xbd, 0), /* 0b0b10111101 */
	[0x5f] = VIDEO_COLOR_RGBA(0xbf, 0xbf, 0xbf, 0), /* 0b0b10111111 */
	[0x60] = VIDEO_COLOR_RGBA(0xc1, 0xc1, 0xc1, 0), /* 0b0b11000001 */
	[0x61] = VIDEO_COLOR_RGBA(0xc3, 0xc3, 0xc3, 0), /* 0b0b11000011 */
	[0x62] = VIDEO_COLOR_RGBA(0xc5, 0xc5, 0xc5, 0), /* 0b0b11000101 */
	[0x63] = VIDEO_COLOR_RGBA(0xc7, 0xc7, 0xc7, 0), /* 0b0b11000111 */
	[0x64] = VIDEO_COLOR_RGBA(0xc9, 0xc9, 0xc9, 0), /* 0b0b11001001 */
	[0x65] = VIDEO_COLOR_RGBA(0xcb, 0xcb, 0xcb, 0), /* 0b0b11001011 */
	[0x66] = VIDEO_COLOR_RGBA(0xcd, 0xcd, 0xcd, 0), /* 0b0b11001101 */
	[0x67] = VIDEO_COLOR_RGBA(0xcf, 0xcf, 0xcf, 0), /* 0b0b11001111 */
	[0x68] = VIDEO_COLOR_RGBA(0xd1, 0xd1, 0xd1, 0), /* 0b0b11010001 */
	[0x69] = VIDEO_COLOR_RGBA(0xd3, 0xd3, 0xd3, 0), /* 0b0b11010011 */
	[0x6a] = VIDEO_COLOR_RGBA(0xd5, 0xd5, 0xd5, 0), /* 0b0b11010101 */
	[0x6b] = VIDEO_COLOR_RGBA(0xd7, 0xd7, 0xd7, 0), /* 0b0b11010111 */
	[0x6c] = VIDEO_COLOR_RGBA(0xd9, 0xd9, 0xd9, 0), /* 0b0b11011001 */
	[0x6d] = VIDEO_COLOR_RGBA(0xdb, 0xdb, 0xdb, 0), /* 0b0b11011011 */
	[0x6e] = VIDEO_COLOR_RGBA(0xdd, 0xdd, 0xdd, 0), /* 0b0b11011101 */
	[0x6f] = VIDEO_COLOR_RGBA(0xdf, 0xdf, 0xdf, 0), /* 0b0b11011111 */
	[0x70] = VIDEO_COLOR_RGBA(0xe1, 0xe1, 0xe1, 0), /* 0b0b11100001 */
	[0x71] = VIDEO_COLOR_RGBA(0xe3, 0xe3, 0xe3, 0), /* 0b0b11100011 */
	[0x72] = VIDEO_COLOR_RGBA(0xe5, 0xe5, 0xe5, 0), /* 0b0b11100101 */
	[0x73] = VIDEO_COLOR_RGBA(0xe7, 0xe7, 0xe7, 0), /* 0b0b11100111 */
	[0x74] = VIDEO_COLOR_RGBA(0xe9, 0xe9, 0xe9, 0), /* 0b0b11101001 */
	[0x75] = VIDEO_COLOR_RGBA(0xeb, 0xeb, 0xeb, 0), /* 0b0b11101011 */
	[0x76] = VIDEO_COLOR_RGBA(0xed, 0xed, 0xed, 0), /* 0b0b11101101 */
	[0x77] = VIDEO_COLOR_RGBA(0xef, 0xef, 0xef, 0), /* 0b0b11101111 */
	[0x78] = VIDEO_COLOR_RGBA(0xf1, 0xf1, 0xf1, 0), /* 0b0b11110001 */
	[0x79] = VIDEO_COLOR_RGBA(0xf3, 0xf3, 0xf3, 0), /* 0b0b11110011 */
	[0x7a] = VIDEO_COLOR_RGBA(0xf5, 0xf5, 0xf5, 0), /* 0b0b11110101 */
	[0x7b] = VIDEO_COLOR_RGBA(0xf7, 0xf7, 0xf7, 0), /* 0b0b11110111 */
	[0x7c] = VIDEO_COLOR_RGBA(0xf9, 0xf9, 0xf9, 0), /* 0b0b11111001 */
	[0x7d] = VIDEO_COLOR_RGBA(0xfb, 0xfb, 0xfb, 0), /* 0b0b11111011 */
	[0x7e] = VIDEO_COLOR_RGBA(0xfd, 0xfd, 0xfd, 0), /* 0b0b11111101 */
	[0x7f] = VIDEO_COLOR_RGBA(0xff, 0xff, 0xff, 0), /* 0b0b11111111 */
/*[[[end]]]*/
};
#endif /* !__OPTIMIZE_SIZE__ */



#define alpha1_tocolor(v) ((video_color_t)(VIDEO_COLOR_ALPHA_MASK) * (v))
#define alpha2_tocolor(v) ((video_color_t)(__UINT32_C(0x22222222) & (VIDEO_COLOR_ALPHA_MASK)) * (v))
#define alpha4_tocolor(v) ((video_color_t)(__UINT32_C(0x11111111) & (VIDEO_COLOR_ALPHA_MASK)) * (v))
#define alpha8_tocolor(v) ((video_color_t)(v) << VIDEO_COLOR_ALPHA_SHIFT)

#define lumen1_tocolor(v) ((VIDEO_COLOR_RED_MASK | VIDEO_COLOR_GREEN_MASK | VIDEO_COLOR_BLUE_MASK) * (v))
#define lumen2_tocolor(v) ((__UINT32_C(0x22222222) & (VIDEO_COLOR_RED_MASK | VIDEO_COLOR_GREEN_MASK | VIDEO_COLOR_BLUE_MASK)) * (v))
#define lumen3_tocolor(v) l3_to_color[v]
#define lumen4_tocolor(v) ((__UINT32_C(0x11111111) & (VIDEO_COLOR_RED_MASK | VIDEO_COLOR_GREEN_MASK | VIDEO_COLOR_BLUE_MASK)) * (v))
#define lumen7_tocolor(v) l7_to_color(v)
#define lumen8_tocolor(v) ((__UINT32_C(0x01010101) & (VIDEO_COLOR_RED_MASK | VIDEO_COLOR_GREEN_MASK | VIDEO_COLOR_BLUE_MASK)) * (v))

#define rgb_getlumen8(r, g, b)      (video_pixel_t)((uint8_t)((uint_fast16_t)((uint_fast16_t)r + g + b + 2) / 3))
#define rgb_getlumen1(r, g, b)      (video_pixel_t)(rgb_getlumen8(r, g, b) >> 7)
#define rgb_getlumen2(r, g, b)      (video_pixel_t)(rgb_getlumen8(r, g, b) >> 6)
#define rgb_getlumen3(r, g, b)      (video_pixel_t)(rgb_getlumen8(r, g, b) >> 5)
#define rgb_getlumen4(r, g, b)      (video_pixel_t)(rgb_getlumen8(r, g, b) >> 4)
#define rgb_getlumen7_shl1(r, g, b) (video_pixel_t)(rgb_getlumen8(r, g, b) & 0xfe)
#define rgb_getlumen7(r, g, b)      (video_pixel_t)(rgb_getlumen8(r, g, b) >> 1)

#define color_getlumen1(c)      rgb_getlumen1(c.r, c.g, c.b)
#define color_getlumen2(c)      rgb_getlumen2(c.r, c.g, c.b)
#define color_getlumen3(c)      rgb_getlumen3(c.r, c.g, c.b)
#define color_getlumen4(c)      rgb_getlumen4(c.r, c.g, c.b)
#define color_getlumen7_shl1(c) rgb_getlumen7_shl1(c.r, c.g, c.b)
#define color_getlumen7(c)      rgb_getlumen7(c.r, c.g, c.b)
#define color_getlumen8(c)      rgb_getlumen8(c.r, c.g, c.b)
#define color_getalpha1_shl7(c) (video_pixel_t)(c.a & 0x80)
#define color_getalpha1(c)      (video_pixel_t)(c.a >> 7)
#define color_getalpha2(c)      (video_pixel_t)(c.a >> 6)
#define color_getalpha3(c)      (video_pixel_t)(c.a >> 5)
#define color_getalpha4(c)      (video_pixel_t)(c.a >> 4)
#define color_getalpha8(c)      (video_pixel_t)(c.a)


PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
l1_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return VIDEO_COLOR_ALPHA_MASK | lumen1_tocolor(pixel & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
l1_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return color_getlumen1(data);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
l2_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return VIDEO_COLOR_ALPHA_MASK | lumen2_tocolor(pixel & 0x3);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
l2_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return rgb_getlumen2(data.r, data.g, data.b);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
l4_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return VIDEO_COLOR_ALPHA_MASK | lumen4_tocolor(pixel & 0xf);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
l4_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return rgb_getlumen4(data.r, data.g, data.b);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
l8_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return VIDEO_COLOR_ALPHA_MASK | lumen8_tocolor(pixel & 0xff);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
l8_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return rgb_getlumen8(data.r, data.g, data.b);
}


PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
al11_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return alpha1_tocolor((pixel) & 1) |
	       lumen1_tocolor((pixel >> 1) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
al11_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha1(data)) |
	       (color_getlumen1(data) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
la11_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return lumen1_tocolor((pixel) & 1) |
	       alpha1_tocolor((pixel >> 1) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
la11_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getlumen1(data)) |
	       (color_getalpha1(data) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
al22_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return alpha2_tocolor((pixel) & 3) |
	       lumen2_tocolor((pixel >> 2) & 3);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
al22_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha2(data)) |
	       (color_getlumen2(data) << 2);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
la22_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return lumen2_tocolor((pixel) & 3) |
	       alpha2_tocolor((pixel >> 2) & 3);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
la22_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha2(data) << 2) |
	       (color_getlumen2(data));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
al13_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return alpha1_tocolor((pixel) & 1) |
	       lumen3_tocolor((pixel >> 1) & 7);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
al13_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha1(data)) |
	       (color_getlumen3(data) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
la31_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return lumen3_tocolor((pixel) & 7) |
	       alpha1_tocolor((pixel >> 3) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
la31_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha1(data) << 3) |
	       (color_getlumen3(data));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
al44_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return alpha4_tocolor((pixel) & 0xf) |
	       lumen4_tocolor((pixel >> 4) & 0xf);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
al44_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha4(data)) |
	       (color_getlumen4(data) << 4);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
la44_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return lumen4_tocolor((pixel) & 0xf) |
	       alpha4_tocolor((pixel >> 4) & 0xf);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
la44_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getlumen4(data)) |
	       (color_getalpha4(data) << 4);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
al17_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return alpha1_tocolor((pixel) & 1) |
	       lumen7_tocolor((pixel >> 1) & 127);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
al17_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha1(data)) |
	       (color_getlumen7_shl1(data));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
la71_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return lumen7_tocolor((pixel) & 127) |
	       alpha1_tocolor((pixel >> 7) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
la71_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getlumen7(data)) |
	       (color_getalpha1_shl7(data));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
al88_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return alpha8_tocolor((pixel) & 0xff) |
	       lumen8_tocolor((pixel >> 8) & 0xff);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
al88_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha8(data)) |
	       (color_getlumen8(data) << 8);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
la88_pixel2color(struct video_format const *__restrict UNUSED(format), video_pixel_t pixel) {
	return lumen8_tocolor((pixel) & 0xff) |
	       alpha8_tocolor((pixel >> 8) & 0xff);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
la88_color2pixel(struct video_format const *__restrict UNUSED(format), video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getlumen8(data)) |
	       (color_getalpha8(data) << 8);
}



/* Extract N-bit values from color codes */
#define COLOR_GETR1(color) (((color) >> (VIDEO_COLOR_RED_SHIFT + 7)) & 0x1)
#define COLOR_GETG1(color) (((color) >> (VIDEO_COLOR_GREEN_SHIFT + 7)) & 0x1)
#define COLOR_GETB1(color) (((color) >> (VIDEO_COLOR_BLUE_SHIFT + 7)) & 0x1)
#define COLOR_GETA1(color) (((color) >> (VIDEO_COLOR_ALPHA_SHIFT + 7)) & 0x1)
#define COLOR_GETR4(color) (((color) >> (VIDEO_COLOR_RED_SHIFT + 4)) & 0xf)
#define COLOR_GETG4(color) (((color) >> (VIDEO_COLOR_GREEN_SHIFT + 4)) & 0xf)
#define COLOR_GETB4(color) (((color) >> (VIDEO_COLOR_BLUE_SHIFT + 4)) & 0xf)
#define COLOR_GETA4(color) (((color) >> (VIDEO_COLOR_ALPHA_SHIFT + 4)) & 0xf)
#define COLOR_GETR5(color) (((color) >> (VIDEO_COLOR_RED_SHIFT + 3)) & 0x1f)
#define COLOR_GETG5(color) (((color) >> (VIDEO_COLOR_GREEN_SHIFT + 3)) & 0x1f)
#define COLOR_GETB5(color) (((color) >> (VIDEO_COLOR_BLUE_SHIFT + 3)) & 0x1f)
#define COLOR_GETA5(color) (((color) >> (VIDEO_COLOR_ALPHA_SHIFT + 3)) & 0x1f)
#define COLOR_GETR6(color) (((color) >> (VIDEO_COLOR_RED_SHIFT + 2)) & 0x3f)
#define COLOR_GETG6(color) (((color) >> (VIDEO_COLOR_GREEN_SHIFT + 2)) & 0x3f)
#define COLOR_GETB6(color) (((color) >> (VIDEO_COLOR_BLUE_SHIFT + 2)) & 0x3f)
#define COLOR_GETA6(color) (((color) >> (VIDEO_COLOR_ALPHA_SHIFT + 2)) & 0x3f)

#define COLOR_SETR1(r) ((video_color_t)((r) * 0xff) << VIDEO_COLOR_RED_SHIFT)
#define COLOR_SETG1(g) ((video_color_t)((g) * 0xff) << VIDEO_COLOR_GREEN_SHIFT)
#define COLOR_SETB1(b) ((video_color_t)((b) * 0xff) << VIDEO_COLOR_BLUE_SHIFT)
#define COLOR_SETA1(a) ((video_color_t)((a) * 0xff) << VIDEO_COLOR_ALPHA_SHIFT)
#define COLOR_SETR4(r) ((video_color_t)repeat_lsb(r, 4) << VIDEO_COLOR_RED_SHIFT)
#define COLOR_SETG4(g) ((video_color_t)repeat_lsb(g, 4) << VIDEO_COLOR_GREEN_SHIFT)
#define COLOR_SETB4(b) ((video_color_t)repeat_lsb(b, 4) << VIDEO_COLOR_BLUE_SHIFT)
#define COLOR_SETA4(a) ((video_color_t)repeat_lsb(a, 4) << VIDEO_COLOR_ALPHA_SHIFT)
#define COLOR_SETR5(r) ((video_color_t)repeat_lsb(r, 3) << VIDEO_COLOR_RED_SHIFT)
#define COLOR_SETG5(g) ((video_color_t)repeat_lsb(g, 3) << VIDEO_COLOR_GREEN_SHIFT)
#define COLOR_SETB5(b) ((video_color_t)repeat_lsb(b, 3) << VIDEO_COLOR_BLUE_SHIFT)
#define COLOR_SETA5(a) ((video_color_t)repeat_lsb(a, 3) << VIDEO_COLOR_ALPHA_SHIFT)
#define COLOR_SETR6(r) ((video_color_t)repeat_lsb(r, 2) << VIDEO_COLOR_RED_SHIFT)
#define COLOR_SETG6(g) ((video_color_t)repeat_lsb(g, 2) << VIDEO_COLOR_GREEN_SHIFT)
#define COLOR_SETB6(b) ((video_color_t)repeat_lsb(b, 2) << VIDEO_COLOR_BLUE_SHIFT)
#define COLOR_SETA6(a) ((video_color_t)repeat_lsb(a, 2) << VIDEO_COLOR_ALPHA_SHIFT)

#define DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGBA(name, datatype, union_type,     \
                                                         r_bits, g_bits, b_bits, a_bits) \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC                             \
	name##_color2pixel(struct video_format const *__restrict UNUSED(format),             \
	                   video_color_t color) {                                            \
		union_type px;                                                                   \
		px.r = COLOR_GETR##r_bits(color);                                                \
		px.g = COLOR_GETG##g_bits(color);                                                \
		px.b = COLOR_GETB##b_bits(color);                                                \
		px.a = COLOR_GETA##a_bits(color);                                                \
		return px.data;                                                                  \
	}                                                                                    \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC                             \
	name##_pixel2color(struct video_format const *__restrict UNUSED(format),             \
	                   video_pixel_t pixel) {                                            \
		union_type px;                                                                   \
		px.data = (datatype)pixel;                                                       \
		return VIDEO_COLOR_RGBA(COLOR_SETR##r_bits(px.r),                                \
		                        COLOR_SETR##g_bits(px.g),                                \
		                        COLOR_SETR##b_bits(px.b),                                \
		                        COLOR_SETR##a_bits(px.a));                               \
	}

#define DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGBX(name, datatype, union_type, \
                                                         r_bits, g_bits, b_bits)     \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC                         \
	name##_color2pixel(struct video_format const *__restrict UNUSED(format),         \
	                   video_color_t color) {                                        \
		union_type px;                                                               \
		px.r = COLOR_GETR##r_bits(color);                                            \
		px.g = COLOR_GETG##g_bits(color);                                            \
		px.b = COLOR_GETB##b_bits(color);                                            \
		px.x = 0;                                                                    \
		return px.data;                                                              \
	}                                                                                \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC                         \
	name##_pixel2color(struct video_format const *__restrict UNUSED(format),         \
	                   video_pixel_t pixel) {                                        \
		union_type px;                                                               \
		px.data = (datatype)pixel;                                                   \
		return VIDEO_COLOR_RGB(COLOR_SETR##r_bits(px.r),                             \
		                       COLOR_SETR##g_bits(px.g),                             \
		                       COLOR_SETR##b_bits(px.b));                            \
	}

#define DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGB(name, datatype, union_type, \
                                                        r_bits, g_bits, b_bits)     \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC                        \
	name##_color2pixel(struct video_format const *__restrict UNUSED(format),        \
	                   video_color_t color) {                                       \
		union_type px;                                                              \
		px.r = COLOR_GETR##r_bits(color);                                           \
		px.g = COLOR_GETG##g_bits(color);                                           \
		px.b = COLOR_GETB##b_bits(color);                                           \
		return px.data;                                                             \
	}                                                                               \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC                        \
	name##_pixel2color(struct video_format const *__restrict UNUSED(format),        \
	                   video_pixel_t pixel) {                                       \
		union_type px;                                                              \
		px.data = (datatype)pixel;                                                  \
		return VIDEO_COLOR_RGB(COLOR_SETR##r_bits(px.r),                            \
		                       COLOR_SETR##g_bits(px.g),                            \
		                       COLOR_SETR##b_bits(px.b));                           \
	}



#define DEFINE_FORMAT_PIXEL_UNION(name, datatype, ...) \
	union pixel_##name {                               \
		datatype data;                                 \
		struct __VA_ARGS__;                            \
	};
#define _DEFINE_FORMAT_CONVERTER_RGBA(name, datatype, r_bits, g_bits, b_bits, a_bits, ...) \
	DEFINE_FORMAT_PIXEL_UNION(name, datatype, __VA_ARGS__) \
	DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGBA(name, datatype, union pixel_##name, r_bits, g_bits, b_bits, a_bits)
#define _DEFINE_FORMAT_CONVERTER_RGBX(name, datatype, r_bits, g_bits, b_bits, ...) \
	DEFINE_FORMAT_PIXEL_UNION(name, datatype, __VA_ARGS__) \
	DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGBX(name, datatype, union pixel_##name, r_bits, g_bits, b_bits)
#define _DEFINE_FORMAT_CONVERTER_RGB(name, datatype, r_bits, g_bits, b_bits, ...)  \
	DEFINE_FORMAT_PIXEL_UNION(name, datatype, __VA_ARGS__) \
	DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGB(name, datatype, union pixel_##name, r_bits, g_bits, b_bits)

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
/* Bitfields are allocated  least-significant to  most-significant.
 * Since LE also sees  the first byte of  input data appear in  the
 * least significant 8 bits, bitfields must be ordered ascendingly. */
#define ENDIAN_ORDER3(_1, _2, _3)     _1; _2; _3;
#define ENDIAN_ORDER4(_1, _2, _3, _4) _1; _2; _3; _4;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
/* Bitfields are allocated  most-significant to  least-significant.
 * Since BE also sees  the first byte of  input data appear in  the
 * most significant 8 bits, bitfields must be ordered descendingly. */
#define ENDIAN_ORDER3(_1, _2, _3)     _3; _2; _1;
#define ENDIAN_ORDER4(_1, _2, _3, _4) _4; _3; _2; _1;
#endif /* __BYTE_ORDER__ == ... */

#define DEFINE_FORMAT_CONVERTER_RGBA(name, datatype, r_bits, g_bits, b_bits, a_bits, fields) \
	_DEFINE_FORMAT_CONVERTER_RGBA(name, datatype, r_bits, g_bits, b_bits, a_bits, { ENDIAN_ORDER4 fields })
#define DEFINE_FORMAT_CONVERTER_RGBX(name, datatype, r_bits, g_bits, b_bits, fields) \
	_DEFINE_FORMAT_CONVERTER_RGBX(name, datatype, r_bits, g_bits, b_bits, { ENDIAN_ORDER4 fields })
#define DEFINE_FORMAT_CONVERTER_RGB(name, datatype, r_bits, g_bits, b_bits, fields) \
	_DEFINE_FORMAT_CONVERTER_RGB(name, datatype, r_bits, g_bits, b_bits, { ENDIAN_ORDER3 fields })

DEFINE_FORMAT_CONVERTER_RGBA(rgba4444, uint16_t, 4, 4, 4, 4, (
	__HYBRID_BITFIELD8_T r : 4,
	__HYBRID_BITFIELD8_T g : 4,
	__HYBRID_BITFIELD8_T b : 4,
	__HYBRID_BITFIELD8_T a : 4
));
DEFINE_FORMAT_CONVERTER_RGBX(rgbx4444, uint16_t, 4, 4, 4, (
	__HYBRID_BITFIELD8_T r : 4,
	__HYBRID_BITFIELD8_T g : 4,
	__HYBRID_BITFIELD8_T b : 4,
	__HYBRID_BITFIELD8_T x : 4
));
DEFINE_FORMAT_CONVERTER_RGBA(argb4444, uint16_t, 4, 4, 4, 4, (
	__HYBRID_BITFIELD8_T a : 4,
	__HYBRID_BITFIELD8_T r : 4,
	__HYBRID_BITFIELD8_T g : 4,
	__HYBRID_BITFIELD8_T b : 4
));
DEFINE_FORMAT_CONVERTER_RGBX(xrgb4444, uint16_t, 4, 4, 4, (
	__HYBRID_BITFIELD8_T x : 4,
	__HYBRID_BITFIELD8_T r : 4,
	__HYBRID_BITFIELD8_T g : 4,
	__HYBRID_BITFIELD8_T b : 4
));
DEFINE_FORMAT_CONVERTER_RGBA(abgr4444, uint16_t, 4, 4, 4, 4, (
	__HYBRID_BITFIELD8_T a : 4,
	__HYBRID_BITFIELD8_T b : 4,
	__HYBRID_BITFIELD8_T g : 4,
	__HYBRID_BITFIELD8_T r : 4
));
DEFINE_FORMAT_CONVERTER_RGBX(xbgr4444, uint16_t, 4, 4, 4, (
	__HYBRID_BITFIELD8_T x : 4,
	__HYBRID_BITFIELD8_T b : 4,
	__HYBRID_BITFIELD8_T g : 4,
	__HYBRID_BITFIELD8_T r : 4
));
DEFINE_FORMAT_CONVERTER_RGBA(bgra4444, uint16_t, 4, 4, 4, 4, (
	__HYBRID_BITFIELD8_T b : 4,
	__HYBRID_BITFIELD8_T g : 4,
	__HYBRID_BITFIELD8_T r : 4,
	__HYBRID_BITFIELD8_T a : 4
));
DEFINE_FORMAT_CONVERTER_RGBX(bgrx4444, uint16_t, 4, 4, 4, (
	__HYBRID_BITFIELD8_T b : 4,
	__HYBRID_BITFIELD8_T g : 4,
	__HYBRID_BITFIELD8_T r : 4,
	__HYBRID_BITFIELD8_T x : 4
));


DEFINE_FORMAT_CONVERTER_RGBA(rgba5551, uint16_t, 5, 5, 5, 1, (
	__HYBRID_BITFIELD8_T r : 5,
	__HYBRID_BITFIELD8_T g : 5,
	__HYBRID_BITFIELD8_T b : 5,
	__HYBRID_BITFIELD8_T a : 1
));
DEFINE_FORMAT_CONVERTER_RGBX(rgbx5551, uint16_t, 5, 5, 5, (
	__HYBRID_BITFIELD8_T r : 5,
	__HYBRID_BITFIELD8_T g : 5,
	__HYBRID_BITFIELD8_T b : 5,
	__HYBRID_BITFIELD8_T x : 1
));
DEFINE_FORMAT_CONVERTER_RGBA(argb1555, uint16_t, 5, 5, 5, 1, (
	__HYBRID_BITFIELD8_T a : 1,
	__HYBRID_BITFIELD8_T r : 5,
	__HYBRID_BITFIELD8_T g : 5,
	__HYBRID_BITFIELD8_T b : 5
));
DEFINE_FORMAT_CONVERTER_RGBX(xrgb1555, uint16_t, 5, 5, 5, (
	__HYBRID_BITFIELD8_T x : 1,
	__HYBRID_BITFIELD8_T r : 5,
	__HYBRID_BITFIELD8_T g : 5,
	__HYBRID_BITFIELD8_T b : 5
));
DEFINE_FORMAT_CONVERTER_RGBA(abgr1555, uint16_t, 5, 5, 5, 1, (
	__HYBRID_BITFIELD8_T a : 1,
	__HYBRID_BITFIELD8_T b : 5,
	__HYBRID_BITFIELD8_T g : 5,
	__HYBRID_BITFIELD8_T r : 5
));
DEFINE_FORMAT_CONVERTER_RGBX(xbgr1555, uint16_t, 5, 5, 5, (
	__HYBRID_BITFIELD8_T x : 1,
	__HYBRID_BITFIELD8_T b : 5,
	__HYBRID_BITFIELD8_T g : 5,
	__HYBRID_BITFIELD8_T r : 5
));
DEFINE_FORMAT_CONVERTER_RGBA(bgra5551, uint16_t, 5, 5, 5, 1, (
	__HYBRID_BITFIELD8_T b : 5,
	__HYBRID_BITFIELD8_T g : 5,
	__HYBRID_BITFIELD8_T r : 5,
	__HYBRID_BITFIELD8_T a : 1
));
DEFINE_FORMAT_CONVERTER_RGBX(bgrx5551, uint16_t, 5, 5, 5, (
	__HYBRID_BITFIELD8_T b : 5,
	__HYBRID_BITFIELD8_T g : 5,
	__HYBRID_BITFIELD8_T r : 5,
	__HYBRID_BITFIELD8_T x : 1
));

DEFINE_FORMAT_CONVERTER_RGB(rgb565, uint16_t, 5, 6, 5, (
	__HYBRID_BITFIELD8_T r : 5,
	__HYBRID_BITFIELD8_T g : 6,
	__HYBRID_BITFIELD8_T b : 5
));
DEFINE_FORMAT_CONVERTER_RGB(bgr565, uint16_t, 5, 6, 5, (
	__HYBRID_BITFIELD8_T b : 5,
	__HYBRID_BITFIELD8_T g : 6,
	__HYBRID_BITFIELD8_T r : 5
));



INTERN ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
pal_pixel2color(struct video_format const *__restrict format,
                video_pixel_t pixel) {
	struct video_palette *pal = format->vf_pal;
	return video_palette_getcolor(pal, pixel);
}

#define pal_color2pixel(format, color) \
	video_palette_getpixel(format->vf_pal, color)
INTERN ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t
(CC pal_color2pixel)(struct video_format const *__restrict format,
                     video_color_t color) {
	return video_palette_getpixel(format->vf_pal, color);
}


#define paletN_tocolor(v, n) (pal_pixel2color(format, v) & ~VIDEO_COLOR_ALPHA_MASK)
#define palet1_tocolor(v)    paletN_tocolor(v, 1)
#define palet2_tocolor(v)    paletN_tocolor(v, 2)
#define palet3_tocolor(v)    paletN_tocolor(v, 3)
#define palet4_tocolor(v)    paletN_tocolor(v, 4)
#define palet7_tocolor(v)    paletN_tocolor(v, 7)
#define palet8_tocolor(v)    paletN_tocolor(v, 8)

#if 1 /* Assume that the palette isn't too large (if it is, we'll encode bad pixel data) */
#define color_getpaletN(v, mask) pal_color2pixel(format, color)
#else
#define color_getpaletN(v, mask) (pal_color2pixel(format, color) & (mask))
#endif
#define color_getpalet1(v) color_getpaletN(v, 1)
#define color_getpalet2(v) color_getpaletN(v, 3)
#define color_getpalet3(v) color_getpaletN(v, 7)
#define color_getpalet4(v) color_getpaletN(v, 0xf)
#define color_getpalet7(v) color_getpaletN(v, 0x7f)
#define color_getpalet8(v) color_getpaletN(v, 0xff)

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
ap11_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel) {
	return alpha1_tocolor((pixel) & 1) |
	       palet1_tocolor((pixel >> 1) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
ap11_color2pixel(struct video_format const *__restrict format, video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha1(data)) |
	       (color_getpalet1(data) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
pa11_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel) {
	return palet1_tocolor((pixel) & 1) |
	       alpha1_tocolor((pixel >> 1) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
pa11_color2pixel(struct video_format const *__restrict format, video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getpalet1(data)) |
	       (color_getalpha1(data) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
ap22_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel) {
	return alpha2_tocolor((pixel) & 3) |
	       palet2_tocolor((pixel >> 2) & 3);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
ap22_color2pixel(struct video_format const *__restrict format, video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha2(data)) |
	       (color_getpalet2(data) << 2);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
pa22_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel) {
	return palet2_tocolor((pixel) & 3) |
	       alpha2_tocolor((pixel >> 2) & 3);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
pa22_color2pixel(struct video_format const *__restrict format, video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha2(data) << 2) |
	       (color_getpalet2(data));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
ap13_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel) {
	return alpha1_tocolor((pixel) & 1) |
	       palet3_tocolor((pixel >> 1) & 7);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
ap13_color2pixel(struct video_format const *__restrict format, video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha1(data)) |
	       (color_getpalet3(data) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
pa31_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel) {
	return palet3_tocolor((pixel) & 7) |
	       alpha1_tocolor((pixel >> 3) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
pa31_color2pixel(struct video_format const *__restrict format, video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha1(data) << 3) |
	       (color_getpalet3(data));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
ap44_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel) {
	return alpha4_tocolor((pixel) & 0xf) |
	       palet4_tocolor((pixel >> 4) & 0xf);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
ap44_color2pixel(struct video_format const *__restrict format, video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha4(data)) |
	       (color_getpalet4(data) << 4);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
pa44_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel) {
	return palet4_tocolor((pixel) & 0xf) |
	       alpha4_tocolor((pixel >> 4) & 0xf);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
pa44_color2pixel(struct video_format const *__restrict format, video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getpalet4(data)) |
	       (color_getalpha4(data) << 4);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
ap17_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel) {
	return alpha1_tocolor((pixel) & 1) |
	       palet7_tocolor((pixel >> 1) & 127);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
ap17_color2pixel(struct video_format const *__restrict format, video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha1(data)) |
	       (color_getpalet7(data) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
pa71_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel) {
	return palet7_tocolor((pixel) & 127) |
	       alpha1_tocolor((pixel >> 7) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
pa71_color2pixel(struct video_format const *__restrict format, video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getpalet7(data)) |
	       (color_getalpha1_shl7(data));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
ap88_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel) {
	return alpha8_tocolor((pixel) & 0xff) |
	       palet8_tocolor((pixel >> 8) & 0xff);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
ap88_color2pixel(struct video_format const *__restrict format, video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getalpha8(data)) |
	       (color_getpalet8(data) << 8);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
pa88_pixel2color(struct video_format const *__restrict format, video_pixel_t pixel) {
	return palet8_tocolor((pixel) & 0xff) |
	       alpha8_tocolor((pixel >> 8) & 0xff);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
pa88_color2pixel(struct video_format const *__restrict format, video_color_t color) {
	union color_data data;
	data.color = color;
	return (color_getpalet8(data)) |
	       (color_getalpha8(data) << 8);
}
#undef paletN_tocolor
#undef palet1_tocolor
#undef palet2_tocolor
#undef palet3_tocolor
#undef palet4_tocolor
#undef palet7_tocolor
#undef palet8_tocolor
#undef color_getpaletN
#undef color_getpalet1
#undef color_getpalet2
#undef color_getpalet3
#undef color_getpalet4
#undef color_getpalet7
#undef color_getpalet8






PRIVATE NONNULL((3)) void CC
buffer32_requirements(video_dim_t size_x, video_dim_t size_y,
                      struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = size_x * 4;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

PRIVATE NONNULL((3)) void CC
buffer24_requirements(video_dim_t size_x, video_dim_t size_y,
                      struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = size_x * 3;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

PRIVATE NONNULL((3)) void CC
buffer16_requirements(video_dim_t size_x, video_dim_t size_y,
                      struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = size_x * 2;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

PRIVATE NONNULL((3)) void CC
buffer8_requirements(video_dim_t size_x, video_dim_t size_y,
                     struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = size_x;
	result->vbs_bufsize = size_y * size_x;
}

PRIVATE NONNULL((3)) void CC
buffer4_requirements(video_dim_t size_x, video_dim_t size_y,
                     struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = (size_x + 1) / 2;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

PRIVATE NONNULL((3)) void CC
buffer2_requirements(video_dim_t size_x, video_dim_t size_y,
                     struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = (size_x + 3) / 4;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

PRIVATE NONNULL((3)) void CC
buffer1_requirements(video_dim_t size_x, video_dim_t size_y,
                     struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = (size_x + 7) / 8;
	result->vbs_bufsize = size_y * result->vbs_stride;
}


/* Lookup the interface for a given codec, or return NULL if the codec isn't supported.
 * Don't declare as  ATTR_CONST; in  PIC-mode, needs  to do  one-time-init of  globals! */
INTERN /*ATTR_CONST*/ WUNUSED struct video_codec const *CC
libvideo_codec_lookup(video_codec_t codec) {
#define UNPACK_SPECS(flags, bpp, cbits, rmask, gmask, bmask, amask) \
	{ flags, CEILDIV(bpp, NBBY), bpp, cbits, rmask, gmask, bmask, amask }

#if defined(__KERNEL__) || !defined(__pic__)
#define _DEFINE_CODEC_AL1(name, codec, specs, rambuffer_requirements,   \
                          getpixel, setpixel, rectcopy,                 \
                          linefill, vertfill, rectfill,                 \
                          pixel2color, color2pixel, initconverter)      \
		PRIVATE struct video_codec const name = {                       \
			/* .vc_codec                  = */ codec,                   \
			/* .vc_specs                  = */ UNPACK_SPECS specs,      \
			/* .vc_align                  = */ 1,                       \
			/* .vc_nalgn                  = */ &name,                   \
			/* .vc_rambuffer_requirements = */ &rambuffer_requirements, \
			/* .vc_pixel2color            = */ &pixel2color,            \
			/* .vc_color2pixel            = */ &color2pixel,            \
			/* .vc_initconverter          = */ &initconverter,          \
			/* .vc_getpixel               = */ &getpixel,               \
			/* .vc_setpixel               = */ &setpixel,               \
			/* .vc_rectcopy               = */ &rectcopy,               \
			/* .vc_linefill               = */ &linefill,               \
			/* .vc_vertfill               = */ &vertfill,               \
			/* .vc_rectfill               = */ &rectfill,               \
		}
#define _DEFINE_CODEC_ALX(name, codec, specs,                           \
                          align, rambuffer_requirements,                \
                          getpixel, setpixel, rectcopy,                 \
                          linefill, vertfill, rectfill,                 \
                          unaligned_getpixel, unaligned_setpixel,       \
                          unaligned_rectcopy,                           \
                          unaligned_linefill, unaligned_vertfill,       \
                          unaligned_rectfill,                           \
                          pixel2color, color2pixel, initconverter)      \
		PRIVATE struct video_codec const unaligned_##name = {           \
			/* .vc_codec                  = */ codec,                   \
			/* .vc_specs                  = */ UNPACK_SPECS specs,      \
			/* .vc_align                  = */ 1,                       \
			/* .vc_nalgn                  = */ &unaligned_##name,       \
			/* .vc_rambuffer_requirements = */ &rambuffer_requirements, \
			/* .vc_pixel2color            = */ &pixel2color,            \
			/* .vc_color2pixel            = */ &color2pixel,            \
			/* .vc_initconverter          = */ &initconverter,          \
			/* .vc_getpixel               = */ &unaligned_getpixel,     \
			/* .vc_setpixel               = */ &unaligned_setpixel,     \
			/* .vc_rectcopy               = */ &unaligned_rectcopy,     \
			/* .vc_linefill               = */ &unaligned_linefill,     \
			/* .vc_vertfill               = */ &unaligned_vertfill,     \
			/* .vc_rectfill               = */ &unaligned_rectfill,     \
		};                                                              \
		PRIVATE struct video_codec const name = {                       \
			/* .vc_codec                  = */ codec,                   \
			/* .vc_specs                  = */ UNPACK_SPECS specs,      \
			/* .vc_align                  = */ align,                   \
			/* .vc_nalgn                  = */ &unaligned_##name,       \
			/* .vc_rambuffer_requirements = */ &rambuffer_requirements, \
			/* .vc_pixel2color            = */ &pixel2color,            \
			/* .vc_color2pixel            = */ &color2pixel,            \
			/* .vc_initconverter          = */ &initconverter,          \
			/* .vc_getpixel               = */ &getpixel,               \
			/* .vc_setpixel               = */ &setpixel,               \
			/* .vc_rectcopy               = */ &rectcopy,               \
			/* .vc_linefill               = */ &linefill,               \
			/* .vc_vertfill               = */ &vertfill,               \
			/* .vc_rectfill               = */ &rectfill,               \
		}
#else /* __KERNEL__ || !__pic__ */
#define _DEFINE_CODEC_AL1(name, codec, specs, rambuffer_requirements,   \
                          getpixel, setpixel, rectcopy,                 \
                          linefill, vertfill, rectfill,                 \
                          pixel2color, color2pixel, initconverter)      \
		PRIVATE struct video_codec name = {                             \
			/* .vc_codec = */ codec,                                    \
			/* .vc_specs = */ UNPACK_SPECS specs,                       \
			/* .vc_align = */ 1,                                        \
		};                                                              \
		if (!name.vc_rambuffer_requirements) {                          \
			name.vc_nalgn         = &name;                              \
			name.vc_pixel2color   = &pixel2color;                       \
			name.vc_color2pixel   = &color2pixel;                       \
			name.vc_initconverter = &initconverter;                     \
			name.vc_getpixel      = &getpixel;                          \
			name.vc_setpixel      = &setpixel;                          \
			name.vc_rectcopy      = &rectcopy;                          \
			name.vc_linefill      = &linefill;                          \
			name.vc_vertfill      = &vertfill;                          \
			name.vc_rectfill      = &rectfill;                          \
			COMPILER_WRITE_BARRIER();                                   \
			name.vc_rambuffer_requirements = &rambuffer_requirements;   \
			COMPILER_WRITE_BARRIER();                                   \
		}
#define _DEFINE_CODEC_ALX(name, codec, specs,                                     \
                          align, rambuffer_requirements,                          \
                          getpixel, setpixel, rectcopy,                           \
                          linefill, vertfill, rectfill,                           \
                          unaligned_getpixel, unaligned_setpixel,                 \
                          unaligned_rectcopy,                                     \
                          unaligned_linefill, unaligned_vertfill,                 \
                          unaligned_rectfill,                                     \
                          pixel2color, color2pixel, initconverter)                \
		PRIVATE struct video_codec unaligned_##name = {                           \
			/* .vc_codec = */ codec,                                              \
			/* .vc_specs = */ UNPACK_SPECS specs,                                 \
			/* .vc_align = */ 1,                                                  \
		};                                                                        \
		PRIVATE struct video_codec name = {                                       \
			/* .vc_codec = */ codec,                                              \
			/* .vc_specs = */ UNPACK_SPECS specs,                                 \
			/* .vc_align = */ align,                                              \
		};                                                                        \
		if (!name.vc_rambuffer_requirements) {                                    \
			unaligned_##name.vc_nalgn                  = &unaligned_##name;       \
			unaligned_##name.vc_rambuffer_requirements = &rambuffer_requirements; \
			unaligned_##name.vc_pixel2color            = &pixel2color;            \
			unaligned_##name.vc_color2pixel            = &color2pixel;            \
			unaligned_##name.vc_initconverter          = &initconverter;          \
			unaligned_##name.vc_getpixel               = &unaligned_getpixel;     \
			unaligned_##name.vc_setpixel               = &unaligned_setpixel;     \
			unaligned_##name.vc_rectcopy               = &unaligned_rectcopy;     \
			unaligned_##name.vc_linefill               = &unaligned_linefill;     \
			unaligned_##name.vc_vertfill               = &unaligned_vertfill;     \
			unaligned_##name.vc_rectfill               = &unaligned_rectfill;     \
			name.vc_nalgn                              = &unaligned_##name;       \
			name.vc_pixel2color                        = &pixel2color;            \
			name.vc_color2pixel                        = &color2pixel;            \
			name.vc_initconverter                      = &initconverter;          \
			name.vc_getpixel                           = &getpixel;               \
			name.vc_setpixel                           = &setpixel;               \
			name.vc_rectcopy                           = &rectcopy;               \
			name.vc_linefill                           = &linefill;               \
			name.vc_vertfill                           = &vertfill;               \
			name.vc_rectfill                           = &rectfill;               \
			COMPILER_WRITE_BARRIER();                                             \
			name.vc_rambuffer_requirements = &rambuffer_requirements;             \
			COMPILER_WRITE_BARRIER();                                             \
		}
#endif /* !__KERNEL__ && __pic__ */

#define CASE_CODEC_AL1(codec, specs, rambuffer_requirements,        \
                       getpixel, setpixel, rectcopy,                \
                       linefill, vertfill, rectfill,                \
                       pixel2color, color2pixel, initconverter)     \
	case codec: {                                                   \
		_DEFINE_CODEC_AL1(_codec_##codec, codec,                    \
		                  specs, rambuffer_requirements,            \
		                  getpixel, setpixel, rectcopy,             \
		                  linefill, vertfill, rectfill,             \
		                  pixel2color, color2pixel, initconverter); \
		result = &_codec_##codec;                                   \
	}	break
#define CASE_CODEC_ALn(codec, specs,                                \
                       align, rambuffer_requirements,               \
                       getpixel, setpixel, rectcopy,                \
                       linefill, vertfill, rectfill,                \
                       unaligned_getpixel, unaligned_setpixel,      \
                       unaligned_rectcopy,                          \
                       unaligned_linefill, unaligned_vertfill,      \
                       unaligned_rectfill,                          \
                       pixel2color, color2pixel, initconverter)     \
	case codec: {                                                   \
		_DEFINE_CODEC_ALX(_codec_##codec, codec, specs,             \
		                  align, rambuffer_requirements,            \
		                  getpixel, setpixel, rectcopy,             \
		                  linefill, vertfill, rectfill,             \
		                  unaligned_getpixel, unaligned_setpixel,   \
		                  unaligned_rectcopy,                       \
		                  unaligned_linefill, unaligned_vertfill,   \
		                  unaligned_rectfill,                       \
		                  pixel2color, color2pixel, initconverter); \
		result = &_codec_##codec;                                   \
	}	break


	struct video_codec const *result;
	switch (codec) {

	/* Grayscale (Luminance) formats. */
	CASE_CODEC_AL1(VIDEO_CODEC_L1_LSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 1,
	                /* vcs_cbits */ 1,
	                /* vcs_rmask */ 0x1,
	                /* vcs_gmask */ 0x1,
	                /* vcs_bmask */ 0x1,
	                /* vcs_amask */ 0x0),
	               buffer1_requirements,
	               getpixel1_lsb, setpixel1_lsb, rectcopy1_lsb,
	               linefill1_lsb, vertfill1_lsb, rectfill1_lsb,
	               l1_pixel2color, l1_color2pixel, initconv_from_l);

	CASE_CODEC_AL1(VIDEO_CODEC_L1_MSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 1,
	                /* vcs_cbits */ 1,
	                /* vcs_rmask */ 0x1,
	                /* vcs_gmask */ 0x1,
	                /* vcs_bmask */ 0x1,
	                /* vcs_amask */ 0x0),
	               buffer1_requirements,
	               getpixel1_msb, setpixel1_msb, rectcopy1_msb,
	               linefill1_msb, vertfill1_msb, rectfill1_msb,
	               l1_pixel2color, l1_color2pixel, initconv_from_l);

	CASE_CODEC_AL1(VIDEO_CODEC_L2_LSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0x3,
	                /* vcs_gmask */ 0x3,
	                /* vcs_bmask */ 0x3,
	                /* vcs_amask */ 0x0),
	               buffer2_requirements,
	               getpixel2_lsb, setpixel2_lsb, rectcopy2_lsb,
	               linefill2_lsb, vertfill2_lsb, rectfill2_lsb,
	               l2_pixel2color, l2_color2pixel, initconv_from_l);

	CASE_CODEC_AL1(VIDEO_CODEC_L2_MSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0x3,
	                /* vcs_gmask */ 0x3,
	                /* vcs_bmask */ 0x3,
	                /* vcs_amask */ 0x0),
	               buffer2_requirements,
	               getpixel2_msb, setpixel2_msb, rectcopy2_msb,
	               linefill2_msb, vertfill2_msb, rectfill2_msb,
	               l2_pixel2color, l2_color2pixel, initconv_from_l);

	CASE_CODEC_AL1(VIDEO_CODEC_L4_LSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0xf,
	                /* vcs_gmask */ 0xf,
	                /* vcs_bmask */ 0xf,
	                /* vcs_amask */ 0x0),
	               buffer4_requirements,
	               getpixel4_lsb, setpixel4_lsb, rectcopy4_lsb,
	               linefill4_lsb, vertfill4_lsb, rectfill4_lsb,
	               l4_pixel2color, l4_color2pixel, initconv_from_l);

	CASE_CODEC_AL1(VIDEO_CODEC_L4_MSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0xf,
	                /* vcs_gmask */ 0xf,
	                /* vcs_bmask */ 0xf,
	                /* vcs_amask */ 0x0),
	               buffer4_requirements,
	               getpixel4_msb, setpixel4_msb, rectcopy4_msb,
	               linefill4_msb, vertfill4_msb, rectfill4_msb,
	               l4_pixel2color, l4_color2pixel, initconv_from_l);

	CASE_CODEC_AL1(VIDEO_CODEC_L8,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0xff,
	                /* vcs_gmask */ 0xff,
	                /* vcs_bmask */ 0xff,
	                /* vcs_amask */ 0x0),
	               buffer8_requirements,
	               getpixel8, setpixel8, rectcopy8,
	               linefill8, vertfill8, rectfill8,
	               l8_pixel2color, l8_color2pixel, initconv_from_l);

	CASE_CODEC_AL1(VIDEO_CODEC_LA11_MSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0x1,
	                /* vcs_gmask */ 0x1,
	                /* vcs_bmask */ 0x1,
	                /* vcs_amask */ 0x2),
	               buffer2_requirements,
	               getpixel2_msb, setpixel2_msb, rectcopy2_msb,
	               linefill2_msb, vertfill2_msb, rectfill2_msb,
	               al11_pixel2color, al11_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_LA11_LSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0x1,
	                /* vcs_gmask */ 0x1,
	                /* vcs_bmask */ 0x1,
	                /* vcs_amask */ 0x2),
	               buffer2_requirements,
	               getpixel2_lsb, setpixel2_lsb, rectcopy2_lsb,
	               linefill2_lsb, vertfill2_lsb, rectfill2_lsb,
	               al11_pixel2color, al11_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_AL11_MSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0x2,
	                /* vcs_gmask */ 0x2,
	                /* vcs_bmask */ 0x2,
	                /* vcs_amask */ 0x1),
	               buffer2_requirements,
	               getpixel2_msb, setpixel2_msb, rectcopy2_msb,
	               linefill2_msb, vertfill2_msb, rectfill2_msb,
	               la11_pixel2color, la11_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_AL11_LSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0x2,
	                /* vcs_gmask */ 0x2,
	                /* vcs_bmask */ 0x2,
	                /* vcs_amask */ 0x1),
	               buffer2_requirements,
	               getpixel2_lsb, setpixel2_lsb, rectcopy2_lsb,
	               linefill2_lsb, vertfill2_lsb, rectfill2_lsb,
	               la11_pixel2color, la11_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_LA22_MSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0x3,
	                /* vcs_gmask */ 0x3,
	                /* vcs_bmask */ 0x3,
	                /* vcs_amask */ 0xc),
	               buffer4_requirements,
	               getpixel4_lsb, setpixel4_lsb, rectcopy4_lsb,
	               linefill4_lsb, vertfill4_lsb, rectfill4_lsb,
	               la22_pixel2color, la22_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_LA22_LSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0x3,
	                /* vcs_gmask */ 0x3,
	                /* vcs_bmask */ 0x3,
	                /* vcs_amask */ 0xc),
	               buffer4_requirements,
	               getpixel4_msb, setpixel4_msb, rectcopy4_msb,
	               linefill4_msb, vertfill4_msb, rectfill4_msb,
	               la22_pixel2color, la22_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_AL22_MSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0xc,
	                /* vcs_gmask */ 0xc,
	                /* vcs_bmask */ 0xc,
	                /* vcs_amask */ 0x3),
	               buffer4_requirements,
	               getpixel4_msb, setpixel4_msb, rectcopy4_msb,
	               linefill4_msb, vertfill4_msb, rectfill4_msb,
	               al22_pixel2color, al22_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_AL22_LSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0xc,
	                /* vcs_gmask */ 0xc,
	                /* vcs_bmask */ 0xc,
	                /* vcs_amask */ 0x3),
	               buffer4_requirements,
	               getpixel4_lsb, setpixel4_lsb, rectcopy4_lsb,
	               linefill4_lsb, vertfill4_lsb, rectfill4_lsb,
	               al22_pixel2color, al22_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_LA31_MSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0x7,
	                /* vcs_gmask */ 0x7,
	                /* vcs_bmask */ 0x7,
	                /* vcs_amask */ 0x8),
	               buffer4_requirements,
	               getpixel4_msb, setpixel4_msb, rectcopy4_msb,
	               linefill4_msb, vertfill4_msb, rectfill4_msb,
	               la31_pixel2color, la31_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_LA31_LSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0x7,
	                /* vcs_gmask */ 0x7,
	                /* vcs_bmask */ 0x7,
	                /* vcs_amask */ 0x8),
	               buffer4_requirements,
	               getpixel4_lsb, setpixel4_lsb, rectcopy4_lsb,
	               linefill4_lsb, vertfill4_lsb, rectfill4_lsb,
	               la31_pixel2color, la31_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_AL13_MSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0xe,
	                /* vcs_gmask */ 0xe,
	                /* vcs_bmask */ 0xe,
	                /* vcs_amask */ 0x1),
	               buffer4_requirements,
	               getpixel4_msb, setpixel4_msb, rectcopy4_msb,
	               linefill4_msb, vertfill4_msb, rectfill4_msb,
	               al13_pixel2color, al13_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_AL13_LSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0xe,
	                /* vcs_gmask */ 0xe,
	                /* vcs_bmask */ 0xe,
	                /* vcs_amask */ 0x1),
	               buffer4_requirements,
	               getpixel4_lsb, setpixel4_lsb, rectcopy4_lsb,
	               linefill4_lsb, vertfill4_lsb, rectfill4_lsb,
	               al13_pixel2color, al13_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_LA44,
	               (VIDEO_CODEC_FLAG_LUM,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0x0f,
	                /* vcs_gmask */ 0x0f,
	                /* vcs_bmask */ 0x0f,
	                /* vcs_amask */ 0xf0),
	               buffer8_requirements,
	               getpixel8, setpixel8, rectcopy8,
	               linefill8, vertfill8, rectfill8,
	               la44_pixel2color, la44_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_AL44,
	               (VIDEO_CODEC_FLAG_LUM,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0xf0,
	                /* vcs_gmask */ 0xf0,
	                /* vcs_bmask */ 0xf0,
	                /* vcs_amask */ 0x0f),
	               buffer8_requirements,
	               getpixel8, setpixel8, rectcopy8,
	               linefill8, vertfill8, rectfill8,
	               al44_pixel2color, al44_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_LA71,
	               (VIDEO_CODEC_FLAG_LUM,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0x7f,
	                /* vcs_gmask */ 0x7f,
	                /* vcs_bmask */ 0x7f,
	                /* vcs_amask */ 0x80),
	               buffer8_requirements,
	               getpixel8, setpixel8, rectcopy8,
	               linefill8, vertfill8, rectfill8,
	               la71_pixel2color, la71_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_AL17,
	               (VIDEO_CODEC_FLAG_LUM,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0xfe,
	                /* vcs_gmask */ 0xfe,
	                /* vcs_bmask */ 0xfe,
	                /* vcs_amask */ 0x01),
	               buffer8_requirements,
	               getpixel8, setpixel8, rectcopy8,
	               linefill8, vertfill8, rectfill8,
	               al17_pixel2color, al17_color2pixel, initconv_from_la);

	CASE_CODEC_ALn(VIDEO_CODEC_LA88,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0x00ff),
	                /* vcs_gmask */ MASK2_LE(0x00ff),
	                /* vcs_bmask */ MASK2_LE(0x00ff),
	                /* vcs_amask */ MASK2_LE(0xff00)),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               la88_pixel2color, la88_color2pixel, initconv_from_la);

	CASE_CODEC_ALn(VIDEO_CODEC_AL88,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0xff00),
	                /* vcs_gmask */ MASK2_LE(0xff00),
	                /* vcs_bmask */ MASK2_LE(0xff00),
	                /* vcs_amask */ MASK2_LE(0x00ff)),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               al88_pixel2color, al88_color2pixel, initconv_from_la);




	/* 4-byte-per-pixel formats. */
	CASE_CODEC_ALn(VIDEO_CODEC_RGBA8888,
	               (VIDEO_CODEC_FLAG_NORMAL | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 32,
	                /* vcs_cbits */ 32,
	                /* vcs_rmask */ MASK4_LE(0x000000ff),
	                /* vcs_gmask */ MASK4_LE(0x0000ff00),
	                /* vcs_bmask */ MASK4_LE(0x00ff0000),
	                /* vcs_amask */ MASK4_LE(0xff000000)),
	               4, buffer32_requirements,
	               getpixel32, setpixel32, rectcopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32, unaligned_rectcopy32,
	               unaligned_linefill32, unaligned_vertfill32, unaligned_rectfill32,
	               identity_pixel2color, identity_color2pixel, initconv_from_rgba);

	CASE_CODEC_ALn(VIDEO_CODEC_RGBX8888,
	               (VIDEO_CODEC_FLAG_NORMAL | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 32,
	                /* vcs_cbits */ 24,
	                /* vcs_rmask */ MASK4_LE(0x000000ff),
	                /* vcs_gmask */ MASK4_LE(0x0000ff00),
	                /* vcs_bmask */ MASK4_LE(0x00ff0000),
	                /* vcs_amask */ 0),
	               4, buffer32_requirements,
	               getpixel32, setpixel32, rectcopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32, unaligned_rectcopy32,
	               unaligned_linefill32, unaligned_vertfill32, unaligned_rectfill32,
	               rgbx8888_pixel2color, identity_color2pixel, initconv_from_rgb);

	CASE_CODEC_ALn(VIDEO_CODEC_ARGB8888,
	               (VIDEO_CODEC_FLAG_NORMAL | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 32,
	                /* vcs_cbits */ 32,
	                /* vcs_rmask */ MASK4_LE(0x0000ff00),
	                /* vcs_gmask */ MASK4_LE(0x00ff0000),
	                /* vcs_bmask */ MASK4_LE(0xff000000),
	                /* vcs_amask */ MASK4_LE(0x000000ff)),
	               4, buffer32_requirements,
	               getpixel32, setpixel32, rectcopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32, unaligned_rectcopy32,
	               unaligned_linefill32, unaligned_vertfill32, unaligned_rectfill32,
	               argb8888_pixel2color, argb8888_color2pixel, initconv_from_rgba);

	CASE_CODEC_ALn(VIDEO_CODEC_XRGB8888,
	               (VIDEO_CODEC_FLAG_NORMAL | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 32,
	                /* vcs_cbits */ 24,
	                /* vcs_rmask */ MASK4_LE(0x0000ff00),
	                /* vcs_gmask */ MASK4_LE(0x00ff0000),
	                /* vcs_bmask */ MASK4_LE(0xff000000),
	                /* vcs_amask */ 0),
	               4, buffer32_requirements,
	               getpixel32, setpixel32, rectcopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32, unaligned_rectcopy32,
	               unaligned_linefill32, unaligned_vertfill32, unaligned_rectfill32,
	               xrgb8888_pixel2color, xrgb8888_color2pixel, initconv_from_rgb);

	CASE_CODEC_ALn(VIDEO_CODEC_ABGR8888,
	               (VIDEO_CODEC_FLAG_NORMAL | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 32,
	                /* vcs_cbits */ 32,
	                /* vcs_rmask */ MASK4_LE(0xff000000),
	                /* vcs_gmask */ MASK4_LE(0x00ff0000),
	                /* vcs_bmask */ MASK4_LE(0x0000ff00),
	                /* vcs_amask */ MASK4_LE(0x000000ff)),
	               4, buffer32_requirements,
	               getpixel32, setpixel32, rectcopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32, unaligned_rectcopy32,
	               unaligned_linefill32, unaligned_vertfill32, unaligned_rectfill32,
	               abgr8888_pixel2color, abgr8888_color2pixel, initconv_from_rgba);

	CASE_CODEC_ALn(VIDEO_CODEC_XBGR8888,
	               (VIDEO_CODEC_FLAG_NORMAL | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 32,
	                /* vcs_cbits */ 24,
	                /* vcs_rmask */ MASK4_LE(0xff000000),
	                /* vcs_gmask */ MASK4_LE(0x00ff0000),
	                /* vcs_bmask */ MASK4_LE(0x0000ff00),
	                /* vcs_amask */ 0),
	               4, buffer32_requirements,
	               getpixel32, setpixel32, rectcopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32, unaligned_rectcopy32,
	               unaligned_linefill32, unaligned_vertfill32, unaligned_rectfill32,
	               xbgr8888_pixel2color, xbgr8888_color2pixel, initconv_from_rgb);

	CASE_CODEC_ALn(VIDEO_CODEC_BGRA8888,
	               (VIDEO_CODEC_FLAG_NORMAL | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 32,
	                /* vcs_cbits */ 32,
	                /* vcs_rmask */ MASK4_LE(0x00ff0000),
	                /* vcs_gmask */ MASK4_LE(0x0000ff00),
	                /* vcs_bmask */ MASK4_LE(0x000000ff),
	                /* vcs_amask */ MASK4_LE(0xff000000)),
	               4, buffer32_requirements,
	               getpixel32, setpixel32, rectcopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32, unaligned_rectcopy32,
	               unaligned_linefill32, unaligned_vertfill32, unaligned_rectfill32,
	               bgra8888_pixel2color, bgra8888_color2pixel, initconv_from_rgba);

	CASE_CODEC_ALn(VIDEO_CODEC_BGRX8888,
	               (VIDEO_CODEC_FLAG_NORMAL | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 32,
	                /* vcs_cbits */ 24,
	                /* vcs_rmask */ MASK4_LE(0x00ff0000),
	                /* vcs_gmask */ MASK4_LE(0x0000ff00),
	                /* vcs_bmask */ MASK4_LE(0x000000ff),
	                /* vcs_amask */ 0),
	               4, buffer32_requirements,
	               getpixel32, setpixel32, rectcopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32, unaligned_rectcopy32,
	               unaligned_linefill32, unaligned_vertfill32, unaligned_rectfill32,
	               bgrx8888_pixel2color, bgrx8888_color2pixel, initconv_from_rgb);



	/* 2-byte-per-pixel formats. */
	CASE_CODEC_ALn(VIDEO_CODEC_RGBA4444,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0x000f),
	                /* vcs_gmask */ MASK2_LE(0x00f0),
	                /* vcs_bmask */ MASK2_LE(0x0f00),
	                /* vcs_amask */ MASK2_LE(0xf000)),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               rgba4444_pixel2color, rgba4444_color2pixel, initconv_from_rgba);

	CASE_CODEC_ALn(VIDEO_CODEC_RGBX4444,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 12,
	                /* vcs_rmask */ MASK2_LE(0x000f),
	                /* vcs_gmask */ MASK2_LE(0x00f0),
	                /* vcs_bmask */ MASK2_LE(0x0f00),
	                /* vcs_amask */ 0),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               rgbx4444_pixel2color, rgbx4444_color2pixel, initconv_from_rgb);

	CASE_CODEC_ALn(VIDEO_CODEC_ARGB4444,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0x00f0),
	                /* vcs_gmask */ MASK2_LE(0x0f00),
	                /* vcs_bmask */ MASK2_LE(0xf000),
	                /* vcs_amask */ MASK2_LE(0x000f)),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               argb4444_pixel2color, argb4444_color2pixel, initconv_from_rgba);

	CASE_CODEC_ALn(VIDEO_CODEC_XRGB4444,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 12,
	                /* vcs_rmask */ MASK2_LE(0x00f0),
	                /* vcs_gmask */ MASK2_LE(0x0f00),
	                /* vcs_bmask */ MASK2_LE(0xf000),
	                /* vcs_amask */ 0),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               xrgb4444_pixel2color, xrgb4444_color2pixel, initconv_from_rgb);

	CASE_CODEC_ALn(VIDEO_CODEC_ABGR4444,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0xf000),
	                /* vcs_gmask */ MASK2_LE(0x0f00),
	                /* vcs_bmask */ MASK2_LE(0x00f0),
	                /* vcs_amask */ MASK2_LE(0x000f)),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               abgr4444_pixel2color, abgr4444_color2pixel, initconv_from_rgba);

	CASE_CODEC_ALn(VIDEO_CODEC_XBGR4444,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 12,
	                /* vcs_rmask */ MASK2_LE(0xf000),
	                /* vcs_gmask */ MASK2_LE(0x0f00),
	                /* vcs_bmask */ MASK2_LE(0x00f0),
	                /* vcs_amask */ 0),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               xbgr4444_pixel2color, xbgr4444_color2pixel, initconv_from_rgb);

	CASE_CODEC_ALn(VIDEO_CODEC_BGRA4444,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0x0f00),
	                /* vcs_gmask */ MASK2_LE(0x00f0),
	                /* vcs_bmask */ MASK2_LE(0x000f),
	                /* vcs_amask */ MASK2_LE(0xf000)),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               bgra4444_pixel2color, bgra4444_color2pixel, initconv_from_rgba);

	CASE_CODEC_ALn(VIDEO_CODEC_BGRX4444,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 12,
	                /* vcs_rmask */ MASK2_LE(0x0f00),
	                /* vcs_gmask */ MASK2_LE(0x00f0),
	                /* vcs_bmask */ MASK2_LE(0x000f),
	                /* vcs_amask */ 0),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               bgrx4444_pixel2color, bgrx4444_color2pixel, initconv_from_rgb);

	CASE_CODEC_ALn(VIDEO_CODEC_RGBA5551,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0x001f),
	                /* vcs_gmask */ MASK2_LE(0x03e0),
	                /* vcs_bmask */ MASK2_LE(0x7c00),
	                /* vcs_amask */ MASK2_LE(0x8000)),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               rgba5551_pixel2color, rgba5551_color2pixel, initconv_from_rgba);

	CASE_CODEC_ALn(VIDEO_CODEC_RGBX5551,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 15,
	                /* vcs_rmask */ MASK2_LE(0x001f),
	                /* vcs_gmask */ MASK2_LE(0x03e0),
	                /* vcs_bmask */ MASK2_LE(0x7c00),
	                /* vcs_amask */ 0),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               rgbx5551_pixel2color, rgbx5551_color2pixel, initconv_from_rgb);

	CASE_CODEC_ALn(VIDEO_CODEC_ARGB1555,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0x003e),
	                /* vcs_gmask */ MASK2_LE(0x07c0),
	                /* vcs_bmask */ MASK2_LE(0xf800),
	                /* vcs_amask */ MASK2_LE(0x0001)),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               argb1555_pixel2color, argb1555_color2pixel, initconv_from_rgba);

	CASE_CODEC_ALn(VIDEO_CODEC_XRGB1555,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 15,
	                /* vcs_rmask */ MASK2_LE(0x003e),
	                /* vcs_gmask */ MASK2_LE(0x07c0),
	                /* vcs_bmask */ MASK2_LE(0xf800),
	                /* vcs_amask */ 0),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               xrgb1555_pixel2color, xrgb1555_color2pixel, initconv_from_rgb);

	CASE_CODEC_ALn(VIDEO_CODEC_ABGR1555,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0xf800),
	                /* vcs_gmask */ MASK2_LE(0x07c0),
	                /* vcs_bmask */ MASK2_LE(0x003e),
	                /* vcs_amask */ MASK2_LE(0x0001)),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               abgr1555_pixel2color, abgr1555_color2pixel, initconv_from_rgba);

	CASE_CODEC_ALn(VIDEO_CODEC_XBGR1555,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 15,
	                /* vcs_rmask */ MASK2_LE(0xf800),
	                /* vcs_gmask */ MASK2_LE(0x07c0),
	                /* vcs_bmask */ MASK2_LE(0x003e),
	                /* vcs_amask */ 0),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               xbgr1555_pixel2color, xbgr1555_color2pixel, initconv_from_rgb);

	CASE_CODEC_ALn(VIDEO_CODEC_BGRA5551,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0x7c00),
	                /* vcs_gmask */ MASK2_LE(0x03e0),
	                /* vcs_bmask */ MASK2_LE(0x001f),
	                /* vcs_amask */ MASK2_LE(0x8000)),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               bgra5551_pixel2color, bgra5551_color2pixel, initconv_from_rgba);

	CASE_CODEC_ALn(VIDEO_CODEC_BGRX5551,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 15,
	                /* vcs_rmask */ MASK2_LE(0x7c00),
	                /* vcs_gmask */ MASK2_LE(0x03e0),
	                /* vcs_bmask */ MASK2_LE(0x001f),
	                /* vcs_amask */ 0),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               bgrx5551_pixel2color, bgrx5551_color2pixel, initconv_from_rgb);

	CASE_CODEC_ALn(VIDEO_CODEC_RGB565,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0x001f),
	                /* vcs_gmask */ MASK2_LE(0x07e0),
	                /* vcs_bmask */ MASK2_LE(0xf800),
	                /* vcs_amask */ 0),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               rgb565_pixel2color, rgb565_color2pixel, initconv_from_rgb);

	CASE_CODEC_ALn(VIDEO_CODEC_BGR565,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0xf800),
	                /* vcs_gmask */ MASK2_LE(0x07e0),
	                /* vcs_bmask */ MASK2_LE(0x001f),
	                /* vcs_amask */ 0),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               bgr565_pixel2color, bgr565_color2pixel, initconv_from_rgb);



	/* 3-byte-per-pixel formats. */
	CASE_CODEC_AL1(VIDEO_CODEC_RGB888,
	               (VIDEO_CODEC_FLAG_NORMAL | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 24,
	                /* vcs_cbits */ 24,
	                /* vcs_rmask */ MASK3_LE(0x0000ff),
	                /* vcs_gmask */ MASK3_LE(0x00ff00),
	                /* vcs_bmask */ MASK3_LE(0xff0000),
	                /* vcs_amask */ 0),
	               buffer24_requirements,
	               getpixel24, setpixel24, rectcopy24,
	               linefill24, vertfill24, rectfill24,
	               rgb888_pixel2color, rgb888_color2pixel, initconv_from_rgb);

	CASE_CODEC_AL1(VIDEO_CODEC_BGR888,
	               (VIDEO_CODEC_FLAG_NORMAL | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 24,
	                /* vcs_cbits */ 24,
	                /* vcs_rmask */ MASK3_LE(0xff0000),
	                /* vcs_gmask */ MASK3_LE(0x00ff00),
	                /* vcs_bmask */ MASK3_LE(0x0000ff),
	                /* vcs_amask */ 0),
	               buffer24_requirements,
	               getpixel24, setpixel24, rectcopy24,
	               linefill24, vertfill24, rectfill24,
	               bgr888_pixel2color, bgr888_color2pixel, initconv_from_rgb);



	/* Palette-driven formats. */
	CASE_CODEC_AL1(VIDEO_CODEC_P1_LSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 1,
	                /* vcs_cbits */ 1,
	                /* vcs_rmask */ 0x1,
	                /* vcs_gmask */ 0x1,
	                /* vcs_bmask */ 0x1,
	                /* vcs_amask */ 0x0),
	               buffer1_requirements,
	               getpixel1_lsb, setpixel1_lsb, rectcopy1_lsb,
	               linefill1_lsb, vertfill1_lsb, rectfill1_lsb,
	               pal_pixel2color, pal_color2pixel, initconv_from_p);

	CASE_CODEC_AL1(VIDEO_CODEC_P1_MSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 1,
	                /* vcs_cbits */ 1,
	                /* vcs_rmask */ 0x1,
	                /* vcs_gmask */ 0x1,
	                /* vcs_bmask */ 0x1,
	                /* vcs_amask */ 0x0),
	               buffer1_requirements,
	               getpixel1_msb, setpixel1_msb, rectcopy1_msb,
	               linefill1_msb, vertfill1_msb, rectfill1_msb,
	               pal_pixel2color, pal_color2pixel, initconv_from_p);

	CASE_CODEC_AL1(VIDEO_CODEC_P2_LSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0x3,
	                /* vcs_gmask */ 0x3,
	                /* vcs_bmask */ 0x3,
	                /* vcs_amask */ 0x0),
	               buffer2_requirements,
	               getpixel2_lsb, setpixel2_lsb, rectcopy2_lsb,
	               linefill2_lsb, vertfill2_lsb, rectfill2_lsb,
	               pal_pixel2color, pal_color2pixel, initconv_from_p);

	CASE_CODEC_AL1(VIDEO_CODEC_P2_MSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0x3,
	                /* vcs_gmask */ 0x3,
	                /* vcs_bmask */ 0x3,
	                /* vcs_amask */ 0x0),
	               buffer2_requirements,
	               getpixel2_msb, setpixel2_msb, rectcopy2_msb,
	               linefill2_msb, vertfill2_msb, rectfill2_msb,
	               pal_pixel2color, pal_color2pixel, initconv_from_p);

	CASE_CODEC_AL1(VIDEO_CODEC_P4_LSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0xf,
	                /* vcs_gmask */ 0xf,
	                /* vcs_bmask */ 0xf,
	                /* vcs_amask */ 0x0),
	               buffer4_requirements,
	               getpixel4_lsb, setpixel4_lsb, rectcopy4_lsb,
	               linefill4_lsb, vertfill4_lsb, rectfill4_lsb,
	               pal_pixel2color, pal_color2pixel, initconv_from_p);

	CASE_CODEC_AL1(VIDEO_CODEC_P4_MSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0xf,
	                /* vcs_gmask */ 0xf,
	                /* vcs_bmask */ 0xf,
	                /* vcs_amask */ 0x0),
	               buffer4_requirements,
	               getpixel4_msb, setpixel4_msb, rectcopy4_msb,
	               linefill4_msb, vertfill4_msb, rectfill4_msb,
	               pal_pixel2color, pal_color2pixel, initconv_from_p);

	CASE_CODEC_AL1(VIDEO_CODEC_P8,
	               (VIDEO_CODEC_FLAG_PAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0xff,
	                /* vcs_gmask */ 0xff,
	                /* vcs_bmask */ 0xff,
	                /* vcs_amask */ 0x0),
	               buffer8_requirements,
	               getpixel8, setpixel8, rectcopy8,
	               linefill8, vertfill8, rectfill8,
	               pal_pixel2color, pal_color2pixel, initconv_from_p);

	CASE_CODEC_AL1(VIDEO_CODEC_PA11_MSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0x1,
	                /* vcs_gmask */ 0x1,
	                /* vcs_bmask */ 0x1,
	                /* vcs_amask */ 0x2),
	               buffer2_requirements,
	               getpixel2_msb, setpixel2_msb, rectcopy2_msb,
	               linefill2_msb, vertfill2_msb, rectfill2_msb,
	               ap11_pixel2color, ap11_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_PA11_LSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0x1,
	                /* vcs_gmask */ 0x1,
	                /* vcs_bmask */ 0x1,
	                /* vcs_amask */ 0x2),
	               buffer2_requirements,
	               getpixel2_lsb, setpixel2_lsb, rectcopy2_lsb,
	               linefill2_lsb, vertfill2_lsb, rectfill2_lsb,
	               ap11_pixel2color, ap11_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_AP11_MSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0x2,
	                /* vcs_gmask */ 0x2,
	                /* vcs_bmask */ 0x2,
	                /* vcs_amask */ 0x1),
	               buffer2_requirements,
	               getpixel2_msb, setpixel2_msb, rectcopy2_msb,
	               linefill2_msb, vertfill2_msb, rectfill2_msb,
	               pa11_pixel2color, pa11_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_AP11_LSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0x2,
	                /* vcs_gmask */ 0x2,
	                /* vcs_bmask */ 0x2,
	                /* vcs_amask */ 0x1),
	               buffer2_requirements,
	               getpixel2_lsb, setpixel2_lsb, rectcopy2_lsb,
	               linefill2_lsb, vertfill2_lsb, rectfill2_lsb,
	               pa11_pixel2color, pa11_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_PA22_MSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0x3,
	                /* vcs_gmask */ 0x3,
	                /* vcs_bmask */ 0x3,
	                /* vcs_amask */ 0xc),
	               buffer4_requirements,
	               getpixel4_lsb, setpixel4_lsb, rectcopy4_lsb,
	               linefill4_lsb, vertfill4_lsb, rectfill4_lsb,
	               pa22_pixel2color, pa22_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_PA22_LSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0x3,
	                /* vcs_gmask */ 0x3,
	                /* vcs_bmask */ 0x3,
	                /* vcs_amask */ 0xc),
	               buffer4_requirements,
	               getpixel4_msb, setpixel4_msb, rectcopy4_msb,
	               linefill4_msb, vertfill4_msb, rectfill4_msb,
	               pa22_pixel2color, pa22_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_AP22_MSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0xc,
	                /* vcs_gmask */ 0xc,
	                /* vcs_bmask */ 0xc,
	                /* vcs_amask */ 0x3),
	               buffer4_requirements,
	               getpixel4_msb, setpixel4_msb, rectcopy4_msb,
	               linefill4_msb, vertfill4_msb, rectfill4_msb,
	               ap22_pixel2color, ap22_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_AP22_LSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0xc,
	                /* vcs_gmask */ 0xc,
	                /* vcs_bmask */ 0xc,
	                /* vcs_amask */ 0x3),
	               buffer4_requirements,
	               getpixel4_lsb, setpixel4_lsb, rectcopy4_lsb,
	               linefill4_lsb, vertfill4_lsb, rectfill4_lsb,
	               ap22_pixel2color, ap22_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_PA31_MSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0x7,
	                /* vcs_gmask */ 0x7,
	                /* vcs_bmask */ 0x7,
	                /* vcs_amask */ 0x8),
	               buffer4_requirements,
	               getpixel4_msb, setpixel4_msb, rectcopy4_msb,
	               linefill4_msb, vertfill4_msb, rectfill4_msb,
	               pa31_pixel2color, pa31_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_PA31_LSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0x7,
	                /* vcs_gmask */ 0x7,
	                /* vcs_bmask */ 0x7,
	                /* vcs_amask */ 0x8),
	               buffer4_requirements,
	               getpixel4_lsb, setpixel4_lsb, rectcopy4_lsb,
	               linefill4_lsb, vertfill4_lsb, rectfill4_lsb,
	               pa31_pixel2color, pa31_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_AP13_MSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0xe,
	                /* vcs_gmask */ 0xe,
	                /* vcs_bmask */ 0xe,
	                /* vcs_amask */ 0x1),
	               buffer4_requirements,
	               getpixel4_msb, setpixel4_msb, rectcopy4_msb,
	               linefill4_msb, vertfill4_msb, rectfill4_msb,
	               ap13_pixel2color, ap13_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_AP13_LSB,
	               (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0xe,
	                /* vcs_gmask */ 0xe,
	                /* vcs_bmask */ 0xe,
	                /* vcs_amask */ 0x1),
	               buffer4_requirements,
	               getpixel4_lsb, setpixel4_lsb, rectcopy4_lsb,
	               linefill4_lsb, vertfill4_lsb, rectfill4_lsb,
	               ap13_pixel2color, ap13_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_PA44,
	               (VIDEO_CODEC_FLAG_PAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0x0f,
	                /* vcs_gmask */ 0x0f,
	                /* vcs_bmask */ 0x0f,
	                /* vcs_amask */ 0xf0),
	               buffer8_requirements,
	               getpixel8, setpixel8, rectcopy8,
	               linefill8, vertfill8, rectfill8,
	               pa44_pixel2color, pa44_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_AP44,
	               (VIDEO_CODEC_FLAG_PAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0xf0,
	                /* vcs_gmask */ 0xf0,
	                /* vcs_bmask */ 0xf0,
	                /* vcs_amask */ 0x0f),
	               buffer8_requirements,
	               getpixel8, setpixel8, rectcopy8,
	               linefill8, vertfill8, rectfill8,
	               ap44_pixel2color, ap44_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_PA71,
	               (VIDEO_CODEC_FLAG_PAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0x7f,
	                /* vcs_gmask */ 0x7f,
	                /* vcs_bmask */ 0x7f,
	                /* vcs_amask */ 0x80),
	               buffer8_requirements,
	               getpixel8, setpixel8, rectcopy8,
	               linefill8, vertfill8, rectfill8,
	               pa71_pixel2color, pa71_color2pixel, initconv_from_pa);

	CASE_CODEC_AL1(VIDEO_CODEC_AP17,
	               (VIDEO_CODEC_FLAG_PAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0xfe,
	                /* vcs_gmask */ 0xfe,
	                /* vcs_bmask */ 0xfe,
	                /* vcs_amask */ 0x01),
	               buffer8_requirements,
	               getpixel8, setpixel8, rectcopy8,
	               linefill8, vertfill8, rectfill8,
	               ap17_pixel2color, ap17_color2pixel, initconv_from_pa);

	CASE_CODEC_ALn(VIDEO_CODEC_PA88,
	               (VIDEO_CODEC_FLAG_PAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0x00ff),
	                /* vcs_gmask */ MASK2_LE(0x00ff),
	                /* vcs_bmask */ MASK2_LE(0x00ff),
	                /* vcs_amask */ MASK2_LE(0xff00)),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               pa88_pixel2color, pa88_color2pixel, initconv_from_pa);

	CASE_CODEC_ALn(VIDEO_CODEC_AP88,
	               (VIDEO_CODEC_FLAG_PAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0xff00),
	                /* vcs_gmask */ MASK2_LE(0xff00),
	                /* vcs_bmask */ MASK2_LE(0xff00),
	                /* vcs_amask */ MASK2_LE(0x00ff)),
	               2, buffer16_requirements,
	               getpixel16, setpixel16, rectcopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16, unaligned_rectcopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               ap88_pixel2color, ap88_color2pixel, initconv_from_pa);

	default:
		result = NULL;
		break;
	}
	return result;
#undef CASE_CODEC_ALn
#undef CASE_CODEC_AL1
#undef _DEFINE_CODEC_ALX
#undef _DEFINE_CODEC_AL1
}




PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
pext_pal_pixel2color(struct video_format const *__restrict format,
                     video_pixel_t pixel) {
	video_pixel_t mask = format->vf_codec->vc_specs.vcs_rmask;
	video_pixel_t pixl = PEXT(pixel, mask);
	return pal_pixel2color(format, pixl);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
pdep_pal_color2pixel(struct video_format const *__restrict format,
                     video_color_t color) {
	video_pixel_t pixl = pal_color2pixel(format, color);
	video_pixel_t mask = format->vf_codec->vc_specs.vcs_rmask;
	return PDEP(pixl, mask);
}

LOCAL ATTR_CONST video_channel_t CC
pext_channel(video_pixel_t pixel,
             video_pixel_t mask,
             shift_t miss_bits) {
	video_channel_t result = PEXT(pixel, mask);
	return repeat_lsb(result, miss_bits);
}

LOCAL ATTR_CONST video_pixel_t CC
pdep_channel(video_channel_t chan,
             video_pixel_t used_mask,
             video_pixel_t xtra_mask) {
	video_pixel_t result = PDEP((video_pixel_t)chan, used_mask);
#if 1 /* Same as other impl, but without if-statements */
	result |= (video_pixel_t)(chan & 1) * xtra_mask;
#else
	if (chan & 1)
		result |= xtra_mask;
#endif
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
pext_pal_pixel2color__withalpha(struct video_format const *__restrict format,
                                video_pixel_t pixel) {
	struct video_codec_custom const *codec;
	video_color_t result = pext_pal_pixel2color(format, pixel);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
pal_pixel2color__withalpha(struct video_format const *__restrict format,
                           video_pixel_t pixel) {
	struct video_codec_custom const *codec;
	video_color_t result = pal_pixel2color(format, pixel);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
pal_color2pixel__withalpha(struct video_format const *__restrict format,
                           video_color_t color) {
	video_pixel_t result;
	struct video_codec_custom const *codec;
	result = pal_color2pixel(format, color);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
pdep_pal_color2pixel__withalpha(struct video_format const *__restrict format,
                                video_color_t color) {
	video_pixel_t result;
	struct video_codec_custom const *codec;
	result = pdep_pal_color2pixel(format, color);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}



PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
pext_gray4_pixel2color(struct video_format const *__restrict format,
                       video_pixel_t pixel) {
	video_pixel_t mask = format->vf_codec->vc_specs.vcs_rmask;
	video_pixel_t pixl = PEXT(pixel, mask);
	return l2_pixel2color(format, pixl);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
pdep_gray4_color2pixel(struct video_format const *__restrict format,
                       video_color_t color) {
	video_pixel_t pixl = l2_color2pixel(format, color);
	video_pixel_t mask = format->vf_codec->vc_specs.vcs_rmask;
	return PDEP(pixl, mask);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
pext_gray16_pixel2color(struct video_format const *__restrict format,
                        video_pixel_t pixel) {
	video_pixel_t mask = format->vf_codec->vc_specs.vcs_rmask;
	video_pixel_t pixl = PEXT(pixel, mask);
	return l4_pixel2color(format, pixl);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
pdep_gray16_color2pixel(struct video_format const *__restrict format,
                        video_color_t color) {
	video_pixel_t pixl = l4_color2pixel(format, color);
	video_pixel_t mask = format->vf_codec->vc_specs.vcs_rmask;
	return PDEP(pixl, mask);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
pext_gray256_pixel2color(struct video_format const *__restrict format,
                         video_pixel_t pixel) {
	video_pixel_t mask = format->vf_codec->vc_specs.vcs_rmask;
	video_pixel_t pixl = PEXT(pixel, mask);
	return l8_pixel2color(format, pixl);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
pdep_gray256_color2pixel(struct video_format const *__restrict format,
                         video_color_t color) {
	video_pixel_t pixl = l8_color2pixel(format, color);
	video_pixel_t mask = format->vf_codec->vc_specs.vcs_rmask;
	return PDEP(pixl, mask);
}



PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
gray2_pixel2color__withalpha(struct video_format const *__restrict format,
                             video_pixel_t pixel) {
	video_color_t result;
	struct video_codec_custom const *codec;
	result = l1_pixel2color(format, pixel);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
gray2_color2pixel__withalpha(struct video_format const *__restrict format,
                             video_color_t color) {
	video_pixel_t result;
	struct video_codec_custom const *codec;
	result = l1_color2pixel(format, color);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
gray4_pixel2color__withalpha(struct video_format const *__restrict format,
                             video_pixel_t pixel) {
	video_color_t result;
	struct video_codec_custom const *codec;
	result = l2_pixel2color(format, pixel);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
pext_gray4_pixel2color__withalpha(struct video_format const *__restrict format,
                                  video_pixel_t pixel) {
	video_color_t result;
	struct video_codec_custom const *codec;
	result = pext_gray4_pixel2color(format, pixel);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
gray4_color2pixel__withalpha(struct video_format const *__restrict format,
                             video_color_t color) {
	video_pixel_t result;
	struct video_codec_custom const *codec;
	result = l2_color2pixel(format, color);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
pdep_gray4_color2pixel__withalpha(struct video_format const *__restrict format,
                                  video_color_t color) {
	video_pixel_t result;
	struct video_codec_custom const *codec;
	result = pdep_gray4_color2pixel(format, color);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
gray16_pixel2color__withalpha(struct video_format const *__restrict format,
                              video_pixel_t pixel) {
	video_color_t result;
	struct video_codec_custom const *codec;
	result = l4_pixel2color(format, pixel);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
pext_gray16_pixel2color__withalpha(struct video_format const *__restrict format,
                                   video_pixel_t pixel) {
	video_color_t result;
	struct video_codec_custom const *codec;
	result = pext_gray16_pixel2color(format, pixel);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
gray16_color2pixel__withalpha(struct video_format const *__restrict format,
                              video_color_t color) {
	video_pixel_t result;
	struct video_codec_custom const *codec;
	result = l4_color2pixel(format, color);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
pdep_gray16_color2pixel__withalpha(struct video_format const *__restrict format,
                                   video_color_t color) {
	video_pixel_t result;
	struct video_codec_custom const *codec;
	result = pdep_gray16_color2pixel(format, color);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
gray256_pixel2color__withalpha(struct video_format const *__restrict format,
                               video_pixel_t pixel) {
	video_color_t result;
	struct video_codec_custom const *codec;
	result = l8_pixel2color(format, pixel);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
pext_gray256_pixel2color__withalpha(struct video_format const *__restrict format,
                                    video_pixel_t pixel) {
	video_color_t result;
	struct video_codec_custom const *codec;
	result = pext_gray256_pixel2color(format, pixel);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
gray256_color2pixel__withalpha(struct video_format const *__restrict format,
                               video_color_t color) {
	video_pixel_t result;
	struct video_codec_custom const *codec;
	result = l8_color2pixel(format, color);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
pdep_gray256_color2pixel__withalpha(struct video_format const *__restrict format,
                                    video_color_t color) {
	video_pixel_t result;
	struct video_codec_custom const *codec;
	result = pdep_gray256_color2pixel(format, color);
	codec  = (struct video_codec_custom const *)format->vf_codec;
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}


PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
pext_rgba_pixel2color(struct video_format const *__restrict format,
                      video_pixel_t pixel) {
	struct video_codec_custom const *codec = (struct video_codec_custom const *)format->vf_codec;
	video_channel_t r = pext_channel(pixel, codec->vcc_used_rmask, codec->vcc_miss_rbits);
	video_channel_t g = pext_channel(pixel, codec->vcc_used_gmask, codec->vcc_miss_gbits);
	video_channel_t b = pext_channel(pixel, codec->vcc_used_bmask, codec->vcc_miss_bbits);
	video_channel_t a = pext_channel(pixel, codec->vcc_used_amask, codec->vcc_miss_abits);
	return VIDEO_COLOR_RGBA(r, g, b, a);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
pdep_rgba_color2pixel(struct video_format const *__restrict format,
                      video_color_t color) {
	struct video_codec_custom const *codec = (struct video_codec_custom const *)format->vf_codec;
	video_channel_t r = VIDEO_COLOR_GET_RED(color);
	video_channel_t g = VIDEO_COLOR_GET_GREEN(color);
	video_channel_t b = VIDEO_COLOR_GET_BLUE(color);
	video_channel_t a = VIDEO_COLOR_GET_ALPHA(color);
	return pdep_channel(r, codec->vcc_used_rmask, codec->vcc_xtra_rmask) |
	       pdep_channel(g, codec->vcc_used_gmask, codec->vcc_xtra_gmask) |
	       pdep_channel(b, codec->vcc_used_bmask, codec->vcc_xtra_bmask) |
	       pdep_channel(a, codec->vcc_used_amask, codec->vcc_xtra_amask);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
pext_rgb_pixel2color(struct video_format const *__restrict format,
                     video_pixel_t pixel) {
	struct video_codec_custom const *codec = (struct video_codec_custom const *)format->vf_codec;
	video_channel_t r = pext_channel(pixel, codec->vcc_used_rmask, codec->vcc_miss_rbits);
	video_channel_t g = pext_channel(pixel, codec->vcc_used_gmask, codec->vcc_miss_gbits);
	video_channel_t b = pext_channel(pixel, codec->vcc_used_bmask, codec->vcc_miss_bbits);
	return VIDEO_COLOR_RGB(r, g, b);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
pdep_rgb_color2pixel(struct video_format const *__restrict format,
                     video_color_t color) {
	struct video_codec_custom const *codec = (struct video_codec_custom const *)format->vf_codec;
	video_channel_t r = VIDEO_COLOR_GET_RED(color);
	video_channel_t g = VIDEO_COLOR_GET_GREEN(color);
	video_channel_t b = VIDEO_COLOR_GET_BLUE(color);
	return pdep_channel(r, codec->vcc_used_rmask, codec->vcc_xtra_rmask) |
	       pdep_channel(g, codec->vcc_used_gmask, codec->vcc_xtra_gmask) |
	       pdep_channel(b, codec->vcc_used_bmask, codec->vcc_xtra_bmask);
}



/* Extra optimized paths */
#define HAVE_shft_channel_decode
#define HAVE_shft_channel_decode_nomiss

#ifdef HAVE_shft_channel_decode
LOCAL ATTR_CONST video_channel_t CC
shft_channel_decode(video_pixel_t pixel,
                    video_pixel_t mask,
                    shift_t shft,
                    shift_t miss_bits) {
	video_channel_t result = (pixel & mask) >> shft;
	return repeat_lsb(result, miss_bits);
}

#ifdef HAVE_shft_channel_decode_nomiss
LOCAL ATTR_CONST video_channel_t CC
shft_channel_decode_nomiss(video_pixel_t pixel,
                           video_pixel_t mask,
                           shift_t shft) {
	return (pixel & mask) >> shft;
}
#endif /* HAVE_shft_channel_decode_nomiss */

LOCAL ATTR_CONST video_pixel_t CC
shft_channel_encode(video_channel_t chan,
                    shift_t shft,
                    shift_t miss_bits) {
	return (video_pixel_t)(chan >> miss_bits) << shft;
}


PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
shft_rgb_pixel2color(struct video_format const *__restrict format,
                     video_pixel_t pixel) {
	struct video_codec_custom const *codec = (struct video_codec_custom const *)format->vf_codec;
	video_channel_t r = shft_channel_decode(pixel, codec->vcc_used_rmask, codec->vcc_shft_rmask, codec->vcc_miss_rbits);
	video_channel_t g = shft_channel_decode(pixel, codec->vcc_used_gmask, codec->vcc_shft_gmask, codec->vcc_miss_gbits);
	video_channel_t b = shft_channel_decode(pixel, codec->vcc_used_bmask, codec->vcc_shft_bmask, codec->vcc_miss_bbits);
	return VIDEO_COLOR_RGB(r, g, b);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
shft_rgba_pixel2color(struct video_format const *__restrict format,
                      video_pixel_t pixel) {
	struct video_codec_custom const *codec = (struct video_codec_custom const *)format->vf_codec;
	video_channel_t r = shft_channel_decode(pixel, codec->vcc_used_rmask, codec->vcc_shft_rmask, codec->vcc_miss_rbits);
	video_channel_t g = shft_channel_decode(pixel, codec->vcc_used_gmask, codec->vcc_shft_gmask, codec->vcc_miss_gbits);
	video_channel_t b = shft_channel_decode(pixel, codec->vcc_used_bmask, codec->vcc_shft_bmask, codec->vcc_miss_bbits);
	video_channel_t a = shft_channel_decode(pixel, codec->vcc_used_amask, codec->vcc_shft_amask, codec->vcc_miss_abits);
	return VIDEO_COLOR_RGBA(r, g, b, a);
}

#ifdef HAVE_shft_channel_decode_nomiss
PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
shft_rgb_pixel2color_nomiss(struct video_format const *__restrict format,
                            video_pixel_t pixel) {
	struct video_codec_custom const *codec = (struct video_codec_custom const *)format->vf_codec;
	video_channel_t r = shft_channel_decode_nomiss(pixel, codec->vcc_used_rmask, codec->vcc_shft_rmask);
	video_channel_t g = shft_channel_decode_nomiss(pixel, codec->vcc_used_gmask, codec->vcc_shft_gmask);
	video_channel_t b = shft_channel_decode_nomiss(pixel, codec->vcc_used_bmask, codec->vcc_shft_bmask);
	return VIDEO_COLOR_RGB(r, g, b);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
shft_rgba_pixel2color_nomiss(struct video_format const *__restrict format,
                             video_pixel_t pixel) {
	struct video_codec_custom const *codec = (struct video_codec_custom const *)format->vf_codec;
	video_channel_t r = shft_channel_decode_nomiss(pixel, codec->vcc_used_rmask, codec->vcc_shft_rmask);
	video_channel_t g = shft_channel_decode_nomiss(pixel, codec->vcc_used_gmask, codec->vcc_shft_gmask);
	video_channel_t b = shft_channel_decode_nomiss(pixel, codec->vcc_used_bmask, codec->vcc_shft_bmask);
	video_channel_t a = shft_channel_decode_nomiss(pixel, codec->vcc_used_amask, codec->vcc_shft_amask);
	return VIDEO_COLOR_RGBA(r, g, b, a);
}
#endif /* HAVE_shft_channel_decode_nomiss */

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
shft_rgb_color2pixel(struct video_format const *__restrict format,
                     video_color_t color) {
	struct video_codec_custom const *codec = (struct video_codec_custom const *)format->vf_codec;
	video_channel_t r = VIDEO_COLOR_GET_RED(color);
	video_channel_t g = VIDEO_COLOR_GET_GREEN(color);
	video_channel_t b = VIDEO_COLOR_GET_BLUE(color);
	return shft_channel_encode(r, codec->vcc_shft_rmask, codec->vcc_miss_rbits) |
	       shft_channel_encode(g, codec->vcc_shft_gmask, codec->vcc_miss_gbits) |
	       shft_channel_encode(b, codec->vcc_shft_bmask, codec->vcc_miss_bbits);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
shft_rgba_color2pixel(struct video_format const *__restrict format,
                      video_color_t color) {
	struct video_codec_custom const *codec = (struct video_codec_custom const *)format->vf_codec;
	video_channel_t r = VIDEO_COLOR_GET_RED(color);
	video_channel_t g = VIDEO_COLOR_GET_GREEN(color);
	video_channel_t b = VIDEO_COLOR_GET_BLUE(color);
	video_channel_t a = VIDEO_COLOR_GET_ALPHA(color);
	return shft_channel_encode(r, codec->vcc_shft_rmask, codec->vcc_miss_rbits) |
	       shft_channel_encode(g, codec->vcc_shft_gmask, codec->vcc_miss_gbits) |
	       shft_channel_encode(b, codec->vcc_shft_bmask, codec->vcc_miss_bbits) |
	       shft_channel_encode(a, codec->vcc_shft_amask, codec->vcc_miss_abits);
}
#endif /* HAVE_shft_channel_decode */



LOCAL ATTR_COLD NONNULL((2, 3, 4, 5)) void CC
video_codec_custom__init__usedmask(video_pixel_t spec_mask,    /* Channel mask, as per codec specs */
                                   video_pixel_t *p_used_mask, /* sub-mask of "spec_mask" of bits encodeable in "video_color_t" */
                                   video_pixel_t *p_xtra_mask, /* sub-mask of "spec_mask" of bits not encodeable in "video_color_t" */
                                   shift_t *p_miss_bits,       /* # of bits that'll be lost during color encode */
                                   shift_t *p_shft_mask) {     /* CLZ(spec_mask) when shift-encode/decode is possible; else (shift_t)-1 */
	shift_t pc = POPCOUNT(spec_mask);
	if (pc > 8) {
		/* Only use the  most significant  8 bits,  since
		 * that's as much as our "video_color_t" can hold */
		*p_used_mask = PDEP((video_pixel_t)VIDEO_CHANNEL_MAX << (pc - 8), spec_mask);
		*p_xtra_mask = spec_mask & ~*p_used_mask;
		*p_miss_bits = 0;
	} else {
		*p_used_mask = spec_mask;
		*p_xtra_mask = 0;
		*p_miss_bits = 8 - pc;
	}

	/* Check if this channel allows for bit shifting */
	*p_shft_mask = (shift_t)-1;
	if (*p_xtra_mask == 0) {
		if (spec_mask == 0) {
			*p_shft_mask = 0; /* Non-present channel */
		} else {
			shift_t chan_ctz = CTZ(spec_mask);
			video_pixel_t cont_bits = ((video_pixel_t)1 << pc) - 1;
			if (spec_mask == (cont_bits << chan_ctz)) {
				/* Channel bits are continuous */
				*p_shft_mask = chan_ctz;
			}
		}
	}
}

PRIVATE ATTR_COLD WUNUSED struct video_codec const *CC
builtin_codec_from_masks(video_pixel_t rmask,
                         video_pixel_t gmask,
                         video_pixel_t bmask,
                         video_pixel_t amask) {
	struct video_codec const *result;
	struct video_codec_specs specs;
	video_pixel_t fullmask;
	specs.vcs_flags = VIDEO_CODEC_FLAG_NORMAL;
	specs.vcs_rmask = rmask;
	specs.vcs_gmask = gmask;
	specs.vcs_bmask = bmask;
	specs.vcs_amask = amask;
	fullmask = rmask | gmask | bmask | amask;
	if (fullmask <= UINT32_C(0xffff)) {
		specs.vcs_bpp = 16;
	} else if (fullmask <= UINT32_C(0xffffff)) {
		specs.vcs_bpp = 24;
	} else {
		specs.vcs_bpp = 32;
	}
	specs.vcs_cbits = specs.vcs_bpp;
	result = libvideo_codec_lookup_specs(&specs);
	if (!result && specs.vcs_bpp == 24) {
		specs.vcs_bpp = 32; /* Try again for a 32-bit codec */
		result = libvideo_codec_lookup_specs(&specs);
	}
	return result;
}

PRIVATE ATTR_COLD ATTR_CONST WUNUSED bool CC
is_8bit_aligned(video_pixel_t mask) {
	return mask == UINT32_C(0x000000ff) ||
	       mask == UINT32_C(0x0000ff00) ||
	       mask == UINT32_C(0x00ff0000) ||
	       mask == UINT32_C(0xff000000);
}

/* Try to populate the following fields of `self' based on `self->vc_specs':
 * - vc_specs.vcs_pxsz
 * - vc_specs.vcs_cbits
 * - vc_codec  (always set `VIDEO_CODEC_CUSTOM')
 * - vc_nalgn  (set to "NULL" if an extra codec is needed here)
 * - vc_align
 * - vc_rambuffer_requirements
 * - vc_getpixel
 * - vc_setpixel
 * - vc_rectcopy
 * - vc_linefill
 * - vc_vertfill
 * - vc_rectfill
 * - vc_pixel2color
 * - vc_color2pixel
 * - vcc_*
 * As such, the caller need only initialize:
 * - vc_specs   (excluding the "vcs_pxsz" and "vcs_cbits" fields)
 *
 * @return: true:  Success -- all fields initialized
 * @return: false: Failure -- codec cannot be represented */
INTERN ATTR_COLD NONNULL((1)) bool CC
libvideo_codec_populate_custom(struct video_codec_custom *__restrict self,
                               bool populate_noalign) {
	self->vc_codec = VIDEO_CODEC_CUSTOM;
	self->vc_specs.vcs_pxsz = CEILDIV(self->vc_specs.vcs_bpp, NBBY);
	switch (self->vc_specs.vcs_bpp) {
	case 1:
		self->vc_align = 1;
		self->vc_rambuffer_requirements = &buffer1_requirements;
		if (VIDEO_CODEC_FLAG_ISLSB(self->vc_specs.vcs_flags)) {
			self->vc_getpixel = &getpixel1_lsb;
			self->vc_setpixel = &setpixel1_lsb;
			self->vc_rectcopy = &rectcopy1_lsb;
			self->vc_linefill = &linefill1_lsb;
			self->vc_vertfill = &vertfill1_lsb;
			self->vc_rectfill = &rectfill1_lsb;
		} else {
			self->vc_getpixel = &getpixel1_msb;
			self->vc_setpixel = &setpixel1_msb;
			self->vc_rectcopy = &rectcopy1_msb;
			self->vc_linefill = &linefill1_msb;
			self->vc_vertfill = &vertfill1_msb;
			self->vc_rectfill = &rectfill1_msb;
		}
		break;
	case 2:
		self->vc_align = 1;
		self->vc_rambuffer_requirements = &buffer2_requirements;
		if (VIDEO_CODEC_FLAG_ISLSB(self->vc_specs.vcs_flags)) {
			self->vc_getpixel = &getpixel2_lsb;
			self->vc_setpixel = &setpixel2_lsb;
			self->vc_rectcopy = &rectcopy2_lsb;
			self->vc_linefill = &linefill2_lsb;
			self->vc_vertfill = &vertfill2_lsb;
			self->vc_rectfill = &rectfill2_lsb;
		} else {
			self->vc_getpixel = &getpixel2_msb;
			self->vc_setpixel = &setpixel2_msb;
			self->vc_rectcopy = &rectcopy2_msb;
			self->vc_linefill = &linefill2_msb;
			self->vc_vertfill = &vertfill2_msb;
			self->vc_rectfill = &rectfill2_msb;
		}
		break;
	case 4:
		self->vc_align = 1;
		self->vc_rambuffer_requirements = &buffer4_requirements;
		if (VIDEO_CODEC_FLAG_ISLSB(self->vc_specs.vcs_flags)) {
			self->vc_getpixel = &getpixel4_lsb;
			self->vc_setpixel = &setpixel4_lsb;
			self->vc_rectcopy = &rectcopy4_lsb;
			self->vc_linefill = &linefill4_lsb;
			self->vc_vertfill = &vertfill4_lsb;
			self->vc_rectfill = &rectfill4_lsb;
		} else {
			self->vc_getpixel = &getpixel4_msb;
			self->vc_setpixel = &setpixel4_msb;
			self->vc_rectcopy = &rectcopy4_msb;
			self->vc_linefill = &linefill4_msb;
			self->vc_vertfill = &vertfill4_msb;
			self->vc_rectfill = &rectfill4_msb;
		}
		break;
	case 8:
		self->vc_align = 1;
		self->vc_rambuffer_requirements = &buffer8_requirements;
		self->vc_getpixel = &getpixel8;
		self->vc_setpixel = &setpixel8;
		self->vc_rectcopy = &rectcopy8;
		self->vc_linefill = &linefill8;
		self->vc_vertfill = &vertfill8;
		self->vc_rectfill = &rectfill8;
		break;
	case 16:
		self->vc_align = 2;
		self->vc_rambuffer_requirements = &buffer16_requirements;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		if (populate_noalign) {
			self->vc_getpixel = &unaligned_getpixel16;
			self->vc_setpixel = &unaligned_setpixel16;
			self->vc_rectcopy = &unaligned_rectcopy16;
			self->vc_linefill = &unaligned_linefill16;
			self->vc_vertfill = &unaligned_vertfill16;
			self->vc_rectfill = &unaligned_rectfill16;
		} else
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		{
			self->vc_getpixel = &getpixel16;
			self->vc_setpixel = &setpixel16;
			self->vc_rectcopy = &rectcopy16;
			self->vc_linefill = &linefill16;
			self->vc_vertfill = &vertfill16;
			self->vc_rectfill = &rectfill16;
		}
		break;
	case 24:
		self->vc_align = 1;
		self->vc_rambuffer_requirements = &buffer24_requirements;
		self->vc_getpixel = &getpixel24;
		self->vc_setpixel = &setpixel24;
		self->vc_rectcopy = &rectcopy24;
		self->vc_linefill = &linefill24;
		self->vc_vertfill = &vertfill24;
		self->vc_rectfill = &rectfill24;
		break;
	case 32:
		self->vc_align = 4;
		self->vc_rambuffer_requirements = &buffer32_requirements;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		if (populate_noalign) {
			self->vc_getpixel = &unaligned_getpixel32;
			self->vc_setpixel = &unaligned_setpixel32;
			self->vc_rectcopy = &unaligned_rectcopy32;
			self->vc_linefill = &unaligned_linefill32;
			self->vc_vertfill = &unaligned_vertfill32;
			self->vc_rectfill = &unaligned_rectfill32;
		} else
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		{
			self->vc_getpixel = &getpixel32;
			self->vc_setpixel = &setpixel32;
			self->vc_rectcopy = &rectcopy32;
			self->vc_linefill = &linefill32;
			self->vc_vertfill = &vertfill32;
			self->vc_rectfill = &rectfill32;
		}
		break;
	default:
		/* Impossible/Unsupported BPP */
		return false;
	}

	/* Fix  broken color masks -- only the least significant "vcs_bpp" bits
	 * can ever be read/written from  pixes to underlying memory.  Anything
	 * above that is impossible to store, so we may as well mask those bits
	 * away since there would be no way to store them anyways. */
	{
		video_pixel_t cmask;
		video_pixel_t bpp_mask = ((video_pixel_t)1 << self->vc_specs.vcs_bpp) - 1;
		self->vc_specs.vcs_rmask &= bpp_mask;
		self->vc_specs.vcs_gmask &= bpp_mask;
		self->vc_specs.vcs_bmask &= bpp_mask;
		self->vc_specs.vcs_amask &= bpp_mask;

		/* Fix color masks. */
		cmask = self->vc_specs.vcs_rmask |
		        self->vc_specs.vcs_gmask |
		        self->vc_specs.vcs_bmask;
		if (self->vc_specs.vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM)) {
			self->vc_specs.vcs_rmask = cmask;
			self->vc_specs.vcs_gmask = cmask;
			self->vc_specs.vcs_bmask = cmask;
			self->vc_specs.vcs_cbits = POPCOUNT(cmask);
		} else {
			cmask |= self->vc_specs.vcs_amask;
			self->vc_specs.vcs_cbits = POPCOUNT(cmask);
		}
	}


	/* Load effective color masks */
	video_codec_custom__init__usedmask(self->vc_specs.vcs_rmask,
	                                   &self->vcc_used_rmask,
	                                   &self->vcc_xtra_rmask,
	                                   &self->vcc_miss_rbits,
	                                   &self->vcc_shft_rmask);
	video_codec_custom__init__usedmask(self->vc_specs.vcs_gmask,
	                                   &self->vcc_used_gmask,
	                                   &self->vcc_xtra_gmask,
	                                   &self->vcc_miss_gbits,
	                                   &self->vcc_shft_gmask);
	video_codec_custom__init__usedmask(self->vc_specs.vcs_bmask,
	                                   &self->vcc_used_bmask,
	                                   &self->vcc_xtra_bmask,
	                                   &self->vcc_miss_bbits,
	                                   &self->vcc_shft_bmask);
	video_codec_custom__init__usedmask(self->vc_specs.vcs_amask,
	                                   &self->vcc_used_amask,
	                                   &self->vcc_xtra_amask,
	                                   &self->vcc_miss_abits,
	                                   &self->vcc_shft_amask);

	/* Check if the codec qualifies for INTERP8888 optimizations. */
	self->vc_specs.vcs_flags &= ~VIDEO_CODEC_FLAG_INTERP8888;
	if (!(self->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL) &&
	    is_8bit_aligned(self->vcc_used_rmask) && is_8bit_aligned(self->vcc_used_gmask) &&
	    is_8bit_aligned(self->vcc_used_bmask) && is_8bit_aligned(self->vcc_used_amask))
		self->vc_specs.vcs_flags |= VIDEO_CODEC_FLAG_INTERP8888;

	/* Select color <=> pixel conversion algorithm */
	if (self->vc_specs.vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM)) {
		/* cmask: Canonical mask */
		video_pixel_t cmask = ((video_pixel_t)1 << self->vc_specs.vcs_cbits) - 1;
		bool need_mask = (self->vc_specs.vcs_rmask & cmask) != cmask;
		bool ispal = (self->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL) != 0;
		if (self->vcc_used_amask) {
			/* Alpha channel is present */
			shift_t lumen_bits = self->vc_specs.vcs_cbits;

			/* Check if we have a dedicated color conversion function for this case */
			if (lumen_bits >= 1 && lumen_bits <= 8) {
				shift_t alpha_bits = POPCOUNT(self->vcc_used_amask);
				if (alpha_bits >= 1 && alpha_bits <= 8 && (self->vcc_used_amask & 1)) {
					bool alpha_first = (self->vcc_used_amask & 1);
					if (alpha_first) {
						video_pixel_t cmask_after_alpha = cmask << alpha_bits;
						if ((self->vc_specs.vcs_rmask & cmask_after_alpha) == cmask_after_alpha) {
							/* Looks like a usable alpha codec */
#define AL(n_alpha, n_lum) ((n_alpha - 1) | ((n_lum - 1) << 3))
							switch (AL(alpha_bits, lumen_bits)) {
							case AL(1, 1):
								self->vc_pixel2color = ispal ? &ap11_pixel2color : &al11_pixel2color;
								self->vc_color2pixel = ispal ? &ap11_color2pixel : &al11_color2pixel;
								goto got_p2c;
							case AL(2, 2):
								self->vc_pixel2color = ispal ? &ap22_pixel2color : &al22_pixel2color;
								self->vc_color2pixel = ispal ? &ap22_color2pixel : &al22_color2pixel;
								goto got_p2c;
							case AL(1, 3):
								self->vc_pixel2color = ispal ? &ap13_pixel2color : &al13_pixel2color;
								self->vc_color2pixel = ispal ? &ap13_color2pixel : &al13_color2pixel;
								goto got_p2c;
							case AL(4, 4):
								self->vc_pixel2color = ispal ? &ap44_pixel2color : &al44_pixel2color;
								self->vc_color2pixel = ispal ? &ap44_color2pixel : &al44_color2pixel;
								goto got_p2c;
							case AL(1, 7):
								self->vc_pixel2color = ispal ? &ap17_pixel2color : &al17_pixel2color;
								self->vc_color2pixel = ispal ? &ap17_color2pixel : &al17_color2pixel;
								goto got_p2c;
							case AL(8, 8):
								self->vc_pixel2color = ispal ? &ap88_pixel2color : &al88_pixel2color;
								self->vc_color2pixel = ispal ? &ap88_color2pixel : &al88_color2pixel;
								goto got_p2c;
							default: break;
							}
#undef AL
						}
					} else if (((self->vcc_used_amask >> lumen_bits) << lumen_bits) ==
					           ((self->vcc_used_amask))) {
						/* Alpha-after-lumen */
#define LA(n_lum, n_alpha) ((n_lum - 1) | ((n_alpha - 1) << 3))
						switch (LA(lumen_bits, alpha_bits)) {
						case LA(1, 1):
							self->vc_pixel2color = ispal ? &pa11_pixel2color : &la11_pixel2color;
							self->vc_color2pixel = ispal ? &pa11_color2pixel : &la11_color2pixel;
							goto got_p2c;
						case LA(2, 2):
							self->vc_pixel2color = ispal ? &pa22_pixel2color : &la22_pixel2color;
							self->vc_color2pixel = ispal ? &pa22_color2pixel : &la22_color2pixel;
							goto got_p2c;
						case LA(3, 1):
							self->vc_pixel2color = ispal ? &pa31_pixel2color : &la31_pixel2color;
							self->vc_color2pixel = ispal ? &pa31_color2pixel : &la31_color2pixel;
							goto got_p2c;
						case LA(4, 4):
							self->vc_pixel2color = ispal ? &pa44_pixel2color : &la44_pixel2color;
							self->vc_color2pixel = ispal ? &pa44_color2pixel : &la44_color2pixel;
							goto got_p2c;
						case LA(7, 1):
							self->vc_pixel2color = ispal ? &pa71_pixel2color : &la71_pixel2color;
							self->vc_color2pixel = ispal ? &pa71_color2pixel : &la71_color2pixel;
							goto got_p2c;
						case LA(8, 8):
							self->vc_pixel2color = ispal ? &pa88_pixel2color : &la88_pixel2color;
							self->vc_color2pixel = ispal ? &pa88_color2pixel : &la88_color2pixel;
							goto got_p2c;
						default: break;
						}
#undef LA
					}
				}
			}

			/* Fallback: use a generic color conversion function */
			if (ispal) {
				self->vc_pixel2color = need_mask ? &pext_pal_pixel2color__withalpha : &pal_pixel2color__withalpha;
				self->vc_color2pixel = need_mask ? &pdep_pal_color2pixel__withalpha : &pal_color2pixel__withalpha;
			} else if (self->vc_specs.vcs_cbits >= 8) {
				self->vc_pixel2color = need_mask ? &pext_gray256_pixel2color__withalpha : &gray256_pixel2color__withalpha;
				self->vc_color2pixel = need_mask ? &pdep_gray256_color2pixel__withalpha : &gray256_color2pixel__withalpha;
			} else if (self->vc_specs.vcs_cbits >= 4) {
				self->vc_pixel2color = need_mask ? &pext_gray16_pixel2color__withalpha : &gray16_pixel2color__withalpha;
				self->vc_color2pixel = need_mask ? &pdep_gray16_color2pixel__withalpha : &gray16_color2pixel__withalpha;
			} else if (self->vc_specs.vcs_cbits >= 2) {
				self->vc_pixel2color = need_mask ? &pext_gray4_pixel2color__withalpha : &gray4_pixel2color__withalpha;
				self->vc_color2pixel = need_mask ? &pdep_gray4_color2pixel__withalpha : &gray4_color2pixel__withalpha;
			} else {
				self->vc_pixel2color = &gray2_pixel2color__withalpha;
				self->vc_color2pixel = &gray2_color2pixel__withalpha;
			}
		} else {
			if (ispal) {
				self->vc_pixel2color = need_mask ? &pext_pal_pixel2color : &pal_pixel2color;
				self->vc_color2pixel = need_mask ? &pdep_pal_color2pixel : &pal_color2pixel;
			} else if (self->vc_specs.vcs_cbits >= 8) {
				self->vc_pixel2color = need_mask ? &pext_gray256_pixel2color : &l8_pixel2color;
				self->vc_color2pixel = need_mask ? &pdep_gray256_color2pixel : &l8_color2pixel;
			} else if (self->vc_specs.vcs_cbits >= 4) {
				self->vc_pixel2color = need_mask ? &pext_gray16_pixel2color : &l4_pixel2color;
				self->vc_color2pixel = need_mask ? &pdep_gray16_color2pixel : &l4_color2pixel;
			} else if (self->vc_specs.vcs_cbits >= 2) {
				self->vc_pixel2color = need_mask ? &pext_gray4_pixel2color : &l2_pixel2color;
				self->vc_color2pixel = need_mask ? &pdep_gray4_color2pixel : &l2_color2pixel;
			} else {
				self->vc_pixel2color = &l1_pixel2color;
				self->vc_color2pixel = &l1_color2pixel;
			}
		}
	} else {
		/* Fallback: must use generic PEXT/PDEP encode/decode functions. */
		bool has_alpha = self->vcc_used_amask != 0;
		self->vc_pixel2color = has_alpha ? &pext_rgba_pixel2color : &pext_rgb_pixel2color;
		self->vc_color2pixel = has_alpha ? &pdep_rgba_color2pixel : &pdep_rgb_color2pixel;

		/* Optimization for codecs where masks are continuous (meaning PDEP/PEXT aren't needed) */
#ifdef HAVE_shft_channel_decode
		if (self->vcc_shft_rmask != (shift_t)-1 && self->vcc_shft_gmask != (shift_t)-1 &&
		    self->vcc_shft_bmask != (shift_t)-1 && self->vcc_shft_amask != (shift_t)-1) {
#ifdef HAVE_shft_channel_decode_nomiss
				bool hasmiss = (self->vcc_miss_rbits | self->vcc_miss_gbits |
			                self->vcc_miss_bbits | self->vcc_miss_abits) != 0;
			if (!hasmiss) {
				self->vc_pixel2color = has_alpha ? &shft_rgba_pixel2color_nomiss
				                                 : &shft_rgb_pixel2color_nomiss;
			} else
#endif /* HAVE_shft_channel_decode_nomiss */
			{
				self->vc_pixel2color = has_alpha ? &shft_rgba_pixel2color
				                                 : &shft_rgb_pixel2color;
			}
			self->vc_color2pixel = has_alpha ? &shft_rgba_color2pixel
			                                 : &shft_rgb_color2pixel;
		}
#endif /* HAVE_shft_channel_decode */

		/* Check if there is a built-in full-color codec
		 * that  can encode/decode the used color masks. */
		{
			struct video_codec const *encode_codec;
			encode_codec = builtin_codec_from_masks(self->vc_specs.vcs_rmask,
			                                        self->vc_specs.vcs_gmask,
			                                        self->vc_specs.vcs_bmask,
			                                        self->vc_specs.vcs_amask);
			if (encode_codec) {
				self->vc_pixel2color = encode_codec->vc_pixel2color;
				self->vc_color2pixel = encode_codec->vc_color2pixel;
			} else {
				/* Even if no codec exists for the true masks, we might  still
				 * find one for the truncated decode-masks when the codec uses
				 * more than 8 bits for some channel. */
				struct video_codec const *decode_codec;
				decode_codec = builtin_codec_from_masks(self->vcc_used_rmask,
				                                        self->vcc_used_gmask,
				                                        self->vcc_used_bmask,
				                                        self->vcc_used_amask);
				if (decode_codec) {
					/* Cannot inherit "vc_color2pixel" because we have to repeat
					 * the least significant color bit into the channel's  extra
					 * color bits.
					 *
					 * "vc_pixel2color" can be inherited because it is a decoder
					 * that loads only  the most significant  (up-to) 8 bits  of
					 * each color channel. */
					self->vc_pixel2color = decode_codec->vc_pixel2color;
				}
			}
		}
	}
got_p2c:

	/* Figure out which pixel conversion init-function to use */
	if (self->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL) {
		self->vc_initconverter = self->vcc_used_amask ? &initconv_from_pa
		                                              : &initconv_from_p;
	} else if (self->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_LUM) {
		self->vc_initconverter = self->vcc_used_amask ? &initconv_from_la
		                                              : &initconv_from_l;
	} else {
		self->vc_initconverter = self->vcc_used_amask ? &initconv_from_rgba
		                                              : &initconv_from_rgb;
	}

	if (populate_noalign) {
		self->vc_nalgn = self;
		self->vc_align = 1;
	} else if (self->vc_align <= 1) {
		self->vc_nalgn = self;
	} else {
		self->vc_nalgn = NULL; /* Need an extra codec here */
	}
	return true;
}


DEFINE_PUBLIC_ALIAS(video_codec_lookup, libvideo_codec_lookup);

DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_CODECS_C */
