/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBSVGADRV_CS_VGA_C
#define GUARD_LIBSVGADRV_CS_VGA_C 1
#define _KOS_ALTERATIONS_SOURCE 1 /* Want sensical parameter order for outb/outw/outl */
#define _KOS_SOURCE 1

#include "api.h"
/**/

#ifdef CONFIG_HAVE_LIBSVGADRV_CHIPSET_VGA
#include <hw/video/vga.h>
#include <hw/video/vgamodes.h>
#include <kos/types.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <libsvgadrv/chipset.h>
#include <libsvgadrv/chipsets/vga.h>
#include <libsvgadrv/util/vgaio.h>

#include "basevga.h"
#include "cs-vga.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* List of supported VGA modes. */
INTERN_CONST struct vga_known_mode const vga_modelist[CS_VGAMODE_COUNT] = {
	[CS_VGAMODE_TEXT] = {
		.vkm_info = {
			.smi_lfb            = 0xB8000,
			.smi_flags          = SVGA_MODEINFO_F_LFB | SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_TXT,
			.smi_scanline       = 160,
			.smi_resx           = 80,
			.smi_resy           = 25,
			.smi_bits_per_pixel = 16,
		},
		.vkm_regs = VGAMODE_INIT_VGA_TEXT,
	},

	[CS_VGAMODE_320X200X16] = {
		.vkm_info = {
			.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
			.smi_scanline       = 40,
			.smi_resx           = 320,
			.smi_resy           = 200,
			.smi_bits_per_pixel = 1,
			.smi_colorbits      = 4,
		},
		.vkm_regs = VGAMODE_INIT_VGA_320X200X16,
	},

	[CS_VGAMODE_640X200X16] = {
		.vkm_info = {
			.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
			.smi_scanline       = 80,
			.smi_resx           = 640,
			.smi_resy           = 200,
			.smi_bits_per_pixel = 1,
			.smi_colorbits      = 4,
		},
		.vkm_regs = VGAMODE_INIT_VGA_640X200X16,
	},

	[CS_VGAMODE_640X350X16] = {
		.vkm_info = {
			.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
			.smi_scanline       = 80,
			.smi_resx           = 640,
			.smi_resy           = 350,
			.smi_bits_per_pixel = 1,
			.smi_colorbits      = 4,
		},
		.vkm_regs = VGAMODE_INIT_VGA_640X350X16,
	},

	[CS_VGAMODE_640X480X16] = {
		.vkm_info = {
			.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
			.smi_scanline       = 80,
			.smi_resx           = 640,
			.smi_resy           = 480,
			.smi_bits_per_pixel = 1,
			.smi_colorbits      = 4,
		},
		.vkm_regs = VGAMODE_INIT_VGA_640X480X16,
	},

	[CS_VGAMODE_640X480X2] = {
		.vkm_info = {
			.smi_flags          = SVGA_MODEINFO_F_BW | SVGA_MODEINFO_F_PAL,
			.smi_scanline       = 80,
			.smi_resx           = 640,
			.smi_resy           = 480,
			.smi_bits_per_pixel = 1,
			.smi_colorbits      = 1, /* By limiting ourselves to only the first plane, and  using
			                          * a special palette that is only white iff the relevant bit
			                          * from plane#0 is 1, we can emulate monochrome 640x480. */
		},
		.vkm_regs = VGAMODE_INIT_VGA_640X480X16,
	},

	[CS_VGAMODE_320X200X256] = {
		.vkm_info = {
			.smi_lfb            = 0xA0000,
			.smi_flags          = SVGA_MODEINFO_F_LFB | SVGA_MODEINFO_F_PAL,
			.smi_scanline       = 320,
			.smi_resx           = 320,
			.smi_resy           = 200,
			.smi_bits_per_pixel = 8,
			.smi_colorbits      = 8,
		},
		.vkm_regs = VGAMODE_INIT_VGA_320X200X256,
	},

	[CS_VGAMODE_320X240X256] = {
		.vkm_info = {
			.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
			.smi_scanline       = 80,
			.smi_resx           = 320,
			.smi_resy           = 240,
			.smi_bits_per_pixel = 2,
			.smi_colorbits      = 8,
		},
		.vkm_regs = VGAMODE_INIT_VGA_320X240X256,
	},

	[CS_VGAMODE_320X400X256] = {
		.vkm_info = {
			.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
			.smi_scanline       = 80,
			.smi_resx           = 320,
			.smi_resy           = 400,
			.smi_bits_per_pixel = 2,
			.smi_colorbits      = 8,
		},
		.vkm_regs = VGAMODE_INIT_VGA_320X400X256,
	},

	[CS_VGAMODE_360X480X256] = {
		.vkm_info = {
			.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
			.smi_scanline       = 90,
			.smi_resx           = 360,
			.smi_resy           = 480,
			.smi_bits_per_pixel = 2,
			.smi_colorbits      = 8,
		},
		.vkm_regs = VGAMODE_INIT_VGA_360X480X256,
	},

	[CS_VGAMODE_720X348X2] = {
		.vkm_info = {
			.smi_flags          = SVGA_MODEINFO_F_BW/* | SVGA_MODEINFO_F_PAL*/, /* XXX: Should this have PAL set? */
			.smi_scanline       = 90,
			.smi_resx           = 720,
			.smi_resy           = 348,
			.smi_bits_per_pixel = 1,
			.smi_colorbits      = 1,
		},
		.vkm_regs = VGAMODE_INIT_VGA_720X348X2,
	},

};


INTERN_CONST struct vga_known_mode const ega_modelist[CS_EGAMODE_COUNT] = {
	[CS_EGAMODE_TEXT] = {
		.vkm_info = {
			.smi_lfb            = 0xB8000,
			.smi_flags          = SVGA_MODEINFO_F_LFB | SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_TXT,
			.smi_scanline       = 160,
			.smi_resx           = 80,
			.smi_resy           = 25,
			.smi_bits_per_pixel = 16,
		},
		.vkm_regs = VGAMODE_INIT_EGA_TEXT,
	},

	[CS_EGAMODE_320X200X16] = {
		.vkm_info = {
			.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
			.smi_scanline       = 40,
			.smi_resx           = 320,
			.smi_resy           = 200,
			.smi_bits_per_pixel = 1,
			.smi_colorbits      = 4,
		},
		.vkm_regs = VGAMODE_INIT_EGA_320X200X16,
	},

	[CS_EGAMODE_640X200X16] = {
		.vkm_info = {
			.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
			.smi_scanline       = 80,
			.smi_resx           = 640,
			.smi_resy           = 200,
			.smi_bits_per_pixel = 1,
			.smi_colorbits      = 4,
		},
		.vkm_regs = VGAMODE_INIT_EGA_640X200X16,
	},

	[CS_EGAMODE_640X350X16] = {
		.vkm_info = {
			.smi_flags          = SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_PLANAR,
			.smi_scanline       = 80,
			.smi_resx           = 640,
			.smi_resy           = 350,
			.smi_bits_per_pixel = 1,
			.smi_colorbits      = 4,
		},
		.vkm_regs = VGAMODE_INIT_EGA_640X350X16,
	},

};





#ifdef SVGA_HAVE_HW_SCROLL
PRIVATE NONNULL((1)) void CC /* For use when `smi_bits_per_pixel == 8' */
vga_v_setdisplaystart_linear(struct svga_chipset *__restrict self, size_t offset) {
	struct vga_chipset *me = (struct vga_chipset *)self;
	vga_wcrt(me->gcs_crt_icX, VGA_CRTC_START_LO, (uint8_t)(offset));
	vga_wcrt(me->gcs_crt_icX, VGA_CRTC_START_HI, (uint8_t)(offset >> 8));
	self->sc_displaystart = offset;
}

PRIVATE NONNULL((1)) void CC /* For use when `smi_bits_per_pixel == 1' (16-color mode) */
vga_v_setdisplaystart_16(struct svga_chipset *__restrict self, size_t offset) {
	struct vga_chipset *me = (struct vga_chipset *)self;
	uint8_t temp = vga_rattr(VGA_IS1_RC, VGA_ATT_IW_PAS | VGA_ATC_PEL);
	vga_wattr(VGA_IS1_RC, VGA_ATT_IW_PAS | VGA_ATC_PEL, (temp & VGA_AT13_FRESERVED) | (offset & 7));
	self->sc_displaystart = offset;
	offset >>= 3;
	vga_wcrt(me->gcs_crt_icX, VGA_CRTC_START_LO, (uint8_t)(offset));
	vga_wcrt(me->gcs_crt_icX, VGA_CRTC_START_HI, (uint8_t)(offset >> 8));
}

PRIVATE NONNULL((1)) void CC /* For use when `smi_bits_per_pixel == 2' (256-color mode) */
vga_v_setdisplaystart_256(struct svga_chipset *__restrict self, size_t offset) {
	struct vga_chipset *me = (struct vga_chipset *)self;
	uint8_t temp = vga_rattr(VGA_IS1_RC, VGA_ATT_IW_PAS | VGA_ATC_PEL);
	vga_wattr(VGA_IS1_RC, VGA_ATT_IW_PAS | VGA_ATC_PEL, (temp & VGA_AT13_FRESERVED) | ((offset & 3) << 1));
	self->sc_displaystart = offset;
	offset >>= 2;
	vga_wcrt(me->gcs_crt_icX, VGA_CRTC_START_LO, (uint8_t)(offset));
	vga_wcrt(me->gcs_crt_icX, VGA_CRTC_START_HI, (uint8_t)(offset >> 8));
}

PRIVATE NONNULL((1)) void CC /* For use when `smi_bits_per_pixel == 2' (256-color mode) */
ega_v_setdisplaystart(struct svga_chipset *__restrict self, size_t offset) {
	struct vga_chipset *me = (struct vga_chipset *)self;
	vga_wattr(VGA_IS1_RC, VGA_ATT_IW_PAS | VGA_ATC_PEL,
	          (baseega_registers.vr_mode.vm_att_pel & VGA_AT13_FRESERVED) |
	          (offset & 7));
	self->sc_displaystart = offset;
	offset >>= 3;
	vga_wcrt(me->gcs_crt_icX, VGA_CRTC_START_LO, (uint8_t)(offset));
	vga_wcrt(me->gcs_crt_icX, VGA_CRTC_START_HI, (uint8_t)(offset >> 8));
}

PRIVATE NONNULL((1)) void CC
vga_v_setlogicalwidth(struct svga_chipset *__restrict self, uint32_t offset) {
	struct vga_chipset *me = (struct vga_chipset *)self;
	/* This right here limits `offset' to: {range: [0,2040], align: 8} */
	vga_wcrt(me->gcs_crt_icX, VGA_CRTC_OFFSET, (uint8_t)(offset >> 3));
	self->sc_logicalwidth = offset;
}
#endif /* SVGA_HAVE_HW_SCROLL */


/* Raw VGA doesn't need to save any additional registers.
 * The base registers  are already saved  by the  caller! */
PRIVATE NONNULL((1)) void CC
vga_v_getregs(struct svga_chipset *__restrict UNUSED(self),
              byte_t regbuf[]) {
	(void)regbuf;
}
#define vga_v_setregs (*(void(CC *)(struct svga_chipset *__restrict, __byte_t const[]))&vga_v_getregs)


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC vga_v_fini)(struct svga_chipset *__restrict UNUSED(self)) {
	/* nothing */
}



INTERN WUNUSED NONNULL((1, 2, 3)) bool CC
vga_v_getmode(struct svga_chipset *__restrict UNUSED(self),
              struct svga_modeinfo *__restrict result,
              uintptr_t *__restrict p_index)
		THROWS(E_IOERROR) {
	if (*p_index >= lengthof(vga_modelist))
		return false; /* No more modes... */
	/* Copy mode information. */
	memcpy(result, &vga_modelist[*p_index].vkm_info,
	       sizeof(struct svga_modeinfo));
	++*p_index;
	return true;
}

PRIVATE WUNUSED NONNULL((1, 2, 3)) bool CC
ega_v_getmode(struct svga_chipset *__restrict UNUSED(self),
              struct svga_modeinfo *__restrict result,
              uintptr_t *__restrict p_index)
		THROWS(E_IOERROR) {
	if (*p_index >= lengthof(ega_modelist))
		return false; /* No more modes... */
	/* Copy mode information. */
	memcpy(result, &ega_modelist[*p_index].vkm_info,
	       sizeof(struct svga_modeinfo));
	++*p_index;
	return true;
}

PRIVATE NONNULL((1, 2)) void CC
vga_setmode_common(struct vga_chipset *__restrict self,
                   struct vga_mode const *__restrict mode) {
	basevga_setmode(mode);
	self->gcs_crt_icX = VGA_CRT_IC;
	if (!(mode->vm_mis & VGA_MIS_FCOLOR)) {
		self->gcs_crt_icX = VGA_CRT_IM;
	}
}

INTERN NONNULL((1, 2)) void CC
vga_v_setmode(struct svga_chipset *__restrict self,
              struct svga_modeinfo const *__restrict mode) {
	struct vga_chipset *me = (struct vga_chipset *)self;
	uint8_t modeid;
	for (modeid = 0;; ++modeid) {
		assert(modeid <= lengthof(vga_modelist));
		if (bcmp(&vga_modelist[modeid].vkm_info, mode,
		         sizeof(struct svga_modeinfo)) == 0)
			break;
	}

	/* Set VGA registers. */
	vga_setmode_common(me, &vga_modelist[modeid].vkm_regs);

	/* Define mode-specific operators. */
#ifdef SVGA_HAVE_HW_SCROLL
	switch (mode->smi_bits_per_pixel) {
	case 1: me->sc_ops.sco_setdisplaystart = &vga_v_setdisplaystart_16; break;
	case 2: me->sc_ops.sco_setdisplaystart = &vga_v_setdisplaystart_256; break;
	case 8: me->sc_ops.sco_setdisplaystart = &vga_v_setdisplaystart_linear; break;
	case 16: break; /* Text-mode. */
	default: __builtin_unreachable();
	}
	self->sc_ops.sco_setlogicalwidth = &vga_v_setlogicalwidth;
	me->sc_displaystart = 0;
	me->sc_logicalwidth = 0;
#endif /* SVGA_HAVE_HW_SCROLL */

	/* NOTE: We don't define the setwindow operators because
	 *       standard EGA/VGA don't  have multiple  windows! */
	self->sc_rdwindow = 0;
	self->sc_wrwindow = 0;
#ifdef SVGA_HAVE_HW_SCROLL
	self->sc_logicalwidth_max   = 2040; /* s.a. `vga_v_setlogicalwidth' */
	self->sc_logicalwidth_align = 8;    /* s.a. `vga_v_setlogicalwidth' */
#endif /* SVGA_HAVE_HW_SCROLL */
}

PRIVATE NONNULL((1, 2)) void CC
ega_v_setmode(struct svga_chipset *__restrict self,
              struct svga_modeinfo const *__restrict mode) {
	struct vga_chipset *me = (struct vga_chipset *)self;
	uint8_t modeid;
	for (modeid = 0;; ++modeid) {
		assert(modeid <= lengthof(vga_modelist));
		if (bcmp(&vga_modelist[modeid].vkm_info, mode,
		         sizeof(struct svga_modeinfo)) == 0)
			break;
	}

	/* Set VGA registers. */
	vga_setmode_common(me, &vga_modelist[modeid].vkm_regs);

	/* Define mode-specific operators. */
#ifdef SVGA_HAVE_HW_SCROLL
	me->sc_ops.sco_setdisplaystart = &ega_v_setdisplaystart;
	me->sc_displaystart            = 0;
	me->sc_logicalwidth            = 0;
#endif /* SVGA_HAVE_HW_SCROLL */
}



/* Probe for VGA support.
 * @return: true:  Chipset found.
 * @return: false: Chipset isn't present. */
INTERN WUNUSED NONNULL((1)) bool CC
cs_vga_probe(struct svga_chipset *__restrict self) {

	/* Initialize the VGA chipset controller. */
	self->sc_ops.sco_fini = &vga_v_fini;

	if (basevga_flags & BASEVGA_FLAG_ISEGA) {
		self->sc_ops.sco_getmode = &ega_v_getmode;
		self->sc_ops.sco_setmode = &ega_v_setmode;
		self->sc_vmemsize        = 16 * 1024; /* EGA had at least 64K video memory. */
	} else {
		self->sc_ops.sco_getmode = &vga_v_getmode;
		self->sc_ops.sco_setmode = &vga_v_setmode;
		self->sc_vmemsize        = 4 * 16 * 1024; /* Standard VGA has 256K of video memory */
	}
	self->sc_ops.sco_modeinfosize = sizeof(struct svga_modeinfo);
	self->sc_ops.sco_strings      = NULL;
	self->sc_ops.sco_getregs      = &vga_v_getregs;
	self->sc_ops.sco_setregs      = &vga_v_setregs;
	self->sc_ops.sco_regsize      = 0;
	return true;
}

DECL_END
#endif /* CONFIG_HAVE_LIBSVGADRV_CHIPSET_VGA */

#endif /* !GUARD_LIBSVGADRV_CS_VGA_C */
