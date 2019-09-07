/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_OUTPUT_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_OUTPUT_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/debugger.h>

#ifndef CONFIG_NO_DEBUGGER
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/rand.h>
#include <kernel/vm.h>

#include <hybrid/byteorder.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <kos/io/vga.h>
#include <sys/io.h>

#include <assert.h>
#include <format-printer.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unicode.h>

DECL_BEGIN

#define VGA_VRAM_ADDR  0xB8000
#define VGA_VRAM_SIZE  0x08000



INTERN ATTR_DBGBSS struct vga_font vga_debugfont;
INTERN_CONST ATTR_DBGRODATA struct vga_mode const vga_debugmode = {
	/* BAD! DON'T YOU DARE TO BLINK!
	 * Like literally, dis shit is dangerous to look at
	 * (Sorry, but even though I never actually had a seizure
	 *  from stupid $h1t like this, every time I see this blinking,
	 *  I can just feel that if I were to stare at it for too long,
	 *  I'd either throw up, or literally just die)
	 * Especially since I use the intensity attribute when the kernel
	 * panics, meaning that while this is still enabled, it'll blink
	 * when I was sitting here knowing that I had to look at it to
	 * figure out what happened.
	 * And I know I could have simply used regular colors at any point,
	 * but before starting this module and reading up on VGA I didn't
	 * see the connection and didn't understand why text was sometimes
	 * blinking.
	 * (And wiki.osdev's VGA TTY page neglects to mention the seizure-
	 *  inducing blinkyness that happens on real hardware and emulators
	 *  ~supporting~ the VgA sTaNdArT's GrEaT iDeA oF iNcLuDiNg ThIs FeAtUrE) */
	.vm_att_mode          = VGA_AT10_FDUP9 & ~(VGA_AT10_FBLINK),
	.vm_att_overscan      = 0x00,
	.vm_att_plane_enable  = 0x0f & VGA_AT12_FMASK,
	.vm_att_pel           = 0x08 & VGA_AT13_FMASK,
	.vm_att_color_page    = 0x00,
	.vm_mis               = VGA_MIS_FCOLOR|VGA_MIS_FENB_MEM_ACCESS|
	                        VGA_MIS_FVSYNCPOL|VGA_MIS_FHSYNCPOL|
	                        VGA_MIS_FSEL_HIGH_PAGE,
	.vm_gfx_sr_value      = 0x00,
	.vm_gfx_sr_enable     = 0x00,
	.vm_gfx_compare_value = 0x00,
	.vm_gfx_data_rotate   = 0x00,
	.vm_gfx_mode          = 0x10,
	.vm_gfx_misc          = 0x0e,
	.vm_gfx_compare_mask  = 0x0f,
	.vm_gfx_bit_mask      = 0xff,
	.vm_crt_h_total       = 0x5f,
	.vm_crt_h_disp        = 0x4f,
	.vm_crt_h_blank_start = 0x50,
	.vm_crt_h_blank_end   = 0x82,
	.vm_crt_h_sync_start  = 0x55,
	.vm_crt_h_sync_end    = 0x81,
	.vm_crt_v_total       = 0xbf,
	.vm_crt_overflow      = 0x1f,
	.vm_crt_preset_row    = 0x00,
	.vm_crt_max_scan      = 0x4f,
	.vm_crt_cursor_start  = 0x0d | VGA_CRA_FCURSOR_DISABLE,
	.vm_crt_cursor_end    = 0x0e,
	.vm_crt_start_hi      = 0x00,
	.vm_crt_start_lo      = 0x00,
	.vm_crt_cursor_hi     = 0x02,
	.vm_crt_cursor_lo     = 0x80,
	.vm_crt_v_sync_start  = 0x9c,
	.vm_crt_v_sync_end    = 0x8e,
	.vm_crt_v_disp_end    = 0x8f,
	.vm_crt_offset        = 0x28,
	.vm_crt_underline     = 0x1f,
	.vm_crt_v_blank_start = 0x96,
	.vm_crt_v_blank_end   = 0xb9 & ~VGA_CR16_FRESERVED,
	.vm_crt_mode          = 0xa3,
	.vm_crt_line_compare  = 0xff,
	.vm_seq_clock_mode    = 0x00,
	.vm_seq_plane_write   = 0x03,
	.vm_seq_character_map = 0x00,
	.vm_seq_memory_mode   = VGA_SR04_FEXT_MEM,
};

PRIVATE ATTR_DBGRODATA struct vga_palette const vga_debugpal = {
#define C(r, g, b) {r<<2, g<<2, b<<2}
	{	C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x2a), C(0x00, 0x2a, 0x00), C(0x00, 0x2a, 0x2a), C(0x2a, 0x00, 0x00), C(0x2a, 0x00, 0x2a), C(0x2a, 0x2a, 0x00), C(0x2a, 0x2a, 0x2a),
		C(0x00, 0x00, 0x15), C(0x00, 0x00, 0x3f), C(0x00, 0x2a, 0x15), C(0x00, 0x2a, 0x3f), C(0x2a, 0x00, 0x15), C(0x2a, 0x00, 0x3f), C(0x2a, 0x2a, 0x15), C(0x2a, 0x2a, 0x3f),
		C(0x00, 0x15, 0x00), C(0x00, 0x15, 0x2a), C(0x00, 0x3f, 0x00), C(0x00, 0x3f, 0x2a), C(0x2a, 0x15, 0x00), C(0x2a, 0x15, 0x2a), C(0x2a, 0x3f, 0x00), C(0x2a, 0x3f, 0x2a),
		C(0x00, 0x15, 0x15), C(0x00, 0x15, 0x3f), C(0x00, 0x3f, 0x15), C(0x00, 0x3f, 0x3f), C(0x2a, 0x15, 0x15), C(0x2a, 0x15, 0x3f), C(0x2a, 0x3f, 0x15), C(0x2a, 0x3f, 0x3f),
		C(0x15, 0x00, 0x00), C(0x15, 0x00, 0x2a), C(0x15, 0x2a, 0x00), C(0x15, 0x2a, 0x2a), C(0x3f, 0x00, 0x00), C(0x3f, 0x00, 0x2a), C(0x3f, 0x2a, 0x00), C(0x3f, 0x2a, 0x2a),
		C(0x15, 0x00, 0x15), C(0x15, 0x00, 0x3f), C(0x15, 0x2a, 0x15), C(0x15, 0x2a, 0x3f), C(0x3f, 0x00, 0x15), C(0x3f, 0x00, 0x3f), C(0x3f, 0x2a, 0x15), C(0x3f, 0x2a, 0x3f),
		C(0x15, 0x15, 0x00), C(0x15, 0x15, 0x2a), C(0x15, 0x3f, 0x00), C(0x15, 0x3f, 0x2a), C(0x3f, 0x15, 0x00), C(0x3f, 0x15, 0x2a), C(0x3f, 0x3f, 0x00), C(0x3f, 0x3f, 0x2a),
		C(0x15, 0x15, 0x15), C(0x15, 0x15, 0x3f), C(0x15, 0x3f, 0x15), C(0x15, 0x3f, 0x3f), C(0x3f, 0x15, 0x15), C(0x3f, 0x15, 0x3f), C(0x3f, 0x3f, 0x15), C(0x3f, 0x3f, 0x3f),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
		C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00), C(0x00, 0x00, 0x00),
#undef  C
	}
};


/* macro for composing an 8-bit VGA register
 * index and value into a single 16-bit quantity */
#define VGA_OUT16VAL(v,r)    (((v) << 8)|(r))

/* decide whether we should enable the faster 16-bit VGA register writes */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define VGA_OUTW_WRITE 1
#endif


/* generic VGA port read/write */
FORCELOCAL ATTR_DBGTEXT u8 KCALL vga_r(port_t port) {
	return inb_p(port);
}
FORCELOCAL ATTR_DBGTEXT void KCALL vga_w(port_t port, u8 val) {
	outb_p(port, val);
}
FORCELOCAL ATTR_DBGTEXT void KCALL vga_w_fast(port_t port, u8 reg, u8 val) {
	outw(port, VGA_OUT16VAL(val, reg));
}

#ifdef VGA_OUTW_WRITE
#if 1
#define __VGA_OUTW_SELECTOR(func, port_i, port_d, reg, val)           func##_fast(port_i, reg, val)
#else
#define __VGA_OUTW_SELECTOR(func, port_i, port_d, reg, val)          ((port_i+1 == port_d) ? func##_fast(port_i, reg, val) : (func(port_i, reg), func(port_d, val)))
#endif
#else
#define __VGA_OUTW_SELECTOR(func, port_i, port_d, reg, val)          (func(port_i, reg),func(port_d, val))
#endif

/* VGA CRTC register read/write */
LOCAL ATTR_DBGTEXT u8 KCALL vga_rcrt(u8 reg) {
	vga_w(VGA_CRT_IC, reg);
	return vga_r(VGA_CRT_DC);
}
LOCAL ATTR_DBGTEXT void KCALL vga_wcrt(u8 reg, u8 val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_CRT_IC, VGA_CRT_DC, reg, val);
}

/* VGA sequencer register read/write */
LOCAL ATTR_DBGTEXT u8 KCALL vga_rseq(u8 reg) {
	vga_w(VGA_SEQ_I, reg);
	return vga_r(VGA_SEQ_D);
}
LOCAL ATTR_DBGTEXT void KCALL vga_wseq(u8 reg, u8 val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_SEQ_I, VGA_SEQ_D, reg, val);
}

/* VGA graphics controller register read/write */
LOCAL ATTR_DBGTEXT u8 KCALL vga_rgfx(u8 reg) {
	vga_w(VGA_GFX_I, reg);
	return vga_r(VGA_GFX_D);
}
LOCAL ATTR_DBGTEXT void KCALL vga_wgfx(u8 reg, u8 val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_GFX_I, VGA_GFX_D, reg, val);
}

/* VGA attribute controller register read/write */
LOCAL ATTR_DBGTEXT u8 KCALL vga_rattr(u8 reg) {
	vga_w(VGA_ATT_IW, reg);
	return vga_r(VGA_ATT_R);
}
LOCAL ATTR_DBGTEXT void KCALL vga_wattr(u8 reg, u8 val) {
	vga_w(VGA_ATT_IW, reg);
	vga_w(VGA_ATT_W, val);
}



PRIVATE ATTR_DBGTEXT void KCALL
VGA_SetMode(struct vga_mode const *__restrict mode) {
	u8 temp, qr1;
	qr1 = vga_rseq(VGA_SEQ_CLOCK_MODE);

	/* Turn off the screen. */
	vga_wseq(VGA_SEQ_RESET, 0x1);
	vga_wseq(VGA_SEQ_CLOCK_MODE, qr1 | VGA_SR01_FSCREEN_OFF);
	vga_wseq(VGA_SEQ_RESET, 0x3);

	/* Enable graphics mode. */
	vga_r(VGA_IS1_RC), vga_w(VGA_ATT_W, 0x00);
	vga_r(VGA_IS1_RC), temp = vga_rattr(VGA_ATC_MODE);
	vga_r(VGA_IS1_RC), vga_wattr(VGA_ATC_MODE, (temp & VGA_AT10_FRESERVED) | mode->vm_att_mode);
	vga_r(VGA_IS1_RC), vga_wattr(VGA_ATC_OVERSCAN, mode->vm_att_overscan);
	vga_r(VGA_IS1_RC), temp = vga_rattr(VGA_ATC_PLANE_ENABLE);
	vga_r(VGA_IS1_RC), vga_wattr(VGA_ATC_PLANE_ENABLE, (temp & VGA_AT12_FRESERVED) | mode->vm_att_plane_enable);
	vga_r(VGA_IS1_RC), temp = vga_rattr(VGA_ATC_PEL);
	vga_r(VGA_IS1_RC), vga_wattr(VGA_ATC_PEL, (temp & VGA_AT13_FRESERVED) | mode->vm_att_pel);
	vga_r(VGA_IS1_RC), temp = vga_rattr(VGA_ATC_COLOR_PAGE);
	vga_r(VGA_IS1_RC), vga_wattr(VGA_ATC_COLOR_PAGE, (temp & VGA_AT14_FRESERVED) | mode->vm_att_color_page);
	vga_r(VGA_IS1_RC), vga_w(VGA_ATT_W, 0x20);

	temp = vga_r(VGA_MIS_R);
	vga_w(VGA_MIS_W, (temp & VGA_MIS_FRESERVED) | mode->vm_mis);

	temp = vga_rseq(VGA_SEQ_PLANE_WRITE);
	vga_wseq(VGA_SEQ_PLANE_WRITE, (temp & VGA_SR02_FRESERVED) | mode->vm_seq_plane_write);
	temp = vga_rseq(VGA_SEQ_CHARACTER_MAP);
	vga_wseq(VGA_SEQ_CHARACTER_MAP, (temp & VGA_SR03_FRESERVED) | mode->vm_seq_character_map);
	temp = vga_rseq(VGA_SEQ_MEMORY_MODE);
	vga_wseq(VGA_SEQ_MEMORY_MODE, (temp & VGA_SR04_FRESERVED) | mode->vm_seq_memory_mode);

	temp = vga_rgfx(VGA_GFX_SR_VALUE), vga_wgfx(VGA_GFX_SR_VALUE, (temp & VGA_GR00_FRESERVED) | mode->vm_gfx_sr_value);
	temp = vga_rgfx(VGA_GFX_SR_ENABLE), vga_wgfx(VGA_GFX_SR_ENABLE, (temp & VGA_GR01_FRESERVED) | mode->vm_gfx_sr_enable);
	temp = vga_rgfx(VGA_GFX_COMPARE_VALUE), vga_wgfx(VGA_GFX_COMPARE_VALUE, (temp & VGA_GR02_FRESERVED) | mode->vm_gfx_compare_value);
	temp = vga_rgfx(VGA_GFX_DATA_ROTATE), vga_wgfx(VGA_GFX_DATA_ROTATE, (temp & VGA_GR03_FRESERVED) | mode->vm_gfx_data_rotate);
	temp = vga_rgfx(VGA_GFX_MODE), vga_wgfx(VGA_GFX_MODE, (temp & VGA_GR05_FRESERVED) | mode->vm_gfx_mode);
	temp = vga_rgfx(VGA_GFX_MISC), vga_wgfx(VGA_GFX_MISC, (temp & VGA_GR06_FRESERVED) | mode->vm_gfx_misc);
	temp = vga_rgfx(VGA_GFX_COMPARE_MASK), vga_wgfx(VGA_GFX_COMPARE_MASK, (temp & VGA_GR07_FRESERVED) | mode->vm_gfx_compare_mask);
	vga_wgfx(VGA_GFX_BIT_MASK, mode->vm_gfx_bit_mask);

	/* Apply new graphics settings. */
	vga_wcrt(VGA_CRTC_H_TOTAL, mode->vm_crt_h_total);
	vga_wcrt(VGA_CRTC_H_DISP, mode->vm_crt_h_disp);
	vga_wcrt(VGA_CRTC_H_BLANK_START, mode->vm_crt_h_blank_start);
	vga_wcrt(VGA_CRTC_H_BLANK_END, mode->vm_crt_h_blank_end);
	vga_wcrt(VGA_CRTC_H_SYNC_START, mode->vm_crt_h_sync_start);
	vga_wcrt(VGA_CRTC_H_SYNC_END, mode->vm_crt_h_sync_end);
	vga_wcrt(VGA_CRTC_V_TOTAL, mode->vm_crt_v_total);
	vga_wcrt(VGA_CRTC_OVERFLOW, mode->vm_crt_overflow);
	temp = vga_rcrt(VGA_CRTC_PRESET_ROW);
	vga_wcrt(VGA_CRTC_PRESET_ROW, (temp & VGA_CR8_FRESERVED) | mode->vm_crt_preset_row);
	vga_wcrt(VGA_CRTC_MAX_SCAN, mode->vm_crt_max_scan);
	temp = vga_rcrt(VGA_CRTC_CURSOR_START);
	vga_wcrt(VGA_CRTC_CURSOR_START, (temp & VGA_CRA_FRESERVED) | mode->vm_crt_cursor_start);
	temp = vga_rcrt(VGA_CRTC_CURSOR_END);
	vga_wcrt(VGA_CRTC_CURSOR_END, (temp & VGA_CRB_FRESERVED) | mode->vm_crt_cursor_end);
	vga_wcrt(VGA_CRTC_START_HI, mode->vm_crt_start_hi);
	vga_wcrt(VGA_CRTC_START_LO, mode->vm_crt_start_lo);
	vga_wcrt(VGA_CRTC_CURSOR_HI, mode->vm_crt_cursor_hi);
	vga_wcrt(VGA_CRTC_CURSOR_LO, mode->vm_crt_cursor_lo);
	vga_wcrt(VGA_CRTC_V_SYNC_START, mode->vm_crt_v_sync_start);
	temp = vga_rcrt(VGA_CRTC_V_SYNC_END);
	vga_wcrt(VGA_CRTC_V_SYNC_END, (temp & VGA_CR11_FRESERVED) | mode->vm_crt_v_sync_end);
	vga_wcrt(VGA_CRTC_V_DISP_END, mode->vm_crt_v_disp_end);
	vga_wcrt(VGA_CRTC_OFFSET, mode->vm_crt_offset);
	vga_wcrt(VGA_CRTC_UNDERLINE, mode->vm_crt_underline);
	vga_wcrt(VGA_CRTC_V_BLANK_START, mode->vm_crt_v_blank_start);
	temp = vga_rcrt(VGA_CRTC_V_BLANK_END);
	vga_wcrt(VGA_CRTC_V_BLANK_END, (temp & VGA_CR16_FRESERVED) | mode->vm_crt_v_blank_end);
	temp = vga_rcrt(VGA_CRTC_MODE);
	vga_wcrt(VGA_CRTC_MODE, (temp & VGA_CR17_FRESERVED) | mode->vm_crt_mode);
	vga_wcrt(VGA_CRTC_LINE_COMPARE, mode->vm_crt_line_compare);

	/* Turn the screen back on. */
	vga_wseq(VGA_SEQ_RESET, 0x1);
	vga_wseq(VGA_SEQ_CLOCK_MODE,
	         (qr1 & VGA_SR01_FRESERVED) |
	         (mode->vm_seq_clock_mode & ~VGA_SR01_FSCREEN_OFF));
	vga_wseq(VGA_SEQ_RESET, 0x3);
}

PRIVATE ATTR_DBGTEXT void KCALL
VGA_GetMode(struct vga_mode *__restrict mode) {
	vga_r(VGA_IS1_RC), vga_w(VGA_ATT_W, 0x00);
	vga_r(VGA_IS1_RC), mode->vm_att_mode         = vga_rattr(VGA_ATC_MODE) & ~VGA_AT10_FRESERVED;
	vga_r(VGA_IS1_RC), mode->vm_att_overscan     = vga_rattr(VGA_ATC_OVERSCAN);
	vga_r(VGA_IS1_RC), mode->vm_att_plane_enable = vga_rattr(VGA_ATC_PLANE_ENABLE) & ~VGA_AT12_FRESERVED;
	vga_r(VGA_IS1_RC), mode->vm_att_pel          = vga_rattr(VGA_ATC_PEL) & ~VGA_AT13_FRESERVED;
	vga_r(VGA_IS1_RC), mode->vm_att_color_page   = vga_rattr(VGA_ATC_COLOR_PAGE) & ~VGA_AT14_FRESERVED;
	vga_r(VGA_IS1_RC), vga_w(VGA_ATT_W, 0x20);

	mode->vm_mis               = vga_r(VGA_MIS_R) & ~VGA_MIS_FRESERVED;
	mode->vm_gfx_sr_value      = vga_rgfx(VGA_GFX_SR_VALUE) & ~VGA_GR00_FRESERVED;
	mode->vm_gfx_sr_enable     = vga_rgfx(VGA_GFX_SR_ENABLE) & ~VGA_GR01_FRESERVED;
	mode->vm_gfx_compare_value = vga_rgfx(VGA_GFX_COMPARE_VALUE) & ~VGA_GR02_FRESERVED;
	mode->vm_gfx_data_rotate   = vga_rgfx(VGA_GFX_DATA_ROTATE) & ~VGA_GR03_FRESERVED;
	mode->vm_gfx_mode          = vga_rgfx(VGA_GFX_MODE) & ~VGA_GR05_FRESERVED;
	mode->vm_gfx_misc          = vga_rgfx(VGA_GFX_MISC) & ~VGA_GR06_FRESERVED;
	mode->vm_gfx_compare_mask  = vga_rgfx(VGA_GFX_COMPARE_MASK) & ~VGA_GR07_FRESERVED;
	mode->vm_gfx_bit_mask      = vga_rgfx(VGA_GFX_BIT_MASK);
	mode->vm_crt_h_total       = vga_rcrt(VGA_CRTC_H_TOTAL);
	mode->vm_crt_h_disp        = vga_rcrt(VGA_CRTC_H_DISP);
	mode->vm_crt_h_blank_start = vga_rcrt(VGA_CRTC_H_BLANK_START);
	mode->vm_crt_h_blank_end   = vga_rcrt(VGA_CRTC_H_BLANK_END);
	mode->vm_crt_h_sync_start  = vga_rcrt(VGA_CRTC_H_SYNC_START);
	mode->vm_crt_h_sync_end    = vga_rcrt(VGA_CRTC_H_SYNC_END);
	mode->vm_crt_v_total       = vga_rcrt(VGA_CRTC_V_TOTAL);
	mode->vm_crt_overflow      = vga_rcrt(VGA_CRTC_OVERFLOW);
	mode->vm_crt_preset_row    = vga_rcrt(VGA_CRTC_PRESET_ROW) & ~VGA_CR8_FRESERVED;
	mode->vm_crt_max_scan      = vga_rcrt(VGA_CRTC_MAX_SCAN);
	mode->vm_crt_cursor_start  = vga_rcrt(VGA_CRTC_CURSOR_START) & ~VGA_CRA_FRESERVED;
	mode->vm_crt_cursor_end    = vga_rcrt(VGA_CRTC_CURSOR_END) & ~VGA_CRB_FRESERVED;
	mode->vm_crt_start_hi      = vga_rcrt(VGA_CRTC_START_HI);
	mode->vm_crt_start_lo      = vga_rcrt(VGA_CRTC_START_LO);
	mode->vm_crt_cursor_hi     = vga_rcrt(VGA_CRTC_CURSOR_HI);
	mode->vm_crt_cursor_lo     = vga_rcrt(VGA_CRTC_CURSOR_LO);
	mode->vm_crt_v_sync_start  = vga_rcrt(VGA_CRTC_V_SYNC_START);
	mode->vm_crt_v_sync_end    = vga_rcrt(VGA_CRTC_V_SYNC_END) & ~VGA_CR11_FRESERVED;
	mode->vm_crt_v_disp_end    = vga_rcrt(VGA_CRTC_V_DISP_END);
	mode->vm_crt_offset        = vga_rcrt(VGA_CRTC_OFFSET);
	mode->vm_crt_underline     = vga_rcrt(VGA_CRTC_UNDERLINE);
	mode->vm_crt_v_blank_start = vga_rcrt(VGA_CRTC_V_BLANK_START);
	mode->vm_crt_v_blank_end   = vga_rcrt(VGA_CRTC_V_BLANK_END) & ~VGA_CR16_FRESERVED;
	mode->vm_crt_mode          = vga_rcrt(VGA_CRTC_MODE) & ~VGA_CR17_FRESERVED;
	mode->vm_crt_line_compare  = vga_rcrt(VGA_CRTC_LINE_COMPARE);
	mode->vm_seq_plane_write   = vga_rseq(VGA_SEQ_PLANE_WRITE) & ~VGA_SR02_FRESERVED;
	mode->vm_seq_character_map = vga_rseq(VGA_SEQ_CHARACTER_MAP) & ~VGA_SR03_FRESERVED;
	mode->vm_seq_memory_mode   = vga_rseq(VGA_SEQ_MEMORY_MODE) & ~VGA_SR04_FRESERVED;
	mode->vm_seq_clock_mode    = vga_rseq(VGA_SEQ_CLOCK_MODE) & ~VGA_SR01_FRESERVED;
}

PRIVATE ATTR_DBGTEXT void KCALL
VGA_SetPalette(struct vga_palette const *__restrict pal) {
	unsigned int i;
	vga_w(VGA_PEL_MSK, 0xff);
	vga_w(VGA_PEL_IW, 0x00);
	for (i = 0; i < 768; ++i)
		vga_w(VGA_PEL_D, ((u8 *)pal)[i] >> 2);
}

INTERN ATTR_DBGTEXT void KCALL
VGA_GetPalette(struct vga_palette *__restrict pal) {
	unsigned int i;
	vga_w(VGA_PEL_MSK, 0xff);
	vga_w(VGA_PEL_IR, 0x00);
	for (i = 0; i < 768; ++i)
		((u8 *)pal)[i] = vga_r(VGA_PEL_D) << 2;
}

//PRIVATE ATTR_DBGTEXT void KCALL
//VGA_SetFont(USER CHECKED struct vga_font const *__restrict font) {
//	vm_copytophys((vm_phys_t)VGA_VRAM_ADDR, font, sizeof(struct vga_font));
//}


#define VGA_WIDTH  80
#define VGA_HEIGHT 25

/* # of screens stored in the VGA backlog. */
#ifndef VGA_BACKLOG_NUMSCREENS
#define VGA_BACKLOG_NUMSCREENS   8
#endif /* !VGA_BACKLOG_NUMSCREENS */


PUBLIC_CONST ATTR_DBGRODATA unsigned int const dbg_scroll_maxline  = VGA_BACKLOG_NUMSCREENS * VGA_HEIGHT;
PUBLIC_CONST ATTR_DBGRODATA unsigned int const dbg_screen_width    = VGA_WIDTH;
PUBLIC_CONST ATTR_DBGRODATA unsigned int const dbg_screen_height   = VGA_HEIGHT;
PUBLIC_CONST ATTR_DBGRODATA unsigned int const dbg_screen_cellsize = 2;
PUBLIC ATTR_DBGDATA unsigned int dbg_tabsize;
PUBLIC ATTR_DBGDATA unsigned int dbg_indent;
PUBLIC ATTR_DBGDATA unsigned int dbg_newline_mode;

/* Terminal display backlog */
PRIVATE ATTR_DBGBSS u16 vga_terminal_backlog[VGA_BACKLOG_NUMSCREENS * VGA_WIDTH * VGA_HEIGHT];
#define vga_terminal_backlog_end COMPILER_ENDOF(vga_terminal_backlog)

/* [>= vga_terminal_backlog][< ENDOF(vga_terminal_backlog)]
 * Pointer to the next character to write.
 * NOTE: Always aligned to the start of a line. */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_backlog_cur;
/* Set to true once old data starts being overwritten. */
PRIVATE ATTR_DBGBSS bool vga_terminal_backlog_full;

/* Append a given line to the backlog */
#define VGA_TERMINAL_BACKLOG_ADDLINE(src)                       \
	(memcpyw(vga_terminal_backlog_cur, src, VGA_WIDTH),         \
	 vga_terminal_backlog_cur += VGA_WIDTH,                     \
	 vga_terminal_backlog_cur < vga_terminal_backlog_end        \
	 ? (void)0                                                  \
	 : (void)(vga_terminal_backlog_cur  = vga_terminal_backlog, \
	          vga_terminal_backlog_full = true))



PRIVATE ATTR_DBGBSS u16 *vga_terminal_start;   /* Terminal display start */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_end;     /* Terminal display end */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_cur;     /* Terminal display cursor */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_2ndln;   /* Start of the second line within the terminal display. */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_lastln;  /* Start of the last line within the terminal display. */
PRIVATE ATTR_DBGBSS bool vga_terminal_showcur; /* True if the current cursor position should be shown. */
PUBLIC  ATTR_DBGBSS u16  vga_terminal_attr ASMNAME("dbg_attr"); /* Color attributes. */
PUBLIC  ATTR_DBGBSS u16  vga_terminal_default_attr ASMNAME("dbg_default_attr"); /* Color attributes. */

#undef CONFIG_USE_HARDWARE_CURSOR
#define CONFIG_USE_HARDWARE_CURSOR 1


#define VGA_SETCUR(x, y) \
	(vga_terminal_cur = vga_terminal_start + (y)*VGA_WIDTH + (x))
#define VGA_GETCUR_X() ((unsigned int)(vga_terminal_cur - vga_terminal_start) % VGA_WIDTH)
#define VGA_GETCUR_Y() ((unsigned int)(vga_terminal_cur - vga_terminal_start) / VGA_WIDTH)


#define VGA_CHR(ch)        ((u16)(u8)(ch) | vga_terminal_attr)
#define VGA_EMPTY            VGA_CHR(' ')

#ifdef CONFIG_USE_HARDWARE_CURSOR
PRIVATE ATTR_DBGBSS bool vga_cursor_is_shown = false;
LOCAL ATTR_DBGTEXT void KCALL vga_enable_cursor(void) {
	if (!vga_cursor_is_shown) {
		vga_wcrt(VGA_CRTC_CURSOR_START,
		         vga_rcrt(VGA_CRTC_CURSOR_START) & ~(VGA_CRA_FCURSOR_DISABLE));
		vga_cursor_is_shown = true;
	}
}

LOCAL ATTR_DBGTEXT void KCALL vga_disable_cursor(void) {
	if (vga_cursor_is_shown) {
		vga_wcrt(VGA_CRTC_CURSOR_START,
		         vga_rcrt(VGA_CRTC_CURSOR_START) | VGA_CRA_FCURSOR_DISABLE);
		vga_cursor_is_shown = false;
	}
}

PRIVATE ATTR_DBGTEXT void KCALL vga_update_cursor_pos(void) {
	if (vga_terminal_cur >= vga_terminal_end) {
		vga_disable_cursor();
	} else {
		unsigned int pos;
		pos = (unsigned int)(vga_terminal_cur - vga_terminal_start);
		vga_wcrt(VGA_CRTC_CURSOR_HI, (pos >> 8));
		vga_wcrt(VGA_CRTC_CURSOR_LO, (u8)pos);
		vga_enable_cursor();
	}
}

#define VGA_SHOWCURSOR_ON()   vga_update_cursor_pos()
#define VGA_SHOWCURSOR_OFF() (void)0
#else /* CONFIG_USE_HARDWARE_CURSOR */
#define VGA_SHOWCURSOR_ON()                       \
	(void)((vga_terminal_cur >= vga_terminal_end) \
	       ? 0                                    \
	       : ((u8 *)vga_terminal_cur)[1] = (u8)((u8)0xff - ((u8 *)vga_terminal_cur)[1]))
#define VGA_SHOWCURSOR_OFF()  VGA_SHOWCURSOR_ON()
#endif /* !CONFIG_USE_HARDWARE_CURSOR */


PRIVATE ATTR_DBGBSS u16 vga_backlog_screen[VGA_WIDTH * VGA_HEIGHT];
PRIVATE ATTR_DBGBSS unsigned int vga_backlog_scrollpos;
#define vga_backlog_scrollmax  \
   (vga_terminal_backlog_full ? (VGA_BACKLOG_NUMSCREENS * VGA_HEIGHT) : \
   (unsigned int)((size_t)(vga_terminal_backlog_cur - vga_terminal_backlog) / VGA_WIDTH))


PRIVATE ATTR_DBGTEXT void
NOTHROW(KCALL vga_backlog_setscrollpos)(unsigned int pos) {
	size_t backlog_offset;
	if (!pos) {
		/* Scroll to the bottom. */
		memcpyw(vga_terminal_start,
		        vga_backlog_screen,
		        VGA_WIDTH * VGA_HEIGHT);
		vga_backlog_scrollpos = 0;
		return;
	}
	/* Start scrolling */
	if (!vga_backlog_scrollpos) {
		memcpyw(vga_backlog_screen,
		        vga_terminal_start,
		        VGA_WIDTH * VGA_HEIGHT);
	}
	/* Copy the relevant section on-screen. */
	backlog_offset = (size_t)pos * VGA_WIDTH;
	if (pos < VGA_HEIGHT) {
		u16 *backlog_src;
		/* Part of the active screen is still visible */
		memcpyw(vga_terminal_start + backlog_offset,
		        vga_backlog_screen,
		        (VGA_HEIGHT - pos) * VGA_WIDTH);
		backlog_src = vga_terminal_backlog_cur - backlog_offset;
		if (backlog_src >= vga_terminal_backlog) {
			memcpyw(vga_terminal_start,
			        backlog_src,
			        backlog_offset);
		} else {
			size_t num_leading, num_trailing;
			num_leading  = (size_t)(vga_terminal_backlog_cur - vga_terminal_backlog);
			num_trailing = (size_t)(backlog_offset - num_leading);
			memcpyw(vga_terminal_start, vga_terminal_backlog_end - num_trailing, num_trailing);
			memcpyw(vga_terminal_start + num_trailing, vga_terminal_backlog, num_leading);
		}
	} else {
		/* Only the backlog is visible. */
		u16 *visible_start, *visible_end;
		visible_start = vga_terminal_backlog_cur - backlog_offset;
		visible_end   = visible_start + (VGA_WIDTH * VGA_HEIGHT);
		if (visible_end < vga_terminal_backlog) {
			visible_start += VGA_BACKLOG_NUMSCREENS * VGA_WIDTH * VGA_HEIGHT;
			visible_end += VGA_BACKLOG_NUMSCREENS * VGA_WIDTH * VGA_HEIGHT;
		}
		assert(visible_end >= vga_terminal_backlog);
		if (visible_start >= vga_terminal_backlog) {
			memcpyw(vga_terminal_start, visible_start, VGA_WIDTH * VGA_HEIGHT);
		} else {
			size_t num_leading, num_trailing;
			num_leading  = (size_t)(vga_terminal_backlog - visible_start);
			num_trailing = (size_t)(backlog_offset - num_leading);
			assertf(num_trailing < COMPILER_LENOF(vga_terminal_backlog), "num_trailing = %Iu\n", num_trailing);
			assertf(num_leading < COMPILER_LENOF(vga_terminal_backlog), "num_leading = %Iu\n", num_leading);
			memcpyw(vga_terminal_start, vga_terminal_backlog_end - num_trailing, num_trailing);
			memcpyw(vga_terminal_start + num_trailing, vga_terminal_backlog, num_leading);
		}
	}
	vga_backlog_scrollpos = pos;
#if 1
	{
		/* Display the current scroll position in the bottom-right corner. */
		char buf[64];
		u16 *dest;
		unsigned int i, len;
		unsigned int maxpos = vga_backlog_scrollmax;
		len = (unsigned int)sprintf(buf, "%u/%u",
		                            maxpos - pos,
		                            maxpos);
		dest = vga_terminal_end - len;
		for (i = 0; i < len; ++i) {
			dest[i] = (u16)(u8)buf[i] | DBG_COLOR_ATTR(DBG_COLOR_LIGHT_GRAY,
			                                           DBG_COLOR_DARK_GRAY);
		}
	}
#endif
}



PUBLIC ATTR_DBGTEXT unsigned int
NOTHROW(KCALL dbg_scroll)(unsigned int cmd, unsigned int pos) {
	unsigned int maxpos;
	if (cmd == DBG_SCROLL_CMD_GET)
		return vga_backlog_scrollpos;
	if (!pos) {
set_pos_0:
		if (vga_backlog_scrollpos) {
			vga_backlog_setscrollpos(0);
			if (vga_terminal_showcur)
				VGA_SHOWCURSOR_ON();
		}
		goto done;
	}
	maxpos = vga_backlog_scrollmax;
	if (pos > maxpos) {
		pos = maxpos;
		if (!pos)
			goto set_pos_0;
	}
	if (pos != vga_backlog_scrollpos) {
		if (!vga_backlog_scrollpos && vga_terminal_showcur) {
#ifdef CONFIG_USE_HARDWARE_CURSOR
			vga_disable_cursor();
#else
			VGA_SHOWCURSOR_OFF();
#endif
		}
		vga_backlog_setscrollpos(pos);
	}
done:
	return pos;
}

/* Set if the current cursor position should be visible.
 * @return: true:  The cursor is (now) visible.
 * @return: false: The cursor is (now) hidden. */
PUBLIC ATTR_DBGTEXT bool
NOTHROW(KCALL dbg_setcur_visible)(unsigned int cmd) {
	switch (cmd) {

	case DBG_SETCUR_VISIBLE_HIDE:
		if (vga_terminal_showcur) {
			if (!vga_backlog_scrollpos) {
#ifdef CONFIG_USE_HARDWARE_CURSOR
				vga_disable_cursor();
#else
				VGA_SHOWCURSOR_OFF();
#endif
			}
			vga_terminal_showcur = false;
		}
		break;

	case DBG_SETCUR_VISIBLE_SHOW:
		if (!vga_terminal_showcur) {
			if (!vga_backlog_scrollpos)
				VGA_SHOWCURSOR_ON();
			vga_terminal_showcur = true;
		}
		break;

	default: break;
	}
	return vga_terminal_showcur;
}

/* Get/Set the current on-screen cursor position. */
PUBLIC ATTR_DBGTEXT u32
NOTHROW(KCALL dbg_setcur)(int x, int y) {
	unsigned int pos;
	if (x < 0)
		x = 0;
	else if (x >= VGA_WIDTH) {
		x = VGA_WIDTH - 1;
	}
	if (y < 0)
		y = 0;
	else if (y >= VGA_WIDTH) {
		y = VGA_WIDTH - 1;
	}
	if (vga_backlog_scrollpos) {
		vga_backlog_setscrollpos(0);
	}
#ifndef CONFIG_USE_HARDWARE_CURSOR
	else {
		if (vga_terminal_showcur)
			VGA_SHOWCURSOR_OFF();
	}
#endif
	pos = (unsigned int)x + (unsigned int)y * VGA_WIDTH;
	vga_terminal_cur = vga_terminal_start + pos;
	if (vga_terminal_showcur)
		VGA_SHOWCURSOR_ON();
	return ((u32)(pos % VGA_WIDTH) |
	        (u32)(pos / VGA_WIDTH) << 16);
}

PUBLIC ATTR_DBGTEXT u32
NOTHROW(KCALL dbg_getcur)(void) {
	unsigned int pos;
	pos = (unsigned int)(vga_terminal_cur - vga_terminal_start);
	return ((u32)(pos % VGA_WIDTH) |
	        (u32)(pos / VGA_WIDTH) << 16);
}


LOCAL ATTR_DBGTEXT void
NOTHROW(KCALL scroll_down_if_cur_end)(void) {
	if (vga_terminal_cur >= vga_terminal_end) {
		/* Scroll down */
		VGA_TERMINAL_BACKLOG_ADDLINE(vga_terminal_start);
		memmovew(vga_terminal_start, vga_terminal_2ndln,
		         (VGA_HEIGHT - 1) * VGA_WIDTH);
		memsetw(vga_terminal_lastln + 1, VGA_EMPTY, VGA_WIDTH - 1);
		vga_terminal_cur = vga_terminal_lastln + dbg_indent;
	}
}




/* The number of missing UTF-8 character bytes. */
PRIVATE ATTR_DBGBSS unsigned int dbg_utf8_curlen;
PRIVATE ATTR_DBGBSS u8 dbg_utf8_pending[8]; /* Pending UTF-8 characters. */


LOCAL ATTR_DBGTEXT u32 KCALL
dbg_utf8_pending_ch32(u8 seqlen) {
	u32 result;
	result = (u32)dbg_utf8_pending[0];
	switch (seqlen) {

	case 0:
	case 1:
		break;

	case 2:
		result = (result & 0x1f) << 6;
		result |= (dbg_utf8_pending[1] & 0x3f);
		break;

	case 3:
		result = (result & 0x0f) << 12;
		result |= (dbg_utf8_pending[1] & 0x3f) << 6;
		result |= (dbg_utf8_pending[2] & 0x3f);
		break;

	case 4:
		result = (result & 0x07) << 18;
		result |= (dbg_utf8_pending[1] & 0x3f) << 12;
		result |= (dbg_utf8_pending[2] & 0x3f) << 6;
		result |= (dbg_utf8_pending[3] & 0x3f);
		break;

	case 5:
		result = (result & 0x03) << 24;
		result |= (dbg_utf8_pending[1] & 0x3f) << 18;
		result |= (dbg_utf8_pending[2] & 0x3f) << 12;
		result |= (dbg_utf8_pending[3] & 0x3f) << 6;
		result |= (dbg_utf8_pending[4] & 0x3f);
		break;

	case 6:
		result = (result & 0x01) << 30;
		result |= (dbg_utf8_pending[1] & 0x3f) << 24;
		result |= (dbg_utf8_pending[2] & 0x3f) << 18;
		result |= (dbg_utf8_pending[3] & 0x3f) << 12;
		result |= (dbg_utf8_pending[4] & 0x3f) << 6;
		result |= (dbg_utf8_pending[5] & 0x3f);
		break;

	case 7:
		result = (dbg_utf8_pending[1] & 0x03 /*0x3f*/) << 30;
		result |= (dbg_utf8_pending[2] & 0x3f) << 24;
		result |= (dbg_utf8_pending[3] & 0x3f) << 18;
		result |= (dbg_utf8_pending[4] & 0x3f) << 12;
		result |= (dbg_utf8_pending[5] & 0x3f) << 6;
		result |= (dbg_utf8_pending[6] & 0x3f);
		break;

	case 8:
		/*result = (result & 0x3f) << 36;*/
		result = (dbg_utf8_pending[1] & 0x03 /*0x3f*/) << 30;
		result |= (dbg_utf8_pending[2] & 0x3f) << 24;
		result |= (dbg_utf8_pending[3] & 0x3f) << 18;
		result |= (dbg_utf8_pending[4] & 0x3f) << 12;
		result |= (dbg_utf8_pending[5] & 0x3f) << 6;
		result |= (dbg_utf8_pending[6] & 0x3f);
		break;

	default:
		__builtin_unreachable();
	}
	return result;
}



/* I/O within the debugger. */
PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_bell)(void) {
	/* TODO: Visual bell */
}
PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_putc)(/*utf-8*/char ch) {
	if (dbg_utf8_curlen) {
		/* Continue a utf-8 sequence. */
		u8 reqlen = unicode_utf8seqlen[dbg_utf8_pending[0]];
		if unlikely(((u8)ch & 0xc0) != 0x80) {
			/* Incomplete utf-8 sequence... */
			dbg_putuni(dbg_utf8_pending_ch32(dbg_utf8_curlen));
			dbg_utf8_curlen = 0;
			goto normal_ch;
		} else {
			dbg_utf8_pending[dbg_utf8_curlen] = (u8)ch;
			++dbg_utf8_curlen;
			if (dbg_utf8_curlen >= reqlen) {
				dbg_putuni(dbg_utf8_pending_ch32(reqlen));
				dbg_utf8_curlen = 0;
			}
		}
	} else {
normal_ch:
		if ((u8)ch < 0xc0) {
			/* Unicode pass-through character. */
			dbg_putuni((u32)(u8)ch);
		} else {
			/* Start a new utf-8 sequence. */
			dbg_utf8_pending[0] = (u8)ch;
			dbg_utf8_curlen     = 1;
		}
	}
}


#ifdef __INTELLISENSE__
/* Encode the given unicode character `ch' using cp437 (the codepage used by VGA)
 * If the character can't be encoded, return 0 instead.
 * s.a.: https://en.wikipedia.org/wiki/Code_page_437  */
LOCAL ATTR_DBGTEXT u8 NOTHROW(KCALL cp437_encode)(/*utf-32*/u32 ch);
#else
#include "cp437_encode.c.inl"
#endif

PUBLIC ATTR_DBGTEXT NONNULL((5)) void KCALL
dbg_getscreendata(int x, int y,
                  unsigned int size_x,
                  unsigned int size_y,
                  void *__restrict buf) {
	u16 *screen;
	int x_end, y_end;
	if unlikely(!size_x || !size_y)
		return;
	x_end = x + size_x;
	y_end = y + size_y;
	if unlikely(y >= VGA_HEIGHT || x >= VGA_WIDTH ||
	            x_end < 0 || y_end < 0) {
		memsetw((u16 *)buf, VGA_EMPTY, size_x * size_y);
		return;
	}
	if (y < 0) {
		memsetw((u16 *)buf, VGA_EMPTY, size_x * (unsigned int)-y);
		size_y += y;
		y = 0;
	}
	if ((unsigned int)y_end > VGA_HEIGHT) {
		memsetw((u16 *)buf + VGA_HEIGHT * size_x, VGA_EMPTY,
		        ((unsigned int)y_end - VGA_HEIGHT) * size_x);
		y_end  = VGA_HEIGHT;
		size_y = VGA_HEIGHT - y;
	}
	screen = vga_backlog_scrollpos
	         ? vga_backlog_screen
	         : vga_terminal_start;
#ifndef CONFIG_USE_HARDWARE_CURSOR
	if (!vga_backlog_scrollpos && vga_terminal_showcur)
		VGA_SHOWCURSOR_OFF();
#endif
	screen += y * VGA_WIDTH;
	if (x == 0 && size_x == VGA_WIDTH) {
		memcpyw(buf, screen, size_y * VGA_WIDTH);
	} else {
		unsigned int xhead, xcopy, xtail;
		xcopy = size_x;
		xtail = xhead = 0;
		if (x < 0) {
			xhead = (unsigned int)-x;
			xcopy -= xhead;
		} else {
			screen += x;
		}
		if (xcopy > VGA_WIDTH) {
			xtail = VGA_WIDTH - xcopy;
			xcopy = VGA_WIDTH;
		}
		while (size_y--) {
			buf = mempsetw(buf, VGA_EMPTY, xhead);
			buf = mempcpyw(buf, screen, xcopy);
			buf = mempsetw(buf, VGA_EMPTY, xtail);
			screen += VGA_WIDTH;
		}
	}
#ifndef CONFIG_USE_HARDWARE_CURSOR
	if (!vga_backlog_scrollpos && vga_terminal_showcur)
		VGA_SHOWCURSOR_ON();
#endif
}


PUBLIC ATTR_DBGTEXT NONNULL((5)) void KCALL
dbg_setscreendata(int x, int y,
                  unsigned int size_x,
                  unsigned int size_y,
                  void const *__restrict buf) {
	u16 *screen;
	int x_end, y_end;
	if unlikely(vga_backlog_scrollpos)
		vga_backlog_setscrollpos(0);
#ifndef CONFIG_USE_HARDWARE_CURSOR
	else {
		if (vga_terminal_showcur)
			VGA_SHOWCURSOR_OFF();
	}
#endif
	if unlikely(!size_x || !size_y)
		goto done;
	x_end = x + size_x;
	y_end = y + size_y;
	if unlikely(y >= VGA_HEIGHT || x >= VGA_WIDTH ||
	            x_end < 0 || y_end < 0)
		goto done;
	if (y < 0) {
		size_y += y;
		y = 0;
	}
	if ((unsigned int)y_end > VGA_HEIGHT) {
		y_end  = VGA_HEIGHT;
		size_y = VGA_HEIGHT - y;
	}
	screen = vga_backlog_scrollpos
	         ? vga_backlog_screen
	         : vga_terminal_start;
	screen += y * VGA_WIDTH;
	if (x == 0 && size_x == VGA_WIDTH) {
		memcpyw(screen, buf, size_y * VGA_WIDTH);
	} else {
		unsigned int xhead, xcopy, xtail;
		xcopy = size_x;
		xtail = xhead = 0;
		if (x < 0) {
			xhead = (unsigned int)-x;
			xcopy -= xhead;
		} else {
			screen += x;
		}
		if (xcopy > VGA_WIDTH) {
			xtail = VGA_WIDTH - xcopy;
			xcopy = VGA_WIDTH;
		}
		while (size_y--) {
			buf = (u16 *)buf + xhead;
			mempcpyw(screen, buf, xcopy);
			buf = (u16 *)buf + xcopy + xtail;
			screen += VGA_WIDTH;
		}
	}
done:
#ifndef CONFIG_USE_HARDWARE_CURSOR
	if (vga_terminal_showcur)
		VGA_SHOWCURSOR_ON();
#endif
	;
}


#define UNENCODABLE_START  "["
#define UNENCODABLE_END    "]"
#define UNENCODABLE(x)     UNENCODABLE_START x UNENCODABLE_END

PRIVATE ATTR_DBGBSS bool vfa_last_chr_caused_linewrap = false;

LOCAL ATTR_DBGTEXT void
NOTHROW(KCALL dbg_putcp437)(/*cp-437*/u8 ch) {
	/* VGA terminal output */
	scroll_down_if_cur_end();
	/* When indent-mode is active, wraps to the next line */
	if (dbg_indent != 0 && vfa_last_chr_caused_linewrap &&
	    !(dbg_newline_mode & DBG_NEWLINE_MODE_NOWRAP) && VGA_GETCUR_X() == 0)
		vga_terminal_cur += dbg_indent;
	*vga_terminal_cur = VGA_CHR(ch);
	if (dbg_newline_mode & DBG_NEWLINE_MODE_NOWRAP) {
		if (VGA_GETCUR_X() != VGA_WIDTH - 1)
			++vga_terminal_cur;
		vfa_last_chr_caused_linewrap = false;
	} else {
		++vga_terminal_cur;
		vfa_last_chr_caused_linewrap = VGA_GETCUR_X() == 0;
	}
}

PRIVATE ATTR_DBGTEXT ATTR_NOINLINE NONNULL((1)) void
NOTHROW(KCALL dbg_putcp437_s)(/*cp-437*/char const *__restrict str) {
	char ch;
	while ((ch = *str++) != '\0')
		dbg_putcp437(ch);
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_fillscreen)(/*utf-32*/u32 ch) {
	u8 cp_ch;
	if unlikely(vga_backlog_scrollpos)
		vga_backlog_setscrollpos(0);
#ifndef CONFIG_USE_HARDWARE_CURSOR
	else {
		if (vga_terminal_showcur)
			VGA_SHOWCURSOR_OFF();
	}
#endif
	cp_ch = cp437_encode(ch);
	if (!cp_ch)
		cp_ch = '?';
	memsetw(vga_terminal_start,
	        VGA_CHR(cp_ch),
	        VGA_WIDTH * VGA_HEIGHT);
	vga_terminal_cur             = vga_terminal_start;
	vfa_last_chr_caused_linewrap = false;
}


PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_fillrect)(int x, int y, unsigned int size_x, unsigned int size_y, /*utf-32*/u32 ch) {
	if (!size_x || !size_y) {
		if unlikely(vga_backlog_scrollpos)
			vga_backlog_setscrollpos(0);
		return;
	}
	dbg_hline(x, y, size_x, ch);
	if (size_y > 1)
		dbg_hline(x, y + size_y - 1, size_x, ch);
	if (size_y > 2) {
		dbg_vline(x, y + 1, size_y - 2, ch);
		if (size_x > 1)
			dbg_vline(x + size_x - 1, y + 1, size_y - 2, ch);
	}
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_fillrect2)(int x, int y, unsigned int size_x, unsigned int size_y,
                             /*utf-32*/u32 tl, /*utf-32*/u32 t, /*utf-32*/u32 tr,
                             /*utf-32*/u32 l, /*utf-32*/u32 r,
                             /*utf-32*/u32 bl, /*utf-32*/u32 b, /*utf-32*/u32 br) {
	if (!size_x || !size_y) {
		if unlikely(vga_backlog_scrollpos)
			vga_backlog_setscrollpos(0);
		return;
	}
	dbg_pputuni(x, y, tl);
	if (size_x > 1)
		dbg_pputuni(x + size_x - 1, y, tr);
	if (size_y > 1) {
		dbg_pputuni(x, y + size_y - 1, bl);
		if (size_x > 1)
			dbg_pputuni(x + size_x - 1, y + size_y - 1, br);
	}
	if (size_x > 2) {
		dbg_hline(x + 1, y, size_x - 2, t);
		dbg_hline(x + 1, y + size_y - 1, size_x - 2, b);
		if (size_y > 2) {
			dbg_vline(x, y + 1, size_y - 2, l);
			dbg_vline(x + size_x - 1, y + 1, size_y - 2, r);
		}
	}
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_hline)(int x, int y, unsigned int size_x, /*utf-32*/ u32 ch) {
	u8 cp_ch;
	if unlikely(vga_backlog_scrollpos)
		vga_backlog_setscrollpos(0);
#ifndef CONFIG_USE_HARDWARE_CURSOR
	else {
		if (vga_terminal_showcur)
			VGA_SHOWCURSOR_OFF();
	}
#endif
	if unlikely(!size_x)
		goto done;
	if unlikely(y < 0 || y >= VGA_HEIGHT)
		goto done;
	if unlikely(x >= VGA_WIDTH)
		goto done;
	if (x < 0) {
		x = -x;
		if (size_x <= (unsigned int)x)
			goto done;
		size_x -= (unsigned int)x;
		x = 0;
	}
	cp_ch = cp437_encode(ch);
	if (!cp_ch)
		cp_ch = '?';
	memsetw(vga_terminal_start +
	        (unsigned int)x +
	        (unsigned int)y * VGA_WIDTH,
	        VGA_CHR(cp_ch),
	        size_x);
done:
#ifndef CONFIG_USE_HARDWARE_CURSOR
	if (vga_terminal_showcur)
		VGA_SHOWCURSOR_ON();
#endif
	;
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_vline)(int x, int y, unsigned int size_y, /*utf-32*/ u32 ch) {
	u8 cp_ch;
	unsigned int i;
	u16 *dst, vga_ch;
	if unlikely(vga_backlog_scrollpos)
		vga_backlog_setscrollpos(0);
#ifndef CONFIG_USE_HARDWARE_CURSOR
	else {
		if (vga_terminal_showcur)
			VGA_SHOWCURSOR_OFF();
	}
#endif
	if unlikely(!size_y)
		goto done;
	if unlikely(y >= VGA_HEIGHT)
		goto done;
	if unlikely(x < 0 || x >= VGA_WIDTH)
		goto done;
	if (y < 0) {
		y = -y;
		if (size_y <= (unsigned int)y)
			goto done;
		size_y -= (unsigned int)y;
		y = 0;
	}
	cp_ch = cp437_encode(ch);
	if (!cp_ch)
		cp_ch = '?';
	vga_ch = VGA_CHR(cp_ch);
	dst    = vga_terminal_start + (unsigned int)x + (unsigned int)y * VGA_WIDTH;
	for (i = 0; i < size_y; ++i) {
		*dst = vga_ch;
		dst += VGA_WIDTH;
	}
done:
#ifndef CONFIG_USE_HARDWARE_CURSOR
	if (vga_terminal_showcur)
		VGA_SHOWCURSOR_ON();
#endif
	;
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_fillbox)(int x, int y,
                           unsigned int size_x,
                           unsigned int size_y,
                           /*utf-32*/ u32 ch) {
	u8 cp_ch;
	int x_end, y_end;
	u16 *screen;
	if unlikely(vga_backlog_scrollpos)
		vga_backlog_setscrollpos(0);
#ifndef CONFIG_USE_HARDWARE_CURSOR
	else {
		if (vga_terminal_showcur)
			VGA_SHOWCURSOR_OFF();
	}
#endif
	if unlikely(!size_x || !size_y)
		goto done;
	x_end = x + size_x;
	y_end = y + size_y;
	if unlikely(y >= VGA_HEIGHT || x >= VGA_WIDTH ||
	            x_end < 0 || y_end < 0)
		goto done;
	if (y < 0) {
		size_y += y;
		y = 0;
	}
	if ((unsigned int)y_end > VGA_HEIGHT) {
		y_end  = VGA_HEIGHT;
		size_y = VGA_HEIGHT - y;
	}
	screen = vga_terminal_start;
	screen += y * VGA_WIDTH;
	cp_ch = cp437_encode(ch);
	if (!cp_ch)
		cp_ch = '?';
	if (x == 0 && size_x == VGA_WIDTH) {
		memsetw(screen, VGA_CHR(cp_ch), size_y * VGA_WIDTH);
	} else {
		if (x < 0) {
			size_x -= (unsigned int)-x;
		} else {
			screen += x;
		}
		if (size_x > VGA_WIDTH)
			size_x = VGA_WIDTH;
		while (size_y--) {
			mempsetw(screen, VGA_CHR(cp_ch), size_x);
			screen += VGA_WIDTH;
		}
	}
done:
#ifndef CONFIG_USE_HARDWARE_CURSOR
	if (vga_terminal_showcur)
		VGA_SHOWCURSOR_ON();
#endif
	;
}






PRIVATE ATTR_DBGBSS u32 dbg_last_character;
LOCAL ATTR_DBGTEXT void NOTHROW(KCALL dbg_do_putuni)(/*utf-32*/u32 ch) {
	u8 cp_ch;
#if 1
	{
		INTDEF port_t debug_port;
		if (debug_port) {
			char buf[UNICODE_UTF8_CURLEN];
			size_t buflen = (size_t)(unicode_writeutf8(buf, ch) - buf);
			outsb(debug_port, buf, buflen);
		}
	}
#endif
	/* Scroll to bottom before printing a character. */
	if unlikely(vga_backlog_scrollpos)
		vga_backlog_setscrollpos(0);
#ifndef CONFIG_USE_HARDWARE_CURSOR
	else {
		if (vga_terminal_showcur)
			VGA_SHOWCURSOR_OFF();
	}
#endif
	cp_ch = cp437_encode(ch);
	if (cp_ch) {
		dbg_putcp437(cp_ch);
	} else {
		switch (ch) {

		case '\t': {
			unsigned int cur_x;
			unsigned int num_space;
			unsigned int max_space;
			scroll_down_if_cur_end();
			cur_x     = VGA_GETCUR_X();
			num_space = dbg_tabsize - (cur_x % dbg_tabsize);
			max_space = VGA_WIDTH - cur_x;
			if (num_space > max_space)
				num_space = max_space;
			/* Output space characters. */
			memsetw(vga_terminal_cur, VGA_EMPTY, num_space);
			vga_terminal_cur += num_space;
		}	break;

		case '\b':
			if (vga_terminal_cur > vga_terminal_start) {
				--vga_terminal_cur;
				vfa_last_chr_caused_linewrap = false;
			}
			break;

		case '\r':
			/* Return to the start of the current line. */
			if (dbg_newline_mode & DBG_NEWLINE_MODE_CLRFREE)
				memsetw(vga_terminal_cur, VGA_EMPTY, VGA_WIDTH - VGA_GETCUR_X());
			VGA_SETCUR(dbg_indent, VGA_GETCUR_Y());
			break;

		case '\n':
			if (VGA_GETCUR_X() <= dbg_indent &&
			    cp437_encode(dbg_last_character) != 0) {
				/* Special case: The previous line was filled entirely, and the cursor had to be wrapped
				 *               to the next line, however the first character then printed was also a
				 *               linefeed. - In this case, don't wrap the line, as the linefeed requested
				 *               by the caller already happened implicitly, thus not creating an entirely
				 *               empty line and wasting what little screen space we only have. */
			} else {
				/* Clear the remainder of the old line */
				if (dbg_newline_mode & DBG_NEWLINE_MODE_CLRFREE)
					memsetw(vga_terminal_cur, VGA_EMPTY, VGA_WIDTH - VGA_GETCUR_X());
				if (vga_terminal_cur >= vga_terminal_lastln) {
					/* Scroll down */
					VGA_TERMINAL_BACKLOG_ADDLINE(vga_terminal_start);
					memmovew(vga_terminal_start, vga_terminal_2ndln,
					         (VGA_HEIGHT - 1) * VGA_WIDTH);
					memsetw(vga_terminal_lastln, VGA_EMPTY, VGA_WIDTH);
					vga_terminal_cur = vga_terminal_lastln + dbg_indent;
				} else {
					VGA_SETCUR(dbg_indent, VGA_GETCUR_Y() + 1);
				}
				vfa_last_chr_caused_linewrap = false;
			}
			break;

		default: {
			char buf[32];
			if (ch <= 0x1f || ch == 0x7f) {
				sprintf(buf, "^%c", ch + '@');
			} else {
				sprintf(buf, UNENCODABLE_START "U+%I32X" UNENCODABLE_END, ch);
			}
			dbg_putcp437_s(buf);
		}	break;
		}
	}
	if (vga_terminal_showcur)
		VGA_SHOWCURSOR_ON();
	dbg_last_character = ch;
}



/* TODO: Use libtty instead of this! */

/* Escape commands */
#define ANSI_CUU  'A' /* Cursor up. */
#define ANSI_CUD  'B' /* Cursor down. */
#define ANSI_CUF  'C' /* Cursor forward. */
#define ANSI_CUB  'D' /* Cursor back. */
#define ANSI_CNL  'E' /* Cursor next line. */
#define ANSI_CPL  'F' /* Cursor previous line. */
#define ANSI_CHA  'G' /* Cursor horizontal absolute. */
#define ANSI_CVA  'b' /* Cursor vertical absolute. */
#define ANSI_CUP  'H' /* Cursor position. */
#define ANSI_HVP  'f' /* Cursor position. */
#define ANSI_ED   'J' /* Erase data. */
#define ANSI_EL   'K' /* Erase in line. */
#define ANSI_SU   'S' /* Scroll up. */
#define ANSI_SD   'T' /* Scroll down. */
#define ANSI_SGR  'm' /* Select graphic rendition. */
#define ANSI_DSR  'n' /* Device status report. */
#define ANSI_SCP  's' /* Save cursor position. */
#define ANSI_RCP  'u' /* Restore cursor position. */
#define ANSI_HIDE 'l' /* DECTCEM - Hide Cursor. */
#define ANSI_SHOW 'h' /* DECTCEM - Show Cursor. */

PRIVATE ATTR_DBGBSS char dbg_ansi_escapebuf[128];
PRIVATE ATTR_DBGBSS size_t dbg_ansi_escapelen;
PRIVATE ATTR_DBGBSS u32 dbg_saved_cursor_position;

#define TERM_CLS_AFTER    0 /* Clear everything after the cursor (including the cursor itself). */
#define TERM_CLS_BEFORE   1 /* Clear everything before the cursor (excluding the cursor itself). */
#define TERM_CLS_ALL      2 /* Clear everything. */
#define TERM_CLS_ALLPAGES 3 /* Clear everything including the scroll-back buffers. */

#define TERM_EL_AFTER     0 /* Erase the line after the cursor (including the cursor itself). */
#define TERM_EL_BEFORE    1 /* Erase the line before the cursor (excluding the cursor itself). */
#define TERM_EL_ALL       2 /* Erase the line. */

PRIVATE ATTR_DBGTEXT void
NOTHROW(KCALL dbg_ansi_process)(int *pcur_x,
                                int *pcur_y) {
	dbg_getcur();
	if (dbg_ansi_escapebuf[1] == '[') {
		size_t argc;
		unsigned int argv[3];
		char mode;
		argc = sscanf(dbg_ansi_escapebuf + 2, "%u;%u;%u",
		              &argv[0], &argv[1], &argv[2]);
		mode = dbg_ansi_escapebuf[dbg_ansi_escapelen - 1];
		switch (mode) {

		case ANSI_CUU: /* Cursor up. */
			if (pcur_y) {
				*pcur_y -= (argc ? argv[0] : 1);
			} else {
				u32 pos = dbg_getcur();
				dbg_setcur((int)DBG_GETCUR_X(pos),
				           (int)DBG_GETCUR_Y(pos) - (argc ? argv[0] : 1));
			}
			break;

		case ANSI_CUD: /* Cursor down. */
			if (pcur_y) {
				*pcur_y += (argc ? argv[0] : 1);
			} else {
				u32 pos = dbg_getcur();
				dbg_setcur((int)DBG_GETCUR_X(pos),
				           (int)DBG_GETCUR_Y(pos) + (argc ? argv[0] : 1));
			}
			break;

		case ANSI_CUF: /* Cursor forward. */
			if (pcur_x) {
				*pcur_x += (argc ? argv[0] : 1);
			} else {
				u32 pos = dbg_getcur();
				dbg_setcur((int)DBG_GETCUR_X(pos) + (argc ? argv[0] : 1),
				           (int)DBG_GETCUR_Y(pos));
			}
			break;

		case ANSI_CUB: /* Cursor back. */
			if (pcur_x) {
				*pcur_x -= (argc ? argv[0] : 1);
			} else {
				u32 pos = dbg_getcur();
				dbg_setcur((int)DBG_GETCUR_X(pos) - (argc ? argv[0] : 1),
				           (int)DBG_GETCUR_Y(pos));
			}
			break;

		case ANSI_CNL: /* Cursor next line. */
			if (pcur_x && pcur_y) {
				*pcur_y += (argc ? argv[0] : 1);
				*pcur_x = 0;
			} else {
				u32 pos = dbg_getcur();
				dbg_setcur(0, (int)DBG_GETCUR_Y(pos) + (argc ? argv[0] : 1));
			}
			break;

		case ANSI_CPL: /* Cursor previous line. */
			if (pcur_x && pcur_y) {
				*pcur_y -= (argc ? argv[0] : 1);
				*pcur_x = 0;
			} else {
				u32 pos = dbg_getcur();
				dbg_setcur(0, (int)DBG_GETCUR_Y(pos) - (argc ? argv[0] : 1));
			}
			break;

		case ANSI_CHA: /* Cursor horizontal absolute. */
			if (pcur_x) {
				*pcur_x = (int)(argc ? argv[0] : 1) - 1;
			} else {
				u32 pos = dbg_getcur();
				dbg_setcur((int)(argc ? argv[0] : 1) - 1,
				           (int)DBG_GETCUR_Y(pos));
			}
			break;

		case ANSI_CVA: /* Cursor vertical absolute. */
			if (pcur_y) {
				*pcur_y = (int)(argc ? argv[0] : 1) - 1;
			} else {
				u32 pos = dbg_getcur();
				dbg_setcur((int)DBG_GETCUR_X(pos),
				           (int)(argc ? argv[0] : 1) - 1);
			}
			break;

		case ANSI_CUP: /* Cursor position. */
		case ANSI_HVP: /* Cursor position. */
			if (pcur_x && pcur_y) {
				*pcur_x = (int)((argc >= 1) ? argv[0] : 1) - 1;
				*pcur_y = (int)((argc >= 2) ? argv[1] : 1) - 1;
			} else {
				dbg_setcur((int)((argc >= 1) ? argv[0] : 1) - 1,
				           (int)((argc >= 2) ? argv[1] : 1) - 1);
			}
			break;

		case ANSI_ED:
			if unlikely(vga_backlog_scrollpos)
				vga_backlog_setscrollpos(0);
#ifndef CONFIG_USE_HARDWARE_CURSOR
			else {
				if (vga_terminal_showcur)
					VGA_SHOWCURSOR_OFF();
			}
#endif
			switch (argc ? argv[0] : 0) {

			default:
				memsetw(vga_terminal_cur, VGA_EMPTY,
				        (size_t)(vga_terminal_end - vga_terminal_cur));
				break;

			case TERM_CLS_BEFORE:
				memsetw(vga_terminal_start, VGA_EMPTY,
				        (size_t)(vga_terminal_cur - vga_terminal_start));
				break;

			case TERM_CLS_ALL:
				memsetw(vga_terminal_start, VGA_EMPTY, VGA_WIDTH * VGA_HEIGHT);
				break;

			case TERM_CLS_ALLPAGES:
				memsetw(vga_terminal_start, VGA_EMPTY, VGA_WIDTH * VGA_HEIGHT);
				memsetw(vga_terminal_backlog, VGA_EMPTY, VGA_BACKLOG_NUMSCREENS * VGA_WIDTH * VGA_HEIGHT);
				break;

			}
#ifndef CONFIG_USE_HARDWARE_CURSOR
			if (vga_terminal_showcur)
				VGA_SHOWCURSOR_ON();
#endif
			break;

		case ANSI_EL:
			if unlikely(vga_backlog_scrollpos)
				vga_backlog_setscrollpos(0);
#ifndef CONFIG_USE_HARDWARE_CURSOR
			else {
				if (vga_terminal_showcur)
					VGA_SHOWCURSOR_OFF();
			}
#endif
			switch (argc ? argv[0] : 0) {

			default:
				memsetw(vga_terminal_cur, VGA_EMPTY, VGA_WIDTH - VGA_GETCUR_X());
				break;
			case TERM_EL_BEFORE: {
				unsigned int count;
				count = VGA_GETCUR_X();
				memsetw(vga_terminal_cur - count, VGA_EMPTY, count);
			}	break;

			case TERM_EL_ALL:
				memsetw(vga_terminal_cur - VGA_GETCUR_X(), VGA_EMPTY, VGA_WIDTH);
				break;

			}
#ifndef CONFIG_USE_HARDWARE_CURSOR
			if (vga_terminal_showcur)
				VGA_SHOWCURSOR_ON();
#endif
			break;

		case ANSI_SU:
			dbg_scroll(DBG_SCROLL_CMD_SET, dbg_scroll(DBG_SCROLL_CMD_GET, 0) + (argc ? argv[0] : 1));
			break;

		case ANSI_SD:
			dbg_scroll(DBG_SCROLL_CMD_SET, dbg_scroll(DBG_SCROLL_CMD_GET, 0) - (argc ? argv[0] : 1));
			break;

		case ANSI_SGR:
			if (!argc) {
				dbg_attr = dbg_default_attr;
			} else {
				size_t i;
				for (i = 0; i < argc; ++i) {
					switch (argv[i]) {
					case 0:
						dbg_attr = dbg_default_attr;
						break;
					case 1:
						/* Brighten foreground output color. */
						dbg_attr |= 0x0800;
						break;
					case 2:
						/* Darken foreground output color. */
						dbg_attr &= ~0x0800;
						break;
					case 7: /* Swap foreground/background colors. */
						dbg_attr = ((dbg_attr & 0x00ff)) |
						           ((dbg_attr & 0x0f00) << 4) |
						           ((dbg_attr & 0xf000) >> 4);
						break;
					case 30 ... 37:
						/* Normal Foreground */
						dbg_attr &= 0xf0ff;
						dbg_attr |= (argv[i] - 30) << 8;
						break;
					case 39: /* Reset Foreground */
						dbg_attr &= 0xf0ff;
						dbg_attr |= dbg_default_attr & 0x0f00;
						break;
					case 40 ... 47:
						/* Normal Background */
						dbg_attr &= 0x0fff;
						dbg_attr |= (argv[i] - 40) << 12;
						break;
					case 49: /* Reset Background */
						dbg_attr &= 0x0fff;
						dbg_attr |= dbg_default_attr & 0xf000;
						break;
					case 90 ... 97:
						/* Bright Foreground */
						dbg_attr &= 0xf0ff;
						dbg_attr |= (argv[i] - 90) << 8;
						dbg_attr |= 0x0800;
						break;
					case 100 ... 107:
						/* Bright Background */
						dbg_attr &= 0x0fff;
						dbg_attr |= (argv[i] - 100) << 12;
						dbg_attr |= 0x8000;
						break;
					default: break;
					}
				}
			}
			break;

		case ANSI_SCP:
			if (pcur_x && pcur_y) {
				dbg_saved_cursor_position = ((u32)((unsigned int)*pcur_x % VGA_WIDTH) |
				                             (u32)((unsigned int)*pcur_y % VGA_HEIGHT) << 16);
			} else {
				dbg_saved_cursor_position = dbg_getcur();
			}
			break;

		case ANSI_RCP:
			if (pcur_x && pcur_y) {
				*pcur_x = (int)DBG_GETCUR_X(dbg_saved_cursor_position);
				*pcur_y = (int)DBG_GETCUR_Y(dbg_saved_cursor_position);
			} else {
				dbg_setcur(DBG_GETCUR_X(dbg_saved_cursor_position),
				           DBG_GETCUR_Y(dbg_saved_cursor_position));
			}
			break;

		case ANSI_HIDE:
			dbg_setcur_visible(DBG_SETCUR_VISIBLE_HIDE);
			break;

		case ANSI_SHOW:
			dbg_setcur_visible(DBG_SETCUR_VISIBLE_SHOW);
			break;

		default: goto do_fallback;
		}
		return;
	} else if (dbg_ansi_escapebuf[1] == 'c') {
		vga_terminal_attr         = DBG_COLOR_ATTR(DBG_COLOR_SILVER, DBG_COLOR_BLACK);
		vga_terminal_default_attr = DBG_COLOR_ATTR(DBG_COLOR_SILVER, DBG_COLOR_BLACK);
		dbg_utf8_curlen           = 0;
		dbg_last_character        = 0;
		dbg_ansi_escapelen        = 0;
		dbg_saved_cursor_position = 0;
		dbg_tabsize               = DBG_TABSIZE_DEFAULT;
		dbg_newline_mode          = DBG_NEWLINE_MODE_NORMAL;
		dbg_setcur_visible(DBG_SETCUR_VISIBLE_HIDE);
	}
do_fallback:
	{
		char32_t ch;
		char *iter = dbg_ansi_escapebuf;
		while ((ch = unicode_readutf8((char const **)&iter)) != 0)
			dbg_do_putuni(ch);
	}
}


PUBLIC ATTR_DBGTEXT void NOTHROW(KCALL dbg_putuni)(/*utf-32*/u32 ch) {
	if (dbg_ansi_escapelen) {
		/* Already inside of an ANSI escape sequence. */
		char *oldbuf, *newbuf;
		oldbuf = &dbg_ansi_escapebuf[dbg_ansi_escapelen];
		newbuf = unicode_writeutf8(oldbuf, ch);
		dbg_ansi_escapelen += (size_t)(newbuf - oldbuf);
		if ((ch >= (unsigned char)'A' && ch <= (unsigned char)'z' && dbg_ansi_escapelen > 2) ||
		    dbg_ansi_escapelen >= (COMPILER_LENOF(dbg_ansi_escapebuf) - UNICODE_UTF8_CURLEN)) {
			dbg_ansi_escapebuf[dbg_ansi_escapelen] = 0;
			dbg_ansi_process(NULL, NULL);
			dbg_ansi_escapelen = 0;
		}
		return;
	} else if (ch == (unsigned char)'\033') {
		/* Start a new ANSI escape sequence. */
		dbg_ansi_escapelen    = 1;
		dbg_ansi_escapebuf[0] = (unsigned char)'\033';
		return;
	}
	/* Output a regular, old character. */
	dbg_do_putuni(ch);
}


LOCAL ATTR_DBGTEXT NONNULL((1)) void
NOTHROW(KCALL dbg_pprinter_putcp437)(dbg_pprinter_arg_t *__restrict printer, /*cp-437*/u8 ch) {
	/* VGA terminal output */
	if (printer->p_printx >= 0 && printer->p_printx < VGA_WIDTH &&
	    printer->p_printy >= 0 && printer->p_printy < VGA_HEIGHT)
		vga_terminal_start[printer->p_printx + printer->p_printy * VGA_WIDTH] = VGA_CHR(ch);
	++printer->p_printx;
}
PRIVATE ATTR_DBGTEXT ATTR_NOINLINE NONNULL((1)) void
NOTHROW(KCALL dbg_pprinter_putcp437_s)(dbg_pprinter_arg_t *__restrict printer, /*cp-437*/char const *__restrict str) {
	char ch;
	while ((ch = *str++) != '\0')
		dbg_pprinter_putcp437(printer, ch);
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
dbg_pprinter_do_putuni(dbg_pprinter_arg_t *__restrict printer, /*utf-32*/u32 ch) {
	u8 cp_ch;
	/* Scroll to bottom before printing a character. */
	if unlikely(vga_backlog_scrollpos)
		vga_backlog_setscrollpos(0);
	cp_ch = cp437_encode(ch);
	if (cp_ch) {
		dbg_pprinter_putcp437(printer, cp_ch);
	} else {
		switch (ch) {

		case '\t': {
			unsigned int cur_x;
			unsigned int num_space;
			unsigned int max_space;
			cur_x     = (unsigned int)printer->p_printx;
			num_space = dbg_tabsize - (cur_x % dbg_tabsize);
			max_space = VGA_WIDTH - cur_x;
			if (num_space > max_space)
				num_space = max_space;
			/* Output space characters. */
			if (printer->p_printx >= 0 && printer->p_printx < VGA_WIDTH &&
			    printer->p_printy >= 0 && printer->p_printy < VGA_HEIGHT) {
				memsetw(&vga_terminal_start[printer->p_printx + printer->p_printy * VGA_WIDTH],
				        VGA_EMPTY, MIN(num_space, VGA_WIDTH - (unsigned int)printer->p_printx));
			}
			printer->p_printx += num_space;
		}	break;

		case '\b':
			--printer->p_printx;
			break;

		case '\r':
		case '\n':
			/* Return to the start of the current line. */
			if (dbg_newline_mode & DBG_NEWLINE_MODE_CLRFREE) {
				if (printer->p_printx >= 0 && printer->p_printx < VGA_WIDTH &&
				    printer->p_printy >= 0 && printer->p_printy < VGA_HEIGHT)
					memsetw(&vga_terminal_start[printer->p_printx + printer->p_printy * VGA_WIDTH],
					        VGA_EMPTY, VGA_WIDTH - (unsigned int)printer->p_printx);
			}
			printer->p_printx = dbg_indent;
			if (ch == '\n')
				++printer->p_printy;
			break;

		default: {
			char buf[32];
			if (ch <= 0x1f || ch == 0x7f) {
				sprintf(buf, "^%c", ch + '@');
			} else {
				sprintf(buf, UNENCODABLE_START "U+%I32X" UNENCODABLE_END, ch);
			}
			dbg_pprinter_putcp437_s(printer, buf);
		}	break;
		}
	}
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
dbg_pprinter_putuni(dbg_pprinter_arg_t *__restrict printer, /*utf-32*/u32 ch) {
	if (dbg_ansi_escapelen) {
		/* Already inside of an ANSI escape sequence. */
		char *oldbuf, *newbuf;
		oldbuf = &dbg_ansi_escapebuf[dbg_ansi_escapelen];
		newbuf = unicode_writeutf8(oldbuf, ch);
		dbg_ansi_escapelen += (size_t)(newbuf - oldbuf);
		if ((ch >= (unsigned char)'A' && ch <= (unsigned char)'z' && dbg_ansi_escapelen > 2) ||
		    dbg_ansi_escapelen >= (COMPILER_LENOF(dbg_ansi_escapebuf) - UNICODE_UTF8_CURLEN)) {
			dbg_ansi_escapebuf[dbg_ansi_escapelen] = 0;
			dbg_ansi_process(&printer->p_printx,
			                 &printer->p_printy);
			dbg_ansi_escapelen = 0;
		}
		return;
	} else if (ch == (unsigned char)'\033') {
		/* Start a new ANSI escape sequence. */
		dbg_ansi_escapelen    = 1;
		dbg_ansi_escapebuf[0] = (unsigned char)'\033';
		return;
	}
	/* Output a regular, old character. */
	dbg_pprinter_do_putuni(printer, ch);
}

LOCAL ATTR_DBGTEXT NONNULL((1)) u32 KCALL
dbg_pprinter_pending_ch32(dbg_pprinter_arg_t *__restrict printer) {
	u32 result;
	u8 seqlen = unicode_utf8seqlen[printer->p_utf8[0]];
	result = (u32)printer->p_utf8[0];
	switch (seqlen) {
	case 0:
	case 1:
		break;
	case 2:
		result  = (result & 0x1f) << 6;
		result |= (printer->p_utf8[1] & 0x3f);
		break;
	case 3:
		result  = (result & 0x0f) << 12;
		result |= (printer->p_utf8[1] & 0x3f) << 6;
		result |= (printer->p_utf8[2] & 0x3f);
		break;
	case 4:
		result  = (result & 0x07) << 18;
		result |= (printer->p_utf8[1] & 0x3f) << 12;
		result |= (printer->p_utf8[2] & 0x3f) << 6;
		result |= (printer->p_utf8[3] & 0x3f);
		break;
	case 5:
		result  = (result & 0x03) << 24;
		result |= (printer->p_utf8[1] & 0x3f) << 18;
		result |= (printer->p_utf8[2] & 0x3f) << 12;
		result |= (printer->p_utf8[3] & 0x3f) << 6;
		result |= (printer->p_utf8[4] & 0x3f);
		break;
	case 6:
		result  = (result & 0x01) << 30;
		result |= (printer->p_utf8[1] & 0x3f) << 24;
		result |= (printer->p_utf8[2] & 0x3f) << 18;
		result |= (printer->p_utf8[3] & 0x3f) << 12;
		result |= (printer->p_utf8[4] & 0x3f) << 6;
		result |= (printer->p_utf8[5] & 0x3f);
		break;
	case 7:
		result  = (printer->p_utf8[1] & 0x03/*0x3f*/) << 30;
		result |= (printer->p_utf8[2] & 0x3f) << 24;
		result |= (printer->p_utf8[3] & 0x3f) << 18;
		result |= (printer->p_utf8[4] & 0x3f) << 12;
		result |= (printer->p_utf8[5] & 0x3f) << 6;
		result |= (printer->p_utf8[6] & 0x3f);
		break;
	case 8:
		/*result = (result & 0x3f) << 36;*/
		result  = (printer->p_utf8[1] & 0x03/*0x3f*/) << 30;
		result |= (printer->p_utf8[2] & 0x3f) << 24;
		result |= (printer->p_utf8[3] & 0x3f) << 18;
		result |= (printer->p_utf8[4] & 0x3f) << 12;
		result |= (printer->p_utf8[5] & 0x3f) << 6;
		result |= (printer->p_utf8[6] & 0x3f);
		break;
	default:
		__builtin_unreachable();
	}
	return result;
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
dbg_pprinter_putc(dbg_pprinter_arg_t *__restrict printer, /*utf-8*/char ch) {
	if (printer->p_utf8[0]) {
		/* Continue a utf-8 sequence. */
		u8 reqlen = unicode_utf8seqlen[printer->p_utf8[0]];
		if unlikely(((u8)ch & 0xc0) != 0x80) {
			/* Incomplete utf-8 sequence... */
			dbg_pprinter_putuni(printer, dbg_pprinter_pending_ch32(printer));
			printer->p_utf8[0] = 0;
			goto normal_ch;
		} else {
			unsigned int i;
			for (i = 0;; ++i) {
				if unlikely(i >= COMPILER_LENOF(printer->p_utf8)) {
					dbg_pprinter_putuni(printer, dbg_pprinter_pending_ch32(printer));
					printer->p_utf8[0] = 0;
					goto normal_ch;
				}
				if (!printer->p_utf8[i])
					break;
			}
			printer->p_utf8[i++] = (u8)ch;
			if (i >= reqlen) {
				dbg_pprinter_putuni(printer, dbg_pprinter_pending_ch32(printer));
				printer->p_utf8[0] = 0;
			}
		}
	} else normal_ch: if ((u8)ch < 0xc0) {
		/* Unicode pass-through character. */
		dbg_pprinter_putuni(printer, (u32)(u8)ch);
	} else {
		/* Start a new utf-8 sequence. */
		printer->p_utf8[0] = (u8)ch;
		memset(printer->p_utf8 + 1, 0,
		       sizeof(printer->p_utf8) -
		       sizeof(*printer->p_utf8));
	}
}

PUBLIC ATTR_DBGTEXT NONNULL((2)) ssize_t KCALL
dbg_pprinter(/*dbg_pprinter_arg_t*/void *arg,
             /*utf-8*/char const *__restrict data,
             size_t datalen) {
	size_t i;
	dbg_pprinter_arg_t *printer;
	printer = (dbg_pprinter_arg_t *)arg;
	for (i = 0; i < datalen; ++i)
		dbg_pprinter_putc(printer, data[i]);
	return (ssize_t)datalen;
}

/* Print text to the given coords. */
PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_pputuni)(int x, int y, /*utf-32*/u32 ch) {
	if (dbg_ansi_escapelen) {
		/* Already inside of an ANSI escape sequence. */
		char *oldbuf, *newbuf;
		oldbuf = &dbg_ansi_escapebuf[dbg_ansi_escapelen];
		newbuf = unicode_writeutf8(oldbuf, ch);
		dbg_ansi_escapelen += (size_t)(newbuf - oldbuf);
		if ((ch >= (unsigned char)'A' && ch <= (unsigned char)'z' && dbg_ansi_escapelen > 2) ||
		    dbg_ansi_escapelen >= (COMPILER_LENOF(dbg_ansi_escapebuf) - UNICODE_UTF8_CURLEN)) {
			dbg_ansi_escapebuf[dbg_ansi_escapelen] = 0;
			dbg_ansi_process(&x, &y);
			dbg_ansi_escapelen = 0;
		}
		return;
	} else if (ch == (unsigned char)'\033') {
		/* Start a new ANSI escape sequence. */
		dbg_ansi_escapelen    = 1;
		dbg_ansi_escapebuf[0] = (unsigned char)'\033';
		return;
	}
	{
		dbg_pprinter_arg_t printer = DBG_PPRINTER_ARG_INIT(x, y);
		dbg_pprinter_do_putuni(&printer, ch);
	}
}

PUBLIC ATTR_DBGTEXT NONNULL((3)) void KCALL
dbg_pprint(int x, int y, /*utf-8*/char const *__restrict str) {
	dbg_pprinter_arg_t printer = DBG_PPRINTER_ARG_INIT(x, y);
	dbg_pprinter(&printer, str, strlen(str));
}

PUBLIC ATTR_DBGTEXT NONNULL((3)) void VCALL
dbg_pprintf(int x, int y, /*utf-8*/char const *__restrict format, ...) {
	va_list args;
	va_start(args, format);
	dbg_vpprintf(x, y, format, args);
	va_end(args);
}

PUBLIC ATTR_DBGTEXT NONNULL((3)) void KCALL
dbg_vpprintf(int x, int y, /*utf-8*/char const *__restrict format, va_list args) {
	dbg_pprinter_arg_t printer = DBG_PPRINTER_ARG_INIT(x, y);
	format_vprintf(&dbg_pprinter, &printer, format, args);
}







PRIVATE ATTR_DBGBSS struct vga_mode debug_oldvgamode;
PRIVATE ATTR_DBGBSS struct vga_palette debug_oldvgapal;
PRIVATE ATTR_DBGBSS byte_t debug_oldvgadat[VGA_VRAM_SIZE];

PRIVATE ATTR_DBGBSS uintptr_t debug_oldvga_paging[VGA_VRAM_SIZE / PAGESIZE];
PRIVATE ATTR_DBGTEXT void KCALL x86_debug_map_terminal(void) {
	unsigned int i;
	vga_terminal_start = (u16 *)(KERNEL_BASE + VGA_VRAM_ADDR);
	/* TODO: We might get here so early during booting that the page frame allocator
	 *       has yet to be initialized, at which point prepare would fail. - However,
	 *       at that point we'd still have access to the physical identity map, so we
	 *       should instead also support its use instead of only hacking around to
	 *       place a temporary mapping of the VGA display just before the kernel. */
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_prepare_map(VM_ADDR2PAGE((vm_virt_t)vga_terminal_start), VGA_VRAM_SIZE / PAGESIZE);
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	for (i = 0; i < COMPILER_LENOF(debug_oldvga_paging); ++i) {
		uintptr_t oldword;
		vm_vpage_t vp = VM_ADDR2PAGE((vm_virt_t)vga_terminal_start) + i;
		oldword = pagedir_push_mapone(vp, VM_ADDR2PAGE((vm_phys_t)VGA_VRAM_ADDR) + i,
		                              PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
		debug_oldvga_paging[i] = oldword;
	}
}

PRIVATE ATTR_DBGTEXT void KCALL x86_debug_unmap_terminal(void) {
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(debug_oldvga_paging); ++i) {
		vm_vpage_t vp = VM_ADDR2PAGE((vm_virt_t)vga_terminal_start) + i;
		pagedir_pop_mapone(vp, debug_oldvga_paging[i]);
	}
}


INTERN ATTR_DBGTEXT void KCALL x86_debug_initialize_vga_terminal(void) {
	x86_debug_map_terminal();
	VGA_GetMode(&debug_oldvgamode);
	VGA_SetMode(&vga_debugmode);
	VGA_GetPalette(&debug_oldvgapal);
	VGA_SetPalette(&vga_debugpal);
	memcpy(debug_oldvgadat, vga_terminal_start, VGA_VRAM_SIZE);
	vga_terminal_backlog_cur     = vga_terminal_backlog;
	vga_terminal_attr            = DBG_COLOR_ATTR(DBG_COLOR_SILVER, DBG_COLOR_BLACK);
	vga_terminal_default_attr    = DBG_COLOR_ATTR(DBG_COLOR_SILVER, DBG_COLOR_BLACK);
	dbg_utf8_curlen              = 0;
	dbg_last_character           = 0;
	dbg_ansi_escapelen           = 0;
	dbg_saved_cursor_position    = 0;
	vga_backlog_scrollpos        = 0;
	vga_terminal_backlog_full    = false;
	vga_terminal_showcur         = false;
	vfa_last_chr_caused_linewrap = false;
	vga_terminal_cur             = vga_terminal_start;
	vga_terminal_2ndln           = vga_terminal_start + VGA_WIDTH;
	vga_terminal_end             = vga_terminal_start + VGA_WIDTH * VGA_HEIGHT;
	vga_terminal_lastln          = vga_terminal_start + VGA_WIDTH * (VGA_HEIGHT - 1);
	dbg_tabsize                  = DBG_TABSIZE_DEFAULT;
	dbg_indent                   = 0;
	dbg_newline_mode             = DBG_NEWLINE_MODE_NORMAL;
#ifdef CONFIG_USE_HARDWARE_CURSOR
	vga_cursor_is_shown = false;
#endif
	memsetw(vga_terminal_start, VGA_EMPTY, VGA_WIDTH * VGA_HEIGHT);
}

INTERN ATTR_DBGTEXT void KCALL
x86_debug_finalize_vga_terminal(void) {
	memcpy(vga_terminal_start, debug_oldvgadat, VGA_VRAM_SIZE);
	VGA_SetPalette(&debug_oldvgapal);
	VGA_SetMode(&debug_oldvgamode);
	x86_debug_unmap_terminal();
}







/* I/O within the debugger. */
PUBLIC ATTR_DBGTEXT NONNULL((1)) void KCALL
dbg_vprintf(/*utf-8*/char const *__restrict format, va_list args) {
	format_vprintf(&dbg_printer, NULL, format, args);
}

PUBLIC ATTR_DBGTEXT NONNULL((1)) void KCALL
dbg_print(/*utf-8*/char const *__restrict str) {
	char ch;
	while ((ch = *str++) != '\0')
		dbg_putc(ch);
}

PUBLIC ATTR_DBGTEXT NONNULL((1)) void VCALL
dbg_printf(/*utf-8*/char const *__restrict format, ...) {
	va_list args;
	va_start(args, format);
	dbg_vprintf(format, args);
	va_end(args);
}

PUBLIC ATTR_DBGTEXT NONNULL((2)) ssize_t KCALL
dbg_printer(void *ignored,
            /*utf-8*/char const *__restrict data,
            size_t datalen) {
	size_t result = datalen;
	while (datalen--)
		dbg_putc(*data++);
	return (ssize_t)result;
}

DECL_END
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_OUTPUT_C */
