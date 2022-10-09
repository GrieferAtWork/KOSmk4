/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBSVGADRV_CS_VESA_C
#define GUARD_LIBSVGADRV_CS_VESA_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#ifdef CONFIG_HAVE_LIBSVGADRV_CHIPSET_VESA
#include <hybrid/align.h>
#include <hybrid/bit.h>

#include <kos/except.h>
#include <kos/kernel/types.h>

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <libbios86/bios.h>

#include "basevga.h"
#include "cs-vesa.h"

#ifndef __KERNEL__
#include <dlfcn.h>
#endif /* !__KERNEL__ */

DECL_BEGIN

/*
 * VESA driver. Based on:
 * - https://www.lowlevel.eu/wiki/VESA_BIOS_Extensions (german)
 * - http://www.phatcode.net/res/221/files/vbe20.pdf
 */

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#ifdef __KERNEL__
#define vesa_chipset_bios86_int(self, intno) \
	bios86_emulator_int(&(self)->vc_emu, intno)
#else /* __KERNEL__ */
#define vesa_chipset_bios86_int(self, intno) \
	((*(self)->_vc_bios86_int)(&(self)->vc_emu, intno))
#endif /* !__KERNEL__ */


/* Check if the BIOS has VESA support. */
PRIVATE WUNUSED NONNULL((1)) struct vbe_biosinfo *CC
vesa_getbiosinfo(struct vesa_chipset *__restrict self) {
	struct vbe_biosinfo *result;
	result = (struct vbe_biosinfo *)vesa_chipset_biosaddr(self, VESA_CHIPSET_BIOSADDR_BIOSINFO);
	DBG_memset(result, 0xcc, sizeof(*result));
	bzero(&self->vc_emu.b86e_vm.vr_regs, sizeof(self->vc_emu.b86e_vm.vr_regs));
	memcpy(result->vbi_signature, "VBE2", 4);
	self->vc_emu.b86e_vm.vr_regs.vr_ax = 0x4f00;
	self->vc_emu.b86e_vm.vr_regs.vr_es = VESA_CHIPSET_BIOSADDR_BIOSINFO >> 4;
	self->vc_emu.b86e_vm.vr_regs.vr_di = VESA_CHIPSET_BIOSADDR_BIOSINFO & 0xf;
	if (!vesa_chipset_bios86_int(self, 0x10))
		return NULL;
	if (self->vc_emu.b86e_vm.vr_regs.vr_ax != 0x4f)
		return NULL;
	if (bcmp(result->vbi_signature, "VESA", 4) != 0)
		return NULL;
	return result;
}

/* Load VESA mode information. */
PRIVATE WUNUSED NONNULL((1)) struct vbe_modeinfo *CC
vesa_getmodeinfo(struct vesa_chipset *__restrict self, uint16_t mode) {
	struct vbe_modeinfo *result;
	result = (struct vbe_modeinfo *)vesa_chipset_biosaddr(self, VESA_CHIPSET_BIOSADDR_MODEINFO);
	DBG_memset(result, 0xcc, sizeof(*result));
	bzero(&self->vc_emu.b86e_vm.vr_regs, sizeof(self->vc_emu.b86e_vm.vr_regs));
	self->vc_emu.b86e_vm.vr_regs.vr_ax = 0x4f01;
	self->vc_emu.b86e_vm.vr_regs.vr_cx = mode;
	self->vc_emu.b86e_vm.vr_regs.vr_es = VESA_CHIPSET_BIOSADDR_MODEINFO >> 4;
	self->vc_emu.b86e_vm.vr_regs.vr_di = VESA_CHIPSET_BIOSADDR_MODEINFO & 0xf;
	if (!vesa_chipset_bios86_int(self, 0x10))
		return NULL;
	return result;
}

/* Set current VESA mode. */
PRIVATE WUNUSED NONNULL((1)) bool CC
vesa_setmode(struct vesa_chipset *__restrict self, uint16_t mode) {
	bzero(&self->vc_emu.b86e_vm.vr_regs, sizeof(self->vc_emu.b86e_vm.vr_regs));
	self->vc_emu.b86e_vm.vr_regs.vr_ax = 0x4f02;
	self->vc_emu.b86e_vm.vr_regs.vr_bx = mode;
	if (!vesa_chipset_bios86_int(self, 0x10))
		return false;
	return true;
}


/* Finalize a given VESA chipset driver controller. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC vesa_v_fini)(struct svga_chipset *__restrict self) {
	struct vesa_chipset *me = (struct vesa_chipset *)self;
#ifdef __KERNEL__
	bios86_emulator_fini(&me->vc_emu);
#else /* __KERNEL__ */
	(*me->_vc_bios86_fini)(&me->vc_emu);
	dlclose(me->_vc_bios86);
#endif /* !__KERNEL__ */
}


/* Get the *p_index'th vesa mode. */
PRIVATE WUNUSED NONNULL((1)) bool CC
vesa_v_getmode(struct svga_chipset *__restrict self,
               struct svga_modeinfo *__restrict result_,
               uintptr_t *__restrict p_index)
		THROWS(E_IOERROR) {
	struct vesa_modeinfo *result = (struct vesa_modeinfo *)result_;
	struct vesa_chipset *me      = (struct vesa_chipset *)self;
	struct vbe_modeinfo *info;
	uint16_t modeid;
	DBG_memset(result, 0xcc, sizeof(*result));
next:
	modeid = me->vc_modelist[*p_index];
	if (modeid == (uint16_t)-1)
		return false; /* End-of-modelist. */
	++*p_index;

	/* Load mode info. */
	info = vesa_getmodeinfo(me, modeid);
	if unlikely(!info)
		goto next; /* Shouldn't happen... */
	if (!(info->vmi_attrib & VBE_MODEINFO_ATTR_SUPPORTED))
		goto next;

	/* Check what kind of memory mode this is (and if we support it) */
	switch (info->vmi_memmodel) {

	case VBE_MEMMODEL_TEXT:
		/* Text mode implies a certain configuration.
		 * Verify  that all of  our criteria are met. */
		result->smi_flags    = (SVGA_MODEINFO_F_TXT | SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_LFB);
		result->smi_resx     = info->vmi_resx;
		result->smi_resy     = info->vmi_resy;
		result->smi_scanline = info->vmi_scanline;
		if (result->smi_scanline == 0)
			result->smi_scanline = result->smi_resx * 2;
		if (result->smi_scanline < result->smi_resx * 2)
			goto next; /* This would mean overlap... */
		result->smi_bits_per_pixel = 16;
		if (info->vmi_attrib & VBE_MODEINFO_ATTR_LFB) {
			result->smi_lfb = info->vmi_lfbaddr;
		} else {
			size_t textmem_size;
			/* We don't support banking in text-mode. As such, the
			 * entire  text-page  must fit  into a  single window. */
			textmem_size = result->smi_scanline * result->smi_resy;
			if unlikely(textmem_size > 0x10000)
				goto next; /* Too large :( */
			if ((info->vmi_wina_attr & (VBE_WINATTR_MAYREAD | VBE_WINATTR_MAYWRITE)) ==
			    /*                  */ (VBE_WINATTR_MAYREAD | VBE_WINATTR_MAYWRITE)) {
				result->smi_lfb = info->vmi_wina_segment << 4;
			} else if ((info->vmi_winb_attr & (VBE_WINATTR_MAYREAD | VBE_WINATTR_MAYWRITE)) ==
			           /*                  */ (VBE_WINATTR_MAYREAD | VBE_WINATTR_MAYWRITE)) {
				result->smi_lfb = info->vmi_winb_segment << 4;
			} else {
				/* Unsupported memory mode. */
				goto next;
			}
		}
		goto got_result;

	case VBE_MEMMODEL_NC4_256:
		/* This is a palette-driven mode. */
		result->smi_flags = SVGA_MODEINFO_F_PAL;
		break;

	case VBE_MEMMODEL_PACKED:
	case VBE_MEMMODEL_DCOLOR:
		/* I don't really know the difference between PACKED and
		 * DIRECT-COLOR, as they appear  to just be the  same... */
		result->smi_flags = 0;
		break;

	default:
		goto next;
	}

	/* Fill in `*result' */
	result->smi_resx           = info->vmi_resx;
	result->smi_resy           = info->vmi_resy;
	result->smi_bits_per_pixel = info->vmi_bpp;
	result->smi_colorbits      = info->vmi_bpp;
	if (info->vmi_attrib & VBE_MODEINFO_ATTR_LFB) {
		result->smi_lfb = info->vmi_lfbaddr;
		result->smi_flags |= SVGA_MODEINFO_F_LFB;
		if (me->vc_info->vbi_version >= 0x0300) {
			result->smi_rshift   = info->vmi_linrshift;
			result->smi_rbits    = info->vmi_linrbits;
			result->smi_gshift   = info->vmi_lingshift;
			result->smi_gbits    = info->vmi_lingbits;
			result->smi_bshift   = info->vmi_linbshift;
			result->smi_bbits    = info->vmi_linbbits;
			result->smi_scanline = info->vmi_lfbscanline;
			if (result->smi_rshift == 0)
				result->smi_rshift = info->vmi_rshift;
			if (result->smi_rbits == 0)
				result->smi_rbits = info->vmi_rbits;
			if (result->smi_gshift == 0)
				result->smi_gshift = info->vmi_gshift;
			if (result->smi_gbits == 0)
				result->smi_gbits = info->vmi_gbits;
			if (result->smi_bshift == 0)
				result->smi_bshift = info->vmi_bshift;
			if (result->smi_bbits == 0)
				result->smi_bbits = info->vmi_bbits;
			if (result->smi_scanline == 0)
				result->smi_scanline = info->vmi_scanline;
		} else {
			result->smi_rshift   = info->vmi_rshift;
			result->smi_rbits    = info->vmi_rbits;
			result->smi_gshift   = info->vmi_gshift;
			result->smi_gbits    = info->vmi_gbits;
			result->smi_bshift   = info->vmi_bshift;
			result->smi_bbits    = info->vmi_bbits;
			result->smi_scanline = info->vmi_scanline;
		}
		result->smi_colorbits = result->smi_rbits +
		                        result->smi_gbits +
		                        result->smi_bbits;
	} else {
		/* Validate window size and granularity parameters.
		 *
		 * NOTE: We require that video memory windows are 64K
		 *       large  because svgalib does the same (and it
		 *       worked well enough) */
		if (me->sc_vmemsize > 64 * 1024) {
			if (info->vmi_win_size != 0 && info->vmi_win_size != 64)
				goto next;
			if (info->vmi_win_granularity == 0)
				info->vmi_win_granularity = 64; /* Guess */
			if (info->vmi_win_granularity > 64)
				goto next; /* Wouldn't make sense. */
		} else {
			/* Video memory is small enough to fit into the standard VGA window. */
		}
		if (!IS_POWER_OF_TWO(info->vmi_win_granularity))
			goto next; /* Needs to be the case to match the expected 64K window size! */
		result->smi_scanline = info->vmi_scanline;
	}
	if (result->smi_scanline == 0)
		result->smi_scanline = CEILDIV(result->smi_resx * result->smi_bits_per_pixel, 8);
	if (!(info->vmi_attrib & VBE_MODEINFO_ATTR_COLOR))
		result->smi_flags |= SVGA_MODEINFO_F_BW;
	if unlikely(result->smi_colorbits == 0)
		goto next;

got_result:
	memcpy(&result->vm_vesa, info, sizeof(struct vbe_modeinfo));
	result->vm_modeid = modeid;

	/* Do some safetey checks; shouldn't happen (but prevents any chance of DIVIDE_BY_ZERO) */
	if unlikely(result->smi_resx == 0)
		goto next;
	if unlikely(result->smi_resy == 0)
		goto next;
	if unlikely(result->smi_bits_per_pixel == 0)
		goto next;
	if unlikely(result->smi_scanline == 0)
		goto next;

	return true;
}

LOCAL NONNULL((1)) void CC
vesa_setwindow(struct svga_chipset *__restrict self, uint8_t no, size_t window) {
	struct vesa_chipset *me = (struct vesa_chipset *)self;
	bzero(&me->vc_emu.b86e_vm.vr_regs, sizeof(me->vc_emu.b86e_vm.vr_regs));
	me->vc_emu.b86e_vm.vr_regs.vr_ax = 0x4f05;
	me->vc_emu.b86e_vm.vr_regs.vr_bx = 0x0000 | no; /* SET_WINDOW */
	me->vc_emu.b86e_vm.vr_regs.vr_dx = (window * 64) >> me->vc_wingranshift;
	if (!vesa_chipset_bios86_int(me, 0x10))
		THROW(E_IOERROR);
}

LOCAL NONNULL((1)) size_t CC
vesa_getwindow(struct svga_chipset *__restrict self, uint8_t no) {
	struct vesa_chipset *me = (struct vesa_chipset *)self;
	bzero(&me->vc_emu.b86e_vm.vr_regs, sizeof(me->vc_emu.b86e_vm.vr_regs));
	me->vc_emu.b86e_vm.vr_regs.vr_ax = 0x4f05;
	me->vc_emu.b86e_vm.vr_regs.vr_bx = 0x0100 | no; /* GET_WINDOW */
	if (!vesa_chipset_bios86_int(me, 0x10))
		THROW(E_IOERROR);
	return ((u32)me->vc_emu.b86e_vm.vr_regs.vr_dx << me->vc_wingranshift) / 64;
}


PRIVATE NONNULL((1)) void CC
vesa_v_setwindow_both_0(struct svga_chipset *__restrict self, size_t window) {
	vesa_setwindow(self, 0, window); /* Only need to set `0' */
	self->sc_rdwindow = window;
	self->sc_wrwindow = window;
}

PRIVATE NONNULL((1)) void CC
vesa_v_setwindow_both_1(struct svga_chipset *__restrict self, size_t window) {
	vesa_setwindow(self, 1, window); /* Only need to set `1' */
	self->sc_rdwindow = window;
	self->sc_wrwindow = window;
}

PRIVATE NONNULL((1)) void CC
vesa_v_setwindow_both_01(struct svga_chipset *__restrict self, size_t window) {
	vesa_setwindow(self, 0, window);
	vesa_setwindow(self, 1, window);
	self->sc_rdwindow = window;
	self->sc_wrwindow = window;
}

PRIVATE NONNULL((1)) void CC
vesa_v_setwindow_rd_0(struct svga_chipset *__restrict self, size_t window) {
	vesa_setwindow(self, 0, window);
	self->sc_rdwindow = window;
}

PRIVATE NONNULL((1)) void CC
vesa_v_setwindow_rd_1(struct svga_chipset *__restrict self, size_t window) {
	vesa_setwindow(self, 1, window);
	self->sc_rdwindow = window;
}

PRIVATE NONNULL((1)) void CC
vesa_v_setwindow_wr_0(struct svga_chipset *__restrict self, size_t window) {
	vesa_setwindow(self, 0, window);
	self->sc_wrwindow = window;
}

PRIVATE NONNULL((1)) void CC
vesa_v_setwindow_wr_1(struct svga_chipset *__restrict self, size_t window) {
	vesa_setwindow(self, 1, window);
	self->sc_wrwindow = window;
}

PRIVATE NONNULL((1)) void CC
vesa_v_setdisplaystart(struct svga_chipset *__restrict self, size_t offset) {
	struct vesa_chipset *me = (struct vesa_chipset *)self;
	bzero(&me->vc_emu.b86e_vm.vr_regs, sizeof(me->vc_emu.b86e_vm.vr_regs));
	me->vc_emu.b86e_vm.vr_regs.vr_ax = 0x4f07;
	me->vc_emu.b86e_vm.vr_regs.vr_bl = 0x00; /* SET_DISPLAY_START */
	me->vc_emu.b86e_vm.vr_regs.vr_cx = offset % me->sc_logicalwidth;
	me->vc_emu.b86e_vm.vr_regs.vr_dx = offset / me->sc_logicalwidth;
	if (!vesa_chipset_bios86_int(me, 0x10))
		THROW(E_IOERROR);
	me->sc_displaystart = offset;
}

PRIVATE WUNUSED NONNULL((1)) size_t CC
vesa_getdisplaystart(struct svga_chipset *__restrict self) {
	struct vesa_chipset *me = (struct vesa_chipset *)self;
	bzero(&me->vc_emu.b86e_vm.vr_regs, sizeof(me->vc_emu.b86e_vm.vr_regs));
	me->vc_emu.b86e_vm.vr_regs.vr_ax = 0x4f07;
	me->vc_emu.b86e_vm.vr_regs.vr_bl = 0x01; /* GET_DISPLAY_START */
	if (!vesa_chipset_bios86_int(me, 0x10))
		THROW(E_IOERROR);
	if unlikely(me->vc_emu.b86e_vm.vr_regs.vr_cx >= me->sc_logicalwidth)
		THROW(E_IOERROR);
	return (me->vc_emu.b86e_vm.vr_regs.vr_dx * me->sc_logicalwidth) +
	       me->vc_emu.b86e_vm.vr_regs.vr_cx;
}

PRIVATE NONNULL((1)) void CC
vesa_v_setlogicalwidth(struct svga_chipset *__restrict self, uint32_t width) {
	struct vesa_chipset *me = (struct vesa_chipset *)self;
	bzero(&me->vc_emu.b86e_vm.vr_regs, sizeof(me->vc_emu.b86e_vm.vr_regs));
	me->vc_emu.b86e_vm.vr_regs.vr_ax = 0x4f06;
	me->vc_emu.b86e_vm.vr_regs.vr_bl = 0x00; /* SET_SCAN_LINE_LENGTH_IN_PIXELS */
	me->vc_emu.b86e_vm.vr_regs.vr_dx = (uint16_t)width;
	if (!vesa_chipset_bios86_int(me, 0x10))
		THROW(E_IOERROR);
	me->sc_logicalwidth = width;
}

PRIVATE WUNUSED NONNULL((1)) uint16_t CC
vesa_getlogicalwidth_max(struct svga_chipset *__restrict self) {
	struct vesa_chipset *me = (struct vesa_chipset *)self;
	bzero(&me->vc_emu.b86e_vm.vr_regs, sizeof(me->vc_emu.b86e_vm.vr_regs));
	me->vc_emu.b86e_vm.vr_regs.vr_ax = 0x4f06;
	me->vc_emu.b86e_vm.vr_regs.vr_bl = 0x03; /* GET_MAXIMUM_SCAN_LINE_LENGTH */
	if (!vesa_chipset_bios86_int(me, 0x10))
		THROW(E_IOERROR);
	return me->vc_emu.b86e_vm.vr_regs.vr_bx;
}


PRIVATE NONNULL((1, 2)) void CC
vesa_v_setmode(struct svga_chipset *__restrict self,
               struct svga_modeinfo const *__restrict mode_) {
	uint16_t modeword;
	struct vesa_modeinfo *mode = (struct vesa_modeinfo *)mode_;
	struct vesa_chipset *me    = (struct vesa_chipset *)self;

	modeword = mode->vm_modeid;
	modeword |= 0x8000; /* Don't clear display memory */
	if (mode->smi_flags & SVGA_MODEINFO_F_LFB)
		modeword |= 0x4000; /* Use linear buffer. */
	if (!vesa_setmode(me, modeword))
		THROW(E_IOERROR);
	DBG_memset(&me->sc_ops.sco_setwindow, 0xcc, sizeof(me->sc_ops.sco_setwindow));
	DBG_memset(&me->sc_ops.sco_setrdwindow, 0xcc, sizeof(me->sc_ops.sco_setrdwindow));
	DBG_memset(&me->sc_ops.sco_setwrwindow, 0xcc, sizeof(me->sc_ops.sco_setwrwindow));
	DBG_memset(&me->sc_rdwindow, 0xcc, sizeof(me->sc_rdwindow));
	DBG_memset(&me->sc_wrwindow, 0xcc, sizeof(me->sc_wrwindow));

	/* Remember current mode. */
	memcpy(&me->vc_mode, &mode->vm_vesa, sizeof(struct vbe_modeinfo));
	me->sc_displaystart       = vesa_getdisplaystart(me);
	me->sc_logicalwidth_max   = vesa_getlogicalwidth_max(me);
	me->sc_logicalwidth_align = 1;
	if (mode->smi_bits_per_pixel <= 1) {
		me->sc_logicalwidth_align = 8;
	} else if (mode->smi_bits_per_pixel <= 2) {
		me->sc_logicalwidth_align = 4;
	} if (mode->smi_bits_per_pixel <= 4) {
		me->sc_logicalwidth_align = 2;
	}

	/* Technically, we should read from BIOS, but if this were to
	 * differ from the mode's scanline right after we've just set
	 * the new mode, something would be wrong. */
	me->sc_logicalwidth = mode->smi_scanline;
	if unlikely(me->sc_logicalwidth_max < me->sc_logicalwidth) {
		/* This shouldn't happen, but we don't want something
		 * like this  causing  unexpected  problems  later... */
		me->sc_logicalwidth_max = me->sc_logicalwidth;
	}

	/* Set operators. */
	me->sc_ops.sco_setdisplaystart = &vesa_v_setdisplaystart;
	me->sc_ops.sco_setlogicalwidth = &vesa_v_setlogicalwidth;

	/* Load extended attributes only needed when there is no LFB */
	if (!(mode->smi_flags & SVGA_MODEINFO_F_LFB)) {
		uint8_t rdwindow, wrwindow;

		/* The granularity is important for loading video memory windows.
		 * >> The window number expected by the BIOS is `INDEX_AS_NTH_64K_PAGE * 64 / GRANULARITY' */
		me->vc_wingranshift = CTZ(me->vc_mode.vmi_win_granularity);

		/* Figure out the window numbers for the read/write windows. */
		rdwindow = wrwindow = 0;
		if ((mode->vm_vesa.vmi_wina_attr & (VBE_WINATTR_MAYREAD | VBE_WINATTR_MAYWRITE)) !=
		    /*                          */ (VBE_WINATTR_MAYREAD | VBE_WINATTR_MAYWRITE)) {
			/* Also need to make use of the secondary window. */
			if (mode->vm_vesa.vmi_winb_attr & VBE_WINATTR_MAYREAD)
				rdwindow = 1;
			if (mode->vm_vesa.vmi_winb_attr & VBE_WINATTR_MAYWRITE)
				wrwindow = 1;
		}

		/* Select most efficient set-window-index operators. */
		if (rdwindow == 0 && wrwindow == 0) {
			me->sc_ops.sco_setwindow   = &vesa_v_setwindow_both_0;
			me->sc_ops.sco_setrdwindow = &vesa_v_setwindow_both_0;
			me->sc_ops.sco_setwrwindow = &vesa_v_setwindow_both_0;
		} else if (rdwindow == 1 && wrwindow == 1) {
			me->sc_ops.sco_setwindow   = &vesa_v_setwindow_both_1;
			me->sc_ops.sco_setrdwindow = &vesa_v_setwindow_both_1;
			me->sc_ops.sco_setwrwindow = &vesa_v_setwindow_both_1;
		} else if (rdwindow == 0 /*&& wrwindow == 1*/) {
			me->sc_ops.sco_setwindow   = &vesa_v_setwindow_both_01;
			me->sc_ops.sco_setrdwindow = &vesa_v_setwindow_rd_0;
			me->sc_ops.sco_setwrwindow = &vesa_v_setwindow_wr_1;
		} else /*if (rdwindow == 1 && wrwindow == 0)*/ {
			me->sc_ops.sco_setwindow   = &vesa_v_setwindow_both_01;
			me->sc_ops.sco_setrdwindow = &vesa_v_setwindow_rd_1;
			me->sc_ops.sco_setwrwindow = &vesa_v_setwindow_wr_0;
		}

		/* Load currently selected window numbers. */
		me->sc_rdwindow = vesa_getwindow(self, rdwindow);
		me->sc_wrwindow = me->sc_rdwindow;
		if (wrwindow != rdwindow)
			me->sc_wrwindow = vesa_getwindow(self, wrwindow);
	}
}



PRIVATE WUNUSED NONNULL((1)) size_t CC
vesa_getregsbufsize(struct svga_chipset *__restrict self) {
	struct vesa_chipset *me = (struct vesa_chipset *)self;
	bzero(&me->vc_emu.b86e_vm.vr_regs, sizeof(me->vc_emu.b86e_vm.vr_regs));
	me->vc_emu.b86e_vm.vr_regs.vr_ax = 0x4f04;
	me->vc_emu.b86e_vm.vr_regs.vr_cx = me->vc_regsavebits;
	me->vc_emu.b86e_vm.vr_regs.vr_dl = 0x00; /* SAVE_RESTORE_STATE_BUFFER_SIZE */
	if (!vesa_chipset_bios86_int(me, 0x10))
		THROW(E_IOERROR);
	return (size_t)me->vc_emu.b86e_vm.vr_regs.vr_bx * 64;
}

PRIVATE NONNULL((1)) void CC
vesa_v_getregs(struct svga_chipset *__restrict self, byte_t regbuf[]) {
	struct vesa_chipset *me = (struct vesa_chipset *)self;
	bzero(&me->vc_emu.b86e_vm.vr_regs, sizeof(me->vc_emu.b86e_vm.vr_regs));
	me->vc_emu.b86e_vm.vr_regs.vr_ax = 0x4f04;
	me->vc_emu.b86e_vm.vr_regs.vr_cx = me->vc_regsavebits;
	me->vc_emu.b86e_vm.vr_regs.vr_dl = 0x01; /* SAVE_STATE */
	me->vc_emu.b86e_vm.vr_regs.vr_es = VESA_CHIPSET_BIOSADDR_REGBUF >> 4;
	me->vc_emu.b86e_vm.vr_regs.vr_bx = VESA_CHIPSET_BIOSADDR_REGBUF & 0xf;
	if (!vesa_chipset_bios86_int(me, 0x10))
		THROW(E_IOERROR);
	memcpy(regbuf, vesa_chipset_biosaddr(me, VESA_CHIPSET_BIOSADDR_REGBUF),
	       me->sc_ops.sco_regsize);
}

PRIVATE NONNULL((1)) void CC
vesa_v_setregs(struct svga_chipset *__restrict self, byte_t const regbuf[]) {
	struct vesa_chipset *me = (struct vesa_chipset *)self;
	memcpy(vesa_chipset_biosaddr(me, VESA_CHIPSET_BIOSADDR_REGBUF), regbuf,
	       me->sc_ops.sco_regsize);
	bzero(&me->vc_emu.b86e_vm.vr_regs, sizeof(me->vc_emu.b86e_vm.vr_regs));
	me->vc_emu.b86e_vm.vr_regs.vr_ax = 0x4f04;
	me->vc_emu.b86e_vm.vr_regs.vr_cx = me->vc_regsavebits;
	me->vc_emu.b86e_vm.vr_regs.vr_dl = 0x02; /* RESTORE_STATE */
	me->vc_emu.b86e_vm.vr_regs.vr_es = VESA_CHIPSET_BIOSADDR_REGBUF >> 4;
	me->vc_emu.b86e_vm.vr_regs.vr_bx = VESA_CHIPSET_BIOSADDR_REGBUF & 0xf;
	if (!vesa_chipset_bios86_int(me, 0x10))
		THROW(E_IOERROR);
}



PRIVATE NONNULL((1, 2)) ssize_t CC
vesa_v_strings(struct svga_chipset *__restrict self,
               svga_chipset_enumstring_t cb, void *arg) {
	ssize_t temp, result;
	struct vesa_chipset *me;
	me = (struct vesa_chipset *)self;

	/* Print the version number. */
	{
		char verbuf[lengthof(PRIMAXu8 "." PRIMAXu8)];
		sprintf(verbuf, "%" PRIu8 ".%" PRIu8,
		        (me->vc_info->vbi_version & 0xff00) >> 8,
		        (me->vc_info->vbi_version & 0xff));
		result = (*cb)(arg, "version", verbuf);
		if unlikely(result < 0)
			goto done;
	}

	/* Print fixed strings. */
	temp = (*cb)(arg, "oem_string", vesa_chipset_get_oem_string(me));
	if unlikely(temp < 0)
		goto err;
	result += temp;
	temp = (*cb)(arg, "oem_vendor_name", vesa_chipset_get_oem_vendor_name(me));
	if unlikely(temp < 0)
		goto err;
	result += temp;
	temp = (*cb)(arg, "oem_product_name", vesa_chipset_get_oem_product_name(me));
	if unlikely(temp < 0)
		goto err;
	result += temp;
	temp = (*cb)(arg, "oem_product_rev", vesa_chipset_get_oem_product_rev(me));
	if unlikely(temp < 0)
		goto err;
	result += temp;

done:
	return result;
err:
	return temp;
}




/* Probe for VESA support.
 * @return: true:  Chipset found.
 * @return: false: Chipset isn't present. */
INTERN WUNUSED NONNULL((1)) bool CC
cs_vesa_probe(struct svga_chipset *__restrict self) {
	struct vesa_chipset *me = (struct vesa_chipset *)self;
#ifdef __KERNEL__
	bios86_emulator_init(&me->vc_emu);
#else /* __KERNEL__ */
	PBIOS86_EMULATOR_INIT emuinit;

	/* Load libbios86 */
	me->_vc_bios86 = dlopen(LIBBIOS86_LIBRARY_NAME, RTLD_LOCAL);
	if unlikely(!me->_vc_bios86)
		return false;

	/* Bind functions and initialize an x86 BIOS emulator. */
	if ((*(void **)&me->_vc_bios86_int = dlsym(me->_vc_bios86, "bios86_emulator_int")) == NULL ||
	    (*(void **)&me->_vc_bios86_fini = dlsym(me->_vc_bios86, "bios86_emulator_fini")) == NULL ||
	    (*(void **)&emuinit = dlsym(me->_vc_bios86, "bios86_emulator_init")) == NULL ||
	    (*emuinit)(&me->vc_emu) != 0) {
		dlclose(me->_vc_bios86);
		return false;
	}
#endif /* !__KERNEL__ */
	TRY {
		struct vbe_biosinfo *bi;

		/* Probe for BIOS support. */
		bi = vesa_getbiosinfo(me);
		if (!bi)
			goto err_emu;

		/* Remember BIOS info */
		me->vc_info     = bi;
		me->vc_modelist = (uint16_t const *)vesa_farptr(me, bi->vbi_vidmodelist_seg, bi->vbi_vidmodelist_off);

		/* Initialize current-mode-related fields to indicate that no mode is selected. */
		DBG_memset(&me->sc_rdwindow, 0xcc, sizeof(me->sc_rdwindow));
		DBG_memset(&me->sc_wrwindow, 0xcc, sizeof(me->sc_wrwindow));
		DBG_memset(&me->sc_displaystart, 0xcc, sizeof(me->sc_displaystart));
		DBG_memset(&me->sc_logicalwidth, 0xcc, sizeof(me->sc_logicalwidth));
		DBG_memset(&me->vc_mode, 0xcc, sizeof(me->vc_mode));
		me->sc_vmemsize           = bi->vbi_vmemsize * 64 * 1024;

		/* Initialize operators. */
		DBG_memset(&me->sc_ops, 0xcc, sizeof(me->sc_ops));
		me->sc_ops.sco_fini         = &vesa_v_fini;
		me->sc_ops.sco_strings      = &vesa_v_strings;
		me->sc_ops.sco_modeinfosize = sizeof(struct vesa_modeinfo);
		me->sc_ops.sco_getmode      = &vesa_v_getmode;
		me->sc_ops.sco_setmode      = &vesa_v_setmode;
		me->vc_regsavebits          = 0x000e; /* Everything except VGA controller hardware state */
		/* XXX: At this point, we could override `me->vc_regsavebits'! */

		/* Fill in register get/set operators. */
		me->sc_ops.sco_regsize = vesa_getregsbufsize(me);
		me->sc_ops.sco_getregs = &vesa_v_getregs;
		me->sc_ops.sco_setregs = &vesa_v_setregs;
	} EXCEPT {
		vesa_v_fini(me);
		RETHROW();
	}
	return true;
err_emu:
	vesa_v_fini(me);
	return false;
}

DECL_END
#endif /* CONFIG_HAVE_LIBSVGADRV_CHIPSET_VESA */

#endif /* !GUARD_LIBSVGADRV_CS_VESA_C */
