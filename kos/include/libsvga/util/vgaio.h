/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBSVGA_UTIL_VGAIO_H
#define _LIBSVGA_UTIL_VGAIO_H 1

#include <hybrid/__assert.h>
#include <hybrid/byteorder.h>

#include <bits/types.h>
#include <hw/video/vga.h>
#include <kos/anno.h>
#include <sys/io.h>

#ifndef __NOTHROW_KERNEL
#ifdef __KERNEL__
#define __NOTHROW_KERNEL __NOTHROW
#else /* __KERNEL__ */
#define __NOTHROW_KERNEL /*__THROWING*/
#endif /* !__KERNEL__ */
#endif /* !__NOTHROW_KERNEL */

#ifdef __CC__
__DECL_BEGIN

/* macro  for  composing an  8-bit  VGA register
 * index and value into a single 16-bit quantity */
#define VGA_OUT16VAL(v, r) (((v) << 8) | (r))

/* decide whether we should enable the faster 16-bit VGA register writes */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define VGA_OUTW_WRITE 1
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */



/* generic VGA port read/write */
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __uint8_t
__NOTHROW_KERNEL(vga_r)(__port_t port) {
	return inb_p(port);
}

__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL void
__NOTHROW_KERNEL(vga_w)(__port_t port, __uint8_t val) {
	outb_p(port, val);
}

__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL void
__NOTHROW_KERNEL(vga_w_fast)(__port_t port, __uint8_t reg, __uint8_t val) {
	outw(port, VGA_OUT16VAL(val, reg));
}

#ifdef VGA_OUTW_WRITE
#if 1
#define __VGA_OUTW_SELECTOR(func, port_i, port_d, reg, val) func##_fast(port_i, reg, val)
#else
#define __VGA_OUTW_SELECTOR(func, port_i, port_d, reg, val) ((port_i + 1 == port_d) ? func##_fast(port_i, reg, val) : (func(port_i, reg), func(port_d, val)))
#endif
#else /* VGA_OUTW_WRITE */
#define __VGA_OUTW_SELECTOR(func, port_i, port_d, reg, val) (func(port_i, reg), func(port_d, val))
#endif /* !VGA_OUTW_WRITE */

/* VGA CRTC register read/write */
__LOCAL __NOBLOCK __uint8_t
__NOTHROW_KERNEL(vga_rcrt)(__uint8_t reg) {
	vga_w(VGA_CRT_IC, reg);
	return vga_r(VGA_CRT_DC);
}

__LOCAL __NOBLOCK void
__NOTHROW_KERNEL(vga_wcrt)(__uint8_t reg, __uint8_t val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_CRT_IC, VGA_CRT_DC, reg, val);
}

__LOCAL __NOBLOCK void
__NOTHROW_KERNEL(vga_wcrt_res)(__uint8_t reg, __uint8_t val, __uint8_t resmask) {
	__hybrid_assert(!(val & resmask));
	if (resmask) {
		__uint8_t oldval;
		oldval = vga_rcrt(reg);
		vga_wcrt(reg, (oldval & resmask) | val);
	} else {
		vga_wcrt(reg, val);
	}
}

/* VGA sequencer register read/write */
__LOCAL __NOBLOCK __uint8_t
__NOTHROW_KERNEL(vga_rseq)(__uint8_t reg) {
	vga_w(VGA_SEQ_I, reg);
	return vga_r(VGA_SEQ_D);
}

__LOCAL __NOBLOCK void
__NOTHROW_KERNEL(vga_wseq)(__uint8_t reg, __uint8_t val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_SEQ_I, VGA_SEQ_D, reg, val);
}

__LOCAL __NOBLOCK void
__NOTHROW_KERNEL(vga_wseq_res)(__uint8_t reg, __uint8_t val, __uint8_t resmask) {
	__hybrid_assert(!(val & resmask));
	if (resmask) {
		__uint8_t oldval;
		oldval = vga_rseq(reg);
		vga_wseq(reg, (oldval & resmask) | val);
	} else {
		vga_wseq(reg, val);
	}
}

/* VGA graphics controller register read/write */
__LOCAL __NOBLOCK __uint8_t
__NOTHROW_KERNEL(vga_rgfx)(__uint8_t reg) {
	vga_w(VGA_GFX_I, reg);
	return vga_r(VGA_GFX_D);
}

__LOCAL __NOBLOCK void
__NOTHROW_KERNEL(vga_wgfx)(__uint8_t reg, __uint8_t val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_GFX_I, VGA_GFX_D, reg, val);
}

__LOCAL __NOBLOCK void
__NOTHROW_KERNEL(vga_wgfx_res)(__uint8_t reg, __uint8_t val, __uint8_t resmask) {
	__hybrid_assert(!(val & resmask));
	if (resmask) {
		__uint8_t oldval;
		oldval = vga_rgfx(reg);
		vga_wgfx(reg, (oldval & resmask) | val);
	} else {
		vga_wgfx(reg, val);
	}
}

/* VGA attribute controller register read/write
 * @param: is1_rX: Either `VGA_IS1_RC' or `VGA_IS1_RM'
 */
__LOCAL __NOBLOCK __uint8_t
__NOTHROW_KERNEL(vga_rattr)(__port_t is1_rX, __uint8_t reg) {
	vga_r(is1_rX); /* Reset flip/flop */
	vga_w(VGA_ATT_IW, reg);
	return vga_r(VGA_ATT_R);
}

__LOCAL __NOBLOCK void
__NOTHROW_KERNEL(vga_wattr)(__port_t is1_rX, __uint8_t reg, __uint8_t val) {
	vga_r(is1_rX); /* Reset flip/flop */
	vga_w(VGA_ATT_IW, reg);
	vga_w(VGA_ATT_W, val);
}

__LOCAL __NOBLOCK void
__NOTHROW_KERNEL(vga_wattr_res)(__port_t is1_rX, __uint8_t reg, __uint8_t val, __uint8_t resmask) {
	__hybrid_assert(!(val & resmask));
	if (resmask) {
		__uint8_t oldval;
		oldval = vga_rattr(is1_rX, reg);
		vga_wattr(is1_rX, reg, (oldval & resmask) | val);
	} else {
		vga_wattr(is1_rX, reg, val);
	}
}

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBSVGA_UTIL_VGAIO_H */
