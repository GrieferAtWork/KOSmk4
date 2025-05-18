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
#ifndef GUARD_LIBSVGADRV_CS_BOCHSVBE_C
#define GUARD_LIBSVGADRV_CS_BOCHSVBE_C 1
#define _KOS_SOURCE 1
#define _KOS_ALTERATIONS_SOURCE 1

#include "api.h"
/**/

#ifdef CONFIG_HAVE_LIBSVGADRV_CHIPSET_BOCHSVBE
#include <hybrid/align.h>
#include <hybrid/minmax.h>
#include <hybrid/sequence/list.h>
#include <hybrid/unaligned.h>

#include <hw/video/bochsvbe.h>
#include <kos/except.h>
#include <kos/kernel/printk.h>
#include <kos/types.h>
#include <sys/io.h>

#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <libpciaccess/pciaccess.h>
#include <libsvgadrv/chipset.h>
#include <libsvgadrv/chipsets/bochsvbe.h>
#include <libsvgadrv/util/vgaio.h>

#include "basevga.h"
#include "cs-bochsvbe.h"
#include "cs-vga.h"

#ifndef __KERNEL__
#include <dlfcn.h>
#endif /* !__KERNEL__ */

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC bochs_v_fini)(struct svga_chipset *__restrict self) {
	struct bochs_chipset *me = (struct bochs_chipset *)self;
	(void)me;
#ifndef __KERNEL__
	if (me->bc_libpciaccess)
		dlclose(me->bc_libpciaccess);
#endif /* !__KERNEL__ */
}


struct bga_mode {
	uint16_t bm_resx;
	uint16_t bm_resy;
	uint16_t bm_bpp;
};

PRIVATE struct bga_mode const bochs_modes[] = {
	/* Supported video modes (resolutions are stolen from what VESA reports under QEMU) */
#define DEFINE_ANYBPP_FOR_RES(resx, resy)                               \
	{ resx, resy, VBE_DISPI_BPP_PAL16 },    /* 16-color mode */         \
	{ resx, resy, VBE_DISPI_BPP_PAL256 },   /* 256-color mode */        \
	{ resx, resy, VBE_DISPI_BPP_BGR555 },   /* 5-5-5 true-color mode */ \
	{ resx, resy, VBE_DISPI_BPP_BGR565 },   /* 5-6-5 true-color mode */ \
	{ resx, resy, VBE_DISPI_BPP_BGR888 },   /* 8-8-8 true-color mode */ \
	{ resx, resy, VBE_DISPI_BPP_BGRX8888 }, /* 8-8-8-X true-color mode */
	DEFINE_ANYBPP_FOR_RES(320, 200)
	DEFINE_ANYBPP_FOR_RES(640, 400)
	DEFINE_ANYBPP_FOR_RES(800, 600)
	DEFINE_ANYBPP_FOR_RES(1024, 768)
	DEFINE_ANYBPP_FOR_RES(1152, 864)
	DEFINE_ANYBPP_FOR_RES(1280, 1024)
	DEFINE_ANYBPP_FOR_RES(1280, 720)
	DEFINE_ANYBPP_FOR_RES(1280, 768)
	DEFINE_ANYBPP_FOR_RES(1280, 800)
	DEFINE_ANYBPP_FOR_RES(1280, 960)
	DEFINE_ANYBPP_FOR_RES(1400, 1050)
	DEFINE_ANYBPP_FOR_RES(1440, 900)
	DEFINE_ANYBPP_FOR_RES(1600, 1200)
	DEFINE_ANYBPP_FOR_RES(1600, 900)
	DEFINE_ANYBPP_FOR_RES(1680, 1050)
	DEFINE_ANYBPP_FOR_RES(1920, 1080)
	DEFINE_ANYBPP_FOR_RES(1920, 1200)
	DEFINE_ANYBPP_FOR_RES(2560, 1440)
	DEFINE_ANYBPP_FOR_RES(2560, 1600)
#undef DEFINE_ANYBPP_FOR_RES
};



PRIVATE WUNUSED NONNULL((1, 2, 3)) bool CC
bochs_v_getmode(struct svga_chipset *__restrict self,
                struct svga_modeinfo *__restrict _result,
                uintptr_t *__restrict p_index)
		THROWS(E_IOERROR) {
	struct bochs_chipset *me      = (struct bochs_chipset *)self;
	struct bochs_modeinfo *result = (struct bochs_modeinfo *)_result;
	struct bga_mode const *bm;
	size_t reqvmem;
next:
	if (*p_index >= lengthof(bochs_modes)) {
		/* Enumerate standard VGA modes. */
		bool ok;
		result->bmi_modeid = (uint8_t)-1;
		*p_index -= lengthof(bochs_modes);
		ok = vga_v_getmode(self, result, p_index);
		*p_index += lengthof(bochs_modes);
		return ok;
	}
	result->bmi_modeid = *p_index;
	bm = &bochs_modes[*p_index];
	++*p_index;

	/* Check if this mode is supported. */
	if (bm->bm_resx > me->bc_maxresx)
		goto next;
	if (bm->bm_resy > me->bc_maxresy)
		goto next;
	if (bm->bm_bpp > me->bc_maxbpp)
		goto next;

	/* Supported mode! */
	result->smi_lfb            = me->bc_lfbaddr;
	result->smi_flags          = SVGA_MODEINFO_F_LFB;
	result->smi_resx           = bm->bm_resx;
	result->smi_resy           = bm->bm_resy;
	result->smi_colorbits      = bm->bm_bpp;
	result->smi_bits_per_pixel = bm->bm_bpp;
	switch (bm->bm_bpp) {

	case VBE_DISPI_BPP_PAL16:
		result->smi_flags |= SVGA_MODEINFO_F_PAL;
		result->smi_scanline = bm->bm_resx / 2;
		break;

	case VBE_DISPI_BPP_PAL256:
		result->smi_flags |= SVGA_MODEINFO_F_PAL;
		result->smi_scanline = bm->bm_resx;
		break;

	case VBE_DISPI_BPP_BGR555:
		result->smi_bits_per_pixel = 16;
		ATTR_FALLTHROUGH
	case VBE_DISPI_BPP_BGR565:
		result->smi_scanline = bm->bm_resx * 2;
		result->smi_bshift   = 0;
		result->smi_gshift   = 5;
		result->smi_rshift   = 10;
		result->smi_bbits    = 5;
		result->smi_rbits    = 5;
		result->smi_gbits    = 5;
		if (bm->bm_bpp == VBE_DISPI_BPP_BGR565) {
			result->smi_rshift = 11;
			result->smi_gbits  = 6;
		}
		break;

	case VBE_DISPI_BPP_BGR888:
		result->smi_scanline = bm->bm_resx * 3;
		__IF0 {
	case VBE_DISPI_BPP_BGRX8888:
			result->smi_scanline = bm->bm_resx * 4;
		}
		result->smi_bshift = 0;
		result->smi_gshift = 8;
		result->smi_rshift = 16;
		result->smi_bbits  = 8;
		result->smi_rbits  = 8;
		result->smi_gbits  = 8;
		break;

	default: __builtin_unreachable();
	}
	reqvmem = (size_t)bm->bm_resy *
	          (size_t)CEILDIV(bm->bm_resx * result->smi_bits_per_pixel, 8);
	if (reqvmem > me->sc_vmemsize)
		goto next;

	return true;
}

PRIVATE NONNULL((1, 2)) void CC
bochs_v_setmode(struct svga_chipset *__restrict self,
                struct svga_modeinfo const *__restrict _mode) {
#ifdef SVGA_HAVE_HW_SCROLL
	struct bochs_chipset *me = (struct bochs_chipset *)self;
#endif /* SVGA_HAVE_HW_SCROLL */
	struct bochs_modeinfo const *mode = (struct bochs_modeinfo const *)_mode;
	struct bga_mode const *bm;

	/* Disable Bochs VBE */
	dispi_wrreg(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);

	/* Support for standard VGA modes. */
	if (mode->bmi_modeid >= lengthof(bochs_modes)) {
		vga_v_setmode(self, mode);
		return;
	}

	/* Load a new video mode. */
	bm = &bochs_modes[mode->bmi_modeid];
	dispi_wrreg(VBE_DISPI_INDEX_BPP, bm->bm_bpp);
	dispi_wrreg(VBE_DISPI_INDEX_XRES, bm->bm_resx);
	dispi_wrreg(VBE_DISPI_INDEX_YRES, bm->bm_resy);
	dispi_wrreg(VBE_DISPI_INDEX_BANK, 0);

	/* Enable video. */
	dispi_wrreg(VBE_DISPI_INDEX_ENABLE,
	            VBE_DISPI_ENABLED |
	            VBE_DISPI_NOCLEARMEM |
	            VBE_DISPI_LFB_ENABLED);

	/* Read additional information. */
#ifdef SVGA_HAVE_HW_SCROLL
	me->sc_logicalwidth = dispi_rdreg(VBE_DISPI_INDEX_VIRT_WIDTH);
	me->sc_displaystart = dispi_rdreg(VBE_DISPI_INDEX_X_OFFSET) +
	                      dispi_rdreg(VBE_DISPI_INDEX_Y_OFFSET) *
	                      me->sc_logicalwidth;
	me->sc_logicalwidth_align = 1;
	if (bm->bm_bpp <= 1) {
		me->sc_logicalwidth_align = 8;
	} else if (bm->bm_bpp <= 2) {
		me->sc_logicalwidth_align = 4;
	} if (bm->bm_bpp <= 4) {
		me->sc_logicalwidth_align = 2;
	}
#endif /* SVGA_HAVE_HW_SCROLL */
}

PRIVATE NONNULL((1, 2)) void CC
bochs_v_getregs(struct svga_chipset *__restrict UNUSED(self), byte_t regbuf[]) {
	struct bochs_regs *reginfo;
	uint16_t index;
	reginfo = (struct bochs_regs *)regbuf;
	index   = inw(VBE_DISPI_IOPORT_INDEX);
	UNALIGNED_SET16(&reginfo->be_index, index);
	UNALIGNED_SET16(&reginfo->be_saved_id, dispi_rdreg(VBE_DISPI_INDEX_ID));
	UNALIGNED_SET16(&reginfo->be_saved_xres, dispi_rdreg(VBE_DISPI_INDEX_XRES));
	UNALIGNED_SET16(&reginfo->be_saved_yres, dispi_rdreg(VBE_DISPI_INDEX_YRES));
	UNALIGNED_SET16(&reginfo->be_saved_bpp, dispi_rdreg(VBE_DISPI_INDEX_BPP));
	UNALIGNED_SET16(&reginfo->be_saved_enable, dispi_rdreg(VBE_DISPI_INDEX_ENABLE));
	UNALIGNED_SET16(&reginfo->be_saved_bank, dispi_rdreg(VBE_DISPI_INDEX_BANK));
	UNALIGNED_SET16(&reginfo->be_saved_virt_width, dispi_rdreg(VBE_DISPI_INDEX_VIRT_WIDTH));
	UNALIGNED_SET16(&reginfo->be_saved_virt_height, dispi_rdreg(VBE_DISPI_INDEX_VIRT_HEIGHT));
	UNALIGNED_SET16(&reginfo->be_saved_x_offset, dispi_rdreg(VBE_DISPI_INDEX_X_OFFSET));
	UNALIGNED_SET16(&reginfo->be_saved_y_offset, dispi_rdreg(VBE_DISPI_INDEX_Y_OFFSET));
	outw(VBE_DISPI_IOPORT_INDEX, index);
}

PRIVATE NONNULL((1, 2)) void CC
bochs_v_setregs(struct svga_chipset *__restrict UNUSED(self), byte_t const regbuf[]) {
	struct bochs_regs const *reginfo;
	uint16_t enabled;
	reginfo = (struct bochs_regs const *)regbuf;
	enabled = UNALIGNED_GET16(&reginfo->be_saved_enable);
	if (enabled & VBE_DISPI_ENABLED) {
		dispi_wrreg(VBE_DISPI_INDEX_ID, UNALIGNED_GET16(&reginfo->be_saved_id));
		dispi_wrreg(VBE_DISPI_INDEX_XRES, UNALIGNED_GET16(&reginfo->be_saved_xres));
		dispi_wrreg(VBE_DISPI_INDEX_YRES, UNALIGNED_GET16(&reginfo->be_saved_yres));
		dispi_wrreg(VBE_DISPI_INDEX_BPP, UNALIGNED_GET16(&reginfo->be_saved_bpp));
		dispi_wrreg(VBE_DISPI_INDEX_BANK, UNALIGNED_GET16(&reginfo->be_saved_bank));
		dispi_wrreg(VBE_DISPI_INDEX_VIRT_WIDTH, UNALIGNED_GET16(&reginfo->be_saved_virt_width));
		dispi_wrreg(VBE_DISPI_INDEX_VIRT_HEIGHT, UNALIGNED_GET16(&reginfo->be_saved_virt_height));
		dispi_wrreg(VBE_DISPI_INDEX_X_OFFSET, UNALIGNED_GET16(&reginfo->be_saved_x_offset));
		dispi_wrreg(VBE_DISPI_INDEX_Y_OFFSET, UNALIGNED_GET16(&reginfo->be_saved_y_offset));
	}
	dispi_wrreg(VBE_DISPI_INDEX_ENABLE, enabled);
	outw(VBE_DISPI_IOPORT_INDEX, UNALIGNED_GET16(&reginfo->be_index));
}

#ifdef SVGA_HAVE_HW_SCROLL
PRIVATE NONNULL((1)) void CC
bochs_v_setdisplaystart(struct svga_chipset *__restrict self, size_t offset)
		THROWS(E_IOERROR) {
	struct bochs_chipset *me = (struct bochs_chipset *)self;
	uint32_t logicalwidth    = me->sc_logicalwidth;
	dispi_wrreg(VBE_DISPI_INDEX_X_OFFSET, offset % logicalwidth);
	dispi_wrreg(VBE_DISPI_INDEX_Y_OFFSET, offset / logicalwidth);
	me->sc_displaystart = offset;
}

PRIVATE NONNULL((1)) void CC
bochs_v_setlogicalwidth(struct svga_chipset *__restrict self, uint32_t width)
		THROWS(E_IOERROR) {
	struct bochs_chipset *me = (struct bochs_chipset *)self;
	dispi_wrreg(VBE_DISPI_INDEX_VIRT_WIDTH, width);
	me->sc_logicalwidth = width;
}
#endif /* SVGA_HAVE_HW_SCROLL */

PRIVATE NONNULL((1, 2)) ssize_t CC
bochs_v_strings(struct svga_chipset *__restrict self,
                svga_chipset_enumstring_t cb, void *arg) {
	ssize_t temp, result;
	struct bochs_chipset *me;
	char valbuf[MAX_C(lengthof(PRIMAXu16),
	                  lengthof(PRIMAXxN(__SIZEOF_PHYSADDR_T__)),
	                  lengthof(PRIMAXx32),
	                  lengthof("0x" PRIMAXx16 ".0x" PRIMAXx16),
	                  lengthof("0x" PRIMAXx8 ".0x" PRIMAXx8 "."
	                           "0x" PRIMAXx8 ".0x" PRIMAXx8))];
	me = (struct bochs_chipset *)self;

	sprintf(valbuf, "%" PRIu16, me->bc_maxresx);
	result = (*cb)(arg, "maxresx", valbuf);
	if unlikely(result < 0)
		goto done;

	sprintf(valbuf, "%" PRIu16, me->bc_maxresy);
	temp = (*cb)(arg, "maxresy", valbuf);
	if unlikely(temp < 0)
		goto err;
	result += temp;

	sprintf(valbuf, "%" PRIu16, me->bc_maxbpp);
	temp = (*cb)(arg, "maxbpp", valbuf);
	if unlikely(temp < 0)
		goto err;
	result += temp;

	sprintf(valbuf, "%#" PRIxN(__SIZEOF_PHYSADDR_T__), me->bc_lfbaddr);
	temp = (*cb)(arg, "lfbaddr", valbuf);
	if unlikely(temp < 0)
		goto err;
	result += temp;

	if (me->bc_pci != NULL) {
		sprintf(valbuf, "%#" PRIx32, me->bc_pci->pd_addr);
		temp = (*cb)(arg, "pci.addr", valbuf);
		if unlikely(temp < 0)
			goto err;
		result += temp;

		sprintf(valbuf, "%#.4" PRIx16 ".%#.4" PRIx16,
		        me->bc_pci->pd_vendor_id,
		        me->bc_pci->pd_subvendor_id);
		temp = (*cb)(arg, "pci.vendor", valbuf);
		if unlikely(temp < 0)
			goto err;
		result += temp;

		sprintf(valbuf, "%#.4" PRIx16 ".%#.4" PRIx16,
		        me->bc_pci->pd_device_id,
		        me->bc_pci->pd_subdevice_id);
		temp = (*cb)(arg, "pci.device", valbuf);
		if unlikely(temp < 0)
			goto err;
		result += temp;

		sprintf(valbuf, "%#.2" PRIx8 ".%#.2" PRIx8 ".%#.2" PRIx8 ".%#.2" PRIx8,
		        me->bc_pci->pd_class_id, me->bc_pci->pd_subclass_id,
		        me->bc_pci->pd_progif_id, me->bc_pci->pd_revision);
		temp = (*cb)(arg, "pci.class", valbuf);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}

done:
	return result;
err:
	return temp;
}



/* Probe for VESA support.
 * @return: true:  Chipset found.
 * @return: false: Chipset isn't present. */
INTERN WUNUSED NONNULL((1)) bool CC
cs_bochs_probe(struct svga_chipset *__restrict self) {
	struct bochs_chipset *me = (struct bochs_chipset *)self;

	/* Probe for bochsvbe */
	if (inw(VBE_DISPI_IOPORT_INDEX) == 0xffff &&
	    inw(VBE_DISPI_IOPORT_DATA) == 0xffff)
		return false; /* In ports don't seem to be present, don't try to write to them... */
	/* We want version 5 (XXX: What happens if this one's not supported?) */
	dispi_wrreg(VBE_DISPI_INDEX_ID, VBE_DISPI_ID5);
	if (dispi_rdreg(VBE_DISPI_INDEX_ID) != VBE_DISPI_ID5)
		return false;

#ifndef __KERNEL__
	me->bc_libpciaccess = NULL;
	TRY
#endif /* !__KERNEL__ */
	{
		uint16_t saved_enable;
		struct pci_device *pci;
#ifdef __KERNEL__
		pci = SLIST_FIRST(&pci_devices);
#else /* __KERNEL__ */
		/* Load+initialize libpciaccess. */
		pci                 = NULL;
		me->bc_libpciaccess = dlopen(LIBPCIACCESS_LIBRARY_NAME, RTLD_LOCAL);
		if (me->bc_libpciaccess) {
			typeof(pci_system_init) *pdyn_pci_system_init;
			typeof(__pci_devices) *pdyn_pci_devices;
			if ((*(void **)&pdyn_pci_system_init = dlsym(me->bc_libpciaccess, "pci_system_init")) == NULL ||
			    (*(void **)&pdyn_pci_devices = dlsym(me->bc_libpciaccess, "pci_devices")) == NULL ||
			    ((*pdyn_pci_system_init)() != EOK) || (pci = (*pdyn_pci_devices)()) == NULL) {
				dlclose(me->bc_libpciaccess);
				me->bc_libpciaccess = NULL;
			}
		}
#endif /* !__KERNEL__ */

		/* Find the relevant PCI device. */
		for (; pci; pci = SLIST_NEXT(pci, _pd_link)) {
			if (pci->pd_vendor_id == VBE_PCI_VENDOR_ID &&
			    pci->pd_device_id == VBE_PCI_DEVICE_ID)
				break;
		}

		/* If we didn't find our wanted PCI device, close the library again. */
#ifndef __KERNEL__
		if (!pci && me->bc_libpciaccess) {
			dlclose(me->bc_libpciaccess);
			me->bc_libpciaccess = NULL;
		}
#endif /* !__KERNEL__ */

		/* Remember the relevant PCI device. */
		me->bc_pci = pci;

		me->bc_lfbaddr = (physaddr_t)VBE_DISPI_LFB_PHYSICAL_ADDRESS;
		if (pci) {
			if (pci->pd_regions[0].pmr_is_IO)
				goto err_initfailed; /* This shouldn't happen... */
			me->bc_lfbaddr = (physaddr_t)pci->pd_regions[0].pmr_addr;
		}
		me->sc_vmemsize = dispi_rdreg(VBE_DISPI_INDEX_VIDEO_MEMORY_64K);
		me->sc_vmemsize *= 64 * 1024;

		/* Load video limits */
		saved_enable = dispi_rdreg(VBE_DISPI_INDEX_ENABLE);
		dispi_wrreg(VBE_DISPI_INDEX_ENABLE, saved_enable | VBE_DISPI_GETCAPS);
		me->bc_maxresx = dispi_rdreg(VBE_DISPI_INDEX_XRES);
		me->bc_maxresy = dispi_rdreg(VBE_DISPI_INDEX_YRES);
		me->bc_maxbpp  = dispi_rdreg(VBE_DISPI_INDEX_BPP);
		dispi_wrreg(VBE_DISPI_INDEX_ENABLE, saved_enable);

		/* Verify that limits are acceptable. */
		if unlikely(me->bc_maxbpp < 4) {
			printk(KERN_ERR "[bochsvbe] max:bpp(%" PRIu16 ") too small; need at least 4\n",
			       me->bc_maxbpp);
			goto err_initfailed;
		}
		if unlikely(me->bc_maxresx < 320 || me->bc_maxresy < 200) {
			printk(KERN_ERR "[bochsvbe] max:res(%" PRIu16 "x%" PRIu16 ") too small; need at least 320x200\n",
			       me->bc_maxresx, me->bc_maxresy);
			goto err_initfailed;
		}
		printk(KERN_INFO "[bochsvbe] Chipset detected ["
		                 "maxbpp:%" PRIu16 ","
		                 "maxres:%" PRIu16 "x%" PRIu16 ","
		                 "vmemsz:%" PRIuSIZ "MiB]\n",
		       me->bc_maxbpp, me->bc_maxresx, me->bc_maxresy,
		       (size_t)CEILDIV(me->sc_vmemsize, 1024 * 1024));

		/* Fill in operators and the like... */
		me->sc_ops.sco_fini         = &bochs_v_fini;
		me->sc_ops.sco_modeinfosize = sizeof(struct bochs_modeinfo);
		me->sc_ops.sco_strings      = &bochs_v_strings;
		me->sc_ops.sco_getmode      = &bochs_v_getmode;
		me->sc_ops.sco_setmode      = &bochs_v_setmode;
		me->sc_ops.sco_getregs      = &bochs_v_getregs;
		me->sc_ops.sco_setregs      = &bochs_v_setregs;
		me->sc_ops.sco_regsize      = sizeof(struct bochs_regs);
		self->sc_ops.sco_getpal     = &cs_basevga_rdpal;
		self->sc_ops.sco_setpal     = &cs_basevga_wrpal;
#ifdef SVGA_HAVE_HW_SCROLL
		me->sc_ops.sco_setdisplaystart = &bochs_v_setdisplaystart;
		me->sc_ops.sco_setlogicalwidth = &bochs_v_setlogicalwidth;
		me->sc_logicalwidth_max        = me->bc_maxresx;
#endif /* SVGA_HAVE_HW_SCROLL */
		return true;
	}
#ifndef __KERNEL__
	EXCEPT {
		if (me->bc_libpciaccess)
			dlclose(me->bc_libpciaccess);
		RETHROW();
	}
#endif /* !__KERNEL__ */
err_initfailed:
#ifndef __KERNEL__
	if (me->bc_libpciaccess)
		dlclose(me->bc_libpciaccess);
#endif /* !__KERNEL__ */
	return false;
}

DECL_END
#endif /* CONFIG_HAVE_LIBSVGADRV_CHIPSET_BOCHSVBE */

#endif /* !GUARD_LIBSVGADRV_CS_BOCHSVBE_C */
