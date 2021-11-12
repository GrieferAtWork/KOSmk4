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
#ifndef GUARD_LIBSVGA_CS_VGA_C
#define GUARD_LIBSVGA_CS_VGA_C 1
#define _KOS_ALTERATIONS_SOURCE 1 /* Want sensical parameter order for outb/outw/outl */

#include "api.h"
/**/

#include <hw/video/vga.h>
#include <hw/video/vgamodes.h>
#include <kos/types.h>

#include <libsvga/chipset.h>
#include <libsvga/chipsets/vga.h>

#include "cs-vga.h"

DECL_BEGIN

/* VGA defines a total of 64K video memory, across 4 planes
 * which  can   be  individually   mapped  at   A0000-BFFFF */
#define CS_VGA_VPAGESIZ (16 * 1024)
#define CS_VGA_VPAGECNT 4

/* List of supported VGA modes. */
INTERN_CONST struct vga_known_mode const vga_modelist[CS_VGAMODE_COUNT] = {
	[CS_VGAMODE_TEXT] = {
		.vkm_info = {
			.gmi_base = {
				.smi_lfb            = 0xb8000,
				.smi_flags          = SVGA_MODEINFO_F_LFB | SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_TXT,
				.smi_scanline       = 160,
				.smi_resx           = 80,
				.smi_resy           = 25,
				.smi_bits_per_pixel = 16,
			},
			.gmi_modeid = CS_VGAMODE_TEXT,
		},
		.vkm_regs = VGAMODE_INIT_VGA_TEXT,
	},

	[CS_VGAMODE_320X200X16] = {
		.vkm_info = {
			.gmi_base = {
				.smi_vpagesiz       = CS_VGA_VPAGESIZ,
				.smi_vpagecnt       = CS_VGA_VPAGECNT,
				.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
				.smi_scanline       = 40,
				.smi_resx           = 320,
				.smi_resy           = 200,
				.smi_bits_per_pixel = 1,
				.smi_colorbits      = 4,
			},
			.gmi_modeid = CS_VGAMODE_320X200X16,
		},
		.vkm_regs = VGAMODE_INIT_VGA_320X200X16,
	},

	[CS_VGAMODE_640X200X16] = {
		.vkm_info = {
			.gmi_base = {
				.smi_vpagesiz       = CS_VGA_VPAGESIZ,
				.smi_vpagecnt       = CS_VGA_VPAGECNT,
				.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
				.smi_scanline       = 80,
				.smi_resx           = 640,
				.smi_resy           = 200,
				.smi_bits_per_pixel = 1,
				.smi_colorbits      = 4,
			},
			.gmi_modeid = CS_VGAMODE_640X200X16,
		},
		.vkm_regs = VGAMODE_INIT_VGA_640X200X16,
	},

	[CS_VGAMODE_640X350X16] = {
		.vkm_info = {
			.gmi_base = {
				.smi_vpagesiz       = CS_VGA_VPAGESIZ,
				.smi_vpagecnt       = CS_VGA_VPAGECNT,
				.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
				.smi_scanline       = 80,
				.smi_resx           = 640,
				.smi_resy           = 350,
				.smi_bits_per_pixel = 1,
				.smi_colorbits      = 4,
			},
			.gmi_modeid = CS_VGAMODE_640X350X16,
		},
		.vkm_regs = VGAMODE_INIT_VGA_640X350X16,
	},

	[CS_VGAMODE_640X480X16] = {
		.vkm_info = {
			.gmi_base = {
				.smi_vpagesiz       = CS_VGA_VPAGESIZ,
				.smi_vpagecnt       = CS_VGA_VPAGECNT,
				.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
				.smi_scanline       = 80,
				.smi_resx           = 640,
				.smi_resy           = 480,
				.smi_bits_per_pixel = 1,
				.smi_colorbits      = 4,
			},
			.gmi_modeid = CS_VGAMODE_640X480X16,
		},
		.vkm_regs = VGAMODE_INIT_VGA_640X480X16,
	},

	[CS_VGAMODE_640X480X2] = {
		.vkm_info = {
			.gmi_base = {
				.smi_vpagesiz       = CS_VGA_VPAGESIZ,
				.smi_vpagecnt       = CS_VGA_VPAGECNT,
				.smi_flags          = SVGA_MODEINFO_F_BW | SVGA_MODEINFO_F_PAL,
				.smi_scanline       = 80,
				.smi_resx           = 640,
				.smi_resy           = 480,
				.smi_bits_per_pixel = 1,
				.smi_colorbits      = 1, /* By limiting ourselves to only the first plane, and  using
				                          * a special palette that is only white iff the relevant bit
				                          * from plane#0 is 1, we can emulate monochrome 640x480. */
			},
			.gmi_modeid = CS_VGAMODE_640X480X2,
		},
		.vkm_regs = VGAMODE_INIT_VGA_640X480X16,
	},

	[CS_VGAMODE_320X200X256] = {
		.vkm_info = {
			.gmi_base = {
				.smi_vpagesiz       = CS_VGA_VPAGESIZ,
				.smi_vpagecnt       = CS_VGA_VPAGECNT,
				.smi_flags          = SVGA_MODEINFO_F_PAL,
				.smi_scanline       = 320,
				.smi_resx           = 320,
				.smi_resy           = 200,
				.smi_bits_per_pixel = 8,
				.smi_colorbits      = 8,
			},
			.gmi_modeid = CS_VGAMODE_320X200X256,
		},
		.vkm_regs = VGAMODE_INIT_VGA_320X200X256,
	},

	[CS_VGAMODE_320X240X256] = {
		.vkm_info = {
			.gmi_base = {
				.smi_vpagesiz       = CS_VGA_VPAGESIZ,
				.smi_vpagecnt       = CS_VGA_VPAGECNT,
				.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
				.smi_scanline       = 80,
				.smi_resx           = 320,
				.smi_resy           = 240,
				.smi_bits_per_pixel = 2,
				.smi_colorbits      = 8,
			},
			.gmi_modeid = CS_VGAMODE_320X240X256,
		},
		.vkm_regs = VGAMODE_INIT_VGA_320X240X256,
	},

	[CS_VGAMODE_320X400X256] = {
		.vkm_info = {
			.gmi_base = {
				.smi_vpagesiz       = CS_VGA_VPAGESIZ,
				.smi_vpagecnt       = CS_VGA_VPAGECNT,
				.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
				.smi_scanline       = 80,
				.smi_resx           = 320,
				.smi_resy           = 400,
				.smi_bits_per_pixel = 2,
				.smi_colorbits      = 8,
			},
			.gmi_modeid = CS_VGAMODE_320X400X256,
		},
		.vkm_regs = VGAMODE_INIT_VGA_320X400X256,
	},

	[CS_VGAMODE_360X480X256] = {
		.vkm_info = {
			.gmi_base = {
				.smi_vpagesiz       = CS_VGA_VPAGESIZ,
				.smi_vpagecnt       = CS_VGA_VPAGECNT,
				.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
				.smi_scanline       = 90,
				.smi_resx           = 360,
				.smi_resy           = 480,
				.smi_bits_per_pixel = 2,
				.smi_colorbits      = 8,
			},
			.gmi_modeid = CS_VGAMODE_360X480X256,
		},
		.vkm_regs = VGAMODE_INIT_VGA_360X480X256,
	},

	[CS_VGAMODE_720X348X2] = {
		.vkm_info = {
			.gmi_base = {
				.smi_vpagesiz       = CS_VGA_VPAGESIZ,
				.smi_vpagecnt       = CS_VGA_VPAGECNT,
				.smi_flags          = SVGA_MODEINFO_F_BW/* | SVGA_MODEINFO_F_PAL*/, /* XXX: Should this have PAL set? */
				.smi_scanline       = 90,
				.smi_resx           = 720,
				.smi_resy           = 348,
				.smi_bits_per_pixel = 1,
				.smi_colorbits      = 1,
			},
			.gmi_modeid = CS_VGAMODE_720X348X2,
		},
		.vkm_regs = VGAMODE_INIT_VGA_720X348X2,
	},

};


/* TODO */


DECL_END

#endif /* !GUARD_LIBSVGA_CS_VGA_C */
