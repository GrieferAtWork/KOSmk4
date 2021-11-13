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

#ifdef __CC__

/* macro  for  composing an  8-bit  VGA register
 * index and value into a single 16-bit quantity */
#define VGA_OUT16VAL(v, r) (((v) << 8) | (r))

/* decide whether we should enable the faster 16-bit VGA register writes */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define VGA_OUTW_WRITE 1
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */

/* generic VGA port read/write */
#define vga_r   inb
#define vga_r_p inb_p
#ifdef __USE_KOS_ALTERATIONS
#define vga_w   outb
#define vga_w_p outb_p
#else /* __USE_KOS_ALTERATIONS */
/* Deal with reversed parameters... */
#define vga_w(port, val)   outb(val, port)
#define vga_w_p(port, val) outb_p(val, port)
#endif /* !__USE_KOS_ALTERATIONS */

#define vga_w_fast(port, reg, val) outw(port, VGA_OUT16VAL(val, reg))

#ifdef VGA_OUTW_WRITE
#if 1 /* `port_i + 1 == port_d' is always the case, so can keep code a bit simpler! */
#define __VGA_OUTW_SELECTOR(func, port_i, port_d, reg, val) func##_fast(port_i, reg, val)
#else
#define __VGA_OUTW_SELECTOR(func, port_i, port_d, reg, val) \
	((port_i + 1 == port_d) ? func##_fast(port_i, reg, val) \
	                        : (func(port_i, reg),           \
	                           func(port_d, val)))
#endif
#else /* VGA_OUTW_WRITE */
#define __VGA_OUTW_SELECTOR(func, port_i, port_d, reg, val) \
	(func(port_i, reg), func(port_d, val))
#endif /* !VGA_OUTW_WRITE */

/* VGA CRTC register read/write
 * @param: reg: One of `VGA_CRTC_*' */
#define vga_rcrt(reg)      (vga_w(VGA_CRT_IC, reg), vga_r(VGA_CRT_DC))
#define vga_wcrt(reg, val) __VGA_OUTW_SELECTOR(vga_w, VGA_CRT_IC, VGA_CRT_DC, reg, val)
#define vga_wcrt_res(reg, val, resmask)                           \
	(__hybrid_assert(!((val) & (resmask))),                       \
	 (resmask) ? vga_wcrt(reg, (vga_rcrt(reg) & (resmask)) | val) \
	           : vga_wcrt(reg, val))

/* VGA sequencer register read/write
 * @param: reg: One of `VGA_SEQ_*' */
#define vga_rseq(reg)      (vga_w(VGA_SEQ_I, reg), vga_r(VGA_SEQ_D))
#define vga_wseq(reg, val) __VGA_OUTW_SELECTOR(vga_w, VGA_SEQ_I, VGA_SEQ_D, reg, val)
#define vga_wseq_res(reg, val, resmask)                           \
	(__hybrid_assert(!((val) & (resmask))),                       \
	 (resmask) ? vga_wseq(reg, (vga_rseq(reg) & (resmask)) | val) \
	           : vga_wseq(reg, val))

/* VGA graphics controller register read/write
 * @param: reg: One of `VGA_GFX_*' */
#define vga_rgfx(reg)      (vga_w(VGA_GFX_I, reg), vga_r(VGA_GFX_D))
#define vga_wgfx(reg, val) __VGA_OUTW_SELECTOR(vga_w, VGA_GFX_I, VGA_GFX_D, reg, val)
#define vga_wgfx_res(reg, val, resmask)                           \
	(__hybrid_assert(!((val) & (resmask))),                       \
	 (resmask) ? vga_wgfx(reg, (vga_rgfx(reg) & (resmask)) | val) \
	           : vga_wgfx(reg, val))

/* VGA attribute controller register read/write
 * @param: is1_rX: Either `VGA_IS1_RC' or `VGA_IS1_RM'
 * @param: reg: One of `VGA_ATC_*' */
#define vga_rattr(is1_rX, reg)              \
	(vga_r_p(is1_rX) /* Reset flip/flop */, \
	 vga_w_p(VGA_ATT_IW, reg), vga_r_p(VGA_ATT_R))
#define vga_wattr(is1_rX, reg, val)         \
	(vga_r_p(is1_rX) /* Reset flip/flop */, \
	 vga_w_p(VGA_ATT_IW, reg),              \
	 vga_w_p(VGA_ATT_W, val))
#define vga_wattr_res(is1_rX, reg, val, resmask)                                    \
	(__hybrid_assert(!((val) & (resmask))),                                         \
	 (resmask) ? vga_wattr(is1_rX, reg, (vga_rattr(is1_rX, reg) & (resmask)) | val) \
	           : vga_wattr(is1_rX, reg, val))
#endif /* __CC__ */

#endif /* !_LIBSVGA_UTIL_VGAIO_H */
