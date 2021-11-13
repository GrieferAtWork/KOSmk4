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
__DECL_BEGIN

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

/************************************************************************/
/* !!! DON'T DEFINE THIS STUFF AS MACROS !!!                            */
/* You're gonna get problems when arguments have side-effects!          */
/************************************************************************/

/* VGA CRTC register read/write
 * @param: reg: One of `VGA_CRTC_*' */
__FORCELOCAL __ATTR_WUNUSED __uint8_t vga_rcrt(__uint8_t __reg) {
	vga_w(VGA_CRT_IC, __reg);
	return vga_r(VGA_CRT_DC);
}
__FORCELOCAL void vga_wcrt(__uint8_t __reg, __uint8_t __val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_CRT_IC, VGA_CRT_DC, __reg, __val);
}
__FORCELOCAL void vga_wcrt_res(__uint8_t __reg, __uint8_t __val, __uint8_t __resmask) {
	__hybrid_assert(!(__val & __resmask));
	if __untraced(__resmask) {
		vga_wcrt(__reg, (vga_rcrt(__reg) & __resmask) | __val);
	} else {
		vga_wcrt(__reg, __val);
	}
}



/* VGA sequencer register read/write
 * @param: reg: One of `VGA_SEQ_*' */
__FORCELOCAL __ATTR_WUNUSED __uint8_t vga_rseq(__uint8_t __reg) {
	vga_w(VGA_SEQ_I, __reg);
	return vga_r(VGA_SEQ_D);
}
__FORCELOCAL void vga_wseq(__uint8_t __reg, __uint8_t __val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_SEQ_I, VGA_SEQ_D, __reg, __val);
}
__FORCELOCAL void vga_wseq_res(__uint8_t __reg, __uint8_t __val, __uint8_t __resmask) {
	__hybrid_assert(!(__val & __resmask));
	if __untraced(__resmask) {
		vga_wseq(__reg, (vga_rseq(__reg) & __resmask) | __val);
	} else {
		vga_wseq(__reg, __val);
	}
}



/* VGA graphics controller register read/write
 * @param: reg: One of `VGA_GFX_*' */
__FORCELOCAL __ATTR_WUNUSED __uint8_t vga_rgfx(__uint8_t __reg) {
	vga_w(VGA_GFX_I, __reg);
	return vga_r(VGA_GFX_D);
}
__FORCELOCAL void vga_wgfx(__uint8_t __reg, __uint8_t __val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_GFX_I, VGA_GFX_D, __reg, __val);
}
__FORCELOCAL void vga_wgfx_res(__uint8_t __reg, __uint8_t __val, __uint8_t __resmask) {
	__hybrid_assert(!(__val & __resmask));
	if __untraced(__resmask) {
		vga_wgfx(__reg, (vga_rgfx(__reg) & __resmask) | __val);
	} else {
		vga_wgfx(__reg, __val);
	}
}



/* VGA attribute controller register read/write
 * @param: is1_rX:      Either `VGA_IS1_RC' or `VGA_IS1_RM'
 * @param: reg_and_pas: One of `VGA_ATC_*', optionally or'd with `VGA_ATT_IW_PAS',
 *                      depending on `pas_or_0' previously passed to `vga_setpas'. */
__FORCELOCAL __ATTR_WUNUSED __uint8_t vga_rattr(__port_t __is1_rX, __uint8_t __reg_and_pas) {
	vga_r_p(__is1_rX); /* Reset flip/flop */
	vga_w_p(VGA_ATT_IW, __reg_and_pas);
	return vga_r_p(VGA_ATT_R);
}
__FORCELOCAL void vga_wattr(__port_t __is1_rX, __uint8_t __reg_and_pas, __uint8_t __val) {
	vga_r_p(__is1_rX); /* Reset flip/flop */
	vga_w_p(VGA_ATT_IW, __reg_and_pas);
	vga_w_p(VGA_ATT_W, __val);
}
__FORCELOCAL void vga_wattr_res(__port_t __is1_rX, __uint8_t __reg_and_pas,
                                __uint8_t __val, __uint8_t __resmask) {
	__hybrid_assert(!(__val & __resmask));
	if __untraced(__resmask) {
		vga_wattr(__is1_rX, __reg_and_pas, (vga_rattr(__is1_rX, __reg_and_pas) & __resmask) | __val);
	} else {
		vga_wattr(__is1_rX, __reg_and_pas, __val);
	}
}

/* Enable/disable color palette access.
 * WARNING: While enabled, nothing (may) be displayed on-screen!
 * @param: pas_or_0: Either `0' (to enable), or `VGA_ATT_IW_PAS' (to disable) */
#define vga_setpas(is1_rX, pas_or_0)        \
	(vga_r_p(is1_rX) /* Reset flip/flop */, \
	 vga_w_p(VGA_ATT_IW, pas_or_0))


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBSVGA_UTIL_VGAIO_H */