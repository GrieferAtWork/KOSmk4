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
#ifndef GUARD_MODVGA_VGA_C
#define GUARD_MODVGA_VGA_C 1
#define _KOS_SOURCE 1

#include "vga.h"

#include <kernel/compiler.h>

#include <dev/char.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/mman.h>
#include <kernel/mman/map.h>
#include <kernel/mman/mfile.h>
#include <kernel/user.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <kos/dev.h>
#include <kos/except/reason/inval.h>
#include <linux/kd.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* TODO: Split all of the stuff that's required by both this driver, and the builtin debugger
 *       into  a separate file that is then included by both components to reduce redundancy. */

DECL_BEGIN


INTERN_CONST struct vga_mode const vga_ansitty_mode = VGA_BIOTEXT80x25_MODE_INIT(VGA_PALINDX_CGA_ANSI_INIT);
INTERN_CONST struct vga_palette16 const vga_ansitty_pal = VGA_PALETTE_CGA_INIT;

INTERN_CONST struct vga_mode const vga_mode_gfx320x200_256 = {
	.vm_att_mode          = 0x41,
	.vm_att_overscan      = 0x00,
	.vm_att_plane_enable  = 0x0f,
	.vm_att_pel           = 0x00,
	.vm_att_color_page    = 0x00,
	.vm_att_pal           = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	                          0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
	.vm_mis               = VGA_MIS_FCOLOR | VGA_MIS_FENB_MEM_ACCESS |
	                        /*VGA_MIS_FVSYNCPOL |*/ VGA_MIS_FHSYNCPOL |
	                        VGA_MIS_FSEL_HIGH_PAGE,
	.vm_gfx_sr_value      = 0x00,
	.vm_gfx_sr_enable     = 0x00,
	.vm_gfx_compare_value = 0x00,
	.vm_gfx_data_rotate   = 0x00,
	.vm_gfx_plane_read    = 0x00,
	.vm_gfx_mode          = 0x40,
	.vm_gfx_misc          = 0x05, /* 0x01 */
	.vm_gfx_compare_mask  = 0x0f, /* 0x00 */
	.vm_gfx_bit_mask      = 0xff,
	.vm_crt_h_total       = 0x5f,
	.vm_crt_h_disp        = 0x4f,
	.vm_crt_h_blank_start = 0x50,
	.vm_crt_h_blank_end   = 0x82,
	.vm_crt_h_sync_start  = 0x54,
	.vm_crt_h_sync_end    = 0x80,
	.vm_crt_v_total       = 0xbf, /* 0x0d */
	.vm_crt_overflow      = 0x1f, /* 0x3e */
	.vm_crt_preset_row    = 0x00,
	.vm_crt_max_scan      = 0x41,
	.vm_crt_v_sync_start  = 0x9c, /* 0xea */
	.vm_crt_v_sync_end    = 0x8e, /* 0xac */
	.vm_crt_v_disp_end    = 0x8f, /* 0xdf */
	.vm_crt_offset        = 0x28,
	.vm_crt_underline     = 0x40, /* 0x00 */
	.vm_crt_v_blank_start = 0x96, /* 0xe7 */
	.vm_crt_v_blank_end   = 0xb9 & ~VGA_CR16_FRESERVED, /* 0x06 */
	.vm_crt_mode          = 0xa3, /* 0xe3 */
	.vm_crt_line_compare  = 0xff,
	.vm_seq_clock_mode    = 0x01,
	.vm_seq_plane_write   = VGA_SR02_FALL_PLANES,
	.vm_seq_character_map = 0x00,
	.vm_seq_memory_mode   = 0x0e, /* 0x06 */
};

INTERN_CONST struct vga_mode const vga_mode_gfx640x480_16 = {
	.vm_att_mode          = 0x01, // 0x01,
	.vm_att_overscan      = 0x00, // 0x00,
	.vm_att_plane_enable  = 0x0f, // 0x0f,
	.vm_att_pel           = 0x00, // 0x00,
	.vm_att_color_page    = 0x00, // 0x00,
	.vm_att_pal           = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	                          0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
	.vm_mis               = 0xe3, // 0xe3,
	.vm_gfx_sr_value      = 0x00, // 0x00,
	.vm_gfx_sr_enable     = 0x00, // 0x00,
	.vm_gfx_compare_value = 0x00, // 0x00,
	.vm_gfx_data_rotate   = 0x00, // 0x00,
	.vm_gfx_plane_read    = 0x00, // 0x00,
	.vm_gfx_mode          = 0x00, // 0x00,
	.vm_gfx_misc          = 0x05, // 0x01,
	.vm_gfx_compare_mask  = 0x0f, // 0x00,
	.vm_gfx_bit_mask      = 0xff, // 0xff,
	.vm_crt_h_total       = 0x5f, // 0x5f,
	.vm_crt_h_disp        = 0x4f, // 0x4f,
	.vm_crt_h_blank_start = 0x50, // 0x50,
	.vm_crt_h_blank_end   = 0x82, // 0x82,
	.vm_crt_h_sync_start  = 0x54, // 0x54,
	.vm_crt_h_sync_end    = 0x80, // 0x80,
	.vm_crt_v_total       = 0x0b, // 0x0b,
	.vm_crt_overflow      = 0x3e, // 0x3e,
	.vm_crt_preset_row    = 0x00, // 0x00,
	.vm_crt_max_scan      = 0x40, // 0x40,
	.vm_crt_v_sync_start  = 0xea, // 0xea,
	.vm_crt_v_sync_end    = 0x8c, // 0x8c,
	.vm_crt_v_disp_end    = 0xdf, // 0xdf,
	.vm_crt_offset        = 0x28, // 0x28,
	.vm_crt_underline     = 0x00, // 0x00,
	.vm_crt_v_blank_start = 0xe7, // 0xe7,
	.vm_crt_v_blank_end   = 0x04, // 0x04,
	.vm_crt_mode          = 0xe3, // 0xe3,
	.vm_crt_line_compare  = 0xff, // 0xff,
	.vm_seq_clock_mode    = 0x01, // 0x01,
	.vm_seq_plane_write   = 0x0f, // 0x0f,
	.vm_seq_character_map = 0x00, // 0x00,
	.vm_seq_memory_mode   = 0x06, // VGA_SR04_FEXT_MEM/*|VGA_SR04_FSEQ_MODE*/,
};


INTERN_CONST struct vga_palette64 const vga_pal_gfx16 = {{
	{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0xaa }, { 0x00, 0xaa, 0x00 }, { 0x00, 0xaa, 0xaa },
	{ 0xaa, 0x00, 0x00 }, { 0xaa, 0x00, 0xaa }, { 0xaa, 0xaa, 0x00 }, { 0xaa, 0xaa, 0xaa },
	{ 0x00, 0x00, 0x55 }, { 0x00, 0x00, 0xff }, { 0x00, 0xaa, 0x55 }, { 0x00, 0xaa, 0xff },
	{ 0xaa, 0x00, 0x55 }, { 0xaa, 0x00, 0xff }, { 0xaa, 0xaa, 0x55 }, { 0xaa, 0xaa, 0xff },
	{ 0x00, 0x55, 0x00 }, { 0x00, 0x55, 0xaa }, { 0x00, 0xff, 0x00 }, { 0x00, 0xff, 0xaa },
	{ 0xaa, 0x55, 0x00 }, { 0xaa, 0x55, 0xaa }, { 0xaa, 0xff, 0x00 }, { 0xaa, 0xff, 0xaa },
	{ 0x00, 0x55, 0x55 }, { 0x00, 0x55, 0xff }, { 0x00, 0xff, 0x55 }, { 0x00, 0xff, 0xff },
	{ 0xaa, 0x55, 0x55 }, { 0xaa, 0x55, 0xff }, { 0xaa, 0xff, 0x55 }, { 0xaa, 0xff, 0xff },
	{ 0x55, 0x00, 0x00 }, { 0x55, 0x00, 0xaa }, { 0x55, 0xaa, 0x00 }, { 0x55, 0xaa, 0xaa },
	{ 0xff, 0x00, 0x00 }, { 0xff, 0x00, 0xaa }, { 0xff, 0xaa, 0x00 }, { 0xff, 0xaa, 0xaa },
	{ 0x55, 0x00, 0x55 }, { 0x55, 0x00, 0xff }, { 0x55, 0xaa, 0x55 }, { 0x55, 0xaa, 0xff },
	{ 0xff, 0x00, 0x55 }, { 0xff, 0x00, 0xff }, { 0xff, 0xaa, 0x55 }, { 0xff, 0xaa, 0xff },
	{ 0x55, 0x55, 0x00 }, { 0x55, 0x55, 0xaa }, { 0x55, 0xff, 0x00 }, { 0x55, 0xff, 0xaa },
	{ 0xff, 0x55, 0x00 }, { 0xff, 0x55, 0xaa }, { 0xff, 0xff, 0x00 }, { 0xff, 0xff, 0xaa },
	{ 0x55, 0x55, 0x55 }, { 0x55, 0x55, 0xff }, { 0x55, 0xff, 0x55 }, { 0x55, 0xff, 0xff },
	{ 0xff, 0x55, 0x55 }, { 0xff, 0x55, 0xff }, { 0xff, 0xff, 0x55 }, { 0xff, 0xff, 0xff }
}};

INTERN_CONST struct vga_palette256 const vga_pal_gfx256 = {{
	{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0xaa }, { 0x00, 0xaa, 0x00 }, { 0x00, 0xaa, 0xaa },
	{ 0xaa, 0x00, 0x00 }, { 0xaa, 0x00, 0xaa }, { 0xaa, 0x55, 0x00 }, { 0xaa, 0xaa, 0xaa },
	{ 0x55, 0x55, 0x55 }, { 0x55, 0x55, 0xff }, { 0x55, 0xff, 0x55 }, { 0x55, 0xff, 0xff },
	{ 0xff, 0x55, 0x55 }, { 0xff, 0x55, 0xff }, { 0xff, 0xff, 0x55 }, { 0xff, 0xff, 0xff },
	{ 0x00, 0x00, 0x00 }, { 0x15, 0x15, 0x15 }, { 0x20, 0x20, 0x20 }, { 0x2f, 0x2f, 0x2f },
	{ 0x3a, 0x3a, 0x3a }, { 0x45, 0x45, 0x45 }, { 0x50, 0x50, 0x50 }, { 0x60, 0x60, 0x60 },
	{ 0x70, 0x70, 0x70 }, { 0x80, 0x80, 0x80 }, { 0x90, 0x90, 0x90 }, { 0xa0, 0xa0, 0xa0 },
	{ 0xb5, 0xb5, 0xb5 }, { 0xca, 0xca, 0xca }, { 0xe0, 0xe0, 0xe0 }, { 0xff, 0xff, 0xff },
	{ 0x00, 0x00, 0xff }, { 0x40, 0x00, 0xff }, { 0x7f, 0x00, 0xff }, { 0xbf, 0x00, 0xff },
	{ 0xff, 0x00, 0xff }, { 0xff, 0x00, 0xbf }, { 0xff, 0x00, 0x7f }, { 0xff, 0x00, 0x40 },
	{ 0xff, 0x00, 0x00 }, { 0xff, 0x40, 0x00 }, { 0xff, 0x7f, 0x00 }, { 0xff, 0xbf, 0x00 },
	{ 0xff, 0xff, 0x00 }, { 0xbf, 0xff, 0x00 }, { 0x7f, 0xff, 0x00 }, { 0x40, 0xff, 0x00 },
	{ 0x00, 0xff, 0x00 }, { 0x00, 0xff, 0x40 }, { 0x00, 0xff, 0x7f }, { 0x00, 0xff, 0xbf },
	{ 0x00, 0xff, 0xff }, { 0x00, 0xbf, 0xff }, { 0x00, 0x7f, 0xff }, { 0x00, 0x40, 0xff },
	{ 0x7f, 0x7f, 0xff }, { 0x9f, 0x7f, 0xff }, { 0xbf, 0x7f, 0xff }, { 0xdf, 0x7f, 0xff },
	{ 0xff, 0x7f, 0xff }, { 0xff, 0x7f, 0xdf }, { 0xff, 0x7f, 0xbf }, { 0xff, 0x7f, 0x9f },
	{ 0xff, 0x7f, 0x7f }, { 0xff, 0x9f, 0x7f }, { 0xff, 0xbf, 0x7f }, { 0xff, 0xdf, 0x7f },
	{ 0xff, 0xff, 0x7f }, { 0xdf, 0xff, 0x7f }, { 0xbf, 0xff, 0x7f }, { 0x9f, 0xff, 0x7f },
	{ 0x7f, 0xff, 0x7f }, { 0x7f, 0xff, 0x9f }, { 0x7f, 0xff, 0xbf }, { 0x7f, 0xff, 0xdf },
	{ 0x7f, 0xff, 0xff }, { 0x7f, 0xdf, 0xff }, { 0x7f, 0xbf, 0xff }, { 0x7f, 0x9f, 0xff },
	{ 0xb5, 0xb5, 0xff }, { 0xc5, 0xb5, 0xff }, { 0xda, 0xb5, 0xff }, { 0xea, 0xb5, 0xff },
	{ 0xff, 0xb5, 0xff }, { 0xff, 0xb5, 0xea }, { 0xff, 0xb5, 0xda }, { 0xff, 0xb5, 0xc5 },
	{ 0xff, 0xb5, 0xb5 }, { 0xff, 0xc5, 0xb5 }, { 0xff, 0xda, 0xb5 }, { 0xff, 0xea, 0xb5 },
	{ 0xff, 0xff, 0xb5 }, { 0xea, 0xff, 0xb5 }, { 0xda, 0xff, 0xb5 }, { 0xc5, 0xff, 0xb5 },
	{ 0xb5, 0xff, 0xb5 }, { 0xb5, 0xff, 0xc5 }, { 0xb5, 0xff, 0xda }, { 0xb5, 0xff, 0xea },
	{ 0xb5, 0xff, 0xff }, { 0xb5, 0xea, 0xff }, { 0xb5, 0xda, 0xff }, { 0xb5, 0xc5, 0xff },
	{ 0x00, 0x00, 0x70 }, { 0x1f, 0x00, 0x70 }, { 0x3a, 0x00, 0x70 }, { 0x55, 0x00, 0x70 },
	{ 0x70, 0x00, 0x70 }, { 0x70, 0x00, 0x55 }, { 0x70, 0x00, 0x3a }, { 0x70, 0x00, 0x1f },
	{ 0x70, 0x00, 0x00 }, { 0x70, 0x1f, 0x00 }, { 0x70, 0x3a, 0x00 }, { 0x70, 0x55, 0x00 },
	{ 0x70, 0x70, 0x00 }, { 0x55, 0x70, 0x00 }, { 0x3a, 0x70, 0x00 }, { 0x1f, 0x70, 0x00 },
	{ 0x00, 0x70, 0x00 }, { 0x00, 0x70, 0x1f }, { 0x00, 0x70, 0x3a }, { 0x00, 0x70, 0x55 },
	{ 0x00, 0x70, 0x70 }, { 0x00, 0x55, 0x70 }, { 0x00, 0x3a, 0x70 }, { 0x00, 0x1f, 0x70 },
	{ 0x3a, 0x3a, 0x70 }, { 0x45, 0x3a, 0x70 }, { 0x55, 0x3a, 0x70 }, { 0x60, 0x3a, 0x70 },
	{ 0x70, 0x3a, 0x70 }, { 0x70, 0x3a, 0x60 }, { 0x70, 0x3a, 0x55 }, { 0x70, 0x3a, 0x45 },
	{ 0x70, 0x3a, 0x3a }, { 0x70, 0x45, 0x3a }, { 0x70, 0x55, 0x3a }, { 0x70, 0x60, 0x3a },
	{ 0x70, 0x70, 0x3a }, { 0x60, 0x70, 0x3a }, { 0x55, 0x70, 0x3a }, { 0x45, 0x70, 0x3a },
	{ 0x3a, 0x70, 0x3a }, { 0x3a, 0x70, 0x45 }, { 0x3a, 0x70, 0x55 }, { 0x3a, 0x70, 0x60 },
	{ 0x3a, 0x70, 0x70 }, { 0x3a, 0x60, 0x70 }, { 0x3a, 0x55, 0x70 }, { 0x3a, 0x45, 0x70 },
	{ 0x50, 0x50, 0x70 }, { 0x5a, 0x50, 0x70 }, { 0x60, 0x50, 0x70 }, { 0x6a, 0x50, 0x70 },
	{ 0x70, 0x50, 0x70 }, { 0x70, 0x50, 0x6a }, { 0x70, 0x50, 0x60 }, { 0x70, 0x50, 0x5a },
	{ 0x70, 0x50, 0x50 }, { 0x70, 0x5a, 0x50 }, { 0x70, 0x60, 0x50 }, { 0x70, 0x6a, 0x50 },
	{ 0x70, 0x70, 0x50 }, { 0x6a, 0x70, 0x50 }, { 0x60, 0x70, 0x50 }, { 0x5a, 0x70, 0x50 },
	{ 0x50, 0x70, 0x50 }, { 0x50, 0x70, 0x5a }, { 0x50, 0x70, 0x60 }, { 0x50, 0x70, 0x6a },
	{ 0x50, 0x70, 0x70 }, { 0x50, 0x6a, 0x70 }, { 0x50, 0x60, 0x70 }, { 0x50, 0x5a, 0x70 },
	{ 0x00, 0x00, 0x40 }, { 0x10, 0x00, 0x40 }, { 0x20, 0x00, 0x40 }, { 0x30, 0x00, 0x40 },
	{ 0x40, 0x00, 0x40 }, { 0x40, 0x00, 0x30 }, { 0x40, 0x00, 0x20 }, { 0x40, 0x00, 0x10 },
	{ 0x40, 0x00, 0x00 }, { 0x40, 0x10, 0x00 }, { 0x40, 0x20, 0x00 }, { 0x40, 0x30, 0x00 },
	{ 0x40, 0x40, 0x00 }, { 0x30, 0x40, 0x00 }, { 0x20, 0x40, 0x00 }, { 0x10, 0x40, 0x00 },
	{ 0x00, 0x40, 0x00 }, { 0x00, 0x40, 0x10 }, { 0x00, 0x40, 0x20 }, { 0x00, 0x40, 0x30 },
	{ 0x00, 0x40, 0x40 }, { 0x00, 0x30, 0x40 }, { 0x00, 0x20, 0x40 }, { 0x00, 0x10, 0x40 },
	{ 0x20, 0x20, 0x40 }, { 0x2a, 0x20, 0x40 }, { 0x30, 0x20, 0x40 }, { 0x3a, 0x20, 0x40 },
	{ 0x40, 0x20, 0x40 }, { 0x40, 0x20, 0x3a }, { 0x40, 0x20, 0x30 }, { 0x40, 0x20, 0x2a },
	{ 0x40, 0x20, 0x20 }, { 0x40, 0x2a, 0x20 }, { 0x40, 0x30, 0x20 }, { 0x40, 0x3a, 0x20 },
	{ 0x40, 0x40, 0x20 }, { 0x3a, 0x40, 0x20 }, { 0x30, 0x40, 0x20 }, { 0x2a, 0x40, 0x20 },
	{ 0x20, 0x40, 0x20 }, { 0x20, 0x40, 0x2a }, { 0x20, 0x40, 0x30 }, { 0x20, 0x40, 0x3a },
	{ 0x20, 0x40, 0x40 }, { 0x20, 0x3a, 0x40 }, { 0x20, 0x30, 0x40 }, { 0x20, 0x2a, 0x40 },
	{ 0x2f, 0x2f, 0x40 }, { 0x30, 0x2f, 0x40 }, { 0x35, 0x2f, 0x40 }, { 0x3f, 0x2f, 0x40 },
	{ 0x40, 0x2f, 0x40 }, { 0x40, 0x2f, 0x3f }, { 0x40, 0x2f, 0x35 }, { 0x40, 0x2f, 0x30 },
	{ 0x40, 0x2f, 0x2f }, { 0x40, 0x30, 0x2f }, { 0x40, 0x35, 0x2f }, { 0x40, 0x3f, 0x2f },
	{ 0x40, 0x40, 0x2f }, { 0x3f, 0x40, 0x2f }, { 0x35, 0x40, 0x2f }, { 0x30, 0x40, 0x2f },
	{ 0x2f, 0x40, 0x2f }, { 0x2f, 0x40, 0x30 }, { 0x2f, 0x40, 0x35 }, { 0x2f, 0x40, 0x3f },
	{ 0x2f, 0x40, 0x40 }, { 0x2f, 0x3f, 0x40 }, { 0x2f, 0x35, 0x40 }, { 0x2f, 0x30, 0x40 },
	{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }
}};

INTERN NOBLOCK void
NOTHROW(KCALL VGA_DoSetMode)(VGA *__restrict self,
                             struct vga_mode const *__restrict mode) {
	u8 temp, qr1;
	unsigned int i;
	qr1 = vga_rseq(VGA_SEQ_CLOCK_MODE);

	/* Turn off the screen. */
	if (!(self->v_state & VGA_STATE_FSCREENOFF)) {
		vga_wseq(VGA_SEQ_RESET, 0x1);
		vga_wseq(VGA_SEQ_CLOCK_MODE, qr1 | VGA_SR01_FSCREEN_OFF);
		vga_wseq(VGA_SEQ_RESET, 0x3);
	}

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
	for (i = 0; i < 16; ++i) {
		vga_r(VGA_IS1_RC);
		temp = vga_rattr(VGA_ATC_PALETTE0 + i);
		vga_r(VGA_IS1_RC);
		vga_wattr(VGA_ATC_PALETTE0 + i,
		          (temp & VGA_ATC_PALETTEn_FRESERVED) |
		          mode->vm_att_pal[i]);
	}
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
	temp = vga_rgfx(VGA_GFX_PLANE_READ), vga_wgfx(VGA_GFX_PLANE_READ, (temp & VGA_GR04_FRESERVED) | mode->vm_gfx_plane_read);
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
	if (!(self->v_state & VGA_STATE_FSCREENOFF)) {
		vga_wseq(VGA_SEQ_RESET, 0x1);
		vga_wseq(VGA_SEQ_CLOCK_MODE,
		         (qr1 & VGA_SR01_FRESERVED) |
		         (mode->vm_seq_clock_mode & ~VGA_SR01_FSCREEN_OFF));
		vga_wseq(VGA_SEQ_RESET, 0x3);
	} else {
		u8 new_mode;
		new_mode = mode->vm_seq_clock_mode | VGA_SR01_FSCREEN_OFF;
		new_mode &= ~VGA_SR01_FRESERVED;
		new_mode |= qr1 & VGA_SR01_FRESERVED;
		if (new_mode != qr1) {
			vga_wseq(VGA_SEQ_RESET, 0x1);
			vga_wseq(VGA_SEQ_CLOCK_MODE, new_mode);
			vga_wseq(VGA_SEQ_RESET, 0x3);
		}
	}
}

INTERN void KCALL
VGA_SetMode(VGA *__restrict self,
            struct vga_mode const *__restrict mode)
		THROWS(E_INVALID_ARGUMENT) {
	unsigned int i;
	/* Validate the given mode. */
	if (mode->vm_att_mode & VGA_AT10_FRESERVED)
		goto invalid_mode;
	if (mode->vm_att_plane_enable & VGA_AT12_FRESERVED)
		goto invalid_mode;
	if (mode->vm_att_pel & VGA_AT13_FRESERVED)
		goto invalid_mode;
	if (mode->vm_att_color_page & VGA_AT14_FRESERVED)
		goto invalid_mode;
	if (mode->vm_mis & VGA_MIS_FRESERVED)
		goto invalid_mode;
	if (mode->vm_seq_plane_write & VGA_SR02_FRESERVED)
		goto invalid_mode;
	if (mode->vm_seq_character_map & VGA_SR03_FRESERVED)
		goto invalid_mode;
	if (mode->vm_seq_memory_mode & VGA_SR04_FRESERVED)
		goto invalid_mode;
	if (mode->vm_gfx_sr_value & VGA_GR00_FRESERVED)
		goto invalid_mode;
	if (mode->vm_gfx_sr_enable & VGA_GR01_FRESERVED)
		goto invalid_mode;
	if (mode->vm_gfx_compare_value & VGA_GR02_FRESERVED)
		goto invalid_mode;
	if (mode->vm_gfx_data_rotate & VGA_GR03_FRESERVED)
		goto invalid_mode;
	if (mode->vm_gfx_plane_read & VGA_GR04_FRESERVED)
		goto invalid_mode;
	if (mode->vm_gfx_mode & VGA_GR05_FRESERVED)
		goto invalid_mode;
	if (mode->vm_gfx_misc & VGA_GR06_FRESERVED)
		goto invalid_mode;
	if (mode->vm_gfx_compare_mask & VGA_GR07_FRESERVED)
		goto invalid_mode;
	if (mode->vm_crt_preset_row & VGA_CR8_FRESERVED)
		goto invalid_mode;
	if (mode->vm_crt_v_sync_end & VGA_CR11_FRESERVED)
		goto invalid_mode;
	if (mode->vm_crt_v_blank_end & VGA_CR16_FRESERVED)
		goto invalid_mode;
	if (mode->vm_crt_mode & VGA_CR17_FRESERVED)
		goto invalid_mode;
	if (mode->vm_seq_clock_mode & VGA_SR01_FRESERVED)
		goto invalid_mode;
	for (i = 0; i < 16; ++i) {
		if (mode->vm_att_pal[i] & VGA_ATC_PALETTEn_FRESERVED)
			goto invalid_mode;
	}
	sync_write(&self->v_lock);
	VGA_DoSetMode(self, mode);
	sync_endwrite(&self->v_lock);
	return;
invalid_mode:
	THROW(E_INVALID_ARGUMENT);
}


INTERN void KCALL
VGA_DoGetMode(VGA *__restrict UNUSED(self),
              struct vga_mode *__restrict mode) {
	unsigned int i;
	vga_r(VGA_IS1_RC), vga_w(VGA_ATT_W, 0x00);
	vga_r(VGA_IS1_RC), mode->vm_att_mode         = vga_rattr(VGA_ATC_MODE) & ~VGA_AT10_FRESERVED;
	vga_r(VGA_IS1_RC), mode->vm_att_overscan     = vga_rattr(VGA_ATC_OVERSCAN);
	vga_r(VGA_IS1_RC), mode->vm_att_plane_enable = vga_rattr(VGA_ATC_PLANE_ENABLE) & ~VGA_AT12_FRESERVED;
	vga_r(VGA_IS1_RC), mode->vm_att_pel          = vga_rattr(VGA_ATC_PEL) & ~VGA_AT13_FRESERVED;
	vga_r(VGA_IS1_RC), mode->vm_att_color_page   = vga_rattr(VGA_ATC_COLOR_PAGE) & ~VGA_AT14_FRESERVED;
	for (i = 0; i < 16; ++i) {
		vga_r(VGA_IS1_RC);
		mode->vm_att_pal[i] = vga_rattr(VGA_ATC_PALETTE0 + i) & ~VGA_ATC_PALETTEn_FRESERVED;
	}
	vga_r(VGA_IS1_RC), vga_w(VGA_ATT_W, 0x20);

	mode->vm_mis               = vga_r(VGA_MIS_R) & ~VGA_MIS_FRESERVED;
	mode->vm_gfx_sr_value      = vga_rgfx(VGA_GFX_SR_VALUE) & ~VGA_GR00_FRESERVED;
	mode->vm_gfx_sr_enable     = vga_rgfx(VGA_GFX_SR_ENABLE) & ~VGA_GR01_FRESERVED;
	mode->vm_gfx_compare_value = vga_rgfx(VGA_GFX_COMPARE_VALUE) & ~VGA_GR02_FRESERVED;
	mode->vm_gfx_data_rotate   = vga_rgfx(VGA_GFX_DATA_ROTATE) & ~VGA_GR03_FRESERVED;
	mode->vm_gfx_plane_read    = vga_rgfx(VGA_GFX_PLANE_READ) & ~VGA_GR04_FRESERVED;
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

INTERN void KCALL
VGA_GetMode(VGA *__restrict self,
            struct vga_mode *__restrict mode)
		THROWS(E_WOULDBLOCK) {
	sync_write(&self->v_lock);
	VGA_DoGetMode(self, mode);
	sync_endwrite(&self->v_lock);
}


INTERN void KCALL
VGA_DoSetPalette(VGA *__restrict UNUSED(self),
                 USER CHECKED void const *__restrict pal,
                 size_t color_count)
		THROWS(E_WOULDBLOCK) {
	unsigned int i = 0;
	TRY {
		vga_w(VGA_PEL_MSK, 0xff);
		vga_w(VGA_PEL_IW, 0x00);
		for (; i < color_count * 3; ++i)
			vga_w(VGA_PEL_D, ((u8 *)pal)[i] >> 2);
	} EXCEPT {
		/* Must complete the operation. - VGA wouldn't understand otherwise. */
		for (; i < 768; ++i)
			vga_w(VGA_PEL_D, 0);
		RETHROW();
	}
	for (; i < 768; ++i)
		vga_w(VGA_PEL_D, 0);
}

INTERN void KCALL
VGA_SetPalette(VGA *__restrict self,
               USER CHECKED void const *__restrict pal,
               size_t color_count)
		THROWS(E_WOULDBLOCK) {
	sync_write(&self->v_lock);
	TRY {
		VGA_DoSetPalette(self, pal, color_count);
	} EXCEPT {
		sync_endwrite(&self->v_lock);
		RETHROW();
	}
	sync_endwrite(&self->v_lock);
}

INTERN void KCALL
VGA_GetPalette(VGA *__restrict self,
               USER CHECKED void *__restrict pal,
               size_t color_count)
		THROWS(E_WOULDBLOCK) {
	unsigned int i = 0;
	sync_write(&self->v_lock);
	TRY {
		vga_w(VGA_PEL_MSK, 0xff);
		vga_w(VGA_PEL_IR, 0x00);
		for (; i < color_count * 3; ++i)
			((u8 *)pal)[i] = vga_r(VGA_PEL_D) << 2;
	} EXCEPT {
		/* Must complete the operation. - VGA wouldn't understand otherwise. */
		for (; i < 768; ++i)
			vga_r(VGA_PEL_D);
		sync_endwrite(&self->v_lock);
		RETHROW();
	}
	for (; i < 768; ++i)
		vga_r(VGA_PEL_D);
	sync_endwrite(&self->v_lock);
}

INTERN void KCALL
VGA_DoSetFont(VGA *__restrict self,
              USER CHECKED struct vga_font const *__restrict font) {
	unsigned int i;
	byte_t *dst = self->v_vram;
	u8 old_seq_plane_write = vga_rseq(VGA_SEQ_PLANE_WRITE);
	u8 old_seq_memory_mode = vga_rseq(VGA_SEQ_MEMORY_MODE);
	u8 old_gfx_plane_read  = vga_rgfx(VGA_GFX_PLANE_READ);
	u8 old_gfx_mode        = vga_rgfx(VGA_GFX_MODE);
	u8 old_gfx_sr_enable   = vga_rgfx(VGA_GFX_SR_ENABLE);
	u8 old_gfx_sr_value    = vga_rgfx(VGA_GFX_SR_VALUE);
	u8 old_gfx_bit_mask    = vga_rgfx(VGA_GFX_BIT_MASK);
	u8 old_gfx_data_rotate = vga_rgfx(VGA_GFX_DATA_ROTATE);
	u8 old_gfx_misc        = vga_rgfx(VGA_GFX_MISC);
	vga_wseq(VGA_SEQ_PLANE_WRITE, (old_seq_plane_write & VGA_SR02_FRESERVED) | VGA_SR02_FPLANE(2));
	vga_wseq(VGA_SEQ_MEMORY_MODE, (old_seq_memory_mode & VGA_SR04_FRESERVED) |
	                              (VGA_SR04_FEXT_MEM | VGA_SR04_FSEQ_MODE));
	vga_wgfx(VGA_GFX_PLANE_READ, (old_gfx_plane_read & VGA_GR04_FRESERVED) | 0x02);
	vga_wgfx(VGA_GFX_MODE, (old_gfx_mode & VGA_GR05_FRESERVED) | 0x00);
	vga_wgfx(VGA_GFX_SR_ENABLE, (old_gfx_sr_enable & VGA_GR01_FRESERVED) | 0x00);
	vga_wgfx(VGA_GFX_SR_VALUE, (old_gfx_sr_value & VGA_GR00_FRESERVED) | 0x00);
	vga_wgfx(VGA_GFX_BIT_MASK, 0xff);
	vga_wgfx(VGA_GFX_DATA_ROTATE, (old_gfx_data_rotate & VGA_GR03_FRESERVED) | 0x00);
	vga_wgfx(VGA_GFX_MISC, (old_gfx_misc & VGA_GR06_FRESERVED) |
	                       (VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K));
	TRY {
		for (i = 0; i < 256; ++i) {
			memcpy(dst, &font->vf_blob[i], 16);
			dst += 32;
		}
	} EXCEPT {
		vga_wseq(VGA_SEQ_PLANE_WRITE, old_seq_plane_write);
		vga_wseq(VGA_SEQ_MEMORY_MODE, old_seq_memory_mode);
		vga_wgfx(VGA_GFX_PLANE_READ, old_gfx_plane_read);
		vga_wgfx(VGA_GFX_MODE, old_gfx_mode);
		vga_wgfx(VGA_GFX_SR_ENABLE, old_gfx_sr_enable);
		vga_wgfx(VGA_GFX_SR_VALUE, old_gfx_sr_value);
		vga_wgfx(VGA_GFX_BIT_MASK, old_gfx_bit_mask);
		vga_wgfx(VGA_GFX_DATA_ROTATE, old_gfx_data_rotate);
		vga_wgfx(VGA_GFX_MISC, old_gfx_misc);
		RETHROW();
	}
	vga_wseq(VGA_SEQ_PLANE_WRITE, old_seq_plane_write);
	vga_wseq(VGA_SEQ_MEMORY_MODE, old_seq_memory_mode);
	vga_wgfx(VGA_GFX_PLANE_READ, old_gfx_plane_read);
	vga_wgfx(VGA_GFX_MODE, old_gfx_mode);
	vga_wgfx(VGA_GFX_SR_ENABLE, old_gfx_sr_enable);
	vga_wgfx(VGA_GFX_SR_VALUE, old_gfx_sr_value);
	vga_wgfx(VGA_GFX_BIT_MASK, old_gfx_bit_mask);
	vga_wgfx(VGA_GFX_DATA_ROTATE, old_gfx_data_rotate);
	vga_wgfx(VGA_GFX_MISC, old_gfx_misc);
}

INTERN void KCALL
VGA_DoGetFont(VGA *__restrict self,
              USER CHECKED struct vga_font *__restrict font) {
	unsigned int i;
	byte_t *src = self->v_vram;
	u8 old_seq_plane_write = vga_rseq(VGA_SEQ_PLANE_WRITE);
	u8 old_seq_memory_mode = vga_rseq(VGA_SEQ_MEMORY_MODE);
	u8 old_gfx_plane_read  = vga_rgfx(VGA_GFX_PLANE_READ);
	u8 old_gfx_mode        = vga_rgfx(VGA_GFX_MODE);
	u8 old_gfx_misc        = vga_rgfx(VGA_GFX_MISC);
	vga_wseq(VGA_SEQ_PLANE_WRITE, (old_seq_plane_write & VGA_SR02_FRESERVED) | VGA_SR02_FPLANE(2));
	vga_wseq(VGA_SEQ_MEMORY_MODE, (old_seq_memory_mode & VGA_SR04_FRESERVED) |
	                              (VGA_SR04_FEXT_MEM | VGA_SR04_FSEQ_MODE));
	vga_wgfx(VGA_GFX_PLANE_READ, (old_gfx_plane_read & VGA_GR04_FRESERVED) | 0x02);
	vga_wgfx(VGA_GFX_MODE, (old_gfx_mode & VGA_GR05_FRESERVED) | 0x00);
	vga_wgfx(VGA_GFX_MISC, (old_gfx_misc & VGA_GR06_FRESERVED) |
	                       (VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K));
	TRY {
		for (i = 0; i < 256; ++i) {
			memcpy(&font->vf_blob[i], src, 16);
			src += 32;
		}
	} EXCEPT {
		vga_wseq(VGA_SEQ_PLANE_WRITE, old_seq_plane_write);
		vga_wseq(VGA_SEQ_MEMORY_MODE, old_seq_memory_mode);
		vga_wgfx(VGA_GFX_PLANE_READ, old_gfx_plane_read);
		vga_wgfx(VGA_GFX_MODE, old_gfx_mode);
		vga_wgfx(VGA_GFX_MISC, old_gfx_misc);
		RETHROW();
	}
	vga_wseq(VGA_SEQ_PLANE_WRITE, old_seq_plane_write);
	vga_wseq(VGA_SEQ_MEMORY_MODE, old_seq_memory_mode);
	vga_wgfx(VGA_GFX_PLANE_READ, old_gfx_plane_read);
	vga_wgfx(VGA_GFX_MODE, old_gfx_mode);
	vga_wgfx(VGA_GFX_MISC, old_gfx_misc);
}


INTERN void KCALL
VGA_SetFont(VGA *__restrict self,
            USER CHECKED struct vga_font const *__restrict font) {
	SCOPED_WRITELOCK(&self->v_lock); /* XXX: atomic lock in except-scenario */
	VGA_DoSetFont(self, font);
}

INTERN void KCALL
VGA_GetFont(VGA *__restrict self,
            USER CHECKED struct vga_font *__restrict font) {
	SCOPED_WRITELOCK(&self->v_lock); /* XXX: atomic lock in except-scenario */
	VGA_DoGetFont(self, font);
}



INTERN NOBLOCK void
NOTHROW(KCALL VGA_DoScreenOn)(VGA *__restrict self) {
	if (self->v_state & VGA_STATE_FSCREENOFF) {
		u8 qr1;
		qr1 = vga_rseq(VGA_SEQ_CLOCK_MODE);
		qr1 &= ~VGA_SR01_FSCREEN_OFF;
		vga_wseq(VGA_SEQ_RESET, 0x1);
		vga_wseq(VGA_SEQ_CLOCK_MODE, qr1);
		vga_wseq(VGA_SEQ_RESET, 0x3);
		self->v_state &= ~VGA_STATE_FSCREENOFF;
	}
}

INTERN NOBLOCK void
NOTHROW(KCALL VGA_DoScreenOff)(VGA *__restrict self) {
	if (!(self->v_state & VGA_STATE_FSCREENOFF)) {
		u8 qr1;
		qr1 = vga_rseq(VGA_SEQ_CLOCK_MODE);
		qr1 |= VGA_SR01_FSCREEN_OFF;
		vga_wseq(VGA_SEQ_RESET, 0x1);
		vga_wseq(VGA_SEQ_CLOCK_MODE, qr1);
		vga_wseq(VGA_SEQ_RESET, 0x3);
		self->v_state |= VGA_STATE_FSCREENOFF;
	}
}


INTERN void KCALL
VGA_ScreenOn(VGA *__restrict self)
		THROWS(E_WOULDBLOCK) {
	sync_write(&self->v_lock);
	VGA_DoScreenOn(self);
	sync_endwrite(&self->v_lock);
}

INTERN void KCALL
VGA_ScreenOff(VGA *__restrict self)
		THROWS(E_WOULDBLOCK) {
	sync_write(&self->v_lock);
	VGA_DoScreenOff(self);
	sync_endwrite(&self->v_lock);
}





/* Conversion table: LATIN-1 --> CP437 */
PRIVATE u8 const cp437_from_latin1[256] = {
/*[[[deemon
local l = [0] * 256;
l[0x00] = 0;
l[0x20] = 32;
l[0x21] = 33;
l[0x22] = 34;
l[0x23] = 35;
l[0x24] = 36;
l[0x25] = 37;
l[0x26] = 38;
l[0x27] = 39;
l[0x28] = 40;
l[0x29] = 41;
l[0x2A] = 42;
l[0x2B] = 43;
l[0x2C] = 44;
l[0x2D] = 45;
l[0x2E] = 46;
l[0x2F] = 47;
l[0x30] = 48;
l[0x31] = 49;
l[0x32] = 50;
l[0x33] = 51;
l[0x34] = 52;
l[0x35] = 53;
l[0x36] = 54;
l[0x37] = 55;
l[0x38] = 56;
l[0x39] = 57;
l[0x3A] = 58;
l[0x3B] = 59;
l[0x3C] = 60;
l[0x3D] = 61;
l[0x3E] = 62;
l[0x3F] = 63;
l[0x40] = 64;
l[0x41] = 65;
l[0x42] = 66;
l[0x43] = 67;
l[0x44] = 68;
l[0x45] = 69;
l[0x46] = 70;
l[0x47] = 71;
l[0x48] = 72;
l[0x49] = 73;
l[0x4A] = 74;
l[0x4B] = 75;
l[0x4C] = 76;
l[0x4D] = 77;
l[0x4E] = 78;
l[0x4F] = 79;
l[0x50] = 80;
l[0x51] = 81;
l[0x52] = 82;
l[0x53] = 83;
l[0x54] = 84;
l[0x55] = 85;
l[0x56] = 86;
l[0x57] = 87;
l[0x58] = 88;
l[0x59] = 89;
l[0x5A] = 90;
l[0x5B] = 91;
l[0x5C] = 92;
l[0x5D] = 93;
l[0x5E] = 94;
l[0x5F] = 95;
l[0x60] = 96;
l[0x61] = 97;
l[0x62] = 98;
l[0x63] = 99;
l[0x64] = 100;
l[0x65] = 101;
l[0x66] = 102;
l[0x67] = 103;
l[0x68] = 104;
l[0x69] = 105;
l[0x6A] = 106;
l[0x6B] = 107;
l[0x6C] = 108;
l[0x6D] = 109;
l[0x6E] = 110;
l[0x6F] = 111;
l[0x70] = 112;
l[0x71] = 113;
l[0x72] = 114;
l[0x73] = 115;
l[0x74] = 116;
l[0x75] = 117;
l[0x76] = 118;
l[0x77] = 119;
l[0x78] = 120;
l[0x79] = 121;
l[0x7A] = 122;
l[0x7B] = 123;
l[0x7C] = 124;
l[0x7D] = 125;
l[0x7E] = 126;
l[0xA0] = 255;
l[0xA1] = 173;
l[0xA2] = 155;
l[0xA3] = 156;
l[0xA5] = 157;
l[0xA7] = 21;
l[0xAA] = 166;
l[0xAB] = 174;
l[0xAC] = 170;
l[0xB0] = 248;
l[0xB1] = 241;
l[0xB2] = 253;
l[0xB5] = 230;
l[0xB6] = 20;
l[0xB7] = 250;
l[0xBA] = 167;
l[0xBB] = 175;
l[0xBC] = 172;
l[0xBD] = 171;
l[0xBF] = 168;
l[0xC4] = 142;
l[0xC5] = 143;
l[0xC6] = 146;
l[0xC7] = 128;
l[0xC9] = 144;
l[0xD1] = 165;
l[0xD6] = 153;
l[0xDC] = 154;
l[0xDF] = 225;
l[0xE0] = 133;
l[0xE1] = 160;
l[0xE2] = 131;
l[0xE4] = 132;
l[0xE5] = 134;
l[0xE6] = 145;
l[0xE7] = 135;
l[0xE8] = 138;
l[0xE9] = 130;
l[0xEA] = 136;
l[0xEB] = 137;
l[0xEC] = 141;
l[0xED] = 161;
l[0xEE] = 140;
l[0xEF] = 139;
l[0xF1] = 164;
l[0xF2] = 149;
l[0xF3] = 162;
l[0xF4] = 147;
l[0xF6] = 148;
l[0xF7] = 246;
l[0xF9] = 151;
l[0xFA] = 163;
l[0xFB] = 150;
l[0xFC] = 129;
l[0xFF] = 152;
#include <util>
print "\t",;
for (local i,x: util.enumerate(l)) {
	if (i) {
		print ",",;
		if ((i % 16) == 0) {
			print;
			print "\t",;
		}
	}
	print "0x%.2I8x" % x,;
}
]]]*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
	0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0xff,0xad,0x9b,0x9c,0x00,0x9d,0x00,0x15,0x00,0x00,0xa6,0xae,0xaa,0x00,0x00,0x00,
	0xf8,0xf1,0xfd,0x00,0x00,0xe6,0x14,0xfa,0x00,0x00,0xa7,0xaf,0xac,0xab,0x00,0xa8,
	0x00,0x00,0x00,0x00,0x8e,0x8f,0x92,0x80,0x00,0x90,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0xa5,0x00,0x00,0x00,0x00,0x99,0x00,0x00,0x00,0x00,0x00,0x9a,0x00,0x00,0xe1,
	0x85,0xa0,0x83,0x00,0x84,0x86,0x91,0x87,0x8a,0x82,0x88,0x89,0x8d,0xa1,0x8c,0x8b,
	0x00,0xa4,0x95,0xa2,0x93,0x00,0x94,0xf6,0x00,0x97,0xa3,0x96,0x81,0x00,0x00,0x98
//[[[end]]]
};


/* Encode the given unicode character `ch' using cp437 (the codepage
 * used by VGA) If the character can't be encoded, return 0 instead.
 * s.a.: https://en.wikipedia.org/wiki/Code_page_437 */
LOCAL ATTR_CONST WUNUSED u8 NOTHROW(KCALL cp437_encode)(/*utf-32*/ u32 ch) {
	u8 result;
	if (ch <= 0xff) {
		result = cp437_from_latin1[ch];
		if (result)
			return result;
	} else {
		switch (ch) {
		case 0x0192: result = 159; break;
		case 0x0393: result = 226; break;
		case 0x0398: result = 233; break;
		case 0x03A3: result = 228; break;
		case 0x03A6: result = 232; break;
		case 0x03A9: result = 234; break;
		case 0x03B1: result = 224; break;
		case 0x03B4: result = 235; break;
		case 0x03B5: result = 238; break;
		case 0x03C0: result = 227; break;
		case 0x03C3: result = 229; break;
		case 0x03C4: result = 231; break;
		case 0x03C6: result = 237; break;
		case 0x2022: result = 7; break;
		case 0x203C: result = 19; break;
		case 0x207F: result = 252; break;
		case 0x20A7: result = 158; break;
		case 0x2190: result = 27; break;
		case 0x2191: result = 24; break;
		case 0x2192: result = 26; break;
		case 0x2193: result = 25; break;
		case 0x2194: result = 29; break;
		case 0x2195: result = 18; break;
		case 0x21A8: result = 23; break;
		case 0x2219: result = 249; break;
		case 0x221A: result = 251; break;
		case 0x221E: result = 236; break;
		case 0x221F: result = 28; break;
		case 0x2229: result = 239; break;
		case 0x2248: result = 247; break;
		case 0x2261: result = 240; break;
		case 0x2264: result = 243; break;
		case 0x2265: result = 242; break;
		case 0x2302: result = 127; break;
		case 0x2310: result = 169; break;
		case 0x2320: result = 244; break;
		case 0x2321: result = 245; break;
		case 0x2500: result = 196; break;
		case 0x2502: result = 179; break;
		case 0x250C: result = 218; break;
		case 0x2510: result = 191; break;
		case 0x2514: result = 192; break;
		case 0x2518: result = 217; break;
		case 0x251C: result = 195; break;
		case 0x2524: result = 180; break;
		case 0x252C: result = 194; break;
		case 0x2534: result = 193; break;
		case 0x253C: result = 197; break;
		case 0x2550: result = 205; break;
		case 0x2551: result = 186; break;
		case 0x2552: result = 213; break;
		case 0x2553: result = 214; break;
		case 0x2554: result = 201; break;
		case 0x2555: result = 184; break;
		case 0x2556: result = 183; break;
		case 0x2557: result = 187; break;
		case 0x2558: result = 212; break;
		case 0x2559: result = 211; break;
		case 0x255A: result = 200; break;
		case 0x255B: result = 190; break;
		case 0x255C: result = 189; break;
		case 0x255D: result = 188; break;
		case 0x255E: result = 198; break;
		case 0x255F: result = 199; break;
		case 0x2560: result = 204; break;
		case 0x2561: result = 181; break;
		case 0x2562: result = 182; break;
		case 0x2563: result = 185; break;
		case 0x2564: result = 209; break;
		case 0x2565: result = 210; break;
		case 0x2566: result = 203; break;
		case 0x2567: result = 207; break;
		case 0x2568: result = 208; break;
		case 0x2569: result = 202; break;
		case 0x256A: result = 216; break;
		case 0x256B: result = 215; break;
		case 0x256C: result = 206; break;
		case 0x2580: result = 223; break;
		case 0x2584: result = 220; break;
		case 0x2588: result = 219; break;
		case 0x258C: result = 221; break;
		case 0x2590: result = 222; break;
		case 0x2591: result = 176; break;
		case 0x2592: result = 177; break;
		case 0x2593: result = 178; break;
		case 0x25A0: result = 254; break;
		case 0x25AC: result = 22; break;
		case 0x25B2: result = 30; break;
		case 0x25BA: result = 16; break;
		case 0x25BC: result = 31; break;
		case 0x25C4: result = 17; break;
		case 0x25CB: result = 9; break;
		case 0x25D8: result = 8; break;
		case 0x25D9: result = 10; break;
		case 0x263A: result = 1; break;
		case 0x263B: result = 2; break;
		case 0x263C: result = 15; break;
		case 0x2640: result = 12; break;
		case 0x2642: result = 11; break;
		case 0x2660: result = 6; break;
		case 0x2663: result = 5; break;
		case 0x2665: result = 3; break;
		case 0x2666: result = 4; break;
		case 0x266A: result = 13; break;
		case 0x266B: result = 14; break;
		default: result = 0; break;
		}
	}
	return result;
}






LOCAL void KCALL vga_enable_cursor(VGA *__restrict self)
		THROWS(E_WOULDBLOCK) {
	if (!(self->v_state & VGA_STATE_FCURSOR)) {
		sync_write(&self->v_lock);
		COMPILER_READ_BARRIER();
		if (!(self->v_state & VGA_STATE_FCURSOR)) {
			vga_wcrt(VGA_CRTC_CURSOR_START, vga_rcrt(VGA_CRTC_CURSOR_START) & ~(VGA_CRA_FCURSOR_DISABLE));
			self->v_state |= VGA_STATE_FCURSOR;
		}
		sync_endwrite(&self->v_lock);
	}
}

LOCAL void KCALL vga_disable_cursor(VGA *__restrict self)
		THROWS(E_WOULDBLOCK) {
	if (self->v_state & VGA_STATE_FCURSOR) {
		sync_write(&self->v_lock);
		COMPILER_READ_BARRIER();
		if (self->v_state & VGA_STATE_FCURSOR) {
			vga_wcrt(VGA_CRTC_CURSOR_START, vga_rcrt(VGA_CRTC_CURSOR_START) | VGA_CRA_FCURSOR_DISABLE);
			self->v_state &= ~VGA_STATE_FCURSOR;
		}
		sync_endwrite(&self->v_lock);
	}
}


PRIVATE void KCALL
vga_update_cursor_pos(VGA *__restrict self)
		THROWS(E_WOULDBLOCK) {
	if (self->v_state & VGA_STATE_FGRAPHICS)
		return;
	if (self->v_textptr >= self->v_textend) {
		vga_disable_cursor(self);
	} else {
		unsigned int pos;
		pos = (unsigned int)(self->v_textptr - self->v_textbase);
		sync_write(&self->v_lock);
		vga_wcrt(VGA_CRTC_CURSOR_HI, (pos >> 8));
		vga_wcrt(VGA_CRTC_CURSOR_LO, (u8)pos);
		COMPILER_READ_BARRIER();
		if (!(self->v_state & VGA_STATE_FCURSOR)) {
			vga_wcrt(VGA_CRTC_CURSOR_START, vga_rcrt(VGA_CRTC_CURSOR_START) & ~(VGA_CRA_FCURSOR_DISABLE));
			self->v_state |= VGA_STATE_FCURSOR;
		}
		sync_endwrite(&self->v_lock);
	}
}

#define TABSIZE 8

#define VGA_CHR(self, ch) ((u16)(ch) | ((u16)(self)->at_ansi.at_color << 8))

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LIBANSITTY_CC vga_do_putcp437)(VGA *__restrict self, u8 ch) {
	u16 *oldptr;
	/* VGA terminal output */
	for (;;) {
		oldptr = ATOMIC_READ(self->v_textptr);
		if (oldptr >= self->v_textend) {
			/* Scroll down */
			if (!ATOMIC_CMPXCH(self->v_textptr, oldptr, self->v_textlline))
				continue;
			memmovew(self->v_textbase, self->v_text2line,
			         (self->v_textsizey - 1) * self->v_textsizex);
			memsetw(self->v_textlline, VGA_CHR(self, ' '), self->v_textsizex);
			continue;
		}
		if (self->at_ansi.at_ttymode & ANSITTY_MODE_NOLINEWRAP) {
			if (((size_t)(oldptr - self->v_textbase) % self->v_textsizex) != (self->v_textsizex - 1))
				goto do_increment_oldptr;
		} else {
do_increment_oldptr:
			if (!ATOMIC_CMPXCH(self->v_textptr, oldptr, oldptr + 1))
				continue;
		}
		*oldptr = VGA_CHR(self, ch);
		break;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LIBANSITTY_CC vga_putcp437)(VGA *__restrict self, u8 ch) {
	if (sync_tryread(&self->v_textlock)) {
		vga_do_putcp437(self, ch);
		sync_endread(&self->v_textlock);
	}
}

PRIVATE NOBLOCK void
NOTHROW(KCALL invert_current_line_colors)(VGA *__restrict self) {
	unsigned int cur_x;
	u16 *line_start, *line_end;
	if (sync_tryread(&self->v_textlock)) {
		line_start  = ATOMIC_READ(self->v_textptr);
		cur_x       = ((size_t)(line_start - self->v_textbase) % self->v_textsizex);
		line_start -= cur_x;
		line_end    = line_start + self->v_textsizex;
		for (; line_start < line_end; ++line_start)
			*line_start ^= 0xff00;
		sync_endread(&self->v_textlock);
	}
}

PRIVATE void KCALL do_flash_screen_pause(void) THROWS(E_WOULDBLOCK, ...) {
	ktime_t tmo = ktime();
	tmo += relktime_from_milliseconds(50);
	task_sleep_until(tmo);
}


PRIVATE void KCALL flash_current_line_pause(void) THROWS(E_WOULDBLOCK, ...) {
	if unlikely(task_wasconnected()) {
		struct task_connections con;
		task_pushconnections(&con);
		assert(!task_wasconnected());
		TRY {
			do_flash_screen_pause();
		} EXCEPT {
			assert(!task_wasconnected());
			task_popconnections();
			RETHROW();
		}
		assert(!task_wasconnected());
		task_popconnections();
	} else {
		do_flash_screen_pause();
	}
}

PRIVATE void KCALL flash_current_line(VGA *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	invert_current_line_colors(self);
	flash_current_line_pause();
	invert_current_line_colors(self);
}

PRIVATE NONNULL((1)) void LIBANSITTY_CC
VGA_Putc(struct ansitty *__restrict self, char32_t ch)
		THROWS(E_WOULDBLOCK, ...) {
	VGA *me = container_of(self, VGA, at_ansi);
	u8 cp_ch;
	cp_ch = cp437_encode(ch);
	if (cp_ch) {
		vga_putcp437(me, cp_ch);
	} else {
		switch (ch) {

		case 7: /* BEL */
			/* Visual bell */
			if (PREEMPTION_ENABLED())
				flash_current_line(me);
			break;

		case '\t': {
			if (sync_tryread(&me->v_textlock)) {
				unsigned int cur_x, num_space, max_space;
				u16 *oldptr;
				do {
again_dotab:
					oldptr = ATOMIC_READ(me->v_textptr);
					if (oldptr >= me->v_textend) {
						/* Scroll down */
						if (!ATOMIC_CMPXCH(me->v_textptr, oldptr, me->v_textlline))
							goto again_dotab;
						memmovew(me->v_textbase, me->v_text2line,
						         (me->v_textsizey - 1) * me->v_textsizex);
						memsetw(me->v_textlline, VGA_CHR(me, ' '), me->v_textsizex);
						goto again_dotab;
					}
					cur_x     = (oldptr - me->v_textbase) % me->v_textsizex;
					num_space = TABSIZE - (cur_x % TABSIZE);
					max_space = me->v_textsizex - cur_x;
					if (num_space > max_space)
						num_space = max_space;
				} while (!ATOMIC_CMPXCH(me->v_textptr, oldptr, oldptr + num_space));
				/* Output space characters. */
				memsetw(oldptr, VGA_CHR(me, ' '), num_space);
				sync_endread(&me->v_textlock);
			}
		}	break;

		case '\b': {
			u16 *oldptr;
			do {
				oldptr = ATOMIC_READ(me->v_textptr);
				if (oldptr <= me->v_textbase)
					return;
			} while (!ATOMIC_CMPXCH(me->v_textptr, oldptr, oldptr - 1));
		}	break;

		case '\r': {
			/* Return to the start of the current line. */
			u16 *oldptr;
			size_t cur_x, size_x;
			size_x = me->v_textsizex;
			if ((me->at_ansi.at_ttymode & ANSITTY_MODE_NEWLINE_CLRFREE) &&
			    sync_tryread(&me->v_textlock)) {
				do {
					oldptr = ATOMIC_READ(me->v_textptr);
					cur_x  = ((size_t)(oldptr - me->v_textbase) % size_x);
#ifdef CONFIG_VGA_LESS_LINE_FEEDS
					if (cur_x == 0 && cp437_encode(me->v_lastch) != 0)
						cur_x = size_x;
#endif /* CONFIG_VGA_LESS_LINE_FEEDS */
				} while (!ATOMIC_CMPXCH(me->v_textptr, oldptr, oldptr - cur_x));
				memsetw(oldptr, VGA_CHR(me, ' '), size_x - cur_x);
				sync_endread(&me->v_textlock);
			} else {
				do {
					oldptr = ATOMIC_READ(me->v_textptr);
					cur_x  = ((size_t)(oldptr - me->v_textbase) % size_x);
#ifdef CONFIG_VGA_LESS_LINE_FEEDS
					if (cur_x == 0 && cp437_encode(me->v_lastch) != 0)
						cur_x = size_x;
#endif /* CONFIG_VGA_LESS_LINE_FEEDS */
				} while (!ATOMIC_CMPXCH(me->v_textptr, oldptr, oldptr - cur_x));
			}
		}	break;

		case '\n':
			if (sync_tryread(&me->v_textlock)) {
				for (;;) {
					u16 *oldptr;
					size_t cur_x, size_x;
					size_x = me->v_textsizex;
					oldptr = ATOMIC_READ(me->v_textptr);
					cur_x  = ((size_t)(oldptr - me->v_textbase) % size_x);
#ifdef CONFIG_VGA_LESS_LINE_FEEDS
					if (cur_x == 0 && cp437_encode(me->v_lastch) != 0) {
						/* Special case: The previous line was filled entirely, and the cursor had to be  wrapped
						 *               to the next line,  however the first character  then printed was also  a
						 *               linefeed. - In this case, don't wrap the line, as the linefeed requested
						 *               by the caller already happened implicitly, thus not creating an entirely
						 *               empty line and wasting what little screen space we only have. */
					} else
#endif /* CONFIG_VGA_LESS_LINE_FEEDS */
					{
						/* Clear the remainder of the old line */
						u16 *lline = ATOMIC_READ(me->v_scrlllin);
						if (oldptr >= lline) {
							size_t offset;
							offset = oldptr - lline;
							if (offset > size_x)
								offset = size_x;
							if (!ATOMIC_CMPXCH(me->v_textptr, oldptr, lline + offset))
								continue;
							/* Scroll down */
							memmovew(me->v_scrlbase, me->v_scrl2lin, me->v_scrlsize);
							memsetw(lline, VGA_CHR(me, ' '), size_x);
						} else {
							if (!ATOMIC_CMPXCH(me->v_textptr, oldptr, oldptr + size_x))
								continue;
							if (me->at_ansi.at_ttymode & ANSITTY_MODE_NEWLINE_CLRFREE)
								memsetw(oldptr, VGA_CHR(me, ' '), (size_t)(size_x - cur_x));
						}
					}
					break;
				}
				sync_endread(&me->v_textlock);
			}
			break;

		default:
			/* Unicode  says we  should use  `U+FFFD', however  that character doesn't
			 * exist in CP437, however we've got this one that looks somewhat similar. */
			vga_putcp437(me, 4); /* U+2666 */
			break;

		}
	}
	if (!(me->at_ansi.at_ttymode & ANSITTY_MODE_HIDECURSOR))
		vga_update_cursor_pos(me);
#ifdef CONFIG_VGA_LESS_LINE_FEEDS
	me->v_lastch = ch;
#endif /* CONFIG_VGA_LESS_LINE_FEEDS */
}

PRIVATE NONNULL((1)) void LIBANSITTY_CC
VGA_SetTTYMode(struct ansitty *__restrict self,
	           uint16_t new_ttymode)
		THROWS(E_WOULDBLOCK) {
	VGA *me = container_of(self, VGA, at_ansi);
	if (me->v_state & VGA_STATE_FGRAPHICS)
		return;
	if (new_ttymode & ANSITTY_MODE_HIDECURSOR) {
		vga_disable_cursor(me);
	} else {
		vga_update_cursor_pos(me);
	}
}

PRIVATE NONNULL((1)) void LIBANSITTY_CC
VGA_SetScrollRegion(struct ansitty *__restrict self,
                    ansitty_coord_t start_line,
                    ansitty_coord_t end_line) {
	VGA *me = container_of(self, VGA, at_ansi);
	if (sync_tryread(&me->v_textlock)) {
		u16 *base = ATOMIC_READ(me->v_textbase);
		u16 *end  = ATOMIC_READ(me->v_textend);
		size_t sizex = ATOMIC_READ(me->v_textsizex);
		u16 *new_scrlbase, *new_scrlllin;
		new_scrlbase = base + start_line * sizex;
		new_scrlllin = base + end_line * sizex;
		if (new_scrlbase > end)
			new_scrlbase = end;
		if (new_scrlbase < base)
			new_scrlbase = base;
		if (new_scrlllin > end)
			new_scrlllin = end;
		new_scrlllin -= sizex;
		if (new_scrlllin < base)
			new_scrlllin = base;
		if (new_scrlllin < new_scrlbase)
			new_scrlllin = new_scrlbase;
		me->v_scrlbase = new_scrlbase;
		me->v_scrl2lin = new_scrlbase + sizex;
		me->v_scrlllin = new_scrlllin;
		me->v_scrlend  = new_scrlllin + sizex;
		me->v_scrlsize = (size_t)(new_scrlllin - new_scrlbase);
		sync_endread(&me->v_textlock);
	}
}



/* Get/Set the current on-screen cursor position. */
PRIVATE NONNULL((1)) void LIBANSITTY_CC
VGA_SetCursor(struct ansitty *__restrict self,
              ansitty_coord_t x, ansitty_coord_t y,
              bool update_hw_cursor)
		THROWS(E_WOULDBLOCK) {
	VGA *me;
	me = container_of(self, VGA, at_ansi);
	if (sync_tryread(&me->v_textlock)) {
		unsigned int pos;
		if (x < 0)
			x = 0;
		else if (x >= me->v_textsizex) {
			x = me->v_textsizex - 1;
		}
		if (y < 0)
			y = 0;
		else if (y >= me->v_textsizey) {
			y = me->v_textsizey - 1;
		}
		pos = (unsigned int)x + (unsigned int)y * me->v_textsizex;
		me->v_textptr = me->v_textbase + pos;
		if (update_hw_cursor && !(me->at_ansi.at_ttymode & ANSITTY_MODE_HIDECURSOR))
			vga_update_cursor_pos(me);
#ifdef CONFIG_VGA_LESS_LINE_FEEDS
		me->v_lastch = 0; /* Prevent the hidden-newline feature from triggering. */
#endif /* CONFIG_VGA_LESS_LINE_FEEDS */
		sync_endread(&me->v_textlock);
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LIBANSITTY_CC VGA_GetCursor)(struct ansitty *__restrict self,
                                     ansitty_coord_t ppos[2]) {
	VGA *me = container_of(self, VGA, at_ansi);
	u16 *ptr = ATOMIC_READ(me->v_textptr);
	size_t offset = (size_t)(ptr - ATOMIC_READ(me->v_textbase));
	size_t sizex = ATOMIC_READ(me->v_textsizex);
	ppos[0] = (ansitty_coord_t)(offset % sizex);
	ppos[1] = (ansitty_coord_t)(offset / sizex);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LIBANSITTY_CC VGA_GetSize)(struct ansitty *__restrict self,
                                   ansitty_coord_t psize[2]) {
	VGA *me = container_of(self, VGA, at_ansi);
	psize[0] = ATOMIC_READ(me->v_textsizex);
	psize[1] = ATOMIC_READ(me->v_textsizey);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LIBANSITTY_CC VGA_CopyCell)(struct ansitty *__restrict self,
                                    ansitty_offset_t dst_offset,
                                    ansitty_coord_t count) {
	VGA *me  = container_of(self, VGA, at_ansi);
	if (sync_tryread(&me->v_textlock)) {
		u16 *base = ATOMIC_READ(me->v_textbase);
		u16 *src  = ATOMIC_READ(me->v_textptr);
		u16 *end  = ATOMIC_READ(me->v_textend);
		u16 *ptr, *copyend;
		ptr = src + dst_offset;
		if (ptr < base) {
			size_t underflow;
			underflow = base - ptr;
			if (underflow >= count)
				return;
			ptr = base;
			count -= underflow;
		}
		copyend = ptr + count;
		if (copyend < ptr) {
			count = (size_t)(end - ptr);
		} else {
			if (copyend > end)
				count = copyend - ptr;
		}
		copyend = src + count;
		if (copyend > end)
			count = (size_t)(end - src);
		memmovew(ptr, src, count);
		sync_endread(&me->v_textlock);
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LIBANSITTY_CC VGA_FillCell)(struct ansitty *__restrict self,
                                    char32_t ch,
                                    ansitty_coord_t count) {
	VGA *me  = container_of(self, VGA, at_ansi);
	if (sync_tryread(&me->v_textlock)) {
		ansitty_coord_t used_count, max_count;
		u16 *ptr, *end, cell;
		char cpch = cp437_encode((u32)ch);
		if unlikely(!cpch)
			cpch = '?';
		cell = VGA_CHR(me, cpch);
		ptr = ATOMIC_READ(me->v_textptr);
		end = ATOMIC_READ(me->v_textend);
		max_count = (size_t)(end - ptr);
		used_count = count;
		if (used_count > max_count)
			used_count = max_count;
		memsetw(ptr, cell, used_count);
		sync_endread(&me->v_textlock);
	}
}


PRIVATE struct ansitty_operators const vga_ansi_operators = {
	/* .ato_putc         = */ &VGA_Putc,
	/* .ato_setcursor    = */ &VGA_SetCursor,
	/* .ato_getcursor    = */ &VGA_GetCursor,
	/* .ato_getsize      = */ &VGA_GetSize,
	/* .ato_copycell     = */ &VGA_CopyCell,
	/* .ato_fillcell     = */ &VGA_FillCell,
	/* .ato_scroll       = */ NULL, /* TODO */
	/* .ato_cls          = */ NULL, /* TODO */
	/* .ato_el           = */ NULL, /* TODO */
	/* .ato_setcolor     = */ NULL,
	/* .ato_setattrib    = */ NULL,
	/* .ato_setttymode   = */ &VGA_SetTTYMode,
	/* .ato_scrollregion = */ &VGA_SetScrollRegion,
};


PRIVATE void KCALL sync_write_both(VGA *__restrict self) {
again:
	sync_write(&self->v_textlock);
	if unlikely(!sync_trywrite(&self->v_lock)) {
		sync_endwrite(&self->v_textlock);
		sync_write(&self->v_lock);
		if unlikely(!sync_trywrite(&self->v_textlock)) {
			sync_endwrite(&self->v_lock);
			goto again;
		}
	}
}

PRIVATE NOBLOCK void
NOTHROW(KCALL sync_endwrite_both)(VGA *__restrict self) {
	sync_endwrite(&self->v_lock);
	sync_endwrite(&self->v_textlock);
}

PRIVATE void KCALL
VGA_EnableGraphicsMode(VGA *__restrict self,
                       struct vga_mode const *__restrict mode,
                       void const *__restrict pal, size_t color_count,
                       bool savefont DFL(true)) {
	struct vga_font *oldfont = NULL;
	if (self->v_state & VGA_STATE_FGRAPHICS) {
		sync_write_both(self);
		COMPILER_READ_BARRIER();
		if (self->v_state & VGA_STATE_FGRAPHICS) {
			VGA_DoSetMode(self, mode);
			VGA_DoSetPalette(self, pal, color_count);
			sync_endwrite_both(self);
			return;
		}
		sync_endwrite_both(self);
	}
	if (savefont) {
		oldfont = (struct vga_font *)kmalloc(sizeof(struct vga_font),
		                                     GFP_NORMAL | GFP_LOCKED | GFP_PREFLT);
	}
	TRY {
again:
		sync_write_both(self);
		if (!(self->v_state & VGA_STATE_FGRAPHICS)) {
			u16 *textbuf;
			size_t textsize;
			ptrdiff_t diff;
			textsize = self->v_textsizex * self->v_textsizey * 2;
			textbuf = (u16 *)kmalloc_nx(textsize, GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
			if unlikely(!textbuf) {
				size_t new_textsize;
				sync_endwrite_both(self);
				textbuf = (u16 *)kmalloc(textsize, GFP_NORMAL | GFP_LOCKED | GFP_PREFLT);
				TRY {
					sync_write_both(self);
				} EXCEPT {
					kfree(textbuf);
					RETHROW();
				}
				new_textsize = self->v_textsizex * self->v_textsizey * 2;;
				if unlikely(self->v_state & VGA_STATE_FGRAPHICS) {
					sync_endwrite_both(self);
					kfree(textbuf);
					return;
				}
				if unlikely(new_textsize != textsize) {
					u16 *newbuf;
					if (new_textsize > textsize) {
						kfree(textbuf);
						goto again;
					}
					newbuf = (u16 *)krealloc_nx(textbuf, new_textsize,
					                            GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
					if likely(newbuf)
						textbuf = newbuf;
					textsize = new_textsize;
				}
			}
			/* Save the current screen contents. */
			memcpy(textbuf, self->v_textbase, textsize);
			diff = (intptr_t)textbuf - (intptr_t)self->v_textbase;
			assert(!self->v_savedfont);
#define REL(x) ((x) = (__typeof__(x))(uintptr_t)((intptr_t)(x) + diff))
			REL(self->v_textbase);
			REL(self->v_text2line);
			REL(self->v_textlline);
			REL(self->v_textend);
			REL(self->v_textptr);
			REL(self->v_scrlbase);
			REL(self->v_scrl2lin);
			REL(self->v_scrlllin);
			REL(self->v_scrlend);
#undef REL
			if (oldfont)
				VGA_DoGetFont(self, oldfont);
			VGA_DoSetMode(self, mode);
			VGA_DoSetPalette(self, pal, color_count);
			self->v_savedfont = oldfont;
			oldfont           = NULL;
			self->v_state |= VGA_STATE_FGRAPHICS;
		} else {
			VGA_DoSetMode(self, mode);
			VGA_DoSetPalette(self, pal, color_count);
		}
		sync_endwrite_both(self);
	} EXCEPT {
		kfree(oldfont);
		RETHROW();
	}
	kfree(oldfont);
}

PRIVATE void KCALL
VGA_DisableGraphicsMode(VGA *__restrict self) {
	if (!(self->v_state & VGA_STATE_FGRAPHICS))
		return;
	sync_write_both(self);
	if (self->v_state & VGA_STATE_FGRAPHICS) {
		struct vga_font *oldfont;
		u16 *textbuf;
		size_t textsize;
		ptrdiff_t diff;
		oldfont  = self->v_savedfont;
		textsize = self->v_textsizex * self->v_textsizey * 2;
		textbuf  = self->v_textbase;
		diff     = (intptr_t)self->v_textbase_real - (intptr_t)textbuf;
		self->v_savedfont = NULL;
		assert(diff != 0);
#define REL(x) ((x) = (__typeof__(x))(uintptr_t)((intptr_t)(x) + diff))
		REL(self->v_textbase);
		REL(self->v_text2line);
		REL(self->v_textlline);
		REL(self->v_textend);
		REL(self->v_textptr);
		REL(self->v_scrlbase);
		REL(self->v_scrl2lin);
		REL(self->v_scrlllin);
		REL(self->v_scrlend);
#undef REL
		if (oldfont) {
			VGA_DoSetFont(self, oldfont);
			kfree(oldfont);
		}
		VGA_DoSetMode(self, &vga_ansitty_mode);
		VGA_DoSetPalette(self, &vga_ansitty_pal, COMPILER_LENOF(vga_ansitty_pal.vp_pal));
		memcpy(self->v_textbase, textbuf, textsize);
		kfree(textbuf);
		self->v_state &= ~VGA_STATE_FGRAPHICS;
		sync_endwrite_both(self);
	} else {
		sync_endwrite_both(self);
	}
}


PRIVATE NONNULL((1)) syscall_slong_t KCALL
VGA_Ioctl(struct character_device *__restrict self, syscall_ulong_t cmd,
          USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	VGA *me = (VGA *)self;
	(void)mode;
	switch (cmd) {

	case KDSETMODE:
		if ((uintptr_t)arg == KD_TEXT) {
			VGA_DisableGraphicsMode(me);
		} else if ((uintptr_t)arg == KD_GRAPHICS) {
			VGA_EnableGraphicsMode(me,
			                       &vga_mode_gfx320x200_256,
			                       &vga_pal_gfx256,
			                       COMPILER_LENOF(vga_pal_gfx256.vp_pal));
		} else {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_GENERIC,
			      arg);
		}
		break;

	case KDGETMODE:
		validate_writable(arg, sizeof(int));
		*(USER CHECKED int *)arg = me->v_state & VGA_STATE_FGRAPHICS
		                           ? KD_GRAPHICS
		                           : KD_TEXT;
		break;

//TODO:	case PIO_CMAP:
//TODO:		validate_readable(arg, 48);
//TODO:		break;

	default:
		/* Fallback: Try to service a generic video ioctl() */
		return video_device_ioctl(self, cmd, arg, mode);
		break;
	}
	return 0;
}

PRIVATE NONNULL((1, 2)) void KCALL
VGA_MMap(struct character_device *__restrict self,
         struct handle_mmap_info *__restrict info) THROWS(...) {
	VGA *me = (VGA *)self;
	info->hmi_file    = incref(&mfile_phys);
	info->hmi_minaddr = (pos_t)me->v_vram_addr;
	info->hmi_maxaddr = (pos_t)me->v_vram_addr + me->v_vram_size - 1;
}

PRIVATE bool KCALL
VGA_GetFmtByIndex(VGA *__restrict self,
                  USER CHECKED struct vd_format *fmt,
                  size_t id) THROWS(E_SEGFAULT) {
	switch (id) {

	case 0: /* vga_ansitty_mode */
		fmt->vdf_codec = VIDEO_CODEC_NONE;
		fmt->vdf_resx  = self->v_textsizex;
		fmt->vdf_resy  = self->v_textsizey;
		fmt->vdf_scan  = self->v_textsizex * 2;
		fmt->vdf_dpix  = 8;
		fmt->vdf_dpiy  = 16;
		break;

	case 1: /* vga_mode_gfx320x200_256  */
		fmt->vdf_codec = VIDEO_CODEC_PAL256;
		fmt->vdf_resx  = 320;
		fmt->vdf_resy  = 200;
		fmt->vdf_scan  = 320;
		fmt->vdf_dpix  = 0;
		fmt->vdf_dpiy  = 0;
		break;

	case 2: /* vga_mode_gfx640x480_16  */
		fmt->vdf_codec = VIDEO_CODEC_PAL16_LSB;
		fmt->vdf_resx  = 640;
		fmt->vdf_resy  = 480;
		fmt->vdf_scan  = 320;
		fmt->vdf_dpix  = 0;
		fmt->vdf_dpiy  = 0;
		break;

	default:
		return false;
		break;
	}
	return true;
}

PRIVATE size_t KCALL
VGA_ListFmt(struct video_device *__restrict self,
            USER CHECKED struct vd_format *fmt,
            size_t offset, size_t limit)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	VGA *me = (VGA *)self;
	size_t i, result = 0;
	for (i = offset; i < offset + limit; ++i, ++fmt, ++result) {
		if (!VGA_GetFmtByIndex(me, fmt, i))
			break;
	}
	return result;
}

PRIVATE void KCALL
VGA_GetFmt(struct video_device *__restrict self,
           USER CHECKED struct vd_format *fmt)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	VGA *me = (VGA *)self;
	u16 state;
	state = ATOMIC_READ(me->v_state);
	if (!(state & VGA_STATE_FGRAPHICS)) {
do_return_tty_mode:
		VGA_GetFmtByIndex(me, fmt, 0);
	} else {
		struct vga_mode mode;
		sync_write_both(me);
		state = ATOMIC_READ(me->v_state);
		if unlikely(!(state & VGA_STATE_FGRAPHICS)) {
			sync_endwrite_both(me);
			goto do_return_tty_mode;
		}
		VGA_DoGetMode(me, &mode);
		sync_endwrite_both(me);
		if (memcmp(&mode, &vga_mode_gfx640x480_16, sizeof(mode)) == 0) {
			VGA_GetFmtByIndex(me, fmt, 2);
		} else {
			VGA_GetFmtByIndex(me, fmt, 1);
		}
	}
}

PRIVATE void KCALL
VGA_SetFmt(struct video_device *__restrict self,
           USER CHECKED struct vd_format const *fmt)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	VGA *me = (VGA *)self;
	struct vd_format new_format;
	memcpy(&new_format, fmt, sizeof(new_format));
	COMPILER_READ_BARRIER();
	if (new_format.vdf_codec == VIDEO_CODEC_NONE) {
		if (new_format.vdf_dpix != 8 ||
		    new_format.vdf_dpiy != 16 ||
		    new_format.vdf_resx != me->v_textsizex ||
		    new_format.vdf_resy != me->v_textsizey ||
		    new_format.vdf_scan != me->v_textsizex * 2)
			goto badcodec;
		VGA_DisableGraphicsMode(me);
	} else if (new_format.vdf_codec == VIDEO_CODEC_PAL256) {
		if (new_format.vdf_resx != 320 ||
		    new_format.vdf_resy != 200 ||
		    new_format.vdf_scan != 320)
			goto badcodec;
		VGA_EnableGraphicsMode(me,
		                       &vga_mode_gfx320x200_256,
		                       &vga_pal_gfx256,
		                       COMPILER_LENOF(vga_pal_gfx256.vp_pal));
	} else if (new_format.vdf_codec == VIDEO_CODEC_PAL16_LSB) {
		if (new_format.vdf_resx != 640 ||
		    new_format.vdf_resy != 480 ||
		    new_format.vdf_scan != 320)
			goto badcodec;
		VGA_EnableGraphicsMode(me,
		                       &vga_mode_gfx640x480_16,
		                       &vga_pal_gfx16,
		                       COMPILER_LENOF(vga_pal_gfx16.vp_pal));
	} else {
badcodec:
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_VIDEO_CODEC,
		      new_format.vdf_codec);
	}
}

PRIVATE void KCALL
VGA_GetPal(struct video_device *__restrict self,
           vd_codec_t codec, USER CHECKED struct vd_palette *pal)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	VGA *me = (VGA *)self;
	size_t i, count;
	count = VIDEO_CODEC_PALSIZ(codec);
	if (count > 256)
		count = 256;
	i = 0;
	sync_write(&me->v_lock);
	TRY {
		vga_w(VGA_PEL_MSK, 0xff);
		vga_w(VGA_PEL_IR, 0x00);
		for (; i < count; ++i) {
			u8 r, g, b;
			vd_color_t color;
			r     = vga_r(VGA_PEL_D) << 2;
			g     = vga_r(VGA_PEL_D) << 2;
			b     = vga_r(VGA_PEL_D) << 2;
			color = VIDEO_COLOR_RGB(r, g, b);
			ATOMIC_WRITE(pal->vdp_pal[i], color);
		}
	} EXCEPT {
		/* Must complete the operation. - VGA wouldn't understand otherwise. */
		for (i *= 3; i < 768; ++i)
			vga_r(VGA_PEL_D);
		sync_endwrite(&me->v_lock);
		RETHROW();
	}
	for (i *= 3; i < 768; ++i)
		vga_r(VGA_PEL_D);
	sync_endwrite(&me->v_lock);
}

PRIVATE void KCALL
VGA_SetPal(struct video_device *__restrict self,
           vd_codec_t codec, USER CHECKED struct vd_palette const *pal)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	VGA *me = (VGA *)self;
	size_t i, count;
	count = VIDEO_CODEC_PALSIZ(codec);
	if (count > 256)
		count = 256;
	if (!pal) {
		if (codec == VIDEO_CODEC_PAL256) {
			VGA_SetPalette(me, &vga_pal_gfx256, COMPILER_LENOF(vga_pal_gfx256.vp_pal));
		} else if (codec == VIDEO_CODEC_PAL16_LSB ||
		           codec == VIDEO_CODEC_PAL16_MSB) {
			VGA_SetPalette(me, &vga_pal_gfx16, COMPILER_LENOF(vga_pal_gfx16.vp_pal));
		} else {
			VGA_SetPalette(me, &vga_ansitty_pal, COMPILER_LENOF(vga_ansitty_pal.vp_pal));
		}
		return;
	}
	i = 0;
	sync_write(&me->v_lock);
	TRY {
		vga_w(VGA_PEL_MSK, 0xff);
		vga_w(VGA_PEL_IW, 0x00);
		for (; i < count; ++i) {
			vd_color_t color = ATOMIC_READ(pal->vdp_pal[i]);
			vga_w(VGA_PEL_D, VIDEO_COLOR_GET_RED(color) >> 2);
			vga_w(VGA_PEL_D, VIDEO_COLOR_GET_GREEN(color) >> 2);
			vga_w(VGA_PEL_D, VIDEO_COLOR_GET_BLUE(color) >> 2);
		}
	} EXCEPT {
		/* Must complete the operation. - VGA wouldn't understand otherwise. */
		for (i *= 3; i < 768; ++i)
			vga_w(VGA_PEL_D, 0);
		sync_endwrite(&me->v_lock);
		RETHROW();
	}
	for (i *= 3; i < 768; ++i)
		vga_w(VGA_PEL_D, 0);
	sync_endwrite(&me->v_lock);
}


PRIVATE struct video_device_ops const vga_video_operators = {
	/* .vdf_listfmt = */ &VGA_ListFmt,
	/* .vdf_getfmt  = */ &VGA_GetFmt,
	/* .vdf_setfmt  = */ &VGA_SetFmt,
	/* .vdf_getpal  = */ &VGA_GetPal,
	/* .vdf_setpal  = */ &VGA_SetPal,
};




PRIVATE REF VGA *vga_device = NULL;

PRIVATE NOBLOCK ATTR_FREETEXT void
NOTHROW(KCALL vga_disable_annoying_blinking)(void) {
	u8 qr1, temp;
	qr1 = vga_rseq(VGA_SEQ_CLOCK_MODE);
	vga_wseq(VGA_SEQ_RESET, 0x1);
	vga_wseq(VGA_SEQ_CLOCK_MODE, qr1 | VGA_SR01_FSCREEN_OFF);
	vga_wseq(VGA_SEQ_RESET, 0x3);

	vga_r(VGA_IS1_RC);
	vga_w(VGA_ATT_W, 0x00);

	vga_r(VGA_IS1_RC);
	temp = vga_rattr(VGA_ATC_MODE);
	vga_r(VGA_IS1_RC);
	vga_wattr(VGA_ATC_MODE, temp & ~(VGA_AT10_FBLINK));

	vga_r(VGA_IS1_RC);
	vga_w(VGA_ATT_W, 0x20);

	vga_wseq(VGA_SEQ_RESET, 0x1);
	vga_wseq(VGA_SEQ_CLOCK_MODE, qr1 & ~VGA_SR01_FSCREEN_OFF);
	vga_wseq(VGA_SEQ_RESET, 0x3);
}

PRIVATE ATTR_FREETEXT DRIVER_INIT void KCALL init(void) {
	vga_disable_annoying_blinking();
	vga_device = CHARACTER_DEVICE_ALLOC(VGA);
	TRY {
		void *vram_base;
		atomic_lock_cinit(&vga_device->v_lock);
		atomic_rwlock_cinit(&vga_device->v_textlock);
		vga_device->v_vram_addr = (physaddr_t)0xa0000;
		vga_device->v_vram_size = 8192 * 4 * 4; /* 128K */

		vram_base = mman_map(/* self:        */ &mman_kernel,
		                     /* hint:        */ MHINT_GETADDR(KERNEL_MHINT_DEVICE),
		                     /* num_bytes:   */ vga_device->v_vram_size,
		                     /* prot:        */ PROT_READ | PROT_WRITE | PROT_SHARED,
		                     /* flags:       */ MHINT_GETMODE(KERNEL_MHINT_DEVICE),
		                     /* file:        */ &mfile_phys,
		                     /* file_fspath: */ NULL,
		                     /* file_fsname: */ NULL,
		                     /* file_pos:    */ (pos_t)vga_device->v_vram_addr);
		TRY {
			vga_device->v_vram  = (byte_t *)vram_base;
			vga_device->v_crt_i = VGA_CRT_IC;
			vga_device->v_crt_d = VGA_CRT_DC;
			vga_device->v_is1_r = VGA_IS1_RC;
			if (!(vga_r(VGA_MIS_R) & VGA_MIS_FCOLOR)) {
				vga_device->v_crt_i = VGA_CRT_IM;
				vga_device->v_crt_d = VGA_CRT_DM;
				vga_device->v_is1_r = VGA_IS1_RM;
			}
			/* Initialize the video and ansi layers */
			video_device_cinit(vga_device,
			                   &vga_video_operators,
			                   &vga_ansi_operators);

			vga_device->cd_type.ct_ioctl = &VGA_Ioctl;
			vga_device->cd_type.ct_mmap  = &VGA_MMap;

			strcpy(vga_device->cd_name, FREESTR("vga"));

			/* Configure text-mode pointers. */
			vga_device->v_textbase_real = (u16 *)(vga_device->v_vram + 0x18000);
			vga_device->v_textbase      = vga_device->v_textbase_real;
			vga_device->v_textsizex     = 80;
			vga_device->v_textsizey     = 25;
			vga_device->v_text2line     = vga_device->v_textbase + vga_device->v_textsizex;
			vga_device->v_textlline     = vga_device->v_textbase + ((vga_device->v_textsizey - 1) * vga_device->v_textsizex);
			vga_device->v_textend       = vga_device->v_textbase + (vga_device->v_textsizey * vga_device->v_textsizex);
			vga_device->v_textptr       = vga_device->v_textbase;
			vga_device->v_scrlbase      = vga_device->v_textbase;
			vga_device->v_scrl2lin      = vga_device->v_text2line;
			vga_device->v_scrlllin      = vga_device->v_textlline;
			vga_device->v_scrlend       = vga_device->v_textend;
			vga_device->v_scrlsize      = ((vga_device->v_textsizey - 1) * vga_device->v_textsizex);

			/* Force text mode, and set the ANSI color palette. */
			VGA_DoSetMode(vga_device, &vga_ansitty_mode);
			VGA_DoSetPalette(vga_device, &vga_ansitty_pal, COMPILER_LENOF(vga_ansitty_pal.vp_pal));

			/* Register the VGA adapter device. */
			character_device_register_auto(vga_device);
		} EXCEPT {
			NESTED_EXCEPTION;
			mman_unmap(&mman_kernel, vram_base, vga_device->v_vram_size);
			RETHROW();
		}
	} EXCEPT {
		destroy(vga_device);
		vga_device = NULL;
		RETHROW();
	}
}

PRIVATE DRIVER_FINI void KCALL fini(void) {
	if (vga_device) {
		character_device_unregister(vga_device);
		decref(vga_device);
	}
}

DECL_END

#endif /* !GUARD_MODVGA_VGA_C */
