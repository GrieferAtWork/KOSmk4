/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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

#include <kos/kernel/types.h>
#include <kos/types.h>

#include <assert.h>
#include <string.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/palette.h>

#include "codecs.h"
#include "palette.h"

DECL_BEGIN

union pixel24 {
	video_pixel_t pixel;
	byte_t        bytes[3];
};

union color_data {
	video_color_t color;
	struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		u8 r;
		u8 g;
		u8 b;
		u8 a;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		u8 a;
		u8 b;
		u8 g;
		u8 r;
#endif
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
#define PIXEL_RD0(pixel)         ((pixel)&0xff)
#define PIXEL_RD1(pixel)         (((pixel) >> 8) & 0xff)
#define PIXEL_RD2(pixel)         (((pixel) >> 16) & 0xff)
#define PIXEL_RD3(pixel)         (((pixel) >> 24) & 0xff)
#define PIXEL_WR0(pixel, byte)   ((pixel) = ((pixel) & ~0x000000ff) | (byte))
#define PIXEL_WR1(pixel, byte)   ((pixel) = ((pixel) & ~0x0000ff00) | ((byte) << 8))
#define PIXEL_WR2(pixel, byte)   ((pixel) = ((pixel) & ~0x00ff0000) | ((byte) << 16))
#define PIXEL_WR3(pixel, byte)   ((pixel) = ((pixel) & ~0xff000000) | ((byte) << 24))
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define PIXEL_RD3(pixel)         ((pixel)&0xff)
#define PIXEL_RD2(pixel)         (((pixel) >> 8) & 0xff)
#define PIXEL_RD1(pixel)         (((pixel) >> 16) & 0xff)
#define PIXEL_RD0(pixel)         (((pixel) >> 24) & 0xff)
#define PIXEL_WR3(pixel, byte)   ((pixel) = ((pixel) & ~0x000000ff) | (byte))
#define PIXEL_WR2(pixel, byte)   ((pixel) = ((pixel) & ~0x0000ff00) | ((byte) << 8))
#define PIXEL_WR1(pixel, byte)   ((pixel) = ((pixel) & ~0x00ff0000) | ((byte) << 16))
#define PIXEL_WR0(pixel, byte)   ((pixel) = ((pixel) & ~0xff000000) | ((byte) << 24))
#endif



LOCAL ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel1_inbyte_lsb(byte_t const *__restrict byte,
                     shift_t shift) {
	assert(shift < 8);
	return (*byte >> shift) & 1;
}

LOCAL NONNULL((1)) void CC
setpixel1_inbyte_lsb(byte_t *__restrict byte,
                     shift_t shift,
                     video_pixel_t pixel) {
	byte_t newbyte;
	assert(shift < 8);
	newbyte = *byte;
	newbyte &= ~(1 << shift);
	newbyte |= ~((u8)(pixel & 1) << shift);
	*byte = newbyte;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel1_inbyte_msb(byte_t const *__restrict byte,
                     shift_t shift) {
	assert(shift < 8);
	return getpixel1_inbyte_lsb(byte, 7 - shift);
}

LOCAL NONNULL((1)) void CC
setpixel1_inbyte_msb(byte_t *__restrict byte,
                     shift_t shift,
                     video_pixel_t pixel) {
	assert(shift < 8);
	setpixel1_inbyte_lsb(byte, 7 - shift, pixel);
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
	return (*byte >> (7 - (shift * 2))) & 3;
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
	newbyte |= ~((u8)(pixel & 3) << shift);
	*byte = newbyte;
}

LOCAL NONNULL((1)) void CC
setpixel2_inbyte_msb(byte_t *__restrict byte,
                     shift_t shift,
                     video_pixel_t pixel) {
	byte_t newbyte;
	assert(shift < 4);
	newbyte = *byte;
	shift = (shift_t)(7 - (shift * 2));
	newbyte &= ~(3 << shift);
	newbyte |= ~((u8)(pixel & 3) << shift);
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
	return (*byte >> (7 - (shift * 4))) & 7;
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
	newbyte |= ~((u8)(pixel & 7) << shift);
	*byte = newbyte;
}

LOCAL NONNULL((1)) void CC
setpixel4_inbyte_msb(byte_t *__restrict byte,
                     shift_t shift,
                     video_pixel_t pixel) {
	byte_t newbyte;
	assert(shift < 2);
	newbyte = *byte;
	shift = (shift_t)(7 - (shift * 4));
	newbyte &= ~(7 << shift);
	newbyte |= ~((u8)(pixel & 7) << shift);
	*byte = newbyte;
}




PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel1_lsb(byte_t const *__restrict line, uintptr_t x) {
	return getpixel1_inbyte_lsb(line + (x / 8), (shift_t)(x % 8));
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel1_msb(byte_t const *__restrict line, uintptr_t x) {
	return getpixel1_inbyte_msb(line + (x / 8), (shift_t)(x % 8));
}

PRIVATE NONNULL((1)) void CC
setpixel1_lsb(byte_t *__restrict line, uintptr_t x, video_pixel_t pixel) {
	setpixel1_inbyte_lsb(line + (x / 8), (shift_t)(x % 8), pixel);
}

PRIVATE NONNULL((1)) void CC
setpixel1_msb(byte_t *__restrict line, uintptr_t x, video_pixel_t pixel) {
	setpixel1_inbyte_msb(line + (x / 8), (shift_t)(x % 8), pixel);
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel2_lsb(byte_t const *__restrict line, uintptr_t x) {
	return getpixel2_inbyte_lsb(line + (x / 4), x % 4);
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel2_msb(byte_t const *__restrict line, uintptr_t x) {
	return getpixel2_inbyte_msb(line + (x / 4), x % 4);
}

PRIVATE NONNULL((1)) void CC
setpixel2_lsb(byte_t *__restrict line, uintptr_t x, video_pixel_t pixel) {
	setpixel2_inbyte_lsb(line + (x / 4), x % 4, pixel);
}

PRIVATE NONNULL((1)) void CC
setpixel2_msb(byte_t *__restrict line, uintptr_t x, video_pixel_t pixel) {
	setpixel2_inbyte_msb(line + (x / 4), x % 4, pixel);
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel4_lsb(byte_t const *__restrict line, uintptr_t x) {
	return getpixel4_inbyte_lsb(line + (x / 2), x % 2);
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel4_msb(byte_t const *__restrict line, uintptr_t x) {
	return getpixel4_inbyte_msb(line + (x / 2), x % 2);
}

PRIVATE NONNULL((1)) void CC
setpixel4_lsb(byte_t *__restrict line, uintptr_t x, video_pixel_t pixel) {
	setpixel4_inbyte_lsb(line + (x / 2), x % 2, pixel);
}

PRIVATE NONNULL((1)) void CC
setpixel4_msb(byte_t *__restrict line, uintptr_t x, video_pixel_t pixel) {
	setpixel4_inbyte_msb(line + (x / 2), x % 2, pixel);
}




PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel8(byte_t const *__restrict line, uintptr_t x) {
	return ((u8 const *)line)[x];
}

PRIVATE NONNULL((1)) void CC
setpixel8(byte_t *__restrict line, uintptr_t x, video_pixel_t pixel) {
	((u8 *)line)[x] = (u8)pixel;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel16(byte_t const *__restrict line, uintptr_t x) {
	return ((u16 const *)line)[x];
}

PRIVATE NONNULL((1)) void CC
setpixel16(byte_t *__restrict line, uintptr_t x, video_pixel_t pixel) {
	((u16 *)line)[x] = (u16)pixel;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel24(byte_t const *__restrict line, uintptr_t x) {
	union pixel24 result;
	line += x * 3;
	result.bytes[0] = line[0];
	result.bytes[1] = line[1];
	result.bytes[2] = line[2];
	return result.pixel;
}

PRIVATE NONNULL((1)) void CC
setpixel24(byte_t *__restrict line, uintptr_t x, video_pixel_t pixel) {
	union pixel24 data;
	data.pixel = pixel;
	line += x * 3;
	line[0] = data.bytes[0];
	line[1] = data.bytes[1];
	line[2] = data.bytes[2];
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
getpixel32(byte_t const *__restrict line, uintptr_t x) {
	return ((u32 const *)line)[x];
}

PRIVATE NONNULL((1)) void CC
setpixel32(byte_t *__restrict line, uintptr_t x, video_pixel_t pixel) {
	((u32 *)line)[x] = (u32)pixel;
}



PRIVATE void CC
linecopy8(byte_t *__restrict dst_line, uintptr_t dst_x,
          byte_t const *__restrict src_line, uintptr_t src_x,
          size_t num_pixels) {
	memcpyb((u8 *)dst_line + dst_x,
	        (u8 *)src_line + src_x,
	         num_pixels);
}

PRIVATE void CC
linecopy16(byte_t *__restrict dst_line, uintptr_t dst_x,
           byte_t const *__restrict src_line, uintptr_t src_x,
           size_t num_pixels) {
	memcpyw((u16 *)dst_line + dst_x,
	        (u16 *)src_line + src_x,
	         num_pixels);
}

PRIVATE void CC
linecopy24(byte_t *__restrict dst_line, uintptr_t dst_x,
           byte_t const *__restrict src_line, uintptr_t src_x,
           size_t num_pixels) {
	memcpy((u8 *)dst_line + dst_x * 3,
	       (u8 *)src_line + src_x * 3,
	        num_pixels, 3);
}

PRIVATE void CC
linecopy32(byte_t *__restrict dst_line, uintptr_t dst_x,
           byte_t const *__restrict src_line, uintptr_t src_x,
           size_t num_pixels) {
	memcpyl((u32 *)dst_line + dst_x,
	        (u32 *)src_line + src_x,
	         num_pixels);
}




PRIVATE void CC
linefill8(byte_t *__restrict dst_line, uintptr_t dst_x,
          video_pixel_t pixel, size_t num_pixels) {
	memsetb((u8 *)dst_line + dst_x, (u8)pixel, num_pixels);
}

PRIVATE void CC
linefill16(byte_t *__restrict dst_line, uintptr_t dst_x,
           video_pixel_t pixel, size_t num_pixels) {
	memsetw((u16 *)dst_line + dst_x, (u16)pixel, num_pixels);
}

PRIVATE void CC
linefill24(byte_t *__restrict dst_line, uintptr_t dst_x,
           video_pixel_t pixel, size_t num_pixels) {
	union pixel24 data;
	size_t i;
	data.pixel = pixel;
	dst_line += dst_x * 3;
	for (i = 0; i < num_pixels; ++i) {
		dst_line[0] = data.bytes[0];
		dst_line[1] = data.bytes[1];
		dst_line[2] = data.bytes[2];
		dst_line += 3;
	}
}

PRIVATE void CC
linefill32(byte_t *__restrict dst_line, uintptr_t dst_x,
           video_pixel_t pixel, size_t num_pixels) {
	memsetl((u32 *)dst_line + dst_x, (u32)pixel, num_pixels);
}





PRIVATE ATTR_CONST WUNUSED NONNULL((1)) u32 CC
colorpixel_identity(struct video_format const *__restrict UNUSED(format),
                    u32 value) {
	return value;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
rgbx8888_pixel2color(struct video_format const *__restrict UNUSED(format),
                     video_pixel_t pixel) {
	return pixel | VIDEO_COLOR_ALPHA_MASK;
}

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define rgb888_pixel2color   rgbx8888_pixel2color
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
rgb888_pixel2color(struct video_format const *__restrict UNUSED(format),
                   video_pixel_t pixel) {
	return (pixel << 8) | VIDEO_COLOR_ALPHA_MASK;
}
#endif

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define rgb888_color2pixel  colorpixel_identity
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
rgb888_color2pixel(struct video_format const *__restrict UNUSED(format),
                   video_color_t color) {
	return color >> 8;
}
#endif



PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
argb8888_pixel2color(struct video_format const *__restrict UNUSED(format),
                     video_pixel_t pixel) {
	return BIGENDIAN_SHL((u32)pixel, 8) | BIGENDIAN_SHR((u32)pixel, 24);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
argb8888_color2pixel(struct video_format const *__restrict UNUSED(format),
                     video_color_t color) {
	return BIGENDIAN_SHR((u32)color, 8) | BIGENDIAN_SHL((u32)color, 24);
}


PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
xrgb8888_pixel2color(struct video_format const *__restrict UNUSED(format),
                     video_pixel_t pixel) {
	return BIGENDIAN_SHL((u32)pixel, 8) | VIDEO_COLOR_ALPHA_MASK;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
xrgb8888_color2pixel(struct video_format const *__restrict UNUSED(format),
                     video_color_t color) {
	return BIGENDIAN_SHR((u32)color, 8);
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
	PIXEL_WR0(result,data.a);
	PIXEL_WR1(result,data.b);
	PIXEL_WR2(result,data.g);
	PIXEL_WR3(result,data.r);
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
	PIXEL_WR1(result,data.b);
	PIXEL_WR2(result,data.g);
	PIXEL_WR3(result,data.r);
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
	PIXEL_WR0(result,data.b);
	PIXEL_WR1(result,data.g);
	PIXEL_WR2(result,data.r);
	PIXEL_WR3(result,data.a);
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
	PIXEL_WR0(result,data.b);
	PIXEL_WR1(result,data.g);
	PIXEL_WR2(result,data.r);
	return result;
}


#define bgr888_pixel2color bgrx8888_pixel2color
#define bgr888_color2pixel bgrx8888_color2pixel




#define VIDEO_CODEC_GRAY2_LSB  0x1001 /* 1-bit-per-pixel, least-significant-bit-first, black/white */
#define VIDEO_CODEC_GRAY2_MSB  0x1002 /* 1-bit-per-pixel, most-significant-bit-first, black/white */
#define VIDEO_CODEC_GRAY4_LSB  0x1003 /* 2-bit-per-pixel, least-significant-bit-first, 4-color grayscale (0=black; 3=white) */
#define VIDEO_CODEC_GRAY4_MSB  0x1004 /* 2-bit-per-pixel, most-significant-bit-first, 4-color grayscale (0=black; 3=white) */


PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
gray2_pixel2color(struct video_format const *__restrict UNUSED(format),
                  video_pixel_t pixel) {
	return pixel ? __UINT32_C(0xffffffff) : VIDEO_COLOR_ALPHA_MASK;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
gray2_color2pixel(struct video_format const *__restrict UNUSED(format),
                  video_color_t color) {
	union color_data data;
	data.color = color;
	return (((u32)data.r + (u32)data.g + (u32)data.b + 2) / 3) >= 128 ? 1 : 0;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
gray4_pixel2color(struct video_format const *__restrict UNUSED(format),
                  video_pixel_t pixel) {
	return VIDEO_COLOR_ALPHA_MASK |
	       ((__UINT32_C(0x22222222) & (VIDEO_COLOR_RED_MASK | VIDEO_COLOR_GREEN_MASK | VIDEO_COLOR_BLUE_MASK)) *
	        (pixel & 0x3));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
gray4_color2pixel(struct video_format const *__restrict UNUSED(format),
                  video_color_t color) {
	union color_data data;
	data.color = color;
	return (((u32)data.r + (u32)data.g + (u32)data.b + 2) / 3) >> 6;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
gray16_pixel2color(struct video_format const *__restrict UNUSED(format),
                   video_pixel_t pixel) {
	return VIDEO_COLOR_ALPHA_MASK |
	       ((__UINT32_C(0x11111111) & (VIDEO_COLOR_RED_MASK | VIDEO_COLOR_GREEN_MASK | VIDEO_COLOR_BLUE_MASK)) *
	        (pixel & 0xf));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
gray16_color2pixel(struct video_format const *__restrict UNUSED(format),
                   video_color_t color) {
	union color_data data;
	data.color = color;
	return (((u32)data.r + (u32)data.g + (u32)data.b + 2) / 3) >> 4;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC
gray256_pixel2color(struct video_format const *__restrict UNUSED(format),
                    video_pixel_t pixel) {
	return VIDEO_COLOR_ALPHA_MASK |
	       ((__UINT32_C(0x01010101) & (VIDEO_COLOR_RED_MASK | VIDEO_COLOR_GREEN_MASK | VIDEO_COLOR_BLUE_MASK)) *
	        (pixel & 0xff));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC
gray256_color2pixel(struct video_format const *__restrict UNUSED(format),
                    video_color_t color) {
	union color_data data;
	data.color = color;
	return (((u32)data.r + (u32)data.g + (u32)data.b + 2) / 3);
}




PRIVATE void CC
linecopy1_lsb(byte_t *__restrict dst_line, uintptr_t dst_x,
              byte_t const *__restrict src_line, uintptr_t src_x,
              size_t num_pixels) {
	dst_line += dst_x / 8;
	src_line += src_x / 8;
	dst_x %= 8;
	src_x %= 8;
	if (dst_x == src_x) {
		/* Same sub-byte offset (can use memcpy for larger areas) */
		if (dst_x != 0) {
			while (dst_x < 8) {
				video_pixel_t pixel;
				if (!num_pixels)
					return;
				pixel = getpixel1_inbyte_lsb(src_line, (shift_t)src_x);
				setpixel1_inbyte_lsb(dst_line, (shift_t)dst_x, pixel);
				++src_x;
				++dst_x;
				--num_pixels;
			}
		}
		/* Directly copy pixel data. */
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

PRIVATE void CC
linecopy1_msb(byte_t *__restrict dst_line, uintptr_t dst_x,
              byte_t const *__restrict src_line, uintptr_t src_x,
              size_t num_pixels) {
	dst_line += dst_x / 8;
	src_line += src_x / 8;
	dst_x %= 8;
	src_x %= 8;
	if (dst_x == src_x) {
		/* Same sub-byte offset (can use memcpy for larger areas) */
		if (dst_x != 0) {
			while (dst_x < 8) {
				video_pixel_t pixel;
				if (!num_pixels)
					return;
				pixel = getpixel1_inbyte_msb(src_line, (shift_t)src_x);
				setpixel1_inbyte_msb(dst_line, (shift_t)dst_x, pixel);
				++src_x;
				++dst_x;
				--num_pixels;
			}
		}
		/* Directly copy pixel data. */
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


PRIVATE void CC
linecopy2_lsb(byte_t *__restrict dst_line, uintptr_t dst_x,
              byte_t const *__restrict src_line, uintptr_t src_x,
              size_t num_pixels) {
	dst_line += dst_x / 4;
	src_line += src_x / 4;
	dst_x %= 4;
	src_x %= 4;
	if (dst_x == src_x) {
		/* Same sub-byte offset (can use memcpy for larger areas) */
		if (dst_x != 0) {
			while (dst_x < 4) {
				video_pixel_t pixel;
				if (!num_pixels)
					return;
				pixel = getpixel2_inbyte_lsb(src_line, (shift_t)src_x);
				setpixel2_inbyte_lsb(dst_line, (shift_t)dst_x, pixel);
				++src_x;
				++dst_x;
				--num_pixels;
			}
		}
		/* Directly copy pixel data. */
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

PRIVATE void CC
linecopy2_msb(byte_t *__restrict dst_line, uintptr_t dst_x,
              byte_t const *__restrict src_line, uintptr_t src_x,
              size_t num_pixels) {
	dst_line += dst_x / 4;
	src_line += src_x / 4;
	dst_x %= 4;
	src_x %= 4;
	if (dst_x == src_x) {
		/* Same sub-byte offset (can use memcpy for larger areas) */
		if (dst_x != 0) {
			while (dst_x < 4) {
				video_pixel_t pixel;
				if (!num_pixels)
					return;
				pixel = getpixel2_inbyte_msb(src_line, (shift_t)src_x);
				setpixel2_inbyte_msb(dst_line, (shift_t)dst_x, pixel);
				++src_x;
				++dst_x;
				--num_pixels;
			}
		}
		/* Directly copy pixel data. */
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

PRIVATE void CC
linecopy4_lsb(byte_t *__restrict dst_line, uintptr_t dst_x,
              byte_t const *__restrict src_line, uintptr_t src_x,
              size_t num_pixels) {
	dst_line += dst_x / 2;
	src_line += src_x / 2;
	dst_x %= 2;
	src_x %= 2;
	if (dst_x == src_x) {
		/* Same sub-byte offset (can use memcpy for larger areas) */
		if (dst_x != 0) {
			video_pixel_t pixel;
			assert(dst_x == 1);
			if (!num_pixels)
				return;
			pixel = getpixel4_inbyte_lsb(src_line, (shift_t)src_x);
			setpixel4_inbyte_lsb(dst_line, (shift_t)dst_x, pixel);
			++src_x;
			++dst_x;
			--num_pixels;
		}
		/* Directly copy pixel data. */
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

PRIVATE void CC
linecopy4_msb(byte_t *__restrict dst_line, uintptr_t dst_x,
              byte_t const *__restrict src_line, uintptr_t src_x,
              size_t num_pixels) {
	dst_line += dst_x / 2;
	src_line += src_x / 2;
	dst_x %= 2;
	src_x %= 2;
	if (dst_x == src_x) {
		/* Same sub-byte offset (can use memcpy for larger areas) */
		if (dst_x != 0) {
			video_pixel_t pixel;
			assert(dst_x == 1);
			if (!num_pixels)
				return;
			pixel = getpixel4_inbyte_msb(src_line, (shift_t)src_x);
			setpixel4_inbyte_msb(dst_line, (shift_t)dst_x, pixel);
			++src_x;
			++dst_x;
			--num_pixels;
		}
		/* Directly copy pixel data. */
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



PRIVATE void CC
linefill1_lsb(byte_t *__restrict dst_line, uintptr_t dst_x,
              video_pixel_t pixel, size_t num_pixels) {
	dst_line += dst_x / 8;
	dst_x %= 8;
	if (dst_x & 7) {
		do {
			setpixel1_inbyte_lsb(dst_line, dst_x, pixel);
		} while ((++dst_x) & 7);
		++dst_line;
	}
	dst_line = mempsetb(dst_line,
	                    0xff * (pixel & 0x1),
	                    num_pixels / 4);
	if (num_pixels & 7) {
		num_pixels &= 7;
		for (dst_x = 0; dst_x < num_pixels; ++dst_x)
			setpixel1_inbyte_lsb(dst_line, dst_x, pixel);
	}
}

PRIVATE void CC
linefill1_msb(byte_t *__restrict dst_line, uintptr_t dst_x,
              video_pixel_t pixel, size_t num_pixels) {
	dst_line += dst_x / 8;
	dst_x %= 8;
	if (dst_x & 7) {
		do {
			setpixel1_inbyte_msb(dst_line, dst_x, pixel);
		} while ((++dst_x) & 7);
		++dst_line;
	}
	dst_line = mempsetb(dst_line,
	                    0xff * (pixel & 0x1),
	                    num_pixels / 4);
	if (num_pixels & 7) {
		num_pixels &= 7;
		for (dst_x = 0; dst_x < num_pixels; ++dst_x)
			setpixel1_inbyte_msb(dst_line, dst_x, pixel);
	}
}


PRIVATE void CC
linefill2_lsb(byte_t *__restrict dst_line, uintptr_t dst_x,
              video_pixel_t pixel, size_t num_pixels) {
	dst_line += dst_x / 4;
	dst_x %= 4;
	if (dst_x & 3) {
		do {
			setpixel2_inbyte_lsb(dst_line, dst_x, pixel);
		} while ((++dst_x) & 3);
		++dst_line;
	}
	dst_line = mempsetb(dst_line,
	                    0x55 * (pixel & 0x3),
	                    num_pixels / 4);
	if (num_pixels & 3) {
		num_pixels &= 3;
		for (dst_x = 0; dst_x < num_pixels; ++dst_x)
			setpixel2_inbyte_lsb(dst_line, dst_x, pixel);
	}
}

PRIVATE void CC
linefill2_msb(byte_t *__restrict dst_line, uintptr_t dst_x,
              video_pixel_t pixel, size_t num_pixels) {
	dst_line += dst_x / 4;
	dst_x %= 4;
	if (dst_x & 3) {
		do {
			setpixel2_inbyte_msb(dst_line, dst_x, pixel);
		} while ((++dst_x) & 3);
		++dst_line;
	}
	dst_line = mempsetb(dst_line,
	                    0x55 * (pixel & 0x3),
	                    num_pixels / 4);
	if (num_pixels & 3) {
		num_pixels &= 3;
		for (dst_x = 0; dst_x < num_pixels; ++dst_x)
			setpixel2_inbyte_msb(dst_line, dst_x, pixel);
	}
}


PRIVATE void CC
linefill4_lsb(byte_t *__restrict dst_line, uintptr_t dst_x,
              video_pixel_t pixel, size_t num_pixels) {
	dst_line += dst_x / 2;
	dst_x %= 2;
	if (dst_x & 1) {
		setpixel4_inbyte_lsb(dst_line, 1, pixel);
		++dst_line;
	}
	dst_line = mempsetb(dst_line, pixel | (pixel << 4), num_pixels / 2);
	if (num_pixels & 1) {
		setpixel4_inbyte_lsb(dst_line, 0, pixel);
	}
}

PRIVATE void CC
linefill4_msb(byte_t *__restrict dst_line, uintptr_t dst_x,
              video_pixel_t pixel, size_t num_pixels) {
	dst_line += dst_x / 2;
	dst_x %= 2;
	if (dst_x & 1) {
		setpixel4_inbyte_msb(dst_line, 1, pixel);
		++dst_line;
	}
	dst_line = mempsetb(dst_line, pixel | (pixel << 4), num_pixels / 2);
	if (num_pixels & 1) {
		setpixel4_inbyte_msb(dst_line, 0, pixel);
	}
}



/* Extract 4-bit values from color codes */
#define COLOR_R4(color) (((color) >> (VIDEO_COLOR_RED_SHIFT + 4)) & 0xf)
#define COLOR_G4(color)	(((color) >> (VIDEO_COLOR_GREEN_SHIFT + 4)) & 0xf)
#define COLOR_B4(color)	(((color) >> (VIDEO_COLOR_BLUE_SHIFT + 4)) & 0xf)
#define COLOR_A4(color)	(((color) >> (VIDEO_COLOR_ALPHA_SHIFT + 4)) & 0xf)

#define DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGBA(name, datatype, union_type) \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC                         \
	name##_color2pixel(struct video_format const *__restrict UNUSED(format),         \
	                   video_color_t color) {                                        \
		union_type px;                                                               \
		px.r = COLOR_R4(color);                                                      \
		px.g = COLOR_G4(color);                                                      \
		px.b = COLOR_B4(color);                                                      \
		px.a = COLOR_A4(color);                                                      \
		return px.data;                                                              \
	}                                                                                \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC                         \
	name##_pixel2color(struct video_format const *__restrict UNUSED(format),         \
	                   video_pixel_t pixel) {                                        \
		union_type px;                                                               \
		px.data = (datatype)pixel;                                                   \
		return VIDEO_COLOR_RGBA(px.r, px.g, px.b, px.a);                             \
	}

#define DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGBX(name, datatype, union_type) \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC                         \
	name##_color2pixel(struct video_format const *__restrict UNUSED(format),         \
	                   video_color_t color) {                                        \
		union_type px;                                                               \
		px.r = COLOR_R4(color);                                                      \
		px.g = COLOR_G4(color);                                                      \
		px.b = COLOR_B4(color);                                                      \
		px.x = 0;                                                                    \
		return px.data;                                                              \
	}                                                                                \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC                         \
	name##_pixel2color(struct video_format const *__restrict UNUSED(format),         \
	                   video_pixel_t pixel) {                                        \
		union_type px;                                                               \
		px.data = (datatype)pixel;                                                   \
		return VIDEO_COLOR_RGB(px.r, px.g, px.b);                                    \
	}

#define DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGB(name, datatype, union_type) \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t CC                        \
	name##_color2pixel(struct video_format const *__restrict UNUSED(format),        \
	                   video_color_t color) {                                       \
		union_type px;                                                              \
		px.r = COLOR_R4(color);                                                     \
		px.g = COLOR_G4(color);                                                     \
		px.b = COLOR_B4(color);                                                     \
		return px.data;                                                             \
	}                                                                               \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t CC                        \
	name##_pixel2color(struct video_format const *__restrict UNUSED(format),        \
	                   video_pixel_t pixel) {                                       \
		union_type px;                                                              \
		px.data = (datatype)pixel;                                                  \
		return VIDEO_COLOR_RGB(px.r, px.g, px.b);                                   \
	}



#define DEFINE_FORMAT_PIXEL_UNION(name, datatype, ...) \
	union pixel_##name {                               \
		datatype data;                                 \
		struct __VA_ARGS__;                            \
	};
#define DEFINE_FORMAT_CONVERTER_RGBA(name, datatype, ...)  \
	DEFINE_FORMAT_PIXEL_UNION(name, datatype, __VA_ARGS__) \
	DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGBA(name, datatype, union pixel_##name)
#define DEFINE_FORMAT_CONVERTER_RGBX(name, datatype, ...)  \
	DEFINE_FORMAT_PIXEL_UNION(name, datatype, __VA_ARGS__) \
	DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGBX(name, datatype, union pixel_##name)
#define DEFINE_FORMAT_CONVERTER_RGB(name, datatype, ...)   \
	DEFINE_FORMAT_PIXEL_UNION(name, datatype, __VA_ARGS__) \
	DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGB(name, datatype, union pixel_##name)


DEFINE_FORMAT_CONVERTER_RGBA(rgba4444, u16, {
	__HYBRID_BITFIELD16_T r : 4;
	__HYBRID_BITFIELD16_T g : 4;
	__HYBRID_BITFIELD16_T b : 4;
	__HYBRID_BITFIELD16_T a : 4;
});
DEFINE_FORMAT_CONVERTER_RGBX(rgbx4444, u16, {
	__HYBRID_BITFIELD16_T r : 4;
	__HYBRID_BITFIELD16_T g : 4;
	__HYBRID_BITFIELD16_T b : 4;
	__HYBRID_BITFIELD16_T x : 4;
});
DEFINE_FORMAT_CONVERTER_RGBA(argb4444, u16, {
	__HYBRID_BITFIELD16_T a : 4;
	__HYBRID_BITFIELD16_T r : 4;
	__HYBRID_BITFIELD16_T g : 4;
	__HYBRID_BITFIELD16_T b : 4;
});
DEFINE_FORMAT_CONVERTER_RGBX(xrgb4444, u16, {
	__HYBRID_BITFIELD16_T x : 4;
	__HYBRID_BITFIELD16_T r : 4;
	__HYBRID_BITFIELD16_T g : 4;
	__HYBRID_BITFIELD16_T b : 4;
});
DEFINE_FORMAT_CONVERTER_RGBA(abgr4444, u16, {
	__HYBRID_BITFIELD16_T a : 4;
	__HYBRID_BITFIELD16_T b : 4;
	__HYBRID_BITFIELD16_T g : 4;
	__HYBRID_BITFIELD16_T r : 4;
});
DEFINE_FORMAT_CONVERTER_RGBX(xbgr4444, u16, {
	__HYBRID_BITFIELD16_T x : 4;
	__HYBRID_BITFIELD16_T b : 4;
	__HYBRID_BITFIELD16_T g : 4;
	__HYBRID_BITFIELD16_T r : 4;
});
DEFINE_FORMAT_CONVERTER_RGBA(bgra4444, u16, {
	__HYBRID_BITFIELD16_T b : 4;
	__HYBRID_BITFIELD16_T g : 4;
	__HYBRID_BITFIELD16_T r : 4;
	__HYBRID_BITFIELD16_T a : 4;
});
DEFINE_FORMAT_CONVERTER_RGBX(bgrx4444, u16, {
	__HYBRID_BITFIELD16_T b : 4;
	__HYBRID_BITFIELD16_T g : 4;
	__HYBRID_BITFIELD16_T r : 4;
	__HYBRID_BITFIELD16_T x : 4;
});


DEFINE_FORMAT_CONVERTER_RGBA(rgba5551, u16, {
	__HYBRID_BITFIELD16_T r : 5;
	__HYBRID_BITFIELD16_T g : 5;
	__HYBRID_BITFIELD16_T b : 5;
	__HYBRID_BITFIELD16_T a : 1;
});
DEFINE_FORMAT_CONVERTER_RGBX(rgbx5551, u16, {
	__HYBRID_BITFIELD16_T r : 5;
	__HYBRID_BITFIELD16_T g : 5;
	__HYBRID_BITFIELD16_T b : 5;
	__HYBRID_BITFIELD16_T x : 1;
});
DEFINE_FORMAT_CONVERTER_RGBA(argb1555, u16, {
	__HYBRID_BITFIELD16_T a : 1;
	__HYBRID_BITFIELD16_T r : 5;
	__HYBRID_BITFIELD16_T g : 5;
	__HYBRID_BITFIELD16_T b : 5;
});
DEFINE_FORMAT_CONVERTER_RGBX(xrgb1555, u16, {
	__HYBRID_BITFIELD16_T x : 1;
	__HYBRID_BITFIELD16_T r : 5;
	__HYBRID_BITFIELD16_T g : 5;
	__HYBRID_BITFIELD16_T b : 5;
});
DEFINE_FORMAT_CONVERTER_RGBA(abgr1555, u16, {
	__HYBRID_BITFIELD16_T a : 1;
	__HYBRID_BITFIELD16_T b : 5;
	__HYBRID_BITFIELD16_T g : 5;
	__HYBRID_BITFIELD16_T r : 5;
});
DEFINE_FORMAT_CONVERTER_RGBX(xbgr1555, u16, {
	__HYBRID_BITFIELD16_T x : 1;
	__HYBRID_BITFIELD16_T b : 5;
	__HYBRID_BITFIELD16_T g : 5;
	__HYBRID_BITFIELD16_T r : 5;
});
DEFINE_FORMAT_CONVERTER_RGBA(bgra5551, u16, {
	__HYBRID_BITFIELD16_T b : 5;
	__HYBRID_BITFIELD16_T g : 5;
	__HYBRID_BITFIELD16_T r : 5;
	__HYBRID_BITFIELD16_T a : 1;
});
DEFINE_FORMAT_CONVERTER_RGBX(bgrx5551, u16, {
	__HYBRID_BITFIELD16_T b : 5;
	__HYBRID_BITFIELD16_T g : 5;
	__HYBRID_BITFIELD16_T r : 5;
	__HYBRID_BITFIELD16_T x : 1;
});

DEFINE_FORMAT_CONVERTER_RGB(rgb565, u16, {
	__HYBRID_BITFIELD16_T r : 5;
	__HYBRID_BITFIELD16_T g : 6;
	__HYBRID_BITFIELD16_T b : 5;
});
DEFINE_FORMAT_CONVERTER_RGB(bgr565, u16, {
	__HYBRID_BITFIELD16_T b : 5;
	__HYBRID_BITFIELD16_T g : 6;
	__HYBRID_BITFIELD16_T r : 5;
});



PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_color_t CC
pal_pixel2color(struct video_format const *__restrict format,
                video_pixel_t pixel) {
	struct video_palette *pal;
	assert(format);
	pal = format->vf_pal;
	assert(pal);
	if (pixel >= pal->vp_cnt)
		return VIDEO_COLOR_RGB(0, 0, 0);
	return pal->vp_pal[pixel];
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
pal_color2pixel(struct video_format const *__restrict format,
                video_color_t color) {
	struct video_palette *pal;
	assert(format);
	pal = format->vf_pal;
	assert(pal);
	return libvideo_palette_getpixel(pal, color);
}


PRIVATE NONNULL((3)) void CC
buffer32_requirements(size_t size_x, size_t size_y,
                      struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = size_x * 4;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

PRIVATE NONNULL((3)) void CC
buffer24_requirements(size_t size_x, size_t size_y,
                      struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = size_x * 3;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

PRIVATE NONNULL((3)) void CC
buffer16_requirements(size_t size_x, size_t size_y,
                      struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = size_x * 2;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

PRIVATE NONNULL((3)) void CC
buffer8_requirements(size_t size_x, size_t size_y,
                     struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = size_x;
	result->vbs_bufsize = size_y * size_x;
}

PRIVATE NONNULL((3)) void CC
buffer4_requirements(size_t size_x, size_t size_y,
                     struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = (size_x + 1) / 2;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

PRIVATE NONNULL((3)) void CC
buffer2_requirements(size_t size_x, size_t size_y,
                     struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = (size_x + 3) / 4;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

PRIVATE NONNULL((3)) void CC
buffer1_requirements(size_t size_x, size_t size_y,
                     struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = (size_x + 7) / 8;
	result->vbs_bufsize = size_y * result->vbs_stride;
}



/* Lookup the interface for a given codec, or return NULL if the codec isn't supported. */
INTERN ATTR_CONST WUNUSED struct video_codec const *CC
libvideo_codec_lookup(video_codec_t codec) {
	struct video_codec const *result;
	switch (codec) {
#if defined(__KERNEL__) || (!defined(__PIC__) && !defined(__PIE__) && !defined(__pic__) && !defined(__pie__))
#define DEFINE_CODEC(codec, align, rambuffer_requirements,              \
                     getpixel, setpixel, linecopy, linefill,            \
                     pixel2color, color2pixel)                          \
	case codec: {                                                       \
		PRIVATE struct video_codec const _codec_##codec = {             \
			/* .vc_codec                  = */ codec,                   \
			/* ._vc_flags                 = */ VIDEO_CODEC_FLAG_NORMAL, \
			/* .vc_align                  = */ align,                   \
			/* .vc_rambuffer_requirements = */ &rambuffer_requirements, \
			/* .vc_getpixel               = */ &getpixel,               \
			/* .vc_setpixel               = */ &setpixel,               \
			/* .vc_linecopy               = */ &linecopy,               \
			/* .vc_linefill               = */ &linefill,               \
			/* .vc_pixel2color            = */ &pixel2color,            \
			/* .vc_color2pixel            = */ &color2pixel,            \
		};                                                              \
		result = &_codec_##codec;                                       \
	} break
#else
#define DEFINE_CODEC(codec, align, rambuffer_requirements,                      \
                     getpixel, setpixel, linecopy, linefill,                    \
                     pixel2color, color2pixel)                                  \
	case codec: {                                                               \
		PRIVATE struct video_codec _codec_##codec = {                           \
			/* .vc_codec  = */ codec,                                           \
			/* ._vc_flags = */ VIDEO_CODEC_FLAG_NORMAL,                         \
			/* .vc_align  = */ align                                            \
		};                                                                      \
		if (!_codec_##codec.vc_color2pixel) {                                   \
			/* Lazily initialize to prevent relocations */                      \
			_codec_##codec.vc_rambuffer_requirements = &rambuffer_requirements; \
			_codec_##codec.vc_getpixel               = &getpixel;               \
			_codec_##codec.vc_setpixel               = &setpixel;               \
			_codec_##codec.vc_linecopy               = &linecopy;               \
			_codec_##codec.vc_linefill               = &linefill;               \
			_codec_##codec.vc_pixel2color            = &pixel2color;            \
			COMPILER_WRITE_BARRIER();                                           \
			_codec_##codec.vc_color2pixel = &color2pixel;                       \
			COMPILER_WRITE_BARRIER();                                           \
		}                                                                       \
		result = &_codec_##codec;                                               \
	} break
#endif

	/* Grayscale formats. */
	DEFINE_CODEC(VIDEO_CODEC_GRAY2_LSB, 1, buffer1_requirements, getpixel1_lsb, setpixel1_lsb, linecopy1_lsb, linefill1_lsb, gray2_pixel2color, gray2_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_GRAY2_MSB, 1, buffer1_requirements, getpixel1_msb, setpixel1_msb, linecopy1_msb, linefill1_msb, gray2_pixel2color, gray2_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_GRAY4_LSB, 1, buffer2_requirements, getpixel2_lsb, setpixel2_lsb, linecopy2_lsb, linefill2_lsb, gray4_pixel2color, gray4_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_GRAY4_MSB, 1, buffer2_requirements, getpixel2_msb, setpixel2_msb, linecopy2_msb, linefill2_msb, gray4_pixel2color, gray4_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_GRAY16_LSB, 1, buffer4_requirements, getpixel4_lsb, setpixel4_lsb, linecopy4_lsb, linefill4_lsb, gray16_pixel2color, gray16_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_GRAY16_MSB, 1, buffer4_requirements, getpixel4_msb, setpixel4_msb, linecopy4_msb, linefill4_msb, gray16_pixel2color, gray16_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_GRAY256, 1, buffer8_requirements, getpixel8, setpixel8, linecopy8, linefill8, gray256_pixel2color, gray256_color2pixel);

	/* 4-byte-per-pixel formats. */
	DEFINE_CODEC(VIDEO_CODEC_RGBA8888, 4, buffer32_requirements, getpixel32, setpixel32, linecopy32, linefill32, colorpixel_identity, colorpixel_identity);
	DEFINE_CODEC(VIDEO_CODEC_RGBX8888, 4, buffer32_requirements, getpixel32, setpixel32, linecopy32, linefill32, rgbx8888_pixel2color, colorpixel_identity);
	DEFINE_CODEC(VIDEO_CODEC_ARGB8888, 4, buffer32_requirements, getpixel32, setpixel32, linecopy32, linefill32, argb8888_pixel2color, argb8888_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_XRGB8888, 4, buffer32_requirements, getpixel32, setpixel32, linecopy32, linefill32, xrgb8888_pixel2color, xrgb8888_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_ABGR8888, 4, buffer32_requirements, getpixel32, setpixel32, linecopy32, linefill32, abgr8888_pixel2color, abgr8888_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_XBGR8888, 4, buffer32_requirements, getpixel32, setpixel32, linecopy32, linefill32, xbgr8888_pixel2color, xbgr8888_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_BGRA8888, 4, buffer32_requirements, getpixel32, setpixel32, linecopy32, linefill32, bgra8888_pixel2color, bgra8888_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_BGRX8888, 4, buffer32_requirements, getpixel32, setpixel32, linecopy32, linefill32, bgrx8888_pixel2color, bgrx8888_color2pixel);

	DEFINE_CODEC(VIDEO_CODEC_RGBA4444, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, rgba4444_pixel2color, rgba4444_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_RGBX4444, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, rgbx4444_pixel2color, rgbx4444_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_ARGB4444, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, argb4444_pixel2color, argb4444_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_XRGB4444, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, xrgb4444_pixel2color, xrgb4444_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_ABGR4444, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, abgr4444_pixel2color, abgr4444_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_XBGR4444, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, xbgr4444_pixel2color, xbgr4444_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_BGRA4444, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, bgra4444_pixel2color, bgra4444_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_BGRX4444, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, bgrx4444_pixel2color, bgrx4444_color2pixel);

	DEFINE_CODEC(VIDEO_CODEC_RGBA5551, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, rgba5551_pixel2color, rgba5551_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_RGBX5551, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, rgbx5551_pixel2color, rgbx5551_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_ARGB1555, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, argb1555_pixel2color, argb1555_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_XRGB1555, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, xrgb1555_pixel2color, xrgb1555_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_ABGR1555, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, abgr1555_pixel2color, abgr1555_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_XBGR1555, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, xbgr1555_pixel2color, xbgr1555_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_BGRA5551, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, bgra5551_pixel2color, bgra5551_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_BGRX5551, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, bgrx5551_pixel2color, bgrx5551_color2pixel);

	DEFINE_CODEC(VIDEO_CODEC_RGB888, 1, buffer24_requirements, getpixel24, setpixel24, linecopy24, linefill24, rgb888_pixel2color, rgb888_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_BGR888, 1, buffer24_requirements, getpixel24, setpixel24, linecopy24, linefill24, bgr888_pixel2color, bgr888_color2pixel);

	DEFINE_CODEC(VIDEO_CODEC_RGB565, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, rgb565_pixel2color, rgb565_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_BGR565, 2, buffer16_requirements, getpixel16, setpixel16, linecopy16, linefill16, bgr565_pixel2color, bgr565_color2pixel);

	DEFINE_CODEC(VIDEO_CODEC_PAL2_LSB, 1, buffer1_requirements, getpixel1_lsb, setpixel1_lsb, linecopy1_lsb, linefill1_lsb, pal_pixel2color, pal_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_PAL2_MSB, 1, buffer1_requirements, getpixel1_msb, setpixel1_msb, linecopy1_msb, linefill1_msb, pal_pixel2color, pal_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_PAL4_LSB, 1, buffer2_requirements, getpixel2_lsb, setpixel2_lsb, linecopy2_lsb, linefill2_lsb, pal_pixel2color, pal_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_PAL4_MSB, 1, buffer2_requirements, getpixel2_msb, setpixel2_msb, linecopy2_msb, linefill2_msb, pal_pixel2color, pal_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_PAL16_LSB, 1, buffer4_requirements, getpixel4_lsb, setpixel4_lsb, linecopy4_lsb, linefill4_lsb, pal_pixel2color, pal_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_PAL16_MSB, 1, buffer4_requirements, getpixel4_msb, setpixel4_msb, linecopy4_msb, linefill4_msb, pal_pixel2color, pal_color2pixel);
	DEFINE_CODEC(VIDEO_CODEC_PAL256, 1, buffer8_requirements, getpixel8, setpixel8, linecopy8, linefill8, pal_pixel2color, pal_color2pixel);

#undef DEFINE_CODEC
	default:
		result = NULL;
	}
	return result;
}


DEFINE_PUBLIC_ALIAS(video_codec_lookup, libvideo_codec_lookup);


DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_CODECS_C */
