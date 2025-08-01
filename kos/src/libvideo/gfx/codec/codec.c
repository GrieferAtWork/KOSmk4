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
#ifndef GUARD_LIBVIDEO_GFX_CODEC_CODEC_C
#define GUARD_LIBVIDEO_GFX_CODEC_CODEC_C 1
#define __VIDEO_CODEC_const /* nothing */
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/__asm.h>
#include <hybrid/__bitfield.h>
#include <hybrid/align.h>
#include <hybrid/bit.h>
#include <hybrid/byteorder.h>
#include <hybrid/host.h>
#include <hybrid/unaligned.h>
#include <hybrid/wordbits.h>

#include <kos/types.h>
#include <sys/param.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libvideo/color.h>
#include <libvideo/gfx/api.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/codec/codec-extra.h>
#include <libvideo/gfx/codec/palette.h>
#include <libvideo/gfx/surface-defs.h>
#include <libvideo/gfx/surface.h>
#include <libvideo/types.h>

#include "codec-specs.h"
#include "codec-utils.h"
#include "codec.h"
#include "converter.h"
#include "palette.h"

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
/* SUB-8-BPP PIXEL OPERATORS                                            */
/************************************************************************/
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel1_msb(byte_t const *__restrict line, video_coord_t x);
PRIVATE NONNULL((1)) void FCC setpixel1_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
PRIVATE NONNULL((1)) void FCC linefill1_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
PRIVATE NONNULL((1)) void FCC vertfill1_msb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
PRIVATE NONNULL((1)) void FCC rectfill1_msb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 4)) void FCC rectcopy1_msb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 3)) void FCC rectmove1_msb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 3)) void FCC linecopy1_msb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel1_lsb(byte_t const *__restrict line, video_coord_t x);
PRIVATE NONNULL((1)) void FCC setpixel1_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
PRIVATE NONNULL((1)) void FCC linefill1_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
PRIVATE NONNULL((1)) void FCC vertfill1_lsb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
PRIVATE NONNULL((1)) void FCC rectfill1_lsb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 4)) void FCC rectcopy1_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 3)) void FCC rectmove1_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 3)) void FCC linecopy1_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel2_msb(byte_t const *__restrict line, video_coord_t x);
PRIVATE NONNULL((1)) void FCC setpixel2_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
PRIVATE NONNULL((1)) void FCC linefill2_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
PRIVATE NONNULL((1)) void FCC vertfill2_msb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
PRIVATE NONNULL((1)) void FCC rectfill2_msb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 4)) void FCC rectcopy2_msb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 3)) void FCC rectmove2_msb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 3)) void FCC linecopy2_msb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel2_lsb(byte_t const *__restrict line, video_coord_t x);
PRIVATE NONNULL((1)) void FCC setpixel2_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
PRIVATE NONNULL((1)) void FCC linefill2_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
PRIVATE NONNULL((1)) void FCC vertfill2_lsb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
PRIVATE NONNULL((1)) void FCC rectfill2_lsb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 4)) void FCC rectcopy2_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 3)) void FCC rectmove2_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 3)) void FCC linecopy2_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel4_msb(byte_t const *__restrict line, video_coord_t x);
PRIVATE NONNULL((1)) void FCC setpixel4_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
PRIVATE NONNULL((1)) void FCC linefill4_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
PRIVATE NONNULL((1)) void FCC vertfill4_msb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
PRIVATE NONNULL((1)) void FCC rectfill4_msb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 4)) void FCC rectcopy4_msb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 3)) void FCC rectmove4_msb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 3)) void FCC linecopy4_msb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC getpixel4_lsb(byte_t const *__restrict line, video_coord_t x);
PRIVATE NONNULL((1)) void FCC setpixel4_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
PRIVATE NONNULL((1)) void FCC linefill4_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel, video_dim_t num_pixels);
PRIVATE NONNULL((1)) void FCC vertfill4_lsb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t num_pixels);
PRIVATE NONNULL((1)) void FCC rectfill4_lsb(byte_t *__restrict line, video_coord_t x, size_t stride, video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 4)) void FCC rectcopy4_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride, byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 3)) void FCC rectmove4_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, size_t stride, video_dim_t size_x, video_dim_t size_y);
PRIVATE NONNULL((1, 3)) void FCC linecopy4_lsb(byte_t *__restrict dst_line, video_coord_t dst_x, byte_t const *__restrict src_line, video_coord_t src_x, video_dim_t size_x);

#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
#if defined(VIDEO_CODEC_HAVE__VC_SETPIXEL3_DUMMY) && !defined(__INTELLISENSE__)
#error "_vc_setpixel3 not supported by compiler, but enabled in features -- rebuild with 'CONFIG_NO_VIDEO_CODEC_HAVE__VC_SETPIXEL3'"
#endif /* VIDEO_CODEC_HAVE__VC_SETPIXEL3_DUMMY && !__INTELLISENSE__ */

/* Work around a GCC code generation inefficiency:
 * - For some reason, GCC always preserved "%ebx" in regparm(3)
 *   function under -fPIC, even when that register doesn't  end
 *   up being used.
 * - Since the function here are probably the most performance
 *   critical  ones in all  of KOS, work  around this issue by
 *   implementing the assembly for RP3 by hand.
 */
#undef USE_INLINE_386_ASSEMBLY_FOR_RP3
#if (defined(__COMPILER_HAVE_GCC_ASM) && defined(__ELF__) && \
     defined(__i386__) && !defined(__x86_64__) && 1)
#define USE_INLINE_386_ASSEMBLY_FOR_RP3
#endif /* ... */

PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel1_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel1_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel2_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel2_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel4_msb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC rp3_setpixel4_lsb(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */

#ifndef __INTELLISENSE__
DECL_END
#define DEFINE_BPP 1
#define DEFINE_MSB
#include "codecs-pixel-lt8.c.inl"
#define DEFINE_BPP 1
#define DEFINE_LSB
#include "codecs-pixel-lt8.c.inl"
#define DEFINE_BPP 2
#define DEFINE_MSB
#include "codecs-pixel-lt8.c.inl"
#define DEFINE_BPP 2
#define DEFINE_LSB
#include "codecs-pixel-lt8.c.inl"
#define DEFINE_BPP 4
#define DEFINE_MSB
#include "codecs-pixel-lt8.c.inl"
#define DEFINE_BPP 4
#define DEFINE_LSB
#include "codecs-pixel-lt8.c.inl"
DECL_BEGIN
#endif /* !__INTELLISENSE__ */




/************************************************************************/
/* 8BPP PIXEL OPERATORS                                                 */
/************************************************************************/

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
getpixel8(byte_t const *__restrict line, video_coord_t x) {
	return ((uint8_t const *)line)[x];
}

PRIVATE NONNULL((1)) void FCC
setpixel8(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	((uint8_t *)line)[x] = (uint8_t)pixel;
}

#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
#ifdef USE_INLINE_386_ASSEMBLY_FOR_RP3
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC
rp3_setpixel8(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
__ASM_BEGIN
__ASM_L(.text)
__ASM_L(.type rp3_setpixel8, @function)
__ASM_L(rp3_setpixel8:)
__ASM_L(	.cfi_startproc)
__ASM_L(	movb %cl, (%eax,%edx))
__ASM_L(	ret)
__ASM_L(	.cfi_endproc)
__ASM_L(.size rp3_setpixel8, .- rp3_setpixel8)
__ASM_END
#else /* USE_INLINE_386_ASSEMBLY_FOR_RP3 */
PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC
rp3_setpixel8(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	((uint8_t *)line)[x] = (uint8_t)pixel;
}
#endif /* !USE_INLINE_386_ASSEMBLY_FOR_RP3 */
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */

PRIVATE NONNULL((1)) void FCC
linefill8(byte_t *__restrict line, video_coord_t x,
          video_pixel_t pixel, video_dim_t num_pixels) {
	line += x;
	codec_assert(num_pixels > 0);
	memsetb(line, (uint8_t)pixel, num_pixels);
}

PRIVATE NONNULL((1)) void FCC
vertfill8(byte_t *__restrict line, video_coord_t x, size_t stride,
          video_pixel_t pixel, video_dim_t num_pixels) {
	line += x;
	codec_assert(num_pixels > 0);
	do {
		*(uint8_t *)line = (uint8_t)pixel;
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void FCC
rectfill8(byte_t *__restrict line, video_coord_t x, size_t stride,
          video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	line += x;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
#ifndef __OPTIMIZE_SIZE__
	if (stride == size_x) {
		memset(line, (uint8_t)pixel, size_x * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		do {
			memset(line, (uint8_t)pixel, size_x);
			line += stride;
		} while (--size_y);
	}
}

PRIVATE NONNULL((1, 4)) void FCC
rectcopy8(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
          byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
          video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x;
	src_line += src_x;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
#ifndef __OPTIMIZE_SIZE__
	if (dst_stride == src_stride && dst_stride == size_x) {
		/* Special case: can memcpy **all** pixel data in a single go */
		memcpyb(dst_line, src_line, size_x * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		do {
			memcpyb(dst_line, src_line, size_x);
			dst_line += dst_stride;
			src_line += src_stride;
		} while (--size_y);
	}
}

PRIVATE NONNULL((1, 3)) void FCC
rectmove8(byte_t *__restrict dst_line, video_coord_t dst_x,
          byte_t const *__restrict src_line, video_coord_t src_x,
          size_t stride, video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x;
	src_line += src_x;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
#ifndef __OPTIMIZE_SIZE__
	if (stride == size_x) {
		/* Special case: can memcpy **all** pixel data in a single go */
		memmoveb(dst_line, src_line, size_x * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		if (dst_line <= src_line) {
			do {
				memmovedownb(dst_line, src_line, size_x);
				dst_line += stride;
				src_line += stride;
			} while (--size_y);
		} else {
			dst_line += size_y * stride;
			src_line += size_y * stride;
			do {
				dst_line -= stride;
				src_line -= stride;
				memmoveupb(dst_line, src_line, size_x);
			} while (--size_y);
		}
	}
}

PRIVATE NONNULL((1, 3)) void FCC
linecopy8(byte_t *__restrict dst_line, video_coord_t dst_x,
          byte_t const *__restrict src_line, video_coord_t src_x,
          video_dim_t size_x) {
	dst_line += dst_x;
	src_line += src_x;
	codec_assert(size_x > 0);
	memcpyb(dst_line, src_line, size_x);
}





/************************************************************************/
/* 16BPP PIXEL OPERATORS                                                */
/************************************************************************/

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
getpixel16(byte_t const *__restrict line, video_coord_t x) {
	return ((uint16_t const *)line)[x];
}

PRIVATE NONNULL((1)) void FCC
setpixel16(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	((uint16_t *)line)[x] = (uint16_t)pixel;
}

#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
#ifdef USE_INLINE_386_ASSEMBLY_FOR_RP3
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC
rp3_setpixel16(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
__ASM_BEGIN
__ASM_L(.text)
__ASM_L(.type rp3_setpixel16, @function)
__ASM_L(rp3_setpixel16:)
__ASM_L(	.cfi_startproc)
__ASM_L(	movw %cx, (%eax,%edx,2))
__ASM_L(	ret)
__ASM_L(	.cfi_endproc)
__ASM_L(.size rp3_setpixel16, .- rp3_setpixel16)
__ASM_END
#else /* USE_INLINE_386_ASSEMBLY_FOR_RP3 */
PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC
rp3_setpixel16(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	((uint16_t *)line)[x] = (uint16_t)pixel;
}
#endif /* !USE_INLINE_386_ASSEMBLY_FOR_RP3 */
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */

PRIVATE NONNULL((1, 4)) void FCC
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
#ifndef __OPTIMIZE_SIZE__
	if (dst_stride == src_stride && dst_stride == (size_x << 1)) {
		/* Special case: can memcpy **all** pixel data in a single go */
		memcpyw(dst_line, src_line, size_x * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		do {
			memcpyw(dst_line, src_line, size_x);
			dst_line += dst_stride;
			src_line += src_stride;
		} while (--size_y);
	}
}

PRIVATE NONNULL((1, 3)) void FCC
rectmove16(byte_t *__restrict dst_line, video_coord_t dst_x,
           byte_t const *__restrict src_line, video_coord_t src_x,
           size_t stride, video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x << 1;
	src_line += src_x << 1;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	codec_assert(!(stride & 1));
	codec_assert(!((uintptr_t)dst_line & 1));
	codec_assert(!((uintptr_t)src_line & 1));
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#ifndef __OPTIMIZE_SIZE__
	if (stride == (size_x << 1)) {
		/* Special case: can memcpy **all** pixel data in a single go */
		memmovew(dst_line, src_line, size_x * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		if (dst_line <= src_line) {
			do {
				memmovedownw(dst_line, src_line, size_x);
				dst_line += stride;
				src_line += stride;
			} while (--size_y);
		} else {
			dst_line += size_y * stride;
			src_line += size_y * stride;
			do {
				dst_line -= stride;
				src_line -= stride;
				memmoveupw(dst_line, src_line, size_x);
			} while (--size_y);
		}
	}
}

PRIVATE NONNULL((1, 3)) void FCC
linecopy16(byte_t *__restrict dst_line, video_coord_t dst_x,
          byte_t const *__restrict src_line, video_coord_t src_x,
          video_dim_t size_x) {
	dst_line += dst_x << 1;
	src_line += src_x << 1;
	codec_assert(size_x > 0);
	memcpyw(dst_line, src_line, size_x);
}

PRIVATE NONNULL((1)) void FCC
linefill16(byte_t *__restrict line, video_coord_t x,
           video_pixel_t pixel, video_dim_t num_pixels) {
	line += x << 1;
	codec_assert(num_pixels > 0);
	memsetw(line, (uint16_t)pixel, num_pixels);
}

PRIVATE NONNULL((1)) void FCC
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

PRIVATE NONNULL((1)) void FCC
rectfill16(byte_t *__restrict line, video_coord_t x, size_t stride,
           video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	line += x << 1;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	codec_assert(!(stride & 1));
	codec_assert(!((uintptr_t)line & 1));
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#ifndef __OPTIMIZE_SIZE__
	if (stride == (size_x << 1)) {
		memsetw(line, (uint16_t)pixel, size_x * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		do {
			memsetw(line, (uint16_t)pixel, size_x);
			line += stride;
		} while (--size_y);
	}
}

#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#define unaligned_getpixel16 getpixel16
#define unaligned_setpixel16 setpixel16
#define unaligned_linefill16 linefill16
#define unaligned_vertfill16 vertfill16
#define unaligned_rectfill16 rectfill16
#define unaligned_rectcopy16 rectcopy16
#define unaligned_rectmove16 rectmove16
#define unaligned_linecopy16 linecopy16
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
unaligned_getpixel16(byte_t const *__restrict line, video_coord_t x) {
	return UNALIGNED_GET16(&((uint16_t const *)line)[x]);
}

PRIVATE NONNULL((1)) void FCC
unaligned_setpixel16(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	UNALIGNED_SET16(&((uint16_t *)line)[x], (uint16_t)pixel);
}

#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC
rp3_unaligned_setpixel16(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	UNALIGNED_SET16(&((uint16_t *)line)[x], (uint16_t)pixel);
}
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */

PRIVATE NONNULL((1)) void FCC
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

PRIVATE NONNULL((1)) void FCC
unaligned_vertfill16(byte_t *__restrict line, video_coord_t x, size_t stride,
                     video_pixel_t pixel, video_dim_t num_pixels) {
	line += x << 1;
	codec_assert(num_pixels > 0);
	do {
		UNALIGNED_SET16(line, (uint16_t)pixel);
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void FCC
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

PRIVATE NONNULL((1, 4)) void FCC
unaligned_rectcopy16(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
                     byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
                     video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x << 1;
	src_line += src_x << 1;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
	size_x <<= 1;
#ifndef __OPTIMIZE_SIZE__
	if (dst_stride == src_stride && dst_stride == size_x) {
		/* Special case: can memcpy **all** pixel data in a single go */
		memcpy(dst_line, src_line, dst_stride * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		do {
			memcpy(dst_line, src_line, size_x);
			dst_line += dst_stride;
			src_line += src_stride;
		} while (--size_y);
	}
}

PRIVATE NONNULL((1, 3)) void FCC
unaligned_rectmove16(byte_t *__restrict dst_line, video_coord_t dst_x,
                     byte_t const *__restrict src_line, video_coord_t src_x,
                     size_t stride, video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x << 1;
	src_line += src_x << 1;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
	size_x <<= 1;
#ifndef __OPTIMIZE_SIZE__
	if (stride == size_x) {
		/* Special case: can memcpy **all** pixel data in a single go */
		memmove(dst_line, src_line, stride * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		if (dst_line <= src_line) {
			do {
				memmovedown(dst_line, src_line, size_x);
				dst_line += stride;
				src_line += stride;
			} while (--size_y);
		} else {
			dst_line += size_y * stride;
			src_line += size_y * stride;
			do {
				dst_line -= stride;
				src_line -= stride;
				memmoveup(dst_line, src_line, size_x);
			} while (--size_y);
		}
	}
}

PRIVATE NONNULL((1, 3)) void FCC
unaligned_linecopy16(byte_t *__restrict dst_line, video_coord_t dst_x,
                     byte_t const *__restrict src_line, video_coord_t src_x,
                     video_dim_t size_x) {
	dst_line += dst_x << 1;
	src_line += src_x << 1;
	codec_assert(size_x > 0);
	memcpy(dst_line, src_line, size_x << 1);
}
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */





/************************************************************************/
/* 24BPP PIXEL OPERATORS                                                */
/************************************************************************/

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
getpixel24(byte_t const *__restrict line, video_coord_t x) {
	union word32 result;
	line += x * 3;
	result.bytes[0] = line[0];
	result.bytes[1] = line[1];
	result.bytes[2] = line[2];
	result.bytes[3] = 0;
	return result.dword;
}

PRIVATE NONNULL((1)) void FCC
setpixel24(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	union word32 data;
	data.dword = pixel;
	line += x * 3;
	line[0] = data.bytes[0];
	line[1] = data.bytes[1];
	line[2] = data.bytes[2];
}

#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
#ifdef USE_INLINE_386_ASSEMBLY_FOR_RP3
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC
rp3_setpixel24(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
__ASM_BEGIN
__ASM_L(.text)
__ASM_L(.type rp3_setpixel24, @function)
__ASM_L(rp3_setpixel24:)
__ASM_L(	.cfi_startproc)
__ASM_L(	leal (%edx,%edx,2), %edx)
__ASM_L(	addl %edx, %eax)
__ASM_L(	movw %cx, (%eax))
__ASM_L(	shrl $16, %ecx)
__ASM_L(	movb %cl, 2(%eax))
__ASM_L(	ret)
__ASM_L(	.cfi_endproc)
__ASM_L(.size rp3_setpixel24, .- rp3_setpixel24)
__ASM_END
#else /* USE_INLINE_386_ASSEMBLY_FOR_RP3 */
PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC
rp3_setpixel24(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	union word32 data;
	data.dword = pixel;
	line += x * 3;
	line[0] = data.bytes[0];
	line[1] = data.bytes[1];
	line[2] = data.bytes[2];
}
#endif /* !USE_INLINE_386_ASSEMBLY_FOR_RP3 */
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */

PRIVATE NONNULL((1)) void FCC
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

PRIVATE NONNULL((1)) void FCC
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

PRIVATE NONNULL((1)) void FCC
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

PRIVATE NONNULL((1, 4)) void FCC
rectcopy24(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
           byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
           video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x * 3;
	src_line += src_x * 3;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
	size_x *= 3;
#ifndef __OPTIMIZE_SIZE__
	if (dst_stride == src_stride && dst_stride == size_x) {
		/* Special case: can memcpy **all** pixel data in a single go */
		memcpy(dst_line, src_line, size_x * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		do {
			memcpy(dst_line, src_line, size_x);
			dst_line += dst_stride;
			src_line += src_stride;
		} while (--size_y);
	}
}

PRIVATE NONNULL((1, 3)) void FCC
rectmove24(byte_t *__restrict dst_line, video_coord_t dst_x,
           byte_t const *__restrict src_line, video_coord_t src_x,
           size_t stride, video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x * 3;
	src_line += src_x * 3;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
	size_x *= 3;
#ifndef __OPTIMIZE_SIZE__
	if (stride == size_x) {
		/* Special case: can memcpy **all** pixel data in a single go */
		memmove(dst_line, src_line, size_x * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		if (dst_line <= src_line) {
			do {
				memmovedown(dst_line, src_line, size_x);
				dst_line += stride;
				src_line += stride;
			} while (--size_y);
		} else {
			dst_line += size_y * stride;
			src_line += size_y * stride;
			do {
				dst_line -= stride;
				src_line -= stride;
				memmoveup(dst_line, src_line, size_x);
			} while (--size_y);
		}
	}
}


PRIVATE NONNULL((1, 3)) void FCC
linecopy24(byte_t *__restrict dst_line, video_coord_t dst_x,
           byte_t const *__restrict src_line, video_coord_t src_x,
           video_dim_t size_x) {
	dst_line += dst_x * 3;
	src_line += src_x * 3;
	codec_assert(size_x > 0);
	memcpy(dst_line, src_line, size_x * 3);
}





/************************************************************************/
/* 32BPP PIXEL OPERATORS                                                */
/************************************************************************/

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
getpixel32(byte_t const *__restrict line, video_coord_t x) {
	return ((uint32_t const *)line)[x];
}

PRIVATE NONNULL((1)) void FCC
setpixel32(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	((uint32_t *)line)[x] = (uint32_t)pixel;
}

#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
#ifdef USE_INLINE_386_ASSEMBLY_FOR_RP3
INTDEF NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC
rp3_setpixel32(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel);
__ASM_BEGIN
__ASM_L(.text)
__ASM_L(.type rp3_setpixel32, @function)
__ASM_L(rp3_setpixel32:)
__ASM_L(	.cfi_startproc)
__ASM_L(	movl %ecx, (%eax,%edx,4))
__ASM_L(	ret)
__ASM_L(	.cfi_endproc)
__ASM_L(.size rp3_setpixel32, .- rp3_setpixel32)
__ASM_END
#else /* USE_INLINE_386_ASSEMBLY_FOR_RP3 */
PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC
rp3_setpixel32(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	((uint32_t *)line)[x] = (uint32_t)pixel;
}
#endif /* !USE_INLINE_386_ASSEMBLY_FOR_RP3 */
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */

PRIVATE NONNULL((1)) void FCC
linefill32(byte_t *__restrict line, video_coord_t x,
           video_pixel_t pixel, video_dim_t num_pixels) {
	line += x << 2;
	codec_assert(num_pixels > 0);
	memsetl(line, (uint32_t)pixel, num_pixels);
}

PRIVATE NONNULL((1)) void FCC
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

PRIVATE NONNULL((1)) void FCC
rectfill32(byte_t *__restrict line, video_coord_t x, size_t stride,
           video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y) {
	line += x << 2;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	codec_assert(!(stride & 3));
	codec_assert(!((uintptr_t)line & 3));
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#ifndef __OPTIMIZE_SIZE__
	if (stride == (size_x << 2)) {
		memsetl(line, (uint32_t)pixel, size_x * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		do {
			memsetl(line, (uint32_t)pixel, size_x);
			line += stride;
		} while (--size_y);
	}
}

PRIVATE NONNULL((1, 4)) void FCC
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
#ifndef __OPTIMIZE_SIZE__
	if (dst_stride == src_stride && dst_stride == size_x) {
		/* Special case: can memcpy **all** pixel data in a single go */
		memcpyl(dst_line, src_line, size_x * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		do {
			memcpyl(dst_line, src_line, size_x);
			dst_line += dst_stride;
			src_line += src_stride;
		} while (--size_y);
	}
}

PRIVATE NONNULL((1, 3)) void FCC
rectmove32(byte_t *__restrict dst_line, video_coord_t dst_x,
           byte_t const *__restrict src_line, video_coord_t src_x,
           size_t stride, video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x << 2;
	src_line += src_x << 2;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	codec_assert(!(stride & 3));
	codec_assert(!((uintptr_t)dst_line & 3));
	codec_assert(!((uintptr_t)src_line & 3));
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#ifndef __OPTIMIZE_SIZE__
	if (stride == (size_x << 2)) {
		/* Special case: can memcpy **all** pixel data in a single go */
		memmovel(dst_line, src_line, size_x * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		if (dst_line <= src_line) {
			do {
				memmovedownl(dst_line, src_line, size_x);
				dst_line += stride;
				src_line += stride;
			} while (--size_y);
		} else {
			dst_line += size_y * stride;
			src_line += size_y * stride;
			do {
				dst_line -= stride;
				src_line -= stride;
				memmoveupl(dst_line, src_line, size_x);
			} while (--size_y);
		}
	}
}
PRIVATE NONNULL((1, 3)) void FCC
linecopy32(byte_t *__restrict dst_line, video_coord_t dst_x,
           byte_t const *__restrict src_line, video_coord_t src_x,
           video_dim_t size_x) {
	dst_line += dst_x << 2;
	src_line += src_x << 2;
	codec_assert(size_x > 0);
	memcpyl(dst_line, src_line, size_x);
}


#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#define unaligned_getpixel32 getpixel32
#define unaligned_setpixel32 setpixel32
#define unaligned_linefill32 linefill32
#define unaligned_vertfill32 vertfill32
#define unaligned_rectfill32 rectfill32
#define unaligned_rectcopy32 rectcopy32
#define unaligned_rectmove32 rectmove32
#define unaligned_linecopy32 linecopy32
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
unaligned_getpixel32(byte_t const *__restrict line, video_coord_t x) {
	return UNALIGNED_GET32(&((uint32_t const *)line)[x]);
}

PRIVATE NONNULL((1)) void FCC
unaligned_setpixel32(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	UNALIGNED_SET32(&((uint32_t *)line)[x], (uint32_t)pixel);
}

#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
PRIVATE NONNULL((1)) void VIDEO_CODEC_SETPIXEL3_CC
rp3_unaligned_setpixel32(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	UNALIGNED_SET32(&((uint32_t *)line)[x], (uint32_t)pixel);
}
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */

PRIVATE NONNULL((1)) void FCC
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

PRIVATE NONNULL((1)) void FCC
unaligned_vertfill32(byte_t *__restrict line, video_coord_t x, size_t stride,
                     video_pixel_t pixel, video_dim_t num_pixels) {
	line += x << 2;
	codec_assert(num_pixels > 0);
	do {
		UNALIGNED_SET32(line, (uint32_t)pixel);
		line += stride;
	} while (--num_pixels);
}

PRIVATE NONNULL((1)) void FCC
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

PRIVATE NONNULL((1, 4)) void FCC
unaligned_rectcopy32(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
                     byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
                     video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x << 2;
	src_line += src_x << 2;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
	size_x <<= 2;
#ifndef __OPTIMIZE_SIZE__
	if (dst_stride == src_stride && dst_stride == size_x) {
		/* Special case: can memcpy **all** pixel data in a single go */
		memcpy(dst_line, src_line, dst_stride * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		do {
			memcpy(dst_line, src_line, size_x);
			dst_line += dst_stride;
			src_line += src_stride;
		} while (--size_y);
	}
}

PRIVATE NONNULL((1, 3)) void FCC
unaligned_rectmove32(byte_t *__restrict dst_line, video_coord_t dst_x,
                     byte_t const *__restrict src_line, video_coord_t src_x,
                     size_t stride, video_dim_t size_x, video_dim_t size_y) {
	dst_line += dst_x << 2;
	src_line += src_x << 2;
	codec_assert(size_x > 0);
	codec_assert(size_y > 0);
	size_x <<= 2;
#ifndef __OPTIMIZE_SIZE__
	if (stride == size_x) {
		/* Special case: can memcpy **all** pixel data in a single go */
		memcpy(dst_line, src_line, stride * size_y);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		if (dst_line <= src_line) {
			do {
				memmovedown(dst_line, src_line, size_x);
				dst_line += stride;
				src_line += stride;
			} while (--size_y);
		} else {
			dst_line += size_y * stride;
			src_line += size_y * stride;
			do {
				dst_line -= stride;
				src_line -= stride;
				memmoveup(dst_line, src_line, size_x);
			} while (--size_y);
		}
	}
}

PRIVATE NONNULL((1, 3)) void FCC
unaligned_linecopy32(byte_t *__restrict dst_line, video_coord_t dst_x,
                     byte_t const *__restrict src_line, video_coord_t src_x,
                     video_dim_t size_x) {
	dst_line += dst_x << 2;
	src_line += src_x << 2;
	codec_assert(size_x > 0);
	memcpy(dst_line, src_line, size_x << 2);
}
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */



/* 64-bit pixel wrappers */
DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX(PRIVATE, 1_msb)
DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX(PRIVATE, 1_lsb)
DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX(PRIVATE, 2_msb)
DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX(PRIVATE, 2_lsb)
DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX(PRIVATE, 4_msb)
DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX(PRIVATE, 4_lsb)
DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX(PRIVATE, 8)
DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX(PRIVATE, 16)
DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX(PRIVATE, 24)
DEFINE_PIXEL64_IO_WRAPPERS__WITH_SUFFIX(PRIVATE, 32)

#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#define MAP_IO(x)   unaligned_##x##16
#define MAP_IO64(x) unaligned_##x##16_64
DEFINE_PIXEL64_IO_WRAPPERS(PRIVATE, MAP_IO, MAP_IO64)
#undef MAP_IO
#undef MAP_IO64

#define MAP_IO(x)   unaligned_##x##32
#define MAP_IO64(x) unaligned_##x##32_64
DEFINE_PIXEL64_IO_WRAPPERS(PRIVATE, MAP_IO, MAP_IO64)
#undef MAP_IO
#undef MAP_IO64
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */







/************************************************************************/
/* COLOR CONVERSION                                                     */
/************************************************************************/

/* 64-bit pixel format support */
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
LOCAL ATTR_CONST video_channel16_t FCC
fill_missing_bits16(video_channel16_t value, shift_t miss_bits) {
	/* TODO: Optimizations */
#define nmax(n) ((1 << (n)) - 1)
	return (video_channel16_t)((((uint_fast32_t)value * 0xffff) +
	                            nmax(16 - miss_bits - 1)) /
	                           nmax(16 - miss_bits));
#undef nmax
}

LOCAL ATTR_CONST video_channel16_t FCC
pext_channel16(video_pixel64_t pixel,
               video_pixel64_t mask,
               shift_t miss_bits) {
	video_channel16_t result = PEXT(pixel, mask);
	return fill_missing_bits16(result, miss_bits);
}

LOCAL ATTR_CONST video_pixel64_t FCC
pdep_channel16(video_channel16_t chan,
               video_pixel64_t used_mask,
               video_pixel64_t xtra_mask) {
	video_pixel64_t result = PDEP((video_pixel64_t)chan, used_mask);
#if 1 /* Same as other impl, but without if-statements */
	result |= (video_pixel64_t)(chan & 1) * xtra_mask;
#else
	if (chan & 1)
		result |= xtra_mask;
#endif
	return result;
}
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */



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


#define PIXEL32(b0, b1, b2, b3) ENCODE_INT32(b0, b1, b2, b3)
#define PIXEL32_B0(pixel)       INT16_I8(pixel, 0)
#define PIXEL32_B1(pixel)       INT16_I8(pixel, 1)
#define PIXEL32_B2(pixel)       INT16_I8(pixel, 2)
#define PIXEL32_B3(pixel)       INT16_I8(pixel, 3)


INTERN ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
identity_color2pixel(struct video_surface const *__restrict UNUSED(surface),
                     video_color_t value) {
	return value;
}

#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
INTERN ATTR_CONST WUNUSED NONNULL((1)) video_pixel64_t FCC
identity_color2pixel64(struct video_surface const *__restrict UNUSED(surface),
                       video_color64_t value) {
	return value;
}
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

INTERN ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
rgbx8888_pixel2color(struct video_surface const *__restrict UNUSED(surface),
                     video_pixel_t pixel) {
	return pixel | VIDEO_COLOR_ALPHA_MASK;
}
DEFINE_PIXEL2COLOR64_WRAPPER32(INTERN ATTR_CONST, rgbx8888_pixel2color, rgbx8888_pixel2color64)

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define rgb888_pixel2color   rgbx8888_pixel2color
#define rgb888_pixel2color64 rgbx8888_pixel2color64
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
rgb888_pixel2color(struct video_surface const *__restrict UNUSED(surface),
                   video_pixel_t pixel) {
	return (pixel << 8) | VIDEO_COLOR_ALPHA_MASK;
}
DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_CONST, rgb888_pixel2color, rgb888_pixel2color64)
#endif /* __BYTE_ORDER__ == ... */

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define rgb888_color2pixel   identity_color2pixel
#define rgb888_color2pixel64 identity_color2pixel64
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
rgb888_color2pixel(struct video_surface const *__restrict UNUSED(surface),
                   video_color_t color) {
	return color >> 8;
}
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_CONST, rgb888_color2pixel, rgb888_color2pixel64)
#endif /* __BYTE_ORDER__ == ... */



PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
argb8888_pixel2color(struct video_surface const *__restrict UNUSED(surface),
                     video_pixel_t pixel) {
	return BIGENDIAN_SHL((uint32_t)pixel, 8) |
	       BIGENDIAN_SHR((uint32_t)pixel, 24);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
argb8888_color2pixel(struct video_surface const *__restrict UNUSED(surface),
                     video_color_t color) {
	return BIGENDIAN_SHR((uint32_t)color, 8) |
	       BIGENDIAN_SHL((uint32_t)color, 24);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
xrgb8888_pixel2color(struct video_surface const *__restrict UNUSED(surface),
                     video_pixel_t pixel) {
	return BIGENDIAN_SHL((uint32_t)pixel, 8) | VIDEO_COLOR_ALPHA_MASK;
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
xrgb8888_color2pixel(struct video_surface const *__restrict UNUSED(surface),
                     video_color_t color) {
	return BIGENDIAN_SHR((uint32_t)color, 8);
}


PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
abgr8888_pixel2color(struct video_surface const *__restrict UNUSED(surface),
                     video_pixel_t pixel) {
	return VIDEO_COLOR_RGBA(PIXEL32_B1(pixel),
	                        PIXEL32_B2(pixel),
	                        PIXEL32_B3(pixel),
	                        PIXEL32_B0(pixel));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
abgr8888_color2pixel(struct video_surface const *__restrict UNUSED(surface),
                     video_color_t color) {
	return PIXEL32(VIDEO_COLOR_GET_ALPHA(color),
	               VIDEO_COLOR_GET_BLUE(color),
	               VIDEO_COLOR_GET_GREEN(color),
	               VIDEO_COLOR_GET_RED(color));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
xbgr8888_pixel2color(struct video_surface const *__restrict UNUSED(surface),
                     video_pixel_t pixel) {
	return VIDEO_COLOR_RGB(PIXEL32_B3(pixel),
	                       PIXEL32_B2(pixel),
	                       PIXEL32_B1(pixel));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
xbgr8888_color2pixel(struct video_surface const *__restrict UNUSED(surface),
                     video_color_t color) {
	return PIXEL32(0 /* undefined */,
	               VIDEO_COLOR_GET_BLUE(color),
	               VIDEO_COLOR_GET_GREEN(color),
	               VIDEO_COLOR_GET_RED(color));
}


PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
bgra8888_pixel2color(struct video_surface const *__restrict UNUSED(surface),
                     video_pixel_t pixel) {
	return VIDEO_COLOR_RGBA(PIXEL32_B2(pixel),
	                        PIXEL32_B1(pixel),
	                        PIXEL32_B0(pixel),
	                        PIXEL32_B3(pixel));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
bgra8888_color2pixel(struct video_surface const *__restrict UNUSED(surface),
                     video_color_t color) {
	return PIXEL32(VIDEO_COLOR_GET_BLUE(color),
	               VIDEO_COLOR_GET_GREEN(color),
	               VIDEO_COLOR_GET_RED(color),
	               VIDEO_COLOR_GET_ALPHA(color));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
bgrx8888_pixel2color(struct video_surface const *__restrict UNUSED(surface),
                     video_pixel_t pixel) {
	return VIDEO_COLOR_RGB(PIXEL32_B2(pixel),
	                       PIXEL32_B1(pixel),
	                       PIXEL32_B0(pixel));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
bgrx8888_color2pixel(struct video_surface const *__restrict UNUSED(surface),
                     video_color_t color) {
	return PIXEL32(VIDEO_COLOR_GET_BLUE(color),
	               VIDEO_COLOR_GET_GREEN(color),
	               VIDEO_COLOR_GET_RED(color),
	               0 /* undefined */);
}


#define bgr888_pixel2color bgrx8888_pixel2color
#define bgr888_color2pixel bgrx8888_color2pixel

DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, argb8888)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, xrgb8888)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, abgr8888)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, xbgr8888)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, bgra8888)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, bgrx8888)

#define bgr888_pixel2color   bgrx8888_pixel2color
#define bgr888_pixel2color64 bgrx8888_pixel2color64
#define bgr888_color2pixel   bgrx8888_color2pixel
#define bgr888_color2pixel64 bgrx8888_color2pixel64


#undef USE_FAST_COLOR_UPSCALE
#if 1 /* Use fast (but for 5/6-bit source values: sometimes off-by-1-inaccurate) color upscaling */
#define USE_FAST_COLOR_UPSCALE
#endif

/* >> channel_t c3_to_c8(channel_t c);
 * Upscale a 3-bit color channel to 8 bits
 *
 * >> in  = [0,8);
 * >> out = (((in * 255) + (7 / 2)) / 7);
 *
 * in:  0b{a}{b}{c}
 * out: 0b{A}{B}{C}{D}{E}{F}{G}{H}
 *
 * | --------- | ----------------- |
 * | in        |  out              |
 * | --------- | ----------------- |
 * |   abc     |   ABCDEFGH        |
 * | 0b000 (0) | 0b00000000 (0x00) |
 * | 0b001 (1) | 0b00100100 (0x24) |
 * | 0b010 (2) | 0b01001001 (0x49) |
 * | 0b011 (3) | 0b01101101 (0x6d) |
 * | 0b100 (4) | 0b10010010 (0x92) |
 * | 0b101 (5) | 0b10110110 (0xb6) |
 * | 0b110 (6) | 0b11011011 (0xdb) |
 * | 0b111 (7) | 0b11111111 (0xff) |
 * | --------- | ----------------- |
 *
 * Logic-mapping:
 * >> A = a
 * >> B = b
 * >> C = c
 * >> D = a
 * >> E = b
 * >> F = c
 * >> G = a
 * >> H = b
 */
#if 1 /* Doesn't have any inaccuracies, so always use */
#define c3_to_c8(c)                      \
	(uint8_t)(((c) >> 1) | /* GH=ab */   \
	          ((c) << 2) | /* DEF=abc */ \
	          ((c) << 5))  /* ABC=abc */
#else
#define c3_to_c8(c) \
	(uint8_t)((((uint_fast16_t)(c) * 255) + (7 / 2)) / 7)
#endif


/* >> channel_t c5_to_c8(channel_t c);
 * Upscale a 5-bit color channel to 8 bits
 *
 * >> in  = [0,32);
 * >> out = (((in * 255) + (31 / 2)) / 31);  // Perfect formula, but see known inaccuracies below
 *
 * in:  0b{a}{b}{c}{d}{e}
 * out: 0b{A}{B}{C}{D}{E}{F}{G}{H}
 *
 * | ------------ | ----------------- |
 * | in           |  out              |
 * | ------------ | ----------------- |
 * |   abcde      |   ABCDEFGH        |
 * | 0b00000 ( 0) | 0b00000000 (0x00) |
 * | 0b00001 ( 1) | 0b00001000 (0x08) |
 * | 0b00010 ( 2) | 0b00010000 (0x10) |
 * | 0b00011 ( 3) | 0b00011000 (0x18) | Wrong! Should be: 0b00011001 (0x19)
 * | 0b00100 ( 4) | 0b00100001 (0x21) |
 * | 0b00101 ( 5) | 0b00101001 (0x29) |
 * | 0b00110 ( 6) | 0b00110001 (0x31) |
 * | 0b00111 ( 7) | 0b00111001 (0x39) | Wrong! Should be: 0b00111010 (0x3a)
 * | 0b01000 ( 8) | 0b01000010 (0x42) |
 * | 0b01001 ( 9) | 0b01001010 (0x4a) |
 * | 0b01010 (10) | 0b01010010 (0x52) |
 * | 0b01011 (11) | 0b01011010 (0x5a) |
 * | 0b01100 (12) | 0b01100011 (0x63) |
 * | 0b01101 (13) | 0b01101011 (0x6b) |
 * | 0b01110 (14) | 0b01110011 (0x73) |
 * | 0b01111 (15) | 0b01111011 (0x7b) |
 * | 0b10000 (16) | 0b10000100 (0x84) |
 * | 0b10001 (17) | 0b10001100 (0x8c) |
 * | 0b10010 (18) | 0b10010100 (0x94) |
 * | 0b10011 (19) | 0b10011100 (0x9c) |
 * | 0b10100 (20) | 0b10100101 (0xa5) |
 * | 0b10101 (21) | 0b10101101 (0xad) |
 * | 0b10110 (22) | 0b10110101 (0xb5) |
 * | 0b10111 (23) | 0b10111101 (0xbd) |
 * | 0b11000 (24) | 0b11000110 (0xc6) | Wrong! Should be: 0b11000101 (0xc5)
 * | 0b11001 (25) | 0b11001110 (0xce) |
 * | 0b11010 (26) | 0b11010110 (0xd6) |
 * | 0b11011 (27) | 0b11011110 (0xde) |
 * | 0b11100 (28) | 0b11100111 (0xe7) | Wrong! Should be: 0b11100110 (0xe6)
 * | 0b11101 (29) | 0b11101111 (0xef) |
 * | 0b11110 (30) | 0b11110111 (0xf7) |
 * | 0b11111 (31) | 0b11111111 (0xff) |
 * | ------------ | ----------------- |
 *
 * Logic-mapping:
 * >> A = a
 * >> B = b
 * >> C = c
 * >> D = d
 * >> E = e
 * >> F = a
 * >> G = b
 * >> H = c */
#ifdef USE_FAST_COLOR_UPSCALE
#define c5_to_c8(c)                      \
	(uint8_t)(((c) >> 2) | /* FGH=abc */ \
	          ((c) << 3))  /* ABCDE=abcde */
#else /* USE_FAST_COLOR_UPSCALE */
#define c5_to_c8(c) \
	(uint8_t)((((uint_fast16_t)(c) * 255) + (31 / 2)) / 31)
#endif /* !USE_FAST_COLOR_UPSCALE */


/* >> channel_t c6_to_c8(channel_t c);
 * Upscale a 6-bit color channel to 8 bits
 *
 * >> in  = [0,64);
 * >> out = (((in * 255) + (63 / 2)) / 63);
 *
 * in:  0b{a}{b}{c}{d}{e}{f}
 * out: 0b{A}{B}{C}{D}{E}{F}{G}{H}
 *
 * | ------------- | ----------------- |
 * | in            |  out              |
 * | ------------- | ----------------- |
 * |   abcdef      |   ABCDEFGH        |
 * | 0b000000 ( 0) | 0b00000000 (0x00) |
 * | 0b000001 ( 1) | 0b00000100 (0x04) |
 * | 0b000010 ( 2) | 0b00001000 (0x08) |
 * | 0b000011 ( 3) | 0b00001100 (0x0c) |
 * | 0b000100 ( 4) | 0b00010000 (0x10) |
 * | 0b000101 ( 5) | 0b00010100 (0x14) |
 * | 0b000110 ( 6) | 0b00011000 (0x18) |
 * | 0b000111 ( 7) | 0b00011100 (0x1c) |
 * | 0b001000 ( 8) | 0b00100000 (0x20) |
 * | 0b001001 ( 9) | 0b00100100 (0x24) |
 * | 0b001010 (10) | 0b00101000 (0x28) |
 * | 0b001011 (11) | 0b00101100 (0x2c) | Wrong! Should be: 0b00101101 (0x2d)
 * | 0b001100 (12) | 0b00110000 (0x30) | Wrong! Should be: 0b00110001 (0x31)
 * | 0b001101 (13) | 0b00110100 (0x33) | Wrong! Should be: 0b00110101 (0x35)
 * | 0b001110 (14) | 0b00111000 (0x38) | Wrong! Should be: 0b00111001 (0x39)
 * | 0b001111 (15) | 0b00111100 (0x3c) | Wrong! Should be: 0b00111101 (0x3d)
 * | 0b010000 (16) | 0b01000001 (0x41) |
 * | 0b010001 (17) | 0b01000101 (0x45) |
 * | 0b010010 (18) | 0b01001001 (0x49) |
 * | 0b010011 (19) | 0b01001101 (0x4d) |
 * | 0b010100 (20) | 0b01010001 (0x51) |
 * | 0b010101 (21) | 0b01010101 (0x55) |
 * | 0b010110 (22) | 0b01011001 (0x59) |
 * | 0b010111 (23) | 0b01011101 (0x5d) |
 * | 0b011000 (24) | 0b01100001 (0x61) |
 * | 0b011001 (25) | 0b01100101 (0x65) |
 * | 0b011010 (26) | 0b01101001 (0x69) |
 * | 0b011011 (27) | 0b01101101 (0x6d) |
 * | 0b011100 (28) | 0b01110001 (0x71) |
 * | 0b011101 (29) | 0b01110101 (0x75) |
 * | 0b011110 (30) | 0b01111001 (0x79) |
 * | 0b011111 (31) | 0b01111101 (0x7d) |
 * | 0b100000 (32) | 0b10000010 (0x82) |
 * | 0b100001 (33) | 0b10000110 (0x86) |
 * | 0b100010 (34) | 0b10001010 (0x8a) |
 * | 0b100011 (35) | 0b10001110 (0x8e) |
 * | 0b100100 (36) | 0b10010010 (0x92) |
 * | 0b100101 (37) | 0b10010110 (0x96) |
 * | 0b100110 (38) | 0b10011010 (0x9a) |
 * | 0b100111 (39) | 0b10011110 (0x9e) |
 * | 0b101000 (40) | 0b10100010 (0xa2) |
 * | 0b101001 (41) | 0b10100110 (0xa6) |
 * | 0b101010 (42) | 0b10101010 (0xaa) |
 * | 0b101011 (43) | 0b10101110 (0xae) |
 * | 0b101100 (44) | 0b10110010 (0xb2) |
 * | 0b101101 (45) | 0b10110110 (0xb6) |
 * | 0b101110 (46) | 0b10111010 (0xba) |
 * | 0b101111 (47) | 0b10111110 (0xbe) |
 * | 0b110000 (48) | 0b11000011 (0xc3) | Wrong! Should be: 0b11000010 (0xc2)
 * | 0b110001 (49) | 0b11000111 (0xc7) | Wrong! Should be: 0b11000110 (0xc6)
 * | 0b110010 (50) | 0b11001011 (0xcb) | Wrong! Should be: 0b11001010 (0xca)
 * | 0b110011 (51) | 0b11001111 (0xcf) | Wrong! Should be: 0b11001110 (0xce)
 * | 0b110100 (52) | 0b11010011 (0xd3) | Wrong! Should be: 0b11010010 (0xd2)
 * | 0b110101 (53) | 0b11010111 (0xd7) |
 * | 0b110110 (54) | 0b11011011 (0xdb) |
 * | 0b110111 (55) | 0b11011111 (0xdf) |
 * | 0b111000 (56) | 0b11100011 (0xe3) |
 * | 0b111001 (57) | 0b11100111 (0xe7) |
 * | 0b111010 (58) | 0b11101011 (0xeb) |
 * | 0b111011 (59) | 0b11101111 (0xef) |
 * | 0b111100 (60) | 0b11110011 (0xf3) |
 * | 0b111101 (61) | 0b11110111 (0xf7) |
 * | 0b111110 (62) | 0b11111011 (0xfb) |
 * | 0b111111 (63) | 0b11111111 (0xff) |
 * | ------------- | ----------------- |
 *
 * Logic-mapping:
 * >> A = a
 * >> B = b
 * >> C = c
 * >> D = d
 * >> E = e
 * >> F = f
 * >> G = a
 * >> H = b */
#ifdef USE_FAST_COLOR_UPSCALE
#define c6_to_c8(c)                    \
	(uint8_t)(((c) >> 4) | /* GH=ab */ \
	          ((c) << 2))  /* ABCDEF=abcdef */
#else /* USE_FAST_COLOR_UPSCALE */
#define c6_to_c8(c) \
	(uint8_t)((((uint_fast16_t)(c) * 255) + (63 / 2)) / 63)
#endif /* !USE_FAST_COLOR_UPSCALE */


/* >> channel_t c7_to_c8(channel_t c);
 * Upscale a 7-bit color channel to 8 bits
 *
 * >> in  = [0,128);
 * >> out = (((in * 255) + (127 / 2)) / 127);
 *
 * in:  0b{a}{b}{c}{d}{e}{f}{g}
 * out: 0b{A}{B}{C}{D}{E}{F}{G}{H}
 *
 * | in              |  out              | in              |  out              |
 * | --------------- | ----------------- | --------------- | ----------------- |
 * |   abcdefg       |   ABCDEFGH        |   abcdefg       |   ABCDEFGH        |
 * | 0b0000000 (  0) | 0b00000000 (0x00) | 0b1000000 ( 64) | 0b10000001 (0x81) |
 * | 0b0000001 (  1) | 0b00000010 (0x02) | 0b1000001 ( 65) | 0b10000011 (0x83) |
 * | 0b0000010 (  2) | 0b00000100 (0x04) | 0b1000010 ( 66) | 0b10000101 (0x85) |
 * | 0b0000011 (  3) | 0b00000110 (0x06) | 0b1000011 ( 67) | 0b10000111 (0x87) |
 * | 0b0000100 (  4) | 0b00001000 (0x08) | 0b1000100 ( 68) | 0b10001001 (0x89) |
 * | 0b0000101 (  5) | 0b00001010 (0x0a) | 0b1000101 ( 69) | 0b10001011 (0x8b) |
 * | 0b0000110 (  6) | 0b00001100 (0x0c) | 0b1000110 ( 70) | 0b10001101 (0x8d) |
 * | 0b0000111 (  7) | 0b00001110 (0x0e) | 0b1000111 ( 71) | 0b10001111 (0x8f) |
 * | 0b0001000 (  8) | 0b00010000 (0x10) | 0b1001000 ( 72) | 0b10010001 (0x91) |
 * | 0b0001001 (  9) | 0b00010010 (0x12) | 0b1001001 ( 73) | 0b10010011 (0x93) |
 * | 0b0001010 ( 10) | 0b00010100 (0x14) | 0b1001010 ( 74) | 0b10010101 (0x95) |
 * | 0b0001011 ( 11) | 0b00010110 (0x16) | 0b1001011 ( 75) | 0b10010111 (0x97) |
 * | 0b0001100 ( 12) | 0b00011000 (0x18) | 0b1001100 ( 76) | 0b10011001 (0x99) |
 * | 0b0001101 ( 13) | 0b00011010 (0x1a) | 0b1001101 ( 77) | 0b10011011 (0x9b) |
 * | 0b0001110 ( 14) | 0b00011100 (0x1c) | 0b1001110 ( 78) | 0b10011101 (0x9d) |
 * | 0b0001111 ( 15) | 0b00011110 (0x1e) | 0b1001111 ( 79) | 0b10011111 (0x9f) |
 * | 0b0010000 ( 16) | 0b00100000 (0x20) | 0b1010000 ( 80) | 0b10100001 (0xa1) |
 * | 0b0010001 ( 17) | 0b00100010 (0x22) | 0b1010001 ( 81) | 0b10100011 (0xa3) |
 * | 0b0010010 ( 18) | 0b00100100 (0x24) | 0b1010010 ( 82) | 0b10100101 (0xa5) |
 * | 0b0010011 ( 19) | 0b00100110 (0x26) | 0b1010011 ( 83) | 0b10100111 (0xa7) |
 * | 0b0010100 ( 20) | 0b00101000 (0x28) | 0b1010100 ( 84) | 0b10101001 (0xa9) |
 * | 0b0010101 ( 21) | 0b00101010 (0x2a) | 0b1010101 ( 85) | 0b10101011 (0xab) |
 * | 0b0010110 ( 22) | 0b00101100 (0x2c) | 0b1010110 ( 86) | 0b10101101 (0xad) |
 * | 0b0010111 ( 23) | 0b00101110 (0x2e) | 0b1010111 ( 87) | 0b10101111 (0xaf) |
 * | 0b0011000 ( 24) | 0b00110000 (0x30) | 0b1011000 ( 88) | 0b10110001 (0xb1) |
 * | 0b0011001 ( 25) | 0b00110010 (0x32) | 0b1011001 ( 89) | 0b10110011 (0xb3) |
 * | 0b0011010 ( 26) | 0b00110100 (0x34) | 0b1011010 ( 90) | 0b10110101 (0xb5) |
 * | 0b0011011 ( 27) | 0b00110110 (0x36) | 0b1011011 ( 91) | 0b10110111 (0xb7) |
 * | 0b0011100 ( 28) | 0b00111000 (0x38) | 0b1011100 ( 92) | 0b10111001 (0xb9) |
 * | 0b0011101 ( 29) | 0b00111010 (0x3a) | 0b1011101 ( 93) | 0b10111011 (0xbb) |
 * | 0b0011110 ( 30) | 0b00111100 (0x3c) | 0b1011110 ( 94) | 0b10111101 (0xbd) |
 * | 0b0011111 ( 31) | 0b00111110 (0x3e) | 0b1011111 ( 95) | 0b10111111 (0xbf) |
 * | 0b0100000 ( 32) | 0b01000000 (0x40) | 0b1100000 ( 96) | 0b11000001 (0xc1) |
 * | 0b0100001 ( 33) | 0b01000010 (0x42) | 0b1100001 ( 97) | 0b11000011 (0xc3) |
 * | 0b0100010 ( 34) | 0b01000100 (0x44) | 0b1100010 ( 98) | 0b11000101 (0xc5) |
 * | 0b0100011 ( 35) | 0b01000110 (0x46) | 0b1100011 ( 99) | 0b11000111 (0xc7) |
 * | 0b0100100 ( 36) | 0b01001000 (0x48) | 0b1100100 (100) | 0b11001001 (0xc9) |
 * | 0b0100101 ( 37) | 0b01001010 (0x4a) | 0b1100101 (101) | 0b11001011 (0xcb) |
 * | 0b0100110 ( 38) | 0b01001100 (0x4c) | 0b1100110 (102) | 0b11001101 (0xcd) |
 * | 0b0100111 ( 39) | 0b01001110 (0x4e) | 0b1100111 (103) | 0b11001111 (0xcf) |
 * | 0b0101000 ( 40) | 0b01010000 (0x50) | 0b1101000 (104) | 0b11010001 (0xd1) |
 * | 0b0101001 ( 41) | 0b01010010 (0x52) | 0b1101001 (105) | 0b11010011 (0xd3) |
 * | 0b0101010 ( 42) | 0b01010100 (0x54) | 0b1101010 (106) | 0b11010101 (0xd5) |
 * | 0b0101011 ( 43) | 0b01010110 (0x56) | 0b1101011 (107) | 0b11010111 (0xd7) |
 * | 0b0101100 ( 44) | 0b01011000 (0x58) | 0b1101100 (108) | 0b11011001 (0xd9) |
 * | 0b0101101 ( 45) | 0b01011010 (0x5a) | 0b1101101 (109) | 0b11011011 (0xdb) |
 * | 0b0101110 ( 46) | 0b01011100 (0x5c) | 0b1101110 (110) | 0b11011101 (0xdd) |
 * | 0b0101111 ( 47) | 0b01011110 (0x5e) | 0b1101111 (111) | 0b11011111 (0xdf) |
 * | 0b0110000 ( 48) | 0b01100000 (0x60) | 0b1110000 (112) | 0b11100001 (0xe1) |
 * | 0b0110001 ( 49) | 0b01100010 (0x62) | 0b1110001 (113) | 0b11100011 (0xe3) |
 * | 0b0110010 ( 50) | 0b01100100 (0x64) | 0b1110010 (114) | 0b11100101 (0xe5) |
 * | 0b0110011 ( 51) | 0b01100110 (0x66) | 0b1110011 (115) | 0b11100111 (0xe7) |
 * | 0b0110100 ( 52) | 0b01101000 (0x68) | 0b1110100 (116) | 0b11101001 (0xe9) |
 * | 0b0110101 ( 53) | 0b01101010 (0x6a) | 0b1110101 (117) | 0b11101011 (0xeb) |
 * | 0b0110110 ( 54) | 0b01101100 (0x6c) | 0b1110110 (118) | 0b11101101 (0xed) |
 * | 0b0110111 ( 55) | 0b01101110 (0x6e) | 0b1110111 (119) | 0b11101111 (0xef) |
 * | 0b0111000 ( 56) | 0b01110000 (0x70) | 0b1111000 (120) | 0b11110001 (0xf1) |
 * | 0b0111001 ( 57) | 0b01110010 (0x72) | 0b1111001 (121) | 0b11110011 (0xf3) |
 * | 0b0111010 ( 58) | 0b01110100 (0x74) | 0b1111010 (122) | 0b11110101 (0xf5) |
 * | 0b0111011 ( 59) | 0b01110110 (0x76) | 0b1111011 (123) | 0b11110111 (0xf7) |
 * | 0b0111100 ( 60) | 0b01111000 (0x78) | 0b1111100 (124) | 0b11111001 (0xf9) |
 * | 0b0111101 ( 61) | 0b01111010 (0x7a) | 0b1111101 (125) | 0b11111011 (0xfb) |
 * | 0b0111110 ( 62) | 0b01111100 (0x7c) | 0b1111110 (126) | 0b11111101 (0xfd) |
 * | 0b0111111 ( 63) | 0b01111110 (0x7e) | 0b1111111 (127) | 0b11111111 (0xff) |
 * | --------------- | ----------------- | --------------- | ----------------- |
 *
 * Logic-mapping:
 * >> A = a
 * >> B = b
 * >> C = c
 * >> D = d
 * >> E = e
 * >> F = f
 * >> G = g
 * >> H = a
 */
#if 1 /* Doesn't have any inaccuracies, so always use */
#define c7_to_c8(c)                              \
	(uint8_t)(((c) << 1) | /* ABCDEFG=abcdefg */ \
	          ((c) >> 6))  /* H=a */
#else
#define c7_to_c8(c) \
	(uint8_t)((((uint_fast16_t)(c) * 255) + (127 / 2)) / 127)
#endif


/* Given  a  "value" whose  top "miss_bits"  are  known to  be all-0,
 * shift it left by "miss_bits" (so the least significant "miss_bits"
 * bits are all  0), then fill  those bits with  repeats of the  most
 * significant  "8 - miss_bits" bits until  all "miss_bits" have been
 * filled.
 *
 * e.g.:
 * >> fill_missing_bits(0x00, 7) == 0x00;
 * >> fill_missing_bits(0x01, 7) == 0xff;
 *
 * >> fill_missing_bits(0x00, 6) == 0x00;
 * >> fill_missing_bits(0x01, 6) == 0x55;
 * >> fill_missing_bits(0x02, 6) == 0xaa;
 * >> fill_missing_bits(0x03, 6) == 0xff;
 */
#ifndef USE_FAST_COLOR_UPSCALE
#define __nmax(n) ((1 << (n)) - 1)
#define __fill_missing_bits(c, n) \
	(uint8_t)((((uint_fast16_t)(c) * 255) + __nmax(8 - (n) - 1)) / __nmax(8 - (n)))
#define _fill_missing_bits(c, n, _else) __fill_missing_bits(c, n)
#define fill_missing_bits(c, n)         __fill_missing_bits(c, n)
#else /* !USE_FAST_COLOR_UPSCALE */
#if 0 /* Basic impl just to get the logic down (don't use; super-inefficient) */
LOCAL ATTR_CONST video_channel_t FCC
fill_missing_bits(video_channel_t value, shift_t miss_bits) {
	video_channel_t result = value << miss_bits;
	shift_t present_bits = NBBY - miss_bits;
	while (miss_bits) {
		shift_t copy_bits = present_bits;
		if (copy_bits > miss_bits)
			copy_bits = miss_bits;
		miss_bits -= copy_bits;
		result |= (result >> (NBBY - copy_bits)) << miss_bits;
	}
	return result;
}
#else
#if 0 /* Slightly less code, but shift offsets aren't constant */
#define _fill_missing_bits(c, n, _else)                               \
	( (n) <= 4 ? (uint8_t)(((c) << (n)) | ((c) >> (8 - ((n) << 1))))  \
	: (n) == 5 ? (uint8_t)(((c) << 5) | ((c) << 2) | ((c) >> 1))      \
	: (n) == 6 ? 0x55 * (c) /* (uint8_t)(((c) << 6) | ((c) << 4) | ((c) << 2) | (c)) */ \
	: (n) == 7 ? 0xff * (c)                                           \
	: _else)
#elif 1
#define _fill_missing_bits(c, n, _else)             \
	( (n) == 0 ? (c)                                \
	: (n) == 1 ? (uint8_t)(((c) << 1) | ((c) >> 6)) \
	: (n) == 2 ? (uint8_t)(((c) << 2) | ((c) >> 4)) \
	: (n) == 3 ? (uint8_t)(((c) << 3) | ((c) >> 2)) \
	: (n) == 4 ? 0x11 * (c) /* (uint8_t)(((c) << 4) | ((c))) */ \
	: (n) == 5 ? (uint8_t)(((c) << 5) | ((c) << 2) | ((c) >> 1))  \
	: (n) == 6 ? 0x55 * (c) /* (uint8_t)(((c) << 6) | ((c) << 4) | ((c) << 2) | (c)) */ \
	: (n) == 7 ? 0xff * (c)                         \
	: _else)
#endif /* ... */

LOCAL ATTR_CONST video_channel_t FCC
fill_missing_bits(video_channel_t value,
                  shift_t miss_bits) {
	return _fill_missing_bits(value, miss_bits, (__builtin_unreachable(), -999));
}
#endif /* ... */
#endif /* USE_FAST_COLOR_UPSCALE */



#define rgb_getlumen8(r, g, b)      ((uint8_t)((uint_fast16_t)((uint_fast16_t)r + g + b + (3 / 2)) / 3))
#define rgb_getlumen1(r, g, b)      (rgb_getlumen8(r, g, b) >> 7)
#define rgb_getlumen2(r, g, b)      (rgb_getlumen8(r, g, b) >> 6)
#define rgb_getlumen3(r, g, b)      (rgb_getlumen8(r, g, b) >> 5)
#define rgb_getlumen4(r, g, b)      (rgb_getlumen8(r, g, b) >> 4)
#define rgb_getlumen7_shl1(r, g, b) (rgb_getlumen8(r, g, b) & 0xfe)
#define rgb_getlumen7(r, g, b)      (rgb_getlumen8(r, g, b) >> 1)

#define color_getlumen1(c)      rgb_getlumen1(VIDEO_COLOR_GET_RED(c), VIDEO_COLOR_GET_GREEN(c), VIDEO_COLOR_GET_BLUE(c))
#define color_getlumen2(c)      rgb_getlumen2(VIDEO_COLOR_GET_RED(c), VIDEO_COLOR_GET_GREEN(c), VIDEO_COLOR_GET_BLUE(c))
#define color_getlumen3(c)      rgb_getlumen3(VIDEO_COLOR_GET_RED(c), VIDEO_COLOR_GET_GREEN(c), VIDEO_COLOR_GET_BLUE(c))
#define color_getlumen4(c)      rgb_getlumen4(VIDEO_COLOR_GET_RED(c), VIDEO_COLOR_GET_GREEN(c), VIDEO_COLOR_GET_BLUE(c))
#define color_getlumen7_shl1(c) rgb_getlumen7_shl1(VIDEO_COLOR_GET_RED(c), VIDEO_COLOR_GET_GREEN(c), VIDEO_COLOR_GET_BLUE(c))
#define color_getlumen7(c)      rgb_getlumen7(VIDEO_COLOR_GET_RED(c), VIDEO_COLOR_GET_GREEN(c), VIDEO_COLOR_GET_BLUE(c))
#define color_getlumen8(c)      rgb_getlumen8(VIDEO_COLOR_GET_RED(c), VIDEO_COLOR_GET_GREEN(c), VIDEO_COLOR_GET_BLUE(c))

#define _color_getx1(c, s)      (((c) & ((video_color_t)0x80 << (s))) >> ((s) + 7))
#define _color_getx2(c, s)      (((c) & ((video_color_t)0xc0 << (s))) >> ((s) + 6))
#define _color_getx3(c, s)      (((c) & ((video_color_t)0xe0 << (s))) >> ((s) + 5))
#define _color_getx4(c, s)      (((c) & ((video_color_t)0xf0 << (s))) >> ((s) + 4))
#define _color_getx5(c, s)      (((c) & ((video_color_t)0xf8 << (s))) >> ((s) + 3))
#define _color_getx6(c, s)      (((c) & ((video_color_t)0xfc << (s))) >> ((s) + 2))
#define _color_getx7(c, s)      (((c) & ((video_color_t)0xfe << (s))) >> ((s) + 1))

#define color_getalpha1_shl7(c) (((c) & ((video_color_t)0x80 << VIDEO_COLOR_ALPHA_SHIFT)) >> VIDEO_COLOR_ALPHA_SHIFT)
#define color_getalpha1(c)      _color_getx1(c, VIDEO_COLOR_ALPHA_SHIFT)
#define color_getalpha2(c)      _color_getx2(c, VIDEO_COLOR_ALPHA_SHIFT)
#define color_getalpha3(c)      _color_getx3(c, VIDEO_COLOR_ALPHA_SHIFT)
#define color_getalpha4(c)      _color_getx4(c, VIDEO_COLOR_ALPHA_SHIFT)
#define color_getalpha5(c)      _color_getx5(c, VIDEO_COLOR_ALPHA_SHIFT)
#define color_getalpha6(c)      _color_getx6(c, VIDEO_COLOR_ALPHA_SHIFT)
#define color_getalpha7(c)      _color_getx7(c, VIDEO_COLOR_ALPHA_SHIFT)
#define color_getalpha8(c)      VIDEO_COLOR_GET_ALPHA(c)

#define color_getred1(c)        _color_getx1(c, VIDEO_COLOR_RED_SHIFT)
#define color_getred2(c)        _color_getx2(c, VIDEO_COLOR_RED_SHIFT)
#define color_getred3(c)        _color_getx3(c, VIDEO_COLOR_RED_SHIFT)
#define color_getred4(c)        _color_getx4(c, VIDEO_COLOR_RED_SHIFT)
#define color_getred5(c)        _color_getx5(c, VIDEO_COLOR_RED_SHIFT)
#define color_getred6(c)        _color_getx6(c, VIDEO_COLOR_RED_SHIFT)
#define color_getred7(c)        _color_getx7(c, VIDEO_COLOR_RED_SHIFT)
#define color_getred8(c)        VIDEO_COLOR_GET_RED(c)

#define color_getgreen1(c)      _color_getx1(c, VIDEO_COLOR_GREEN_SHIFT)
#define color_getgreen2(c)      _color_getx2(c, VIDEO_COLOR_GREEN_SHIFT)
#define color_getgreen3(c)      _color_getx3(c, VIDEO_COLOR_GREEN_SHIFT)
#define color_getgreen4(c)      _color_getx4(c, VIDEO_COLOR_GREEN_SHIFT)
#define color_getgreen5(c)      _color_getx5(c, VIDEO_COLOR_GREEN_SHIFT)
#define color_getgreen6(c)      _color_getx6(c, VIDEO_COLOR_GREEN_SHIFT)
#define color_getgreen7(c)      _color_getx7(c, VIDEO_COLOR_GREEN_SHIFT)
#define color_getgreen8(c)      VIDEO_COLOR_GET_GREEN(c)

#define color_getblue1(c)       _color_getx1(c, VIDEO_COLOR_BLUE_SHIFT)
#define color_getblue2(c)       _color_getx2(c, VIDEO_COLOR_BLUE_SHIFT)
#define color_getblue3(c)       _color_getx3(c, VIDEO_COLOR_BLUE_SHIFT)
#define color_getblue4(c)       _color_getx4(c, VIDEO_COLOR_BLUE_SHIFT)
#define color_getblue5(c)       _color_getx5(c, VIDEO_COLOR_BLUE_SHIFT)
#define color_getblue6(c)       _color_getx6(c, VIDEO_COLOR_BLUE_SHIFT)
#define color_getblue7(c)       _color_getx7(c, VIDEO_COLOR_BLUE_SHIFT)
#define color_getblue8(c)       VIDEO_COLOR_GET_BLUE(c)

#define red8_tocolor(v)         (video_color_t)((UINT32_C(0x01010101) & VIDEO_COLOR_RED_MASK) * (v))
#define red7_tocolor(v)         red8_tocolor(c7_to_c8(v))
#define red6_tocolor(v)         red8_tocolor(c6_to_c8(v))
#define red5_tocolor(v)         red8_tocolor(c5_to_c8(v))
#define red4_tocolor(v)         (video_color_t)((UINT32_C(0x11111111) & VIDEO_COLOR_RED_MASK) * (v))
#define red3_tocolor(v)         red8_tocolor(c3_to_c8(v))
#define red2_tocolor(v)         (video_color_t)((UINT32_C(0x55555555) & VIDEO_COLOR_RED_MASK) * (v))
#define red1_tocolor(v)         (video_color_t)(VIDEO_COLOR_RED_MASK * (v))

#define green8_tocolor(v)       (video_color_t)((UINT32_C(0x01010101) & VIDEO_COLOR_GREEN_MASK) * (v))
#define green7_tocolor(v)       green8_tocolor(c7_to_c8(v))
#define green6_tocolor(v)       green8_tocolor(c6_to_c8(v))
#define green5_tocolor(v)       green8_tocolor(c5_to_c8(v))
#define green4_tocolor(v)       (video_color_t)((UINT32_C(0x11111111) & VIDEO_COLOR_GREEN_MASK) * (v))
#define green3_tocolor(v)       green8_tocolor(c3_to_c8(v))
#define green2_tocolor(v)       (video_color_t)((UINT32_C(0x55555555) & VIDEO_COLOR_GREEN_MASK) * (v))
#define green1_tocolor(v)       (video_color_t)(VIDEO_COLOR_GREEN_MASK * (v))

#define blue8_tocolor(v)        (video_color_t)((UINT32_C(0x01010101) & VIDEO_COLOR_BLUE_MASK) * (v))
#define blue7_tocolor(v)        blue8_tocolor(c7_to_c8(v))
#define blue6_tocolor(v)        blue8_tocolor(c6_to_c8(v))
#define blue5_tocolor(v)        blue8_tocolor(c5_to_c8(v))
#define blue4_tocolor(v)        (video_color_t)((UINT32_C(0x11111111) & VIDEO_COLOR_BLUE_MASK) * (v))
#define blue3_tocolor(v)        blue8_tocolor(c3_to_c8(v))
#define blue2_tocolor(v)        (video_color_t)((UINT32_C(0x55555555) & VIDEO_COLOR_BLUE_MASK) * (v))
#define blue1_tocolor(v)        (video_color_t)(VIDEO_COLOR_BLUE_MASK * (v))

#define alpha8_tocolor(v)       (video_color_t)((UINT32_C(0x01010101) & VIDEO_COLOR_ALPHA_MASK) * (v))
#define alpha7_tocolor(v)       alpha8_tocolor(c7_to_c8(v))
#define alpha6_tocolor(v)       alpha8_tocolor(c6_to_c8(v))
#define alpha5_tocolor(v)       alpha8_tocolor(c5_to_c8(v))
#define alpha4_tocolor(v)       (video_color_t)((UINT32_C(0x11111111) & VIDEO_COLOR_ALPHA_MASK) * (v))
#define alpha3_tocolor(v)       alpha8_tocolor(c3_to_c8(v))
#define alpha2_tocolor(v)       (video_color_t)((UINT32_C(0x55555555) & VIDEO_COLOR_ALPHA_MASK) * (v))
#define alpha1_tocolor(v)       (video_color_t)(VIDEO_COLOR_ALPHA_MASK * (v))

#define lumen8_tocolor(v)       (video_color_t)((UINT32_C(0x01010101) & (VIDEO_COLOR_RED_MASK | VIDEO_COLOR_GREEN_MASK | VIDEO_COLOR_BLUE_MASK)) * (v))
#define lumen7_tocolor(v)       lumen8_tocolor(c7_to_c8(v))
#define lumen6_tocolor(v)       lumen8_tocolor(c6_to_c8(v))
#define lumen5_tocolor(v)       lumen8_tocolor(c5_to_c8(v))
#define lumen4_tocolor(v)       (video_color_t)((UINT32_C(0x11111111) & (VIDEO_COLOR_RED_MASK | VIDEO_COLOR_GREEN_MASK | VIDEO_COLOR_BLUE_MASK)) * (v))
#define lumen3_tocolor(v)       lumen8_tocolor(c3_to_c8(v))
#define lumen2_tocolor(v)       (video_color_t)((UINT32_C(0x55555555) & (VIDEO_COLOR_RED_MASK | VIDEO_COLOR_GREEN_MASK | VIDEO_COLOR_BLUE_MASK)) * (v))
#define lumen1_tocolor(v)       (video_color_t)((VIDEO_COLOR_RED_MASK | VIDEO_COLOR_GREEN_MASK | VIDEO_COLOR_BLUE_MASK) * (v))



/************************************************************************/
/* Assert that conversion from fixed-length alpha/lumen works           */
#ifdef _fill_missing_bits
#define _ASSERT__fill_missing_bits(n, v, result) \
	static_assert(_fill_missing_bits(v, 8 - n, -999) == result);
#else /* _fill_missing_bits */
#define _ASSERT__fill_missing_bits(n, v, result) /* nothing */
#endif /* !_fill_missing_bits */

#define ASSERT_N_TO_COLOR(n, v, result)                                                  \
	_ASSERT__fill_missing_bits(n, v, result)                                             \
	static_assert(lumen##n##_tocolor(v) == VIDEO_COLOR_RGBA(result, result, result, 0)); \
	static_assert(red##n##_tocolor(v) == VIDEO_COLOR_RGBA(result, 0, 0, 0));             \
	static_assert(green##n##_tocolor(v) == VIDEO_COLOR_RGBA(0, result, 0, 0));           \
	static_assert(blue##n##_tocolor(v) == VIDEO_COLOR_RGBA(0, 0, result, 0));            \
	static_assert(alpha##n##_tocolor(v) == VIDEO_COLOR_RGBA(0, 0, 0, result))


#ifdef USE_FAST_COLOR_UPSCALE
#define ASSERT_N_TO_COLOR_FAST(n, v, fast_result, correct_result) \
	ASSERT_N_TO_COLOR(n, v, fast_result)
#else /* USE_FAST_COLOR_UPSCALE */
#define ASSERT_N_TO_COLOR_FAST(n, v, fast_result, correct_result) \
	ASSERT_N_TO_COLOR(n, v, correct_result)
#endif /* !USE_FAST_COLOR_UPSCALE */


ASSERT_N_TO_COLOR(1, 0, 0x00);
ASSERT_N_TO_COLOR(1, 1, 0xff);

ASSERT_N_TO_COLOR(2, 0, 0x00);
ASSERT_N_TO_COLOR(2, 1, 0x55);
ASSERT_N_TO_COLOR(2, 2, 0xaa);
ASSERT_N_TO_COLOR(2, 3, 0xff);

ASSERT_N_TO_COLOR(3, 0, 0x00);
ASSERT_N_TO_COLOR(3, 1, 0x24);
ASSERT_N_TO_COLOR(3, 2, 0x49);
ASSERT_N_TO_COLOR(3, 3, 0x6d);
ASSERT_N_TO_COLOR(3, 4, 0x92);
ASSERT_N_TO_COLOR(3, 5, 0xb6);
ASSERT_N_TO_COLOR(3, 6, 0xdb);
ASSERT_N_TO_COLOR(3, 7, 0xff);

ASSERT_N_TO_COLOR(4, 0x0, 0x00);
ASSERT_N_TO_COLOR(4, 0x1, 0x11);
ASSERT_N_TO_COLOR(4, 0x2, 0x22);
ASSERT_N_TO_COLOR(4, 0x3, 0x33);
ASSERT_N_TO_COLOR(4, 0x4, 0x44);
ASSERT_N_TO_COLOR(4, 0x5, 0x55);
ASSERT_N_TO_COLOR(4, 0x6, 0x66);
ASSERT_N_TO_COLOR(4, 0x7, 0x77);
ASSERT_N_TO_COLOR(4, 0x8, 0x88);
ASSERT_N_TO_COLOR(4, 0x9, 0x99);
ASSERT_N_TO_COLOR(4, 0xa, 0xaa);
ASSERT_N_TO_COLOR(4, 0xb, 0xbb);
ASSERT_N_TO_COLOR(4, 0xc, 0xcc);
ASSERT_N_TO_COLOR(4, 0xd, 0xdd);
ASSERT_N_TO_COLOR(4, 0xe, 0xee);
ASSERT_N_TO_COLOR(4, 0xf, 0xff);

ASSERT_N_TO_COLOR(5, 0, 0x00);
ASSERT_N_TO_COLOR(5, 1, 0x08);
ASSERT_N_TO_COLOR(5, 2, 0x10);
ASSERT_N_TO_COLOR_FAST(5, 3, 0x18, 0x19);
ASSERT_N_TO_COLOR(5, 4, 0x21);
ASSERT_N_TO_COLOR(5, 5, 0x29);
ASSERT_N_TO_COLOR(5, 6, 0x31);
ASSERT_N_TO_COLOR_FAST(5, 7, 0x39, 0x3a);
ASSERT_N_TO_COLOR(5, 8, 0x42);
ASSERT_N_TO_COLOR(5, 9, 0x4a);
ASSERT_N_TO_COLOR(5, 10, 0x52);
ASSERT_N_TO_COLOR(5, 11, 0x5a);
ASSERT_N_TO_COLOR(5, 12, 0x63);
ASSERT_N_TO_COLOR(5, 13, 0x6b);
ASSERT_N_TO_COLOR(5, 14, 0x73);
ASSERT_N_TO_COLOR(5, 15, 0x7b);
ASSERT_N_TO_COLOR(5, 16, 0x84);
ASSERT_N_TO_COLOR(5, 17, 0x8c);
ASSERT_N_TO_COLOR(5, 18, 0x94);
ASSERT_N_TO_COLOR(5, 19, 0x9c);
ASSERT_N_TO_COLOR(5, 20, 0xa5);
ASSERT_N_TO_COLOR(5, 21, 0xad);
ASSERT_N_TO_COLOR(5, 22, 0xb5);
ASSERT_N_TO_COLOR(5, 23, 0xbd);
ASSERT_N_TO_COLOR_FAST(5, 24, 0xc6, 0xc5);
ASSERT_N_TO_COLOR(5, 25, 0xce);
ASSERT_N_TO_COLOR(5, 26, 0xd6);
ASSERT_N_TO_COLOR(5, 27, 0xde);
ASSERT_N_TO_COLOR_FAST(5, 28, 0xe7, 0xe6);
ASSERT_N_TO_COLOR(5, 29, 0xef);
ASSERT_N_TO_COLOR(5, 30, 0xf7);
ASSERT_N_TO_COLOR(5, 31, 0xff);

ASSERT_N_TO_COLOR(6, 0, 0x00);
ASSERT_N_TO_COLOR(6, 1, 0x04);
ASSERT_N_TO_COLOR(6, 2, 0x08);
ASSERT_N_TO_COLOR(6, 3, 0x0c);
ASSERT_N_TO_COLOR(6, 4, 0x10);
ASSERT_N_TO_COLOR(6, 5, 0x14);
ASSERT_N_TO_COLOR(6, 6, 0x18);
ASSERT_N_TO_COLOR(6, 7, 0x1c);
ASSERT_N_TO_COLOR(6, 8, 0x20);
ASSERT_N_TO_COLOR(6, 9, 0x24);
ASSERT_N_TO_COLOR(6, 10, 0x28);
ASSERT_N_TO_COLOR_FAST(6, 11, 0x2c, 0x2d);
ASSERT_N_TO_COLOR_FAST(6, 12, 0x30, 0x31);
ASSERT_N_TO_COLOR_FAST(6, 13, 0x34, 0x35);
ASSERT_N_TO_COLOR_FAST(6, 14, 0x38, 0x39);
ASSERT_N_TO_COLOR_FAST(6, 15, 0x3c, 0x3d);
ASSERT_N_TO_COLOR(6, 16, 0x41);
ASSERT_N_TO_COLOR(6, 17, 0x45);
ASSERT_N_TO_COLOR(6, 18, 0x49);
ASSERT_N_TO_COLOR(6, 19, 0x4d);
ASSERT_N_TO_COLOR(6, 20, 0x51);
ASSERT_N_TO_COLOR(6, 21, 0x55);
ASSERT_N_TO_COLOR(6, 22, 0x59);
ASSERT_N_TO_COLOR(6, 23, 0x5d);
ASSERT_N_TO_COLOR(6, 24, 0x61);
ASSERT_N_TO_COLOR(6, 25, 0x65);
ASSERT_N_TO_COLOR(6, 26, 0x69);
ASSERT_N_TO_COLOR(6, 27, 0x6d);
ASSERT_N_TO_COLOR(6, 28, 0x71);
ASSERT_N_TO_COLOR(6, 29, 0x75);
ASSERT_N_TO_COLOR(6, 30, 0x79);
ASSERT_N_TO_COLOR(6, 31, 0x7d);
ASSERT_N_TO_COLOR(6, 32, 0x82);
ASSERT_N_TO_COLOR(6, 33, 0x86);
ASSERT_N_TO_COLOR(6, 34, 0x8a);
ASSERT_N_TO_COLOR(6, 35, 0x8e);
ASSERT_N_TO_COLOR(6, 36, 0x92);
ASSERT_N_TO_COLOR(6, 37, 0x96);
ASSERT_N_TO_COLOR(6, 38, 0x9a);
ASSERT_N_TO_COLOR(6, 39, 0x9e);
ASSERT_N_TO_COLOR(6, 40, 0xa2);
ASSERT_N_TO_COLOR(6, 41, 0xa6);
ASSERT_N_TO_COLOR(6, 42, 0xaa);
ASSERT_N_TO_COLOR(6, 43, 0xae);
ASSERT_N_TO_COLOR(6, 44, 0xb2);
ASSERT_N_TO_COLOR(6, 45, 0xb6);
ASSERT_N_TO_COLOR(6, 46, 0xba);
ASSERT_N_TO_COLOR(6, 47, 0xbe);
ASSERT_N_TO_COLOR_FAST(6, 48, 0xc3, 0xc2);
ASSERT_N_TO_COLOR_FAST(6, 49, 0xc7, 0xc6);
ASSERT_N_TO_COLOR_FAST(6, 50, 0xcb, 0xca);
ASSERT_N_TO_COLOR_FAST(6, 51, 0xcf, 0xce);
ASSERT_N_TO_COLOR_FAST(6, 52, 0xd3, 0xd2);
ASSERT_N_TO_COLOR(6, 53, 0xd7);
ASSERT_N_TO_COLOR(6, 54, 0xdb);
ASSERT_N_TO_COLOR(6, 55, 0xdf);
ASSERT_N_TO_COLOR(6, 56, 0xe3);
ASSERT_N_TO_COLOR(6, 57, 0xe7);
ASSERT_N_TO_COLOR(6, 58, 0xeb);
ASSERT_N_TO_COLOR(6, 59, 0xef);
ASSERT_N_TO_COLOR(6, 60, 0xf3);
ASSERT_N_TO_COLOR(6, 61, 0xf7);
ASSERT_N_TO_COLOR(6, 62, 0xfb);
ASSERT_N_TO_COLOR(6, 63, 0xff);


ASSERT_N_TO_COLOR(7, 0, 0x00);
ASSERT_N_TO_COLOR(7, 1, 0x02);
ASSERT_N_TO_COLOR(7, 2, 0x04);
ASSERT_N_TO_COLOR(7, 3, 0x06);
ASSERT_N_TO_COLOR(7, 4, 0x08);
ASSERT_N_TO_COLOR(7, 5, 0x0a);
ASSERT_N_TO_COLOR(7, 6, 0x0c);
ASSERT_N_TO_COLOR(7, 7, 0x0e);
ASSERT_N_TO_COLOR(7, 8, 0x10);
ASSERT_N_TO_COLOR(7, 9, 0x12);
ASSERT_N_TO_COLOR(7, 10, 0x14);
ASSERT_N_TO_COLOR(7, 11, 0x16);
ASSERT_N_TO_COLOR(7, 12, 0x18);
ASSERT_N_TO_COLOR(7, 13, 0x1a);
ASSERT_N_TO_COLOR(7, 14, 0x1c);
ASSERT_N_TO_COLOR(7, 15, 0x1e);
ASSERT_N_TO_COLOR(7, 16, 0x20);
ASSERT_N_TO_COLOR(7, 17, 0x22);
ASSERT_N_TO_COLOR(7, 18, 0x24);
ASSERT_N_TO_COLOR(7, 19, 0x26);
ASSERT_N_TO_COLOR(7, 20, 0x28);
ASSERT_N_TO_COLOR(7, 21, 0x2a);
ASSERT_N_TO_COLOR(7, 22, 0x2c);
ASSERT_N_TO_COLOR(7, 23, 0x2e);
ASSERT_N_TO_COLOR(7, 24, 0x30);
ASSERT_N_TO_COLOR(7, 25, 0x32);
ASSERT_N_TO_COLOR(7, 26, 0x34);
ASSERT_N_TO_COLOR(7, 27, 0x36);
ASSERT_N_TO_COLOR(7, 28, 0x38);
ASSERT_N_TO_COLOR(7, 29, 0x3a);
ASSERT_N_TO_COLOR(7, 30, 0x3c);
ASSERT_N_TO_COLOR(7, 31, 0x3e);
ASSERT_N_TO_COLOR(7, 32, 0x40);
ASSERT_N_TO_COLOR(7, 33, 0x42);
ASSERT_N_TO_COLOR(7, 34, 0x44);
ASSERT_N_TO_COLOR(7, 35, 0x46);
ASSERT_N_TO_COLOR(7, 36, 0x48);
ASSERT_N_TO_COLOR(7, 37, 0x4a);
ASSERT_N_TO_COLOR(7, 38, 0x4c);
ASSERT_N_TO_COLOR(7, 39, 0x4e);
ASSERT_N_TO_COLOR(7, 40, 0x50);
ASSERT_N_TO_COLOR(7, 41, 0x52);
ASSERT_N_TO_COLOR(7, 42, 0x54);
ASSERT_N_TO_COLOR(7, 43, 0x56);
ASSERT_N_TO_COLOR(7, 44, 0x58);
ASSERT_N_TO_COLOR(7, 45, 0x5a);
ASSERT_N_TO_COLOR(7, 46, 0x5c);
ASSERT_N_TO_COLOR(7, 47, 0x5e);
ASSERT_N_TO_COLOR(7, 48, 0x60);
ASSERT_N_TO_COLOR(7, 49, 0x62);
ASSERT_N_TO_COLOR(7, 50, 0x64);
ASSERT_N_TO_COLOR(7, 51, 0x66);
ASSERT_N_TO_COLOR(7, 52, 0x68);
ASSERT_N_TO_COLOR(7, 53, 0x6a);
ASSERT_N_TO_COLOR(7, 54, 0x6c);
ASSERT_N_TO_COLOR(7, 55, 0x6e);
ASSERT_N_TO_COLOR(7, 56, 0x70);
ASSERT_N_TO_COLOR(7, 57, 0x72);
ASSERT_N_TO_COLOR(7, 58, 0x74);
ASSERT_N_TO_COLOR(7, 59, 0x76);
ASSERT_N_TO_COLOR(7, 60, 0x78);
ASSERT_N_TO_COLOR(7, 61, 0x7a);
ASSERT_N_TO_COLOR(7, 62, 0x7c);
ASSERT_N_TO_COLOR(7, 63, 0x7e);
ASSERT_N_TO_COLOR(7, 64, 0x81);
ASSERT_N_TO_COLOR(7, 65, 0x83);
ASSERT_N_TO_COLOR(7, 66, 0x85);
ASSERT_N_TO_COLOR(7, 67, 0x87);
ASSERT_N_TO_COLOR(7, 68, 0x89);
ASSERT_N_TO_COLOR(7, 69, 0x8b);
ASSERT_N_TO_COLOR(7, 70, 0x8d);
ASSERT_N_TO_COLOR(7, 71, 0x8f);
ASSERT_N_TO_COLOR(7, 72, 0x91);
ASSERT_N_TO_COLOR(7, 73, 0x93);
ASSERT_N_TO_COLOR(7, 74, 0x95);
ASSERT_N_TO_COLOR(7, 75, 0x97);
ASSERT_N_TO_COLOR(7, 76, 0x99);
ASSERT_N_TO_COLOR(7, 77, 0x9b);
ASSERT_N_TO_COLOR(7, 78, 0x9d);
ASSERT_N_TO_COLOR(7, 79, 0x9f);
ASSERT_N_TO_COLOR(7, 80, 0xa1);
ASSERT_N_TO_COLOR(7, 81, 0xa3);
ASSERT_N_TO_COLOR(7, 82, 0xa5);
ASSERT_N_TO_COLOR(7, 83, 0xa7);
ASSERT_N_TO_COLOR(7, 84, 0xa9);
ASSERT_N_TO_COLOR(7, 85, 0xab);
ASSERT_N_TO_COLOR(7, 86, 0xad);
ASSERT_N_TO_COLOR(7, 87, 0xaf);
ASSERT_N_TO_COLOR(7, 88, 0xb1);
ASSERT_N_TO_COLOR(7, 89, 0xb3);
ASSERT_N_TO_COLOR(7, 90, 0xb5);
ASSERT_N_TO_COLOR(7, 91, 0xb7);
ASSERT_N_TO_COLOR(7, 92, 0xb9);
ASSERT_N_TO_COLOR(7, 93, 0xbb);
ASSERT_N_TO_COLOR(7, 94, 0xbd);
ASSERT_N_TO_COLOR(7, 95, 0xbf);
ASSERT_N_TO_COLOR(7, 96, 0xc1);
ASSERT_N_TO_COLOR(7, 97, 0xc3);
ASSERT_N_TO_COLOR(7, 98, 0xc5);
ASSERT_N_TO_COLOR(7, 99, 0xc7);
ASSERT_N_TO_COLOR(7, 100, 0xc9);
ASSERT_N_TO_COLOR(7, 101, 0xcb);
ASSERT_N_TO_COLOR(7, 102, 0xcd);
ASSERT_N_TO_COLOR(7, 103, 0xcf);
ASSERT_N_TO_COLOR(7, 104, 0xd1);
ASSERT_N_TO_COLOR(7, 105, 0xd3);
ASSERT_N_TO_COLOR(7, 106, 0xd5);
ASSERT_N_TO_COLOR(7, 107, 0xd7);
ASSERT_N_TO_COLOR(7, 108, 0xd9);
ASSERT_N_TO_COLOR(7, 109, 0xdb);
ASSERT_N_TO_COLOR(7, 110, 0xdd);
ASSERT_N_TO_COLOR(7, 111, 0xdf);
ASSERT_N_TO_COLOR(7, 112, 0xe1);
ASSERT_N_TO_COLOR(7, 113, 0xe3);
ASSERT_N_TO_COLOR(7, 114, 0xe5);
ASSERT_N_TO_COLOR(7, 115, 0xe7);
ASSERT_N_TO_COLOR(7, 116, 0xe9);
ASSERT_N_TO_COLOR(7, 117, 0xeb);
ASSERT_N_TO_COLOR(7, 118, 0xed);
ASSERT_N_TO_COLOR(7, 119, 0xef);
ASSERT_N_TO_COLOR(7, 120, 0xf1);
ASSERT_N_TO_COLOR(7, 121, 0xf3);
ASSERT_N_TO_COLOR(7, 122, 0xf5);
ASSERT_N_TO_COLOR(7, 123, 0xf7);
ASSERT_N_TO_COLOR(7, 124, 0xf9);
ASSERT_N_TO_COLOR(7, 125, 0xfb);
ASSERT_N_TO_COLOR(7, 126, 0xfd);
ASSERT_N_TO_COLOR(7, 127, 0xff);
#undef ASSERT_N_TO_COLOR_FAST
#undef ASSERT_N_TO_COLOR



PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
l1_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return VIDEO_COLOR_ALPHA_MASK | lumen1_tocolor(pixel & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
l1_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return color_getlumen1(color);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
l2_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return VIDEO_COLOR_ALPHA_MASK | lumen2_tocolor(pixel & 0x3);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
l2_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return color_getlumen2(color);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
l4_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return VIDEO_COLOR_ALPHA_MASK | lumen4_tocolor(pixel & 0xf);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
l4_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return color_getlumen4(color);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
l8_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return VIDEO_COLOR_ALPHA_MASK | lumen8_tocolor(pixel & 0xff);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
l8_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return color_getlumen8(color);
}


PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
a1_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return alpha1_tocolor(pixel & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
a1_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return color_getalpha1(color);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
a2_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return alpha2_tocolor(pixel & 0x3);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
a2_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return color_getalpha2(color);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
a4_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return alpha4_tocolor(pixel & 0xf);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
a4_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return color_getalpha4(color);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
a8_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return alpha8_tocolor(pixel & 0xff);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
a8_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return color_getalpha8(color);
}


PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
al11_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return alpha1_tocolor((pixel) & 1) |
	       lumen1_tocolor((pixel >> 1) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
al11_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return ((video_pixel_t)color_getalpha1(color)) |
	       ((video_pixel_t)color_getlumen1(color) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
la11_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return lumen1_tocolor((pixel) & 1) |
	       alpha1_tocolor((pixel >> 1) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
la11_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return ((video_pixel_t)color_getlumen1(color)) |
	       ((video_pixel_t)color_getalpha1(color) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
al22_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return alpha2_tocolor((pixel) & 3) |
	       lumen2_tocolor((pixel >> 2) & 3);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
al22_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return ((video_pixel_t)color_getalpha2(color)) |
	       ((video_pixel_t)color_getlumen2(color) << 2);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
la22_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return lumen2_tocolor((pixel) & 3) |
	       alpha2_tocolor((pixel >> 2) & 3);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
la22_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return ((video_pixel_t)color_getlumen2(color)) |
	       ((video_pixel_t)color_getalpha2(color) << 2);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
al13_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return alpha1_tocolor((pixel) & 1) |
	       lumen3_tocolor((pixel >> 1) & 7);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
al13_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return ((video_pixel_t)color_getalpha1(color)) |
	       ((video_pixel_t)color_getlumen3(color) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
la31_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return lumen3_tocolor((pixel) & 7) |
	       alpha1_tocolor((pixel >> 3) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
la31_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return ((video_pixel_t)color_getlumen3(color)) |
	       ((video_pixel_t)color_getalpha1(color) << 3);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
al44_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return alpha4_tocolor((pixel) & 0xf) |
	       lumen4_tocolor((pixel >> 4) & 0xf);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
al44_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return ((video_pixel_t)color_getalpha4(color)) |
	       ((video_pixel_t)color_getlumen4(color) << 4);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
la44_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return lumen4_tocolor((pixel) & 0xf) |
	       alpha4_tocolor((pixel >> 4) & 0xf);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
la44_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return ((video_pixel_t)color_getlumen4(color)) |
	       ((video_pixel_t)color_getalpha4(color) << 4);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
al17_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return alpha1_tocolor((pixel) & 1) |
	       lumen7_tocolor((pixel >> 1) & 127);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
al17_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return ((video_pixel_t)color_getalpha1(color)) |
	       ((video_pixel_t)color_getlumen7_shl1(color));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
la71_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return lumen7_tocolor((pixel) & 127) |
	       alpha1_tocolor((pixel >> 7) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
la71_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return ((video_pixel_t)color_getlumen7(color)) |
	       ((video_pixel_t)color_getalpha1_shl7(color));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
al88_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return alpha8_tocolor((pixel) & 0xff) |
	       lumen8_tocolor((pixel >> 8) & 0xff);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
al88_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return ((video_pixel_t)color_getalpha8(color)) |
	       ((video_pixel_t)color_getlumen8(color) << 8);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
la88_pixel2color(struct video_surface const *__restrict UNUSED(surface), video_pixel_t pixel) {
	return lumen8_tocolor((pixel) & 0xff) |
	       alpha8_tocolor((pixel >> 8) & 0xff);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
la88_color2pixel(struct video_surface const *__restrict UNUSED(surface), video_color_t color) {
	return ((video_pixel_t)color_getlumen8(color)) |
	       ((video_pixel_t)color_getalpha8(color) << 8);
}


DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, l1)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, l2)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, l4)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, l8)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, a1)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, a2)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, a4)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, a8)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, al11)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, la11)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, al22)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, la22)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, al13)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, la31)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, al44)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, la44)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, al17)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, la71)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, al88)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, la88)


/* Cross-byte pixel format coverters */
#define DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGBA(name, datatype, union_type,     \
                                                         r_bits, g_bits, b_bits, a_bits) \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC                            \
	name##_color2pixel(struct video_surface const *__restrict UNUSED(surface),           \
	                   video_color_t color) {                                            \
		union_type px;                                                                   \
		px.r = color_getred##r_bits(color);                                              \
		px.g = color_getgreen##g_bits(color);                                            \
		px.b = color_getblue##b_bits(color);                                             \
		px.a = color_getalpha##a_bits(color);                                            \
		return px.data;                                                                  \
	}                                                                                    \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC                            \
	name##_pixel2color(struct video_surface const *__restrict UNUSED(surface),           \
	                   video_pixel_t pixel) {                                            \
		union_type px;                                                                   \
		px.data = (datatype)pixel;                                                       \
		return red##r_bits##_tocolor(px.r) |                                             \
		       green##g_bits##_tocolor(px.g) |                                           \
		       blue##b_bits##_tocolor(px.b) |                                            \
		       alpha##a_bits##_tocolor(px.a);                                            \
	}                                                                                    \
	DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, name)

#define DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGBX(name, datatype, union_type, \
                                                         r_bits, g_bits, b_bits)     \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC                        \
	name##_color2pixel(struct video_surface const *__restrict UNUSED(surface),       \
	                   video_color_t color) {                                        \
		union_type px;                                                               \
		px.r = color_getred##r_bits(color);                                          \
		px.g = color_getgreen##g_bits(color);                                        \
		px.b = color_getblue##b_bits(color);                                         \
		px.x = 0;                                                                    \
		return px.data;                                                              \
	}                                                                                \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC                        \
	name##_pixel2color(struct video_surface const *__restrict UNUSED(surface),       \
	                   video_pixel_t pixel) {                                        \
		union_type px;                                                               \
		px.data = (datatype)pixel;                                                   \
		return red##r_bits##_tocolor(px.r) |                                         \
		       green##g_bits##_tocolor(px.g) |                                       \
		       blue##b_bits##_tocolor(px.b) |                                        \
		       VIDEO_COLOR_ALPHA_MASK;                                               \
	}                                                                                \
	DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, name)

#define DEFINE_FORMAT_CONVERTER_WITH_BITFIELD_UNION_RGB(name, datatype, union_type, \
                                                        r_bits, g_bits, b_bits)     \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC                       \
	name##_color2pixel(struct video_surface const *__restrict UNUSED(surface),      \
	                   video_color_t color) {                                       \
		union_type px;                                                              \
		px.r = color_getred##r_bits(color);                                         \
		px.g = color_getgreen##g_bits(color);                                       \
		px.b = color_getblue##b_bits(color);                                        \
		return px.data;                                                             \
	}                                                                               \
	PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC                       \
	name##_pixel2color(struct video_surface const *__restrict UNUSED(surface),      \
	                   video_pixel_t pixel) {                                       \
		union_type px;                                                              \
		px.data = (datatype)pixel;                                                  \
		return red##r_bits##_tocolor(px.r) |                                        \
		       green##g_bits##_tocolor(px.g) |                                      \
		       blue##b_bits##_tocolor(px.b) |                                       \
		       VIDEO_COLOR_ALPHA_MASK;                                              \
	}                                                                               \
	DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_CONST, name)



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

DEFINE_FORMAT_CONVERTER_RGB(rgb332, uint8_t, 3, 3, 2, (
	__HYBRID_BITFIELD8_T r : 3,
	__HYBRID_BITFIELD8_T g : 3,
	__HYBRID_BITFIELD8_T b : 2
));

DEFINE_FORMAT_CONVERTER_RGB(rgb323, uint8_t, 3, 2, 3, (
	__HYBRID_BITFIELD8_T r : 3,
	__HYBRID_BITFIELD8_T g : 2,
	__HYBRID_BITFIELD8_T b : 3
));

DEFINE_FORMAT_CONVERTER_RGB(rgb233, uint8_t, 2, 3, 3, (
	__HYBRID_BITFIELD8_T r : 2,
	__HYBRID_BITFIELD8_T g : 3,
	__HYBRID_BITFIELD8_T b : 3
));

DEFINE_FORMAT_CONVERTER_RGB(bgr332, uint8_t, 3, 3, 2, (
	__HYBRID_BITFIELD8_T b : 3,
	__HYBRID_BITFIELD8_T g : 3,
	__HYBRID_BITFIELD8_T r : 2
));

DEFINE_FORMAT_CONVERTER_RGB(bgr323, uint8_t, 3, 2, 3, (
	__HYBRID_BITFIELD8_T b : 3,
	__HYBRID_BITFIELD8_T g : 2,
	__HYBRID_BITFIELD8_T r : 3
));

DEFINE_FORMAT_CONVERTER_RGB(bgr233, uint8_t, 2, 3, 3, (
	__HYBRID_BITFIELD8_T b : 2,
	__HYBRID_BITFIELD8_T g : 3,
	__HYBRID_BITFIELD8_T r : 3
));

DEFINE_FORMAT_CONVERTER_RGBA(rgba2222, uint8_t, 2, 2, 2, 2, (
	__HYBRID_BITFIELD8_T r : 2,
	__HYBRID_BITFIELD8_T g : 2,
	__HYBRID_BITFIELD8_T b : 2,
	__HYBRID_BITFIELD8_T a : 2
));

DEFINE_FORMAT_CONVERTER_RGBX(rgbx2222, uint8_t, 2, 2, 2, (
	__HYBRID_BITFIELD8_T r : 2,
	__HYBRID_BITFIELD8_T g : 2,
	__HYBRID_BITFIELD8_T b : 2,
	__HYBRID_BITFIELD8_T x : 2
));

DEFINE_FORMAT_CONVERTER_RGBA(argb2222, uint8_t, 2, 2, 2, 2, (
	__HYBRID_BITFIELD8_T a : 2,
	__HYBRID_BITFIELD8_T r : 2,
	__HYBRID_BITFIELD8_T g : 2,
	__HYBRID_BITFIELD8_T b : 2
));

DEFINE_FORMAT_CONVERTER_RGBX(xrgb2222, uint8_t, 2, 2, 2, (
	__HYBRID_BITFIELD8_T x : 2,
	__HYBRID_BITFIELD8_T r : 2,
	__HYBRID_BITFIELD8_T g : 2,
	__HYBRID_BITFIELD8_T b : 2
));

DEFINE_FORMAT_CONVERTER_RGBA(bgra2222, uint8_t, 2, 2, 2, 2, (
	__HYBRID_BITFIELD8_T b : 2,
	__HYBRID_BITFIELD8_T g : 2,
	__HYBRID_BITFIELD8_T r : 2,
	__HYBRID_BITFIELD8_T a : 2
));

DEFINE_FORMAT_CONVERTER_RGBX(bgrx2222, uint8_t, 2, 2, 2, (
	__HYBRID_BITFIELD8_T b : 2,
	__HYBRID_BITFIELD8_T g : 2,
	__HYBRID_BITFIELD8_T r : 2,
	__HYBRID_BITFIELD8_T x : 2
));

DEFINE_FORMAT_CONVERTER_RGBA(abgr2222, uint8_t, 2, 2, 2, 2, (
	__HYBRID_BITFIELD8_T a : 2,
	__HYBRID_BITFIELD8_T b : 2,
	__HYBRID_BITFIELD8_T g : 2,
	__HYBRID_BITFIELD8_T r : 2
));

DEFINE_FORMAT_CONVERTER_RGBX(xbgr2222, uint8_t, 2, 2, 2, (
	__HYBRID_BITFIELD8_T x : 2,
	__HYBRID_BITFIELD8_T b : 2,
	__HYBRID_BITFIELD8_T g : 2,
	__HYBRID_BITFIELD8_T r : 2
));

#ifdef VIDEO_CODEC_X_TILE16
DEFINE_FORMAT_CONVERTER_RGB(rgb844, uint16_t, 8, 4, 4, (
	__HYBRID_BITFIELD16_T r : 8,
	__HYBRID_BITFIELD16_T g : 4,
	__HYBRID_BITFIELD16_T b : 4
));
#endif /* VIDEO_CODEC_X_TILE16 */




INTERN ATTR_PURE WUNUSED NONNULL((1)) video_color_t
(FCC pal_pixel2color)(struct video_surface const *__restrict surface,
                      video_pixel_t pixel) {
	struct video_palette const *pal = video_surface_getpalette(surface);
	return video_palette_pixel2color(pal, pixel);
}

INTERN ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t
(FCC pal_color2pixel)(struct video_surface const *__restrict surface,
                      video_color_t color) {
	struct video_palette const *pal = video_surface_getpalette(surface);

	/* If the surface has an object-palette, can do a fast pixel lookup */
	if likely(video_surface_hasobjpalette(surface))
		return video_palette_color2pixel(pal, color);

	/* Else: must do a slow (fallback) pixel calculation */
	return libvideo_palette_color2pixel_generic(pal,
	                                            video_codec_getpalcolors(video_surface_getcodec(surface)),
	                                            color);
}


#define _paletN_tocolor(v, n) (video_palette_pixel2color(video_surface_getpalette(surface), v) & ~VIDEO_COLOR_ALPHA_MASK)
#define palet1_tocolor(v)     (_paletN_tocolor(v, 1))
#define palet2_tocolor(v)     (_paletN_tocolor(v, 2))
#define palet3_tocolor(v)     (_paletN_tocolor(v, 3))
#define palet4_tocolor(v)     (_paletN_tocolor(v, 4))
#define palet7_tocolor(v)     (_paletN_tocolor(v, 7))
#define palet8_tocolor(v)     (_paletN_tocolor(v, 8))

#if 1 /* Assume that the palette isn't too large (if it is, we'll encode bad pixel data) */
#define color_getpaletN(v, mask) pal_color2pixel(surface, color)
#else
#define color_getpaletN(v, mask) (pal_color2pixel(surface, color) & (mask))
#endif
#define color_getpalet1(v) color_getpaletN(v, 1)
#define color_getpalet2(v) color_getpaletN(v, 3)
#define color_getpalet3(v) color_getpaletN(v, 7)
#define color_getpalet4(v) color_getpaletN(v, 0xf)
#define color_getpalet7(v) color_getpaletN(v, 0x7f)
#define color_getpalet8(v) color_getpaletN(v, 0xff)

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
ap11_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel) {
	return alpha1_tocolor((pixel) & 1) |
	       palet1_tocolor((pixel >> 1) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
ap11_color2pixel(struct video_surface const *__restrict surface, video_color_t color) {
	return ((video_pixel_t)color_getalpha1(color)) |
	       ((video_pixel_t)color_getpalet1(color) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
pa11_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel) {
	return palet1_tocolor((pixel) & 1) |
	       alpha1_tocolor((pixel >> 1) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
pa11_color2pixel(struct video_surface const *__restrict surface, video_color_t color) {
	return ((video_pixel_t)color_getpalet1(color)) |
	       ((video_pixel_t)color_getalpha1(color) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
ap22_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel) {
	return alpha2_tocolor((pixel) & 3) |
	       palet2_tocolor((pixel >> 2) & 3);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
ap22_color2pixel(struct video_surface const *__restrict surface, video_color_t color) {
	return ((video_pixel_t)color_getalpha2(color)) |
	       ((video_pixel_t)color_getpalet2(color) << 2);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
pa22_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel) {
	return palet2_tocolor((pixel) & 3) |
	       alpha2_tocolor((pixel >> 2) & 3);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
pa22_color2pixel(struct video_surface const *__restrict surface, video_color_t color) {
	return ((video_pixel_t)color_getpalet2(color)) |
	       ((video_pixel_t)color_getalpha2(color) << 2);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
ap13_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel) {
	return alpha1_tocolor((pixel) & 1) |
	       palet3_tocolor((pixel >> 1) & 7);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
ap13_color2pixel(struct video_surface const *__restrict surface, video_color_t color) {
	return ((video_pixel_t)color_getalpha1(color)) |
	       ((video_pixel_t)color_getpalet3(color) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
pa31_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel) {
	return palet3_tocolor((pixel) & 7) |
	       alpha1_tocolor((pixel >> 3) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
pa31_color2pixel(struct video_surface const *__restrict surface, video_color_t color) {
	return ((video_pixel_t)color_getpalet3(color)) |
	       ((video_pixel_t)color_getalpha1(color) << 3);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
ap44_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel) {
	return alpha4_tocolor((pixel) & 0xf) |
	       palet4_tocolor((pixel >> 4) & 0xf);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
ap44_color2pixel(struct video_surface const *__restrict surface, video_color_t color) {
	return ((video_pixel_t)color_getalpha4(color)) |
	       ((video_pixel_t)color_getpalet4(color) << 4);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
pa44_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel) {
	return palet4_tocolor((pixel) & 0xf) |
	       alpha4_tocolor((pixel >> 4) & 0xf);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
pa44_color2pixel(struct video_surface const *__restrict surface, video_color_t color) {
	return ((video_pixel_t)color_getpalet4(color)) |
	       ((video_pixel_t)color_getalpha4(color) << 4);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
ap17_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel) {
	return alpha1_tocolor((pixel) & 1) |
	       palet7_tocolor((pixel >> 1) & 127);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
ap17_color2pixel(struct video_surface const *__restrict surface, video_color_t color) {
	return ((video_pixel_t)color_getalpha1(color)) |
	       ((video_pixel_t)color_getpalet7(color) << 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
pa71_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel) {
	return palet7_tocolor((pixel) & 127) |
	       alpha1_tocolor((pixel >> 7) & 1);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
pa71_color2pixel(struct video_surface const *__restrict surface, video_color_t color) {
	return ((video_pixel_t)color_getpalet7(color)) |
	       ((video_pixel_t)color_getalpha1_shl7(color));
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
ap88_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel) {
	return alpha8_tocolor((pixel) & 0xff) |
	       palet8_tocolor((pixel >> 8) & 0xff);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
ap88_color2pixel(struct video_surface const *__restrict surface, video_color_t color) {
	return ((video_pixel_t)color_getalpha8(color)) |
	       ((video_pixel_t)color_getpalet8(color) << 8);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_color_t FCC
pa88_pixel2color(struct video_surface const *__restrict surface, video_pixel_t pixel) {
	return palet8_tocolor((pixel) & 0xff) |
	       alpha8_tocolor((pixel >> 8) & 0xff);
}

PRIVATE ATTR_CONST WUNUSED NONNULL((1)) video_pixel_t FCC
pa88_color2pixel(struct video_surface const *__restrict surface, video_color_t color) {
	return ((video_pixel_t)color_getpalet8(color)) |
	       ((video_pixel_t)color_getalpha8(color) << 8);
}
#undef _paletN_tocolor
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


DEFINE_PIXEL64_WRAPPERS(INTERN ATTR_PURE, pal)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, ap11)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, pa11)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, ap22)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, pa22)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, ap13)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, pa31)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, ap44)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, pa44)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, ap17)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, pa71)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, ap88)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, pa88)




INTERN ATTR_OUT(3) void FCC
buffer32_requirements(video_dim_t size_x, video_dim_t size_y,
                      struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = size_x * 4;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

INTERN ATTR_OUT(3) void FCC
buffer24_requirements(video_dim_t size_x, video_dim_t size_y,
                      struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = size_x * 3;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

INTERN ATTR_OUT(3) void FCC
buffer16_requirements(video_dim_t size_x, video_dim_t size_y,
                      struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = size_x * 2;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

INTERN ATTR_OUT(3) void FCC
buffer8_requirements(video_dim_t size_x, video_dim_t size_y,
                     struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = size_x;
	result->vbs_bufsize = size_y * size_x;
}

INTERN ATTR_OUT(3) void FCC
buffer4_requirements(video_dim_t size_x, video_dim_t size_y,
                     struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = (size_x + 1) / 2;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

INTERN ATTR_OUT(3) void FCC
buffer2_requirements(video_dim_t size_x, video_dim_t size_y,
                     struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = (size_x + 3) / 4;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

INTERN ATTR_OUT(3) void FCC
buffer1_requirements(video_dim_t size_x, video_dim_t size_y,
                     struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = (size_x + 7) / 8;
	result->vbs_bufsize = size_y * result->vbs_stride;
}


/* Lookup the interface for a given codec, or return NULL if the codec isn't supported.
 * Don't declare as  ATTR_CONST; in  PIC-mode, needs  to do  one-time-init of  globals! */
INTERN /*ATTR_CONST*/ WUNUSED struct video_codec *FCC
libvideo_codec_lookup(video_codec_t codec) {
#define CASE_CODEC_AL1(codec, specs, rambuffer_requirements,        \
                       getpixel, setpixel, rectcopy, rectmove,      \
                       linecopy, linefill, vertfill, rectfill,      \
                       pixel2color, color2pixel, initconverter)     \
	case codec: {                                                   \
		_DEFINE_CODEC_AL1(_codec_##codec, codec,                    \
		                  specs, rambuffer_requirements,            \
		                  getpixel, setpixel, rectcopy, rectmove,   \
		                  linecopy, linefill, vertfill, rectfill,   \
		                  pixel2color, color2pixel, initconverter); \
		result = &_codec_##codec;                                   \
	}	break
#define CASE_CODEC_ALn(codec, specs,                                \
                       align, rambuffer_requirements,               \
                       getpixel, setpixel, rectcopy, rectmove,      \
                       linecopy, linefill, vertfill, rectfill,      \
                       unaligned_getpixel, unaligned_setpixel,      \
                       unaligned_rectcopy, unaligned_rectmove,      \
                       unaligned_linecopy, unaligned_linefill,      \
                       unaligned_vertfill, unaligned_rectfill,      \
                       pixel2color, color2pixel, initconverter)     \
	case codec: {                                                   \
		_DEFINE_CODEC_ALX(_codec_##codec, codec, specs,             \
		                  align, rambuffer_requirements,            \
		                  getpixel, setpixel, rectcopy, rectmove,   \
		                  linecopy, linefill, vertfill, rectfill,   \
		                  unaligned_getpixel, unaligned_setpixel,   \
		                  unaligned_rectcopy, unaligned_rectmove,   \
		                  unaligned_linecopy, unaligned_linefill,   \
		                  unaligned_vertfill, unaligned_rectfill,   \
		                  pixel2color, color2pixel, initconverter); \
		result = &_codec_##codec;                                   \
	}	break


	struct video_codec *result;
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
	               getpixel1_lsb, setpixel1_lsb,
	               rectcopy1_lsb, rectmove1_lsb, linecopy1_lsb,
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
	               getpixel1_msb, setpixel1_msb,
	               rectcopy1_msb, rectmove1_msb, linecopy1_msb,
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
	               getpixel2_lsb, setpixel2_lsb,
	               rectcopy2_lsb, rectmove2_lsb, linecopy2_lsb,
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
	               getpixel2_msb, setpixel2_msb,
	               rectcopy2_msb, rectmove2_msb, linecopy2_msb,
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
	               getpixel4_lsb, setpixel4_lsb,
	               rectcopy4_lsb, rectmove4_lsb, linecopy4_lsb,
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
	               getpixel4_msb, setpixel4_msb,
	               rectcopy4_msb, rectmove4_msb, linecopy4_msb,
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
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
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
	               getpixel2_msb, setpixel2_msb,
	               rectcopy2_msb, rectmove2_msb, linecopy2_msb,
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
	               getpixel2_lsb, setpixel2_lsb,
	               rectcopy2_lsb, rectmove2_lsb, linecopy2_lsb,
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
	               getpixel2_msb, setpixel2_msb,
	               rectcopy2_msb, rectmove2_msb, linecopy2_msb,
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
	               getpixel2_lsb, setpixel2_lsb,
	               rectcopy2_lsb, rectmove2_lsb, linecopy2_lsb,
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
	               getpixel4_lsb, setpixel4_lsb,
	               rectcopy4_lsb, rectmove4_lsb, linecopy4_lsb,
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
	               getpixel4_msb, setpixel4_msb,
	               rectcopy4_msb, rectmove4_msb, linecopy4_msb,
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
	               getpixel4_msb, setpixel4_msb,
	               rectcopy4_msb, rectmove4_msb, linecopy4_msb,
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
	               getpixel4_lsb, setpixel4_lsb,
	               rectcopy4_lsb, rectmove4_lsb, linecopy4_lsb,
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
	               getpixel4_msb, setpixel4_msb,
	               rectcopy4_msb, rectmove4_msb, linecopy4_msb,
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
	               getpixel4_lsb, setpixel4_lsb,
	               rectcopy4_lsb, rectmove4_lsb, linecopy4_lsb,
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
	               getpixel4_msb, setpixel4_msb,
	               rectcopy4_msb, rectmove4_msb, linecopy4_msb,
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
	               getpixel4_lsb, setpixel4_lsb,
	               rectcopy4_lsb, rectmove4_lsb, linecopy4_lsb,
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
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
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
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
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
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
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
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               al88_pixel2color, al88_color2pixel, initconv_from_la);

	CASE_CODEC_AL1(VIDEO_CODEC_A1_LSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 1,
	                /* vcs_cbits */ 1,
	                /* vcs_rmask */ 0,
	                /* vcs_gmask */ 0,
	                /* vcs_bmask */ 0,
	                /* vcs_amask */ 0x1),
	               buffer1_requirements,
	               getpixel1_lsb, setpixel1_lsb,
	               rectcopy1_lsb, rectmove1_lsb, linecopy1_lsb,
	               linefill1_lsb, vertfill1_lsb, rectfill1_lsb,
	               a1_pixel2color, a1_color2pixel, initconv_from_a);

	CASE_CODEC_AL1(VIDEO_CODEC_A1_MSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 1,
	                /* vcs_cbits */ 1,
	                /* vcs_rmask */ 0,
	                /* vcs_gmask */ 0,
	                /* vcs_bmask */ 0,
	                /* vcs_amask */ 0x1),
	               buffer1_requirements,
	               getpixel1_msb, setpixel1_msb,
	               rectcopy1_msb, rectmove1_msb, linecopy1_msb,
	               linefill1_msb, vertfill1_msb, rectfill1_msb,
	               a1_pixel2color, a1_color2pixel, initconv_from_a);

	CASE_CODEC_AL1(VIDEO_CODEC_A2_LSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0,
	                /* vcs_gmask */ 0,
	                /* vcs_bmask */ 0,
	                /* vcs_amask */ 0x3),
	               buffer2_requirements,
	               getpixel2_lsb, setpixel2_lsb,
	               rectcopy2_lsb, rectmove2_lsb, linecopy2_lsb,
	               linefill2_lsb, vertfill2_lsb, rectfill2_lsb,
	               a2_pixel2color, a2_color2pixel, initconv_from_a);

	CASE_CODEC_AL1(VIDEO_CODEC_A2_MSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 2,
	                /* vcs_cbits */ 2,
	                /* vcs_rmask */ 0,
	                /* vcs_gmask */ 0,
	                /* vcs_bmask */ 0,
	                /* vcs_amask */ 0x3),
	               buffer2_requirements,
	               getpixel2_msb, setpixel2_msb,
	               rectcopy2_msb, rectmove2_msb, linecopy2_msb,
	               linefill2_msb, vertfill2_msb, rectfill2_msb,
	               a2_pixel2color, a2_color2pixel, initconv_from_a);

	CASE_CODEC_AL1(VIDEO_CODEC_A4_LSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_LSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0,
	                /* vcs_gmask */ 0,
	                /* vcs_bmask */ 0,
	                /* vcs_amask */ 0xf),
	               buffer4_requirements,
	               getpixel4_lsb, setpixel4_lsb,
	               rectcopy4_lsb, rectmove4_lsb, linecopy4_lsb,
	               linefill4_lsb, vertfill4_lsb, rectfill4_lsb,
	               a4_pixel2color, a4_color2pixel, initconv_from_a);

	CASE_CODEC_AL1(VIDEO_CODEC_A4_MSB,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_MSB,
	                /* vcs_bpp   */ 4,
	                /* vcs_cbits */ 4,
	                /* vcs_rmask */ 0,
	                /* vcs_gmask */ 0,
	                /* vcs_bmask */ 0,
	                /* vcs_amask */ 0xf),
	               buffer4_requirements,
	               getpixel4_msb, setpixel4_msb,
	               rectcopy4_msb, rectmove4_msb, linecopy4_msb,
	               linefill4_msb, vertfill4_msb, rectfill4_msb,
	               a4_pixel2color, a4_color2pixel, initconv_from_a);

	CASE_CODEC_AL1(VIDEO_CODEC_A8,
	               (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_INTERP8888,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0,
	                /* vcs_gmask */ 0,
	                /* vcs_bmask */ 0,
	                /* vcs_amask */ 0xff),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               a8_pixel2color, a8_color2pixel, initconv_from_a);

#define VIDEO_CODEC_A1_MSB   0x101a /* 1-bit-per-pixel, alpha-mask (rgb=0), left->right pixels are encoded in a byte as "0b01234567" (e.g. x=1 is defined by "byte & 0x40") */
#define VIDEO_CODEC_A1_LSB   0x101b /* 1-bit-per-pixel, alpha-mask (rgb=0), left->right pixels are encoded in a byte as "0b76543210" (e.g. x=1 is defined by "byte & 0x02") */
#define VIDEO_CODEC_A2_MSB   0x101c /* 2-bit-per-pixel, 4-level alpha-mask (0=transparent; 3=opaque; rgb=0), left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_A2_LSB   0x101d /* 2-bit-per-pixel, 4-level alpha-mask (0=transparent; 3=opaque; rgb=0), left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_A4_MSB   0x101e /* 4-bit-per-pixel, 16-level alpha-mask (0=transparent; 15=opaque; rgb=0), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_A4_LSB   0x101f /* 4-bit-per-pixel, 16-level alpha-mask (0=transparent; 15=opaque; rgb=0), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_A8       0x1020 /* 1-byte-per-pixel, 256-level alpha-mask (0=transparent; 255=opaque; rgb=0) */





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
	               getpixel32, setpixel32,
	               rectcopy32, rectmove32, linecopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32,
	               unaligned_rectcopy32, unaligned_rectmove32, unaligned_linecopy32,
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
	               getpixel32, setpixel32,
	               rectcopy32, rectmove32, linecopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32,
	               unaligned_rectcopy32, unaligned_rectmove32, unaligned_linecopy32,
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
	               getpixel32, setpixel32,
	               rectcopy32, rectmove32, linecopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32,
	               unaligned_rectcopy32, unaligned_rectmove32, unaligned_linecopy32,
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
	               getpixel32, setpixel32,
	               rectcopy32, rectmove32, linecopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32,
	               unaligned_rectcopy32, unaligned_rectmove32, unaligned_linecopy32,
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
	               getpixel32, setpixel32,
	               rectcopy32, rectmove32, linecopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32,
	               unaligned_rectcopy32, unaligned_rectmove32, unaligned_linecopy32,
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
	               getpixel32, setpixel32,
	               rectcopy32, rectmove32, linecopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32,
	               unaligned_rectcopy32, unaligned_rectmove32, unaligned_linecopy32,
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
	               getpixel32, setpixel32,
	               rectcopy32, rectmove32, linecopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32,
	               unaligned_rectcopy32, unaligned_rectmove32, unaligned_linecopy32,
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
	               getpixel32, setpixel32,
	               rectcopy32, rectmove32, linecopy32,
	               linefill32, vertfill32, rectfill32,
	               unaligned_getpixel32, unaligned_setpixel32,
	               unaligned_rectcopy32, unaligned_rectmove32, unaligned_linecopy32,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               bgr565_pixel2color, bgr565_color2pixel, initconv_from_rgb);

	CASE_CODEC_AL1(VIDEO_CODEC_RGB332,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0xe0,
	                /* vcs_gmask */ 0x1c,
	                /* vcs_bmask */ 0x03,
	                /* vcs_amask */ 0),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               rgb332_pixel2color, rgb332_color2pixel, initconv_from_rgb);

	CASE_CODEC_AL1(VIDEO_CODEC_RGB323,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0xe0,
	                /* vcs_gmask */ 0x18,
	                /* vcs_bmask */ 0x07,
	                /* vcs_amask */ 0),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               rgb323_pixel2color, rgb323_color2pixel, initconv_from_rgb);

	CASE_CODEC_AL1(VIDEO_CODEC_RGB233,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0xc0,
	                /* vcs_gmask */ 0x38,
	                /* vcs_bmask */ 0x07,
	                /* vcs_amask */ 0),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               rgb233_pixel2color, rgb233_color2pixel, initconv_from_rgb);

	CASE_CODEC_AL1(VIDEO_CODEC_BGR332,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0x03,
	                /* vcs_gmask */ 0x1c,
	                /* vcs_bmask */ 0xe0,
	                /* vcs_amask */ 0),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               bgr332_pixel2color, bgr332_color2pixel, initconv_from_rgb);

	CASE_CODEC_AL1(VIDEO_CODEC_BGR323,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0x07,
	                /* vcs_gmask */ 0x18,
	                /* vcs_bmask */ 0xe0,
	                /* vcs_amask */ 0),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               bgr323_pixel2color, bgr323_color2pixel, initconv_from_rgb);

	CASE_CODEC_AL1(VIDEO_CODEC_BGR233,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0x07,
	                /* vcs_gmask */ 0x38,
	                /* vcs_bmask */ 0xc0,
	                /* vcs_amask */ 0),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               bgr233_pixel2color, bgr233_color2pixel, initconv_from_rgb);

	CASE_CODEC_AL1(VIDEO_CODEC_RGBA2222,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0xc0,
	                /* vcs_gmask */ 0x30,
	                /* vcs_bmask */ 0x0c,
	                /* vcs_amask */ 0x03),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               rgba2222_pixel2color, rgba2222_color2pixel, initconv_from_rgba);

	CASE_CODEC_AL1(VIDEO_CODEC_RGBX2222,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 6,
	                /* vcs_rmask */ 0xc0,
	                /* vcs_gmask */ 0x30,
	                /* vcs_bmask */ 0x0c,
	                /* vcs_amask */ 0),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               rgbx2222_pixel2color, rgbx2222_color2pixel, initconv_from_rgb);

	CASE_CODEC_AL1(VIDEO_CODEC_ARGB2222,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0x30,
	                /* vcs_gmask */ 0x0c,
	                /* vcs_bmask */ 0x03,
	                /* vcs_amask */ 0xc0),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               argb2222_pixel2color, argb2222_color2pixel, initconv_from_rgba);

	CASE_CODEC_AL1(VIDEO_CODEC_XRGB2222,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 6,
	                /* vcs_rmask */ 0x30,
	                /* vcs_gmask */ 0x0c,
	                /* vcs_bmask */ 0x03,
	                /* vcs_amask */ 0),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               xrgb2222_pixel2color, xrgb2222_color2pixel, initconv_from_rgb);

	CASE_CODEC_AL1(VIDEO_CODEC_BGRA2222,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0x0c,
	                /* vcs_gmask */ 0x30,
	                /* vcs_bmask */ 0xc0,
	                /* vcs_amask */ 0x03),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               bgra2222_pixel2color, bgra2222_color2pixel, initconv_from_rgba);

	CASE_CODEC_AL1(VIDEO_CODEC_BGRX2222,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 6,
	                /* vcs_rmask */ 0x0c,
	                /* vcs_gmask */ 0x30,
	                /* vcs_bmask */ 0xc0,
	                /* vcs_amask */ 0),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               bgrx2222_pixel2color, bgrx2222_color2pixel, initconv_from_rgb);

	CASE_CODEC_AL1(VIDEO_CODEC_ABGR2222,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 8,
	                /* vcs_rmask */ 0x03,
	                /* vcs_gmask */ 0x0c,
	                /* vcs_bmask */ 0x30,
	                /* vcs_amask */ 0xc0),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               abgr2222_pixel2color, abgr2222_color2pixel, initconv_from_rgba);

	CASE_CODEC_AL1(VIDEO_CODEC_XBGR2222,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 8,
	                /* vcs_cbits */ 6,
	                /* vcs_rmask */ 0x03,
	                /* vcs_gmask */ 0x0c,
	                /* vcs_bmask */ 0x30,
	                /* vcs_amask */ 0),
	               buffer8_requirements,
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
	               linefill8, vertfill8, rectfill8,
	               xbgr2222_pixel2color, xbgr2222_color2pixel, initconv_from_rgb);


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
	               getpixel24, setpixel24,
	               rectcopy24, rectmove24, linecopy24,
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
	               getpixel24, setpixel24,
	               rectcopy24, rectmove24, linecopy24,
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
	               getpixel1_lsb, setpixel1_lsb,
	               rectcopy1_lsb, rectmove1_lsb, linecopy1_lsb,
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
	               getpixel1_msb, setpixel1_msb,
	               rectcopy1_msb, rectmove1_msb, linecopy1_msb,
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
	               getpixel2_lsb, setpixel2_lsb,
	               rectcopy2_lsb, rectmove2_lsb, linecopy2_lsb,
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
	               getpixel2_msb, setpixel2_msb,
	               rectcopy2_msb, rectmove2_msb, linecopy2_msb,
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
	               getpixel4_lsb, setpixel4_lsb,
	               rectcopy4_lsb, rectmove4_lsb, linecopy4_lsb,
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
	               getpixel4_msb, setpixel4_msb,
	               rectcopy4_msb, rectmove4_msb, linecopy4_msb,
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
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
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
	               getpixel2_msb, setpixel2_msb,
	               rectcopy2_msb, rectmove2_msb, linecopy2_msb,
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
	               getpixel2_lsb, setpixel2_lsb,
	               rectcopy2_lsb, rectmove2_lsb, linecopy2_lsb,
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
	               getpixel2_msb, setpixel2_msb,
	               rectcopy2_msb, rectmove2_msb, linecopy2_msb,
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
	               getpixel2_lsb, setpixel2_lsb,
	               rectcopy2_lsb, rectmove2_lsb, linecopy2_lsb,
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
	               getpixel4_lsb, setpixel4_lsb,
	               rectcopy4_lsb, rectmove4_lsb, linecopy4_lsb,
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
	               getpixel4_msb, setpixel4_msb,
	               rectcopy4_msb, rectmove4_msb, linecopy4_msb,
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
	               getpixel4_msb, setpixel4_msb,
	               rectcopy4_msb, rectmove4_msb, linecopy4_msb,
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
	               getpixel4_lsb, setpixel4_lsb,
	               rectcopy4_lsb, rectmove4_lsb, linecopy4_lsb,
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
	               getpixel4_msb, setpixel4_msb,
	               rectcopy4_msb, rectmove4_msb, linecopy4_msb,
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
	               getpixel4_lsb, setpixel4_lsb,
	               rectcopy4_lsb, rectmove4_lsb, linecopy4_lsb,
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
	               getpixel4_msb, setpixel4_msb,
	               rectcopy4_msb, rectmove4_msb, linecopy4_msb,
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
	               getpixel4_lsb, setpixel4_lsb,
	               rectcopy4_lsb, rectmove4_lsb, linecopy4_lsb,
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
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
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
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
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
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
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
	               getpixel8, setpixel8,
	               rectcopy8, rectmove8, linecopy8,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
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
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               ap88_pixel2color, ap88_color2pixel, initconv_from_pa);

#ifdef VIDEO_CODEC_X_TILE16
	CASE_CODEC_ALn(VIDEO_CODEC_X_TILE16,
	               (VIDEO_CODEC_FLAG_NORMAL,
	                /* vcs_bpp   */ 16,
	                /* vcs_cbits */ 16,
	                /* vcs_rmask */ MASK2_LE(0x00ff),
	                /* vcs_gmask */ MASK2_LE(0x0f00),
	                /* vcs_bmask */ MASK2_LE(0xf000),
	                /* vcs_amask */ 0),
	               2, buffer16_requirements,
	               getpixel16, setpixel16,
	               rectcopy16, rectmove16, linecopy16,
	               linefill16, vertfill16, rectfill16,
	               unaligned_getpixel16, unaligned_setpixel16,
	               unaligned_rectcopy16, unaligned_rectmove16, unaligned_linecopy16,
	               unaligned_linefill16, unaligned_vertfill16, unaligned_rectfill16,
	               rgb844_pixel2color, rgb844_color2pixel, initconv_from_rgb);
#endif /* VIDEO_CODEC_X_TILE16 */

	default:
		result = libvideo_codec_lookup_extra(codec);
		break;
	}
	return result;
#undef CASE_CODEC_ALn
#undef CASE_CODEC_AL1
#undef _DEFINE_CODEC_ALX
#undef _DEFINE_CODEC_AL1
}


#define video_surface_getccodec(self) \
	((struct video_codec_custom const *)video_surface_getcodec(self))


PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
pext_pal_pixel2color(struct video_surface const *__restrict surface,
                     video_pixel_t pixel) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_pixel_t mask = codec->vc_specs.vcs_rmask;
	video_pixel_t pixl = PEXT(pixel, mask);
	return pal_pixel2color(surface, pixl);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
pdep_pal_color2pixel(struct video_surface const *__restrict surface,
                     video_color_t color) {
	video_pixel_t pixl = pal_color2pixel(surface, color);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_pixel_t mask = codec->vc_specs.vcs_rmask;
	return PDEP(pixl, mask);
}

LOCAL ATTR_CONST video_channel_t FCC
pext_channel(video_pixel_t pixel,
             video_pixel_t mask,
             shift_t miss_bits) {
	video_channel_t result = PEXT(pixel, mask);
	return fill_missing_bits(result, miss_bits);
}

LOCAL ATTR_CONST video_pixel_t FCC
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

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
pext_pal_pixel2color__withalpha(struct video_surface const *__restrict surface,
                                video_pixel_t pixel) {
	video_color_t result = pext_pal_pixel2color(surface, pixel);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
pal_pixel2color__withalpha(struct video_surface const *__restrict surface,
                           video_pixel_t pixel) {
	video_color_t result = pal_pixel2color(surface, pixel);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
pal_color2pixel__withalpha(struct video_surface const *__restrict surface,
                           video_color_t color) {
	video_pixel_t result = pal_color2pixel(surface, color);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
pdep_pal_color2pixel__withalpha(struct video_surface const *__restrict surface,
                                video_color_t color) {
	video_pixel_t result = pdep_pal_color2pixel(surface, color);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}



PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
pext_gray4_pixel2color(struct video_surface const *__restrict surface,
                       video_pixel_t pixel) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_pixel_t mask = codec->vc_specs.vcs_rmask;
	video_pixel_t pixl = PEXT(pixel, mask);
	return l2_pixel2color(surface, pixl);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
pdep_gray4_color2pixel(struct video_surface const *__restrict surface,
                       video_color_t color) {
	video_pixel_t pixl = l2_color2pixel(surface, color);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_pixel_t mask = codec->vc_specs.vcs_rmask;
	return PDEP(pixl, mask);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
pext_gray16_pixel2color(struct video_surface const *__restrict surface,
                        video_pixel_t pixel) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_pixel_t mask = codec->vc_specs.vcs_rmask;
	video_pixel_t pixl = PEXT(pixel, mask);
	return l4_pixel2color(surface, pixl);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
pdep_gray16_color2pixel(struct video_surface const *__restrict surface,
                        video_color_t color) {
	video_pixel_t pixl = l4_color2pixel(surface, color);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_pixel_t mask = codec->vc_specs.vcs_rmask;
	return PDEP(pixl, mask);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
pext_gray256_pixel2color(struct video_surface const *__restrict surface,
                         video_pixel_t pixel) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_pixel_t mask = codec->vc_specs.vcs_rmask;
	video_pixel_t pixl = PEXT(pixel, mask);
	return l8_pixel2color(surface, pixl);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
pdep_gray256_color2pixel(struct video_surface const *__restrict surface,
                         video_color_t color) {
	video_pixel_t pixl = l8_color2pixel(surface, color);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_pixel_t mask = codec->vc_specs.vcs_rmask;
	return PDEP(pixl, mask);
}



PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
gray2_pixel2color__withalpha(struct video_surface const *__restrict surface,
                             video_pixel_t pixel) {
	video_color_t result = l1_pixel2color(surface, pixel);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
gray2_color2pixel__withalpha(struct video_surface const *__restrict surface,
                             video_color_t color) {
	video_pixel_t result = l1_color2pixel(surface, color);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
gray4_pixel2color__withalpha(struct video_surface const *__restrict surface,
                             video_pixel_t pixel) {
	video_color_t result = l2_pixel2color(surface, pixel);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
pext_gray4_pixel2color__withalpha(struct video_surface const *__restrict surface,
                                  video_pixel_t pixel) {
	video_color_t result = pext_gray4_pixel2color(surface, pixel);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
gray4_color2pixel__withalpha(struct video_surface const *__restrict surface,
                             video_color_t color) {
	video_pixel_t result = l2_color2pixel(surface, color);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
pdep_gray4_color2pixel__withalpha(struct video_surface const *__restrict surface,
                                  video_color_t color) {
	video_pixel_t result = pdep_gray4_color2pixel(surface, color);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
gray16_pixel2color__withalpha(struct video_surface const *__restrict surface,
                              video_pixel_t pixel) {
	video_color_t result = l4_pixel2color(surface, pixel);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
pext_gray16_pixel2color__withalpha(struct video_surface const *__restrict surface,
                                   video_pixel_t pixel) {
	video_color_t result = pext_gray16_pixel2color(surface, pixel);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
gray16_color2pixel__withalpha(struct video_surface const *__restrict surface,
                              video_color_t color) {
	video_pixel_t result = l4_color2pixel(surface, color);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
pdep_gray16_color2pixel__withalpha(struct video_surface const *__restrict surface,
                                   video_color_t color) {
	video_pixel_t result = pdep_gray16_color2pixel(surface, color);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
gray256_pixel2color__withalpha(struct video_surface const *__restrict surface,
                               video_pixel_t pixel) {
	video_color_t result = l8_pixel2color(surface, pixel);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
pext_gray256_pixel2color__withalpha(struct video_surface const *__restrict surface,
                                    video_pixel_t pixel) {
	video_color_t result = pext_gray256_pixel2color(surface, pixel);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result &= ~VIDEO_COLOR_ALPHA_MASK;
	result |= pext_channel(pixel, codec->vcc_used_amask,
	                       codec->vcc_miss_abits)
	          << VIDEO_COLOR_ALPHA_SHIFT;
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
gray256_color2pixel__withalpha(struct video_surface const *__restrict surface,
                               video_color_t color) {
	video_pixel_t result = l8_color2pixel(surface, color);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
pdep_gray256_color2pixel__withalpha(struct video_surface const *__restrict surface,
                                    video_color_t color) {
	video_pixel_t result = pdep_gray256_color2pixel(surface, color);
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	result |= pdep_channel(VIDEO_COLOR_GET_ALPHA(color),
	                       codec->vcc_used_amask,
	                       codec->vcc_xtra_amask);
	return result;
}


PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
pext_rgba_pixel2color(struct video_surface const *__restrict surface,
                      video_pixel_t pixel) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_channel_t r = pext_channel(pixel, codec->vcc_used_rmask, codec->vcc_miss_rbits);
	video_channel_t g = pext_channel(pixel, codec->vcc_used_gmask, codec->vcc_miss_gbits);
	video_channel_t b = pext_channel(pixel, codec->vcc_used_bmask, codec->vcc_miss_bbits);
	video_channel_t a = pext_channel(pixel, codec->vcc_used_amask, codec->vcc_miss_abits);
	return VIDEO_COLOR_RGBA(r, g, b, a);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
pdep_rgba_color2pixel(struct video_surface const *__restrict surface,
                      video_color_t color) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_channel_t r = VIDEO_COLOR_GET_RED(color);
	video_channel_t g = VIDEO_COLOR_GET_GREEN(color);
	video_channel_t b = VIDEO_COLOR_GET_BLUE(color);
	video_channel_t a = VIDEO_COLOR_GET_ALPHA(color);
	return pdep_channel(r, codec->vcc_used_rmask, codec->vcc_xtra_rmask) |
	       pdep_channel(g, codec->vcc_used_gmask, codec->vcc_xtra_gmask) |
	       pdep_channel(b, codec->vcc_used_bmask, codec->vcc_xtra_bmask) |
	       pdep_channel(a, codec->vcc_used_amask, codec->vcc_xtra_amask);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
pext_rgb_pixel2color(struct video_surface const *__restrict surface,
                     video_pixel_t pixel) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_channel_t r = pext_channel(pixel, codec->vcc_used_rmask, codec->vcc_miss_rbits);
	video_channel_t g = pext_channel(pixel, codec->vcc_used_gmask, codec->vcc_miss_gbits);
	video_channel_t b = pext_channel(pixel, codec->vcc_used_bmask, codec->vcc_miss_bbits);
	return VIDEO_COLOR_RGB(r, g, b);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
pdep_rgb_color2pixel(struct video_surface const *__restrict surface,
                     video_color_t color) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
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
LOCAL ATTR_CONST video_channel_t FCC
shft_channel_decode(video_pixel_t pixel,
                    video_pixel_t mask,
                    shift_t shft,
                    shift_t miss_bits) {
	video_channel_t result = (pixel & mask) >> shft;
	return fill_missing_bits(result, miss_bits);
}

#ifdef HAVE_shft_channel_decode_nomiss
LOCAL ATTR_CONST video_channel_t FCC
shft_channel_decode_nomiss(video_pixel_t pixel,
                           video_pixel_t mask,
                           shift_t shft) {
	return (pixel & mask) >> shft;
}
#endif /* HAVE_shft_channel_decode_nomiss */

LOCAL ATTR_CONST video_pixel_t FCC
shft_channel_encode(video_channel_t chan,
                    shift_t shft,
                    shift_t miss_bits) {
	return (video_pixel_t)(chan >> miss_bits) << shft;
}


PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
shft_rgb_pixel2color(struct video_surface const *__restrict surface,
                     video_pixel_t pixel) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_channel_t r = shft_channel_decode(pixel, codec->vcc_used_rmask, codec->vcc_shft_rmask, codec->vcc_miss_rbits);
	video_channel_t g = shft_channel_decode(pixel, codec->vcc_used_gmask, codec->vcc_shft_gmask, codec->vcc_miss_gbits);
	video_channel_t b = shft_channel_decode(pixel, codec->vcc_used_bmask, codec->vcc_shft_bmask, codec->vcc_miss_bbits);
	return VIDEO_COLOR_RGB(r, g, b);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
shft_rgba_pixel2color(struct video_surface const *__restrict surface,
                      video_pixel_t pixel) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_channel_t r = shft_channel_decode(pixel, codec->vcc_used_rmask, codec->vcc_shft_rmask, codec->vcc_miss_rbits);
	video_channel_t g = shft_channel_decode(pixel, codec->vcc_used_gmask, codec->vcc_shft_gmask, codec->vcc_miss_gbits);
	video_channel_t b = shft_channel_decode(pixel, codec->vcc_used_bmask, codec->vcc_shft_bmask, codec->vcc_miss_bbits);
	video_channel_t a = shft_channel_decode(pixel, codec->vcc_used_amask, codec->vcc_shft_amask, codec->vcc_miss_abits);
	return VIDEO_COLOR_RGBA(r, g, b, a);
}

#ifdef HAVE_shft_channel_decode_nomiss
PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
shft_rgb_pixel2color_nomiss(struct video_surface const *__restrict surface,
                            video_pixel_t pixel) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_channel_t r = shft_channel_decode_nomiss(pixel, codec->vcc_used_rmask, codec->vcc_shft_rmask);
	video_channel_t g = shft_channel_decode_nomiss(pixel, codec->vcc_used_gmask, codec->vcc_shft_gmask);
	video_channel_t b = shft_channel_decode_nomiss(pixel, codec->vcc_used_bmask, codec->vcc_shft_bmask);
	return VIDEO_COLOR_RGB(r, g, b);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_color_t FCC
shft_rgba_pixel2color_nomiss(struct video_surface const *__restrict surface,
                             video_pixel_t pixel) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_channel_t r = shft_channel_decode_nomiss(pixel, codec->vcc_used_rmask, codec->vcc_shft_rmask);
	video_channel_t g = shft_channel_decode_nomiss(pixel, codec->vcc_used_gmask, codec->vcc_shft_gmask);
	video_channel_t b = shft_channel_decode_nomiss(pixel, codec->vcc_used_bmask, codec->vcc_shft_bmask);
	video_channel_t a = shft_channel_decode_nomiss(pixel, codec->vcc_used_amask, codec->vcc_shft_amask);
	return VIDEO_COLOR_RGBA(r, g, b, a);
}
#endif /* HAVE_shft_channel_decode_nomiss */

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
shft_rgb_color2pixel(struct video_surface const *__restrict surface,
                     video_color_t color) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
	video_channel_t r = VIDEO_COLOR_GET_RED(color);
	video_channel_t g = VIDEO_COLOR_GET_GREEN(color);
	video_channel_t b = VIDEO_COLOR_GET_BLUE(color);
	return shft_channel_encode(r, codec->vcc_shft_rmask, codec->vcc_miss_rbits) |
	       shft_channel_encode(g, codec->vcc_shft_gmask, codec->vcc_miss_gbits) |
	       shft_channel_encode(b, codec->vcc_shft_bmask, codec->vcc_miss_bbits);
}

PRIVATE ATTR_COLD ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t FCC
shft_rgba_color2pixel(struct video_surface const *__restrict surface,
                      video_color_t color) {
	struct video_codec_custom const *codec = video_surface_getccodec(surface);
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



DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, pext_pal_pixel2color, pext_pal_pixel2color64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, pdep_pal_color2pixel, pdep_pal_color2pixel64)
DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, pext_pal_pixel2color__withalpha, pext_pal_pixel2color__withalpha64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, pdep_pal_color2pixel__withalpha, pdep_pal_color2pixel__withalpha64)
DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, pal_pixel2color__withalpha, pal_pixel2color__withalpha64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, pal_color2pixel__withalpha, pal_color2pixel__withalpha64)

DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, pext_gray4_pixel2color, pext_gray4_pixel2color64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, pdep_gray4_color2pixel, pdep_gray4_color2pixel64)
DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, pext_gray16_pixel2color, pext_gray16_pixel2color64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, pdep_gray16_color2pixel, pdep_gray16_color2pixel64)
DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, pext_gray256_pixel2color, pext_gray256_pixel2color64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, pdep_gray256_color2pixel, pdep_gray256_color2pixel64)

DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, gray2_pixel2color__withalpha, gray2_pixel2color__withalpha64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, gray2_color2pixel__withalpha, gray2_color2pixel__withalpha64)
DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, gray4_pixel2color__withalpha, gray4_pixel2color__withalpha64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, gray4_color2pixel__withalpha, gray4_color2pixel__withalpha64)
DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, gray16_pixel2color__withalpha, gray16_pixel2color__withalpha64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, gray16_color2pixel__withalpha, gray16_color2pixel__withalpha64)
DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, gray256_pixel2color__withalpha, gray256_pixel2color__withalpha64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, gray256_color2pixel__withalpha, gray256_color2pixel__withalpha64)

DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, pext_gray4_pixel2color__withalpha, pext_gray4_pixel2color__withalpha64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, pdep_gray4_color2pixel__withalpha, pdep_gray4_color2pixel__withalpha64)
DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, pext_gray16_pixel2color__withalpha, pext_gray16_pixel2color__withalpha64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, pdep_gray16_color2pixel__withalpha, pdep_gray16_color2pixel__withalpha64)
DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, pext_gray256_pixel2color__withalpha, pext_gray256_pixel2color__withalpha64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, pdep_gray256_color2pixel__withalpha, pdep_gray256_color2pixel__withalpha64)

DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, pext_rgba_pixel2color, pext_rgba_pixel2color64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, pdep_rgba_color2pixel, pdep_rgba_color2pixel64)
DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, pext_rgb_pixel2color, pext_rgb_pixel2color64)
DEFINE_COLOR2PIXEL64_WRAPPER32(PRIVATE ATTR_PURE, pdep_rgb_color2pixel, pdep_rgb_color2pixel64)

#ifdef HAVE_shft_channel_decode
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, shft_rgb)
DEFINE_PIXEL64_WRAPPERS(PRIVATE ATTR_PURE, shft_rgba)
#ifdef HAVE_shft_channel_decode_nomiss
DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, shft_rgb_pixel2color_nomiss, shft_rgb_pixel2color_nomiss64)
DEFINE_PIXEL2COLOR64_WRAPPER32(PRIVATE ATTR_PURE, shft_rgba_pixel2color_nomiss, shft_rgba_pixel2color_nomiss64)
#endif /* HAVE_shft_channel_decode_nomiss */
#endif /* HAVE_shft_channel_decode */



LOCAL ATTR_COLD NONNULL((2, 3, 4, 5)) void FCC
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

PRIVATE ATTR_COLD WUNUSED struct video_codec const *FCC
builtin_codec_from_masks(video_pixel64_t rmask,
                         video_pixel64_t gmask,
                         video_pixel64_t bmask,
                         video_pixel64_t amask) {
	struct video_codec const *result;
	struct video_codec_specs specs;
	video_pixel64_t fullmask;
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
#ifndef CONFIG_LIBVIDEO_HAVE_PIXEL64
		specs.vcs_bpp = 32;
#else /* !CONFIG_LIBVIDEO_HAVE_PIXEL64 */
		if (fullmask <= UINT32_C(0xffffffff)) {
			specs.vcs_bpp = 32;
		} else {
			/* TODO: 5-byte, 6-byte, 7-byte codecs (XXX: Do those even exist?) */
			specs.vcs_bpp = 64;
		}
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
	}
	specs.vcs_cbits = specs.vcs_bpp;
	result = libvideo_codec_lookup_specs(&specs);
	if (!result) {
		if (specs.vcs_bpp == 24) {
			specs.vcs_bpp = 32; /* Try again for a 32-bit codec */
			result = libvideo_codec_lookup_specs(&specs);
		} else if (specs.vcs_bpp > 32 && specs.vcs_bpp < 64) {
			specs.vcs_bpp = 64; /* Try again for a 64-bit codec */
			result = libvideo_codec_lookup_specs(&specs);
		}
	}
	return result;
}

PRIVATE ATTR_COLD ATTR_CONST WUNUSED bool FCC
is_8bit_aligned(video_pixel64_t mask) {
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
INTERN ATTR_COLD NONNULL((1)) bool FCC
libvideo_codec_populate_custom(struct video_codec_custom *__restrict self,
                               bool populate_noalign) {
	self->vc_codec = VIDEO_CODEC_CUSTOM;
	self->vc_specs.vcs_pxsz = CEILDIV(self->vc_specs.vcs_bpp, NBBY);
	switch (self->vc_specs.vcs_bpp) {
#if defined(CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3) && defined(VIDEO_CODEC_HAVE__VC_SETPIXEL3_DUMMY)
#define INIT__vc_setpixel(self, f) (&rp3_##f, self->vc_setpixel = &f, self->_vc_setpixel3 = NULL)
#elif defined(CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3)
#define INIT__vc_setpixel(self, f) (self->vc_setpixel = &f, self->_vc_setpixel3 = &rp3_##f)
#else /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */
#define INIT__vc_setpixel(self, f) (self->vc_setpixel = &f)
#endif /* !CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */
	case 1:
		self->vc_align = 1;
		self->vc_rambuffer_requirements = &buffer1_requirements;
		if (VIDEO_CODEC_FLAG_ISLSB(self->vc_specs.vcs_flags)) {
			self->vc_getpixel = &getpixel1_lsb;
			INIT__vc_setpixel(self, setpixel1_lsb);
			self->vc_linefill = &linefill1_lsb;
			self->vc_vertfill = &vertfill1_lsb;
			self->vc_rectfill = &rectfill1_lsb;
			self->vc_rectcopy = &rectcopy1_lsb;
			self->vc_rectmove = &rectmove1_lsb;
			self->vc_linecopy = &linecopy1_lsb;
		} else {
			self->vc_getpixel = &getpixel1_msb;
			INIT__vc_setpixel(self, setpixel1_msb);
			self->vc_linefill = &linefill1_msb;
			self->vc_vertfill = &vertfill1_msb;
			self->vc_rectfill = &rectfill1_msb;
			self->vc_rectcopy = &rectcopy1_msb;
			self->vc_rectmove = &rectmove1_msb;
			self->vc_linecopy = &linecopy1_msb;
		}
		break;
	case 2:
		self->vc_align = 1;
		self->vc_rambuffer_requirements = &buffer2_requirements;
		if (VIDEO_CODEC_FLAG_ISLSB(self->vc_specs.vcs_flags)) {
			self->vc_getpixel = &getpixel2_lsb;
			INIT__vc_setpixel(self, setpixel2_lsb);
			self->vc_linefill = &linefill2_lsb;
			self->vc_vertfill = &vertfill2_lsb;
			self->vc_rectfill = &rectfill2_lsb;
			self->vc_rectcopy = &rectcopy2_lsb;
			self->vc_rectmove = &rectmove2_lsb;
			self->vc_linecopy = &linecopy2_lsb;
		} else {
			self->vc_getpixel = &getpixel2_msb;
			INIT__vc_setpixel(self, setpixel2_msb);
			self->vc_linefill = &linefill2_msb;
			self->vc_vertfill = &vertfill2_msb;
			self->vc_rectfill = &rectfill2_msb;
			self->vc_rectcopy = &rectcopy2_msb;
			self->vc_rectmove = &rectmove2_msb;
			self->vc_linecopy = &linecopy2_msb;
		}
		break;
	case 4:
		self->vc_align = 1;
		self->vc_rambuffer_requirements = &buffer4_requirements;
		if (VIDEO_CODEC_FLAG_ISLSB(self->vc_specs.vcs_flags)) {
			self->vc_getpixel = &getpixel4_lsb;
			INIT__vc_setpixel(self, setpixel4_lsb);
			self->vc_linefill = &linefill4_lsb;
			self->vc_vertfill = &vertfill4_lsb;
			self->vc_rectfill = &rectfill4_lsb;
			self->vc_rectcopy = &rectcopy4_lsb;
			self->vc_rectmove = &rectmove4_lsb;
			self->vc_linecopy = &linecopy4_lsb;
		} else {
			self->vc_getpixel = &getpixel4_msb;
			INIT__vc_setpixel(self, setpixel4_msb);
			self->vc_linefill = &linefill4_msb;
			self->vc_vertfill = &vertfill4_msb;
			self->vc_rectfill = &rectfill4_msb;
			self->vc_rectcopy = &rectcopy4_msb;
			self->vc_rectmove = &rectmove4_msb;
			self->vc_linecopy = &linecopy4_msb;
		}
		break;
	case 8:
		self->vc_align = 1;
		self->vc_rambuffer_requirements = &buffer8_requirements;
		self->vc_getpixel = &getpixel8;
		INIT__vc_setpixel(self, setpixel8);
		self->vc_linefill = &linefill8;
		self->vc_vertfill = &vertfill8;
		self->vc_rectfill = &rectfill8;
		self->vc_rectcopy = &rectcopy8;
		self->vc_rectmove = &rectmove8;
		self->vc_linecopy = &linecopy8;
		break;
	case 16:
		self->vc_align = 2;
		self->vc_rambuffer_requirements = &buffer16_requirements;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		if (populate_noalign) {
			self->vc_getpixel = &unaligned_getpixel16;
			INIT__vc_setpixel(self, unaligned_setpixel16);
			self->vc_linefill = &unaligned_linefill16;
			self->vc_vertfill = &unaligned_vertfill16;
			self->vc_rectfill = &unaligned_rectfill16;
			self->vc_rectcopy = &unaligned_rectcopy16;
			self->vc_rectmove = &unaligned_rectmove16;
			self->vc_linecopy = &unaligned_linecopy16;
		} else
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		{
			self->vc_getpixel = &getpixel16;
			INIT__vc_setpixel(self, setpixel16);
			self->vc_linefill = &linefill16;
			self->vc_vertfill = &vertfill16;
			self->vc_rectfill = &rectfill16;
			self->vc_rectcopy = &rectcopy16;
			self->vc_rectmove = &rectmove16;
			self->vc_linecopy = &linecopy16;
		}
		break;
	case 24:
		self->vc_align = 1;
		self->vc_rambuffer_requirements = &buffer24_requirements;
		self->vc_getpixel = &getpixel24;
		INIT__vc_setpixel(self, setpixel24);
		self->vc_linefill = &linefill24;
		self->vc_vertfill = &vertfill24;
		self->vc_rectfill = &rectfill24;
		self->vc_rectcopy = &rectcopy24;
		self->vc_rectmove = &rectmove24;
		self->vc_linecopy = &linecopy24;
		break;
	case 32:
		self->vc_align = 4;
		self->vc_rambuffer_requirements = &buffer32_requirements;
#ifndef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
		if (populate_noalign) {
			self->vc_getpixel = &unaligned_getpixel32;
			INIT__vc_setpixel(self, unaligned_setpixel32);
			self->vc_linefill = &unaligned_linefill32;
			self->vc_vertfill = &unaligned_vertfill32;
			self->vc_rectfill = &unaligned_rectfill32;
			self->vc_rectcopy = &unaligned_rectcopy32;
			self->vc_rectmove = &unaligned_rectmove32;
			self->vc_linecopy = &unaligned_linecopy32;
		} else
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
		{
			self->vc_getpixel = &getpixel32;
			INIT__vc_setpixel(self, setpixel32);
			self->vc_linefill = &linefill32;
			self->vc_vertfill = &vertfill32;
			self->vc_rectfill = &rectfill32;
			self->vc_rectcopy = &rectcopy32;
			self->vc_rectmove = &rectmove32;
			self->vc_linecopy = &linecopy32;
		}
		break;

	/* TODO: 40bpp, 48bpp, 56bpp, 64bpp */

	default:
		/* Impossible/Unsupported BPP */
		return false;
#undef INIT__vc_setpixel
	}

	/* Fix  broken color masks -- only the least significant "vcs_bpp" bits
	 * can ever be read/written from  pixes to underlying memory.  Anything
	 * above that is impossible to store, so we may as well mask those bits
	 * away since there would be no way to store them anyways. */
	{
		video_pixel64_t cmask;
		video_pixel64_t bpp_mask = ((video_pixel64_t)1 << self->vc_specs.vcs_bpp) - 1;
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

#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
		if (cmask > UINT32_C(0xffffffff)) {
			/* TODO: 64-bit codec */
			/* TODO: BPP > 32 */
			/* TODO: In this mode, the regular pixel2color  / color2pixel are just the  identity
			 *       function, since *actual* pixel values  can't be encoded. Instead, only  the
			 *       pixel2color64 / color2pixel64 function actually do anything, and the non-64
			 *       line/vert/rect-fill function have to do the actual pixel encoding...
			 * XXX: But that won't work for custom codecs since those operators don't take the
			 *      video_surface as argument, meaning there'd need to be 1 function for every
			 *      possible format, and we want to support arbitrary formats...
			 * FIXME: Figure out a way to compress/uncompress 32/64-bit pixels in this case.
			 *        It should be possible, since we know  that there will only be at  most
			 *        32 bits of color information,  and all *we* need  is a limited set  of
			 *        functions to expand those 32 bits  of color from video_pixel_t into  a
			 *        larger video_pixel64_t (at that point we won't even need to deal  with
			 *        reordering  bits,  since  that  can  still  happen  in  "color2pixel")
			 *        (hmm...  but now that I think about it, there might still be *way* too
			 *        many possible constellations of pixel expansion)
			 * Solution: The only real solution here is to have a set of upscaling functions
			 *           for operators like vc_linefill, and  when being given a codec  that
			 *           doesn't  support any of these, we need to dynamically generate code
			 *           that **does** support this.
			 */
			return false;
		}
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
	}


	/* Load effective color masks */
	video_codec_custom__init__usedmask((video_pixel_t)self->vc_specs.vcs_rmask,
	                                   &self->vcc_used_rmask, &self->vcc_xtra_rmask,
	                                   &self->vcc_miss_rbits, &self->vcc_shft_rmask);
	video_codec_custom__init__usedmask((video_pixel_t)self->vc_specs.vcs_gmask,
	                                   &self->vcc_used_gmask, &self->vcc_xtra_gmask,
	                                   &self->vcc_miss_gbits, &self->vcc_shft_gmask);
	video_codec_custom__init__usedmask((video_pixel_t)self->vc_specs.vcs_bmask,
	                                   &self->vcc_used_bmask, &self->vcc_xtra_bmask,
	                                   &self->vcc_miss_bbits, &self->vcc_shft_bmask);
	video_codec_custom__init__usedmask((video_pixel_t)self->vc_specs.vcs_amask,
	                                   &self->vcc_used_amask, &self->vcc_xtra_amask,
	                                   &self->vcc_miss_abits, &self->vcc_shft_amask);


	/* Check if the codec qualifies for INTERP8888 optimizations. */
	self->vc_specs.vcs_flags &= ~VIDEO_CODEC_FLAG_INTERP8888;
	if (!(self->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL) &&
	    is_8bit_aligned(self->vcc_used_rmask) && is_8bit_aligned(self->vcc_used_gmask) &&
	    is_8bit_aligned(self->vcc_used_bmask) && is_8bit_aligned(self->vcc_used_amask))
		self->vc_specs.vcs_flags |= VIDEO_CODEC_FLAG_INTERP8888;

	/* Select color <=> pixel conversion algorithm */
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
#define INIT__vc_pixel2color(v) (self->vc_pixel2color = v, self->vc_pixel2color64 = v##64)
#define INIT__vc_color2pixel(v) (self->vc_color2pixel = v, self->vc_color2pixel64 = v##64)
#else /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
#define INIT__vc_pixel2color(v) (self->vc_pixel2color = v)
#define INIT__vc_color2pixel(v) (self->vc_color2pixel = v)
#endif /* !CONFIG_LIBVIDEO_HAVE_PIXEL64 */
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
						video_pixel64_t cmask_after_alpha = cmask << alpha_bits;
						if ((self->vc_specs.vcs_rmask & cmask_after_alpha) == cmask_after_alpha) {
							/* Looks like a usable alpha codec */
#define AL(n_alpha, n_lum) ((n_alpha - 1) | ((n_lum - 1) << 3))
							switch (AL(alpha_bits, lumen_bits)) {
							case AL(1, 1):
								if (ispal) {
									INIT__vc_pixel2color(&ap11_pixel2color);
									INIT__vc_color2pixel(&ap11_color2pixel);
								} else {
									INIT__vc_pixel2color(&al11_pixel2color);
									INIT__vc_color2pixel(&al11_color2pixel);
								}
								goto got_p2c;
							case AL(2, 2):
								if (ispal) {
									INIT__vc_pixel2color(&ap22_pixel2color);
									INIT__vc_color2pixel(&ap22_color2pixel);
								} else {
									INIT__vc_pixel2color(&al22_pixel2color);
									INIT__vc_color2pixel(&al22_color2pixel);
								}
								goto got_p2c;
							case AL(1, 3):
								if (ispal) {
									INIT__vc_pixel2color(&ap13_pixel2color);
									INIT__vc_color2pixel(&ap13_color2pixel);
								} else {
									INIT__vc_pixel2color(&al13_pixel2color);
									INIT__vc_color2pixel(&al13_color2pixel);
								}
								goto got_p2c;
							case AL(4, 4):
								if (ispal) {
									INIT__vc_pixel2color(&ap44_pixel2color);
									INIT__vc_color2pixel(&ap44_color2pixel);
								} else {
									INIT__vc_pixel2color(&al44_pixel2color);
									INIT__vc_color2pixel(&al44_color2pixel);
								}
								goto got_p2c;
							case AL(1, 7):
								if (ispal) {
									INIT__vc_pixel2color(&ap17_pixel2color);
									INIT__vc_color2pixel(&ap17_color2pixel);
								} else {
									INIT__vc_pixel2color(&al17_pixel2color);
									INIT__vc_color2pixel(&al17_color2pixel);
								}
								goto got_p2c;
							case AL(8, 8):
								if (ispal) {
									INIT__vc_pixel2color(&ap88_pixel2color);
									INIT__vc_color2pixel(&ap88_color2pixel);
								} else {
									INIT__vc_pixel2color(&al88_pixel2color);
									INIT__vc_color2pixel(&al88_color2pixel);
								}
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
							if (ispal) {
								INIT__vc_pixel2color(&pa11_pixel2color);
								INIT__vc_color2pixel(&pa11_color2pixel);
							} else {
								INIT__vc_pixel2color(&la11_pixel2color);
								INIT__vc_color2pixel(&la11_color2pixel);
							}
							goto got_p2c;
						case LA(2, 2):
							if (ispal) {
								INIT__vc_pixel2color(&pa22_pixel2color);
								INIT__vc_color2pixel(&pa22_color2pixel);
							} else {
								INIT__vc_pixel2color(&la22_pixel2color);
								INIT__vc_color2pixel(&la22_color2pixel);
							}
							goto got_p2c;
						case LA(3, 1):
							if (ispal) {
								INIT__vc_pixel2color(&pa31_pixel2color);
								INIT__vc_color2pixel(&pa31_color2pixel);
							} else {
								INIT__vc_pixel2color(&la31_pixel2color);
								INIT__vc_color2pixel(&la31_color2pixel);
							}
							goto got_p2c;
						case LA(4, 4):
							if (ispal) {
								INIT__vc_pixel2color(&pa44_pixel2color);
								INIT__vc_color2pixel(&pa44_color2pixel);
							} else {
								INIT__vc_pixel2color(&la44_pixel2color);
								INIT__vc_color2pixel(&la44_color2pixel);
							}
							goto got_p2c;
						case LA(7, 1):
							if (ispal) {
								INIT__vc_pixel2color(&pa71_pixel2color);
								INIT__vc_color2pixel(&pa71_color2pixel);
							} else {
								INIT__vc_pixel2color(&la71_pixel2color);
								INIT__vc_color2pixel(&la71_color2pixel);
							}
							goto got_p2c;
						case LA(8, 8):
							if (ispal) {
								INIT__vc_pixel2color(&pa88_pixel2color);
								INIT__vc_color2pixel(&pa88_color2pixel);
							} else {
								INIT__vc_pixel2color(&la88_pixel2color);
								INIT__vc_color2pixel(&la88_color2pixel);
							}
							goto got_p2c;
						default: break;
						}
#undef LA
					}
				}
			}

			/* Fallback: use a generic color conversion function */
			if (ispal) {
				if (need_mask) {
					INIT__vc_pixel2color(&pext_pal_pixel2color__withalpha);
					INIT__vc_color2pixel(&pdep_pal_color2pixel__withalpha);
				} else {
					INIT__vc_pixel2color(&pal_pixel2color__withalpha);
					INIT__vc_color2pixel(&pal_color2pixel__withalpha);
				}
			} else if (self->vc_specs.vcs_cbits >= 8) {
				if (need_mask) {
					INIT__vc_pixel2color(&pext_gray256_pixel2color__withalpha);
					INIT__vc_color2pixel(&pdep_gray256_color2pixel__withalpha);
				} else {
					INIT__vc_pixel2color(&gray256_pixel2color__withalpha);
					INIT__vc_color2pixel(&gray256_color2pixel__withalpha);
				}
			} else if (self->vc_specs.vcs_cbits >= 4) {
				if (need_mask) {
					INIT__vc_pixel2color(&pext_gray16_pixel2color__withalpha);
					INIT__vc_color2pixel(&pdep_gray16_color2pixel__withalpha);
				} else {
					INIT__vc_pixel2color(&gray16_pixel2color__withalpha);
					INIT__vc_color2pixel(&gray16_color2pixel__withalpha);
				}
			} else if (self->vc_specs.vcs_cbits >= 2) {
				if (need_mask) {
					INIT__vc_pixel2color(&pext_gray4_pixel2color__withalpha);
					INIT__vc_color2pixel(&pdep_gray4_color2pixel__withalpha);
				} else {
					INIT__vc_pixel2color(&gray4_pixel2color__withalpha);
					INIT__vc_color2pixel(&gray4_color2pixel__withalpha);
				}
			} else {
				INIT__vc_pixel2color(&gray2_pixel2color__withalpha);
				INIT__vc_color2pixel(&gray2_color2pixel__withalpha);
			}
		} else {
			if (ispal) {
				if (need_mask) {
					INIT__vc_pixel2color(&pext_pal_pixel2color);
					INIT__vc_color2pixel(&pdep_pal_color2pixel);
				} else {
					INIT__vc_pixel2color(&pal_pixel2color);
					INIT__vc_color2pixel(&pal_color2pixel);
				}
			} else if (self->vc_specs.vcs_cbits >= 8) {
				if (need_mask) {
					INIT__vc_pixel2color(&pext_gray256_pixel2color);
					INIT__vc_color2pixel(&pdep_gray256_color2pixel);
				} else {
					INIT__vc_pixel2color(&l8_pixel2color);
					INIT__vc_color2pixel(&l8_color2pixel);
				}
			} else if (self->vc_specs.vcs_cbits >= 4) {
				if (need_mask) {
					INIT__vc_pixel2color(&pext_gray16_pixel2color);
					INIT__vc_color2pixel(&pdep_gray16_color2pixel);
				} else {
					INIT__vc_pixel2color(&l4_pixel2color);
					INIT__vc_color2pixel(&l4_color2pixel);
				}
			} else if (self->vc_specs.vcs_cbits >= 2) {
				if (need_mask) {
					INIT__vc_pixel2color(&pext_gray4_pixel2color);
					INIT__vc_color2pixel(&pdep_gray4_color2pixel);
				} else {
					INIT__vc_pixel2color(&l2_pixel2color);
					INIT__vc_color2pixel(&l2_color2pixel);
				}
			} else {
				INIT__vc_pixel2color(&l1_pixel2color);
				INIT__vc_color2pixel(&l1_color2pixel);
			}
		}
	} else {
		/* Fallback: must use generic PEXT/PDEP encode/decode functions. */
		bool has_alpha = self->vcc_used_amask != 0;
		/* TODO: Codecs with >8 bits for some channel need to use custom
		 *       callbacks for `vc_color2pixel64' /  `vc_pixel2color64',
		 *       even though they still use <=32-bit pixels.
		 * The  default ones linked here will just strip the extra bits
		 * during color conversion, meaning that e.g. RGBA1010102 would
		 * lose the least significant 2 bits of color information. */
		if (has_alpha) {
			INIT__vc_pixel2color(&pext_rgba_pixel2color);
			INIT__vc_color2pixel(&pdep_rgba_color2pixel);
		} else {
			INIT__vc_pixel2color(&pext_rgb_pixel2color);
			INIT__vc_color2pixel(&pdep_rgb_color2pixel);
		}

		/* Optimization for codecs where masks are continuous (meaning PDEP/PEXT aren't needed) */
#ifdef HAVE_shft_channel_decode
		if (self->vcc_shft_rmask != (shift_t)-1 && self->vcc_shft_gmask != (shift_t)-1 &&
		    self->vcc_shft_bmask != (shift_t)-1 && self->vcc_shft_amask != (shift_t)-1) {
#ifdef HAVE_shft_channel_decode_nomiss
			bool hasmiss = (self->vcc_miss_rbits | self->vcc_miss_gbits |
			                self->vcc_miss_bbits | self->vcc_miss_abits) != 0;
			if (!hasmiss) {
				if (has_alpha) {
					INIT__vc_pixel2color(&shft_rgba_pixel2color_nomiss);
				} else {
					INIT__vc_pixel2color(&shft_rgb_pixel2color_nomiss);
				}
			} else
#endif /* HAVE_shft_channel_decode_nomiss */
			{
				if (has_alpha) {
					INIT__vc_pixel2color(&shft_rgba_pixel2color);
				} else {
					INIT__vc_pixel2color(&shft_rgb_pixel2color);
				}
			}
			if (has_alpha) {
				INIT__vc_color2pixel(&shft_rgba_color2pixel);
			} else {
				INIT__vc_color2pixel(&shft_rgb_color2pixel);
			}
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
				INIT__vc_pixel2color(encode_codec->vc_pixel2color);
				INIT__vc_color2pixel(encode_codec->vc_color2pixel);
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
					INIT__vc_pixel2color(decode_codec->vc_pixel2color);
				}
			}
		}
	}
#undef INIT__vc_pixel2color
#undef INIT__vc_color2pixel
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

#endif /* !GUARD_LIBVIDEO_GFX_CODEC_CODEC_C */
