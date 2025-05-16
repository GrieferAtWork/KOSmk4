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
#ifndef GUARD_LIBSVGADRV_CS_VMWARE_C
#define GUARD_LIBSVGADRV_CS_VMWARE_C 1
#define _KOS_SOURCE 1
#define _KOS_ALTERATIONS_SOURCE 1

#include "api.h"
/**/

#ifdef CONFIG_HAVE_LIBSVGADRV_CHIPSET_VMWARE
#include <hybrid/align.h>
#include <hybrid/bit.h>
#include <hybrid/minmax.h>
#include <hybrid/sequence/list.h>

#include <hw/bus/pci.h>
#include <hw/video/vmware.h>
#include <kos/except.h>
#include <kos/except/reason/io.h>
#include <kos/kernel/printk.h>

#include <errno.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <libpciaccess/pciaccess.h>
#include <libsvgadrv/chipsets/vmware.h>

#include "cs-vga.h"
#include "cs-vmware.h"

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
NOTHROW(CC vmware_v_fini)(struct svga_chipset *__restrict self) {
	struct vmware_chipset *me = (struct vmware_chipset *)self;
	(void)me;
#ifndef __KERNEL__
	if (me->vw_libpciaccess)
		dlclose(me->vw_libpciaccess);
#endif /* !__KERNEL__ */
}


struct vmware_videomode {
	uint16_t vm_resx;
	uint16_t vm_resy;
};

PRIVATE struct vmware_videomode const vmware_videomodes[] = {
	/* Supported video modes (resolutions are stolen from what VESA reports under QEMU) */
	{ 320, 200 },
	{ 640, 400 },
	{ 800, 600 },
	{ 1024, 768 },
	{ 1152, 864 },
	{ 1280, 1024 },
	{ 1280, 720 },
	{ 1280, 768 },
	{ 1280, 800 },
	{ 1280, 960 },
	{ 1400, 1050 },
	{ 1440, 900 },
	{ 1600, 1200 },
	{ 1600, 900 },
	{ 1680, 1050 },
	{ 1920, 1080 },
	{ 1920, 1200 },
	{ 2560, 1440 },
	{ 2560, 1600 },
};



PRIVATE WUNUSED NONNULL((1, 2, 3)) bool CC
vmware_v_getmode(struct svga_chipset *__restrict self,
                 struct svga_modeinfo *__restrict _result,
                 uintptr_t *__restrict p_index)
		THROWS(E_IOERROR) {
	uint32_t old_enable, old_config_done;
	uint32_t old_width, old_height, old_bpp;
	uint32_t rmask, gmask, bmask;
	struct vmware_chipset *me = (struct vmware_chipset *)self;
	struct vmware_modeinfo *result = (struct vmware_modeinfo *)_result;
	struct vmware_videomode const *vm;
next:
	if (*p_index >= lengthof(vmware_videomodes)) {
		/* Enumerate standard VGA modes. */
		bool ok;
		result->vmi_modeid = (uint8_t)-1;
		*p_index -= lengthof(vmware_videomodes);
		ok = vga_v_getmode(self, result, p_index);
		*p_index += lengthof(vmware_videomodes);
		return ok;
	}
	vm = &vmware_videomodes[*p_index];
	++*p_index;

	/* Check if this mode is supported. */
	if (vm->vm_resx > me->vw_maxresx)
		goto next;
	if (vm->vm_resy > me->vw_maxresy)
		goto next;

	result->vmi_modeid         = *p_index;
	result->smi_flags          = SVGA_MODEINFO_F_LFB;
	result->smi_resx           = vm->vm_resx;
	result->smi_resy           = vm->vm_resy;
	result->smi_bits_per_pixel = me->vw_hbpp;
	result->smi_scanline       = CEIL_ALIGN(vm->vm_resx * 4, 64);

	/* Figure out scanline and such... */
	old_enable      = vm_getreg(me, SVGA_REG_ENABLE);
	old_config_done = vm_getreg(me, SVGA_REG_CONFIG_DONE);
	old_width       = vm_getreg(me, SVGA_REG_WIDTH);
	old_height      = vm_getreg(me, SVGA_REG_HEIGHT);
	old_bpp         = vm_getreg(me, SVGA_REG_BPP);
	vm_setreg(me, SVGA_REG_CONFIG_DONE, 0);
	vm_setreg(me, SVGA_REG_ENABLE, SVGA_REG_ENABLE_DISABLE);
	vm_setreg(me, SVGA_REG_WIDTH, vm->vm_resx);
	vm_setreg(me, SVGA_REG_HEIGHT, vm->vm_resy);
	if (me->vw_caps & SVGA_CAP_8BIT_EMULATION)
		vm_setreg(me, SVGA_REG_BPP, me->vw_hbpp);

	result->smi_lfb = me->vw_fbstart + vm_getreg(me, SVGA_REG_FB_OFFSET);
	result->smi_scanline = vm_getreg(me, SVGA_REG_BYTES_PER_LINE);
	result->smi_colorbits = vm_getreg(me, SVGA_REG_DEPTH);
	rmask = vm_getreg(me, SVGA_REG_RED_MASK);
	gmask = vm_getreg(me, SVGA_REG_GREEN_MASK);
	bmask = vm_getreg(me, SVGA_REG_BLUE_MASK);
	result->smi_rshift = rmask ? CTZ(rmask) : 0;
	result->smi_rbits  = POPCOUNT(rmask);
	result->smi_gshift = gmask ? CTZ(gmask) : 0;
	result->smi_gbits  = POPCOUNT(gmask);
	result->smi_bshift = bmask ? CTZ(bmask) : 0;
	result->smi_bbits  = POPCOUNT(bmask);

	/* Restore old registers */
	if (me->vw_caps & SVGA_CAP_8BIT_EMULATION)
		vm_setreg(me, SVGA_REG_BPP, old_bpp);
	vm_setreg(me, SVGA_REG_HEIGHT, old_height);
	vm_setreg(me, SVGA_REG_WIDTH, old_width);
	vm_setreg(me, SVGA_REG_ENABLE, old_enable);
	vm_setreg(me, SVGA_REG_CONFIG_DONE, old_config_done);
	return true;
}

PRIVATE uint32_t const vmware_noop_fifo_config[] = {
	[SVGA_FIFO_MIN]      = 16,
	[SVGA_FIFO_MAX]      = 16 + (10 * 1024),
	[SVGA_FIFO_NEXT_CMD] = 16,
	[SVGA_FIFO_STOP]     = 16,
};

PRIVATE NONNULL((1, 2)) void CC
vmware_v_setmode(struct svga_chipset *__restrict self,
                 struct svga_modeinfo const *__restrict _mode) {
	uint32_t final_scanline;
	uint32_t rmask, gmask, bmask;
	uint32_t want_rmask, want_gmask, want_bmask;
	struct vmware_chipset *me = (struct vmware_chipset *)self;
	struct vmware_modeinfo const *mode = (struct vmware_modeinfo const *)_mode;

	/* Support for standard VGA modes. */
	if (mode->vmi_modeid >= lengthof(vmware_videomodes)) {
		vm_setreg(me, SVGA_REG_ENABLE, SVGA_REG_ENABLE_DISABLE);
		vga_v_setmode(self, mode);
		return;
	}

	/* SetMode */
	vm_setreg(me, SVGA_REG_CONFIG_DONE, 0);
	vm_setreg(me, SVGA_REG_WIDTH, mode->smi_resx);
	vm_setreg(me, SVGA_REG_HEIGHT, mode->smi_resy);
	if (me->vw_caps & SVGA_CAP_8BIT_EMULATION)
		vm_setreg(me, SVGA_REG_BPP, mode->smi_bits_per_pixel);

	/* Read scanline config and verify it. */
	final_scanline = vm_getreg(me, SVGA_REG_BYTES_PER_LINE);
	if unlikely(final_scanline != mode->smi_scanline) {
		printk(KERN_ERR "[vmware] Final scanline=%" PRIu32 " differs from cached scanline=%" PRIu32 "\n",
		       final_scanline, mode->smi_scanline);
	}

	/* Read color mask config and verify it. */
	rmask = vm_getreg(me, SVGA_REG_RED_MASK);
	gmask = vm_getreg(me, SVGA_REG_GREEN_MASK);
	bmask = vm_getreg(me, SVGA_REG_BLUE_MASK);
	want_rmask = (((uint32_t)1 << mode->smi_rbits) - 1) << mode->smi_rshift;
	want_gmask = (((uint32_t)1 << mode->smi_gbits) - 1) << mode->smi_gshift;
	want_bmask = (((uint32_t)1 << mode->smi_bbits) - 1) << mode->smi_bshift;
	if (rmask != want_rmask)
		printk(KERN_ERR "[vmware] Final rmask=%#.8" PRIx32 " differs from cached rmask=%#.8" PRIx32 "\n", rmask, want_rmask);
	if (gmask != want_gmask)
		printk(KERN_ERR "[vmware] Final gmask=%#.8" PRIx32 " differs from cached gmask=%#.8" PRIx32 "\n", gmask, want_gmask);
	if (bmask != want_bmask)
		printk(KERN_ERR "[vmware] Final bmask=%#.8" PRIx32 " differs from cached bmask=%#.8" PRIx32 "\n", bmask, want_bmask);

	/* Enable SVGA */
	vm_setreg(me, SVGA_REG_ENABLE, SVGA_REG_ENABLE_ENABLE);

	/* Initialize the command FIFO */
	vm_copytophys(me, me->vw_fifoaddr, vmware_noop_fifo_config,
	              sizeof(vmware_noop_fifo_config));

	/* Enable the command FIFO */
	vm_setreg(me, SVGA_REG_CONFIG_DONE, 1);
}

PRIVATE NONNULL((1, 2)) void CC
vmware_v_getregs(struct svga_chipset *__restrict self, byte_t regbuf[]) {
	struct vmware_chipset *me = (struct vmware_chipset *)self;
	struct vmware_regs *reginfo = (struct vmware_regs *)regbuf;
	/* TODO */
	reginfo->vmr_index = vm_getindex(me);
}

PRIVATE NONNULL((1, 2)) void CC
vmware_v_setregs(struct svga_chipset *__restrict self, byte_t const regbuf[]) {
	struct vmware_chipset *me = (struct vmware_chipset *)self;
	struct vmware_regs const *reginfo = (struct vmware_regs const *)regbuf;
	/* TODO */
	vm_setindex(me, reginfo->vmr_index);
}

PRIVATE NONNULL((1, 2)) ssize_t CC
vmware_v_strings(struct svga_chipset *__restrict self,
                svga_chipset_enumstring_t cb, void *arg) {
	ssize_t temp, result = 0;
	struct vmware_chipset *me = (struct vmware_chipset *)self;
	char valbuf[MAX_C(lengthof(PRIMAXx16),
	                  lengthof(PRIMAXx32),
	                  lengthof(PRIMAXu32),
	                  lengthof("0x" PRIMAXx16 ".0x" PRIMAXx16),
	                  lengthof("0x" PRIMAXx8 ".0x" PRIMAXx8 "."
	                           "0x" PRIMAXx8 ".0x" PRIMAXx8))];
#define REPORT(name, ...)                \
	do {                                 \
		sprintf(valbuf, __VA_ARGS__);    \
		temp = (*cb)(arg, name, valbuf); \
		if unlikely (temp < 0)           \
			goto err;                    \
		result += temp;                  \
	}	__WHILE0
	REPORT("vmware.iobase", "%#" PRIx32, me->vw_iobase);
	REPORT("vmware.reg.CAPABILITIES", "%#" PRIx32, me->vw_caps);
	REPORT("vmware.reg.HOST_BITS_PER_PIXEL", "%#" PRIu32, me->vw_hbpp);
	REPORT("vmware.reg.FB_START", "%#" PRIx32, me->vw_fbstart);
	REPORT("vmware.reg.FB_SIZE", "%#" PRIx32, me->vw_fbsize);
	REPORT("vmware.reg.FIFO_START", "%#" PRIx32, me->vw_fifoaddr);
	REPORT("vmware.reg.FIFO_SIZE", "%#" PRIx32, me->vw_fifosize);
	REPORT("vmware.reg.MAX_WIDTH", "%#" PRIu32, me->vw_maxresx);
	REPORT("vmware.reg.MAX_HEIGHT", "%#" PRIu32, me->vw_maxresy);
	REPORT("pci.addr", "%#" PRIx32, me->vw_pci->pd_addr);
	REPORT("pci.vendor", "%#.4" PRIx16 ".%#.4" PRIx16, me->vw_pci->pd_vendor_id, me->vw_pci->pd_subvendor_id);
	REPORT("pci.device", "%#.4" PRIx16 ".%#.4" PRIx16, me->vw_pci->pd_device_id, me->vw_pci->pd_subdevice_id);
	REPORT("pci.class", "%#.2" PRIx8 ".%#.2" PRIx8 ".%#.2" PRIx8 ".%#.2" PRIx8,
	       me->vw_pci->pd_class_id, me->vw_pci->pd_subclass_id,
	       me->vw_pci->pd_progif_id, me->vw_pci->pd_revision);
	return result;
err:
	return temp;
#undef REPORT
}



/* Probe for VESA support.
 * @return: true:  Chipset found.
 * @return: false: Chipset isn't present. */
INTERN WUNUSED NONNULL((1)) bool CC
cs_vmware_probe(struct svga_chipset *__restrict self) {
	struct vmware_chipset *me = (struct vmware_chipset *)self;
#ifndef __KERNEL__
	me->vw_libpciaccess = NULL;
	me->vw_libphys = NULL;
	TRY
#endif /* !__KERNEL__ */
	{
		struct pci_device *pci;
#ifdef __KERNEL__
		pci = SLIST_FIRST(&pci_devices);
#else /* __KERNEL__ */
		/* Load+initialize libphys. */
		me->vw_libphys = dlopen(LIBPHYS_LIBRARY_NAME, RTLD_LOCAL);
		if unlikely(!me->vw_libphys)
			goto err_initfailed;
		*(void **)&me->vw_copytophys = dlsym(me->vw_libphys, "copytophys");
		if unlikely(!me->vw_copytophys)
			goto err_initfailed;

		/* Load+initialize libpciaccess. */
		pci = NULL;
		me->vw_libpciaccess = dlopen(LIBPCIACCESS_LIBRARY_NAME, RTLD_LOCAL);
		if (me->vw_libpciaccess) {
			typeof(pci_system_init) *pdyn_pci_system_init;
			typeof(__pci_devices) *pdyn_pci_devices;
			if ((*(void **)&pdyn_pci_system_init = dlsym(me->vw_libpciaccess, "pci_system_init")) == NULL ||
			    (*(void **)&pdyn_pci_devices = dlsym(me->vw_libpciaccess, "pci_devices")) == NULL ||
			    ((*pdyn_pci_system_init)() != EOK) || (pci = (*pdyn_pci_devices)()) == NULL) {
				dlclose(me->vw_libpciaccess);
				me->vw_libpciaccess = NULL;
			}
		}
#endif /* !__KERNEL__ */

		/* Find the relevant PCI device. */
		for (;; pci = SLIST_NEXT(pci, _pd_link)) {
			if (!pci)
				goto err_initfailed;
			if (pci->pd_vendor_id == PCI_VENDOR_ID_VMWARE &&
			    pci->pd_device_id == PCI_DEVICE_ID_VMWARE_SVGA2)
				break;
		}

		/* Remember the relevant PCI device. */
		me->vw_pci = pci;
		printk(KERN_INFO "[vmware] Chipset detected [pci: %#" PRIx32 "]\n", pci->pd_addr);

		/* Load video limits */
		if (!pci->pd_regions[0].pmr_is_IO)
			goto err_initfailed_late;
		if (!pci->pd_regions[0].pmr_addr)
			goto err_initfailed_late;
		me->vw_iobase = (uint16_t)pci->pd_regions[0].pmr_addr;
		printk(KERN_INFO "[vmware] iobase=%#" PRIx16 "\n", me->vw_iobase);
		me->vw_index  = (uint32_t)-1;
		printk(KERN_INFO "[vmware] Enable PCI BUSMASTER+MEMTOUCH+IOTOUCH\n");
		pci_device_cfg_writel(pci, PCI_DEV4,
		                      (pci_device_cfg_readl(pci, PCI_DEV4)) |
		                      (PCI_CDEV4_BUSMASTER | PCI_CDEV4_ALLOW_MEMTOUCH | PCI_CDEV4_ALLOW_IOTOUCH));

		vm_setreg(me, SVGA_REG_ID, SVGA_ID_2);
		{
			uint32_t ver = vm_getreg(me, SVGA_REG_ID);
			if (ver != SVGA_ID_2) {
				printk(KERN_WARNING "[vmware] Unsupported verison %#" PRIx32 " "
				                    "reported (expected: %#" PRIx32 ")\n",
				       ver, SVGA_ID_2);
				goto err_initfailed_late;
			}
		}

		/* Read memory config */
		me->vw_fbstart  = vm_getreg(me, SVGA_REG_FB_START);
		me->vw_fbsize   = vm_getreg(me, SVGA_REG_FB_SIZE);
		me->vw_fifoaddr = vm_getreg(me, SVGA_REG_MEM_START);
		me->vw_fifosize = vm_getreg(me, SVGA_REG_MEM_SIZE);
		me->sc_vmemsize = vm_getreg(me, SVGA_REG_VRAM_SIZE);

		/* Read display config */
		me->vw_caps     = vm_getreg(me, SVGA_REG_CAPABILITIES);
		me->vw_maxresx  = vm_getreg(me, SVGA_REG_MAX_WIDTH);
		me->vw_maxresy  = vm_getreg(me, SVGA_REG_MAX_HEIGHT);
		me->vw_hbpp     = vm_getreg(me, SVGA_REG_HOST_BITS_PER_PIXEL);

		/* Advertise our OS (we like to act like we're linux) */
		vm_setreg(me, SVGA_REG_GUEST_ID, SVGA_REG_GUEST_LINUX);

		/* Fill in operators and the like... */
		DBG_memset(&me->sc_ops, 0xcc, sizeof(me->sc_ops));
		me->sc_logicalwidth_max = UINT32_MAX; /* Max value that can physically be written */
		if (me->sc_logicalwidth_max > self->sc_vmemsize)
			me->sc_logicalwidth_max = self->sc_vmemsize;
		me->sc_ops.sco_fini            = &vmware_v_fini;
		me->sc_ops.sco_modeinfosize    = sizeof(struct vmware_modeinfo);
		me->sc_ops.sco_strings         = &vmware_v_strings;
		me->sc_ops.sco_getmode         = &vmware_v_getmode;
		me->sc_ops.sco_setmode         = &vmware_v_setmode;
		me->sc_ops.sco_getregs         = &vmware_v_getregs;
		me->sc_ops.sco_setregs         = &vmware_v_setregs;
		me->sc_ops.sco_regsize         = sizeof(struct vmware_regs);
		me->sc_ops.sco_setdisplaystart = NULL; /* Not supported */
		me->sc_ops.sco_setlogicalwidth = NULL; /* Not supported */
		return true;
	}
#ifndef __KERNEL__
#undef pci_devices
	EXCEPT {
		if (me->vw_libphys)
			dlclose(me->vw_libphys);
		if (me->vw_libpciaccess)
			dlclose(me->vw_libpciaccess);
		RETHROW();
	}
#endif /* !__KERNEL__ */
err_initfailed_late:
	printk(KERN_ERR "[vmware] Adapter initialization failed\n");
err_initfailed:
#ifndef __KERNEL__
	if (me->vw_libphys)
		dlclose(me->vw_libphys);
	if (me->vw_libpciaccess)
		dlclose(me->vw_libpciaccess);
#endif /* !__KERNEL__ */
	return false;
}

DECL_END
#endif /* CONFIG_HAVE_LIBSVGADRV_CHIPSET_VMWARE */

#endif /* !GUARD_LIBSVGADRV_CS_VMWARE_C */
