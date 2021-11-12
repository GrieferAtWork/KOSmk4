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

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include <libsvga/chipset.h>
#include <libsvga/chipsets/vga.h>
#include <libsvga/util/vgaio.h>

#include "basevga.h"

DECL_BEGIN

/* Basic VGA adapter flags. (Set of `BASEVGA_FLAG_*') */
INTERN uint32_t basevga_flags = 0;

/* Either `VGA_IS1_RC' or `VGA_IS1_RM' (as appropriate) */
INTERN port_t basevga_is1rx = 0; /* Initialized in `basevga_init()' */


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
 * - basevga_is1rx
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

	/* Set-up the correct input-status register. */
	basevga_is1rx = hascolor ? VGA_IS1_RC
	                         : VGA_IS1_RM;
}


/* Current (assumed) EGA register state. */
PRIVATE struct vga_mode ega_registers = VGAMODE_INIT_EGA_TEXT;

/* Get/Set standard VGA registers.
 * NOTE: Must be called while holding a lock to the true VGA Chipset driver. */
INTERN NONNULL((1)) void CC
basevga_getregs(struct vga_mode *__restrict regs) {
	unsigned int i;

	if (basevga_flags & BASEVGA_FLAG_ISEGA) {
		/* Special case for EGA */
		memcpy(regs, &ega_registers, sizeof(struct vga_mode));
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
		regs->vm_att_pal[i] = vga_rattr(basevga_is1rx, VGA_ATC_PALETTE0 + i);
	regs->vm_att_mode         = vga_rattr(basevga_is1rx, VGA_ATC_MODE);
	regs->vm_att_overscan     = vga_rattr(basevga_is1rx, VGA_ATC_OVERSCAN);
	regs->vm_att_plane_enable = vga_rattr(basevga_is1rx, VGA_ATC_PLANE_ENABLE);
	regs->vm_att_pel          = vga_rattr(basevga_is1rx, VGA_ATC_PEL);
	regs->vm_att_color_page   = vga_rattr(basevga_is1rx, VGA_ATC_COLOR_PAGE);
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
	if (!(basevga_flags & BASEVGA_FLAG_ISEGA)) 	/* Unlock CRT registers. */
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
		vga_wattr(basevga_is1rx, VGA_ATC_PALETTE0 + i, regs->vm_att_pal[i]);
	vga_wattr(basevga_is1rx, VGA_ATC_MODE, regs->vm_att_mode);
	vga_wattr(basevga_is1rx, VGA_ATC_OVERSCAN, regs->vm_att_overscan);
	vga_wattr(basevga_is1rx, VGA_ATC_PLANE_ENABLE, regs->vm_att_plane_enable);
	vga_wattr(basevga_is1rx, VGA_ATC_PEL, regs->vm_att_pel);
	vga_wattr(basevga_is1rx, VGA_ATC_COLOR_PAGE, regs->vm_att_color_page);

	/* Remember EGA register state. */
	if (basevga_flags & BASEVGA_FLAG_ISEGA)
		memcpy(&ega_registers, regs, sizeof(struct vga_mode));
}


/* Special case: EGA doesn't allow (normal) register reads. As such,
 * we must fix-up `regs' and apply them via `basevga_setregs()'! */
PRIVATE ATTR_NOINLINE NONNULL((1)) void CC
ega_setmode(struct vga_mode const *__restrict regs) {
	unsigned int i;
	struct vga_mode newregs;
	memcpy(&newregs, regs, sizeof(struct vga_mode));

	/* Load reserved bits from expected register state `ega_registers'. */
#define MASK_REGISTER(name, reserved_mask) \
	(newregs.name &= ~reserved_mask,       \
	 newregs.name |= ega_registers.name & reserved_mask)
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
 * NOTE: Must be called while holding a lock to the true VGA Chipset driver. */
INTERN NONNULL((1)) void CC
basevga_setmode(struct vga_mode const *__restrict regs) {
	unsigned int i;

	if (basevga_flags & BASEVGA_FLAG_ISEGA) {
		/* Special case: EGA doesn't allow (normal) register reads. As such,
		 * we must fix-up `regs' and apply them via `basevga_setregs()'! */
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
	if (!(basevga_flags & BASEVGA_FLAG_ISEGA)) 	/* Unlock CRT registers. */
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
	assert(!(regs->vm_crt_v_sync_end & VGA_CR11_FLOCK_CR0_CR7));
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
		vga_wattr_res(basevga_is1rx,
		              VGA_ATC_PALETTE0 + i, regs->vm_att_pal[i],
		              VGA_ATC_PALETTEn_FRESERVED);
	}
	vga_wattr_res(basevga_is1rx, VGA_ATC_MODE, regs->vm_att_mode, VGA_AT10_FRESERVED);
	vga_wattr(basevga_is1rx, VGA_ATC_OVERSCAN, regs->vm_att_overscan);
	vga_wattr_res(basevga_is1rx, VGA_ATC_PLANE_ENABLE, regs->vm_att_plane_enable, VGA_AT12_FRESERVED);
	vga_wattr_res(basevga_is1rx, VGA_ATC_PEL, regs->vm_att_pel, VGA_AT13_FRESERVED);
	vga_wattr_res(basevga_is1rx, VGA_ATC_COLOR_PAGE, regs->vm_att_color_page, VGA_AT14_FRESERVED);
}



DECL_END

#endif /* !GUARD_LIBSVGA_BASEVGA_C */
