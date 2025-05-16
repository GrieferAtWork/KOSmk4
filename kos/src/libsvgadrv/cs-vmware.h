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
	uint32_t vmr_INDEX_PORT; /* SVGA_INDEX_PORT */
	uint32_t vmr_REG_ID;
	uint32_t vmr_REG_ENABLE;
	uint32_t vmr_REG_WIDTH;
	uint32_t vmr_REG_HEIGHT;
	uint32_t vmr_REG_DEPTH;
	uint32_t vmr_REG_BPP;
	uint32_t vmr_REG_CONFIG_DONE;
	uint32_t vmr_REG_SYNC;
	uint32_t vmr_REG_GUEST_ID;
	uint32_t vmr_REG_CURSOR_ID;
	uint32_t vmr_REG_CURSOR_X;
	uint32_t vmr_REG_CURSOR_Y;
	uint32_t vmr_REG_CURSOR_ON;
	uint32_t vmr_REG_PITCHLOCK;
	uint32_t vmr_REG_PALETTE[(SVGA_PALETTE_END + 1) - SVGA_PALETTE_BASE];
	COMPILER_FLEXIBLE_ARRAY(uint32_t, vmr_REG_SCRATCH);
#define sizeof__vmware_regs(nscratch) \
	(offsetof(struct vmware_regs, vmr_REG_SCRATCH) + (nscratch) * 4)
};

struct vmware_modeinfo: svga_modeinfo {
	uint8_t vmi_modeid; /* VMWare mode ID, or (uint8_t)-1 if this is a VGA mode */
};

/* Max # of words that can be allocated for fifo operations */
#define VMWARE_MAX_FIFO_COMMAND_WORDS 8

struct vmware_chipset: svga_chipset {
	uint32_t           vw_index;        /* Last-accessed register number (value of "SVGA_INDEX_PORT") */
	uint32_t           vw_caps;         /* [const] SVGA_REG_CAPABILITIES */
	uint32_t           vw_hbpp;         /* [const] SVGA_REG_HOST_BITS_PER_PIXEL */
	uint32_t           vw_nscratch;     /* [const] SVGA_REG_SCRATCH_SIZE */
	PHYS uint32_t      vw_fbstart;      /* [const] SVGA_REG_FB_START */
	uint32_t           vw_fbsize;       /* [const] SVGA_REG_FB_SIZE */
	PHYS uint32_t      vw_fifoaddr;     /* [const] SVGA_REG_MEM_START */
	uint32_t           vw_fifosize;     /* [const] SVGA_REG_MEM_SIZE */
	uint32_t           vw_maxresx;      /* [const] SVGA_REG_MAX_WIDTH */
	uint32_t           vw_maxresy;      /* [const] SVGA_REG_MAX_HEIGHT */
	uint16_t           vw_iobase;       /* [const] I/O-port base address. */
	struct pci_device *vw_pci;          /* [1..1][const] Associated PCI device. */
	uint32_t volatile *vm_fifo;         /* [1..1][const][owned] Memory mapping of "vw_fifoaddr" */
	uint32_t           vw_fifo_caps;    /* [lock(EXTERN)] SVGA_FIFO_CAPABILITIES */
	uint32_t           vw_fifo_rfsz;    /* [lock(EXTERN)] Size of the FIFO register file */
#define vw_fifo_min    vw_fifo_rfsz     /* SVGA_FIFO_MIN */
#define vw_fifo_max    vw_fifosize      /* SVGA_FIFO_MAX */
#define vm_fifo_hascap(self, cap)   ((self)->vw_fifo_caps & (cap))
#define vm_fifo_hasreg(self, regno) (((regno) * 4) < (self)->vw_fifo_rfsz)
	uint32_t vm_fifo_debounce[VMWARE_MAX_FIFO_COMMAND_WORDS]; /* [lock(EXTERN)] Debounce buffer for fifo */
	bool     vm_fifo_debounce_inuse;    /* [lock(EXTERN)] Is `vm_fifo_debounce' being used? */
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
