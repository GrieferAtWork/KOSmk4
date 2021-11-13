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
#ifndef GUARD_LIBSVGA_BASEVGA_C
#define GUARD_LIBSVGA_BASEVGA_C 1
#define _KOS_ALTERATIONS_SOURCE 1 /* Want sensical parameter order for outb/outw/outl */

#include "api.h"
/**/

#include <hw/video/vga.h>
#include <hw/video/vgamodes.h> /* VGAMODE_INIT_EGA_TEXT */
#include <kos/types.h>

#include <stdbool.h>
#include <string.h>

#include <libphys/phys.h>
#include <libsvga/chipset.h>
#include <libsvga/chipsets/vga.h>
#include <libsvga/util/vgaio.h>

#include "basevga.h"

DECL_BEGIN

/* Basic VGA adapter flags. (Set of `BASEVGA_FLAG_*') */
INTERN uint32_t basevga_flags = 0;

/* Initialized in `basevga_init()' */
INTERN port_t basevga_CRT_I = 0; /* Either `VGA_CRT_IC' or `VGA_CRT_IM' (as appropriate) */
INTERN port_t basevga_CRT_D = 0; /* Either `VGA_CRT_DC' or `VGA_CRT_DM' (as appropriate) */
INTERN port_t basevga_IS1_R = 0; /* Either `VGA_IS1_RC' or `VGA_IS1_RM' (as appropriate) */


/* Check if we're dealing */
PRIVATE bool CC probe_ega(void) {
	uint8_t saved, readback;
	/* Check if a DAC is present */
	saved = inb_p(VGA_PEL_IW);
	outb_p(VGA_PEL_IW, ~saved);
	readback = inb_p(VGA_PEL_IW);
	outb(VGA_PEL_IW, saved);
	return readback != (uint8_t)~saved;
}

/* Initialize base-vga global variables.
 * This function initializes:
 * - basevga_flags
 * - basevga_IS1_R
 * Called during chipset driver probe functions. */
INTERN void CC basevga_init(void) {
	bool hascolor;
	basevga_flags = 0;

	/* Check if we've got an EGA board */
	if (probe_ega())
		basevga_flags |= BASEVGA_FLAG_ISEGA;

	/* Check if we've got color emulation. */
	if (basevga_flags & BASEVGA_FLAG_ISEGA) {
		hascolor = true; /* Special case for EGA */
	} else {
		hascolor = (inb(VGA_MIS_R) & 0x01) != 0;
	}

	/* Set-up the correct registers for color/mono mode. */
	if (hascolor) {
		basevga_IS1_R = VGA_IS1_RC;
		basevga_CRT_I = VGA_CRT_IC;
		basevga_CRT_D = VGA_CRT_DC;
	} else {
		basevga_IS1_R = VGA_IS1_RM;
		basevga_CRT_I = VGA_CRT_IM;
		basevga_CRT_D = VGA_CRT_DM;
	}
}


/* Current (assumed) EGA register state. */
INTERN struct vga_mode baseega_registers = VGAMODE_INIT_EGA_TEXT;

/* Get/Set standard VGA registers.
 * NOTE: Must be called while holding a lock to the true VGA Chipset driver.
 * NOTE: Setting the basevga register state leaves the screen turned off! */
INTERN NONNULL((1)) void CC
basevga_getregs(struct vga_mode *__restrict regs) {
	unsigned int i;

	if (basevga_flags & BASEVGA_FLAG_ISEGA) {
		/* Special case for EGA */
		memcpy(regs, &baseega_registers, sizeof(struct vga_mode));
		return;
	}

	/* Write registers. */
	regs->vm_mis = vga_r(VGA_MIS_W);

	/* Sequencer... */
	regs->vm_seq_clock_mode    = vga_rseq(VGA_SEQ_CLOCK_MODE);
	regs->vm_seq_plane_write   = vga_rseq(VGA_SEQ_PLANE_WRITE);
	regs->vm_seq_character_map = vga_rseq(VGA_SEQ_CHARACTER_MAP);
	regs->vm_seq_memory_mode   = vga_rseq(VGA_SEQ_MEMORY_MODE);

	/* CRT... */
	regs->vm_crt_h_total       = vga_rcrt(VGA_CRTC_H_TOTAL);
	regs->vm_crt_h_disp        = vga_rcrt(VGA_CRTC_H_DISP);
	regs->vm_crt_h_blank_start = vga_rcrt(VGA_CRTC_H_BLANK_START);
	regs->vm_crt_h_blank_end   = vga_rcrt(VGA_CRTC_H_BLANK_END);
	regs->vm_crt_h_sync_start  = vga_rcrt(VGA_CRTC_H_SYNC_START);
	regs->vm_crt_h_sync_end    = vga_rcrt(VGA_CRTC_H_SYNC_END);
	regs->vm_crt_v_total       = vga_rcrt(VGA_CRTC_V_TOTAL);
	regs->vm_crt_overflow      = vga_rcrt(VGA_CRTC_OVERFLOW);
	regs->vm_crt_preset_row    = vga_rcrt(VGA_CRTC_PRESET_ROW);
	regs->vm_crt_max_scan      = vga_rcrt(VGA_CRTC_MAX_SCAN);
	regs->vm_crt_cursor_start  = vga_rcrt(VGA_CRTC_CURSOR_START);
	regs->vm_crt_cursor_end    = vga_rcrt(VGA_CRTC_CURSOR_END);
	regs->vm_crt_start_hi      = vga_rcrt(VGA_CRTC_START_HI);
	regs->vm_crt_start_lo      = vga_rcrt(VGA_CRTC_START_LO);
	regs->vm_crt_cursor_hi     = vga_rcrt(VGA_CRTC_CURSOR_HI);
	regs->vm_crt_cursor_lo     = vga_rcrt(VGA_CRTC_CURSOR_LO);
	regs->vm_crt_v_sync_start  = vga_rcrt(VGA_CRTC_V_SYNC_START);
	regs->vm_crt_v_sync_end    = vga_rcrt(VGA_CRTC_V_SYNC_END);
	regs->vm_crt_v_disp_end    = vga_rcrt(VGA_CRTC_V_DISP_END);
	regs->vm_crt_offset        = vga_rcrt(VGA_CRTC_OFFSET);
	regs->vm_crt_underline     = vga_rcrt(VGA_CRTC_UNDERLINE);
	regs->vm_crt_v_blank_start = vga_rcrt(VGA_CRTC_V_BLANK_START);
	regs->vm_crt_v_blank_end   = vga_rcrt(VGA_CRTC_V_BLANK_END);
	regs->vm_crt_mode          = vga_rcrt(VGA_CRTC_MODE);
	regs->vm_crt_line_compare  = vga_rcrt(VGA_CRTC_LINE_COMPARE);

	/* Graphics controller. */
	regs->vm_gfx_sr_value      = vga_rgfx(VGA_GFX_SR_VALUE);
	regs->vm_gfx_sr_enable     = vga_rgfx(VGA_GFX_SR_ENABLE);
	regs->vm_gfx_compare_value = vga_rgfx(VGA_GFX_COMPARE_VALUE);
	regs->vm_gfx_data_rotate   = vga_rgfx(VGA_GFX_DATA_ROTATE);
	regs->vm_gfx_plane_read    = vga_rgfx(VGA_GFX_PLANE_READ);
	regs->vm_gfx_mode          = vga_rgfx(VGA_GFX_MODE);
	regs->vm_gfx_misc          = vga_rgfx(VGA_GFX_MISC);
	regs->vm_gfx_compare_mask  = vga_rgfx(VGA_GFX_COMPARE_MASK);
	regs->vm_gfx_bit_mask      = vga_rgfx(VGA_GFX_BIT_MASK);

	/* Attribute controller. */
	for (i = 0; i < 16; ++i)
		regs->vm_att_pal[i] = vga_rattr(basevga_IS1_R, VGA_ATC_PALETTE0 + i);
	regs->vm_att_mode         = vga_rattr(basevga_IS1_R, VGA_ATC_MODE);
	regs->vm_att_overscan     = vga_rattr(basevga_IS1_R, VGA_ATC_OVERSCAN);
	regs->vm_att_plane_enable = vga_rattr(basevga_IS1_R, VGA_ATC_PLANE_ENABLE);
	regs->vm_att_pel          = vga_rattr(basevga_IS1_R, VGA_ATC_PEL);
	regs->vm_att_color_page   = vga_rattr(basevga_IS1_R, VGA_ATC_COLOR_PAGE);
}

INTERN NONNULL((1)) void CC
basevga_setregs(struct vga_mode const *__restrict regs) {
	unsigned int i;

	if (basevga_flags & BASEVGA_FLAG_ISEGA) {
		/* Unlock graphics registers */
		outb(EGA_GFX_E0, 0x00);
		outb(EGA_GFX_E1, 0x01);
	}

	/* Write registers. */
	vga_w(VGA_MIS_W, regs->vm_mis);

	/* Sequencer... */
	vga_wseq(VGA_SEQ_RESET, 1);
	vga_wseq(VGA_SEQ_CLOCK_MODE, regs->vm_seq_clock_mode | VGA_SR01_FSCREEN_OFF);
	vga_wseq(VGA_SEQ_PLANE_WRITE, regs->vm_seq_plane_write);
	vga_wseq(VGA_SEQ_CHARACTER_MAP, regs->vm_seq_character_map);
	vga_wseq(VGA_SEQ_MEMORY_MODE, regs->vm_seq_memory_mode);
	vga_wseq(VGA_SEQ_RESET, 3);

	/* CRT... */
	if (!(basevga_flags & BASEVGA_FLAG_ISEGA)) /* Unlock CRT registers. */
		vga_wcrt(VGA_CRTC_V_SYNC_END, vga_rcrt(VGA_CRTC_V_SYNC_END) & ~VGA_CR11_FLOCK_CR0_CR7);
	vga_wcrt(VGA_CRTC_H_TOTAL, regs->vm_crt_h_total);
	vga_wcrt(VGA_CRTC_H_DISP, regs->vm_crt_h_disp);
	vga_wcrt(VGA_CRTC_H_BLANK_START, regs->vm_crt_h_blank_start);
	vga_wcrt(VGA_CRTC_H_BLANK_END, regs->vm_crt_h_blank_end);
	vga_wcrt(VGA_CRTC_H_SYNC_START, regs->vm_crt_h_sync_start);
	vga_wcrt(VGA_CRTC_H_SYNC_END, regs->vm_crt_h_sync_end);
	vga_wcrt(VGA_CRTC_V_TOTAL, regs->vm_crt_v_total);
	vga_wcrt(VGA_CRTC_OVERFLOW, regs->vm_crt_overflow);
	vga_wcrt(VGA_CRTC_PRESET_ROW, regs->vm_crt_preset_row);
	vga_wcrt(VGA_CRTC_MAX_SCAN, regs->vm_crt_max_scan);
	vga_wcrt(VGA_CRTC_CURSOR_START, regs->vm_crt_cursor_start);
	vga_wcrt(VGA_CRTC_CURSOR_END, regs->vm_crt_cursor_end);
	vga_wcrt(VGA_CRTC_START_HI, regs->vm_crt_start_hi);
	vga_wcrt(VGA_CRTC_START_LO, regs->vm_crt_start_lo);
	vga_wcrt(VGA_CRTC_CURSOR_HI, regs->vm_crt_cursor_hi);
	vga_wcrt(VGA_CRTC_CURSOR_LO, regs->vm_crt_cursor_lo);
	vga_wcrt(VGA_CRTC_V_SYNC_START, regs->vm_crt_v_sync_start);
	/* IMPORTANT: `VGA_CRTC_V_SYNC_END' must be set _AFTER_ CR0-CR7:
	 *  - VGA_CRTC_H_TOTAL
	 *  - VGA_CRTC_H_DISP
	 *  - VGA_CRTC_H_BLANK_START
	 *  - VGA_CRTC_H_BLANK_END
	 *  - VGA_CRTC_H_SYNC_START
	 *  - VGA_CRTC_H_SYNC_END
	 *  - VGA_CRTC_V_TOTAL
	 *  - VGA_CRTC_OVERFLOW
	 * This is because `VGA_CRTC_V_SYNC_END' includes `VGA_CR11_FLOCK_CR0_CR7' */
	vga_wcrt(VGA_CRTC_V_SYNC_END, regs->vm_crt_v_sync_end);
	vga_wcrt(VGA_CRTC_V_DISP_END, regs->vm_crt_v_disp_end);
	vga_wcrt(VGA_CRTC_OFFSET, regs->vm_crt_offset);
	vga_wcrt(VGA_CRTC_UNDERLINE, regs->vm_crt_underline);
	vga_wcrt(VGA_CRTC_V_BLANK_START, regs->vm_crt_v_blank_start);
	vga_wcrt(VGA_CRTC_V_BLANK_END, regs->vm_crt_v_blank_end);
	vga_wcrt(VGA_CRTC_MODE, regs->vm_crt_mode);
	vga_wcrt(VGA_CRTC_LINE_COMPARE, regs->vm_crt_line_compare);

	/* Graphics controller. */
	vga_wgfx(VGA_GFX_SR_VALUE, regs->vm_gfx_sr_value);
	vga_wgfx(VGA_GFX_SR_ENABLE, regs->vm_gfx_sr_enable);
	vga_wgfx(VGA_GFX_COMPARE_VALUE, regs->vm_gfx_compare_value);
	vga_wgfx(VGA_GFX_DATA_ROTATE, regs->vm_gfx_data_rotate);
	vga_wgfx(VGA_GFX_PLANE_READ, regs->vm_gfx_plane_read);
	vga_wgfx(VGA_GFX_MODE, regs->vm_gfx_mode);
	vga_wgfx(VGA_GFX_MISC, regs->vm_gfx_misc);
	vga_wgfx(VGA_GFX_COMPARE_MASK, regs->vm_gfx_compare_mask);
	vga_wgfx(VGA_GFX_BIT_MASK, regs->vm_gfx_bit_mask);

	/* Attribute controller. */
	for (i = 0; i < 16; ++i)
		vga_wattr(basevga_IS1_R, VGA_ATC_PALETTE0 + i, regs->vm_att_pal[i]);
	vga_wattr(basevga_IS1_R, VGA_ATC_MODE, regs->vm_att_mode);
	vga_wattr(basevga_IS1_R, VGA_ATC_OVERSCAN, regs->vm_att_overscan);
	vga_wattr(basevga_IS1_R, VGA_ATC_PLANE_ENABLE, regs->vm_att_plane_enable);
	vga_wattr(basevga_IS1_R, VGA_ATC_PEL, regs->vm_att_pel);
	vga_wattr(basevga_IS1_R, VGA_ATC_COLOR_PAGE, regs->vm_att_color_page);

	/* Remember EGA register state. */
	if (basevga_flags & BASEVGA_FLAG_ISEGA)
		memcpy(&baseega_registers, regs, sizeof(struct vga_mode));
}


/* Special case: EGA doesn't allow (normal) register reads. As such,
 * we must  fix-up `regs'  and apply  them via  `basevga_setregs()'! */
PRIVATE ATTR_NOINLINE NONNULL((1)) void CC
ega_setmode(struct vga_mode const *__restrict regs) {
	unsigned int i;
	struct vga_mode newregs;
	memcpy(&newregs, regs, sizeof(struct vga_mode));

	/* Load reserved bits from expected register state `baseega_registers'. */
#define MASK_REGISTER(name, reserved_mask) \
	(newregs.name &= ~reserved_mask,       \
	 newregs.name |= baseega_registers.name & reserved_mask)
	MASK_REGISTER(vm_seq_clock_mode, VGA_SR01_FRESERVED);
	MASK_REGISTER(vm_seq_plane_write, VGA_SR02_FRESERVED);
	MASK_REGISTER(vm_seq_character_map, VGA_SR03_FRESERVED);
	MASK_REGISTER(vm_seq_memory_mode, VGA_SR04_FRESERVED);
	MASK_REGISTER(vm_crt_preset_row, VGA_CR8_FRESERVED);
	MASK_REGISTER(vm_crt_cursor_start, VGA_CRA_FRESERVED);
	MASK_REGISTER(vm_crt_cursor_end, VGA_CRB_FRESERVED);
	MASK_REGISTER(vm_crt_v_sync_end, VGA_CR11_FRESERVED);
	MASK_REGISTER(vm_crt_v_blank_end, VGA_CR16_FRESERVED);
	MASK_REGISTER(vm_crt_mode, VGA_CR17_FRESERVED);
	MASK_REGISTER(vm_gfx_sr_value, VGA_GR00_FRESERVED);
	MASK_REGISTER(vm_gfx_sr_enable, VGA_GR01_FRESERVED);
	MASK_REGISTER(vm_gfx_compare_value, VGA_GR02_FRESERVED);
	MASK_REGISTER(vm_gfx_data_rotate, VGA_GR03_FRESERVED);
	MASK_REGISTER(vm_gfx_plane_read, VGA_GR04_FRESERVED);
	MASK_REGISTER(vm_gfx_mode, VGA_GR05_FRESERVED);
	MASK_REGISTER(vm_gfx_misc, VGA_GR06_FRESERVED);
	MASK_REGISTER(vm_gfx_compare_mask, VGA_GR07_FRESERVED);
	for (i = 0; i < 16; ++i)
		MASK_REGISTER(vm_att_pal[i], VGA_ATC_PALETTEn_FRESERVED);
	MASK_REGISTER(vm_att_mode, VGA_AT10_FRESERVED);
	MASK_REGISTER(vm_att_plane_enable, VGA_AT12_FRESERVED);
	MASK_REGISTER(vm_att_pel, VGA_AT13_FRESERVED);
	MASK_REGISTER(vm_att_color_page, VGA_AT14_FRESERVED);
#undef MASK_REGISTER

	/* Apply the properly sanitized new register state. */
	basevga_setregs(&newregs);
}

/* Same as `basevga_setregs()', but preserve the state of reserved bits.
 * NOTE: Must be called while holding a lock to the true VGA Chipset driver.
 * NOTE: This function leaves the screen turned off! */
INTERN NONNULL((1)) void CC
basevga_setmode(struct vga_mode const *__restrict regs) {
	unsigned int i;

	if (basevga_flags & BASEVGA_FLAG_ISEGA) {
		/* Special case: EGA doesn't allow (normal) register reads. As such,
		 * we must  fix-up `regs'  and apply  them via  `basevga_setregs()'! */
		ega_setmode(regs);
		return;
	}

	/* Write registers. */
	vga_w(VGA_MIS_W, regs->vm_mis);

	/* Sequencer... */
	vga_wseq(VGA_SEQ_RESET, 1);
	vga_wseq_res(VGA_SEQ_CLOCK_MODE, regs->vm_seq_clock_mode | VGA_SR01_FSCREEN_OFF, VGA_SR01_FRESERVED);
	vga_wseq_res(VGA_SEQ_PLANE_WRITE, regs->vm_seq_plane_write, VGA_SR02_FRESERVED);
	vga_wseq_res(VGA_SEQ_CHARACTER_MAP, regs->vm_seq_character_map, VGA_SR03_FRESERVED);
	vga_wseq_res(VGA_SEQ_MEMORY_MODE, regs->vm_seq_memory_mode, VGA_SR04_FRESERVED);
	vga_wseq(VGA_SEQ_RESET, 3);

	/* CRT... */
	if (!(basevga_flags & BASEVGA_FLAG_ISEGA)) /* Unlock CRT registers. */
		vga_wcrt(VGA_CRTC_V_SYNC_END, vga_rcrt(VGA_CRTC_V_SYNC_END) & ~VGA_CR11_FLOCK_CR0_CR7);
	vga_wcrt(VGA_CRTC_H_TOTAL, regs->vm_crt_h_total);
	vga_wcrt(VGA_CRTC_H_DISP, regs->vm_crt_h_disp);
	vga_wcrt(VGA_CRTC_H_BLANK_START, regs->vm_crt_h_blank_start);
	vga_wcrt(VGA_CRTC_H_BLANK_END, regs->vm_crt_h_blank_end | VGA_CR3_FALWAYS1);
	vga_wcrt(VGA_CRTC_H_SYNC_START, regs->vm_crt_h_sync_start);
	vga_wcrt(VGA_CRTC_H_SYNC_END, regs->vm_crt_h_sync_end);
	vga_wcrt(VGA_CRTC_V_TOTAL, regs->vm_crt_v_total);
	vga_wcrt(VGA_CRTC_OVERFLOW, regs->vm_crt_overflow);
	vga_wcrt_res(VGA_CRTC_PRESET_ROW, regs->vm_crt_preset_row, VGA_CR8_FRESERVED);
	vga_wcrt(VGA_CRTC_MAX_SCAN, regs->vm_crt_max_scan);
	vga_wcrt_res(VGA_CRTC_CURSOR_START, regs->vm_crt_cursor_start, VGA_CRA_FRESERVED);
	vga_wcrt_res(VGA_CRTC_CURSOR_END, regs->vm_crt_cursor_end, VGA_CRB_FRESERVED);
	vga_wcrt(VGA_CRTC_START_HI, regs->vm_crt_start_hi);
	vga_wcrt(VGA_CRTC_START_LO, regs->vm_crt_start_lo);
	vga_wcrt(VGA_CRTC_CURSOR_HI, regs->vm_crt_cursor_hi);
	vga_wcrt(VGA_CRTC_CURSOR_LO, regs->vm_crt_cursor_lo);
	vga_wcrt(VGA_CRTC_V_SYNC_START, regs->vm_crt_v_sync_start);
	vga_wcrt_res(VGA_CRTC_V_SYNC_END, regs->vm_crt_v_sync_end, VGA_CR11_FRESERVED);
	vga_wcrt(VGA_CRTC_V_DISP_END, regs->vm_crt_v_disp_end);
	vga_wcrt(VGA_CRTC_OFFSET, regs->vm_crt_offset);
	vga_wcrt(VGA_CRTC_UNDERLINE, regs->vm_crt_underline);
	vga_wcrt(VGA_CRTC_V_BLANK_START, regs->vm_crt_v_blank_start);
	vga_wcrt_res(VGA_CRTC_V_BLANK_END, regs->vm_crt_v_blank_end, VGA_CR16_FRESERVED);
	vga_wcrt_res(VGA_CRTC_MODE, regs->vm_crt_mode, VGA_CR17_FRESERVED);
	vga_wcrt(VGA_CRTC_LINE_COMPARE, regs->vm_crt_line_compare);

	/* Graphics controller. */
	vga_wgfx_res(VGA_GFX_SR_VALUE, regs->vm_gfx_sr_value, VGA_GR00_FRESERVED);
	vga_wgfx_res(VGA_GFX_SR_ENABLE, regs->vm_gfx_sr_enable, VGA_GR01_FRESERVED);
	vga_wgfx_res(VGA_GFX_COMPARE_VALUE, regs->vm_gfx_compare_value, VGA_GR02_FRESERVED);
	vga_wgfx_res(VGA_GFX_DATA_ROTATE, regs->vm_gfx_data_rotate, VGA_GR03_FRESERVED);
	vga_wgfx_res(VGA_GFX_PLANE_READ, regs->vm_gfx_plane_read, VGA_GR04_FRESERVED);
	vga_wgfx_res(VGA_GFX_MODE, regs->vm_gfx_mode, VGA_GR05_FRESERVED);
	vga_wgfx_res(VGA_GFX_MISC, regs->vm_gfx_misc, VGA_GR06_FRESERVED);
	vga_wgfx_res(VGA_GFX_COMPARE_MASK, regs->vm_gfx_compare_mask, VGA_GR07_FRESERVED);
	vga_wgfx(VGA_GFX_BIT_MASK, regs->vm_gfx_bit_mask);

	/* Attribute controller. */
	for (i = 0; i < 16; ++i) {
		vga_wattr_res(basevga_IS1_R,
		              VGA_ATC_PALETTE0 + i, regs->vm_att_pal[i],
		              VGA_ATC_PALETTEn_FRESERVED);
	}
	vga_wattr_res(basevga_IS1_R, VGA_ATC_MODE, regs->vm_att_mode, VGA_AT10_FRESERVED);
	vga_wattr(basevga_IS1_R, VGA_ATC_OVERSCAN, regs->vm_att_overscan);
	vga_wattr_res(basevga_IS1_R, VGA_ATC_PLANE_ENABLE, regs->vm_att_plane_enable, VGA_AT12_FRESERVED);
	vga_wattr_res(basevga_IS1_R, VGA_ATC_PEL, regs->vm_att_pel, VGA_AT13_FRESERVED);
	vga_wattr_res(basevga_IS1_R, VGA_ATC_COLOR_PAGE, regs->vm_att_color_page, VGA_AT14_FRESERVED);
}


/* Read/write to/from the current color palette.
 * @param: color_index: Starting palette color index.
 * @param: count:       # of color rgb-triples to read/write */
INTERN NONNULL((2)) void CC
basevga_rdpal(uint8_t color_index,
              struct vga_palcolor *__restrict buf,
              uint8_t count) {
	vga_w(VGA_PEL_IR, color_index);
	while (count--) {
		buf->vpc_r = vga_r(VGA_PEL_D);
		buf->vpc_g = vga_r(VGA_PEL_D);
		buf->vpc_b = vga_r(VGA_PEL_D);
		++buf;
	}
}

INTERN NONNULL((2)) void CC
basevga_wrpal(uint8_t color_index,
              struct vga_palcolor const *__restrict buf,
              uint8_t count) {
	vga_w(VGA_PEL_IW, color_index);
	while (count--) {
		vga_w(VGA_PEL_D, buf->vpc_r);
		vga_w(VGA_PEL_D, buf->vpc_g);
		vga_w(VGA_PEL_D, buf->vpc_b);
		++buf;
	}
}



/* Direct access  to the  standard 256K  of VGA  video  memory.
 * These functions take the current register state into account
 * in order to  work around any  weird address  transformations
 * which may be done by the video card:
 *  - VGA_GR04_READMAP(i)  // For `basevga_rdvmem()'
 *  - VGA_GR05_FREADMODE_* // For `basevga_rdvmem()'
 *  - VGA_GR06_FCHAINOE
 *  - VGA_GR06_FMM_*
 *  - VGA_SR02_FPLANE(i)   // For `basevga_wrvmem()'
 * Any VGA registers modified by these functions will be restored
 * before they return. These functions  aren't very fast and  are
 * meant  to be used to backup and restore base-vga video memory.
 *
 * Here are some important memory locations:
 *  - 00000h: Plane 0
 *    - On-screen text characters in text-mode
 *    - yes: Only the characters (not attributes), tightly packed together
 *  - 40000h: Plane 1
 *    - On-screen text attributes in text-mode
 *    - yes: Text-mode uses `VGA_GR05_FHOSTOE' + `VGA_GR06_FCHAINOE'
 *           and  `VGA_GR06_FMM_32K_HI' to create  a linear array of
 *           u16-cells at `B8000h'
 *  - 80000h: Plane 2
 *    - Text-mode font data as array of 32-byte scanline bitsets,
 *      even though only  the first 16  are used for  characters.
 *  - C0000h: Plane 3 */
INTERN NONNULL((2)) void CC
basevga_rdvmem(uint32_t addr, void *buf, uint32_t num_bytes) {
	uint8_t saved_VGA_GFX_PLANE_READ;
	uint8_t saved_VGA_GFX_MODE;
	uint8_t saved_VGA_GFX_MISC;
	uint8_t saved_VGA_SEQ_MEMORY_MODE;
	if (basevga_flags & BASEVGA_FLAG_ISEGA) {
		saved_VGA_GFX_PLANE_READ  = baseega_registers.vm_gfx_plane_read;
		saved_VGA_GFX_MODE        = baseega_registers.vm_gfx_mode;
		saved_VGA_GFX_MISC        = baseega_registers.vm_gfx_misc;
		saved_VGA_SEQ_MEMORY_MODE = baseega_registers.vm_seq_memory_mode;
		/* TODO: EGA had less video memory than VGA, meaning  this
		 *       function probably won't work with an EGA adapter.
		 * Question is if this makes EGA's plane-select work differently,
		 * in  that everything  is located in  the first plane,  or if it
		 * does something else. In the  later case, what would that  mean
		 * for VGA memory locations? -  Normal VGA uses 80000h+ to  store
		 * the text-mode font... */
	} else {
		saved_VGA_GFX_PLANE_READ  = vga_rgfx(VGA_GFX_PLANE_READ);
		saved_VGA_GFX_MODE        = vga_rgfx(VGA_GFX_MODE);
		saved_VGA_GFX_MISC        = vga_rgfx(VGA_GFX_MISC);
		saved_VGA_SEQ_MEMORY_MODE = vga_rgfx(VGA_SEQ_MEMORY_MODE);
	}
	vga_wgfx(VGA_GFX_MISC, (saved_VGA_GFX_MISC & ~(VGA_GR06_FMM_MASK | VGA_GR06_FCHAINOE)) | VGA_GR06_FMM_64K);
	vga_wgfx(VGA_GFX_MODE, (saved_VGA_GFX_MODE & ~(VGA_GR05_FREADMODE | VGA_GR05_FHOSTOE)) | VGA_GR05_FREADMODE_0);
	vga_wseq(VGA_SEQ_MEMORY_MODE, (saved_VGA_SEQ_MEMORY_MODE & ~VGA_SR04_FCHN_4M) | VGA_SR04_FEXT_MEM | VGA_SR04_FSEQ_MODE);
	while (num_bytes) {
		uint32_t bankspace;
		bankspace = 0x10000 - (addr & 0xffff); /* Limit to 64K (1 plane) at a time */
		if (bankspace > num_bytes)
			bankspace = num_bytes;

		/* Select the bank we want to read from. */
		vga_wgfx(VGA_GFX_PLANE_READ,
		         (saved_VGA_GFX_PLANE_READ & ~VGA_GR04_FREADMAP) |
		         VGA_GR04_READMAP((addr >> 16) & 3));

		/* Copy memory. */
		copyfromphys(buf, 0xA0000 + (addr & 0xffff), bankspace);

		/* Advance buffers. */
		buf = (byte_t *)buf + bankspace;
		addr += bankspace;
		num_bytes -= bankspace;
	}

	/* Restore registers. */
	vga_wseq(VGA_SEQ_MEMORY_MODE, saved_VGA_SEQ_MEMORY_MODE);
	vga_wgfx(VGA_GFX_MISC, saved_VGA_GFX_MISC);
	vga_wgfx(VGA_GFX_MODE, saved_VGA_GFX_MODE);
	vga_wgfx(VGA_GFX_PLANE_READ, saved_VGA_GFX_PLANE_READ);
}

INTERN NONNULL((2)) void CC
basevga_wrvmem(uint32_t addr, void const *buf, uint32_t num_bytes) {
	uint8_t saved_VGA_SEQ_PLANE_WRITE;
	uint8_t saved_VGA_GFX_MODE;
	uint8_t saved_VGA_GFX_MISC;
	uint8_t saved_VGA_SEQ_MEMORY_MODE;
	if (basevga_flags & BASEVGA_FLAG_ISEGA) {
		saved_VGA_SEQ_PLANE_WRITE = baseega_registers.vm_seq_plane_write;
		saved_VGA_GFX_MODE        = baseega_registers.vm_gfx_mode;
		saved_VGA_GFX_MISC        = baseega_registers.vm_gfx_misc;
		saved_VGA_SEQ_MEMORY_MODE = baseega_registers.vm_seq_memory_mode;
	} else {
		saved_VGA_SEQ_PLANE_WRITE = vga_rseq(VGA_SEQ_PLANE_WRITE);
		saved_VGA_GFX_MODE        = vga_rgfx(VGA_GFX_MODE);
		saved_VGA_GFX_MISC        = vga_rgfx(VGA_GFX_MISC);
		saved_VGA_SEQ_MEMORY_MODE = vga_rgfx(VGA_SEQ_MEMORY_MODE);
	}
	vga_wgfx(VGA_GFX_MISC, (saved_VGA_GFX_MISC & ~(VGA_GR06_FMM_MASK | VGA_GR06_FCHAINOE)) | VGA_GR06_FMM_64K);
	vga_wgfx(VGA_GFX_MODE, (saved_VGA_GFX_MODE & ~(VGA_GR05_FWRITEMODE | VGA_GR05_FHOSTOE)) | VGA_GR05_FWRITEMODE_0);
	vga_wseq(VGA_SEQ_MEMORY_MODE, (saved_VGA_SEQ_MEMORY_MODE & ~VGA_SR04_FCHN_4M) | VGA_SR04_FEXT_MEM | VGA_SR04_FSEQ_MODE);
	while (num_bytes) {
		uint32_t bankspace;
		bankspace = 0x10000 - (addr & 0xffff); /* Limit to 64K (1 plane) at a time */
		if (bankspace > num_bytes)
			bankspace = num_bytes;

		/* Select the bank we want to read from. */
		vga_wgfx(VGA_SEQ_PLANE_WRITE,
		         (saved_VGA_SEQ_PLANE_WRITE & ~VGA_SR02_FALL_PLANES) |
		         VGA_SR02_FPLANE((addr >> 16) & 3));

		/* Copy memory. */
		copytophys(0xA0000 + (addr & 0xffff), buf, bankspace);

		/* Advance buffers. */
		buf = (byte_t *)buf + bankspace;
		addr += bankspace;
		num_bytes -= bankspace;
	}

	/* Restore registers. */
	vga_wseq(VGA_SEQ_MEMORY_MODE, saved_VGA_SEQ_MEMORY_MODE);
	vga_wgfx(VGA_GFX_MISC, saved_VGA_GFX_MISC);
	vga_wgfx(VGA_GFX_MODE, saved_VGA_GFX_MODE);
	vga_wgfx(VGA_SEQ_PLANE_WRITE, saved_VGA_SEQ_PLANE_WRITE);
}


DECL_END

#endif /* !GUARD_LIBSVGA_BASEVGA_C */
