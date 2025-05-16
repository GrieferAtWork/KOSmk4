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
#ifndef GUARD_LIBSVGADRV_CS_VMWARE_H
#define GUARD_LIBSVGADRV_CS_VMWARE_H 1

#include "api.h"
/**/

#ifdef CONFIG_HAVE_LIBSVGADRV_CHIPSET_VMWARE
#include <kos/anno.h>
#include <kos/types.h>
#include <sys/io.h>

#include <stdbool.h>

#include <libphys/phys.h>
#include <libsvgadrv/chipset.h>
#include <libsvgadrv/chipsets/vmware.h>

DECL_BEGIN

struct pci_device;

struct vmware_regs {
	uint32_t vmr_index; /* SVGA_INDEX */
	uint32_t vmr_regs[1]; /* TODO */
};

struct vmware_modeinfo: svga_modeinfo {
	uint8_t vmi_modeid; /* VMWare mode ID, or (uint8_t)-1 if this is a VGA mode */
};

struct vmware_chipset: svga_chipset {
	uint32_t           vw_index;        /* Last-accessed register number (value of "SVGA_INDEX") */
	uint32_t           vw_caps;         /* [const] SVGA_REG_CAPABILITIES */
	uint32_t           vw_hbpp;         /* [const] SVGA_REG_HOST_BITS_PER_PIXEL */
	PHYS uint32_t      vw_fbstart;      /* [const] SVGA_REG_FB_START */
	uint32_t           vw_fbsize;       /* [const] SVGA_REG_FB_SIZE */
	PHYS uint32_t      vw_fifoaddr;     /* [const] SVGA_REG_FIFO_START */
	uint32_t           vw_fifosize;     /* [const] SVGA_REG_FIFO_SIZE */
	uint32_t           vw_maxresx;      /* [const] SVGA_REG_MAX_WIDTH */
	uint32_t           vw_maxresy;      /* [const] SVGA_REG_MAX_HEIGHT */
	uint16_t           vw_iobase;       /* [const] I/O-port base address. */
	struct pci_device *vw_pci;          /* [1..1][const] Associated PCI device. */
	uint32_t          *vm_fifo;         /* [1..1][const][owned] Memory mapping of "vw_fifoaddr" */
#ifdef __KERNEL__
	void              *vm_fifo_unmap_cookie; /* [1..1][owned] Unmap cookie for `vm_fifo' */
#else /* __KERNEL__ */
	void              *vw_libpciaccess; /* [1..1][const] dlopen(3D) handle for libpciaccess. */
	void              *vw_libphys;      /* [1..1][const] dlopen(3D) handle for libphys. */
	PMUNMAPPHYS        vw_munmapphys;   /* [1..1][const] munmapphys. */
#endif /* !__KERNEL__ */
};

/* @param: portno: SVGA_INDEX_PORT, SVGA_VALUE_PORT, ... */
#define vm_in(self, portno)     inl((self)->vw_iobase + (portno))
#define vm_out(self, portno, v) outl((self)->vw_iobase + (portno), v)

#define vm_getindex(self) (self)->vw_index
#define vm_setindex(self, index)                                           \
	((self)->vw_index == (index) || (vm_out(self, SVGA_INDEX_PORT, index), \
	                                 (self)->vw_index = (index), 1))
#define vm_getvalue(self)        vm_in(self, SVGA_VALUE_PORT)
#define vm_setvalue(self, value) vm_out(self, SVGA_VALUE_PORT, value)

#define vm_getreg(self, regno)    (vm_setindex(self, regno), vm_getvalue(self))
#define vm_setreg(self, regno, v) (vm_setindex(self, regno), vm_setvalue(self, v))


/* Probe for VESA support.
 * @return: true:  Chipset found.
 * @return: false: Chipset isn't present. */
INTDEF WUNUSED NONNULL((1)) bool CC
cs_vmware_probe(struct svga_chipset *__restrict self);


/* VESA Chipset driver initializer. */
#define SVGA_CHIPSET_DRIVER_INIT_VMWARE              \
	{                                                \
		.scd_cssize = sizeof(struct vmware_chipset), \
		.scd_probe  = &cs_vmware_probe,              \
		/* .scd_name = */ "vmware",                  \
	}

DECL_END
#endif /* CONFIG_HAVE_LIBSVGADRV_CHIPSET_VMWARE */

#endif /* !GUARD_LIBSVGADRV_CS_VMWARE_H */
