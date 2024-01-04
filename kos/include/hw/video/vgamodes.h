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
#ifndef _HW_VIDEO_VGAMODES_H
#define _HW_VIDEO_VGAMODES_H 1

#include <__stdinc.h>

#include <hw/video/vga.h>

/* VGA Video mode register sets. */


/************************************************************************/
/* EGA                                                                  */
/************************************************************************/

/* EGA registers (320x200x16) */
#define VGAMODE_INIT_EGA_320X200X16                                               \
	{                                                                             \
		.vm_att_pal           = {                                                 \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,                       \
			0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,                       \
		},                                                                        \
		.vm_att_mode          = VGA_AT10_FGRAPHICS,                               \
		.vm_att_overscan      = 0x00,                                             \
		.vm_att_plane_enable  = 0x0f,                                             \
		.vm_att_pel           = 0x00,                                             \
		.vm_att_color_page    = 0x00,                                             \
		.vm_mis               = VGA_MIS_FCLOCK_25175_640 | VGA_MIS_FCOLOR |       \
		                        VGA_MIS_FSEL_HIGH_PAGE | VGA_MIS_FENB_MEM_ACCESS, \
		.vm_gfx_sr_value      = 0x00,                                             \
		.vm_gfx_sr_enable     = 0x00,                                             \
		.vm_gfx_compare_value = 0x00,                                             \
		.vm_gfx_data_rotate   = 0x00,                                             \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                              \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0,     \
		.vm_gfx_misc          = VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K,       \
		.vm_gfx_compare_mask  = 0x0f,                                             \
		.vm_gfx_bit_mask      = 0xff,                                             \
		.vm_crt_h_total       = 0x37,                                             \
		.vm_crt_h_disp        = 0x27,                                             \
		.vm_crt_h_blank_start = 0x2d,                                             \
		.vm_crt_h_blank_end   = VGA_CR3_FALWAYS1 | 0x34,                          \
		.vm_crt_h_sync_start  = 0x30,                                             \
		.vm_crt_h_sync_end    = 0x14,                                             \
		.vm_crt_v_total       = 0x04,                                             \
		.vm_crt_overflow      = VGA_CR7_FV_TOTAL_8 | VGA_CR7_FV_LINECOMP_8,       \
		.vm_crt_preset_row    = 0x00,                                             \
		.vm_crt_max_scan      = 0x00,                                             \
		.vm_crt_cursor_start  = 0x00,                                             \
		.vm_crt_cursor_end    = 0x00,                                             \
		.vm_crt_start_hi      = 0x00,                                             \
		.vm_crt_start_lo      = 0x00,                                             \
		.vm_crt_cursor_hi     = 0x00,                                             \
		.vm_crt_cursor_lo     = 0x00,                                             \
		.vm_crt_v_sync_start  = 0xe1,                                             \
		.vm_crt_v_sync_end    = 0x24,                                             \
		.vm_crt_v_disp_end    = 0xc7,                                             \
		.vm_crt_offset        = 0x14,                                             \
		.vm_crt_underline     = 0x00,                                             \
		.vm_crt_v_blank_start = 0xe0,                                             \
		.vm_crt_v_blank_end   = 0xf0,                                             \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x63,             \
		.vm_crt_line_compare  = 0xff,                                             \
		.vm_seq_clock_mode    = VGA_SR01_FCHAR_CLK_8DOTS | 0x0a,                  \
		.vm_seq_plane_write   = VGA_SR02_FALL_PLANES,                             \
		.vm_seq_character_map = 0x00,                                             \
		.vm_seq_memory_mode   = VGA_SR04_FSEQ_MODE | VGA_SR04_FEXT_MEM,           \
	}

/* EGA registers (640x200x16) */
#define VGAMODE_INIT_EGA_640X200X16                                               \
	{                                                                             \
		.vm_att_pal           = {                                                 \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,                       \
			0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,                       \
		},                                                                        \
		.vm_att_mode          = VGA_AT10_FGRAPHICS,                               \
		.vm_att_overscan      = 0x00,                                             \
		.vm_att_plane_enable  = 0x0f,                                             \
		.vm_att_pel           = 0x00,                                             \
		.vm_att_color_page    = 0x00,                                             \
		.vm_mis               = VGA_MIS_FCLOCK_25175_640 | VGA_MIS_FCOLOR |       \
		                        VGA_MIS_FSEL_HIGH_PAGE | VGA_MIS_FENB_MEM_ACCESS, \
		.vm_gfx_sr_value      = 0x00,                                             \
		.vm_gfx_sr_enable     = 0x00,                                             \
		.vm_gfx_compare_value = 0x00,                                             \
		.vm_gfx_data_rotate   = 0x00,                                             \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                              \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0,     \
		.vm_gfx_misc          = VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K,       \
		.vm_gfx_compare_mask  = 0x0f,                                             \
		.vm_gfx_bit_mask      = 0xff,                                             \
		.vm_crt_h_total       = 0x70,                                             \
		.vm_crt_h_disp        = 0x4f,                                             \
		.vm_crt_h_blank_start = 0x59,                                             \
		.vm_crt_h_blank_end   = 0x2d,                                             \
		.vm_crt_h_sync_start  = 0x5e,                                             \
		.vm_crt_h_sync_end    = 0x06,                                             \
		.vm_crt_v_total       = 0x04,                                             \
		.vm_crt_overflow      = VGA_CR7_FV_TOTAL_8 | VGA_CR7_FV_LINECOMP_8,       \
		.vm_crt_preset_row    = 0x00,                                             \
		.vm_crt_max_scan      = 0x00,                                             \
		.vm_crt_cursor_start  = 0x00,                                             \
		.vm_crt_cursor_end    = 0x00,                                             \
		.vm_crt_start_hi      = 0x00,                                             \
		.vm_crt_start_lo      = 0x00,                                             \
		.vm_crt_cursor_hi     = 0x00,                                             \
		.vm_crt_cursor_lo     = 0x00,                                             \
		.vm_crt_v_sync_start  = 0xe0,                                             \
		.vm_crt_v_sync_end    = 0x23,                                             \
		.vm_crt_v_disp_end    = 0xc7,                                             \
		.vm_crt_offset        = 0x28,                                             \
		.vm_crt_underline     = 0x00,                                             \
		.vm_crt_v_blank_start = 0xdf,                                             \
		.vm_crt_v_blank_end   = 0xef,                                             \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x63,             \
		.vm_crt_line_compare  = 0xff,                                             \
		.vm_seq_clock_mode    = VGA_SR01_FCHAR_CLK_8DOTS,                         \
		.vm_seq_plane_write   = VGA_SR02_FALL_PLANES,                             \
		.vm_seq_character_map = 0x00,                                             \
		.vm_seq_memory_mode   = VGA_SR04_FSEQ_MODE | VGA_SR04_FEXT_MEM,           \
	}

/* EGA registers (640x350x16) */
#define VGAMODE_INIT_EGA_640X350X16                                                  \
	{                                                                                \
		.vm_att_pal           = {                                                    \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,                          \
			0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,                          \
		},                                                                           \
		.vm_att_mode          = VGA_AT10_FGRAPHICS,                                  \
		.vm_att_overscan      = 0x00,                                                \
		.vm_att_plane_enable  = 0x0f,                                                \
		.vm_att_pel           = 0x00,                                                \
		.vm_att_color_page    = 0x00,                                                \
		.vm_mis               = VGA_MIS_FCOLOR | VGA_MIS_FSEL_HIGH_PAGE |            \
		                        VGA_MIS_FENB_MEM_ACCESS | VGA_MIS_FVSYNCPOL |        \
		                        0x04,                                                \
		.vm_gfx_sr_value      = 0x00,                                                \
		.vm_gfx_sr_enable     = 0x00,                                                \
		.vm_gfx_compare_value = 0x00,                                                \
		.vm_gfx_data_rotate   = 0x00,                                                \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                                 \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0,        \
		.vm_gfx_misc          = VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K,          \
		.vm_gfx_compare_mask  = 0x0f,                                                \
		.vm_gfx_bit_mask      = 0xff,                                                \
		.vm_crt_h_total       = 0x5b,                                                \
		.vm_crt_h_disp        = 0x4f,                                                \
		.vm_crt_h_blank_start = 0x53,                                                \
		.vm_crt_h_blank_end   = VGA_CR3_FALWAYS1 | 0x34,                             \
		.vm_crt_h_sync_start  = 0x52,                                                \
		.vm_crt_h_sync_end    = 0x00,                                                \
		.vm_crt_v_total       = 0x6c,                                                \
		.vm_crt_overflow      = VGA_CR7_FV_SYNC_START_8 | VGA_CR7_FV_BLANK_START_8 | \
		                        VGA_CR7_FV_TOTAL_8 | VGA_CR7_FV_DISP_END_8 |         \
		                        VGA_CR7_FV_LINECOMP_8,                               \
		.vm_crt_preset_row    = 0x00,                                                \
		.vm_crt_max_scan      = 0x00,                                                \
		.vm_crt_cursor_start  = 0x00,                                                \
		.vm_crt_cursor_end    = 0x00,                                                \
		.vm_crt_start_hi      = 0x00,                                                \
		.vm_crt_start_lo      = 0x00,                                                \
		.vm_crt_cursor_hi     = 0x00,                                                \
		.vm_crt_cursor_lo     = 0x00,                                                \
		.vm_crt_v_sync_start  = 0x5e,                                                \
		.vm_crt_v_sync_end    = 0x2b,                                                \
		.vm_crt_v_disp_end    = 0x5e,                                                \
		.vm_crt_offset        = 0x28,                                                \
		.vm_crt_underline     = 0x0f,                                                \
		.vm_crt_v_blank_start = 0x5f,                                                \
		.vm_crt_v_blank_end   = 0x0a,                                                \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x63,                \
		.vm_crt_line_compare  = 0xff,                                                \
		.vm_seq_clock_mode    = VGA_SR01_FCHAR_CLK_8DOTS,                            \
		.vm_seq_plane_write   = VGA_SR02_FALL_PLANES,                                \
		.vm_seq_character_map = 0x00,                                                \
		.vm_seq_memory_mode   = VGA_SR04_FSEQ_MODE | VGA_SR04_FEXT_MEM,              \
	}

/* EGA registers (text) */
#define VGAMODE_INIT_EGA_TEXT                                                        \
	{                                                                                \
		.vm_att_pal           = {                                                    \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,                          \
			0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,                          \
		},                                                                           \
		.vm_att_mode          = VGA_AT10_FBLINK | 0x02,                              \
		.vm_att_overscan      = 0x00,                                                \
		.vm_att_plane_enable  = 0x0f,                                                \
		.vm_att_pel           = 0x00,                                                \
		.vm_att_color_page    = 0x00,                                                \
		.vm_mis               = VGA_MIS_FCOLOR | VGA_MIS_FSEL_HIGH_PAGE |            \
		                        VGA_MIS_FENB_MEM_ACCESS | VGA_MIS_FVSYNCPOL |        \
		                        0x04,                                                \
		.vm_gfx_sr_value      = 0x00,                                                \
		.vm_gfx_sr_enable     = 0x00,                                                \
		.vm_gfx_compare_value = 0x00,                                                \
		.vm_gfx_data_rotate   = 0x00,                                                \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                                 \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0 |       \
		                        VGA_GR05_FHOSTOE,                                    \
		.vm_gfx_misc          = VGA_GR06_FTEXT_MODE | VGA_GR06_FCHAINOE |            \
		                        VGA_GR06_FMM_32K_HI,                                 \
		.vm_gfx_compare_mask  = 0x00,                                                \
		.vm_gfx_bit_mask      = 0xff,                                                \
		.vm_crt_h_total       = 0x5b,                                                \
		.vm_crt_h_disp        = 0x4f,                                                \
		.vm_crt_h_blank_start = 0x53,                                                \
		.vm_crt_h_blank_end   = VGA_CR3_FALWAYS1 | 0x34,                             \
		.vm_crt_h_sync_start  = 0x51,                                                \
		.vm_crt_h_sync_end    = 0x5b,                                                \
		.vm_crt_v_total       = 0x6c,                                                \
		.vm_crt_overflow      = VGA_CR7_FV_SYNC_START_8 | VGA_CR7_FV_BLANK_START_8 | \
		                        VGA_CR7_FV_TOTAL_8 | VGA_CR7_FV_DISP_END_8 |         \
		                        VGA_CR7_FV_LINECOMP_8,                               \
		.vm_crt_preset_row    = 0x00,                                                \
		.vm_crt_max_scan      = 0x0d,                                                \
		.vm_crt_cursor_start  = 0x0a,                                                \
		.vm_crt_cursor_end    = 0x0c,                                                \
		.vm_crt_start_hi      = 0x00,                                                \
		.vm_crt_start_lo      = 0x00,                                                \
		.vm_crt_cursor_hi     = 0x00,                                                \
		.vm_crt_cursor_lo     = 0x00,                                                \
		.vm_crt_v_sync_start  = 0x5e,                                                \
		.vm_crt_v_sync_end    = 0x2b,                                                \
		.vm_crt_v_disp_end    = 0x5d,                                                \
		.vm_crt_offset        = 0x28,                                                \
		.vm_crt_underline     = 0x0f,                                                \
		.vm_crt_v_blank_start = 0x5e,                                                \
		.vm_crt_v_blank_end   = 0x0a,                                                \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x23,                \
		.vm_crt_line_compare  = 0xff,                                                \
		.vm_seq_clock_mode    = VGA_SR01_FCHAR_CLK_8DOTS,                            \
		.vm_seq_plane_write   = VGA_SR02_FPLANE(0) | VGA_SR02_FPLANE(1),             \
		.vm_seq_character_map = VGA_SR03_CSETA_SET(VGA_SR03_CSET_0000_1FFF) |        \
		                        VGA_SR03_CSETB_SET(VGA_SR03_CSET_0000_1FFF),         \
		.vm_seq_memory_mode   = VGA_SR04_FEXT_MEM | 0x01,                            \
	}






/************************************************************************/
/* VGA                                                                  */
/************************************************************************/

/* VGA registers (80x25 text mode) */
#define VGAMODE_INIT_VGA_TEXT                                                        \
	{                                                                                \
		.vm_att_pal           = {                                                    \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,                          \
			0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,                          \
		},                                                                           \
		.vm_att_mode          = VGA_AT10_FDUP9,                                      \
		.vm_att_overscan      = 0x00,                                                \
		.vm_att_plane_enable  = 0x0f,                                                \
		.vm_att_pel           = 0x08,                                                \
		.vm_att_color_page    = 0x00,                                                \
		.vm_mis               = VGA_MIS_FCOLOR | VGA_MIS_FENB_MEM_ACCESS |           \
		                        VGA_MIS_FCLOCK_28322_720 | VGA_MIS_FHSYNCPOL |       \
		                        VGA_MIS_FSEL_HIGH_PAGE,                              \
		.vm_gfx_sr_value      = 0x00,                                                \
		.vm_gfx_sr_enable     = 0x00,                                                \
		.vm_gfx_compare_value = 0x00,                                                \
		.vm_gfx_data_rotate   = 0x00,                                                \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                                 \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0 |       \
		                        VGA_GR05_FHOSTOE,                                    \
		.vm_gfx_misc          = VGA_GR06_FTEXT_MODE | VGA_GR06_FCHAINOE |            \
		                        VGA_GR06_FMM_32K_HI,                                 \
		.vm_gfx_compare_mask  = 0x0f,                                                \
		.vm_gfx_bit_mask      = 0xff,                                                \
		.vm_crt_h_total       = 0x5f,                                                \
		.vm_crt_h_disp        = 0x4f,                                                \
		.vm_crt_h_blank_start = 0x50,                                                \
		.vm_crt_h_blank_end   = VGA_CR3_FALWAYS1 | 0x02,                             \
		.vm_crt_h_sync_start  = 0x55,                                                \
		.vm_crt_h_sync_end    = VGA_CR5_FH_BLANK_END_5 | 0x01,                       \
		.vm_crt_v_total       = 0xbf,                                                \
		.vm_crt_overflow      = VGA_CR7_FV_TOTAL_8 | VGA_CR7_FV_DISP_END_8 |         \
		                        VGA_CR7_FV_SYNC_START_8 | VGA_CR7_FV_BLANK_START_8 | \
		                        VGA_CR7_FV_LINECOMP_8,                               \
		.vm_crt_preset_row    = 0x00,                                                \
		.vm_crt_max_scan      = VGA_CR9_FV_LINECOMP_9 | 0x0f,                        \
		.vm_crt_cursor_start  = 0x0d,                                                \
		.vm_crt_cursor_end    = 0x0e,                                                \
		.vm_crt_start_hi      = 0x00,                                                \
		.vm_crt_start_lo      = 0x00,                                                \
		.vm_crt_cursor_hi     = 0x00,                                                \
		.vm_crt_cursor_lo     = 0x00,                                                \
		.vm_crt_v_sync_start  = 0x9c,                                                \
		.vm_crt_v_sync_end    = VGA_CR11_FLOCK_CR0_CR7 | 0x0e,                       \
		.vm_crt_v_disp_end    = 0x8f,                                                \
		.vm_crt_offset        = 0x28,                                                \
		.vm_crt_underline     = 0x1f,                                                \
		.vm_crt_v_blank_start = 0x96,                                                \
		.vm_crt_v_blank_end   = 0x39,                                                \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x23,                \
		.vm_crt_line_compare  = 0xff,                                                \
		.vm_seq_clock_mode    = 0x00,                                                \
		.vm_seq_plane_write   = VGA_SR02_FPLANE(0) | VGA_SR02_FPLANE(1),             \
		.vm_seq_character_map = VGA_SR03_CSETA_SET(VGA_SR03_CSET_0000_1FFF) |        \
		                        VGA_SR03_CSETB_SET(VGA_SR03_CSET_0000_1FFF),         \
		.vm_seq_memory_mode   = VGA_SR04_FEXT_MEM,                                   \
	}

/* VGA registers (320x200x16) */
#define VGAMODE_INIT_VGA_320X200X16                                                  \
	{                                                                                \
		.vm_att_pal           = {                                                    \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,                          \
			0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,                          \
		},                                                                           \
		.vm_att_mode          = VGA_AT10_FGRAPHICS,                                  \
		.vm_att_overscan      = 0x00,                                                \
		.vm_att_plane_enable  = 0x0f,                                                \
		.vm_att_pel           = 0x00,                                                \
		.vm_att_color_page    = 0x00,                                                \
		.vm_mis               = VGA_MIS_FCOLOR | VGA_MIS_FSEL_HIGH_PAGE |            \
		                        VGA_MIS_FENB_MEM_ACCESS | VGA_MIS_FHSYNCPOL,         \
		.vm_gfx_sr_value      = 0x00,                                                \
		.vm_gfx_sr_enable     = 0x00,                                                \
		.vm_gfx_compare_value = 0x00,                                                \
		.vm_gfx_data_rotate   = 0x20,                                                \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                                 \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0,        \
		.vm_gfx_misc          = VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K,          \
		.vm_gfx_compare_mask  = 0x0f,                                                \
		.vm_gfx_bit_mask      = 0xff,                                                \
		.vm_crt_h_total       = 0x2d,                                                \
		.vm_crt_h_disp        = 0x27,                                                \
		.vm_crt_h_blank_start = 0x28,                                                \
		.vm_crt_h_blank_end   = 0x90,                                                \
		.vm_crt_h_sync_start  = 0x2b,                                                \
		.vm_crt_h_sync_end    = VGA_CR5_FH_BLANK_END_5,                              \
		.vm_crt_v_total       = 0xbf,                                                \
		.vm_crt_overflow      = VGA_CR7_FV_SYNC_START_8 | VGA_CR7_FV_BLANK_START_8 | \
		                        VGA_CR7_FV_TOTAL_8 | VGA_CR7_FV_DISP_END_8 |         \
		                        VGA_CR7_FV_LINECOMP_8,                               \
		.vm_crt_preset_row    = 0x00,                                                \
		.vm_crt_max_scan      = VGA_CR9_FV_LINECOMP_9 | VGA_CR9_FSCANDOUBLE,         \
		.vm_crt_cursor_start  = 0x00,                                                \
		.vm_crt_cursor_end    = 0x00,                                                \
		.vm_crt_start_hi      = 0x00,                                                \
		.vm_crt_start_lo      = 0x00,                                                \
		.vm_crt_cursor_hi     = 0x00,                                                \
		.vm_crt_cursor_lo     = 0x00,                                                \
		.vm_crt_v_sync_start  = 0x9c,                                                \
		.vm_crt_v_sync_end    = VGA_CR11_FLOCK_CR0_CR7 | 0x0e,                       \
		.vm_crt_v_disp_end    = 0x8f,                                                \
		.vm_crt_offset        = 0x14,                                                \
		.vm_crt_underline     = 0x00,                                                \
		.vm_crt_v_blank_start = 0x96,                                                \
		.vm_crt_v_blank_end   = 0xb9,                                                \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x63,                \
		.vm_crt_line_compare  = 0xff,                                                \
		.vm_seq_clock_mode    = VGA_SR01_FCHAR_CLK_8DOTS | 0x08,                     \
		.vm_seq_plane_write   = VGA_SR02_FALL_PLANES,                                \
		.vm_seq_character_map = 0x00,                                                \
		.vm_seq_memory_mode   = VGA_SR04_FSEQ_MODE | VGA_SR04_FEXT_MEM,              \
	}

/* VGA registers (640x200x16) */
#define VGAMODE_INIT_VGA_640X200X16                                                  \
	{                                                                                \
		.vm_att_pal           = {                                                    \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,                          \
			0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,                          \
		},                                                                           \
		.vm_att_mode          = VGA_AT10_FGRAPHICS,                                  \
		.vm_att_overscan      = 0x00,                                                \
		.vm_att_plane_enable  = 0x0f,                                                \
		.vm_att_pel           = 0x00,                                                \
		.vm_att_color_page    = 0x00,                                                \
		.vm_mis               = VGA_MIS_FCOLOR | VGA_MIS_FSEL_HIGH_PAGE |            \
		                        VGA_MIS_FENB_MEM_ACCESS | VGA_MIS_FHSYNCPOL,         \
		.vm_gfx_sr_value      = 0x00,                                                \
		.vm_gfx_sr_enable     = 0x00,                                                \
		.vm_gfx_compare_value = 0x00,                                                \
		.vm_gfx_data_rotate   = 0x20,                                                \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                                 \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0,        \
		.vm_gfx_misc          = VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K,          \
		.vm_gfx_compare_mask  = 0x0f,                                                \
		.vm_gfx_bit_mask      = 0xff,                                                \
		.vm_crt_h_total       = 0x5f,                                                \
		.vm_crt_h_disp        = 0x4f,                                                \
		.vm_crt_h_blank_start = 0x50,                                                \
		.vm_crt_h_blank_end   = 0x82,                                                \
		.vm_crt_h_sync_start  = 0x54,                                                \
		.vm_crt_h_sync_end    = VGA_CR5_FH_BLANK_END_5,                              \
		.vm_crt_v_total       = 0xbf,                                                \
		.vm_crt_overflow      = VGA_CR7_FV_SYNC_START_8 | VGA_CR7_FV_BLANK_START_8 | \
		                        VGA_CR7_FV_TOTAL_8 | VGA_CR7_FV_DISP_END_8 |         \
		                        VGA_CR7_FV_LINECOMP_8,                               \
		.vm_crt_preset_row    = 0x00,                                                \
		.vm_crt_max_scan      = VGA_CR9_FV_LINECOMP_9 | VGA_CR9_FSCANDOUBLE,         \
		.vm_crt_cursor_start  = 0x00,                                                \
		.vm_crt_cursor_end    = 0x00,                                                \
		.vm_crt_start_hi      = 0x00,                                                \
		.vm_crt_start_lo      = 0x00,                                                \
		.vm_crt_cursor_hi     = 0x00,                                                \
		.vm_crt_cursor_lo     = 0x00,                                                \
		.vm_crt_v_sync_start  = 0x9c,                                                \
		.vm_crt_v_sync_end    = VGA_CR11_FLOCK_CR0_CR7 | 0x0e,                       \
		.vm_crt_v_disp_end    = 0x8f,                                                \
		.vm_crt_offset        = 0x28,                                                \
		.vm_crt_underline     = 0x00,                                                \
		.vm_crt_v_blank_start = 0x96,                                                \
		.vm_crt_v_blank_end   = 0xb9,                                                \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x63,                \
		.vm_crt_line_compare  = 0xff,                                                \
		.vm_seq_clock_mode    = VGA_SR01_FCHAR_CLK_8DOTS,                            \
		.vm_seq_plane_write   = VGA_SR02_FALL_PLANES,                                \
		.vm_seq_character_map = 0x00,                                                \
		.vm_seq_memory_mode   = VGA_SR04_FSEQ_MODE | VGA_SR04_FEXT_MEM,              \
	}

/* VGA registers (640x350x16) */
#define VGAMODE_INIT_VGA_640X350X16                                                  \
	{                                                                                \
		.vm_att_pal           = {                                                    \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,                          \
			0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,                          \
		},                                                                           \
		.vm_att_mode          = VGA_AT10_FGRAPHICS,                                  \
		.vm_att_overscan      = 0x00,                                                \
		.vm_att_plane_enable  = 0x0f,                                                \
		.vm_att_pel           = 0x00,                                                \
		.vm_att_color_page    = 0x00,                                                \
		.vm_mis               = VGA_MIS_FCOLOR | VGA_MIS_FSEL_HIGH_PAGE |            \
		                        VGA_MIS_FENB_MEM_ACCESS | VGA_MIS_FVSYNCPOL,         \
		.vm_gfx_sr_value      = 0x00,                                                \
		.vm_gfx_sr_enable     = 0x00,                                                \
		.vm_gfx_compare_value = 0x00,                                                \
		.vm_gfx_data_rotate   = 0x20,                                                \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                                 \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0,        \
		.vm_gfx_misc          = VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K,          \
		.vm_gfx_compare_mask  = 0x0f,                                                \
		.vm_gfx_bit_mask      = 0xff,                                                \
		.vm_crt_h_total       = 0x5f,                                                \
		.vm_crt_h_disp        = 0x4f,                                                \
		.vm_crt_h_blank_start = 0x50,                                                \
		.vm_crt_h_blank_end   = 0x82,                                                \
		.vm_crt_h_sync_start  = 0x54,                                                \
		.vm_crt_h_sync_end    = VGA_CR5_FH_BLANK_END_5,                              \
		.vm_crt_v_total       = 0xbf,                                                \
		.vm_crt_overflow      = VGA_CR7_FV_SYNC_START_8 | VGA_CR7_FV_BLANK_START_8 | \
		                        VGA_CR7_FV_TOTAL_8 | VGA_CR7_FV_DISP_END_8 |         \
		                        VGA_CR7_FV_LINECOMP_8,                               \
		.vm_crt_preset_row    = 0x00,                                                \
		.vm_crt_max_scan      = VGA_CR9_FV_LINECOMP_9,                               \
		.vm_crt_cursor_start  = 0x00,                                                \
		.vm_crt_cursor_end    = 0x00,                                                \
		.vm_crt_start_hi      = 0x00,                                                \
		.vm_crt_start_lo      = 0x00,                                                \
		.vm_crt_cursor_hi     = 0x00,                                                \
		.vm_crt_cursor_lo     = 0x00,                                                \
		.vm_crt_v_sync_start  = 0x83,                                                \
		.vm_crt_v_sync_end    = VGA_CR11_FLOCK_CR0_CR7 | 0x05,                       \
		.vm_crt_v_disp_end    = 0x5d,                                                \
		.vm_crt_offset        = 0x28,                                                \
		.vm_crt_underline     = 0x0f,                                                \
		.vm_crt_v_blank_start = 0x63,                                                \
		.vm_crt_v_blank_end   = 0xba,                                                \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x63,                \
		.vm_crt_line_compare  = 0xff,                                                \
		.vm_seq_clock_mode    = VGA_SR01_FCHAR_CLK_8DOTS,                            \
		.vm_seq_plane_write   = VGA_SR02_FALL_PLANES,                                \
		.vm_seq_character_map = 0x00,                                                \
		.vm_seq_memory_mode   = VGA_SR04_FSEQ_MODE | VGA_SR04_FEXT_MEM,              \
	}

/* VGA registers (640x480x16) */
#define VGAMODE_INIT_VGA_640X480X16                                                  \
	{                                                                                \
		.vm_att_pal           = {                                                    \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,                          \
			0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,                          \
		},                                                                           \
		.vm_att_mode          = VGA_AT10_FGRAPHICS,                                  \
		.vm_att_overscan      = 0x00,                                                \
		.vm_att_plane_enable  = 0x0f,                                                \
		.vm_att_pel           = 0x00,                                                \
		.vm_att_color_page    = 0x00,                                                \
		.vm_mis               = VGA_MIS_FCOLOR | VGA_MIS_FSEL_HIGH_PAGE |            \
		                        VGA_MIS_FENB_MEM_ACCESS | VGA_MIS_FHSYNCPOL |        \
		                        VGA_MIS_FVSYNCPOL,                                   \
		.vm_gfx_sr_value      = 0x00,                                                \
		.vm_gfx_sr_enable     = 0x00,                                                \
		.vm_gfx_compare_value = 0x00,                                                \
		.vm_gfx_data_rotate   = 0x20,                                                \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                                 \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0,        \
		.vm_gfx_misc          = VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K,          \
		.vm_gfx_compare_mask  = 0x0f,                                                \
		.vm_gfx_bit_mask      = 0xff,                                                \
		.vm_crt_h_total       = 0x5f,                                                \
		.vm_crt_h_disp        = 0x4f,                                                \
		.vm_crt_h_blank_start = 0x50,                                                \
		.vm_crt_h_blank_end   = 0x82,                                                \
		.vm_crt_h_sync_start  = 0x54,                                                \
		.vm_crt_h_sync_end    = VGA_CR5_FH_BLANK_END_5,                              \
		.vm_crt_v_total       = 0x0b,                                                \
		.vm_crt_overflow      = VGA_CR7_FV_SYNC_START_8 | VGA_CR7_FV_BLANK_START_8 | \
		                        VGA_CR7_FV_TOTAL_9 | VGA_CR7_FV_DISP_END_8 |         \
		                        VGA_CR7_FV_LINECOMP_8,                               \
		.vm_crt_preset_row    = 0x00,                                                \
		.vm_crt_max_scan      = VGA_CR9_FV_LINECOMP_9,                               \
		.vm_crt_cursor_start  = 0x00,                                                \
		.vm_crt_cursor_end    = 0x00,                                                \
		.vm_crt_start_hi      = 0x00,                                                \
		.vm_crt_start_lo      = 0x00,                                                \
		.vm_crt_cursor_hi     = 0x00,                                                \
		.vm_crt_cursor_lo     = 0x00,                                                \
		.vm_crt_v_sync_start  = 0xea,                                                \
		.vm_crt_v_sync_end    = VGA_CR11_FLOCK_CR0_CR7 | 0x0c,                       \
		.vm_crt_v_disp_end    = 0xdf,                                                \
		.vm_crt_offset        = 0x28,                                                \
		.vm_crt_underline     = 0x00,                                                \
		.vm_crt_v_blank_start = 0xe7,                                                \
		.vm_crt_v_blank_end   = 0x04,                                                \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x63,                \
		.vm_crt_line_compare  = 0xff,                                                \
		.vm_seq_clock_mode    = VGA_SR01_FCHAR_CLK_8DOTS,                            \
		.vm_seq_plane_write   = VGA_SR02_FALL_PLANES,                                \
		.vm_seq_character_map = 0x00,                                                \
		.vm_seq_memory_mode   = VGA_SR04_FSEQ_MODE | VGA_SR04_FEXT_MEM,              \
	}

/* VGA registers (320x200x256) */
#define VGAMODE_INIT_VGA_320X200X256                                                 \
	{                                                                                \
		.vm_att_pal           = {                                                    \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,                          \
			0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,                          \
		},                                                                           \
		.vm_att_mode          = VGA_AT10_FGRAPHICS | VGA_AT10_F8BITPAL,              \
		.vm_att_overscan      = 0x00,                                                \
		.vm_att_plane_enable  = 0x0f,                                                \
		.vm_att_pel           = 0x00,                                                \
		.vm_att_color_page    = 0x00,                                                \
		.vm_mis               = VGA_MIS_FCOLOR | VGA_MIS_FSEL_HIGH_PAGE |            \
		                        VGA_MIS_FENB_MEM_ACCESS | VGA_MIS_FHSYNCPOL,         \
		.vm_gfx_sr_value      = 0x00,                                                \
		.vm_gfx_sr_enable     = 0x00,                                                \
		.vm_gfx_compare_value = 0x00,                                                \
		.vm_gfx_data_rotate   = 0x00,                                                \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                                 \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0 |       \
		                        VGA_GR05_FSHIFT256,                                  \
		.vm_gfx_misc          = VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K,          \
		.vm_gfx_compare_mask  = 0x0f,                                                \
		.vm_gfx_bit_mask      = 0xff,                                                \
		.vm_crt_h_total       = 0x5f,                                                \
		.vm_crt_h_disp        = 0x4f,                                                \
		.vm_crt_h_blank_start = 0x50,                                                \
		.vm_crt_h_blank_end   = 0x82,                                                \
		.vm_crt_h_sync_start  = 0x54,                                                \
		.vm_crt_h_sync_end    = VGA_CR5_FH_BLANK_END_5,                              \
		.vm_crt_v_total       = 0xbf,                                                \
		.vm_crt_overflow      = VGA_CR7_FV_SYNC_START_8 | VGA_CR7_FV_BLANK_START_8 | \
		                        VGA_CR7_FV_TOTAL_8 | VGA_CR7_FV_DISP_END_8 |         \
		                        VGA_CR7_FV_LINECOMP_8,                               \
		.vm_crt_preset_row    = 0x00,                                                \
		.vm_crt_max_scan      = VGA_CR9_FV_LINECOMP_9 | 0x01,                        \
		.vm_crt_cursor_start  = 0x00,                                                \
		.vm_crt_cursor_end    = 0x00,                                                \
		.vm_crt_start_hi      = 0x00,                                                \
		.vm_crt_start_lo      = 0x00,                                                \
		.vm_crt_cursor_hi     = 0x00,                                                \
		.vm_crt_cursor_lo     = 0x00,                                                \
		.vm_crt_v_sync_start  = 0x9c,                                                \
		.vm_crt_v_sync_end    = VGA_CR11_FLOCK_CR0_CR7 | 0x0e,                       \
		.vm_crt_v_disp_end    = 0x8f,                                                \
		.vm_crt_offset        = 0x28,                                                \
		.vm_crt_underline     = 0x40,                                                \
		.vm_crt_v_blank_start = 0x96,                                                \
		.vm_crt_v_blank_end   = 0xb9,                                                \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x23,                \
		.vm_crt_line_compare  = 0xff,                                                \
		.vm_seq_clock_mode    = VGA_SR01_FCHAR_CLK_8DOTS,                            \
		.vm_seq_plane_write   = VGA_SR02_FALL_PLANES,                                \
		.vm_seq_character_map = 0x00,                                                \
		.vm_seq_memory_mode   = VGA_SR04_FCHN_4M | VGA_SR04_FSEQ_MODE |              \
		                        VGA_SR04_FEXT_MEM,                                   \
	}

/* VGA registers (320x240x256) */
#define VGAMODE_INIT_VGA_320X240X256                                                 \
	{                                                                                \
		.vm_att_pal           = {                                                    \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,                          \
			0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,                          \
		},                                                                           \
		.vm_att_mode          = VGA_AT10_FGRAPHICS | VGA_AT10_F8BITPAL,              \
		.vm_att_overscan      = 0x00,                                                \
		.vm_att_plane_enable  = 0x0f,                                                \
		.vm_att_pel           = 0x00,                                                \
		.vm_att_color_page    = 0x00,                                                \
		.vm_mis               = VGA_MIS_FCOLOR | VGA_MIS_FSEL_HIGH_PAGE |            \
		                        VGA_MIS_FENB_MEM_ACCESS | VGA_MIS_FHSYNCPOL |        \
		                        VGA_MIS_FVSYNCPOL,                                   \
		.vm_gfx_sr_value      = 0x00,                                                \
		.vm_gfx_sr_enable     = 0x00,                                                \
		.vm_gfx_compare_value = 0x00,                                                \
		.vm_gfx_data_rotate   = 0x00,                                                \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                                 \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0 |       \
		                        VGA_GR05_FSHIFT256,                                  \
		.vm_gfx_misc          = VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K,          \
		.vm_gfx_compare_mask  = 0x0f,                                                \
		.vm_gfx_bit_mask      = 0xff,                                                \
		.vm_crt_h_total       = 0x5f,                                                \
		.vm_crt_h_disp        = 0x4f,                                                \
		.vm_crt_h_blank_start = 0x50,                                                \
		.vm_crt_h_blank_end   = 0x82,                                                \
		.vm_crt_h_sync_start  = 0x54,                                                \
		.vm_crt_h_sync_end    = VGA_CR5_FH_BLANK_END_5,                              \
		.vm_crt_v_total       = 0x0d,                                                \
		.vm_crt_overflow      = VGA_CR7_FV_SYNC_START_8 | VGA_CR7_FV_BLANK_START_8 | \
		                        VGA_CR7_FV_TOTAL_9 | VGA_CR7_FV_DISP_END_8 |         \
		                        VGA_CR7_FV_LINECOMP_8,                               \
		.vm_crt_preset_row    = 0x00,                                                \
		.vm_crt_max_scan      = VGA_CR9_FV_LINECOMP_9 | 0x01,                        \
		.vm_crt_cursor_start  = 0x00,                                                \
		.vm_crt_cursor_end    = 0x00,                                                \
		.vm_crt_start_hi      = 0x00,                                                \
		.vm_crt_start_lo      = 0x00,                                                \
		.vm_crt_cursor_hi     = 0x00,                                                \
		.vm_crt_cursor_lo     = 0x00,                                                \
		.vm_crt_v_sync_start  = 0xea,                                                \
		.vm_crt_v_sync_end    = VGA_CR11_FLOCK_CR0_CR7 | 0x2c,                       \
		.vm_crt_v_disp_end    = 0xdf,                                                \
		.vm_crt_offset        = 0x28,                                                \
		.vm_crt_underline     = 0x00,                                                \
		.vm_crt_v_blank_start = 0xe7,                                                \
		.vm_crt_v_blank_end   = 0x06,                                                \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x63,                \
		.vm_crt_line_compare  = 0xff,                                                \
		.vm_seq_clock_mode    = VGA_SR01_FCHAR_CLK_8DOTS,                            \
		.vm_seq_plane_write   = VGA_SR02_FALL_PLANES,                                \
		.vm_seq_character_map = 0x00,                                                \
		.vm_seq_memory_mode   = VGA_SR04_FSEQ_MODE | VGA_SR04_FEXT_MEM,              \
	}

/* VGA registers (320x400x256) */
#define VGAMODE_INIT_VGA_320X400X256                                                 \
	{                                                                                \
		.vm_att_pal           = {                                                    \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,                          \
			0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,                          \
		},                                                                           \
		.vm_att_mode          = VGA_AT10_FGRAPHICS | VGA_AT10_F8BITPAL,              \
		.vm_att_overscan      = 0x00,                                                \
		.vm_att_plane_enable  = 0x0f,                                                \
		.vm_att_pel           = 0x00,                                                \
		.vm_att_color_page    = 0x00,                                                \
		.vm_mis               = VGA_MIS_FCOLOR | VGA_MIS_FSEL_HIGH_PAGE |            \
		                        VGA_MIS_FENB_MEM_ACCESS | VGA_MIS_FHSYNCPOL,         \
		.vm_gfx_sr_value      = 0x00,                                                \
		.vm_gfx_sr_enable     = 0x00,                                                \
		.vm_gfx_compare_value = 0x00,                                                \
		.vm_gfx_data_rotate   = 0x00,                                                \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                                 \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0 |       \
		                        VGA_GR05_FSHIFT256,                                  \
		.vm_gfx_misc          = VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K,          \
		.vm_gfx_compare_mask  = 0x0f,                                                \
		.vm_gfx_bit_mask      = 0xff,                                                \
		.vm_crt_h_total       = 0x5f,                                                \
		.vm_crt_h_disp        = 0x4f,                                                \
		.vm_crt_h_blank_start = 0x50,                                                \
		.vm_crt_h_blank_end   = 0x82,                                                \
		.vm_crt_h_sync_start  = 0x54,                                                \
		.vm_crt_h_sync_end    = VGA_CR5_FH_BLANK_END_5,                              \
		.vm_crt_v_total       = 0xbf,                                                \
		.vm_crt_overflow      = VGA_CR7_FV_SYNC_START_8 | VGA_CR7_FV_BLANK_START_8 | \
		                        VGA_CR7_FV_TOTAL_8 | VGA_CR7_FV_DISP_END_8 |         \
		                        VGA_CR7_FV_LINECOMP_8,                               \
		.vm_crt_preset_row    = 0x00,                                                \
		.vm_crt_max_scan      = VGA_CR9_FV_LINECOMP_9,                               \
		.vm_crt_cursor_start  = 0x00,                                                \
		.vm_crt_cursor_end    = 0x00,                                                \
		.vm_crt_start_hi      = 0x00,                                                \
		.vm_crt_start_lo      = 0x00,                                                \
		.vm_crt_cursor_hi     = 0x00,                                                \
		.vm_crt_cursor_lo     = 0x00,                                                \
		.vm_crt_v_sync_start  = 0x9c,                                                \
		.vm_crt_v_sync_end    = VGA_CR11_FLOCK_CR0_CR7 | 0x0e,                       \
		.vm_crt_v_disp_end    = 0x8f,                                                \
		.vm_crt_offset        = 0x28,                                                \
		.vm_crt_underline     = 0x00,                                                \
		.vm_crt_v_blank_start = 0x96,                                                \
		.vm_crt_v_blank_end   = 0xb9,                                                \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x63,                \
		.vm_crt_line_compare  = 0xff,                                                \
		.vm_seq_clock_mode    = VGA_SR01_FCHAR_CLK_8DOTS,                            \
		.vm_seq_plane_write   = VGA_SR02_FALL_PLANES,                                \
		.vm_seq_character_map = 0x00,                                                \
		.vm_seq_memory_mode   = VGA_SR04_FSEQ_MODE | VGA_SR04_FEXT_MEM,              \
	}

/* VGA registers (360x480x256) */
#define VGAMODE_INIT_VGA_360X480X256                                                 \
	{                                                                                \
		.vm_att_pal           = {                                                    \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,                          \
			0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,                          \
		},                                                                           \
		.vm_att_mode          = VGA_AT10_FGRAPHICS | VGA_AT10_F8BITPAL,              \
		.vm_att_overscan      = 0x00,                                                \
		.vm_att_plane_enable  = 0x0f,                                                \
		.vm_att_pel           = 0x00,                                                \
		.vm_att_color_page    = 0x00,                                                \
		.vm_mis               = VGA_MIS_FCOLOR | VGA_MIS_FSEL_HIGH_PAGE |            \
		                        VGA_MIS_FENB_MEM_ACCESS | VGA_MIS_FHSYNCPOL |        \
		                        VGA_MIS_FVSYNCPOL | 0x04,                            \
		.vm_gfx_sr_value      = 0x00,                                                \
		.vm_gfx_sr_enable     = 0x00,                                                \
		.vm_gfx_compare_value = 0x00,                                                \
		.vm_gfx_data_rotate   = 0x00,                                                \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                                 \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0 |       \
		                        VGA_GR05_FSHIFT256,                                  \
		.vm_gfx_misc          = VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K,          \
		.vm_gfx_compare_mask  = 0x0f,                                                \
		.vm_gfx_bit_mask      = 0xff,                                                \
		.vm_crt_h_total       = 0x6b,                                                \
		.vm_crt_h_disp        = 0x59,                                                \
		.vm_crt_h_blank_start = 0x5a,                                                \
		.vm_crt_h_blank_end   = 0x8e,                                                \
		.vm_crt_h_sync_start  = 0x5e,                                                \
		.vm_crt_h_sync_end    = VGA_CR5_FH_BLANK_END_5 | 0x0a,                       \
		.vm_crt_v_total       = 0x0d,                                                \
		.vm_crt_overflow      = VGA_CR7_FV_SYNC_START_8 | VGA_CR7_FV_BLANK_START_8 | \
		                        VGA_CR7_FV_TOTAL_9 | VGA_CR7_FV_DISP_END_8 |         \
		                        VGA_CR7_FV_LINECOMP_8,                               \
		.vm_crt_preset_row    = 0x00,                                                \
		.vm_crt_max_scan      = VGA_CR9_FV_LINECOMP_9,                               \
		.vm_crt_cursor_start  = 0x00,                                                \
		.vm_crt_cursor_end    = 0x00,                                                \
		.vm_crt_start_hi      = 0x00,                                                \
		.vm_crt_start_lo      = 0x00,                                                \
		.vm_crt_cursor_hi     = 0x00,                                                \
		.vm_crt_cursor_lo     = 0x00,                                                \
		.vm_crt_v_sync_start  = 0xea,                                                \
		.vm_crt_v_sync_end    = VGA_CR11_FLOCK_CR0_CR7 | 0x2c,                       \
		.vm_crt_v_disp_end    = 0xdf,                                                \
		.vm_crt_offset        = 0x2d,                                                \
		.vm_crt_underline     = 0x00,                                                \
		.vm_crt_v_blank_start = 0xe7,                                                \
		.vm_crt_v_blank_end   = 0x06,                                                \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x63,                \
		.vm_crt_line_compare  = 0xff,                                                \
		.vm_seq_clock_mode    = VGA_SR01_FCHAR_CLK_8DOTS,                            \
		.vm_seq_plane_write   = VGA_SR02_FALL_PLANES,                                \
		.vm_seq_character_map = 0x00,                                                \
		.vm_seq_memory_mode   = VGA_SR04_FSEQ_MODE | VGA_SR04_FEXT_MEM,              \
	}

/* VGA registers (720x348x2) */
#define VGAMODE_INIT_VGA_720X348X2                                                   \
	{                                                                                \
		.vm_att_pal           = {                                                    \
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,                          \
			0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,                          \
		},                                                                           \
		.vm_att_mode          = VGA_AT10_FGRAPHICS,                                  \
		.vm_att_overscan      = 0x00,                                                \
		.vm_att_plane_enable  = 0x0f,                                                \
		.vm_att_pel           = 0x00,                                                \
		.vm_att_color_page    = 0x00,                                                \
		.vm_mis               = VGA_MIS_FCOLOR | VGA_MIS_FSEL_HIGH_PAGE |            \
		                        VGA_MIS_FENB_MEM_ACCESS | VGA_MIS_FVSYNCPOL |        \
		                        0x04,                                                \
		.vm_gfx_sr_value      = 0x00,                                                \
		.vm_gfx_sr_enable     = 0x00,                                                \
		.vm_gfx_compare_value = 0x00,                                                \
		.vm_gfx_data_rotate   = 0x20,                                                \
		.vm_gfx_plane_read    = VGA_GR04_READMAP(0),                                 \
		.vm_gfx_mode          = VGA_GR05_FWRITEMODE_0 | VGA_GR05_FREADMODE_0,        \
		.vm_gfx_misc          = VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K,          \
		.vm_gfx_compare_mask  = 0x0f,                                                \
		.vm_gfx_bit_mask      = 0xff,                                                \
		.vm_crt_h_total       = 0x6b,                                                \
		.vm_crt_h_disp        = 0x59,                                                \
		.vm_crt_h_blank_start = 0x5a,                                                \
		.vm_crt_h_blank_end   = 0x8e,                                                \
		.vm_crt_h_sync_start  = 0x5e,                                                \
		.vm_crt_h_sync_end    = VGA_CR5_FH_BLANK_END_5 | 0x0a,                       \
		.vm_crt_v_total       = 0xbf,                                                \
		.vm_crt_overflow      = VGA_CR7_FV_SYNC_START_8 | VGA_CR7_FV_BLANK_START_8 | \
		                        VGA_CR7_FV_TOTAL_8 | VGA_CR7_FV_DISP_END_8 |         \
		                        VGA_CR7_FV_LINECOMP_8,                               \
		.vm_crt_preset_row    = 0x00,                                                \
		.vm_crt_max_scan      = VGA_CR9_FV_LINECOMP_9,                               \
		.vm_crt_cursor_start  = 0x00,                                                \
		.vm_crt_cursor_end    = 0x00,                                                \
		.vm_crt_start_hi      = 0x00,                                                \
		.vm_crt_start_lo      = 0x00,                                                \
		.vm_crt_cursor_hi     = 0x00,                                                \
		.vm_crt_cursor_lo     = 0x00,                                                \
		.vm_crt_v_sync_start  = 0x83,                                                \
		.vm_crt_v_sync_end    = VGA_CR11_FLOCK_CR0_CR7 | 0x05,                       \
		.vm_crt_v_disp_end    = 0x5d,                                                \
		.vm_crt_offset        = 0x2d,                                                \
		.vm_crt_underline     = 0x0f,                                                \
		.vm_crt_v_blank_start = 0x63,                                                \
		.vm_crt_v_blank_end   = 0xba,                                                \
		.vm_crt_mode          = VGA_CR17_FH_V_SIGNALS_ENABLED | 0x63,                \
		.vm_crt_line_compare  = 0xff,                                                \
		.vm_seq_clock_mode    = VGA_SR01_FCHAR_CLK_8DOTS,                            \
		.vm_seq_plane_write   = VGA_SR02_FALL_PLANES,                                \
		.vm_seq_character_map = 0x00,                                                \
		.vm_seq_memory_mode   = VGA_SR04_FSEQ_MODE | VGA_SR04_FEXT_MEM,              \
	}




#endif /* !_HW_VIDEO_VGAMODES_H */
