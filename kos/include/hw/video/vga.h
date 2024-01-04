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
#ifndef _HW_VIDEO_VGA_H
#define _HW_VIDEO_VGA_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <sys/io.h>

__SYSDECL_BEGIN

/* Taken from linux, before changes were made. */

/*
 * linux/include/video/vga.h -- standard VGA chipset interaction
 *
 * Copyright 1999 Jeff Garzik <jgarzik@pobox.com>
 *
 * Copyright history from vga16fb.c:
 *	Copyright 1999 Ben Pfaff and Petr Vandrovec
 *	Based on VGA info at http://www.osdever.net/FreeVGA/home.htm
 *	Based on VESA framebuffer (c) 1998 Gerd Knorr
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file COPYING in the main directory of  this
 * archive for more details.
 *
 */

/* Some of the code below is taken from SVGAlib.  The original,
   unmodified copyright notice for that code is below. */
/* VGAlib version 1.2 - (c) 1993 Tommy Frandsen                    */
/*                                                                 */
/* This library is free software; you can redistribute it and/or   */
/* modify it without any restrictions. This library is distributed */
/* in the hope that it will be useful, but without any warranty.   */

/* Multi-chipset support Copyright 1993 Harm Hanemaayer */
/* partially copyrighted (C) 1993 by Hartmut Schirmer */

/* VGA data register ports */
#define VGA_CRT_DC      __IOPORT(0x3d5) /* CRT Controller Data Register - color emulation. */
#define VGA_CRT_DM      __IOPORT(0x3b5) /* CRT Controller Data Register - mono emulation. */
#define VGA_ATT_R       __IOPORT(0x3c1) /* Attribute Controller Data Read Register. */
#define VGA_ATT_W       __IOPORT(0x3c0) /* Attribute Controller Data Write Register. */
#define VGA_GFX_D       __IOPORT(0x3cf) /* Graphics Controller Data Register. */
#define VGA_SEQ_D       __IOPORT(0x3c5) /* Sequencer Data Register. */
#define VGA_MIS_R       __IOPORT(0x3cc) /* Misc Output Read Register. */
#define VGA_MIS_W       __IOPORT(0x3c2) /* Misc Output Write Register. */
#   define VGA_MIS_FRESERVED        0x10 /* Mask of reserved registers */
#   define VGA_MIS_FCOLOR           0x01
#   define VGA_MIS_FENB_MEM_ACCESS  0x02 /* Enable system access to the display buffer. */
#   define VGA_MIS_FCLOCK_25175_640 0x00 /* 25 Mhz clock -- for 320/640 pixel wide modes */
#   define VGA_MIS_FCLOCK_28322_720 0x04 /* 28 Mhz clock -- for 360/720 pixel wide modes */
#   define VGA_MIS_FCLOCKMASK       0x0c /* Mask for the clock selection. */
#   define VGA_MIS_FSEL_HIGH_PAGE   0x20 /* Select high memory when configured for even/odd mode */
#   define VGA_MIS_FHSYNCPOL        0x40 /* HSYNC polarity (0 = positive horizontal retrace sync pulse) */
#   define VGA_MIS_FVSYNCPOL        0x80 /* VSYNC polarity (0 = positive vertical retrace sync pulse) */
#define VGA_FTC_R       __IOPORT(0x3ca) /* Feature Control Read Register. */
#define VGA_IS1_RC      __IOPORT(0x3da) /* Input Status Register 1 - color emulation. */
#define VGA_IS1_RM      __IOPORT(0x3ba) /* Input Status Register 1 - mono emulation. */
#define VGA_PEL_D       __IOPORT(0x3c9) /* PEL Data Register. */
#define VGA_PEL_MSK     __IOPORT(0x3c6) /* PEL mask register. */

/* EGA-specific registers */
#define EGA_GFX_E0      __IOPORT(0x3cc) /* Graphics enable processor 0. */
#define EGA_GFX_E1      __IOPORT(0x3ca) /* Graphics enable processor 1. */

/* VGA index register ports */
#define VGA_CRT_IC      __IOPORT(0x3d4) /* CRT Controller Index - color emulation. */
#define VGA_CRT_IM      __IOPORT(0x3b4) /* CRT Controller Index - mono emulation. */
#define VGA_ATT_IW      __IOPORT(0x3c0) /* Attribute Controller Index & Data Write Register. */
#   define VGA_ATT_IW_PAS 0x20          /* Palette Address Source (must be clear to modify ) */
#define VGA_GFX_I       __IOPORT(0x3ce) /* Graphics Controller Index. */
#define VGA_SEQ_I       __IOPORT(0x3c4) /* Sequencer Index. */
#define VGA_PEL_IW      __IOPORT(0x3c8) /* PEL Write Index. */
#define VGA_PEL_IR      __IOPORT(0x3c7) /* PEL Read Index. */

/* standard VGA indexes max counts */
#define VGA_CRT_C       0x19  /* Number of CRT Controller Registers. */
#define VGA_ATT_C       0x15  /* Number of Attribute Controller Registers. */
#define VGA_GFX_C       0x09  /* Number of Graphics Controller Registers. */
#define VGA_SEQ_C       0x05  /* Number of Sequencer Registers. */
#define VGA_MIS_C       0x01  /* Number of Misc Output Register. */




/* VGA CRT controller register indices */
#define VGA_CRTC_H_TOTAL       0x00
#define VGA_CRTC_H_DISP        0x01
#define VGA_CRTC_H_BLANK_START 0x02
#define VGA_CRTC_H_BLANK_END   0x03
#   define VGA_CR3_FMASK            0x1f /* Mask of bits used for hblank-end */
#   define VGA_CR3_FALWAYS1         0x80 /* Always set this bit when writing this register (backward compatibility) */
#define VGA_CRTC_H_SYNC_START  0x04
#define VGA_CRTC_H_SYNC_END    0x05
#   define VGA_CR5_FMASK            0x1f /* Mask of bits used for hsync-end */
#   define VGA_CR5_FH_BLANK_END_5   0x80 /* 5th bit for `VGA_CRTC_H_BLANK_END' */
#define VGA_CRTC_V_TOTAL       0x06
#define VGA_CRTC_OVERFLOW      0x07
#   define VGA_CR7_FV_TOTAL_8       0x01 /* 8th bit for `VGA_CRTC_V_TOTAL' */
#   define VGA_CR7_FV_DISP_END_8    0x02 /* 8th bit for `VGA_CRTC_V_DISP_END' */
#   define VGA_CR7_FV_SYNC_START_8  0x04 /* 8th bit for `VGA_CRTC_V_SYNC_START' */
#   define VGA_CR7_FV_BLANK_START_8 0x08 /* 8th bit for `VGA_CRTC_V_BLANK_START' */
#   define VGA_CR7_FV_LINECOMP_8    0x10 /* 8th bit for `VGA_CRTC_LINE_COMPARE' */
#   define VGA_CR7_FV_TOTAL_9       0x20 /* 9th bit for `VGA_CRTC_V_TOTAL' */
#   define VGA_CR7_FV_DISP_END_9    0x40 /* 9th bit for `VGA_CRTC_V_DISP_END' */
#   define VGA_CR7_FV_SYNC_START_9  0x80 /* 9th bit for `VGA_CRTC_V_SYNC_START' */
#define VGA_CRTC_PRESET_ROW    0x08
#   define VGA_CR8_FRESERVED        0x80 /* Mask of reserved registers */
#define VGA_CRTC_MAX_SCAN      0x09
#   define VGA_CR9_FMASK            0x1f /* Mask of bits used for max-scan */
#   define VGA_CR9_FV_BLANK_START_9 0x20 /* 9th bit for `VGA_CRTC_V_BLANK_START' */
#   define VGA_CR9_FV_LINECOMP_9    0x40 /* 9th bit for `VGA_CRTC_LINE_COMPARE' */
#   define VGA_CR9_FSCANDOUBLE      0x80 /* Better don't set... (Don't really understand what this done) */
#define VGA_CRTC_CURSOR_START  0x0a
#   define VGA_CRA_FCURSOR_DISABLE  0x20 /* Disable the text-mode cursor */
#   define VGA_CRA_FRESERVED        0xc0 /* Mask of reserved registers */
#define VGA_CRTC_CURSOR_END    0x0b
#   define VGA_CRB_FRESERVED        0x80 /* Mask of reserved registers */
#define VGA_CRTC_START_HI      0x0c
#define VGA_CRTC_START_LO      0x0d
#define VGA_CRTC_CURSOR_HI     0x0e
#define VGA_CRTC_CURSOR_LO     0x0f
#define VGA_CRTC_V_SYNC_START  0x10
#define VGA_CRTC_V_SYNC_END    0x11
#   define VGA_CR11_FRESERVED       0x30 /* Mask of reserved registers */
#   define VGA_CR11_FMASK           0x0f /* Mask of bits used for vsync-end */
#   define VGA_CR11_FLOCK_CR0_CR7   0x80 /* lock writes to CR0 - CR7. */
#define VGA_CRTC_V_DISP_END    0x12
#define VGA_CRTC_OFFSET        0x13
#define VGA_CRTC_UNDERLINE     0x14
#define VGA_CRTC_V_BLANK_START 0x15
#define VGA_CRTC_V_BLANK_END   0x16
#   define VGA_CR16_FRESERVED       0x80 /* Mask of reserved registers */
#define VGA_CRTC_MODE          0x17
#   define VGA_CR17_FRESERVED       0x10 /* Mask of reserved registers */
#   define VGA_CR17_FH_V_SIGNALS_ENABLED 0x80
#define VGA_CRTC_LINE_COMPARE  0x18
#define VGA_CRTC_REGS          VGA_CRT_C




/* VGA attribute controller register indices */
#define VGA_ATC_PALETTE0       0x00
#define VGA_ATC_PALETTE1       0x01
#define VGA_ATC_PALETTE2       0x02
#define VGA_ATC_PALETTE3       0x03
#define VGA_ATC_PALETTE4       0x04
#define VGA_ATC_PALETTE5       0x05
#define VGA_ATC_PALETTE6       0x06
#define VGA_ATC_PALETTE7       0x07
#define VGA_ATC_PALETTE8       0x08
#define VGA_ATC_PALETTE9       0x09
#define VGA_ATC_PALETTEA       0x0a
#define VGA_ATC_PALETTEB       0x0b
#define VGA_ATC_PALETTEC       0x0c
#define VGA_ATC_PALETTED       0x0d
#define VGA_ATC_PALETTEE       0x0e
#define VGA_ATC_PALETTEF       0x0f
#   define VGA_ATC_PALETTEn_FRESERVED 0xc0
#define VGA_ATC_MODE           0x10
#   define VGA_AT10_FRESERVED       0x10 /* Mask of reserved registers */
#   define VGA_AT10_FGRAPHICS       0x01 /* Enable graphics, rather than alphanumeric mode */
#   define VGA_AT10_FDUP9           0x04 /* Duplicate the 8`th text dot into the 9`th when `VGA_SR01_CHAR_CLK_8DOTS' isn't set, instead of filling it with background */
#   define VGA_AT10_FBLINK          0x08 /* Set to cause character attribute bit #7 to be used for blinking text;
                                          * NEVER SET THIS! YOU'LL CAUSE SEIZURES IN PEOPLE
                                          * WARNING: After boot, a BIOS mode switch, or a video card reset, this flag
                                          *          is enabled and _MUST_ under all circumstances be disabled again! */
#   define VGA_AT10_F8BITPAL        0x40 /* 8-bit palette index */
#define VGA_ATC_OVERSCAN       0x11
#define VGA_ATC_PLANE_ENABLE   0x12
#   define VGA_AT12_FMASK           0x0f /* Mask of planes */
#   define VGA_AT12_FRESERVED       0xf0 /* Mask of reserved registers */
#define VGA_ATC_PEL            0x13
#   define VGA_AT13_FMASK           0x0f /* Mask for pixel panning */
#   define VGA_AT13_FRESERVED       0xf0 /* Mask of reserved registers */
#define VGA_ATC_COLOR_PAGE     0x14
#   define VGA_AT14_FRESERVED       0xf0 /* Mask of reserved registers */

#define VGA_AR_ENABLE_DISPLAY  0x20




/* VGA sequencer register indices */
#define VGA_SEQ_RESET          0x00
#define VGA_SEQ_CLOCK_MODE     0x01
#   define VGA_SR01_FCHAR_CLK_8DOTS 0x01 /* bit 0: character clocks 8 dots wide are generated */
#   define VGA_SR01_FSCREEN_OFF     0x20 /* bit 5: Screen is off
                                          * NOTE: The `VGA_SETMODE' ioctl ignores this bit! */
#   define VGA_SR01_FRESERVED       0xc2 /* Mask of reserved registers */
#define VGA_SEQ_PLANE_WRITE    0x02
#   define VGA_SR02_FPLANE(i)     ((1) << (i)) /* ... */
#   define VGA_SR02_FALL_PLANES     0x0f /* bits 3-0: enable access to all planes */
#   define VGA_SR02_FRESERVED       0xf0 /* Mask of reserved registers */
#define VGA_SEQ_CHARACTER_MAP  0x03
#   define VGA_SR03_CSETB_MASK      0x13 /* Mask for character set B */
#   define VGA_SR03_CSETA_MASK      0x2c /* Mask for character set A */
#   define VGA_SR03_CSETB_GET(x) (((x) & 3) | (((x) >> 2) & 4))        /* Extract character set B index */
#   define VGA_SR03_CSETA_GET(x) ((((x) >> 2) & 3) | (((x) >> 3) & 4)) /* Extract character set A index */
#   define VGA_SR03_CSETB_SET(i) (((i) & 3) | (((i) & 4) << 2))        /* Encode character set B index */
#   define VGA_SR03_CSETA_SET(i) ((((i) & 3) << 2) | (((i) & 4) << 3)) /* Encode character set A index */
/* Character set indices (returned by `VGA_SR03_CSET(A|B)_GET'; encoded by `VGA_SR03_CSET(A|B)_SET') */
#      define VGA_SR03_CSET_0000_1FFF 0 /* Font is stored at in plane 2 at 0000h-1FFFh */
#      define VGA_SR03_CSET_4000_5FFF 1 /* Font is stored at in plane 2 at 4000h-5FFFh */
#      define VGA_SR03_CSET_8000_9FFF 2 /* Font is stored at in plane 2 at 8000h-9FFFh */
#      define VGA_SR03_CSET_C000_DFFF 3 /* Font is stored at in plane 2 at C000h-DFFFh */
#      define VGA_SR03_CSET_2000_3FFF 4 /* Font is stored at in plane 2 at 2000h-3FFFh */
#      define VGA_SR03_CSET_6000_7FFF 5 /* Font is stored at in plane 2 at 6000h-7FFFh */
#      define VGA_SR03_CSET_A000_BFFF 6 /* Font is stored at in plane 2 at A000h-BFFFh */
#      define VGA_SR03_CSET_E000_FFFF 7 /* Font is stored at in plane 2 at E000h-FFFFh */
#   define VGA_SR03_FRESERVED       0xc0 /* Mask of reserved registers */
#define VGA_SEQ_MEMORY_MODE    0x04
#   define VGA_SR04_FEXT_MEM        0x02 /* bit 1: allows complete mem access to 256K */
#   define VGA_SR04_FSEQ_MODE       0x04 /* bit 2: directs system to use a sequential addressing mode */
#   define VGA_SR04_FCHN_4M         0x08 /* bit 3: selects modulo 4 addressing for CPU access to display memory */
#   define VGA_SR04_FRESERVED       0xf1 /* Mask of reserved registers */




/* VGA graphics controller register indices */
#define VGA_GFX_SR_VALUE        0x00
#   define VGA_GR00_FMASK           0x0f /* Mask-index or'd onto the input value during writes (should be `0x00') */
#   define VGA_GR00_FRESERVED       0xf0 /* Mask of reserved registers */
#define VGA_GFX_SR_ENABLE       0x01
#   define VGA_GR01_FMASK           0x0f /* Mask-index describing which bits are actually used from input values during writes (should be `0x00') */
#   define VGA_GR01_FRESERVED       0xf0 /* Mask of reserved registers */
#define VGA_GFX_COMPARE_VALUE   0x02
#   define VGA_GR02_FRESERVED       0xf0 /* Mask of reserved registers */
#define VGA_GFX_DATA_ROTATE     0x03
#   define VGA_GR03_FRESERVED       0xe0 /* Mask of reserved registers */
#define VGA_GFX_PLANE_READ      0x04
#   define VGA_GR04_FREADMAP        0x03 /* Source plane index in read-mode #0. */
#   define VGA_GR04_READMAP(i)      (i)  /* Read from the i'th source plane. */
#   define VGA_GR04_FRESERVED       0xfc /* Mask of reserved registers */
#define VGA_GFX_MODE            0x05
#   define VGA_GR05_FWRITEMODE_0    0x00 /* Write mode #0. */
#   define VGA_GR05_FWRITEMODE_1    0x01 /* Write mode #1. */
#   define VGA_GR05_FWRITEMODE_2    0x02 /* Write mode #2. */
#   define VGA_GR05_FWRITEMODE_3    0x03 /* Write mode #3. */
#   define VGA_GR05_FWRITEMODE      0x03 /* Mask */
#   define VGA_GR05_FREADMODE_0     0x00 /* Read mode #0. */
#   define VGA_GR05_FREADMODE_1     0x08 /* Read mode #1. */
#   define VGA_GR05_FREADMODE       0x08 /* Mask */
#   define VGA_GR05_FHOSTOE         0x10 /* Enable odd/even mode (used for 16-bit-per-character text-mode). */
#   define VGA_GR05_FSHIFTREG       0x20 /* ... */
#   define VGA_GR05_FSHIFT256       0x40 /* ... */
#   define VGA_GR05_FRESERVED       0x84 /* Mask of reserved registers */
#define VGA_GFX_MISC            0x06
#   define VGA_GR06_FTEXT_MODE      0x00 /* Enable text-mode (as opposed to graphics-mode) */
#   define VGA_GR06_FGRAPHICS_MODE  0x01 /* Enable graphics-mode (as opposed to text-mode) */
#   define VGA_GR06_FCHAINOE        0x02 /* Use address bit #0 to select between even/odd maps */
#   define VGA_GR06_FMM_128K        0x00 /* A0000h-BFFFFh (128K region) */
#   define VGA_GR06_FMM_64K         0x04 /* A0000h-AFFFFh (64K region) */
#   define VGA_GR06_FMM_32K_LO      0x08 /* B0000h-B7FFFh (32K region) */
#   define VGA_GR06_FMM_32K_HI      0x0c /* B8000h-BFFFFh (32K region) */
#   define VGA_GR06_FMM_MASK        0x0c /* Mask for memory mode */
#   define VGA_GR06_FMM_SHIFT       2    /* Shift for memory mode */
#   define VGA_GR06_FRESERVED       0xf0 /* Mask of reserved registers */
#define VGA_GFX_COMPARE_MASK    0x07
#   define VGA_GR07_FRESERVED       0xf0 /* Mask of reserved registers */
#define VGA_GFX_BIT_MASK        0x08
/* === END OF LINUX-DERIVED CONTENT === */




#ifdef __CC__
struct __ATTR_PACKED vga_palcolor {
	/* NOTE: Yes, VGA palette colors are only 6-bit per channel! */
	__uint8_t vpc_r; /* Red color component (00h-3fh). */
	__uint8_t vpc_g; /* Green color component (00h-3fh). */
	__uint8_t vpc_b; /* Blue color component (00h-3fh). */
};

struct __ATTR_PACKED vga_mode {
	__uint8_t vm_att_pal[16];       /* VGA_ATC_PALETTEn. */
	__uint8_t vm_att_mode;          /* VGA_ATC_MODE. */
	__uint8_t vm_att_overscan;      /* VGA_ATC_OVERSCAN. */
	__uint8_t vm_att_plane_enable;  /* VGA_ATC_PLANE_ENABLE. */
	__uint8_t vm_att_pel;           /* VGA_ATC_PEL. */
	__uint8_t vm_att_color_page;    /* VGA_ATC_COLOR_PAGE. */

	__uint8_t vm_mis;               /* VGA_MIS_R / VGA_MIS_W. */

	__uint8_t vm_gfx_sr_value;      /* VGA_GFX_SR_VALUE. */
	__uint8_t vm_gfx_sr_enable;     /* VGA_GFX_SR_ENABLE. */
	__uint8_t vm_gfx_compare_value; /* VGA_GFX_COMPARE_VALUE. */
	__uint8_t vm_gfx_data_rotate;   /* VGA_GFX_DATA_ROTATE. */
	__uint8_t vm_gfx_plane_read;    /* VGA_GFX_PLANE_READ. */
	__uint8_t vm_gfx_mode;          /* VGA_GFX_MODE. */
	__uint8_t vm_gfx_misc;          /* VGA_GFX_MISC. */
	__uint8_t vm_gfx_compare_mask;  /* VGA_GFX_COMPARE_MASK. */
	__uint8_t vm_gfx_bit_mask;      /* VGA_GFX_BIT_MASK. */

	__uint8_t vm_crt_h_total;       /* VGA_CRTC_H_TOTAL. */
	__uint8_t vm_crt_h_disp;        /* VGA_CRTC_H_DISP. */
	__uint8_t vm_crt_h_blank_start; /* VGA_CRTC_H_BLANK_START. */
	__uint8_t vm_crt_h_blank_end;   /* VGA_CRTC_H_BLANK_END. */
	__uint8_t vm_crt_h_sync_start;  /* VGA_CRTC_H_SYNC_START. */
	__uint8_t vm_crt_h_sync_end;    /* VGA_CRTC_H_SYNC_END. */
	__uint8_t vm_crt_v_total;       /* VGA_CRTC_V_TOTAL. */
	__uint8_t vm_crt_overflow;      /* VGA_CRTC_OVERFLOW. */
	__uint8_t vm_crt_preset_row;    /* VGA_CRTC_PRESET_ROW. */
	__uint8_t vm_crt_max_scan;      /* VGA_CRTC_MAX_SCAN. */
	__uint8_t vm_crt_cursor_start;  /* VGA_CRTC_CURSOR_START. */
	__uint8_t vm_crt_cursor_end;    /* VGA_CRTC_CURSOR_END. */
	__uint8_t vm_crt_start_hi;      /* VGA_CRTC_START_HI. */
	__uint8_t vm_crt_start_lo;      /* VGA_CRTC_START_LO. */
	__uint8_t vm_crt_cursor_hi;     /* VGA_CRTC_CURSOR_HI. */
	__uint8_t vm_crt_cursor_lo;     /* VGA_CRTC_CURSOR_LO. */
	__uint8_t vm_crt_v_sync_start;  /* VGA_CRTC_V_SYNC_START. */
	__uint8_t vm_crt_v_sync_end;    /* VGA_CRTC_V_SYNC_END. */
	__uint8_t vm_crt_v_disp_end;    /* VGA_CRTC_V_DISP_END. */
	__uint8_t vm_crt_offset;        /* VGA_CRTC_OFFSET. */
	__uint8_t vm_crt_underline;     /* VGA_CRTC_UNDERLINE. */
	__uint8_t vm_crt_v_blank_start; /* VGA_CRTC_V_BLANK_START. */
	__uint8_t vm_crt_v_blank_end;   /* VGA_CRTC_V_BLANK_END. */
	__uint8_t vm_crt_mode;          /* VGA_CRTC_MODE. */
	__uint8_t vm_crt_line_compare;  /* VGA_CRTC_LINE_COMPARE. */

	__uint8_t vm_seq_clock_mode;    /* VGA_SEQ_CLOCK_MODE. */
	__uint8_t vm_seq_plane_write;   /* VGA_SEQ_PLANE_WRITE. */
	__uint8_t vm_seq_character_map; /* VGA_SEQ_CHARACTER_MAP. */
	__uint8_t vm_seq_memory_mode;   /* VGA_SEQ_MEMORY_MODE. */
};


/* Full VGA register state (not just mode registers) */
struct __ATTR_PACKED vga_regs {
	struct vga_mode vr_mode;      /* Mode registers. */
	__uint8_t       vr_seq_reset; /* VGA_SEQ_RESET. */
	__uint8_t       vr_ftc;       /* VGA_FTC_R. */
	__uint8_t       vr_crt_index; /* VGA_CRT_DC / VGA_CRT_IC. */
	__uint8_t       vr_seq_index; /* VGA_SEQ_I. */
	__uint8_t       vr_gfx_index; /* VGA_GFX_I. */
	__uint8_t       vr_att_index; /* VGA_ATT_IW. */

};

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_HW_VIDEO_VGA_H */
