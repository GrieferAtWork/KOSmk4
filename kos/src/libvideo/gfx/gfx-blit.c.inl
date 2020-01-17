/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "gfx.c"
//#define DEFINE_BLIT 1
#define DEFINE_BITBLIT 1
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_BLIT) + defined(DEFINE_BITBLIT)) != 1
#error "Must #define exactly one of `DEFINE_BLIT' or `DEFINE_BITBLIT'"
#endif

DECL_BEGIN

#ifdef DEFINE_BLIT
#define FUNC(x)         x##_blit
#define IF_BLIT(...)    __VA_ARGS__
#define IF_BITBLIT(...) /* nothing */
#else /* DEFINE_BLIT */
#define FUNC(x)         x##_bitblit
#define IF_BLIT(...)    /* nothing */
#define IF_BITBLIT(...) __VA_ARGS__
#endif /* !DEFINE_BLIT */


LOCAL void CC
FUNC(copy_perpixel_fixed)(struct video_gfx *self,
                          uintptr_t dst_x, uintptr_t dst_y,
                          struct video_gfx const *src,
                          uintptr_t src_x, uintptr_t src_y,
                          size_t size_x, size_t size_y
#ifdef DEFINE_BITBLIT
                          ,
                          void const *__restrict bitmask,
                          size_t bitmask_base_offset,
                          size_t bitmask_size_x
#endif /* DEFINE_BITBLIT */
                          ) {
	size_t x, y;
	src_x += src->vx_offt_x;
	src_y += src->vx_offt_y;
#ifdef DEFINE_BITBLIT
	if (bitmask_base_offset == 0 && bitmask_size_x == size_x) {
		uint8_t byte, bits = 0;
		for (y = 0; y < size_y; ++y) {
			for (x = 0; x < size_x; ++x) {
				video_color_t color;
				uint8_t bit;
				if (!bits) {
					byte    = *(uint8_t *)bitmask;
					bitmask = (uint8_t *)bitmask + 1;
					bits    = 8;
				}
				--bits;
				bit = byte & 1;
				byte >>= 1;
				if (!bit)
					continue;
				color = video_gfx_getabscolor(src,
				                              src_x + x,
				                              src_y + y);
				video_gfx_putabscolor(self,
				                      dst_x + x,
				                      dst_y + y,
				                      color);
			}
		}
	} else
#endif /* DEFINE_BITBLIT */
	{
		for (y = 0; y < size_y; ++y) {
			for (x = 0; x < size_x; ++x) {
				video_color_t color;
#ifdef DEFINE_BITBLIT
				size_t bitno;
				uint8_t byte;
				bitno = bitmask_base_offset + y * bitmask_size_x + x;
				byte = ((uint8_t *)bitmask)[bitno / 8];
				if (!(byte & (bitno % 8)))
					continue;
#endif /* DEFINE_BITBLIT */
				color = video_gfx_getabscolor(src,
				                              src_x + x,
				                              src_y + y);
				video_gfx_putabscolor(self,
				                      dst_x + x,
				                      dst_y + y,
				                      color);
			}
		}
	}
}



INTERN void CC
FUNC(libvideo_gfx_defaultgfx)(struct video_gfx *self,
                              intptr_t dst_x, intptr_t dst_y,
                              struct video_gfx const *src,
                              intptr_t src_x, intptr_t src_y,
                              size_t size_x, size_t size_y
                              IF_BITBLIT(, void const *__restrict bitmask)) {
	size_t dst_sx, dst_sy;
	size_t src_sx, src_sy;
	uintptr_t temp;
	IF_BITBLIT(size_t bitmask_base_offset);
	IF_BITBLIT(size_t bitmask_size_x);
	if (!size_x || !size_y)
		return;
	IF_BITBLIT(bitmask_base_offset = 0);
	IF_BITBLIT(bitmask_size_x = size_x);
	if (dst_x < 0) {
		if unlikely((uintptr_t)(-dst_x) >= size_x)
			return;
		IF_BITBLIT(bitmask_base_offset = (uintptr_t)-dst_x);
		src_x += (uintptr_t)-dst_x;
		size_x -= (uintptr_t)-dst_x;
		dst_x = 0;
	}
	if (dst_y < 0) {
		if unlikely((uintptr_t)(-dst_y) >= size_y)
			return;
		IF_BITBLIT(bitmask_base_offset += ((uintptr_t)-dst_y) * bitmask_size_x);
		src_y += (uintptr_t)-dst_y;
		size_y -= (uintptr_t)-dst_y;
		dst_y = 0;
	}
	if (src_x < 0) {
		if unlikely((uintptr_t)(-src_x) >= size_x)
			return;
		IF_BITBLIT(bitmask_base_offset += (uintptr_t)-src_x);
		dst_x += (uintptr_t)-src_x;
		size_x -= (uintptr_t)-src_x;
		src_x = 0;
	}
	if (src_y < 0) {
		if unlikely((uintptr_t)(-src_y) >= size_y)
			return;
		IF_BITBLIT(bitmask_base_offset += ((uintptr_t)-src_y) * bitmask_size_x);
		dst_y += (uintptr_t)-src_y;
		size_y -= (uintptr_t)-src_y;
		src_y = 0;
	}
	dst_sx = self->vx_size_x;
	dst_sy = self->vx_size_y;
	src_sx = src->vx_size_x;
	src_sy = src->vx_size_y;
	/* Check for out-of-bounds rendering */
	if unlikely((uintptr_t)dst_x >= dst_sx)
		return;
	if unlikely((uintptr_t)dst_y >= dst_sy)
		return;
	if unlikely((uintptr_t)src_x >= src_sx)
		return;
	if unlikely((uintptr_t)src_y >= src_sy)
		return;
	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_x, size_x, &temp) || temp > dst_sx)
		size_x = dst_sx - (uintptr_t)dst_x;
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_y, size_y, &temp) || temp > dst_sy)
		size_y = dst_sy - (uintptr_t)dst_y;
	if unlikely(OVERFLOW_UADD((uintptr_t)src_x, size_x, &temp) || temp > src_sx)
		size_x = src_sx - (uintptr_t)src_x;
	if unlikely(OVERFLOW_UADD((uintptr_t)src_y, size_y, &temp) || temp > src_sy)
		size_y = src_sy - (uintptr_t)src_y;
	FUNC(copy_perpixel_fixed)(self,
	                          (uintptr_t)dst_x,
	                          (uintptr_t)dst_y,
	                          src,
	                          (uintptr_t)src_x,
	                          (uintptr_t)src_y,
	                          size_x,
	                          size_y
#ifdef DEFINE_BITBLIT
	                          ,
	                          bitmask,
	                          bitmask_base_offset,
	                          bitmask_size_x
#endif /* DEFINE_BITBLIT */
	                          );
}






DECL_END

#undef IF_BLIT
#undef IF_BITBLIT
#undef FUNC
#undef DEFINE_BLIT
#undef DEFINE_BITBLIT
