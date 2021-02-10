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
#ifndef GUARD_LIBVGASTATE_VGAIO_H
#define GUARD_LIBVGASTATE_VGAIO_H 1

#include "api.h"
/**/

#include <hw/video/vga.h>
#include <kos/kernel/types.h>
#include <kos/types.h>
#include <sys/io.h>

DECL_BEGIN

#ifndef __port_t_defined
#define __port_t_defined 1
typedef __IOPORT_T port_t;
#endif /* !__port_t_defined */

#define VGA_VRAM_BASE 0xa0000
#define VGA_VRAM_TEXT 0xb8000
#define VGA_VRAM_SIZE 0x01000


/* macro  for  composing an  8-bit  VGA register
 * index and value into a single 16-bit quantity */
#define VGA_OUT16VAL(v, r) (((v) << 8) | (r))

/* decide whether we should enable the faster 16-bit VGA register writes */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define VGA_OUTW_WRITE 1
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */



/* generic VGA port read/write */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL u8
NOTHROW_KERNEL(CC vga_r)(port_t port) {
	return inb_p(port);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW_KERNEL(CC vga_w)(port_t port, u8 val) {
	outb_p(port, val);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW_KERNEL(CC vga_w_fast)(port_t port, u8 reg, u8 val) {
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
LOCAL NOBLOCK u8
NOTHROW_KERNEL(CC vga_rcrt)(u8 reg) {
	vga_w(VGA_CRT_IC, reg);
	return vga_r(VGA_CRT_DC);
}

LOCAL NOBLOCK void
NOTHROW_KERNEL(CC vga_wcrt)(u8 reg, u8 val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_CRT_IC, VGA_CRT_DC, reg, val);
}

LOCAL NOBLOCK void
NOTHROW_KERNEL(CC vga_wcrt_res)(u8 reg, u8 val, u8 resmask) {
	if (resmask) {
		u8 oldval;
		oldval = vga_rcrt(reg);
		vga_wcrt(reg, (oldval & resmask) | val);
	} else {
		vga_wcrt(reg, val);
	}
}

/* VGA sequencer register read/write */
LOCAL NOBLOCK u8
NOTHROW_KERNEL(CC vga_rseq)(u8 reg) {
	vga_w(VGA_SEQ_I, reg);
	return vga_r(VGA_SEQ_D);
}

LOCAL NOBLOCK void
NOTHROW_KERNEL(CC vga_wseq)(u8 reg, u8 val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_SEQ_I, VGA_SEQ_D, reg, val);
}

LOCAL NOBLOCK void
NOTHROW_KERNEL(CC vga_wseq_res)(u8 reg, u8 val, u8 resmask) {
	if (resmask) {
		u8 oldval;
		oldval = vga_rseq(reg);
		vga_wseq(reg, (oldval & resmask) | val);
	} else {
		vga_wseq(reg, val);
	}
}

/* VGA graphics controller register read/write */
LOCAL NOBLOCK u8
NOTHROW_KERNEL(CC vga_rgfx)(u8 reg) {
	vga_w(VGA_GFX_I, reg);
	return vga_r(VGA_GFX_D);
}

LOCAL NOBLOCK void
NOTHROW_KERNEL(CC vga_wgfx)(u8 reg, u8 val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_GFX_I, VGA_GFX_D, reg, val);
}

LOCAL NOBLOCK void
NOTHROW_KERNEL(CC vga_wgfx_res)(u8 reg, u8 val, u8 resmask) {
	if (resmask) {
		u8 oldval;
		oldval = vga_rgfx(reg);
		vga_wgfx(reg, (oldval & resmask) | val);
	} else {
		vga_wgfx(reg, val);
	}
}

/* VGA attribute controller register read/write */
LOCAL NOBLOCK u8
NOTHROW_KERNEL(CC vga_rattr)(u8 reg) {
	vga_r(VGA_IS1_RC);
	vga_w(VGA_ATT_IW, reg);
	return vga_r(VGA_ATT_R);
}

LOCAL NOBLOCK void
NOTHROW_KERNEL(CC vga_wattr)(u8 reg, u8 val) {
	vga_r(VGA_IS1_RC);
	vga_w(VGA_ATT_IW, reg);
	vga_w(VGA_ATT_W, val);
}

LOCAL NOBLOCK void
NOTHROW_KERNEL(CC vga_wattr_res)(u8 reg, u8 val, u8 resmask) {
	if (resmask) {
		u8 oldval;
		oldval = vga_rattr(reg);
		vga_wattr(reg, (oldval & resmask) | val);
	} else {
		vga_wattr(reg, val);
	}
}


DECL_END

#endif /* !GUARD_LIBVGASTATE_VGAIO_H */
